#include "mu-emu/rv32i.h"
#define FMT_HEADER_ONLY
#include <iostream>
#include "mu-emu/core.h"
#include "fmt/core.h"
#include "mu-emu/tui.h"
#include "argparse/argparse.hpp"

int main(int argc, char *argv[]) {
    argparse::ArgumentParser parser("mu-emu");
    parser.add_argument("--isa")
        .help("Select the ISA. Currently supported ISAs include: RV32I")
        .required();
    parser.add_argument("--tui")
        .help("Select the TUI. Currently supported ISAs include: Generic, RV32I")
        .required();

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error &err){
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    auto tuiOption = parser.get<std::string>("--tui");
    auto isaOption = parser.get<std::string>("--isa");
    
    auto vm = MuEmu::VM(1024 * 1024);
    vm.SetExecutionStrategy(isaOption);
    // TODO: Change the TUI interface to look like the VM
    auto tui = MuEmu::ISA::RV32I::TUIStrategy(vm);
    tui.start();
}
