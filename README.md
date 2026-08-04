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


Strict parameters validaiton rules:
- All values other than scheduler must be valid integers
- Negative values are rejected
- `number_of_coders` should be more than 0
- The parser accepts `-0` as `0`.

## Usage Notes

The program prints a timestamped event log showing when coders take dongles, compile, debug,
refactor, or burn out. Important events are colorized for readability.

The core flow is:

1. Initialize the simulation state, coder threads, dongles, and monitor.
2. Release all workers at the same start time through a shared simulation gate.
3. Let coders cycle through compile, debug, and refactor while respecting dongle cooldowns.
4. Stop the simulation when a coder burns out or when atleast all required compiles are completed for each coder.

## Blocking cases handled

This solution addresses the main concurrency hazards explicitly:

- Deadlock prevention: dongles are always locked in pointer order, so the code does not create a circular wait.
- Hold-and-wait reduction: a coder only proceeds into a compile when both dongles are available in the expected queue order.
- Starvation mitigation: coders are pre-seeded into the dongle queues and the monitor list so the first scheduling window is not dominated by startup order alone.
- Burnout detection: the monitor uses `pthread_cond_timedwait` against each coder's computed burnout deadline, so a coder is declared burned out precisely when the deadline expires.
- Clean shutdown: once burnout or completion is detected, the simulation status flips to `END` and all waiting threads observe the same stop signal.
- Log serialization: output is guarded so concurrent threads do not interleave event messages.

The code also handles the single-coder edge case separately, since one coder can never acquire two dongles.

## Thread synchronization mechanisms

The implementation uses several synchronization layers that work together:

- `pthread_mutex_t` on each dongle protects its queue, availability flag, and cooldown state.
- `pthread_cond_t` on each dongle wakes waiting coders when a dongle becomes available again.
- A dedicated `pthread_mutex_t` and `pthread_cond_t` pair inside `sim_action()` acts as a shared start/stop event for the whole simulation.
- Each coder has a `compiled_mutex` protecting `last_compile`, `burnout_date`, and its remaining compile count while the monitor reads the same data.
- The monitor link `pthread_cond_t` lets a coder notify the monitor immediately after a successful compile, which keeps burnout checks precise without busy waiting.
- The shared burnout list is protected by its own mutex so coders can move in and out of the monitor queue safely.

Two patterns are especially important here:

1. Race-free state updates: a coder updates its timing information under `compiled_mutex` before signaling the monitor, so the monitor never sees a half-updated burnout deadline.
2. Thread-safe resource handoff: when a dongle is released, the code updates its next available time, removes the current owner from the queue, clears the taken flag, and signals the dongle condition variable while still holding the dongle mutex.

This is what keeps the communication between coders and the monitor predictable: coders publish their new state with mutex protection, and the monitor reacts only after it has exclusive access to the same data.

## Technical Highlights

- The simulation gate in `sim_action()` is a small custom event primitive that handles `OFF`, `ON`, `WAIT_RUN`, `WAIT_STP`, `STAT`, and `END` states.
- Dongles can be scheduled with either EDF or FIFO ordering.
- EDF uses a tiny heap per dongle to prioritize the coder with the earliest burnout deadline.
- The monitor waits on a linked list of coders so it always watches active participants first.
- The startup phase pre-seeds both the dongle queues and the first compile timestamps to avoid awkward first-turn bias.

## Resources

Classic references used while building this project:

- https://www.baeldung.com/cs/concurrency-vs-parallelism
- https://www.baeldung.com/cs/process-scheduling#2-shortest-job-first-sjf
- https://www.lenovo.com/us/en/glossary/what-is-deadlock
- https://broman.dev/download/The%20Linux%20Programming%20Interface.pdf
- https://kuleuven-diepenbeek.github.io/osc-course/ch6-tasks/processes/
- https://www.geeksforgeeks.org/operating-systems/thread-control-block-in-operating-system/
- https://www.geeksforgeeks.org/dsa/priority-queue-using-binary-heap/
- https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2

AI was used as a coding aid for understanding pthread patterns, checking concurrency design choices, and spotting likely race-condition or cleanup issues while rewriting the README and reviewing the implementation. The final structure, explanations, and project-specific conclusions were written to match the code in this repository.
