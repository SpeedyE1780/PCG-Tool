// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "ISequenceNode.h"
#include "Engine/Selection.h"

void USequenceGenerationData::GenerateSequence()
{
    pcg::engine::cpp_api::setSeed(seed);

    if (auto* node = Cast<ISequenceNode>(sequenceNode))
    {
        if (cyclicSequence)
        {
            auto vec = pcg::engine::cpp_api::generateSequence(node->getPCGSequenceNode(), sequenceLength);
        }
        else
        {
            pcg::engine::cpp_api::generateSequence(node->getPCGSequenceNode());
        }
    }
}
