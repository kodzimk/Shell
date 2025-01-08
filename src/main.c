#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>


int main()
{
    while (1)
    {
        char arr[100];

        printf("$ ");
        fgets(arr,100,stdin);
        int split = 0;
        
        char* command = strtok(arr," "); 
        fwrite(command, sizeof(command[0]), sizeof(command), stdout);
        char* argument_list[3];
        argument_list[0] = command;

        int index = 0;
        for (int i = 0; i < 100; i++)
        {
            if (arr[i] == ' ')
            {
                split = 1;
                continue;
            }
            else if(arr[i] == ' ' && split == 1)
                break;

            if (split == 1 && arr[i] != ' ')
            {
                argument_list[2][index] = arr[i];
                index++;
            }
        }
        argument_list[2] = NULL;

        pid_t p = fork();
        if (p == 0) {
            execvp(command, argument_list);
        }
        else
        {
            printf("Hello world!, process_id(pid) = %d \n", getpid());
         
        }
    }
    return 0;
}