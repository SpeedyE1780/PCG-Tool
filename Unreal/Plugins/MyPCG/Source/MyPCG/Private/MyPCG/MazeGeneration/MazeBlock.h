// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "pcg/engine/maze-generation/Common.hpp"
#include "MyPCG/MazeGeneration/IMazeNode.h"
#include "MazeBlock.generated.h"

UCLASS()
class MYPCG_API AMazeBlock : public AActor, public IMazeNode
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeBlock();

	virtual void SetAdjacentNodes(pcg::engine::maze_generation::NodeValue adjacentNodes) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* left;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* right;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* forward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* backward;
};
