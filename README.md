# 42 School - Philosophers Project

A classic implementation of the **Dining Philosophers Problem** using C, demonstrating threading, process management, and synchronization techniques.

## 📋 Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Testing](#testing)
- [Output Format](#output-format)

## 🎯 Overview

The Dining Philosophers Problem is a classic synchronization problem in computer science that illustrates the challenges of resource allocation and deadlock prevention in concurrent programming.

### Problem Description:

- N philosophers sit around a circular table
- Each philosopher alternates between thinking, eating, and sleeping
- There is one fork between each pair of adjacent philosophers
- A philosopher needs both left and right forks to eat

### Challenge:

Prevent deadlock while ensuring all philosophers can eat efficiently.

## 📁 Project Structure

```
philosophers/
├── philos/                 # Mandatory part (threads + mutexes)
│   ├── include/
│   │   └── philos.h
│   ├── src/
│   │   ├── main.c         # Main program entry point
│   │   ├── args.c         # Argument validation
│   │   ├── init.c         # Data initialization
│   │   ├── routine.c      # Philosopher and monitor routines
│   │   ├── actions.c      # Eating, sleeping, thinking actions
│   │   ├── monitor.c      # Death and completion monitoring
│   │   ├── thread_management.c # Thread creation and management
│   │   ├── utils.c        # Utility functions
│   │   └── cleanup.c      # Memory cleanup
│   └── Makefile
├── libft/                  # Custom C library
│   ├── *.c               # Library source files
│   ├── libft.h           # Library header
│   └── Makefile
└── Makefile               # Main build file
```

## 🚀 Installation

1. **Clone the repository:**

   ```bash
   git clone <repository-url>
   cd philosophers
   ```

2. **Build the project:**
   ```bash
   make                    # Build everything
   make philos            # Build mandatory part only
   ```

## 💻 Usage

### Mandatory Part (philos)

```bash
./philos/philos number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters:

- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time in ms after which a philosopher dies if they haven't eaten
- `time_to_eat`: Time in ms it takes for a philosopher to eat
- `time_to_sleep`: Time in ms a philosopher spends sleeping
- `[number_of_times_each_philosopher_must_eat]`: Optional. If specified, simulation stops when all philosophers have eaten at least this many times

### Example Usage:

```bash
# Basic simulation with 5 philosophers
./philos/philos 5 800 200 200

# Simulation with eating limit
./philos/philos 5 800 200 200 7

# Death test - philosopher should die
./philos/philos 1 800 200 200

# Edge case - should complete without death
./philos/philos 4 410 200 200
```

## 🔧 Implementation Details

### Mandatory Part (Threads + Mutexes):

- Each philosopher is a separate thread
- Forks are represented by mutexes
- Global mutexes for:
  - `meal_lock`: Protects meal count and last meal time
  - `write_lock`: Protects output messages
  - `dead_lock`: Protects death flag
- Deadlock prevention:
  - Odd-numbered philosophers pick up left fork first, then right
  - Even-numbered philosophers pick up right fork first, then left

### Key Features:

- **Deadlock Prevention**: Alternating fork pickup order
- **Death Detection**: Monitor thread checks for philosopher death
- **Completion Detection**: Optional eating limit with completion check
- **Thread Safety**: All shared data protected by mutexes
- **Memory Management**: Proper cleanup of all allocated resources

## 🧪 Testing

### Basic Tests:

```bash
# Normal operation
./philos/philos 5 800 200 200

# Death scenarios
./philos/philos 1 800 200 200    # Should die immediately
./philos/philos 4 310 200 100    # Someone should die

# Completion tests
./philos/philos 5 800 200 200 7  # Should stop after all eat 7 times

# Edge cases
./philos/philos 2 400 200 200    # Minimal case
./philos/philos 100 800 200 200  # Stress test
```

### Expected Behavior:

- Philosophers should eat, sleep, and think in cycles
- No deadlock should occur
- Death should be detected and reported
- Optional completion should work correctly

## 📊 Output Format

The program outputs messages in the following format:

```
[timestamp_ms] [philosopher_id] [action]
```

### Actions:

- `has taken a fork`: Philosopher picked up a fork
- `is eating`: Philosopher is eating
- `is sleeping`: Philosopher is sleeping
- `is thinking`: Philosopher is thinking
- `died`: Philosopher has died

### Example Output:

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
400 1 is thinking
400 2 is sleeping
```

## 🛠️ Build Commands

```bash
make        # Build everything
make clean  # Remove object files
make fclean # Remove object files and executables
make re     # Rebuild everything
```

## 📝 Notes

- The program uses milliseconds for all time measurements
- Philosophers start eating immediately when they get both forks
- The simulation continues until a philosopher dies or all complete their eating limit
- All output is thread-safe and properly synchronized
