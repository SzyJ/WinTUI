-- Author: Szymon Jackiewicz
-- 
-- Project: WinTUI
-- File: sandbox.lua
-- Date: 011/10/2019

project "sandbox"
    location "%{wks.location}/sandbox"
    kind "ConsoleApp"
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
        "%{wks.location}/WinTUI/src",
    }

    defines {
        "WTUI_ALLOW_MENU_LOOP"
    }

    links {
        "WinTUI"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        runtime "Release"
        optimize "On"
