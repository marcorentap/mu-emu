cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
project(mu-emu)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main
)
 
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


add_library(rv32i
            src/rv32i/disasm.cpp
            src/rv32i/inst.cpp
            src/rv32i/exec.cpp
)
target_include_directories(rv32i PUBLIC lib/fmt/include)
target_include_directories(rv32i PUBLIC include)

add_library(core
            src/core/vm.cpp
)
target_include_directories(core PUBLIC lib/fmt/include)
target_include_directories(core PUBLIC include)

add_library(tui
            src/tui/rv32i.cpp
)
target_include_directories(tui PUBLIC lib/fmt/include)
target_include_directories(tui PUBLIC include)
target_link_libraries(tui
  PUBLIC ftxui::screen
  PUBLIC ftxui::dom
  PUBLIC ftxui::component
)


add_executable(mu-emu src/main.cpp)
target_link_libraries(mu-emu core rv32i tui)
target_include_directories(mu-emu PUBLIC lib/argparse)
