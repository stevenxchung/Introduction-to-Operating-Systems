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

## File vs Directory Service

- Too many options?
  - Sharing frequency
  - Write frequency
  - Importance of consistent view
- Optimize for common case
- Two types of files:
  - Regular files vs directories
  - Choose different policies for each
    - E.g., session-semantics for files, UNIX for directories
    - E.g., less frequent write-back for files than directories

## Replication and Partitioning

- **Replication**: each machine holds all files
  - Pros: load balancing, availability, fault tolerance
  - Cons:
    - Writes become more complex:
      - Synchronously to all
      - Or write to one then propagated to others
    - Replicas must be reconciled:
      - E.g., voting
- **Partitioning**: each machine has subset of files
  - Pros:
    - Availability vs single server DFS
    - Scalability with file system size
    - Single file writes simpler
  - Cons:
    - On failure, lose portion of data
    - Load balancing harder; if not balanced them hot-spots possible
- Can combined both techniques, replicate each partition

## NFS (Network File System)

- _See lecture for figure_
- A NFS typically includes a client and a server; however, clients act as the remote server over a network
- **Client**:
  - Client requests for file access starts at _system call layer_ and moves to _VFS layer_
  - At the _VFS layer_, a decision will be made for where the file belongs to (the _local file system interface_ or the _NFS client_)
  - If _NFS client_ is chosen, it will move on to the _RPC client stub_ which communicates with the _RPC server sub_
- **Server**:
  - Continuing from the _RPC server stub_, the call could make it's way to the _NFS server_ which resides on a remote machine
  - The _NFS server_ could communicate with the _VFS layer_ on the server side to get access to the file
  - From the _VFS layer_, the layout is about the same as the client side
  - When an open request comes from the client, the _NFS server_ will create a file handle (i.e. a byte sequence that encodes both the server machine as well as the server local file information which will be return to the client)
  - If files are deleted or the server machine dies, the file handle will return an error for _stale data_ (invalid data)

## NFS Versions

- Since 80s, currently NFSv3 and NFSv4
- NFSv3: stateless, NFSv4: stateful
- **Caching**:
  - Session-based (non-concurrent)
  - Periodic updates
    - Default: three seconds for files; 30 seconds for directory
    - NFSv4: delegation to client for a period of time (avoids _update checks_)
- **Locking**:
  - Lease-based
  - NFSv4: also _share reservation_, reader/writer lock

## Sprite Distributed File Systems

- _Caching in the Sprite Network File System_, by Nelson et al.
  - Research DFS
  - Great value in the explanation of the design process
- Takeaway: used trace data on usage/file access patterns to analyze DFS design requirements and justify decisions

## Sprite DFS Access Pattern Analysis

- **Access pattern (workload) analysis**:
  - 33% of all file accesses are writes
    - Caching ok but write-though not sufficient
  - 75% of files are open less than 0.5 seconds
  - 90% of files are open less than 10 seconds
    - Session semantics still too high overhead
  - 20-30% of new data deleted within 30 seconds
  - 50% of new data deleted within 5 minutes
  - File sharing is rare!
    - Write-back on close not necessary
    - No need to optimize for concurrent access but must support it

## Sprite DFS from Analysis to Design

- **From analysis to design**:
  - Cache with write-back
  - Every 30 seconds write-blocks that have NOT been modified for the last 30 seconds
    - When another client opens file: get dirty blocks
  - Open goes to server, directories not cached
  - On _concurrent write_: disable caching
- **Sprite sharing semantics**:
  - Sequential write sharing: caching and sequential semantics
  - Concurrent write sharing: no caching

## File Access Operations in Sprite

- $R_1... R_n$ **readers, w, writer**:
  - All `open()` go through server
  - All clients cache blocks
  - Writer keeps timestamps for each modified block
- $w_2$ **sequential writer** (sequential sharing):
  - Server contacts last last writer for dirty blocks
  - Since $w_2$ has not closed: disabled caching!
