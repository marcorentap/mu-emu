#pragma once
#include "../vm.h"

namespace MuEmu { namespace ISA { namespace RV32I {
    class ExecutionStrategy : public MuEmu::VM::ExecutionStrategy {
        public:
            ExecutionStrategy(MuEmu::VM &vm) : MuEmu::VM::ExecutionStrategy(vm) {}
            void Execute() override;
    };

}}}