#include <iostream>
using namespace std;

int main()
{
   int firstvalue = 5, secondvalue = 15;
   int * p1, * p2;
 
   p1 = &firstvalue;//p1 adressed firstvalue
   p2 = &secondvalue;
   *p1 = 10;
   *p2 = *p1;
   p1 = p2; // p1 wskazuje to co p2, a p2 wskazuje seconvalue
   // w tym czasie firstvalue jest 10, a seconvalue też
   *p1 = 20; // p1 nie wskazuje już firstvalue...

 cout << "firstvalue is " << firstvalue << endl;
  cout << "secondvalue is " << secondvalue << endl;
  return 0;
}
