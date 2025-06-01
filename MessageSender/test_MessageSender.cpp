#include "MessageSender.h"
#include <iostream>
#include <fstream>

int main() {
    int failedTests = 0;
    const std::string testFileName = "messages.txt";

    std::cout << "Running tests...\n";

    {
        MessageSender sender("127.0.0.1", 12345);
        const bool result = sender.sendMessagesFromFile(testFileName);
        if (!result) {
            std::cerr << "Test 1 failed: Should successfully send existing file\n";
            failedTests++;
        } else {
            std::cout << "Test 1 passed: Successfully sent existing file\n";
        }
    }

    if (failedTests == 0) {
        std::cout << "All tests passed!\n";
        return 0;
    }

    std::cerr << failedTests << " test(s) failed!\n";
    return 1;
}
