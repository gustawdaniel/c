#include <iostream>

using namespace std;

double P(int n,double x);


int main()
{
   //część deklaracyjna
   double x;
   int n;
   double y;

   //część operacyjna
   cout << "Funkcja Legendrea(n,x), podaj rząd i argument \n";
   cin >> n;
   cin >> x;
   cout << xxfunkcja(x)"\n"; 
 cout << "\n n="<<n<<" x="<<x<<endl;
    y=P(n,x);
    cout << "\n wynik: " <<y<<endl;
}

double P(int n,double x)
{

    double y;
   if(n==0)
      return 1;
   if(n==1)
      return x;
   else
      cout <<"*";
      y= (1.0/(double)(n))*( (double)(2*n-1)*x*P(n-1,x)-(double)(n-1)*P(n-2,x) );
      cout <<y;
    return y;
}
