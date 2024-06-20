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

    if (count == 0 || nodeSize == 0 || axes == EGenerationAxis::none)
    {
        return;
    }

    pcg::engine::level_generation::GenerationData data
    {
        count,
        nodeSize,
        { startPosition.X, startPosition.Y, startPosition.Z }
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
    spawnedBlock->SetActorLocation(FVector{ position.x, position.y, position.z });
    spawnedBlock->UpdateMeshes(adjacentNodes);
}
