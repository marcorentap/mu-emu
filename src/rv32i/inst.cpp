#include "mu-emu/rv32i.h"

using MuEmu::ISA::RV32I::Instruction;
using MuEmu::ISA::RV32I::InstructionType;

// Slices bits from instruction word, with sign extension
int32_t GetBitrange(int32_t word, int32_t start, int32_t end) {
    int32_t lmask = ~0 << start; // Mask from start to leftmost bit
    int32_t rmask = ~((~0 << end) << 1); // Mask from start to rightmost bit
    int32_t mask = lmask & rmask;
    return (mask & (int32_t) word) >> start;
}

// immstart and immend correspond to the indexes of imm's bits imm[immstart:immend];
// bitstart correspond to the bit position of the slice relative to the word
int32_t GetImmPartition(int32_t word, int8_t immstart, int8_t immend, int8_t bitstart) {
    int8_t length = immend - immstart + 1;
    int32_t mask = ~(-1 << (length));
    return (GetBitrange(word, bitstart, bitstart + length - 1) & mask) << immstart;
}

// Similar to get_imm_partition, but if immend is the leftmost bit of imm, then use this
int32_t GetLeftmostImmPartition(int32_t word, int8_t immstart, int8_t immend, int8_t bitstart) {
    int8_t length = immend - immstart + 1;
    int32_t mask = ~(-1 << length);
    // Don't mask to keep leftmost 1's for negative numbers
    return GetBitrange(word, bitstart, bitstart + length - 1) << immstart;
}

uint8_t Instruction::Rd() {
    return GetBitrange(word, 7, 11);
}

uint8_t Instruction::Rs1() {
    return GetBitrange(word, 15, 19);
}

uint8_t Instruction::Rs2() {
    return GetBitrange(word, 20, 24);
}

int8_t Instruction::Opcode() {
    return GetBitrange(word, 0, 6);
}

int8_t Instruction::Func3() {
    return GetBitrange(word, 12, 14);
}

int8_t Instruction::Func7() {
    return GetBitrange(word, 25, 31);
}

int32_t Instruction::ImmS() {
    int32_t bits0_4 = GetImmPartition(word, 0, 4, 7);
    int32_t bits5_11 = GetLeftmostImmPartition(word, 5, 11, 25);
    return bits0_4 + bits5_11;
}

int32_t Instruction::ImmI() {
    return GetLeftmostImmPartition(word, 0, 11, 20);
}

int32_t Instruction::ImmB() {
    int32_t bits1_4 = GetImmPartition(word, 1, 4, 8);
    int32_t bits5_10 = GetImmPartition(word, 5, 10, 25);
    int32_t bits11 = GetImmPartition(word, 11, 11, 7);
    int32_t bits12 = GetLeftmostImmPartition(word, 12, 12, 31);
    return bits1_4 + bits5_10 + bits11 + bits12;
}

int32_t Instruction::ImmU() {
    int32_t bits12_31 = GetLeftmostImmPartition(word, 12, 31, 12);
    return bits12_31;
}

int32_t Instruction::ImmJ() {
    int32_t bits1_10 = GetImmPartition(word, 1, 10, 21);
    int32_t bits11 = GetImmPartition(word, 11, 11, 20);
    int32_t bits12_19 = GetImmPartition(word, 12, 19, 12);
    int32_t bits20 = GetLeftmostImmPartition(word, 20, 20, 31);
    return bits1_10 + bits11 + bits12_19 + bits20;
}

// TODO: Write function to lookup instructionSet. Duplicate here
std::string Instruction::Mnemonic() {
    for (auto &inst: instructionSet) {
        if (inst.opcode == this->Opcode() &&
            inst.func3 == this->Func3() &&
            inst.func7 == this->Func7()) {
            return inst.mnemonic;
        }
    } 
    return "unknown";
}

InstructionType Instruction::Type() {
    for (auto &inst: instructionSet) {
        if (inst.opcode == this->Opcode() &&
            inst.func3 == this->Func3() &&
            inst.func7 == this->Func7()) {
            return inst.type;
        }
    } 

    return InstructionType::X;
}
