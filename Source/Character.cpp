#include "Character.hpp"

constexpr float MOVE_STEP = 0.5f;

Character::Character()
    : Chicane::Pawn(),
    m_health(100.0f)
{}

void Character::getPossesedBy(Chicane::Controller* inController)
{
    Chicane::Pawn::getPossesedBy(inController);

    // Movement
    m_controller->bindEvent(
        SDL_SCANCODE_W,
        std::bind(&Character::onMoveFrontBack, this, true)
    );
    m_controller->bindEvent(
        SDL_SCANCODE_S,
        std::bind(&Character::onMoveFrontBack, this, false)
    );
    m_controller->bindEvent(
        SDL_SCANCODE_A,
        std::bind(&Character::onMoveSideways, this, true)
    );
    m_controller->bindEvent(
        SDL_SCANCODE_D,
        std::bind(&Character::onMoveSideways, this, false)
    );

    // Rotation
    m_controller->bindEvent(
        SDL_SCANCODE_Q,
        std::bind(&Character::onRotateYaw, this, true)
    );
    m_controller->bindEvent(
        SDL_SCANCODE_E,
        std::bind(&Character::onRotateYaw, this, false)
    );
}

bool Character::isDead()
{
    return m_health <= 0.0f;
}

bool Character::isFullHealth()
{
    return m_health >= 100.0f;
}

float Character::getHealth()
{
    return m_health;
}

void Character::setHealth(float inHealth)
{
    m_health = inHealth;
}

void Character::onMoveFrontBack(bool isMovingForwards)
{
    glm::vec3 newTranslation = glm::vec3(0.0f);
    newTranslation.x = (isMovingForwards ? 1 : -1) * MOVE_STEP;

    setAbsoluteTranslation(newTranslation);
}

void Character::onMoveSideways(bool isMovingLeft)
{
    glm::vec3 newTranslation = glm::vec3(0.0f);
    newTranslation.y = (isMovingLeft ? 1 : -1) * MOVE_STEP;

    setAbsoluteTranslation(newTranslation);
}
void Character::onRotateYaw(bool isRotatingLeft)
{
    glm::vec3 newTranslation = glm::vec3(0.0f);
    newTranslation.y = (isRotatingLeft ? -1 : 1) * MOVE_STEP;

    setRelativeRotation(newTranslation);
}