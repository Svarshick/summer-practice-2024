#include <iostream>

template<typename _H, typename _G1, typename _G2, typename _G, typename _G11>

class H {
public: 
    H(_H h, _G1 g1, _G2 g2, _G g, _G11 g11) : _h(h), _g1(g1), _g2(g2), _g(g), _g11(g11) {}
    
    template<typename T>
    auto operator()(T x, T y) { return _h(_g1(x), _g2(y), _g(x, y), _g11(x)); }
private:
    _H _h;
    _G1 _g1;
    _G2 _g2;
    _G _g;
    _G11 _g11;
};

class HBuilder {
public:
    template<typename _H, typename _G1, typename _G2, typename _G, typename _G11>
    auto operator()(_H h, _G1 g1, _G2 g2, _G g, _G11 g11) { return H<_H, _G1, _G2, _G, _G11>(h, g1, g2, g, g11); }
};

int main(){
    
    std::cout << "hello";
}