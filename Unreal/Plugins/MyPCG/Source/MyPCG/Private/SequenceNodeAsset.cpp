// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceNodeAsset.h"

void USequenceNodeAsset::setNext(pcg::engine::combination_generation::ISequenceNode* next)
{
    nextNode = (USequenceNodeAsset*)next;
}

pcg::engine::combination_generation::ISequenceNode* USequenceNodeAsset::getNext() const
{
    return nextNode;
}

pcg::engine::combination_generation::ISequenceNode* USequenceNodeAsset::getNextAt(int index) const
{
    return nextNodes[index];
}

int USequenceNodeAsset::getNextCount() const
{
    return nextNodes.Num();
}

void USequenceNodeAsset::generateSequence() const
{

}
