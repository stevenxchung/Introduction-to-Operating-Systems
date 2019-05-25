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
