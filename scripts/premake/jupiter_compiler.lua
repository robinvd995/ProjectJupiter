
function createJupiterCompiler()
    project "JupiterCompiler"
    location "JupiterCompiler"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    defaultOutDirectories()
    defaultLibDirectories()
    defaultFiles()
    defaultFilters()
    defaultIncludes()
    defaultDefines()

    defines { "JPT_CORE_ENABLE_LOGGER" }
    
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
