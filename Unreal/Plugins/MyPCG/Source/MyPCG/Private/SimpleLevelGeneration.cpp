// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleLevelGeneration.h"

#include "pcg/engine/cpp-api/api.hpp"


// Sets default values
ASimpleLevelGeneration::ASimpleLevelGeneration()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

}

void ASimpleLevelGeneration::SpawnBlock(pcg::engine::math::Vector3 position)
{
    auto* spawnedActor = GetWorld()->SpawnActor(levelBlock);
    spawnedActor->SetActorLocation(FVector{ position.x, position.z, position.y });
}

void ASimpleLevelGeneration::GenerateLevel()
{
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "TEST");
    pcg::engine::level_generation::GenerationData data{ blockCount, blockSize, {0, 0, 0} };
    pcg::engine::cpp_api::multiDimensionGeneration(&data, pcg::engine::math::axis::xz, true, [this](pcg::engine::math::Vector3 position) { this->SpawnBlock(position); });
}
