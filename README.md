# get_next_line

> **42 cursus** · C · read a file line by line from a file descriptor.

A function that returns the next line from a file descriptor on each call, handling any buffer size through a persistent static buffer.

## Features

- Reads one line per call, newline included
- Works with files, stdin and any valid file descriptor
- Configurable read size via the `BUFFER_SIZE` macro
- Bonus: handles multiple file descriptors simultaneously

## Build

```bash
cc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

## Usage

```bash
char *line;
int fd = open("file.txt", O_RDONLY);
while ((line = get_next_line(fd)))
{
    printf("%s", line);
    free(line);
}
```

## Key concepts

Static variables, dynamic memory, and buffered reading with `read()`.

---

*42 cursus project — [github.com/rjacquet31](https://github.com/rjacquet31)*
