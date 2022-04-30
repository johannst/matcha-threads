# riscv64 (RISC-V ELF)
Provide an implementation of the platform specific API as required in
[`api.h`](../api.h) according to the `RISC-V ELF ABI`.

## Notes: RISC-V ABI
- Integer/pointer arguments via `x10` - `x17`
- Integer/pointer return values via `x10` - `x11`
- Callee saved registers `x2`, `x8` - `x9`, `x18` - `x27`, `f8` - `f9`, `f18` - `f27`

## References
- [johannst riscv notes](https://johannst.github.io/notes/arch/riscv.html)
- [RISC-V ABI](https://github.com/riscv/riscv-elf-psabi-doc/blob/master/riscv-elf.md)
- [RISC-V asm manual](https://github.com/riscv/riscv-asm-manual/blob/master/riscv-asm.md)
