#ifndef PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP
#define PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP

#include <pcg/engine/level-generation/GenerationData.hpp>

#include <pcg/engine/math/enums.hpp>
#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <optional>
#include <unordered_set>
#include <vector>

namespace pcg::engine::level_generation
{
    namespace
    {
        std::optional<math::Vector3> getNextPosition(std::unordered_set<math::Vector3, math::Vector3Hash>& positions, const math::Vector3& currentPosition, const std::vector<const math::Vector3*>& directions, float offset)
        {
            std::vector<math::Vector3> availablePositions{};

            for (const auto* direction : directions)
            {
                math::Vector3 position = currentPosition + *direction * offset;

                if (positions.find(position) == end(positions))
                {
                    availablePositions.emplace_back(std::move(position));
                }
            }

            if (availablePositions.size() == 0)
            {
                return std::nullopt;
            }

            return availablePositions[math::Random::generate(0, availablePositions.size())];
        }
    }

    template<typename addPointCallback>
    void multiDimensionalGeneration(GenerationData* data, const std::vector<const math::Vector3*>& directions, bool disableOverlap, addPointCallback callback)
    {
        utility::logInfo("Multi-Dimension Generation Started");

        std::unordered_set<math::Vector3, math::Vector3Hash> positions{};
        math::Vector3 position = data->startPoint;

        for (int i = 0; i < data->limit; i++)
        {
            callback(position);

            if (disableOverlap)
            {
                positions.insert(position);
            }

            auto nextPosition = getNextPosition(positions, position, directions, data->size);

            if (!nextPosition.has_value())
            {
                utility::logInfo("Multi-Dimension Generation Ended Early");
                return;
            }

            position = nextPosition.value();
        }

        utility::logInfo("Multi-Dimension Generation Ended");
    }
}

#endif // PCG_ENGINE_LEVEL_GENERATION_MULTI_DIMENSIONAL_GENERATION_HPP
