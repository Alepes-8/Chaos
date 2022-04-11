#include "GameEngine.h"
#include <iostream>
#include <filamat/MaterialBuilder.h>

class Game : public GameEngine::Application
{
public:
	Game()
	{

	}
	~Game()
	{

	}
};

void* getNativeWindow(SDL_Window* sdlWindow) {
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    ASSERT_POSTCONDITION(SDL_GetWindowWMInfo(sdlWindow, &wmi), "SDL version unsupported!");
    HWND win = (HWND)wmi.info.win.window;
    return (void*)win;
}

struct Config {
    std::string title;
    std::string iblDirectory;
    std::string dirt;
    float scale = 1.0f;
    bool splitView = false;
    mutable filament::Engine::Backend backend = filament::Engine::Backend::DEFAULT;
    filament::camutils::Mode cameraMode = filament::camutils::Mode::ORBIT;
    bool resizeable = true;
    bool headless = false;
};

//static constexpr uint8_t BAKED_MATERIAL_PACKAGE[] = {
//#include "materials/aiDefaultMat.inc"
//};

filamat::Package buildMaterial() {
    // Must be called before any materials can be built.
    filamat::MaterialBuilder::init();

    filamat::MaterialBuilder builder;
    builder
        .name("My material")
        .material("void material (inout MaterialInputs material) {"
            "  prepareMaterial(material);"
            "  material.baseColor.rgb = float3(1.0, 0.0, 0.0);"
            "}")
        .shading(filamat::MaterialBuilder::Shading::LIT)
        .targetApi(filamat::MaterialBuilder::TargetApi::ALL)
        .platform(filamat::MaterialBuilder::Platform::ALL);

    filamat::Package package = builder.build();
    if (package.isValid()) {
        std::cout << "Success!" << std::endl;
    }

    // Call when finished building all materials to release internal MaterialBuilder resources.
    filamat::MaterialBuilder::shutdown();
    return package;
}

int main(int argc, char** argv)
{
    const static uint32_t indices[] = {
    0, 1, 2, 2, 3, 0 };

    const static filament::math::float3 vertices[] = {
        {-10, 0, -10},
        {-10, 0, 10},
        {10, 0, 10},
        {10, 0, -10},
    };

    filament::math::short4 tbn = filament::math::packSnorm16(
        filament::math::mat3f::packTangentFrame(
            filament::math::mat3f{
                filament::math::float3{1.0f, 0.0f, 0.0f}, filament::math::float3{0.0f, 0.0f, 1.0f},
                filament::math::float3{0.0f, 1.0f, 0.0f} })
                .xyzw);

    const static filament::math::short4 normals[]{ tbn, tbn, tbn, tbn };


    Config config;
    config.title = "hellotriangle";
    const int x = SDL_WINDOWPOS_CENTERED;
    const int y = SDL_WINDOWPOS_CENTERED;
    uint32_t windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE;
    SDL_Window* mWindow = SDL_CreateWindow("Filament", x, y, (int)720, (int)1280, windowFlags);

    void* nativeWindow = ::getNativeWindow(mWindow);
    // Create the Engine after the window in case this happens to be a single-threaded platform.
    // For single-threaded platforms, we need to ensure that Filament's OpenGL context is
    // current, rather than the one created by SDL.
    filament::Engine* engine = filament::Engine::create(config.backend);
    config.backend = engine->getBackend();
    void* nativeSwapChain = nativeWindow;
    filament::SwapChain* swapChain = engine->createSwapChain(nativeSwapChain);
    filament::Renderer* renderer = engine->createRenderer();

    filament::Camera* camera = engine->createCamera(utils::EntityManager::get().create());
    filament::View* view = engine->createView();
    filament::Scene* scene = engine->createScene();

    view->setCamera(camera);
    view->setScene(scene);


    filament::VertexBuffer* vertexBuffer = filament::VertexBuffer::Builder()
        .vertexCount(4)
        .bufferCount(2)
        .attribute(filament::VertexAttribute::POSITION, 0, filament::VertexBuffer::AttributeType::FLOAT3)
        .attribute(filament::VertexAttribute::TANGENTS, 1, filament::VertexBuffer::AttributeType::SHORT4)
        .normalized(filament::VertexAttribute::TANGENTS)
        .build(*engine);

    vertexBuffer->setBufferAt(*engine, 0, filament::VertexBuffer::BufferDescriptor(vertices, vertexBuffer->getVertexCount() * sizeof(vertices[0])));
    vertexBuffer->setBufferAt(*engine, 1, filament::VertexBuffer::BufferDescriptor(normals, vertexBuffer->getVertexCount() * sizeof(normals[0])));

    filament::IndexBuffer* indexBuffer = filament::IndexBuffer::Builder()
        .indexCount(6)
        .build(*engine);

    indexBuffer->setBuffer(*engine, filament::IndexBuffer::BufferDescriptor(
        indices, indexBuffer->getIndexCount() * sizeof(uint32_t)));

    filamat::Package package = buildMaterial();

    filament::Material* material = filament::Material::Builder()
        //.package((void*)BAKED_MATERIAL_PACKAGE, sizeof(BAKED_MATERIAL_PACKAGE))
        .package(package.getData(), package.getSize())
        .build(*engine);
    filament::MaterialInstance* materialInstance = material->createInstance();


    utils::Entity renderable = utils::EntityManager::get().create();
    // build a quad

    filament::RenderableManager::Builder(1)
        .boundingBox({ { -1, -1, -1 }, { 1, 1, 1 } })
        .material(0, materialInstance)
        .geometry(0, filament::RenderableManager::PrimitiveType::TRIANGLES, vertexBuffer, indexBuffer, 0, 6)
        .culling(false)
        .build(*engine, renderable);
    scene->addEntity(renderable);

    while (1)
    {
        // beginFrame() returns false if we need to skip a frame
        if (renderer->beginFrame(swapChain))
        {
            // for each View
            renderer->render(view);
            renderer->endFrame();
        }
        SDL_Delay(16);
        // std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    //engine->destroy(camera);


	printf("Starting GameEngine Hejsan\n");


	GameEngine::Log::Init();
	GameEngine::Log::GetCoreLogger()->warn("The code making this should be shortend with define in log.h");


	auto game = GameEngine::CreateApplication();
	game->Run();
	delete game;
    return 0;
}



GameEngine::Application* GameEngine::CreateApplication()
{
	return new Game;
}