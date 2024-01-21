#pragma once

#include "Core.hpp"

class Character : public Engine::Pawn
{
public:
    void getPossesedBy(Engine::Controller* inController) override;

private:
    void onMoveFrontBack(bool isMovingForwards);
    void onMoveSideways(bool isMovingRight);
    void onRotateYaw(bool isMovingRight);
};