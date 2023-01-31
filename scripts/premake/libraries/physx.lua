-- PhysX SDK root folder
PHYSX_SDK = "E:/Libraries/PhysX/PhysX-104.1-physx-5.1.2";

-- PhysX include folder
PHYSX_INCLUDE = "%{PHYSX_SDK}/physx/include"

-- PhysX static library folders
PHYSX_STATIC_WIN64_CHECKED = "%{PHYSX_SDK}/physx/bin/win.x86_64.vc142.mt/checked"
PHYSX_STATIC_WIN64_DEBUG = "%{PHYSX_SDK}/physx/bin/win.x86_64.vc142.mt/debug"
PHYSX_STATIC_WIN64_PROFILE = "%{PHYSX_SDK}/physx/bin/win.x86_64.vc142.mt/profile"
PHYSX_STATIC_WIN64_RELEASE = "%{PHYSX_SDK}/physx/bin/win.x86_64.vc142.mt/release"

PHYSX_LIBRARIES_GENERAL = "PhysX_static_64.lib"
PHYSX_LIBRARIES_COMMON = "PhysXCommon_static_64.lib"
PHYSX_LIBRARIES_FOUNDATION = "PhysXFoundation_static_64.lib"
PHYSX_LIBRARIES_EXTENSIONS = "PhysXExtensions_static_64.lib"

PHYSX_LIBRARIES_COOKING = "PhysXCooking_static_64.lib"
PHYSX_LIBRARIES_CHARACTER_KINEMATIC = "PhysXCharacterKinematic_static_64.lib"
PHYSX_LIBRARIES_PVD_SDK = "PhysXPvdSDK_static_64.lib"
PHYSX_LIBRARIES_VEHICLE = "PhysXVehicle_static_64.lib"
PHYSX_LIBRARIES_VEHICLE2 = "PhysXVehicle2_static_64.lib"

function addPhysX()
    includePhysX()
    linkPhysX()
end

-- Adds PhysX include folder to include list
function includePhysX()
    includedirs "%{PHYSX_INCLUDE}"
end

-- Links all repsective PhysX libraries for all configurations
function linkPhysX()
    filter "configurations:Debug"
    linkPhysX_Checked()

    filter "configurations:Test"
    linkPhysX_Debug()

    filter "configurations:Release"
    linkPhysX_Release()
    filter {}
end

function linkPhysX_Debug()
    links "%{PHYSX_STATIC_WIN64_DEBUG}/%{PHYSX_LIBRARIES_GENERAL}"
    links "%{PHYSX_STATIC_WIN64_DEBUG}/%{PHYSX_LIBRARIES_COMMON}"
    links "%{PHYSX_STATIC_WIN64_DEBUG}/%{PHYSX_LIBRARIES_FOUNDATION}"
    links "%{PHYSX_STATIC_WIN64_DEBUG}/%{PHYSX_LIBRARIES_EXTENSIONS}"
end

function linkPhysX_Checked()
    links "%{PHYSX_STATIC_WIN64_CHECKED}/%{PHYSX_LIBRARIES_GENERAL}"
    links "%{PHYSX_STATIC_WIN64_CHECKED}/%{PHYSX_LIBRARIES_COMMON}"
    links "%{PHYSX_STATIC_WIN64_CHECKED}/%{PHYSX_LIBRARIES_FOUNDATION}"
    links "%{PHYSX_STATIC_WIN64_CHECKED}/%{PHYSX_LIBRARIES_EXTENSIONS}"
end

function linkPhysX_Profile()
    links "%{PHYSX_STATIC_WIN64_PROFILE}/%{PHYSX_LIBRARIES_GENERAL}"
    links "%{PHYSX_STATIC_WIN64_PROFILE}/%{PHYSX_LIBRARIES_COMMON}"
    links "%{PHYSX_STATIC_WIN64_PROFILE}/%{PHYSX_LIBRARIES_FOUNDATION}"
    links "%{PHYSX_STATIC_WIN64_PROFILE}/%{PHYSX_LIBRARIES_EXTENSIONS}"
end

function linkPhysX_Release()
    links "%{PHYSX_STATIC_WIN64_RELEASE}/%{PHYSX_LIBRARIES_GENERAL}"
    links "%{PHYSX_STATIC_WIN64_RELEASE}/%{PHYSX_LIBRARIES_COMMON}"
    links "%{PHYSX_STATIC_WIN64_RELEASE}/%{PHYSX_LIBRARIES_FOUNDATION}"
    links "%{PHYSX_STATIC_WIN64_RELEASE}/%{PHYSX_LIBRARIES_EXTENSIONS}"
end
