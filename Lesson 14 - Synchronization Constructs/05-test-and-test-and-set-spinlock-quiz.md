# Quiz 5: Test and Test and Set Spinlock

In an SMP system with **N processors**, what is the **complexity** of the memory contention (accesses), relative to N, that will result from releasing a `test_and_test_and_set` **spinlock** (code provided in lecture)?

- Cache coherent with `write_update` 
- Cache coherent with `write_invalidate`

A: The answers are as follows,

- *O(n)*
- *O(n^2)*
