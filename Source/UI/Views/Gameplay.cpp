#include "Gameplay.hpp"

#include "Runtime/Core.hpp"

namespace UI
{
    namespace GameplayView
    {
        int percentageModifier = 1;
        float percentage       = 0.0f;

        void onHealButtonClick(pugi::xml_node& outNode)
        {
            Character* character = State::getController()->getPawn<Character>();

            if (character->isFullHealth())
            {
                return;
            }

            character->setHealth(character->getHealth() + 1.0f);
        }

        void onTakeDamageButtonClick(pugi::xml_node& outNode)
        {
            Character* character = State::getController()->getPawn<Character>();

            if (character->isDead())
            {
                return;
            }

            character->setHealth(character->getHealth() - 1.0f);
        }

        void onHealthBarTick(pugi::xml_node& outNode)
        {
            if (outNode.attribute("percentage").empty())
            {
                outNode.append_attribute("percentage");
            }

            outNode.attribute("percentage").set_value(
                State::getController()->getPawn<Character>()->getHealth()
            );
        }
    }
}