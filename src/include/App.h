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
    bool _checkExtensions(std::vector<VkExtensionProperties> *extensions, const char **glfwExtensions, uint32_t glfwExtensionCount);

private:
    GLFWwindow *_window;
    uint32_t _width = 800;
    uint32_t _height = 600;

    VkInstance _instance;
};