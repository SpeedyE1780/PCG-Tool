#ifndef PCG_ENGINE_MAZE_MAZE_HPP
#define PCG_ENGINE_MAZE_MAZE_HPP

#include <pcg/engine/maze/AldousBroder.hpp>
#include <pcg/engine/maze/BinaryTree.hpp>
#include <pcg/engine/maze/Sidewinder.hpp>
#include <pcg/engine/maze/Wilson.hpp>

namespace pcg::engine::maze
{
    typedef void (*addMazePointCallback)(int x, int y, int neighbors);
}

#endif // PCG_ENGINE_MAZE_MAZE_HPP
