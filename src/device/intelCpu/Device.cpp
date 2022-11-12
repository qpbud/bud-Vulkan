#include "device/intelCpu/Device.hpp"
#include "queue/intelCpu/Queue.hpp"

namespace bud::vk::intelCpu {

void Device::destroy(VkDevice device, const VkAllocationCallbacks* allocator) {
    if (device) {
        auto& deviceInternal = static_cast<Device&>(*device);
        Allocator alloc = deviceInternal.getAllocator();
        alloc.destruct<Device>(deviceInternal);
    }
}

void Device::getQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* queue) {
    VkDeviceQueueInfo2 deviceQueueInfo;
    deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_INFO_2;
    deviceQueueInfo.pNext = nullptr;
    deviceQueueInfo.flags = 0;
    deviceQueueInfo.queueFamilyIndex = queueFamilyIndex;
    deviceQueueInfo.queueIndex = queueIndex;
    auto& deviceInternal = static_cast<Device&>(*device);
    *queue = &deviceInternal.DeviceCommon::getQueue(deviceQueueInfo);
}

void Device::getQueue2(VkDevice device, const VkDeviceQueueInfo2* queueInfo, VkQueue* queue) {
    auto& deviceInternal = static_cast<Device&>(*device);
    *queue = &deviceInternal.DeviceCommon::getQueue(*queueInfo);
}

Device::Device(
    PhysicalDevice& physicalDevice,
    const VkDeviceCreateInfo& deviceCreateInfo,
    const Allocator& allocator)
    : DeviceCommon(physicalDevice, deviceCreateInfo, allocator) {
#define ADD_FUNCTION(name, real) \
    m_dispatchableCommands.insert(std::make_pair(#name, reinterpret_cast<PFN_vkVoidFunction>(real)))

    ADD_FUNCTION(vkGetDeviceProcAddr, vkGetDeviceProcAddr);
    ADD_FUNCTION(vkDestroyDevice, &Device::destroy);
    ADD_FUNCTION(vkGetDeviceQueue, &Device::getQueue);
    ADD_FUNCTION(vkGetDeviceQueue2, &Device::getQueue2);

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
