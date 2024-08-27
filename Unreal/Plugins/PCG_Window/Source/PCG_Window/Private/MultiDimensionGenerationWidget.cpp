// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/LevelGeneration/MultiDimensionGenerationWidget.h"

void SMultiDimensionGenerationWidget::Construct(const FArguments& InArgs)
{
    MultipleDimensionData = NewObject<UMultiDimensionGenerationData>();

    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

    //FDetailsViewArgs is a struct of settings to customize our Details View Widget
    FDetailsViewArgs Args;
    Args.bHideSelectionTip = true;

    //Create the widget and store it in the PropertyWidget pointer
    MultipleDimensionDataWidget = PropertyModule.CreateDetailView(Args);

    //Important! We set our new Details View to a mutable version of our custom settings.
    MultipleDimensionDataWidget->SetObject(MultipleDimensionData);

    ChildSlot
        [
            SNew(SBorder).Padding(FMargin(20))
                [
                    // Put your tab content here!
                    SNew(SVerticalBox)
                        + SVerticalBox::Slot().AutoHeight()
                        [
                            MultipleDimensionDataWidget.ToSharedRef()
                        ]
                ]
        ];
}
