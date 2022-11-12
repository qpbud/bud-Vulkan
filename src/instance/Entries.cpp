#include <vulkan/vulkan.h>
#include "instance/Instance.hpp"

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(
    VkInstance instance,
    const char* pName) {
    if (!instance) {
        if (std::string_view(pName) == "vkGetInstanceProcAddr") {
            return reinterpret_cast<PFN_vkVoidFunction>(vkGetInstanceProcAddr);
        }
        if (auto iter = bud::vk::Instance::s_globalCommands.find(pName); iter != bud::vk::Instance::s_globalCommands.end()) {
            return iter->second;
        }
    } else {
        if (auto iter = bud::vk::Instance::s_dispatchableCommands.find(pName); iter != bud::vk::Instance::s_dispatchableCommands.end()) {
            return iter->second;
        }
    }
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

VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDevices(
    VkInstance instance,
    uint32_t* pPhysicalDeviceCount,
    VkPhysicalDevice* pPhysicalDevices) {
    auto& instanceInternal = static_cast<bud::vk::Instance&>(*instance);
    uint32_t physicalDeviceCount = instanceInternal.getPhysicalDeviceCount();
    if (!pPhysicalDevices) {
        *pPhysicalDeviceCount = physicalDeviceCount;
        return VK_SUCCESS;
    }
    if (*pPhysicalDeviceCount > physicalDeviceCount) {
        *pPhysicalDeviceCount = physicalDeviceCount;
    }
    for (uint32_t i = 0; i < *pPhysicalDeviceCount; i++) {
        pPhysicalDevices[i] = &instanceInternal.getPhysicalDevice(i);
    }
    if (*pPhysicalDeviceCount < physicalDeviceCount) {
        return VK_INCOMPLETE;
    }
    return VK_SUCCESS;
}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDeviceGroups(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) {
    auto& instanceInternal = static_cast<bud::vk::Instance&>(*instance);
    uint32_t physicalDeviceGroupCount = instanceInternal.getPhysicalDeviceGroupCount();
    if (!pPhysicalDeviceGroupProperties) {
        *pPhysicalDeviceGroupCount = physicalDeviceGroupCount;
    }
    if (*pPhysicalDeviceGroupCount > physicalDeviceGroupCount) {
        *pPhysicalDeviceGroupCount = physicalDeviceGroupCount;
    }
    for (uint32_t i = 0; i < physicalDeviceGroupCount; i++) {
        pPhysicalDeviceGroupProperties[i] = instanceInternal.getPhysicalDeviceGroupProperties(i);
    }
    if (*pPhysicalDeviceGroupCount < physicalDeviceGroupCount) {
        return VK_INCOMPLETE;
    }
    return VK_SUCCESS;
}
