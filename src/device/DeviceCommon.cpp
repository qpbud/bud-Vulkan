#include <exception>
#include "device/DeviceCommon.hpp"
#include "device/intelCpu/Device.hpp"
#include "queue/QueueCommon.hpp"

namespace bud::vk {

PFN_vkVoidFunction DeviceCommon::Entry::getDeviceProcAddr(VkDevice device, const char* pName) {
    if (std::string_view(pName) == "vkGetDeviceProcAddr") {
        return reinterpret_cast<PFN_vkVoidFunction>(&DeviceCommon::Entry::getDeviceProcAddr);
    }
    auto& deviceCommonInternal = static_cast<DeviceCommon&>(*device);
    return deviceCommonInternal.getProcAddr(pName);
}

VkResult DeviceCommon::Entry::createDevice(
    VkPhysicalDevice physicalDevice,
    const VkDeviceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDevice* pDevice) {
    auto& physicalDeviceInternal = static_cast<PhysicalDevice&>(*physicalDevice);
    Allocator allocator{pAllocator, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE};
    if (physicalDeviceInternal.isOfType<PhysicalDevice::IntelCpu>()) {
        *pDevice = &allocator.construct<intelCpu::Device>(physicalDeviceInternal, *pCreateInfo, allocator);
        return VK_SUCCESS;
    }
    return VK_ERROR_INITIALIZATION_FAILED;
}

void DeviceCommon::Entry::destroyDevice(
    VkDevice device,
    const VkAllocationCallbacks* pAllocator) {
    if (device != VK_NULL_HANDLE) {
        auto& deviceCommonInternal = static_cast<DeviceCommon&>(*device);
        Allocator alloc = deviceCommonInternal.getAllocator();
        alloc.destruct(deviceCommonInternal);
    }
}

void DeviceCommon::Entry::getDeviceQueue2(
    VkDevice device,
    const VkDeviceQueueInfo2* pQueueInfo,
    VkQueue* pQueue) {
    auto& deviceCommonInternal = static_cast<DeviceCommon&>(*device);
    *pQueue = &deviceCommonInternal.getQueue(*pQueueInfo);
}

void DeviceCommon::Entry::getDeviceQueue(
    VkDevice device,
    uint32_t queueFamilyIndex,
    uint32_t queueIndex,
    VkQueue* pQueue) {
    VkDeviceQueueInfo2 deviceQueueInfo;
    deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
    deviceQueueInfo.pNext = nullptr;
    deviceQueueInfo.flags = 0;
    deviceQueueInfo.queueFamilyIndex = queueFamilyIndex;
    deviceQueueInfo.queueIndex = queueIndex;
    auto& deviceCommonInternal = static_cast<DeviceCommon&>(*device);
    *pQueue = &deviceCommonInternal.getQueue(deviceQueueInfo);
}

DeviceCommon::DeviceCommon(
    PhysicalDevice& physicalDevice,
    const VkDeviceCreateInfo& deviceCreateInfo,
    const Allocator& allocator)
    : Object<VkDevice_T>(allocator)
    , m_physicalDevice(physicalDevice)
    , m_dispatchableCommands()
    , m_queues() {}

PFN_vkVoidFunction DeviceCommon::getProcAddr(std::string_view name) {
    return m_dispatchableCommands.at(name);
}

QueueCommon& DeviceCommon::getQueue(const VkDeviceQueueInfo2& deviceQueueInfo) {
    auto& familyQueues = m_queues.at(deviceQueueInfo.queueFamilyIndex);
    uint32_t i = 0;
    for (auto& queue : familyQueues) {
        if (queue->flags() != deviceQueueInfo.flags) {
            break;
        }
        if (i == deviceQueueInfo.queueIndex) {
            return *queue;
        }
        i++;
    }
    std::terminate();
}

}
