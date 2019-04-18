#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


extern int create_process (char* program, char** arg_list);


int create_process (char* program, char** arg_list)
{
    pid_t child_pid;		//pid_t实际就是int类型
    child_pid = fork ();	//调用fork函数之前,只有一个进程在执行这段代码，但在这条语句之后，就变成两个进程在执行了，这两个进程的几乎完全相同
    if (child_pid != 0)		//在父进程中，fork返回新创建子进程的进程ID,也就是说这段代码将被父进程执行，子进程不执行
        return child_pid;
    else {					//为0表示，此时是子进程
        execvp (program, arg_list);		//execvp()会从PATH 环境变量所指的目录中查找符合参数file 的文件名，找到后便执行该文件，然后将第二个参数argv传给该欲执行的文件
        abort ();
    }
}