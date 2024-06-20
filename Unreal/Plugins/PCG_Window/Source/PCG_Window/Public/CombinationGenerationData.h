// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CombinationActor.h"
#include "CombinationGenerationData.generated.h"

/**
 *
 */
UCLASS(BlueprintType, config = EditorPerProjectUserSettings)
class PCG_WINDOW_API UCombinationGenerationData : public UObject
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Combination Generation Data")
    void GenerateCombination();

    UPROPERTY(EditAnywhere, Category = "Combination Generation Data")
    unsigned int seed;
    UPROPERTY(EditAnywhere, Category = "Combination Generation Data")
    bool resetSeed;

};
