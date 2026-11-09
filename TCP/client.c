#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock_fd;
    struct sockaddr_in server;
    char buffer[1024] = "Hello from Client";

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_fd, (struct sockaddr *)&server, sizeof(server));

    send(sock_fd, buffer, strlen(buffer) + 1, 0);

    recv(sock_fd, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    close(sock_fd);

    return 0;
}
