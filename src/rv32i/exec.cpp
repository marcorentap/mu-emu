#include "mu-emu/rv32i.h"

using MuEmu::ISA::RV32I::ExecutionStrategy;

void ExecutionStrategy::Add(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto rd = inst.Rd();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);
    vm.RegWrite(rd, vmRs1 + vmRs2);
}

void ExecutionStrategy::Sub(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto rd = inst.Rd();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);
    vm.RegWrite(rd, vmRs1 - vmRs2);
}

void ExecutionStrategy::Addi(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rd = inst.Rd();
    auto immi = inst.ImmI();

    auto vmRs1 = vm.RegRead(rs1);
    vm.RegWrite(rd, vmRs1 - immi);
}

void ExecutionStrategy::Xor(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto rd = inst.Rd();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);
    vm.RegWrite(rd, vmRs1 ^ vmRs2);
}

void ExecutionStrategy::Or(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto rd = inst.Rd();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);
    vm.RegWrite(rd, vmRs1 | vmRs2);
}

void ExecutionStrategy::And(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto rd = inst.Rd();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);
    vm.RegWrite(rd, vmRs1 & vmRs2);
}

void ExecutionStrategy::Xori(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rd = inst.Rd();
    auto immi = inst.ImmI();

    auto vmRs1 = vm.RegRead(rs1);
    vm.RegWrite(rd, vmRs1 ^ immi);
}

void ExecutionStrategy::Ori(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rd = inst.Rd();
    auto immi = inst.ImmI();

    auto vmRs1 = vm.RegRead(rs1);
    vm.RegWrite(rd, vmRs1 | immi);
}

void ExecutionStrategy::Andi(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rd = inst.Rd();
    auto immi = inst.ImmI();

    auto vmRs1 = vm.RegRead(rs1);
    vm.RegWrite(rd, vmRs1 & immi);
}

void ExecutionStrategy::Slli(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rd = inst.Rd();
    auto shamt = inst.Rs2();

    auto vmRs1 = vm.RegRead(rs1);
    vm.RegWrite(rd, vmRs1 << shamt);
}

void ExecutionStrategy::Srli(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = (uint32_t) inst.Rs1();
    auto rd = inst.Rd();
    auto shamt = inst.Rs2();

    auto vmRs1 = vm.RegRead(rs1);
    vm.RegWrite(rd, vmRs1 >> shamt);
}

void ExecutionStrategy::Srai(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rd = inst.Rd();
    auto shamt = inst.Rs2();

    auto vmRs1 = vm.RegRead(rs1);
    vm.RegWrite(rd, (vmRs1 >> shamt));
}

void ExecutionStrategy::Sll(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto rd = inst.Rd();

    auto vmRs1 = (uint32_t) vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);
    auto shamt = vmRs2 & (0xff >> 3);
    vm.RegWrite(rd, (vmRs1 << shamt));
}

void ExecutionStrategy::Srl(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto rd = inst.Rd();

    auto vmRs1 = (uint32_t) vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);
    auto shamt = vmRs2 & (0xff >> 3);
    vm.RegWrite(rd, (vmRs1 >> shamt));
}

void ExecutionStrategy::Sra(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto rd = inst.Rd();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);
    auto shamt = vmRs2 & (0xff >> 3);
    vm.RegWrite(rd, (vmRs1 >> shamt));
}

void ExecutionStrategy::Slti(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto immi = inst.ImmI();
    auto rd = inst.Rd();

    auto vmRs1 = vm.RegRead(rs1);
    vm.RegWrite(rd, (vmRs1 < immi));
}

void ExecutionStrategy::Slt(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto rd = inst.Rd();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);
    vm.RegWrite(rd, (vmRs1 < vmRs2));
}

void ExecutionStrategy::Auipc(MuEmu::VM &vm, Instruction &inst) {
    auto rd = inst.Rd();
    auto immu = inst.ImmU();
    auto vmPc = vm.RegRead(RegisterName::pc);

    vm.RegWrite(rd, (vmPc + immu));
}

void ExecutionStrategy::Lui(MuEmu::VM &vm, Instruction &inst) {
    auto rd = inst.Rd();
    auto immu = inst.ImmU();

    vm.RegWrite(rd, (immu));
}

void ExecutionStrategy::Jal(MuEmu::VM &vm, Instruction &inst) {
    auto rd = inst.Rd();
    auto immj = inst.ImmJ();
    auto vmPc = vm.RegRead(RegisterName::pc);
    auto nextPc = vmPc + 4;

    vm.RegWrite(RegisterName::pc, vmPc + immj);
    vm.RegWrite(rd, nextPc);
}

void ExecutionStrategy::Jalr(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rd = inst.Rd();
    auto immi = inst.ImmI();

    auto vmPc = vm.RegRead(RegisterName::pc);
    auto nextPc = vmPc + 4;
    int32_t vmRs1 = vm.RegRead(rs1);

    vm.RegWrite(RegisterName::pc, vmRs1 + immi);
    vm.RegWrite(rd, nextPc);
}

void ExecutionStrategy::Beq(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto immb = inst.ImmB();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);

    if (vmRs1 == vmRs2) {
        auto vmPc = vm.RegRead(RegisterName::pc);
        vm.RegWrite(RegisterName::pc, immb + vmPc);
    }
}

void ExecutionStrategy::Bne(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto immb = inst.ImmB();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);

    if (vmRs1 != vmRs2) {
        auto vmPc = vm.RegRead(RegisterName::pc);
        vm.RegWrite(RegisterName::pc, immb + vmPc);
    }
}

void ExecutionStrategy::Blt(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto immb = inst.ImmB();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);

    if (vmRs1 < vmRs2) {
        auto vmPc = vm.RegRead(RegisterName::pc);
        vm.RegWrite(RegisterName::pc, immb + vmPc);
    }
}

void ExecutionStrategy::Bge(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto immb = inst.ImmB();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);

    if (vmRs1 >= vmRs2) {
        auto vmPc = vm.RegRead(RegisterName::pc);
        vm.RegWrite(RegisterName::pc, immb + vmPc);
    }
}

void ExecutionStrategy::Lw(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rd = inst.Rd();
    auto immi = inst.ImmI();

    auto vmRs1 = vm.RegRead(rs1);
    auto srcAddr = immi + vmRs1;

    int32_t buf;
    vm.MemRead(&buf, srcAddr, 32);
    vm.RegWrite(rd, buf);
}

void ExecutionStrategy::Sw(MuEmu::VM &vm, Instruction &inst) {
    auto rs1 = inst.Rs1();
    auto rs2 = inst.Rs2();
    auto rd = inst.Rd();
    auto imms = inst.ImmS();

    auto vmRs1 = vm.RegRead(rs1);
    auto vmRs2 = vm.RegRead(rs2);

    auto destAddr = vmRs1 + imms;
    vm.MemWrite(destAddr, &imms, 32);
}

void ExecutionStrategy::Execute() {
    int32_t pc = this->vm.RegRead(RegisterName::pc);
    Instruction inst = Instruction(pc);

    for (auto &entry: instructionSet) {
        if (entry.opcode == inst.Opcode() &&
            entry.func3 == inst.Func3() &&
            entry.func7 == inst.Func7()) {
            entry.execFunc(vm, inst);
            break;
        }
    }

    // Restore x0
    this->vm.RegWrite(RegisterName::zero, 0);

    // PC unchanged, advance normally
    int32_t newPc = this->vm.RegRead(RegisterName::pc);
    if (newPc == pc) {
        this->vm.RegWrite(RegisterName::pc, pc + 4);
    }
}

void ExecutionStrategy::InitializeVM() {
    this->vm.regfile.resize(33);
}