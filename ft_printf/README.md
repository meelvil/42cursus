*This project has been created as part of the 42 curriculum by mbou-ani.*

---
# Description
---

During the **ft_printf** project, we needed to create a library that would contain functions, the main one being ***ft_printf()***.

The original *printf* accepts a string as its first argument. It can be a single classic line, or can contain an indicator starting with `%`, followed by a single letter that links to a certain type of content. Every `%` inside the string is replaced in the output by the matching content, if any is provided.

**Example :**

|Entry|Output|
|---|---|
|`ft_printf("Hello World")` |```Hello World```|
|`ft_printf("Hello %s", "World")` | ```Hello World```|
|`ft_printf("Hello %s")` |```Hello  ���0�``` (undefined behavior : no argument was provided)|

**Handled conversions :**

| Conversion | Type | Description |
| :---: | --- | --- |
| `%c` | `int` | A single character |
| `%s` | `char *` | A string |
| `%p` | `void *` | A pointer, in lowercase hexadecimal prefixed by `0x` (`(nil)` for a NULL pointer) |
| `%d` / `%i` | `int` | A signed decimal number |
| `%u` | `unsigned int` | An unsigned decimal number |
| `%x` | `unsigned int` | A lowercase hexadecimal number |
| `%X` | `unsigned int` | An uppercase hexadecimal number |
| `%%` | | A literal `%` |

> Here are the functions inside the *LIBFTPRINTF* library :

| Function name | Description | Input | Output |
| :---: | --- | --- | :---: |
| **ft_printf** | Writes in stdout and returns the amount of characters written | `ft_printf("Hello World")` | `Hello World` / `11` |
| **ft_format** | Spots the **character** following the `%` then redirects to the goal function | `%c` / `%s` ...| Redirecting to ft_putchar() / ft_putstr() ... |
| **ft_putchar** | Writes a **character** and returns the amount of characters written | `ft_putchar('c')` | `c` / `1` |
| **ft_putstr** | Writes a **string** and returns the amount of characters written | `ft_putstr("Melvil")` | `Melvil` / `6` |
| **ft_printadress** | Writes the **address** of a pointer, as `0x` followed by a **long hexadecimal**, and returns the amount of characters written | `ft_printadress(p)` | `0x7ffd...` / `characters written` |
| **ft_putnbr** | Writes a **decimal number** and returns the amount of characters written | `ft_putnbr(14)` | `14` / `2` |
| **ft_putunsignednbr** | Writes an unsigned **decimal number** and returns the amount of characters written | `ft_putunsignednbr(-1)` | `4294967295` / `10` |
| **ft_lowerhex** | Converts an unsigned int into a **lowercase hexadecimal** | `ft_lowerhex(348)` | `15c` / `3` |
| **ft_upperhex** | Converts an unsigned int into an **uppercase hexadecimal** | `ft_upperhex(348)` | `15C` / `3` |
| **ft_longhex** | Converts an unsigned long into a **lowercase hexadecimal** (used for pointers) | `ft_longhex(-1)` | `ffffffffffffffff` / `16` |

All of these functions return `-1` if a call to `write` fails, and this error is propagated up to `ft_printf`.

---

**Why did I choose this coding method rather than something else ?**

I chose to give **one function per conversion**, with `ft_format` acting as a simple dispatcher. This keeps every function short (in line with the Norm), easy to test on its own, and makes adding a new conversion trivial : write the function, declare it in the header, add one line in `ft_format`.

The number conversions (`ft_putnbr`, `ft_lowerhex`...) are **recursive** : they print the leading digits first, then the last one. It avoids having to allocate a buffer or reverse a string, so the library needs no `malloc` at all (it means no leak !).

Every function **returns the amount of characters written** (or `-1` on error), so `ft_printf` only has to add up the returned values to give the same return value as the original *printf*.

# Instructions
---

The project is delivered with every *.c* file uncompiled, the *ft_printf.h* file and the *Makefile*. The compilation is the result of the command `make`, creating a *libftprintf.a* file.

It also creates a lot of intermediate files named objects and dependencies, having respectively the `.o` and `.d` extensions. If you want to clean every file created during the compilation, you can run `make clean`, which keeps the **libftprintf.a** file, or `make fclean`, which cleans everything up, including the `.a` file. `make re` rebuilds everything from scratch.

To use the library in your own program, include the header and link the archive :

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello %s, you are number %d\n", "World", 42);
	return (0);
}
```

```bash
make
cc -Wall -Wextra -Werror main.c libftprintf.a -o test
./test
```

# Resources
---

- `man 3 printf` : reference for the behavior of the original function.
- `man 3 stdarg` : how `va_list`, `va_start`, `va_arg` and `va_end` work.
- `man 2 write` : the system call used for every output.
- **AI usage :** AI was used to help me understand much better every man pages. I also used it in order to take notes from what I did at the end of every coding sessions, so I knew what would need to be fixed everytime, and from where to start. The code itself was written by me.
