#include <pcg/engine/core/generators.hpp>
#include <pcg/engine/math/random.hpp>

#include <functional>
#include <optional>
#include <unordered_set>

namespace pcg::engine::core
{
    void setSeed(unsigned int seed)
    {
        math::Random::seed(seed);
    }

    void simpleGeneration(GenerationData* data, math::Axis axis, math::Direction direction, addPointCallback callback)
    {
        std::function<void()> updatePosition;
        math::Vector3 position = data->startPoint;
        float offset = direction == math::Direction::positive ? data->size : -data->size;

        switch (axis)
        {
        case math::Axis::x:
        {
            updatePosition = [&position, offset]()
                {
                    position.x += offset;
                };
            break;
        }
        case math::Axis::y:
        {
            updatePosition = [&position, offset]()
                {
                    position.y += offset;
                };
            break;
        }
        case math::Axis::z:
        {
            updatePosition = [&position, offset]()
                {
                    position.z += offset;
                };
            break;
        }
        default:
        {
            break;
        }
        }

        for (int i = 0; i < data->limit; i++)
        {
            callback(position);
            updatePosition();
        }
    }

    static std::optional<math::Vector3> getNextPosition(std::unordered_set<math::Vector3, math::Vector3Hash>& positions, const math::Vector3& currentPosition, const std::vector<const math::Vector3*>& directions, float offset)
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

        return availablePositions[math::Random::generate() % availablePositions.size()];
    }

    static void multiDimensionalGeneration(GenerationData* data, const std::vector<const math::Vector3*>& directions, bool disableOverlap, addPointCallback callback)
    {
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
                return;
            }

            position = nextPosition.value();
        }
    }

    void generation2D(GenerationData* data, math::Plane plane, bool disableOverlap, addPointCallback callback)
    {
        std::vector<const math::Vector3*> directions{};

        switch (plane)
        {
        case math::Plane::xy:
            directions.insert(begin(directions), { &math::Vector3::right, &math::Vector3::left, &math::Vector3::up, &math::Vector3::down });
            break;
        case math::Plane::xz:
            directions.insert(begin(directions), { &math::Vector3::right, &math::Vector3::left, &math::Vector3::forward, &math::Vector3::backward });
            break;
        case math::Plane::yz:
            directions.insert(begin(directions), { &math::Vector3::up, &math::Vector3::down, &math::Vector3::forward, &math::Vector3::backward });
            break;
        default:
            break;
        }

        multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }

    void generation3D(GenerationData* data, bool disableOverlap, addPointCallback callback)
    {
        static const std::vector<const math::Vector3*> directions{ {&math::Vector3::right, &math::Vector3::left, &math::Vector3::up, &math::Vector3::down, &math::Vector3::forward, &math::Vector3::backward} };
        multiDimensionalGeneration(data, directions, disableOverlap, callback);
    }
}
