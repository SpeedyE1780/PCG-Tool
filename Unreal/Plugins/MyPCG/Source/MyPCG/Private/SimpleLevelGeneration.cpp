// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleLevelGeneration.h"

#include "pcg/engine/cpp-api/api.hpp"

UWorld* world = nullptr;
TSubclassOf<AActor> block = nullptr;

static void SpawnBlock(pcg::engine::math::Vector3 position)
{
    auto* spawnedActor = world->SpawnActor(block);
    spawnedActor->SetActorLocation(FVector{ position.x, position.y, position.z });
}

// Sets default values
ASimpleLevelGeneration::ASimpleLevelGeneration()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimpleLevelGeneration::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ASimpleLevelGeneration::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ASimpleLevelGeneration::GenerateLevel()
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "TEST");
    world = GetWorld();
    block = levelBlock;

    pcg::engine::level_generation::GenerationData data{ blockCount, blockSize, {0, 0, 0} };
    pcg::engine::cpp_api::multiDimensionGeneration(&data, pcg::engine::math::axis::xz, true, SpawnBlock);
}
