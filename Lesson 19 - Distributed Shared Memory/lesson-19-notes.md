# Lesson 19: Distributed Shared Memory

- Topics to be covered in this lesson:
  - DSM (distributed shared memory)
  - Distributed state management and design alternatives
  - Consistency model

## Visual Metaphor

- **Managing distributed shared memory** is like **managing a tools/parts across all workspaces in a toy shop**:
  - Must decide placement:
    - Place memory (pages) close to relevant processes
  - Must decide migration:
    - When to copy memory (pages) from remote to local
  - Must decide sharing rules:
    - Ensure memory operations are properly ordered

## Reviewing DFS

- **Clients**:
  - Send requests to file service
- **Caching**:
  - Improve performance (seen by clients) and scalability (supported by servers)
- **Servers**:
  - Own and manage state (files)
  - Provide service (file access)

## Peer Distributed Applications

- **Each node**:
  - _Owns_ state
  - Provides service
  - All nodes are _peers_
- In _peer-to-peer_ even overall control and management done by all

## DSM (Distributed Shared Memory)

- **Each node**:
  - _Owns_ state: memory
  - Provides service:
    - Memory reads/writes from any node
    - Consistency protocols
- Permits scaling beyond single machine memory limits:
  - More _shared_ memory at lower cost
  - Slower overall memory access
  - Commodity interconnect technologies support this RDMA

## Hardware vs Software DSM

- **Hardware-supported** (expensive!):
  - Relies on interconnect
  - OS manages larger physical memory
  - NICs (network interconnect card) translate remote memory access to messages
  - NICs involved in all aspects of memory management; support atomics, etc.
- **Software-supported**:
  - Everything done by software
  - OS, or language run-time
