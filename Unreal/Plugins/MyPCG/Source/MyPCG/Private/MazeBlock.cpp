// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBlock.h"
#include "pcg/engine/maze/Common.hpp"

// Sets default values
AMazeBlock::AMazeBlock()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>("ROOT");

    left = CreateDefaultSubobject<USceneComponent>("Left");
    left->SetupAttachment(RootComponent);
    right = CreateDefaultSubobject<USceneComponent>("Right");
    right->SetupAttachment(RootComponent);
    forward = CreateDefaultSubobject<USceneComponent>("Forward");
    forward->SetupAttachment(RootComponent);
    backward = CreateDefaultSubobject<USceneComponent>("Backward");
    backward->SetupAttachment(RootComponent);
}

void AMazeBlock::UpdateMeshes(int neighbors)
{
    left->SetVisibility((neighbors & pcg::engine::maze::left) == 0, true);
    right->SetVisibility((neighbors & pcg::engine::maze::right) == 0, true);
    forward->SetVisibility((neighbors & pcg::engine::maze::up) == 0, true);
    backward->SetVisibility((neighbors & pcg::engine::maze::down) == 0, true);
}
