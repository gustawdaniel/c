#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;



void powitanie(double &a1, double &a2, double &a3, double &a4, double &a5){
  cout << "Planeta \n Podaj jaka czesc populacji (0-10) zajmuje sie zywnoscia w pieciu kolejnych latach : ";
  cin >> a1 >> a2 >> a3 >> a4 >> a5;
  a1=a1/10;a2=a2/10;a3=a3/10;a4=a4/10;a5=a5/10;
}

int main(){     cout.precision(4);
double a[5];
double N=1;//populacja
double r=2;//rozmnazanie
double x,v;//wielkosc pomocnicza do obliczania walki o jedzenie
double beta=2;//produkcja i
double alfa=1;// spozycie pozywienia na mieszkanca
double gamma=1;//tworzenie nauki

powitanie(a[0],a[1],a[2],a[3],a[4]);

cout<< " Poczatkowe parametry: populacja "<<N<<" Rozmnazanie "<< r << " Technologia "<< beta <<" Spozycie na osobe "<<alfa<<" Szybkosc odkrywania "<< gamma<<"\n";

cout <<" Pokolenie   Produkcja   Nadwyzka   Konkurencja   Technologiczny   Przyrost   Populacja   Wynik   Ocena \n";
cout <<" 0           0.5         0          2.4           2                -0.4       1           2       1 \n";



/*fstream plk;
plk.open( "planeta.txt", ios::out );
  plk.precision(2);
  plk.setf(ios::fixed,ios::floatfield);*/

for(int i=1; i<=5; i++){
beta=beta*(1+gamma*N*(1-a[i-1]));//rozwiniecie produkcji
x=a[i-1]*beta-alfa;
v=sqrt(x*x+1)-x;
N=N*(r-v);
cout <<" " <<i<<"           "<<a[i-1]<<"         "<<x<<"      "<<v<<"       "<< beta<<"           "<<r-v<<"        "<<N<<"      "<<beta*N<<"     "<<log(beta*N)<<"\n";
     //plk<<i<<"  "<<a[i-1]<<" "<<x<<" "<<v<<" "<< beta<<"  "<<r-v<<" "<<N<<"  "<<beta*N <<endl;
}
//plk.close();


return 0;
}

