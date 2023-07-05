#include <iostream>
#include <memory>
#include <cstring>
#include <utility>
#include "vm.h"
#include "rv32i/rv32i.h"

using namespace MuEmu;

VM::VM(size_t memorySize) {
    this->memory = std::make_unique<char[]>(memorySize);
}

void VM::SetExecutionStrategy(std::string execStrat) {
    std::cout << "Set execution" << std::endl;
    if (execStrat == "RV32I") {
        auto execStrat= std::make_unique<MuEmu::ISA::RV32I::ExecutionStrategy>(*this);
        this->execStrat = std::move(execStrat);
    }
}

void VM::PrintSomething(std::string str) {
    std::cout << str << std::endl;
}

void VM::Step() {
    this->execStrat->Execute();
}

void VM::Run() {
    std::cout << "run" << std::endl;
}

void VM::MemWrite(size_t addr, void* src, size_t size) {
    void* real_addr = this->memory.get() + addr;
    std::memcpy(real_addr, src, size);
}

void VM::MemRead(void *dest, size_t addr, size_t size) {
    void *real_addr = this->memory.get() + addr;
    std::memcpy(dest, real_addr, size);
}
