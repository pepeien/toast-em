#pragma once

#include "UI/Base.hpp"

#include "Character.hpp"
#include "State.hpp"

namespace UI
{
    namespace GameplayView
    {
        const std::string VIEW_ID = "gameplay-hud";

        void onFPSCounterTick(pugi::xml_node& outNode);
        void onFrametimeTick(pugi::xml_node& outNode);

        const ComponentCallbackMap Callbacks = {
            { "onFPSCounterTick", &onFPSCounterTick },
            { "onFrametimeTick", &onFrametimeTick }
        };
    }
}