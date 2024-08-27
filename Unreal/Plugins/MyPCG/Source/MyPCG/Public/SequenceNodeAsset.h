// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ISequenceNode.h"
#include "SequenceNodeAsset.generated.h"

/**
 *
 */
UCLASS()
class MYPCG_API USequenceNodeAsset : public UDataAsset, public ISequenceNode, public pcg::engine::combination_generation::ISequenceNode
{
    GENERATED_BODY()

public:
    virtual void setNext(pcg::engine::combination_generation::ISequenceNode* nextNode) override;
    virtual pcg::engine::combination_generation::ISequenceNode* getNext() const override;
    virtual pcg::engine::combination_generation::ISequenceNode* getNextAt(int index) const override;
    virtual int getNextCount() const override;
    virtual void generateSequence() const override;
    virtual pcg::engine::combination_generation::ISequenceNode& getPCGSequenceNode() override { return *this; }

private:
    UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
    TArray<TObjectPtr<USequenceNodeAsset>> nextNodes;
    UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USequenceNodeAsset> nextNode;
};
