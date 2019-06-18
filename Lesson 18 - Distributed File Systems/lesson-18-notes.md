# Lesson 18: Distributed File Systems

- Topics to be covered in this lesson:
  - DFS (distributed file systems) design and implementation
  - NFS (network file systems)

## Visual Metaphor

- **Distributed file systems** are like **distributed storage facilities**:
  - Accessed via well-defined interface:
    - Access via VFS
  - Focus on consistent state:
    - Tracking state, file updates, cache coherence, etc.
  - Mix distribution models possible:
    - Replicated vs partitioned, peer-like systems, etc.

## Distributed File Systems

- _See lecture for figure_
- **DFS**: an environment where multiple machines are involved in the delivery of the file system service
  - Includes file-system interfaces which use VFS interface to abstract and hide file system organizations
  - Uses OS to hide local physical storage on a machine
  - Has files maintained on a remote machine or on a remote file system that is being accessed over the network

## DFS Models

- **Client/server on different machines**
- File server distributed on multiple machines
  - **Replicated** (each server: all files)
  - **Partitioned** (each server: part of files)
  - **Both** (files partitioned; each partition replicated)
- Files stored on and served from all machines (peers)
- Blurred distinction between clients and servers

## Remote File Service: Extremes

- **Extreme 1: upload/download**
  - Like FTP, SVN, etc.
- **Extreme 2: true remote file access**
  - Every access to remote file, nothing done locally
- Pros:
  - File accesses centralized, easy to reason about consistency
- Cons:
  - Every file operation pays network cost
  - Limits server scalability

## Remote File Service: A Compromise

- A more practical remote file access (with caching)
- Allow clients to store parts of files locally (blocks)
  - Pros:
    - Low latency on file operations
    - Server load reduced: is more scalable
- Force clients to interact with server (frequently)
  - Pros:
    - Server has insights into what clients are doing
    - Server has control into which accesses can be permitted: easier to maintain consistency
  - Cons:
    - Server more complex, requires difference file sharing semantics

## Stateless vs Stateful File Server

- **Stateless**: keeps no state, ok with extreme models but cannot support _practical_ model
  - Pros:
    - No resources are used on server side (CPU/memory)
    - ON failure, just restart
  - Cons:
    - Cannot support caching and consistency management
    - Every request self-contained: more bits transferred
- **Stateful**: keeps client state, needed for _practical_ model to track what is cached/accessed
  - Pros:
    - Can support locking, caching, incremental operations
  - Cons:
    - On failure, need check-pointing and recovery mechanisms
    - Overheads to maintain state and consistency: depends on caching mechanism and consistency protocol

## Caching State in a DFS

- Locally clients maintain portion of state (e.g., file blocks)
- Locally clients perform operations on cached state (e.g. open/read/write, etc.): requires coherence mechanisms
- How?
  - SMP: write-update/write-invalidate
  - DFS: client/server-driven
- When?
  - SMP: on write
  - DFS: on demand, periodically, on open, etc.
- Details depend on file sharing semantics

## File Sharing Semantics on a DFS

- **UNIX semantics**: every write visible immediately
- **Session semantics**: (between open-close: session)
  - Write-back on `close()`, update on `open()`
  - Easy to reason, but may be insufficient
- **Periodic updates**:
  - Client writes-back periodically: clients have a _lease_ on cached data (not exclusive necessarily)
  - Server invalidates periodically: provides bounds on _inconsistency_
  - Augment with `flush()`/`sync()` API
- **Immutable files**: never modify, new files created instead
- **Transactions**: all changes atomic
