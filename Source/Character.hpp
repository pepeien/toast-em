#pragma once

#include "Core.hpp"
#include "Game.hpp"

class Character : public Chicane::Pawn
{
public:
    void getPossesedBy(Chicane::Controller* inController) override;

private:
    void onMoveFrontBack(bool isMovingForwards);
    void onMoveSideways(bool isMovingRight);
    void onRotateYaw(bool isMovingRight);
};