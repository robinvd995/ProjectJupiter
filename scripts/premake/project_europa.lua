
function createProjectEuropa()
    print("Generating project Europa...")

    project "ProjectEuropa"
        location "ProjectEuropa"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"

        defaultOutDirectories()
        defaultFiles()
        defaultFilters()
        defaultIncludes()
        defaultDefines()
end
