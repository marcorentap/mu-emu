#include <iostream>
#include <memory>
#include <cstring>
#include "vm.h"

MuVM::MuVM(size_t regfileSize, size_t memorySize) {
    this->regfile.resize(regfileSize);
    this->memory = std::make_unique<char[]>(memorySize);
}

void MuVM::PrintSomething(std::string str) {
    std::cout << str << std::endl;
}

void MuVM::Step() {
    std::cout <<"step" << std::endl;
}

void MuVM::Run() {
    std::cout << "run" << std::endl;
}

void MuVM::MemWrite(size_t addr, void* src, size_t size) {
    void* real_addr = this->memory.get() + addr;
    std::memcpy(real_addr, src, size);
}

void MuVM::MemRead(void *dest, size_t addr, size_t size) {
    void *real_addr = this->memory.get() + addr;
    std::memcpy(dest, real_addr, size);
}
