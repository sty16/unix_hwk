#include<iostream>
using namespace std;

typedef struct fraction {
    int numerator, denominator;
    fraction(int _numerator, int _denominator) : numerator(_numerator), denominator(_denominator) {};

    fraction operator + (const fraction& rhs) {
        fraction ans(0, 0);
        ans.numerator = numerator * rhs.denominator + denominator * rhs.numerator;
        ans.denominator = denominator * rhs.denominator;
        ans.simplify();
        return ans;
    }

    fraction operator - (const fraction& rhs) {
        fraction ans(0, 0);
        ans.numerator = numerator * rhs.denominator - denominator * rhs.numerator;
        ans.denominator = denominator * rhs.denominator;
        ans.simplify();
        return ans;
    }

    fraction operator * (const fraction& rhs) {
        fraction ans(0, 0);
        ans.numerator = numerator * rhs.numerator;
        ans.denominator = denominator * rhs.denominator;
        ans.simplify();
        return ans;
    }

    fraction operator / (const fraction& rhs) {
        fraction ans(0, 0);
        ans.numerator = numerator * rhs.denominator;
        ans.denominator = denominator * rhs.numerator;
        ans.simplify();
        return ans;
    }

    friend ostream & operator << (ostream& out , fraction rhs);

    void simplify() {
        int c = gcd(numerator, denominator);
        numerator = numerator / c;
        denominator = denominator / c;
    }

    double toDouble() {
        return 1.0 * numerator / denominator;
    }

    int gcd(int a, int b) {
        return b ? gcd(b, a % b) : a;
    }

} fraction;

ostream & operator << (ostream &out, fraction rhs) {
    out << rhs.numerator << " / " << rhs.denominator << endl;
    return out;
}

int main() {
    fraction a(3, 5), b(3, 12);
    cout << a + b << a - b << a * b << a / b;
    cout << a.toDouble() << endl;
    b.simplify();
    cout << b;
}