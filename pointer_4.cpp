#include <iostream>
using namespace std;

void increase (void* data, int psize)
{
   if ( psize == sizeof ( char ) )
   { char * pchar; pchar=(char*)data; (*pchar)++; }// co tu się naprawdę dzieje?
   // tworzymy wskaźnik na char, jeśl rozmiar przekazany przez psize jest rozmiarem char
   // trn wskaźnik wskazuje na data, który jest typu void, ale jest rzutowany na char
   // wtedy powiększamy wartość wskazywaną przez wskaźnik pchar, bo ją wywlekamy, z niego, tzn, jego wartość i powiększamy przez ++, 
   //jaka róznica jeśli ++ stoi z tyłu?
   //żadna, bo tak czy inaczej podnosimy wartość w nawiasie i przypisujemy ją na obecną
   else if (psize == sizeof(int) )
   { int * pint; pint=(int*)data; (*pint)++; }
}

int main()
{
   char a = 'x';
   int b = 1602;
   increase(&a,sizeof(a));
   increase(&b,sizeof(b));
   cout<<a<<" , "<<b<<endl;
   return 0;
}
