add_library(anti_cheat_common INTERFACE)

target_include_directories(anti_cheat_common INTERFACE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(anti_cheat_common
        INTERFACE
        absl::status
        absl::statusor
)

add_library(anti_cheat::common ALIAS anti_cheat_common)