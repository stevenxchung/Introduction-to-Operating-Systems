# Quiz 3: Condition Variable

Recall the consumer code from the previous example for **condition variables**. Instead of `while` why did we not simply use `if`?

- Option 1: `while` can support multiple consumer threads
- Option 2: cannot guarantee access to *m* once the condition is signaled
- Option 3: the list can change before the consumer gets access again
- Option 4: all of the above

A: The valid answer is Option 4, all answers are valid.
