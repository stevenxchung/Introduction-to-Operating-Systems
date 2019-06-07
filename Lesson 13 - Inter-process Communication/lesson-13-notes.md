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
