# Lesson 15: I/O Management

- Topics to be covered in this lesson:
  - OS support for I/O devices
  - Block device stack
  - File system architecture

## Visual Metaphor

- **I/O** is like **a top shop shipping department**:
  - Have protocols:
    - Interfaces for device I/O
  - Have dedicated handlers:
    - Device drivers, interrupt handlers, etc.
  - Decouple I/O details from core processing:
    - Abstract I/O device detail from applications

## I/O Devices


