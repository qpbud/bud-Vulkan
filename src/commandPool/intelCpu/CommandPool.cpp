#include "commandPool/intelCpu/CommandPool.hpp"
#include "commandBuffer/intelCpu/CommandBuffer.hpp"

namespace bud::vk::intelCpu {

CommandPool::CommandPool(
    Device& device,
    const VkCommandPoolCreateInfo& commandPoolCreateInfo,
    const Allocator& allocator)
    : CommandPoolCommon(device, commandPoolCreateInfo, allocator) {}

void CommandPool::trim(VkCommandPoolTrimFlags flags) {}

void CommandPool::reset(VkCommandPoolResetFlags flags) {}

CommandBufferCommon& CommandPool::allocateCommandBuffer(VkCommandBufferLevel level) {
    return m_allocator.construct<CommandBuffer>(*this, level);
}

void CommandPool::freeCommandBuffer(CommandBufferCommon& commandBufferCommon) {
    m_allocator.destruct(commandBufferCommon);
}

}
