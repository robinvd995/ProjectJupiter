-- includes --
include "scripts/premake/jupiter_core.lua"
include "scripts/premake/project_io.lua"
include "scripts/premake/project_europa.lua"

-- library function includes --

function includeRapidXml()

    includedirs "lib/rapidxml"

end

-- basic functions --

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

-- variables --

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- workspace --

workspace "Project Jupiter"
    filename "jupiter"
    architecture "x64"
    configurations { "Debug", "Release" }


-- create projects --

createProjectIo()
createProjectEuropa()
createJupiterCore()
