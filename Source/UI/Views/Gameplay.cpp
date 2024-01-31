#include "Gameplay.hpp"

#include "Runtime/Core.hpp"

namespace UI
{
    namespace GameplayView
    {
        int percentageModifier = 1;
        float percentage       = 0.0f;

        void onFirstButtonClick(pugi::xml_node& outNode)
        {
            LOG_INFO("FIRST HUD BUTTON CLICK");
        }

        void onSecondButtonClick(pugi::xml_node& outNode)
        {
            LOG_INFO("SECOND HUD BUTTON CLICK");
        }

        void onProgressBarTick(pugi::xml_node& outNode)
        {
            if (percentage >= 100.0f)
            {
                percentageModifier = -1;
            }

            if (percentage <= 0.0f)
            {
                percentageModifier = 1;
            }

            if (outNode.attribute("percentage").empty())
            {
                outNode.append_attribute("percentage");
            }

            outNode.attribute("percentage").set_value(percentage);

            percentage += 0.005f * percentageModifier;
        }
    }
}