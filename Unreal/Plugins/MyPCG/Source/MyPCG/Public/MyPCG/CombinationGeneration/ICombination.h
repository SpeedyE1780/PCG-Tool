// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICombination.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombination : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPCG_API ICombination
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ToggleElement(int index, bool included) = 0;
	virtual int GetElementCount() = 0;
};
