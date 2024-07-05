#include <iostream>

template<typename H, typename G1, typename G2, typename G, typename G11>
class Composed {
public: 
    Composed(H h, G1 g1, G2 g2, G g, G11 g11) : _h(h), _g1(g1), _g2(g2), _g(g), _g11(g11) {}
    
    template<typename T>
    auto operator()(T x, T y) { return _h(_g1(x), _g2(y), _g(x, y), _g11(x)); }
private:
    H _h;
    G1 _g1;
    G2 _g2;
    G _g;
    G11 _g11;
};

class ComposedBuilder {
public:
    template<typename H, typename G1, typename G2, typename G, typename G11>
    auto operator()(H h, G1 g1, G2 g2, G g, G11 g11) { return Composed<H, G1, G2, G, G11>(h, g1, g2, g, g11); }
};

// template<typename Op, typename ... Fs>
// class TupleComposed {
// public:
//     TupleComposed(Op op, Fs ... fs) : _op(op), _fs(fs ...) {}

//     template <typename T>
//     auto operator()(T x) { 
//         return callFunction(x, std::make_index_sequence<sizeof...(Fs)>());   
//     }
// private:
//     template<typename T, typename TupleT, std::size_t ... Is>
//     decltype(auto) callFunction(T x, std::integer_sequence<TupleT, Is...>) const { 
//         return _op(std::get<Is>(_fs)(x)...);
//     }
// private:
//     Op _op;
//     std::tuple<Fs ...> _fs;

// };

// template<typename Op, typename ... Fs>
// TupleComposed<Op, Fs ...> buildTupleComposed(Op op, Fs ... fs){
//     return TupleComposed<Op, Fs ...>(op, fs...);
// }

template<typename H, typename G1, typename G2, typename G, typename ... G1n>
class TupleComposed {
public:
    TupleComposed(H h, G1 g1, G2 g2, G g, G1n ... g1n) : _h(h), _g1(g1), _g2(g2), _g(g), _g1n(g1n ...) {}
    template<typename T>
    auto operator ()(T x, T y){
        return callFunction(x, y, std::make_index_sequence<sizeof ...(G1n)>());
    }
private:
    template<typename T, typename G1nT, typename std::size_t ... Is> 
    decltype(auto) callFunction(T x, T y, std::integer_sequence<G1nT, Is...>) const {
        return _h(_g1(x), _g2(y), _g(x, y), std::get<Is>(_g1n)(x)...);
    }
private:
    H _h;
    G1 _g1;
    G2 _g2;
    G _g;
    std::tuple<G1n ...> _g1n;
};

template<typename H, typename G1, typename G2, typename G, typename ... G1n>
TupleComposed<H, G1, G2, G, G1n ...> buildTupleComposed(H h, G1 g1, G2 g2, G g, G1n ... g1n){
    return TupleComposed<H, G1, G2, G, G1n ...>(h, g1, g2, g, g1n...);
}

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

    auto tupleComposed = buildTupleComposed(h, g1, g2, g, g11);
    std::cout << "result with tuple is: " << tupleComposed(x, y) << '\n';

    auto g12 = [](auto x) { return -x; };
    auto g13 = [](auto x) { return x * x * x; };
    auto g14 = [](auto x) { return x + 100; };  
    auto h14 = [](auto a1, auto a2, auto a, auto a11, auto a12, auto a13, auto a14) { return a1 + a2 + a + a11 + a12 + a13 + a14; };
    auto tupleComposed14 = buildTupleComposed(h14, g1, g2, g, g11, g12, g13, g14);
    std::cout << "result with tuple 14 is: " << tupleComposed14(x, y) << '\n';
}