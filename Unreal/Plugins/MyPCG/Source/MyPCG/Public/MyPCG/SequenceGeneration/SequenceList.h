// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SequenceList.generated.h"

/**
 *
 */
UCLASS()
class MYPCG_API USequenceList : public UDataAsset
{
    GENERATED_BODY()
public:

    void AddNode(UDataAsset* node);

private:
    UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
    TArray<TObjectPtr<UDataAsset>> Nodes;
};
