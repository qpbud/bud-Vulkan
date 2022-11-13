#include <vulkan/vulkan.h>
#include "instance/Instance.hpp"
#include "physicalDevice/PhysicalDevice.hpp"
#include "device/DeviceCommon.hpp"

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(
    VkInstance instance,
    const char* pName) {
    return bud::vk::Instance::Entry::getInstanceProcAddr(instance, pName);
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(
    VkDevice device,
    const char* pName) {
    return bud::vk::DeviceCommon::Entry::getDeviceProcAddr(device, pName);
}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceVersion(
    uint32_t* pApiVersion) {
    auto fp = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(
        bud::vk::Instance::Entry::getInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));
    return fp(pApiVersion);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateInstance(
    const VkInstanceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkInstance* pInstance) {
    auto fp = reinterpret_cast<PFN_vkCreateInstance>(
        bud::vk::Instance::Entry::getInstanceProcAddr(nullptr, "vkCreateInstance"));
    return fp(pCreateInfo, pAllocator, pInstance);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyInstance(
    VkInstance instance,
    const VkAllocationCallbacks* pAllocator) {
    auto fp = reinterpret_cast<PFN_vkDestroyInstance>(
        bud::vk::Instance::Entry::getInstanceProcAddr(instance, "vkDestroyInstance"));
    fp(instance, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDevices(
    VkInstance instance,
    uint32_t* pPhysicalDeviceCount,
    VkPhysicalDevice* pPhysicalDevices) {
    auto fp = reinterpret_cast<PFN_vkEnumeratePhysicalDevices>(
        bud::vk::Instance::Entry::getInstanceProcAddr(instance, "vkEnumeratePhysicalDevices"));
    return fp(instance, pPhysicalDeviceCount, pPhysicalDevices);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties* pProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    VkInstance instance = &physicalDeviceInternal.getInstance();
    auto fp = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties>(
        bud::vk::Instance::Entry::getInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties"));
    fp(physicalDevice, pProperties);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties2(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    VkInstance instance = &physicalDeviceInternal.getInstance();
    auto fp = reinterpret_cast<PFN_vkGetPhysicalDeviceProperties2>(
        bud::vk::Instance::Entry::getInstanceProcAddr(instance, "vkGetPhysicalDeviceProperties2"));
    fp(physicalDevice, pProperties);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties* pQueueFamilyProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    VkInstance instance = &physicalDeviceInternal.getInstance();
    auto fp = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties>(
        bud::vk::Instance::Entry::getInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties"));
    fp(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties2(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    VkInstance instance = &physicalDeviceInternal.getInstance();
    auto fp = reinterpret_cast<PFN_vkGetPhysicalDeviceQueueFamilyProperties2>(
        bud::vk::Instance::Entry::getInstanceProcAddr(instance, "vkGetPhysicalDeviceQueueFamilyProperties2"));
    fp(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDeviceGroups(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) {
    auto fp = reinterpret_cast<PFN_vkEnumeratePhysicalDeviceGroups>(
        bud::vk::Instance::Entry::getInstanceProcAddr(instance, "vkEnumeratePhysicalDeviceGroups"));
    return fp(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDevice(
    VkPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDevice* pDevice) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    VkInstance instance = &physicalDeviceInternal.getInstance();
    auto fp = reinterpret_cast<PFN_vkCreateDevice>(
        bud::vk::Instance::Entry::getInstanceProcAddr(instance, "vkCreateDevice"));
    return fp(physicalDevice, pCreateInfo, pAllocator, pDevice);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDevice(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator) {
    auto fp = reinterpret_cast<PFN_vkDestroyDevice>(
        bud::vk::DeviceCommon::Entry::getDeviceProcAddr(device, "vkDestroyDevice"));
    fp(device, pAllocator);
}

VKAPI_ATTR void VKAPI_CALL vkGetDeviceQueue(
    VkDevice device,
    uint32_t queueFamilyIndex,
    uint32_t queueIndex,
    VkQueue* pQueue) {
    auto fp = reinterpret_cast<PFN_vkGetDeviceQueue>(
        bud::vk::DeviceCommon::Entry::getDeviceProcAddr(device, "vkGetDeviceQueue"));
    fp(device, queueFamilyIndex, queueIndex, pQueue);
}

VKAPI_ATTR void VKAPI_CALL vkGetDeviceQueue2(
    VkDevice device,
    const VkDeviceQueueInfo2* pQueueInfo,
    VkQueue* pQueue) {
    auto fp = reinterpret_cast<PFN_vkGetDeviceQueue2>(
        bud::vk::DeviceCommon::Entry::getDeviceProcAddr(device, "vkGetDeviceQueue2"));
    fp(device, pQueueInfo, pQueue);
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateCommandPool(
    VkDevice device,
    const VkCommandPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkCommandPool* pCommandPool) {
    auto fp = reinterpret_cast<PFN_vkCreateCommandPool>(
        bud::vk::DeviceCommon::Entry::getDeviceProcAddr(device, "vkCreateCommandPool"));
    return fp(device, pCreateInfo, pAllocator, pCommandPool);
}

VKAPI_ATTR void VKAPI_CALL vkTrimCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolTrimFlags flags) {
    auto fp = reinterpret_cast<PFN_vkTrimCommandPool>(
        bud::vk::DeviceCommon::Entry::getDeviceProcAddr(device, "vkTrimCommandPool"));
    fp(device, commandPool, flags);
}

VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandPoolResetFlags flags) {
    auto fp = reinterpret_cast<PFN_vkResetCommandPool>(
        bud::vk::DeviceCommon::Entry::getDeviceProcAddr(device, "vkResetCommandPool"));
    return fp(device, commandPool, flags);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyCommandPool(
    VkDevice device,
    VkCommandPool commandPool,
    const VkAllocationCallbacks* pAllocator) {
    auto fp = reinterpret_cast<PFN_vkDestroyCommandPool>(
        bud::vk::DeviceCommon::Entry::getDeviceProcAddr(device, "vkDestroyCommandPool"));
    fp(device, commandPool, pAllocator);
}
