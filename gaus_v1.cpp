#include <iostream>
#include <math.h>

using namespace std;

#define N 4
#define M 5

double abs(double x)
{
return sqrt(x*x);
}

int main()
{
   double a[N][M] = {{2,2,0,1,1},{3,2,1,0,0},{0,1,0,1,1},{4,-1,2,1,0}};
   double x[N] = {0,0,0,0};
   double d,eps=10e-5;

   for(int k=0;k<N;k++)
   {
      if(abs(a[k][k])<eps)
      {
         for(int s=0;s<M;s++)
         {
            d=a[k][s];
            a[k][s] = a[k+1][s];
            a[k+1][s]=d;
         }
      }
      for(int p=0;p<N;p++)
      {
         for(int q=0;q<M;q++)
         {
            cout << "      "<<a[p][q]<< "       "; 
            if(q==N-1)
            {
               cout <<"|";
            }
         }
         cout<<endl;
      }
      cout<<endl;
   
      for(int j=k+1;j<N;j++)
      {
         d=a[j][k]/a[k][k];
         for(int i=k;i<M;i++)
         {
            a[j][i]=a[j][i]-d*a[k][i];
            //cout << "  "<<a[j][i]<< "   ";
         }
         //cout<<endl;
      }
   }
   for(int k=N-1;k>=0;k--)
   {
      x[k]=a[k][M-1]/a[k][k];
      //cout <<a[k][M-1];
      for(int i=N-1;i>k;i--)
      {
         x[k]-=a[k][i]/a[k][k]*x[i];
         cout<<"xk "<<x[k]<<" k "<<k<<" aki "<<a[k][i] << " akk " <<a[k][k] <<" i "<<i<<endl;
      }
      cout << "  "<<x[k]<<endl;
   }
}
