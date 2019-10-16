-- Author: Szymon Jackiewicz
-- 
-- Project: WinTUI
-- File: WinTUI.lua
-- Date: 11/10/2019

project "WinTUI"
    location "%{wks.location}/WinTUI"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"
    staticruntime "on"

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
