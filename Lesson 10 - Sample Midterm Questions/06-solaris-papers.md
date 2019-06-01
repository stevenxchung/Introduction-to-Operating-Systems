# Problem 6: Solaris Papers

The implementation of Solaris threads described in the paper _Beyond Multiprocessing: Multi-threading the Sun OS Kernel_, describes four key data structures used by the OS to support threads.

For each of these data structures, **list at least two elements** they must contain.

1. Process
2. LWP
3. Kernel-threads
4. CPU

A: The answers are as follows,

1. Process must include at least information on user-level registers and a list of KLTs
2. LWP must include at least user-level registers and system call arguments
3. Kernel-threads must include at least kernel-level registers and scheduling information
4. CPU must include information on the current thread and a list of KLTs
