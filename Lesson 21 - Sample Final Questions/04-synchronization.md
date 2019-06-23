# Problem 4: Synchronization

In a multi-processor system, a thread is trying to acquire a locked mutex.

1. Should the thread spin until the mutex is released or block?
2. Why might it be better to spin in some instances?
3. What if this were a uni-processor system?

A: The answers are as follows,

1. Spin if thread is running on another CPU, otherwise block
2. Spinning is better than accumulating overhead for context switching
3. Block when using uni-processor system since there is no way to run threads in parallel on a single-core processor system
