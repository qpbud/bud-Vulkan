#pragma once

#include <unordered_map>
#include <string_view>
#include <vector>
#include <vulkan/vulkan.h>
#include "common/Object.hpp"
#include "common/Allocator.hpp"
#include "physicalDevice/PhysicalDevice.hpp"

namespace bud::vk {

class Instance : public Object<VkInstance_T> {
    std::pmr::vector<PhysicalDevice> m_physicalDevices;
    std::pmr::vector<VkPhysicalDeviceGroupProperties> m_physicalDeviceGroupsProperties;
public:
    static const std::unordered_map<std::string_view, PFN_vkVoidFunction> s_globalCommands;
    static const std::unordered_map<std::string_view, PFN_vkVoidFunction> s_dispatchableCommands;
    static constexpr uint32_t s_version = VK_API_VERSION_1_3;

    static Instance& create(const VkInstanceCreateInfo& instanceCreateInfo, const VkAllocationCallbacks* allocatorCallbacks);
    static void destroy(Instance& instance);

    Instance(const VkInstanceCreateInfo& instanceCreateInfo, const Allocator& allocator);

    uint32_t getPhysicalDeviceCount() const;
    PhysicalDevice& getPhysicalDevice(uint32_t index);
    uint32_t getPhysicalDeviceGroupCount() const;
    const VkPhysicalDeviceGroupProperties& getPhysicalDeviceGroupProperties(uint32_t index) const;
};

}
