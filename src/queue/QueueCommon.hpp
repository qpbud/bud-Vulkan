#pragma once

#include <vulkan/vulkan.h>
#include "common/Object.hpp"
#include "common/Allocator.hpp"
#include "device/DeviceCommon.hpp"

namespace bud::vk {

class QueueCommon : public Object<VkQueue_T> {
protected:
    DeviceCommon& m_deviceCommon;
    VkDeviceQueueCreateFlags m_deviceQueueCreateFlags;
    uint32_t m_familyIndex;
    float m_priority;
public:
    QueueCommon(
        DeviceCommon& deviceCommon,
        VkDeviceQueueCreateFlags deviceQueueCreateFlags,
        uint32_t familyIndex,
        float priority,
        const Allocator& allocator);
    virtual ~QueueCommon() = default;

    VkDeviceQueueCreateFlags flags() const;
    uint32_t familyIndex() const;
    float priotiry() const;
};

}
