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
