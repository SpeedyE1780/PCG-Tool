// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/SequenceGeneration/CyclicSequenceGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "MyPCG/SequenceGeneration/ISequenceNode.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"

void UCyclicSequenceGenerationData::GenerateSequence() const
{
    pcg::engine::cpp_api::setSeed(seed);

    if (auto* node = Cast<ISequenceNode>(sequenceNode))
    {
        pcg::engine::cpp_api::generateSequence(node->getPCGSequenceNode(),
            sequenceLength,
            [this](pcg::engine::combination_generation::ISequenceNode* node)
            {
                sequence->AddNode((UDataAsset*)node);
            });

        sequence->MarkPackageDirty();
    }
}
