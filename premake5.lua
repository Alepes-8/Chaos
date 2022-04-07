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
        "%{prj.name}/library/filament/lib/x86_64/mtd/",
        "%{prj.name}/library/SDL2/lib/x64"
    }

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/library/filament/include",
        "%{prj.name}/src",
        "%{prj.name}/library/spdlog/include",
        "%{prj.name}/library/SDL2/include"

    }

    links
    {
        "backend",
        "bluegl",
        "bluevk",
        "camutils",
        "civetweb",
        "dracodec",
        "filabridge",
        "filaflat",
        --"filamat",
        "filamat_lite",
        "filament-iblprefilter",
        "filament",
        "filameshio",
        "geometry",
        "gltfio",
        "gltfio_core",
        "gltfio_resources",
        "gltfio_resources_lite",
        "ibl-lite",
        --"ibl",
        "image",
        --"matdbg",
        "meshoptimizer",
        "shaders",
        "smol-v",
        "utils",
        "viewer",
        "vkshaders",
        "opengl32",
        "SDL2",
        "SDL2main",
        "SDL2test",
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            --"HZ_PLATFORM_WINDOWS",
            --"GE_BUILD_DLL"
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
        "GameEngine/library/filament/include",
        "GameEngine/library/spdlog/include",
        "GameEngine/src",
        "GameEngine/library/SDL2/include"
    }

    links
    {
        "GameEngine",
        "bin/Debug-windows-x86_64/GameEngine/GameEngine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            --"HZ_PLATFORM_WINDOWS"
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