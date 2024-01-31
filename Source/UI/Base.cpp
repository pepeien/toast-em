#include "Base.hpp"

#include "UI/Maps.hpp"

namespace UI
{
    View m_activeView = {};

    std::string getTag(const pugi::xml_node& inNode)
    {
        return inNode.name();
    }

    pugi::xml_attribute getAttribute(
        const std::string& inName,
        const pugi::xml_node& inNode
    )
    {
        return inNode.attribute(inName.c_str());
    }

    View getActiveView()
    {
        return m_activeView;
    }

    void setActiveView(const View& inView)
    {
        m_activeView = inView;
    }

    void compileChildren(pugi::xml_node& outNode)
    {
        for (pugi::xml_node& child : outNode.children())
        {
            compileChild(child);
        }
    }

    void compileChild(pugi::xml_node& outNode)
    {
        if (outNode.name() == nullptr)
        {
            return;
        }

        std::string tagName = std::string(outNode.name());

        if (Components.find(tagName) == Components.end())
        {
            return;
        }

        std::string onTickSignature = getAttribute(ON_TICK_ATTRIBUTE, outNode).as_string();

        if (
            !onTickSignature.empty() &&
            m_activeView.callbacks.find(onTickSignature) != m_activeView.callbacks.end()
        )
        {
            m_activeView.callbacks.at(onTickSignature)(outNode);
        }

        Components.at(tagName)(outNode);
    }
}