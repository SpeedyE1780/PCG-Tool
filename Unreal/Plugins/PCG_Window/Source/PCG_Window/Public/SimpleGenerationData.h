// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "pcg/engine/math/Vector3.hpp"
#include "GenerationAxisEnum.h"
#include "SimpleGenerationData.generated.h"

/**
 *
 */
UCLASS()
class PCG_WINDOW_API USimpleGenerationData : public UObject
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Linear Generation Data")
    void GenerateLevel() const;

    UPROPERTY(EditAnywhere, Category = "Linear Generation Data")
    int count;
    UPROPERTY(EditAnywhere, Category = "Linear Generation Data")
    TSubclassOf<AActor> node;
    UPROPERTY(EditAnywhere, Category = "Linear Generation Data")
    float nodeSize;
    UPROPERTY(EditAnywhere, Category = "Linear Generation Data")
    EGenerationAxis axes;
    UPROPERTY(EditAnywhere, Category = "Linear Generation Data")
    FVector startPosition;

private:
    void SpawnNode(pcg::engine::math::Vector3 position) const;
};
