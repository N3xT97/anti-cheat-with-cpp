#include <spdlog/spdlog.h>

#include <cstdlib>

#include "app/manager.h"

int main(int argc, char **argv) {
  spdlog::set_level(spdlog::level::trace);

  spdlog::info("Anti-Cheat started");
  const absl::Status result = app::Manager::run();
  if (!result.ok()) {
    spdlog::critical("Anti-Cheat failed\n{}", result.ToString());
    return EXIT_FAILURE;
  }
  spdlog::info("Anti-Cheat exiting");
  return EXIT_SUCCESS;
}
