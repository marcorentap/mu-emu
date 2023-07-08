#include <iostream>
#include <memory>
#include <cstring>
#include <utility>
#include "mu-emu/core.h"
#include "mu-emu/rv32i.h"

using namespace MuEmu;

VM::VM(uint32_t memorySize) {
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

void VM::MemWrite(uint32_t addr, void* src, uint32_t size) {
    void* real_addr = this->memory.get() + addr;
    std::memcpy(real_addr, src, size);
}

void VM::MemRead(void *dest, uint32_t addr, uint32_t size) {
    void *real_addr = this->memory.get() + addr;
    std::memcpy(dest, real_addr, size);
}

void VM::RegWrite(size_t regId, int32_t src) {
    this->regfile[regId] = src;
}

int32_t VM::RegRead(size_t regId) {
    return this->regfile[regId];
}