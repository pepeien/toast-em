#pragma once

#include "UI/Base.hpp"

namespace UI
{
    namespace View
    {
        const std::string TAG_ID = "View";

        void compileChild(const pugi::xml_node& inNode);
        void compile(const pugi::xml_node& inNode);
    }
}