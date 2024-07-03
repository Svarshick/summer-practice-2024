#include <regex>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>

using str_it = std::string::const_iterator;

void printAllMatches(str_it beg, str_it end, const std::regex& rex){
    std::smatch sm;
    for (;std::regex_search(beg, end, sm, rex); beg += (sm.position() + sm.length()))
        std::cout << sm.str() << '\n';
}

void simple_paragraph(const std::string& data, const std::regex& rex, int p) {
    std::cout << "------p" << p << " is beginnig------\n";
    printAllMatches(data.cbegin(), data.cend(), rex);
    std::cout << "p" << p << " is completed\n";
}

void p11(const std::string& data){
    std::regex rex("\\d");

    assert(("there is no numerics", std::regex_search(data, rex)));

    auto beg = data.cbegin();
    auto end = data.cend();
    std::smatch sm;
    double sum = 0;
    for (;std::regex_search(beg, end, sm, rex); beg += (sm.position() + sm.length()))
        sum += stoi(sm.str());
    
    std::cout << "------result of p11: " << sum << "------\n";
}

void p12(const std::string& data){
    std::regex rex("<([^<>]+)>");
    
    assert(("there is no <lps> type string", std::regex_search(data, rex)));

    auto beg = data.cbegin();
    auto end = data.cend();
    std::smatch sm; 
    std::string result;
    for (; std::regex_search(beg, end, sm, rex); beg += (sm.position() + sm.length()))
        result += sm[1].str();
    
    std::cout << "------result of p12: " << result << "------\n";
}

int main(){
    std::string data;
    data = "abca a1a a2a a6,7sdc8.9ksdja 2+++3 ab<sdf<here>bbbb>>a <>abba<and here>  >>";
    std::vector<std::regex> rex_storage {
        std::regex("a..a"),
        std::regex("a([^b].|b[^c])a"), 
        std::regex("a(b)*a"), 
        std::regex("(ab)+"), 
        std::regex("2(\\+)*3"),
        std::regex("a(b){2,4}a"),
        std::regex("a(b){4,}"),
        std::regex("a[0-9]a"),
        std::regex("a\\Da"),
        std::regex("a[a-z]+a"),
    };
    for (int i = 0; i < rex_storage.size(); ++i)
        simple_paragraph(data, rex_storage[i], i + 1);
    
    p11(data);
    p12(data);
}