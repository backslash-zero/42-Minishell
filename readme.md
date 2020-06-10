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

## Ressources 
[Création d'un minisystème](https://chrtophe.developpez.com/tutoriels/minisysteme/#L11)
[Write a shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)