
function createProjectJuno()

    project "Sanbox_Juno"
    location "Juno"
    kind "ConsoleApp"
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
    includeJupiterEngine()
end