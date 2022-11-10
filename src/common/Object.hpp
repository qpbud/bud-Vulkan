#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vk_icd.h>
namespace bud::vk {

struct DispatchableObject {
    VK_LOADER_DATA loaderData;

    DispatchableObject() : loaderData() {
        set_loader_magic_value(&loaderData);
    }
};

}

struct VkInstance_T : public bud::vk::DispatchableObject {};
struct VkPhysicalDevice_T : public bud::vk::DispatchableObject {};

namespace bud::vk {

template<typename T>
class Object : public T {};

}
