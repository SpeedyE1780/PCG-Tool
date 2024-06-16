// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FPCG_WindowModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	void SimpleGeneration();
	void MultiDimensionGeneration();
	void WaveFunctionCollapse();
	void MazeGeneration();
	
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSimpleGeneration(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> OnMultiDimensionGeneration(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> OnWaveFunctionCollapse(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> OnMazeGeneration(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
