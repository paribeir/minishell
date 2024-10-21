# Minishell

## Overview

**Mini(s)hell** is a Unix-like shell written in C that mimics Bash. It has a history, allows you to run commands and built-ins, handles pipes, redirection, heredoc and basic signals (SIGINT, SIGTERM, EOF).

## Features

- Displays a prompt and waits for user input
- Has a history
- Runs binaries and bulabsolute paths
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
- Supports heredoc `<<`, with special attention to bash's specific behaviour (var expansion, signal handling, quotes)
- Environment variables
- single (`'`) and double (`"`) work quotes like in Bash
- Basic signal handling for `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`
