#pragma once
#include <vector>
#include <string>
#include <memory>

// Only 32 bits for now
class MuVM {
    private:
        // All registers, including general purpose, control, etc.
        std::vector<int> regfile;
        std::unique_ptr<char[]> memory;

    public:
        MuVM(std::size_t regfileSize, size_t memorySize);
        void PrintSomething(std::string str);
        void Step();
        void Run();
        void MemWrite(size_t addr, void *src, size_t size);
        void MemRead(void *dest, size_t addr, size_t size);
};
