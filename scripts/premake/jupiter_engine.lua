
function createJupiterEngine()

    project "JupiterEngine"
    location "JupiterEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    defaultOutDirectories()
    defaultLibDirectories()
    defaultFiles()
    defaultFilters()
    defaultIncludes()
    defaultDefines()

    includeJupiterCore()

    defines "GLFW_INCLUDE_NONE"

    linkGlad()
    linkGLFW()
    includeGlad()
    includeGLFW()
end

function includeJupiterEngine()
    includedirs "JupiterEngine/include"
    links "JupiterEngine"
end
