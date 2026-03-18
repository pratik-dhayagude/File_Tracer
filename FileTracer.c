#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

void getSectionType(char * details,char*prms,char*section)
{
    if(strcmp(details,"[heap]")==0)
    {
        strcpy(section,"HEAP");
    }
    else if(strcmp(details,"[stack]")==0)
    {
        strcpy(section,"STACK");
    }
    else if(strcmp(details,"[vdso]")==0)
    {
        strcpy(section,"VDSO");
    }
    else if(strcmp(details,"[vvar]")==0)
    {
        strcpy(section,"VVAR");
    }
    else if(strcmp(details,"[vsyscall]")==0)
    {
        strcpy(section,"VSYSCALL");
    }
     else if(prms[2]=='x')
    {
        strcpy(section,"TEXT");
    }
    else if(prms[1]=='w')
    {
        strcpy(section,"DATA");
    }
    else 
    {
        strcpy(section,"OTHER");
    }

}

////////////////////////////////////////////////////////////////
//
//
//  : Function to show the memory layout of the process
//
//
////////////////////////////////////////////////////////////////

void ShowMemoryLayout(int pid)
{
    FILE * fp = NULL;
    char line[80];
    char FileName[100];

    sprintf(FileName,"/proc/%d/maps",pid);

    printf("Accessing the file information from %s\n",FileName);
    
    fp = fopen(FileName,"r");

    if(fp ==NULL)
    {
        printf("Unable to access system file");
        return;
    }

    printf("-------------------------------------------------\n");
    printf("-------------Memory Information-----------------\n");
    printf("-------------------------------------------------\n");
    printf("---------------Headder--------------------------\n");

     char address[100],prms[10],offset[20],dev[20],details[300]="";

        unsigned long inode;
        unsigned long start ,end;
        unsigned long sizekb;

        char section[50];

        int Ret =0;
          


    while(fgets(line,sizeof(line),fp)!=NULL)
    {
        Ret = sscanf(line,"%s %s %s %s %lu %[^\n]",address,prms,offset,dev,&inode,details);
       
        if(Ret >= 5)
        {
            sscanf(address,"%lx-%lx",&start,&end);
            sizekb = (end - start)/1024;

            getSectionType(details,prms,section);

            if(strlen(details)==0)
            {
                strcpy(details,"Anonymous");
            }
            printf("%lx %lx %lu %s %s %s\n",start,end,sizekb,prms,section,details);  
        }
    }
    printf("-------------------------------------------------\n");
    fclose(fp);

    
}
////////////////////////////////////////////////////////////////
//
//
//  : Function to fetch the process information
//
//
////////////////////////////////////////////////////////////////
void ShowProcessInformation(int pid)
{
    FILE * fp = NULL;
    char line[80];
    char FileName[100];

    sprintf(FileName,"/proc/%d/status",pid);

    printf("Accessing the file information from %s\n",FileName);

    fp = fopen(FileName,"r");

    if(fp ==NULL)
    {
        printf("Unable to access system file");
        return;
    }

    printf("-------------------------------------------------\n");
    printf("-------------Process Information-----------------\n");
    printf("-------------------------------------------------\n");

    while(fgets(line,sizeof(line),fp)!=NULL)
    {
        if(strncmp(line,"Name:",5)==0||
              strncmp(line,"Pid:",4)==0||  
                 strncmp(line,"State:",6)==0||
                     strncmp(line,"Threads:",8)==0||
                            strncmp(line,"PPid:",5)==0)
                     {
                        printf("%s\n",line);

                     }
             
    }

}
////////////////////////////////////////////////////////////////
//
//
//  : Entry point function
//
//
////////////////////////////////////////////////////////////////
int main()
{
    int PID = 0;
    printf("-------------------------------------------------\n");
    printf("----------Marvellous Process Inpesector----------\n");
    printf("-------------------------------------------------\n");

    printf("Enter the pid of a process that you want to inspect\n");
    scanf("%d",&PID);

    if(PID<=0)
    {
        printf("Invalid PID\n");
        return -1;
    }

    ShowProcessInformation(PID);
    ShowMemoryLayout(PID);
    return 0;
}

/*
    text/code   Binary instructions
    Data        global variables
    Stack       local variables
    vdso        Virtual dynamic shared object
    VVAR        Virtual variables
    VSYSCALL    Virtual System call page
    other       other memory regions
*/