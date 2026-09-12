# Phase 4 — Learning `write()` System Call

In Phase 3, I learned how `read()` gets data from a file into a buffer.
In this phase, I learned the opposite operation — how `write()` sends data from a buffer to stdout, stderr, or a file.

The basic syntax is:

```c
ssize_t write(int fd, const void *buf, size_t count);
```

Where:

```text
fd      → file descriptor
buf     → address of data in memory
count   → number of bytes to write
```

The main idea I learned is:

```text
read()  → source → buffer
write() → buffer → destination
```

---

## Experiment 1 — `write()` to stdout

### Goal

To understand how `write()` can print data to the terminal without using `printf()`.

### Code

```c
#include <unistd.h>

int main(void)
{
    char msg[] = "Hello from write()\n";

    write(1, msg, sizeof(msg) - 1);

    return 0;
}
```

Here `1` is the file descriptor for stdout.

### Output

```text
PASTE YOUR OUTPUT HERE
```

### What I learned

`write(1, ...)` sends the given bytes to stdout, which normally means the terminal.

---

# Experiment 2 — Understanding `count`

### Goal

To understand that `write()` works with a specific number of bytes.

### Code

```c
#include <unistd.h>

int main(void)
{
    char msg[] = "ABCDEFGHIJ\n";

    write(1, msg, 5);

    return 0;
}
```

### Output

```text
PASTE YOUR OUTPUT HERE
```

### What I learned

The third argument tells `write()` how many bytes to write. It does not automatically write the complete C string.

This made me understand that `write()` is **byte-oriented**.

---

# Experiment 3 — `write()` to stderr

### Goal

To understand the difference between stdout and stderr.

### Code

```c
#include <unistd.h>

int main(void)
{
    char message[] = "Normal output\n";
    char error[] = "Error output\n";

    write(1, message, sizeof(message) - 1);
    write(2, error, sizeof(error) - 1);

    return 0;
}
```

### Output

```text
PASTE YOUR OUTPUT HERE
```

### What I learned

```text
1 → stdout
2 → stderr
```

Both normally appear on the terminal, but they are separate file descriptors.

I also tested stdout redirection using:

```bash
./write_to_stderr > output.txt
```

This showed me that stdout and stderr can be redirected separately.

### `output.txt`

```text
PASTE YOUR OUTPUT HERE
```

---

# Experiment 4 — Writing directly to a file

### Goal

To combine `open()` from Phase 2 with `write()`.

### Code

```c
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    char msg[] = "Hello from write() to a file!\n";

    write(fd, msg, sizeof(msg) - 1);

    close(fd);

    return 0;
}
```

### Output

```text
PASTE YOUR TERMINAL OUTPUT HERE
```

### `output.txt`

```text
PASTE FILE CONTENT HERE
```

### What I learned

`open()` returns a file descriptor, and that descriptor can then be passed to `write()`.

For example:

```text
open() → fd = 3
           ↓
write(3, buffer, count)
           ↓
       output.txt
```

---

# Experiment 5 — Checking the return value

### Goal

To understand what `write()` returns.

### Code

```c
ssize_t n = write(fd, msg, sizeof(msg) - 1);
```

### What I learned

The return value tells how many bytes were actually written.

```text
n > 0  → number of bytes written
n == 0 → no bytes written
n < 0  → error
```

Checking the return value is important instead of assuming every `write()` succeeds completely.

### Output

```text
PASTE YOUR OUTPUT HERE
```

---

# Experiment 6 — Intentionally creating an error

### Goal

To see what happens when `write()` is used with a file opened only for reading.

### Important part

```c
int fd = open("output.txt", O_RDONLY);

ssize_t n = write(fd, msg, sizeof(msg) - 1);

if (n < 0)
    perror("write");
```

### Output

```text
PASTE YOUR OUTPUT HERE
```

### What I learned

A file descriptor has an access mode. If I open a file using `O_RDONLY`, I cannot use that descriptor for writing.

This also helped me understand how `write()` errors can be checked using its return value and `perror()`.

---

# Key Takeaways

After these experiments, I understand:

```text
write(fd, buffer, count)
```

as:

> Write up to `count` bytes from my buffer to the object represented by `fd`.

I learned:

* `1` normally represents stdout.
* `2` normally represents stderr.
* `open()` gives a file descriptor that can be used with `write()`.
* `write()` works with bytes, not specifically with C strings.
* The return value of `write()` should be checked.
* stdout and stderr are separate streams.
* A file opened with `O_RDONLY` cannot be used for writing.

### Basic flow

```text
User buffer
    ↓
  write()
    ↓
File Descriptor
    ↓
  Kernel
    ↓
Destination
```

This phase gives me the basic foundation required to combine `open()`, `read()`, and `write()` in the next experiments.
