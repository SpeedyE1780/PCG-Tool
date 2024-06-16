// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"

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

    blocks.Empty(gridSize.X * gridSize.Y);
    pcg::engine::cpp_api::generateMaze(gridSize.X, gridSize.Y, static_cast<pcg::engine::maze::MazeAlgorithm>(mazeAlgorithm),
        [this](int x, int y, int neighbors) {
            this->SpawnBlock(x, y, neighbors);
        });
}

void UMazeGenerationData::SpawnBlock(int x, int y, int neighbors)
{
    if (blocks.Contains({ x, y }))
    {
        blocks[{x, y}]->UpdateMeshes(neighbors);
    }
    else
    {
        UWorld* world = GEditor->GetEditorWorldContext().World();
        AMazeBlock* block = world->SpawnActor<AMazeBlock>(levelBlock);
        block->SetActorLocation({ y * nodeSize, x * nodeSize, 0 });
        block->UpdateMeshes(neighbors);
        blocks.Add({ x, y }, block);
    }
}
