#include <iostream>
#include <fstream>

#define N 29
#define NN 8000//N=(int)((a.tk-a.tp)/a.dt)

using namespace std;

struct spline //zmienne do obliczeń na tablicach
{   //deklaracja struktury spline//opis struktury
   double x[N];//n punktów
   double f[N];//n punktów, n-1 przedziałów
   double d[N-1],b[N-1];
   double c[N];//współczynniki (dla wygody mamy o 1 indeks więcej niż przedziałów
   //ostani indeks stosuje się nie dla przedziałów ale dla wygody zapisu przy
   //liczeniu pozostałych obliczeń, pozwala wprowadzić łatwiejsze pętle
   double h[N-1];//różnice (zmienna pomocnicza)
};

struct analiz//zmienne do obliczeń typu całkowanie, różniczkowanie
{
double tp;
double tk;
double dt;
double dq;
double eps;
//tablice
double p[NN],q[NN],t[NN];
//zmienne do wyliczenia
double T;
//zmienne pomocnicze
bool ps;//do dwóch trybów działania programu
bool okr;
double min, mins,minn;//do obliczania okresu
double cP, cQ;//do całkowania
int imax;
//zmienne plikowe
fstream plik;
};


void iana(analiz &a)
{
a.tp=0.0;
a.tk=8.0;
a.dt=0.001;
a.dq=0.0001;
a.eps=1e-2;
a.T=0; a.okr=0;
a.ps=0;//do obliczania okresu
a.min=0, a.mins=0, a.minn=0;
a.cP=0, a.cQ=0;//do całkowania
//ustawienie pliku do zapisu
a.plik.open( "nazwa_pliku.txt", ios::out );

//ustawienia precyzji zapisu do pliku
  a.plik.precision(10);
  a.plik.setf(ios::fixed,ios::floatfield);

//warunki początkowe
a.t[0]=0; a.p[0]=0; a.q[0]=2.5;
};








int intmax(int a, int b)
{
   if(a>b)
      return a;
   else
      return b;
};

double dolaczony(int i, spline s)
{//dla i=2 wskazuje min 1, a dla i=1 wskazuje min np h[0] czyli ok
   return 3*((s.f[i+1]-s.f[i])/s.h[i]-(s.f[i]-s.f[i-1])/s.h[i-1]);
};

void inic(spline &s)
{
   double a[N-2][N-1];//liczba przedziałów minus 1; tzn punkty wewnętrzne + dołączony wiersz
   double d,eps=10e-5;   
//wyełnianie macierzy
   for(int p=0;p<N-2;p++)//od drugiego do przedostatniego
      {//p osiąga najwyżej N-3 co daje indeks N-3, więc element N-2 z N-1 elementów więc przedostatni
         for(int q=0;q<N-2;q++)//o jeden więcej
         {
            if(p==q)//diagonalna
            {//dla p=N-3 mamy p+1=N-2 tzn element N-1 tak jak ma być
               a[p][q]=2*(s.h[p]+s.h[p+1]);
            }//dla p=0 mamy h[0]+h[1]=h1+h2 tak jak ma być
            else if(p+1 == q || q+1 ==p )
            {//tzn np p=0 q=1 spełnia bo p+1=q, dla ostatniego jest nadpisanie
               a[p][q]=s.h[intmax(p,q)];
            }//dla q=1 mamy h[1] czyli h2 zgadza się
            else
               a[p][q]=0;
         }
     }
//wypełnianie wiersza dołączonego
   for(int p=0;p<N-2;p++)
   {// od p+1=1 do p+1=N-2, bo max p = N-3 tzn min h[0] max f[N-1], wszystko sią zgadza
      a[p][N-2]=dolaczony(p+1,s);
   }


//wyswitlanie do pliku
fstream plk;
plk.open( "plik_macierz.txt", ios::out );

  plk.precision(2);
  plk.setf(ios::fixed,ios::floatfield);

for(int i=0; i<N-2;i++)
{
   for(int j=0; j<N-1;j++)
   {
      plk<<a[i][j]<< " "; 
            if(j==N-3)
            {
               plk <<"|";
            }
   }
   plk<<endl;
}
plk.close();



//eliminacja
   for(int k=0;k<N-2;k++)
   {   
      for(int j=k+1;j<N-2;j++)
      {
         d=a[j][k]/a[k][k];
         for(int i=k;i<N-1;i++)
         {
            a[j][i]=a[j][i]-d*a[k][i];
            //cout << "  "<<a[j][i]<< "   ";
         }
         //cout<<endl;
      }
   }


//wyswitlanie do pliku
//fstream plk;
plk.open( "plik_macierzR.txt", ios::out );

  plk.precision(2);
  plk.setf(ios::fixed,ios::floatfield);

for(int i=0; i<N-2;i++)
{
   for(int j=0; j<N-1;j++)
   {
      plk<<a[i][j]<< " "; 
            if(j==N-3)
            {
               plk <<"|";
            }
   }
   plk<<endl;
}
plk.close();





//wyniki
   //dla macierzy 3x3 sprawdzone na kartce 1
/*   for(int k=N-2;k>=0;k--)//indeksowanie c
   {
      s.c[k]=a[k][N-2];//dopełniony 
      //cout <<a[k][M-1];

      for(int i=N-2;i>k;i--){  cout<<"*";  }
      cout<<endl;
      for(int i=N-2;i>k;i--)//powinno być dobrze...
      {//tesy na kartce 1
         s.c[k]-=a[k][i]*s.c[i]; cout<<"  "<<i<<"  "<<s.c[i];
      }//   cout<<"xk "<<x[k]<<" k "<<k<<" aki "<<a[k][i] << " akk " <<a[k][k] <<" i "<<i<<endl;
      s.c[k]=s.c[k]/a[k][k];  cout<<"    k="<<k<<"    s.c[k]="<< s.c[k]<<"    a[k][N-2]="<<a[k][N-2]<<endl;
      //cout << "  "<<s.c[k]<<endl;
   }//tam wypełniane były od c
   s.c[0]=0; s.c[N-1]=0;*/


  for(int i=N-3; i>=0; i--)
  {
    cout <<" "<<i;
  } //podnosimi o 1 indeksy przy c, w celu zapisu tak c[1]...c[N-2]
  cout<<endl;
  for(int i=N-3; i>=0; i--)
  {
    s.c[i+1]=a[i][N-2]/a[i][i];
    for(int j=N-2;j>=i+1;j--)
    {
       s.c[i+1]-=a[i][j]*s.c[j+1];
    }
  }
  s.c[0]=0; s.c[N-1]=0;
  for(int k=0;k<N-2;k++){
  cout<<"* "<<s.c[k+1];
  }
  cout<<endl;
}








void inid(spline &s)
{
   for(int i=0;i<N-1;i++)//zmieniamy i=0,1...N-2 czyli indeksy mat od 1 do N-1,
   {// lub indeksy mat+1 od 2 do N
      s.d[i]=(s.c[i+1]-s.c[i])/(3*s.h[i]);
   }//tzn d[0]=(c[1]-c[0]) /(3h[0]) ... d[N-2]=(c[N-1]-c[N-2]) /(3h[N-2])
}//zakresy się zgadzają dla c[0]=c[n-1]=0
//d[0]~c[1]/h[0]; d[n-2]~ -c[n-2]/h[n-2]

void inib(spline &s)
{
   for(int i=0;i<N-1;i++)//zmieniamy i=0,1...N-2 czyli indeksy mat od 1 do N-1,
   {// lub indeksy mat+1 od 2 do N jak wcześniej
      s.b[i]=(s.f[i+1]-s.f[i])/(s.h[i])-(2*s.c[i]+s.c[i+1])*s.h[i]/3;
   }
}








void inicjalizacja(spline &s)
{
    s.x[0]= -4; s.x[1]= -3; s.x[2]= -2; s.x[3]= -1.8; s.x[4]= -1.6; s.x[5]= -1.4; 
    s.x[6]= -1.2; s.x[7]= -1; s.x[8]= -0.8; s.x[9]= -0.6; s.x[10]= -0.4; s.x[11] =  -0.2;
    s.x[12]= 1.11e-16;s.x[13]= 0.2; s.x[14]= 0.4;s.x[15]= 0.6;s.x[16]= 0.8;s.x[17]= 1;
    s.x[18]= 1.2;s.x[19]= 1.4;s.x[20]= 1.6;s.x[21]= 1.8;s.x[22]= 2;s.x[23]= 2.2;s.x[24]= 2.4;
    s.x[25]= 2.6;s.x[26]= 2.8;s.x[27]= 3;s.x[28]= 4;
    
    s.f[0]= 94.08;s.f[1]= 23.2;s.f[2]= 0;s.f[3]= -1.411;s.f[4]= -2.166;s.f[5]= -2.415;
    s.f[6]= -2.294;s.f[7]= -1.92;s.f[8]= -1.398;s.f[9]= -0.8154;s.f[10]= -0.2458;
    s.f[11]= 0.2534; s.f[12]= 0.64;s.f[13]= 0.887;s.f[14]= 0.983;s.f[15]= 0.9318;
    s.f[16]= 0.7526;s.f[17]= 0.48; s.f[18]= 0.1638;s.f[19]= -0.1306;s.f[20]= -0.3226;
    s.f[21]= -0.3162;s.f[22]= 0;s.f[23]= 0.7526; s.f[24]= 2.084;s.f[25]= 4.151;
    s.f[26]= 7.127;s.f[27]= 11.2;s.f[28]= 55.68;

   for(int i=0; i<=N-1; i++)
   {
     s.h[i]=s.x[i+1]-s.x[i];
   }

   inic(s);//bardzo ważna kolejność
   inib(s);
   inid(s);
}



//   fstream plik;
//   plik.open( "dane_wej.txt", std::ios::in | std::ios::out );



int num(spline s, double q)
{
  for(int i=0;i<=N-1;i++)
  {
    if(s.x[i]<=q && q<s.x[i+1]){
    return i;}
  }
}

double S(double q, spline s)
{
  int k=0;
  //if(q<s.x[0] || q>=s.x[N-1]){cout <<"Bład <1>";return -1000;}//błąd punkt poza przedziałem interpolacji
  //else
  {
     k=num(s,q);
     return s.f[k]+s.b[k]*(q-s.x[k])+s.c[k]*(q-s.x[k])*(q-s.x[k])+s.d[k]*(q-s.x[k])*(q-s.x[k])*(q-s.x[k]);
  }
}

double V(double q, spline s, bool unum)
{
   if(unum==0) {
   return (q*q-4)*(q*q-q-0.4)*0.4; }
   else
   return S(q,s);
}


double fp(double q, double dq,spline s, bool unum)//siła inaczej dp/dt = -dv/dq
{
   return -(V(q+dq/2,s,unum)-V(q-dq/2,s,unum))/dq;
}

double fq(double p)//prędkość inaczej dq/dt = p/m
{
   return p;//m=1.0
}


void obliczenia(analiz &a, spline s,bool unum)
{

  fstream pplk, qplk;
pplk.open( "p.txt", ios::out );
qplk.open( "q.txt", ios::out );

  pplk.precision(6);
  pplk.setf(ios::fixed,ios::floatfield);
  qplk.precision(6);
  qplk.setf(ios::fixed,ios::floatfield);

  cout<<"a";
  //jeśli uda się otworzyć plik
  if( a.plik.good() == true )
  {
    //cout << "Uzyskano dostep do pliku!" << endl;
    a.plik << "Czas [s] " <<"             "<< "Położenie [m]" <<"           "<<"Pęd [kg m / s] "<< endl;// <<"          potencjał"
    a.plik << a.t[0] <<"          "<< a.q[0] <<"             "<<a.p[0] <<endl;//"          "<< V(a.q[0],s,unum)<<
     
    qplk <<a.t[0] <<"          "<< a.q[0] <<endl;
    pplk <<a.t[0] <<"          "<< a.p[0] <<endl;
    
    for(int i=1; i<NN; i++)
    {//wykonaj pętlę w której wypełniane są tablice
    
      a.t[i]=a.t[i-1]+a.dt;
      a.p[i]=a.p[i-1]+fp(a.q[i-1],a.dq,s,unum)*a.dt;
      a.q[i]=a.q[i-1]+fq(a.p[i-1])*a.dt;//oraz zapisywane są do pliku wyniki
      a.plik << a.t[i] <<"          "<< a.q[i] <<"            "<<a.p[i] << endl;//<<"          "<< V(a.q[i],s,unum)
      qplk <<a.t[i] <<"          "<< a.q[i] <<endl;
      pplk <<a.t[i] <<"          "<< a.p[i] <<endl;
      //obliczanie okresu
      if(a.okr==0)//jeśli nie zaliczyliśmy jeszcze okresu
      {
         a.mins=a.min;//przekazanie poprzedniego "minimum" (najstarszego)
         a.min=a.minn;//potencjalnie prawdziwe minimum o jeden krok wcześniejsze
         a.minn=((a.p[i]-a.p[0])*(a.p[i]-a.p[0]) + (a.q[i]-a.q[0])*(a.q[i]-a.q[0]));//obecna wartość
         if(a.min<a.mins and a.min < a.minn and a.min < a.eps) //ma być minimum i do tego bardzo małe
         {
            a.T=(i-1) *a.dt; //okres
            a.imax=(int)(((double)(i-1))/2.0); //maksymalny indeks przy całkowaniu
            a.okr=1;//zaliczyliśmy już okres, nie robimy tego więcej
            //cout << " T [ "<<i<<" ] = " << T<< "      ;      min = " << min<<endl;
         }
       }
      }
  pplk.close();
  qplk.close();
 
  a.plik.close();//zamknięcie pliku 
  } else cout << "Dostep do pliku zostal zabroniony!" << endl;
  cout <<"b";
}

void calkowanie(analiz &a)
{//całkowanie 
a.cP=(0.5)*(a.p[0]+a.p[a.imax]);//wyrazy skrajne przed wejsciem w nastepna petle;
a.cQ=(0.5)*(a.q[0]+a.q[a.imax]);
for(int i=1;i<a.imax;i++)
{
   a.cP+=a.p[i]; a.cQ+=a.q[i];
};
a.cP*=a.dt; a.cQ*=a.dt;//z petli wyrzucac mozliwie duzo mnorzen
}

void wyswietlpotencjal(spline s)
{
   cout << "skok" <<"          "<< "potencjal         num         sx[i]" <<endl; 
   int i=0;
   for(double skok=s.x[0];skok<s.x[N-1]+1;skok+=0.2){
   
   cout << skok <<"          "<< S(skok,s) << "      "<<num(s, skok)<<"       "<< s.x[num(s,skok)]<<endl;
   i++;
   }

   cout << endl;
   cout << "num(s,-2.9)"<<num(s,-2.9)<<endl;

  cout.precision(5);
  cout.setf(ios::fixed,ios::floatfield);

   cout << "Wspolczynniki: do spline";
   double argument, a1,a2;
   a1=8.0/((double)(N-1));
   a2=-4.0;
   cout <<endl<<"argum,       j,         f,          x,         c,          b,         d,        s"<<endl;
   for(int j=0;j<N;j++)
   {
      argument = a1*(double)(j)+a2;
      cout << argument <<"     "<<j<<"     "<<s.f[num(s,argument)]<<"    "<<s.x[num(s,argument)]<<"     "<<s.c[num(s,argument)];
      cout <<"     "<<s.b[num(s,argument)]<<"     "<<s.d[num(s,argument)]<<"     "<<S(argument,s)<<endl;
   }

  fstream plk;
  plk.open( "plotp1.txt", ios::out );

    plk.precision(5);
    plk.setf(ios::fixed,ios::floatfield);

  
   double rrr, r1,r2;
   r1=8.0/((double)(10*N-1));
   r2=-4.0;
   for(int j=0;j<10*N;j++)
   {
      rrr = r1*(double)(j)+r2;
      plk << rrr <<"     "<<S(rrr,s)<<endl;
   } 
  plk.close();

}


int main()//sprawdzić czy potrzeba & wszędzie
{
spline s;
analiz a;


//   for(int i=0; i<N-1; i++)   {     cout << " ="<<i<<"   h="<<s.h[i]<<endl;}
   inicjalizacja(s);
   iana(a);
//   for(int i=0; i<N-1; i++)   {     cout << " ="<<i<<"   h="<<s.h[i]<<endl;}
   obliczenia(a,s,1);//potencjał zwykły
   calkowanie(a);

cout << "Okres T = "<< a.T<<endl;
cout << "Całki P = " << a.cP << "    Q = " <<a.cQ <<endl;

   wyswietlpotencjal(s);


}




/*s.x[N] ={-4, -3, -2, -1.8, -1.6, -1.4, -1.2, -1, -0.8, -0.6, -0.4, -0.2, 1.11e-16, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 2.6, 2.8, 3, 4};
s.f[N] = {94.08, 23.2, 0, -1.411, -2.166, -2.415, -2.294, -1.92, -1.398, -0.8154, -0.2458, 0.2534, 0.64, 0.887, 0.983, 0.9318, 0.7526, 0.48, 0.1638, -0.1306, -0.3226, -0.3162, 0, 0.7526, 2.084, 4.151, 7.127, 11.2, 55.68};*/
