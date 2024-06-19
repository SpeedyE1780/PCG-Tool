#include <pcg/engine/level-generation/MultiDimensionalGeneration.hpp>

#include <pcg/engine/math/random.hpp>

#include <pcg/engine/utility/logging.hpp>

#include <optional>
#include <unordered_set>

namespace pcg::engine::level_generation
{
    namespace
    {
        std::optional<math::Vector3> getNextPosition(std::unordered_set<math::Vector3>& positions, const math::Vector3& currentPosition, const std::vector<const math::Vector3*>& directions, float offset)
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

            return availablePositions[math::Random::generateNumber(0, availablePositions.size())];
        }
    }

    void multiDimensionalGeneration(GenerationData* data, const std::vector<const math::Vector3*>& directions, bool disableOverlap, utility::CallbackFunctor<void(math::Vector3)>&& callback)
    {
        utility::logInfo("Multi-Dimension Generation Started");

        std::unordered_set<math::Vector3> positions{};
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

