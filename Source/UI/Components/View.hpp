#pragma once

#include "UI/Base.hpp"

#include "Runtime/Base.hpp"

namespace UI
{
    namespace ViewComponent
    {
        const std::string TAG_ID = "View";

        void validate(const pugi::xml_node& inNode);
        void compile(
            pugi::xml_node& outNode,
            const Chicane::Vec2& inResolution,
            const Chicane::Vec2& inPosition
        );
    }
}