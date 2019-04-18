# Linux下如何创建进程
来源
https://time.geekbang.org/column/article/90855

在 Linux 下面，二进制的程序也要有严格的格式，这个格式们称为ELF（Executeable and Linkable Format，可执行与可链接格式）。这个格式可以根据编译的结果不同，分为不同的格式。

## 编译方法
* 编译
即生成为可重定位文件（Relocatable File）；后缀名为.o
```
gcc -c -fPIC process.c
gcc -c -fPIC createprocess.c
```

* 归档
要想让 create_process 这个函数作为库文件被重用，不能以.o 的形式存在，而是要形成库文件，最简单的类型是静态链接库.a 文件（Archives），仅仅将一系列对象文件（.o）归档为一个文件，使用命令 ar 创建。
```
ar cr libstaticprocess.a process.o
```

* 静态链接
```
gcc -o staticcreateprocess createprocess.o -L. -lstaticprocess
```
在这个命令里，-L 表示在当前目录下找.a 文件，-lstaticprocess 会自动补全文件名，比如加前缀 lib，后缀.a，变成 libstaticprocess.a，
找到这个.a 文件后，将里面的 process.o 取出来，和 createprocess.o 做一个链接，形成二进制执行文件 staticcreateprocess。

* 动态链接
静态链接库一旦链接进去，代码和变量的 section 都合并了，因而程序运行的时候，就不依赖于这个库是否存在。但是这样有一个缺点，就是相同的代码段，如果被多个程序使用的话，在内存里面就有多份，而且一旦静态链接库更新了，如果二进制执行文件不重新编译，也不随着更新。

生成动态链接库
```
gcc -shared -fPIC -o libdynamicprocess.so process.o
```

生成用动态链接库的二进制执行文件
```
gcc -o dynamiccreateprocess createprocess.o -L. -ldynamicprocess
```

* 执行动态链接库的程序
当运行这个程序的时候，首先寻找动态链接库，然后加载它。默认情况下，系统在 /lib 和 /usr/lib 文件夹下寻找动态链接库。如果找不到就会报错，我们可以设定 LD_LIBRARY_PATH 环境变量，程序运行时会在此环境变量指定的文件夹下寻找动态链接库。
```
# export LD_LIBRARY_PATH=.
# ./dynamiccreateprocess
# total 40
-rw-r--r--. 1 root root 1572 Oct 24 18:38 CentOS-Base.repo

```

对于 ELF，有几个工具能帮你看这些文件的格式。readelf 工具用于分析 ELF 的信息，
objdump 工具用来显示二进制文件的信息，
hexdump 工具用来查看文件的十六进制编码，
nm 工具用来显示关于指定文件中符号的信息。
你可以尝试用这几个工具，来解析这一节生成的.o, .so 和可执行文件。
