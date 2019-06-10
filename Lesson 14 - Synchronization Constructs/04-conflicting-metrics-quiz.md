# Quiz 4: Conflicting Metrics

1. Reduce **latency**:

- _Time to acquire a free lock_
- Ideally immediately execute atomic

2. Reduce **waiting time (delay)**:

- _Time to stop spinning and acquire a lock that has been freed_
- Ideally immediately

3. Reduce **contention**:

- _Bus/network I/C traffic_
- Ideally zero

Among the described **metrics** are there any conflicting goals? Check all that apply.

- Option 1: 1 conflicts with 2
- Option 2: 1 conflicts with 3
- Option 3: 2 conflicts with 3

A: The correct answer is Option 2 and 3.
