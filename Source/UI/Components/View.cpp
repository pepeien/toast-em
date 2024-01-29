#include "View.hpp"

#include "UI/Maps.hpp"

namespace UI
{
    namespace ViewComponent
    {
        void validate(const pugi::xml_node& inNode)
        {
            bool isRoot  = inNode.parent() == inNode.root();
            bool isAlone = isRoot && inNode.next_sibling() == nullptr;

            if (!isRoot || !isAlone)
            {
                throw std::runtime_error("UI document root element must not have any siblings");
            }

            if (ViewComponent::TAG_ID.compare(inNode.name()) != 0)
            {
                throw std::runtime_error("UI document root element must be a " + ViewComponent::TAG_ID);
            }

            std::string viewID = getID(inNode);

            if (viewID.empty())
            {
                return;
            }

            if (Views.find(viewID) == Views.end())
            {
                throw std::runtime_error("View ID " + viewID + " is not registered on the system");
            }
        }

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

        void compile(
            const pugi::xml_node& inNode,
            const Chicane::Vec2& inResolution,
            const Chicane::Vec2& inPosition
        )
        {
            validate(inNode);

            ImGuiWindowFlags viewFlags = ImGuiWindowFlags_NoNav |
                                         ImGuiWindowFlags_NoDecoration |
                                         ImGuiWindowFlags_NoMove |
                                         ImGuiWindowFlags_NoBackground;

            View activeView = {};
            activeView.callbacks = Views.at(getID(inNode));

            setActiveView(activeView);

            ImGui::Begin(
                inNode.attribute("title").as_string(),
                nullptr,
                viewFlags
            );
                ImGui::SetWindowSize(ImVec2(inResolution.x, inResolution.y));
                ImGui::SetWindowPos(ImVec2(inPosition.x, inPosition.y));

                for (pugi::xml_node& child : inNode.children())
                {
                    compileChild(child);
                }
            ImGui::End();
        }
    }
}