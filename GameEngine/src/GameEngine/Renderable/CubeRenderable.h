#pragma once
#include "Renderable.h"
#include <bgfx/bgfx.h>
#include <GameEngine/Shaders/Shader.h>

namespace GameEngine {
	class CubeRenderable : public Renderable {
	private:
		const struct PosColorVertex vertices[4] = {
			{  0.5f,  0.5f, 0.0f, 0xff0000ff },
			{  0.5f, -0.5f, 0.0f, 0xff0000ff },
			{ -0.5f, -0.5f, 0.0f, 0xff00ff00 },
			{ -0.5f,  0.5f, 0.0f, 0xff00ff00 }
		};

		const int indices[6] = {
			0,1,3,
			1,2,3
		};

		//buffers
		bgfx::VertexBufferHandle m_vbh;
		bgfx::IndexBufferHandle m_ibh;

		Shader shader;

	public:

		void setShader(Shader s) override;

		void init() override;

		void render() override;
	};
}