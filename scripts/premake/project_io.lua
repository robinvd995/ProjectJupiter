
function createProjectIo()
    print("Generating project Io...")

    project "ProjectIo"
    location "ProjectIo"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    defaultOutDirectories()
    defaultFiles()
    defaultFilters()
    defaultIncludes()
    defaultDefines()

    defines {
        
    }

    includeRapidXml()
    includeJupiterCore()
end
