#ifndef PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP
#define PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP

#include <pcg/engine/maze/Common.hpp>

namespace pcg::engine::maze
{
    const math::Vector3& getDirection(int direction)
    {
        switch (direction)
        {
        case left:
        {
            return math::Vector3::left;
        }
        case right:
        {
            return math::Vector3::right;
        }
        case up:
        {
            return math::Vector3::up;
        }
        case down:
        {
            return math::Vector3::down;
        }
        default:
        {
            return math::Vector3::left;
        }
        }
    }

    int getFlippedDirection(int direction)
    {
        switch (direction)
        {
        case left:
        {
            return right;
        }
        case right:
        {
            return left;
        }
        case up:
        {
            return down;
        }
        case down:
        {
            return up;
        }
        default:
        {
            return left;
        }
        }
    }

    std::tuple<int, int> getNeighborXY(int x, int y, int direction)
    {
        const math::Vector3& directionVector = getDirection(direction);
        int nx = x + directionVector.x;
        int ny = y + directionVector.y;
        return { nx, ny };
    }
}

#endif // PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP
