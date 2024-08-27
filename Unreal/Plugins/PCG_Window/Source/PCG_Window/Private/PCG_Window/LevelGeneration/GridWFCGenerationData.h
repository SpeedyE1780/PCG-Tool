// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "pcg/engine/math/Vector3.hpp"
#include "MyPCG/PCGEnums.h"
#include "GridWFCGenerationData.generated.h"

/**
 *
 */
UCLASS()
class PCG_WINDOW_API UGridWFCGenerationData : public UObject
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "WFC Dimension Generation Data")
    void GenerateLevel() const;

    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data")
    FIntVector2 gridSize;
    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data")
    TSubclassOf<AActor> block;
    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data")
    float nodeSize;
    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data")
    EGenerationPlane plane;
    UPROPERTY(EditAnywhere, Category = "WFC Dimension Generation Data")
    unsigned int seed;

private:
    void SpawnNode(FVector position, pcg::engine::utility::enums::Direction adjacentNodes) const;
    FString GetFolderName() const;
};
