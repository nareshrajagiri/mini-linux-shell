# Mini Linux Shell (C, POSIX)

A minimal, modular Linux shell implemented in C to demonstrate core
operating system concepts such as process creation, signal handling,
inter-process communication, and job control.



---

## 📌 Features

- Execute external commands using `fork`, `execvp`, and `wait`
- Argument parsing (e.g., `ls -l`, `ps aux`)
- Built-in commands:
  - `cd` — change directory
  - `exit` — terminate shell
- Signal handling:
  - `Ctrl+C` terminates the running command, not the shell
  - Zombie process cleanup using `SIGCHLD`
- Background execution using `&`
- Single pipe support (`cmd1 | cmd2`)
- Modular code structure with Makefile-based build

---

## 🧠 Design Overview

### Shell Execution Model

The shell follows the classic Unix execution flow:

1. Read user input
2. Parse input into an argument vector (`argv`)
3. Handle built-in commands in the parent process
4. Create child processes using `fork`
5. Replace child process image using `execvp`
6. Wait for foreground jobs or continue for background jobs

---

### Built-in Commands

Commands like `cd` must run in the shell process itself because they modify
the shell’s internal state (current working directory).
These commands are handled before any `fork` call.

---

### Signal Handling

- The shell ignores `SIGINT` so it does not exit on `Ctrl+C`
- Child processes restore default signal behavior
- `SIGCHLD` is handled to clean up terminated background processes

---

### Pipes

Single pipes are implemented using `pipe()` and `dup2()`:
- One child process writes output to the pipe
- Another child process reads input from the pipe

---

## 🗂️ Project Structure

```
mini-linux-shell/
├── src/
│   ├── main.c        # Shell loop and orchestration
│   ├── parser.c      # Input parsing logic
│   ├── builtins.c    # Built-in command handling
│   ├── executor.c    # Process creation and execution
│   ├── signals.c     # Signal handling logic
│   └── pipe.c        # Pipe execution logic
├── include/
│   ├── parser.h
│   ├── builtins.h
│   ├── executor.h
│   ├── signals.h
│   └── pipe.h
├── Makefile
├── README.md
└── .gitignore

```



---

## ⚙️ Build & Run

### Build
```bash

make

./mini-shell

```


## Example Usage

```
mini-shell> ls -l
mini-shell> cd /tmp
mini-shell> sleep 5 &
mini-shell> ls | wc -l
mini-shell> exit
```

---

## 🎯 Learning Outcomes

Through this project, I gained hands-on experience with:

1. POSIX process lifecycle (fork, exec, wait)
2. Parent vs child process responsibilities
3. Signal handling and job control
4. Inter-process communication using pipes
5. Modular C project organization
6. Makefile-based builds
