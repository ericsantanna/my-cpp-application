#pragma once
#include <MessageFilter.h>
#include <cstddef>

class MessageProcessor {
public:
    explicit MessageProcessor(int port);
    ~MessageProcessor();
    void run();

private:
    int socketFd_;
    static constexpr size_t BUFFER_SIZE = 50;
    unsigned char buffer[BUFFER_SIZE]{};
};