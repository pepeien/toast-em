#pragma once

#include "UI/Base.hpp"

#include "UI/Components/Box.hpp"
#include "UI/Components/Button.hpp"
#include "UI/Components/List.hpp"
#include "UI/Components/ProgressBar.hpp"
#include "UI/Components/Text.hpp"

#include "UI/Views/Gameplay.hpp"

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