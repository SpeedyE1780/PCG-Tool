// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/SequenceGeneration/CyclicSequenceGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "MyPCG/SequenceGeneration/ISequenceNode.h"
#include "MyPCG/SequenceGeneration/SequenceList.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"

USequenceList* UCyclicSequenceGenerationData::CreateSequenceListAsset() const
{
    IAssetTools& assetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();;
    auto* sequenceAsset = assetTools.CreateAsset(FString(sequenceName).Append(FString::FromInt(seed)),
        FString("/Game/").Append(folderPath),
        USequenceList::StaticClass(),
        nullptr);

    return Cast<USequenceList>(sequenceAsset);
}

void UCyclicSequenceGenerationData::GenerateSequence() const
{
    pcg::engine::cpp_api::setSeed(seed);

    if (auto* node = Cast<ISequenceNode>(sequenceNode))
    {
        USequenceList* sequence = CreateSequenceListAsset();

        if (sequence)
        {
            ISequenceNode* current = node;

            pcg::engine::cpp_api::generateSequence(node->getPCGSequenceNode(),
                sequenceLength,
                [&current, sequence](pcg::engine::combination_generation::ISequenceNode* pcgNode, int nextNodeIndex)
                {
                    if (nextNodeIndex != -1)
                    {
                        current = Cast<ISequenceNode>(current->getNextUnrealObjectAt(nextNodeIndex));
                    }

                    sequence->AddNode(Cast<UDataAsset>(current));
                });
        }
    }
}
