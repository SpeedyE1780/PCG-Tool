// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPCG/SequenceGeneration/SequenceList.h"

void USequenceList::AddNode(UDataAsset* node)
{
    Nodes.Add(node);
}
