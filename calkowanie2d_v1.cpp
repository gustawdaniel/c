#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

double F(double x, double y, int n){
  if(n==1) {
    if(sqrt(x*x+y*y)<5)
      return 5;}
  if(n==2) {
    if(sqrt(x*x+y*y)<5)
      return 5 - 0.2*(x*x+y*y);}
  return 0;
}

double calka(double xmin, double xmax, double xdok, double ymin, double ymax, double ydok, int n, int m){
double S=0;
double u, v;
//  if (m==1){
    for(double i=xmin;i<=xmax;i+=xdok){
      for(double j=ymin;j<=ymax;j+=ydok){
        if (m==1){
          S+=F(i,j,n);
//          cout <<"    i="<<i<<" j="<<j<<" F="<<F(i,j,n);
        }
        if(m==2){
          u=(((double)(rand())/(double)(RAND_MAX))*(xmax-xmin)+xmin);
          v=(((double)(rand())/(double)(RAND_MAX))*(ymax-ymin)+ymin);
          S+=F(u,v,n);
//          cout <<"    u="<<u<<" v="<<v<<" F="<<F(u,v,n);
        }
      }
//    cout <<endl;
    }
//  }
  S*=(xdok*ydok);
  return S;
}


int main(){
  
  srand ( time(NULL) );
  
  double xmin,  xmax,  xdok, ymin,  ymax,  ydok;
  cout <<"Całka, podaj xmin, xmax, xdok, ymin,ymax,ydok:";
  cin>>xmin>>  xmax>>  xdok>> ymin>>  ymax>> ydok;
  cout<<"całka z walca : ";
  cout << endl<<calka( xmin,  xmax,  xdok,  ymin,  ymax,  ydok, 1,1)<<endl;
  cout<<"całka z paraboloidy: ";
  cout << endl<<calka( xmin,  xmax,  xdok,  ymin,  ymax,  ydok, 2,1)<<endl;
  cout<<"całka z walca losowa: ";
  cout << endl<<calka( xmin,  xmax,  xdok,  ymin,  ymax,  ydok, 1,2)<<endl;
  cout<<"całka z paraboloidy losowa: ";
  cout << endl<<calka( xmin,  xmax,  xdok,  ymin,  ymax,  ydok, 2,2)<<endl;
}


