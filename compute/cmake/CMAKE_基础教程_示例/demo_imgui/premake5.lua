workspace "IMGUI_DEMO" 
	architecture "x64"

    configurations{
        "Debug",  
        "Release", 
        "Dist"
    }

-- outputdir = Debug-windows-x64
outputdir= "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
 


project "ImGuiDemoGlad"
    location "ImGuiDemoGlad"
    -- kind "SharedLib" 
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")
    
    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/Fonts/**.ttf",
    }
 
    --include文件操作
    includedirs{
        "%{prj.name}/../_dependency_/glad/include/",
        "%{prj.name}/../_dependency_/glfw/glfw-3.3.8.bin.WIN64/include/",
        "%{prj.name}/../_dependency_/imgui/1.88/",
        "%{prj.name}/../_dependency_/glm",
        -- "%{prj.name}/../_dependency_/glew/glew-2.1.0/include/",
        -- /Hazel/src 可链接其他项目的h头文件
		-- "%{IncludeDir.GLFW}"
    }

    libdirs {
		"%{prj.name}/../_dependency_/glfw/glfw-3.3.8.bin.WIN64/lib-vc2022", 
		-- "%{prj.name}/../_dependency_/glew/glew-2.1.0/lib/Release/x64", 
	 }
	 links{
		"glfw3.lib",
		"opengl32.lib",
		-- "glew32s.lib"
        -- "Hazel"  这里可以链接其他项目
	}

    --针对windows系统的操作
    filter "system:windows"
        cppdialect "C++14"
        staticruntime "On" 
        -- systemversion "10.0.19041.0" --启用静态运行时
        systemversion "latest"

        --预编译宏
        defines{

        }

        --编译后动作 通常为 复制 dll到特定位置
        postbuildcommands{
            -- ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        symbols "On"
 
    filter "configurations:Release"
        defines "HZ_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "HZ_DIST"
        optimize "On"



        
    filter {"system:windows", "configurations:Debug"}
                buildoptions "/MDd"
                
    filter {"system:windows", "configurations:Release"}
        buildoptions "/MD"
        
    filter {"system:windows", "configurations:Dist"}
        buildoptions "/MD"


