#include <iostream>
#include<string.h>
#include<vector>;
using namespace std;
struct data
{
    unsigned zi,luna,an;
};
class Plata
{
    public:
    unsigned suma;
    struct data dat;
    Plata *next;

        Plata(){};
        Plata(unsigned s,struct data d)
        {
            suma=s;
            dat=d;
            next=NULL;
        }
        Plata(const Plata &p)
        {
            suma=p.suma;
            dat=p.dat;
            next=NULL;
        }
        Plata operator=(const Plata &p)
        {
            *(this)=p;
        }
        void setnext(Plata *p)
        {
            next=p;
        }
        void citire();
        virtual void afisare(){
            cout<<"Cash\nSuma: "<<suma<<endl;
            cout<<"Data: "<<dat.zi<<" "<<dat.luna<<" "<<dat.an<<endl;

        };
};
void Plata::citire ()
{
    int i;
    cout<<"Suma: ";
    cin>>i;
    if(i<0)
    {
        cout<<"Suma nu poate fi Negativa, suma va fi setata ca 10"<<endl;
        suma=10;
    }
    else
        suma=i;
    cout<<"Ziua: ";
    cin>>i;
    if(i<0 || i>32)
    {
        cout<<"Zi invalida , ziua va fi setata ca 10"<<endl;
        dat.zi=10;
    }
    else
        dat.zi=i;
    cout<<"Luna: ";
    cin>>i;
    if(i<0 || i>12)
    {
        cout<<"luna invalida, luna va fi setata ca 10"<<endl;
        dat.luna=10;
    }
    else
        dat.luna=i;
    cout<<"Anul: ";
    cin>>i;
    if(i<1900 || i>2018)
    {
        cout<<"An Invalid, anul va fi setata ca 2018"<<endl;
        dat.an=2018;
    }
    else
        dat.an=i;
    next=NULL;
}

class Card: public Plata
{
    public:
    char *nume;
    vector<int> nrcard;

       Card() :Plata(){};
       Card(unsigned s,struct data d,char* n,vector<int> nr) :Plata(s,d)
       {
            nume=new char(strlen(n)+1);
            strcpy(nume,n);
            nrcard=nr;
       };
       ~Card()
       {
           delete nume;
           nrcard.clear();
       }
       void citirecard();
       void afisare();
};
void Card::citirecard()
{
    this->citire();
    char c[20];
    cout<<"Numele: ";
    cin>>c;
    nume=new char(strlen(c)+1);
    strcpy(nume,c);
    int i,a;
    cout<<"Cardul: ";
    for(i=1;i<=12;i++)
    {
        cin>>a;
        if(a<0 || a>9)
        {
            cout<<"variabila invalida ,se va pune 5"<<endl;
            nrcard.push_back(5);
        }
        else
            nrcard.push_back(a);

    }
}
 void Card::afisare()
{
    cout<<"Card\nSuma: "<<suma<<endl;
    cout<<"Data: "<<dat.zi<<" "<<dat.luna<<" "<<dat.an<<endl;
    cout<<"Nume: "<<nume<<endl;
    cout<<"Card: ";
    for(int i=0;i<12;i++)
        cout<<nrcard[i]<<" ";
    cout<<"\n";
}
template <class T>
class Gestiune
{
    public:
    int nrplati;
    Plata *comenzi;

        Gestiune()
        {
            nrplati=0;
            comenzi=NULL;
        };
        Gestiune(Plata p)
        {
            comenzi=new Plata(p);
            nrplati=1;
        }
        ~Gestiune()
        {
            Plata *p;
            if(comenzi!=NULL)
            {
                while(comenzi->next!=NULL)
                {

                    p=comenzi;
                    comenzi=comenzi->next;
                    delete p;
                }
                delete comenzi;
            }
        };
        Gestiune& operator+=(const Plata &p)
        {

            if(nrplati!=0)
            {
                Plata *q=new Plata(p),*t;
                nrplati++;
                t=comenzi;
                while(t->next!=NULL)
                    t=t->next;
                t->setnext(q);
            }
            else
            {

                nrplati=1;
                comenzi=new Plata(p);
            }
            return *this;
        };
        void citireg()
        {
              cout<<"Nr de plati: ";
                int n,i,c;
                Plata pla;
                Card card;
                cin>>n;
                for(i=0;i<n;i++)
                {
                    cout<<"1)Card 2)Cash: ";
                    cin>>c;
                    if(c==1)
                    {

                        card.citirecard();
                        *(this)+=card;
                    }
                    else
                    {

                        pla.citire();
                        *(this)+=pla;
                    }

                }
        };
        void afisare()
        {
            cout<<"Nr de palti: "<<nrplati<<endl;
            Plata *p;
            p=comenzi;
            for(int i=0;i<nrplati;i++)
            {

                    p->afisare();


                p=p->next;
            }
        }
};

template<>
class Gestiune<char*>{
    public:
    int nrclienti;
    char *clienti[100];

        Gestiune()
        {
            nrclienti=0;
        };
        Gestiune(char *p)
        {
            clienti[0]=new char(strlen(p)+1);
            strcpy(clienti[0],p);
            nrclienti=1;
        }
        ~Gestiune()
        {
            for(int i=0;i<nrclienti;i++)
                delete clienti[i];
        };
        Gestiune& operator+=(const Card &p)
        {
            Card *q;
            int ok=0;
            q=(Card*)&p;
            if(nrclienti!=0)
            {
               for(int i=0;i<nrclienti;i++)
               {
                   if(!(strcmp(clienti[i],q->nume)))
                   {
                        ok=1;
                        break;
                   }
               }
               if(ok==0)
               {
                    clienti[nrclienti]=new char(strlen(q->nume)+1);
                    strcpy(clienti[nrclienti],q->nume);
                    nrclienti++;
               }
            }
            else
            {
                clienti[0]=new char(strlen(q->nume)+1);
                strcpy(clienti[0],q->nume);
                nrclienti=1;
            }
            return *this;
        };
        void citireg()
        {
              cout<<"Nr de plati: ";
                int n,i,c;
                Plata pla;
                Card card;
                cin>>n;
                for(i=0;i<n;i++)
                {
                    cout<<"1)Card 2)Cash: ";
                    cin>>c;
                    if(c==1)
                    {

                        card.citirecard();
                        *(this)+=card;
                    }
                    else
                    {
                        pla.citire();
                    }

                }
        };
        void afisare()
        {
            cout<<"Nr de clienti: "<<nrclienti<<endl;
            char p[50];
            strcpy(p,clienti[0]);
            for(int i=1;i<nrclienti;i++)
            {
                cout<<p<<"\n";
                strcpy(p,clienti[i]);
            }
        }

};
 int main()
{
       Gestiune<int> g;
       g.citireg();
       g.afisare();
       return 0;
}
