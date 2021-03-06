#include "Renderable.h"


bgfx::VertexLayout GameEngine::PosColorVertex::ms_decl;

/// <summary>
/// Destructor of the class
/// </summary>
GameEngine::Renderable::~Renderable() {
	std::cout << "Delete Renderable" << std::endl;
    delete(vertices);
    delete(indices);
}

GameEngine::Renderable::Renderable() : BaseComponent(nullptr)
{
    vertices = nullptr;
    indices = nullptr;
    i_len = 0;
    v_len = 0;
}

/// <summary>
/// Build a Renderable object using a .obj and .mtl file
/// </summary>
/// <param name="parent"> - Parent GameObject</param>
/// <param name="dirMesh"> - Path to the .obj and .mtl file. Format : dir/name without .obj or .mtl</param>
/// <param name="dirFrag"> - Path to the fragment shader</param>
/// <param name="dirVert"> - Path to the vertex shader</param>
GameEngine::Renderable::Renderable
(
    GameObject* parent,
    const char* dirMesh,
    const char* dirFrag,
    const char* dirVert
) : BaseComponent(parent)
{
    vsh = loadShader(dirFrag);
    fsh = loadShader(dirVert);
    m_program = createProgram();

    PosColorVertex::init();

    //if the mesh is in the cache load directly the mesh from the cache
    if (cache.find(dirMesh) != cache.cend())
    {
        initFromCache(parent, cache.at(dirMesh));
    }
    //if not load the mesh from obj and mtl files and add it to the cache
    else
    {
        parseObj(dirMesh);
        cache[dirMesh] = *this;
    }

    createBuffers();

    SetBoundingBox();
}

void GameEngine::Renderable::initFromCache(const BaseComponent& parent, const Renderable& r)
{
    vertices = (PosColorVertex*)calloc(r.v_len, sizeof(PosColorVertex));
    v_len = r.v_len;
    for (int i = 0; i < v_len; i++) {
        vertices[i] = r.vertices[i];
    }

    i_len = r.i_len;
    indices = (uint16_t*)calloc(r.i_len, sizeof(uint16_t));
    for (int i = 0; i < i_len; i++) {
        indices[i] = r.indices[i];
    }
}

/// <summary>
/// Create the buffers needed to pass values of vertices and indices to the shader program
/// </summary>
void GameEngine::Renderable::createBuffers()
{
    this->m_vbh = bgfx::createVertexBuffer(
        // Static data can be passed with bgfx::makeRef
        bgfx::makeRef(vertices, sizeof(PosColorVertex) * v_len),
        //bgfx::makeRef(vertices, sizeof(vertices)),
        PosColorVertex::ms_decl
    );

    this->m_ibh = bgfx::createIndexBuffer(
        // Static data can be passed with bgfx::makeRef
        bgfx::makeRef(indices, sizeof(uint16_t) * i_len)
        //bgfx::makeRef(indices, sizeof(indices))
    );
}


/// <summary>
///  Send the renderer to the shader program
/// </summary>
/// <param name="view"> - id of the view </param>
/// <param name="prog"> - shader program </param>
/// <param name="STATE">
/// <para> - BGFX_STATE_CULL_CCW for conter clockwise faces orientation </para> 
/// <para> - BGFX_STATE_CULL_CW for clockwise faces orientation </para>
/// </param>
void GameEngine::Renderable::submit(bgfx::ViewId view, bgfx::ProgramHandle prog, uint64_t STATE)
{
    Transform* parentTransform = this->getParentTransform();
    bgfx::setTransform(parentTransform->mtx);
    bgfx::setVertexBuffer(0, m_vbh);
    bgfx::setIndexBuffer(m_ibh);

    // Set render states.
    bgfx::setState(BGFX_STATE_DEFAULT | STATE);

    // Submit primitive for rendering to view 0.
    bgfx::submit(view, prog);
}

/// <summary>
/// Parse .obj file to create a Renderable. 
/// Note : this functino also needs .mtl file to works
/// </summary>
/// <param name="filename"> - Path to the .obj and .mtl file. Format : dir/name without .obj or .mtl</param>
void GameEngine::Renderable::parseObj(const std::string filename)
{
    std::list<GameEngine::Vector3> vertices;
    std::list<uint32_t> colors;
    std::list<int> indices;

    //Parse .mtl file to get colors
    std::map<std::string, float> material_dict = parseMtl(filename);

    //open the file
    std::ifstream in(filename + ".obj", std::ios::in);
    if (!in)
    {
        std::cerr << "Cannot open " << filename << ".obj" << std::endl;
        exit(1);

    }

    //parse the file
    std::string line;
    std::string current_mat;
    std::regex mat("^usemtl (.*)$");
    std::regex v("^v (.*) (.*) (.*)*$");
    std::regex vt("vt (.*) (.*).*$");
    std::regex vn("vn (.*) (.*) (.*).*$");
    std::regex f("f (.*)/(.*)/(.*) (.*)/(.*)/(.*) (.*)/(.*)/(.*).*$");

    while (getline(in, line)) {
        std::smatch match;

        //check for vertices
        if (regex_match(line, match, v)) {
            if (match.size() != 4) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - number of vertex coordinates incorrect\n");
                exit(1);
            }

            std::string x = match[1].str();
            std::string y = match[2].str();
            std::string z = match[3].str();

            //TODO implement vertices
            //result.addVertex(GameEngine::Vector3(stof(x), stof(y), stof(z)));
            vertices.push_back(GameEngine::Vector3(stof(x), stof(y), stof(z)));            
        }
        else if (regex_match(line, match, mat)) {
            if (match.size() != 2) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - error while reading material\n");
                exit(1);
            }

            current_mat = match[1].str();
        }

        //check for texture
        else if (regex_match(line, match, vt)) {
            if (match.size() != 3) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - number of vertex texture coordinates incorrect\n");
                exit(1);
            }

            std::string x = match[1].str();
            std::string y = match[2].str();

            //TODO implement tetures
            //result.addTexture(math::float2(stof(x), stof(y)));
        }

        //check for normales
        else if (regex_match(line, match, vn)) {
            if (match.size() != 4) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - number of normal coordinates incorrect\n");
                exit(1);
            }

            std::string x = match[1].str();
            std::string y = match[2].str();
            std::string z = match[2].str();

            //TODO implement normals
            //result.addNormal(math::float3(stof(x), stof(y), stof(z)));
        }


        //check for faces (triangles)
        else if (regex_match(line, match, f)) {
            if (match.size() != 10) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - number of face parameters incorrect\n");
                exit(1);
            }

            //vertex indices for the corresponding triangle
            std::string v1 = match[1].str();
            std::string v2 = match[4].str();
            std::string v3 = match[7].str();
            //TODO implement vertices index
            /*result.addIndex(stoi(v1));
            result.addIndex(stoi(v2));
            result.addIndex(stoi(v3));*/
            indices.push_back(stoi(v1));
            indices.push_back(stoi(v2));
            indices.push_back(stoi(v3));
            try {
                float c = material_dict.at(current_mat);
                colors.push_back(c);
                colors.push_back(c);
                colors.push_back(c);
            }
            catch (std::out_of_range) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - couldn't find a material\n");
            }
            

            //textures indices for the corresponding triangle
            std::string t1 = match[2].str();
            std::string t2 = match[5].str();
            std::string t3 = match[8].str();
            //TODO implements textures index
            /*result.addIndex(stoi(t1));
            result.addIndex(stoi(t2));
            result.addIndex(stoi(t3));*/

            //normals indices for the corresponding triangle
            std::string n1 = match[3].str();
            std::string n2 = match[6].str();
            std::string n3 = match[9].str();
            //TODO implements normals index
           /* result.addIndex(stoi(n1));
            result.addIndex(stoi(n2));
            result.addIndex(stoi(n3));*/
        }
    }
    this->v_len = vertices.size();
    this->vertices = (PosColorVertex*)calloc(this->v_len, sizeof(PosColorVertex));
    
    for (int i = 0; i < this->v_len; i++) {
        Vector3 v = vertices.front();
        vertices.pop_front();
        this->vertices[i] = PosColorVertex{ v.x, v.y, v.z, 0 };
    }

    assert(indices.size() == colors.size());
    this->i_len = indices.size();
    this->indices = (uint16_t*)calloc(this->i_len, sizeof(uint16_t));
    for (int i = 0; i < this->i_len; i++) {
        uint16_t indice = indices.front();
        indices.pop_front();
        uint32_t color = colors.front();
        colors.pop_front();
        this->vertices[indice - 1].m_abgr = color;
        this->indices[i] = indice - 1;
    }
}


/// <summary>
/// Parse a .mtl file
/// </summary>
/// <param name="filename"> - Path to the .mtl file</param>
/// <returns> Map of key the name of the material and value the RGB components</returns>
std::map<std::string, float> GameEngine::Renderable::parseMtl(const std::string filename)
{
    //output
    std::map<std::string, float> res = std::map<std::string, float>();

    //open the file
    std::ifstream in(filename + ".mtl", std::ios::in);
    if (!in)
    {
        std::cerr << "Cannot open " << filename << ".mtl" << std::endl;
        exit(1);
    }

    //parse the file
    std::string line;
    std::string current_name;

    while (getline(in, line)) {
        std::smatch match;
        std::regex n("^newmtl (.*)$");
        std::regex kd("^Kd (.*) (.*) (.*)$");

        //check for vertices
        if (regex_match(line, match, kd)) {
            if (match.size() != 4) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - number of colors values incorrect\n");
                exit(1);
            }
            std::string r = match[1].str();
            std::string g = match[2].str();
            std::string b = match[3].str();
            res.insert(std::pair(current_name, RGB(stof(r) * 255, stof(g) * 255, stof(b) * 255)));
        }
        else if (regex_match(line, match, n)) {
            if (match.size() != 2) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - error while parsing the name of material\n");
                exit(1);
            }
            current_name = match[1].str();
        }
    }
    return res;
}

/// <summary>
/// Print in the console the information of the current Renderable
/// </summary>
void GameEngine::Renderable::print()
{
    for (int i = 0; i < v_len; i++) {
        std::cout << "(" << vertices[i].m_x << "," << vertices[i].m_y << "," << vertices[i].m_z << ") col : " << vertices[i].m_abgr << std::endl;
    }

    for (int i = 0; i < i_len; i++) {
        std::cout << indices[i] << " ";
    }

    std::cout << std::endl;

    std::cout << "v_len : " << v_len << " - i_len : " << i_len << std::endl;
}


//util functions

/// <summary>
/// Load a shader
/// </summary>
/// <param name="_name">Path to the shader</param>
/// <returns>ShaderHandle</returns>
bgfx::ShaderHandle GameEngine::loadShader(const char* _name) {
    {
        char* data = new char[2048];
        std::ifstream file;
        size_t fileSize;
        file.open(_name);
        if (file.is_open()) {
            file.seekg(0, std::ios::end);
            fileSize = file.tellg();
            file.seekg(0, std::ios::beg);
            file.read(data, fileSize);
            file.close();
        }
        const bgfx::Memory* mem = bgfx::copy(data, fileSize + 1);
        mem->data[mem->size - 1] = '\0';
        bgfx::ShaderHandle handle = bgfx::createShader(mem);
        bgfx::setName(handle, _name);
        return handle;
    }
}
bgfx::ProgramHandle GameEngine::Renderable::createProgram() {
    return bgfx::createProgram(vsh, fsh, true);
}

void GameEngine::Renderable::SetBoundingBox() {
    float minX = 0;
    float minY = 0;
    float minZ = 0;
    float maxX = 0;
    float maxY = 0;
    float maxZ = 0;

    /*-----------to create the bounding box--------------*/

    for (int i = 0; i < v_len; i++) {
        if (vertices[i].m_x < minX) { minX = vertices[i].m_x; } //Smaller then the currently smallest x value
        else if (vertices[i].m_x > maxX) { maxX = vertices[i].m_x; } //Larger then the currently largest x value

        if (vertices[i].m_y < minY) { minY = vertices[i].m_y; } //Smaller then the currently smallest y value
        else if (vertices[i].m_y > maxY) { maxY = vertices[i].m_y; } //Larger then the currently largest y value

        if (vertices[i].m_z < minZ) { minZ = vertices[i].m_z; } //Smaller then the currently smallest x value
        else if (vertices[i].m_z > maxZ) { maxZ = vertices[i].m_z; } //Larger then the currently largest x value
    }


    boundingBox[0] = Vector3((float)minX, (float)minY, (float)minZ);
    boundingBox[1] = Vector3((float)maxX, (float)maxY, (float)maxZ);

}

void GameEngine::Renderable::GetBoundingBox(Vector3* min, Vector3* max) {
    *min = boundingBox[0];
    *max = boundingBox[1];
}

/// <summary>
/// Update the Renderable value and send it to the shader program
/// </summary>
void GameEngine::Renderable::Update() {

    submit(0, m_program, BGFX_STATE_CULL_CCW);
}