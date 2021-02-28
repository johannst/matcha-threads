# ARM (aapcs32)
Provide an implementation of the platform specific API as required in
[`api.h`](../api.h) according to the `ARM Procedure Call Standard (aapcs32)`.

## Notes: Procedure Call Standard ARM (aapcs32)
- Integer/pointer arguments via `r0`-`r3`
- Integer/pointer return values via `r0`
- Callee saved registers `r4`-`r11`, `sp`

## References
- [johannst armv7 notes](https://johannst.github.io/notes/arch/armv7.html)
- [Procedure Call Standard aapcs32](https://github.com/ARM-software/abi-aa/blob/master/aapcs32/aapcs32.rst)
