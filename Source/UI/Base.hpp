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
    typedef std::unordered_map<std::string, void (*)(const pugi::xml_node& inNode)> ComponentCallbackMap;
    typedef std::unordered_map<std::string, ComponentCallbackMap> ViewCallbackMap;

    // Attributes
    const std::string ID_ATTRIBUTE_NAME    = "id";
    const std::string TITLE_ATTRIBUTE_NAME = "title";

    struct View
    {
        ComponentCallbackMap callbacks;
    };

    std::string getTag(const pugi::xml_node& inNode);

    // Attributes
    std::string getID(const pugi::xml_node& inNode);
    std::string getTitle(const pugi::xml_node& inNode);

    View getActiveView();
    void setActiveView(const View& inView);
    
    void compileChildren(const pugi::xml_node& inNode);
    void compileChildrenRecursive(const pugi::xml_node& inNode);

    void compileChild(const pugi::xml_node& inNode);
    void compileChildRecursive(const pugi::xml_node& inNode);
}