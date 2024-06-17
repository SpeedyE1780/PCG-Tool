#ifndef PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP
#define PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP

#include <pcg/engine/maze/Common.hpp>

namespace pcg::engine::maze
{
    namespace
    {
        constexpr const math::Vector3& getDirection(utility::enums::Direction direction)
        {
            switch (direction)
            {
            case utility::enums::Direction::left:
            {
                return math::Vector3::left;
            }
            case utility::enums::Direction::right:
            {
                return math::Vector3::right;
            }
            case utility::enums::Direction::forward:
            {
                return math::Vector3::up;
            }
            case utility::enums::Direction::backward:
            {
                return math::Vector3::down;
            }
            default:
            {
                return math::Vector3::left;
            }
            }
        }
    }

    utility::enums::Direction getFlippedDirection(utility::enums::Direction direction)
    {
        switch (direction)
        {
        case utility::enums::Direction::left:
        {
            return utility::enums::Direction::right;
        }
        case utility::enums::Direction::right:
        {
            return utility::enums::Direction::left;
        }
        case utility::enums::Direction::forward:
        {
            return utility::enums::Direction::backward;
        }
        case utility::enums::Direction::backward:
        {
            return utility::enums::Direction::forward;
        }
        default:
        {
            return utility::enums::Direction::left;
        }
        }
    }

    std::tuple<int, int> getNeighborXY(int x, int y, utility::enums::Direction direction)
    {
        const math::Vector3& directionVector = getDirection(direction);
        int nx = x + directionVector.x;
        int ny = y + directionVector.y;
        return { nx, ny };
    }
}

#endif // PCG_ENGINE_MAZE_ALDOUS_BRODER_HPP
