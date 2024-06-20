// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "PCG2Unreal.h"

void UWFCGenerationData::GenerateLevel() const
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATING Wave Function Collapse Level");

    UWorld* world = GEditor->GetEditorWorldContext().World();

    if (!world || !block)
    {
        return;
    }

    if (count == 0 || nodeSize == 0 || axes == 0)
    {
        return;
    }

    pcg::engine::level_generation::GenerationData data
    {
        count,
        nodeSize,
        FVectorToPCGVector(startPosition)
    };

    pcg::engine::cpp_api::waveFunctionCollapseGeneration(data, static_cast<pcg::engine::level_generation::ExpansionMode>(expansionMode), static_cast<pcg::engine::math::Axis>(axes),
        [this](pcg::engine::math::Vector3 position, pcg::engine::utility::enums::Direction adjacentNodes)
        {
            SpawnNode(position, adjacentNodes);
        });
}

void UWFCGenerationData::SpawnNode(pcg::engine::math::Vector3 position, pcg::engine::utility::enums::Direction adjacentNodes) const
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    AWFCBlock* spawnedBlock = world->SpawnActor<AWFCBlock>(block);
    spawnedBlock->SetActorLocation(PCGVectorToFVector(position));
    spawnedBlock->UpdateMeshes(adjacentNodes);
}
