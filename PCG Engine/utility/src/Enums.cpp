#include <pcg/engine/utility/Enums.hpp>
#include <pcg/engine/utility/logging.hpp>

namespace pcg::engine::utility::enums
{
    Direction getFlippedDirection(Direction direction)
    {
        switch (direction)
        {
        case Direction::left:
        {
            return Direction::right;
        }
        case Direction::right:
        {
            return Direction::left;
        }
        case Direction::forward:
        {
            return Direction::backward;
        }
        case Direction::backward:
        {
            return Direction::forward;
        }
        default:
        {
            utility::logError("Invalid direction passed to getFlippedDirection");
            return Direction::none;
        }
        }
    }
}
