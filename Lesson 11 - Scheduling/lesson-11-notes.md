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
  - *T2* arrives first
  - *T2* should be preempted
- **Heuristics based on history**: job running time
- How long did a task run last time?
- How long did a task run last *n* times?

## Preemptive Scheduling: Priority

- **Priority scheduling**:
  - Tasks have different priority levels
  - Run highest priority tasks next (preemption)
  - Run-queue is equal to per priority queues, tree ordered based on priority, etc.
  - Low priority tasks stuck in a run-queue (starvation)
  - *Priority aging* is where `priority = f(actual priority, time spend in run queue)`
  - Eventually task will run (prevents starvation!)

## Priority Inversion

- Assume SJF (see lecture for table and graph):
  - Priority: *T1*, *T2*, *T3*
  - Order of execution: *T2*, *T3*, *T1* (priorities inverted)
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
