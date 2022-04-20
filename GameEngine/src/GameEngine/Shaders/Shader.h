#pragma once
#include <bgfx/bgfx.h>
#include <fstream>
namespace GameEngine {
    bgfx::ShaderHandle loadShader(const char* _name);

    class Shader {
    private:
        bgfx::ShaderHandle vsh;
        bgfx::ShaderHandle fsh;


    public:
        void loadVertexShader(char* path);
        void loadFragmentShader(char* path);
        bgfx::ProgramHandle createProgram();
    };
}