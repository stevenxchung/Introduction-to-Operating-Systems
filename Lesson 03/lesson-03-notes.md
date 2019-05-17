# Lesson 3: Introduction to Operating Systems

- Topics to be covered in this lesson:
  - What is an OS (operating system)?
  - What are key components of an OS?
  - Design and implementation considerations of OSs

## What is an Operating System?

- An OS is a special piece of software that abstracts and arbitrates the use of a computer system
- An OS is like a toy shop manager in that an OS:
  - Directs operational resources
  - Enforces working policies
  - Mitigates difficulty of complex tasks
- By definition, an OS is a layer of systems software that:
  - Directly has privileged access to the underlying hardware
  - Hides the hardware complexity
  - Manages hardware on behalf of one of more applications according to some predefined polices
  - In addition, it ensures that applications are isolated and protected from one another

## OS Elements

- Abstractions:
  - Process, thread, file, socket, memory page
- Mechanisms
  - Create, schedule, open, write, allocate
- Policies
  - Least recently used (LRU), earliest deadline first (EDF)

## Design Principles

- Separation of mechanisms to policy:
  - Implement flexible mechanisms to support many policies
- Optimize for common case:
  - Where will the OS be used?
  - What will the user want to execute on that machine?
  - What are the workload requirements?

## OS Protection Boundary

- Generally, applications operate in unprivileged mode (user level) while operating systems operate in privileged mode (kernel level)
- Kernel level software is able to access hardware directly
- User-kernel switch is supported by hardware

## Crossing The OS Boundary

- Applications will need to utilize user-kernel transitions which is accomplished by hardware, this involves a number of instructions and switches locality
- Switching locality will affect hardware cache (transitions are costly)
- Hardware will set *traps* on illegal instructions or memory accesses requiring special privilege