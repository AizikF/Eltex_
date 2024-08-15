#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/udp.h>
#include <netinet/ip.h>

#define BUFFER_SIZE 65536

void process_packet(unsigned char *buff, int size)
{
    struct iphdr *iph = (struct iphdr *) buff;
    unsigned short iphdrlen = iph->ihl * 4;
    struct udphdr *udph = (struct udphdr *) (buff + iphdrlen);

    unsigned short source_port = ntohs(udph->source);
    unsigned short dest_port = ntohs(udph->dest);

    if (source_port == 667 || dest_port == 667)
    {
        printf("Received TCP Packet:\n");
        printf("From: %u.%u.%u.%u:%d\n",
                (iph->saddr) & 0xFF,
                (iph->saddr >> 8) & 0xFF,
                (iph->saddr >> 16) & 0xFF,
                (iph->saddr >> 24) & 0xFF,
                ntohs(udph->source));

        printf("To: %u.%u.%u.%u:%d\n",
                (iph->daddr) & 0xFF,
                (iph->daddr >> 8) & 0xFF,
                (iph->daddr >> 16) & 0xFF,
                (iph->daddr >> 24) & 0xFF,
                ntohs(udph->dest));

        printf("Data (Payload): ");

        int payload_size = size - (iphdrlen + sizeof(struct udphdr));
        unsigned char *data = buff + iphdrlen + sizeof(struct udphdr);

        for (int i = 0; i < payload_size; i++) {
            printf("%02X ", data[i]);
        }
        printf("\n\n");
    }

}

int main()
{
    int sockfd;
    unsigned char *buffer = (unsigned char *)malloc(BUFFER_SIZE);
    struct sockaddr saddr;
    int saddr_len = sizeof(saddr);

    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0)
    {
        perror("Socket Creation Error");
        return 1;
    }

    while (1)
    {
        int packet_size = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, &saddr, (socklen_t *)&saddr_len);
        if (packet_size < 0)
        {
            perror("Recvfrom Error");
            return 1;
        }

        process_packet(buffer, packet_size);
    }

    close(sockfd);
    free(buffer);
    return 0;
}