#pragma once
#include <bgfx/bgfx.h>
#include <fstream>
#include <iostream>

namespace GameEngine {
    bgfx::ShaderHandle loadShader(const char* _name);

    class Shader {
    private:
        bgfx::ShaderHandle vsh;
        bgfx::ShaderHandle fsh;

        /*void loadVertexShader(char* path);
        void loadFragmentShader(char* path);*/
    public:
        bgfx::ProgramHandle createProgram();
        Shader(char* frag, char* vert);

    };
}