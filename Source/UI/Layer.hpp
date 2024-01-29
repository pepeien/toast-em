#pragma once

#include "UI/Base.hpp"

#include "Components/View.hpp"

#include "Runtime/Core.hpp"
#include "Runtime/Renderer/Frame.hpp"

namespace UI
{
    class Layer : public Chicane::Layer
    {
    public:
        Layer(Chicane::Window* inWindow);
        ~Layer();
    
    public:
        void init() override;
        void onEvent(const SDL_Event& inEvent) override;
        void setup(Chicane::Frame::Instance& outFrame) override;
        void render(
            Chicane::Frame::Instance& outFrame,
            const vk::CommandBuffer& inCommandBuffer,
            const vk::Extent2D& inSwapChainExtent
        ) override;
        void destroy() override;
    
    private:
        void initDescriptorPool();
        void initRenderpass();
        void initFramebuffers();
        void initImgui();
        void parseUI(const std::string& inFilepath);
    
    private:
        Chicane::Window* m_window;
        Chicane::Renderer* m_renderer;
    
        vk::RenderPass m_renderPass;
        vk::DescriptorPool m_descriptorPool;
    };
}