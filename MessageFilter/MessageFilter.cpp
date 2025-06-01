#include "MessageFilter.h"
#include <sys/types.h>

void MessageFilter::filter(unsigned char* buffer, const ssize_t size) {
    ssize_t writeIndex = 0;

    for (ssize_t readIndex = 0; readIndex < size; ++readIndex) {
        if (buffer[readIndex] <= 127) {
            buffer[writeIndex++] = buffer[readIndex];
        }
    }

    for (ssize_t i = writeIndex; i < size; ++i) {
        buffer[i] = 0;
    }
}
