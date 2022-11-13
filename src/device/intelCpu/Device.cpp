#include "device/intelCpu/Device.hpp"
#include "queue/intelCpu/Queue.hpp"
#include "commandPool/intelCpu/CommandPool.hpp"

namespace bud::vk::intelCpu {

Device::Device(
    PhysicalDevice& physicalDevice,
    const VkDeviceCreateInfo& deviceCreateInfo,
    const Allocator& allocator)
    : DeviceCommon(physicalDevice, deviceCreateInfo, allocator) {
#define ADD_FUNCTION(name, real) \
    m_dispatchableCommands.insert(std::make_pair(#name, reinterpret_cast<PFN_vkVoidFunction>(real)))

    ADD_FUNCTION(vkDestroyDevice, &DeviceCommon::Entry::destroyDevice);
    ADD_FUNCTION(vkGetDeviceQueue, &DeviceCommon::Entry::getDeviceQueue);
    ADD_FUNCTION(vkGetDeviceQueue2, &DeviceCommon::Entry::getDeviceQueue2);
    ADD_FUNCTION(vkCreateCommandPool, &CommandPool::Entry::createCommandPool);
    ADD_FUNCTION(vkTrimCommandPool, &CommandPoolCommon::Entry::trimCommandPool);
    ADD_FUNCTION(vkResetCommandPool, &CommandPoolCommon::Entry::resetCommandPool);
    ADD_FUNCTION(vkDestroyCommandPool, &CommandPoolCommon::Entry::destroyCommandPool);

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
