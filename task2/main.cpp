#include <regex>
#include <cassert>
#include <string>
#include <iostream>

std::wstring getMaxMutched(const std::wstring& data, const std::wregex& rex){
    
    assert(("there is no mutches", regex_search(data, rex)));

    auto beg = data.begin();
    auto end = data.end();
    std::wsmatch sm;
    std::wstring out;
    for (; std::regex_search(beg, end, sm, rex); beg += (sm.position() + sm.length()))
        if(sm.length() > out.length())
            out = sm.str();
    
    return out;
}
    
int main(){
    std::wstring data;
    data = L"12345 q22ab2345abc534500ab";
    std::wregex rex(L"\\d+");

    std::wcout << getMaxMutched(data, rex) << '\n';
}