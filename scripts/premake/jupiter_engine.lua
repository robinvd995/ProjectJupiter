
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

    includeStbImage()
    includeEntt()
    includeJupiterCore()

    defines "GLFW_INCLUDE_NONE"

    linkGlad()
    linkGLFW()
    includeGlad()
    includeGLFW()

    includeGoogleTest()
    linkGoogleTest()

    -- Include vulkan
    includeVulkan()

    -- Link vulkan libraries
    linkVulkanShaderC()
    linkVulkanSPIRVCross()

    -- Link and include PhysX
    addPhysX()
end

function includeJupiterEngine()
    includedirs "JupiterEngine/include"
    links "JupiterEngine"
end
