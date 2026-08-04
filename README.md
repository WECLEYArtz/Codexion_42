*This project has been created as part of the 42 curriculum by ahmounsi.*

# Codexion

## Description

Codexion is a multithreaded simulation in C where a number of "coders" sit around a
shared table and take turns compiling, debugging, and refactoring. Compiling requires
two shared "dongles" (one per hand), and coders must avoid "burning out" by compiling
regularly.
The project inspired from the classic concurrency problems "Dining philosophers"
touching the neccesary multithreading conceps (mutual exclusion, resource starvation, fair scheduling)

## Instructions

To compile:
```sh
make (all / re / clean / fclean)
```

Note:	The makefile uses automatic dependencies to prevent uneccesary relink
     	and the compilation results in a clear structure keeping the code clean
     	and remaining easy to read.

### Usage

These are the parameters required for the simulation to work.
```sh
./codexion  <number_of_coders>
            <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor>
            <number_of_compiles_required> <dongle_cooldown> <scheduler>
```
Valid Parameters Requirements:
- None valid integer are rejected, including ones containing spaces
- Negative values are rejected
- There has to be atleast one coder


Note:
- `-0` will be considered a `0`


### Output

The output follows a pattern similar to this:
```
0 1 has taken a dongle
1 1 has taken a dongle
1 1 is compiling
201 1 is debugging
401 1 is refactoring
402 2 has taken a dongle
403 2 has taken a dongle
403 2 is compiling
603 2 is debugging
803 2 is refactoring
1204 3 burned out
```
Important events are colorized for better reading experience

## Resources
Mandatory entry knowledge for proccesses, concurrency and parallelism
- https://www.baeldung.com/cs/process-scheduling#2-shortest-job-first-sjf
- https://www.baeldung.com/cs/concurrency-vs-parallelism
- https://www.youtube.com/watch?v=RlM9AfWf1WU

Deeper knowledge for how proccesses and threads works
- https://broman.dev/download/The%20Linux%20Programming%20Interface.pdf
- https://kuleuven-diepenbeek.github.io/osc-course/ch6-tasks/processes/
- https://www.geeksforgeeks.org/operating-systems/thread-control-block-in-operating-system/

Heap Implementation for EDF *(not even needed in this project, but what can you do, f*ck the subject)*
- https://medium.com/data-science-collective/heaps-priority-queues-data-structures-algorithms-for-data-scientists-17d392ab0074
- https://www.geeksforgeeks.org/dsa/priority-queue-using-binary-heap/

Good to know:
- https://en.wikipedia.org/wiki/Process_state
- https://www.geeksforgeeks.org/operating-systems/states-of-a-process-in-operating-systems/

C's pthread introduction and usage tutorial:
- https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2


Lenovo's explanation for coffman's conditions
- https://www.lenovo.com/us/en/glossary/what-is-deadlock

AI was used for first steps getting used to multithreading APIs, and books parsin for faster information reach (claude)
Also a tool for potential issues prediction in release code bases, and recognising bad practices (github's copilot)


## Blocking cases handled
In order to prevent deadlocks, the common solution of either acquiring both resources
neccesary or none was implemented, which translates to a coder either taking both dongles or none,
this way, no coder would block another from a dongle while waiting for another, causing a circular wait.

To avoid stravation, a preseeding is performed at the begining of the simulation, forcing all even coders to start
leaving no coder who should've taken a dongle be a victim of bad run order.

A locking mechanism relying on dongle's pointer order was used to keep a global consistant locking and unlocking order
which just minimizes the likelyhood of a potential circular wait deadlock.


## Thread synchronization mechanisms
Generally, every shared data between coders and monitors (as in every side can access the data of the other and possibly manipulate it)
is considered a critical section, and every critical section has to be loked during read or write.


### Mutex usage
Mutexes are to implement any atomic function, such as
- announce (logging)
- dual dongle taking
- monitor's burnout wait list updating
- coder's and dongle's data updating, such as dates or records


### Conditional variables usage
Cond vars helped achieving a comunication between coders and monitors,
resulting in a precise control of the simulation without unreasonable sleeps with magical values.

Shared functions containing both neccesary mutex and conv in that function's purpose scope helped minimizing code syntax and improves readability too
especially debugging, due to the locking and unlocking in fewer code blocks

A shared variable of how many coders left to finished their compile which coders modify (once per coder),
and monitor reads everytime someone compiles to determine when the simulation stops
