#pragma once

#include <vulkan/vulkan.h>
#include "queue/QueueCommon.hpp"

namespace bud::vk::intelCpu {

class Queue : public QueueCommon {
public:
    Queue(
        DeviceCommon& deviceCommon,
        VkDeviceQueueCreateFlags deviceQueueCreateFlags,
        uint32_t familyIndex,
        float priority,
        const Allocator& allocator);
};

}
