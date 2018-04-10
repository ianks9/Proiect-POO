#include <iostream>
#include<fstream>
using namespace std;
class polinom;

class pereche
{
    double coeficient;
    unsigned exponent;

    friend class polinom;

public:pereche *next;
    pereche(){};
    pereche(double c,unsigned e)
    {
        coeficient=c;
        exponent=e;
        next=NULL;
    };
    pereche(pereche &p)
    {
        coeficient =p.getc();
        exponent=p.gete();
        next=NULL;
    }
    friend std::ostream& operator<< (std::ostream &out, const pereche &p);
    friend std::istream& operator>> (std::istream &in, pereche &p);
    double getc(){return coeficient;};
    unsigned gete(){return exponent;};
    void setc(double c)
    {
        if(isalpha(c))
            cout<<"Fail set c";
        else
            coeficient=c;
    };
    void sete(unsigned e)
    {
        if(isalpha(e))
            cout<<"Fail sete";
        else
            exponent=e;
    };
};
std::ostream& operator<< (std::ostream &out, const pereche &p)
{
    out <<p.coeficient<<"*x^"<<p.exponent;
    return out;
}
std::istream& operator >>(std::istream &in, pereche &p)
{
   // cout<<"coeficientul:";
    in>>p.coeficient;
    //cout<<"exponentul:";
    in>>p.exponent;
    return in;
}
class polinom
{
pereche *p;
public:
    ~polinom()
    {
        if(p!=NULL)
        p->next=NULL;
    }
    polinom (){p=NULL;};
    polinom(pereche *q)
    {
        p=q;
    }
    polinom(double c,unsigned e)
    {
        p=new pereche(c,e);
    };
    polinom(const polinom &pol)
    {
        pereche *e,*c,*d;
        int ok=0;
        d=pol.p;
        while(d!=NULL)
        {

            e=new pereche(d->getc(),d->gete());
            if(ok==0)
            {
                ok=1;
                c=e;
                p=c;
            }
            else
            {
                c->next=e;
                c=c->next;
                c->next=NULL;
            }
            d=d->next;
        }
    };
    pereche* getp(){return p;};
    void calcpunct(int n);
    void ordonare();
    void ordonareinversa();
    void mergepol();        //scapa de perechi cu acelasi exponent
    void szero();       //scapa de perechi cu coeficientul 0
    pereche & operator[](const int n);
    friend std::ostream& operator<< (std::ostream &out, const polinom &p);
    friend std::istream& operator>> (std::istream &in, polinom &p);
    friend polinom operator+(const polinom &p1,const polinom &p2);
    friend polinom operator-(const polinom &p1,const polinom &p2);
    friend polinom operator*(const polinom &p1,const polinom &p2);
    friend polinom operator/(const polinom &p1,const polinom &p2);
    friend polinom operator%(const polinom &p1,const polinom &p2);
};
void polinom ::szero()
{
    pereche *r,*q,*zero;
    zero=new pereche(0,0);
    int ok=0;
    q=p;
    r=p->next;
    while(r!=0)
    {

        ok=0;
        if(r->coeficient==0)
        {
            if(r->next==NULL)
            {

                q->next=NULL;
                delete r;
                break;
            }
            else
            {
                q->next=r->next;

                delete r;

                r=q;

                ok=1;
            }
        }
        if(ok==0)
            q=q->next;

        r=r->next;

    }
    if(p->coeficient==0)
        if(p->next==NULL)
            p=zero;
        else
        {
            p=p->next;
        }
}
std::ostream& operator<< (std::ostream &out, const polinom &p)
{

    pereche *r;
    r=p.p;
    if(p.p==NULL)
    {
        cout<<"nimic";
        return out;
    }
    else
    {
    while(r->next!=NULL)
    {
        cout <<*(r)<<" + ";
        r=r->next;
    }
    cout <<*(r);
    }

    return out;
}
std::istream& operator>> (std::istream &in, polinom &p)
{
    int a,i;
    pereche q,*r,*t;
    in>>a;
    for(i=0;i<a;i++)
    {

        in>>q;
        t=new pereche(q);
        if(i==0)
        {
            p.p=t;
            r=p.p;
        }
        else
        {
            r->next=t;
            r=r->next;
        }

    }
    r->next=NULL;
    return in;
}
void polinom ::calcpunct(int n)
{
    long s=0,pn;
    int i;
    pereche *r;
    r=p;
    while(r!=NULL)
    {
        pn=n;
        for(i=0;i<r->gete();i++)
            pn=pn*n;
        s=s+pn*r->getc();
        r=r->next;
    }
    cout<<s;
}
void polinom ::ordonare()
{
    pereche *r;
    r=p;
    int ordonat=0;
    unsigned e;
    double c;
    while(ordonat!=1)
    {
        r=p;
        ordonat=1;

        while(r->next!=NULL)
        {
            if(r->gete() > r->next->gete())
            {
                e=r->gete();
                c=r->getc();
                r->setc(r->next->getc());
                r->sete(r->next->gete());
                r->next->setc(c);
                r->next->sete(e);
                ordonat=0;
            }
            r=r->next;
        }
       // cout<<"Y";
    }
}
void polinom ::ordonareinversa()
{
    pereche *r;
    r=p;
    int ordonat=0;
    unsigned e;
    double c;
    while(ordonat!=1)
    {
        r=p;
        ordonat=1;

        while(r->next!=NULL)
        {
            if(r->gete() < r->next->gete())
            {
                e=r->gete();
                c=r->getc();
                r->setc(r->next->getc());
                r->sete(r->next->gete());
                r->next->setc(c);
                r->next->sete(e);
                ordonat=0;
            }
            r=r->next;
        }
       // cout<<"Y";
    }
}
void polinom:: mergepol()
{
    pereche *r;
    r=p;
    while(r->next!=NULL)
    {

        while(r->next!=NULL && r->gete()==r->next->gete())
        {
                r->setc(r->getc()+r->next->getc());
                if(r->next->next!=NULL)
                    r->next=r->next->next;
                else
                    r->next=NULL;

        }
        if(r->next!=NULL)
            r=r->next;
        else
            break;
    }
}
polinom operator+(const polinom &p1,const polinom &p2)
{
    polinom s;
    pereche *r1,*r2,*c,*r,*rc;
    int i=0;
    r1=p1.p;
    r2=p2.p;
    while(r1!=NULL && r2!=NULL)
    {
        if(r1->gete()==r2->gete())
        {
            c=new pereche(r1->getc()+r2->getc(),r1->gete());
            r1=r1->next;
            r2=r2->next;
        }
        else
            if(r1->gete()>r2->gete())
            {
                c=new pereche(*(r2));
                r2=r2->next;
            }
            else
            {
                c=new pereche(*(r1));
                r1=r1->next;
            }
        if(i==0)
        {
            i=1;
            r=c;
            rc=r;
            r->next=NULL;
        }
        else
        {
            r->next=c;
            r=r->next;
            r->next=NULL;
        }
    }
    while(r1!=NULL)
    {
        c=new pereche(*(r1));
        r1=r1->next;
        if(i==0)
        {
            i=1;
            r=c;
            rc=r;
            r->next=NULL;

        }
        else
        {
            r->next=c;
            r=r->next;
            r->next=NULL;
        }
    }
    while(r2!=NULL)
    {
        c=new pereche(*(r2));
        r2=r2->next;
        if(i==0)
        {
            i=1;
            r=c;
            rc=r;
            r->next=NULL;

        }
        else
        {
            r->next=c;
            r=r->next;
            r->next=NULL;
        }
    }
    s.p=rc;
    s.ordonare();
    s.mergepol();
    s.szero();
    //cout<<p1<<endl<<p2<<endl;
    return s;
}
polinom operator-(const polinom &p1,const polinom &p2)
{
    polinom s;
    pereche *r1,*r2,*c,*r,*rc;
    int i=0;
    r1=p1.p;
    r2=p2.p;
    while(r1!=NULL && r2!=NULL)
    {
        if(r1->gete()==r2->gete())
        {
            c=new pereche(r1->getc()-r2->getc(),r1->gete());
            r1=r1->next;
            r2=r2->next;
        }
        else
            if(r1->gete()>r2->gete())
            {
                c=new pereche(*(r2));
                c->setc(-1*c->getc());
                r2=r2->next;
            }
            else
            {
                c=new pereche(*(r1));
                r1=r1->next;
            }
        if(i==0)
        {
            i=1;
            r=c;
            rc=r;
            r->next=NULL;
        }
        else
        {
            r->next=c;
            r=r->next;
            r->next=NULL;
        }
    }
    while(r1!=NULL)
    {
        c=new pereche(*(r1));
        r1=r1->next;
        if(i==0)
        {
            i=1;
            r=c;
            rc=r;
            r->next=NULL;
        }
        else
        {
            r->next=c;
            r=r->next;
            r->next=NULL;
        }
    }
    while(r2!=NULL)
    {
        c=new pereche(*(r2));
        c->setc(-1*c->getc());
        r2=r2->next;
        if(i==0)
        {
            i=1;
            r=c;
            rc=r;
        }
        else
        {
            r->next=c;
            r=r->next;
            r->next=NULL;
        }
    }
    s.p=rc;
    s.ordonare();
    s.mergepol();
    s.szero();
    return s;
}
polinom operator*(const polinom &p1,const polinom &p2)
{
    polinom s;
    pereche *r1,*r2,*r,*c,*rc;
    int i=0;
    r2=p2.p;
    while(r2!=NULL)
    {
        r1=p1.p;
        while(r1!=NULL)
        {
            r=new pereche(r2->getc()*r1->getc(),r2->gete()+r1->gete());
            if(i==0)
            {
                rc=r;
                c=r;
                i=1;
            }
            else
            {
                c->next=r;
                c=c->next;
            }
            r1=r1->next;
        }
        r2=r2->next;
    }
    s.p=rc;
    s.ordonare();
    s.mergepol();
    s.szero();
    return s;
}
polinom operator/(const polinom &p1,const polinom &p2)
{
    polinom catul,restul(p1),test(p2);
    pereche *dempartitul,*impartitorul,*element,*inceputul,*ultimulele,*ult,*elescazut,*parcurgere;
    int i=0,j=0;
    unsigned exp;
    int co,grad=0;
    //test daca p2.p e 0

    test.szero();
    if(test.p->next==NULL && test.p->getc()==0 && test.p->gete()==0)
    {
        cout<<"EROR NU SE POATE IMPARTI CU 0"<<"\n";
        return 0;
    }
    //ordornarea inversa
    test.ordonareinversa();
    restul.ordonareinversa();
    //impartirea
    dempartitul=restul.p;
    impartitorul=test.p;
    while(dempartitul->gete()>=impartitorul->gete())
    {

        exp=dempartitul->gete()-impartitorul->gete();
        co=dempartitul->getc()/impartitorul->getc();
        if(exp==0)
        {
            if(grad==0)
            {
                grad=1;
            }
            else
                break;
        }
        //construire cat

        element=new pereche(co,exp);
        if(i==0)
        {
            i=1;
            ultimulele=element;
            inceputul=ultimulele;
        }
        else
        {
            ultimulele->next=element;
            ultimulele=ultimulele->next;
        }

        //construire rest

        ult=dempartitul;
        while(ult->next!=NULL)
            ult=ult->next;
        parcurgere=impartitorul;
        while(parcurgere!=NULL)
        {
            elescazut=new pereche(-1*(parcurgere->getc()*co),parcurgere->gete()+exp);
            ult->next=elescazut;
            ult=ult->next;
            parcurgere=parcurgere->next;
        }

        restul.ordonareinversa();
        restul.mergepol();
        restul.szero();
        dempartitul=restul.p;

    }
    catul.p=inceputul;
    catul.ordonare();
    return catul;
}
polinom operator%(const polinom &p1,const polinom &p2)
{
    polinom r1(p1/p2);
    polinom r2(r1*p2);
    polinom restul(p1-r2);
    return restul;
}
pereche& polinom::operator[](const int n)
{
    if(n==0)
         return *(p);
    else
    {
    pereche *p1;
    p1=p;
    int i;
    for(i=0;i<n;i++)
        p1=p1->next;
    return *(p1);
    }
}
    int main()
{

    polinom p1,p2,zero(0,0);
    int i=1,punct,ok=0;
    while(i)
    {
        cout<<"1)citire fisier\n2)citire tastatura\n3)afisare polinom (pol 1)\n4)calcularea intr-un punct (pol 1)\n5)suma\n6)diferenta\n7)produsul\n8)catul\n9)restul\n10)afisarea unui element\n11)impartire cu 0\n";
        cin>>i;

        switch(i)
        {
        case 1:
            {
                ifstream fin;
                fin.open("pol.text");
                if(fin.is_open())
                {
                    fin>>p1;
                    fin>>p2;
                    ok=1;
                    fin.close();
                    p1.ordonare();
                    p2.ordonare();
                }
                else
                    cout<<"eroare la deschiderea fisierului";
                break;
            }
        case 2:
            {
               cout<<"introdu cate elemente are polinomul 1 si apoi elementele acestuia";
               cin>>p1;
               cout<<"introdu cate elemente are polinomul 2 si apoi elementele acestuia";
               cin>>p2;
               ok=1;
               p1.ordonare();
               p2.ordonare();
            }
        case 3:
            {
               if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {
               cout<<p1<<"\n"<<p2<<"\n";
               }
               break;
            }
        case 4:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {
                cout<<"punctul:";
                cin>>punct;
                p1.calcpunct(punct);
                cout<<"\n";
               }
                break;
            }
        case 5:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {
                polinom s(p1+p2);
                cout<<s<<"\n";

                }
                break;
            }
        case 6:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {

                cout<<p1-p2<<"\n";

                }
                break;
            }
        case 7:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {

                cout<<p1*p2<<"\n";

               }
                break;
            }
        case 8:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {

                cout<<p1/p2<<"\n";

               }
                break;
            }
        case 9:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {

                cout<<p1%p2<<"\n";

               }
                break;
            }
        case 10:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {
                cout<<"al catelea element:";
                cin>>punct;
               }
                cout<<p1[punct]<<"\n";
                break;
            }
        case 11:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {
                p1/zero;
               }
                break;
            }
        default:
            {
                cout<<"nu meriti sa folosesti programul!!!";
                break;
            }
        }
    }

}
