#include <vulkan/vulkan.h>
#include "physicalDevice/PhysicalDevice.hpp"

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties* pProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    *pProperties = physicalDeviceInternal.getProperties2().properties;
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties2(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    *pProperties = physicalDeviceInternal.getProperties2();
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties* pQueueFamilyProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    uint32_t queueFamilyPropertiesCount = physicalDeviceInternal.getQueueFamilyProperties2Count();
    if (!pQueueFamilyProperties) {
        *pQueueFamilyPropertyCount = queueFamilyPropertiesCount;
        return;
    }
    if (*pQueueFamilyPropertyCount > queueFamilyPropertiesCount) {
        *pQueueFamilyPropertyCount = queueFamilyPropertiesCount;
    }
    for (uint32_t i = 0; i < *pQueueFamilyPropertyCount; i++) {
        pQueueFamilyProperties[i] = physicalDeviceInternal.getQueueFamilyProperties2(i).queueFamilyProperties;
    }
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties2(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    uint32_t queueFamilyProperties2Count = physicalDeviceInternal.getQueueFamilyProperties2Count();
    if (!pQueueFamilyProperties) {
        *pQueueFamilyPropertyCount = queueFamilyProperties2Count;
        return;
    }
    if (*pQueueFamilyPropertyCount > queueFamilyProperties2Count) {
        *pQueueFamilyPropertyCount = queueFamilyProperties2Count;
    }
    for (uint32_t i = 0; i < *pQueueFamilyPropertyCount; i++) {
        pQueueFamilyProperties[i] = physicalDeviceInternal.getQueueFamilyProperties2(i);
    }
}
