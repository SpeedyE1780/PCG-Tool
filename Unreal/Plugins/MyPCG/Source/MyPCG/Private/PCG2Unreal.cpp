#include "MyPCG/PCG2Unreal.h"

namespace math = pcg::engine::math;

math::Vector3 FVectorToPCGVector(const FVector& vector)
{
    return math::Vector3{ vector.Y, vector.Z, vector.X };
}

FVector PCGVectorToFVector(const math::Vector3& vector)
{
    return FVector{ vector.z, vector.x, vector.y };
}

FVector PCGVectorToFVector(const math::Vector4& vector)
{
    return FVector{ vector.z, vector.x, vector.y };
}
