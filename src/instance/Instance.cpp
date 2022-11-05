#include "instance/Instance.hpp"

namespace bud::vk {

Instance& Instance::create(const VkInstanceCreateInfo& createInfo) {
    Instance* instance = new Instance(createInfo);
    return *instance;
}

void Instance::destroy(Instance& instance) {
    delete &instance;
}

Instance::Instance(const VkInstanceCreateInfo& createInfo) {}

}
