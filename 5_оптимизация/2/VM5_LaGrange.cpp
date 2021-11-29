#include <iostream>
#include <conio.h>
using namespace std;
int main()
{
 double lg, rg; int cvar;
 double *x; double *y; double X, sum=0, proizv=1;
  double proizv1=1;
  cout << "Read left gran: "; cin >> lg;
  cout << "Read right gran: "; cin >> rg;
  cout << "Count of variables = "; cin >> cvar;
  x = new double [cvar]; y = new double [cvar];
  for (int i=0; i < cvar; i++) {
	 cout << "x" << i+1 << "="; cin >> x[i];
	 cout << "y" << i+1 << "="; cin >> y[i];
  }
  cout << "X="; cin >> X;
  for (int i=0; i < cvar; i++) {
	 for (int j = 0; j < cvar; j++) {
	 if (i!=j) {
		proizv *= (X-x[j]);
		proizv1 *= (x[i]-x[j]);
	 }
	 }
	 sum += y[i]*(proizv/proizv1);
	 proizv=1; proizv1=1;
  }
  cout << "Y=" << sum;
  getch();
  return 0;
}
