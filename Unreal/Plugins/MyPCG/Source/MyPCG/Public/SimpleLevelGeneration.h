// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "pcg/engine/math/Vector3.hpp"

#include "SimpleLevelGeneration.generated.h"

UCLASS()
class MYPCG_API ASimpleLevelGeneration : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleLevelGeneration();

	UFUNCTION(BlueprintCallable)
	void GenerateLevel();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int blockCount = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int blockSize = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> levelBlock;

private:
	void SpawnBlock(pcg::engine::math::Vector3 position);
};
