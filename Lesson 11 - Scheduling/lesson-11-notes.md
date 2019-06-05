# Lesson 11: Scheduling

- Topics to be covered in this lesson:
  - Scheduling mechanisms, algorithms and data structures
  - Linux O(1) and CFS schedulers
  - Scheduling on multi-CPU platforms

## Visual Metaphor

- Like an **OS scheduler**, a **toy shop manager** schedules work:
  - Assign task immediately:
    - Scheduling is simple (first-come first-serve)
  - Assign simple tasks first:
    - Maximize throughput (shortest job first)
  - Assign complex tasks first:
    - Maximize utilization of CPU devices, memory, etc.

## CPU Scheduling

- The **CPU scheduler**:
  - Decides how and when **processes** (and their **threads**) access shared CPUs
  - Schedules tasks running **user-level processes/threads** as well as **KLTs**
  - Chooses one of ready **tasks** to run on CPU when:
    - CPU becomes idle
    - New **task** becomes ready
    - Time-slice expired timeout
  - **Thread** is dispatched on CPU
- Scheduling is equivalent to choosing a **task** from ready queue:
  - Which **task** should be selected?
    - Scheduling policy/algorithm
  - How is this done?
    - Depends on run-queue data structure (run-queue is the scheduling algorithm)

## Run To Completion Scheduling

- Initial assumptions:
  - Group of tasks/jobs
  - Known execution times
  - No preemption
  - Single CPU
- Metrics:
  - Throughput
  - Average job completion time
  - Average job wait time
  - CPU utilization
- First-come first-serve (FCFS):
  - Schedules tasks in order of arrival
  - Run-queue is the same as queue (FIFO)
- Shortest job first (SJF):
  - Schedules tasks in order of their execution time
  - Run-queue is the same as ordered queue or tree

## Preemptive Scheduling: SJF + Preempt

- **SJF + Preemption**:
  - _T2_ arrives first
  - _T2_ should be preempted
- **Heuristics based on history**: job running time
- How long did a task run last time?
- How long did a task run last _n_ times?

## Preemptive Scheduling: Priority

- **Priority scheduling**:
  - Tasks have different priority levels
  - Run highest priority tasks next (preemption)
  - Run-queue is equal to per priority queues, tree ordered based on priority, etc.
  - Low priority tasks stuck in a run-queue (starvation)
  - _Priority aging_ is where `priority = f(actual priority, time spend in run queue)`
  - Eventually task will run (prevents starvation!)

## Priority Inversion

- Assume SJF (see lecture for table and graph):
  - Priority: _T1_, _T2_, _T3_
  - Order of execution: _T2_, _T3_, _T1_ (priorities inverted)
  - Solution:
    - Temp boost priority of mutex owner
    - Lower again release

## Round Robin Scheduling

- Pick up first tasks from queue (like FCFS)
- Task may yield, to wait on I/O (unlike FCFS)
- Round robin with priorities:
  - Include preemption
- Round robin with interleaving:
  - Time-slicing

## Time-sharing and time-slices

- **Time-slice** - maximum amount of uninterrupted time given to a task (time quantum)
- Task may run less than time-slice time:
  - Has to wait for I/O, synchronization, etc. (will be placed on a queue)
  - Higher priority task becomes runnable
- Using time-slices tasks are interleaved (time-sharing the CPU):
  - CPU bound tasks (preempted after time-slice)
- Pros:
  - Short tasks finish sooner
  - More responsive
  - Lengthy I/O operations initiated sooner
- Cons:
  - Overheads (interrupt, schedule, context switch)

## Summarizing Time-slice Length

- How long should a time-slice be?
  - **CPU bound tasks prefer longer time-slices**:
    - Limits context switching overheads
    - Keeps CPU utilization and throughput high
  - **I/O bound tasks prefer shorter time-slices**:
    - I/O bound tasks can issue I/O operations earlier
    - Keeps CPU and device utilization high
    - Better used perceived performance

## Run-queue Data Structure

- If we want I/O and CPU bound tasks have different time-slice values, then...
  - Same run-queue, check type, etc.
  - Two different structures
- One solution: use a multi-queue data structure with separate internal queues
  - First time-slice is most I/O intensive (highest priority)
  - Second time-slice is medium I/O intensive (mix of I/O and CPU processing)
  - Third and beyond time-slice is CPU intensive (lowest priority)
  - Pros:
    - Time-slicing benefits provided for I/O bound tasks
    - Time-slicing overheads avoided for CPU bound tasks
- Handling different time-slice values:
  - Tasks enter top-most queue
  - If task yields voluntarily keep task at this level
  - If task uses up entire time-slice push down to lower level
  - Task in lower queue gets priority boost when releasing CPU due to I/O waits
- In summary, MLFQ (multi-level feedback queue) is not a priority queue (MLFQ has a feedback mechanism) and offer different treatment of threads at each level

## Linux O(1) Scheduler

- The Linux O(1) scheduler has several of unique characteristics:
  - The name **O(1)** means it takes constant time to select/add task, regardless of task count
  - **Preemptive, priority-based**:
    - Real time (0-99)
    - Time-sharing (100-139)
  - **User processes**:
    - Default 120
    - Nice value (-20 to 19)
- Time-slice value for the Linux O(1) scheduler:
  - Depends on priority
  - Smallest for low priority
  - Highest for high priority
- Feedback for the Linux O(1) scheduler:
  - Sleep time: waiting/idling
  - Longer sleep: interactive
  - Smaller sleep: compute-intensive
- Run-queue for Linux O(1) scheduler: two arrays of tasks...
  - Active:
    - Used to pick next task to run
    - Constant time to add/select
    - Tasks remain in queue in active array until time-slice expires
  - Expired:
    - Inactive list
    - When no more tasks in active array (swap active and expired)

## Linux CFS Scheduler

- Problems with Linux O(1) scheduler:
  - Performance of interactive tasks is not satisfactory
  - Lacks fairness during task prioritization
- Solution: Linux CFS (Completely Fair Scheduler)
  - CFS is the default scheduler since Linux 2.6.23
  - Run-queue is based on a red-black tree:
    - Ordered by `vruntime` where `vruntime` is time spent on CPU
- CFS scheduling works as follows:
  - Always pick left-most node
  - Periodically adjust `vruntime`
  - Compare to left-most `vruntime`:
    - If smaller, continue running
    - If larger, preempt and place appropriately in the tree
  - `vruntime` progress rate depends on priority and niceness:
    - Rate fast for low-priority
    - Rate slower for high-priority
    - Same tree for all priorities
  - Performance:
    - Select task: _O(1)_
    - Add task: _O(log(n))_

## Scheduling on Multi-processors

- **Cache-affinity** important!
  - Keeps tasks on the same CPU as much as possible
  - Hierarchical scheduler architecture
- **Per-CPU run-queue** and **scheduler**:
  - Load balance across CPUs based on queue length or when CPU is idle
- **NUMA (Non-uniform Memory Access)**:
  - Multiple memory nodes
  - Memory node closer to a _socket_ of multiple processors:
    - Access to local memory node faster than access to remote memory node
    - Keep tasks on CPU closer to memory node where their state is
    - NUMA-aware scheduling

## Hyper-threading

- Multiple hardware-supported execution contexts
- Still one CPU but with **very fast** context switch:
  - Hardware multi-threading
  - Hyper-threading
  - CMT (chip multi-threading)
  - CMT (simultaneous multi-threading)

## Scheduling for Hyper-threading

- **Assumptions**:
  - Thread issues instruction on each cycle (one max IPC or instruction per cycle)
  - Memory access (four cycles)
  - Hardware switching instantaneous
  - SMT with two hardware threads
- Threads _interfere_ and _contend_ for CPU pipeline resource:
  - Performance degrades
  - Memory degrades
- CPU idle: waste CPU cycles
- Mix of CPU and memory-intensive threads:
  - Avoid/limit contention on processor pipeline
  - All components (CPU and memory) well utilized
  - However, still leads to interference and degradation but minimal

## CPU-bound or Memory-bound?

- Use historic information:
  - _Sleep time_ won't work:
    - The thread is not sleeping when waiting on memory
    - Software takes too much time to compute
- What about hardware counters?
  - Hardware counters estimate what kind of resources a thread needs
  - Scheduler can make informed decisions:
    - Typically multiple counters
    - Models with per architecture thresholds
    - Based on well-understood workloads
