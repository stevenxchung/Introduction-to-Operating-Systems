# Introduction to Operating Systems

Course taught by Dr. Ada Gavrilovska and offered by Georgia Tech on Udacity.

## Course topics

- Processes and process management
- Threads and concurrency
- Resource management:
  - Scheduling
  - Memory management
- OS services for communication and I/O
- OS support for distributed services
- System software for data center and cloud environments

# Lesson 1: Course Readiness Survey

_No notes from this lesson_

# Lesson 2: Course Overview

_No notes from this lesson_

# Lesson 3: Introduction to Operating Systems

- Topics to be covered in this lesson:
  - What is an OS (operating system)?
  - What are key components of an OS?
  - Design and implementation considerations of OSs

## What is an Operating System?

- An OS is a special piece of software that abstracts and arbitrates the use of a computer system
- An **OS** is like **a toy shop manager** in that an OS:
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
- Hardware will set _traps_ on illegal instructions or memory accesses requiring special privilege

## Monolithic OS

- Pros:
  - Everything included
  - Inlining, compile-time optimizations
- Cons:
  - Customization, portability, manageability
  - Memory footprint
  - Performance

## Modular OS

- Pros:
  - Maintainability
  - Smaller footprint
  - Less resource needs
- Cons:
  - Indirection can impact performance
  - Maintenance can still be an issue

## Microkernel

- Pros:
  - Size
  - Verifiability
- Cons:
  - Portability
  - Complexity of software development
  - Cost of user/kernel crossing

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

- **Address space** - _in memory_ representation of a process
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

## Role of the CPU Scheduler

- A **CPU Scheduler** determines which one of the currently ready processes will be dispatched to the CPU to start running, and how long it should run for
- In general, the OS must be efficient:
  - **Preempt** - interrupt and save current context
  - **Schedule** - run scheduler to choose next process
  - **Dispatch** - dispatch process to switch into its context

## Length of Process

- Useful CPU work can be determined by the following: `total processing time / total time`
- In general, total scheduling time should be considered overhead, we want most of the CPU time to be spent doing useful work
- **Time-slice** - time allocated to a process on the CPU

### Inter Process Communication

- An OS must provide mechanisms to allow processes to interact with one another
- **IPC mechanisms**:
  - Help transfer data/info between address spaces
  - Maintain protection and isolation
  - Provide flexibility and performance
- **Message-passing IPC**:
  - OS provides communication channel liked shared buffer
  - Processes write (send)/read (receive) messages to/from channel
  - Pros: OS manages
  - Cons: overheads
- **Shared Memory IPC**:
  - OS establishes a shared channel and maps it into each process address space
  - Processes directly read/write from this memory
  - Pros: OS is out of the way!
  - Cons: may need to re-implement code

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

# Lesson 6: Thread Case Study - PThreads

- Topics to be covered in this lesson:
  - What are PThreads?
    - POSIX Threads
  - What is POSIX?
    - POSIX stands for Portable Operating System Interface
- **POSIX Threads**:
  - POSIX versions of Birrell's API
  - Specifies syntax and semantics of the operations

## PThread Creation

- PThread creation is similar to thread abstraction proposed by Birrell:

| Birrell's Mechanisms | PThreads                     |
| -------------------- | ---------------------------- |
| `Thread`             | `pthread_t` (type of thread) |
| `Fork()`             | `pthread_create()`           |
| `Join()`             | `pthread_join()`             |

- `pthread_attr_t`:

  - Specified in `pthread_create`
  - Defines features of the new thread
  - Has default behavior with NULL in `pthread_create`

- **Detaching PThreads**:
  - Mechanism not considered by Birrell
  - Default: joinable threads
    - Parent thread creates children threads and joins them at a later time
    - The parent thread should not terminate until the children threads have completed their executions and have been joined via the explicit join operation
    - If parent threads exits early, children threads can become _zombies_
  - **Detached threads**:
    - There is a possibility for children threads to be detached from the parent
    - Once detached, threads cannot join
    - If a parent exits, children threads are free to continue their execution
    - Parent and children are equivalent to one another

## Compiling Threads

- Ensure to include the PThread header file, `pthread.h`, in your main file that contains the PThreads code, otherwise the program will not compile
- Compile source with `-lpthread` or `-pthread`
- Check the return values of common functions

## PThread Mutexes

- PThread mutexes were designed to solve mutual exclusion problems among concurrent threads
- Below is a comparison of Birrell's mechanisms and PThreads for mutexes:

| Birrell's Mechanisms      | PThreads                                   |
| ------------------------- | ------------------------------------------ |
| `Mutex`                   | `pthread_mutex_t` (mutex type)             |
| `Lock()` (to lock)        | `pthread_mutex_lock()` (explicit lock)     |
| `Lock()` (also to unlock) | `pthread_mutex_unlock()` (explicit unlock) |

- **Mutex safety tips**:
  - Shared data should always be accessed through a single mutex!
  - Mutex scope must be visible to all!
  - Globally order locks
    - For all threads, lock mutexes in order
  - Always unlock a mutex
    - Always unlock the correct mutex

## PThread Condition Variables

- Below is a comparison of Birrell's mechanisms and PThreads for condition variables:

| Birrell's Mechanisms           | PThreads                                 |
| ------------------------------ | ---------------------------------------- |
| `Condition`                    | `pthread_cond_t` (type of cond variable) |
| `Wait()` (to lock)             | `pthread_cond_wait()`                    |
| `Signal()` (also to unlock)    | `pthread_cond_signal()`                  |
| `Broadcast()` (also to unlock) | `pthread_cond_broadcast()`               |

- There are also other condition variables such as `pthread_cond_init()` and `pthread_cond_destroy()`
- **Condition variable safety tips**:
  - Do not forget to notify waiting threads!
    - Predicate change => signal/broadcast correct condition variable
  - When in doubt broadcast
    - However, broadcast too often will result in **performance loss**
  - You do not need a mutex to signal/broadcast (it may be necessary to wait until mutex is removed before signaling/broadcasting)

# Lesson 7: Problem Set 1

_No notes from this lesson_

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
  - NPTL (Native POSIX Threads Library) - _one-to-one model_:
    - Kernel sees each ULT info
    - Kernel traps are cheaper
    - More resources: memory, large range of IDs, etc.
  - Order Linux Threads - _many-to-many model_:
    - Similar issues to those described in Solaris papers

# Lesson 9: Thread Performance Considerations

- Topics to be covered in this lesson:
  - Performance comparisons:
    - Multi-process vs multi-threaded vs event-driven
  - Event-driven architectures
    - "Flash: An Efficient and Portable Web Server" vs Apache

## Which Threading Modeling is Better?

- Consider the _Boss-worker_ vs _Pipeline_ example as discussed in lesson 5 (see lecture for specific initial conditions):
  - We care about two metrics, execution time and average time to complete order
  - The _Boss-worker_ model has an execution time greater than that of the _Pipeline_ model (undesirable)
  - However, the _Boss-worker_ model has an average time to complete order less than that of the _Pipeline_ model (desirable)
  - Which model is better?
    - It really depends on the metrics!

## Are Threads Useful?

- Threads are useful because of:
  - Parallelization: speed up
  - Specialization: hot cache!
  - Efficiency: lower memory requirement and cheaper synchronization
- Threads hide latency of I/O operations (single CPU)
- Now consider what is useful...
  - For a matrix multiply application: execution time
  - For a web service application:
    - Number of client requests/time
    - Response time
  - For hardware: higher utilization (e.g., CPU)
- Again, it depends on the metrics!

## Visual Metaphor

- **Metrics** exist for OS and for toy shops (some examples below):
  - **Throughput**:
    - Process completion rate
  - **Response time**:
    - Average time to respond to input (e.g., mouse click)
  - **Utilization**:
    - Percentage of CPU

## Performance Metrics Intro

- Metrics are a measurement standard **measurable** and/or **quantifiable property** (e.g., execution time) of the **system** (software implementation of a problem) we're interested in that can be used to **evaluate the system behavior** (its improvement compared to other implementations)

## Performance Metrics

- What are some performance metrics computer scientists typically care about?
  - Previously covered metrics:
    - Execution time
    - Throughput
    - Request rate
    - CPU utilization
  - Other metrics one might care about:
    - Wait time
    - Platform efficiency
    - Performance/cost
    - Performance/power
    - Percentage of SLA violations
    - Client-perceived performance
    - Aggregate performance
    - Average resource usage

## Performance Metrics Summary

- Performance metrics are a **measurable quantity** obtained from:
  - Experiments with real software deployment, real machines, real workloads
  - _Toy_ experiments representative of realistic settings
  - Simulation: test-bed

## Really... Are Threads Useful?

- Depends on **metrics**!
- Depends on **workload**!
- Bottom line: it depends!

## Multi-process vs Multi-thread

- Consider how to best provide concurrency (see lecture for simple web server example):
  - **Multi-process web server**:
    - Pros: simple programming
    - Cons:
      - Many processes which means high memory usage costly context switch hard/costly to maintain shared state (tricky port setup)
  - **Multi-threaded web server**:
    - Pros:
      - Shared address space
      - Shared state
      - Cheap context switch
    - Cons:
      - Not simple implementation
      - Requires synchronization
      - Underlying support for threads

## Event-driven Model

- An event-driven model contains the following elements (see lecture for diagram):
  - **Event handlers**:
    - Accept connection
    - Read request
    - Send header
    - Read file/send data
  - **Dispatch loop**
  - **Events**:
    - Receipt of request
    - Completion of send
    - Completion of disk read
- An event driven model has a single address space, single process, and single thread of control!
- The **dispatcher** is in charge of state machine external events (call handler and jump to code)
- The **handler**:
  - Runs to completion
  - Facilitates blocking:
    - Initiate blocking operation and pass control to dispatch loop

## Concurrency in the Event-driven Model

- If the event-driven model operates on a single thread, how to achieve concurrency?
  - Single thread switches among processing of different requests
- **Multi-process and multi-threaded**:
  - One request per execution context (process/thread)
- **Event-driven**:
  - Many requests interleaved in an execution context

## Event-driven Model: Why

- Why does this work?
  - On one CPU, _threads hide latency_:
    - `if (t_idle > 2 * t_context_switch)`, context switch to hide latency
    - `if (t_idle == 0)`, context switching just wastes cycles that could have been used for request processing
- **Event-driven**:
  - Process request until wait necessary then switch to another request
- **Multiple CPUs**:
  - Multiple event-driven processes

## Event-driven Model: How

- How does this work?
  - **Event** is equal to input on FD (file descriptor)
- Which **file descriptor**?
  - `select()`
  - `poll()`
  - `epoll()`
- Benefits of event-driven model:
  - Single address space and single flow of control
  - Smaller memory requirement and no context switching
  - No synchronization

## Helper Threads and Processes

- Problem: for the event-driven model, a blocking request/handler will block the entire process
- Solution:
  - Use **asynchronous I/O operations**:
    - Process/thread makes system call
    - OS obtains all relevant into from stack and either learns where to return results, or tells caller where to get results later
    - Process/thread can continue
- However, an asynchronous system call requires support from kernel (e.g., threads) and/or device
- In general, asynchronous system calls fit nicely with the event-driven model!
- Another problem: what if async calls are not available?
  - Use **helpers**:
    - Designated for blocking I/O operations only
    - Pipe/socket based communication with event dispatcher
    - Helper blocks! But main event loop (and process) will not!
- Before, there were no multi-threaded solutions, therefore, a AMPED (Asymmetric Multi-process Event-driven Model) solution was created similar to that mentioned above
- With the addition of multi-threaded capabilities, the multi-threaded event-driven model discussed in previously became known as the AMTED (Asymmetric Multi-threaded Event-driven Model) solution
- In summary, helper threads/processes:
  - Pros:
    - Resolves portability limitations of basic event-driven model
    - Smaller footprint than regular worker thread
  - Cons:
    - Applicability to certain classes of applications
    - Event-driven routing on multi CPU systems

## Flash Web Server

- **Flash: event-driven web server**:
  - An **event-driven web server (AMPED)** with **asymmetric helper processes**
  - _Helpers_ used for disk reads
  - Pipes used for communication with dispatcher
  - Helper reads file in memory (via memory map)
  - Dispatcher checks (via mincore) if pages are in memory to decide _local handler_ or _helper_
- In general, a flash web server can offer possible big savings!
- **Flash: additional optimizations**:
  - Application-level caching (data and computation)
  - Alignment for DMA (direct memory access)
  - Use of DMA with scatter-gather, vector I/O operations
- Back in the day these optimizations would be novel, now they are fairly common

## Apache Web Server

- An Apache web server (diagram available in lecture slides) consists of the following elements:
  - **Core** - basic server skeleton
  - **Modules** - per functionality
  - **Flow of control** - similar to event-driven model
- However, an Apache web server differs in:
  - Combination of MP and MT:
    - Each process is equivalent to boss/worker with dynamic thread pool
    - Number of processes can also be dynamically adjusted

## Experimental Methodology

- To set up performance comparisons consider the following:
  - First, define the comparison points:
    - What systems are you comparing?
  - Second, define inputs:
    - What workloads will be used?
  - Third, define metrics:
    - How will you measure performance?

## Summary of Performance Results

- **When data is in cache**:
  - SPED (single-process event-driven) >> AMPED Flash:
    - Unnecessary test for memory presence
  - SPED and AMPED Flash >> MT/MP:
    - Sync and context switching overhead
- **Disk-bound workload**:
  - AMPED Flash >> SPED:
    - Blocks because no async I/O
  - AMPED Flash >> MT/MP:
    - More memory efficient and less context switching

## Advice on Designing Experiments

- **Design relevant experiments**: statements about a solution that others believe in and care for
- **Purpose of relevant experiments** (e.g., web server experiment):
  - Clients: response time
  - Operations: throughput
  - **Possible goals**:
    - Increase response time and throughput
    - Increase response time
    - Increase response time while decreasing throughput
    - Maintains response time when request rate increases
  - **Goals**: metrics and configuration of experiments
- _Rule of thumb_ for picking **metrics**:
  - Standard **metrics** equals broader audience
  - **Metrics** answering the _"Who? What? Why?"_ questions:
    - Client performance: response time, timed-out request, etc.
    - Operator costs: throughput, costs, etc.
- **Picking the right configuration space**:
  - **System resources**:
    - Hardware and software
  - **Workload**:
    - Web server: request rate, number of concurrent requests, file size, access pattern
  - **Now pick!**:
    - Choose a subset of configuration parameters
    - Pick ranges for each variable factor
    - Pick relevant workload
    - Include the best/worst case scenarios
- **Are you comparing apples to apples?**:
  - Pick useful combination of factors, many just reiterate the same point
- **What about the competition and baseline?**:
  - Compare system to:
    - State-of-the-art
    - Most common practice
    - Ideal best/worst case scenario

## Advice on Running Experiments

- If you have designed the experiments you should consider:
  - Running test cases _n_ times
  - Compute metrics
  - Represent results
- Additionally, do not forget about making conclusions!

# Lesson 10: Sample Midterm Questions

_No notes from this lesson_

# Lesson 11: Scheduling

- Topics to be covered in this lesson:
  - Scheduling mechanisms, algorithms and data structures
  - Linux O(1) and CFS schedulers
  - Scheduling on multi-CPU platforms

## Visual Metaphor

- Like an **OS scheduler**, a **toy shop manager** schedules work:
  - Assign task immediately:
    - Scheduling is simple (first-come first-serve)
  - Assign simple tasks first:
    - Maximize throughput (shortest job first)
  - Assign complex tasks first:
    - Maximize utilization of CPU devices, memory, etc.

## CPU Scheduling

- The **CPU scheduler**:
  - Decides how and when **processes** (and their **threads**) access shared CPUs
  - Schedules tasks running **user-level processes/threads** as well as **KLTs**
  - Chooses one of ready **tasks** to run on CPU when:
    - CPU becomes idle
    - New **task** becomes ready
    - Time-slice expired timeout
  - **Thread** is dispatched on CPU
- Scheduling is equivalent to choosing a **task** from ready queue:
  - Which **task** should be selected?
    - Scheduling policy/algorithm
  - How is this done?
    - Depends on run-queue data structure (run-queue is the scheduling algorithm)

## Run To Completion Scheduling

- Initial assumptions:
  - Group of tasks/jobs
  - Known execution times
  - No preemption
  - Single CPU
- Metrics:
  - Throughput
  - Average job completion time
  - Average job wait time
  - CPU utilization
- First-come first-serve (FCFS):
  - Schedules tasks in order of arrival
  - Run-queue is the same as queue (FIFO)
- Shortest job first (SJF):
  - Schedules tasks in order of their execution time
  - Run-queue is the same as ordered queue or tree

## Preemptive Scheduling: SJF + Preempt

- **SJF + Preemption**:
  - _T2_ arrives first
  - _T2_ should be preempted
- **Heuristics based on history**: job running time
- How long did a task run last time?
- How long did a task run last _n_ times?

## Preemptive Scheduling: Priority

- **Priority scheduling**:
  - Tasks have different priority levels
  - Run highest priority tasks next (preemption)
  - Run-queue is equal to per priority queues, tree ordered based on priority, etc.
  - Low priority tasks stuck in a run-queue (starvation)
  - _Priority aging_ is where `priority = f(actual priority, time spend in run queue)`
  - Eventually task will run (prevents starvation!)

## Priority Inversion

- Assume SJF (see lecture for table and graph):
  - Priority: _T1_, _T2_, _T3_
  - Order of execution: _T2_, _T3_, _T1_ (priorities inverted)
  - Solution:
    - Temp boost priority of mutex owner
    - Lower again release

## Round Robin Scheduling

- Pick up first tasks from queue (like FCFS)
- Task may yield, to wait on I/O (unlike FCFS)
- Round robin with priorities:
  - Include preemption
- Round robin with interleaving:
  - Time-slicing

## Time-sharing and time-slices

- **Time-slice** - maximum amount of uninterrupted time given to a task (time quantum)
- Task may run less than time-slice time:
  - Has to wait for I/O, synchronization, etc. (will be placed on a queue)
  - Higher priority task becomes runnable
- Using time-slices tasks are interleaved (time-sharing the CPU):
  - CPU bound tasks (preempted after time-slice)
- Pros:
  - Short tasks finish sooner
  - More responsive
  - Lengthy I/O operations initiated sooner
- Cons:
  - Overheads (interrupt, schedule, context switch)

## Summarizing Time-slice Length

- How long should a time-slice be?
  - **CPU bound tasks prefer longer time-slices**:
    - Limits context switching overheads
    - Keeps CPU utilization and throughput high
  - **I/O bound tasks prefer shorter time-slices**:
    - I/O bound tasks can issue I/O operations earlier
    - Keeps CPU and device utilization high
    - Better used perceived performance

## Run-queue Data Structure

- If we want I/O and CPU bound tasks have different time-slice values, then...
  - Same run-queue, check type, etc.
  - Two different structures
- One solution: use a multi-queue data structure with separate internal queues
  - First time-slice is most I/O intensive (highest priority)
  - Second time-slice is medium I/O intensive (mix of I/O and CPU processing)
  - Third and beyond time-slice is CPU intensive (lowest priority)
  - Pros:
    - Time-slicing benefits provided for I/O bound tasks
    - Time-slicing overheads avoided for CPU bound tasks
- Handling different time-slice values:
  - Tasks enter top-most queue
  - If task yields voluntarily keep task at this level
  - If task uses up entire time-slice push down to lower level
  - Task in lower queue gets priority boost when releasing CPU due to I/O waits
- In summary, MLFQ (multi-level feedback queue) is not a priority queue (MLFQ has a feedback mechanism) and offer different treatment of threads at each level

## Linux O(1) Scheduler

- The Linux O(1) scheduler has several of unique characteristics:
  - The name **O(1)** means it takes constant time to select/add task, regardless of task count
  - **Preemptive, priority-based**:
    - Real time (0-99)
    - Time-sharing (100-139)
  - **User processes**:
    - Default 120
    - Nice value (-20 to 19)
- Time-slice value for the Linux O(1) scheduler:
  - Depends on priority
  - Smallest for low priority
  - Highest for high priority
- Feedback for the Linux O(1) scheduler:
  - Sleep time: waiting/idling
  - Longer sleep: interactive
  - Smaller sleep: compute-intensive
- Run-queue for Linux O(1) scheduler: two arrays of tasks...
  - Active:
    - Used to pick next task to run
    - Constant time to add/select
    - Tasks remain in queue in active array until time-slice expires
  - Expired:
    - Inactive list
    - When no more tasks in active array (swap active and expired)

## Linux CFS Scheduler

- Problems with Linux O(1) scheduler:
  - Performance of interactive tasks is not satisfactory
  - Lacks fairness during task prioritization
- Solution: Linux CFS (Completely Fair Scheduler)
  - CFS is the default scheduler since Linux 2.6.23
  - Run-queue is based on a red-black tree:
    - Ordered by `vruntime` where `vruntime` is time spent on CPU
- CFS scheduling works as follows:
  - Always pick left-most node
  - Periodically adjust `vruntime`
  - Compare to left-most `vruntime`:
    - If smaller, continue running
    - If larger, preempt and place appropriately in the tree
  - `vruntime` progress rate depends on priority and niceness:
    - Rate fast for low-priority
    - Rate slower for high-priority
    - Same tree for all priorities
  - Performance:
    - Select task: _O(1)_
    - Add task: _O(log(n))_

## Scheduling on Multi-processors

- **Cache-affinity** important!
  - Keeps tasks on the same CPU as much as possible
  - Hierarchical scheduler architecture
- **Per-CPU run-queue** and **scheduler**:
  - Load balance across CPUs based on queue length or when CPU is idle
- **NUMA (Non-uniform Memory Access)**:
  - Multiple memory nodes
  - Memory node closer to a _socket_ of multiple processors:
    - Access to local memory node faster than access to remote memory node
    - Keep tasks on CPU closer to memory node where their state is
    - NUMA-aware scheduling

## Hyper-threading

- Multiple hardware-supported execution contexts
- Still one CPU but with **very fast** context switch:
  - Hardware multi-threading
  - Hyper-threading
  - CMT (chip multi-threading)
  - CMT (simultaneous multi-threading)

## Scheduling for Hyper-threading

- **Assumptions**:
  - Thread issues instruction on each cycle (one max IPC or instruction per cycle)
  - Memory access (four cycles)
  - Hardware switching instantaneous
  - SMT with two hardware threads
- Threads _interfere_ and _contend_ for CPU pipeline resource:
  - Performance degrades
  - Memory degrades
- CPU idle: waste CPU cycles
- Mix of CPU and memory-intensive threads:
  - Avoid/limit contention on processor pipeline
  - All components (CPU and memory) well utilized
  - However, still leads to interference and degradation but minimal

## CPU-bound or Memory-bound?

- Use historic information:
  - _Sleep time_ won't work:
    - The thread is not sleeping when waiting on memory
    - Software takes too much time to compute
- What about hardware counters?
  - Hardware counters estimate what kind of resources a thread needs
  - Scheduler can make informed decisions:
    - Typically multiple counters
    - Models with per architecture thresholds
    - Based on well-understood workloads

## CPI Experiment Results

- Resource contention in _SMTs_ for process pipeline
- Hardware counters can be used to characterize workload
- Schedulers should be aware of resource contention, not just load balancing

# Lesson 12: Memory Management

- Topics to be covered in this lesson:
  - Physical and virtual memory management
  - Review of memory management mechanisms
  - Illustration of advanced services

## Visual Metaphor

- **OS** and **toy shops** each have **memory (part) management systems**:
  - Uses intelligently sized containers:
    - Memory pages or segments
  - Not all memory is needed at once:
    - Tasks operate on subset of memory
  - Optimized for performance:
    - Reduce time to access state in memory (better performance)

## Memory Management: Goals

- Virtual vs physical memory:
  - Allocate: Allocation, replacement, etc.
  - Arbitrate: Address translation and validation
- Page-based memory management:
  - Allocate: Pages to page frames
  - Arbitrate: Page tables
- Segment-based memory management:
  - Allocate: Segments
  - Arbitrate: segment registers

## Memory Management: Hardware Support

- MMU (memory management unit):
  - Translate **VA (virtual address)** to **PA (physical addresses)**
  - Reports faults: illegal access, permission not present in memory
- Registers:
  - Pointers to page table
  - Base and limit size, number of segments, etc.
- Cache - TLB (translation look-aside buffer):
  - Valid virtual address to physical address translations: TLB
- Translation:
  - Actual PA generation done in hardware

## Page Tables

- Virtual memory pages and physical memory page frames are the same size
- Useful acronyms for page tables:
  - VPN (virtual page number)
  - PFN (physical frame number)
- Page table has allocation on first touch!
- Unused pages are reclaimed:
  - Mapping invalid
  - Hardware will fault
  - Re-establish on re-access
- In summary, the OS creates a page table for every process:
  - On context switch, switch to valid page table
  - Update register

## Page Table Entry

- Flags:
  - Present (valid/invalid)
  - Dirty (written to)
  - Accessed (for read or write)
  - Protection bits (read, write, and execute)
- **Page fault**:
  - Two options for PFN:
    - Generate physical address and access
    - Generate error code on kernel stack (trap into kernel)
  - Page fault handler determines action based on error code and faulting address:
    - Bring page from disk to memory
    - Protection error (`SIGSEGV`)
    - Error code from PTE flags
    - Faulting address CR2 register

## Page Table Size

- **64-bit Architecture**:
  - PTE (Page Table Entry): 8 bytes including PFN + flags
  - VPN: 2^64 / page size
  - Page size: (2^64 / 2^12) \* 8 bytes = 32 petabytes per process
- **Process** does not use entire address space:
  - Even on 32-bit architecture will not always use all of 4 GB
  - But **page table** assumes an entry per **VPN**, regardless of whether corresponding virtual memory is needed or not

## Multi-level Page Tables

- **Outer page table**: page table directory
- **Internal page table**: only for valid virtual memory regions
- **Additional layers**:
  - Page table directory pointer (third level)
  - Page table directory point map (fourth level)
    - Important on 64-bit architectures
    - Larger and more sparse
    - Larger gaps could save more internal page table components
- **Multi-level page tables**:
  - Pros:
    - Smaller internal page tables/directories
    - Granularity of coverage (potential reduced page table size)
  - Cons:
    - More memory access required for translation (increased translation latency)

## Speeding Up Translation TLB

- Overhead of address translation:
  - Single-level page table:
    - 1x access to page table entry
    - 1x access to memory
  - Four-level page table:
    - 4x accesses to page table entries
    - 1x access to memory (can lead to slow down!)
- **Page table cache (TLB)**:
  - MMU-level address translation cache
  - On TLB miss: page table access from memory
  - Has protection/validity bits
  - Small number of cached address, high TLB hit rate and temporal and spatial locality

## Inverted Page Tables

- Another way of organizing the address translation process (see lecture for the inverted page table diagram):
  - Components:
    - Logical address
    - Physical address
    - Physical memory
    - Page table
    - Search
  - TLB to catch memory references
- Inverted page tables use hashing page tables (see lecture for diagram) to optimize efficiency:
  - Speeds up linear search process and narrows it down to few possible entries into the inverted page table, this speeds up address translation

## Segmentation

- **Segments** are arbitrary and granular:
  - E.g., code, heap, data, stack, etc.
  - Address is equivalent to the segment selector + offset
- **Segment** is a contiguous physical memory:
  - Segment size is equivalent to segment base + limit registers
- **Segmentation + paging**:
  - IA x86_32: segmentation + paging
    - Linux up to 8K per process / global segment
  - IA 86x_64: paging

## Page Size

- 10-bit offset: 1 KB page size
- 12-bit offset: 4 KB page size
- Below is a table detailing _large vs huge_ pages

|                                       | Large   | Huge    |
| ------------------------------------- | ------- | ------- |
| Page size                             | 2 MB    | 1 GB    |
| Offset bits                           | 21 bits | 30 bits |
| Reduction factor (on page table size) | x512    | x1024   |

- In general, for larger pages:
  - Pros: fewer page table entries, smaller page tables, more TLB hits, etc.
  - Cons: internal fragmentation (wastes memory)

## Memory Allocation

- **Memory allocator**:
  - Determines VA to PA mapping, address translation, page tables, etc.
  - Simply determine PA from VA and check validity/permissions
- **Kernel-level allocators**:
  - Kernel state, static process state
- **User-level allocators**:
  - Dynamic process state (heap), malloc/free
  - E.g., `dimalloc`, `jemalloc`, `hoard`, `tcmalloc`

## Memory Allocation Challenges

- Problem: **external fragmentation**
  - Occurs with multiple interleaved allocate and free operations, and as a result of them, we have holes of free memory that is not contiguous
  - Requests for larger contiguous memory allocations cannot be satisfied
- Solution:
  - When pages are freed, the allocator can aggregate adjacent areas of free pages into one larger free area, this allows for larger future requests

## Allocators in the Linux Kernel

- The Linux kernel relies on two basic allocation mechanisms:
  - **Buddy**:
    - Starts with consecutive memory region that's free (2^x area)
    - On request, sub-divide into 2^x chunks and find smallest 2^x chunk that can satisfy request (fragmentation still there)
    - On free:
      - Check buddy to see if it can aggregate into a larger chunk
      - Aggregate more up the tree (aggregation works well and fast)
  - **Slab**:
    - Addresses 2^x granularity in Buddy
    - Addresses internal fragmentation
    - **Slab allocator**:
      - Caches for common object types/sizes, on top of contiguous memory
    - Pros:
      - Internal fragmentation avoided
      - External fragmentation not an issue

## Demand Paging

- Virtual memory >> physical memory:
  - Virtual memory page note always in physical memory
  - Physical page frame saved and restored to/from secondary storage
- **Demand paging**: pages swapped in/out of memory and a swap partition
  - Original PA is not equal to PA after swap
  - If page is _pinned_ swapping disabled

## Freeing Up Physical Memory

- When should pages be swapped out?
  - OS runs page (out) daemon:
    - When memory usage is above threshold (high watermark)
    - When CPU usage is below threshold (low watermark)
- Which pages should be swapped out?
  - Pages that won't be used
  - History-based prediction:
    - LRU (least-recently used) policy: access bit to track if page is referenced
  - Pages that don't need to be written out
    - Dirty bit to track if modified
  - Avoid non-swappable pages
- In Linux:
  - Parameters to tune thresholds: target page count, etc.
  - Categorize pages into different types: e.g., claimable, swappable, etc.
  - _Second chance_ variation of LRU

## Copy On Write

- MMU Hardware:
  - Perform translation, track access, enforce protection, etc.
  - Useful to build other services and optimizations
- **COW (copy-on-write)**:
  - On process creation:
    - Copy entire parent address space
    - Many pages are static, don't change (why keep multiple copies?)
  - On create:
    - Map new VA to original page
    - Write protect original page
    - If only read: save memory and time to copy
  - On write:
    - Page fault copy
    - Pay copy cost only if necessary

## Failure Management Check-pointing

- **Check-pointing**: failure and recovery management technique
  - Periodically save process state
  - Failure may be unavoidable but can restart from checkpoint so recovery much faster
- **Simple approach**: pause and copy
- **Better approach**:
  - Write-protect and copy everything once
  - Copy diffs of _dirtied_ pages for incremental checkpoints, rebuild from mutiple diffs, or in background
- **Debugging**:
  - RR (rewind-replay)
  - Rewind means to restart from checkpoint
  - Gradually go back to older checkpoints until error found
- **Migration**:
  - Continue on another machine
  - Disaster recovery
  - Consolidation
  - Repeated checkpoints in a fast loop until pause-and-copy becomes acceptable (or unavoidable)

# Lesson 13: Inter-process Communication

- Topics to be covered in this lesson:
  - IPC (inter-process communication)
  - Shared Memory IPC

## Visual Metaphor

- An **IPC** is like **working together** in the toy shop:
  - Processes share memory:
    - Data shared in memory
  - Processes exchange messages:
    - Message passing via sockets
  - Requires synchronization:
    - Mutexes, writing, etc.

## Inter-process Communication

- **IPC**: OS-supported mechanisms for interaction among processes (coordination and communication)
- Message passing: e.g., sockets, pipes, message queues
- Memory-based IPC: shared memory, memory mapped files
- Higher-level semantics: files, RPC
- Synchronization primitives

## Message Based IPC

- **Processes** create messages and send/receive them:
  - Send/write messages to a port
  - Receive/read messages from a port
- **OS** creates and maintains a channel (i.e., buffer, FIFO queue, etc.):
  - OS provides interface to processes - a port
- **Kernel** required to:
  - Establish a connection
  - Perform each IPC operation
- Send: system call + data copy
- Receive: system call + data copy
- Pros:
  - Simplicity: kernel does channel management and synchronization
- Cons: overheads

## Forms of Message Passing

- **Pipes**:
  - Carry byte stream between two processes (e.g., connect output from one process to input of another)
- **Message queues**:
  - Carry _messages_ among processes
  - OS management includes priorities, scheduling of message delivery, etc.
  - APIs: `SysV` and `POSIX`
- **Sockets**:
  - `send()`, `recv()` to pass message buffers
  - `socket()` to create kernel-level socket buffer
  - Associate necessary kernel-level processing (TCP/IP)
  - If different machines, channel between process and network device
  - If same machine, bypass fall protocol stack

### Shared Memory IPC

- Read and write to shared memory region
- OS establishes shared channel between the processes
  - Physical pages mapped into virtual address space
  - VA (_P1_) and VA (_P2_) map to the same physical address (see lecture for diagram)
  - VA (_P1_) is **not** equal to VA (_P2_)
  - Physical memory does no need to be contiguous
- Pros:
  - System calls only for setup data copies potentially reduced (but not eliminated)
- Cons:
  - Explicit synchronization
  - Communication protocol, shared buffer management, etc. (programmer responsibility)

## Copy vs Map

- Goal: transfer data from one into target address space
- **Copy**:
  - CPU cycles to copy data to/from port
  - Large data: `t(copy) >> t(map)`
- **Map**:
  - CPU cycles to map memory into address space
  - CPU to copy data to channel
  - Set up once use many times (good payoff)
  - Can perform well for one-time use
- Tradeoff exercised in Windows LPC (local producer callsS)

## SysV Shared Memory

- **Segments** of shared memory: not necessarily contiguous physical pages
- Shared memory is system-wide: system limits on number of segments and total size
- **Create**: OS assigns unique key
- **Attach**: map VA to PA
- **Detach**: invalidate address mappings
- **Destroy**: only remove when explicitly deleted (or reboot)

## Shared Memory and Sync

- _Like threads accessing shared state in a single address space but for processes_
- **Synchronization method**:
  - Mechanisms supported by process threading library (pthreads)
  - OS-supported IPC for synchronization
- **Either method must coordinate**:
  - Number of concurrent access to shared segment
  - When data is available and ready for consumption

## Shared Memory Design Considerations

- Consider the following when designing for memory:
  - Different API/mechanisms for synchronization
  - OS provides shared memory and is out of the way
  - Data passing/sync protocols are up to the programmer

## How Many Segments?

- One large segment: manager for allocating/freeing memory from shared segment
- Many small segment:
  - Use pool of segments, queue of segment ids
  - Communicate segment IDs among processes

## Design Considerations

- Consider the following questions:
  - What size segments?
  - What if data doesn't fit
- Segment size is equivalent to data size:
  - Works for well-known static sizes
  - Limits max data size
- Segment size is greater than message size:
  - Transfer data in rounds
  - Include protocol to track progress

# Lesson 14: Synchronization Constructs

- Topics to be covered in this lesson:
  - More synchronization constructs
  - Hardware supported synchronization

## Visual Metaphor

- **Synchronization** is like **waiting** for a coworker to finish **so you can continue working**:
  - May repeatedly check to continue:
    - Sync using spinlocks
  - May wait for a signal to continue:
    - Sync using mutexes and condition variables
  - Waiting hurts performance:
    - CPUs waste cycles for checking
    - Cache effects

## More About Synchronization

- Limitation of mutexes and condition variables:
  - Error prone/correctness/ease-of-use:
    - Unlock wrong mutex, signal wrong condition variable
  - Lack of expressive power:
    - Helper variables for access or priority control
  - Low level support:
    - Hardware atomic instructions

## Spinlocks

- Spinlock is like a mutex:
  - Mutual exclusion
  - Lock and unlock (free)
- When lock is busy that means the thread is spinning

## Semaphores

- Semaphores are a common sync construct in OS kernels:
  - Similar to a traffic light (stop and go state)
  - Similar to a mutex but more general
- **Count-based sync** (semaphores can be an integer value):
  - On init: assigned a max value positive integer (maximum count)
  - On try (wait): if non-zero, decrement and proceed (counting semaphore)
  - If initialized with `1`: semaphore is equal to mutex (binary semaphore)
  - On exit (post): increment

## Reader Writer Locks

- Syncing different types of accesses:
  - Read (never modify): shared access
  - Write (always modify): exclusive access
- Read/write locks:
  - Specify the type of access then lock behaves accordingly

## Monitors

- Monitors are a high-level synchronization construct
- Monitors specify:
  - Shared resource
  - Entry procedure
  - Possible condition variables
- On entry: lock, check, etc.
- On exit: unlock, check, signal, etc.

## Need for Hardware Support

- Problem: concurrent check/update on different CPUs can overlap
- Solution: hardware-supported atomic instructions

## Atomic Instructions

- Hardware specific:
  - `test_and_set()`
  - `read_and_compare()`
  - `compare_and_swap()`
- Guarantees:
  - Atomicity
  - Mutual exclusion
  - Queue all concurrent instructions but one
- Atomic instructions are critical sections with hardware-supported synchronization:

```c
// Specialize/optimize to available atomics
spinlock_lock(lock): // Spin until free
    while(test_and_set(lock) == busy);
```

- `test_and_set(lock)`: atomically returns `(tests)` original value and sets new value to `1` (busy)
- First thread: `test_and_set(lock) == 0` (free)
- Next ones: `test_and_set(lock) == 1` (busy)
  - Reset lock to `1` (busy)

## Shared Memory Multi-processors

- A multi-processor system consists of more than one CPU and has memory accessible to all CPUs (see lecture slide for bus-based vs interconnect based)
- SMP (shared memory multi-processors): systems where a bus is shared across all modules which allows the system's memory to be accessible to all CPUs
- SMPs also have cache:
  - Hides memory latency
  - Memory _further away_ due to contention
  - No write, write-through, write-back

## Cache Coherence and Atomics

- Atomics always issued to the memory controller:
  - Pros: can be ordered and synchronized
  - Cons: takes much longer and generates coherence traffic regardless of change
- Atomics and SMP:
  - Expensive because of bus or I/C contention
  - Expensive because of cache bypass and coherence trafficX

## Spinlock Performance Metrics

- Reduce **latency**:
  - _Time to acquire a free lock_
  - Ideally immediately execute atomic
- Reduce **waiting time (delay)**:
  - _Time to stop spinning and acquire a lock that has been freed_
  - Ideally immediately
- Reduce **contention**:
  - _Bus/network I/C traffic_
  - Ideally zero

## Test and Set Spinlock

- Test and set spinlock implementation (see lecture):
  - Pros:
    - Latency: minimal (atomic)
    - Delay: Potentially min (spinning continuously on the atomic)
  - Cons:
    - Contention: processors go to memory on each spin

## Test and Test and Set Spinlock

- Test and test and set spinlock implementation (see lecture):
  - Spin on read
  - Spin on cached value
  - Pros:
    - Latency: ok
    - Delay: ok
  - Cons:
    - Contention: better than test and set spinlock but...
      - Non-cached coherent architecture: no difference
      - Cache coherence with write update architecture: ok
      - Cache coherence with write invalidate architecture: horrible
    - Contention due to atomics + caches invalidated means more contention
    - Everyone sees lock is free at the same time
    - Everyone tries to acquire the lock at the same time

## Spinlock _Delay_ Alternatives

- Delay after lock release:
  - Everyone sees lock is free
  - Not everyone attempts to acquire it
  - Pros:
    - Contention improved
    - Latency ok
  - Cons:
    - Delay is much worse
- Delay after each lock reference:
  - Does not spin constantly
  - Works on non-cached coherent architectures
  - Can hurt delay even more however
  - Pros:
    - Contention improved
    - Latency ok
  - Cons:
    - Delay is **much worse**

## Picking a Delay

- **Static Delay** (based on fixed value, e.g., CPU ID):
  - Simple approach
  - Unnecessary delay under low contention
- **Dynamic Delay** (backoff-based):
  - Random delay in a range that increases with _perceived_ contention
  - Perceived is the same as failed `test_and_set()`
  - Delay after each reference will keep growing based on contention or length of critical section

## Queueing Lock

- **Common problem in spinlock implementations**:
  - Everyone tries to acquire lock at the same time once lock is freed: delay alternatives
  - Everyone sees the lock is free at the same time (Anderson's Queueing Lock)
- Solution:
  - Set unique **ticket** for arriving thread
  - Assigned `queue[ticket]` is private lock
  - Enter critical section when you have lock:
    - `queue[ticket] == must_wait` (spin)
    - `queue[ticket] == has_lock` (enter critical section)
  - Signal/set next lock holder on exit:
    - `queue[ticket + 1] = has_lock`
- Cons:
  - Assumes `read_and_increment` atomic
  - _O(n)_ size

## Queueing Lock Implementation

- Pros:
  - Delay: directly signal next CPU/thread to run
  - Contention: better but requires cache coherence and cache line aligned elements
  - Only one CPU/thread sees the lock is free and tries to acquire lock!
- Cons:
  - Latency: more costly read and increment

## Spinlock Performance Comparisons

- **Setup** (see lecture for figure):
  - _N_ processes running critical section one million times
  - _N_ varied based on system
- **Metrics**:
  - Overhead compared to ideal performance
  - Theoretical limit based on number of critical sections to be run
- **Under high loads**:
  - Queue best (most scalable), `test_and_test_and_set` worst
  - Static better than dynamic, reference better than release (avoids extra invalidations)
- **Under light loads**:
  - `test_and_test_and_set` good (low latency)
  - Dynamic better than static (lower delay)
  - Queueing lock worst (high latency due to read and increment)

# Lesson 15: I/O Management

- Topics to be covered in this lesson:
  - OS support for I/O devices
  - Block device stack
  - File system architecture

## Visual Metaphor

- **I/O** is like **a top shop shipping department**:
  - Have protocols:
    - Interfaces for device I/O
  - Have dedicated handlers:
    - Device drivers, interrupt handlers, etc.
  - Decouple I/O details from core processing:
    - Abstract I/O device detail from applications

## I/O Devices

- Basic I/O device features:
  - Control registers:
    - Command
    - Data transfers
    - Status
  - Micro-controller (device's CPU)
  - On device memory
  - Other logic: e.g., analog to digital converters

## CPU Device Interconnect

- Peripheral Component Interconnect (PCI):
  - PCI express (PCIe)
- Other types of interconnects:
  - SCSI (small computer system interface) bus
  - Peripheral bus
  - Bridges handle differences

## Device Drivers

- Per each device type
- Responsible for device access, management and control
- Provided by device manufacturers per OS/version
- Each OS standardizes interfaces:
  - Device independence
  - Device diversity

## Types of Devices

- **Block: disk**
  - Read/write blocks of data
  - Direct access to arbitrary block
- **Character: keyboard**
  - Get/put character
- **Network devices**
- OS representation of a device: special device file

## Device Interactions

- Access device registers: memory load/store
- **Memory-mapped I/O**:
  - Part of _host_ physical memory dedicated for device interactions
  - BAR (base address registers)
- **I/O port**:
  - Dedicated in/out instructions for device access
  - Target device (I/O port) and value in register
- **Interrupt**:
  - Pros: can be generated as soon as possible
  - Cons: interrupt handling steps
- **Polling**:
  - Pros: When convenient for OS
  - Cons: delay or CPU overhead

## Device Access PIO

- No additional hardware support
- CPU _programs_ the device:
  - Via command registers
  - Via data movement
- An example of a PIO (programmed I/O): NIC data (network packet shown in lecture)
  - Write command to request packet transmission
  - Copy packet to data registers
  - Repeat until packet sent

## Device Access DMA

- Relies on DMA (direct memory access) controller
- CPU _programs_ the device:
  - Via command registers
  - Via DMA controls
- An example of a DMA: NIC data (network packet shown in lecture)
  - Write command to request packet transmission
  - Configure DMA controller with **in-memory address and size of packet buffer**
  - Less steps but DMA config is more complex
- For DMAs:
  - Data buffer must be in physical memory until transfer completes: pinning regions (non-swappable)

## Typical Device Access

- _See lecture for diagram_
- Typical device access includes the following:
  - System call
  - In-kernel stack
  - Driver invocation
  - Device request configuration
  - Device performs request

## OS Bypass

- _See lecture for diagram_
- Device regs/data directly accessible
- OS configures then out-of-the-way
- **User-level driver**:
  - OS retains coarse-grain control
  - Relies on device features:
    - Sufficient registers
    - Demux capability

## Sync vs Async Access

- _See lecture for diagram_
- **Synchronous I/O operations**: process blocks
- **Asynchronous I/O operations**: process continues
  - Process checks and retrieves result
  - Process is notified that the operation completed and results are ready

## Block Device Stack

- _See lecture for diagram_
- Processes use files: logical storage unit
- Kernel file system (FS):
  - Where and how to find and access file
  - OS specifies interface
- Generic block layer:
  - OS standardized block interface
- Device driver

## Virtual File System

- Problem: how to address the following?
  - What if files are on more than one device?
  - What if devices work better with different file system implementations?
  - What if files are not on a local device (accessed via network)?
- Solution: use a file system

## Virtual File System Abstractions

- **File**: elements on which the VFS (virtual file system) operations
- **File descriptor**: OS representation of file
  - Open, read, write, send file, lock, close, etc.
- **Inode**: persistent representation of file _index_
  - List of all data blocks
  - Device, permissions, size, etc.
- **Dentry**: directory entry, corresponds to single path component
- **Superblock**: file system specific information regarding the file system layout

## VFS on Disk

- **File**: data blocks on disk
- **Inode**: track files' blocks and also resides on disk in some block
- **Superblock**: overall map of disk blocks
  - Inode blocks
  - Data blocks
  - Free blocks

## `ext2`: Second Extended File System

- For each block group:
  - **Superblock**: number of inodes, disk blocks, start of free blocks
  - **Group descriptor**: bitmaps, number of free nodes, directories
  - **Bitmaps**: tracks free blocks and inodes
  - **Inodes**: one to max number (one per file)
  - **Data blocks**: file data

## Inodes

- **Inodes**: index of all disk blocks corresponding to a file
  - File: identified by inode
  - Inode: list of all blocks plus other metadata
- Pros: easy to perform sequential or random access
- Cons: limit on file size

## Inodes with Indirect Pointers

- **Inodes with indirect pointers**: index of all disk blocks corresponding to a file
- Inodes contain:
  - Metadata
  - Pointers to blocks
- **Direct pointer**: points to data block
- **Indirect pointer**: block of pointers
- **Double indirect pointer**: block of block of pointers
- Pros: small inode means large file size
- Cons: file access slow down

## Disk Access Optimizations

- **Caching/buffering**: reduce number of disk accesses
  - Buffer cache in main memory
  - Read/write from cache
  - Periodically flush to disk (`fsync()`)
- **I/O scheduling**: reduce disk head movement
  - Maximize sequential vs random access
- **Prefetching**: increase cache hits
  - Leverages locality
- **Journaling/logging**: reduce random access
  - _Describe_ write in log: block, offset, value, etc.
  - Periodically apply updates to proper disk locations

# Lesson 16: Virtualization

- Topics to be covered in this lesson:
  - Overview of virtualization
  - Main technical approaches in popular virtualization solutions
  - Virtualization-related hardware advances

## What is Virtualization?

- **Virtualization** allows concurrent execution of multiple OS (and their applications) on the same physical machine
- **Virtual resources**: each OS thinks that it _owns_ hardware resources
- **Virtual machine (VM)**: OS applications and virtual resources (guest domain)
- **Virtualization layer**: management of physical hardware (virtual machine monitor, hypervisor)

## Defining Virtualization

- A **virtual machine** is an **efficient, isolated duplicated of the real machine** supported by a **VMM (virtual machine monitor)**:
  - Provides environment essentially identical with the original machine
  - Programs show at worst only minor decrease in speed
  - VMM is in complete control of system resources

## Benefits of Virtualization

- Pros:
  - Consolidation: decrease cost; improve manageability
  - Migration: availability, reliability
  - Security, debugging, support for legacy OS

## Virtualization Models: Bare-metal

- **Bare-metal**: hypervisor-based
  - VMM (hypervisor) manages all hardware resources and supports execution of VMs
  - Privileged, service VM to deal with devices
- Xen (open source or Citrix XenServer):
  - DomO and DomU
  - Drivers in DomO
- ESX (VMWare):
  - Many open APIs
  - Drivers in VMM
  - Used to have Linux control core, now remote APIs

## Virtualization Models: Hosted

- **Hosted**:
  - Host OS owns all hardware
  - Special VMM module provides **hardware interfaces** to VMs and deals with VM context switching
- Example: KVM (kernel-based VM shown in lecture)
  - Based on Linux
  - KVM kernel module plus QEMU (Quick Emulator) for hardware virtualization
  - Leverages Linux open-source community

## Processor Virtualization

- **Trap-and-emulate**:
  - Guest instructions are executed directly by hardware
  - For non-privileged operations: hardware speeds must provide efficiency
  - For privileged operations: trap to hypervisor
  - Hypervisor determines what needs to be done:
    - If illegal operation: terminate VM
    - If legal operation: emulate the behavior the guest OS was expecting from the hardware

## x86 Virtualization in the Past

- **x86 virtualization pre-2005**
  - Four rings, no root/non-root modes yet
  - Hypervisor in ring 0, guest OS in ring 1
  - However, 17 privileged instructions do not trap, they fail silently!
- Cons:
  - Hypervisor does not know so it does not try to change settings
  - OS does not know, so it assumes change was successful

## Binary Translation

- **Main idea**: rewrite the VM binary to never issue those 17 instructions
  - Pioneered by Mendel Rosenblum's group at Stanford, commercialized as VMware
- **Binary translation**:
  - Goal: full virtualization (guest OS not modified)
  - Approach: dynamic binary translation
- Inspect code blocks to be executed
- If needed, translate to alternate instruction sequence
- Otherwise, run at hardware speeds

## Paravirtualization

- Goal: performance, give up on unmodified guests
- Approach: paravirtualization, modify guest so that...
  - It knows it's running virtualized
  - It makes explicit calls to the hypervisor (hypercalls)
  - **Hypercall**: system calls
    - Package context info
    - Specify desired hypercall
    - Trap to VMM

## Memory Virtualization Full

- All guests expect contiguous physical memory, starting at 0
- Virtual vs physical vs machine addresses (VA vs PA vs MA) and page frame numbers
- Still leverages hardware MMU, TLB, etc.
- **Option 1**:
  - Guest page table: VA to PA
  - Hypervisor: PA to MA
  - **Too expensive!**
- **Option 2**:
  - Guest page tables: VA to PA
  - Hypervisor shadow PT: VA to MA
  - Hypervisor maintains consistence

## Memory Virtualization Paravirtualized

- **Paravirtualized**:
  - Guest aware of virtualization
  - No longer strict requirement on contiguous physical memory starting at 0
  - Explicitly registers page tables with hypervisor
  - Can _batch_ page table updates to reduce VM exits
  - _Other optimizations_
- **Bottom line**: overheads eliminated or reduced on newer platforms

## Device Virtualization

- For CPUs and memory:
  - Less diversity
  - ISA level (instruction set architecture level) _standardization_ of interface
- For devices:
  - High diversity
  - Lack of standard specification of device interface and behavior
- Three key models for device virtualization (see later slides)

## Passthrough Model

- **Approach**: VMM-level driver configures device access permissions
- Pros:
  - VM provided with exclusive access to the device
  - VM can directly access the device (VMM-bypass)
- Cons:
  - Device sharing difficult
  - VMM must have exact type of device as what VM expects
  - VM migration tricky

## Hypervisor Direct Model

- **Approach**:
  - VMM intercepts all device accesses
  - Emulate device operation:
    - Translate to generic I/O operation
    - Transverse VMM-resident I/O stack
    - Invoke VMM-resident driver
- Cons:
  - Latency of device operations
  - Device driver ecosystem complexities in hypervisor

## Split-device Driver Model

- **Approach**:
  - Device access control **split** between:
    - Front-end driver in guest VM (device API)
    - Back-end driver in service VM (or host)
    - Modified guest drivers
- Pros:
  - Eliminate emulation overhead
  - Allow for better management of shared devices

## Hardware Virtualization

- **AMD Pacifica and Intel Vanderpool Technology (Intel-VT)**, 2005:
  - _Close holes_ in x86 ISA
  - Modes: root/non-root (or _host_ and _guest_ mode)
  - VM control structure
  - Extended page tables and tagged TLB with VM ids
  - Multi-queue devices and interrupt routing
  - Security and management support
  - Additional instructions to exercise previously mentioned features

# Lesson 17: Remote Procedure Calls

- Topics to be covered in this lesson:
  - RPC (remote procedure calls)

## Why RPC?

- **Example 1: Get File App**
  - Client-server
  - **Create** and **init sockets**
  - **Allocate** and **populate buffers**
  - **Include _protocol_ info** (e.g., get file, size, etc.)
  - **Copy data** into buffers (e.g., filename, file, etc.)
- **Example 2: Mod Image App**
  - Client-server
  - **Create** and **init sockets**
  - **Allocate** and **populate buffers**
  - **Include _protocol_ info** (e.g., algorithm, parameters, etc.)
  - **Copy data** into buffers (e.g., image data, etc.)
- Common steps (highlighted in bold) related to remote IPC (inter-process communication): RPC

## Benefits of RPC

- RPC is intended to simplify the development of cross-address space and cross-machine interactions
- Pros:
  - Higher-level interface for data movement and communication
  - Error handling
  - Hiding complexities of cross-machine interactions

## RPC Requirements

- Some requirements of RPCs include:
  - Client/server interactions
  - Procedure call interface:
    - Sync call semantics
  - Type checking
    - Error handling
    - Packet bytes interpretation
  - Cross-machine conversion
    - E.g., big/little endian
  - Higher-level protocol
    - Access control, fault tolerance, etc.
    - different transport protocols

## Structure of RPC

- _See lecture slides for figure_
- The execution order of an RPC is as follows:
  1. Client call to procedure
  2. Stub builds message
  3. Message is sent across the network
  4. Server OS hands message to server stub
  5. Stub unpacks message
  6. Stub makes local call to _add_

## Steps in RPC

- There are some general steps in RPC:
  1. **Register**: server _registers_ procedure, argument types, location, etc.
  2. **Bind**: client finds and _binds_ to desired server
  3. **Call**: client makes RPC call; control passed to sub, client code blocks
  4. **Marshal**: client stub _marshals_ arguments (serialize arguments into buffer)
  5. **Send**: client sends message to server
  6. **Receive**: server receives message; passes message to server-stub; access control
  7. **Unmarshal**: server stub _unmarshals_ arguments (extracts arguments and creates data structures)
  8. **Actual call**: server stub calls local procedure implementation
  9. **Result**: server performs operation and computes result of RPC operation
- The above steps are similar on return

## Interface Definition Language

- What can the server do?
- What arguments are required for the various operations (need agreement!)?
- Why:
  - Client-side bind decision
  - Run-time to automate stub generation: IDL (interface definition language)

## Specifying an IDL

- An IDL used to describe the interface the server exports
- RPC can use IDL that is:
  - Language-agnostic
  - Language-specific
- Remember that an IDL is just an interface not an implementation!

## Binding

- Client determines:
  - Which server should it connect to?
  - How will it connect to that server?
- **Registry**: database of available services
  - Search for service name to find a service (which) and contact details (how)
- **Distributed**:
  - Any RPC service can register
- **Machine-specific**:
  - For services running on same machine
  - Clients must known machine address: registry provides port number needed for connection
- **Needs naming protocol**:
  - Exact match for _add_
  - Or consider _summation_, _sum_, _addition_, etc.

## Visual Metaphor

- Applications use **binding and registries** like toy shops use directories of **outsourcing services**:
- Who can provide services?
  - Look u registry for image processing
- What services are provided?
  - Compress, filter, version number, etc. (IDL)
- How will they send/receive?
  - TCP/UDP (registry)

## What About Pointers?

- Solutions:
  - No pointers!
  - Serialize pointers; copy referenced _pointed to_ data structure to send buffer

## Handling Partial Failures

- When a client hangs, what is the problem?
  - Server, service, or network down? Message lost?
  - Timeout and retry (no guarantees!)
- Special RPC error notification (signal, exception, etc.):
  - Catch all possible ways in which the RPC call can (partially) fail

## RPC Design Choice Summary

- **Design decisions for RPC systems** (e.g., Sun RPC, Java RMI)
  - **Binding**: how to find the server
  - **IDL**: how to talk to the server; how to package data
  - **Pointers as arguments**: disallow or serialize pointed data
  - **Partial failures**: special error notifications

## What is Sun RPC?

- Sun RPC was developed in the 80x by Sun for UNIX; now widely available on other platforms
- Design choices:
  - **Binding**: per-machine registry daemon
  - **IDL**: XDR (for interface specification and for encoding)
  - **Pointers as arguments**: allowed and serialized
  - **Partial failures**: retries; return as much information as possible

## Sun RPC Overview

- _See lecture for figure_
- Client-server via procedure calls
- Interface specified via XDR (x file)
- `rpcgen` compiler: converts x to language-specified stubs
- Server registers with local registry damon
- Registry:
  - Name of service, version, protocol(s), port number, etc.
- Binding creates handle:
  - Client uses handle in calls
  - RPC run-time uses handle to track per-client RPC state
- Client and server on same or different machines
- Documentation, tutorials and examples now maintained by Orcale
  - TI-RPC: Transport-independent Sun RPC
  - Provides Sun RPC/XDR documentation and code examples
  - Older online references still relevant
  - Linux man pages for _rpc_

## Compiling XDR

- `rpcgen` compiler:
  - `square.h`: data types and function definitions
  - `square_svc.c`: server stub and skeleton (main)
  - `square_clnt.c`: client stub
  - `square_xdr.c`:common marshalling routines

## Summarizing XDR Compilation

- _See lecture for figure_
- **Developer**:
  - Server code: implementation of `square.proc_1_svc`
  - Client side: call `squareproc_1()`
  - `#include.h`
  - Link with stub objects
- **RPC run-time - the rest**:
  - OS interactions, communication management, etc.
- `rpcgen -C square.x`: not thread safe!
- `rpcgen -C -M square.x`: multi-threading safe!
  - Does not make a multi-threaded _svc.c_ server

## Sun RPC Registry

- **RPC daemon**: port mapper
- **Query with** `rpcinfo -p`:
  - `/usr/sbin/rpcinfo -p`
  - Program id, version, protocol (tcp, udp), socket port number, service name, etc.
  - Port mapper runs with tcp and udp on port 111

## Sun RPC Binding

- **Client type**:
  - Client handle
  - Status, error, authentication, etc.

## XDR Data Types

- **Default types**:
  - `char`, `byte`, `int`, `float`
- Additional XDR types:
  - `const` (`#define`)
  - `hyper` (64-bit `integer`)
  - `quadruple` (128-bit `float`)
  - `opaque` (C `byte`)
    - Uninterpreted binary data
- **Fixed-length array** (e.g., `int data[80]`)
- **Variable-length array** (e.g., `int data<80>`): translates into a data structure with _len_ and _val_ fields
  - **Except for strings**:
    - String line `<80>`: c pointer to `char`
    - Stored in memory as a normal null-terminated string
    - Encoded (for transmission) as a pair of length and data

## XDR Routines

- **Marshalling/unmarshalling**: found in `square_xdr.c`
- **Clean-up**:
  - `xdr_free()`
  - User-defined `freeresult` procedure (e.g., `square_prog_1_freeresult`)
  - Called after results returned

## Encoding

- What goes on the wire?
  - **Transport header** (e.g., TCP, UDP)
  - **RPC header**: service procedure ID, version number, request ID, etc.
  - **Actual data**:
    - Arguments or results
    - Encoded into a byte stream depending on data type

## XDR Encoding

- **XDR**: **IDL + the encoding** (i.e., the binary representation of data _on-the-wire_)
- **XDR encoding rules**:
  - All data types are encoded in multiples of four bytes
  - Big endian is the transmission standard
  - Two's complement is used for integers
  - IEEE format is used for floating point

## Java RMI

- **Java RMI (Remote Method Invocations)**:
  - Among address spaces in JVM(s)
  - Matches Java OO semantics
  - **IDL**: Java (language specific)
- **RMI run-time**:
  - **Remote reference layer**:
    - Unicast, broadcast, return-first response, return-if-all-match
  - **Transport**:
    - TCP, UDP, shared memory, etc.

# Lesson 18: Distributed File Systems

- Topics to be covered in this lesson:
  - DFS (distributed file systems) design and implementation
  - NFS (network file systems)

## Visual Metaphor

- **Distributed file systems** are like **distributed storage facilities**:
  - Accessed via well-defined interface:
    - Access via VFS
  - Focus on consistent state:
    - Tracking state, file updates, cache coherence, etc.
  - Mix distribution models possible:
    - Replicated vs partitioned, peer-like systems, etc.

## Distributed File Systems

- _See lecture for figure_
- **DFS**: an environment where multiple machines are involved in the delivery of the file system service
  - Includes file-system interfaces which use VFS interface to abstract and hide file system organizations
  - Uses OS to hide local physical storage on a machine
  - Has files maintained on a remote machine or on a remote file system that is being accessed over the network

## DFS Models

- **Client/server on different machines**
- File server distributed on multiple machines
  - **Replicated** (each server: all files)
  - **Partitioned** (each server: part of files)
  - **Both** (files partitioned; each partition replicated)
- Files stored on and served from all machines (peers)
- Blurred distinction between clients and servers

## Remote File Service: Extremes

- **Extreme 1: upload/download**
  - Like FTP, SVN, etc.
- **Extreme 2: true remote file access**
  - Every access to remote file, nothing done locally
- Pros:
  - File accesses centralized, easy to reason about consistency
- Cons:
  - Every file operation pays network cost
  - Limits server scalability

## Remote File Service: A Compromise

- A more practical remote file access (with caching)
- Allow clients to store parts of files locally (blocks)
  - Pros:
    - Low latency on file operations
    - Server load reduced: is more scalable
- Force clients to interact with server (frequently)
  - Pros:
    - Server has insights into what clients are doing
    - Server has control into which accesses can be permitted: easier to maintain consistency
  - Cons:
    - Server more complex, requires difference file sharing semantics

## Stateless vs Stateful File Server

- **Stateless**: keeps no state, ok with extreme models but cannot support _practical_ model
  - Pros:
    - No resources are used on server side (CPU/memory)
    - ON failure, just restart
  - Cons:
    - Cannot support caching and consistency management
    - Every request self-contained: more bits transferred
- **Stateful**: keeps client state, needed for _practical_ model to track what is cached/accessed
  - Pros:
    - Can support locking, caching, incremental operations
  - Cons:
    - On failure, need check-pointing and recovery mechanisms
    - Overheads to maintain state and consistency: depends on caching mechanism and consistency protocol

## Caching State in a DFS

- Locally clients maintain portion of state (e.g., file blocks)
- Locally clients perform operations on cached state (e.g. open/read/write, etc.): requires coherence mechanisms
- How?
  - SMP: write-update/write-invalidate
  - DFS: client/server-driven
- When?
  - SMP: on write
  - DFS: on demand, periodically, on open, etc.
- Details depend on file sharing semantics

## File Sharing Semantics on a DFS

- **UNIX semantics**: every write visible immediately
- **Session semantics**: (between open-close: session)
  - Write-back on `close()`, update on `open()`
  - Easy to reason, but may be insufficient
- **Periodic updates**:
  - Client writes-back periodically: clients have a _lease_ on cached data (not exclusive necessarily)
  - Server invalidates periodically: provides bounds on _inconsistency_
  - Augment with `flush()`/`sync()` API
- **Immutable files**: never modify, new files created instead
- **Transactions**: all changes atomic

## File vs Directory Service

- Too many options?
  - Sharing frequency
  - Write frequency
  - Importance of consistent view
- Optimize for common case
- Two types of files:
  - Regular files vs directories
  - Choose different policies for each
    - E.g., session-semantics for files, UNIX for directories
    - E.g., less frequent write-back for files than directories

## Replication and Partitioning

- **Replication**: each machine holds all files
  - Pros: load balancing, availability, fault tolerance
  - Cons:
    - Writes become more complex:
      - Synchronously to all
      - Or write to one then propagated to others
    - Replicas must be reconciled:
      - E.g., voting
- **Partitioning**: each machine has subset of files
  - Pros:
    - Availability vs single server DFS
    - Scalability with file system size
    - Single file writes simpler
  - Cons:
    - On failure, lose portion of data
    - Load balancing harder; if not balanced them hot-spots possible
- Can combined both techniques, replicate each partition

## NFS (Network File System)

- _See lecture for figure_
- A NFS typically includes a client and a server; however, clients act as the remote server over a network
- **Client**:
  - Client requests for file access starts at _system call layer_ and moves to _VFS layer_
  - At the _VFS layer_, a decision will be made for where the file belongs to (the _local file system interface_ or the _NFS client_)
  - If _NFS client_ is chosen, it will move on to the _RPC client stub_ which communicates with the _RPC server sub_
- **Server**:
  - Continuing from the _RPC server stub_, the call could make it's way to the _NFS server_ which resides on a remote machine
  - The _NFS server_ could communicate with the _VFS layer_ on the server side to get access to the file
  - From the _VFS layer_, the layout is about the same as the client side
  - When an open request comes from the client, the _NFS server_ will create a file handle (i.e. a byte sequence that encodes both the server machine as well as the server local file information which will be return to the client)
  - If files are deleted or the server machine dies, the file handle will return an error for _stale data_ (invalid data)

## NFS Versions

- Since 80s, currently NFSv3 and NFSv4
- NFSv3: stateless, NFSv4: stateful
- **Caching**:
  - Session-based (non-concurrent)
  - Periodic updates
    - Default: three seconds for files; 30 seconds for directory
    - NFSv4: delegation to client for a period of time (avoids _update checks_)
- **Locking**:
  - Lease-based
  - NFSv4: also _share reservation_, reader/writer lock

## Sprite Distributed File Systems

- _Caching in the Sprite Network File System_, by Nelson et al.
  - Research DFS
  - Great value in the explanation of the design process
- Takeaway: used trace data on usage/file access patterns to analyze DFS design requirements and justify decisions

## Sprite DFS Access Pattern Analysis

- **Access pattern (workload) analysis**:
  - 33% of all file accesses are writes
    - Caching ok but write-though not sufficient
  - 75% of files are open less than 0.5 seconds
  - 90% of files are open less than 10 seconds
    - Session semantics still too high overhead
  - 20-30% of new data deleted within 30 seconds
  - 50% of new data deleted within 5 minutes
  - File sharing is rare!
    - Write-back on close not necessary
    - No need to optimize for concurrent access but must support it

## Sprite DFS from Analysis to Design

- **From analysis to design**:
  - Cache with write-back
  - Every 30 seconds write-blocks that have NOT been modified for the last 30 seconds
    - When another client opens file: get dirty blocks
  - Open goes to server, directories not cached
  - On _concurrent write_: disable caching
- **Sprite sharing semantics**:
  - Sequential write sharing: caching and sequential semantics
  - Concurrent write sharing: no caching

## File Access Operations in Sprite

- $R_1... R_n$ **readers, w, writer**:
  - All `open()` go through server
  - All clients cache blocks
  - Writer keeps timestamps for each modified block
- $w_2$ **sequential writer** (sequential sharing):
  - Server contacts last last writer for dirty blocks
  - Since $w_2$ has not closed: disabled caching!

# Lesson 19: Distributed Shared Memory

- Topics to be covered in this lesson:
  - DSM (distributed shared memory)
  - Distributed state management and design alternatives
  - Consistency model

## Visual Metaphor

- **Managing distributed shared memory** is like **managing a tools/parts across all workspaces in a toy shop**:
  - Must decide placement:
    - Place memory (pages) close to relevant processes
  - Must decide migration:
    - When to copy memory (pages) from remote to local
  - Must decide sharing rules:
    - Ensure memory operations are properly ordered

## Reviewing DFS

- **Clients**:
  - Send requests to file service
- **Caching**:
  - Improve performance (seen by clients) and scalability (supported by servers)
- **Servers**:
  - Own and manage state (files)
  - Provide service (file access)

## Peer Distributed Applications

- **Each node**:
  - _Owns_ state
  - Provides service
  - All nodes are _peers_
- In _peer-to-peer_ even overall control and management done by all

## DSM (Distributed Shared Memory)

- **Each node**:
  - _Owns_ state: memory
  - Provides service:
    - Memory reads/writes from any node
    - Consistency protocols
- Permits scaling beyond single machine memory limits:
  - More _shared_ memory at lower cost
  - Slower overall memory access
  - Commodity interconnect technologies support this RDMA

## Hardware vs Software DSM

- **Hardware-supported** (expensive!):
  - Relies on interconnect
  - OS manages larger physical memory
  - NICs (network interconnect card) translate remote memory access to messages
  - NICs involved in all aspects of memory management; support atomics, etc.
- **Software-supported**:
  - Everything done by software
  - OS, or language run-time

## DSM Design: Sharing Granularity

- Cache line granularity?
  - Overheads too high for DSM
- Pros:
  - Page granularity (OS-level)
  - Object granularity (language run-time)
- Cons:
  - Variable granularity
- Beware of false sharing, e.g., X and Y are on the same page!

## DSM Design: Access Algorithm

- **What types of applications use DSM**?
  - Application access algorithm:
    - Single reader/single writer (SRSW)
    - Multiple readers/single writer (MRSW)
    - Multiple readers/multiple writers (MRMW)

## DSM Design: Migration vs Replication

- **DSM performance metric**: access latency
- Achieving low latency through:
  - **Migration**:
    - Makes sense for SRSW
    - Requires data movement
  - **Replication** (caching):
    - More general
    - Requires consistency management

## DSM Design: Consistency Management

- **DSM**: shared memory in SMPs
- **In SMP**:
  - Write-invalidate
  - Write-update
- Coherence operations on each write: overhead too high
- Push invalidations when data is written to:
  - Proactive
  - Eager
  - Pessimistic
- Pull modification info periodically
  - On-demand (reactive)
  - Lazy
  - Optimistic
- When these methods get triggered depends on the consistency model for the shared state!

## DSM Architecture

- **DSM architecture** (page-based, OS-supported):
  - Each node contributes part of memory pages to DSM
  - Need local caches for performance (latency)
  - All nodes responsible for part of distributed memory
  - Home node manages access and tracks page ownership
- **Exact replicas** (explicit replication):
  - For load balancing, performance, or reliability
  - _home_/manager node controls management

## Indexing Distributed State

- **Each page (object) has**:
  - Address: node ID and page frame number
  - Node ID: _home_ node
- **Global map (replicated)**:
  - Object (page) ID: manager node ID
  - Manager map available on each node!
- **Metadata for local pages (partitioned)**:
  - Per-page metadata is distributed across managers
- **Global mapping table**:
  - Object ID: index into mapping table: manager node

## Implementing DSM

- **Problem**: DSM must _intercept_ accesses to DSM state
  - To send remote messages requesting access
  - To trigger coherence messages
  - Overheads should be avoided for local, non-shared state (pages)
  - Dynamically _engage_ and _disengage_ DSM when necessary
- **Solution**: Use hardware MMU support!
  - Trap in OS if mapping invalid or access not permitted
  - Remote address mapping: trap and pass to DSM to send message
  - Cached content: trap and pass to DSM to perform necessary coherence operations
  - Other MMU information useful (e.g., dirty page)

## What is a Consistency Model?

- **Consistency model**: agreement between memory (state) and upper software layers
- _Memory behaves correctly if and only if software follows specific rules_
- Memory (state) guarantees to behave correctly:
  - Access ordering
  - Propagation/visibility of updates

## Strict Consistency

- **Strict consistency**: updates visible everywhere immediately
- In practice:
  - Even on single SMP, no guarantees on order without extra locking and synchronization
  - In distributed systems, latency and message reorder/loss make this even harder (impossible to guarantee)

## Sequential Consistency

- **Sequential consistency**:
  - Memory updates from different processors may be arbitrarily interleaved
  - All processes will see the same interleaving
  - Operations from same process always appear in order they were issued

## Casual Consistency

- **Casual consistency**:
  - _Concurrent_ writes: No guarantees
  - Casually related writes: ordered

## Weak Consistency

- **Synchronization points**: operations (read, write, sync)
  - All updates prior to a sync point will be visible
  - No guarantee what happens in between
- **Variations**:
  - Single sync operations (sync)
  - Separate sync per subset of state (page)
  - Separate _entry/acquire_ vs _exit/release_ operations
- Pros: limit data movement and coherence operations
- Cons: maintain extra state for additional operations

# Lesson 20: Data Center Technologies

- Topics to be covered in this lesson:
  - Brief and high-level overview of challenges and technologies facing data centers
  - **Goal**: provide context for mechanisms from previous lessons
  - Multi-tier architectures for internet services
  - Cloud computing
  - Cloud and _big data_ technologies

## Internet Services

- **Internet service**: any type of service provided via web interface
- **Presentation**: static content
- **Business logic**: dynamic content
- **Database tier**: data store
  - Not necessarily separate processes on separate machines
  - Many available open source and proprietary technologies
- **Middleware**: supporting, integrative or value-added software technologies
  - In multi-process configurations: some form of IPC used, including RPC/RMI, shared memory, etc.

## Internet Service Architectures

- For scale: multi-process, multi-node (_scale out_ architecture)
  1. _Boss-worker_: front-end distributes requests to nodes
  2. _All equal_: all nodes execute any possible step in request processing, for any request (functionally homogeneous)
  3. _Specialized nodes_: nodes execute some specific step(s) in request processing for some request type (functionally heterogeneous)

## Homogeneous Architectures

- **Functionally homogeneous**:
  - Each node can do any processing step
  - Pros:
    - Keeps front-end simple
    - Does not mean that each node has all data, just each node can get to all data
  - Cons:
    - How to benefit from caching?

## Heterogeneous Architectures

- **Functionally heterogeneous**:
  - Different nodes, different tasks/requests
  - Data does not have to be uniformly accessible everywhere
  - Pros:
    - Benefit of locality and caching
  - Cons:
    - More complex front-end
    - More complex management

## Cloud Computing Requirements

- **Traditional approach**:
  - Buy and configure resources: determine capacity based on expected demand (peak)
  - When demand exceeds capacity:
    - Dropped requests
    - Lost opportunity
- **Ideal cloud**:
  - Pros:
    - Capacity scales elastically with demand
    - Scaling instantaneous, both up and down
      - Cost is proportional to demand, to revenue opportunity
    - All of this happens automatically, no need for hacking wizardry
    - Can access anytime, anywhere
  - Cons:
    - Don't _own_ resources
- **Cloud computing requirements** (summarized):
  - On-demand, elastic resources and services
  - Fine-grained pricing based on usage
  - Professionally managed and hosted
  - API-based access

## Cloud Computing Overview

- **Shared resources**:
  - Infrastructure and software/services
- **APIs for access and configuration**:
  - Web-based, libraries, command line, etc.
- **Billing/accounting services**:
  - Many models: spot, reservation, entire marketplace
  - Typically discrete quantities: tiny, medium, x-large, etc.
- **Managed by cloud provider**

## Why Does Cloud Computing Work?

- **Law of large numbers**:
  - Per customer there is large variation in resource needs
  - Average across many customers is roughly constant
- **Economies of scale**:
  - Unit cost of providing resources or service drops at _bulk_

## Cloud Computing Vision

> If computers of the kind I have advocated become computers of the future, then computing many some day be organized as a public utility, just as the telephone system is a public utility... The computer utility could become the basis of a new and important industry. (_John McCarthy, MIT Centennial, 1961_)

- Computing: fungible utility
- Limitations exist: API lock-in, hardware dependence, latency, privacy, security, etc.

## Cloud Deployment Models

- **Public**: third-party customers/tenants
- **Private**: leverage technology internally
- **Hybrid (public + private)**: fail over, dealing with spikes, testing
- **Community**: used by certain type of users

## Cloud Service Models

- **On-premise**:
  - You must manage all components and services
- **IaaS (Infrastructure as a Service)**:
  - You manage components such as applications, data, run-time, middleware, OS
  - Others manage virtualization, servers, storage, and networking
- **PaaS (Platform as a Service)**:
  - You manage components such as applications and data
  - Others manage run-time, middleware, OS, virtualization, servers, storage, and networking
- **SaaS (Software as a Service)**:
  - Opposite of on-premise, others manage all components and services

## Requirements for the Cloud

1. _Fungible_ resources
2. Elastic, dynamic resource allocation methods
3. Scale: management at scale, scalable resources allocations
4. Dealing with failures
5. Multi-tenancy: performance and isolation
6. Security

## Cloud Enabling Technologies

- **Virtualization**:
  - Resource provisioning (scheduling)
- **Big data** processing (Hadoop MapReduce, Spark, etc.)
- Storage:
  - Distributed front-end (_append only_)
  - NoSQL, distributed in-memory caches
- Software-defined networking, storage, data centers, etc.
- Monitoring: real-time log processing (e.g., AWS CloudWatch)

## The Cloud as a Big Data Engine

- Data storage layer
- Data processing layer
- Caching layer
- Language front-ends (e.g., querying)
- Analytics libraries (e.g., ML)
- Continuously streaming data

# Lesson 21: Sample Final Questions

_No notes from this lesson_
