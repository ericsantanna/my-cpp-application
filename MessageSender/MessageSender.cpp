#include "MessageSender.h"
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

MessageSender::MessageSender(const std::string& serverIp, const uint16_t port) {
    socketFd_ = -1;
    memset(&serverAddr_, 0, sizeof(serverAddr_));
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_port = htons(port);
    inet_pton(AF_INET, serverIp.c_str(), &serverAddr_.sin_addr);

    initializeSocket();
}

MessageSender::~MessageSender() {
    if (socketFd_ >= 0) {
        close(socketFd_);
    }
}

bool MessageSender::initializeSocket() {
    socketFd_ = socket(AF_INET, SOCK_STREAM, 0);
    return socketFd_ >= 0;
}

bool MessageSender::sendMessage(const std::string& message) {
    if (socketFd_ < 0) return false;

    const ssize_t bytesSent = sendto(
        socketFd_,
        message.c_str(),
        message.length(),
        0,
        reinterpret_cast<struct sockaddr *>(&serverAddr_),
        sizeof(serverAddr_)
    );

    return bytesSent == static_cast<ssize_t>(message.length());
}

bool MessageSender::sendMessagesFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        std::size_t pos = 1;
        while (pos < line.length()) {
            std::string chunk = line.substr(pos, MAX_MESSAGE_SIZE);
            if (pos + MAX_MESSAGE_SIZE >= line.length()) {
                chunk += "\n";
            }
            if (!sendMessage(chunk)) {
                file.close();
                return false;
            }
            pos += MAX_MESSAGE_SIZE;
        }
    }

    file.close();
    return true;
}