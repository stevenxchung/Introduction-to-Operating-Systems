# Problem 4: Calendar Critical Section

A shared calendar supports three types of operations for reservations:

1. Read
2. Cancel
3. Enter

Requests for cancellations should have priority above reads, who in turn have priority over new updates.

In pseudo-code, write the critical section enter/exit code for the **read** operation.
