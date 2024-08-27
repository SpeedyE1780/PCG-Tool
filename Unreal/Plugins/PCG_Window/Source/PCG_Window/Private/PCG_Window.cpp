// Copyright Epic Games, Inc. All Rights Reserved.

#include "PCG_Window.h"
#include "PCG_WindowStyle.h"
#include "PCG_WindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

#include "PCG_Window/CombinationGeneration/CombinationGenerationWidget.h"

#include "PCG_Window/MazeGeneration/MazeGenerationWidget.h"

#include "PCG_Window/LevelGeneration/SimpleGenerationWidget.h"
#include "PCG_Window/LevelGeneration/MultiDimensionGenerationWidget.h"
#include "PCG_Window/LevelGeneration/WFCGenerationWidget.h"

#include "PCG_Window/SequenceGeneration/SequenceGenerationWidget.h"

static const FName SimpleGenerationID("SimpleGeneration");
static const FName MultiDimensionID("MultiDimensionGeneration");
static const FName WaveFunctionCollapseID("WaveFunctionCollapse");
static const FName MazeGenerationID("MazeGeneration");
static const FName CombinationGenerationID("CombinationGeneration");
static const FName SequenceGenerationID("SequenceGeneration");

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

    PluginCommands->MapAction(
        FPCG_WindowCommands::Get().OpenCombinationWindow,
        FExecuteAction::CreateRaw(this, &FPCG_WindowModule::CombinationGeneration),
        FCanExecuteAction());

    PluginCommands->MapAction(
        FPCG_WindowCommands::Get().OpenSequenceWindow,
        FExecuteAction::CreateRaw(this, &FPCG_WindowModule::SequenceGeneration),
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

    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CombinationGenerationID, FOnSpawnTab::CreateRaw(this, &FPCG_WindowModule::OnCombinationGeneration))
        .SetDisplayName(LOCTEXT("FPCG_WindowTabTitle", "Combination Generation"))
        .SetMenuType(ETabSpawnerMenuType::Hidden);

    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SequenceGenerationID, FOnSpawnTab::CreateRaw(this, &FPCG_WindowModule::OnSequenceGeneration))
        .SetDisplayName(LOCTEXT("FPCG_WindowTabTitle", "Sequence Generation"))
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
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CombinationGenerationID);
    FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SequenceGenerationID);
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
    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SWFCGenerationWidget)
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

TSharedRef<SDockTab> FPCG_WindowModule::OnCombinationGeneration(const FSpawnTabArgs& SpawnTabArgs)
{
    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SCombinationGenerationWidget)
        ];
}

TSharedRef<SDockTab> FPCG_WindowModule::OnSequenceGeneration(const FSpawnTabArgs& SpawnTabArgs)
{
    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SSequenceGenerationWidget)
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

void FPCG_WindowModule::CombinationGeneration()
{
    FGlobalTabmanager::Get()->TryInvokeTab(CombinationGenerationID);
}

void FPCG_WindowModule::SequenceGeneration()
{
    FGlobalTabmanager::Get()->TryInvokeTab(SequenceGenerationID);
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
        }

        {
            FToolMenuSection& Section = PCGMenu->FindOrAddSection("MazeGeneration");
            Section.Label = FText::FromString("Maze Generation");
            Section.AddMenuEntryWithCommandList(FPCG_WindowCommands::Get().OpenMazeWindow, PluginCommands);
        }

        {
            FToolMenuSection& Section = PCGMenu->FindOrAddSection("CombinationGeneration");
            Section.Label = FText::FromString("Combination Generation");
            Section.AddMenuEntryWithCommandList(FPCG_WindowCommands::Get().OpenCombinationWindow, PluginCommands);
        }

        {
            FToolMenuSection& Section = PCGMenu->FindOrAddSection("SequenceGeneration");
            Section.Label = FText::FromString("Sequence Generation");
            Section.AddMenuEntryWithCommandList(FPCG_WindowCommands::Get().OpenSequenceWindow, PluginCommands);
        }
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPCG_WindowModule, PCG_Window)