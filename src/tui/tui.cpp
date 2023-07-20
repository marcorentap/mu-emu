#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/screen/color.hpp>
#include <memory>
#define FMT_HEADER_ONLY
#include "fmt/core.h"
#include "mu-emu/tui.h"
#include <iostream>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

void MuEmu::TUI::start() {
    ftxui::Element document = ftxui::window(ftxui::text("My window") | ftxui::color(ftxui::Color::Blue) | ftxui::blink, ftxui::hbox({
        ftxui::text("left") | ftxui::border,
        ftxui::text("middle") | ftxui::border | ftxui::flex,
        ftxui::text("right") | ftxui::border,
    }));

    auto mainComponent = ftxui::Renderer([&] {
        return document;
    });

    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screen.Loop(mainComponent);
}
