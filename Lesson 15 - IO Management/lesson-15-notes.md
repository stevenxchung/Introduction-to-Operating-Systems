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
