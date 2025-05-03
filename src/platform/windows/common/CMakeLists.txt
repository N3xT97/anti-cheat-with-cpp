include(GoogleTest)

add_library(anti_cheat_windows_common INTERFACE)

target_include_directories(anti_cheat_windows_common INTERFACE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(anti_cheat_windows_common
        INTERFACE
        absl::status
        absl::statusor
)

add_library(anti_cheat::windows::common ALIAS anti_cheat_windows_common)