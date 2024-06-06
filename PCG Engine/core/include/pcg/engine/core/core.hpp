#ifndef PCG_ENGINE_CORE_CORE_HPP
#define PCG_ENGINE_CORE_CORE_HPP

#include <pcg/engine/core/config.hpp>

#include <pcg/engine/math/enums.hpp>

namespace pcg::engine::core
{
    struct Vector3
    {
        float x;
        float y;
        float z;

        void operator+=(const Vector3& rhs);
    };

    typedef void (*addPointCallback)(Vector3 vector);

    struct GenerationData
    {
        unsigned int limit;
        float size;
        Vector3 startPoint;
    };
    
    Vector3 operator*(const Vector3& vector, float scalar);
    Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    bool operator==(const Vector3& lhs, const Vector3& rhs);

    PCG_ENGINE_CORE_API int add(int x, int y);
    PCG_ENGINE_CORE_API void setSeed(unsigned int seed);
    PCG_ENGINE_CORE_API void simpleGeneration(GenerationData* data, math::Axis axis, math::Direction direction, addPointCallback callback);
    PCG_ENGINE_CORE_API void generation2D(GenerationData* data, math::Plane plane, bool disableOverlap, addPointCallback callback);
    PCG_ENGINE_CORE_API void generation3D(GenerationData* data, bool disableOverlap, addPointCallback callback);
}

#endif // PCG_ENGINE_CORE_CORE_HPP
