# 01 — File Descriptors

This is my first experiment while learning Unix/Linux system programming.

The goal of this experiment is to understand **file descriptors**, especially the standard file descriptors:

```text
0 → stdin
1 → stdout
2 → stderr
```

I am learning this before moving on to `open()`, `read()`, and other system calls.

---

## What is a file descriptor?

A file descriptor (FD) is a small integer that a process uses to refer to an open input/output object managed by the kernel.

The three standard file descriptors are:

```text
0 → standard input  (stdin)
1 → standard output (stdout)
2 → standard error  (stderr)
```

For example:

```c
write(1, "hello\n", 6);
```

The `1` is the file descriptor.

It means:

> Write these bytes to whatever object is currently represented by file descriptor 1.

Normally, FD 1 is connected to standard output, which is usually my terminal.

---

# Experiment 1 — Understanding the numbers

### `fd_demo.c`

My first program was:

```c
#include <stdio.h>

int main(void)
{
    printf("stdin  = %d\n", 0);
    printf("stdout = %d\n", 1);
    printf("stderr = %d\n", 2);

    return 0;
}
```

This program simply prints the conventional numbers:

```text
stdin  = 0
stdout = 1
stderr = 2
```

At this stage, I was only printing the numbers. I wasn't actually using the file descriptors.

---

# Experiment 2 — Using `write()`

After understanding the numbers, I moved away from `printf()` and started using `write()`.

### `fd_demo2.c`

```c
#include <unistd.h>

int main(void)
{
    write(1, "Hello from stdout\n", 18);

    return 0;
}
```

Here:

```c
write(1, "Hello from stdout\n", 18);
```

means:

```text
FD     = 1
data   = "Hello from stdout\n"
bytes  = 18
```

Since FD 1 normally represents stdout, the message appears in the terminal.

This was the first time I actually used a file descriptor.

---

# Experiment 3 — stdout vs stderr

### `fd_demo3.c`

```c
#include <unistd.h>

int main(void)
{
    write(1, "this is stdout\n", 15);
    write(2, "this is stderr\n", 15);

    return 0;
}
```

Here I used two different file descriptors:

```text
1 → stdout
2 → stderr
```

When running normally:

```bash
./fd_demo3
```

both messages appear in the terminal.

Even though they appear in the same terminal, they are still two different file descriptors.

---

# Experiment 4 — Redirecting stdout

I then tested:

```bash
./fd_demo3 > output.txt
```

My actual output was:

```text
this is stderr
```

The stdout message did not appear in the terminal.

Then I checked the file:

```bash
cat output.txt
```

My output was:

```text
this is stdout
```

This showed me that:

```text
FD 1 → output.txt
FD 2 → terminal
```

The program itself did not change.

It still executed:

```c
write(1, "this is stdout\n", 15);
write(2, "this is stderr\n", 15);
```

The shell changed where FD 1 was connected before starting the program.

---

# Experiment 5 — Redirecting stderr

Next I tested:

```bash
./fd_demo3 2> error.txt
```

My actual output was:

```text
this is stdout
```

The stderr message was redirected into the file.

Then:

```bash
cat error.txt
```

gave:

```text
this is stderr
```

So now I could see the difference clearly:

```text
./fd_demo3 > output.txt

FD 1 → output.txt
FD 2 → terminal
```

And:

```text
./fd_demo3 2> error.txt

FD 1 → terminal
FD 2 → error.txt
```

---

# What I learned

The biggest thing I learned is that `1` and `2` are not just random numbers.

They are file descriptors belonging to the process.

Normally:

```text
0 → stdin
1 → stdout
2 → stderr
```

A program can use these descriptors directly:

```c
write(1, ...);   // stdout
write(2, ...);   // stderr
```

The shell can also change what these descriptors refer to.

For example:

```bash
./program > output.txt
```

redirects FD 1.

And:

```bash
./program 2> error.txt
```

redirects FD 2.

---

# My mental model

I currently think about a process like this:

```text
                 MY PROCESS
                     │
        ┌────────────┼────────────┐
        │            │            │
       FD 0         FD 1         FD 2
        │            │            │
        ▼            ▼            ▼
      stdin        stdout       stderr
        │            │            │
        └────────────┴────────────┘
                     │
                  terminal
```

But the shell can redirect them:

```text
./program > output.txt

FD 1 ─────────► output.txt
FD 2 ─────────► terminal
```

or:

```text
./program 2> error.txt

FD 1 ─────────► terminal
FD 2 ─────────► error.txt
```

This helped me understand that a file descriptor is an **interface/handle used by the process**, while the thing it refers to can be different.

---

# Why this matters for `open()` and `read()`

The next step is `open()`.

So far I have:

```text
0 → stdin
1 → stdout
2 → stderr
```

When I use `open()` to open another file, I should expect the kernel to give me another file descriptor, for example:

```text
0 → stdin
1 → stdout
2 → stderr
3 → some file I opened
```

Then I can use that descriptor with:

```c
read(3, ...);
write(3, ...);
close(3);
```

So the important idea I want to carry into the next experiment is:

> A file descriptor is a number that my process uses to refer to an open I/O object managed by the kernel.

---

## Experiments completed

```text
01_file_descriptor/
├── fd_demo.c
├── fd_demo2.c
├── fd_demo3.c
├── output.txt
├── error.txt
└── README.md
```

Next:

```text
02_open/
└── open_demo.c
```

The next goal is to understand **why `open()` returns a file descriptor and why the first newly opened file is commonly FD 3**.
