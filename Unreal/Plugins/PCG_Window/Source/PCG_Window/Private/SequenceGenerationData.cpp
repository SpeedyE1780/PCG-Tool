// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/SequenceGeneration/SequenceGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "MyPCG/SequenceGeneration/ISequenceNode.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"

void USequenceGenerationData::GenerateSequence() const
{
    pcg::engine::cpp_api::setSeed(seed);

    if (auto* node = Cast<ISequenceNode>(sequenceNode))
    {
        pcg::engine::cpp_api::generateSequence(node->getPCGSequenceNode());
    }
}
