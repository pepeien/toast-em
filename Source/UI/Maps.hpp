#pragma once

#include "UI/Base.hpp"

#include "Components/Button.hpp"
#include "Components/List.hpp"
#include "Components/Text.hpp"

#include "Views/Gameplay.hpp"

namespace UI
{
    const ComponentCallbackMap Components = {
        { ButtonComponent::TAG_ID, &ButtonComponent::compile },
        { ListComponent::TAG_ID, &ListComponent::compile },
        { TextComponent::TAG_ID, &TextComponent::compile }
    };

    const ViewCallbackMap Views = {
        { GameplayView::VIEW_ID, GameplayView::Callbacks }
    };
}