#pragma once

#include <memory>
#include <vector>
namespace momas::brokly::nn {

class Module;

typedef std::shared_ptr<Module> ModulePtr;

/**
 * class `Module` does not have virtual method named `forward`, bcause
 * the virtualization of a method make it slow to invoke, therefore
 * caution! each one the specific module should implement this method.
 */
class Module {
public:
  void registerModule(ModulePtr) noexcept;

private:
  std::vector<ModulePtr> registeredModule;
};

} // namespace momas::brokly::nn