#include "Gameplay.hpp"

#include "Runtime/Core.hpp"

namespace UI
{
    namespace GameplayView
    {
        void onFirstButtonClick(const pugi::xml_node& inNode)
        {
            LOG_INFO("FIRST HUD BUTTON CLICK");
        }

        void onSecondButtonClick(const pugi::xml_node& inNode)
        {
            LOG_INFO("SECOND HUD BUTTON CLICK");
        }
    }
}