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

## Indexing Distributed State

- **Each page (object) has**:
  - Address: node ID and page frame number
  - Node ID: _home_ node
- **Global map (replicated)**:
  - Object (page) ID: manager node ID
  - Manager map available on each node!
- **Metadata for local pages (partitioned)**:
  - Per-page metadata is distributed across managers
- **Global mapping table**:
  - Object ID: index into mapping table: manager node

## Implementing DSM

- **Problem**: DSM must _intercept_ accesses to DSM state
  - To send remote messages requesting access
  - To trigger coherence messages
  - Overheads should be avoided for local, non-shared state (pages)
  - Dynamically _engage_ and _disengage_ DSM when necessary
- **Solution**: Use hardware MMU support!
  - Trap in OS if mapping invalid or access not permitted
  - Remote address mapping: trap and pass to DSM to send message
  - Cached content: trap and pass to DSM to perform necessary coherence operations
  - Other MMU information useful (e.g., dirty page)

## What is a Consistency Model?

- **Consistency model**: agreement between memory (state) and upper software layers
- _Memory behaves correctly if and only if software follows specific rules_
- Memory (state) guarantees to behave correctly:
  - Access ordering
  - Propagation/visibility of updates

## Strict Consistency

- **Strict consistency**: updates visible everywhere immediately
- In practice:
  - Even on single SMP, no guarantees on order without extra locking and synchronization
  - In distributed systems, latency and message reorder/loss make this even harder (impossible to guarantee)

## Sequential Consistency

- **Sequential consistency**:
  - Memory updates from different processors may be arbitrarily interleaved
  - All processes will see the same interleaving
  - Operations from same process always appear in order they were issued

## Casual Consistency

- **Casual consistency**:
  - _Concurrent_ writes: No guarantees
  - Casually related writes: ordered

## Weak Consistency

- **Synchronization points**: operations (read, write, sync)
  - All updates prior to a sync point will be visible
  - No guarantee what happens in between
- **Variations**:
  - Single sync operations (sync)
  - Separate sync per subset of state (page)
  - Separate _entry/acquire_ vs _exit/release_ operations
- Pros: limit data movement and coherence operations
- Cons: maintain extra state for additional operations
