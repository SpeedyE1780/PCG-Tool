// Fill out your copyright notice in the Description page of Project Settings.


#include "Sequence.h"

void USequence::AddNode(TObjectPtr<UDataAsset> node)
{
    sequence.Add(node);
}
