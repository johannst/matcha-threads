# ARM64 (aapcs64)
Provide an implementation of the platform specific API as required in
[`api.h`](../api.h) according to the `ARM64 Procedure Call Standard (aapcs64)`.

## Notes: Procedure Call Standard ARM64 (aapcs64)
- Integer/pointer arguments via `x0`-`x7`
- Integer/pointer return values via `x0`
- Callee saved registers `x19`-`x28`, `sp`

## References
- [johannst arm64 notes](https://johannst.github.io/notes/arch/arm64.html)
- [Procedure Call Standard aapcs64](https://github.com/ARM-software/abi-aa/blob/master/aapcs64/aapcs64.rst)
