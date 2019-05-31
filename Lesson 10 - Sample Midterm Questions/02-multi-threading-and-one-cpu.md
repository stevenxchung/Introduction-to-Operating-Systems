# Multi-threading and One CPU

Is there a benefit of multi-threading on one CPU?

- Yes
- No

A: Yes, reason are (from lecture):

- Threads can implement **parallelization** which can process the input much faster than if only a single thread on a single CPU had to process say, an entire matrix for example
- Threads may execute completely different portions of the program
- Threads can also utilize **specialization** which takes advantage of the hot cache present on each thread
- A multi-threaded application is more memory efficient and has lower memory requirements than its multi-processor alternative
- Additionally, a multi-threaded application incurs lower overheads for their inter-thread communication then the corresponding inter-process alternatives
