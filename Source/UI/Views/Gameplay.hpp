#pragma once

#include "UI/Base.hpp"

namespace UI
{
    namespace GameplayView
    {
        const std::string VIEW_ID = "gameplay-hud";

        void onFirstButtonClick(pugi::xml_node& outNode);
        void onSecondButtonClick(pugi::xml_node& outNode);
        void onProgressBarTick(pugi::xml_node& outNode);

        const ComponentCallbackMap Callbacks = {
            { "onFirstButtonClick", &onFirstButtonClick },
            { "onSecondButtonClick", &onSecondButtonClick },
            { "onProgressBarTick", &onProgressBarTick }
        };
    }
}