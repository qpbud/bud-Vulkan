#include <vulkan/vulkan.h>
#include "physicalDevice/PhysicalDevice.hpp"
#include "device/DeviceCommon.hpp"

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(
    VkDevice device,
    const char* pName) {
    auto& deviceCommonInternal = static_cast<bud::vk::DeviceCommon&>(*device);
    return deviceCommonInternal.getProcAddr(pName);
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
