// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "PCG_Window/LevelGeneration/MultiDimensionGenerationData.h"

/**
 * 
 */
class PCG_WINDOW_API SMultiDimensionGenerationWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SMultiDimensionGenerationWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedPtr<IDetailsView> MultipleDimensionDataWidget;
    UMultiDimensionGenerationData* MultipleDimensionData;
};
