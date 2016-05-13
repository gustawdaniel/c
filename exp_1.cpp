#include <iostream>

using namespace std;

int main()
{
   //część deklaracyjna
   long double x,xp,exp=1;//warość początkowa to 1 bo zaczynamy sumę od x^1/1+...
   int p,n=1;//zaczynamy od n=1

   //część operacyjna
   cout << "Funkcja exp(x), podaj argument i dokładność \n";
   cin >> x;xp=x;//na xp operujemy
   cin >> p;
   cout << "\n xp="<<xp<<" p="<<p<<endl;
   // suma od 0 do p
   for(int i=0; i<=p; i++)
   {
      cout <<" " << exp<<" "<< x <<" "<< n<<" \n";
      //tu x w pierwszej potędze
      n*=i+1;
      exp+=xp/n;
      xp*=x;//potęga tu razy x i będzie 2
      ;//silnia
      //iloczynów
   }
   cout << "\n wynik: " <<exp<<endl;
}


