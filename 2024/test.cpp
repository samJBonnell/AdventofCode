#include <iostream>

const void testFunc(uint32_t a);

int main(int argc, char** argv) {
    std::cout << "Have " << argc << " arguments:\n";
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << "\n";
    }
    return 0;
}

const void testFunc(uint32_t a) {
    std::cout << a << std::endl;
}