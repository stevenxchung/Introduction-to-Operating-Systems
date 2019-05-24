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
