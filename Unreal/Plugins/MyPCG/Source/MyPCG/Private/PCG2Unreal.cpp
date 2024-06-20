#include "PCG2Unreal.h"

pcg::engine::math::Vector3 FVectorToPCGVector(const FVector& vector)
{
    return pcg::engine::math::Vector3{ (float)vector.Y, (float)vector.Z, (float)vector.X };
}

FVector PCGVectorToFVector(const pcg::engine::math::Vector3& vector)
{
    return FVector{ vector.z, vector.x, vector.y };
}
