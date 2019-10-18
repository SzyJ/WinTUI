-- Author: Szymon Jackiewicz
-- 
-- Project: WinTUI
-- File: WinTUI.lua
-- Date: 18/10/2019

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
        "%{prj.location}/include/**.h",
        "%{prj.location}/build/**.cpp"
    }

    includedirs {
        "%{prj.location}/include",
    }

    filter "configurations:Debug"
        buildoptions "/MTd"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        buildoptions "/MT"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        buildoptions "/MT"
        runtime "Release"
        optimize "On"
