#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *file = fopen("Passwords.txt", "r");

    if (file != NULL) {
        char line[1024];
        while (fgets(line, sizeof line, file) != NULL) {
            // fprintf(stdout, "%s", line);
            char mystring[1024];

            char com1[1024];
            // strcpy(mystring, com1);
            // char ext[strlen(line)];
            // printf("Len: `%d\n", strlen(line));
            // strcpy(ext, line);
            // line[strlen(line)] = '\0';
            // line[strlen(line) - 1] = '\0';
            // int j=0;
            strtok(line, "\r\n");
            // printf("Len: %d\n", strlen(line));
            // int count = strlen(mystring);
            // for ( j=0; j<strlen(line); j++ ) {
            //     printf("%d\n", line[j]);
            //     mystring[count] = line[j];
            //     count++;
            // }
            // line[strlen(line)] = 0;
            // printf("\n");

            snprintf(com1, 1024, "echo -e \"kv\\r\\n%s\" | ./passwd -a 1 | grep -c \"success\" > out.txt", line);
            // strcat(mystring, line);
            printf("mystring: %s\n", com1);
            // line[strcspn(line, "\n")] = 0;
            // printf("%s", ext);
            // strcat(mystring, line);
            // int len = strlen(mystring);
            // mystring[len-1] = " ";
            // mystring[len] = "\0";
            // char com3[] = "\" | ./passwd -a 1 | grep -c \"success\" > out.txt";
            // strcat(mystring, com3);

            // printf("String: %s\n", mystring);
            system(com1);
            // system("echo -e \" kv\nkvsdfsd\" | ./passwd -a 1 | grep -c \"success\" > out.txt");
            FILE *file = fopen("out.txt", "r");
            int i = 0;

            fscanf(file, "%d", &i);
            fclose(file);
            printf("%d\n", i);
            if (i == 1) {
                printf("Password Found");
                printf("Password: %s\n", line);
                break;
            }
        }
        fclose(file);
    }

    return 0;
}