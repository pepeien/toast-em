#pragma once

#include "Runtime/Game.hpp"
#include "Runtime/Core.hpp"

namespace State
{
    void setCamera(Chicane::Camera* inCamera);
    Chicane::Camera* getCamera();

    void setController(Chicane::Controller* inController);
    Chicane::Controller* getController();

    void setStats(const Chicane::Stats& inStats);
    Chicane::Stats getStats();

    void setResolution(const Chicane::Vec2& inResolution);
    Chicane::Vec2 getResolution();
}