#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>

// Only 32 bits for now
namespace MuEmu {
    class VM {
        public:
            // All registers, including general purpose, control, etc.
            std::vector<int32_t> regfile;
            std::unique_ptr<char[]> memory;

            class ExecutionStrategy {
                protected:
                    VM &vm;
                public:
                    ExecutionStrategy(VM &vm) : vm(vm) {}
                    virtual void Execute() {
                        std::cout << "Using default Execute()" << std::endl;
                    }
            };
        
        private:
            std::unique_ptr<ExecutionStrategy> execStrat;

        public:
            VM(uint32_t memorySize);
            void PrintSomething(std::string str);
            void SetExecutionStrategy(std::string execStrat);
            void Step();
            void Run();
            void MemWrite(uint32_t addr, void *src, uint32_t size);
            void MemRead(void *dest, uint32_t addr, uint32_t size);
            void RegWrite(size_t regId, int32_t src);
            int32_t RegRead(size_t regId);
    };
}
