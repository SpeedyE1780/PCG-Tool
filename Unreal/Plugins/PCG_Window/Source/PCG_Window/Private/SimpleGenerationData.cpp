// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"

void USimpleGenerationData::GenerateLevel() const
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATING Linear Level");

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

    pcg::engine::cpp_api::simpleGeneration(&data, static_cast<int>(axis), static_cast<pcg::engine::math::Direction>(direction),
        [this](pcg::engine::math::Vector3 position)
        {
            SpawnNode(position);
        });
}

void USimpleGenerationData::SpawnNode(pcg::engine::math::Vector3 position) const
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    AActor* spawnedNode = world->SpawnActor(node);
    spawnedNode->SetActorLocation(FVector{ position.z, position.x, position.y });
}
