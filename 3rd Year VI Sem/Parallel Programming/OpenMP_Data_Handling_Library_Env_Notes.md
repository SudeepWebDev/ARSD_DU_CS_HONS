# OpenMP: Data Handling, Library Functions, and Environment Variables

---

## 1. Data Handling in OpenMP

### 1.1 Heuristics for Data Classes

- **private:**  
  - Use when a variable is initialized/used only by a single thread (e.g., loop indices).
  - Each thread gets a local copy.

- **firstprivate:**  
  - Use when a thread needs a local copy of a variable, initialized to a value from before the parallel region.
  - Good for data reuse/caching for performance.

- **reduction:**  
  - For variables manipulated by multiple threads (e.g., counters), keep local copies and combine with a global operation at the end.

- **shared:**  
  - Use for variables accessed by multiple threads only after exhausting private/local splitting.

- **lastprivate:**  
  - Ensures that the value from the last iteration of a parallel loop is assigned to the variable after the loop.

- **threadprivate:**  
  - Variables persist across parallel regions (if thread count remains constant).
  - Syntax: `#pragma omp threadprivate(variable_list)`

- **copyin:**  
  - Used with `threadprivate`, to copy the same value to all threads at the start of a parallel region.

---

## 2. OpenMP Library Functions

### 2.1 Controlling Threads and Processors

| Function                        | Purpose                                                      | Notes                                         |
|----------------------------------|--------------------------------------------------------------|-----------------------------------------------|
| `void omp_set_num_threads(int)`  | Sets default threads for next parallel region (if not overridden by clause). | Call outside parallel region; requires dynamic adjustment enabled. |
| `int omp_get_num_threads()`      | Returns number of threads in current team.                   | 1 if not in parallel region.                  |
| `int omp_get_max_threads()`      | Returns max possible threads for a parallel region.          |                                               |
| `int omp_get_thread_num()`       | Unique thread ID in team (0 = master).                       |                                               |
| `int omp_get_num_procs()`        | Returns number of available processors.                      |                                               |
| `int omp_in_parallel()`          | Non-zero if called within a parallel region.                 |                                               |

### 2.2 Controlling/Monitoring Thread Creation

| Function                           | Purpose                                                        |
|-------------------------------------|----------------------------------------------------------------|
| `void omp_set_dynamic(int)`         | Enables/disables dynamic thread adjustment (non-zero=enabled). |
| `int omp_get_dynamic()`             | Returns if dynamic adjustment is enabled.                      |
| `void omp_set_nested(int)`          | Enables/disables nested parallelism (non-zero=enabled).        |
| `int omp_get_nested()`              | Returns if nested parallelism is enabled.                      |

### 2.3 Mutual Exclusion: Locks

#### Simple Locks (`omp_lock_t`)

| Function                        | Purpose                                 |
|----------------------------------|-----------------------------------------|
| `void omp_init_lock(omp_lock_t*)`| Initialize a lock.                      |
| `void omp_destroy_lock(omp_lock_t*)`| Destroy a lock.                    |
| `void omp_set_lock(omp_lock_t*)` | Acquire lock (blocks if not available). |
| `void omp_unset_lock(omp_lock_t*)`| Release lock.                        |
| `int omp_test_lock(omp_lock_t*)` | Try to acquire lock (non-blocking).     |

#### Nested Locks (`omp_nest_lock_t`)

- Same set of functions as above, using `omp_nest_lock_t`.

| Rule/Note                                                |
|----------------------------------------------------------|
| Must initialize before use, destroy after use.           |
| Only owner can unlock; unlocking by others is undefined. |
| Illegal to use before initialization or after destruction.|

---

## 3. Environment Variables in OpenMP

| Variable            | Purpose/Effect                                                                                                     | Usage Example                           |
|---------------------|--------------------------------------------------------------------------------------------------------------------|-----------------------------------------|
| OMP_NUM_THREADS     | Default number of threads for parallel regions.                                                                    | `setenv OMP_NUM_THREADS 8`              |
| OMP_DYNAMIC         | Allows dynamic adjustment of thread count at runtime.                                                              | Enabled (TRUE) or disabled (FALSE)      |
| OMP_NESTED          | Enables nested parallelism.                                                                                        | Enabled (TRUE) or disabled (FALSE)      |
| OMP_SCHEDULE        | Defines schedule for `for` directives using `runtime` schedule.                                                    | `setenv OMP_SCHEDULE "static,4"`        |

- **Note:** Chunk size for OMP_SCHEDULE defaults to 1 if not specified.

---

## 4. Explicit Threads vs. OpenMP Programming

### 4.1 Advantages of OpenMP

- Simplifies thread-related tasks: no need to manually partition work or set up thread attributes.
- Suitable for problems with static/regular task graphs.
- Minimal overhead for automated code generation.

### 4.2 Advantages of Explicit Threading (e.g., Pthreads)

| Advantage                      | Details                                                                                         |
|--------------------------------|-------------------------------------------------------------------------------------------------|
| Finer control                  | More transparency in data exchange; better for managing data movement and preventing contention. |
| Advanced synchronization       | Richer API (condition waits, various locks, composite operations).                              |
| Ecosystem and tool support     | Wider tool and support availability for Pthreads.                                               |

### 4.3 Choosing an API

- Weigh simplicity and abstraction of OpenMP against control and flexibility of explicit threading.
- Consider problem structure, performance needs, and available support/tools.

---