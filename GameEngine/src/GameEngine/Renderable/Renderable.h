#pragma once
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GameEngine/Shaders/Shader.h>
namespace GameEngine {
	class Renderable {
    public:
		virtual ~Renderable(){};
        virtual void setShader(Shader s) {};
        virtual void init(){};
        virtual void render(){};
	};

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
}