#include <iostream>
#include<fstream>
using namespace std;
int ma[100][26][100],sfin[100],stari[100],litere[26];
int starilenoi[100][100],strc[100],st[100];
void ord(int *p)
{
    int ord=0,a,i;
    while(ord==0)
    {
        ord=1;
        for(i=1;i<p[0];i++)
        {
            if(p[i]>p[i+1])
            {
                a=p[i];
                p[i]=p[i+1];
                p[i+1]=a;
                ord=0;
            }
        }
    }
}
int verificare(int *p,int ult)
{

    int i=0,j;
/*
    for(i=0;i<=5;i++)
        cout<<st[i]<<" ";
        cout<<"\n";
  */if(p[0]==0)
        return 0;
    for(j=0;j<=ult;j++)
    {
        while(p[i]==starilenoi[j][i])
        {
            if(p[i]==0)
            {
                if(p[i-1]!= starilenoi[j][i-1] || p[i-2]!= starilenoi[j][i-2])
                    break;
                cout<<" /"<<p[i-3]<<" "<<starilenoi[j][i-3];
                return 0;
            }
            i++;
        }

    }
/*
    for(i=0;i<=5;i++)
        cout<<st[i]<<" ";
        cout<<"\n";
*/
    return 1;
}
void copiere1(int *p,int ult)
{
    int i;
    for(i=0;i<=p[0];i++)
        starilenoi[ult][i]=p[i];
}
void copiere2(int *p,int ult)
{
    int i;

    for(i=1;i<=p[0];i++)
    {
        p[i]=0;
    }
    for(i=0;i<=starilenoi[ult][0];i++)
        p[i]=starilenoi[ult][i];
}
void initializare(int *p)
{
    int i;
    for(i=0;i<=100;i++)
            p[i]=0;
}
void starenoua(int *stc,char c,int &ult)
{
    int i,j,ok,k;
    /*
    for(i=0;i<=5;i++)
        cout<<stc[i]<<" ";
        cout<<"\n";
    */
    initializare(st);
    for(i=1;i<=stc[0];i++)
    {
            for(j=1;j<=ma[stc[i]][c-'a'][0];j++)
            {
                //cout<<ma[stc[i]][c-'a'][0]<<"\n";
                ok=0;
                for(k=1;k<=st[0];k++)
                {
                    if(ma[stc[i]][c-'a'][j]==st[k])
                    {
                        ok=1;
                        break;
                    }
                }
                if(ok==0)
                {
                    st[0]++;
                    st[st[0]]=ma[stc[i]][c-'a'][j];


                }
            }

    }
    ord(st);
    for(i=1;i<=5;i++)
        cout<<st[i]<<" ";

    if(verificare(st,ult))
    {
        cout<<"ADMIS";
        copiere1(st,ult);
        ult++;
    }
    cout<<"\n";
}
int main()
{
    FILE *fin,*fout;
    fin=fopen("citire.txt","r");
    fout=fopen("scriere.txt","w");

    int n,m,q,i,j,k,t1,t2,ok=0;
    char c;

    //citire stari
    fscanf(fin,"%d",&n);
    stari[0]=n;

    for(i=1;i<=n;i++)
    {
        fscanf(fin,"%d",&stari[i]);

    }
    //citire litere
    fscanf(fin,"%d",&m);
    fscanf(fin,"%c",&c);
    for(i=1;i<=m;i++)
    {
        fscanf(fin,"%c",&c);
        if(c>='a' && c<='z')
        litere[c-'a']=1;
        else
        {
          cout<<"EROR";
          return 0;
        }
        fscanf(fin,"%c",&c);
    }

    //starea initiala si stari finale
    fscanf(fin,"%d",&q);
    for(i=1;i<stari[0];i++)
        if(q==stari[i])
        {
            q=i;
            ok=1;
        }
    if(ok==0)
    {

    }
    fscanf(fin,"%d",&n);
    sfin[0]=n;
    for(i=1;i<=n;i++)
    {
        fscanf(fin,"%d",&sfin[i]);
    }
    //tranziti
    fscanf(fin,"%d",&n);
    for(i=0;i<n;i++)
    {

        fscanf(fin,"%d",&t1);
        fscanf(fin,"%c",&c);
        fscanf(fin,"%c",&c);
        fscanf(fin,"%d",&t2);
        for(j=1;j<=stari[0];j++)
            if(stari[j]==t1)
                break;
        for(k=1;k<=stari[0];k++)
            if(stari[k]==t2)
                break;

        ma[j][c-'a'][0]++;

        ma[j][c-'a'][ ma[j][c-'a'][0]]=k;
    }
    int actual=0,ultimul=1;
    strc[0]=1;
    strc[1]=q;
    copiere1(strc,0);

    while(actual<=ultimul)
    {

        for(i=1;i<=5;i++)
        cout<<strc[i]<<" ";
        cout<<"\n\n";

        for(i=0;i<=26;i++)
        {
            if(litere[i]==1)
            {
                starenoua(strc,i+'a',ultimul);
            }
        }
        actual++;
        copiere2(strc,actual);
         cout<<"\n";
        //cout<<" \n"<<ultimul<<" \n";
    }
/*

     for(i=0;i<=10;i++)
    {
        for(j=0;j<=5;j++)
                cout<<starilenoi[i][j]<<" ";
        cout<<"\n";
    }
   */
    fprintf(fout,"%d\n",ultimul);
    for(i=1;i<=ultimul;i++)
        fprintf(fout,"%d ",i);
    fprintf(fout,"\n%d\n",m);
    for(i=0;i<=26;i++)
    {
        if(litere[i]==1)
        {
            fprintf(fout,"%c ",i+'a');
        }
    }
    fprintf(fout,"\n1\n");

}
