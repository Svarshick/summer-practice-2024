#include <iostream>
#include <regex>
#include <cassert>

using str_I = std::wstring::const_iterator; 

void printAllMatches(str_I beg, str_I end, std::wregex& rex) {
    std::wsmatch sm;
    for(; std::regex_search(beg, end, sm, rex); beg += (sm.position() + sm.str().length()))
        std::wcout << sm.str() << '\n';
}

bool populationIsRight(std::wstring& data){
    std::wregex rex(L"население\\s+(((-)?\\d+\\.\\d+)|-\\d+)");
    return !std::regex_search(data, rex);
}

void task3(std::wstring& data) {
    assert(populationIsRight(data));
    std::wstring rex_s = L"((\\s+(I|N))?(\\S+\\s+))?";
    rex_s += L"(Беларусь|Венгрия|Польша|Болгария)";
    rex_s += L"(\\s+\\d+)?\\s+";
    rex_s += L"(площадь\\s+(\\S+\\s+)?\\d+(\\.\\d+)?кв.км|";
    rex_s += L"население\\s+\\d+)";
    std::wcout << L"regular expression is: " << rex_s << '\n'; 
    std::wregex rex(rex_s);
    std::wcout << L"data: " << data << '\n';
    std::wcout << "result:\n";
    printAllMatches(data.begin(), data.end(), rex);
}

int main() {
    std::wstring data = L" dfg Беларусь  367 площадь 6.3456кв.км";
    task3(data);
}