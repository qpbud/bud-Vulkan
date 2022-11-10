#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "common/Object.hpp"
#include "common/Allocator.hpp"
#include "physicalDevice/PhysicalDevice.hpp"

namespace bud::vk {

class Instance : public Object<VkInstance_T> {
    Allocator m_allocator;
    std::pmr::vector<PhysicalDevice> m_physicalDevices;
public:
    static constexpr uint32_t s_version = VK_MAKE_API_VERSION(0, 1, 3, 0);

    static Instance& create(const VkInstanceCreateInfo& instanceCreateInfo, const VkAllocationCallbacks* allocatorCallbacks);
    static void destroy(Instance& instance);

    Instance(const VkInstanceCreateInfo& instanceCreateInfo, Allocator allocator);

    uint32_t getPhysicalDeviceCount() const;
    PhysicalDevice& getPhysicalDevice(uint32_t index);

    Allocator getAllocator() const;
};

}
