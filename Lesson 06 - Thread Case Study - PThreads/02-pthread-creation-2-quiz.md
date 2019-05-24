# Quiz 2: PThread Creation 2

**Code provided in lecture**.

What are the possible **outputs** to this program?

- Option 1:
  ```bash
  Thread number 0
  Thread number 1
  Thread number 2
  Thread number 3
  ```
- Option 2:
  ```bash
  Thread number 0
  Thread number 2
  Thread number 1
  Thread number 3
  ```
- Option 3:
  ```bash
  Thread number 0
  Thread number 2
  Thread number 2
  Thread number 3
  ```

A: All options are possible, there is no control over when each input thread is scheduled, `i` is a global variable, and all other threads see the new value. Additionally, a race condition is possible (a thread tries to read a value while another is modifying that value).
