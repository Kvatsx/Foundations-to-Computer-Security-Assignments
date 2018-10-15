// Kaustav Vats ( 2016048 )

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/aes.h>

// #define PORT 5555
#define BUFSIZE 1024

const unsigned char * Key = "BA67C85F805DB78A9E01812383348483";
AES_KEY EncKey;
AES_KEY DecKey;

int main(int argc, char const *argv[])
{
    int FileDescriptor_Socket;
    struct sockaddr_in Address;
    socklen_t AddressLength = sizeof(Address);
    char Buffer[BUFSIZE] = {0};
    int MssgRecvStatus;

    // printf("argc: %d\n", argc);
    if (argc != 3) {
        printf("Usage: ./client <ip> <port>\n");
        return 1;
    }

    AES_set_encrypt_key((const unsigned char *) Key, 128, &EncKey);
    AES_set_decrypt_key((const unsigned char *) Key, 128, &DecKey);

    int PORT = strtol(argv[2], NULL, 10);

    /* Creating a server File descriptor.
    IPv4
    SOCK_STREAM: TCP connection
    Protocol value: 0
    */
    if ((FileDescriptor_Socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket not created\n");
		exit(1);
    }

    Address.sin_family = AF_INET;
    Address.sin_port = htons(PORT);
    // Address.sin_addr.s_addr = inet_addr(argv[1]);

    /*
    Converts IPv4 & IPv6 from text to Binary address.
    returns 1 on success.
    domain: AF_INET: IPv4
    src: "127.0.0.1"
    dest: &Address.sin_addr
    Conerts character string src into a network address structure,
    then copies the network address structure to dest.
    */
    if ( inet_pton(AF_INET, argv[1], &Address.sin_addr) <= 0 ) {
        perror("Invalid Address!\n");
        exit(1);
    }

    memset(Address.sin_zero, '\0', sizeof Address.sin_zero);

    /*
    Connects the socket referred by the FileDescriptor_Socket 
    to the address specified by "Address". 
    If connection successful then returns 0 else -1.
    */
    if ( connect(FileDescriptor_Socket, (struct sockaddr *)&Address, sizeof(struct sockaddr_in)) < 0 ) {
        perror("Connection Fail\n");
        exit(1);
    }

    while(1) {
        char Buffer[BUFSIZE] = {0};
        fgets(Buffer, BUFSIZE, stdin);
        if (strncmp(Buffer, "exit", 4) == 0) {
            close(FileDescriptor_Socket);
            return NULL;
        }
        char BuffNew[BUFSIZ] = {0};
                // printf("Buffer New: \n");

        AES_encrypt((const unsigned char *) Buffer, BuffNew, (const AES_KEY *) &EncKey);
                // printf("Buffer New: \n");

        if (send(FileDescriptor_Socket, BuffNew, strlen(BuffNew), 0) == -1) {
            perror("send error\n");
        }
        // printf("Buffer New: %s\n", BuffNew);
        int MssgRecvStatus;
        if ((MssgRecvStatus = recv(FileDescriptor_Socket, BuffNew, BUFSIZE, 0)) <= 0) {
            if (MssgRecvStatus == 0) {
                printf("Server closed!\n");
            }
            else {
                perror("recv error!\n");
            }
            close(socket);
            return NULL;
        }
        printf("Buffer New: %s\n", BuffNew);
        AES_decrypt((const unsigned char *) BuffNew, Buffer, (const AES_KEY *) &DecKey); 
        printf("\n%s\n", Buffer);

    }

    close(FileDescriptor_Socket);
    return 0;
}
