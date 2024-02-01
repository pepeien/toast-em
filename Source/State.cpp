#include "State.hpp"

namespace State
{
    Chicane::Controller* m_controller;

    void setController(Chicane::Controller* inController)
    {
        m_controller = inController;
    }

    Chicane::Controller* getController()
    {
        return m_controller;
    }
}