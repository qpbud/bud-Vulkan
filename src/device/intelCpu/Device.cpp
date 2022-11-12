#include "device/intelCpu/Device.hpp"
#include "queue/intelCpu/Queue.hpp"
#include "commandPool/intelCpu/CommandPool.hpp"

namespace bud::vk::intelCpu {

void Device::Entry::destroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) {
    if (device) {
        auto& deviceInternal = static_cast<Device&>(*device);
        Allocator alloc = deviceInternal.getAllocator();
        alloc.destruct<Device>(deviceInternal);
    }
}

void Device::Entry::getDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) {
    VkDeviceQueueInfo2 deviceQueueInfo;
    deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
    deviceQueueInfo.pNext = nullptr;
    deviceQueueInfo.flags = 0;
    deviceQueueInfo.queueFamilyIndex = queueFamilyIndex;
    deviceQueueInfo.queueIndex = queueIndex;
    auto& deviceInternal = static_cast<Device&>(*device);
    *pQueue = &deviceInternal.getQueue(deviceQueueInfo);
}

void Device::Entry::getDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) {
    auto& deviceInternal = static_cast<Device&>(*device);
    *pQueue = &deviceInternal.getQueue(*pQueueInfo);
}

Device::Device(
    PhysicalDevice& physicalDevice,
    const VkDeviceCreateInfo& deviceCreateInfo,
    const Allocator& allocator)
    : DeviceCommon(physicalDevice, deviceCreateInfo, allocator) {
#define ADD_FUNCTION(name, real) \
    m_dispatchableCommands.insert(std::make_pair(#name, reinterpret_cast<PFN_vkVoidFunction>(real)))

    ADD_FUNCTION(vkGetDeviceProcAddr, vkGetDeviceProcAddr);
    ADD_FUNCTION(vkDestroyDevice, &Device::Entry::destroyDevice);
    ADD_FUNCTION(vkGetDeviceQueue, &Device::Entry::getDeviceQueue);
    ADD_FUNCTION(vkGetDeviceQueue2, &Device::Entry::getDeviceQueue2);
    ADD_FUNCTION(vkCreateCommandPool, &CommandPool::Entry::createCommandPool);
    ADD_FUNCTION(vkTrimCommandPool, &CommandPool::Entry::trimCommandPool);
    ADD_FUNCTION(vkResetCommandPool, &CommandPool::Entry::resetCommandPool);
    ADD_FUNCTION(vkDestroyCommandPool, &CommandPool::Entry::destroyCommandPool);

#undef ADD_FUNCTION

    for (uint32_t i = 0; i < deviceCreateInfo.queueCreateInfoCount; i++) {
        const VkDeviceQueueCreateInfo& deviceQueueCreateInfo = deviceCreateInfo.pQueueCreateInfos[i];
        for (uint32_t j = 0; j < deviceQueueCreateInfo.queueCount; j++) {
            VkDeviceQueueCreateFlags deviceQueueCreateFlags = deviceQueueCreateInfo.flags;
            uint32_t queueFamilyIndex = deviceQueueCreateInfo.queueFamilyIndex;
            float queuePriority = deviceQueueCreateInfo.pQueuePriorities[j];
            if (m_queues.find(queueFamilyIndex) == m_queues.end()) {
                m_queues.insert(std::make_pair(queueFamilyIndex, &m_allocator));
            }
            m_queues.at(queueFamilyIndex).emplace_back(
                &m_allocator.construct<Queue>(*this, deviceQueueCreateFlags, queueFamilyIndex, queuePriority, m_allocator),
                m_allocator);
        }
    }
}

}
