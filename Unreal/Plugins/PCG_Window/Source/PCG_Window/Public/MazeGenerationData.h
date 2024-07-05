// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MazeBlock.h"
#include "pcg/engine/maze-generation/Common.hpp"

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
    sidewinder = 6,
    eller = 7,
    huntAndKill = 8,
    recursiveBacktracker = 9,
    recursiveDivision = 10,
    kruskal = 11,
    prim = 12,
    growingTreeOldest = 13,
    growingTreeMiddle = 14,
    growingTreeNewest = 15,
    growingTreeRandom = 16,
    blobbyDivisionCorridors = 17,
    blobbyDivisionSmall = 18,
    blobbyDivisionMedium = 19,
    blobbyDivisionLarge = 20,
    blobbyDivisionHuge = 21,
};

/**
 *
 */
UCLASS(BlueprintType, config = EditorPerProjectUserSettings)
class PCG_WINDOW_API UMazeGenerationData : public UObject
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Maze Generation Data")
    void GenerateMaze();

    UPROPERTY(EditAnywhere, Category = "Maze Generation Data")
    EMazeAlgorithm mazeAlgorithm;

    UPROPERTY(EditAnywhere, Category = "Maze Generation Data")
    TSubclassOf<AMazeBlock> levelBlock;

    UPROPERTY(EditAnywhere, Category = "Maze Generation Data")
    FIntVector2 gridSize;

    UPROPERTY(EditAnywhere, Category = "Maze Generation Data")
    float nodeSize;
    UPROPERTY(EditAnywhere, Category = "Maze Generation Data")
    unsigned int seed;

private:
    void SpawnBlock(int x, int y, pcg::engine::maze_generation::NodeValue adjacentNodes);

    TMap<TTuple<int, int>, AMazeBlock*> blocks;
};
