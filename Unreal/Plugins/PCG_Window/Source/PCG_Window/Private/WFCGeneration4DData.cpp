// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/LevelGeneration/WFCGeneration4DData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "MyPCG/LevelGeneration/IWFCNode.h"
#include "PCG_Window/Utility/Utility.hpp"
#include "MyPCG/PCG2Unreal.h"

void UWFCGeneration4DData::GenerateLevel() const
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATING 4D Wave Function Collapse Level");

    UWorld* world = GEditor->GetEditorWorldContext().World();

    if (!world || !block)
    {
        return;
    }

    if (count == 0 || nodeSize == 0 || axes == 0)
    {
        return;
    }

    if (!block->ImplementsInterface(UWFCNode::StaticClass()))
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "Block does not implement IWFCNode");
        return;
    }

    pcg::engine::cpp_api::setSeed(seed);
    dimensions.Empty(1);

    pcg::engine::level_generation::GenerationData data
    {
        count,
        nodeSize,
        FVectorToPCGVector(startPosition)
    };

    pcg::engine::cpp_api::waveFunctionCollapse4DGeneration(data, static_cast<pcg::engine::level_generation::ExpansionMode>(expansionMode), static_cast<pcg::engine::math::Axis>(axes),
        [this](pcg::engine::math::Vector4 position, pcg::engine::utility::enums::Direction adjacentNodes)
        {
            SpawnNode(position, adjacentNodes);
        });
}

void UWFCGeneration4DData::SpawnNode(pcg::engine::math::Vector4 position, pcg::engine::utility::enums::Direction adjacentNodes) const
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    auto* spawnedBlock = world->SpawnActor<AActor>(block);
    spawnedBlock->SetActorLocation(PCGVectorToFVector(position));
    spawnedBlock->SetFolderPath(*GetFolderName());
    Cast<IWFCNode>(spawnedBlock)->SetAdjacentNodes(adjacentNodes);
}

FString UWFCGeneration4DData::GetFolderName() const
{
    FString path = "WFC 4D/";
    path.Append(GetEnumAsString(expansionMode));
    path.Append("/");
    path.Append(FString::FromInt(seed));
    return path;
}
