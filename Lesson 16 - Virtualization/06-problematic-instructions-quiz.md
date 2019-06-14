# Quiz 6: Problematic Instructions

In earlier x86 platforms the flags **privileged register** was accessed via the **instructions POPF (pop flags off stack) and PUSHF (push flags onto stack)** that **failed silently** if not called from **ring 0 (hypervisor)**. What do you think can occur as a result?

- Option 1: guest VM could not request interrupts enabled
- Option 2: guest VM could not request interrupts disabled
- Option 3: guest VM could not find out what is the state of the interrupts enabled/disabled bit
- Option 4: all of the above

A: The correct answer is Option 4, all of the above.
