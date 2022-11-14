#include "commandPool/intelCpu/CommandPool.hpp"
#include "commandBuffer/intelCpu/CommandBuffer.hpp"

namespace bud::vk::intelCpu {

CommandBuffer::CommandBuffer(CommandPool& commandPool, VkCommandBufferLevel level)
    : CommandBufferCommon(commandPool, level) {}

VkResult CommandBuffer::reset(VkCommandBufferResetFlags flags) {
    return VK_SUCCESS;
}

VkResult CommandBuffer::begin(const VkCommandBufferBeginInfo& beginInfo) {
    return VK_SUCCESS;
}

VkResult CommandBuffer::end() {
    return VK_SUCCESS;
}

}
