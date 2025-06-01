#include "MessageProcessor.h"
#include <iostream>

int main() {
    const int port = 2300;

    try {
        MessageProcessor processor(port);
        processor.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}