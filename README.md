#   Minishell

## 📌 Description

Minishell is a simplified Unix shell written in C as part of the 42 curriculum.
The goal of this project is to understand how a shell works by recreating its core functionalities, including command execution, environment variables, pipes, and redirections.

This project focuses on process management, file descriptors, signals, and parsing.

## 🚀 Features

Minishell implements the following features:

- Display a prompt and wait for user input
- Execute commands with absolute or relative paths
- Handle environment variables (`$VAR`)
- Built-in commands:
    - echo (with `-n`)
    - cd
    - pwd
    - export
    - unset
    - env
    - exit

- Pipes (`|`)

- Redirections:
    - Input `<`
    - Output `>`
    - Append `>>`
    - Heredoc `<<`

- Signal handling:
    - `Ctrl-C`
    - `Ctrl-D`
    - `Ctrl-\`

- Proper error handling and exit status management

## ⚙️ Installation & Compilation

Clone the repository and compile the project:

```bash
git clone https://github.com/minicube707/C--Minishell.git
cd minishell
make
```

This will generate the executable:

```bash
./minishell
```

## 🧪 Usage

Once launched, Minishell behaves like a basic shell:

```bash
Minishell> echo Hello World
Hello World

Minishell> ls -l | grep minishell
```

To exit:

```bash
Minishell> exit
```

## 🧪 Tests

A file containing multiple execution examples and test cases is available at:
doc/execution-exemple.txt

## ⭐ Bonus

- Wildcards (`*`) limited to the current working directory
- Logical operators (`&&`, `||`) 
- Environment variable expansion inside double quotes (`"`) and single quotes (`'`)

## 🌟 Extra-Bonus

- Wildcards (`*`) behaving like in Bash
- Subshell management with parentheses `()`

##  📚 What We Learned

- How shells manage processes and file descriptors
- Parsing complex user input
- Implementing built-in commands
- Handling Unix signals correctly
- Memory management and error handling in C

## 🧑‍🎓 Authors

- `fmotte`  
    - -> Execution
    - -> Built-in
    - -> `$` expand
    - -> `*` expand
    - -> Manage fd

- `lupayet`
    - -> Parsing
    - -> Lexing
    - -> Built-in
    - -> Manage signal


##  ✅ Status
⭐ Project validated: 125 / 125


## 📜 License

This project is part of the 42 School curriculum and is intended for educational purposes only.

