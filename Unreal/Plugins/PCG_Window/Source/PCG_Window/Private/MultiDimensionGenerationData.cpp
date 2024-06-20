// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiDimensionGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "PCG2Unreal.h"

void UMultiDimensionGenerationData::GenerateLevel() const
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATING Multi Dimension Level");

    UWorld* world = GEditor->GetEditorWorldContext().World();

    if (!world || !node)
    {
        return;
    }

    if (count == 0 || nodeSize == 0 || axes == 0)
    {
        return;
    }

    pcg::engine::cpp_api::setSeed(seed);

    pcg::engine::level_generation::GenerationData data
    {
        count,
        nodeSize,
        FVectorToPCGVector(startPosition)
    };

    pcg::engine::cpp_api::multiDimensionGeneration(data, static_cast<pcg::engine::math::Axis>(axes), disableOverlap,
        [this](pcg::engine::math::Vector3 position)
        {
            SpawnNode(position);
        });
}

void UMultiDimensionGenerationData::SpawnNode(pcg::engine::math::Vector3 position) const
{
    UWorld* world = GEditor->GetEditorWorldContext().World();
    AActor* spawnedNode = world->SpawnActor(node);
    spawnedNode->SetActorLocation(PCGVectorToFVector(position));
}

