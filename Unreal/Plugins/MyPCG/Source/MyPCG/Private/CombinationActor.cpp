// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPCG/CombinationGeneration/CombinationActor.h"

// Sets default values
ACombinationActor::ACombinationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ACombinationActor::ToggleElement(int index, bool included)
{
    combinationSet[index]->SetVisibility(included, true);
}

