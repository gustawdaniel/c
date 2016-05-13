#include <iostream>
#include <math.h>

using namespace std;

double H(int n, double x){
  if (n==0)
    return 1;
  if (n==1)
    return 2*x;
  else
    return 2*x*H(n-1,x)-2*(double)(n-1)*H(n-2,x);
}

double calka1(double dok_x, double r){//dokładność i zakres całkowania
  double S=0;
  for(double i=-r; i<r;i+=dok_x){
    S+=H(5,i)*H(5,i)*exp(-i*i);}  
  return S*dok_x;
}

double F(double u)
{
  return (H(5,tan(u))*H(5,tan(u))*exp(-(tan(u)*tan(u)))/(cos(u)*cos(u)));
}

/*double F(double u)
{
  return (H(5,u)*H(5,u)*exp(-u*u));
}*/

double calka2(double dok_x)
{
  double S=0;
  for(double i=-M_PI/2; i<M_PI/2;i+=dok_x){
    S+=F(i);}  
  return S*dok_x;
}



double calka(double dok_x, double r)
{
  double S=0;
  for(double i=-r; i<r;i+=dok_x){
    S+=F(i);}  
  return S*dok_x;
}

int main(){

  cout.precision(20);
  cout.setf(ios::fixed,ios::floatfield);

  cout << " " << calka1(0.01,100)<<endl;
  cout << " " << calka2(0.0001)<<endl;
/*  for(double i=-M_PI/2;i<M_PI/2;i+=0.2)
  {
    cout << F(i)<<endl;
  }*/

}

