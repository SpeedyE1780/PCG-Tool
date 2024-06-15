// Copyright Epic Games, Inc. All Rights Reserved.

#include "PCG_Window.h"
#include "PCG_WindowStyle.h"
#include "PCG_WindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName SimpleGenerationID("SimpleGeneration");

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

    UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FPCG_WindowModule::RegisterMenus));

    FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SimpleGenerationID, FOnSpawnTab::CreateRaw(this, &FPCG_WindowModule::OnSimpleGeneration))
        .SetDisplayName(LOCTEXT("FPCG_WindowTabTitle", "Simple Generation"))
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
}

TSharedRef<SDockTab> FPCG_WindowModule::OnSimpleGeneration(const FSpawnTabArgs& SpawnTabArgs)
{
    FText WidgetText = FText::Format(
        LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
        FText::FromString(TEXT("FPCG_WindowModule::OnSimpleGeneration")),
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

void FPCG_WindowModule::SimpleGeneration()
{
    FGlobalTabmanager::Get()->TryInvokeTab(SimpleGenerationID);
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
        }
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPCG_WindowModule, PCG_Window)