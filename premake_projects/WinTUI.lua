-- Author: Szymon Jackiewicz
-- 
-- Project: WinTUI
-- File: WinTUI.lua
-- Date: 11/10/2019

project "WinTUI"
    location "%{wks.location}/WinTUI"
    kind "StaticLib"
    language "C++"
    systemversion "latest"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/src",
    }

    filter {"system:windows", "configurations:Release"}
        buildoptions "/MT"
