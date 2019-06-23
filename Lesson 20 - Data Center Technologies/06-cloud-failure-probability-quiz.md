# Quiz 6: Cloud Failure Probability

A hypothetical cloud has `N = 10` components (CPUs). Each has failure probability of `p = 0.03`. What is the probability that there will be a **failure** somewhere in the system? What if the system has `N = 100` components?

A: Using the given equation in lecture $P_{system} = 1-((1-P)^N) * 100$, the answers are as follows,

- `N = 10 and p = 0.03`: probability for system failure is 26 %
- `N = 100 and p = 0.03`: probability for system failure is 95 %
