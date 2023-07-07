cmake_minimum_required(VERSION 3.13)
project(mu-emu)

add_library(rv32i
            src/rv32i/disasm.cpp
            src/rv32i/inst.cpp
            src/rv32i/rv32i.cpp
)
target_include_directories(rv32i PUBLIC lib/fmt/include)
target_include_directories(rv32i PUBLIC include)


add_library(core
            src/core/vm.cpp
)
target_include_directories(core PUBLIC lib/fmt/include)
target_include_directories(core PUBLIC include)


add_executable(mu-emu src/main.cpp)
target_link_libraries(mu-emu core rv32i core)
