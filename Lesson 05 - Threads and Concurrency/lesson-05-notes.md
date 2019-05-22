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
