#include "Shader.h"


bgfx::ShaderHandle GameEngine::Shader::loadShader(const char* _name) {
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
        GameEngine::Log::GetCoreLogger()->error("couldn't open the shader");
        exit(1);
    }
    const bgfx::Memory* mem = bgfx::copy(data, fileSize + 1);
    mem->data[mem->size - 1] = '\0';
    bgfx::ShaderHandle handle = bgfx::createShader(mem);
    bgfx::setName(handle, _name);
    return handle;
}

GameEngine::Shader::Shader(char* vertex_shader_name, char* fragment_shader_name) {
    bgfx::ShaderHandle vsh = loadShader(vertex_shader_name);
    bgfx::ShaderHandle fsh = loadShader(fragment_shader_name);
    m_program = bgfx::createProgram(vsh, fsh, true);
}

void GameEngine::Shader::setVertexBufferHandle(bgfx::VertexBufferHandle m_vbh) {
    bgfx::setVertexBuffer(0, m_vbh);
}

void GameEngine::Shader::setIndiceBufferHandle(bgfx::IndexBufferHandle m_ibh) {
    bgfx::setIndexBuffer(m_ibh);
}

void GameEngine::Shader::submit() {
    bgfx::submit(0, m_program);
}

