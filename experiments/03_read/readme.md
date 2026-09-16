# Phase 3 — Learning `read()` in Linux

## Objective

In Phase 2, I learned how `open()` gives a file descriptor.
In this phase, I learned how to actually **read data from that file descriptor** using the Linux `read()` system call.

The basic flow is:

```text
File
 ↓
open()
 ↓
File Descriptor
 ↓
read()
 ↓
Buffer
 ↓
write()
 ↓
Terminal
```

The function I am learning is:

```c
ssize_t read(int fd, void *buf, size_t count);
```

Where:

* `fd` → file descriptor from which data is read
* `buf` → memory where the data will be stored
* `count` → maximum number of bytes to read
* return value → number of bytes actually read

### Return values

```text
n > 0   → bytes were successfully read
n == 0  → EOF (End Of File)
n < 0   → error
```

One important thing I learned is that `read()` does **not** always read the complete file in one call.

---

# Experiment A — Read 5 Bytes

### Goal

I wanted to check what happens when I request only 5 bytes.

```c
n = read(fd, buffer, 5);
```

For the test file:

```text
Hello Pratyush Priydarshan
```

I expected only the first 5 bytes to be read.

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/03_read/Experiment A$ ./read_exactly_5_bytes 
read() returned: 5
```

### What I learned

`read()` reads **up to** the number of bytes specified by `count`.

---

# Experiment B — Read 10 Bytes

### Goal

I changed the requested size from 5 to 10:

```c
n = read(fd, buffer, 10);
```

This was to compare how changing `count` affects the result.

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/03_read/Experiment B$ ./read_exactly_10_bytes 
read() returned: 10
```

### What I learned

The third argument tells `read()` the **maximum number of bytes** it can return.

It does not mean that the entire file will be read.

---

# Experiment C — File Larger Than Buffer

### Goal

I used a file containing:

```text
PRATYUSH PRIYADARSHAN COLLEGE-ABESEC GZB
```

and a buffer of only 10 bytes:

```c
char buffer[10];
```

Then I called `read()` only once.

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/03_read/Experiment C$ ./File_larger_than_buffer 
read() returned: 15
```

### What I learned

Only the amount that fits into the buffer was read. The remaining data was still unread.

This made it clear that:

> One `read()` call does not mean reading the whole file.

---

# Experiment D — Call `read()` Twice

### Goal

After Experiment C, I wanted to see what happens when I call `read()` again using the same file descriptor.

For example:

```c
n = read(fd, buffer, 10);
```

followed by another:

```c
n = read(fd, buffer, 10);
```

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/03_read/Experiment D$ ./Call_read\(\)_twice 
First read: 10 bytes
PRATYUSH P
Second read: 10 bytes
RIYADARSHA
```

### What I learned

The second `read()` continues from the **current file position**.

For example:

```text
First read  → PRATYUSH P
Second read → RIYADARSHA
```

So `read()` moves the file position forward after successfully reading data.

---

# Experiment E — Read Until EOF

### Goal

Now I wanted to read the complete file even though the buffer is smaller than the file.

I used:

```c
while ((n = read(fd, buffer, sizeof(buffer))) > 0)
{
    write(1, buffer, n);
}
```

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/03_read/Experiment E$ ./Read_until_EOF 
PRATYUSH PRIYADARSHAN
```

### What I learned

A file may need multiple `read()` calls.

For example, with a 10-byte buffer:

```text
read → 10 bytes
read → 10 bytes
read → remaining bytes
read → 0
```

When `read()` returns `0`, it means **EOF**.

This is the main pattern I learned in this phase.

---

# Experiment F — Read an Empty File

### Goal

I created an empty file and tried to read from it.

```text
empty.txt
```

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/03_read/Experiment F$ ./Empty_file 
read() returned: 0
```

### What I learned

When there is no data left to read:

```text
read() → 0
```

This means EOF, not an error.

So now I understand the difference:

```text
> 0  → data
= 0  → EOF
< 0  → error
```

---

# Experiment G — Open a Nonexistent File

### Goal

I tried to open a file that does not exist:

```text
does_not_exist.txt
```

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/03_read/Experiment G$ ./Nonexistent_file 
open: No such file or directory
```

### What I learned

If `open()` fails:

```text
fd == -1
```

I used:

```c
perror("open");
```

to see the reason for the failure.

This also helped me connect `open()` error handling with the `read()` experiments.

---

# Experiment H — Use a 4-Byte Buffer

### Goal

For the final experiment, I used a very small buffer:

```c
char buffer[4];
```

with:

```text
ABCDEFGHIJKLM
```

The expected reading pattern is:

```text
ABCD → 4 bytes
EFGH → 4 bytes
IJKL → 4 bytes
M    → 1 byte
EOF  → 0 bytes
```

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/03_read/Experiment H$ ./Tiny_4_byte_buffer 
ABCD
EFGH
IJKL
M
Read 1: 4 bytes -> Read 2: 4 bytes -> Read 3: 4 bytes -> Read 4: 1 bytes -> EOF reached.
```

### What I learned

This experiment made one thing very clear:

`count` is the **maximum** number of bytes `read()` can return.

If only 1 byte is left, `read()` returns 1 even if I requested 4.

---

# Important Things I Learned

After completing these experiments, I understand:

* How `read()` works with a file descriptor
* Meaning of `fd`, `buffer`, and `count`
* Why `read()` returns `ssize_t`
* How to interpret its return value
* What EOF means
* How the file position changes after `read()`
* Why one `read()` cannot be assumed to read the complete file
* Why a loop is required for reading until EOF
* Why `write()` should use the actual number of bytes read

For example:

```c
n = read(fd, buffer, sizeof(buffer));

if (n > 0)
{
    write(1, buffer, n);
}
```

I should use `n`, not `sizeof(buffer)`, because `n` tells me how many bytes actually contain valid data.

---

# Final Understanding

The main pattern I learned from this phase is:

```c
while ((n = read(fd, buffer, sizeof(buffer))) > 0)
{
    write(1, buffer, n);
}
```

The overall idea is:

```text
open()
  ↓
get file descriptor
  ↓
read some bytes
  ↓
process those bytes
  ↓
read again
  ↓
...
  ↓
read() returns 0
  ↓
EOF
```
