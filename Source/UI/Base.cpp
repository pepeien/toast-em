#include "Base.hpp"

namespace UI
{
    View m_activeView = {};

    std::string getID(const pugi::xml_node& inNode)
    {
        return inNode.attribute(ID_ATTRIBUTE_NAME.c_str()).as_string();
    }

    View getActiveView()
    {
        return m_activeView;
    }

    void setActiveView(const View& inView)
    {
        m_activeView = inView;
    }
}