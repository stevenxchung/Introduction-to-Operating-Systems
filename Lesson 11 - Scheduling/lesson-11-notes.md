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
    - Time slice expired timeout
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
