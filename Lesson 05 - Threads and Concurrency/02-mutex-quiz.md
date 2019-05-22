# Quiz 2: Mutex

Threads *T1-T5* are contending for a mutex *m*, *T1* is the first to obtain the mutex. Which thread will get access to *m* after *T1* releases it?

- T2
- T3
- T4
- T5

A: From the diagram in lecture, only *T2*, *T4*, and *T5* are valid, *T3* does not open up until later in time.
