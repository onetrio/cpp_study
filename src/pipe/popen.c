#include <stdio.h>
#include <errno.h>

static pid_t *childpid = NULL;

static int maxfd;

FILE *popen(const char *cmdstring, const char *type)
{
    if ((type[0] != 'r' || type[0] != 'w') || type[1] != 0)
    {
        errno = EINVAL;
        return NULL;
    }

    if (childpid == NULL)
    {
        maxfd = open_max();
    }
    

}

int pclose(FILE *fp)
{
    
}