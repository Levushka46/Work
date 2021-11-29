﻿//---------------------------------------------------------------------------
#include <string>
#include <fstream>
#include <vcl.h>
#include "windows.h"
#pragma hdrstop

#include "Unit1.h"
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int i,j,n,m;
float **mas=new float*[n];
int **mas1=new int*[n];
const double eps = 1e-10;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 n=StrToInt(Edit1->Text);
 m=n;
 StringGrid1->ColCount=m;
 StringGrid1->RowCount=n;     
 for (i = 0; i < n; i++) {
	 mas[i]=new float [m];
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
int a,b;
a=StrToInt(Edit3->Text);
b=StrToInt(Edit4->Text);
for (i = 0; i < n; i++)   //osnova
{
	for (j = 0; j < m; j++) 
	{
	  mas[i][j]=rand()%b+a-1;
	}
}

for (i = 0; i<n; i++)
{
	for (j = 0;j<m; j++)                    
	{
	StringGrid1->Cells[j][i]=FloatToStr(mas[i][j]);    
	}	
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	int stroka=0,stolb=0,sim,k=0;
	int znak=0;
    int a=1;
	string str;      
	string chis;
	if (OpenDialog1->Execute())
	{
	ifstream input(OpenDialog1->FileName.c_str());
	while(k<n+1)
	{
	if (k==0) {
	   getline(input,str);
	   n=StrToInt(str[0]);
	   m=n;
		StringGrid1->ColCount=m;
		StringGrid1->RowCount=n;
		for (i = 0; i < n; i++) {
			mas[i]=new float [m];
 		}
       k++;
	}
	else
	{
	getline(input,str);
    int o=str.length();
	for (sim = 0; sim < o; sim++)
	{
		if(str[sim]=='-')
		znak=1;
		
		if ((str[sim]!=' ')&&(str[sim]!='\0')&&(str[sim]!='-'))
		chis=chis+str[sim];

		if ((str[sim]==' ')||(str[sim+1]=='\0'))
		{
		mas[stroka][stolb]=StrToInt(chis.c_str());
			if (znak==1) 
			{
			mas[stroka][stolb]=mas[stroka][stolb]*(-1);
			znak=0;
			} 
		StringGrid1->Cells[stolb][stroka]=FloatToStr(mas[stroka][stolb]);
		stolb++;
		chis.erase();
		if(stolb==m)
		{
		stroka++;
		stolb=0;
		k++;
		}
			if(stroka==n)
			{
            input.close();
			break;
			}
		}
	}
	}
	}
	}
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
for (i = 0; i < n; i++) {
	for (j = 0; j < m; j++) {
	mas[i][j]=StrToInt(StringGrid1->Cells[j][i]);
	}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
if (OpenDialog2->Execute())
	{
ofstream fout(OpenDialog2->FileName.c_str());
for (i=0; i < n; i++) {
	for (j = 0; j < m; j++) {
	fout<<mas[i][j]<<" ";
	}
	fout<<endl;
}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{ 
   int i, j, k;
   int countSwaps = 0;
   for (i = 0; i < n; ++ i)
   {
	  // находим строку с максимальным первым элементом
	  int iMax = i;
	  for (j = i + 1; j < n; ++ j)
		 if (abs (mas[j][i]) > abs (mas[iMax][i]))
			iMax = j;
	  if (abs (mas[iMax][i]) < eps)
		 continue;
	  for (k = 0; k < m; ++ k)
	  {
		 swap (mas[i][k], mas[iMax][k]);
		 countSwaps++;
	  }


	  //  вычитаем текущую строку из всех остальных
	  for (j = i + 1; j < m; ++ j)
	  {
		 double q = - mas[j][i] / mas[i][i];
		 for (k = m - 1; k >= i; -- k)
			mas[j][k] += q * mas[i][k];
	  }
   }
   // умножаем матрицу на -1, если мы сделали  нечётное количество перестановок строк
   // в итоге определитель результирующей матрицы  будет равен определителю начальной матрицы
   // умножение матрицы на число

if (countSwaps%2!=0)
{
   for (int i = 0; i < n; ++ i)
	  for (int j = 0; j < m; ++ j)
		 mas[i][j] = mas[i][j] * (-1);
   }


  for (i=0;i<n;i++)
	for (j=0;j<m;j++)
	{
	StringGrid1->Cells[j][i]=FloatToStr(mas[i][j]);
	}

  }

//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{  int jj,ij,znm,k;

	for (i = 0; i < n; i++)
	{
	 mas1[i]=new int [m];
	}

    for (i=0;i<n;i++)
	for (j=0;j<m;j++)
	{
	mas1[i][j]=static_cast<int>(mas[i][j]);
	}

	for(j=0;j<n;j++)
   {
   jj = mas1[j][j];//определяем первый множитель
   
   if(j==0)//определяем знаменатель
	 znm=1;
   else
	 znm=(mas1[j][j]);

	 if (znm==0)
	 break;

	for (i=j+1; i<n;i++)
		{
		ij=mas1[i][j];//определяем второй множитель
		for(k=j; k<m; k++)
		mas1[i][k]=(jj*mas1[i][k]-ij*mas1[j][k])/znm;
		}
   }

	for (i=0;i<n;i++)
	for (j=0;j<m;j++)
	{
	StringGrid1->Cells[j][i]=IntToStr(mas1[i][j]);
	} 
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button8Click(TObject *Sender)
{
int c,p;
c=StrToInt(Edit5->Text);
p=StrToInt(Edit6->Text);

for(i=0;i<n;i++)
{
	for(j=0;j<m;j++)
	{
		if (i<j)
		{
		mas[i][j]=rand()%c+p-1;
		}
		if (i==j)
		{
		mas[i][j]=rand()%c+p-1;
		}
	}
}

for(i=0;i<n;i++)
{
	for(j=0;j<m;j++)
	{
		if (i>j)
		{
         mas[i][j]=mas[j][i];
		}
	}
}

for (i = 0; i<n; i++)
{
	for (j = 0;j<m; j++)
	{
	StringGrid1->Cells[j][i]=FloatToStr(mas[i][j]);
	}
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
int kolvoiter=0;
int i, j, k;
double q=0;
   int countSwaps = 0;
   for (i = 0; i < n; ++ i)
   {
	  // находим строку с максимальным первым элементом
	  int iMax = i;
	  for (j = i + 1; j < n; ++ j)
	  {
		 if (abs (mas[j][i]) > abs (mas[iMax][i]))
			iMax = j;
			kolvoiter++;
	  }
	  if (abs (mas[iMax][i]) < eps)
		 continue;
	  for (k = 0; k < m; ++ k)
	  {
		 swap (mas[i][k], mas[iMax][k]);
		 countSwaps++;
		 kolvoiter++;
	  }

	  //  вычитаем текущую строку из всех остальных
	  for (j = i + 1; j < m; ++ j)
	  {
         kolvoiter++;
		 q = - mas[j][i] / mas[i][i];
		 for (k = m - 1; k >= i; -- k)
		 {
			mas[j][k] += q * mas[i][k];
			kolvoiter++;
		 }
	  }
	  kolvoiter++;
   }
   // умножаем матрицу на -1, если мы сделали  нечётное количество перестановок строк
   // в итоге определитель результирующей матрицы  будет равен определителю начальной матрицы
   // умножение матрицы на число

if (countSwaps%2!=0)
{
   for (int i = 0; i < n; ++ i)
   {
   kolvoiter++;
	  for (int j = 0; j < m; ++ j)
      kolvoiter++;
		 mas[i][j] = mas[i][j] * (-1);
   }
}

  for (int i = 1; i < n; ++ i)
  {
      for (int j = 0; j < i; ++ j)
      {
		 if (abs (mas[i][i]) < eps)
			break;
		 double q = - mas[j][i] / mas[i][i];
		 for (int k = m - 1; k >= i; -- k)
		 {
			mas[j][k] += q * mas[i][k];
		  kolvoiter++;
		 }
          kolvoiter++;
	  }
	   kolvoiter++;
  }


  for (i = 0; i<n; i++)
{
	for (j = 0;j<m; j++)
	{
	StringGrid1->Cells[j][i]=FloatToStr(mas[i][j]);
	}
}
Label9->Caption=IntToStr(kolvoiter);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button10Click(TObject *Sender)
{
int kolvoiter=0;
   int k=0;
   int countSwaps = 1;
   bool exit=false;
   MessageBox(0,L"Жмите Enter для продолжения итераций или esc чтобы выйти",L"Окошечко", MB_OK);

   for (i = 0; i<n; ++ i)
   {
	  // находим строку с максимальным первым элементом
	  int iMax = i;
	  for (j = i + 1; j < n; ++ j)
		 {if (fabs(mas[j][i]) > fabs(mas[iMax][i]))
			iMax = j;
		 }

	  if (fabs (mas[iMax][i]) <= eps)
		 continue;

	  for (k = 0; k<m; ++ k)
	  {
		if (GetAsyncKeyState(VK_ESCAPE))
		{
		exit=true;
		 break;
		}
		else
		{
		 swap(mas[i][k], mas[iMax][k]);
		 StringGrid1->Cells[k][i]=FloatToStr(mas[i][k]);
		}
	  }
	  countSwaps = - countSwaps * (i != iMax ? 1 : - 1);

	  //  вычитаем текущую строку из всех остальных
	  for (j = i + 1; j < n; ++ j)
	  {
		 double z = - mas[j][i] / mas[i][i];
		 for (k = m - 1; k >= i; -- k)
		  {
			 if (GetAsyncKeyState(VK_ESCAPE))
			{
			exit=true;
			 break;
			}
			else
			{
				mas[j][k] += z * mas[i][k];
				StringGrid1->Cells[k][j]=FloatToStr(mas[j][k]);
			}
				if (exit==true)
				{
				break;
				}
		}
		if (exit==true)
		break;

	  }
	  if (exit==true)
	  break;
	}
   /*
  for (i = 1; i < n; i++)
  {
	for (j = 0; j < i; j++)
	{
	  double q=-mas[j][i]/mas[i][i];
	  for (int  k=m-1; k >= i; k--)
	  {
	   mas[j][k]+=q*mas[i][k];
	  }
	}
  }             */

   for (i = 1; i <n; ++ i)
   {
      for (int j = 0; j < i; ++ j)
	  {
		if (fabs(mas[i][i])<=eps) {
		 continue;
		}
		 double q = -mas[j][i] / mas[i][i];
		 for (k = m- 1; k >= i; -- k)
		 {
			if (GetAsyncKeyState(VK_ESCAPE))
			{
			exit=true;
			 break;
			}
			else
			{
				mas[j][k] += q * mas[i][k];
				StringGrid1->Cells[k][j]=FloatToStr(mas[j][k]);
			}
		 StringGrid1->Cells[j][i]=FloatToStr(mas[i][j]);
		 if (exit==true)
		 break;

		}
        if (exit==true)
		 break;
	}
    if (exit==true)
		 break;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{

double w0[100],w[100],summ=0,w0norm[100],e,d,d0;
int i,j,k;
	for (i=0;i<n;i++)
		w0[i]=0;
		w0[0]=1;
do
	{
	for (i=0;i<n;i++)
		summ=summ+w0[i]*w0[i];
	d0=sqrt(summ);
	for (i=0;i<n;i++)
		w0norm[i]=w0[i]/d0;
	for (i=0;i<n;i++)
    {
		w[i]=0;
		for (j=0;j<n;j++)
			w[i]=w[i]+mas[i][j]*w0norm[j];
    }
	summ=0;
		for (i=0;i<n;i++)
			summ=summ+w[i]*w[i];
		d=sqrt(summ);
		e=fabs(d-d0);
	for (i=0;i<n;i++)
		w0[i]=w[i];
		summ=0;
	}
	while(e>0.001);

	if (OpenDialog3->Execute())
	{
		ofstream fout1(OpenDialog3->FileName.c_str());
		fout1<<d<<endl;
		for (i=0; i < n; i++)
			fout1<<w0norm[i]<<"->"<<endl;
	}
	/*
	Это алгоритм степенного метода.
1) Выбираем вектор X0 - начальное приближение, при этом X0!=0;
2) Строим Xn+1=A*Xn=An+1 * X0
3) Находим λn=(Xn+1, Xn)/(Xn, Xn); (Где запятая - скалярное умножение векторов)
Критерий окончания: |λn-λn-1|<E
*/
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
 MessageBox(0,L"Для размера матрицы используйте только целые числа. Для ввода матрицы из файла в 1 строку пишите размер, а дальше вводите построчно саму матрицу через пробел между элементами.Границы диапазона задавайте от меньшего к большему.",L"Окошечко",MB_OK);
}
//---------------------------------------------------------------------------

