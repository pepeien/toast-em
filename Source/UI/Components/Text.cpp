#include "Text.hpp"

namespace UI
{
    namespace Text
    {
        void compile(const pugi::xml_node& inNode)
        {
            if (std::string(inNode.name()).compare(TAG_ID) != 0)
            {
                return;
            }

            if (inNode.children().empty())
            {
                return;
            }

            ImGui::Text(inNode.child_value());
        }
    }
}