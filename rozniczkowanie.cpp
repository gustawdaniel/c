#include <iostream>
#include <math.h>

using namespace std;



double f(double t, double y){//prawa strona równania
return -y;
}

int main(){

double y=1; 
double A=1;
double dt=0.01;
double dy;
double t=0;
double tmax=1;

do{
  dy=dt*f(t,y);
  y=y+dy; 
  t=t+dt;
  cout<<"y("<< t <<")= "<< y <<"    "<<"exp(-"<<t<<")="<<exp(-t)<<endl;

}
while(t < tmax);


}


/*double Fswith(double x, int k)
{

switch ( k ) {
case 1
     return 1;//jeśli k=1
  break;
case 2
     return 0;//jeśli k=2
  break;
default:
     return 0;//jeśli k inne
  break;
}
}*/

