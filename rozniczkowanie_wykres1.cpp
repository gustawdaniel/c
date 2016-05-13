//ruch w polu potencału

#include <iostream>
#include <math.h>

using namespace std;

double fp(double t, double p, double q){
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
}


int main(){

  cout.precision(10);
  cout.setf(ios::fixed,ios::floatfield);

double p=0,q=1, t=0,dt=0.1,tmax=10;

do{
  p+=dp(t,p,q,dt);
  q+=dq(t,p,q,dt);
  t=t+dt;
 // cout<<"p("<< t <<")= "<< p <<"            q("<< t <<")= "<<q<< endl;
 cout<< t <<"          "<< p <<"            "<<q << endl;
}
while(t < tmax);
//cout<<"ye("<< t <<")  = "<< ye <<endl<<"yk("<< t <<")  = "<< yk <<endl<<"exp(-"<<t<<")= "<<exp(-t)<<endl;


/*plot './wyniki.txt' u 1:2 w p
gnuplot> replot './wyniki.txt' u 1:3 w p
gnuplot> replot './wyniki.txt' u 2:3 w p
gnuplot> plot './wyniki.txt' u 2:3 w p
*/

}
