// Fill out your copyright notice in the Description page of Project Settings.


#include "CombinationGenerationWidget.h"
#include "PropertyEditorModule.h"

void SCombinationGenerationWidget::Construct(const FArguments& InArgs)
{
    CombinationData = NewObject<UCombinationGenerationData>();

    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

    //FDetailsViewArgs is a struct of settings to customize our Details View Widget
    FDetailsViewArgs Args;
    Args.bHideSelectionTip = true;

    //Create the widget and store it in the PropertyWidget pointer
    CombinationDataWidget = PropertyModule.CreateDetailView(Args);

    //Important! We set our new Details View to a mutable version of our custom settings.
    CombinationDataWidget->SetObject(CombinationData);

    ChildSlot
        [
            SNew(SBorder).Padding(FMargin(20))
                [
                    // Put your tab content here!
                    SNew(SVerticalBox)
                        + SVerticalBox::Slot().AutoHeight()
                        [
                            CombinationDataWidget.ToSharedRef()
                        ]
                ]
        ];
}

