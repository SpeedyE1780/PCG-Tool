#ifndef PCG_ENGINE_MAZE_COMMON_HPP
#define PCG_ENGINE_MAZE_COMMON_HPP

#include <pcg/engine/math/vector3.hpp>

#include <pcg/engine/utility/CallbackFunctor.hpp>
#include <pcg/engine/utility/Enums.hpp>

#include <tuple>
#include <vector>

namespace pcg::engine::maze
{
    using Grid = std::vector<std::vector<utility::enums::Direction>>;
    using MazeCallback = utility::CallbackFunctor<void(int, int, utility::enums::Direction)>;

    inline constexpr int in = 1 << 6;

    utility::enums::Direction getFlippedDirection(utility::enums::Direction direction);
    std::tuple<int, int> getNeighborXY(int x, int y, utility::enums::Direction direction);
    inline constexpr Grid generateGrid(int width, int height, utility::enums::Direction defaultValue = utility::enums::Direction::none) { return Grid(width, std::vector<utility::enums::Direction>(height, defaultValue)); }
}

#endif // PCG_ENGINE_MAZE_COMMON_HPP
