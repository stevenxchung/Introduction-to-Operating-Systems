# Problem 3: Hardware Counters

Consider a quad-core machine with a single memory module connected to the CPU's via a shared _bus_. On this machine, a CPU instruction takes 1 cycle, and a memory instruction takes 4 cycles.

The machine has two hardware counters:

- Counter that measures IPC
- Counter that measures CPI

Answer the following:

1. What does IPC stand for in this context?
2. What does CPI stand for in this context?
3. What is the highest IPC on this machine?
4. What is the highest CPI on this machine?

A: The answers are as follows,

1. IPC (instructions per cycle)
2. CPI (cycles per instruction)
3. Since it is a quad-cord machine the highest IPC is 4
4. Since a memory instruction takes 4 cycles, the highest CPI is 16 if each core issues a memory instruction (contention)
