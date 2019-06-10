# Quiz 2: Spinlock 1

Does this **spinlock implementation** (see lecture slide) correctly guarantee **mutual exclusion**? Is it **efficient**?

A: The answer is as follows,

- Mutual exclusion for this spinlock implementation is incorrect:
  - It is possible that more than one thread will see if the lock is free at the same time
- It is also not efficient:
  - As long as lock is not free, `goto spin` will be executed so the cycle will be repeated executed (waste of CPU resources)
