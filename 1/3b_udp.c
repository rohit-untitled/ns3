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
    char send_data[1024], recv_data[1024];
    struct sockaddr_in server_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    printf("Write Sentence to send\n");
    gets(send_data);
    send(sock, send_data, strlen(send_data), 0);

    while ((bytes_recv = recv(sock, recv_data, 1024, 0)) > 0)
    {
        recv_data[bytes_recv] = '\0';
        printf("Capital sentence recieved is %s\n", recv_data);
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

void capitalize(char *str)
{
    int length = strlen(str);

    for (int i = 0; i < length; i++)
    {
        str[i] = toupper(str[i]);
    }
}

int main()
{
    int sock, bytes_recv;
    char send_data[1024], recv_data[1024];
    struct sockaddr_in server_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    listen(sock, 5);

    printf("UDP server is waiting for client on port 3000\n");

    while (1)
    {
        int sin_size = sizeof(struct sockaddr);
        int con = accept(sock, (struct sockaddr *)&server_addr, &sin_size);
        printf("Client connected\n");

        bytes_recv = recv(con, recv_data, 1024, 0);
        recv_data[bytes_recv] = '\0';
        printf("Received data is '%s'\n", recv_data);

        capitalize(recv_data);

        send(con, recv_data, 1024, 0);

        close(con);
    }

    close(sock);
    return 0;
}
