-- includes --
include "scripts/premake/jupiter_core.lua"
include "scripts/premake/project_io.lua"
include "scripts/premake/project_europa.lua"

-- library function includes --

function linkAssimp()
    links "assimp-vc142-mtd"
    links "zlibstaticd"
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
end

function defaultFilters()

    filter "system:windows"
        systemversion "latest"

        defines{"JPT_PLATFORM_WINDOWS"}

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
    includedirs {
        "%{prj.name}/src"
    }
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
configurations { "Debug", "Release" }


-- setup dependencies --
--createExternalDependencies()

-- create projects --

createProjectIo()
createProjectEuropa()
createJupiterCore()
