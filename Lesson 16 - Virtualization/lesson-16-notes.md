# Lesson 16: Virtualization

- Topics to be covered in this lesson:
  - Overview of virtualization
  - Main technical approaches in popular virtualization solutions
  - Virtualization-related hardware advances

## What is Virtualization?

- **Virtualization** allows concurrent execution of multiple OS (and their applications) on the same physical machine
- **Virtual resources**: each OS thinks that it _owns_ hardware resources
- **Virtual machine (VM)**: OS applications and virtual resources (guest domain)
- **Virtualization layer**: management of physical hardware (virtual machine monitor, hypervisor)

## Definining Virtualization

- A **virtual machine** is an **efficient, isolated duplicated of the real machine** supported by a **VMM (virtual machine monitor)**:
  - Provides environment essentially identical with the original machine
  - Programs show at worst only minor decrease in speed
  - VMM is in complete control of system resources

## Benefits of Virtualization

- Pros:
  - Consolidation: decrease cost; improve manageability
  - Migration: availability, reliability
  - Security, debugging, support for legacy OS
