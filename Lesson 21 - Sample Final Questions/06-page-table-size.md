# Problem 6: Page Table Size

Consider a 32-bit (x86) platform running Linux that uses a single-level page table. What are the **maximum number of page table entries** when the following page sizes are used?

1. Regular (4 kB) pages?
2. Large (2 MB) pages?

A: The following answers are valid,

1. We would need 20 bits for the regular pages so $2^{20}$ entries for each virtual page
2. We would need 11 bits for the large pages so $2^{11}$ entries for each virtual page
