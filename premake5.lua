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

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/library/filament",
        "%{prj.name}/src",
        "%{prj.name}/library/spdlog/include",
		"%{prj.name}/library/recastnavigation/DebugUtils/include",
		"%{prj.name}/library/recastnavigation/Recast/include",
		"%{prj.name}/library/recastnavigation/Detour/include"
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

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "GameEngine/library/filament",
        "GameEngine/library/spdlog/include",
        "GameEngine/src",
		"GameEngine/library/recastnavigation/Detour/include"
    }

    links
    {
        "GameEngine"
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