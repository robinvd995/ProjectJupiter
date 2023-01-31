
function createProjectIo()
    project "ProjectIo"
    location "ProjectIo"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    defaultOutDirectories()
    defaultLibDirectories()
    defaultFiles()
    defaultFilters()
    defaultIncludes()
    defaultDefines()

    defines {}
    
    includeJupiterCore()

    includeRapidXml()
    includeAssimp()
    includeGoogleTest()
    includeVulkan()

    linkAssimp()
    linkGoogleTest()

    linkVulkanShaderC()
    linkVulkanSPIRVCross()

end
