# Notes on OpenMP: A Standard for Directive-Based Parallel Programming

## 1. Introduction to OpenMP

- **OpenMP** is an API for shared address space programming, supporting **FORTRAN, C, and C++**.
- Unlike lower-level threading APIs like Pthreads, OpenMP uses **compiler directives** (pragmas) for parallelism.
- Designed for *application programmers* (not just system programmers) by abstracting thread management details.
- OpenMP directives manage **concurrency**, **synchronization**, and **data handling**, removing the need for manual setup of mutexes, condition variables, etc.

---

## 2. OpenMP Programming Model

- **Directives** use the format:  
  `#pragma omp directive [clause list]`
- Programs execute **serially** until they encounter a `parallel` directive, which creates threads.

### 2.1 Parallel Directive

| Aspect             | Description                                                                                               |
|--------------------|----------------------------------------------------------------------------------------------------------|
| Syntax             | `#pragma omp parallel [clause list]` <br> Followed by a structured block `{ ... }`                      |
| Thread Creation    | Number of threads can be set: <ul><li>In the directive (`num_threads`)</li><li>By environment variable</li><li>At runtime (OpenMP functions)</li></ul>|
| Master Thread      | The thread encountering the directive is the *master* (thread id 0).                                     |

#### Example Syntax
```c
#pragma omp parallel if(is_parallel == 1) num_threads(8) \
    private(a) shared(b) firstprivate(c)
{
    /* structured block */
}
```
- If `is_parallel == 1`, creates 8 threads.
- `a`: private to each thread.
- `b`: shared among all threads.
- `c`: each thread gets a private copy, initialized to its value before the directive.

---

### 2.2 Clause Types and Their Uses

| Clause           | Purpose                                                                                                 |
|------------------|--------------------------------------------------------------------------------------------------------|
| `if(expression)` | Conditionally creates threads if expression is true. Only one `if` clause per directive.               |
| `num_threads(n)` | Sets the number of threads to `n`.                                                                     |
| `private(list)`  | Variables in `list` are local to each thread, uninitialized.                                           |
| `firstprivate(list)` | Variables are private, but initialized to their pre-directive values.                              |
| `shared(list)`   | Variables are shared among all threads.                                                                |
| `default(shared)`| By default, variables are shared.                                                                      |
| `default(none)`  | Forces explicit variable state declaration for safety.                                                 |
| `reduction(operator: list)` | Performs reduction (e.g., sum, product) across all threads for variables in `list`.         |

#### Reduction Clause Example
```c
#pragma omp parallel reduction(+: sum) num_threads(8)
{
    // compute local sums
}
// After parallel region, sum contains the total of all local sums
```

---

### 2.3 Data Handling and Initialization

| Clause          | Behavior                                                                                                     |
|-----------------|-------------------------------------------------------------------------------------------------------------|
| `private`       | Each thread gets its own uninitialized copy.                                                                 |
| `firstprivate`  | Each thread gets its own copy, initialized to the value before entering the parallel region.                 |
| `shared`        | All threads share the same variable (single copy).                                                          |
| `default`       | Sets the default variable behavior (shared or none).                                                        |
| `reduction`     | Combines private copies of a variable from all threads using an operator when threads exit the parallel region. |

---

### 2.4 Thread Identification and Control Functions

| Function                     | Purpose                                               |
|------------------------------|------------------------------------------------------|
| `omp_get_num_threads()`      | Returns number of threads in the parallel region.    |
| `omp_get_thread_num()`       | Returns thread ID (master is 0).                     |

---

## 3. Example: Computing PI Using OpenMP

- Problem: Estimate PI using random sampling across multiple threads.
- OpenMP makes parallelism simpler than with POSIX threads.

#### Code Excerpt
```c
#pragma omp parallel default(private) shared(npoints) \
                     reduction(+: sum) num_threads(8)
{
    num_threads = omp_get_num_threads();
    sample_points_per_thread = npoints / num_threads;
    sum = 0;
    for (i = 0; i < sample_points_per_thread; i++) {
        rand_no_x = (double)(rand_r(&seed)) / (double)((2<<14)-1);
        rand_no_y = (double)(rand_r(&seed)) / (double)((2<<14)-1);
        if (((rand_no_x - 0.5) * (rand_no_x - 0.5) +
             (rand_no_y - 0.5) * (rand_no_y - 0.5)) < 0.25)
            sum++;
    }
}
```

| Variable        | Handling                  | Purpose                                   |
|-----------------|--------------------------|-------------------------------------------|
| `npoints`       | shared                   | Total number of points                    |
| `sum`           | reduction(+: sum)        | Local sums combined after threads finish  |
| `sample_points_per_thread` | private       | Number of points sampled per thread       |

- The program splits the work across threads, each computing a portion of the total, and then combines results automatically.

---

## 4. Key Advantages of OpenMP (vs. Pthreads)

- **Simplicity**: Abstracts away thread creation, synchronization, and termination.
- **Safety**: Explicitly controls data sharing and privatization, reducing bugs.
- **Productivity**: Faster to write and maintain parallel code.