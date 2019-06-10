# Quiz 3: Spinlock 2

Does this **spinlock implementation** (see lecture slide) correctly guarantee **mutual exclusion**? Is it **efficient**?

A: The answer is as follows,

- Mutual exclusion for this spinlock implementation is still incorrect:
  - If threads are allowed to execute concurrently, there is not way to guarantee that a race condition will not occur (need hardware support)
- It is also still not efficient:
  - Continuous loop will spin as long as the lock is busy
