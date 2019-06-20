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

## DSM Design: Sharing Granularity

- Cache line granularity?
  - Overheads too high for DSM
- Pros:
  - Page granularity (OS-level)
  - Object granularity (language run-time)
- Cons:
  - Variable granularity
- Beware of false sharing, e.g., X and Y are on the same page!

## DSM Design: Access Algorithm

- **What types of applications use DSM**?
  - Application access algorithm:
    - Single reader/single writer (SRSW)
    - Multiple readers/single writer (MRSW)
    - Multiple readers/multiple writers (MRMW)

## DSM Design: Migration vs Replication

- **DSM performance metric**: access latency
- Achieving low latency through:
  - **Migration**:
    - Makes sense for SRSW
    - Requires data movement
  - **Replication** (caching):
    - More general
    - Requires consistency management

## DSM Design: Consistency Management

- **DSM**: shared memory in SMPs
- **In SMP**:
  - Write-invalidate
  - Write-update
- Coherence operations on each write: overhead too high
- Push invalidations when data is written to:
  - Proactive
  - Eager
  - Pessimistic
- Pull modification info periodically
  - On-demand (reactive)
  - Lazy
  - Optimistic
- When these methods get triggered depends on the consistency model for the shared state!

## DSM Architecture

- **DSM architecture** (page-based, OS-supported):
  - Each node contributes part of memory pages to DSM
  - Need local caches for performance (latency)
  - All nodes responsible for part of distributed memory
  - Home node manages access and tracks page ownership
- **Exact replicas** (explicit replication):
  - For load balancing, performance, or reliability
  - _home_/manager node controls management
