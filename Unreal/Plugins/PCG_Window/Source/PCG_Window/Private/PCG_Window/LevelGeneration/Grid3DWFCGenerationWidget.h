// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "PCG_Window/LevelGeneration/Grid3DWFCGenerationData.h"

/**
 * 
 */
class PCG_WINDOW_API SGrid3DWFCGenerationWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SGrid3DWFCGenerationWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedPtr<IDetailsView> WFCDataWidget;
    UGrid3DWFCGenerationData* WFCData;
};
