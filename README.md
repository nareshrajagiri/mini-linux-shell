# Mini Linux Shell (C, POSIX)

A minimal Linux shell implemented in C to demonstrate core operating system
concepts such as process creation, signal handling, and inter-process communication.

## Features
- Execute external commands
- Built-in commands (`cd`, `exit`)
- Signal handling (`Ctrl+C`, background jobs)
- Single pipe support (`cmd1 | cmd2`)

## Build & Run

```bash
make
./mini-shell
```