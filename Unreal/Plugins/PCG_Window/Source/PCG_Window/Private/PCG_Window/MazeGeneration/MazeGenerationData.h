// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "pcg/engine/maze-generation/Common.hpp"
#include "MyPCG/PCGEnums.h"
#include "MazeGenerationData.generated.h"

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

    UPROPERTY(EditAnywhere, Category = "Maze Generation Data")
    float nodeSize;
    UPROPERTY(EditAnywhere, Category = "Maze Generation Data")
    unsigned int seed;

private:
    void SpawnBlock(int x, int y, pcg::engine::maze_generation::NodeValue adjacentNodes) const;
    FString GetFolderName() const;
};
