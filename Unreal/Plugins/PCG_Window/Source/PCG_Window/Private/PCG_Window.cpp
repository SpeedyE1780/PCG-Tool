// Copyright Epic Games, Inc. All Rights Reserved.

#include "PCG_Window.h"
#include "PCG_WindowStyle.h"
#include "PCG_WindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "MazeGenerationWidget.h"
#include "SimpleGenerationWidget.h"
#include "MultiDimensionGenerationWidget.h"

static const FName SimpleGenerationID("SimpleGeneration");
static const FName MultiDimensionID("MultiDimensionGeneration");
static const FName WaveFunctionCollapseID("WaveFunctionCollapse");
static const FName MazeGenerationID("MazeGeneration");

#define LOCTEXT_NAMESPACE "FPCG_WindowModule"

void FPCG_WindowModule::StartupModule()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

    FPCG_WindowStyle::Initialize();
    FPCG_WindowStyle::ReloadTextures();

    FPCG_WindowCommands::Register();

    PluginCommands = MakeShareable(new FUICommandList);

    PluginCommands->MapAction(
        FPCG_WindowCommands::Get().OpenSimpleGenerationWindow,
        FExecuteAction::CreateRaw(this, &FPCG_WindowModule::SimpleGeneration),
        FCanExecuteAction());

    PluginCommands->MapAction(
        FPCG_WindowCommands::Get().OpenMultiDimensionGenerationWindow,
        FExecuteAction::CreateRaw(this, &FPCG_WindowModule::MultiDimensionGeneration),
        FCanExecuteAction());

    PluginCommands->MapAction(
        FPCG_WindowCommands::Get().OpenWaveFunctionCollapseGenerationWindow,
        FExecuteAction::CreateRaw(this, &FPCG_WindowModule::WaveFunctionCollapse),
        FCanExecuteAction());

    PluginCommands->MapAction(
        FPCG_WindowCommands::Get().OpenMazeWindow,
        FExecuteAction::CreateRaw(this, &FPCG_WindowModule::MazeGeneration),
        FCanExecuteAction());

    UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FPCG_WindowModule::RegisterMenus));

    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SimpleGenerationID, FOnSpawnTab::CreateRaw(this, &FPCG_WindowModule::OnSimpleGeneration))
        .SetDisplayName(LOCTEXT("FPCG_WindowTabTitle", "Simple Generation"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);

    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MultiDimensionID, FOnSpawnTab::CreateRaw(this, &FPCG_WindowModule::OnMultiDimensionGeneration))
        .SetDisplayName(LOCTEXT("FPCG_WindowTabTitle", "Multi Dimension Generation"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);

    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(WaveFunctionCollapseID, FOnSpawnTab::CreateRaw(this, &FPCG_WindowModule::OnWaveFunctionCollapse))
        .SetDisplayName(LOCTEXT("FPCG_WindowTabTitle", "Wave Function Collapse Generation"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);

    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MazeGenerationID, FOnSpawnTab::CreateRaw(this, &FPCG_WindowModule::OnMazeGeneration))
        .SetDisplayName(LOCTEXT("FPCG_WindowTabTitle", "Maze Generation"))
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

    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SimpleGenerationID);
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MultiDimensionID);
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WaveFunctionCollapseID);
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MazeGenerationID);
}

TSharedRef<SDockTab> FPCG_WindowModule::OnSimpleGeneration(const FSpawnTabArgs& SpawnTabArgs)
{
    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SSimpleGenerationWidget)
        ];
}

TSharedRef<SDockTab> FPCG_WindowModule::OnMultiDimensionGeneration(const FSpawnTabArgs& SpawnTabArgs)
{
    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SMultiDimensionGenerationWidget)
        ];
}

TSharedRef<SDockTab> FPCG_WindowModule::OnWaveFunctionCollapse(const FSpawnTabArgs& SpawnTabArgs)
{
    FText WidgetText = FText::Format(
        LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
        FText::FromString(TEXT("FPCG_WindowModule::OnWaveFunctionCollapse")),
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

TSharedRef<SDockTab> FPCG_WindowModule::OnMazeGeneration(const FSpawnTabArgs& SpawnTabArgs)
{
    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SMazeGenerationWidget)
        ];
}

void FPCG_WindowModule::SimpleGeneration()
{
    FGlobalTabmanager::Get()->TryInvokeTab(SimpleGenerationID);
}

void FPCG_WindowModule::MultiDimensionGeneration()
{
    FGlobalTabmanager::Get()->TryInvokeTab(MultiDimensionID);
}

void FPCG_WindowModule::WaveFunctionCollapse()
{
    FGlobalTabmanager::Get()->TryInvokeTab(WaveFunctionCollapseID);
}

void FPCG_WindowModule::MazeGeneration()
{
    FGlobalTabmanager::Get()->TryInvokeTab(MazeGenerationID);
}

void FPCG_WindowModule::RegisterMenus()
{
    // Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
    FToolMenuOwnerScoped OwnerScoped(this);

    {
        UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");
        UToolMenu* PCGMenu = Menu->AddSubMenu(OwnerScoped.GetOwner(), "LevelGeneration", "LevelEditor.MainMenu.PCG", FText::FromString("PCG Window"));
        {
            FToolMenuSection& Section = PCGMenu->FindOrAddSection("LevelGeneration");
            Section.Label = FText::FromString("Level Generation");
            Section.AddMenuEntryWithCommandList(FPCG_WindowCommands::Get().OpenSimpleGenerationWindow, PluginCommands);
            Section.AddMenuEntryWithCommandList(FPCG_WindowCommands::Get().OpenMultiDimensionGenerationWindow, PluginCommands);
            Section.AddMenuEntryWithCommandList(FPCG_WindowCommands::Get().OpenWaveFunctionCollapseGenerationWindow, PluginCommands);
            Section.AddMenuEntryWithCommandList(FPCG_WindowCommands::Get().OpenMazeWindow, PluginCommands);
        }
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPCG_WindowModule, PCG_Window)