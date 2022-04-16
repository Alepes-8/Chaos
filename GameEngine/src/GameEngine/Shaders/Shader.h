#pragma once
#include <bgfx/bgfx.h>
#include <fstream>
#include <GameEngine/Log.h>

namespace GameEngine {
	class Shader {
	private:
		bgfx::ProgramHandle m_program;

		bgfx::ShaderHandle loadShader(const char* _name);

	public:
		Shader(){};
		Shader(char *vertex_shatder_name, char *fragment_shader_name);
		void setVertexBufferHandle(bgfx::VertexBufferHandle m_vbh);
		void setIndiceBufferHandle(bgfx::IndexBufferHandle m_ibh);
		void submit();
	};
}