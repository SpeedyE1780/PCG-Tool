#pragma once

#include "CoreMinimal.h"
#include "pcg/engine/math/Vector3.hpp"
#include "pcg/engine/math/Vector4.hpp"

MYPCG_API pcg::engine::math::Vector3 FVectorToPCGVector(const FVector& vector);
MYPCG_API FVector PCGVectorToFVector(const pcg::engine::math::Vector3& vector);
MYPCG_API FVector PCGVectorToFVector(const pcg::engine::math::Vector4& vector);
