# Minishell

## About
Minishell is simple shell with similar behaviour as [bash](https://www.gnu.org/software/bash/).
Following builtins were self made: `echo`, `cd`, `pwd`, `export`, `unset`, `env` and `exit` while other calls are made via `execve` and path lookup.

### Functionalities
`'` and `"`, `;`, `|`, `>`, `>>`, `$?`, `$VARIABLES`, `ctrl+C`, `ctrl+D`, `ctrl+\`  
  
![Minishell example](https://github.com/backslash-zero/minishell/blob/master/Capture%20d%E2%80%99e%CC%81cran%202020-09-27%20a%CC%80%2016.07.47.png)  
  
## Basic Concepts
- Processes
- Fork, wait, exec functions
- Dup & FD handling
- Pipes
- Parsing
- Errno & strerror

## Allowed External Functions:
```
malloc, free, write, open, read, close, fork, wait, waitpid, wait3, wait4, signal, kill, exit, getcwd, chdir, stat, lstat, fstat, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, errno
```

## External self code libraries:
[Libft](https://github.com/backslash-zero/42/tree/master/Libft): Self-made basic functions of C default libraries.  
[Printf_fd](https://github.com/backslash-zero/printf_fd): Self-made library with similar behaviour as [printf](http://www.cplusplus.com/reference/cstdio/printf/) with custome file descriptor.


## Project Structure
````
├── Makefile
├── incs
│   ├── builtin.h
│   ├── env.h
│   ├── error.h
│   ├── ft_printf.h
│   ├── libft.h
│   ├── minishell.h
│   ├── parsing.h
│   └── pipe.h
└── src
    ├── builtins
    │   ├── builtins_nametab.c
    │   ├── cd.c
    │   ├── echo.c
    │   ├── env.c
    │   ├── exit.c
    │   ├── export.c
    │   ├── export_2.c
    │   ├── export_next.c
    │   ├── export_next_2.c
    │   ├── pwd.c
    │   └── unset.c
    ├── execs
    │   ├── path.c
    │   ├── path_2.c
    │   ├── reads.c
    │   ├── reads_2.c
    │   ├── reads_3.c
    │   ├── redirections.c
    │   ├── redirections2.c
    │   └── sort_redir.c
    ├── ft_printf_fd
    │   └── libftprintf.a
    ├── libft
    │   └── libft.a
    ├── minishell.c
    ├── parsing
    │   ├── append.c
    │   ├── cleanup
    │   │   ├── cleanup.c
    │   │   ├── cleanup_bs_quote.c
    │   │   ├── cleanup_gret.c
    │   │   └── cleanup_var.c
    │   ├── parsing.c
    │   └── utils
    │       ├── is_funcs
    │       │   ├── is_funcs_1.c
    │       │   ├── is_funcs_2.c
    │       │   └── is_funcs_3.c
    │       ├── parsing_utils_1.c
    │       └── tools
    │           ├── backslash_tools_1.c
    │           ├── backslash_tools_2.c
    │           ├── gret_tools.c
    │           ├── quote_tools.c
    │           ├── redir_pipe_tools.c
    │           ├── semicolon_tools.c
    │           ├── var_tools_1.c
    │           └── var_tools_2.c
    ├── pipe
    │   ├── pipe.c
    │   ├── pipe2.c
    │   ├── pipe3.c
    │   └── pipe4.c
    └── utils
        ├── arg.c
        ├── error.c
        ├── free.c
        ├── ft_strncpy.c
        ├── prints.c
        └── semicolon.c
````

## Ressources 
[Création d'un minisystème](https://chrtophe.developpez.com/tutoriels/minisysteme/#L11)   
[Exit Codes](https://tldp.org/LDP/abs/html/exitcodes.html)  
[Write a shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)  
[Single quote vs Double quotes](https://stackoverflow.com/questions/6697753/difference-between-single-and-double-quotes-in-bash)  