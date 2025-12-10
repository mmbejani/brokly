#pragma once

#include <memory>
#include <vector>
namespace momas::brokly::nn {

class Module;

typedef std::shared_ptr<Module> ModulePtr;

class Module {
public:
  void registerModule(ModulePtr) noexcept;

private:
  std::vector<ModulePtr> registeredModule;
};

} // namespace momas::brokly::nn