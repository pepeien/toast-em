#pragma once

#include "UI/Base.hpp"

namespace UI
{
    namespace ButtonComponent
    {
        const std::string TAG_ID                = "Button";
        const std::string ON_CLICK_ATTRIBUTE_ID = "onClick";

        void compile(const pugi::xml_node& inNode);
    }
}