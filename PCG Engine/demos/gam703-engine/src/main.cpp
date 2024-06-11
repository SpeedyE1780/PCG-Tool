#include <engine/core/Engine.hpp>

#include <engine/components/Camera.hpp>
#include <engine/components/DirectionalLight.hpp>
#include <engine/components/Renderer.hpp>
#include <engine/components/Transform.hpp>

#include <game/components/FollowTarget.hpp>
#include <game/components/MovementController.hpp>

#include <pcg/engine/core/generators.hpp>
#include <pcg/engine/core/node.hpp>

#include <iostream>
#include <format>

namespace engine = gam703::engine;
namespace game = gam703::game;

constexpr float PlaneSize = 5;

engine::core::Engine* pxEngine = nullptr;

glm::vec3 white{ 1, 1, 1 };
glm::vec3 black{ 0, 0, 0 };
glm::vec3 red{ 1, 0, 0 };
glm::vec3 blue{ 0, 0, 1 };
int index = 0;

namespace
{
    void addNeighbor(pcg::engine::math::Vector3 point)
    {
        auto* cubeModel = pxEngine->getResourceManager().getModel("resources/Models/cube/cube.obj");
        auto* cubeTransform = pxEngine->getScene().addTransform(glm::vec3(point.x, point.y, point.z));
        auto* renderer = cubeTransform->addComponent<engine::components::Renderer>(cubeModel);
        renderer->getMaterial().setColor(index % 2 == 0 ? red : blue);
    }

    void addPoints(pcg::engine::math::Vector3 point)
    {
        auto* cubeModel = pxEngine->getResourceManager().getModel("resources/Models/cube/cube.obj");
        auto* cubeTransform = pxEngine->getScene().addTransform(glm::vec3(point.x, point.y, point.z), glm::vec3(), glm::vec3(PlaneSize, 0.2, PlaneSize));
        auto* renderer = cubeTransform->addComponent<engine::components::Renderer>(cubeModel);
        renderer->getMaterial().setColor(index % 2 == 0 ? white : black);
        index += 1;
    }

    void addWFCPoints(pcg::engine::math::Vector3 point, int neighbors)
    {
        if (neighbors & pcg::engine::core::Neighbors::left)
        {
            addNeighbor(point + pcg::engine::math::Vector3::left);
        }

        if (neighbors & pcg::engine::core::Neighbors::right)
        {
            addNeighbor(point + pcg::engine::math::Vector3::right);
        }

        if (neighbors & pcg::engine::core::Neighbors::forward)
        {
            addNeighbor(point + pcg::engine::math::Vector3::forward);
        }

        if (neighbors & pcg::engine::core::Neighbors::backward)
        {
            addNeighbor(point + pcg::engine::math::Vector3::backward);
        }

        if (neighbors & pcg::engine::core::Neighbors::up)
        {
            addNeighbor(point + pcg::engine::math::Vector3::up);
        }

        if (neighbors & pcg::engine::core::Neighbors::down)
        {
            addNeighbor(point + pcg::engine::math::Vector3::down);
        }

        addPoints(point);
    }
}

int main()
{
    std::cout << "GAM703-GameEngine/PCG Engine Demo" << std::endl;
    std::cout << "Choose Option: " << std::endl;
    std::cout << "1 Simple Generation along Z Axis" << std::endl;
    std::cout << "2 2D Generation on XZ Plane" << std::endl;
    std::cout << "3 Wave Function Collapse" << std::endl;
    int choice = 0;
    std::cin >> choice;

    engine::core::Engine engine("GAM703", 1280, 720);
    pxEngine = &engine;
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

    pcg::engine::core::GenerationData data{ 10, PlaneSize, { 0, 0, 0 } };
    switch (choice)
    {
    case 1:
    {
        pcg::engine::core::simpleGeneration(&data, pcg::engine::math::Axis::z, pcg::engine::math::Direction::negative, addPoints);
        break;
    }
    case 2:
    {
        pcg::engine::core::generation2D(&data, pcg::engine::math::Plane::xz, true, addPoints);
        break;
    }
    case 3:
    {
        data.limit = 100;
        pcg::engine::core::waveFunctionCollapse(&data, addWFCPoints);
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
