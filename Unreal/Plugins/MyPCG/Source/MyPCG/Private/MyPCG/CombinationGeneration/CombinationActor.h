// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPCG/CombinationGeneration/ICombination.h"
#include "CombinationActor.generated.h"

UCLASS()
class MYPCG_API ACombinationActor : public AActor, public ICombination
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombinationActor();

	virtual void ToggleElement(int index, bool included) override;
	virtual int GetElementCount() override { return combinationSet.Num(); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combination Actor")
	TArray<USceneComponent*> combinationSet;
};
