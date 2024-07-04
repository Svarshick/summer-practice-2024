#include <regex>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>

using str_it = std::wstring::const_iterator;

void printAllMatches(str_it beg, str_it end, const std::wregex& rex){
    std::wsmatch sm;
    for (;std::regex_search(beg, end, sm, rex); beg += (sm.position() + sm.length()))
        std::wcout << sm.str() << '\n';
}

void simple_paragraph(const std::wstring& data, const std::wregex& rex, int p) {
    std::wcout << "------p" << p << " is beginnig------\n";
    printAllMatches(data.cbegin(), data.cend(), rex);
    std::wcout << "p" << p << " is completed\n";
}

void p11(const std::wstring& data){
    std::wregex rex(L"\\d");

    assert(("there is no numerics", std::regex_search(data, rex)));

    auto beg = data.cbegin();
    auto end = data.cend();
    std::wsmatch sm;
    double sum = 0;
    for (;std::regex_search(beg, end, sm, rex); beg += (sm.position() + sm.length()))
        sum += stoi(sm.str());
    
    std::wcout << "------result of p11: " << sum << "------\n";
}

void p12(const std::wstring& data){
    std::wregex rex(L"<([^<>]+)>");
    
    assert(("there is no <lps> type string", std::regex_search(data, rex)));

    auto beg = data.cbegin();
    auto end = data.cend();
    std::wsmatch sm; 
    std::wstring result;
    for (; std::regex_search(beg, end, sm, rex); beg += (sm.position() + sm.length()))
        result += sm[1].str();
    
    std::wcout << "------result of p12: " << result << "------\n";
}

int main(){
    setlocale(LC_ALL, "");
    std::wstring data;
    data = L"aбfццбfa";
    std::vector<std::wregex> rex_storage {
        std::wregex(L"a..a"),
        std::wregex(L"a([^b].|b[^c])a"), 
        std::wregex(L"a(b)*a"), 
        std::wregex(L"(ab)+"), 
        std::wregex(L"2(\\+)*3"),
        std::wregex(L"a(b){2,4}a"),
        std::wregex(L"a(b){4,}"),
        std::wregex(L"a[0-9]a"),
        std::wregex(L"a\\Da"),
        std::wregex(L"a[a-zа-я]+?a"),
    };
    std::wcout << "data: " << data << '\n';
    for (int i = 0; i < rex_storage.size(); ++i)
        simple_paragraph(data, rex_storage[i], i + 1);
    
    p11(data);
    p12(data);
}