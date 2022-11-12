#include <vulkan/vulkan.h>
#include "instance/Instance.hpp"
#include "physicalDevice/PhysicalDevice.hpp"
#include "device/DeviceCommon.hpp"

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

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(
    VkDevice device,
    const char* pName) {
    auto& deviceCommonInternal = static_cast<bud::vk::DeviceCommon&>(*device);
    return deviceCommonInternal.getProcAddr(pName);
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

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties* pProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    *pProperties = physicalDeviceInternal.getProperties().properties;
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties2(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    *pProperties = physicalDeviceInternal.getProperties();
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties* pQueueFamilyProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    uint32_t queueFamilyCount = physicalDeviceInternal.getQueueFamilyCount();
    if (!pQueueFamilyProperties) {
        *pQueueFamilyPropertyCount = queueFamilyCount;
        return;
    }
    if (*pQueueFamilyPropertyCount > queueFamilyCount) {
        *pQueueFamilyPropertyCount = queueFamilyCount;
    }
    for (uint32_t i = 0; i < *pQueueFamilyPropertyCount; i++) {
        pQueueFamilyProperties[i] = physicalDeviceInternal.getQueueFamilyProperties(i).queueFamilyProperties;
    }
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties2(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    uint32_t queueFamilyCount = physicalDeviceInternal.getQueueFamilyCount();
    if (!pQueueFamilyProperties) {
        *pQueueFamilyPropertyCount = queueFamilyCount;
        return;
    }
    if (*pQueueFamilyPropertyCount > queueFamilyCount) {
        *pQueueFamilyPropertyCount = queueFamilyCount;
    }
    for (uint32_t i = 0; i < *pQueueFamilyPropertyCount; i++) {
        pQueueFamilyProperties[i] = physicalDeviceInternal.getQueueFamilyProperties(i);
    }
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

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDevice(
    VkPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDevice* pDevice) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    *pDevice = &bud::vk::DeviceCommon::create(physicalDeviceInternal, *pCreateInfo, pAllocator);
    return VK_SUCCESS;
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDevice(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator) {
    auto& deviceCommonInternal = static_cast<bud::vk::DeviceCommon&>(*device);
    auto fp = reinterpret_cast<PFN_vkDestroyDevice>(deviceCommonInternal.getProcAddr("vkDestroyDevice"));
    fp(device, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL vkGetDeviceQueue(
    VkDevice device,
    uint32_t queueFamilyIndex,
    uint32_t queueIndex,
    VkQueue* pQueue) {
    auto& deviceCommonInternal = static_cast<bud::vk::DeviceCommon&>(*device);
    auto fp = reinterpret_cast<PFN_vkGetDeviceQueue>(deviceCommonInternal.getProcAddr("vkGetDeviceQueue"));
    fp(device, queueFamilyIndex, queueIndex, pQueue);
}

VKAPI_ATTR void VKAPI_CALL vkGetDeviceQueue2(
    VkDevice device,
    const VkDeviceQueueInfo2* pQueueInfo,
    VkQueue* pQueue) {
    auto& deviceCommonInternal = static_cast<bud::vk::DeviceCommon&>(*device);
    auto fp = reinterpret_cast<PFN_vkGetDeviceQueue2>(deviceCommonInternal.getProcAddr("vkGetDeviceQueue2"));
    fp(device, pQueueInfo, pQueue);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateCommandPool(
    VkDevice device,
    const VkCommandPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkCommandPool* pCommandPool) {
    auto& deviceCommonInternal = static_cast<bud::vk::DeviceCommon&>(*device);
    auto fp = reinterpret_cast<PFN_vkCreateCommandPool>(deviceCommonInternal.getProcAddr("vkCreateCommandPool"));
    return fp(device, pCreateInfo, pAllocator, pCommandPool);
}

VKAPI_ATTR void VKAPI_CALL vkTrimCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags) {
    auto& deviceCommonInternal = static_cast<bud::vk::DeviceCommon&>(*device);
    auto fp = reinterpret_cast<PFN_vkTrimCommandPool>(deviceCommonInternal.getProcAddr("vkTrimCommandPool"));
    return fp(device, commandPool, flags);
}

VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolResetFlags flags) {
    auto& deviceCommonInternal = static_cast<bud::vk::DeviceCommon&>(*device);
    auto fp = reinterpret_cast<PFN_vkResetCommandPool>(deviceCommonInternal.getProcAddr("vkResetCommandPool"));
    return fp(device, commandPool, flags);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    const VkAllocationCallbacks* pAllocator) {
    auto& deviceCommonInternal = static_cast<bud::vk::DeviceCommon&>(*device);
    auto fp = reinterpret_cast<PFN_vkDestroyCommandPool>(deviceCommonInternal.getProcAddr("vkDestroyCommandPool"));
    return fp(device, commandPool, pAllocator);
}
