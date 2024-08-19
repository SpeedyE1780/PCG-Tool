// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataAsset.h"
#include "SequenceGenerationData.generated.h"

/**
 *
 */
UCLASS(BlueprintType, config = EditorPerProjectUserSettings)
class PCG_WINDOW_API USequenceGenerationData : public UObject
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Sequence Generation Data")
    void GenerateSequence();

    UPROPERTY(EditAnywhere, Category = "Sequence Generation Data")
    TObjectPtr<UDataAsset> sequenceNode;
    UPROPERTY(EditAnywhere, Category = "Sequence Generation Data")
    unsigned int seed;
    UPROPERTY(EditAnywhere, Category = "Sequence Generation Data")
    bool cyclicSequence;
    UPROPERTY(EditAnywhere, Category = "Sequence Generation Data")
    unsigned int sequenceLength;
};
