#include <iostream>
#include <string>
#include <iomanip>
//1 == long, 0 == double
#define TYPE 0
using namespace std;

class Dezimal4{
private:
    long long value;
public:
    Dezimal4(double a) : value(a*10000) {}
    Dezimal4(int a)    : value(a*10000) {}
    Dezimal4(){}
    Dezimal4 operator+(Dezimal4 other)
        {Dezimal4 temp;  temp.value = value + other.getV();  return temp;}
    Dezimal4 operator-(Dezimal4 other)
        {Dezimal4 temp;  temp.value = value - other.getV();  return temp;}
    Dezimal4 operator*(Dezimal4 other)
        {Dezimal4 temp;  temp.value = value * other.getV() / 10000; return temp;}
    Dezimal4 operator/(Dezimal4 other)
        {Dezimal4 temp;  temp.value = value / other.getV() * 10000; return temp;}

    long long getV() {return value;};
    void setV(long long c) {value = c;}
    friend ostream& operator<<(ostream& os, const Dezimal4 c);
};
template <typename plusDx>
Dezimal4 operator+(Dezimal4 a, plusDx b){
    Dezimal4 temp(b);   temp.setV(a.getV() + temp.getV());  return temp;
}
template <typename plusDx>
Dezimal4 operator+(plusDx b, Dezimal4 a){
    Dezimal4 temp(b);   temp.setV(a.getV() + temp.getV());  return temp;
}
template <typename minusDx>
Dezimal4 operator-(Dezimal4 a, minusDx b){
    Dezimal4 temp(b);   temp.setV(a.getV() - temp.getV());  return temp;
}
template <typename minusDx>
Dezimal4 operator-(minusDx b, Dezimal4 a){
    Dezimal4 temp(b);   temp.setV(temp.getV() - a.getV());  return temp;
}
template <typename malDx>
Dezimal4 operator*(Dezimal4 a, malDx b){
    Dezimal4 temp(b);   temp.setV(a.getV() * temp.getV() / 10000);  return temp;
}
template <typename malDx>
Dezimal4 operator*(malDx b, Dezimal4 a){
    Dezimal4 temp(b);   temp.setV(a.getV() * temp.getV() / 10000);  return temp;
}
template <typename divDx>
Dezimal4 operator/(Dezimal4 a, divDx b){
    Dezimal4 temp(b);   temp.setV(a.getV() * 10000 / temp.getV());
    //if(temp.getV() == 0) throw runtime_error("Division durch 0");
    return temp;
}
template <typename divDx>
Dezimal4 operator/(divDx b, Dezimal4 a){
    Dezimal4 temp(b);   temp.setV(temp.getV() * 10000 / a.getV());
    //if(a.getV() == 0) throw runtime_error("Division durch 0");
    return temp;
}
//ueberlade << und <=
string toString(Dezimal4 c) {
    #if TYPE == 0
    return to_string(static_cast<double>(c.getV()) / 10000.0);
    #endif // TYPE
    #if TYPE == 1
    return to_string(static_cast<long>(c.getV()) / 10000);
    #endif // TYPE
}

ostream& operator<<(ostream& os, Dezimal4 c) {
    #if TYPE == 0
    os << static_cast<double>(c.value) / 10000.0;
    #endif // TYPE
    #if TYPE == 1
    os << static_cast<long>(c.value) / 10000;
    #endif // TYPE
    return os;
}
bool operator<=(Dezimal4 x, Dezimal4 c){
    if(x.getV() <= c.getV()) {return true;}
    else {return false;}
}

Dezimal4 est(Dezimal4 x) {
    // Einkommensteuertarif nach § 32a (1) - heute veraltet
    Dezimal4 est;
    x = (x / 54) * 54;

    if (x <= 12365){
        est.setV(0);
    }
    else if (x <= 58643){
        Dezimal4 y = (x - 12312) / 10000;
        est = (91.19 * y + 2590) * y;
    }
    else if (x <= 120041){
        Dezimal4 z = (x - 58590) / 10000;
        est = (151.96 * z + 3434) * z + 13938;
    }
    else{
        est = 0.53 * x - 22843;
    }
    est = est * 10000 / 10000;
    return est;
}
int main() {
    cout << setw(7) << 'x' << setw(15) << "Est" << endl;
    for(int i = 10800; i <= 118800; i += 5400){
        cout << setw(7) << i << setw(15) << toString(est(i)) << endl;
        if( (i-5400)%7 == 0) {printf("\n");}
    }
    #if TYPE == 0
    double zahl = 12.99;
    Dezimal4 zahl1(zahl);
    cout << "StartWert: " << zahl1 << endl;
    cout << endl;//teste Plus
    Dezimal4 test1 = zahl1 + zahl1;     //4.8
    Dezimal4 test2 = 2 + 2.3 + zahl1;   //6.7
    Dezimal4 test3 = zahl1 + 2.3 + 2;   //6.7
    cout << test1 << endl;
    cout << test2 << endl;
    cout << test3 << endl;
    cout << endl;//teste Minus
    Dezimal4 test4 = zahl1 - zahl1;     //0
    Dezimal4 test5 = 2 - 2.3 - zahl1;   //-2.7
    Dezimal4 test6 = zahl1 - 2.3 - 2;   //-1.9
    cout << test4 << endl;
    cout << test5 << endl;
    cout << test6 << endl;
    cout << endl;//teste Produkt
    Dezimal4 test7 = zahl1 * zahl1;     //5.76
    Dezimal4 test8 = 2 * 2.3 * zahl1;   //11.04
    Dezimal4 test9 = zahl1 * 2.3 * 2;   //11.04
    cout << test7 << endl;
    cout << test8 << endl;
    cout << test9 << endl;
    cout << endl;//teste Division
    Dezimal4 test10 = zahl1 / zahl1;    //1
    Dezimal4 test11 = 20 / 2.3 / zahl1; //3.62
    Dezimal4 test12 = zahl1 / 8;  //0.52
    cout << test10 << endl;
    cout << test11 << endl;
    cout << test12 << endl;
    #endif // TYPE
    return 0;
}
