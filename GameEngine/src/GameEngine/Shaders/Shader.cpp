#include "GameEngine/Shaders/Shader.h"

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
        else {
            std::cerr << printf("Shader not found.") << std::endl;
            exit(1);
        }
        const bgfx::Memory* mem = bgfx::copy(data, fileSize + 1);
        mem->data[mem->size - 1] = '\0';
        bgfx::ShaderHandle handle = bgfx::createShader(mem);
        bgfx::setName(handle, _name);
        return handle;
    }
}

void GameEngine::Shader::loadVertexShader(char* path) 
{
	vsh = loadShader(path);
}

void GameEngine::Shader::loadFragmentShader(char* path)
{
	fsh = loadShader(path);
}

bgfx::ProgramHandle GameEngine::Shader::createProgram() {
	return bgfx::createProgram(vsh, fsh, true);
}