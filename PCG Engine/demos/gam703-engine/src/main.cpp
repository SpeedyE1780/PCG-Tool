#include <engine/core/Engine.hpp>

#include <engine/components/Camera.hpp>
#include <engine/components/DirectionalLight.hpp>
#include <engine/components/Renderer.hpp>
#include <engine/components/Transform.hpp>

#include <game/components/FollowTarget.hpp>
#include <game/components/MovementController.hpp>

#include <pcg/engine/level-generation/node.hpp>

#include <pcg/engine/cpp-api/api.hpp>

#include <iostream>
#include <format>

namespace engine = gam703::engine;
namespace game = gam703::game;

constexpr float PlaneSize = 5;

glm::vec3 white{ 1, 1, 1 };
glm::vec3 black{ 0, 0, 0 };
glm::vec3 red{ 1, 0, 0 };
glm::vec3 blue{ 0, 0, 1 };
int index = 0;

namespace
{
    void addNeighbor(gam703::engine::core::Engine& engine, pcg::engine::math::Vector3 point)
    {
        auto* cubeModel = engine.getResourceManager().getModel("resources/Models/cube/cube.obj");
        auto* cubeTransform = engine.getScene().addTransform(glm::vec3(point.x, point.y, point.z));
        auto* renderer = cubeTransform->addComponent<engine::components::Renderer>(cubeModel);
        renderer->getMaterial().setColor(index % 2 == 0 ? red : blue);
    }

    void addPoints(gam703::engine::core::Engine& engine, pcg::engine::math::Vector3 point)
    {
        auto* cubeModel = engine.getResourceManager().getModel("resources/Models/cube/cube.obj");
        auto* cubeTransform = engine.getScene().addTransform(glm::vec3(point.x, point.y, point.z), glm::vec3(), glm::vec3(PlaneSize, 0.2, PlaneSize));
        auto* renderer = cubeTransform->addComponent<engine::components::Renderer>(cubeModel);
        renderer->getMaterial().setColor(index % 2 == 0 ? white : black);
        index += 1;
    }

    void addWFCPoints(gam703::engine::core::Engine& engine, pcg::engine::math::Vector3 point, pcg::engine::utility::enums::Direction neighbors)
    {
        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::left))
        {
            addNeighbor(engine, point + pcg::engine::math::Vector3::left);
        }

        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::right))
        {
            addNeighbor(engine, point + pcg::engine::math::Vector3::right);
        }

        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::forward))
        {
            addNeighbor(engine, point + pcg::engine::math::Vector3::forward);
        }

        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::backward))
        {
            addNeighbor(engine, point + pcg::engine::math::Vector3::backward);
        }

        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::up))
        {
            addNeighbor(engine, point + pcg::engine::math::Vector3::up);
        }

        if (pcg::engine::utility::enums::hasFlag(neighbors, pcg::engine::utility::enums::Direction::down))
        {
            addNeighbor(engine, point + pcg::engine::math::Vector3::down);
        }

        addPoints(engine, point);
    }
}

int main()
{
    std::cout << "GAM703-GameEngine/PCG Engine Demo" << std::endl;
    std::cout << "Choose Option: " << std::endl;
    std::cout << "1 Simple Generation along Z Axis" << std::endl;
    std::cout << "2 2D Generation on XZ Plane" << std::endl;
    std::cout << "3 DFS Wave Function Collapse" << std::endl;
    std::cout << "4 BFS Wave Function Collapse" << std::endl;
    int choice = 0;
    std::cin >> choice;

    engine::core::Engine engine("GAM703", 1280, 720);
    auto& scene = engine.getScene();

    auto* cubeModel = engine.getResourceManager().getModel("resources/Models/cube/cube.obj");
    auto* playerTransform = scene.addTransform();
    auto* renderer = playerTransform->addComponent<engine::components::Renderer>(cubeModel);
    renderer->getMaterial().setColor(glm::vec3(0.0f, 0.0f, 1.0f));
    playerTransform->addBehavior<game::components::MovementController>();

    auto* cameraTransform = scene.addTransform(glm::vec3(0.0f, 20.0f, 20.0f), glm::vec3(glm::radians(-45.0f), glm::radians(-90.0f), 0));
    auto* camera = cameraTransform->addComponent<engine::components::Camera>();
    cameraTransform->addBehavior<game::components::FollowTarget>(playerTransform->getReference(), cameraTransform->getPosition());

    scene.setActiveCamera(camera);

    auto* directionalLightTransform = scene.addTransform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(glm::radians(-90.f), 0.0f, 0.0f));
    auto* directionalLight = directionalLightTransform->addComponent < engine::components::DirectionalLight>(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);

    pcg::engine::level_generation::GenerationData data{ 10, PlaneSize, { 0, 0, 0 } };
    auto addPointCallback = [&engine](pcg::engine::math::Vector3 point)
        {
            addPoints(engine, point);
        };

    auto addWFCPointCallback = [&engine](pcg::engine::math::Vector3 point, pcg::engine::utility::enums::Direction neighbors)
        {
            addWFCPoints(engine, point, neighbors);
        };

    switch (choice)
    {
    case 1:
    {
        pcg::engine::cpp_api::simpleGeneration(&data, pcg::engine::math::axis::z, pcg::engine::math::Direction::negative, addPointCallback);
        break;
    }
    case 2:
    {
        pcg::engine::cpp_api::multiDimensionGeneration(&data, pcg::engine::math::axis::xz, true, addPointCallback);
        break;
    }
    case 3:
    {
        data.limit = 100;
        pcg::engine::cpp_api::waveFunctionCollapseGeneration(&data, pcg::engine::level_generation::ExpansionMode::DFS, pcg::engine::math::axis::xz, addWFCPointCallback);
        break;
    }
    case 4:
    {
        data.limit = 100;
        pcg::engine::cpp_api::waveFunctionCollapseGeneration(&data, pcg::engine::level_generation::ExpansionMode::BFS, pcg::engine::math::axis::xz, addWFCPointCallback);
        break;
    }
    default:
    {
        std::cout << "Choice not valid" << std::endl;
        return 1;
    }
    }

    engine.start();

    return 0;
}
