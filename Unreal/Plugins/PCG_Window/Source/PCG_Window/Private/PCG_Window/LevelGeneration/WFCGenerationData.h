// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "pcg/engine/math/Vector3.hpp"
#include "MyPCG/PCGEnums.h"
#include "WFCGenerationData.generated.h"

/**
 * 
 */
UCLASS()
class PCG_WINDOW_API UWFCGenerationData : public UObject
{
	GENERATED_BODY()
	
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "WFC Generation Data")
    void GenerateLevel() const;

    UPROPERTY(EditAnywhere, Category = "WFC Generation Data")
    int count;
    UPROPERTY(EditAnywhere, Category = "WFC Generation Data")
    TSubclassOf<AActor> block;
    UPROPERTY(EditAnywhere, Category = "WFC Generation Data")
    float nodeSize;
    UPROPERTY(EditAnywhere, Category = "WFC Generation Data")
    EExpansionMode expansionMode;
    UPROPERTY(EditAnywhere, Category = "WFC Generation Data", meta = (Bitmask, BitmaskEnum = "EGenerationAxis"))
    uint8 axes;
    UPROPERTY(EditAnywhere, Category = "WFC Generation Data")
    FVector startPosition;
    UPROPERTY(EditAnywhere, Category = "WFC Generation Data")
    unsigned int seed;

private:
    void SpawnNode(pcg::engine::math::Vector3 position, pcg::engine::utility::enums::Direction adjacentNodes) const;
    FString GetFolderName() const;
};
