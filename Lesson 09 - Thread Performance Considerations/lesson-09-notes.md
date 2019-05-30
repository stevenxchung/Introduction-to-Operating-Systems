# Lesson 9: Thread Performance Considerations

- Topics to be covered in this lesson:
  - Performance comparisons:
    - Multi-process vs multi-threaded vs event-driven
  - Event-driven architectures
    - "Flash: An Efficient and Portable Web Server" vs Apache

## Which Threading Modeling is Better?

- Consider the _Boss-worker_ vs _Pipeline_ example as discussed in lesson 5 (see lecture for specific initial conditions):
  - We care about two metrics, execution time and average time to complete order
  - The _Boss-worker_ model has an execution time greater than that of the _Pipeline_ model (undesirable)
  - However, the _Boss-worker_ model has an average time to complete order less than that of the _Pipeline_ model (desirable)
  - Which model is better?
    - It really depends on the metrics!

## Are Threads Useful?

- Threads are useful because of:
  - Parallelization: speed up
  - Specialization: hot cache!
  - Efficiency: lower memory requirement and cheaper synchronization
- Threads hide latency of I/O operations (single CPU)
- Now consider what is useful...
  - For a matrix multiply application: execution time
  - For a web service application:
    - Number of client requests/time
    - Response time
  - For hardware: higher utilization (e.g., CPU)
- Again, it depends on the metrics!

## Visual Metaphor

- **Metrics** exist for OS and for toy shops (some examples below):
  - **Throughput**:
    - Process completion rate
  - **Response time**:
    - Average time to respond to input (e.g., mouse click)
  - **Utilization**:
    - Percentage of CPU

## Performance Metrics Intro

- Metrics are a measurement standard **measurable** and/or **quantifiable property** (e.g., execution time) of the **system** (software implementation of a problem) we're interested in that can be used to **evaluate the system behavior** (its improvement compared to other implementations)

## Performance Metrics

- What are some performance metrics computer scientists typically care about?
  - Previously covered metrics:
    - Execution time
    - Throughput
    - Request rate
    - CPU utilization
  - Other metrics one might care about:
    - Wait time
    - Platform efficiency
    - Performance/cost
    - Performance/power
    - Percentage of SLA violations
    - Client-perceived performance
    - Aggregate performance
    - Average resource usage

## Performance Metrics Summary

- Performance metrics are a **measurable quantity** obtained from:
  - Experiments with real software deployment, real machines, real workloads
  - _Toy_ experiments representative of realistic settings
  - Simulation: test-bed

## Really... Are Threads Useful?

- Depends on **metrics**!
- Depends on **workload**!
- Bottom line: it depends!

## Multi-process vs Multi-thread

- Consider how to best provide concurrency (see lecture for simple web server example):
  - **Multi-process web server**:
    - Pros: simple programming
    - Cons:
      - Many processes which means high memory usage costly context switch hard/costly to maintain shared state (tricky port setup)
  - **Multi-threaded web server**:
    - Pros:
      - Shared address space
      - Shared state
      - Cheap context switch
    - Cons:
      - Not simple implementation
      - Requires synchronization
      - Underlying support for threads

## Event-driven Model

- An event-driven model contains the following elements (see lecture for diagram):
  - **Event handlers**:
    - Accept connection
    - Read request
    - Send header
    - Read file/send data
  - **Dispatch loop**
  - **Events**:
    - Receipt of request
    - Completion of send
    - Completion of disk read
- An event driven model has a single address space, single process, and single thread of control!
- The **dispatcher** is in charge of state machine external events (call handler and jump to code)
- The **handler**:
  - Runs to completion
  - Facilitates blocking:
    - Initiate blocking operation and pass control to dispatch loop

## Concurrency in the Event-driven Model

- If the event-driven model operates on a single thread, how to achieve concurrency?
  - Single thread switches among processing of different requests
- **Multi-process and multi-threaded**:
  - One request per execution context (process/thread)
- **Event-driven**:
  - Many requests interleaved in an execution context

## Event-driven Model: Why

- Why does this work?
  - On one CPU, _threads hide latency_:
    - `if (t_idle > 2 * t_context_switch)`, context switch to hide latency
    - `if (t_idle == 0)`, context switching just wastes cycles that could have been used for request processing
- **Event-driven**:
  - Process request until wait necessary then switch to another request
- **Multiple CPUs**:
  - Multiple event-driven processes

## Event-driven Model: How

- How does this work?
  - **Event** is equal to input on FD (file descriptor)
- Which **file descriptor**?
  - `select()`
  - `poll()`
  - `epoll()`
- Benefits of event-driven model:
  - Single address space and single flow of control
  - Smaller memory requirement and no context switching
  - No synchronization

## Helper Threads and Processes

- Problem: for the event-driven model, a blocking request/handler will block the entire process
- Solution:
  - Use **asynchronous I/O operations**:
    - Process/thread makes system call
    - OS obtains all relevant into from stack and either learns where to return results, or tells caller where to get results later
    - Process/thread can continue
- However, an asynchronous system call requires support from kernel (e.g., threads) and/or device
- In general, asynchronous system calls fit nicely with the event-driven model!
- Another problem: what if async calls are not available?
  - Use **helpers**:
    - Designated for blocking I/O operations only
    - Pipe/socket based communication with event dispatcher
    - Helper blocks! But main event loop (and process) will not!
- Before, there were no multi-threaded solutions, therefore, a AMPED (Asymmetric Multi-process Event-driven Model) solution was created similar to that mentioned above
- With the addition of multi-threaded capabilities, the multi-threaded event-driven model discussed in previously became known as the AMTED (Asymmetric Multi-threaded Event-driven Model) solution
- In summary, helper threads/processes:
  - Pros:
    - Resolves portability limitations of basic event-driven model
    - Smaller footprint than regular worker thread
  - Cons:
    - Applicability to certain classes of applications
    - Event-driven routing on multi CPU systems

## Flash Web Server

- **Flash: event-driven web server**:
  - An **event-driven web server (AMPED)** with **asymmetric helper processes**
  - _Helpers_ used for disk reads
  - Pipes used for communication with dispatcher
  - Helper reads file in memory (via memory map)
  - Dispatcher checks (via mincore) if pages are in memory to decide _local handler_ or _helper_
- In general, a flash web server can offer possible big savings!
- **Flash: additional optimizations**:
  - Application-level caching (data and computation)
  - Alignment for DMA (direct memory access)
  - Use of DMA with scatter-gather, vector I/O operations
- Back in the day these optimizations would be novel, now they are fairly common

## Apache Web Server

- An Apache web server (diagram available in lecture slides) consists of the following elements:
  - **Core** - basic server skeleton
  - **Modules** - per functionality
  - **Flow of control** - similar to event-driven model
- However, an Apache web server differs in:
  - Combination of MP and MT:
    - Each process is equivalent to boss/worker with dynamic thread pool
    - Number of processes can also be dynamically adjusted

## Experimental Methodology

- To set up performance comparisons consider the following:
  - First, define the comparison points:
    - What systems are you comparing?
  - Second, define inputs:
    - What workloads will be used?
  - Third, define metrics:
    - How will you measure performance?

## Summary of Performance Results

- **When data is in cache**:
  - SPED (single-process event-driven) >> AMPED Flash:
    - Unnecessary test for memory presence
  - SPED and AMPED Flash >> MT/MP:
    - Sync and context switching overhead
- **Disk-bound workload**:
  - AMPED Flash >> SPED:
    - Blocks because no async I/O
  - AMPED Flash >> MT/MP:
    - More memory efficient and less context switching

## Advice on Designing Experiments

- **Design relevant experiments**: statements about a solution that others believe in and care for
- **Purpose of relevant experiments** (e.g., web server experiment):
  - Clients: response time
  - Operations: throughput
  - **Possible goals**:
    - Increase response time and throughput
    - Increase response time
    - Increase response time while decreasing throughput
    - Maintains response time when request rate increases
  - **Goals**: metrics and configuration of experiments
- _Rule of thumb_ for picking **metrics**:
  - Standard **metrics** equals broader audience
  - **Metrics** answering the _"Who? What? Why?"_ questions:
    - Client performance: response time, timed-out request, etc.
    - Operator costs: throughput, costs, etc.
- **Picking the right configuration space**:
  - **System resources**:
    - Hardware and software
  - **Workload**:
    - Web server: request rate, number of concurrent requests, file size, access pattern
  - **Now pick!**:
    - Choose a subset of configuration parameters
    - Pick ranges for each variable factor
    - Pick relevant workload
    - Include the best/worst case scenarios
- **Are you comparing apples to apples?**:
  - Pick useful combination of factors, many just reiterate the same point
- **What about the competition and baseline?**:
  - Compare system to:
    - State-of-the-art
    - Most common practice
    - Ideal best/worst case scenario

## Advice on Running Experiments

- If you have designed the experiments you should consider:
  - Running test cases _n_ times
  - Compute metrics
  - Represent results
- Additionally, do not forget about making conclusions!
