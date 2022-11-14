#pragma once

#include <vulkan/vulkan.h>
#include "common/Object.hpp"
#include "common/Allocator.hpp"
#include "device/DeviceCommon.hpp"

namespace bud::vk {

class CommandBufferCommon;

class CommandPoolCommon : public Object<VkCommandPool_T> {
    DeviceCommon& m_deviceCommon;
    VkCommandPoolCreateFlags m_flags;
    uint32_t m_queueFamilyIndex;
public:
    struct Entry {
        static VkResult createCommandPool(
            VkDevice device,
            const VkCommandPoolCreateInfo* pCreateInfo,
            const VkAllocationCallbacks* pAllocator,
            VkCommandPool* pCommandPool);
        static void trimCommandPool(
            VkDevice device,
            VkCommandPool commandPool,
            VkCommandPoolTrimFlags flags);
        static VkResult resetCommandPool(
            VkDevice device,
            VkCommandPool commandPool,
            VkCommandPoolResetFlags flags);
        static void destroyCommandPool(
            VkDevice device,
            VkCommandPool commandPool,
            const VkAllocationCallbacks* pAllocator);
    };

    CommandPoolCommon(
        DeviceCommon& deviceCommon,
        const VkCommandPoolCreateInfo& commandPoolCreateInfo,
        const Allocator& allocator);
    virtual ~CommandPoolCommon() = default;

    virtual void trim(VkCommandPoolTrimFlags flags) = 0;
    virtual void reset(VkCommandPoolResetFlags flags) = 0;
    virtual CommandBufferCommon& allocateCommandBuffer(VkCommandBufferLevel level) = 0;
    virtual void freeCommandBuffer(CommandBufferCommon& commandBufferCommon) = 0;

    DeviceCommon& getDevice();
};

}
