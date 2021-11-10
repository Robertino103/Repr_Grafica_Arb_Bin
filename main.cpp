#include <iostream>
#include <math.h>
#include <graphics.h>
#include <winbgim.h>
#include <string.h>

#define colorcerc GREEN
#define colorline WHITE
#define WindowWidth 800
#define WindowHeight 600

using namespace std;

struct nod{int info;
           nod *st;
           nod *dr;
           int coloana;};

void creare(nod*&a,int x)
{
    if(x!=0)
    {
        a = new nod;
        a->info = x;
        a->st = a->dr = NULL;
        int val;
        cout << "Fiul Stanga lui " << x << " este: ";
        cin >> val;
        cout << '\n';
        creare(a->st,val);
        cout << "Fiul Dreapta lui " << x << " este: ";
        cin >> val;
        cout << '\n';
        creare(a->dr,val);
    }
}

int k=0;

void inordine(nod *arbore)
{
    if(arbore!=NULL)
    {
        inordine(arbore->st);
        arbore->coloana=++k;
        inordine(arbore->dr);
    }
}


void linie(int x1,int y1,int x2,int y2)
{
    int d=8,h=8; // d lungimea sagetii, h inaltimea sagetii
    line(x1,y1,x2,y2);
    int dx = x2 - x1, dy = y2 - y1;
    double D =sqrt(dx*dx + dy*dy);
    double xm = D - d, xn = xm, ym = h, yn = -h, x;
    double sin = dy / D, cos = dx / D;

    x = xm*cos - ym*sin + x1;
    ym = xm*sin + ym*cos + y1;
    xm = x;

    x = xn*cos - yn*sin + x1;
    yn = xn*sin + yn*cos + y1;
    xn = x;
    line(xm,ym,x2,y2);
    line(xn,yn,x2,y2);
}

int nrNiveluri(nod *a)
{
    if(a==NULL) return 0;
    else {int n1=nrNiveluri(a->st);
          int n2=nrNiveluri(a->dr);
          return 1+max(n1,n2);}
}

int nrColoane(nod *a)
{
    if(a==NULL) return 0;
    else {int n1=nrColoane(a->st);
          int n2=nrColoane(a->dr);
          return 1+n1+n2;}
}

int winw=WindowWidth, winh=WindowHeight;

void centrucasuta(int n,int m,int i,int j,int &xc,int &yc) // winw/winh=window width/height; n si m sunt indicii numarului maxim de casute; i si j indicii casutei careia i se cauta centrul;
{
    int ki,kj;
    ki=winw/m;
    kj=winh/n;
    xc=(j*ki)-(ki/2);
    yc=(i*kj)-(kj/2);
}

void deseneaza(int nmax,int mmax, int n,int linie,int coloana,int &xc,int &yc)
{
    centrucasuta(nmax,mmax,linie,coloana,xc,yc);
    setcolor(colorcerc);
    circle(xc,yc,30);
    setcolor(colorline);
    char buffer[16]={0};
    itoa(n,buffer,10);
    outtextxy(xc-8,yc-8,buffer);
}

int xc1=0,yc1=0;

void desenarb(int nmax,int mmax,nod *a,int niv)
{
    int xc,yc;
    if(a!=NULL)
    {
        deseneaza(nmax,mmax,a->info,niv,a->coloana,xc,yc);
        desenarb(nmax,mmax,a->st,niv+1);
        if((xc1*yc1!=0)&&(a->st!=NULL)) linie(xc-22,yc+22,xc1+22,yc1-22);
        desenarb(nmax,mmax,a->dr,niv+1);
        if((xc1*yc1!=0)&&(a->dr!=NULL)) linie(xc+22,yc+22,xc1-22,yc1-22);
        deseneaza(nmax,mmax,a->info,niv,a->coloana,xc1,yc1);
    }
}

int main()
{
    nod *a;
    int radacina,nmax,mmax;
    cout<<"Radacina : "; cin>>radacina;
    cout<<endl;
    creare(a,radacina);
    nmax=nrNiveluri(a);
    mmax=nrColoane(a);
    initwindow(WindowWidth,WindowHeight);
    inordine(a);
    desenarb(nmax,mmax,a,1);
    getch();
    closegraph();
    return 0;
}
