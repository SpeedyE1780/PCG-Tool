// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/LevelGeneration/GridWFCGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "IWFCNode.h"
#include "PCG2Unreal.h"

void UGridWFCGenerationData::GenerateLevel() const
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATING Wave Function Collapse Level");

    UWorld* world = GEditor->GetEditorWorldContext().World();

    if (!world || !block)
    {
        return;
    }

    if (gridSize.X == 0 || gridSize.Y == 0 || nodeSize == 0 || plane == EGenerationPlane::None)
    {
        return;
    }

    if (!block->ImplementsInterface(UWFCNode::StaticClass()))
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "Block does not implement IWFCNode");
        return;
    }

    pcg::engine::cpp_api::setSeed(seed);

    pcg::engine::cpp_api::gridWaveFunctionCollapseGeneration(gridSize.X, gridSize.Y, static_cast<pcg::engine::math::Plane>(plane), true,
        [this](int x, int y, pcg::engine::utility::enums::Direction adjacentNodes)
        {
            FVector position{};

            switch (plane)
            {
            case EGenerationPlane::XY:
            {
                position.Y = x * nodeSize;
                position.Z = y * nodeSize;
                break;
            }
            case EGenerationPlane::XZ:
            {
                position.Y = x * nodeSize;
                position.X = y * nodeSize;
                break;
            }
            case EGenerationPlane::YZ:
            {
                position.Z = x * nodeSize;
                position.X = y * nodeSize;
                break;
            }
            }

            SpawnNode(position, adjacentNodes);
        });
}

void UGridWFCGenerationData::SpawnNode(FVector position, pcg::engine::utility::enums::Direction adjacentNodes) const
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    auto* spawnedBlock = world->SpawnActor<AActor>(block);
    spawnedBlock->SetActorLocation(position);
    spawnedBlock->SetFolderPath(*GetFolderName());
    Cast<IWFCNode>(spawnedBlock)->SetAdjacentNodes(adjacentNodes);
}

FString UGridWFCGenerationData::GetFolderName() const
{
    FString path = "Grid2DWFC/";
    path.Append(FString::FromInt(gridSize.X));
    path.Append("-");
    path.Append(FString::FromInt(gridSize.Y));
    path.Append("/");
    path.Append(FString::FromInt(seed));
    return path;
}
