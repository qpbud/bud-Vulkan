#pragma once

#include <variant>
#include <vector>
#include <vulkan/vulkan.h>
#include "common/Object.hpp"
#include "common/Allocator.hpp"

namespace bud::vk {

class PhysicalDevice : public Object<VkPhysicalDevice_T> {
public:
    struct IntelCpu {};
private:
    std::variant<IntelCpu> m_variant;
    VkPhysicalDeviceProperties2 m_physicalDeviceProperties;
    std::pmr::vector<VkQueueFamilyProperties2> m_queueFamiliesProperties;
public:
    template<typename T> PhysicalDevice(T, const Allocator& allocator);

    const VkPhysicalDeviceProperties2& getProperties() const;
    uint32_t getQueueFamilyCount() const;
    const VkQueueFamilyProperties2& getQueueFamilyProperties(uint32_t index) const;

    template<typename T>
    bool isOfType() const {
        return std::get_if<T>(&m_variant);
    }
};

}
