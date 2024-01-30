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

            if (TAG_ID.compare(inNode.name()) != 0)
            {
                throw std::runtime_error("UI document root element must be a " + TAG_ID);
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
                getTitle(inNode).c_str(),
                nullptr,
                viewFlags
            );
                ImGui::SetWindowSize(ImVec2(inResolution.x, inResolution.y));
                ImGui::SetWindowPos(ImVec2(inPosition.x, inPosition.y));

                compileChildren(inNode);
            ImGui::End();
        }
    }
}