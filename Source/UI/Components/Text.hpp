#pragma once

#include "UI/Base.hpp"

namespace UI
{
    namespace TextComponent
    {
        const std::string TAG_ID = "Text";

        void compile(pugi::xml_node& outNode);
    }
}