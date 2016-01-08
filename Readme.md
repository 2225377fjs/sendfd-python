# sendfd-python介绍

------
因为一些需求，需要在python进程之间通过unixdomain socket来传递文件描述符，因为python的socket并没有sendmsg接口，所以只好用到cython来包装了一个扩展库，代码和api也都很简单，我一般都是通过将其编译成.so文件之后直接在程序中引用，不会安装库，具体就看每个人的使用习惯吧

