// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/MazeGeneration/MazeGenerationData.h"
#include "PCG_Window/Utility/Utility.hpp"
#include "MyPCG/MazeGeneration/IMazeNode.h"
#include "pcg/engine/cpp-api/api.hpp"

namespace maze_generation = pcg::engine::maze_generation;
namespace pcg_api = pcg::engine::cpp_api;

void UMazeGenerationData::GenerateMaze() const
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

    if (!levelBlock->ImplementsInterface(UMazeNode::StaticClass()))
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "Maze Block does not implement IMazeNode");
        return;
    }

    pcg_api::setSeed(seed);

    pcg_api::generateMaze(gridSize.X, gridSize.Y, true, static_cast<pcg_api::MazeAlgorithm>(mazeAlgorithm),
        [this](int x, int y, maze_generation::NodeValue adjacentNodes) {
            this->SpawnBlock(x, y, adjacentNodes);
        });
}

void UMazeGenerationData::SpawnBlock(int x, int y, maze_generation::NodeValue adjacentNodes) const
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    auto* block = world->SpawnActor<AActor>(levelBlock);
    block->SetActorLocation({ y * nodeSize, x * nodeSize, 0 });
    block->SetFolderPath(*GetFolderName());
    block->SetActorLabel(FString::FromInt(x) + "-" + FString::FromInt(y));
    Cast<IMazeNode>(block)->SetAdjacentNodes(adjacentNodes);
}

FString UMazeGenerationData::GetFolderName() const
{
    FString path = "Maze/";
    path.Append(GetEnumAsString(mazeAlgorithm));
    path.Append("/");
    path.Append(FString::FromInt(seed));
    return path;
}
