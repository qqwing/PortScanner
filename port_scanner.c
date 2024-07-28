#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

void scan_port(const char *ip, int port) {
    int sockfd;
    struct sockaddr_in target;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    inet_pton(AF_INET, ip, &target.sin_addr);

    int result = connect(sockfd, (struct sockaddr *)&target, sizeof(target));
    if (result == 0) {
        printf("Port %d is open\n", port);
    }

    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <IP> <Port Range>\n", argv[0]);
        printf("Example: %s 192.168.1.1 1-1000\n", argv[0]);
        return 1;
    }

    char *ip = argv[1];
    char *port_range = argv[2];
    int start_port, end_port;
    sscanf(port_range, "%d-%d", &start_port, &end_port);

    for (int port = start_port; port <= end_port; port++) {
        scan_port(ip, port);
    }

    return 0;
}

