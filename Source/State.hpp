#pragma once

#include "Runtime/Game.hpp"

namespace State
{
    void setController(Chicane::Controller* inController);
    Chicane::Controller* getController();
}