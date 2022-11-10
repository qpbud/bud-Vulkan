#include <vulkan/vulkan.h>
#include "instance/Instance.hpp"

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
