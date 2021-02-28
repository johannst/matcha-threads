# x86_64 (SystemV)
Provide an implementation of the platform specific API as required in
[`api.h`](../api.h) according to the `x86_64 SystemV ABI`.

## Notes: SystemV ABI
- Integer/pointer arguments via `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`
- Integer/pointer return values via `rax`
- Callee saved registers `rbx`, `rbp`, `r12` – `r15`

## References
- [johannst x86_64 notes](https://johannst.github.io/notes/arch/x86_64.html)
- [x86_64 SystemV ABI](https://www.uclibc.org/docs/psABI-x86_64.pdf)
