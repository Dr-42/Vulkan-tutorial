#include "App.h"

#include <stdexcept>
#include <iostream>
#include <cstring>

void App::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void App::initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = glfwCreateWindow(_width, _height, "Vulkan", nullptr, nullptr);
}

void App::mainLoop() {
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();
    }
}

void App::initVulkan() {
    createInstance();
}

void App::createInstance(){
    if(_enableValidationLayers && !_checkValidationLayerSupport()){
        throw std::runtime_error("Validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char ** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    if(_enableValidationLayers){
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    VkResult result = vkCreateInstance(&createInfo, nullptr, &_instance);
    if(result != VK_SUCCESS){
        //Log the error type
        std::cerr << "Error: " << result << std::endl;
        throw std::runtime_error("Failed to create instance!");
    }

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    if(!_checkExtensions(&extensions, glfwExtensions, glfwExtensionCount)){
        throw std::runtime_error("Required extensions not available!");
    } else {
        std::cout << "Required extensions available!" << std::endl;
    }
}

bool App::_checkExtensions(std::vector<VkExtensionProperties> *extensions, const char **extension_names, uint32_t extensionCount) {
    bool allExtensionsAvailable = true;
    for(uint32_t i = 0; i < extensionCount; i++){
        bool extensionAvailable = false;
        for(const auto& extension : *extensions){
            if(strcmp(extension_names[i], extension.extensionName) == 0){
                extensionAvailable = true;
                break;
            }
        }
        if(!extensionAvailable){
            allExtensionsAvailable = false;
            break;
        }
    }
    return allExtensionsAvailable;
}

bool App::_checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layerName : validationLayers)
    {
        bool layerFound = false;

        for (const auto &layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }

    std::cout << "Validation layers available!" << std::endl;
    return true;
}

void App::cleanup()
{
    vkDestroyInstance(_instance, nullptr);

    glfwDestroyWindow(_window);
    glfwTerminate();
}