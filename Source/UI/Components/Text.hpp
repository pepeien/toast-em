#pragma once

#include "UI/Base.hpp"

namespace UI
{
    namespace TextComponent
    {
        const std::string TAG_ID = "Text";

        void compile(const pugi::xml_node& inNode);
    }
}