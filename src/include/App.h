#pragma once

#include <array>
#include <optional>
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    std::optional<uint32_t> transferFamily;

    bool isComplete();
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};

class App {
   public:
    void run();
    bool _framebufferResized = false;

   private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    void createInstance();
    void createSurface();
    void setupDebugMessenger();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    void createFrameBuffers();
    void createCommandPool();
    void createVertexBuffer();
    void createIndexBuffer();
    void createCommandBuffer();
    void createSyncObjects();

    void recreateSwapChain();
    void cleanupSwapChain();

    void _populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
    std::vector<const char *> _getRequiredExtensions();
    bool _checkExtensions(std::vector<const char *> extensions);
    bool _checkValidationLayerSupport();

    static VKAPI_ATTR VkBool32 VKAPI_CALL _debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
        void *pUserData);

    bool _isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices _findQueueFamilies(VkPhysicalDevice device);
    bool _checkDeviceExtensionSupport(VkPhysicalDevice device);

    SwapChainSupportDetails _querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR _chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    VkPresentModeKHR _chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D _chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    VkShaderModule _createShaderModule(const std::vector<char> &code);

    void _recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void _drawFrame();

    uint32_t _findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void _createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
    void _copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

   private:
    GLFWwindow *_window;
    uint32_t _width = 800;
    uint32_t _height = 600;

    VkInstance _instance;
    VkDebugUtilsMessengerEXT _debugMessenger;
    VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
    VkDevice _device;
    VkQueue _graphicsQueue;
    VkQueue _presentQueue;

    VkSurfaceKHR _surface;
    VkSwapchainKHR _swapChain;
    std::vector<VkImage> _swapChainImages;
    VkFormat _swapChainImageFormat;
    VkExtent2D _swapChainExtent;
    std::vector<VkImageView> _swapChainImageViews;
    VkRenderPass _renderPass;
    VkPipelineLayout _pipelineLayout;
    VkPipeline _graphicsPipeline;
    std::vector<VkFramebuffer> _swapChainFramebuffers;
    VkCommandPool _commandPool;
    std::vector<VkCommandBuffer> _commandBuffers;

    std::vector<VkSemaphore> _imageAvailableSemaphores;
    std::vector<VkSemaphore> _renderFinishedSemaphores;
    std::vector<VkFence> _inFlightFences;

    size_t _currentFrame = 0;

    const std::vector<Vertex> _vertices = {
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}};

    const std::vector<uint16_t> _indices = {0, 1, 2, 2, 3, 0};

    VkBuffer _vertexBuffer;
    VkDeviceMemory _vertexBufferMemory;
    VkBuffer _indexBuffer;
    VkDeviceMemory _indexBufferMemory;

    std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"};
    std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};
#ifdef NDEBUG
    const bool _enableValidationLayers = false;
#else
    const bool _enableValidationLayers = true;
#endif
};