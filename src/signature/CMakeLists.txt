add_library(signature STATIC
        process.cpp
        store.cpp
)

target_include_directories(signature PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(signature
        PUBLIC
        absl::status
        absl::statusor
        PRIVATE
        spdlog::spdlog
)

add_library(anti_cheat::signature ALIAS signature)