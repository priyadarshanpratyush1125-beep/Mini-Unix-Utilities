# Mini Unix Utilities

A small systems programming project where I am building my own versions of some basic Unix utilities in **C**.

The main purpose of this project is not just to make `cat`, `cp`, and `wc` work. I want to understand **how these commands work internally** and how a C program communicates with the Linux kernel through low-level file I/O.

## What am I building?

I will implement:

* `mycat` → display the contents of a file
* `mycp` → copy one file to another
* `mywc` → count lines, words, and bytes

Instead of using high-level functions like `fopen()` and `fread()`, I will mainly work with:

```c
open()
read()
write()
close()
```

This will help me understand **file descriptors, buffers, system calls, and low-level file handling**.

## How I am going to build it

I don't want to directly copy the implementation of these commands.

I will follow a learn → experiment → implement approach.

For example, before making `mycat`:

```text
Learn file descriptors
        ↓
Learn open()
        ↓
Learn read()
        ↓
Learn write()
        ↓
Make small C experiments
        ↓
Understand how they work
        ↓
Implement mycat
        ↓
Test it against cat
```

Then I will use the same approach for `mycp` and `mywc`.

## Project Structure

```text
mini-unix-utils/
│
├── experiments/
│   ├── 01_file_descriptor/
│   ├── 02_open/
│   ├── 03_read/
│   ├── 04_write/
│   ├── 05_close/
│   └── 06_error_handling/
│
├── src/
│   ├── mycat.c
│   ├── mycp.c
│   └── mywc.c
│
├── tests/
│   └── input.txt
│
├── Makefile
└── README.md
```

The `experiments` folder contains the small programs I write while learning each concept.

The `src` folder contains the actual utilities.

## What I will learn

During this project I will learn about:

* File descriptors
* `stdin`, `stdout`, and `stderr`
* `open()`
* `read()`
* `write()`
* `close()`
* Buffers
* EOF
* Error handling with `errno` and `perror()`
* File metadata with `stat()`
* File offsets with `lseek()`
* Basic system call behavior
* Using `strace` to see system calls
* Building C programs using `gcc` and `make`

## Goal

By the end of this project, I want to be able to explain not only **what my programs do**, but also what happens when a program opens, reads, writes, and closes a file at the Linux system level.

This project is mainly for learning **C, Linux, system calls, and systems programming**.
