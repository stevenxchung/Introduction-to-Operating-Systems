# Quiz 1: Virtual Address

If two processes, *P1* and *P2*, are running at the same time, what are the **virtual address space** ranges they will have?

- Option 1:
  - *P1*: 0-32000
  - *P2*: 32001-64000
- Option 2:
  - *P1*: 0-64000
  - *P2*: 0-64000
- Option 3:
  - *P1*: 32001-64000
  - *P2*: 0-32000

A: Option 2 is the only valid answer since we have decoupled the virtual addresses that are used by the processes from the physical address where data actually is makes it possible for different processes to have the exact same address space range and to use the exact same addresses.
