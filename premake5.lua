workspace "GameEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GameEngine"
    location "GameEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    libdirs 
    {
        "%{prj.name}/library/bgfx/.build/win64_vs2017/bin",
        "%{prj.name}/library/SDL2/lib/x64",
        "%{prj.name}/library/jsoncpp/.Build/lib/Debug",
        "%{prj.name}/library/imgui/examples/libs/glfw/lib-vc2010-32",
        "%{prj.name}/library/imgui/examples/libs/glfw/lib-vc2010-64"       

        
    }

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/library/spdlog/include",
        "%{prj.name}/library/bgfx/include",
        "%{prj.name}/library/bx/include",
        "%{prj.name}/library/bgfx/examples/common",
        "%{prj.name}/library/bimg/include",
        "%{prj.name}/library/bgfx/3rdparty",
        "%{prj.name}/library/bx/include/compat/msvc",
        "%{prj.name}/library/sdl2/include",
        "%{prj.name}/library/jsoncpp/include",
        "%{prj.name}/library/imgui/backends",
        "%{prj.name}/library/imgui"
    }

    links
    {
        "SDL2",
        "SDL2main",
        "SDL2test",
        "SDL2_mixer",
        "bgfxDebug",
        "bimgDebug",
        "bimg_decodeDebug",
        "bxDebug",
        "example-14-shadowvolumesDebug",
        "example-commonDebug",
        "example-glueDebug",
        "jsoncpp",
        "jsoncpp_static",
        "glfw3"

    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
			"BX_CONFIG_DEBUG"

        }

    filter "configurations:Debug"
        defines "GE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "GE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "GE_DIST"
        runtime "Release"
        optimize "on"




project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    libdirs {"bin/Debug-windows-x86_64/GameEngine"}

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "GameEngine/src",
        "GameEngine/library/spdlog/include",
        "GameEngine/library/bgfx/include",
        "GameEngine/library/bx/include",
        "GameEngine/library/bgfx/examples/common",
        "GameEngine/library/bimg/include",
        "GameEngine/library/bgfx/3rdparty",
        "GameEngine/library/bx/include/compat/msvc",
        "GameEngine/library/sdl2/include",
        "GameEngine/library/jsoncpp/include",
        "GameEngine/library/imgui/backends",
        "GameEngine/library/imgui"


    }

    links
    {
        "GameEngine",
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            --"HZ_PLATFORM_WINDOWS"
			"BX_CONFIG_DEBUG"
        }

        postbuildcommands 
        {
            "{COPY} ../GameEngine/library/sdl2/lib/x64/SDL2.dll ../bin/" .. outputdir .. "/Game",
            "{COPY} ../GameEngine/library/jsoncpp/.Build/bin/Debug/jsoncpp.dll ../bin/" .. outputdir .. "/Game"

        }

    filter "configurations:Debug"
        defines "GE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "GE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "GE_DIST"
        runtime "Release"
        optimize "on"