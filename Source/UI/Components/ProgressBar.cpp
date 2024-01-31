#include "ProgressBar.hpp"

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
                    getAttribute(WIDTH_ATTRIBUTE_NAME, outNode).as_float(),
                    getAttribute(HEIGHT_ATTRIBUTE_NAME, outNode).as_float()
                ),
                outNode.value()
            );
        }
    }
}