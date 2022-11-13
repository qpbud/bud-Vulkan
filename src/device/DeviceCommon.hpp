#pragma once

#include <string_view>
#include <unordered_map>
#include <memory>
#include <vulkan/vulkan.h>
#include "common/Object.hpp"
#include "common/Allocator.hpp"
#include "physicalDevice/PhysicalDevice.hpp"

namespace bud::vk {

class QueueCommon;

class DeviceCommon : public Object<VkDevice_T> {
protected:
    PhysicalDevice& m_physicalDevice;
    std::unordered_map<std::string_view, PFN_vkVoidFunction> m_dispatchableCommands;
    std::unordered_map<uint32_t, std::pmr::vector<std::unique_ptr<QueueCommon, Allocator::Deleter<QueueCommon>>>> m_queues;
public:
    struct Entry {
        static PFN_vkVoidFunction getDeviceProcAddr(
            VkDevice device,
            const char* pName);
        static VkResult createDevice(
            VkPhysicalDevice physicalDevice,
            const VkDeviceCreateInfo* pCreateInfo,
            const VkAllocationCallbacks* pAllocator,
            VkDevice* pDevice);
        static void destroyDevice(
            VkDevice device,
            const VkAllocationCallbacks* pAllocator);
        static void getDeviceQueue(
            VkDevice device,
            uint32_t queueFamilyIndex,
            uint32_t queueIndex,
            VkQueue* pQueue);
        static void getDeviceQueue2(
            VkDevice device,
            const VkDeviceQueueInfo2* pQueueInfo,
            VkQueue* pQueue);
    };

    static DeviceCommon& create(PhysicalDevice& physicalDevice, const VkDeviceCreateInfo& deviceCreateInfo, const VkAllocationCallbacks* allocatorCallbacks);

    DeviceCommon(PhysicalDevice& physicalDevice, const VkDeviceCreateInfo& deviceCreateInfo, const Allocator& allocator);
    virtual ~DeviceCommon() = default;

    PFN_vkVoidFunction getProcAddr(std::string_view name);
    QueueCommon& getQueue(const VkDeviceQueueInfo2& deviceQueueInfo);
};

}
