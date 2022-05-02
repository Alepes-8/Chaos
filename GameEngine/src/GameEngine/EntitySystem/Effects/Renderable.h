#pragma once
#include "../BaseComponent.h"
#include "GameEngine/EntitySystem/Physic/Transform.h"
#include <cstdint>
#include <bgfx/bgfx.h>
#include <vector>
#include <map>

#include "GameEngine/MathHelper.h"
#include <list>
#include <fstream>
#include <iostream>
#include <regex>
#include <GameEngine/Log.h>
#include <stdio.h>
#include <bx/math.h>


namespace GameEngine {
    struct PosColorVertex {
        // 3d space position
        float m_x;
        float m_y;
        float m_z;
        // Color value
        uint32_t m_abgr;

        static void init() {
            // start the attribute declaration
            ms_decl
                .begin()
                // Has three float values that denote position
                .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                // and a uint8 color value that denotes color
                .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
                .end();
        };

        static bgfx::VertexLayout ms_decl;
    };

    bgfx::ShaderHandle loadShader(const char* _name);

    class Renderable : public BaseComponent {
    protected:
        PosColorVertex* vertices;
        unsigned int v_len;
        uint16_t* indices;
        unsigned int i_len;


        bgfx::ShaderHandle vsh;
        bgfx::ShaderHandle fsh;

        //buffer to pass values to the shader 
        bgfx::VertexBufferHandle m_vbh;
        bgfx::IndexBufferHandle m_ibh;

        //matrix that define position of the renderable
        bgfx::ProgramHandle m_program;


    public:
        Renderable(GameObject* parent, const char* dirMesh, const char* dirFrag, const char* dirVert, float x_value, float y_value);
        void createBuffers();
        void setTransform(Transform t);
        void submit(bgfx::ViewId view, bgfx::ProgramHandle prog, uint64_t STATE);
        void parseObj(const std::string filename);
        std::map<std::string, float> parseMtl(const std::string filename);
        void print();
        ~Renderable();
        void Update() override;

        bgfx::ProgramHandle createProgram();
    };
}