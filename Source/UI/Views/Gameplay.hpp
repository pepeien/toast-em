#pragma once

#include "UI/Base.hpp"

namespace UI
{
    namespace GameplayView
    {
        const std::string VIEW_ID = "gameplay-hud";

        void onFirstButtonClick(const pugi::xml_node& inNode);
        void onSecondButtonClick(const pugi::xml_node& inNode);

        const ComponentCallbackMap Callbacks = {
            { "onFirstButtonClick", &onFirstButtonClick },
            { "onSecondButtonClick", &onSecondButtonClick }
        };
    }
}