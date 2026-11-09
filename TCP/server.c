#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    listen(server_fd, 5);

    printf("Server waiting for client...\n");

    socklen_t len = sizeof(client);
    client_fd = accept(server_fd, (struct sockaddr *)&client, &len);

    recv(client_fd, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    strcpy(buffer, "Hello from Server");
    send(client_fd, buffer, strlen(buffer) + 1, 0);

    close(client_fd);
    close(server_fd);

    return 0;
}
