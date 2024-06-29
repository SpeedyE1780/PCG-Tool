#ifndef PCG_ENGINE_MAZE_GENERATION_BLOBBY_DIVISION_HPP
#define PCG_ENGINE_MAZE_GENERATION_BLOBBY_DIVISION_HPP

#include <pcg/engine/maze-generation/Common.hpp>

namespace pcg::engine::maze_generation
{
    /// @brief SubRegionSize sets the size minimum size of a subregion
    enum class SubRegionSize
    {
        corridors = 0,
        small,
        medium,
        large,
        huge
    };

    /// @brief Geneate maze using Blobby Division Algorithm
    /// @param width Grid Width
    /// @param height Grid Height
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param regionSize Defines region size
    /// @param callback Callback when a node is generated
    void blobbyDivision(int width, int height, bool invokeAfterGeneration, SubRegionSize regionSize, MazeCallback&& callback);
    /// @brief Geneate maze using Blobby Division Algorithm
    /// @param width Grid Width
    /// @param height Grid Height
    /// @param invokeAfterGeneration If true callback will only be called after all nodes are generated
    /// @param regionThreshold User defined region threshold
    /// @param callback Callback when a node is generated
    void blobbyDivision(int width, int height, bool invokeAfterGeneration, int regionThreshold, MazeCallback&& callback);
}

#endif // PCG_ENGINE_MAZE_GENERATION_BLOBBY_DIVISION_HPP
