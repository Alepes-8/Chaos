#pragma once
#include "../BaseComponent.h"
#include "Recast.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"
#include "DetourCommon.h"
#include "RecastDebugDraw.h"
#include "GameEngine/EntitySystem/Physic/Transform.h"

namespace GameEngine {
	class PathFinding : public BaseComponent 
	{
	public:
		PathFinding(GameObject* parent, const char* path);
		~PathFinding();
		void Update() override;
		dtNavMesh* LoadMesh(const char* path);
		void Init(const char* path);
		void Init();
		void setNavMesh(dtNavMesh* navMesh);
		void setTarget(float xpos, float ypos, float zpos);
		dtNavMesh* getNavMesh();
		
	private:
		void recalc();
		int fixupCorridor(dtPolyRef* path, const int npath, const int maxPath,
			const dtPolyRef* visited, const int nvisited);
		static int fixupShortcuts(dtPolyRef* path, int npath, dtNavMeshQuery* navQuery);
		bool getSteerTarget(dtNavMeshQuery* navQuery, const float* startPos, const float* endPos,
			const float minTargetDist,
			const dtPolyRef* path, const int pathSize,
			float* steerPos, unsigned char& steerPosFlag, dtPolyRef& steerPosRef,
			float* outPoints = 0, int* outPointCount = 0);
		bool inRange(const float* v1, const float* v2, const float r, const float h);
		static const int MAX_POLYS = 256;
		static const int MAX_SMOOTH = 2048;
		dtNavMesh* m_navMesh;
		dtNavMeshQuery* m_navQuery;
		dtQueryFilter m_filter;
		dtPolyRef m_startRef;
		dtPolyRef m_endRef;
		dtStatus m_pathFindStatus;
		dtPolyRef m_polys[MAX_POLYS];
		float m_smoothPath[MAX_SMOOTH * 3];
		bool m_sposSet;
		bool m_eposSet;
		float m_polyPickExt[3];
		float m_epos[3];
		float m_spos[3];
		int m_npolys;
		int m_pathIterNum;
		int m_nsmoothPath;
		float m_randomRadius;
		GameObject* parentObj;
		Transform* startPoint;
		int timeStep = 0;
		bool randomPathfinding = false;

	};
}