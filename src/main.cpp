#define FMT_HEADER_ONLY
#include <iostream>
#include "mu-emu/core.h"
#include "fmt/core.h"

int main() {
    auto vm = MuEmu::VM(1024 * 1024);
    vm.SetExecutionStrategy("RV32I");
    vm.PrintSomething("something");
    vm.Step();

}