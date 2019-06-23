# Problem 1: Time-slices

On a single CPU system, consider the following workload and conditions:

- 10 I/O-bound tasks and 1 CPU-bound task
- I/O-bound tasks issue an I/O operation once every 1 ms of CPU computing
- I/O operations always take 10 ms to complete
- Context switching overhead is 0.1 ms
- I/O device(s) have infinite capacity to handle concurrent I/O requests
- All tasks are long-running

Now, answer the following questions (for each question, round to the nearest percent):

1. What is the CPU utilization (%) for a round-robin scheduler where the time-slice is 20 ms?
2. What is the I/O utilization (%) for a round-robin scheduler where the time-slice is 20 ms?
