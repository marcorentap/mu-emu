# mu-emu
μ-emu, a small RISC-V emulator supporting the RV32I instruction set, excluding EBREAK, ECALL and CSRs. Might extend to support x86 in the future.

![image](https://github.com/marcorentap/mu-emu/assets/17574533/659760b0-febc-4adb-91df-2cd88607972b)

Figure 1: A small emu

# Roadmap
The idea is to convert this emulator into a simple virtual platform to do low-level programming. I'm envisioning writing a bootloader, OS, compilers, etc. and being able to run them.
- Rewrite in C++, refactor to separate the core from displays [[cpp-rewrite](https://github.com/marcorentap/mu-emu/tree/cpp-rewrite)]
- Add TUI with disassembly view for step-by-step execution
- Add text-mode monitor
- ...
