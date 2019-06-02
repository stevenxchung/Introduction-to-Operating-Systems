# Problem 8: Performance Observations

Here is a graph from the paper [*Flash: An Efficient and Portable Web Server*](https://s3.amazonaws.com/content.udacity-data.com/courses/ud923/references/ud923-pai-paper.pdf), that compares the performance of Flash with other web servers.

For data sets **where the data set size is less than 100 MB** why does...

1. Flash perform worse than SPED?
2. Flash perform better than MP?

A: The answers are as follows,

1. Flash checks the cache where SPED does not.
2. Flash uses cache where MP does not.
