# Mini Linux Shell (C, POSIX)

A minimal Linux shell implemented in C to demonstrate core operating system
concepts such as `process creation`, `signal handling`, and `inter-process communication`.

## Features
- Execute external commands
- Argument parsing (`ls -l`, `ps aux`)
- Built-in commands (`cd`, `exit`)
- Signal handling (`Ctrl+C`, background jobs)
- Single pipe support (`cmd1 | cmd2`)

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

## Build & Run

```bash
make
./mini-shell
```

## 📘 Documentation

For detailed design explanations and OS-level concepts, refer to:
- docs/design.md
