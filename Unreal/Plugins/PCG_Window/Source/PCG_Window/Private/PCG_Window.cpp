// Copyright Epic Games, Inc. All Rights Reserved.

#include "PCG_Window.h"
#include "PCG_WindowStyle.h"
#include "PCG_WindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName PCG_WindowTabName("PCG_Window");

#define LOCTEXT_NAMESPACE "FPCG_WindowModule"

void FPCG_WindowModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FPCG_WindowStyle::Initialize();
	FPCG_WindowStyle::ReloadTextures();

	FPCG_WindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FPCG_WindowCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FPCG_WindowModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FPCG_WindowModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PCG_WindowTabName, FOnSpawnTab::CreateRaw(this, &FPCG_WindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FPCG_WindowTabTitle", "PCG_Window"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FPCG_WindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FPCG_WindowStyle::Shutdown();

	FPCG_WindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PCG_WindowTabName);
}

TSharedRef<SDockTab> FPCG_WindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FPCG_WindowModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("PCG_Window.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FPCG_WindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(PCG_WindowTabName);
}

void FPCG_WindowModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FPCG_WindowCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FPCG_WindowCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPCG_WindowModule, PCG_Window)