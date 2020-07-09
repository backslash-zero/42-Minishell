# Minishell

## Algorithm mindmap
[Mind map here](https://www.figma.com/file/G5oAf6m91dH57ye0YDG7cs/Minishell-Mindmap?node-id=0%3A1)

## About
Minishell is simple shell.
`process` :  a program in execution.
`` : 

## External Functions:
```
malloc, free, write, open, read, close, fork, wait, waitpid, wait3, wait4, signal, kill, exit, getcwd, chdir, stat, lstat, fstat, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, errno
```
### Fork
`fork` : creates a new *process* by duplicating the calling processing.
 
### Wait
All of these system calls are used to wait for state changes in a child of the calling process, and obtain information about the child whose state has changed.
`wait` supends execution of 

### Max arg
As seen [here](https://serverfault.com/questions/163371/linux-command-line-character-limit), the maximum ammount of characters in a command in shell should be `131072`

## Error Management
We have 2 functions that return -1: `ft_sterror` & `ft_error`

### System errors:
We can use `errno` and `strerror` when we call functions that sets it automatically.

We then call our custom `ft_strerror`, which we can also use to free any meemory allocated variable or our arg tab.
We can also add _param_ and _param2_ to give more information about the error, like the cmd name, for example.

### Custom errors:
`ft_error` works the same way as except we need to set a custom _msg_ 

## Ressources 
[Création d'un minisystème](https://chrtophe.developpez.com/tutoriels/minisysteme/#L11)
[Exit Codes](https://tldp.org/LDP/abs/html/exitcodes.html)
[Write a shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
[Single quote vs Double quotes](https://stackoverflow.com/questions/6697753/difference-between-single-and-double-quotes-in-bash)