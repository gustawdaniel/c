#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;



void powitanie(){
  cout << "Inwestor \n Co turę podawaj jaką część przychodu chcesz inwestować. : ";
}



int main(){     cout.precision(4);
double z[50]; //zarobki w danym roku
double s[50]; //prawdopodobienstwo smierci
double h[50]; //stopa zwrotu
double a;//alfa stopien inwestowania
double k;//konsumpcja
double p;//przychód
double o=1.0;//jedynka
double inw;//inwestycja
double ksum; //suma konsumpcji

for(int i=0;i<50;i++){
z[i]=1;
s[i]=2*i;
h[i]=0.07;}

powitanie();

cout <<"Przychód początkowy: " <<z[0]<<"\n";
cout <<"Jaka część jest inwestowana?: \n";

cout <<" Konsumpcja   Inwestycja   Przychód   Nadwyżka konsumpcji   Stopa zwrotu   Smierc \n";

p=z[0];//pierwszy przychód
ksum=0;
//cout<< "p="<<p<<"   o="<<o<<"\n";

for(int i=1; i<50; i++){
	cin >> a;
	k=(1-a/100)*p;
	inw=a/100*p;
	p=z[i]+inw*(1+h[i]);
	ksum+=k;
cout <<k<<"        "<<inw<<"        "<<p<<"        "<<ksum-i*z[i]<<"        "<<h[i]<<"       "<<s[i]<<"\n";
}


return 0;
}

