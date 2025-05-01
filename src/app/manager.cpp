#include "app/manager.h"

#include <spdlog/spdlog.h>

#include <iostream>

#include "common/status_macros.h"
#include "target/controller_factory.h"
#include "target/manager.h"

namespace app {
absl::Status Manager::run() {
  spdlog::trace("app::Manager::run");
  print_logo();
  const absl::Status result = main_loop();
  return result;
}

void Manager::print_logo() {
  spdlog::trace("app::Manager::print_logo");
  const wchar_t *logo =
      LR"(
    +========================================================+
    |                                                        |
    |       _          _   _    ____ _                _      |
    |      / \   _ __ | |_(_)  / ___| |__   ___  __ _| |_    |
    |     / _ \ | '_ \| __| | | |   | '_ \ / _ \/ _` | __|   |
    |    / ___ \| | | | |_| | | |___| | | |  __/ (_| | |_    |
    |   /_/   \_\_| |_|\__|_|  \____|_| |_|\___|\__,_|\__|   |
    |                                           with rust    |
    |                                             by n3xt    |
    |                                                        |
    +========================================================+
    )";
  std::wcout << logo << std::endl;
}

absl::Status Manager::main_loop() {
  spdlog::trace("app::Manager::main_loop");

  const std::string target_path = "C:\\Windows\\System32\\notepad.exe";
  ASSIGN_OR_RETURN(auto target_controller,
                   target::ControllerFactory::Create(
                       target::ControllerType::kWindows, target_path));
  target::Manager target_manager(std::move(target_controller));
  RETURN_IF_ERROR(target_manager.launch());
  spdlog::info("Target '{}' launched", target_path);

  // todo

  ASSIGN_OR_RETURN(bool is_target_running, target_manager.is_running());
  if (is_target_running) {
    RETURN_IF_ERROR(target_manager.terminate());
  }
  return absl::OkStatus();
}
}  // namespace app
