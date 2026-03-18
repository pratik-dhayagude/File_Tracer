#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("Inside my exe process with pid : %d\n",getpid());
    return 0;
}