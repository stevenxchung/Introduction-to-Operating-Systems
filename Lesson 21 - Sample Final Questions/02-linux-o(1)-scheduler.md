# Problem 2: Linux O(1) Scheduler

For the next four questions, consider a Linux system with the following assumptions:

- Uses the O(1) scheduling algorithm for time sharing threads
- Must assign a time quantum for thread T1 with priority 110
- Must assign a time quantum for thread T2 with priority 135

Provide answers to the following:

1. Which thread has a "higher" priority (will be serviced first)?
2. Which thread is assigned a longer time quantum?
3. Assume T2 has used its time quantum without blocking. What will happen to the value that represents its priority level when T2 gets scheduled again?
   - Lower/decrease
   - Higher/increase
   - Same
4. Assume now that T2 blocks for I/O before its time quantum expired. What will happen to the value that represents its priority level when T2 gets scheduled again?
   - Lower/decrease
   - Higher/increase
   - Same

A: The answers are as follows,

1. The O(1) scheduling algorithm assigns higher priority to threads with a lower priority number (T1)
2. The O(1) scheduling algorithm dictates that higher priority tasks will have a longer time quantum (T1)
3. Increase, if T2 uses time quantum without blocking it should have a lower priority next time around
4. Decrease, if T2 blocks for I/O before time quantum expiration then priority will be higher due to blocking (more I/O intense)
