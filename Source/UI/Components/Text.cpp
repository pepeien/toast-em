#include "UI/Components/Text.hpp"

namespace UI
{
    namespace TextComponent
    {
        void compile(pugi::xml_node& outNode)
        {
            if (std::string(outNode.name()).compare(TAG_ID) != 0)
            {
                return;
            }

            if (outNode.children().empty())
            {
                return;
            }

            ImGui::Text(outNode.child_value());
        }
    }
}