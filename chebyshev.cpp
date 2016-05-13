#include <iostream>
#include <math.h>

using namespace std;

double T(int n, double x){
  if (n==0)
    return 1;
  if (n==1)
    return x;
  else
    return 2*x*T(n-1,x)-T(n-2,x);
}

void wyswietl(){
for(double i=-1;i<=1.05;i+=0.05){
cout<<i<<" "<<T(3,i)<<endl;}
}

double calka(double dok)
{
double S=0;
for(double i=-1.0;i<=1.0;i+=dok){
S+=T(4,i)*T(4,i)*sqrt(1.0-i*i);
}
return S*dok;
}

double zero(double dok_x, dok_y,int n){
  if(abs(T(n,-1.0))<=dok_y)
    return -1.0;
  else{
    for(double i=-1.0;i<=1.0;i+=dok){
      if(T(n,i)*T(n,i+dok_x)<=0;    
    }
  }
}

int main()
{
wyswietl();
cout <<"całka wynosi  " <<calka(0.000005)<<endl;
}


