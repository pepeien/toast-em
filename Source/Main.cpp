#include "Main.hpp"

int main(int argc, char *argv[])
{
    try
    {
        std::unique_ptr<Chicane::Controller> controller = std::make_unique<Chicane::Controller>();

        State::setController(controller.get());

        Chicane::Box::Instance skybox = Chicane::Box::read("./Content/Textures/Skybox/Sunset");

        std::unique_ptr<Character> character = std::make_unique<Character>();
        character->setRelativeTranslation(glm::vec3(0.0f));
        character->setRelativeScale(glm::vec3(25.0f));
        character->setMesh(Chicane::Box::read("./Content/Meshes/Toaster"));

        controller->possess(character.get());

        std::unique_ptr<Chicane::Level> level = std::make_unique<Chicane::Level>();
        level->setSkybox(skybox);
        level->addActor(character.get());

        Chicane::WindowCreateInfo windowCreateInfo = {};
        windowCreateInfo.title         = "Toast' Em";
        windowCreateInfo.resolution.x  = 1600;
        windowCreateInfo.resolution.y  = 900;
        windowCreateInfo.displayIndex  = 1;

        std::unique_ptr<Chicane::Window> window = std::make_unique<Chicane::Window>(
            windowCreateInfo,
            controller.get(),
            level.get()
        );
        window->addLayer(new UI::Layer(window.get()));
        window->run();
    }
    catch (const std::exception& e)
    {
        LOG_CRITICAL(e.what());

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}