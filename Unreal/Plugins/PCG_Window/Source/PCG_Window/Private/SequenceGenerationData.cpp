// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "ISequenceNode.h"
#include "Sequence.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"

void USequenceGenerationData::GenerateCyclicSequence()
{
    if (auto* node = Cast<ISequenceNode>(sequenceNode))
    {
        TArray<TObjectPtr<UDataAsset>> sequence{};
        pcg::engine::cpp_api::generateSequence(node->getPCGSequenceNode(),
            sequenceLength,
            [&sequence](pcg::engine::combination_generation::ISequenceNode* node)
            {
                sequence.Add((UDataAsset*)node);
            });

        for (auto& n : sequence)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, n.GetName());
        }
    }
}

void USequenceGenerationData::GenerateLinearSequence()
{
    if (auto* node = Cast<ISequenceNode>(sequenceNode))
    {
        pcg::engine::cpp_api::generateSequence(node->getPCGSequenceNode());
    }
}

void USequenceGenerationData::GenerateSequence()
{
    pcg::engine::cpp_api::setSeed(seed);

    if (cyclicSequence)
    {
        GenerateCyclicSequence();
    }
    else
    {
        GenerateLinearSequence();
    }
}
