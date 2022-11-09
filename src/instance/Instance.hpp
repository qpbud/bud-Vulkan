#pragma once

#include <vulkan/vulkan.h>
#include "common/Object.hpp"

namespace bud::vk {

class Instance : public Object<VkInstance_T> {
public:
    static constexpr uint32_t s_version = VK_MAKE_API_VERSION(0, 1, 3, 0);

    static Instance& create(const VkInstanceCreateInfo& createInfo);
    static void destroy(Instance& instance);

    Instance(const VkInstanceCreateInfo& createInfo);
};

}
