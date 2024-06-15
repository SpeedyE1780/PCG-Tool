// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPCG.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FMyPCGModule"

void FMyPCGModule::StartupModule()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    // Get the base directory of this plugin
    FString BaseDir = IPluginManager::Get().FindPlugin("MyPCG")->GetBaseDir();
    FString MyPcgPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/PCGEngine/PCG-Engine-Cpp-API.dll"));
    // Add on the relative location of the third party dll and load it
    PCGLibraryHandle = !MyPcgPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*MyPcgPath) : nullptr;
    if (PCGLibraryHandle)
    {
        // Some code that will be executed if dll was found
        FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("PCGEngine", "LOADED DLL"));
    }
    else
    {
        FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("PCGEngineError", "Failed to load PCG Engine DLL"));
    }
}

void FMyPCGModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    // Free the dll handle
    FPlatformProcess::FreeDllHandle(PCGLibraryHandle);
    PCGLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyPCGModule, MyPCG)