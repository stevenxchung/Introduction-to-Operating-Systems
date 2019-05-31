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
     if (out == (in + 1) % BUFFERSIZE)) // buffer full
        condition_wait(&not_full);
   add_item(buffer[in]); // add item
     in = (in + 1) % BUFFERSIZE
      cond_broadcast(&not_empty);

} // end producer code
```

- **Consumer Code**:

```c
   while (more_to_consume) {
   mutex_lock(&m);
   if (out == in) // buffer empty
     condition_wait(&not_empty);
   remove_item(out);
   out = (out + 1) % BUFFERSIZE;
   condition_signal(&not_empty);

} // end consumer code
```
