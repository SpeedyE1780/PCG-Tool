// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SVectorInputBox.h"


using GridSize = SNumericVectorInputBox<int, FIntVector2, 2>;

/**
 *
 */
class PCG_WINDOW_API SMazeGenerationWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SMazeGenerationWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
    FReply GenerateMaze();

private:
    TOptional<int32> GetGridSize(int32 Axis) const;
    void SetGridSize(int NewValue, ETextCommit::Type CommitInfo, int32 Axis);

    static const TArray<FText> Algorithms;

    TSharedPtr<FText> SelectedAlgorithm;
    TArray<TSharedPtr<FText>> AlgorithmsOptions;
    FIntVector2 gridSize;
};
