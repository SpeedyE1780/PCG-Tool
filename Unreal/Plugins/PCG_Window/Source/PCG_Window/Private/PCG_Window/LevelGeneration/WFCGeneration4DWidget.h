// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "PCG_Window/LevelGeneration/WFCGeneration4DData.h"

/**
 * 
 */
class PCG_WINDOW_API SWFCGeneration4DWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SWFCGeneration4DWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedPtr<IDetailsView> WFCDataWidget;
    UWFCGeneration4DData* WFCData;
};
