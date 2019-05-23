# Quiz 5: Multi-threading Patterns

For the 6-step toy order application, we have designed two solutions:

- A **boss-workers** solution
- A **pipeline** solution

Both solutions have six threads:

- In the **boss-workers** solution, a worker processes a toy order in 120 ms
- In the **pipeline** solution, each of the six stages (= step) take 20 ms

How long will it take for these solutions to complete 10 toy orders?
What about if there were 11 toy orders?

A: Using the following formulas:

- **Boss-worker formula**: `time_to_finish_one_order * ceiling * (num_orders / num_concurrent_threads)`
- **Pipeline formula**: `time_to_finish_first_order + (remaining_orders * time_to_finish_last_stage)`

We get the following:
-**Boss-workers (10)**: 240 ms
-**Boss-workers (11)**: 360 ms
-**Pipeline (10)**: 300 ms
-**Pipeline (11)**: 320 ms
