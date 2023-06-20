#pragma once

#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class App{
public:
    void run();

private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    void createInstance();
    void setupDebugMessenger();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    std::vector<const char*> _getRequiredExtensions();
    bool _checkExtensions(std::vector<const char*> extensions);
    bool _checkValidationLayerSupport();
    static VKAPI_ATTR VkBool32 VKAPI_CALL _debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);

private:
    GLFWwindow *_window;
    uint32_t _width = 800;
    uint32_t _height = 600;

    VkInstance _instance;
    VkDebugUtilsMessengerEXT _debugMessenger;

    std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    #ifdef NDEBUG
        const bool _enableValidationLayers = false;
    #else
        const bool _enableValidationLayers = true;
    #endif
};