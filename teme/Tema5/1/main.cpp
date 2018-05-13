#include <iostream>
#include <string.h>
using namespace std;
class lista
{
    char *ele;
    lista *next;
    friend void intro(class CD &cd);
public:
    lista(int n)
    {
        ele=new char(n);
        next=NULL;
    };
    lista()
    { };
};
class CD
{
   char *interpret;
   char *titlu;
   lista *melodi;
   public:
       friend void intro(class CD &cd);
};
void intro(class CD *cd)
{
     char c[100];
     lista *initial,*e;
     int n.m;
     cout<<"cate CD:";
     cin>>n;
     for(int i=0;i<n;i++)
     {
        cout<<"interpretul:";
        cin>>c;
        cd.interpret=new char(strlen(c)+1);
        strcpy(cd.interpret,c);
        cout<<"titlul:";
        cin>>c;
        cd->titlu=new char(strlen(c)+1);
        strcpy(cd->titlu,c);
        cout<<"cate melodi:";
        cin>>n;
        for(int j=0;j<n;j++)
        {
            cout<<"melodia "<<j+1<<":";
            cin>>c;
            e=new struct lista(strlen(c)+1);
            strcpy(e->ele,c);
            e->next=NULL;
            if(j==0)
            {
                initial=e;
                cd->melodi=e;
            }
            else
            {
            cd->melodi->next=e;
            cd->melodi=cd->melodi->next;
            }
        }
        cd->melodi=initial;
     }
}
void
int main()
{
    CD *c;
    intro(c);
    return 0;
}
