# Problem 5: Spinlocks

For the following question, consider a multi-processor with write-invalidated cache coherence.

Determine whether the use of a dynamic (exponential backoff) delay has the **same, better, or worse performance** than a test-and-test-and-set (“spin on read”) lock. Then, explain why.

Make a performance comparison using each of the following metrics:

1. Latency
2. Delay
3. Contention

A: The answers are as follows,

1. Latency is the same since operations are identical when lock is free
2. Delay is worst for dynamic delay since lock could be released during delay
3. Contention is better for dynamic delay since there exists a delay (does not trigger any additional memory access requests)
