#include <iostream>
#include <format>
#include <vector>
#include <string>

int main() {
    std::string msg1 = std::format("{:*^10}\n{:*>10}\n{:*<10}\n", "hello", "world", "!");
    int var = 0x324;
    std::string msg2 = std::format("{0:#016}\n{0:#016b}\n{0:#016x}\n", var);
    int width = 10;
    std::string msg3 = std::format("{0:*<{1}}", "here!", width);
    std::cout << std::format("formatting hello:\n{}formatting {:#x}:\n{}formatting with using width variable = {}:\n{}\n", msg1, var, msg2, width, msg3);
}