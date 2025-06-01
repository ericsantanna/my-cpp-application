#include "MessageSender.h"
#include <iostream>
#include <string>
#include <cstdlib>

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <server_ip> <port> <file_path>\n";
    std::cout << "Example: " << programName << " 127.0.0.1 12345 messages.txt\n";
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Error: Invalid number of arguments\n";
        printUsage(argv[0]);
        return 1;
    }

    const std::string serverIp = argv[1];
    uint16_t port;
    try {
        port = static_cast<uint16_t>(std::stoi(argv[2]));
    } catch (const std::exception& e) {
        std::cerr << "Error: Invalid port number\n";
        return 1;
    }
    const std::string filePath = argv[3];

    std::cout << "Initializing connection to " << serverIp << ":" << port << "...\n";
    MessageSender sender(serverIp, port);

    std::cout << "Sending messages from file: " << filePath << "\n";
    if (!sender.sendMessagesFromFile(filePath)) {
        std::cerr << "Error: Failed to send messages\n";
        return 1;
    }

    std::cout << "Messages sent successfully\n";
    return 0;
}