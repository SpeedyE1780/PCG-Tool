// Fill out your copyright notice in the Description page of Project Settings.

#include "WFCBlock.h"
#include "pcg/engine/level-generation/Node.hpp"

// Sets default values
AWFCBlock::AWFCBlock()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>("ROOT");

    left = CreateDefaultSubobject<USceneComponent>("Left");
    left->SetupAttachment(RootComponent);
    right = CreateDefaultSubobject<USceneComponent>("Right");
    right->SetupAttachment(RootComponent);
    up = CreateDefaultSubobject<USceneComponent>("Up");
    up->SetupAttachment(RootComponent);
    down = CreateDefaultSubobject<USceneComponent>("Down");
    down->SetupAttachment(RootComponent);
    forward = CreateDefaultSubobject<USceneComponent>("Forward");
    forward->SetupAttachment(RootComponent);
    backward = CreateDefaultSubobject<USceneComponent>("Backward");
    backward->SetupAttachment(RootComponent);
}

void AWFCBlock::UpdateMeshes(int neighbors)
{
    left->SetVisibility((neighbors & pcg::engine::level_generation::Neighbors::left) == 0, true);
    right->SetVisibility((neighbors & pcg::engine::level_generation::Neighbors::right) == 0, true);
    up->SetVisibility((neighbors & pcg::engine::level_generation::Neighbors::up) == 0, true);
    down->SetVisibility((neighbors & pcg::engine::level_generation::Neighbors::down) == 0, true);
    forward->SetVisibility((neighbors & pcg::engine::level_generation::Neighbors::forward) == 0, true);
    backward->SetVisibility((neighbors & pcg::engine::level_generation::Neighbors::backward) == 0, true);
}
