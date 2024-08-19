// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "ISequenceNode.h"
#include "Sequence.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"

void USequenceGenerationData::GenerateSequence()
{
    pcg::engine::cpp_api::setSeed(seed);

    if (auto* node = Cast<ISequenceNode>(sequenceNode))
    {
        //if (cyclicSequence)
        //{
        //    UPackage* package = CreatePackage(TEXT("Sequence"));
        //    auto* sequence = NewObject<USequence>();
        //    //auto* sequence = NewObject<USequence>(package, USequence::StaticClass(), TEXT("SequenceAsset"), EObjectFlags::RF_Public | EObjectFlags::RF_Standalone);
        //    
        //    std::vector<pcg::engine::combination_generation::ISequenceNode*> nodeSequence = pcg::engine::cpp_api::generateSequence(node->getPCGSequenceNode(), sequenceLength);
        //    for (auto n : nodeSequence)
        //    {
        //        if (auto* nodeAsset = (UDataAsset*)n)
        //        {
        //            sequence->AddNode(nodeAsset);
        //        }
        //    }

        //    FAssetRegistryModule::AssetCreated(sequence);
        //    sequence->MarkPackageDirty();

        //    FString path = FPaths::ProjectContentDir().Append("Sequence/CyclicSequence").Append(*FPackageName::GetAssetPackageExtension());
        //    FSavePackageArgs args{};
        //    args.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
        //    auto result = UPackage::Save(package, sequence, *path, args);
        //}
        //else
        //{
        //    pcg::engine::cpp_api::generateSequence(node->getPCGSequenceNode());
        //}

        if (cyclicSequence)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Yellow, "Cyclic Sequence is not yet supported");
            return;
        }

        pcg::engine::cpp_api::generateSequence(node->getPCGSequenceNode());

    }
}
