#include "Main.hpp"

int main(int argc, char *argv[])
{
    try
    {
        std::unique_ptr<Engine::Controller> controller = std::make_unique<Engine::Controller>();

        Engine::Kerb::Instance skybox = Engine::Kerb::read("./Content/Textures/Skybox/Sunset");

        std::unique_ptr<Character> character = std::make_unique<Character>();
        character->setRelativeTranslation(glm::vec3(0.0f));
        character->setRelativeScale(glm::vec3(25.0f));
        character->setMesh(Engine::Kerb::read("./Content/Meshes/Cube"));

        controller->possess(character.get());

        std::unique_ptr<Engine::Level> level = std::make_unique<Engine::Level>();
        level->setSkybox(skybox);
        level->addActor(character.get());

        Engine::WindowCreateInfo windowCreateInfo = {};
        windowCreateInfo.title             = "Toast' Em";
        windowCreateInfo.resolution.width  = 1600;
        windowCreateInfo.resolution.height = 900;

        std::unique_ptr<Engine::Window> window = std::make_unique<Engine::Window>(
            windowCreateInfo,
            level.get(),
            controller.get()
        );
        window->run();
    }
    catch (const std::exception& e)
    {
        LOG_CRITICAL(e.what());

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}