#include "queue/intelCpu/Queue.hpp"

namespace bud::vk::intelCpu {

Queue::Queue(
    DeviceCommon& deviceCommon,
    VkDeviceQueueCreateFlags deviceQueueCreateFlags,
    uint32_t familyIndex,
    float priority,
    const Allocator& allocator)
    : QueueCommon(deviceCommon, deviceQueueCreateFlags, familyIndex, priority, allocator) {
}

}
