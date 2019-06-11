# Quiz 6: Queueing Lock Array

Assume we are using **Anderson's queueing spinlock implementation** where each array element of the **queue** can have one of two values: `has_lock(0)` and `must_wait(1)`. If a system has 32 CPUs, then how large is the **array data structure**?

- Option 1: 32 bits
- Option 2: 32 bytes
- Option 3: neither

A: The answer is Option 3 since the size of the data structure depends on the size of the cache line.
