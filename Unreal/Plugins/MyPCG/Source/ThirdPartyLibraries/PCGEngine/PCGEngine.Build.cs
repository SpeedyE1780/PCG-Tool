using System;
using System.IO;
using UnrealBuildTool;
public class PCGEngine : ModuleRules
{
    public PCGEngine(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Add the import library
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "pcg-engine-combination-generation.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "pcg-engine-cpp-api.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "pcg-engine-level-generation.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "pcg-engine-math.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "pcg-engine-maze-generation.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "pcg-engine-utility.lib"));
            // Delay-load the DLL, so we can load it from the right place first
            PublicDelayLoadDLLs.Add("pcg-engine-cpp-api.dll");
            // Ensure that the DLL is staged along with the executable
            RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/PCGEngine/pcg-engine-cpp-api.dll");
        }
    }
}