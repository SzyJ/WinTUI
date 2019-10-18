-- Author: Szymon Jackiewicz
-- 
-- Project: WinTUI
-- File: premake5.lua
-- Date: 18/10/2019

workspace "WinTUI"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "sandbox"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    -- Dependencies
    extincludes = {}
    extincludes["WinTUI"]  = "%{wks.location}/WinTUI/include"

    -- WinTUI project .lib --
    include "premake_projects/WinTUI.lua"

    -- Main Project
    -- Requires: WinTUI
    include "premake_projects/sandbox.lua"
