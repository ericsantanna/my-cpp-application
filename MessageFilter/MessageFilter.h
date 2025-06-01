#pragma once
#include <sys/types.h>

class MessageFilter {
public:
    static void filter(unsigned char buffer, ssize_t size);
};
