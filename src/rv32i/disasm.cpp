#include <string>
#include "mu-emu/rv32i.h"
#include "fmt/core.h"

using MuEmu::ISA::RV32I::Instruction;

std::string DisassembleR(Instruction inst) {
    return "";
}
std::string DisassembleI(Instruction inst) {
    return "";
}
std::string DisassembleS(Instruction inst) {
    return "";
}
std::string DisassembleB(Instruction inst) {
    return "";
}
std::string DisassembleU(Instruction inst) {
    return "";
}
std::string DisassembleJ(Instruction inst) {
    return "";
}

namespace MuEmu { namespace ISA {namespace RV32I {
    std::string Disassemble(Instruction inst) {
        switch (inst.Type()) {
            case InstructionType::R:
                return DisassembleR(inst);
                break;
            case InstructionType::I:
                return DisassembleI(inst);
                break;
            case InstructionType::S:
                return DisassembleS(inst);
                break;
            case InstructionType::B:
                return DisassembleB(inst);
                break;
            case InstructionType::U:
                return DisassembleU(inst);
                break;
            case InstructionType::J:
                return DisassembleJ(inst);
                break;
            case InstructionType::X:
            default:
                return "unknown instruction";
        }
    }

    std::string Disassemble(int32_t word) {
        Instruction inst = Instruction(word);
        return Disassemble(inst);
    }
}}}