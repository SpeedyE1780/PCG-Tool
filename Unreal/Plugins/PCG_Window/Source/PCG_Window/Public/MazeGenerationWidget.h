// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

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
};
