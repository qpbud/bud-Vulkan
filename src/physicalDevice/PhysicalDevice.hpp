#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "common/Object.hpp"

namespace bud::vk {

class PhysicalDevice : public Object<VkPhysicalDevice_T> {
    VkPhysicalDeviceProperties2 m_physicalDeviceProperties2;
    std::vector<VkQueueFamilyProperties2> m_queueFamilyProperties2;
public:
    struct Cpu {};

    template<typename T> PhysicalDevice(T);

    const VkPhysicalDeviceProperties2& getProperties2() const;
    uint32_t getQueueFamilyProperties2Count() const;
    const VkQueueFamilyProperties2& getQueueFamilyProperties2(uint32_t index) const;
};

}
