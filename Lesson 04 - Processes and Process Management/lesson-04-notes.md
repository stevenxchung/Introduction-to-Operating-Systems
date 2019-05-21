# Lesson 4: Processes and Process Management

- Topics to be covered in this lesson:
  - What is a process?
  - How are processes represented by OS's?
  - How are multiple concurrent processes managed by OS's?

## What is a Process?

- What is a process?
  - A **process** is like **an order of toys** in that a process:
    - Has a state of execution (e.g., program counter, stack)
    - Has parts and temporary holding area (e.g., data, register state occupies state in memory)
    - May require special hardware (e.g., I/O devices)
- OS manages hardware on behalf of applications
- **Application** - program on disk, flash memory (static entity)
- **Process** - state of a program when executing loaded in memory (active entity)

## What does a Process look like?

- A process encapsulates all data of a running application
- Every single element of the process state has to be uniquely identified by its address (OS abstraction used to encapsulate the process state is an address space)
- Some types of state include:
  - Text and data (static state when process first loads)
  - Heap - dynamically created during execution
  - Stack - grows and strinks (has LIFO queue)

## Process Address Space

- **Address space** - *in memory* representation of a process
- **Page tables** - mapping of virtual to physical addresses
- **Physical address** - locations in physical memory

## Address Space and Memory Management

- Parts of virtual address space may not be allocated
- May not be enough physical memory for all state
- Solution: the operating system dynamically decides which portion of which address space will be present where in physical memory

## Process Execution State

- How does the OS know what a process is doing?
  - The **program counter** allows the OS to know where a process currently is in the instruction sequence
  - The program counter is maintained on a **CPU register** while the process is executing
  - There also exists a **stack pointer** which points to the top of the stack (useful for LIFO operations)
  - To maintain all of the above, the OS maintains a **PCB** (process control block)

## Process Control Block

- What is a PCB?
  - A PCB (process control block) is a data structure that the OS maintains for every one of the processes that it manages
  - A PCB is created when process is created
- Certain fields are updated when process state changes
- Other fields change too frequently

## Context Switch

- **Context switch** - switching the CPU from the context of one process to the context of another
- Context switching is expensive!
  - **Direct costs** - number of cycles for load to store instructions
  - **Indirect costs** - COLD cache! Cache misses!
  - Ultimately, we want to limit how frequently context switching is done!

## Process Life Cycle: States

- Processes can be **running** or **idle**
- Process states can be: new, ready, running, waiting, or terminated

## Process Life Cycle: Creation

- Two mechanisms for process creation:
  - **Fork**:
    - Copies the parent PCB into new child PCB
    - Child continues execution at instruction after fork
  - **Exec**:
    - Replace child image
    - Load new program and start from first instruction