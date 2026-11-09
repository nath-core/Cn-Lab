#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include <sys/socket.h>

int main(){
    int sockfd;
    char buffer[65536];
    struct sockaddr addr;
    socklen_t addr_len = sizeof(addr);
    struct iphdr *ip;
    sockfd = socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
    printf("Packet capturing started");
    while(1){
        addr_len=sizeof(addr);
        int n = recvfrom(sockfd,buffer,sizeof(buffer),0,&addr,&addr_len);
        ip = (struct iphdr *)buffer;
        printf("\n Packet Received \n");
        printf("Source_IP : %s \n",inet_ntoa(*(struct in_addr *)&ip->saddr));
        printf("Destination_IP: %s \n",inet_ntoa(*(struct in_addr *)&ip->daddr));
        printf("Protocol : %d \n",ip->protocol);
        printf("Packet Size : %d bytes\n", n);
    
    }
}
