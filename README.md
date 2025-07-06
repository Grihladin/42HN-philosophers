<div align="center">

# <img src="https://github.com/Grihladin/42-project-badges/blob/main/badges/philosopherse.png" width="150" height="150"> 

</div>

Philosophers([42Heilbronn](https://www.42heilbronn.de/en/) project) simulates the classic dining philosophers problem using threads and mutexes. The program demonstrates concurrent programming concepts while avoiding deadlocks and race conditions.

## Problem Description

The dining philosophers problem involves N philosophers sitting around a circular table with N forks. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher needs both adjacent forks, but must avoid deadlock situations.

## Implementation

- **Threading**: Each philosopher runs in a separate thread
- **Mutex Protection**: Forks are protected by mutexes to prevent race conditions
- **Fork Ordering**: Even/odd philosopher fork pickup order prevents deadlock
- **Death Monitoring**: Separate thread monitors for philosopher deaths
- **Message Queue**: Timestamp-ordered output system for thread-safe printing

## Performance Optimizations

- **Adaptive Monitoring**: Death monitor frequency adjusts based on time_to_die
- **Hybrid Sleep Function**: Combines actual sleep with busy-waiting for precision
- **Reduced Mutex Contention**: Less frequent status checks in philosopher loop
- **Smart Print Delays**: Adaptive delays when no messages are available

## Installation

**Requirements:**
- macOS or Linux
- Make

```bash
git clone https://github.com/Grihladin/42HN-philosophers.git
cd 42HN-philosophers/philo
make
```

## Usage

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]
```

**Parameters:**
- `number_of_philosophers`: Number of philosophers (1-200)
- `time_to_die`: Time in ms before a philosopher dies without eating
- `time_to_eat`: Time in ms it takes to eat
- `time_to_sleep`: Time in ms spent sleeping
- `number_of_times_each_philosopher_must_eat`: Optional meal limit

**Example:**
```bash
./philo 5 800 200 200
./philo 4 410 200 200 5
```

## Project Structure

```
philo/
├── philosophers.h      # Header file with structures and function declarations
├── main.c              # Main program entry point and simulation setup
├── protocol.c          # Philosopher behavior (think, eat, sleep)
├── death_check.c       # Death monitoring and meal limit checking
├── time.c              # Time utilities and optimized sleep function
├── printing.c          # Thread-safe message output system
├── initialisation.c    # Setup functions for philosophers and mutexes
├── lst_fts.c           # Linked list functions for message queue
├── utils.c             # Helper functions and input validation
├── cleanup.c           # Memory and mutex cleanup functions
├── Makefile            # Build configuration
└── README.md           # Project documentation
```

---

Made with ❤️ by **[mratke](https://github.com/Grihladin)** - 42 Heilbronn
