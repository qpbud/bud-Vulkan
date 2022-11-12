#pragma once

#include <vulkan/vulkan.h>
#include "common/Object.hpp"
#include "common/Allocator.hpp"
#include "device/DeviceCommon.hpp"

namespace bud::vk {

class CommandPoolCommon : public Object<VkCommandPool_T> {
    DeviceCommon& m_deviceCommon;
    VkCommandPoolCreateFlags m_flags;
    uint32_t m_queueFamilyIndex;
public:
    CommandPoolCommon(
        DeviceCommon& deviceCommon,
        const VkCommandPoolCreateInfo& commandPoolCreateInfo,
        const Allocator& allocator);

    virtual void trim(VkCommandPoolTrimFlags flags) = 0;
    virtual void reset(VkCommandPoolResetFlags flags) = 0;
};

}
