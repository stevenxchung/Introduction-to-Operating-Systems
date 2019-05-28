# Lesson 8: Thread Design Considerations

- Topics to be covered in this lesson:
  - Kernel vs user-level threads
  - Threads and interrupts
  - Threads and signal handling

## Kernel vs User-level Threads

- **User-level library**:
  - Provides thread abstraction scheduling, sync
- **OS kernel**:
  - Maintains thread abstraction scheduling, sync

## Thread Data Structures: Single CPU

- **ULT (user-level thread)**:
  - User-level thread ID
  - User-level refs
  - Thread stack
- **PCB**:
  - Virtual address mapping
- **KLT (kernel-level thread)**:
  - Stack
  - Registers

## Thread Data Structures: At Scale

- When running multiple processes:
  - We need copies of KLT, PCB, and KLT structures
  - We will need to have a relationship between ULT, PCB, and KLT to what is the address space within which that thread executes
  - For a system with multiple CPUs we will need to have another data structure to represent the CPU as well as a relationship between the KLTs and the CPU
- When the kernel is multi-threaded:
  - We can have multiple kernel-level threads supporting a single user-level process
  - When kernel needs to context switch among KLTs that belong to different processes, it can quickly determined that they point to a different PCB

## Hard and Light Process State

- When two KLTs belong to the same address space:
  - Information in the PCB are split into a _hard_ and _light_ process state
  - **Hard process state** - relevant for all of the ULTs that execute within that process
  - **Light process state** - relevant for a subset of the ULTs that are currently associated with a particular KLT

## Rationale for Data Structures

- **Single PCB**:
  - Large continuous data structure
  - Private for each entity
  - Saved and restored on each context switch
  - Update for any changes
- **Multiple data structures**:
  - Smaller data structures
  - Easier to share
  - On context switch only save and restore what needs to change
  - User-level library need only update portion of the state
- In general, pivoting to multiple data structures improves scalability, overheads, performance, and flexibility
- Modern OS adopt multiple data structures for organizing information about their execution contexts

## Basic Thead Management Interactions

- Problem:
  - User-level library does not know what is happening in the kernel
  - Kernel does not know what is happening in the user-level library
- Solution:
  - System calls and special signals allow kernel and ULT to interact and coordinate (as shown in Solaris 2.0 demo in lecture)

## Thread Management Visibility and Design

- Problem:
  - Visibility of state and decisions between kernel and user-level library
- **User-level library** sees:
  - ULTs
  - Available KLTs
- **Kernel** sees:
  - KLTs
  - CPUs
  - Kernel-level scheduler
- Invisible to kernel:
  - Mutex variable
  - Wait queues
- Additionally there are many to many:
  - User-level scheduling decisions
  - Change ULT-KLT mapping
- One way to address visibility issue is to use one-to-one models
- How/when does the user-level library run?
  - Process jump to user-level libary scheduler when:
    - ULTs explicitly yield
    - Timer set by user-level library expires
    - ULTs call library functions like lock/unlock
    - Blocked threads become runnable
  - User-level library scheduler:
    - Runs on ULT operations
    - Runs on signals from timer

## Issues on Multple CPUs

- Problem:
  - Have ULTs split running on multiple CPUs, how to get CPUs to communicate?
- Solution:
  - On the kernel level, need to send signal to other KLT on the other CPU to run library code locally

## Synchronization-related Issues

- Problem:
  - Have ULTs split running on multiple CPUs, how to get CPUs to synchronize?
- Solution:
  - Use **adaptive mutexes**:
    - If critical section short do not block, spin instead!
    - For long critical sections we resort to default blocking behavior
- Destroying threads:
  - Instead of destroying, we should reuse threads
  - When a thread exits:
    - Put on **death row**
    - Periodically destroyed by **reaper thread**
    - Otherwise thread structures/stacks are reused (performance gains!)

## Interrupts vs Signals

- **Interrupts**:
  - Events generated externally by components other than the CPU (I/O devices, timers, other CPUs)
  - Determined based on the physical platform
  - Appear asynchronously
- **Signals**:
  - Events triggered by the CPU and software running on it
  - Determined based on the operating system
  - Appear synchronously or asynchronously
- **Interrupts and Signals**:
  - Have a unique ID depending on the hardware or OS
  - Can be masked and disabled/suspended via corresponding mask
    - Per-CPU interrupt mask, per-process signal mask
  - If enabled, trigger corresponding handler
    - Interrupt handler set for entire system by OS
    - Signal handlers set on per process basis, by process

## Interrupt Handling

- Recall that interrupts are generated externally
- When a device sends an interrupt to the CPU it is basically sending a signal through the interconnect that connects the device to the CPU complex
- For most modern devices there is an MSI (message signal interrupter) message that can be carried on the same interconnect that connects the devices to the CPU complex
- Based on the MSI message, the interrupt can be uniquely identified through a interrupt handler table

## Signal Handling

- Recall that signals are generated internally
- If a thread decides to access illegal memory, a signal (`SIGSEGV`) will be generated from the OS
- The OS maintains a signal handler table for every process in the system
- A process may specify how a signal should be handled, this is because the OS actually specifies some default actions for handling signals
- **Handlers/actions** (default actions):
  - Terminate
  - Ignore
  - Terminate and core dump
  - Stop or continue
- **Synchronous**:
  - `SIGSEGV` (access to protected memory)
  - `SIGFPE` (divide by zero)
  - `SIGKILL` (kill, id) can be directed to s specific thread
- **Asynchronous**:
  - `SIGKILL` (kill)
  - `SIGALARM`

## Why Disable Interrupts or Signals?

- Problem:
  - Interrupts and signals are handled on the thread stack which can cause handler code to deadlock
- Solution:
  - Control interruptions by handler code (user interrupt/signal masks)
- A **mask** is a sequence of bits where each bit corresponds to a specific interrupt or signal and the value of the bit, zero or one, will indicate whether the specific interrupter signal is disabled or enabled

## More on Masks

- **Interrupt masks** are per CPU:
  - If mask disables interrupt, hardware interrupt routing mechanism will not deliver interrupt to CPU
- **Signal masks** are per execution context (ULT on top of KLT) if mask disables signal, kernel sees mask and will not interrupt corresponding thread

## Interrupts on Multi-core systems

- Interrupts can be directed to any CPU that has them enabled
- May set interrupt on just a single core
  - Avoids overheads and perturbations on all other cores

## Types of Signals

- **One-shot signals**:
  - `n_signals_pending == one_signal_pending` at least once
  - Must be explicitly re-enabled
- **Real-time signals**:
  - _If n signals raised, then handler is called n times_

## Interrupts as Threads

- Problem:
  - Deadlocks can happen for signal handling routines
- Solution:
  - As mentioned in the SunOS paper, we can allow interrupts to become full-fledged threads every time interrupts are performing blocking operations
- However, dynamic thread creation is expensive!
  - **Dynamic decision**:
    - If handler doesn't lock, execute on interrupted thread's stack
    - If handler can block, turn into real thread
  - **Optimization**:
    - Pre-create and pre-initialize thread structures for interrupt routines

## Interrupts: Top vs Bottom Half

- Interrupts as threads can be handled in two ways (see diagram from lecture):
  - **Top half**:
    - Fast, non-blocking
    - Min amount of processing
  - **Bottom half**:
    - Arbitrary
    - Complexity
- Bottom line:
  - To permit arbitrary functionality to be incorporated into the interrupt-handling operations, the handling routine must be executed by another thread where synchronization and blocking is a possibility

## Performance of Threads as Interrupts

- **Overall cost**:
  - Overhead of 40 SPARC instructions per interupt
  - Saving of 12 instructions per mutex
    - No changes in interrupt mask, level, etc.
  - Fewer interrupts than mutex lock/unlock operations
- To summarize, optimize for the common case!

## Task Structure in Linux

- Main execution abstraction: task
  - KLT
- Single-threaded process: one task
- Multi-threaded process: many tasks
- **Task creation** - use `clone` command
- **Linux threads model**:
  - NPTL (Native POSIX Threads Library) - *one-to-one model*:
    - Kernel sees each ULT info
    - Kernel traps are cheaper
    - More resources: memory, large range of IDs, etc.
  - Order Linux Threads - *many-to-many model*:
    - Similar issues to those described in Solaris papers
