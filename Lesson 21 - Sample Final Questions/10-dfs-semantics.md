# Problem 10: DFS Semantics

Consider the following timeline where 'f' is distributed shared file and P1 and P2 are processes:

![dfs-semantics-diagram](https://s3.amazonaws.com/content.udacity-data.com/courses/ud923/notes/ud923-final-dfs-semantics.png)

Other Assumptions:

- 't' represents the time intervals in which functions execute
- The 'w' flag means write/append
- The 'r' flag means read
- The original content of 'f' was _a_
- The `read()` function returns the entire contents of the file

For each of the following DFS semantics, what will be read -- **the contents of 'f'** -- by P2 when t = 4s?

1. UNIX semantics
2. NFS semantics
3. Sprite semantics

A: The following answers are valid,

1. `ab` since all updates are instantaneous
2. `a` since the write at 2 seconds would not be read
3. `ab` since a check occurs for *P1* most recent value
