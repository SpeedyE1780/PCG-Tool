// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "pcg/engine/cpp-api/api.hpp"
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

UENUM(BlueprintType)
enum class EMazeAlgorithm
{
    aldousBroder = pcg::engine::cpp_api::MazeAlgorithm::aldousBroder,
    wilson = pcg::engine::cpp_api::MazeAlgorithm::wilson,
    binaryTreeNE = pcg::engine::cpp_api::MazeAlgorithm::binaryTreeNE,
    binaryTreeNW = pcg::engine::cpp_api::MazeAlgorithm::binaryTreeNW,
    binaryTreeSE = pcg::engine::cpp_api::MazeAlgorithm::binaryTreeSE,
    binaryTreeSW = pcg::engine::cpp_api::MazeAlgorithm::binaryTreeSW,
    sidewinder = pcg::engine::cpp_api::MazeAlgorithm::sidewinder,
    eller = pcg::engine::cpp_api::MazeAlgorithm::eller,
    huntAndKill = pcg::engine::cpp_api::MazeAlgorithm::huntAndKill,
    recursiveBacktracker = pcg::engine::cpp_api::MazeAlgorithm::recursiveBacktracker,
    recursiveDivision = pcg::engine::cpp_api::MazeAlgorithm::recursiveDivision,
    kruskal = pcg::engine::cpp_api::MazeAlgorithm::kruskal,
    prim = pcg::engine::cpp_api::MazeAlgorithm::prim,
    growingTreeOldest = pcg::engine::cpp_api::MazeAlgorithm::growingTreeOldest,
    growingTreeMiddle = pcg::engine::cpp_api::MazeAlgorithm::growingTreeMiddle,
    growingTreeNewest = pcg::engine::cpp_api::MazeAlgorithm::growingTreeNewest,
    growingTreeRandom = pcg::engine::cpp_api::MazeAlgorithm::growingTreeRandom,
    blobbyDivisionCorridors = pcg::engine::cpp_api::MazeAlgorithm::blobbyDivisionCorridors,
    blobbyDivisionSmall = pcg::engine::cpp_api::MazeAlgorithm::blobbyDivisionSmall,
    blobbyDivisionMedium = pcg::engine::cpp_api::MazeAlgorithm::blobbyDivisionMedium,
    blobbyDivisionLarge = pcg::engine::cpp_api::MazeAlgorithm::blobbyDivisionLarge,
    blobbyDivisionHuge = pcg::engine::cpp_api::MazeAlgorithm::blobbyDivisionHuge,
};
