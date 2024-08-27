#include "MyPCG/PCG2Unreal.h"

namespace math = pcg::engine::math;

math::Vector3 FVectorToPCGVector(const FVector& vector)
{
    return math::Vector3{ (float)vector.Y, (float)vector.Z, (float)vector.X };
}

FVector PCGVectorToFVector(const math::Vector3& vector)
{
    return FVector{ vector.z, vector.x, vector.y };
}
