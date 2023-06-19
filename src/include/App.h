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
    bool _checkExtensions(std::vector<VkExtensionProperties> *extensions, const char **extension_names, uint32_t extensionCount);
    bool _checkValidationLayerSupport();

private:
    GLFWwindow *_window;
    uint32_t _width = 800;
    uint32_t _height = 600;

    VkInstance _instance;

    std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    #ifdef NDEBUG
        const bool _enableValidationLayers = false;
    #else
        const bool _enableValidationLayers = true;
    #endif
};