#include <iostream>
#include <variant>  // C++17 feature

int main() {
    std::variant<int, std::string> data = "C++17 is enabled!";
    std::cout << std::get<std::string>(data) << std::endl;
    return 0;
}
