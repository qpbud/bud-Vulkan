#include <vulkan/vulkan.h>
#include "physicalDevice/PhysicalDevice.hpp"

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
