# The-Dining-Philosophers

## Overview

This solution addresses the classic synchronization problem known as the Dining Philosophers. It involves five philosophers who alternately think and eat from a limited number of forks (in this case, five). The implementation uses IPC semaphores to avoid deadlock and ensure that each philosopher can eat and think without causing resource contention.

## Features

- Implements a deadlock-free solution to the Dining Philosophers problem.
- Uses IPC semaphores for managing access to forks.
- Demonstrates process synchronization and inter-process communication.

## Compilation and Execution

### Requirements

- A Unix-like operating system with support for IPC semaphores.
- GCC or another C compiler that supports POSIX standards.

### Compilation

Compile the program using the following command:

```sh
gcc -o dining_philosophers dining_philosophers.c -lpthread
```

This command compiles the `dining_philosophers.c` file into an executable named `dining_philosophers`, linking the pthread library as needed for semaphore operations.

### Running the Program

Run the compiled executable with:

```sh
./dining_philosophers
```

Upon execution, the program simulates the actions of the philosophers as they think, become hungry, eat, and then put away their forks to think again.

## Program Structure

The solution is structured around key functions:

- `grab_forks(int left_fork_id)`: A philosopher calls this function to acquire the forks on both their left and right sides.
- `put_away_forks(int left_fork_id)`: This function is called by a philosopher to release the forks after eating.

Each philosopher is represented as a process that alternates between thinking and eating. Forks are represented by semaphores to control access and prevent deadlock.

## Cleaning Up

The program is designed to run indefinitely. To stop it, use a terminal interrupt command like `Ctrl+C`. Upon termination, it cleans up the semaphores used for fork representation.

## Debugging and Troubleshooting

If you encounter any issues with semaphore operations (e.g., `semop`, `semctl` returning errors), ensure your system has support for IPC semaphores and that you have the necessary permissions to create and manipulate them.
