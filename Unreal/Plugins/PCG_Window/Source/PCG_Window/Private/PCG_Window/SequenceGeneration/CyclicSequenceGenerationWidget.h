// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "CyclicSequenceGenerationData.h"

/**
 *
 */
class PCG_WINDOW_API SCylicSequenceGenerationWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SCylicSequenceGenerationWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedPtr<IDetailsView> SequenceDataWidget;
    UCyclicSequenceGenerationData* SequenceData;
};
