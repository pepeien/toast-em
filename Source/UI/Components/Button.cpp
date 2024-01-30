#include "Button.hpp"

#include "UI/Maps.hpp"

#include "Runtime/Core.hpp"

namespace UI
{
    namespace ButtonComponent
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

            auto buttonText = inNode.child_value();

            View activeView = getActiveView();

            std::string callbackSignature = inNode.attribute(ON_CLICK_ATTRIBUTE_NAME.c_str()).as_string();

            if (activeView.callbacks.find(callbackSignature) == activeView.callbacks.end())
            {
                ImGui::Button(buttonText);

                return;
            }

            if (ImGui::Button(buttonText))
            {
                activeView.callbacks.at(callbackSignature)(inNode);
            }
        }
    }
}