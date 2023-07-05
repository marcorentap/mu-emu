#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>

// Only 32 bits for now
namespace MuEmu {
    class VM {
        public:
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
            // All registers, including general purpose, control, etc.
            std::vector<int> regfile;
            std::unique_ptr<char[]> memory;
            std::unique_ptr<ExecutionStrategy> execStrat;

        public:
            VM(size_t memorySize);
            void PrintSomething(std::string str);
            void SetExecutionStrategy(std::string execStrat);
            void Step();
            void Run();
            void MemWrite(size_t addr, void *src, size_t size);
            void MemRead(void *dest, size_t addr, size_t size);
    };
}
