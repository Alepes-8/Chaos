#include "CubeRenderable.h"

void GameEngine::CubeRenderable::setShader(Shader s) {
	shader = s;
}

void GameEngine::CubeRenderable::init() {
	PosColorVertex::init();

	m_vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(vertices, sizeof(vertices)),
		PosColorVertex::ms_decl
	);

	m_ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(indices, sizeof(indices))
	);
	PosColorVertex::init();
}

void GameEngine::CubeRenderable::render() {
	shader.setIndiceBufferHandle(m_ibh);
	shader.setVertexBufferHandle(m_vbh);
	shader.submit();
}