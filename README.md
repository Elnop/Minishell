# Minishell

## Run
```
git clone --recurse-submodules git@github.com:Elnop/Minishell.git
cd Minishell
make
./minishell
```

## External functions
- [execve](http://manpagesfr.free.fr/man/man2/execve.2.html)
- [fork](http://manpagesfr.free.fr/man/man2/fork.2.html)
- [pipe](http://manpagesfr.free.fr/man/man2/pipe.2.html)
- [dup](http://manpagesfr.free.fr/man/man2/dup.2.html)

![](assets/image1.png)
![](assets/image2.png)

## Posix Rules to Know

## Valgrind flags

```
valgrind --suppressions=./valg.supp --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes  ./minishell
```
