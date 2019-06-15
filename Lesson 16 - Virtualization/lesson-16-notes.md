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

## Defining Virtualization

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

## Memory Virtualization Full

- All guests expect contiguous physical memory, starting at 0
- Virtual vs physical vs machine addresses (VA vs PA vs MA) and page frame numbers
- Still leverages hardware MMU, TLB, etc.
- **Option 1**:
  - Guest page table: VA to PA
  - Hypervisor: PA to MA
  - **Too expensive!**
- **Option 2**:
  - Guest page tables: VA to PA
  - Hypervisor shadow PT: VA to MA
  - Hypervisor maintains consistence

## Memory Virtualization Paravirtualized

- **Paravirtualized**:
  - Guest aware of virtualization
  - No longer strict requirement on contiguous physical memory starting at 0
  - Explicitly registers page tables with hypervisor
  - Can _batch_ page table updates to reduce VM exits
  - _Other optimizations_
- **Bottom line**: overheads eliminated or reduced on newer platforms

## Device Virtualization

- For CPUs and memory:
  - Less diversity
  - ISA level (instruction set architecture level) _standardization_ of interface
- For devices:
  - High diversity
  - Lack of standard specification of device interface and behavior
- Three key models for device virtualization (see later slides)

## Passthrough Model

- **Approach**: VMM-level driver configures device access permissions
- Pros:
  - VM provided with exclusive access to the device
  - VM can directly access the device (VMM-bypass)
- Cons:
  - Device sharing difficult
  - VMM must have exact type of device as what VM expects
  - VM migration tricky

## Hypervisor Direct Model

- **Approach**:
  - VMM intercepts all device accesses
  - Emulate device operation:
    - Translate to generic I/O operation
    - Transverse VMM-resident I/O stack
    - Invoke VMM-resident driver
- Cons:
  - Latency of device operations
  - Device driver ecosystem complexities in hypervisor

## Split-device Driver Model

- **Approach**:
  - Device access control **split** between:
    - Front-end driver in guest VM (device API)
    - Back-end driver in service VM (or host)
    - Modified guest drivers
- Pros:
  - Eliminate emulation overhead
  - Allow for better management of shared devices

## Hardware Virtualization

- **AMD Pacifica and Intel Vanderpool Technology (Intel-VT)**, 2005:
  - _Close holes_ in x86 ISA
  - Modes: root/non-root (or _host_ and _guest_ mode)
  - VM control structure
  - Extended page tables and tagged TLB with VM ids
  - Multi-queue devices and interrupt routing
  - Security and management support
  - Additional instructions to exercise previously mentioned features
