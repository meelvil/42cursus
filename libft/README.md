*This project has been created as part of the 42 curriculum by mbou-ani.*

# Description

During the **libft** project, we needed to create our own library named *LIBFT* that will be used in .c files in order to use several functions. A library is a repository containing functions that we created ourselves. They can be used in any file and any program that *"includes"* this library. It means that on top of your files, you wrote *"include "libft.h""*. The program then knows where to look for specific calls that are made inside of it. There are a lot of existing libraries and they all work the same.

Brut example of usage : I have a box containing the instructions to fold a paper into an airplane. If I take a piece of paper without the instructions, I won't be able to know where to look for information, so I will stuck on the first step. If someone points the box in order to make me open it, I will be able to find the correct instructions on folding a paper sheet into an airplane. This is how libraries work.

> Here is what contains the *LIBFT* library :

### Libc functions
| Function name | Description | Input | Output |
| :---: | --- | --- | :---: |
| ft_isalpha | **c** is a letter | **c** = `a` / **c** = `1` | `1` / `0` |
| ft_isdigit | **c** is a number | **c** = `1` / **c** = `a` | `1` / `0` |
| ft_isalnum | **c** is a letter or a number | **c** = `a` / **c** = `1` / **c** = `\n` | `1` / `1` / `0`|
| ft_isascii | **c** is an ASCII | **c** = `a` / **c** = `255` | `1` / `0` |
| ft_isprint | **c** is printable | **c** = ` ` / **c** = `;` / **c** = `\t` | `1` / `1` / `0` |
| ft_strlen | Returns the **length** of a **string** | `Hello World` | `11` |
| ft_memset | Fills the first `n` bytes of a **memory area** with the byte **c** | `str[6]` **c** = `a` n = `3` | `aaa` |
| ft_bzero | Sets the first `n` bytes of a **memory area** to zero | `Hello` n = `5` | `\0\0\0\0\0` |
| ft_memcpy | Copies `n` bytes from a source **memory area** to a destination (areas must not overlap) | `Hello` `dest[10]` n = `5` | `Hello` |
| ft_memmove | Copies `n` bytes from a source to a destination, even if the areas overlap | `Hello` `dest[10]` n = `5` | `Hello` |
| ft_strlcpy | Returns the **length** of the source **string** | `Melvil` `dest[10]` | `6` |
| ft_strlcat | Returns the total **length** of the **string** created (if so) | `Melvil` `2` | `8` |
| ft_toupper | **c** transformed into uppercase | **c** = `m`| `M` |
| ft_tolower | **c** transformed into lowercase | **c** = `M`| `m` |
| ft_strchr | Returns a **pointer** to the first occurrence of **c** in a **string** (`NULL` if not found) | `Hello` **c** = `l` / `Hello` **c** = `z` | `llo` / `NULL` |
| ft_strrchr | Returns a **pointer** to the last occurrence of **c** in a **string** (`NULL` if not found) | `Hello` **c** = `l` / `Hello` **c** = `z` | `lo` / `NULL` |
| ft_strncmp | Compares two **strings** for `n` characters and returns the difference as an **int** | n = `3` : `Heello` `Hello` / n = `6` : `Melvil` `Melvil` | `-7` / `0` |
| ft_memchr | Returns a **pointer** to the first occurrence of **c** in the first `n` bytes of a **memory area** (`NULL` if not found) | `Hello` **c** = `l` n = `5` / `Hello` **c** = `l` n = `2` | `llo` / `NULL` |
| ft_memcmp | Compares two **memory areas** for `n` bytes and returns the difference as an **int** | n = `3` : `Heello` `Hello` / n = `5` : `Hello` `Hello` | `-7` / `0` |
| ft_strnstr | Returns a **pointer** to the first occurrence of a **substring** in a **string**, searching at most `n` characters (`NULL` if not found) | `Hello World` `World` n = `11` / `Hello World` `World` n = `5` | `World` / `NULL` |
| ft_atoi | Takes a **string**, returns a contained number as an **int** | `136World` | `136` |
| ft_calloc | Allocates memory for `n` elements of a given **size** and sets it all to zero | n = `5` size = `4` | `20` bytes set to `0` |
| ft_strdup | Allocates memory to copy a **string** into a new one | `Hello World` | `Hello World` |
### Additional functions
| Function name | Description | Input | Output |
| :---: | --- | --- | :---: |
| ft_substr | Allocates and returns a **substring** of `len` characters starting at index `start` | `Hello World` start = `6` len = `5` | `World` |
| ft_strjoin | Allocates and returns a new **string** made of two **strings** concatenated | `Hello ` `World` | `Hello World` |
| ft_strtrim | Allocates and returns a copy of a **string** without the characters of a **set** at its beginning and end | `xxHelloxx` set = `x` | `Hello` |
| ft_split | Allocates and returns an **array of strings** obtained by splitting a **string** with the delimiter **c** (ends with `NULL`) | `Hello World 42` **c** = ` ` | `Hello` / `World` / `42` |
| ft_itoa | Allocates and returns a **string** representing an **int** | `-136` | `"-136"` |
| ft_strmapi | Applies a function **f** to each character of a **string** (with its index) and returns a new **string** of the results | `abc` **f** = uppercase | `ABC` |
| ft_striteri | Applies a function **f** to each character of a **string** (with its index), modifying it in place | `abc` **f** = uppercase | `ABC` |
| ft_putchar_fd | Writes the character **c** on the file descriptor **fd** | **c** = `a` fd = `1` | `a` |
| ft_putstr_fd | Writes a **string** on the file descriptor **fd** | `Hello` fd = `1` | `Hello` |
| ft_putendl_fd | Writes a **string** followed by a newline on the file descriptor **fd** | `Hello` fd = `1` | `Hello\n` |
| ft_putnbr_fd | Writes an **int** on the file descriptor **fd** | `-42` fd = `1` | `-42` |
### Linked list
| Function name | Description | Input | Output |
| :---: | --- | --- | :---: |
| ft_lstnew | Allocates and returns a new **node** whose `content` is set and `next` is `NULL` | `Hello` | node (`Hello` -> `NULL`) |
| ft_lstadd_front | Adds a **node** at the beginning of a **list** | list `B` -> `C` / new node `A` | `A` -> `B` -> `C` |
| ft_lstsize | Returns the number of **nodes** in a **list** | `A` -> `B` -> `C` | `3` |
| ft_lstlast | Returns the last **node** of a **list** | `A` -> `B` -> `C` | `C` |
| ft_lstadd_back | Adds a **node** at the end of a **list** | list `A` -> `B` / new node `C` | `A` -> `B` -> `C` |
| ft_lstdelone | Frees a **node**'s content with the function **del**, then frees the **node** itself | node `A` **del** = `free` | `A` freed |
| ft_lstclear | Deletes and frees a **node** and all the following ones, then sets the list pointer to `NULL` | `A` -> `B` -> `C` **del** = `free` | `NULL` |
| ft_lstiter | Applies a function **f** to the content of each **node** of a **list** | `a` -> `b` **f** = uppercase | `A` -> `B` |
| ft_lstmap | Applies a function **f** to each **node**'s content and returns a new **list** of the results (cleans up with **del** on failure) | `a` -> `b` **f** = uppercase | new list `A` -> `B` |

# Instructions

The project is delivered with every *.c* files uncompiled, the *libft.h* file and the *Makefile*. The compilation will be the result of the command `make`, resulting in the creation of a *libft.a* file. 

It will create a lot of files as well named objects, having the .o extension. If you want to clean every files created during the compilation, you can run the command `make clean` and it will keep the **libft.a** file or `make fclean` and everything will be cleaned up, including the .a file.

# Resources

During the project, I used official websites that delivers man description of certain functions. Some functions were new to me, so I asked AI to give me examples and the precise behavior of unknown functions. It helped on the writting side, due to the fact that when you know what to expect from what you are coding, everything is easier and smoother. 
Although I knew a lot about fundamental notions around this project, some new knowledge came directly within reading man pages (such as the file descriptor).
Finally, I took a look back at my Piscine's project, because some elements weren't in my head since then, so I needed a refresh. *(Makefile, .h)*
For the chained list part, YouTube channel Neso academy helped me understand the basics about this notion.