#pragma once
#include <string>
#include <fstream>
#include <netinet/in.h>

class MessageSender {
public:
    MessageSender(const std::string& serverIp, uint16_t port);
    ~MessageSender();

    bool sendMessagesFromFile(const std::string& filePath);

private:
    bool sendMessage(const std::string& message);
    bool initializeSocket();

    static constexpr size_t MAX_MESSAGE_SIZE = 50;
    int socketFd_;
    sockaddr_in serverAddr_{};
};
