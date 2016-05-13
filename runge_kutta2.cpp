#include <iostream>
#include <math.h>

using namespace std;

long double f(long double t,long double y){
return -y;
}

long double delyk(long double t, long double y,long double dt){//runge_kutta 4 rzędu
long double k1,k2,k3,k4;
k1=f(t,y);
k2=f(t+0.5*dt,y+0.5*dt*k1);
k3=f(t+0.5*dt,y+0.5*dt*k2);
k4=f(t+dt,y+dt*k3);
return (1.0/6.0)*(k1+2*k2+2*k3+k4)*dt;
}

long double delye(long double t, long double y,long double dt){//eulera 
return dt*f(t,y);
}

int main(){

  cout.precision(10);
  cout.setf(ios::fixed,ios::floatfield);


long double ye=1, yk=1, t=0, dt=0.1, tmax=1;

do{
  cout<<"de("<< t <<")= "<< delye(t,ye,dt) <<"   "<<"dk("<< t <<")= "<< delyk(t,yk,dt) <<"    "<<"dxp(-"<<t<<")="<<exp(-t)-exp(-t+dt)<<endl;
  ye+=delye(t,ye,dt);
  yk+=delyk(t,yk,dt);
  t=t+dt;
  cout<<"ye("<< t <<")= "<< ye <<"    "<<"yk("<< t <<")= "<< yk <<"     "<<"exp(-"<<t<<")="<<exp(-t)<<endl;
  cout<<endl;
}
while(t < tmax);
//cout<<"ye("<< t <<")  = "<< ye <<endl<<"yk("<< t <<")  = "<< yk <<endl<<"exp(-"<<t<<")= "<<exp(-t)<<endl;


}


