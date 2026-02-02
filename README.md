*This project has been created as part of the 42 curriculum by dufama.*

# Philosophers

## Description

The **Philosophers** project is a classic synchronization problem that simulates the Dining Philosophers Problem, originally formulated by Edsger Dijkstra in 1965.

The scenario involves a number of philosophers sitting at a round table, alternating between three states: **eating**, **thinking**, and **sleeping**. Each philosopher needs two forks to eat, but there is only one fork between each pair of adjacent philosophers. The challenge is to design a solution where no philosopher starves (deadlock) and the simulation runs correctly with proper thread synchronization.

### Rules

- Each philosopher is a separate thread
- There is one fork between each pair of philosophers
- A philosopher must hold both adjacent forks to eat
- After eating, a philosopher puts down the forks and starts sleeping
- After sleeping, a philosopher starts thinking
- The simulation stops when a philosopher dies of starvation or when all philosophers have eaten a specified number of times

### Key Concepts Learned

- Thread creation and management with `pthread`
- Mutex locks for resource protection
- Avoiding deadlocks and data races
- Proper synchronization between threads

## Instructions

### Prerequisites

- GCC compiler
- Make
- POSIX threads library (pthread)

### Compilation
```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile the project
```

### Execution
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` | Time in ms before a philosopher dies without eating |
| `time_to_eat` | Time in ms it takes to eat |
| `time_to_sleep` | Time in ms it takes to sleep |
| `number_of_times_each_philosopher_must_eat` | (Optional) Simulation stops when all philosophers have eaten this many times |

### Examples
```bash
# 5 philosophers, no one should die
./philo 5 800 200 200

# Someone will die around 310ms
./philo 5 310 200 100

# Single philosopher (always dies)
./philo 1 800 200 200

# Simulation ends after each philosopher eats 3 times
./philo 5 800 200 200 3
```

### Output Format
```
timestamp_in_ms philosopher_id action
```

Actions:
- `Has taken a fork`
- `Is eating`
- `Is sleeping`
- `Is thinking`
- `died`

### Debug Tools
```bash
make valgrind   # Check for memory leaks
make helgrind   # Check for data races
make gdb        # Launch GDB debugger
```

## Technical Choices

### Synchronized Start

All philosopher threads and the monitor thread wait on a shared `start_flag` protected by `start_lock`. The main thread creates all threads, initializes `last_meal` timestamps, then sets `start_flag` to 1. This ensures all philosophers begin the simulation at the same time with accurate initial meal timestamps, preventing false death detections at startup.

### Deadlock Prevention

To prevent deadlocks, philosophers pick up forks in different orders based on their ID:
- **Even-numbered philosophers**: Pick up left fork first, then right fork
- **Odd-numbered philosophers**: Pick up right fork first, then left fork

Even-numbered philosophers also have a small initial delay (`ft_usleep(1)`) at the start of the simulation to stagger fork acquisition and reduce contention.

### Single Philosopher Handling

When there is only one philosopher, they can only take one fork and will inevitably die. This edge case is handled explicitly: the philosopher takes a fork, then waits until the monitor detects their death.

### Monitor Thread

A dedicated monitor thread continuously checks two conditions:
- **Death detection**: Compares the time since each philosopher's last meal against `time_to_die`
- **Meal completion**: If a meal count is specified, checks whether all philosophers have eaten the required number of times

The monitor polls at 500µs intervals to balance responsiveness with CPU usage.

### Data Race Prevention

All shared variables are protected with mutexes:
- `meal_lock`: Protects `last_meal` and `meal_eaten` for each philosopher
- `write_lock`: Protects console output to prevent garbled messages
- `dead_lock`: Protects the `dead` flag checked by all threads
- `start_lock`: Synchronizes simulation start

### Precise Sleep

The `ft_usleep` function implements a busy-wait loop with `usleep(500)` increments instead of a single `usleep` call. This provides more accurate timing and allows threads to check the `dead` flag during sleep, enabling faster termination when a philosopher dies.

## Resources

### Documentation

- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Mutex Lock for Linux Thread Synchronization](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)
- [CodeVault](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2).

### Man Pages

- `man pthread_create`
- `man pthread_join`
- `man pthread_mutex_init`
- `man pthread_mutex_lock`
- `man pthread_mutex_unlock`
- `man pthread_mutex_destroy`
- `man usleep`
- `man gettimeofday`

### AI Usage

AI assistance (Claude by Anthropic) was used during this project as a **learning tool only**, similar to asking questions to a teacher or mentor:

- **Conceptual explanations**: Understanding the Dining Philosophers Problem, thread synchronization, mutex usage, and deadlock prevention strategies
- **Debugging guidance**: When encountering errors, AI helped explain what the error meant and pointed towards the general direction to investigate, without providing code solutions
- **Clarifying documentation**: Getting clearer explanations of pthread functions and their proper usage patterns

**No code was generated or copied from AI.** All implementation, logic, and code were written entirely by the student. AI was used exclusively as an educational resource to better understand concepts and resolve doubts, similar to consulting documentation or asking a peer for clarification.

The core logic and implementation were written by the student, with AI serving as a learning tool and debugging assistant.

## Author

- **dufama** - 42 Lausanne
