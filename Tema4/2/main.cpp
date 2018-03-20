#include <iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
class node
 {
  static node *head;
  node *next;
  node *ant;
  char *interpret;
  char *melodie;
  public:

  node (char *a,char *b,node *c);
  ~node(void);
  node* getnext();
  char* getmelodie();
  char* getintrpret();
  void afisare();
  void display_all ();
  void citireAlbum ();
  void modificare();
  void ordonare();
  void stergere();
  void copiere(char *p,char *p1);
  void setnext(node *n);
  void setan(node *n);
 };
 node *node :: head = NULL;
 void node::setan(node *n)
 {
     ant=n;
 }
 node::~node(void)
 {
     delete interpret;
     delete melodie;
     //delete next;
 }
 void node::setnext(node *n)
 {
     next=n;
 }
 char* node:: getmelodie()
 {
     return melodie;
 }
 char* node:: getintrpret()
 {
     return interpret;
 }
 void node::copiere(char *p,char *p1)
 {
     strcpy(interpret,p1);
     strcpy(melodie,p);
 }
 node* node :: getnext()
 {
     return next;
 }
 void node::afisare()
 {
     cout<<this->melodie<<" "<<this->interpret<<"\n";
 }
 node :: node(char *ptr, char *ptr1,node *ante)
 {
         interpret=new char[strlen(ptr)+1];
         strcpy(interpret,ptr);
         melodie=new char[strlen(ptr1)+1];
         strcpy(melodie,ptr1);
         ant=ante;
         next=0;
 }
 void node :: display_all ()
 {
    node *r;
    r=head;
    while(r->getnext()!=0)
    {
        r->afisare();
        r=r->getnext();
    }
 }
 void node:: citireAlbum ()
 {
     FILE *f;
     char ptr[25],ptr1[25];
     f=fopen("f.text","r");
     while(!feof(f))
     {
         fscanf(f,"%25s",&ptr);
         fscanf(f,"%25s",&ptr1);
         node *p;

        if(head==NULL)
        {
            p=new node(ptr1,ptr,0);
            head=p;
        }
        else
        {
            node *r;
            r=head;
            while(r->getnext()!=0)
            {
                r=r->getnext();
            }
            p=new node(ptr1,ptr,r);
            r->next=p;
        }
     }
 }
 void node:: modificare()
 {
     char p[25],p1[25];
     cout<<"cantecul:";
     cin>>p;
    node *r;
    int ok=0;
    r=head;
    while(r->getnext()!=0)
    {
        if(strcmp(r->getmelodie(),p)==0)
        {
            cout<<"noa melodie:";
            cin>>p;
            cout<<"noul interpret:";
            cin>>p1;
            r->copiere(p,p1);
            ok=1;
            break;
        }
        r=r->getnext();
    }
    if(ok==0)
        cout<<"melodia nu a fost gasita\n";
 }
 void node::ordonare()
 {
     node *r;
     char m[25],i[25];
    int ordonat=0;
    while(ordonat!=1)
    {
        ordonat=1;
        r=head;
        while(r->getnext()->getnext()!=0)
        {
            if(strcmp(r->getmelodie(),r->getnext()->getmelodie())<0)
            {
                ordonat=0;
                strcpy(m,r->getmelodie());
                strcpy(i,r->getintrpret());
                //cout<<r->getnext()->getmelodie()<<" "<<r->getnext()->getintrpret()<<"\n";
                r->copiere(r->getnext()->getmelodie(),r->getnext()->getintrpret());
                r->getnext()->copiere(m,i);
            }
            r=r->getnext();

        }
    }
 }
 void node::stergere()
 {
    char p[25];
    cout<<"cantecul:";
    cin>>p;
    node *r,*q;
    int ok=0;
    r=head;
    while(r->getnext()!=0)
    {
        if(strcmp(r->getmelodie(),p)==0)
        {
            q->setnext(r->getnext());
            r->getnext()->setan(q);
            delete r;
            ok=1;
            break;
        }
        q=r;
        r=r->getnext();
    }
    if(ok==0)
        cout<<"melodia nu a fost gasita\n";
 }
 int main()
 {
        node *i;
        i->citireAlbum();
        i->stergere();
        i->display_all();
 }
