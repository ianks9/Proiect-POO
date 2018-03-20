#include <iostream>

using namespace std;
class pereche
{
    double coeficient;
    unsigned exponent;
public:
    pereche(double c,unsigned e)
    {
        coeficient=c;
        exponent=e;
    }
    friend std::ostream& operator<< (std::ostream &out, const pereche &p);
};
std::ostream& operator<< (std::ostream &out, const pereche &p)
{
    out <<p.coeficient<<"*x^"<<p.exponent;
    return out;
}
class polinom
{
    friend class pereche;
};

int main()
{
    pereche a(4.5,6);
    cout<<a;
}
