#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc , char * argv[])
{
    int Ans = 0;

    if(argc != 3)
    {
        printf("Invalid arguments\n");
        return -1;
    }
    Ans = atoi(argv[1])+atoi(argv[2]);

    printf("Addition is :%d\n",Ans);

    return 0;
}