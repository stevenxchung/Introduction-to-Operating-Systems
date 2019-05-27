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
