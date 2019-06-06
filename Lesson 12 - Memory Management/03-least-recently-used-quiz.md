# Quiz 3: Least Recently Used

Suppose you have an array with **11 page-sized entries** that are **accessed one-by-one and then manipulated one-by-one in a loop**. Also, suppose you have a system with **10 pages of physical memory**.

What is the **percentage of pages** that will need to be **demand paged using the LRU policy**? (round to the nearest %)

Assume the following structure:

```c
int i = 0;
int j = 0;

while(1) {
    for(i = 0; i < 11; ++i) {
        // access page[i]
    }

    for(j = 0; j < 11; ++j) {
        // manipulate page[i]
    }
    break;
}
```
