#pragma once

#include <variant>
#include <vector>
#include <vulkan/vulkan.h>
#include "common/Object.hpp"
#include "common/Allocator.hpp"

namespace bud::vk {

class Instance;

class PhysicalDevice : public Object<VkPhysicalDevice_T> {
public:
    struct IntelCpu {};
private:
    Instance& m_instance;
    std::variant<IntelCpu> m_variant;
    VkPhysicalDeviceProperties2 m_physicalDeviceProperties;
    std::pmr::vector<VkQueueFamilyProperties2> m_queueFamiliesProperties;
public:
    struct Entry {
        static VkResult enumeratePhysicalDevices(
            VkInstance instance,
            uint32_t* pPhysicalDeviceCount,
            VkPhysicalDevice* pPhysicalDevices);
        static void getPhysicalDeviceProperties(
            VkPhysicalDevice physicalDevice,
            VkPhysicalDeviceProperties* pProperties);
        static void getPhysicalDeviceProperties2(
            VkPhysicalDevice physicalDevice,
            VkPhysicalDeviceProperties2* pProperties);
        static void getPhysicalDeviceQueueFamilyProperties(
            VkPhysicalDevice physicalDevice,
            uint32_t* pQueueFamilyPropertyCount,
            VkQueueFamilyProperties* pQueueFamilyProperties);
        static void getPhysicalDeviceQueueFamilyProperties2(
            VkPhysicalDevice physicalDevice,
            uint32_t* pQueueFamilyPropertyCount,
            VkQueueFamilyProperties2* pQueueFamilyProperties);
        static VkResult enumeratePhysicalDeviceGroups(
            VkInstance instance,
            uint32_t* pPhysicalDeviceGroupCount,
            VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties);
    };

    template<typename T> PhysicalDevice(T, Instance& instance, const Allocator& allocator);

    const VkPhysicalDeviceProperties2& getProperties() const;
    uint32_t getQueueFamilyCount() const;
    const VkQueueFamilyProperties2& getQueueFamilyProperties(uint32_t index) const;

    Instance& getInstance();
    template<typename T>
    bool isOfType() const {
        return std::get_if<T>(&m_variant);
    }
};

}
