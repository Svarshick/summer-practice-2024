#include <iostream>
#include <cassert>
#include <vector>
#include <concepts>

class MyRational {
public:
    // MyRational(int num, int den) : _num(num), _den(den) { 
    //     assert(("denominator have not to be null", _den != 0)); 
    //     transform();
    // }
    // MyRational(const MyRational& rat) : _num(rat._num), _den(rat._den) {};

    MyRational() : _num(1), _den(1) {} 

    friend std::ostream& operator<< (std::ostream& out, const MyRational& rat) { rat.print(out); return out; }
    friend bool operator== (const MyRational& rat1, const MyRational& rat2) { return (rat1._den == rat2._den) && (rat1._num == rat2._num); }
private:
    int gcd(int a, int b) {
        int t;
        while (b != 0) {
            t = b;
            b = a % b;
            a = t;
        }
        return a;
    }
    void transform() {
        bool numNeg = _num < 0;
        bool denNeg = _den < 0;
        if (numNeg && denNeg) {
            _num = -_num;
            _den = -_den;
        } else if (numNeg && !denNeg) {
            _num = -_num;
            _neg = true;
        } else if (!numNeg && denNeg) {
            _den = -_den;
            _neg = true;
        }
        int c = gcd(_num, _den);
        _num /= c;
        _den /= c;
    }
    void print(std::ostream& out) const { 
        if (_neg) { out << "-"; } 
        out << _num / _den << "(" << _num % _den << "/" << _den << ")"; 
    }
    
private:
    int _num;
    int _den;
    bool _neg = false;
};

template<std::regular T>
class CheckRegularity {
public:
    friend std::ostream& operator<< (std::ostream& out, const CheckRegularity<T>&) { out << "It is regular"; return out; }
};

int main() {
    // std::vector<MyRational> rat_vec {
    //     MyRational(1, 7),
    //     MyRational(6, 4),
    //     MyRational(5, 10),
    //     MyRational(0, 5),
    //     MyRational(6, 9),
    // };
    // for(auto e: rat_vec){
    //     std::cout << e << '\n';
    // }
    CheckRegularity<MyRational> checker1;
    std::cout << checker1 << '\n';
}