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

/*double abs(double x)//wartość bezwzględna
{
   return 
}*/






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
double min=0, mins=0,minn=0;//do obliczania okresu

//zmienne przełączniki
bool s=0;

//zmienne plikowe
fstream plik;

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
           T=(i-1) *dt;
           s=1;//zaliczyliśmy już okres, nie robimy tego więcej
           //cout << " T [ "<<i<<" ] = " << T<< "      ;      min = " << min<<endl;
        }
      }
   }

   plik.close();//zamknięcie pliku 
} else cout << "Dostep do pliku zostal zabroniony!" << endl;

cout << "Okres T = "<< T<<endl; 

//getchar();






}


/*double fp(double t, double p, double q){
double k=1.0;
return -k*q;}

double fq(double t, double p, double q){
double m=1.0;
return p/m;}


double dp(double t, double y, double z, double dt){//runge_kutta 4 rzędu
double k1,k2,k3,k4;
k1=fp(t,y,z);
k2=fp(t+0.5*dt,y+0.5*dt*k1,z+0.5*dt*k1);
k3=fp(t+0.5*dt,y+0.5*dt*k2,z+0.5*dt*k2);
k4=fp(t+dt,y+dt*k3,z+dt*k3);
return (1.0/6.0)*(k1+2*k2+2*k3+k4)*dt;
}

double dq(double t, double y, double z,double dt){//runge_kutta 4 rzędu
double k1,k2,k3,k4;
k1=fq(t,y,z);
k2=fq(t+0.5*dt,y+0.5*dt*k1,z+0.5*dt*k1);
k3=fq(t+0.5*dt,y+0.5*dt*k2,z+0.5*dt*k2);
k4=fq(t+dt,y+dt*k3,z+dt*k3);
return (1.0/6.0)*(k1+2*k2+2*k3+k4)*dt;
}*/
