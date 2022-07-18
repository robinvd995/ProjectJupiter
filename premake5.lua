-- includes --
include "scripts/premake/jupiter_core.lua"
include "scripts/premake/project_io.lua"
include "scripts/premake/project_europa.lua"

-- library function includes --

function linkAssimp()
    links "assimp-vc142-mtd"
    links "zlibstaticd"
end

function linkGoogleTest()
    filter "configurations:Test"
    links "gtest"
    filter {}
end

function includeGoogleTest()
    filter "configurations:Test"
    includedirs "external/googletest/googletest/include"
    filter {}
end

function includeAssimp()
    includedirs "external/assimp/include"
end

function includeRapidXml()
    includedirs "external/rapidxml"
end

-- basic functions --

function defaultLibDirectories()
    libdirs "lib"
end

function defaultOutDirectories()
    targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/bin-int/" .. outputdir .. "/%{prj.name}")
end

function defaultFiles()
    files {
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }
    filter "configurations:Debug"
        files "%{prj.name}/src/**.cxx"

    filter "configurations:Release"
        files "%{prj.name}/src/**.cxx"

    filter "configurations:Test"
        files "%{prj.name}/test/**.cpp"
        files "%{prj.name}/test/**.cxx"

    filter {}
end

function defaultFilters()

    filter "system:windows"
        systemversion "latest"

        defines{"JPT_PLATFORM_WINDOWS"}

    filter "configurations:Test"
        defines {"JPT_DEBUG", "JPT_TEST"}
        runtime "Debug"
        symbols "on"

    filter "configurations:Debug"
        defines "JPT_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "JPT_RELEASE"
        runtime "Release"
        optimize "on"

    filter {}
end

function defaultIncludes()
    includedirs "%{prj.name}/src"
    filter "configurations:Debug"
        includedirs "%{prj.name}/test"
    filter {}
end

function defaultDefines()
    defines {

    }
end

function createExternalDependencies()
    group "External_Dependencies"

    --include "external/assimp"

    group ""
end

-- variables --

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- workspace --

workspace "Project Jupiter"
filename "jupiter"
architecture "x64"
configurations { "Debug", "Release", "Test" }


-- setup dependencies --
--createExternalDependencies()

-- create projects --

createProjectIo()
createProjectEuropa()
createJupiterCore()
