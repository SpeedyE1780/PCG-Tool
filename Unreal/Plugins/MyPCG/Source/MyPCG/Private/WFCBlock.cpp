// Fill out your copyright notice in the Description page of Project Settings.

#include "WFCBlock.h"
#include "pcg/engine/level-generation/Node.hpp"

namespace pcgEnums = pcg::engine::utility::enums;

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

void AWFCBlock::SetAdjacentNodes(pcgEnums::Direction adjacentNodes)
{
    left->SetVisibility(!pcgEnums::hasFlag(adjacentNodes, pcgEnums::Direction::left), true);
    right->SetVisibility(!pcgEnums::hasFlag(adjacentNodes, pcgEnums::Direction::right), true);
    up->SetVisibility(pcgEnums::hasFlag(adjacentNodes, pcgEnums::Direction::up), true);
    down->SetVisibility(pcgEnums::hasFlag(adjacentNodes, pcgEnums::Direction::down), true);
    forward->SetVisibility(!pcgEnums::hasFlag(adjacentNodes, pcgEnums::Direction::forward), true);
    backward->SetVisibility(!pcgEnums::hasFlag(adjacentNodes, pcgEnums::Direction::backward), true);
}
