*This project has been created as part of the 42 curriculum by isoulima.*

# Get Next Line

<img src="score.png" width="150" alt="Score 105/100">

![Language](https://img.shields.io/badge/Language-C-blue)
![Norminette](https://img.shields.io/badge/Norminette-OK-brightgreen)

## Description

Get Next Line is a function that reads a file line by line from a file descriptor. The project teaches memory management, the use of static variables to keep state between calls, and buffered reading with `read()`. The function can read from files as well as from standard input, whatever the `BUFFER_SIZE`.

---

## Instructions

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

`BUFFER_SIZE` can be changed to test different behaviors. Without the `-D` flag, the default value is 42 (defined in `get_next_line.h`).

### Usage

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    int   fd = open("file.txt", O_RDONLY);
    char  *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## Features

- Reads line by line from a file descriptor
- Each returned line includes the `\n` (except at end of file without a `\n`)
- Works on files and standard input
- Compatible with any `BUFFER_SIZE` (1, 42, 9999, 10000000...)
- Returns `NULL` at end of file or on error

---

## Technical choices

The implementation relies on a **stash** (persistent memory reserve kept in a static variable):

1. On the first call, the stash is initialized with `ft_strdup("")` (empty string)
2. `read_to_stash` reads into a buffer with `read()` and appends it to the stash through `stash_join` (which uses `ft_strjoin` and frees the old stash)
3. The read loop stops as soon as a `\n` is found in the stash (with `ft_strchr`) or `read()` returns 0
4. `stash_line` extracts the line: if a `\n` is found, `ft_substr` cuts the line and `ft_strdup` keeps the remainder; otherwise the whole stash is returned and the pointer is set to `NULL`
5. On a `read()` or `malloc` error, `error_free` cleanly frees the buffer and the stash

**Code structure:**
- `get_next_line.c`: 4 static functions (`error_free`, `stash_join`, `read_to_stash`, `stash_line`) + the public `get_next_line` function
- `get_next_line_utils.c`: 5 re-implemented utility functions (`ft_strlen`, `ft_strdup`, `ft_strchr`, `ft_strjoin`, `ft_substr`) since libft is not allowed in this project

This approach was chosen because it only reads what is strictly needed on each call, without loading the whole file into memory. The static variable keeps state between calls without using global variables (forbidden by the subject).

---

## Resources

- `man read`
- Documentation on file descriptors
- Documentation on static variables in C
- Dynamic memory management (`malloc`, `free`)
- Official 42 subject

---

## AI usage

AI was used only to:
- clarify some points of the subject
- structure this README

The implementation, the logic and the understanding of the code were done manually.

---

## Author

42 Lausanne
Login: isoulima
