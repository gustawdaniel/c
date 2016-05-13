#include <iostream>
#include <math.h>

#define ABS(x) x<0 ? -x : x

using namespace std;

const double eps=1e-7;

double f(double);
double fpa(double);
double fpn(double);

void wyswietlanie(double &a,double &b, int &s){
cout << "Program Find root - metoda dwosiecznej}; \n dla funkcji sin(x)-0.5;\n ";
do{
cout << "Podaj parametry a,b, w od których zaczynasz: \n";
cin >> a >> b; 
cout << "wybierz metodę, szybka -0 ,prosta 1, z pochodnną numeryczną-2,  pochodnną analityczną-3 ;\n";
cin >> s;
} 
while(f(a)*f(b)>0);//różny znak możemy iść dalej
}





int main(){
double a,b,c;//początek i koniec, argument
int s;//metoda;

wyswietlanie(a,b,s);
cout<<" a= "<<a<<" b= "<<b<<"\n";

c=(a+b);//na początku średnia


while(ABS(f(c))>eps){

if(s==0)
c = -f(a)*(b-a)/(f(b)-f(a) );
else if(s==1)
c=(a+b)/2;
else if(s==2)
c=(fpn(c)*c-f(c))/fpn(c);
else if(s==3) 
c=(fpa(c)*c-f(c))/fpa(c);

if ( f(a)*f(c)>0)//są tego samego znaku
a=c;//to a=c bo tego samego znaku, z drugiej strony znaku jest b;
    //zwężenie przedziału, a jest inne
else
b=c;
cout<<" a= "<<a<<" b= "<<b<<" c = " <<c;
cout<<" f(a)= "<<f(a)<<" f(b)= "<<f(b)<<"\n";
}

cout << "\n\n Wynik :    f( "<<c<<" ) = "<<f(c)<<"\n\n";

return 0;



}



double f(double x){
   return sin(x)-0.5;
}//sprawdź w pkt 0, 1.5


double fpa(double x){//pochona analityczna
   return cos(x);
}//sprawdź w pkt 0, 1.5


double fpn(double x){//pochona analityczna
   return (f(x+eps)-f(x-eps))/(2 *eps);
}//sprawdź w pkt 0, 1.5



