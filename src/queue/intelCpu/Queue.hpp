#pragma once

#include <vulkan/vulkan.h>
#include "device/intelCpu/Device.hpp"
#include "queue/QueueCommon.hpp"

namespace bud::vk::intelCpu {

class Queue : public QueueCommon {
public:
    Queue(
        Device& device,
        VkDeviceQueueCreateFlags deviceQueueCreateFlags,
        uint32_t familyIndex,
        float priority,
        const Allocator& allocator);
};

}
