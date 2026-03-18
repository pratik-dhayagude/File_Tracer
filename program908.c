#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main()
{
    printf("Home directory:%s\n",getenv("HOME"));  
    printf("Shell used:%s\n",getenv("SHELL"));
    
    return 0;
}