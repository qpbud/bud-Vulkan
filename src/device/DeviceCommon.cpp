#include <exception>
#include "device/DeviceCommon.hpp"
#include "device/intelCpu/Device.hpp"
#include "queue/QueueCommon.hpp"

namespace bud::vk {

DeviceCommon& DeviceCommon::create(
    PhysicalDevice& physicalDevice,
    const VkDeviceCreateInfo& deviceCreateInfo,
    const VkAllocationCallbacks* allocatorCallbacks) {
    Allocator allocator{allocatorCallbacks, VK_SYSTEM_ALLOCATION_SCOPE_DEVICE};
    if (physicalDevice.isOfType<PhysicalDevice::IntelCpu>()) {
        return allocator.construct<intelCpu::Device>(physicalDevice, deviceCreateInfo, allocator);
    }
    std::terminate();
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
