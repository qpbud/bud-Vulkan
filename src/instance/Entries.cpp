#include <string_view>
#include <vulkan/vulkan.h>
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
            return reinterpret_cast<PFN_vkVoidFunction>(vkCreateInstance);
        } else if (std::string_view(pName) == "vkGetInstanceProcAddr") {
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetInstanceProcAddr);
        }
    } else {
        if (std::string_view(pName) == "vkGetInstanceProcAddr") {
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetInstanceProcAddr);
        } else if (std::string_view(pName) == "vkGetDeviceProcAddr") {
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetDeviceProcAddr);
        } else if (std::string_view(pName) == "vkDestroyInstance") {
            return reinterpret_cast<PFN_vkVoidFunction>(vkDestroyInstance);
        } else if (std::string_view(pName) == "vkEnumeratePhysicalDevices") {
            return reinterpret_cast<PFN_vkVoidFunction>(vkEnumeratePhysicalDevices);
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
    *pInstance = &bud::vk::Instance::create(*pCreateInfo, pAllocator);
    return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyInstance(
    VkInstance instance,
    const VkAllocationCallbacks* pAllocator) {
    if (instance != VK_NULL_HANDLE) {
        auto& instanceInternal = static_cast<bud::vk::Instance&>(*instance);
        bud::vk::Instance::destroy(instanceInternal);
    }
}
