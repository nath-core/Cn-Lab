
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <net/ethernet.h>
#include <sys/socket.h>
#include <linux/if_packet.h>

int main(){
    int socket_fd;
    char packet_buffer[65536];
    struct sockaddr_ll source_address;
    socklen_t address_length = sizeof(source_address);
    struct iphdr *ip_header;

    socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    printf("Packet capturing started...\n");

    while (1){
        int packet_size = recvfrom(socket_fd, packet_buffer, sizeof(packet_buffer), 0,
                                   (struct sockaddr *)&source_address, &address_length);
                                   
        if (packet_size < (int)(sizeof(struct ethhdr) + sizeof(struct iphdr)))
            continue;

        struct ethhdr *ethernet_header = (struct ethhdr *)packet_buffer;
        if (ntohs(ethernet_header->h_proto) != ETH_P_IP)
            continue;

        ip_header = (struct iphdr *)(packet_buffer + sizeof(struct ethhdr));

        printf("\nPacket Received\n");
        printf("Source IP      : %s\n", inet_ntoa(*(struct in_addr *)&ip_header->saddr));
        printf("Destination IP : %s\n", inet_ntoa(*(struct in_addr *)&ip_header->daddr));
        printf("Protocol       : %d\n", ip_header->protocol);
        printf("Packet Size    : %d bytes\n", packet_size);
    }

    close(socket_fd);
    return 0;
}

