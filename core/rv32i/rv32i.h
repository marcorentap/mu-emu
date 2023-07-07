#pragma once
#include "../vm.h"
#include "inst.h"

namespace MuEmu { namespace ISA { namespace RV32I {
    // X for unknown
    enum class InstructionType {
        R,I,S,B,U,J,X
    };

    class ExecutionStrategy : public MuEmu::VM::ExecutionStrategy {
        public:
            ExecutionStrategy(MuEmu::VM &vm) : MuEmu::VM::ExecutionStrategy(vm) {}
            void Execute() override;
    };

    class InstructionSetEntry {
        public:
            std::string mnemonic;
            enum InstructionType type;
            int8_t opcode;
            int8_t func3;
            int8_t func7;
            void (*execFunc)(MuEmu::VM &vm, int32_t);

            InstructionSetEntry(std::string mnemonic, InstructionType instType, int8_t opcode, int8_t func3, int8_t func7,
                        void (*execFunc)(MuEmu::VM&, int32_t)) : mnemonic(mnemonic), type(instType), opcode(opcode),
                        func3(func3), func7(func7), execFunc(execFunc) {}
    };

    const InstructionSetEntry instructionSet[] = {
        InstructionSetEntry("lui",     InstructionType::U,     0b0110111,         -1,       -1       ,  nullptr),
        InstructionSetEntry("auipc",   InstructionType::U,     0b0010111,         -1,       -1       ,  nullptr),
        InstructionSetEntry("jal",     InstructionType::J,     0b1101111,         -1,       -1       ,  nullptr),
        InstructionSetEntry("jalr",    InstructionType::I,     0b1100111,      0b000,       -1       ,  nullptr),
        InstructionSetEntry("beq",     InstructionType::B,     0b1100011,      0b000,       -1       ,  nullptr),
        InstructionSetEntry("bne",     InstructionType::B,     0b1100011,      0b001,       -1       ,  nullptr),
        InstructionSetEntry("blt",     InstructionType::B,     0b1100011,      0b100,       -1       ,  nullptr),
        InstructionSetEntry("bge",     InstructionType::B,     0b1100011,      0b101,       -1       ,  nullptr),
        InstructionSetEntry("bltu",    InstructionType::B,     0b1100011,      0b110,       -1       ,  nullptr),
        InstructionSetEntry("bgeu",    InstructionType::B,     0b1100011,      0b111,       -1       ,  nullptr),
        InstructionSetEntry("lb",      InstructionType::I,     0b0000011,      0b000,       -1       ,  nullptr),
        InstructionSetEntry("lh",      InstructionType::I,     0b0000011,      0b001,       -1       ,  nullptr),
        InstructionSetEntry("lw",      InstructionType::I,     0b0000011,      0b010,       -1       ,  nullptr),
        InstructionSetEntry("lbu",     InstructionType::I,     0b0000011,      0b100,       -1       ,  nullptr),
        InstructionSetEntry("lhu",     InstructionType::I,     0b0000011,      0b101,       -1       ,  nullptr),
        InstructionSetEntry("sb",      InstructionType::S,     0b0100011,      0b000,       -1       ,  nullptr),
        InstructionSetEntry("sh",      InstructionType::S,     0b0100011,      0b001,       -1       ,  nullptr),
        InstructionSetEntry("sw",      InstructionType::S,     0b0100011,      0b010,       -1       ,  nullptr),
        InstructionSetEntry("addi",    InstructionType::I,     0b0010011,      0b000,       -1       ,  nullptr),
        InstructionSetEntry("slti",    InstructionType::I,     0b0010011,      0b010,       -1       ,  nullptr),
        InstructionSetEntry("sltiu",   InstructionType::I,     0b0010011,      0b011,       -1       ,  nullptr),
        InstructionSetEntry("xori",    InstructionType::I,     0b0010011,      0b100,       -1       ,  nullptr),
        InstructionSetEntry("ori",     InstructionType::I,     0b0010011,      0b110,       -1       ,  nullptr),
        InstructionSetEntry("andi",    InstructionType::I,     0b0010011,      0b111,       -1       ,  nullptr),
        InstructionSetEntry("slli",    InstructionType::R,     0b0010011,      0b001,       0b0000000,  nullptr),
        InstructionSetEntry("srli",    InstructionType::R,     0b0010011,      0b101,       0b0000000,  nullptr),
        InstructionSetEntry("srai",    InstructionType::R,     0b0010011,      0b101,       0b0100000,  nullptr),
        InstructionSetEntry("add",     InstructionType::R,     0b0110011,      0b000,       0b0000000,  nullptr),
        InstructionSetEntry("sub",     InstructionType::R,     0b0110011,      0b000,       0b0100000,  nullptr),
        InstructionSetEntry("sll",     InstructionType::R,     0b0110011,      0b001,       0b0000000,  nullptr),
        InstructionSetEntry("slt",     InstructionType::R,     0b0110011,      0b010,       0b0000000,  nullptr),
        InstructionSetEntry("sltu",    InstructionType::R,     0b0110011,      0b011,       0b0000000,  nullptr),
        InstructionSetEntry("xor",     InstructionType::R,     0b0110011,      0b100,       0b0000000,  nullptr),
        InstructionSetEntry("srl",     InstructionType::R,     0b0110011,      0b101,       0b0000000,  nullptr),
        InstructionSetEntry("sra",     InstructionType::R,     0b0110011,      0b101,       0b0100000,  nullptr),
        InstructionSetEntry("or",      InstructionType::R,     0b0110011,      0b110,       0b0000000,  nullptr),
        InstructionSetEntry("and",     InstructionType::R,     0b0110011,      0b111,       0b0000000,  nullptr),
    };

    class Instruction;
    // Get the ins index in the table given opcode, funct3 and funct7, or word
    std::string Disassemble(Instruction inst);
    std::string Disassemble(int32_t word);
}}}