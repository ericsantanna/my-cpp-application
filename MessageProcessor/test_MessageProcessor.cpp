#include <iostream>
#include <thread>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "MessageProcessor.h"

void message_filter(char* buffer, const size_t size) {
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = toupper(buffer[i]);
    }
}

void mockMessageSender(const int port, const char* message) {
    const int socketFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketFd < 0) {
        perror("Socket creation failed");
        return;
    }

    sockaddr_in serverAddr{};
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(socketFd, message, strlen(message), 0, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr));
    close(socketFd);
}

int main() {
    constexpr int port = 2300;
    const char* testMessage = "I'm a message";

    std::thread receiverThread([&port]() {
        MessageProcessor receiver(port);
        receiver.run();
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    mockMessageSender(port, testMessage);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    receiverThread.detach();

    return 0;
}