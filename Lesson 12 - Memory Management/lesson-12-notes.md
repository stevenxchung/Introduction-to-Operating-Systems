# Lesson 12: Memory Management

- Topics to be covered in this lesson:
  - Physical and virtual memory management
  - Review of memory management mechanisms
  - Illustration of advanced services

## Visual Metaphor

- **OS** and **toy shops** each have **memory (part) management systems**:
  - Uses intelligently sized containers:
    - Memory pages or segments
  - Not all memory is needed at once:
    - Tasks operate on subset of memory
  - Optimized for performance:
    - Reduce time to access state in memory (better performance)

## Memory Management: Goals

- Virtual vs physical memory:
  - Allocate: Allocation, replacement, etc.
  - Arbitrate: Address translation and validation
- Page-based memory management:
  - Allocate: Pages to page frames
  - Arbitrate: Page tables
- Segment-based memory management:
  - Allocate: Segments
  - Arbitrate: segment registers

## Memory Management: Hardware Support

- MMU (memory management unit):
  - Translate **virtual** to **physical addresses**
  - Reports faults: illegal access, permission not present in memory
- Registers:
  - Pointers to page table
  - Base and limit size, number of segments, etc.
- Cache - TLB (translation look-aside buffer):
  - Valid virtual address to physical address translations: TLB
- Translation:
  - Actual PA generation done in hardware

## Page Tables

- Virtual memory pages and physical memory page frames are the same size
- Useful acronyms for page tables:
  - VPN (virtual page number)
  - PFN (physical frame number)
- Page table has allocation on first touch!
- Unused pages are reclaimed:
  - Mapping invalid
  - Hardware will fault
  - Re-establish on re-access
- In summary, the OS creates a page table for every process:
  - On context switch, switch to valid page table
  - Update register

## Page Table Entry

- Flags:
  - Present (valid/invalid)
  - Dirty (written to)
  - Accessed (for read or write)
  - Protection bits (read, write, and execute)
- **Page fault**:
  - Two options for PFN:
    - Generate physical address and access
    - Generate error code on kernel stack (trap into kernel)
  - Page fault handler determines action based on error code and faulting address:
    - Bring page from disk to memory
    - Protection error (`SIGSEGV`)
    - Error code from PTE flags
    - Faulting address CR2 register

## Page Table Size

- **64-bit Architecture**:
  - PTE (Page Table Entry): 8 bytes including PFN + flags
  - VPN: 2^64 / page size
  - Page size: (2^64 / 2^12) \* 8 bytes = 32 petabytes per process
- **Process** does not use entire address space:
  - Even on 32-bit architecture will not always use all of 4 GB
  - But **page table** assumes an entry per **VPN**, regardless of whether corresponding virtual memory is needed or not

## Multi-level Page Tables

- **Outer page table**: page table directory
- **Internal page table**: only for valid virtual memory regions
- **Additional layers**:
  - Page table directory pointer (third level)
  - Page table directory point map (fourth level)
    - Important on 64-bit architectures
    - Larger and more sparse
    - Larger gaps could save more internal page table components
- **Multi-level page tables**:
  - Pros:
    - Smaller internal page tables/directories
    - Granularity of coverage (potential reduced page table size)
  - Cons:
    - More memory access required for translation (increased translation latency)
