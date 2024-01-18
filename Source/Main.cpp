#include "Main.hpp"

int main(int argc, char *argv[])
{
    try
    {
        std::unique_ptr<Engine::Level> level = std::make_unique<Engine::Level>();
        level->setSkybox(Engine::Kerb::read("./Content/Textures/Skybox/Sunset"));
    
        std::unique_ptr<Engine::Actor> floor = std::make_unique<Engine::Actor>();
        floor->setAbsoluteTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
        floor->setAbsoluteScale(glm::vec3(0.5f, 0.5f, 0.5f));
        floor->setMesh(Engine::Kerb::read("./Content/Meshes/Apple"));

        level->addActor(floor.get());

        Engine::WindowCreateInfo windowCreateInfo = {};
        windowCreateInfo.title             = "Toast' Em";
        windowCreateInfo.resolution.width  = 1600;
        windowCreateInfo.resolution.height = 900;
        windowCreateInfo.level             = level.get();

        std::unique_ptr<Engine::Window> window = std::make_unique<Engine::Window>(windowCreateInfo);
        window->run();
    }
    catch (const std::exception& e)
    {
        LOG_CRITICAL(e.what());

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}