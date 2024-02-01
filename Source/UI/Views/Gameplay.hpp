#pragma once

#include "UI/Base.hpp"

#include "Character.hpp"
#include "State.hpp"

namespace UI
{
    namespace GameplayView
    {
        const std::string VIEW_ID = "gameplay-hud";

        void onHealButtonClick(pugi::xml_node& outNode);
        void onTakeDamageButtonClick(pugi::xml_node& outNode);
        void onHealthBarTick(pugi::xml_node& outNode);

        const ComponentCallbackMap Callbacks = {
            { "onHealButtonClick", &onHealButtonClick },
            { "onTakeDamageButtonClick", &onTakeDamageButtonClick },
            { "onHealthBarTick", &onHealthBarTick }
        };
    }
}