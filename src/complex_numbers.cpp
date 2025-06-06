#include <iostream> //cout
#include <cmath>    //sqrt
#include <iomanip>  //setprecision
using namespace std;

class Complex
{
private:
    double a;
    double b;
    double betrag; // wird im Konstruktor berechnet und mit display() angezeigt
public:
    Complex(const double &aKonstruktor, const double &bKonstruktor);
    Complex operator+(const Complex &other) const;
    Complex operator-(const Complex &other) const;
    Complex operator*(const Complex &other) const;
    Complex operator/(const Complex &other) const;
    Complex operator+(const double &x) const;
    Complex operator-(const double &x) const;
    Complex operator*(const double &x) const;
    Complex operator/(const double &x) const;
    double getA() const { return a; };
    double getB() const { return b; };
    void display();
    void display(const Complex &other);
    friend ostream &operator<<(ostream &os, const Complex &c);
};
Complex::Complex(const double &aKonstruktor, const double &bKonstruktor)
{ // Konstruktor
    a = aKonstruktor;
    b = bKonstruktor;
    betrag = sqrt(a * a + b * b);
}
// ueberlade Operatoren fuer den Fall, wenn beide Operanden komplex sind
Complex Complex::operator+(const Complex &other) const
{
    return Complex(a + other.a, b + other.b);
}
Complex Complex::operator-(const Complex &other) const
{
    return Complex(a - other.a, b - other.b);
}
Complex Complex::operator*(const Complex &other) const
{
    return Complex((a * other.a - b * other.b), (a * other.b + b * other.a));
}
Complex Complex::operator/(const Complex &other) const
{
    if (other.betrag == 0)
    {
        throw runtime_error("Division durch Null nicht erlaubt");
    }
    return Complex((a * other.a + b * other.b) / (other.a * other.a + other.b * other.b),
                   (b * other.a - a * other.b) / (other.a * other.a + other.b * other.b));
}
// ueberlade Operatoren fuer den Fall: komplex/reell
Complex Complex::operator+(const double &x) const
{
    return Complex(a + x, b);
}
Complex Complex::operator-(const double &x) const
{
    return Complex(a - x, b);
}
Complex Complex::operator*(const double &x) const
{
    return Complex(a * x, b * x);
}
Complex Complex::operator/(const double &x) const
{
    if (x == 0)
    {
        throw runtime_error("Division durch Null nicht erlaubt");
    }
    return Complex(a / x, b / x);
}
// ueberlade Operatoren (global) fuer den Fall: reell/komplex
Complex operator+(const double &x, const Complex &other)
{
    Complex temp = other;
    return Complex(temp.getA() + x, temp.getB());
}
Complex operator-(const double &x, const Complex &other)
{
    Complex temp = other;
    return Complex(x - temp.getA(), -temp.getB());
}
Complex operator*(const double &x, const Complex &other)
{
    Complex temp = other;
    return Complex(x * temp.getA(), x * temp.getB());
}
Complex operator/(const double &x, const Complex &other)
{
    Complex temp = other;
    return Complex((x * temp.getA()) / (temp.getA() * temp.getA() + temp.getB() * temp.getB()),
                   (-x * temp.getB()) / (temp.getA() * temp.getA() + temp.getB() * temp.getB()));
}
void Complex::display()
{
    cout << a << "+" << b << "i (Betrag: " << setprecision(4) << betrag << ")" << endl;
}
ostream &operator<<(ostream &os, const Complex &c)
{
    os << "(" << c.a << "+" << c.b << "i)";
    return os;
}

int main()
{
    try
    {
        Complex zahl1(4, 5);
        Complex zahl2(5, 7);
        cout << "Zwei komplexe Zahle, K1 und K2: " << endl;
        zahl1.display();
        zahl2.display();
        cout << '\n'
             << "Teste Komplex & Komplex (K1+K2-K2)*K2/K2, Ergebnis: " << endl;
        Complex ergebnisKK = (zahl1 + zahl2); // teste komplexe Zahlen
        ergebnisKK = ergebnisKK - zahl2;
        ergebnisKK = ergebnisKK * zahl2;
        ergebnisKK = ergebnisKK / zahl2;
        ergebnisKK.display();
        cout << '\n'
             << "Teste Komplex & Reell (K2+7-7)*7/7, Ergebnis: " << endl;
        Complex ergebnisKR = zahl2 + 7; // teste reelle Zahlen
        ergebnisKR = ergebnisKR - 7;    // einzelne Tests sind notwendig,
        ergebnisKR = ergebnisKR / 7;    // sonst optimiert Kompiler +7-7 zu 0
        ergebnisKR = ergebnisKR * 7;
        ergebnisKR.display();
        cout << '\n'
             << "Teste Reell & Komplex (Reell = 9, Komplex = K1): " << endl;
        Complex ergebnisRK1 = 9 + zahl1;
        cout << "9 + " << zahl1 << " = " << ergebnisRK1 << endl;
        ergebnisRK1 = 9 - zahl1;
        cout << "9 - " << zahl1 << " = " << ergebnisRK1 << endl;
        ergebnisRK1 = 9 * zahl1;
        cout << "9 * " << zahl1 << " = " << ergebnisRK1 << endl;
        ergebnisRK1 = 9 / zahl1;
        cout << "9 / " << zahl1 << " = " << ergebnisRK1 << endl;
        cout << endl;
    }
    catch (const runtime_error &e)
    {
        cout << "Fehler: " << e.what() << endl;
    }
}
