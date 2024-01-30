#pragma once

#include "UI/Base.hpp"

namespace UI
{
    namespace ListComponent
    {
        const std::string TAG_ID = "List";

        // Attributes
        const std::string WIDTH_ATTRIBUTE_NAME     = "width";
        const std::string HEIGHT_ATTRIBUTE_NAME    = "height";
        const std::string DIRECTION_ATTRIBUTE_NAME = "direction";

        // Direction
        const std::string DIRECTION_ROW    = "ROW";
        const std::string DIRECTION_COLUMN = "COLUMN";

        enum class Direction : uint8_t
        {
            Column,
            Row
        };

        int getWidth(const pugi::xml_node& inNode);
        int getHeight(const pugi::xml_node& inNode);
        Direction getDirection(const pugi::xml_node& inNode);

        void validate(const pugi::xml_node& inNode);
        void compile(const pugi::xml_node& inNode);
    }
}