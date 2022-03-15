#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>

#define DEF_PAGER "/usr/bin/more"
#define	MAXLINE	4096

int main(int argc, char *argv[])
{
    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line[MAXLINE];
    FILE *fp;

    if (argc != 2)
    {
        printf("usage: pager <pathname>");
        exit(-1);
    }

    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        perror("fopen failed.");
        exit(-2);
    }

    if (pipe(fd) < 0)
    {
        perror("pipe failed.");
        exit(-3);
    }

    if ((pid = fork()) < 0)
    {
        perror("fork failed.");
        exit(-3);
    }
    else if (pid > 0)
    {
        // 父进程
        close(fd[0]); // close read

        while (fgets(line, MAXLINE, fp) != NULL)
        {
            int len = strlen(line);
            if (write(fd[1], line, len) != len)
            {
                perror("write pipe failed.");
                exit(-3);
            }
        }

        if (ferror(fp))
        {
            perror("read from file failed.");
            exit(-4);
        }

        close(fd[1]);

        if (waitpid(pid, NULL, 0) < 0)
        {
            perror("waitpid failed.");
            exit(-1);
        }

        printf("child process exited.\n");

        exit(0);
    }
    else
    {
        // 子进程
        close(fd[1]);

        if (fd[0] != STDIN_FILENO)
        {
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
            {
                perror("dup2 error to stdin");
            }
            close(fd[0]);
        }

        pager = DEF_PAGER;
        if ((argv0 = strrchr(pager, '/')) != NULL)
        {
            argv0++;
        }
        else
        {
            argv0 = pager;
        }

        printf("pager = %s, argv0 = %s\n", pager, argv0);

        // execl出错返回 -1，成功不返回。
        // ! 进程调用一种 exec 函数时，该进程完全由新程序替换，而新程序则从其 main 函数开始执行。
        // 因为调用 exec 并不创建新进程，所以前后的进程 ID （当然还有父进程号、进程组号、当前工作目录……）并未改变。
        // exec 只是用另一个新程序替换了当前进程的正文、数据、堆和栈段（进程替换）
        if (execl(pager, argv0, (char *)0) < 0)
        {
            perror("execl error");
            exit(-1);
        }
    }
    exit(0);
}