// Fill out your copyright notice in the Description page of Project Settings.


#include "WFCGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"

void UWFCGenerationData::GenerateLevel() const
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATING Wave Function Collapse Level");

    UWorld* world = GEditor->GetEditorWorldContext().World();

    if (!world || !block)
    {
        return;
    }

    if (count == 0 || nodeSize == 0 || axis == 0)
    {
        return;
    }

    pcg::engine::level_generation::GenerationData data
    {
        count,
        nodeSize,
        { startPosition.Y, startPosition.Z, startPosition.X }
    };

    pcg::engine::cpp_api::waveFunctionCollapseGeneration(&data, static_cast<pcg::engine::level_generation::ExpansionMode>(expansionMode), axis,
        [this](pcg::engine::math::Vector3 position, int neighbors)
        {
            SpawnNode(position, neighbors);
        });
}

void UWFCGenerationData::SpawnNode(pcg::engine::math::Vector3 position, int neighbors) const
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    AWFCBlock* spawnedBlock = world->SpawnActor<AWFCBlock>(block);
    spawnedBlock->SetActorLocation(FVector{ position.z, position.x, position.y });
    spawnedBlock->UpdateMeshes(neighbors);
}
