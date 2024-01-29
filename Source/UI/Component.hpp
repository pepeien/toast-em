#pragma once

#include "UI/Base.hpp"

#include "Components/Text.hpp"

namespace UI
{
    const std::unordered_map<std::string, void (*)(const pugi::xml_node &inNode)> Components = {
        { Text::TAG_ID, &Text::compile }
    };
}