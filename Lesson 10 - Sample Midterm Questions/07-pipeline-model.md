# Problem 7: Pipeline Model

An image web server has three stages with average execution times as follows:

- Stage 1: read and parse request (10 ms)
- Stage 2: read and process image (30 ms)
- Stage 3: send image (20 ms)

You have been asked to build a multi-threaded implementation of this server using the **pipeline model**. Using a **pipeline model**, answer the following questions:

1. How many threads will you allocate to each pipeline stage?
2. What is the expected execution time for 100 requests (in sec)?
3. What is the average throughput of the system in Question 2 (in req/sec)? Assume there are infinite processing resources (CPU's, memory, etc.).

A: The answers are as follows:

1. We need to vary the number of threads for each stage:
   1. Stage 1 needs one thread (1 \* 10 ms = 10 ms)
   2. Stage 2 needs three threads (3 \* 10 ms = 30 ms)
   3. Stage 3 needs two threads (2 \* 10 ms = 20 ms)
2. Around 1.05 s since the first request takes 60 ms (each stage added up), remaining 99 requests will take 10 ms.
3. If we complete 100 requests in 1.05 s then our rate is about 95.2 req/s.
