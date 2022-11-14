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
    static const std::unordered_map<std::string_view, PFN_vkVoidFunction> s_globalCommands;
    static constexpr uint32_t s_version = VK_API_VERSION_1_3;

    std::unordered_map<std::string_view, PFN_vkVoidFunction> m_dispatchableCommands;
    std::pmr::vector<PhysicalDevice> m_physicalDevices;
    std::pmr::vector<VkPhysicalDeviceGroupProperties> m_physicalDeviceGroupsProperties;
public:
    struct Entry {
        static PFN_vkVoidFunction getInstanceProcAddr(
            VkInstance instance,
            const char* pName);
        static VkResult enumerateInstanceVersion(
            uint32_t* pApiVersion);
        static VkResult createInstance(
            const VkInstanceCreateInfo* pCreateInfo,
            const VkAllocationCallbacks* pAllocator,
            VkInstance* pInstance);
        static void destroyInstance(
            VkInstance instance,
            const VkAllocationCallbacks* pAllocator);
    };

    Instance(const VkInstanceCreateInfo& instanceCreateInfo, const Allocator& allocator);

    PFN_vkVoidFunction getProcAddr(std::string_view name) const;
    uint32_t getPhysicalDeviceCount() const;
    PhysicalDevice& getPhysicalDevice(uint32_t index);
    uint32_t getPhysicalDeviceGroupCount() const;
    const VkPhysicalDeviceGroupProperties& getPhysicalDeviceGroupProperties(uint32_t index) const;
};

}
