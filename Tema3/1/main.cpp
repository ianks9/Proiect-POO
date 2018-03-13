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
    for(int i=0;i<=poz;i++)
    {
        info[i]=info[i+1];
    }
    poz--;
}
void Stiva::afisare()
{
    for(int i=0;i<poz;i++)
        cout<<info[i]<<" ";
    cout<<"\n";
}
int main()
{
    int n,i,ok=1,in;
    Stiva a;
    while(ok)
    {
        cout<<"1)initializarea pointerului in stiva\n2)introducerea unei noi valori in stiva\n3)scoaterea unei valori din stivia\n4)afisare\ndefault)iesire\n";
        cin>>i;

        switch(i)
        {
        case 1:
            {
             cout<<"dimensiunea:";
             cin>>in;
             Stiva a(in);
             break;
            }
        case 2:
            {
            cout<<"elementul:";
            cin>>in;
            a.adaug(in);
            break;
            }
        case 3:
            a.scoate();
            break;
        case 4:
            a.afisare();
            break;
        default:
            cout<<"EROR\n";
            break;
        }
    }
}
