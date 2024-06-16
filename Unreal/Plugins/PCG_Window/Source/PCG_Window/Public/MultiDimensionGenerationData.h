// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SimpleGenerationData.h"
#include "MultiDimensionGenerationData.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EMultiDimensionGenerationAxis : uint8
{
    None = 0,
    X = 1 << 0,
    Y = 1 << 1,
    Z = 1 << 2
};

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
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data", meta = (Bitmask, BitmaskEnum = "EMultiDimensionGenerationAxis"))
    uint8 axis;
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data")
    bool disableOverlap;
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data")
    FVector startPosition;

private:
    void SpawnNode(pcg::engine::math::Vector3 position) const;
};
