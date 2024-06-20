// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombinationActor.generated.h"

UCLASS()
class MYPCG_API ACombinationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombinationActor();

	UFUNCTION(BlueprintImplementableEvent)
	void ToggleElement(int elementIndex, bool includedInSet);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combination Actor")
	TArray<USceneComponent*> combinationSet;
};
