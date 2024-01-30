#include "Base.hpp"

#include "UI/Maps.hpp"

namespace UI
{
    View m_activeView = {};

    std::string getTag(const pugi::xml_node& inNode)
    {
        return inNode.name();
    }

    std::string getID(const pugi::xml_node& inNode)
    {
        return inNode.attribute(ID_ATTRIBUTE_NAME.c_str()).as_string();
    }

    std::string getTitle(const pugi::xml_node& inNode)
    {
        return inNode.attribute(TITLE_ATTRIBUTE_NAME.c_str()).as_string();
    }

    View getActiveView()
    {
        return m_activeView;
    }

    void setActiveView(const View& inView)
    {
        m_activeView = inView;
    }

    void compileChildren(const pugi::xml_node& inNode)
    {
        for (pugi::xml_node& child : inNode.children())
        {
            compileChild(child);
        }
    }

    void compileChildrenRecursive(const pugi::xml_node& inNode)
    {
        for (pugi::xml_node& child : inNode.children())
        {
            compileChildRecursive(child);
        }
    }

    void compileChild(const pugi::xml_node& inNode)
    {
        if (inNode.name() == nullptr)
        {
            return;
        }

        std::string tagName = std::string(inNode.name());

        if (Components.find(tagName) == Components.end())
        {
            return;
        }

        Components.at(tagName)(inNode);
    }

    void compileChildRecursive(const pugi::xml_node& inNode)
    {
        compileChild(inNode);

        if (getTag(inNode).compare(ListComponent::TAG_ID) == 0)
        {
            return;
        }

        for (pugi::xml_node& child : inNode.children())
        {
            compileChildRecursive(child);
        }
    }
}