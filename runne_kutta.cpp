#include <iostream>
#include <math.h>

using namespace std;

double f(double t,double y){
return -y;
}

double delyk(double t, double y,double dt){//runge_kutta 4 rzędu
double k1,k2,k3,k4;
k1=f(t,y);
k2=f(t+0.5*dt,y+0.5*dt*k1);
k3=f(t+0.5*dt,y+0.5*dt*k2);
k4=f(t+dt,y+dt*k3);
return (1.0/6.0)*(k1+2*k2+2*k3+k4)*dt;
}

double delye(double t, double y,double dt){//eulera 
return dt*f(t,y);
}

int main(){
double ye=1, yk=1, t=0, dt=0.01, tmax=1;

do{

  ye+=delye(t,ye,dt);
  yk+=delyk(t,yk,dt);
  t=t+dt;
  cout<<"ye("<< t <<")= "<< ye <<"    "<<"yk("<< t <<")= "<< yk <<"     "<<"exp(-"<<t<<")="<<exp(-t)<<endl;

}
while(t < tmax);



}


