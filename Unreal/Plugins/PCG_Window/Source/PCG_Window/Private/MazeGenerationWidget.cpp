// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/MazeGeneration/MazeGenerationWidget.h"
#include "PropertyEditorModule.h"


void SMazeGenerationWidget::Construct(const FArguments& InArgs)
{
    MazeData = NewObject<UMazeGenerationData>();

    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

    //FDetailsViewArgs is a struct of settings to customize our Details View Widget
    FDetailsViewArgs Args;
    Args.bHideSelectionTip = true;

    //Create the widget and store it in the PropertyWidget pointer
    MazeDataWidget = PropertyModule.CreateDetailView(Args);

    //Important! We set our new Details View to a mutable version of our custom settings.
    MazeDataWidget->SetObject(MazeData);

    ChildSlot
        [
            SNew(SBorder).Padding(FMargin(20))
                [
                    // Put your tab content here!
                    SNew(SVerticalBox)
                        + SVerticalBox::Slot().AutoHeight()
                        [
                            MazeDataWidget.ToSharedRef()
                        ]
                ]
        ];
}

