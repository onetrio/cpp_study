#include "pipe_sample.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

// fd[0] 为读打开，fd[1] 为写打开
// fd[1] 的输出为 fd[0] 的输入
static int fd[2];
static char buffer[1024] = { 0 };

void signal_handler(int signo)
{
    printf("catch a signo = %d\n", signo);
}

void pipe_sample()
{
    // 创建管道, 若成功返回 0, 若失败返回 -1
    if (pipe(fd) == -1)
    {
        printf("pipe failed.\n");
        return;
    }

    do
    {
        // fstat函数对管道的每一端都返回一个FIFO类型的文件描述符，可以用S_ISFIFO宏来测试管道
        for (size_t i = 0; i < sizeof(fd); i++)
        {
            struct stat buf;
            if (fstat(fd[i], &buf) == -1)
            {
                printf("fstat failed.\n");
                break;
            }

            if (S_ISFIFO(buf.st_mode))
            {
                printf("fd[%ld] type is FIFO.\n", i);
            }
        }

        int pid = fork();
        if (pid < 0)
        {
            perror("fork failed.");
            break;
        }
        else if (pid == 0)
        {
            signal(SIGPIPE, signal_handler);
            // 子进程，关闭管道的读端
            close(fd[0]);

            // 如果写一个读端已关闭的管道，会产生SIGPIPE信号。如果忽略该信号或者捕捉该信号并从其处理程序返回，
            // 则write 返 回-1, errno设置为 EPIPE
            int n = write(fd[1], "Hello world\n", 12);
            if (n == -1)
            {
                printf("write pipe failed. errno = %d, msg = %s\n", errno, strerror(errno));
            }
        }
        else if (pid > 0)
        {
            // 父进程，关闭管道的写端
            close(fd[1]);
            // close(fd[0]); // test EPIPE
            while (1)
            {
                // 当读（read）一个写端已关闭的管道时，在所有数据被读取后，read 返回 ，表示文件结束。
                // 如果管道的写端还有进程，就不会产生文件的结束。
                int n = read(fd[0], buffer, 1024);
                printf("read data len : %d\n", n);
                if (n > 0)
                {
                    printf("parent process receive data : %s", buffer);
                }
                else
                {
                    break;
                }
            }
        }
    } while (0);
}