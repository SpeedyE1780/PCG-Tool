// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "pcg/engine/math/Vector3.hpp"
#include "MyPCG/PCGEnums.h"
#include "MultiDimensionGenerationData.generated.h"

/**
 *
 */
UCLASS()
class PCG_WINDOW_API UMultiDimensionGenerationData : public UObject
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "Multi Dimension Generation Data")
    void GenerateLevel() const;

    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data")
    int count;
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data")
    TSubclassOf<AActor> node;
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data")
    float nodeSize;
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data", meta = (Bitmask, BitmaskEnum = "EGenerationAxis"))
    uint8 axes;
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data")
    unsigned int seed;
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data")
    bool disableOverlap;
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data")
    FVector startPosition;

private:
    void SpawnNode(pcg::engine::math::Vector3 position) const;
    FString GetFolderName() const;
};
