#ifndef ANTI_CHEAT_APP_MANAGER_H
#define ANTI_CHEAT_APP_MANAGER_H

#include <absl/status/status.h>

namespace app {
class Manager final {
 public:
  Manager() = delete;

  Manager(const Manager&) = delete;
  Manager& operator=(const Manager&) = delete;

  Manager(Manager&&) = delete;
  Manager& operator=(Manager&&) = delete;

  ~Manager() = delete;

  static absl::Status run();

 private:
  static void print_logo();
  static absl::Status main_loop();
};
}  // namespace app

#endif  // ANTI_CHEAT_APP_MANAGER_H