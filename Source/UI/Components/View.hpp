#pragma once

#include "UI/Base.hpp"

#include "Runtime/Base.hpp"

namespace UI
{
    namespace ViewComponent
    {
        const std::string TAG_ID = "View";

        void validate(const pugi::xml_node& inNode);
        void compileChild(const pugi::xml_node& inNode);
        void compile(
            const pugi::xml_node& inNode,
            const Chicane::Vec2& inResolution,
            const Chicane::Vec2& inPosition
        );
    }
}