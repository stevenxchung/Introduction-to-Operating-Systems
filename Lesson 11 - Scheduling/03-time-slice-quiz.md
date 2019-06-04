# Problem 3: Time-slice

On a single CPU system, consider the following workload and conditions:

- **10 I/O bound tasks** and **1 CPU bound** task
- I/O bound tasks issue an I/O op every **1 ms** of CPU computing
- I/O operations always take **10 ms** to complete
- Context switching overhead is **0.1 ms**
- All tasks are long running

What is the **CPU utilization** (%) for a **round robin scheduler** where the **time-slice** is **1 ms**? How about for a **10 ms time-slice**? (round to nearest percent)

A: The answers are as follows,

- 1 ms: 91 %
- 10 ms: 95 %
