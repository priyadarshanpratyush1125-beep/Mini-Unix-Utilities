# Phase 0 — Unix/Linux Fundamentals

Before jumping into `open()`, `read()`, `write()`, and `close()`, I want to understand what is actually happening when a program works with files in Linux.

The goal of this phase is **not to memorize Linux internals**.

I just want to build a good enough mental model so that when I later write my own versions of:

* `cat`
* `cp`
* `wc`

I understand what my code is actually asking the operating system to do.

---

## What I need to learn

1. Process
2. Kernel
3. User space
4. Kernel space
5. System call
6. POSIX
7. File
8. File descriptor
9. stdin
10. stdout
11. stderr

---

# 1. Process

A process is basically a **program that is currently running**.

For example, if I have:

```bash
./mycat file.txt
```

`mycat` is a program stored on disk.

When Linux starts it, it becomes a **process**.

```text
mycat program
     |
     | Linux runs it
     v
 mycat process
```

A process has its own memory, state, process ID, file descriptors, etc.

For now, the important thing is:

> **Program = code stored somewhere. Process = that program while it is running.**

---

# 2. Kernel

The kernel is the core part of the operating system.

My program cannot just directly access the disk or control hardware whenever it wants.

Instead, it asks the kernel to do things for it.

For example:

```c
read(fd, buffer, 100);
```

My program is basically asking:

> "Kernel, can you read some data for me?"

The kernel handles the actual interaction with the filesystem and hardware.

```text
My program
    |
    | request
    v
 Kernel
    |
    v
 Filesystem / Hardware
```

---

# 3. User Space

Normal programs run in **user space**.

For example:

```text
cat
cp
wc
bash
vim
mycat
```

All of these are user-space programs.

User-space programs have limited privileges. They cannot just modify kernel memory or directly control hardware.

A simple way to think about it:

```text
USER SPACE
-------------------
my program
bash
cat
cp
wc
-------------------
        |
        | system call
        v
KERNEL SPACE
```

My mini Unix utilities will mostly be user-space programs.

---

# 4. Kernel Space

Kernel space is where the kernel runs.

The kernel has much more privilege than normal programs.

It is responsible for things like:

* managing processes
* managing memory
* filesystems
* devices
* networking
* communicating with hardware

For example:

```text
mycat
  |
  | read()
  v
kernel
  |
  v
filesystem
  |
  v
disk
```

I don't need to understand all of kernel space right now.

The main thing I need to remember is:

> **My program runs in user space and uses system calls to ask the kernel for services.**

---

# 5. System Call

A system call is how a user-space program requests something from the kernel.

Some important system calls/functions I'll be using are:

```c
open()
read()
write()
close()
```

There are many others, but these are enough to get started with simple Unix utilities.

For example:

```c
read(fd, buffer, 100);
```

Conceptually:

```text
My program
    |
    | "Please read some data"
    v
  Kernel
    |
    | gets data
    v
  My buffer
```

This is the basic idea behind `cat`.

A simple `cat` can basically do:

```text
open file
    ↓
read file
    ↓
write to stdout
    ↓
close file
```

---

# 6. POSIX

POSIX is a set of standards that defines common interfaces and behavior for Unix-like systems.

It is one reason concepts like:

```c
open()
read()
write()
close()
```

are so important when learning Unix programming.

I can think of POSIX as a **common contract for Unix-like operating systems**.

```text
                 POSIX
                   |
        -----------------------
        |          |          |
      Linux      macOS       BSD
```

The implementations can be different internally, but they share many common interfaces.

For this project, I mainly care about POSIX because I'm trying to learn the **Unix programming model**, not just make something that works on my machine.

---

# 7. File

A file is an object managed by the filesystem.

For now, I'll mostly think about regular files:

```text
file.txt
```

For example:

```text
file.txt

Hello
World
```

My program can ask the kernel to open this file:

```c
open("file.txt", ...);
```

But there is an important thing to understand:

```text
file
```

and

```text
file descriptor
```

are not the same thing.

The file is the object.

The file descriptor is how my process refers to an open file.

---

# 8. File Descriptor

This is probably the most important concept for this project.

A **file descriptor (FD)** is a small integer used by a process to refer to an open file or another I/O object.

For example:

```c
int fd = open("file.txt", ...);
```

Suppose `open()` returns:

```text
3
```

Then:

```text
fd = 3
```

My process might have something like:

```text
FD      Object
--------------------
0       stdin
1       stdout
2       stderr
3       file.txt
```

So when I write:

```c
read(3, buffer, 100);
```

I'm saying:

> "Read from the object associated with file descriptor 3."

This is a very important mental model.

The kernel maintains information about what these descriptors refer to.

```text
My process

FD table
----------------
0 → stdin
1 → stdout
2 → stderr
3 → file.txt
```

This is why `read()` doesn't need the filename again.

It just needs the descriptor.

---

# 9. stdin

`stdin` means **standard input**.

Its file descriptor is normally:

```text
0
```

For example:

```bash
./myprogram
```

If the program reads from stdin, it can receive input from the terminal.

Conceptually:

```text
Keyboard
   |
   v
stdin (FD 0)
   |
   v
myprogram
```

I can read from stdin using:

```c
read(0, buffer, 100);
```

or:

```c
read(STDIN_FILENO, buffer, 100);
```

This becomes useful for `cat`.

When I run:

```bash
cat
```

without giving it a filename, `cat` reads from stdin.

---

# 10. stdout

`stdout` means **standard output**.

Its file descriptor is normally:

```text
1
```

Normally, stdout goes to the terminal.

For example:

```c
write(1, "Hello\n", 6);
```

This writes:

```text
Hello
```

to stdout.

Conceptually:

```text
my program
    |
    | write()
    v
stdout (FD 1)
    |
    v
terminal
```

This is exactly what I need for `cat`.

Suppose:

```text
file.txt

Hello
World
```

My `cat` program can:

```text
file.txt
   |
   | read()
   v
buffer
   |
   | write()
   v
stdout
   |
   v
terminal
```

---

# 11. stderr

`stderr` means **standard error**.

Its file descriptor is normally:

```text
2
```

It is used for error messages and diagnostics.

For example, if I try:

```bash
./mycat does-not-exist.txt
```

my program should report an error.

Conceptually:

```text
mycat
  |
  | error message
  v
stderr (FD 2)
  |
  v
terminal
```

So the three standard file descriptors are:

```text
0 → stdin  → input
1 → stdout → normal output
2 → stderr → error output
```

This is something I should memorize:

> **0 = input, 1 = output, 2 = error**

---

# How Everything Connects

Now I can put all the concepts together.

Suppose I run:

```bash
./mycat hello.txt
```

Linux starts my program as a process.

```text
hello.txt
    |
    v
mycat process
```

The process already has:

```text
FD 0 → stdin
FD 1 → stdout
FD 2 → stderr
```

Then my program calls:

```c
int fd = open("hello.txt", ...);
```

Let's say it returns:

```text
3
```

Now:

```text
FD 0 → stdin
FD 1 → stdout
FD 2 → stderr
FD 3 → hello.txt
```

Then I can do:

```c
read(3, buffer, 100);
```

The idea is:

> "Kernel, read up to 100 bytes from the object represented by FD 3 and put them into my buffer."

Then:

```c
write(1, buffer, n);
```

means:

> "Kernel, write these `n` bytes to the object represented by FD 1."

Since FD 1 is stdout, the data appears on my terminal.

---

# The Big Picture

This is the mental model I'm trying to build:

```text
                 USER SPACE

              mycat process
                   |
                   |
          ┌────────┴────────┐
          |                 |
       read()            write()
          |                 |
          v                 v
       FD 3              FD 1
          |                 |
          v                 v
     hello.txt           stdout
          |                 |
          |                 v
          |              terminal
          |
          v
      KERNEL SPACE
          |
          v
      FILESYSTEM
          |
          v
         DISK
```

Or, more generally:

```text
USER PROGRAM
     |
     | system call
     v
   KERNEL
     |
     v
 FILESYSTEM
     |
     v
   DISK
```

---

# What `read()` Means Now

When I see:

```c
read(fd, buffer, 100);
```

I should no longer think:

> "This magically reads a file."

Instead I should think:

```text
My process
    |
    | read(fd, buffer, 100)
    |
    | fd = which open object?
    | buffer = where should data go?
    | 100 = maximum bytes requested
    v
  KERNEL
    |
    v
object associated with fd
    |
    v
data copied into buffer
```

That's the mental model I need before going deeper into `read()`.

---

# Connection to My Mini Unix Utilities

The reason I'm learning all of this is to eventually build small versions of Unix utilities.

## `cat`

Basic idea:

```text
open()
   ↓
read()
   ↓
write()
   ↓
close()
```

For example:

```text
file.txt
   ↓
 read
   ↓
buffer
   ↓
write
   ↓
stdout
```

---

## `cp`

Basic idea:

```text
open source
     ↓
   read
     ↓
   buffer
     ↓
  write
     ↓
destination
```

So `cp` is basically moving bytes from one file to another.

---

## `wc`

Basic idea:

```text
open()
   ↓
read()
   ↓
analyze buffer
   ↓
count lines/words/bytes
   ↓
print result
```

For example:

```text
hello
world
```

My program reads the bytes and counts them.

---

# Things I Should Remember

The most important points from Phase 0:

```text
Process
    ↓
running program

Kernel
    ↓
core of the OS

User space
    ↓
where my normal program runs

Kernel space
    ↓
where the kernel runs

System call
    ↓
way my program asks the kernel for services

POSIX
    ↓
common Unix-like programming interface/standard

File
    ↓
object managed by the filesystem

File descriptor
    ↓
integer used by my process to refer to an open object

stdin
    ↓
FD 0

stdout
    ↓
FD 1

stderr
    ↓
FD 2
```

The three numbers I definitely need to remember:

```text
0 → stdin
1 → stdout
2 → stderr
```

And the most important relationship:

```text
program
   ↓
system call
   ↓
kernel
   ↓
file/object
```

---

# Phase 0 Goal

I don't need to know the entire Linux kernel.

By the end of Phase 0, I should be able to look at something like:

```c
read(fd, buffer, 100);
```

and understand what is happening conceptually.

Once that makes sense, I'll move on to:

```text
Phase 1
--------
open()
read()
write()
close()
```


and start building my first mini Unix utility: **`cat`**.
