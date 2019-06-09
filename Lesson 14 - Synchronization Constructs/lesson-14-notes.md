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
