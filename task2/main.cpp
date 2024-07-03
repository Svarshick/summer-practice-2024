#include <regex>
#include <cassert>
#include <string>
#include <iostream>

std::string getMaxMutched(const std::string& data, const std::regex& rex){
    
    assert(("there is no mutches", regex_search(data, rex)));

    auto beg = data.begin();
    auto end = data.end();
    std::smatch sm;
    std::string out;
    for (; std::regex_search(beg, end, sm, rex); beg += (sm.position() + sm.length()))
        if(sm.length() > out.length())
            out = sm.str();
    
    return out;
}

int main(){
    std::string data;
    data = "blablaasdlf;kaaaaaaaabj asaaabdfl";
    std::regex rex("(a)+b");

    std::cout << getMaxMutched(data, rex) << '\n';
}