# Minishell

<p align="center">
<img src="https://github.com/user-attachments/assets/fb4c5361-65d3-43af-8634-f9dae24e1636" alt="Minishell banner"/>
</p>

## Overview

**Mini(s)hell** is a Unix-like shell written in C that mimics Bash. It has a history, allows you to run commands and built-ins, handles pipes, redirections, heredocs and basic signals (SIGINT, SIGTERM, EOF).

## Features

- Displays a prompt and waits for user input
- Has a history
- Runs binaries and built-ins, also with absolute paths
- Supports the following built-in commands:
  - `echo` with `-n` option
  - `cd` (change directory)
  - `pwd` (print current directory)
  - `export` (set environment variables)
  - `unset` (remove environment variables)
  - `env` (list environment variables)
  - `exit` (exit the shell)
- Supports pipes (`|`)
- Supports redirect in `<`, redirect out `>`, append `>>`)
- Supports heredoc `<<`, with special attention to bash's heredoc-specific behaviour (var expansion, signal handling, quotes)
- Environment variables
- Single (`'`) and double (`"`) quotes
- Basic signal handling for `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`
