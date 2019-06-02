# Problem 7: Pipeline Model

An image web server has three stages with average execution times as follows:

- Stage 1: read and parse request (10 ms)
- Stage 2: read and process image (30 ms)
- Stage 3: send image (20 ms)

You have been asked to build a multi-threaded implementation of this server using the **pipeline model**. Using a **pipeline model**, answer the following questions:

1. How many threads will you allocate to each pipeline stage?
2. What is the expected execution time for 100 requests (in sec)?
3. What is the average throughput of the system in Question 2 (in req/sec)? Assume there are infinite processing resources (CPU's, memory, etc.).
