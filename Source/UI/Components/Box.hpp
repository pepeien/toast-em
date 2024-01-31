#pragma once

#include "UI/Base.hpp"

#include <imgui/imgui_internal.h>

namespace UI
{
    namespace BoxComponent
    {
        const std::string TAG_ID = "Box";

        void compile(pugi::xml_node& outNode);
    }
}