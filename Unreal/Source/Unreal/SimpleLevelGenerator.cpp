// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleLevelGenerator.h"

// Sets default values
ASimpleLevelGenerator::ASimpleLevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASimpleLevelGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimpleLevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimpleLevelGenerator::GenerateLevel()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "TEST");
	GetWorld()->SpawnActor(levelBlock);
}

