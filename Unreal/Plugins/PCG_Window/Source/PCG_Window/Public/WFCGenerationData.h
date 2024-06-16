// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "pcg/engine/math/Vector3.hpp"
#include "WFCGenerationData.generated.h"

UENUM(BlueprintType)
enum class EExpansionMode
{
    BFS,
    DFS
};

/**
 * 
 */
UCLASS()
class PCG_WINDOW_API UWFCGenerationData : public UObject
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
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data")
    EExpansionMode expansionMode;
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data", meta = (Bitmask, BitmaskEnum = "EMultiDimensionGenerationAxis"))
    uint8 axis;
    UPROPERTY(EditAnywhere, Category = "Multi Dimension Generation Data")
    FVector startPosition;

private:
    void SpawnNode(pcg::engine::math::Vector3 position, int neighbors) const;

};
