// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenerationAxisEnum.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EGenerationAxis : uint8
{
    none = 0,
    left = 1 << 0,
    right = 1 << 1,
    up = 1 << 2,
    down = 1 << 3,
    forward = 1 << 4,
    backward = 1 << 5
};
