// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/LevelGeneration/Grid3DWFCGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "IWFCNode.h"
#include "PCG2Unreal.h"

void UGrid3DWFCGenerationData::GenerateLevel() const
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATING Wave Function Collapse Level");

    UWorld* world = GEditor->GetEditorWorldContext().World();

    if (!world || !block)
    {
        return;
    }

    if (gridSize.X == 0 || gridSize.Y == 0 || gridSize.Z == 0 || nodeSize == 0)
    {
        return;
    }

    if (!block->ImplementsInterface(UWFCNode::StaticClass()))
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "Block does not implement IWFCNode");
        return;
    }

    pcg::engine::cpp_api::setSeed(seed);

    pcg::engine::cpp_api::gridWaveFunctionCollapseGeneration(gridSize.X, gridSize.Y, gridSize.Z, true,
        [this](int x, int y, int z, pcg::engine::utility::enums::Direction adjacentNodes)
        {
            FVector position{ z * nodeSize ,x * nodeSize,  y * nodeSize };
            SpawnNode(position, adjacentNodes);
        });
}

void UGrid3DWFCGenerationData::SpawnNode(FVector position, pcg::engine::utility::enums::Direction adjacentNodes) const
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    auto* spawnedBlock = world->SpawnActor<AActor>(block);
    spawnedBlock->SetActorLocation(position);
    spawnedBlock->SetFolderPath(*GetFolderName());
    Cast<IWFCNode>(spawnedBlock)->SetAdjacentNodes(adjacentNodes);
}

FString UGrid3DWFCGenerationData::GetFolderName() const
{
    FString path = "Grid3DWFC/";
    path.Append(FString::FromInt(gridSize.X));
    path.Append("-");
    path.Append(FString::FromInt(gridSize.Y));
    path.Append("-");
    path.Append(FString::FromInt(gridSize.Z));
    path.Append("/");
    path.Append(FString::FromInt(seed));
    return path;
}
