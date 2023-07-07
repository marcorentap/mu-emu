#pragma once
#include <cstdint>
#include <string>
#include "rv32i.h"

namespace MuEmu { namespace ISA { namespace RV32I {
    enum class InstructionType;
    class Instruction {
        private:
            int32_t word;
        public:
            Instruction(int32_t word) : word(word) {}
            uint8_t Rd();
            uint8_t Rs1();
            uint8_t Rs2();
            int8_t Opcode();
            int8_t Func3();
            int8_t Func7();
            int32_t ImmI();
            int32_t ImmS();
            int32_t ImmB();
            int32_t ImmU();
            int32_t ImmJ();
            InstructionType Type();
            std::string Mnemonic();
    };
}}}

