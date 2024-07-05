#include <iostream>

template<typename _H, typename _G1, typename _G2, typename _G, typename _G11>
class Composed {
public: 
    Composed(_H h, _G1 g1, _G2 g2, _G g, _G11 g11) : _h(h), _g1(g1), _g2(g2), _g(g), _g11(g11) {}
    
    template<typename T>
    auto operator()(T x, T y) { return _h(_g1(x), _g2(y), _g(x, y), _g11(x)); }
private:
    _H _h;
    _G1 _g1;
    _G2 _g2;
    _G _g;
    _G11 _g11;
};

class ComposedBuilder {
public:
    template<typename _H, typename _G1, typename _G2, typename _G, typename _G11>
    auto operator()(_H h, _G1 g1, _G2 g2, _G g, _G11 g11) { return Composed<_H, _G1, _G2, _G, _G11>(h, g1, g2, g, g11); }
};

// template<typename Op, typename ... Fs>
// class TupleComposed {
// public:
//     TupleComposed(Op op, Fs ... fs) : _op(op), _fs(fs ...) {}

//     template <typename T>
//     auto operator()(T x, T y) { return _op(_fs ...); }
// private:
//     template<typename T, typename TupleT, std::size_t ... Is>
//     auto callFunction()
// private:
//     Op _op;
//     std::tuple<Fs ...> _fs;

// }

int main(){
    auto LambdaComposedBuilder = [](auto h, auto g1, auto g2, auto g, auto g11) -> auto {
        return [h, g1, g2, g, g11](auto x, auto y) { return h(g1(x), g2(y), g(x, y), g11(x)); };
    };
    auto h = [](auto a1, auto a2, auto a, auto a11) { return a1 + a2 + a + a11; };
    auto g1 = [](auto x) { return x * x; };
    auto g2 = [](auto y) { return y * 2; };
    auto g = [](auto x, auto y) { return x * y; };
    auto g11 = [](auto x) { return x * 2; };

    auto lambdaComposed = LambdaComposedBuilder(h, g1, g2, g, g11);
    
    ComposedBuilder ComposedBuilder;
    auto funObjComposed = ComposedBuilder(h, g1, g2, g, g11);
    
    int x = 5;
    int y = 9;
    std::cout << "input is:\nx = " << x << "\ny = " << y << '\n';  
    std::cout << "result with lamda is: " << lambdaComposed(x, y) << '\n';
    std::cout << "result with functional object is: " << funObjComposed(x, y) << '\n';
}