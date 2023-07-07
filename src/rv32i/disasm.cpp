#include <string>
#include "mu-emu/rv32i.h"
#include "fmt/core.h"

using MuEmu::ISA::RV32I::Instruction;

std::string DisassembleX(Instruction inst) {
    return "unknown instruction";
}

std::string DisassembleR(Instruction inst) {
    if (inst.Opcode() == 0b0010011) {
        // Shift instructions
        return fmt::format("{:s} x{:d}, x{:d}, {:d}",
            inst.Mnemonic(), inst.Rd(), inst.Rs1(), inst.Rs2()
        );
    }

    return fmt::format("{:s} x{:d}, x{:d}, x{:d}",
        inst.Mnemonic(), inst.Rd(), inst.Rs1(), inst.Rs2()
    );
}

// TODO: Some code here assumes proper opcodes, but some don't
//       and this is likely fine since Instruction::Type
//       is X when proper opcode,func3,func7 combination is not found
//       Need to change for consistency and sanity :)

std::string DisassembleI(Instruction inst) {
    // Load instructions
    if (inst.Opcode() == 0b0000011) {
        return fmt::format("{:s} x{:d}, {:d}(x{:d})",
            inst.Mnemonic(), inst.Rd(), inst.ImmI(), inst.Rs1());
    }

    // Logic instructions
    if (inst.Opcode() == 0b0010011) {
        return fmt::format("{:s} x{:d}, x{:d}, {:d}",
            inst.Mnemonic(), inst.Rd(), inst.Rs1(), inst.ImmI());
    }

    // Jalr instructions
    if (inst.Opcode() == 0b1100111) {
        return fmt::format("{:s} x{:d}, {:d}(x{:d})",
            inst.Mnemonic(), inst.Rd(), inst.ImmI(), inst.Rs1());
    }

    // Unknown instruction
    return DisassembleX(inst);
}

std::string DisassembleS(Instruction inst) {
    // Shift instructions
    if (inst.Opcode() == 0b0100011) {
        return fmt::format("{:s} x{:d}, {:d}(x{:d})",
            inst.Mnemonic(), inst.Rs2(), inst.ImmS(), inst.Rs1());
    }

    // Unknown instruction
    return DisassembleX(inst);
}

std::string DisassembleB(Instruction inst) {
    if (inst.Opcode() == 0b1100011) {
        // Branch instructions
        return fmt::format("{:s} x{:d}, x{:d}, {:d}",
            inst.Mnemonic(), inst.Rs1(), inst.Rs2(), inst.ImmB());
    }

    // Unknown instruction
    return DisassembleX(inst);
}

std::string DisassembleU(Instruction inst) {
    return fmt::format("{:s} x{:d}, {:d}",
        inst.Mnemonic(), inst.Rd(), inst.ImmU());
}

std::string DisassembleJ(Instruction inst) {
    return fmt::format("{:s} x{:d}, {:d}",
        inst.Mnemonic(), inst.Rd(), inst.ImmJ());
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