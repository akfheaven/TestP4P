// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class TestP4P : ModuleRules
{
    private string OpenCVDIR
    {
        get { return "D:/OpenCV/opencv-2.4.13/Buildx64Dy/install/x64/vc12"; }
    }

    private string CUDADIR
    {
        get { return "E:/CUDA/Toolkit"; }

    }

    public TestP4P(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateIncludePaths.AddRange(new string[] {
               Path.Combine(OpenCVDIR, "../../include/"),
                Path.Combine(CUDADIR, "include/")
        });


        PublicAdditionalLibraries.Add(Path.Combine(OpenCVDIR, "staticlib", "opencv_calib3d2413d.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(OpenCVDIR, "staticlib", "opencv_imgproc2413d.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(OpenCVDIR, "staticlib", "zlibd.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(OpenCVDIR, "staticlib", "opencv_core2413d.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(CUDADIR, "lib/x64", "cudart_static.lib"));
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
        // if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        // {
        //		if (UEBuildConfiguration.bCompileSteamOSS == true)
        //		{
        //			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        //		}
        // }


    }
}
