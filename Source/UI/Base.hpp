#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl2.h>
#include <imgui/backends/imgui_impl_vulkan.h>

#include <pugixml.hpp>

namespace UI
{
    typedef std::unordered_map<std::string, void (*)(pugi::xml_node& outNode)> ComponentCallbackMap;
    typedef std::unordered_map<std::string, ComponentCallbackMap> ViewCallbackMap;

    // Value attributes
    const std::string ID_ATTRIBUTE_NAME     = "id";
    const std::string TITLE_ATTRIBUTE_NAME  = "title";
    const std::string WIDTH_ATTRIBUTE_NAME  = "width";
    const std::string HEIGHT_ATTRIBUTE_NAME = "height";

    // Lifecycle attributes
    const std::string ON_TICK_ATTRIBUTE = "onTick";

    struct View
    {
        ComponentCallbackMap callbacks;
    };

    std::string getTag(const pugi::xml_node& outNode);
    pugi::xml_attribute getAttribute(
        const std::string& inName,
        const pugi::xml_node& outNode
    );

    View getActiveView();
    void setActiveView(const View& inView);
    
    void compileChildren(pugi::xml_node& outNode);
    void compileChild(pugi::xml_node& outNode);
}