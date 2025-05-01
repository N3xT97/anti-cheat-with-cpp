add_library(anti_cheat_windows_process STATIC
        controller.cpp
)

target_include_directories(anti_cheat_windows_process
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(anti_cheat_windows_process
        PUBLIC
        absl::status
        absl::statusor
        PRIVATE
        anti_cheat::target
        anti_cheat::windows::common
        spdlog::spdlog
)

add_library(anti_cheat::windows::process ALIAS anti_cheat_windows_process)