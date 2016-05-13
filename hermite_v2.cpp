//kompilacja: g++ hermite_v2.cpp -o hermite_v2
//program liczy całki z wielomianów Hermite'a z odpowiednimi wagami
//pierwsza metoda polega na całkowaniu szerokiego obszaru
//druga na podstawieniu x=tan(u) i zawężeniu przedziału całkowania

#include <iostream>
#include <math.h>

using namespace std;//wprowadza nazwy cout, cin

double H(int n, double x){
// rekurencyjna definicja wielomianów Hermite'a
// n - stopień, x - punkt dla którego liczymy warość 
  if (n==0)
    return 1;
  if (n==1)
    return 2*x;
  else
    return 2*x*H(n-1,x)-2*(double)(n-1)*H(n-2,x);
}

double F(int n,double u,bool p)
//wyrażenia całkowane to znaczy wszystko poza różniczką argumentu pod całką
// n - stopień wielomianów, u, argument dla którego zwracamy wartość wyrażenia
//podcałkowego, p - wybór które z dostępnych wyrażeń ma być użyte
{
  if (p==0)//przypadek całkowania po szerokim przedziale
    return (H(n,u)*H(n,u)*exp(-u*u));
  if (p==1)// po podstawieniu x=tan(u), istotne tu jest dzielenie przez cos^2(u)
    return (H(n,tan(u))*H(n,tan(u))*exp(-(tan(u)*tan(u)))/(cos(u)*cos(u)));
}

double calka(int n,double dok_x, double r,bool p)
//całka zwraca wartość całki z jednego z dostępnych wyrażeń podcałkowych F
//na wyznaczonym przedziale z rządaną dokładnością.
//n - stopień wielomianu, dok_x, krok całkowania, r- ponieważ całkujemy
//po przedziale symetrycznym wystarczy wyspecyfikować jedną liczbę, (całkujem
//po przedziale <-r,r> ), p - wybór wyrażenia podcałkowego
{
  double S=0;//część deklaracyjna
  
  for(double i=-r; i<r;i+=dok_x){//część operacyjna
    S+=F(n,i,p);}  
  return S*dok_x;
}

void wyswietlanie(int n, double r, double dok_x_0,double dok_x_1){
//funkcja wyświetla wszystko co ma być wyświetlane;

//ilość kroków w całce jest podwojonym iloczynem promienia dzielonym przez 
//precyzję. W pierwszej całce mamy 2*100/0.01 = 20 000 kroków
//w drugiej 2*3.14/0.0001 = 62 800, stała M_PI oznacza liczbę Pi w bibliotece
//math.h
  cout << endl<<"Program: Hermite_v2 "<<endl<<" Całkuje H(5,x)^2 e^-x^2";
  cout << " po przedziale (-inf,+inf)"<<endl;
  cout << "  metoda bezpośrednia " << calka(n,dok_x_0,r,0)<<endl;
  cout << "  metoda podstawienia " << calka(n,dok_x_1,M_PI/2,1)<<endl;
  cout << "  wartość z dużą dokł ";
  cout <<"6806.22278747718154482496"<<endl;
  cout << " dokładoś wynosi 10^-9             ^"<<endl<<endl; 
}

int main(){
//brak części deklaracyjne ponieważ parametry zadania są już ustalone z góry
//odpowiednie liczby znajdują się w argumentach poleceń "calka" wewnątrz
//funkcji wyświetlającej;

//część ustawień dla poleceń
  cout.precision(20);//ustawienie precyzji wyświetlania
  cout.setf(ios::fixed,ios::floatfield);

//część deklaracji zmiennych
int n=5;//stopień wielomianu
double r=100;//granice przezdiału w całce 1
double dok_x_0 = 0.01;//dokładność całki 1
double dok_x_1 = 0.0001;//dokładnośc całki 2

  wyswietlanie(n,r,dok_x_0,dok_x_1);//wyswietlanie

//6806.2227874771815448249631360299975019425899115099665723410
//żródło wolframalpha.com
}

