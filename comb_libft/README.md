# Combined libft && gnl && printft

**Overview**

This project is a custom reimplementation of the libft library, get_next_line function and printf function, combined into a single static archive. 
The goal is to provide a reusable library that includes essential C utility functions along with formatted output capabilities, all in one place.
The static archive (libftprintf.a) provides a powerful toolset that can be easily integrated into any C project. By using this library, developers can avoid rewriting common functions and focus on more advanced logic in their applications.

**How to Use**

Clone the Repository

To get started, first clone the repository to your local machine

```
git clone https://github.com/daniek1010/comb_libft.git comb_libft && cd comb_libft && make 
```
Copy the Static Library (libftprintf.a) and Header Files into your project directory
```
cp libftprintf.a /path/to/your/project/
cp ft_printf.h /path/to/your/project/includes/
```

Include the Header Files in Your source Code

````
#include "ft_printf.h"
````
Compile your code with the static libraby(libftprintf.a) and run :)

````
gcc -o my_program my_program.c libftprintf.a
````
