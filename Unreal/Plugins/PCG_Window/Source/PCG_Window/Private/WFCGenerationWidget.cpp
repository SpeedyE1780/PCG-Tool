// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/LevelGeneration/WFCGenerationWidget.h"

void SWFCGenerationWidget::Construct(const FArguments& InArgs)
{
    WFCData = NewObject<UWFCGenerationData>();

    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

    //FDetailsViewArgs is a struct of settings to customize our Details View Widget
    FDetailsViewArgs Args;
    Args.bHideSelectionTip = true;

    //Create the widget and store it in the PropertyWidget pointer
    WFCDataWidget = PropertyModule.CreateDetailView(Args);

    //Important! We set our new Details View to a mutable version of our custom settings.
    WFCDataWidget->SetObject(WFCData);

    ChildSlot
        [
            SNew(SBorder).Padding(FMargin(20))
                [
                    // Put your tab content here!
                    SNew(SVerticalBox)
                        + SVerticalBox::Slot().AutoHeight()
                        [
                            WFCDataWidget.ToSharedRef()
                        ]
                ]
        ];
}
