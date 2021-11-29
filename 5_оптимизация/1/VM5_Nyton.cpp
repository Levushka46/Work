#include <iostream>
#include <conio.h>
using namespace std;
double ArrDeltaH [20][20];
double x[20], y[20];   double a, b;
double h; double X,Y;
double Factorial(int n)
{
 if (n>0) {
  return n*Factorial(n-1);
 }
 else
 {
   return 1;
 }
}
double Polynomdiff(double n, double q, bool type)
{
	 if (type==true) {
	  if (n>=1)
		return (q-n)*Polynomdiff(n-1, q, type);
	  else
		return q;
	 }
	 else
	 {
	 if (n>=1)
		return (q+n)*Polynomdiff(n-1, q, type);
	  else
		return q;
	 }
}
int main()
{
   cout << "h="; cin >> h;
   cout << "a="; cin >> a;
   cout << "b="; cin >> b;
   int i=0;
   x[i]=a;
   while((x[i]-b+h)<0.05)
   {
	 ++i;
	 x[i]=x[i-1]+h;
   }
   for (int i1=0; i1 <= i; i1++) {
	 cout << "y" << i1 << "="; cin >> y[i1];
   }
   for (int i1=1; i1 <= i; i1++) {
	 ArrDeltaH[i1-1][0]=y[i1]-y[i1-1];
   }
   i--;
   for (int j = 1; j <= i; j++) {
	for (int i1=1; i1 <= i-j+1; i1++) {
	   ArrDeltaH[i1-1][j]=ArrDeltaH[i1][j-1]-ArrDeltaH[i1-1][j-1];
	}
   }
   cout << "Please enter x: "; cin >> X;
   double q;
   double MedianaOtr = (a+b)/2;
   if (MedianaOtr>=X)
   {
   Y=y[0];
	q=(X-x[0])/h;
	   for (int k=0; k<=i; k++)
	   {
		   Y+=ArrDeltaH[0][k]*Polynomdiff(k, q, true)/Factorial(k+1);
	   }
   }
   else
   {
   Y=y[i+1];
	 q=(X-x[i+1])/h;
	  for (int k=0; k<=i; k++)
	   {   cout << ArrDeltaH[i-k][k];
		   Y+=ArrDeltaH[i-k][k]*Polynomdiff(k, q, false)/Factorial(k+1);
	   }
   }
   cout << "Y=" << Y << endl;
  getch();
  return 0;
}
