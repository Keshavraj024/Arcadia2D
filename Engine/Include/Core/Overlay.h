#pragma once

#include "Managers/GuiManager.h"

enum class OverlaySelection { Resume, Restart, Menu, Quit };

class Overlay
{
public:
    Overlay(GuiManager &manager);
    ~Overlay();

    std::optional<OverlaySelection> FetchSelection();
    void SetVisible(bool visible);
    bool IsVisible() const;

private:
    std::optional<OverlaySelection> m_selection;
    tgui::Group::Ptr m_groupPtr;

private:
    void InitBackground();
    void InitButton();
};
