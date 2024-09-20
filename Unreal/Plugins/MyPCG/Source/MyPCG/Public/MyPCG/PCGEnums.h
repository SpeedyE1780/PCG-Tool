// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <pcg/engine/math/enums.hpp>
#include "CoreMinimal.h"
#include "PCGEnums.generated.h"

namespace math = pcg::engine::math;

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EGenerationAxis : uint8
{
    none = math::Axis::none,
    right = math::Axis::positiveX,
    left = math::Axis::negativeX,
    up = math::Axis::positiveY,
    down = math::Axis::negativeY,
    forward = math::Axis::positiveZ,
    backward = math::Axis::negativeZ
};

UENUM(BlueprintType)
enum class EGenerationPlane : uint8
{
    None = 0,
    XY = math::Plane::xy,
    XZ = math::Plane::xz,
    YZ = math::Plane::yz
};

UENUM(BlueprintType)
enum class EExpansionMode
{
    BFS,
    DFS
};
