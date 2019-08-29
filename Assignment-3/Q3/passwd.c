// Kaustav Vats (2016048)
// Ref:- http://www.cplusplus.com/articles/E6vU7k9E/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define BUFSIZE 1024

struct User
{
    char username[BUFSIZE];
    char password[BUFSIZE];
};

int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);

    return ch;
}

void getPass(char *prompt, int show_asterisk, char password[])
{
    int BACKSPACE = 127;
    int RETURN = 10;

    int count = 0;
    int ch = 0;

    printf("%s: ", prompt);

    while ((ch = getch()) != RETURN)
    {

        if (ch == BACKSPACE)
        {
            if (count != 0) {
                if (show_asterisk != 0) {
                    printf("\b \b");
                }
                count--;
            }
        }
        else
        {
            char temp = ch;
            password[count] = temp;
            count++;
            if (show_asterisk != 0) {
                printf("*");
            }
        }
    }
    password[count] = '\0';
    printf("\n");
}

int main(int argc, char const *argv[])
{
    if ( argc != 3 ) {
        printf("Usage: ./passwd <Option> <asterisk>\n-r: To Register a User\n-a: To Authenticate a User\nAsterisk: Non Zero to show asterisk.\n");
        return -1;
    }

    if (strcmp(argv[1], "-r") != 0 && strcmp(argv[1], "-a") != 0) {
        printf("Usage: ./passwd <Option> <asterisk>\n-r: To Register a User\n-a: To Authenticate a User\nAsterisk: Non Zero to show asterisk.\n");
        return -1;
    }

    if (strcmp(argv[1], "-a") == 0) {
        char input_username[BUFSIZE];
        char input_password[BUFSIZE];

        printf("Enter Username: ");
        gets(input_username);

        getPass("Enter Password", atoi(argv[2]), input_password);

        FILE *file;
        struct User user;

        file = fopen("credentials.dat", "r");
        if (file == NULL) {
            fprintf(stderr, "\nError opening file\n");
            exit(1);
        }
        int flag = 0;
        while (fread(&user, sizeof(struct User), 1, file)) {
            if ((strcmp(user.username, input_username) == 0) && (strcmp(user.password, input_password) == 0)) {
                flag = 1;
                printf("[success] Authenticated\n");
                break;
            }
        }
        if (flag == 0) {
            printf("[error] User not registered\n");
        }

        fclose(file);
    }   
    else {
        struct User user;

        printf("Enter Username: ");
        gets(user.username);
   
        char input_password[BUFSIZE];
        getPass("Enter Password", atoi(argv[2]), input_password);
        strcpy(user.password, input_password);
        // printf("%s\n", user.password);

        FILE *file;
        file = fopen("credentials.dat", "a");
        if (file == NULL) {
            fprintf(stderr, "\nError opening file\n");
            exit(1);
        }
        fwrite(&user, sizeof(struct User), 1, file);
        if (fwrite != 0) {
            printf("[success] User registered successfully!\n");
        }
        else {
            printf("[error] While registering user!\n");
        }
        fclose(file);
    }
    return 0;
}
