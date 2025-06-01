#include "MessageFilter.h"
#include <iostream>
#include <cassert>
#include <array>

void testFilter() {
    std::array<unsigned char, 7> buffer = {65, 200, 66, 128, 67, 127, 68};

    MessageFilter::filter(buffer.data(), buffer.size());

    const std::array<unsigned char, 7> expected = {65, 66, 67, 127, 68, 0, 0};
    for (std::size_t i = 0; i < buffer.size(); ++i) {
        assert(buffer[i] == expected[i]);
    }

    std::cout << "Test passed!" << std::endl;
}

int main() {
    testFilter();
    return 0;
}