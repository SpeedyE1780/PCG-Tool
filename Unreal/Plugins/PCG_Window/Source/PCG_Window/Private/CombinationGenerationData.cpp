// Fill out your copyright notice in the Description page of Project Settings.


#include "CombinationGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "Engine/Selection.h"

void UCombinationGenerationData::GenerateCombination()
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "GENERATING COMBINATION");

    FSelectionIterator  selectedActors = GEditor->GetSelectedActorIterator();

    while (selectedActors)
    {
        if (auto* combinationActor = Cast<ACombinationActor>(*selectedActors))
        {
            if (resetSeed)
            {
                pcg::engine::cpp_api::setSeed(seed);
            }

            pcg::engine::cpp_api::generateCombination(combinationActor->combinationSet.Num(),
                [combinationActor](int elementIndex, bool includedInSet) {
                    combinationActor->ToggleElement(elementIndex, includedInSet);
                });
        }

        ++selectedActors;
    }
}
