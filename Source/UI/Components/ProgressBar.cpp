#include "UI/Components/ProgressBar.hpp"

#include "UI/Maps.hpp"

namespace UI
{
    namespace ProgressBarComponent
    {
        void compile(pugi::xml_node& outNode)
        {
            float percentage = std::clamp(
                getAttribute(PERCENTAGE_ATTRIBUTE_NAME, outNode).as_float(),
                MIN_PERCENTAGE,
                MAX_PERCENTAGE
            ) / 100;

            ImGui::ProgressBar(
                percentage,
                ImVec2(
                    getSize(WIDTH_ATTRIBUTE_NAME, outNode),
                    getSize(HEIGHT_ATTRIBUTE_NAME, outNode)
                ),
                outNode.child_value()
            );
        }
    }
}