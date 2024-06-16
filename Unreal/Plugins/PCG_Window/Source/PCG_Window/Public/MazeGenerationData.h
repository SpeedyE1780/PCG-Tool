// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MazeGenerationData.generated.h"

UENUM(BlueprintType)
enum class EMazeAlgorithm
{
    aldousBroder = 0,
    wilson = 1,
    binaryTreeNE = 2,
    binaryTreeNW = 3,
    binaryTreeSE = 4,
    binaryTreeSW = 5,
    sidewinder = 6
};

/**
 * 
 */
UCLASS(BlueprintType, config = EditorPerProjectUserSettings)
class PCG_WINDOW_API UMazeGenerationData : public UObject
{
	GENERATED_BODY()

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Maze Generation Data")
    void GenerateMaze() const;

	UPROPERTY(EditAnywhere, Category = "Maze Generation Data")
    EMazeAlgorithm mazeAlgorithm;

    UPROPERTY(EditAnywhere, Category = "Maze Generation Data")
    TSubclassOf<AActor> levelBlock;

    UPROPERTY(EditAnywhere, Category = "Maze Generation Data")
	FIntVector2 gridSize;
};
