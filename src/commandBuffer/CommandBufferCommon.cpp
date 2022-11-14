#include "commandBuffer/CommandBufferCommon.hpp"

namespace bud::vk {

VkResult CommandBufferCommon::Entry::allocateCommandBuffers(
    VkDevice device,
    const VkCommandBufferAllocateInfo* pAllocateInfo,
    VkCommandBuffer* pCommandBuffers) {
    auto& commandPoolCommonInternal = static_cast<CommandPoolCommon&>(*pAllocateInfo->commandPool);
    for (uint32_t i = 0; i < pAllocateInfo->commandBufferCount; i++) {
        pCommandBuffers[i] = &commandPoolCommonInternal.allocateCommandBuffer(pAllocateInfo->level);
    }
    return VK_SUCCESS;
}

VkResult CommandBufferCommon::Entry::resetCommandBuffer(
    VkCommandBuffer commandBuffer,
    VkCommandBufferResetFlags flags) {
    auto& commandBufferCommonInternal = static_cast<CommandBufferCommon&>(*commandBuffer);
    return commandBufferCommonInternal.reset(flags);
}

void CommandBufferCommon::Entry::freeCommandBuffers(
    VkDevice device,
    VkCommandPool commandPool,
    uint32_t commandBufferCount,
    const VkCommandBuffer* pCommandBuffers) {
    auto& commandPoolCommonInternal = static_cast<CommandPoolCommon&>(*commandPool);
    for (uint32_t i = 0; i < commandBufferCount; i++) {
        auto& commandBufferCommonInternal = static_cast<CommandBufferCommon&>(*pCommandBuffers[i]);
        commandPoolCommonInternal.freeCommandBuffer(commandBufferCommonInternal);
    }
}

VkResult CommandBufferCommon::Entry::beginCommandBuffer(
    VkCommandBuffer commandBuffer,
    const VkCommandBufferBeginInfo* pBeginInfo) {
    auto& commandBufferCommonInternal = static_cast<CommandBufferCommon&>(*commandBuffer);
    return commandBufferCommonInternal.begin(*pBeginInfo);
}

VkResult CommandBufferCommon::Entry::endCommandBuffer(
    VkCommandBuffer commandBuffer) {
    auto& commandBufferCommonInternal = static_cast<CommandBufferCommon&>(*commandBuffer);
    return commandBufferCommonInternal.end();
}

CommandBufferCommon::CommandBufferCommon(
    CommandPoolCommon& commandPoolCommon,
    VkCommandBufferLevel level)
    : Object<VkCommandBuffer_T>(commandPoolCommon.getAllocator())
    , m_commandPoolCommon(commandPoolCommon)
    , m_level(level) {}

DeviceCommon& CommandBufferCommon::getDevice() {
    return m_commandPoolCommon.getDevice();
}

}
