#include <iostream>  //strumienie
#include <math.h>    //matematyczne
#include <fstream>   //pliki


using namespace std;


double V(double q)//potnecjał
{
   return (q*q-4)*(q*q-q-0.4)*0.4;
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

//parametry pomocnicze
int N=(int)((tk-tp)/dt);

//tablice
double p[N],q[N],t[N];

//zmienne do wyliczenia
double T;

//zmienne plikowe
fstream plik;

//otworzenie pliku
plik.open( "nazwa_pliku.txt", ios::out );
cout << "N="<< N<<endl;

if( plik.good() == true )
{
    cout << "Uzyskano dostep do pliku!" << endl;
    //tu operacje na pliku
} else cout << "Dostep do pliku zostal zabroniony!" << endl;

getchar();

//warunki początkowe
t[0]=0; p[0]=0; q[0]=2.5;

for(int i=1; i<N; i++){
  t[i]=t[i-1]+dt;
  p[i]=p[i-1]+fp(q[i-1],dq)*dt;
  q[i]=q[i-1]+fq(p[i-1])*dt;
 cout<< t[i] <<"          "<< p[i] <<"            "<<q[i] << endl;
}


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
