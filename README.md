*This project has been created as part of the 42 curriculum by ahmounsi.*

# Codexion

## Description

Codexion is a multithreaded simulation in C inspired by the classic dining philosophers problem.
A group of coders that repeatedly compile, debug, and refactor while competing for shared
dongles. Each compile requires two dongles, each dongle has a cooldown before it can be reused,
and a monitor thread watches for burnout to stop the simulation, and cleanly.

## Instructions

Build the project with:

```sh
make (clean / fclean / re)
```

Run the executable with:

```sh
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

**number_of_coders:**
The number of coders and also the number of dongles. 

**time_to_burnout:**
(in milliseconds): If a coder did not start compiling within time_to_burnout milliseconds since the beginning of their last compile or the beginning of the simulation, they burn out.

**time_to_compile:**
(in milliseconds): The time it takes for a coder to compile. During that time, they must hold two dongles.

**time_to_debug:**
(in milliseconds): The time a coder will spend debugging. 

**time_to_refactor:**
(in milliseconds): The time a coder will spend refactoring. After completing the refactoring phase, the coder will immediately attempt to acquire dongles and start compiling again.

**number_of_compiles_required::**
If all coders have compiled at least this many times, the simulation stops. Otherwise, it stops when a coder burns out.

**dongle_cooldown:**
(in milliseconds): After being released, a dongle is unavailable until its cooldown has passed.

**scheduler::**
The arbitration policy used by dongles to decide who gets them when multiple coders request them. The value must be exactly one of: fifo or edf. fifo means First In, First Out: the dongle is granted to the coder whose request arrived first. edf means Earliest Deadline First with deadline = last_compile_start + time_to_burnout.


>   NOTE: Strict parameters validaiton rules:
    - All values other than scheduler must be valid integers
    - Negative values are rejected
    - `number_of_coders` should be more than 0
    - The parser accepts `-0` as `0`.

## Usage Notes

The program prints a timestamped event log showing when coders take dongles, compile, debug,
refactor, or burn out. Important events are colorized for readability.

The core flow is:

1. Initialize the simulation state, coder threads, dongles, and monitor.
2. Run all Coders at the same start time through a shared simulation control API.
3. Let coders cycle through compile, debug, and refactor while respecting dongle cooldowns, and simulation status.
4. Stop the simulation when a coder burns out or when atleast all required compiles are completed for each coder.

## Blocking cases handled

These solution ere implemented to avoid deadlock or temporary hanging:

- Deadlock prevention: dongles are always locked in pointer order, so the code does not create a circular wait.
- Hold-and-wait reduction: a coder only proceeds into a compile when both dongles are available in the expected queue order, which helps breaking one of coffman's conditions for a deadlock to happen.
- Starvation mitigation: coders are pre-seeded into the dongle queues and the monitor list so the first scheduling window is not dominated by startup order alone.
- Burnout detection: the monitor uses `pthread_cond_timedwait` against each coder's computed burnout deadline, so a coder is declared burned out precisely when the deadline expires.
- Clean shutdown: once burnout or completion is detected, the simulation status flips to `END` and all waiting threads recieve the same stop signal.
- Log serialization: output is guarded atomically so concurrent threads event messages do not overlap .

The code also handles the single-coder edge case separately, since one coder can never acquire two dongles.

## Thread synchronization mechanisms

The implementation uses several synchronization layers that work together:

- `pthread_mutex_t` on each dongle protects its queue, availability flag, and cooldown state.
- `pthread_cond_t` on each dongle wakes waiting coders when a dongle becomes available again.
- A dedicated `pthread_mutex_t` and `pthread_cond_t` pair inside `sim_action()` acts as a shared start/stop event for the whole simulation.
- Each coder has a `compiled_mutex` protecting `last_compile`, `burnout_date`, and its remaining compile count while the monitor reads the same data.
- The monitor link `pthread_cond_t` lets a watched coder notify the monitor that's watching it immediately after a successful compile, which keeps burnout checks precise without busy waiting.
- The shared burnout list is protected by its own mutex so coders can move in and out of the monitor queue safely.

This is what keeps the communication between coders and the monitor predictable: coders publish their new state with mutex protection, and the monitor reacts only after it has exclusive access to the same data.

- The simulation gate in `sim_action()` is a small custom event handler acting based on one of the options: `OFF`, `ON`, `WAIT_RUN`, `WAIT_STP`, `STAT`, and `END`.
- Dongles can be scheduled with either EDF or FIFO ordering.
- EDF uses a tiny heap per dongle to prioritize the coder with the earliest burnout deadline.
- The monitor waits on a linked list of coders so it always watches active participants first.
- The startup phase pre-seeds both the dongle queues and the first compile timestamps to avoid awkward first-turn bias.


## Resources
Classic references used while building this project:

**Mandatory entry knowledge for proccesses, concurrency and parallelism**
- https://www.baeldung.com/cs/process-scheduling#2-shortest-job-first-sjf
- https://www.baeldung.com/cs/concurrency-vs-parallelism
- https://www.youtube.com/watch?v=RlM9AfWf1WU

**Deeper knowledge for how proccesses and threads works**
- https://broman.dev/download/The%20Linux%20Programming%20Interface.pdf
- https://kuleuven-diepenbeek.github.io/osc-course/ch6-tasks/processes/
- https://www.geeksforgeeks.org/operating-systems/thread-control-block-in-operating-system/

**Heap Implementation for EDF *(not even needed in this project, but what can you do, f*ck the subject)**
- https://medium.com/data-science-collective/heaps-priority-queues-data-structures-algorithms-for-data-scientists-17d392ab0074
- https://www.geeksforgeeks.org/dsa/priority-queue-using-binary-heap/

**Good to know:**
- https://en.wikipedia.org/wiki/Process_state
- https://www.geeksforgeeks.org/operating-systems/states-of-a-process-in-operating-systems/

**C's pthread introduction and usage tutorial:**
- https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2


**Lenovo's explanation for coffman's conditions**
- https://www.lenovo.com/us/en/glossary/what-is-deadlock

AI was used as a coding aid for understanding pthread patterns, checking concurrency design choices, and spotting likely race-condition or cleanup issues while rewriting the README and reviewing the implementation and highlighting bad practices.
