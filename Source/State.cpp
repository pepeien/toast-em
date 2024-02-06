#include "State.hpp"

namespace State
{
    Chicane::Controller* m_controller;
    Chicane::Camera* m_camera;
    Chicane::Stats m_stats;
    Chicane::Vec2 m_resolution;

    void setCamera(Chicane::Camera* inCamera)
    {
        m_camera = inCamera;
    }

    Chicane::Camera* getCamera()
    {
        return m_camera;
    }

    void setController(Chicane::Controller* inController)
    {
        m_controller = inController;
    }

    Chicane::Controller* getController()
    {
        return m_controller;
    }

    void setStats(const Chicane::Stats& inStats)
    {
        m_stats = inStats;
    }

    Chicane::Stats getStats()
    {
        return m_stats;
    }

    void setResolution(const Chicane::Vec2& inResolution)
    {
        m_resolution = inResolution;
    }

    Chicane::Vec2 getResolution()
    {
        return m_resolution;
    }
}