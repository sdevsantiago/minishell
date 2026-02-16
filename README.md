<div align="center">

  <!-- Project badge -->
  <a href=".">
    <img src=".github/README/minishelln.png">
  </a>

  <!-- Project name -->
  <h1>minishell</h1>

  <!-- Short description -->
  <p>A simple bash-like shell written in C.</p>

  <!-- Info badges -->
  <img src="https://img.shields.io/badge/Score-101%2F100-brightgreen?style=for-the-badge&labelColor=black" alt="Score">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&labelColor=black" alt="Language">
  <br>
  <img src="https://img.shields.io/github/last-commit/sdevsantiago/minishell?display_timestamp=committer&style=for-the-badge&labelColor=black" alt="Last commit">
  <br>
  <img src="https://github.com/sdevsantiago/minishell/actions/workflows/norminette.yml/badge.svg">
  <img src="https://github.com/sdevsantiago/minishell/actions/workflows/makefile.yml/badge.svg">

</div>

---

## ℹ️ About Project

> The purpose of this project is to create a simple bash-like shell.

**minishell** is a minimal bash-like shell implementation written in C. It provides essential shell functionality including command execution, piping, input/output redirection, and built-in commands.

### Key Features

- **Command Execution**: Execute external programs with argument parsing and path resolution.
- **Pipelines**: Connect multiple commands using the pipe operator (`|`).
- **Redirections**: Support for input (`<`), output (`>`), and append (`>>`) file redirections.
- **Built-in Commands**: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`.
- **Environment Variables**: Access and manage shell environment variables.
- **Interactive Shell**: Read-Evaluate-Print Loop (REPL) powered by GNU Readline.
- **Quote Handling**: Proper handling of single and double quotes for literal strings.

For detailed info, refer to this project [subject](docs/en.subject.pdf).

## 🚀 Getting Started

### Prerequisites

- GCC compiler
- Make utility
- Unix-like system (Linux, macOS, WSL)

### Install prerequisites

- APT

  ```bash
  sudo apt install build-essential libreadline-dev
  ```

- Pacman

  ```bash
  sudo pacman -Sy base-devel readline-devel
  ```

## 🔧 Build

1. **Clone the repository:**
    ```bash
    git clone https://github.com/sdevsantiago/minishell.git
    cd minishell
    ```

2. **Compile the project:**
    ```bash
    make        # Full compilation
    ```

3. **Clean build files:**
    ```bash
    make clean  # Remove object files
    ```

#### Available Make Targets

| Command | Description |
|---------|-------------|
| `make` | Compiles all |
| `make all` | Same as `make` |
| `make clean` | Remove object files (*.o) |
| `make fclean` | Remove object files and binaries |
| `make re` | Clean and rebuild everything |

## 👨‍💻 Usage

### Basic Usage

1. **Execute the shell**

```bash
./minishell
```

2. **Interact with it like if it was bash**
```bash
echo "Hello, World!"
...
cat groceries.txt | grep tomatoes
...
echo "Greetings $USER!" > greetings.txt
```

## 📏 Norminette

The code strictly complies with 42's **Norminette v4**:

```bash
norminette *.c *.h
```

More info in the official [Norminette](https://github.com/42school/norminette) repository.

## 🙇‍♂️ Special thanks

- [lrcouto](https://github.com/lrcouto) and [ayogun](https://github.com/ayogun) for creating and publishing, respectively, the [42-project-badges](https://github.com/ayogun/42-project-badges) repository.
- [gcamerli](https://github.com/gcamerli) for creating the [42unlicense](https://github.com/gcamerli/42unlicense) repository.

## ⚖️ License

<div align="center">

<a href="./LICENSE">
<img src="https://img.shields.io/badge/License-42_Unlicense-red?style=for-the-badge&labelColor=black">
</a>

</div>

**This work is published under the terms of [42 Unlicense](LICENSE).** This means you are free to use, modify, and share this software.
