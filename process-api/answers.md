## 1
1) Child process have value a=100, which equal to parent process.
2) Child and parent processes have own copies of all values.

## 2
1) Child and parent have own fd values, but!!! they use the same descriptor (because there is only one file)
2) If both write concurrently without synchronization, their outputs can be interleaved

## 3
1) q3.c

## 4
1) q4.c
2) There are different variants of exec() for different method to pass args

## 5
1) q5.c
2) wait() returns PID of finishied process. If there is no child processes, it returns -1
3) It will return -1 as child doesnt have other child processes

## 6
1) q6.c
2) It would be usefull when we need to wait particular child process instead of waiting any child

## 7
1) q7.c
2) After the child closes `STDOUT_FILENO`, it will not be able to write to standard output.
The parent will still be able to write to standard output, because it has its own separate copy of the descriptor.

## 8
1) q8.c
