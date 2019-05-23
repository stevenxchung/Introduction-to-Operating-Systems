# Lesson 5: Threads and Concurrency

- Topics to be covered in this lesson:
  - What are threads?
  - How do threads differ from processes?
  - What data structures are used to implement and manage threads?

## What is a Thread?

- What is a thread?
  - A **thread** is like a **worker in a toy shop** in that a thread:
    - Is an active entity (e.g., executing unit of a process)
    - Works simultaneously with others (e.g., many threads executing)
    - Requires coordination (e.g., sharing of I/O devices, CPUs, memory, etc.)

## Process vs Thread

- A single thread of process is represented by its address space
- Threads represent multiple, independent execution contexts
- Threads are part of the same virtual address space all threads share all of the virtual to physical address mappings as well as the code, data, and files
- Key differences:
  - However, threads will potentially execute different instructions, access different portions of that address space, operating on different portions of the input and differ in other ways
  - Each thread will need to have a different program counter, stack pointer, stack, thread-specific registers
  - Implication: for each thread we must have separate data structures to represent this per-thread information; consequently, the OS has a more complex PCB structure than a process

## Why are threads useful?

- Threads can implement **parallelization** which can process the input much faster than if only a single thread on a single CPU had to process say, an entire matrix for example
- Threads may execute completely different portions of the program
- Threads can also utilize **specialization** which takes advantage of the hot cache present on each thread
- A multi-threaded application is more memory efficient and has lower memory requirements than its multi-processor alternative
- Additionally, a multi-threaded application incurs lower overheads for their inter-thread communication then the corresponding inter-process alternatives

## Basic Thread Mechanisms

- **Thread data structure** - identify threads, keep track of resource usage, etc.
- Mechanisms to **create** and **manage** threads
- Mechanisms to safely **coordinate** among threads running **concurrently** in the same address space
- Processes:
  - Operate within their own address space
  - OS and hardware makes sure that no access from one address space is allowed to be performed on memory that belongs to another
- Threads:
  - Share the same virtual-to-physical address mappings
  - Can access the same data at the same time (concurrency issue)
- To address concurrency issues we use **synchronization mechanisms**:
  - **Mutual exclusion**:
    - Exclusive access to only on thread at a time
    - **Mutex** (mutual exclusion object) - a program object that is created so that multiple program threads can take turns sharing the same resource
  - **Waiting** on other threads:
    - Specific condition before proceeding
    - **Condition variable** - a container of threads that are waiting for a certain condition
  - Waking up other threads from wait state

## Thread Creation

- There are three main steps in thread creation process:
  - **Thread type**:
    - Thread data structure
  - **Fork (proc, args)**:
    - Create a thread
    - Not UNIX fork
  - **Join (thread)**:
    - Terminate a thread

## Mutual Exclusion

- **Mutex** - a lock that should be used whenever accessing data or state that's shared among threads
- When a thread locks a mutex (also termed acquiring the mutex) it has exclusive access to a resource until the thread decides to unlock the mutex
- A mutex has the following information:
  - Is the mutex locked?
  - Which thread owns the mutex?
  - Which threads are blocked?
- **Critical section** - portion of the code protected by the mutex

## Condition Variable

- Condition variables can be used in conjuction with mutexes to control the behavior of concurrent threads
- In the consumer and producer example in lecture, there is a condition where both consumer and producer checks if lists is/is not full, move foward
  - We combat this wait condition with a condition variable which **releases** the mutex to allow for producers to finish filling up the list and then **acquires** the mutex after the `Wait()` statement is finished

## Condition Variable API

- A condition variable API conists of the following:
  - **Condition** type
  - **Wait (mutex, condition)**:
    - Mutex is automatically released and re-acquired on wait
  - **Signal (condition)**:
    - Notify one thread waiting on condition
  - **Broadcast (condition)**:
    - Notify all waiting threads

## Common Pitfalls

- Keep track of mutex/condition variables used with a resource:
  - e.g., mutex*type \_m1*; // mutex for file1
- Check that that you are always (and correctly) using lock and unlock:
  - e.g., did you forget to lock/unlock? What about compilers?
- Use a single mutex to access a single resource!
  - We do not want reads and writes to happen concurrently!
- Check that you are signaling correct condition
- Check that you are not using signal when broadcast is needed:
  - Signal - only one thread will proceed, remaining threads will continue to wait, possibly indefinitely!
- Ask yourself: do you need priority guarantees?
  - Thread execution order not controlled by signals to condition variables!
- Other pitfalls include:
  - Spurious wake-ups
  - Deadlocks

## Spurious Wake-ups

- Spurious wake-ups occur when cycles are wasted via context switching threads to run on the CPU and then back again to wait on the wait queue
- When you unlock a mutex after broadcast/signal, no other thread can get lock
- Solution: broadcast/signal after mutex is unlocked, this only works in some cases however (write to file)

## Deadlocks

- Deadlocks occur when two or more competing threads are waiting on each other to complete but none of them ever do
- Solution: a good general solution is to maintain lock order, e.g., first _m_a_ then _m_b_

## Kernel vs User level Threads

- Kernel level:
  - Kernel level threads imply that the OS itself is multi-threaded
  - Kernel threads are managed bny kernel level components like the kernel level scheduler (the OS scheduler will decide how kernel level threads will be mapped onto the physical CPUs and which one of the threads will execute)
- User level:
  - The processes are multi-threaded
  - For a user level thread to execute it must be associated with a kernel level thread and the OS level scheduler must schedule that kernel level thread onto a CPU
- What is the relationship between a kernel level thread and a user level thread?

## Multi-threading models

- **One-to-one model**:
  - Pros:
    - OS sees/understands threads, synchronization, blocking, etc.
  - Cons:
    - Must go to OS for all operations (may be expensive)
    - OS may have limits on policies, thread number
    - Portability
- **Many-to-one model**:
  - Pros:
    - Totally portable, does not depend on OS limits and polices
  - Cons:
    - OS has no insights into application needs
    - OS may block entire process if one user level thread blocks on I/O
- **Many-to-many model**:
  - Pros:
    - Can be best of both worlds
    - Can have bound or unbound threads
  - Cons:
    - Requires coordination between user and kernel level thread managers

## Scope of Multi-threading

- **Process scope**:
  - User level library manages threads within a single process
- **System scope**:
  - System-wide thread management by OS level thread managers (e.g., CPU scheduler)

## Multi-threading Patterns

- **Boss-workers**:
  - Boss: assigns work to workers
  - Worker: performs entire tasks
  - Scenario 1: boss assigns work by directly signaling specific worker
    - Pros:
      - Workers don't need to synchronize
    - Cons:
      - Boss must track what each worker is doing
      - Throughput will do down!
  - Scenario 2: boss assigns work in producer/consumer queue
    - Pros:
      - Boss does not need to know details about workers
    - Cons:
      - Queue synchronization
  - Scenario 3: worker pool (static or dynamic)
    - Pros:
      - Simplicity
    - Cons:
      - Thread pool management
      - Locality
- **Boss-workers variants**:
  - All workers created equal versus workers specialized for certain tasks
  - Pros:
    - Better locality
    - Quality of service management
  - Cons:
    - Load balancing
- **Pipeline pattern**:
  - Threads assigned one subtask in the system
  - Entire tasks are pipeline of threads
  - Multiple tasks concurrently in the system, in different pipeline stages
  - Throughput is the longest stage in the pipeline (weakest link) in the pipeline
  - Pipeline stages can be managed via thread pool
  - The best way to pass work is through a shared-buffer based communication between stages
  - Pros:
    - Specialization and locality
  - Cons:
    - Balancing and synchronization overheadss
- **Layered pattern**:
  - Each layer group of related subtasks
  - End-to-end task must pass up and down through all layers
  - Pros:
    - Specialization
    - Less fine-grained than pipeline
  - Cons:
    - Not suitable for all applications
    - Synchronization
