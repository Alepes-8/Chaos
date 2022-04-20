#include "Renderable.h"

bgfx::VertexLayout GameEngine::PosColorVertex::ms_decl;

void GameEngine::Renderable::init()
{
	PosColorVertex::init();
}

void GameEngine::Renderable::createBuffers()
{
    this->m_vbh = bgfx::createVertexBuffer(
        // Static data can be passed with bgfx::makeRef
        bgfx::makeRef(vertices, sizeof(vertices)),
        PosColorVertex::ms_decl
    );

    this->m_ibh = bgfx::createIndexBuffer(
        // Static data can be passed with bgfx::makeRef
        bgfx::makeRef(indices, sizeof(indices))
    );
}


void GameEngine::Renderable::setMtx(float* m)
{
    mtx = m;
}

void GameEngine::Renderable::submit(bgfx::ViewId view, bgfx::ProgramHandle prog)
{
    bgfx::setTransform(mtx);
    bgfx::setVertexBuffer(0, m_vbh);
    bgfx::setIndexBuffer(m_ibh);

    // Set render states.
    bgfx::setState(BGFX_STATE_DEFAULT);

    // Submit primitive for rendering to view 0.
    bgfx::submit(view, prog);
}

