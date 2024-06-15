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
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void SimpleGeneration();
	void MultiDimensionGeneration();
	
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSimpleGeneration(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> OnMultiDimensionGeneration(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
