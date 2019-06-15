# Lesson 16: Remote Procedure Calls

- Topics to be covered in this lesson:
  - RPC (remote procedure calls)

## Why RPC?

- **Example 1: Get File App**
  - Client-server
  - **Create** and **init sockets**
  - **Allocate** and **populate buffers**
  - **Include _protocol_ info** (e.g., get file, size, etc.)
  - **Copy data** into buffers (e.g., filename, file, etc.)
- **Example 2: Mod Image App**
  - Client-server
  - **Create** and **init sockets**
  - **Allocate** and **populate buffers**
  - **Include _protocol_ info** (e.g., algorithm, parameters, etc.)
  - **Copy data** into buffers (e.g., image data, etc.)
- Common steps (highlighted in bold) related to remote IPC (inter-process communication): RPC

## Benefits of RPC

- RPC is intended to simplify the development of cross-address space and cross-machine interactions
- Pros:
  - Higher-level interface for data movement and communication
  - Error handling
  - Hiding complexities of cross-machine interactions

## RPC Requirements

- Some requirements of RPCs include:
  - Client/server interactions
  - Procedure call interface:
    - Sync call semantics
  - Type checking
    - Error handling
    - Packet bytes interpretation
  - Cross-machine conversion
    - E.g., big/little endian
  - Higher-level protocol
    - Access control, fault tolerance, etc.
    - different transport protocols

## Structure of RPC

- _See lecture slides for figure_
- The execution order of an RPC is as follows:
  1. Client call to procedure
  2. Stub builds message
  3. Message is sent across the network
  4. Server OS hands message to server stub
  5. Stub unpacks message
  6. Stub makes local call to _add_

## Steps in RPC

- There are some general steps in RPC:
  1. **Register**: server _registers_ procedure, argument types, location, etc.
  2. **Bind**: client finds and _binds_ to desired server
  3. **Call**: client makes RPC call; control passed to sub, client code blocks
  4. **Marshal**: client stub _marshals_ arguments (serialize arguments into buffer)
  5. **Send**: client sends message to server
  6. **Receive**: server receives message; passes message to server-stub; access control
  7. **Unmarshal**: server stub _unmarshals_ arguments (extracts arguments and creates data structures)
  8. **Actual call**: server stub calls local procedure implementation
  9. **Result**: server performs operation and computes result of RPC operation
- The above steps are similar on return

## Interface Definition Language

- What can the server do?
- What arguments are required for the various operations (need agreement!)?
- Why:
  - Client-side bind decision
  - Run-time to automate stub generation: IDL (interface definition language)

## Specifying an IDL

- An IDL used to describe the interface the server exports
- RPC can use IDL that is:
  - Language-agnostic
  - Language-specific
- Remember that an IDL is just an interface not an implementation!

## Binding

- Client determines:
  - Which server should it connect to?
  - How will it connect to that server?
- **Registry**: database of available services
  - Search for service name to find a service (which) and contact details (how)
- **Distributed**:
  - Any RPC service can register
- **Machine-specific**:
  - For services running on same machine
  - Clients must known machine address: registry provides port number needed for connection
- **Needs naming protocol**:
  - Exact match for _add_
  - Or consider _summation_, _sum_, _addition_, etc.

## Visual Metaphor

- Applications use **binding and registries** like toy shops use directories of **outsourcing services**:
- Who can provide services?
  - Look u registry for image processing
- What services are provided?
  - Compress, filter, version number, etc. (IDL)
- How will they send/receive?
  - TCP/UDP (registry)

## What About Pointers?

- Solutions:
  - No pointers!
  - Serialize pointers; copy referenced _pointed to_ data structure to send buffer

## Handling Partial Failures

- When a client hangs, what is the problem?
  - Server, service, or network down? Message lost?
  - Timeout and retry (no guarantees!)
- Special RPC error notification (signal, exception, etc.):
  - Catch all possible ways in which the RPC call can (partially) fail
