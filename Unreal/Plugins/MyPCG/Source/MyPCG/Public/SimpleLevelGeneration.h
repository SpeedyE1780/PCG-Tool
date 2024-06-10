// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleLevelGeneration.generated.h"

UCLASS()
class MYPCG_API ASimpleLevelGeneration : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleLevelGeneration();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void GenerateLevel();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int blockCount = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int blockSize = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> levelBlock;
};
