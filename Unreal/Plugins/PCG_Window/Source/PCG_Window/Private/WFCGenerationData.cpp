// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/LevelGeneration/WFCGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "MyPCG/LevelGeneration/IWFCNode.h"
#include "MyPCG/PCG2Unreal.h"

namespace
{
    FString GetExpansionMode(EExpansionMode mode)
    {
        // Strip the namespace from the name.
        FString EnumNameString = UEnum::GetValueAsString(mode);
        int32 ScopeIndex = EnumNameString.Find(TEXT("::"), ESearchCase::CaseSensitive);
        if (ScopeIndex != INDEX_NONE)
        {
            return EnumNameString.Mid(ScopeIndex + 2);
        }

        return FString();
    }
}

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

    if (!block->ImplementsInterface(UWFCNode::StaticClass()))
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "Block does not implement IWFCNode");
        return;
    }

    pcg::engine::cpp_api::setSeed(seed);

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
    auto* spawnedBlock = world->SpawnActor<AActor>(block);
    spawnedBlock->SetActorLocation(PCGVectorToFVector(position));
    spawnedBlock->SetFolderPath(*GetFolderName());
    Cast<IWFCNode>(spawnedBlock)->SetAdjacentNodes(adjacentNodes);
}

FString UWFCGenerationData::GetFolderName() const
{
    FString path = "WFC/";
    path.Append(GetExpansionMode(expansionMode));
    path.Append("/");
    path.Append(FString::FromInt(seed));
    return path;
}
