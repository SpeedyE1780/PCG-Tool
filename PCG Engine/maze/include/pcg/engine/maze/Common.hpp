#ifndef PCG_ENGINE_MAZE_COMMON_HPP
#define PCG_ENGINE_MAZE_COMMON_HPP

#include <pcg/engine/math/vector3.hpp>

#include <tuple>

namespace pcg::engine::maze
{
    static constexpr int left = 1 << 0;
    static constexpr int right = 1 << 1;
    static constexpr int up = 1 << 2;
    static constexpr int down = 1 << 3;
    static constexpr int in = 1 << 6;

    const math::Vector3& getDirection(int direction);
    int getFlippedDirection(int direction);
    std::tuple<int, int> getNeighborXY(int x, int y, int direction);
}

#endif // PCG_ENGINE_MAZE_COMMON_HPP
