# Problem 3: Critical Section

In the (pseudo) code segments for the **producer code** and **consumer code**, mark and explain all the lines where there are errors.

- **Global Section**:

```c
int in, out, buffer[BUFFERSIZE];
mutex_t m;
cond_var_t not_empty, not_full;
```

- **Producer Code**:

```c
   while (more_to_produce) {
     mutex_lock(&m);
     if (out == (in + 1) % BUFFERSIZE)) // buffer full, should use a while loop
        condition_wait(&not_full); // I believe this needs a mutex input
   add_item(buffer[in]); // add item
     in = (in + 1) % BUFFERSIZE
      cond_broadcast(&not_empty); // Use signal instead

} // end producer code
```

- **Consumer Code**:

```c
   while (more_to_consume) {
   mutex_lock(&m);
   if (out == in) // buffer empty, should use while loop
     condition_wait(&not_empty); // Needs mutex input
   remove_item(out);
   out = (out + 1) % BUFFERSIZE;
   condition_signal(&not_empty); // Should be not_full
   // Insert mutex unlock here!
} // end consumer code
```
