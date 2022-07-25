-- includes --
include "scripts/premake/jupiter_core.lua"
include "scripts/premake/jupiter_engine.lua"

include "scripts/premake/project_io.lua"
include "scripts/premake/project_europa.lua"

include "scripts/premake/project_juno.lua"

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

function linkGlad()
    links "Glad"
end

function linkGLFW()
    links "GLFW"
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

function includeGlad()
    includedirs "external/glad/include"
end

function includeGLFW()
    includedirs "external/glfw/include"
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
        "%{prj.location}/src/**.c",
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.cpp",

        "%{prj.location}/include/**.c",
        "%{prj.location}/include/**.h",
        "%{prj.location}/include/**.hpp",
        "%{prj.location}/include/**.cpp"
    }
    filter "configurations:Debug"
        files "%{prj.location}/src/**.cxx"

    filter "configurations:Release"
        files "%{prj.location}/src/**.cxx"

    filter "configurations:Test"
        files "%{prj.location}/test/**.cpp"
        files "%{prj.location}/test/**.cxx"

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
    includedirs "%{prj.name}/include/%{prj.name}"
    filter "configurations:Test"
        includedirs "%{prj.name}/test"
    filter {}
end

function defaultDefines()
    defines {

    }
end

-- variables --

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- workspace --

workspace "Project Jupiter"
filename "jupiter"
architecture "x64"
configurations { "Debug", "Release", "Test" }

-- create external projects --
group "External"
include "external/glad"
include "external/glfw"
group ""

-- create projects --

createJupiterCore()
createJupiterEngine()

createProjectIo()

createProjectJuno()
