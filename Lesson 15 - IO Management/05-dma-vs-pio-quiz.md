# Quiz 5: DMA vs PIO

For a hypothetical system, assume the following:

- It costs one cycle to run a **store instruction** to a **device register**
- It costs five cycles to configure a **DMA controller**
- The PCI-bus is eight bytes wide
- All devices support both **DMA** and **PIO** access

Which **device access method** is best for the following devices?

- Keyboard
- NIC

A: The answer is as follows,

- Keyboard: PIO
- NIC: depends
