#include "PathFinding.h"
#include <string>

GameEngine::PathFinding::PathFinding(GameObject* parent, const char* path) : BaseComponent(parent) {
	std::cout << "Create PathFinding" << std::endl;
	std::string stringPath = path;
	parentObj = parent;
	if (stringPath != "no") {
		std::cout << "Used Path" << std::endl;
		Init(path);
	}
}
GameEngine::PathFinding::~PathFinding() {
	std::cout << "Delete PathFinding" << std::endl;
}

static const int NAVMESHSET_MAGIC = 'M' << 24 | 'S' << 16 | 'E' << 8 | 'T'; //'MSET';
static const int NAVMESHSET_VERSION = 1;

struct NavMeshSetHeader
{
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams params;
};

struct NavMeshTileHeader
{
	dtTileRef tileRef;
	int dataSize;
};

static float frand()
{
	//	return ((float)(rand() & 0xffff)/(float)0xffff);
	return (float)rand() / (float)RAND_MAX;
}

/// <summary>
/// Loads the navmesh and sets up 
/// </summary>
/// /// <param name="path"> - Path to navmesh binary</param>
void GameEngine::PathFinding::Init(const char* path) {

	m_navMesh = LoadMesh(path);
	if(m_navMesh) std::cout << "navMesh loaded" << std::endl;


	//Init();

}
/// <summary>
/// Finds a random point and moves towards it
/// </summary>
void GameEngine::PathFinding::Init() {
	randomPathfinding = true;
	m_randomRadius = 30.0f;
	m_polyPickExt[0] = 2;
	m_polyPickExt[1] = 4;
	m_polyPickExt[2] = 2;

	startPoint = this->getParentTransform();
	m_spos[0] = this->startPoint->getPosition().pos[0];
	m_spos[1] = this->startPoint->getPosition().pos[1];
	m_spos[2] = this->startPoint->getPosition().pos[2];
	m_navQuery = dtAllocNavMeshQuery();
	m_navQuery->init(m_navMesh, 2048);
	//dtStatus status = m_navQuery->findRandomPoint(&m_filter, frand, &m_startRef, m_spos);
	float dist[3] = { 1,1,1 };
	float nearPt[3];
	m_navQuery->findNearestPoly(m_spos, dist, &m_filter, &m_startRef, nearPt);
	//std::cout << m_startRef << std::endl;
	std::cout << "Starting position:" << std::endl;
	std::cout << nearPt[0] << std::endl;
	std::cout << nearPt[1] << std::endl;
	std::cout << nearPt[2] << std::endl;
	m_sposSet = true;
	dtStatus status = m_navQuery->findRandomPointAroundCircle(m_startRef, m_spos, m_randomRadius, &m_filter, frand, &m_endRef, m_epos);
	if (dtStatusSucceed(status))
	{
		std::cout << "Movetarget:" << std::endl;
		std::cout << m_epos[0] << std::endl;
		std::cout << m_epos[1] << std::endl;
		std::cout << m_epos[2] << std::endl;
		m_eposSet = true;
	}

	recalc();
}
/// <summary>
/// Set the navmesh
/// </summary>
/// <param name="navMesh"> - Navmesh to set</param>
void GameEngine::PathFinding::setNavMesh(dtNavMesh* navMesh) {
	m_navMesh = navMesh;
}

dtNavMesh* GameEngine::PathFinding::getNavMesh() {
	return m_navMesh;
}

/// <summary>
/// Set the movement target to a position in the worldspace
/// </summary>
/// <param name="xpos"> - x coordinate of the position</param>
/// <param name="ypos"> - y coordinate of the position</param>
/// <param name="zpos"> - z coordinate of the position</param>
void GameEngine::PathFinding::setTarget(float xpos, float ypos, float zpos)
{
	float dist[3] = { 1,1,1 };
	float nearPt[3];
	float nearPtStart[3];
	m_epos[0] = xpos;
	m_epos[1] = ypos;
	m_epos[2] = zpos;
	m_navQuery->findNearestPoly(m_epos, dist, &m_filter, &m_endRef, nearPt);
	m_epos[0] = nearPt[0];
	m_epos[1] = nearPt[1];
	m_epos[2] = nearPt[2];

	m_spos[0] = this->startPoint->getPosition().pos[0];
	m_spos[1] = this->startPoint->getPosition().pos[1];
	m_spos[2] = this->startPoint->getPosition().pos[2];
	m_navQuery->findNearestPoly(m_spos, dist, &m_filter, &m_startRef, nearPtStart);
	m_spos[0] = nearPtStart[0];
	m_spos[1] = nearPtStart[1];
	m_spos[2] = nearPtStart[2];

	recalc();
}



dtNavMesh* GameEngine::PathFinding::LoadMesh(const char* path) {
	FILE* fp = fopen(path, "rb");
	if (!fp) return 0;

	// Read header.
	NavMeshSetHeader header;
	size_t readLen = fread(&header, sizeof(NavMeshSetHeader), 1, fp);
	if (readLen != 1)
	{
		fclose(fp);
		std::cout << "Readlen 1 " << std::endl;
		return 0;
	}
	if (header.magic != NAVMESHSET_MAGIC)
	{
		fclose(fp);
		std::cout << "Magic" << std::endl;
		return 0;
	}
	if (header.version != NAVMESHSET_VERSION)
	{
		fclose(fp);
		std::cout << "Version" << std::endl;
		return 0;
	}

	dtNavMesh* mesh = dtAllocNavMesh();
	if (!mesh)
	{
		fclose(fp);
		std::cout << "No mesh" << std::endl;

		return 0;
	}
	dtStatus status = mesh->init(&header.params);
	if (dtStatusFailed(status))
	{
		fclose(fp);
		std::cout << "Failed init" << std::endl;

		return 0;
	}

	// Read tiles.
	for (int i = 0; i < header.numTiles; ++i)
	{
		NavMeshTileHeader tileHeader;
		readLen = fread(&tileHeader, sizeof(tileHeader), 1, fp);
		if (readLen != 1)
		{
			fclose(fp);
			std::cout << "Readlen 2" << std::endl;

			return 0;
		}

		if (!tileHeader.tileRef || !tileHeader.dataSize)
			break;

		unsigned char* data = (unsigned char*)dtAlloc(tileHeader.dataSize, DT_ALLOC_PERM);
		if (!data) break;
		memset(data, 0, tileHeader.dataSize);
		readLen = fread(data, tileHeader.dataSize, 1, fp);
		if (readLen != 1)
		{
			dtFree(data);
			fclose(fp);
			std::cout << "Readlen 3 " << std::endl;

			return 0;
		}

		mesh->addTile(data, tileHeader.dataSize, DT_TILE_FREE_DATA, tileHeader.tileRef, 0);
	}

	fclose(fp);

	return mesh;
}

int GameEngine::PathFinding::fixupCorridor(dtPolyRef* path, const int npath, const int maxPath,
	const dtPolyRef* visited, const int nvisited)
{
	int furthestPath = -1;
	int furthestVisited = -1;

	// Find furthest common polygon.
	for (int i = npath - 1; i >= 0; --i)
	{
		bool found = false;
		for (int j = nvisited - 1; j >= 0; --j)
		{
			if (path[i] == visited[j])
			{
				furthestPath = i;
				furthestVisited = j;
				found = true;
			}
		}
		if (found)
			break;
	}

	// If no intersection found just return current path. 
	if (furthestPath == -1 || furthestVisited == -1)
		return npath;

	// Concatenate paths.	

	// Adjust beginning of the buffer to include the visited.
	const int req = nvisited - furthestVisited;
	const int orig = rcMin(furthestPath + 1, npath);
	int size = rcMax(0, npath - orig);
	if (req + size > maxPath)
		size = maxPath - req;
	if (size)
		memmove(path + req, path + orig, size * sizeof(dtPolyRef));

	// Store visited
	for (int i = 0; i < req; ++i)
		path[i] = visited[(nvisited - 1) - i];

	return req + size;
}

// This function checks if the path has a small U-turn, that is,
// a polygon further in the path is adjacent to the first polygon
// in the path. If that happens, a shortcut is taken.
// This can happen if the target (T) location is at tile boundary,
// and we're (S) approaching it parallel to the tile edge.
// The choice at the vertex can be arbitrary, 
//  +---+---+
//  |:::|:::|
//  +-S-+-T-+
//  |:::|   | <-- the step can end up in here, resulting U-turn path.
//  +---+---+
int GameEngine::PathFinding::fixupShortcuts(dtPolyRef* path, int npath, dtNavMeshQuery* navQuery)
{
	if (npath < 3)
		return npath;

	// Get connected polygons
	static const int maxNeis = 16;
	dtPolyRef neis[maxNeis];
	int nneis = 0;

	const dtMeshTile* tile = 0;
	const dtPoly* poly = 0;
	if (dtStatusFailed(navQuery->getAttachedNavMesh()->getTileAndPolyByRef(path[0], &tile, &poly)))
		return npath;

	for (unsigned int k = poly->firstLink; k != DT_NULL_LINK; k = tile->links[k].next)
	{
		const dtLink* link = &tile->links[k];
		if (link->ref != 0)
		{
			if (nneis < maxNeis)
				neis[nneis++] = link->ref;
		}
	}

	// If any of the neighbour polygons is within the next few polygons
	// in the path, short cut to that polygon directly.
	static const int maxLookAhead = 6;
	int cut = 0;
	for (int i = dtMin(maxLookAhead, npath) - 1; i > 1 && cut == 0; i--) {
		for (int j = 0; j < nneis; j++)
		{
			if (path[i] == neis[j]) {
				cut = i;
				break;
			}
		}
	}
	if (cut > 1)
	{
		int offset = cut - 1;
		npath -= offset;
		for (int i = 1; i < npath; i++)
			path[i] = path[i + offset];
	}

	return npath;
}

bool GameEngine::PathFinding::inRange(const float* v1, const float* v2, const float r, const float h)
{
	const float dx = v2[0] - v1[0];
	const float dy = v2[1] - v1[1];
	const float dz = v2[2] - v1[2];
	return (dx * dx + dz * dz) < r * r && fabsf(dy) < h;
}


bool GameEngine::PathFinding::getSteerTarget(dtNavMeshQuery* navQuery, const float* startPos, const float* endPos,
	const float minTargetDist,
	const dtPolyRef* path, const int pathSize,
	float* steerPos, unsigned char& steerPosFlag, dtPolyRef& steerPosRef,
	float* outPoints, int* outPointCount)
{
	// Find steer target.
	static const int MAX_STEER_POINTS = 3;
	float steerPath[MAX_STEER_POINTS * 3];
	unsigned char steerPathFlags[MAX_STEER_POINTS];
	dtPolyRef steerPathPolys[MAX_STEER_POINTS];
	int nsteerPath = 0;
	navQuery->findStraightPath(startPos, endPos, path, pathSize,
		steerPath, steerPathFlags, steerPathPolys, &nsteerPath, MAX_STEER_POINTS);
	if (!nsteerPath)
		return false;

	if (outPoints && outPointCount)
	{
		*outPointCount = nsteerPath;
		for (int i = 0; i < nsteerPath; ++i)
			dtVcopy(&outPoints[i * 3], &steerPath[i * 3]);
	}


	// Find vertex far enough to steer to.
	int ns = 0;
	while (ns < nsteerPath)
	{
		// Stop at Off-Mesh link or when point is further than slop away.
		if ((steerPathFlags[ns] & DT_STRAIGHTPATH_OFFMESH_CONNECTION) ||
			!inRange(&steerPath[ns * 3], startPos, minTargetDist, 1000.0f))
			break;
		ns++;
	}
	// Failed to find good point to steer to.
	if (ns >= nsteerPath)
		return false;

	dtVcopy(steerPos, &steerPath[ns * 3]);
	steerPos[1] = startPos[1];
	steerPosFlag = steerPathFlags[ns];
	steerPosRef = steerPathPolys[ns];

	return true;
}

void GameEngine::PathFinding::recalc()
{
	if (!m_navMesh)
		return;

	if (m_sposSet)
		m_navQuery->findNearestPoly(m_spos, m_polyPickExt, &m_filter, &m_startRef, 0);
	else
		m_startRef = 0;

	if (m_eposSet)
		m_navQuery->findNearestPoly(m_epos, m_polyPickExt, &m_filter, &m_endRef, 0);
	else
		m_endRef = 0;

	m_pathFindStatus = DT_FAILURE;


	m_pathIterNum = 0;
	if (m_sposSet && m_eposSet && m_startRef && m_endRef)
	{
		m_navQuery->findPath(m_startRef, m_endRef, m_spos, m_epos, &m_filter, m_polys, &m_npolys, MAX_POLYS);

		m_nsmoothPath = 0;

		if (m_npolys)
		{
			// Iterate over the path to find smooth path on the detail mesh surface.
			dtPolyRef polys[MAX_POLYS];
			memcpy(polys, m_polys, sizeof(dtPolyRef) * m_npolys);
			int npolys = m_npolys;

			float iterPos[3], targetPos[3];
			m_navQuery->closestPointOnPoly(m_startRef, m_spos, iterPos, 0);
			m_navQuery->closestPointOnPoly(polys[npolys - 1], m_epos, targetPos, 0);

			static const float STEP_SIZE = 0.03f;
			static const float SLOP = 0.01f;

			m_nsmoothPath = 0;

			dtVcopy(&m_smoothPath[m_nsmoothPath * 3], iterPos);
			m_nsmoothPath++;

			// Move towards target a small advancement at a time until target reached or
			// when ran out of memory to store the path.
			while (npolys && m_nsmoothPath < MAX_SMOOTH)
			{
				// Find location to steer towards.
				float steerPos[3];
				unsigned char steerPosFlag;
				dtPolyRef steerPosRef;

				if (!getSteerTarget(m_navQuery, iterPos, targetPos, SLOP,
					polys, npolys, steerPos, steerPosFlag, steerPosRef))
					break;

				bool endOfPath = (steerPosFlag & DT_STRAIGHTPATH_END) ? true : false;
				bool offMeshConnection = (steerPosFlag & DT_STRAIGHTPATH_OFFMESH_CONNECTION) ? true : false;

				// Find movement delta.
				float delta[3], len;
				dtVsub(delta, steerPos, iterPos);
				len = dtMathSqrtf(dtVdot(delta, delta));
				// If the steer target is end of path or off-mesh link, do not move past the location.
				if ((endOfPath || offMeshConnection) && len < STEP_SIZE)
					len = 1;
				else
					len = STEP_SIZE / len;
				float moveTgt[3];
				dtVmad(moveTgt, iterPos, delta, len);

				// Move
				float result[3];
				dtPolyRef visited[16];
				int nvisited = 0;
				m_navQuery->moveAlongSurface(polys[0], iterPos, moveTgt, &m_filter,
					result, visited, &nvisited, 16);

				npolys = fixupCorridor(polys, npolys, MAX_POLYS, visited, nvisited);
				npolys = fixupShortcuts(polys, npolys, m_navQuery);

				float h = 0;
				m_navQuery->getPolyHeight(polys[0], result, &h);
				result[1] = h;
				dtVcopy(iterPos, result);

				// Handle end of path and off-mesh links when close enough.
				if (endOfPath && inRange(iterPos, steerPos, SLOP, 1.0f))
				{
					// Reached end of path.
					dtVcopy(iterPos, targetPos);
					if (m_nsmoothPath < MAX_SMOOTH)
					{
						dtVcopy(&m_smoothPath[m_nsmoothPath * 3], iterPos);
						m_nsmoothPath++;
					}
					break;
				}
				else if (offMeshConnection && inRange(iterPos, steerPos, SLOP, 1.0f))
				{
					// Reached off-mesh connection.
					float startPos[3], endPos[3];

					// Advance the path up to and over the off-mesh connection.
					dtPolyRef prevRef = 0, polyRef = polys[0];
					int npos = 0;
					while (npos < npolys && polyRef != steerPosRef)
					{
						prevRef = polyRef;
						polyRef = polys[npos];
						npos++;
					}
					for (int i = npos; i < npolys; ++i)
						polys[i - npos] = polys[i];
					npolys -= npos;

					// Handle the connection.
					dtStatus status = m_navMesh->getOffMeshConnectionPolyEndPoints(prevRef, polyRef, startPos, endPos);
					if (dtStatusSucceed(status))
					{
						if (m_nsmoothPath < MAX_SMOOTH)
						{
							dtVcopy(&m_smoothPath[m_nsmoothPath * 3], startPos);
							m_nsmoothPath++;
							// Hack to make the dotted path not visible during off-mesh connection.
							if (m_nsmoothPath & 1)
							{
								dtVcopy(&m_smoothPath[m_nsmoothPath * 3], startPos);
								m_nsmoothPath++;
							}
						}
						// Move position at the other side of the off-mesh link.
						dtVcopy(iterPos, endPos);
						float eh = 0.0f;
						m_navQuery->getPolyHeight(polys[0], iterPos, &eh);
						iterPos[1] = eh;
					}
				}

				// Store results.
				if (m_nsmoothPath < MAX_SMOOTH)
				{
					dtVcopy(&m_smoothPath[m_nsmoothPath * 3], iterPos);
					m_nsmoothPath++;
				}
			}
		}

	}
	else
	{
		m_npolys = 0;
		m_nsmoothPath = 0;
	}
}

/// <summary>
/// Moves on a pre calculated path, if it is done then it calculates a new point to move towards
/// </summary>
void GameEngine::PathFinding::Update() {
	if (!(timeStep >= m_nsmoothPath)) {
		float xpos, ypos, zpos;
		xpos = m_smoothPath[timeStep * 3];
		ypos = m_smoothPath[timeStep * 3 + 1];
		zpos = m_smoothPath[timeStep * 3 + 2];
		startPoint->SetTransform(xpos, ypos, zpos);
		timeStep++;
	}
	else if (randomPathfinding) {
		m_startRef = m_endRef;
		m_spos[0] = m_epos[0];
		m_spos[1] = m_epos[1];
		m_spos[2] = m_epos[2];
		dtStatus status = m_navQuery->findRandomPointAroundCircle(m_startRef, m_spos, m_randomRadius, &m_filter, frand, &m_endRef, m_epos);
		recalc();
		timeStep = 0;
	}
}
