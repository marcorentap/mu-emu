#include <iostream>
#include "core/vm.h"

int main() {
    auto vm = MuEmu::VM(1024 * 1024);
    vm.SetExecutionStrategy("RV32I");
    vm.PrintSomething("something");
    vm.Step();
}