# Teensy 4.1
- IMXRT1062, same as IMXRT1060
- ARM Cortex-M7 ARMv7E-M, differences to ARMv7-M:
  - DSP Instructions for math-intensive algorithms.
  - Coprocessor interface, which is not clear how the Teensy 4.1 makes use of this.
  - NVIC for better interrupts.
  - WIC for I/O pin interrupts.
  - Memory Protection for safer memory read/write/execute.
  - Bit-Banding, access for individual bits directly. Supposedly speeds up single bit manipulation.
  - Single Cycle I/O for many things, but realisticly it takes 4 or more cycles for anything outside of DTCM.

The DSP instructions that are made available are useful for audio and video processing, though the 600Mhz default clock speed without cooling does put a slight stop to it. With passive or active cooling it is supposedly possible to reach 1Ghz, and even up to 1.2Ghz. However since the chip becomes unstable above 60°C, it is not really feasible to go beyond 800Mhz, which is the last "officially supported" cpu frequency.
