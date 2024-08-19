// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SequenceGenerationData.h"

/**
 *
 */
class PCG_WINDOW_API SSequenceGenerationWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SSequenceGenerationWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    TSharedPtr<IDetailsView> SequenceDataWidget;
    USequenceGenerationData* SequenceData;
};
