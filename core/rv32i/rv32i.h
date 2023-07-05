#pragma once
#include "../vm.h"

namespace MuEmu { namespace ISA { namespace RV32I {
    class ExecStrat : public MuEmu::VM::ExecutionStrategy {
        public:
            ExecStrat(MuEmu::VM &vm) : MuEmu::VM::ExecutionStrategy(vm) {}
            void Execute() override;
    };
}}}