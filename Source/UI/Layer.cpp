#include "UI/Layer.hpp"

#include "UI/Components/View.hpp"

#include "State.hpp"

namespace UI
{
    Layer::Layer(Chicane::Window* inWindow)
        : Chicane::Layer("UI"),
        m_window(inWindow),
        m_renderer(inWindow->getRenderer())
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplSDL2_InitForVulkan(m_window->instance);
    }

    Layer::~Layer()
    {
        m_renderer->m_logicalDevice.waitIdle();

        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        m_renderer->m_logicalDevice.destroyRenderPass(m_renderPass);
        m_renderer->m_logicalDevice.destroyDescriptorPool(m_descriptorPool);
    }

    void Layer::build()
    {
        initDescriptorPool();
        initRenderpass();
        initFramebuffers();
        initImgui();

        State::setResolution(m_window->getResolution());
    }

    void Layer::rebuild()
    {
        initFramebuffers();

        State::setResolution(m_window->getResolution());
    }

    void Layer::onEvent(const SDL_Event& inEvent)
    {
        ImGui_ImplSDL2_ProcessEvent(&inEvent);
    }

    void Layer::setup(Chicane::Frame::Instance& outFrame)
    {
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window->instance);
        ImGui::NewFrame();

        parseUI("./Content/UI/HUD/Gameplay.xml");

    	ImGui::Render();
    }

    void Layer::render(
        Chicane::Frame::Instance& outFrame,
        const vk::CommandBuffer& inCommandBuffer,
        const vk::Extent2D& inSwapChainExtent
    )
    {
        // Renderpass
        std::vector<vk::ClearValue> clearValues;
        clearValues.push_back(vk::ClearColorValue(0.0f, 0.0f, 0.0f, 1.0f));

        vk::RenderPassBeginInfo renderPassBeginInfo = {};
        renderPassBeginInfo.renderPass          = m_renderPass;
        renderPassBeginInfo.framebuffer         = outFrame.getFramebuffer(m_name);
        renderPassBeginInfo.renderArea.offset.x = 0;
        renderPassBeginInfo.renderArea.offset.y = 0;
        renderPassBeginInfo.renderArea.extent   = inSwapChainExtent;
        renderPassBeginInfo.clearValueCount     = static_cast<uint32_t>(clearValues.size());
        renderPassBeginInfo.pClearValues        = clearValues.data();

        inCommandBuffer.beginRenderPass(
            &renderPassBeginInfo,
            vk::SubpassContents::eInline
        );

        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), inCommandBuffer);

        inCommandBuffer.endRenderPass();

        ImGui::EndFrame();

        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    	{
    		ImGui::UpdatePlatformWindows();
    		ImGui::RenderPlatformWindowsDefault();
    	}

        State::setStats(m_window->getStats());
    }

    void Layer::initDescriptorPool()
    {
        Chicane::Descriptor::PoolCreateInfo descriptorPoolCreateInfo;
        descriptorPoolCreateInfo.flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet;
        descriptorPoolCreateInfo.size  = static_cast<uint32_t>(m_renderer->m_swapChain.images.size());
        descriptorPoolCreateInfo.types.push_back(vk::DescriptorType::eSampler);
        descriptorPoolCreateInfo.types.push_back(vk::DescriptorType::eCombinedImageSampler);
        descriptorPoolCreateInfo.types.push_back(vk::DescriptorType::eSampledImage);
        descriptorPoolCreateInfo.types.push_back(vk::DescriptorType::eStorageImage);
        descriptorPoolCreateInfo.types.push_back(vk::DescriptorType::eUniformTexelBuffer);
        descriptorPoolCreateInfo.types.push_back(vk::DescriptorType::eStorageTexelBuffer);
        descriptorPoolCreateInfo.types.push_back(vk::DescriptorType::eUniformBuffer);
        descriptorPoolCreateInfo.types.push_back(vk::DescriptorType::eStorageBuffer);
        descriptorPoolCreateInfo.types.push_back(vk::DescriptorType::eUniformBufferDynamic);
        descriptorPoolCreateInfo.types.push_back(vk::DescriptorType::eStorageBufferDynamic);
        descriptorPoolCreateInfo.types.push_back(vk::DescriptorType::eInputAttachment);

        Chicane::Descriptor::initPool(
            m_descriptorPool,
            m_renderer->m_logicalDevice,
            descriptorPoolCreateInfo
        );
    }

    void Layer::initRenderpass()
    {
        vk::AttachmentDescription attachment = Chicane::GraphicsPipeline::createColorAttachment(
            m_renderer->m_swapChain.format,
            vk::AttachmentLoadOp::eLoad,
            vk::ImageLayout::ePresentSrcKHR
        );

        m_renderPass = Chicane::GraphicsPipeline::createRendepass(
            false,
            { attachment },
            m_renderer->m_logicalDevice
        );
    }

    void Layer::initFramebuffers()
    {
        Chicane::Frame::Buffer::CreateInfo framebufferCreateInfo = {};
        framebufferCreateInfo.id              = m_name;
        framebufferCreateInfo.logicalDevice   = m_renderer->m_logicalDevice;
        framebufferCreateInfo.renderPass      = m_renderPass;
        framebufferCreateInfo.swapChainExtent = m_renderer->m_swapChain.extent;

        for (Chicane::Frame::Instance& frame : m_renderer->m_swapChain.images)
        {
            framebufferCreateInfo.attachments.clear();
            framebufferCreateInfo.attachments.push_back(frame.imageView);

            Chicane::Frame::Buffer::init(frame, framebufferCreateInfo);
        }
    }

    void Layer::initImgui()
    {
        Chicane::Queue::FamilyIndices familyIndices;
        Chicane::Queue::findFamilyInidices(
            familyIndices,
            m_renderer->m_physicalDevice,
            m_renderer->m_surface
        );

        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance        = m_renderer->m_instance;
        init_info.PhysicalDevice  = m_renderer->m_physicalDevice;
        init_info.Device          = m_renderer->m_logicalDevice;
        init_info.QueueFamily     = familyIndices.graphicsFamily.value();
        init_info.Queue           = m_renderer->m_graphicsQueue;
        init_info.PipelineCache   = VK_NULL_HANDLE;
        init_info.DescriptorPool  = m_descriptorPool;
        init_info.Allocator       = nullptr;
        init_info.MinImageCount   = 3;
        init_info.ImageCount      = m_renderer->m_imageCount;

        ImGui_ImplVulkan_Init(&init_info, m_renderPass);
    }

    void Layer::parseUI(const std::string& inFilepath)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(inFilepath.c_str());

        if (!result)
        {
            throw std::runtime_error("Failed to read " + inFilepath);
        }

        if (doc.empty() || doc.children().empty())
        {
            throw std::runtime_error("UI document " + inFilepath + " does not have any components");
        }

        pugi::xml_node rootComponent = doc.first_child();

        ViewComponent::compile(
            rootComponent,
            m_window->getResolution(),
            m_window->getPosition()
        );
    }
}