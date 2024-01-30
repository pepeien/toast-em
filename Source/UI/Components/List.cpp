#include "List.hpp"

namespace UI
{
    namespace ListComponent
    {
        int getWidth(const pugi::xml_node& inNode)
        {
            return inNode.attribute(WIDTH_ATTRIBUTE_NAME.c_str()).as_int();
        }

        int getHeight(const pugi::xml_node& inNode)
        {
            return inNode.attribute(HEIGHT_ATTRIBUTE_NAME.c_str()).as_int();
        }

        Direction getDirection(const pugi::xml_node& inNode)
        {
            std::string rawDirection = inNode.attribute(DIRECTION_ATTRIBUTE_NAME.c_str()).as_string();

            std::transform(
                rawDirection.begin(),
                rawDirection.end(),
                rawDirection.begin(),
                ::toupper
            );

            if (rawDirection.compare(DIRECTION_ROW) == 0)
            {
                return Direction::Row;
            }

            return Direction::Column;
        }

        void validate(const pugi::xml_node& inNode)
        {
            if (TAG_ID.compare(inNode.name()) != 0)
            {
                throw std::runtime_error("Component is not a " + TAG_ID);
            }

            std::string title = getTitle(inNode);

            if (title.empty())
            {
                throw std::runtime_error(TAG_ID + " components must have a " + TITLE_ATTRIBUTE_NAME + " attribute");
            }
        }

        void compile(const pugi::xml_node& inNode)
        {
            validate(inNode);

            Direction direction = getDirection(inNode);

            ImGui::BeginChild(
                getTitle(inNode).c_str(),
                ImVec2(getWidth(inNode), getHeight(inNode))
            );
                if (!inNode.children().empty())
                {
                    for (pugi::xml_node& child : inNode.children())
                    {
                        if (direction == Direction::Row)
                        {
                            ImGui::SameLine();
                        }

                        compileChildRecursive(child);
                    }
                }
            ImGui::EndChild();
        }
    }
}