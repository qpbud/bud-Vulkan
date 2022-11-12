#include "queue/intelCpu/Queue.hpp"

namespace bud::vk::intelCpu {

Queue::Queue(
    Device& device,
    VkDeviceQueueCreateFlags deviceQueueCreateFlags,
    uint32_t familyIndex,
    float priority,
    const Allocator& allocator)
    : QueueCommon(device, deviceQueueCreateFlags, familyIndex, priority, allocator) {
}

}
