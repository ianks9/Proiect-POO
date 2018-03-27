#include <iostream>
#include<fstream>
using namespace std;
class polinom;

class pereche
{
    double coeficient;
    unsigned exponent;


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

    friend class pereche;
    pereche p;
    polinom *next;
public:

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
    friend std::ostream& operator<< (std::ostream &out, const polinom &p);
    friend std::istream& operator>> (std::istream &in, polinom &p);
    friend polinom operator+(const polinom p1,const polinom p2);
    friend polinom operator-(const polinom p1,const polinom p2);
    friend polinom operator*(const polinom p1,const polinom p2);
    void ordonare();
};
polinom polinom::  getnext()
{
    return *next;
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
polinom operator+(const polinom p1,const polinom p2)
{
    polinom s,*r1,*r2,*c,*r;
    int i=0;
    r1=new polinom(p1.p);
    r1->next=p1.next;
    r2=new polinom(p2.p);
    r2->next=p2.next;

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
    polinom s,*r1,*r2,*c,*r;
    int i=0;
    r1=new polinom(p1.p);
    r1->next=p1.next;
    r2=new polinom(p2.p);
    r2->next=p2.next;

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
    return s;
}
polinom operator*(const polinom p1,const polinom p2)
{
    polinom s(0,0),*r1,*r2,*c,*r,*cc;
    r1=new polinom(p1.p);
    r1->next=p1.next;
    r2=new polinom(p2.p);
    r2->next=p2.next;
    while(r2!=NULL)
    {
        r1=new polinom(p1.p);
        r1->next=p1.next;
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
    }
    s.ordonare();
    return s;
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
}
int main()
{
    ifstream fin;
    fin.open("pol.text");
    polinom p1,p2,s;
    fin>>p1;
    fin>>p2;
    s=p1*p2;
    p1.ordonare();
    cout<<p1;
}
