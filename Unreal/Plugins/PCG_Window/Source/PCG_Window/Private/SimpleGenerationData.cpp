// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "PCG2Unreal.h"

void USimpleGenerationData::GenerateLevel() const
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATING Linear Level");

    UWorld* world = GEditor->GetEditorWorldContext().World();

    if (!world || !node)
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
        FVectorToPCGVector(startPosition)
    };

    pcg::engine::cpp_api::simpleGeneration(data, static_cast<pcg::engine::math::Axis>(axes),
        [this](pcg::engine::math::Vector3 position)
        {
            SpawnNode(position);
        });
}

void USimpleGenerationData::SpawnNode(pcg::engine::math::Vector3 position) const
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    AActor* spawnedNode = world->SpawnActor(node);
    spawnedNode->SetActorLocation(PCGVectorToFVector(position));
}
