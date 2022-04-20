#include "ObjParser.h"


/// <summary>
/// This functionne parse an obj file in order to create a Renderable object
/// </summary>
/// <param name="filename"> The path to the .obj file</param>
/// <returns> A Renderable object corresponding to the .obj file</returns>
Renderable parseObj(string filename)
{
    //Renderable to return
    Renderable result = Renderable();


    //open the file
    std::ifstream in(filename, std::ios::in);
    if (!in)
    {
        std::cerr << "Cannot open " << filename << std::endl;
        exit(1);

    }

    //parse the file
    string line;
    regex v("v (-?\\d+\.\\d+) (-?\\d+\.\\d+) (-?\\d+\.\\d+).*$");
    regex vt("vt (-?\\d+\.\\d+) (-?\\d+\.\\d+).*$");
    regex vn("vn (-?\\d+\.\\d+) (-?\\d+\.\\d+) (-?\\d+\.\\d+).*$");
    regex f("f (\\d+)/(\\d+)/(\\d+) (\\d+)/(\\d+)/(\\d+) (\\d+)/(\\d+)/(\\d+).*$");

    while (getline(in, line)) {
        smatch match;

        //check for vertices
        regex_match(line, match, v);
        if (regex_match(line, match, v)) {
            if (match.size() != 4) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - number of vertex coordinates incorrect\n");
                exit(1);
            }

            string x = match[1].str();
            string y = match[2].str();
            string z = match[3].str();

            result.addVertex(math::float3(stof(x), stof(y), stof(z)));
        }

        //check for texture
        else if (regex_match(line, match, vt)) {
            if (match.size() != 3) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - number of vertex texture coordinates incorrect\n");
                exit(1);
            }

            string x = match[1].str();
            string y = match[2].str();

            result.addTexture(math::float2(stof(x), stof(y)));
        }

        //check for normales
        else if (regex_match(line, match, vn)) {
            if (match.size() != 4) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - number of normal coordinates incorrect\n");
                exit(1);
            }

            string x = match[1].str();
            string y = match[2].str();
            string z = match[2].str();

            result.addNormal(math::float3(stof(x), stof(y), stof(z)));
        }


        //check for faces (triangles)
        else if (regex_match(line, match, f)) {
            if (match.size() != 10) {
                GameEngine::Log::GetCoreLogger()->error("Error while parsing - number of face parameters incorrect\n");
                exit(1);
            }

            //vertex indices for the corresponding triangle
            string v1 = match[1].str();
            string v2 = match[4].str();
            string v3 = match[7].str();
            result.addVertexIndices(stoi(v1));
            result.addVertexIndices(stoi(v2));
            result.addVertexIndices(stoi(v3));

            //textures indices for the corresponding triangle
            string t1 = match[2].str();
            string t2 = match[5].str();
            string t3 = match[8].str();
            result.addTextureIndices(stoi(t1));
            result.addTextureIndices(stoi(t2));
            result.addTextureIndices(stoi(t3));

            //normals indices for the corresponding triangle
            string n1 = match[3].str();
            string n2 = match[6].str();
            string n3 = match[9].str();
            result.addNormalsIndices(stoi(n1));
            result.addNormalsIndices(stoi(n2));
            result.addNormalsIndices(stoi(n3));
        }
    }

    return result;
}
