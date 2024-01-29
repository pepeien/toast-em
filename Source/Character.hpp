#pragma once

#include "Runtime/Core.hpp"
#include "Runtime/Game.hpp"

class Character : public Chicane::Pawn
{
public:
    void getPossesedBy(Chicane::Controller* inController) override;

private:
    void onMoveFrontBack(bool isMovingForwards);
    void onMoveSideways(bool isMovingRight);
    void onRotateYaw(bool isMovingRight);
};