add_executable(anti_cheat
        main.cpp
)

target_link_libraries(anti_cheat
        PRIVATE
        spdlog::spdlog
        anti_cheat::common
        anti_cheat::app
)