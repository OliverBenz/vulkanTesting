#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <optional>
#include <memory>

#include "device.hpp"
#include "window.hpp"
#include "swapchain.hpp"
#include "vertex.hpp"
#include "model.hpp"
#include "buffer.hpp"
#include "pipeline.hpp"

class Application {
public:
    Application();
    ~Application();

    void run();

private:
    void createDescriptorSetLayout();
    void createGraphicsPipeline();

    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();

    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void drawFrame();
    void updateUniformBuffer(uint32_t currentImage, glm::vec3 offset);

	// To be moved to renderer
	void recreateSwapchain();

private:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    Window m_window{WIDTH, HEIGHT, "Vulkan"};
    Device m_device{m_window};
	std::unique_ptr<Swapchain> m_swapchain{std::make_unique<Swapchain>(m_window, m_device)};

	const std::string m_pathVertexShader = "../resources/shaders/vert.spv";
	const std::string m_pathFragmentShader = "../resources/shaders/frag.spv";

	std::unique_ptr<Pipeline> m_graphicsPipeline;

    VkDescriptorPool m_descriptorPool;
    std::vector<VkDescriptorSet> m_descriptorSets;
    VkDescriptorSetLayout m_descriptorSetLayout;

    // Buffers
    std::vector<VkCommandBuffer> m_commandBuffers;
    
    std::vector<VkBuffer> m_uniformBuffers;
    std::vector<VkDeviceMemory> m_uniformBuffersMemory;

	// Model
	Model m_modelViking{m_device, "../resources/models/viking_room.obj","../resources/textures/viking_room.png"};
};
