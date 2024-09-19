#include <pcg/engine/level-generation/MultiDimensionalGeneration.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <optional>
#include <unordered_set>

namespace pcg::engine::level_generation
{
    namespace
    {
        /// @brief Get next valid position to spawn node
        /// @param spawnedPositions Set of positions containing nodes
        /// @param currentPosition Current node position
        /// @param directions Possible directions to reach adjacent node
        /// @param offset Offset between each node
        /// @return The next valid position or null if no position is found
        std::optional<math::Vector3> getNextPosition(std::unordered_set<math::Vector3>& spawnedPositions, const math::Vector3& currentPosition, const std::vector<const math::Vector3*>& directions, float offset)
        {
            std::vector<math::Vector3> availablePositions{};

            for (const auto* direction : directions)
            {
                math::Vector3 nodePosition = currentPosition + *direction * offset;

                if (spawnedPositions.find(nodePosition) == end(spawnedPositions))
                {
                    availablePositions.emplace_back(std::move(nodePosition));
                }
            }

            if (availablePositions.size() == 0)
            {
                return std::nullopt;
            }

            return math::Random::element<math::Vector3>(availablePositions);
        }
    }

    void multiDimensionalGeneration(const GenerationData& data, math::Axis axes, bool disableOverlap, const std::function<void(math::Vector3)>& callback)
    {
        utility::logInfo("Multi-Dimension Generation Started");

        std::vector<const math::Vector3*> directions = math::Vector3::getUnitVectors(axes);

        if (directions.empty())
        {
            utility::logError("Invalid axes passed to multiDimensionalGeneration");
            return;
        }

        std::unordered_set<math::Vector3> spawnedPositions{};
        math::Vector3 nodePosition = data.startPoint;

        for (int i = 0; i < data.count; i++)
        {
            callback(nodePosition);

            if (disableOverlap)
            {
                spawnedPositions.insert(nodePosition);
            }

            auto nextPosition = getNextPosition(spawnedPositions, nodePosition, directions, data.size);

            if (!nextPosition.has_value())
            {
                utility::logInfo("Multi-Dimension Generation Ended Early");
                return;
            }

            nodePosition = nextPosition.value();
        }

        utility::logInfo("Multi-Dimension Generation Ended");
    }
}
