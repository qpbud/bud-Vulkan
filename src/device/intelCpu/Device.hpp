#pragma once

#include <vulkan/vulkan.h>
#include "device/DeviceCommon.hpp"
#include "commandPool/CommandPoolCommon.hpp"
#include "commandBuffer/CommandBufferCommon.hpp"

namespace bud::vk::intelCpu {

class Device : public DeviceCommon {
public:
    Device(PhysicalDevice& physicalDevice, const VkDeviceCreateInfo& deviceCreateInfo, const Allocator& allocator);

    CommandPoolCommon& createCommandPool(
        const VkCommandPoolCreateInfo& commandPoolCreateInfo,
        const Allocator& allocator) override;
};

}
