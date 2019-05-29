# Quiz 1: Models and Memory

Of the three **models** mentioned so far, which **model** likely requires **least amount of memory**?

- Boss-worker model
- Pipeline model
- Event-driven model

Why do you think this **model** requires the **least amount of memory**?

A: Event-driven model requires the least amount of memory since it operates on a single thread. Extra memory is only required for helper thread for concurrent blocking I/O, not for all concurrent requests
