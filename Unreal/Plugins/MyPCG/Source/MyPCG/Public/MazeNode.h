// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "pcg/engine/maze-generation/Common.hpp"
#include "MazeNode.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMazeNode : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPCG_API IMazeNode
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void UpdateAdjacentNodes(pcg::engine::maze_generation::NodeValue adjacentNodes) = 0;
};
