// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "CombinationGenerationData.h"

/**
 *
 */
class PCG_WINDOW_API SCombinationGenerationWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SCombinationGenerationWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedPtr<IDetailsView> CombinationDataWidget;
    UCombinationGenerationData* CombinationData;
};
