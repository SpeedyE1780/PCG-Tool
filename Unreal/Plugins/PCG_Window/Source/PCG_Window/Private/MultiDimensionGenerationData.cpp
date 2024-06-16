// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiDimensionGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"

void UMultiDimensionGenerationData::GenerateLevel() const
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATING Multi Dimension Level");

    UWorld* world = GEditor->GetEditorWorldContext().World();

    if (!world)
    {
        return;
    }

    if (count == 0 || nodeSize == 0 || axis == EGenerationAxis::None)
    {
        return;
    }

    pcg::engine::level_generation::GenerationData data
    {
        count,
        nodeSize,
        { startPosition.Y, startPosition.Z, startPosition.X }
    };

    pcg::engine::cpp_api::multiDimensionGeneration(&data, static_cast<int>(axis), disableOverlap,
        [this](pcg::engine::math::Vector3 position)
        {
            SpawnNode(position);
        });
}

void UMultiDimensionGenerationData::SpawnNode(pcg::engine::math::Vector3 position) const
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    AActor* spawnedNode = world->SpawnActor(node);
    spawnedNode->SetActorLocation(FVector{ position.z, position.x, position.y });
}

