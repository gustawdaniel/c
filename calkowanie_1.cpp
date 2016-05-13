#include <iostream>
#include <math.h>

using namespace std;

double F(double x)
{
return 1*x*x*x*x+3*x*x*x+1*x*x+2;
}

double Fcalka(double a, double b, double N){
double h=(b-a)/N;
double calka;
calka=(0.5)*(F(a)+F(b));//wyrazy skrajne przed wejsciem w nastepna petle;

for(int i=1;i<N;i++)
{
//cout << "Pary ("<< i <<","<< i+1 <<")";
calka+=F(a+((double)i)*h);
};

calka*=h;//z petli wyrzucac mozliwie duzo mnorzen

}


double trap(double a,double b, double N){

double I1,I2;
double h1,h2;

h1=(b-a)/(3*N);
h2=(b-a)/(N);

I1=Fcalka(a,b,3*N);
I2=Fcalka(a,b,N);

return (I1*h2-I2*h1)/(h2-h1);

}

int main(){

  cout.precision(20);
  cout.setf(ios::fixed,ios::floatfield);   // floatfield set to fixed

double calka=0;//wartosc calki
double a,b;//granice
double h;//skok
double N;//dokładność

cout <<"Witaj, całkujemy funkcję x^4+3x^3+x^2+2"<<endl;
cout <<"Podaj granice całkowania i dokładność: ";
cin >> a>> b>> N;

//obliczanie skoku
h=(b-a)/N;

for(int i=0;i<N;i++)
{
//cout << "Pary ("<< i <<","<< i+1 <<")";
calka+=F(a+((double)i)*h)*h;
};

cout << "Prostokąty : "<<calka<<endl;


calka=(0.5)*(F(a)+F(b));//wyrazy skrajne przed wejsciem w nastepna petle;

for(int i=1;i<N;i++)
{
//cout << "Pary ("<< i <<","<< i+1 <<")";
calka+=F(a+((double)i)*h);
};

calka*=h;//z petli wyrzucac mozliwie duzo mnorzen

cout << "Trapezy    : "<<calka<<endl;

cout << "Rombert    : "<<trap(a,b,N)<<endl;

//kwadratury Gaussa Legendra 3 stopnia

double gaus;

gaus=(5.0/9.0)*F(-sqrt(3.0/5.0) ) + (8.0/9.0)*F(0.0)+ (5.0/9.0) *F( sqrt(3.0/5.0) );

cout << "Gaus      : "<<gaus<<endl;

return 0;
}


