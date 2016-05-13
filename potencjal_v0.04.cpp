#include <iostream>  //strumienie
#include <math.h>    //matematyczne
#include <fstream>   //pliki
#include <cmath>     //abs

using namespace std;


double V(double q)//potnecjał
{
   return (q*q-4)*(q*q-q-0.4)*0.4;
   //return q*q; //potencjał treningowy, dla niego okres jest zgodny 
   //z wynikami obliczeń analitycznych
}

double fp(double q, double dq)//siła inaczej dp/dt = -dv/dq
{
   return -(V(q+dq/2)-V(q-dq/2))/dq;
}

double fq(double p)//prędkość inaczej dq/dt = p/m
{
   return p;//m=1.0
}




int main(){
  cout.precision(10);
  cout.setf(ios::fixed,ios::floatfield);

//część deklaracyjna zmiennych

//podstawowe parametry
double tp=0.0;
double tk=8.0;
double dt=0.001;
double dq=0.0001;
double eps=1e-2;

//parametry pomocnicze
int N=(int)((tk-tp)/dt);

//tablice
double p[N],q[N],t[N];

//zmienne do wyliczenia
double T=0;

//zmienne pomocnicze
bool s=0;//do obliczania okresu
double min=0, mins=0,minn=0;
double cP=0, cQ=0;//do całkowania
int imax;

//zmienne plikowe
fstream plik;

//zmienne do spline
int np=9;//liczba punktkow
double f[]= {80, 20, 10, -4.4, 0.0, 5.1, 5.02, -7.2, 99.1};//wartości
double x[]={-9.9, -8.0, -4.3, -2.1, 0.01, 2e-1, 4.41, 5.0, 8.7};//wspolrzedne

double test;
test=-7.0;
int i=0;
do{
i++;
}
while(test<x[i+1] && test>=x[i]);

cout << " i="<<i<<endl;


//otworzenie pliku
plik.open( "nazwa_pliku.txt", ios::out );

//ustawienia precyzji zapisu do pliku
  plik.precision(10);
  plik.setf(ios::fixed,ios::floatfield);

cout << "N="<< N<<endl;


//warunki początkowe
t[0]=0; p[0]=0; q[0]=2.5;

//jeśli uda się otworzyć plik
if( plik.good() == true )
{
   cout << "Uzyskano dostep do pliku!" << endl;
   plik << "Czas [s] " <<"             "<< "Położenie [m]" <<"           "<<"Pęd [kg m / s] " << endl;
   plik << t[0] <<"          "<< q[0] <<"             "<<p[0] << endl;
   for(int i=1; i<N; i++){//wykonaj pętlę w której wypełniane są tablice
     t[i]=t[i-1]+dt;
     p[i]=p[i-1]+fp(q[i-1],dq)*dt;
     q[i]=q[i-1]+fq(p[i-1])*dt;//oraz zapisywane są do pliku wyniki
     plik << t[i] <<"          "<< q[i] <<"            "<<p[i] << endl;
     //obliczanie okresu
     if(s==0)//jeśli nie zaliczyliśmy jeszcze okresu
     {
        mins=min;//przekazanie poprzedniego "minimum" (najstarszego)
        min=minn;//potencjalnie prawdziwe minimum o jeden krok wcześniejsze
        minn=((p[i]-p[0])*(p[i]-p[0]) + (q[i]-q[0])*(q[i]-q[0]));//obecna wartość
        if(min<mins and min < minn and min < eps) //ma być minimum i do tego bardzo małe
        {
           T=(i-1) *dt; //okres
           imax=(int)(((double)(i-1))/2.0); //maksymalny indeks przy całkowaniu
           s=1;//zaliczyliśmy już okres, nie robimy tego więcej
           //cout << " T [ "<<i<<" ] = " << T<< "      ;      min = " << min<<endl;
        }
      }
   }

   plik.close();//zamknięcie pliku 
} else cout << "Dostep do pliku zostal zabroniony!" << endl;

cout << "Okres T = "<< T<<endl;

//całkowanie 

cP=(0.5)*(p[0]+p[imax]);//wyrazy skrajne przed wejsciem w nastepna petle;
cQ=(0.5)*(q[0]+q[imax]);
for(int i=1;i<imax;i++)
{
   cP+=p[i]; cQ+=q[i];
};
cP*=dt; cQ*=dt;//z petli wyrzucac mozliwie duzo mnorzen





cout << "Całki P = " << cP << "    Q = " <<cQ <<endl;


}



