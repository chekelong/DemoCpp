#include <iostream>
#include <string>

int main() {
    std::string input;
    while (true)
    {
        std::cout << "Please enter a string: ";
        std::getline(std::cin, input);
        std::cout << "You entered: " << input << std::endl;
    }
    return 0;
}