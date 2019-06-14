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

## Virtualization Models: Bare-metal

- **Bare-metal**: hypervisor-based
  - VMM (hypervisor) manages all hardware resources and supports execution of VMs
  - Privileged, service VM to deal with devices
- Xen (open source or Citrix XenServer):
  - DomO and DomU
  - Drivers in DomO
- ESX (VMWare):
  - Many open APIs
  - Drivers in VMM
  - Used to have Linux control core, now remote APIs

## Virtualization Models: Hosted

- **Hosted**:
  - Host OS owns all hardware
  - Special VMM module provides **hardware interfaces** to VMs and deals with VM context switching
- Example: KVM (kernel-based VM shown in lecture)
  - Based on Linux
  - KVM kernel module plus QEMU (Quick Emulator) for hardware virtualization
  - Leverages Linux open-source community

## Processor Virtualization

- **Trap-and-emulate**:
  - Guest instructions are executed directly by hardware
  - For non-privileged operations: hardware speeds must provide efficiency
  - For privileged operations: trap to hypervisor
  - Hypervisor determines what needs to be done:
    - If illegal operation: terminate VM
    - If legal operation: emulate the behavior the guest OS was expecting from the hardware

## x86 Virtualization in the Past

- **x86 virtualization pre-2005**
  - Four rings, no root/non-root modes yet
  - Hypervisor in ring 0, guest OS in ring 1
  - However, 17 privileged instructions do not trap, they fail silently!
- Cons:
  - Hypervisor does not know so it does not try to change settings
  - OS does not know, so it assumes change was successful

## Binary Translation

- **Main idea**: rewrite the VM binary to never issue those 17 instructions
  - Pioneered by Mendel Rosenblum's group at Stanford, commercialized as VMware
- **Binary translation**:
  - Goal: full virtualization (guest OS not modified)
  - Approach: dynamic binary translation
- Inspect code blocks to be executed
- If needed, translate to alternate instruction sequence
- Otherwise, run at hardware speeds

## Paravirtualization

- Goal: performance, give up on unmodified guests
- Approach: paravirtualization, modify guest so that...
  - It knows it's running virtualized
  - It makes explicit calls to the hypervisor (hypercalls)
  - **Hypercall**: system calls
    - Package context info
    - Specify desired hypercall
    - Trap to VMM
