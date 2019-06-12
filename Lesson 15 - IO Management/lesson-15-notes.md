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
