# Phase 2 — Learning `open()`

In Phase 2, I started learning the `open()` system call in C.

The main goal of this phase was to understand **how Linux opens files, how file descriptors are returned, and how different flags change the behavior of `open()`**.

Instead of directly using `open()` in the final `mycat` or `mycp` program, I first made small experiments for each important flag.

---

## What I learned

The basic form of `open()` is:

```c
int fd = open("filename", flags);
```

If the file is opened successfully, `open()` returns a **file descriptor**.

For example:

```text
0 → stdin
1 → stdout
2 → stderr
3 → first file opened by the program
```

If `open()` fails, it returns:

```text
-1
```

I also learned that different flags can change how a file is opened.

---

# Experiments

## 1. Basic `open()`

Folder:

```text
BASIC/
├── open_basic.c
├── open_basic
├── open_create.c
├── open_create
├── newfile.txt
└── does_not_exist.txt
```

### What I learned

First I experimented with opening an existing file.

I also tested what happens when I try to open a file that does not exist.

Then I learned about:

```c
O_CREAT
```

which can be used to create a file when it does not already exist.

### Example idea

```c
open("newfile.txt", O_WRONLY | O_CREAT, 0644);
```

The important thing I understood here is that `O_CREAT` is different from simply opening an existing file.

### My Output

```c
o/p of 1 exp 
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ ls
input.txt  newfile.txt  open_basic.c  open_create  open_create.c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ gcc open_basic.c -o open_basic
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ ls
input.txt  newfile.txt  open_basic  open_basic.c  open_create  open_create.c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ ./open_basic 
fd = 3
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ mv input.txt does_not_exist.txt
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ ls
does_not_exist.txt  newfile.txt  open_basic  open_basic.c  open_create  open_create.c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ ./open_basic 
open: No such file or directory
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ 

o/p of 2 exp 
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ ls
does_not_exist.txt  open_basic  open_basic.c  open_create.c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ gcc open_create.c -o open_create
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ ls
does_not_exist.txt  open_basic  open_basic.c  open_create  open_create.c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ ./open_create 
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/BASIC$ ls
does_not_exist.txt  newfile.txt  open_basic  open_basic.c  open_create  open_create.c
```

---

# 2. `O_RDONLY`

Folder:

```text
O_RDONLY/
├── open_RDONLY.c
├── open_RDONLY
└── log1.txt
```

### What I learned

`O_RDONLY` opens a file in **read-only mode**.

I experimented with opening `log1.txt` and observed the returned file descriptor.

I also understood that opening a file for reading does not mean I can write to it.

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open$ cd O_RDONLY/
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_RDONLY$ gcc open_RDONLY.c -o open_RDONLY
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_RDONLY$ ./open_RDONLY 
Hello
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_RDONLY$ cat log1.txt 
Hello
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_RDONLY$
```

---

# 3. `O_WRONLY`

Folder:

```text
O_WRONLY/
├── open_WRONLY.c
├── open_WRONLY
└── log2.txt
```

### What I learned

`O_WRONLY` opens a file in **write-only mode**.

This helped me understand the difference between:

```text
O_RDONLY → read
O_WRONLY → write
```

I also experimented with the behavior when trying to perform an operation that the selected access mode does not allow.

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open$ cd O_WRONLY/
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_WRONLY$ gcc open_WRONLY.c -o open_WRONLY
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_WRONLY$ ./open_WRONLY 
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_WRONLY$ cat log2.txt 
Pratyush
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_WRONLY$ 
```

---

# 4. `O_RDWR`

Folder:

```text
O_RDWR/
├── open_RDWR.c
├── open_RDWR
└── log3.txt
```

### What I learned

`O_RDWR` opens a file for **both reading and writing**.

So instead of choosing only one access mode:

```text
read only
      OR
write only
```

I can use:

```text
read + write
```

This experiment helped me understand the three basic access modes:

```text
O_RDONLY
O_WRONLY
O_RDWR
```

### My Output

```c

avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_RDWR$ ls
log3.txt  open_RDWR.c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_RDWR$ cat log3.txt 
Hello
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_RDWR$ gcc open_RDWR.c -o open_RDWR
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_RDWR$ ./open_RDWR 
Hello
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_RDWR$ cat log3.txt 
HelloPratyush
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_RDWR$ 
```

---

# 5. `O_APPEND`

Folder:

```text
O_APPEND/
├── open_append.c
├── open_append
└── log.txt
```

### What I learned

`O_APPEND` is used when I want new data to be written at the **end of the file**.

I experimented by writing data multiple times to `log.txt`.

Instead of replacing the existing content, new data was added after the existing content.

This is useful for things like log files.

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_APPEND$ nano log.txt
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_APPEND$ ls
does_not_exist.txt  newfile.txt    open_basic    open_create    open_turncate    test.txt
log.txt             open_append.c  open_basic.c  open_create.c  open_turncate.c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_APPEND$ gcc open_append.c -o open_append
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_APPEND$ cat log.txt
hello 
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_APPEND$ ./open_append 
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_APPEND$ cat log.txt
hello 
Pratyusavatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_APPEND$

```

---

# 6. `O_TRUNC`

Folder:

```text
O_TRUNC/
├── open_turncate.c
├── open_turncate
└── test.txt
```

### What I learned

`O_TRUNC` was one of the important flags I tested.

When a file is opened with `O_TRUNC` and the appropriate write access, its existing contents are **removed and the file size becomes zero**.

For example:

```text
Before:

test.txt
----------------
Hello World
This is a test


After opening with O_TRUNC:

test.txt
----------------
(empty)
```

This helped me understand why flags such as:

```c
O_WRONLY | O_TRUNC
```

are commonly used when a program wants to overwrite a file.

### My Output

```c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_TRUNC$ ls
does_not_exist.txt  newfile.txt  open_basic  open_basic.c  open_create  open_create.c  open_turncate.c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_TRUNC$ gcc open_turncate.c -o open_turncate
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_TRUNC$ ls
does_not_exist.txt  newfile.txt  open_basic  open_basic.c  open_create  open_create.c  open_turncate  open_turncate.c
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_TRUNC$ nano test.txt
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_TRUNC$ cat test.txt
hello my name is pratyush
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_TRUNC$ ./open_turncate 
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_TRUNC$ cat test.txt
avatar@gzb:~/Projects/mini-unix-utils/experiments/02_open/O_TRUNC$ 

```

---

# What I Understand After Phase 2

After these experiments, I now understand the basic behavior of:

```text
O_RDONLY
O_WRONLY
O_RDWR
O_CREAT
O_APPEND
O_TRUNC
```

I also understand that `open()` does not simply mean "open a file".

The **flags tell the kernel what I want to do with that file**.

For example:

```text
open()
  │
  ├── O_RDONLY
  │      → read
  │
  ├── O_WRONLY
  │      → write
  │
  ├── O_RDWR
  │      → read + write
  │
  ├── O_CREAT
  │      → create if needed
  │
  ├── O_APPEND
  │      → write at end
  │
  └── O_TRUNC
         → remove existing contents
```

---

# What I will learn next

Now that I understand `open()`, the next step is to learn:

```text
read()
```

I will learn:

* How `read()` works
* What a buffer is
* How many bytes `read()` actually returns
* What `read() == 0` means
* What happens when `read()` fails
* Reading a file in multiple chunks
* Reading until EOF

After understanding `read()`, I will use it later while implementing my own:

```text
mycat
```

So the overall path is:

```text
File Descriptor
      ↓
open()
      ↓
read()
      ↓
write()
      ↓
close()
      ↓
mycat
      ↓
mycp
      ↓
mywc
```
