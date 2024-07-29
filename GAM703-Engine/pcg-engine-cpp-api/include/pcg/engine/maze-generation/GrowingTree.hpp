#ifndef PCG_ENGINE_MAZE_GENERATION_GROWING_TREE_HPP
#define PCG_ENGINE_MAZE_GENERATION_GROWING_TREE_HPP

#include <pcg/engine/maze-generation/Common.hpp>

namespace pcg::engine::maze_generation
{
    /// @brief GrowingTreeSelectionMethod defines how will the next node be chosen
    enum class GrowingTreeSelectionMethod
    {
        oldest = 0,
        middle = 1,
        newest = 2,
        random = 3
    };

    /// @brief Geneate maze using Growing Tree Algorithm
    /// @param width Grid Width
    /// @param height Grid Height
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param method Callback used to select the next node
    /// @param callback Callback when a node is generated
    void growingTree(int width, int height, bool invokeAfterGeneration, GrowingTreeSelectionMethod method, MazeCallback&& callback);
    /// @brief Geneate maze using Growing Tree Algorithm
    /// @param width Grid Width
    /// @param height Grid Height
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param nodeSelectionCallback Callback used to select a node from pending growing tree nodes
    /// @param callback Callback when a node is generated
    void growingTree(int width, int height, bool invokeAfterGeneration, utility::CallbackFunctor<int(int)>&& nodeSelectionCallback, MazeCallback&& callback);
}

#endif // PCG_ENGINE_MAZE_GENERATION_GROWING_TREE_HPP
