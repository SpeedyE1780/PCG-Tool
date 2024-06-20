// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EGenerationAxis : uint8
{
    none = 0,
    positiveX = 1 << 0,
    negativeX = 1 << 1,
    positiveY = 1 << 2,
    negativeY = 1 << 3,
    positiveZ = 1 << 4,
    negativeZ = 1 << 5,
    x = positiveX | negativeX,
    y = positiveY | negativeY,
    z = positiveZ | negativeZ,
    xy = x | y,
    xz = x | z,
    yz = y | z,
    xyz = x | y | z
};
