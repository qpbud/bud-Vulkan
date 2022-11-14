#pragma once

#include <vulkan/vulkan.h>
#include "common/Object.hpp"
#include "common/Allocator.hpp"
#include "commandPool/CommandPoolCommon.hpp"

namespace bud::vk {

class CommandBufferCommon : public Object<VkCommandBuffer_T> {
    CommandPoolCommon& m_commandPoolCommon;
    VkCommandBufferLevel m_level;
public:
    struct Entry {
        static VkResult allocateCommandBuffers(
            VkDevice device,
            const VkCommandBufferAllocateInfo* pAllocateInfo,
            VkCommandBuffer* pCommandBuffers);
        static VkResult resetCommandBuffer(
            VkCommandBuffer commandBuffer,
            VkCommandBufferResetFlags flags);
        static void freeCommandBuffers(
            VkDevice device,
            VkCommandPool commandPool,
            uint32_t commandBufferCount,
            const VkCommandBuffer* pCommandBuffers);
        static VkResult beginCommandBuffer(
            VkCommandBuffer commandBuffer,
            const VkCommandBufferBeginInfo* pBeginInfo);
        static VkResult endCommandBuffer(
            VkCommandBuffer commandBuffer);
    };

    CommandBufferCommon(CommandPoolCommon& commandPoolCommon, VkCommandBufferLevel level);
    virtual ~CommandBufferCommon() = default;

    virtual VkResult reset(VkCommandBufferResetFlags flags) = 0;
    virtual VkResult begin(const VkCommandBufferBeginInfo& beginInfo) = 0;
    virtual VkResult end() = 0;

    DeviceCommon& getDevice();
};

}
