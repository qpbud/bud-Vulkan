#pragma once

#include <string_view>
#include <unordered_map>
#include <memory>
#include <vulkan/vulkan.h>
#include "common/Object.hpp"
#include "common/Allocator.hpp"
#include "physicalDevice/PhysicalDevice.hpp"

namespace bud::vk {

class QueueCommon;

class DeviceCommon : public Object<VkDevice_T> {
protected:
    PhysicalDevice& m_physicalDevice;
    std::unordered_map<std::string_view, PFN_vkVoidFunction> m_dispatchableCommands;
    std::unordered_map<uint32_t, std::pmr::vector<std::unique_ptr<QueueCommon, Allocator::Deleter<QueueCommon>>>> m_queues;
public:
    static DeviceCommon& create(PhysicalDevice& physicalDevice, const VkDeviceCreateInfo& deviceCreateInfo, const VkAllocationCallbacks* allocatorCallbacks);

    DeviceCommon(PhysicalDevice& physicalDevice, const VkDeviceCreateInfo& deviceCreateInfo, const Allocator& allocator);

    PFN_vkVoidFunction getProcAddr(std::string_view name);
    QueueCommon& getQueue(const VkDeviceQueueInfo2& deviceQueueInfo);
};

}
