#include <iostream>

using namespace std;
class Stiva
{
    int dim;
    int poz=0;
    int *info;
public:
    Stiva(int dimensiune=0);
    void adaug(int el);
    void scoate();
    void afisare();
};
Stiva::Stiva(int dimensiune)
{
    dim=dimensiune;
    poz=0;
    info=new int[dim];
}
void Stiva::adaug(int el)
{
    info[poz]=el;
    poz++;
}
void Stiva::scoate()
{
    info[poz]=0;
    poz--;
}
void Stiva::afisare()
{
    for(int i=0;i<poz;i++)
        cout<<info[i]<<" ";
}
int main()
{
    Stiva a(0);
    a.adaug(1);
    a.adaug(2);
    a.adaug(3);
    a.scoate();
    a.afisare();
}
