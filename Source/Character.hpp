#pragma once

#include "Runtime/Core.hpp"
#include "Runtime/Game.hpp"

class Character : public Chicane::Pawn
{
public:
    Character();

public:
    void getPossesedBy(Chicane::Controller* inController) override;

    bool isDead();
    bool isFullHealth();
    float getHealth();
    void setHealth(float inHealth);

private:
    void onMoveFrontBack(bool isMovingForwards);
    void onMoveSideways(bool isMovingRight);
    void onRotateYaw(bool isMovingRight);

private:
    float m_health;
};