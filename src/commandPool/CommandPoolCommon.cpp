#include "commandPool/CommandPoolCommon.hpp"

namespace bud::vk {

CommandPoolCommon::CommandPoolCommon(
    DeviceCommon& deviceCommon,
    const VkCommandPoolCreateInfo& commandPoolCreateInfo,
    const Allocator& allocator)
    : Object<VkCommandPool_T>(allocator)
    , m_deviceCommon(deviceCommon)
    , m_flags(commandPoolCreateInfo.flags)
    , m_queueFamilyIndex(commandPoolCreateInfo.queueFamilyIndex) {}

}
