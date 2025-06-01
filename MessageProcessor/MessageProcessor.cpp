#include "MessageProcessor.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

MessageProcessor::MessageProcessor(const int port) {
    socketFd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFd_ < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr{};
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(socketFd_, reinterpret_cast<const sockaddr *>(&serverAddr), sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(socketFd_);
        exit(EXIT_FAILURE);
    }
}

MessageProcessor::~MessageProcessor() {
    close(socketFd_);
}

void MessageProcessor::run() {
    while (true) {
        sockaddr_in serverAddr{};
        socklen_t len = sizeof(serverAddr);
        const ssize_t n = recvfrom(socketFd_, buffer, BUFFER_SIZE, 0, reinterpret_cast<struct sockaddr *>(&serverAddr), &len);
        if (n < 0) {
            perror("Receive failed");
            continue;
        }

        MessageFilter::filter(buffer, n);

        std::cout << "" << buffer;
    }
}
