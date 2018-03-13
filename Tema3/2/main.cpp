#include <iostream>

using namespace std;
class Nod{
    public:
    int info;
    Nod *next;

    Nod(int info);

    Nod* adaugare(int a);
    Nod* scoatere(Nod *p);
};
Nod::Nod(int info)
{
        this->info=info;
        this->next=0;
}
Nod* Nod::adaugare(int a)
{
    Nod *p;
    p=new Nod(a);
    this->next=p;
    return p;
}
Nod* Nod::scoatere(Nod *p)
{
    Nod *q,*k;
    q=p;
    while(q->next!=0)
    {
        k=q;
        q=q->next;
    }
    k->next=0;
    delete q;
    return k;
}
int main()
{
    int n,i,ok=1,in;
    Nod *primu,*ultimu;
    while(ok)
    {
        cout<<"1)initializarea pointerului in stiva\n2)introducerea unei noi valori in stiva\n3)scoaterea unei valori din stivia\n4)Afisare\ndefault)iesire\n";
        cin>>i;

        switch(i)
        {
        case 1:
            {
             cout<<"primul element:";
             cin>>in;
             primu=new Nod(in);
             ultimu=primu;
             ok=2;
             break;
            }
        case 2:
            {
            if(ok!=2)
            {
                cout<<"EROR"<<"\n";
                break;
            }
            cout<<"elementul:";
            cin>>in;
            ultimu=ultimu->adaugare(in);
            break;
            }
        case 3:
             if(ok!=2)
            {
                cout<<"EROR"<<"\n";
                break;
            }
            if(ultimu==primu)
            {
                ok=1;
                delete primu;
            }
            else
                ultimu=primu->scoatere(primu);
            break;
        case 4:
            if(ok!=2)
            {
                cout<<"EROR"<<"\n";
                break;
            }
            Nod *parcurgere;
            parcurgere=primu;
            while(parcurgere!=0)
            {
                cout<<parcurgere->info<<" ";
                parcurgere=parcurgere->next;

            }
            cout<<"\n";
            break;
        default:
            ok=0;
            break;

        }
    }

}
