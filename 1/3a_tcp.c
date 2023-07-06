#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
int main()
{
    int sock, bytes_recv;
    struct sockaddr_in server_addr;
    char recv_data[1024], send_data[1024];
    struct hostent *host;
    host = gethostbyname("127.0.0.1");
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6119);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }
    printf("send Filename to send\n");
    gets(send_data);

    if (strcmp(send_data, "q") != 0)
        send(sock, send_data, strlen(send_data), 0);

    while ((bytes_recv = recv(sock, recv_data, 1024, 0)) > 0)
    {
        recv_data[bytes_recv] = '\0';
        printf("%s\n", recv_data);
    }
    close(sock);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
int main()
{
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    FILE *fptr;
    int sock, connected, bytes_recv;
    char ch, send_data[1024], recv_data[1024];
    int sin_size, flag = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6119);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("unable to bind");
        exit(1);
    }

    if (listen(sock, 5) == -1)
    {
        perror("lsten");
        exit(1);
    }

    printf("tcp server is waiting for client on port XXXX\n");
    sin_size = sizeof(struct sockaddr_in);
    connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);

    while (1)
    {

        bytes_recv = recv(connected, recv_data, 1024, 0);
        recv_data[bytes_recv] = '\0';

        printf("reciecved data is %s\n\n\n", recv_data);

        fptr = fopen(recv_data, "r");
        if (fptr == NULL)
        {
            strcpy(send_data, "FILE");
            send(connected, send_data, strlen(send_data), 0);
        }
        ch = fgetc(fptr);

        while (ch != EOF)
        {
            send_data[flag] = ch;
            flag++;
            ch = fgetc(fptr);
        }
        send(connected, send_data, strlen(send_data), 0);
        close(connected);
        break;
    }
}