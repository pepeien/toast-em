#pragma once

#include <functional>
#include <unordered_map>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl2.h>
#include <imgui/backends/imgui_impl_vulkan.h>

#include <pugixml.hpp>

namespace UI
{
    typedef std::unordered_map<std::string, void (*)(const pugi::xml_node& inNode)> ComponentCallbackMap;
    typedef std::unordered_map<std::string, ComponentCallbackMap> ViewCallbackMap;

    const std::string ID_ATTRIBUTE_NAME = "id";

    struct View
    {
        ComponentCallbackMap callbacks;
    };

    std::string getID(const pugi::xml_node& inNode);

    View getActiveView();
    void setActiveView(const View& inView);
}