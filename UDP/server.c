#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock_fd;
    struct sockaddr_in server, client;
    char buffer[1024];
    socklen_t len = sizeof(client);

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sock_fd, (struct sockaddr *)&server, sizeof(server));

    printf("UDP Server waiting for client...\n");

    recvfrom(sock_fd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&client, &len);

    printf("Client: %s\n", buffer);

    strcpy(buffer, "Hello from Server");

    sendto(sock_fd, buffer, strlen(buffer) + 1, 0,
           (struct sockaddr *)&client, len);

    close(sock_fd);

    return 0;
}
