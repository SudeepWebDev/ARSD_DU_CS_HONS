# OpenMP Synchronization Constructs

## 1. Introduction

- Synchronization is crucial for coordinating threads, ensuring correct execution order, atomicity, and serial execution of code.
- OpenMP provides high-level synchronization constructs, simplifying what would otherwise require manual lock management (like in Pthreads).

---

## 2. Barrier Synchronization

### 2.1 The `barrier` Directive

- **Syntax:**  
  ```c
  #pragma omp barrier
  ```
- **Behavior:**  
  - All threads in a team wait at the barrier until every thread has reached it, then all proceed.
  - In nested parallel regions, binds to the closest enclosing parallel region.
- **Conditional Barriers:**  
  - Must be placed in a compound statement if used conditionally.

| Method                    | Overhead    | Use Case                        |
|---------------------------|-------------|----------------------------------|
| `#pragma omp barrier`     | Low         | Preferred for barriers           |
| End/restart parallel region| Higher      | Not recommended for barriers     |

---

## 3. Single Thread Execution

### 3.1 The `single` Directive

- **Syntax:**  
  ```c
  #pragma omp single [clause list]
  // structured block
  ```
- **Clauses:** `private`, `firstprivate`, `nowait`
- **Behavior:**  
  - Only one (arbitrary) thread executes the block; others skip to end of block.
  - If `nowait` is used, threads do not wait at end of block; otherwise, they wait (implicit barrier).
- **Use Cases:**  
  - Computing global data, performing I/O, or any computation that must occur once in a parallel region.

### 3.2 The `master` Directive

- **Syntax:**  
  ```c
  #pragma omp master
  // structured block
  ```
- **Behavior:**  
  - Only the master thread (thread 0) executes the block.
  - No implicit barrier at the end (unlike `single`).

---

## 4. Critical Sections

### 4.1 The `critical` Directive

- **Syntax:**  
  ```c
  #pragma omp critical [(name)]
  // structured block
  ```
- **Behavior:**  
  - Only one thread at a time can execute a named critical section.
  - Optional `name` allows different critical regions to be managed separately.
- **Use Cases:**  
  - Protecting shared resources (e.g., queues in producer-consumer scenarios).
- **Best Practice:**  
  - Keep critical sections as short as possible to minimize serialization and improve performance.
- **Restrictions:**  
  - Block must be structured; no jumps in or out.

### 4.2 The `atomic` Directive

- **Purpose:**  
  - For simple, atomic updates to a single memory location.
- **Syntax:**  
  ```c
  #pragma omp atomic
  x binary_op= expr;
  // or: x++; ++x; x--; --x;
  ```
- **Notes:**  
  - Only the load/store of the variable is atomic, not the full expression.
  - `expr` must not reference `x` (prevents race conditions).
- **Performance:**  
  - Usually faster than `critical` for simple updates, as it may use hardware atomic instructions.

---

## 5. In-Order Execution

### 5.1 The `ordered` Directive

- **Syntax:**  
  ```c
  #pragma omp ordered
  // structured block
  ```
- **Usage:**  
  - Must be within a `for` or `parallel for` region with the `ordered` clause.
- **Behavior:**  
  - Only one thread at a time executes the ordered block, in the order of loop indices.
- **Restriction:**  
  - Only one ordered block per for directive.
- **Performance Note:**  
  - Excessive use reduces parallelism.

---

## 6. Memory Consistency

### 6.1 The `flush` Directive

- **Syntax:**  
  ```c
  #pragma omp flush[(list)]
  ```
- **Purpose:**  
  - Makes specified (or all) shared variables consistent across threads (memory fence).
  - Ensures updates to shared variables are visible to other threads.
- **Implicit Flush Occurs At:**  
  - At barriers.
  - Entry/exit of `critical`, `ordered`, `parallel`, `parallel for`, `parallel sections`.
  - Exit of `for`, `sections`, and `single` blocks.
- **Not Implied:**  
  - If `nowait` clause is present.
  - At entry to `for`, `sections`, `single`, or `master` blocks.
- **Applies Only To:**  
  - Shared variables; private variables are unaffected.

---

## 7. Summary Table: Synchronization Constructs

| Directive       | Purpose                             | Barrier Behavior         | Typical Use Case                |
|-----------------|-------------------------------------|-------------------------|---------------------------------|
| `barrier`       | Wait for all threads                | Yes                     | Synchronize threads             |
| `single`        | One thread executes code block      | Yes (unless nowait)     | Unique computation, I/O         |
| `master`        | Master thread executes code block   | No                      | Master-only tasks               |
| `critical`      | Mutual exclusion for code block     | No                      | Protect shared resources        |
| `atomic`        | Atomic memory update                | No                      | Simple variable updates         |
| `ordered`       | In-order loop execution             | No                      | Serialize loop segment          |
| `flush`         | Memory consistency for variables    | No (explicit/implicit)  | Ensure visibility of variables  |
