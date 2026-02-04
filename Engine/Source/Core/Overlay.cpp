#include "Core/Overlay.h"

#include <magic_enum/magic_enum.hpp>
#include <utility>

Overlay::Overlay(GuiManager &manager)
{
    m_groupPtr = tgui::Group::create();
    m_groupPtr->setVisible(false);

    manager.AddWidget(m_groupPtr);

    InitBackground();
    InitButton();
}

Overlay::~Overlay() {}

std::optional<OverlaySelection> Overlay::FetchSelection()
{
    return std::exchange(m_selection, std::nullopt);
}

void Overlay::SetVisible(bool visible)
{
    m_groupPtr->setVisible(visible);
}

bool Overlay::IsVisible() const
{
    return m_groupPtr->isVisible();
}

void Overlay::InitBackground()
{
    auto background = tgui::Panel::create();
    background->getRenderer()->setBackgroundColor({0, 0, 0, 175});

    m_groupPtr->add(background);
}

void Overlay::InitButton()
{
    auto layout = tgui::VerticalLayout::create();
    layout->setSize("37%", "63%");
    layout->setPosition("31%", "18%");

    for (const auto &[selection, name] : magic_enum::enum_entries<OverlaySelection>()) {
        auto button = tgui::Button::create(name.data());
        button->setTextSize(30);
        button->onPress([this, selection] { this->m_selection = selection; });

        layout->add(button);
    }

    m_groupPtr->add(layout);
}
