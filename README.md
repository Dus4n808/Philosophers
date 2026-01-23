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
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

### Debug Tools
```bash
make valgrind   # Check for memory leaks
make helgrind   # Check for data races
make gdb        # Launch GDB debugger
```

## Technical Choices

### Deadlock Prevention

To prevent deadlocks, philosophers pick up forks in different orders based on their ID:
- **Even-numbered philosophers**: Pick up left fork first, then right fork
- **Odd-numbered philosophers**: Pick up right fork first, then left fork

### Data Race Prevention

All shared variables are protected with mutexes:
- `meal_lock`: Protects `last_meal` and `meal_eaten` for each philosopher
- `write_lock`: Protects console output
- `start_lock`: Synchronizes simulation start

### Odd Number of Philosophers

When there is an odd number of philosophers, an additional thinking time is added to prevent starvation.

## Resources

### Documentation

- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Mutex Lock for Linux Thread Synchronization](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)

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
