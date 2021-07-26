-- SOLUTION
workspace "Arcana Tools"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

-- PROJECTS
-- Arcana Tools
-- 
-- [ Engine ] --------> [ Arcana ]
--                         ↑ ↑ ↑  
--                         | | |
--       [ Lab ] ----------+ | |
--                           | +------ [ Animator ]
--      [ Modeler ]----------+
--


-- Arcana
--  
project "Arcana"
    location "Arcana"
    kind "consoleapp"
    language "c++"
    
    targetdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"
    objdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"


    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.hpp",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.c",
        "%{prj.name}/**.glsl",
        "%{prj.name}/**.vert",
        "%{prj.name}/**.frag",
    }


    includedirs {
        -- Include Main Engine
        "Engine/src/",
        "Engine/dependencies/",
        

        -- Inlude the Tools
        "Tools/ArcaneLab/src",

        -- include all dependencies
        "dependencies/include/",
    }
    libdirs{
        "dependencies/lib/"
    }
    links {
        "Engine",
        "ArcaneLab",
        -- OpenGL
        "opengl32.lib",
        -- Vulkan
        
        -- Direct X
        -- 11

        -- 12
        -- "yaml-cppd.lib"

    }
    defines{
        
    }
    filter "system:windows"
        cppdialect "c++latest"
        staticruntime "off"
        systemversion "latest"

        defines {
            "WIN32",
        }
    filter "configurations:Debug"
        defines { 
            "_DEBUG"
        }
        symbols "on"
        buildoptions "/MDd"
        
    filter "configurations:Release"
        defines {
            "_DEBUG"
        }
        optimize "on"
        symbols "on"
        buildoptions "/MD"
    filter "configurations:Release"
        defines {
            "NDEBUG"
        }
        optimize "on"
        symbols "off"
        buildoptions "/MD"

    
-- Engine
--
project "Engine"
    location "Engine"
    kind "staticLib"
    language "c++"

    targetdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"
    objdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"

    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.hpp",
        "%{prj.name}/**.cpp",
        "%{prj.name}/**.c",
        "%{prj.name}/**.glsl",
        "%{prj.name}/**.vert",
        "%{prj.name}/**.frag",
    }

    includedirs {
        "%{prj.name}/src/",

        "%{prj.name}/dependencies/",
        "dependencies/include/",
    }
    libdirs{
        "dependencies/lib/"
    }
    links {
        -- OpenGL
        "opengl32.lib",
        -- Vulkan
        
        -- Direct X
        -- 11

        -- 12
        -- "yaml-cppd.lib"
    }
    filter "system:windows"
        cppdialect "c++latest"
        staticruntime "off"
        systemversion "latest"

        defines {
            "WIN32",
            "ARCANA_ENGINE"
        }
    filter "configurations:Debug"
        defines { 
            "_DEBUG",
        }
        symbols "on"
        buildoptions "/MDd"
        
    filter "configurations:Release"
        defines {
            "_DEBUG",
        }
        optimize "on"
        symbols "on"
        buildoptions "/MD"

    filter "configurations:Release"
        defines {
            "NDEBUG",
            "DRENGR_API"
        }
        optimize "on"
        symbols "off"
        buildoptions "/MD"


-- ArcaneLabratory
--
project "ArcaneLab"
    location "Tools/ArcaneLab"
    kind "staticLib"
    language "c++"

    targetdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"
    objdir "bin/%{cfg.buildcfg}-%{cfg.buildsystem}-x64/%{prj.name}"

    files {
        "Tools/%{prj.name}/**.h",
        "Tools/%{prj.name}/**.hpp",
        "Tools/%{prj.name}/**.cpp",
        "Tools/%{prj.name}/**.c",
        "Tools/%{prj.name}/**.glsl",
        "Tools/%{prj.name}/**.vert",
        "Tools/%{prj.name}/**.frag",
    }

    includedirs {
        "Engine/src/",
        "Engine/dependencies/",
        "dependencies/include/",
    }
    libdirs{
        "dependencies/lib/"
    }
    links {
        "Engine",   
        -- OpenGL
        "opengl32.lib",
        -- Vulkan
        
        -- Direct X
        -- 11

        -- 12
        -- "yaml-cppd.lib"
    }
    filter "system:windows"
        cppdialect "c++latest"
        staticruntime "off"
        systemversion "latest"

        defines {
            "WIN32"

        }
    filter "configurations:Debug"
        defines { 
            "_DEBUG"
        }
        symbols "on"
        buildoptions "/MDd"
        
    filter "configurations:Release"
        defines {
            "_DEBUG"
        }
        optimize "on"
        symbols "on"
        buildoptions "/MD"
    filter "configurations:Release"
        defines {
            "NDEBUG"
        }
        optimize "on"
        symbols "off"
        buildoptions "/MD"

