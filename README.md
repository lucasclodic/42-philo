*This project has been created as part of the 42 curriculum by lclodic.*

# Philosophers

## Description

`philo` is the mandatory part of the 42 Philosophers project.

The program simulates the classic Dining Philosophers problem using POSIX threads
and mutexes. Each philosopher is represented by a thread, each fork is protected
by a mutex, and the simulation must stop when a philosopher dies or when every
philosopher has eaten enough times if the optional argument is provided.

The main goals of this project are:

- understand the basics of multithreading in C
- reason about shared data and race conditions
- protect critical sections with mutexes
- design a simulation that avoids deadlocks and handles timing constraints

The current repository contains the mandatory implementation in the
[`philo/`](/Users/lucas/Dev/42/42-philo/philo) directory.

## Instructions

### Build

From the repository root:

```sh
cd philo
make
```

This builds the executable:

```sh
./philo
```

### Run

Usage:

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Examples:

```sh
./philo 4 410 200 200
./philo 5 800 200 200 3
```

### Project Structure

- [`philo/philo.c`](/Users/lucas/Dev/42/42-philo/philo/philo.c): argument parsing and program entry point
- [`philo/init.c`](/Users/lucas/Dev/42/42-philo/philo/init.c): table and philosopher initialization
- [`philo/routine.c`](/Users/lucas/Dev/42/42-philo/philo/routine.c): philosopher routine, simulation start, and monitoring
- [`philo/sync_utils.c`](/Users/lucas/Dev/42/42-philo/philo/sync_utils.c): shared-state helpers, printing, and cleanup
- [`philo/utils.c`](/Users/lucas/Dev/42/42-philo/philo/utils.c): numeric parsing and time helpers
- [`philo/includes/philo.h`](/Users/lucas/Dev/42/42-philo/philo/includes/philo.h): shared types and function prototypes

## Technical Choices

- One thread per philosopher
- One mutex per fork
- One global mutex for output
- One global mutex for the stop flag
- One mutex per philosopher for meal-related state (`last_meal`, `meals_eaten`)
- A monitor loop in the main thread to detect death or completion

This design keeps the data flow explicit and makes the synchronization easier to
reason about during testing and peer evaluation.

## Resources

Classic references used for the project:

- The Dining Philosophers problem
- `man pthread_create`
- `man pthread_join`
- `man pthread_mutex_init`
- `man pthread_mutex_lock`
- `man pthread_mutex_unlock`
- `man gettimeofday`
- `man usleep`

### AI Usage

AI was used as a learning and review tool during this project.

It was mainly used to:

- clarify thread and mutex concepts
- review design decisions for shared data
- reason about race conditions, deadlocks, and starvation
- help identify bugs in control flow and synchronization

The implementation itself was written and iterated manually, with AI used as
support for understanding, debugging, and structuring the work.
