#include "GameEngine/ObjParser/ObjParser.h"


/// <summary>
/// This functionne parse an obj file in order to create a Renderable object
/// </summary>
/// <param name="filename"> The path to the .obj file</param>
/// <returns> A Renderable object corresponding to the .obj file</returns>
GameEngine::Renderable parseObj(char* filename)
{
    //Renderable to return
    GameEngine::Renderable result = GameEngine::Renderable();

    //open the file
    std::ifstream in(filename, std::ios::in);
    if (!in)
    {
        std::cerr << "Cannot open " << filename << std::endl;
        exit(1);

    }

    //parse the file
    std::string line;
    std::regex v("v (-?\\d+\.\\d+) (-?\\d+\.\\d+) (-?\\d+\.\\d+).*$");
    std::regex vt("vt (-?\\d+\.\\d+) (-?\\d+\.\\d+).*$");
    std::regex vn("vn (-?\\d+\.\\d+) (-?\\d+\.\\d+) (-?\\d+\.\\d+).*$");
    std::regex f("f (\\d+)/(\\d+)/(\\d+) (\\d+)/(\\d+)/(\\d+) (\\d+)/(\\d+)/(\\d+).*$");

    while (getline(in, line)) {
        std::smatch match;

        //check for vertices
        regex_match(line, match, v);
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

    return result;
}
