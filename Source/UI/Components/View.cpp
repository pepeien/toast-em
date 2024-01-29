#include "View.hpp"

#include "UI/Component.hpp"

namespace UI
{
    namespace View
    {
        void compileChild(const pugi::xml_node& inNode)
        {
            if (inNode.name() == nullptr)
            {
                return;
            }

            std::string tagName = std::string(inNode.name());

            if (Components.find(tagName) == Components.end())
            {
                return;
            }

            Components.at(tagName)(inNode);

            for (pugi::xml_node& child : inNode.children())
            {
                compileChild(child);
            }
        }

        void compile(const pugi::xml_node& inNode)
        {
            if (std::string(inNode.name()).compare(TAG_ID) != 0)
            {
                return;
            }

            ImGui::Begin(inNode.attribute("title").as_string());
                for (pugi::xml_node& child : inNode.children())
                {
                    compileChild(child);
                }
            ImGui::End();
        }
    }
}