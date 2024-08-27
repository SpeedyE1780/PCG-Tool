// Fill out your copyright notice in the Description page of Project Settings.


#include "PCG_Window/CombinationGeneration/CombinationGenerationData.h"
#include "pcg/engine/cpp-api/api.hpp"
#include "ICombination.h"
#include "Engine/Selection.h"

void UCombinationGenerationData::GenerateCombination() const
{
    FSelectionIterator  selectedActors = GEditor->GetSelectedActorIterator();

    while (selectedActors)
    {
        if (auto* combinationActor = Cast<ICombination>(*selectedActors))
        {
            if (resetSeed)
            {
                pcg::engine::cpp_api::setSeed(seed);
            }

            pcg::engine::cpp_api::generateCombination(combinationActor->GetElementCount(),
                [combinationActor](int elementIndex, bool includedInSet) {
                    combinationActor->ToggleElement(elementIndex, includedInSet);
                });
        }

        ++selectedActors;
    }
}
