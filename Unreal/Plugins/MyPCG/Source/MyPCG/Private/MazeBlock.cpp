// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeBlock.h"
#include "pcg/engine/utility/Enums.hpp"

namespace maze_generation = pcg::engine::maze_generation;
namespace pcgEnums = pcg::engine::utility::enums;

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

void AMazeBlock::UpdateMeshes(maze_generation::NodeValue adjacentNode)
{
    left->SetVisibility(!pcgEnums::hasFlag(adjacentNode, maze_generation::NodeValue::left), true);
    right->SetVisibility(!pcgEnums::hasFlag(adjacentNode, maze_generation::NodeValue::right), true);
    forward->SetVisibility(!pcgEnums::hasFlag(adjacentNode, maze_generation::NodeValue::forward), true);
    backward->SetVisibility(!pcgEnums::hasFlag(adjacentNode, maze_generation::NodeValue::backward), true);
}
