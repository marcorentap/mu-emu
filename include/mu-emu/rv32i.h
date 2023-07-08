#pragma once
#include "mu-emu/core.h"

namespace MuEmu { namespace ISA { namespace RV32I {
    // X for unknown
    enum class InstructionType {
        R,I,S,B,U,J,X
    };

    // Register ABI names
    enum RegisterName{
        zero,
        ra,
        sp,
        gp,
        tp,
        t0,
        t1,
        t2,
        s0,
        s1,
        a0,
        a1,
        a2,
        a3,
        a4,
        a5,
        a6,
        a7,
        s2,
        s3,
        s4,
        s5,
        s6,
        s7,
        s8,
        s9,
        s10,
        s11,
        t3,
        t4,
        t5,
        t6,
        pc
    };

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

    class ExecutionStrategy : public MuEmu::VM::ExecutionStrategy {
        public:
            static void Lui(MuEmu::VM &vm, Instruction &inst); 
            static void Auipc(MuEmu::VM &vm, Instruction &inst);
            static void Jal(MuEmu::VM &vm, Instruction &inst); 
            static void Jalr(MuEmu::VM &vm, Instruction &inst);
            static void Beq(MuEmu::VM &vm, Instruction &inst); 
            static void Bne(MuEmu::VM &vm, Instruction &inst); 
            static void Blt(MuEmu::VM &vm, Instruction &inst); 
            static void Bge(MuEmu::VM &vm, Instruction &inst); 
            static void Bltu(MuEmu::VM &vm, Instruction &inst);
            static void Bgeu(MuEmu::VM &vm, Instruction &inst);
            static void Lb(MuEmu::VM &vm, Instruction &inst);  
            static void Lh(MuEmu::VM &vm, Instruction &inst);  
            static void Lw(MuEmu::VM &vm, Instruction &inst);  
            static void Lbu(MuEmu::VM &vm, Instruction &inst); 
            static void Lhu(MuEmu::VM &vm, Instruction &inst); 
            static void Sb(MuEmu::VM &vm, Instruction &inst);  
            static void Sh(MuEmu::VM &vm, Instruction &inst);  
            static void Sw(MuEmu::VM &vm, Instruction &inst);  
            static void Addi(MuEmu::VM &vm, Instruction &inst);
            static void Slti(MuEmu::VM &vm, Instruction &inst);
            static void Sltiu(MuEmu::VM &vm, Instruction &inst);
            static void Xori(MuEmu::VM &vm, Instruction &inst);
            static void Ori(MuEmu::VM &vm, Instruction &inst); 
            static void Andi(MuEmu::VM &vm, Instruction &inst);
            static void Slli(MuEmu::VM &vm, Instruction &inst);
            static void Srli(MuEmu::VM &vm, Instruction &inst);
            static void Srai(MuEmu::VM &vm, Instruction &inst);
            static void Add(MuEmu::VM &vm, Instruction &inst); 
            static void Sub(MuEmu::VM &vm, Instruction &inst); 
            static void Sll(MuEmu::VM &vm, Instruction &inst); 
            static void Slt(MuEmu::VM &vm, Instruction &inst); 
            static void Sltu(MuEmu::VM &vm, Instruction &inst);
            static void Xor(MuEmu::VM &vm, Instruction &inst); 
            static void Srl(MuEmu::VM &vm, Instruction &inst); 
            static void Sra(MuEmu::VM &vm, Instruction &inst); 
            static void Or(MuEmu::VM &vm, Instruction &inst);  
            static void And(MuEmu::VM &vm, Instruction &inst); 
            ExecutionStrategy(MuEmu::VM &vm) : MuEmu::VM::ExecutionStrategy(vm) {InitializeVM();}
            void Execute() override;
            void InitializeVM();
    };


    class InstructionSetEntry {
        public:
            std::string mnemonic;
            enum InstructionType type;
            int8_t opcode;
            int8_t func3;
            int8_t func7;
            void (*execFunc)(MuEmu::VM &vm, Instruction &inst);

            InstructionSetEntry(std::string mnemonic, InstructionType instType, int8_t opcode, int8_t func3, int8_t func7,
                        void (*execFunc)(MuEmu::VM&, Instruction&)) : mnemonic(mnemonic), type(instType), opcode(opcode),
                        func3(func3), func7(func7), execFunc(execFunc) {}
    };

    const InstructionSetEntry instructionSet[] = {
        InstructionSetEntry("lui",     InstructionType::U,     0b0110111,         -1,       -1       ,  ExecutionStrategy::Lui),
        InstructionSetEntry("auipc",   InstructionType::U,     0b0010111,         -1,       -1       ,  ExecutionStrategy::Auipc),
        InstructionSetEntry("jal",     InstructionType::J,     0b1101111,         -1,       -1       ,  ExecutionStrategy::Jal),
        InstructionSetEntry("jalr",    InstructionType::I,     0b1100111,      0b000,       -1       ,  ExecutionStrategy::Jalr),
        InstructionSetEntry("beq",     InstructionType::B,     0b1100011,      0b000,       -1       ,  ExecutionStrategy::Beq),
        InstructionSetEntry("bne",     InstructionType::B,     0b1100011,      0b001,       -1       ,  ExecutionStrategy::Beq),
        InstructionSetEntry("blt",     InstructionType::B,     0b1100011,      0b100,       -1       ,  ExecutionStrategy::Blt),
        InstructionSetEntry("bge",     InstructionType::B,     0b1100011,      0b101,       -1       ,  ExecutionStrategy::Bge),
        InstructionSetEntry("bltu",    InstructionType::B,     0b1100011,      0b110,       -1       ,  NULL),
        InstructionSetEntry("bgeu",    InstructionType::B,     0b1100011,      0b111,       -1       ,  NULL),
        InstructionSetEntry("lb",      InstructionType::I,     0b0000011,      0b000,       -1       ,  NULL),
        InstructionSetEntry("lh",      InstructionType::I,     0b0000011,      0b001,       -1       ,  NULL),
        InstructionSetEntry("lw",      InstructionType::I,     0b0000011,      0b010,       -1       ,  ExecutionStrategy::Lw),
        InstructionSetEntry("lbu",     InstructionType::I,     0b0000011,      0b100,       -1       ,  NULL),
        InstructionSetEntry("lhu",     InstructionType::I,     0b0000011,      0b101,       -1       ,  NULL),
        InstructionSetEntry("sb",      InstructionType::S,     0b0100011,      0b000,       -1       ,  NULL),
        InstructionSetEntry("sh",      InstructionType::S,     0b0100011,      0b001,       -1       ,  NULL),
        InstructionSetEntry("sw",      InstructionType::S,     0b0100011,      0b010,       -1       ,  ExecutionStrategy::Sw),
        InstructionSetEntry("addi",    InstructionType::I,     0b0010011,      0b000,       -1       ,  ExecutionStrategy::Addi),
        InstructionSetEntry("slti",    InstructionType::I,     0b0010011,      0b010,       -1       ,  ExecutionStrategy::Slti),
        InstructionSetEntry("sltiu",   InstructionType::I,     0b0010011,      0b011,       -1       ,  NULL),
        InstructionSetEntry("xori",    InstructionType::I,     0b0010011,      0b100,       -1       ,  ExecutionStrategy::Xori),
        InstructionSetEntry("ori",     InstructionType::I,     0b0010011,      0b110,       -1       ,  ExecutionStrategy::Ori),
        InstructionSetEntry("andi",    InstructionType::I,     0b0010011,      0b111,       -1       ,  ExecutionStrategy::Andi),
        InstructionSetEntry("slli",    InstructionType::R,     0b0010011,      0b001,       0b0000000,  ExecutionStrategy::Slli),
        InstructionSetEntry("srli",    InstructionType::R,     0b0010011,      0b101,       0b0000000,  ExecutionStrategy::Srli),
        InstructionSetEntry("srai",    InstructionType::R,     0b0010011,      0b101,       0b0100000,  ExecutionStrategy::Srai),
        InstructionSetEntry("add",     InstructionType::R,     0b0110011,      0b000,       0b0000000,  ExecutionStrategy::Add),
        InstructionSetEntry("sub",     InstructionType::R,     0b0110011,      0b000,       0b0100000,  ExecutionStrategy::Sub),
        InstructionSetEntry("sll",     InstructionType::R,     0b0110011,      0b001,       0b0000000,  ExecutionStrategy::Sll),
        InstructionSetEntry("slt",     InstructionType::R,     0b0110011,      0b010,       0b0000000,  ExecutionStrategy::Slt),
        InstructionSetEntry("sltu",    InstructionType::R,     0b0110011,      0b011,       0b0000000,  NULL),
        InstructionSetEntry("xor",     InstructionType::R,     0b0110011,      0b100,       0b0000000,  ExecutionStrategy::Xor),
        InstructionSetEntry("srl",     InstructionType::R,     0b0110011,      0b101,       0b0000000,  ExecutionStrategy::Srl),
        InstructionSetEntry("sra",     InstructionType::R,     0b0110011,      0b101,       0b0100000,  ExecutionStrategy::Sra),
        InstructionSetEntry("or",      InstructionType::R,     0b0110011,      0b110,       0b0000000,  ExecutionStrategy::Or),
        InstructionSetEntry("and",     InstructionType::R,     0b0110011,      0b111,       0b0000000,  ExecutionStrategy::And),
    };

    class Instruction;
    // Get the ins index in the table given opcode, funct3 and funct7, or word
    std::string Disassemble(Instruction inst);
    std::string Disassemble(int32_t word);
}}};