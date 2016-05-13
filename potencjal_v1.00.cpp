#include <iostream>
#include <fstream>

using namespace std;

//   fstream plik;
//   plik.open( "dane_wej.txt", std::ios::in | std::ios::out );

int num(double* x,double q, int N)
{
  for(int i=0;i<=N-1;i++)
  {
    if(x[i]<=q || q<x[i+1]){
    return i;}
  }
}

double S(double q,double* f, double* b, double* c, double* d,int N, double* x)
{
  int k=0;
  if(q<x[0] || q>=x[N-1]){cout <<"Bład <1>";return -1000;}//błąd punkt poza przedziałem interpolacji
  else
  {
     k=num(x,q, N);
     return f[k]+b[k]*(q-x[k])+c[k]*(q-x[k])*(q-x[k])+d[k]*(q-x[k])*(q-x[k])*(q-x[k]);
  }
}

double ht(double* h,double* x, int N)
{
   for(int i=0; i<=N-1; i++)
   {
     h[i]=x[i+1]-x[i];
   }
}

  

//for(int i=0; i<=28; i++){
//   cout << " i="<<i<<"   x="<<x[i]<<"    f="<<f[i]<<endl;
//   }

//double a[29]

//  int *tablica = new int[5];
//  tablica[1] = 1;
//  delete [] tablica; 

//}

double V(double q, bool s, double* f, double* c, double* b, double*d,int N,double*x)
{
   if(s==0)
   return (q*q-4)*(q*q-q-0.4)*0.4;
   else
   return S(q,f,c,b,d,N,x);
}



int main()
{
   int N=29;//liczba punków

   double x[N] ={-4, -3, -2, -1.8, -1.6, -1.4, -1.2, -1, -0.8, -0.6, -0.4, -0.2, 1.11e-16, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 2.6, 2.8, 3, 4};
   double f[N] = {94.08, 23.2, 0, -1.411, -2.166, -2.415, -2.294, -1.92, -1.398, -0.8154, -0.2458, 0.2534, 0.64, 0.887, 0.983, 0.9318, 0.7526, 0.48, 0.1638, -0.1306, -0.3226, -0.3162, 0, 0.7526, 2.084, 4.151, 7.127, 11.2, 55.68};
   double d[N-1],b[N-1],c[N-1];//współczynniki
   double h[N-1];//różnice (zmienna pomocnicza)

   for(int i=0; i<=N-1; i++)
   {
     cout << " ="<<i<<"   h="<<h[i]<<endl
   }
   ht(h, x, N);
   for(int i=0; i<=N-1; i++)
   {
     cout << " ="<<i<<"   h="<<h[i]<<endl
   }

 


V(1.0,1,f, c, b, d,N, x);
}
