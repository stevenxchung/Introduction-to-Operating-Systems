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
