#ifndef ANTI_CHEAT_TARGET_MANAGER_H
#define ANTI_CHEAT_TARGET_MANAGER_H

#include "target/controller.h"

namespace target {
class Manager final {
 public:
  Manager() = delete;
  explicit Manager(std::unique_ptr<IController> controller);

  Manager(const Manager&) = delete;
  Manager& operator=(const Manager&) = delete;
  Manager(Manager&&) = delete;
  Manager& operator=(Manager&&) = delete;

  ~Manager() = default;

  absl::Status launch();
  [[nodiscard]]
  absl::StatusOr<bool> is_running() const;
  absl::Status terminate();

 private:
  std::unique_ptr<IController> controller_;
};
}  // namespace target

#endif  // ANTI_CHEAT_TARGET_MANAGER_H
