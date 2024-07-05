#include <iostream>
#include <format>
#include <concepts>

template<typename T>
void printF(T printable) { std::cout << "there is: " << printable << '\n'; }

template<std::integral T>
void printF(T printable) { std::cout << "there is integral: " << printable << '\n'; }

template<std::floating_point T>
void printF(T printable) { std::cout << "there is float: " << printable << '\n'; }

int main() {
    printF("bla");
    printF(12);
    printF(12.2);
}