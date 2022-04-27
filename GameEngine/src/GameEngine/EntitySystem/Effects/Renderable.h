#pragma once
#include "../BaseComponent.h"
#include <bgfx/bgfx.h>



namespace GameEngine {


    class Renderable : public BaseComponent {
    

    public:
        Renderable();
        ~Renderable();
        void Update() override;

    };
}