#ifndef PCG_ENGINE_CORE_CORE_HPP
#define PCG_ENGINE_CORE_CORE_HPP

#include <pcg/engine/core/config.hpp>

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

    enum class Axis
    {
        x = 0,
        y = 1,
        z = 2
    };

    enum class Direction
    {
        positive = 0,
        negative = 1
    };

    enum class Plane
    {
        xy = 0,
        xz = 1,
        yz = 2
    };

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
    PCG_ENGINE_CORE_API void simpleGeneration(GenerationData* data, Axis axis, Direction direction, addPointCallback callback);
    PCG_ENGINE_CORE_API void generation2D(GenerationData* data, Plane plane, bool disableOverlap, addPointCallback callback);
    PCG_ENGINE_CORE_API void generation3D(GenerationData* data, bool disableOverlap, addPointCallback callback);
}

#endif // PCG_ENGINE_CORE_CORE_HPP
