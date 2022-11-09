#include <string_view>
#include <vulkan/vulkan.h>
#include "common/Except.hpp"
#include "instance/Instance.hpp"

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(
    VkInstance instance,
    const char* pName) {
    if (!instance) {
        if (std::string_view(pName) == "vkEnumerateInstanceVersion") {
            return reinterpret_cast<PFN_vkVoidFunction>(vkEnumerateInstanceVersion);
        } else if (std::string_view(pName) == "vkEnumerateInstanceExtensionProperties") {
            // return reinterpret_cast<PFN_vkVoidFunction>(vkEnumerateInstanceExtensionProperties);
        } else if (std::string_view(pName) == "vkEnumerateInstanceLayerProperties") {
            // return reinterpret_cast<PFN_vkVoidFunction>(vkEnumerateInstanceLayerProperties);
        } else if (std::string_view(pName) == "vkCreateInstance") {
            // return reinterpret_cast<PFN_vkVoidFunction>(vkCreateInstance);
        } else if (std::string_view(pName) == "vkGetInstanceProcAddr") {
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetInstanceProcAddr);
        }
    } else {
        if (std::string_view(pName) == "vkGetInstanceProcAddr") {
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetInstanceProcAddr);
        } else if (std::string_view(pName) == "vkGetDeviceProcAddr") {
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetDeviceProcAddr);
        }
    }
    return nullptr;
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(
    VkDevice device,
    const char* pName) {
    return nullptr;
}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceVersion(
    uint32_t* pApiVersion) {
    *pApiVersion = bud::vk::Instance::s_version;
    return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateInstance(
    const VkInstanceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkInstance* pInstance) {
    try {
        *pInstance = &bud::vk::Instance::create(*pCreateInfo);
        return VK_SUCCESS;
    } catch (const std::exception& e) {
        if (auto except = dynamic_cast<const bud::vk::Except*>(&e); except) {
            return except->res();
        }
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
}
