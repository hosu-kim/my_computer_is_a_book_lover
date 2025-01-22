<div align="center">
	<h1>my_file_content_reader 📄🧐✍️</h1>
    <img src="https://github.com/user-attachments/assets/b268e4fb-4c9d-4dcf-b0ac-f86ef159f705" width="400" alt="A black cute pug reading a book">
</div>

## Overview
`get_next_line` is a simple function that reads a line from a file descriptor. The function is designed to be called in a loop, returning one line at a time from the file descriptor until the end of the file is reached. This project is a common exercise in C programming, often used to practice file I/O operations and dynamic memory management.
## Features
- Reads a line from a file descriptor.
- Handles multiple calls to return successive lines.
- Manages memory dynamically to accommodate varying line lengths.
## Files
- `get_next_line.c`: Contains the main logic for reading lines from a file descriptor.
- `get_next_line_utils.c`: Utility functions used by get_next_line.c, such as string manipulation and memory management functions.
- `get_next_line.h`: Header file containing function prototypes and necessary includes.
## Functions
### `get_next_line.c`
- `line_into_storage(int fd, char *line_storage)`: Reads from the file descriptor and appends the data to the line storage.
- `extract_line(char *line_storage)`: Extracts a single line from the line storage.
- `new_line_storage(char *line_storage)`: Updates the line storage after a line has been extracted.
- `get_next_line(int fd)`: Main function to be called by the user, which coordinates the reading, extracting, and updating of lines from the file descriptor.
### `get_next_line_utils.c`
- `ft_strlen(const char *s)`: Returns the length of a string.
- `ft_strchr(const char *s, int c)`: Returns a pointer to the first occurrence of a character in a string.
- `ft_strdup(const char *s1)`: Returns a duplicate of the provided string.
- `ft_strjoin_and_free(char *s1, const char *s2)`: Joins two strings and frees the first string.
- `ft_bzero(void *s, size_t n)`: Sets a block of memory to zero.
## Usage
To use the get_next_line function, include get_next_line.h in your C program and call get_next_line with the file descriptor you wish to read from.

Example:
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```
## Compilation
To compile the `get_next_line` function, you can use the following command:
```sh
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1024 get_next_line.c get_next_line_utils.c -o get_next_line
```
## License
This project is licensed under the MIT License. See the LICENSE file for details.
