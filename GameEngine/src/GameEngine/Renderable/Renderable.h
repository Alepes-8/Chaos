#pragma once
#include <cstdint>
#include <bgfx/bgfx.h>
#include <vector>

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


	class Renderable {
	protected:
		PosColorVertex* vertices;
        unsigned int v_len;
		uint16_t* indices;
        unsigned int i_len;

        //buffer to pass values to the shader 
        bgfx::VertexBufferHandle m_vbh;
        bgfx::IndexBufferHandle m_ibh;

        //matrix that define position of the renderable
        float mtx[16];
		
	public:
        static void init();
        void createBuffers();
        void setMtx(float m[]);
        void submit(bgfx::ViewId view, bgfx::ProgramHandle prog);
	};
}