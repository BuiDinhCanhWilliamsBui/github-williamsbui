#include <iostream>
#include <variant>  // C++17 feature
using namespace std;


int main() {
    std::variant<int, std::string> data = "C++17 is enabled!";
    std::cout << std::get<std::string>(data) << std::endl;
    cout << "cuối cùng t đã biết dùng git" << endl;
    return 0;
}
