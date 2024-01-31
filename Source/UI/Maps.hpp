#pragma once

#include "UI/Base.hpp"

#include "Components/Box.hpp"
#include "Components/Button.hpp"
#include "Components/List.hpp"
#include "Components/ProgressBar.hpp"
#include "Components/Text.hpp"

#include "Views/Gameplay.hpp"

namespace UI
{
    const ComponentCallbackMap Components = {
        { BoxComponent::TAG_ID, &BoxComponent::compile },
        { ButtonComponent::TAG_ID, &ButtonComponent::compile },
        { ListComponent::TAG_ID, &ListComponent::compile },
        { ProgressBarComponent::TAG_ID, &ProgressBarComponent::compile },
        { TextComponent::TAG_ID, &TextComponent::compile }
    };

    const ViewCallbackMap Views = {
        { GameplayView::VIEW_ID, GameplayView::Callbacks }
    };
}