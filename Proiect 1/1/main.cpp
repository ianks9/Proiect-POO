#include <iostream>
#include<fstream>
using namespace std;
class polinom;

class pereche
{
    double coeficient;
    unsigned exponent;
    friend class polinom;

public:
    pereche(){};
    pereche(double c,unsigned e)
    {
        coeficient=c;
        exponent=e;
    };
    friend std::ostream& operator<< (std::ostream &out, const pereche &p);
    friend std::istream& operator>> (std::istream &in, pereche &p);
    double getc(){return coeficient;};
    unsigned gete(){return exponent;};
    void setc(double c){coeficient=c;};
    void sete(unsigned e){exponent=e;};
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


    pereche p;
    polinom *next;
public:
    ~polinom()
    {
        next=NULL;
    }
    polinom (){};
    polinom(pereche q)
    {
        p=q;
        next=NULL;
    }
    polinom(double c,unsigned e)
    {
        p.setc(c);
        p.sete(e);
        next=NULL;
    };
    polinom getnext();
    pereche getp(){return p;};
    void calcpunct(int n);
    void ordonare();
    void ordonareinversa();
    polinom mergepol();        //scapa de perechi cu acelasi exponent
    polinom* szero();       //scapa de perechi cu coeficientul 0
    polinom & operator[](const int n);
    friend std::ostream& operator<< (std::ostream &out, const polinom &p);
    friend std::istream& operator>> (std::istream &in, polinom &p);
    friend polinom operator+(const polinom p1,const polinom p2);
    friend polinom operator-(const polinom p1,const polinom p2);
    friend polinom operator*(const polinom p1,const polinom p2);
    friend polinom operator/(const polinom p1,const polinom p2);
    friend polinom operator%(const polinom p1,const polinom p2);
};
polinom polinom::  getnext()
{
    return *next;
}
polinom* polinom ::szero()
{
    polinom *r,*q,*cr;
    int ok=0;
    r=new polinom(p);
    r->next=next;
    q=r;
    cr=r;
    r=r->next;
    while(r!=0)
    {
        ok=0;
        if(r->p.getc()==0)
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
    if(cr->p.getc()==0)
        if(cr->next==NULL)
            return 0;
        else
            return cr->next;
    else
        return cr;
}
std::ostream& operator<< (std::ostream &out, const polinom &p)
{

    pereche t(0,0);
    polinom cp(t);
    cp=p;
    while(cp.next!=NULL)
    {
        cout <<cp.p<<" + ";
        cp=*(cp.next);
    }
    cout <<cp.p;
    return out;
}
std::istream& operator>> (std::istream &in, polinom &p)
{
    int a,i;
    pereche q;
    polinom *t,*r;
    in>>a;
    for(i=0;i<a;i++)
    {

        in>>q;
        t=new polinom(q);
        if(i==0)
        {
            p=*(t);
            r=&(p);
        }
        else
        {
            r->next=t;
            r=r->next;
        }

    }
    return in;
}
void polinom ::ordonare()
{
    polinom *r,*rc;
    r=new polinom(p);
    r->next=next;
    rc=r;
    int ordonat=0;
    unsigned e;
    double c;
    while(ordonat!=1)
    {
        r=rc;
        ordonat=1;

        while(r->next!=NULL)
        {
            if(r->p.gete() > r->next->p.gete())
            {
                e=r->p.gete();
                c=r->p.getc();
                r->p.setc(r->next->p.getc());
                r->p.sete(r->next->p.gete());
                r->next->p.setc(c);
                r->next->p.sete(e);
                ordonat=0;
            }
            r=r->next;
        }
    }
    p.setc(rc->p.getc());
    p.sete(rc->p.gete());
    delete rc;
}
void polinom ::ordonareinversa()
{
    polinom *r,*rc;
    r=new polinom(p);
    r->next=next;
    rc=r;
    int ordonat=0;
    unsigned e;
    double c;
    while(ordonat!=1)
    {
        r=rc;
        ordonat=1;

        while(r->next!=NULL)
        {
            if(r->p.gete() < r->next->p.gete())
            {
                e=r->p.gete();
                c=r->p.getc();
                r->p.setc(r->next->p.getc());
                r->p.sete(r->next->p.gete());
                r->next->p.setc(c);
                r->next->p.sete(e);
                ordonat=0;
            }
            r=r->next;
        }
    }
    p.setc(rc->p.getc());
    p.sete(rc->p.gete());
    delete rc;
}
polinom polinom:: mergepol()
{
    polinom *r,*rc;
    r=new polinom(p);
    r->next=next;
    rc=r;
    while(r->next!=NULL)
    {

        while(r->next!=NULL && r->p.gete()==r->next->p.gete())
        {
                r->p.setc(r->p.getc()+r->next->p.getc());
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
    return *(rc);
}
polinom operator+(const polinom p1,const polinom p2)
{
    polinom s,*r1,*r2,*c,*r,*rc1,*rc2;
    int i=0;
    r1=new polinom(p1.p);
    r1->next=p1.next;
    r2=new polinom(p2.p);
    r2->next=p2.next;
    rc1=r1;
    rc2=r2;
    while(r1!=NULL && r2!=NULL)
    {
        if(r1->p.gete()==r2->p.gete())
        {
            c=new polinom(r1->p.getc()+r2->p.getc(),r1->p.gete());
            r1=r1->next;
            r2=r2->next;
        }
        else
            if(r1->p.gete()>r2->p.gete())
            {
                c=new polinom(r2->p);
                r2=r2->next;
            }
            else
            {
                c=new polinom(r1->p);
                r1=r1->next;
            }
        if(i==0)
        {
            i=1;
            s=*(c);
            r=&(s);
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
        c=new polinom(r1->p);
        r1=r1->next;
        if(i==0)
        {
            i=1;
            s=*(c);
            r=&(s);
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
        c=new polinom(r2->p);
        r2=r2->next;
        if(i==0)
        {
            i=1;
            s=*(c);
            r=&(s);
        }
        else
        {
            r->next=c;
            r=r->next;
            r->next=NULL;
        }
    }
    s.ordonare();
    return s;
}
polinom operator-(const polinom p1,const polinom p2)
{
    polinom s,*r1,*r2,*c,*r,*rc1,*rc2;
    int i=0;
    r1=new polinom(p1.p);
    r1->next=p1.next;
    r2=new polinom(p2.p);
    r2->next=p2.next;
    rc1=r1;
    rc2=r2;
    while(r1!=NULL && r2!=NULL)
    {
        if(r1->p.gete()==r2->p.gete())
        {
            c=new polinom(r1->p.getc()-r2->p.getc(),r1->p.gete());
            r1=r1->next;
            r2=r2->next;
        }
        else
            if(r1->p.gete()>r2->p.gete())
            {
                c=new polinom(r2->p);
                c->p.setc(-1*c->p.getc());
                r2=r2->next;
            }
            else
            {
                c=new polinom(r1->p);
                r1=r1->next;
            }
        if(i==0)
        {
            i=1;
            s=*(c);
            r=&(s);
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
        c=new polinom(r1->p);
        r1=r1->next;
        if(i==0)
        {
            i=1;
            s=*(c);
            r=&(s);
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
        c=new polinom(r2->p);
        c->p.setc(-1*c->p.getc());
        r2=r2->next;
        if(i==0)
        {
            i=1;
            s=*(c);
            r=&(s);
        }
        else
        {
            r->next=c;
            r=r->next;
            r->next=NULL;
        }
    }
    s.ordonare();
    delete rc1;
    delete rc2;
    return s;
}
polinom operator*(const polinom p1,const polinom p2)
{
    polinom s(0,0),*r1,*r2,*c,*r,*cc,*rc1,*rc2;
    r2=new polinom(p2.p);
    r2->next=p2.next;
    rc2=r2;
    while(r2!=NULL)
    {
        r1=new polinom(p1.p);
        r1->next=p1.next;
        rc1=r1;
        c=new polinom(r2->p.getc()*r1->p.getc(),r2->p.gete()+r1->p.gete());
        cc=c;
        r1=r1->next;
        while(r1!=NULL)
        {
            r=new polinom(r2->p.getc()*r1->p.getc(),r2->p.gete()+r1->p.gete());
            cc->next=r;
            cc=r;
            r1=r1->next;
        }
        s=s+*(c);
        r2=r2->next;
        delete rc1;
    }
    delete rc2;
    return s;
}
polinom operator/(const polinom p1,const polinom p2)
{
    polinom s(0,0),*r1,*r2,*c,c1,c2,*rc1,*rc2;
    unsigned exp;
    double co;
    r1=new polinom(p1.p);
    r1->next=p1.next;
    rc1=r1;
    r2=new polinom(p2.p);
    r2->next=p2.next;
    rc2=r2;
    r1->ordonareinversa();
    r2->ordonareinversa();
    r2=r2->szero();
    if(r2==NULL)
    {
        cout<<"EROR";
        return s;
    }
    while(r1->p.gete()>=r2->p.gete())
    {
        exp=r1->p.gete()-r2->p.gete();
        co=r1->p.getc()/r2->p.getc();
        c=new polinom(co,exp);
        s=s+*(c);
        c1=*(r1);
        c2=*(r2);
        c1=c1-*(c)*c2;
        *(r1)=c1;
        r1=r1->szero();
        r1->ordonareinversa();
    }
    s.ordonare();
    delete rc1;
    delete rc2;
    return s;
}
polinom operator%(const polinom p1,const polinom p2)
{
    polinom s(0,0),c;
    c=p2*(p1/p2);
    c.ordonare();
    s=p1-c;
    s=*(s.szero());
    return s;
}
void polinom ::calcpunct(int n)
{
    long s=0,pn;
    int i;
    polinom *r,*rc;
    r=new polinom(p);
    r->next=next;
    rc=r;
    while(r!=NULL)
    {
        pn=n;
        for(i=0;i<r->p.gete();i++)
            pn=pn*n;
        s=s+pn*r->p.getc();
        r=r->next;
    }
    cout<<s;
    delete rc;
}
polinom& polinom::operator[](const int n)
{
    if(n==0)
            ;
    else
    {
    polinom *p1,*pc1;
    p1=new polinom(p);
    p1->next=next;
    pc1=p1;
    int i;
    for(i=0;i<n;i++)
        p1=p1->next;
    delete pc1;
    return *(p1);
    }
}
int main()
{

    polinom p1,p2,s,zero(0,0);
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
                }
                else
                    cout<<"eroare la deschiderea fisierului";
                break;
            }
        case 2:
            {
               cout<<"introdu cat elemente are polinomul 1 si elementele acestuia";
               cin>>p1;
               cout<<"introdu cat elemente are polinomul 2 si elementele acestuia";
               cin>>p2;
               ok=1;
            }
        case 3:
            {
               if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {
               cout<<p1<<"\n";
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
                s=p1+p2;
                s=s.mergepol();
                s=*(s.szero());
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
                s=p1-p2;
                s=s.mergepol();
                s=*(s.szero());
                cout<<s<<"\n";
                }
                break;
            }
        case 7:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {
                s=p1*p2;
                s=s.mergepol();
                s=*(s.szero());
                cout<<s<<"\n";
               }
                break;
            }
        case 8:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {
                s=p1/p2;
                s=s.mergepol();
                s=*(s.szero());
                cout<<s<<"\n";
               }
                break;
            }
        case 9:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {
                s=p1%p2;
                s=s.mergepol();
                s=*(s.szero());
                cout<<s<<"\n";
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
                cout<<p1[punct].getp()<<"\n";
                break;
            }
        case 11:
            {
                if(ok==0)
                cout<<"NU sa citit niciun polinom";
               else
               {
                s=p1/zero;
               }
                break;
            }
        }
    }

}
