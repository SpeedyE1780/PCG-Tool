// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"

namespace maze_generation = pcg::engine::maze_generation;
namespace pcg_api = pcg::engine::cpp_api;

void UMazeGenerationData::GenerateMaze()
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATING MAZE");

    UWorld* world = GEditor->GetEditorWorldContext().World();

    if (!world || !levelBlock)
    {
        return;
    }

    if (gridSize.X == 0 || gridSize.Y == 0 || nodeSize == 0)
    {
        return;
    }

    pcg_api::setSeed(seed);

    pcg_api::generateMaze(gridSize.X, gridSize.Y, true, static_cast<pcg_api::MazeAlgorithm>(mazeAlgorithm),
        [this](int x, int y, maze_generation::NodeValue adjacentNodes) {
            this->SpawnBlock(x, y, adjacentNodes);
        });
}

void UMazeGenerationData::SpawnBlock(int x, int y, maze_generation::NodeValue adjacentNodes)
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    AMazeBlock* block = world->SpawnActor<AMazeBlock>(levelBlock);
    block->SetActorLocation({ y * nodeSize, x * nodeSize, 0 });
    block->UpdateMeshes(adjacentNodes);
}
