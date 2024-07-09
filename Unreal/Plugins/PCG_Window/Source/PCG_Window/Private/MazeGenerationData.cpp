// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"

namespace maze_generation = pcg::engine::maze_generation;
namespace pcg_api = pcg::engine::cpp_api;

namespace
{
    FString GetMazeAlgorith(EMazeAlgorithm algorithm)
    {
        // Strip the namespace from the name.
        FString EnumNameString = UEnum::GetValueAsString(algorithm);
        int32 ScopeIndex = EnumNameString.Find(TEXT("::"), ESearchCase::CaseSensitive);
        if (ScopeIndex != INDEX_NONE)
        {
            return EnumNameString.Mid(ScopeIndex + 2);
        }

        return FString();
    }
}

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

void UMazeGenerationData::SpawnBlock(int x, int y, maze_generation::NodeValue adjacentNodes)
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    auto* block = world->SpawnActor<AActor>(levelBlock);
    block->SetActorLocation({ y * nodeSize, x * nodeSize, 0 });
    block->SetFolderPath(*GetFolderName());
    Cast<IMazeNode>(block)->UpdateAdjacentNodes(adjacentNodes);
}

FString UMazeGenerationData::GetFolderName() const
{
    FString path = "Maze/";
    path.Append(GetMazeAlgorith(mazeAlgorithm));
    path.Append("/");
    path.Append(FString::FromInt(seed));
    return path;
}
