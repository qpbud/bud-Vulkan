#include "queue/QueueCommon.hpp"

namespace bud::vk {

QueueCommon::QueueCommon(
    DeviceCommon& deviceCommon,
    VkDeviceQueueCreateFlags deviceQueueCreateFlags,
    uint32_t familyIndex,
    float priority,
    const Allocator& allocator)
    : Object<VkQueue_T>(allocator)
    , m_deviceCommon(deviceCommon)
    , m_deviceQueueCreateFlags(deviceQueueCreateFlags)
    , m_familyIndex(familyIndex)
    , m_priority(priority) {}

VkDeviceQueueCreateFlags QueueCommon::flags() const {
    return m_deviceQueueCreateFlags;
}

uint32_t QueueCommon::familyIndex() const {
    return m_familyIndex;
}

float QueueCommon::priotiry() const {
    return m_priority;
}

}
