#include <iostream>

using namespace std;
class Lemon
{
    int lamai;
    int zahar;
    int suma_incasari$$$;
public:
    Lemon(int z=0,int l=0);
    void bea_o_limonada_indulcita();
    void bea_o_limonada_neindulcita();
    void afisare_total_incasari();
};
Lemon::Lemon(int z,int l)
{
    lamai=l;
    zahar=z;
    suma_incasari$$$=0;
}
void Lemon::bea_o_limonada_indulcita()
{
    if(lamai<1 || zahar<2)
        cout<<"EROR\n";
    else
    {
    lamai--;
    zahar--;
    zahar--;
    suma_incasari$$$=suma_incasari$$$+2;
    }
}
void Lemon::bea_o_limonada_neindulcita()
{
    if(lamai<1)
        cout<<"EROR\n";
    {
    lamai--;
    suma_incasari$$$=suma_incasari$$$+1;
    }
}
void Lemon::afisare_total_incasari()
{
    cout<<"Totalul incasat este:"<<suma_incasari$$$<<"$\n";
}
int main()
{
    int z,l,i,ok=1;
    cout<<"Cate lamai?\n";
    cin>>l;
    cout<<"Cat Zahar?\n";
    cin>>z;
    Lemon lam(z,l);
    while(ok)
    {
        cout<<"1)O limonada indulcita($2)\n2)O limonada neindulcita($1)\n3)Afisare total incasari\n4)Iesire\n";
        cin>>i;
        switch(i)
        {
        case 1:
            lam.bea_o_limonada_indulcita();
            break;
        case 2:
            lam.bea_o_limonada_neindulcita();
            break;
        case 3:
            lam.afisare_total_incasari();
            break;
        case 4:
            ok=0;
            break;
        default:
            cout<<"EROR\n";
            break;

        }
    }
}
