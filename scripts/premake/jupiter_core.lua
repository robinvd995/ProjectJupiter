
function createJupiterCore()
    project "JupiterCore"
    location "JupiterCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    defaultOutDirectories()
    defaultFiles()
    defaultFilters()
    defaultIncludes()
    defaultDefines()

    includeRapidXml()

end

function includeJupiterCore()

    includedirs { "JupiterCore/src" }
    links { "JupiterCore" }

end
