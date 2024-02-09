#pragma once

#include "Runtime/Game/State.hpp"
#include "Runtime/Grid/Essential.hpp"

#include "Character.hpp"

namespace UI
{
    namespace GameplayView
    {
        const std::string VIEW_ID = "gameplay-hud";

        void onFPSCounterTick(pugi::xml_node& outNode);
        void onFrametimeTick(pugi::xml_node& outNode);

        const Chicane::Grid::ComponentCallbackMap Callbacks = {
            { "onFPSCounterTick", &onFPSCounterTick },
            { "onFrametimeTick", &onFrametimeTick }
        };
    }
}