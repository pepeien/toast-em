#include "Main.hpp"

int main(int argc, char *argv[])
{
    try
    {
        std::unique_ptr<Chicane::Level> level = std::make_unique<Chicane::Level>();
        std::unique_ptr<Chicane::Controller> controller = std::make_unique<Chicane::Controller>();

        Chicane::State::setController(controller.get());

        Chicane::Box::Instance skybox = Chicane::Box::read("./Content/Textures/SKY_Grid");
        level->setSkybox(skybox);

        std::unique_ptr<Character> character = std::make_unique<Character>();
        character->setRelativeTranslation(glm::vec3(0.0f));
        character->setRelativeScale(glm::vec3(25.0f));
        character->setRelativeRotation(glm::vec3(-90.0f, 0.0f, -90.0f));
        character->setMesh(Chicane::Box::read("./Content/Meshes/Toaster"));
        level->addActor(character.get());
        controller->possess(character.get());

        Chicane::WindowCreateInfo windowCreateInfo = {};
        windowCreateInfo.title         = "Toast' Em";
        windowCreateInfo.resolution.x  = 1600;
        windowCreateInfo.resolution.y  = 900;
        windowCreateInfo.type          = Chicane::WindowType::Windowed;
        windowCreateInfo.displayIndex  = 1;

        std::unique_ptr<Chicane::Window> window = std::make_unique<Chicane::Window>(
            windowCreateInfo,
            controller.get(),
            level.get()
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