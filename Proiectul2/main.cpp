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
    protected:
    unsigned suma;
    struct data dat;
    Plata *next;
    public:
        Plata(){};
        Plata(unsigned s,struct data d)
        {
            suma=s;
            dat=d;
            next=NULL;
        }
        Plata* getnext()
        {
            return next;
        }
        struct data getd()
        {
            return dat;
        };
        unsigned getsuma()
        {
            return suma;
        }
        Plata(const Plata &p)
        {
            suma=p.suma;
            dat=p.dat;
            next=NULL;
        }
        Plata operator=(Plata &p)
        {
            *(this)=p;
        }
        void setnext( Plata *p)
        {
            next=p;
        }
        friend void citire(Plata &p);
        virtual void afisare(){
            cout<<"Cash\nSuma: "<<suma<<endl;
            cout<<"Data: "<<dat.zi<<" "<<dat.luna<<" "<<dat.an<<endl;

        };
};
void citire (Plata &p)
{

    int i;
    cout<<"Suma: ";
    cin>>i;
    if(i<0)
    {
        cout<<"Suma nu poate fi Negativa, suma va fi setata ca 10"<<endl;
        p.suma=10;
    }
    else
        p.suma=i;
    cout<<"Ziua: ";
    cin>>i;
    if(i<0 || i>32)
    {
        cout<<"Zi invalida , ziua va fi setata ca 10"<<endl;
        p.dat.zi=10;
    }
    else
        p.dat.zi=i;
    cout<<"Luna: ";
    cin>>i;
    if(i<0 || i>12)
    {
        cout<<"luna invalida, luna va fi setata ca 10"<<endl;
        p.dat.luna=10;
    }
    else
        p.dat.luna=i;
    cout<<"Anul: ";
    cin>>i;
    if(i<1900 || i>2018)
    {
        cout<<"An Invalid, anul va fi setata ca 2018"<<endl;
        p.dat.an=2018;
    }
    else
        p.dat.an=i;
    p.next=NULL;
}

class Card: public Plata
{
    protected:
    char *nume;
    vector<int> nrcard;
    public:
       Card() :Plata(){};
       char *getnu()
       {
           return nume;
       }
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
       void cc(Plata p)
       {
           this->dat=p.getd();
           this->suma=p.getsuma();
           this->next=p.getnext();
       }
       friend void citirecard();
       void afisare();
       void citirenume()
       {
           char c[20];
            cout<<"Numele: ";
            cin>>c;
            this->nume=new char(strlen(c)+1);
            strcpy(this->nume,c);
       }
       void adaugainvector(int a)
       {
           this->nrcard.push_back(a);
       }
};
void citirecard(Card ca)
{
    Plata p;
    citire(p);
    ca.cc(p);
    ca.citirenume();
    int i,a;
    cout<<"Cardul: ";
    for(i=1;i<=12;i++)
    {
        cin>>a;
        if(a<0 || a>9)
        {
            cout<<"variabila invalida ,se va pune 5"<<endl;
            ca.adaugainvector(5);
        }
        else
            ca.adaugainvector(a);

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
    protected:
    int nrplati;
    Plata *comenzi;
    public:
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
                while(comenzi->getnext()!=NULL)
                {

                    p=comenzi;
                    comenzi=comenzi->getnext();
                    delete p;
                }
                delete comenzi;
            }
        };
        Gestiune& operator+=(const Plata &p)
        {

            if(nrplati!=0)
            {
                Plata *t,*q=new Plata(p);
                nrplati++;
                t=comenzi;
                while(t->getnext()!=NULL)
                    t=t->getnext();
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
                Plata pla,*p;
                Card card;
                cin>>n;
                for(i=0;i<n;i++)
                {
                    cout<<"1)Card 2)Cash: ";
                    cin>>c;
                    if(c==1)
                    {

                        citirecard(card);

                        p=dynamic_cast<Plata*>(&card);
                        *(this)+=*p;
                    }
                    else
                    {
                        if(c!=2)
                            cout<<"input gresit , se va citi cash";
                        citire(pla);
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
                    p=p->getnext();
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
        Gestiune& operator+=(Card &p)
        {
            Card *q;
            int ok=0;
            q=&p;
            if(nrclienti!=0)
            {
               for(int i=0;i<nrclienti;i++)
               {
                   if(!(strcmp(clienti[i],q->getnu())))
                   {
                        ok=1;
                        break;
                   }
               }
               if(ok==0)
               {
                    clienti[nrclienti]=new char(strlen(q->getnu())+1);
                    strcpy(clienti[nrclienti],q->getnu());
                    nrclienti++;
               }
            }
            else
            {
                //------------------------EROR----------------------------------------------
                clienti[0]=new char(strlen(q->getnu())+1);
                strcpy(clienti[0],q->getnu());
                //------------------------EROR----------------------------------------------
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

                        citirecard(card);
                        *(this)+=card;
                    }
                    else{
                    if(c==2)
                    {
                        citire(pla);
                    }
                    else
                        cout<<"input prost se va citi cash<<endl";
                        citire(pla);
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
