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

- Basic I/O device features:
  - Control registers:
    - Command
    - Data transfers
    - Status
  - Micro-controller (device's CPU)
  - On device memory
  - Other logic: e.g., analog to digital converters

## CPU Device Interconnect

- Peripheral Component Interconnect (PCI):
  - PCI express (PCIe)
- Other types of interconnects:
  - SCSI (small computer system interface) bus
  - Peripheral bus
  - Bridges handle differences

## Device Drivers

- Per each device type
- Responsible for device access, management and control
- Provided by device manufacturers per OS/version
- Each OS standardizes interfaces:
  - Device independence
  - Device diversity

## Types of Devices

- **Block: disk**
  - Read/write blocks of data
  - Direct access to arbitrary block
- **Character: keyboard**
  - Get/put character
- **Network devices**
- OS representation of a device: special device file

## Device Interactions

- Access device registers: memory load/store
- **Memory-mapped I/O**:
  - Part of _host_ physical memory dedicated for device interactions
  - BAR (base address registers)
- **I/O port**:
  - Dedicated in/out instructions for device access
  - Target device (I/O port) and value in register
- **Interrupt**:
  - Pros: can be generated as soon as possible
  - Cons: interrupt handling steps
- **Polling**:
  - Pros: When convenient for OS
  - Cons: delay or CPU overhead

## Device Access PIO

- No additional hardware support
- CPU _programs_ the device:
  - Via command registers
  - Via data movement
- An example of a PIO (programmed I/O): NIC data (network packet shown in lecture)
  - Write command to request packet transmission
  - Copy packet to data registers
  - Repeat until packet sent

## Device Access DMA

- Relies on DMA (direct memory access) controller
- CPU _programs_ the device:
  - Via command registers
  - Via DMA controls
- An example of a DMA: NIC data (network packet shown in lecture)
  - Write command to request packet transmission
  - Configure DMA controller with **in-memory address and size of packet buffer**
  - Less steps but DMA config is more complex
- For DMAs:
  - Data buffer must be in physical memory until transfer completes: pinning regions (non-swappable)

## Typical Device Access

- _See lecture for diagram_
- Typical device access includes the following:
  - System call
  - In-kernel stack
  - Driver invocation
  - Device request configuration
  - Device performs request

## OS Bypass

- _See lecture for diagram_
- Device regs/data directly accessible
- OS configures then out-of-the-way
- **User-level driver**:
  - OS retains coarse-grain control
  - Relies on device features:
    - Sufficient registers
    - Demux capability

## Sync vs Async Access

- _See lecture for diagram_
- **Synchronous I/O operations**: process blocks
- **Asynchronous I/O operations**: process continues
  - Process checks and retrieves result
  - Process is notified that the operation completed and results are ready

## Block Device Stack

- _See lecture for diagram_
- Processes use files: logical storage unit
- Kernel file system (FS):
  - Where and how to find and access file
  - OS specifies interface
- Generic block layer:
  - OS standardized block interface
- Device driver

## Virtual File System

- Problem: how to address the following?
  - What if files are on more than one device?
  - What if devices work better with different file system implementations?
  - What if files are not on a local device (accessed via network)?
- Solution: use a file system

## Virtual File System Abstractions

- **File**: elements on which the VFS (virtual file system) operations
- **File descriptor**: OS representation of file
  - Open, read, write, send file, lock, close, etc.
- **Inode**: persistent representation of file _index_
  - List of all data blocks
  - Device, permissions, size, etc.
- **Dentry**: directory entry, corresponds to single path component
- **Superblock**: file system specific information regarding the file system layout

## VFS on Disk

- **File**: data blocks on disk
- **Inode**: track files' blocks and also resides on disk in some block
- **Superblock**: overall map of disk blocks
  - Inode blocks
  - Data blocks
  - Free blocks

## `ext2`: Second Extended File System

- For each block group:
  - **Superblock**: number of inodes, disk blocks, start of free blocks
  - **Group descriptor**: bitmaps, number of free nodes, directories
  - **Bitmaps**: tracks free blocks and inodes
  - **Inodes**: one to max number (one per file)
  - **Data blocks**: file data

## Inodes

- **Inodes**: index of all disk blocks corresponding to a file
  - File: identified by inode
  - Inode: list of all blocks plus other metadata
- Pros: easy to perform sequential or random access
- Cons: limit on file size

## Inodes with Indirect Pointers

- **Inodes with indirect pointers**: index of all disk blocks corresponding to a file
- Inodes contain:
  - Metadata
  - Pointers to blocks
- **Direct pointer**: points to data block
- **Indirect pointer**: block of pointers
- **Double indirect pointer**: block of block of pointers
- Pros: small inode means large file size
- Cons: file access slow down

## Disk Access Optimizations

- **Caching/buffering**: reduce number of disk accesses
  - Buffer cache in main memory
  - Read/write from cache
  - Periodically flush to disk (`fsync()`)
- **I/O scheduling**: reduce disk head movement
  - Maximize sequential vs random access
- **Prefetching**: increase cache hits
  - Leverages locality
- **Journaling/logging**: reduce random access
  - _Describe_ write in log: block, offset, value, etc.
  - Periodically apply updates to proper disk locations
