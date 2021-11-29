//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
  #include <math.h>
#include "Vm9.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
  TForm1 *Form1; int X0, Y0;
int xe, ye;   int alphax;  int alphay;
int N=300; double h=0;
double a=-1, b=1;
double ArrX[10];  double ArrY[10];
 double SrXY=0, SrX=0, SrY=0, sumkvadr=0;
 double delta;
 float SmLnx=0, SmLny=0, SmLnxy=0, SmLnx2=0;
void WtS(TImage* Im, double xi, double yi)
{
	alphax=Im->Width/40;
	alphay=Im->Height/30;

	 xe=static_cast<int>(alphax*xi+X0);
	 ye=static_cast<int>(-alphay*yi+Y0);
}

void DrawcoordGrid(TImage* Im)
{
	alphax=Im->Width/40;
	alphay=Im->Height/30;
	  Im->Canvas->Pen->Style=psDash;
	for (int i = 0; i <= 40; i++) {
	   Im->Canvas->MoveTo(i*alphax,0);  Im->Canvas->LineTo(i*alphax, Im->Height);
	}

	for (int j = 0; j <= 30; j++) {
	   Im->Canvas->MoveTo(0,j*alphay);  Im->Canvas->LineTo(Im->Width, j*alphay);
	}
		WtS(Im, 0.0000, 0.0000);
	   Im->Canvas->Pen->Style=psSolid;
	  Im->Canvas->MoveTo(0,ye);  Im->Canvas->LineTo(Im->Width, ye);
	   Im->Canvas->MoveTo(Im->Width-7,ye+3);  Im->Canvas->LineTo(Im->Width, ye);
	   Im->Canvas->MoveTo(Im->Width-7,ye-3);  Im->Canvas->LineTo(Im->Width, ye);

	   Im->Canvas->MoveTo(xe,0);  Im->Canvas->LineTo(xe, Im->Height);
		Im->Canvas->MoveTo(xe+3,7);  Im->Canvas->LineTo(xe, 0);
		 Im->Canvas->MoveTo(xe-3,7);  Im->Canvas->LineTo(xe, 0);
	for (int i = 0; i <= 40; i++) {

		WtS(Im, 0, 0);
	   Im->Canvas->TextOut(i*alphax+3, ye+2, FloatToStr(-20+i));
	}

	for (int j = 0; j <= 30; j++) {
		Im->Canvas->TextOut(xe+3,j*alphay-1, FloatToStr(15-j));
	}
}
double F1(double x)
{
  double y=  x/(1+x+x*x);
  return y;
}
double F2(double x)
{
  double y= log(pow(1+2*cos(x),2));
  return y;
}
double F3(double x)
{
    double y=log(x)/sqrt(x);
  return y;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
for (int i=0; i < 10; i++) {
 ArrX[i]=0;    ArrY[i]=0;
}
 X0=static_cast<int>(Image1->Width/2.0000)-1; Y0=static_cast<int>(Image1->Height/2.0000)-2;
//StringGrid1->Cells[0][0]="x";  StringGrid1->Cells[0][1]="y";
  DrawcoordGrid(Image1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	   Image1->Canvas->Rectangle(-4,-4,Image1->Width+3,Image1->Height+3);
	DrawcoordGrid(Image1);
	a=StrToFloat(Edit1->Text);
	b=StrToFloat(Edit2->Text);
		 for (double xi = -30; xi <= 30; xi+=0.02) {
		 double dry=F1(xi);
	  WtS(Image1, xi, dry);
	  Image1->Canvas->Brush->Color=clGreen;
	  Image1->Canvas->Ellipse(xe-1, ye-1, xe+1, ye+1);
	  Image1->Canvas->Brush->Color=clWhite;
	 }
	 double Sm=0;
	 double del=(b-a)/N;
	 for (double xi=a; xi < b; xi+=del)
	 {
	   h= abs(F1(xi));
	   Sm+=h*(xi+del-xi);
	 }
	  Label3->Caption="S(x)="+FloatToStr(Sm);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
      Image1->Canvas->Rectangle(-4,-4,Image1->Width+3,Image1->Height+3);
	DrawcoordGrid(Image1);
     	a=StrToFloat(Edit1->Text);
	b=StrToFloat(Edit2->Text);
			 for (double xi = -30; xi <= 30; xi+=0.02) {
		 double dry=F1(xi);
	  WtS(Image1, xi, dry);
	  Image1->Canvas->Brush->Color=clGreen;
	  Image1->Canvas->Ellipse(xe-1, ye-1, xe+1, ye+1);
	  Image1->Canvas->Brush->Color=clWhite;
	 }
		 double Sm=0;
	 double del=(b-a)/N;
	 for (double xi=a+del; xi <= b; xi+=del)
	 {
	   h= abs(F1(xi));
	   Sm+=h*(xi+del-xi);
	 }

	 Label3->Caption="S(x)="+FloatToStr(Sm);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
      Image1->Canvas->Rectangle(-4,-4,Image1->Width+3,Image1->Height+3);
	DrawcoordGrid(Image1);
   	a=StrToFloat(Edit1->Text);
	b=StrToFloat(Edit2->Text);
		 for (double xi = -30; xi <= 30; xi+=0.02) {
		 double dry=F1(xi);
	  WtS(Image1, xi, dry);
	  Image1->Canvas->Brush->Color=clGreen;
	  Image1->Canvas->Ellipse(xe-1, ye-1, xe+1, ye+1);
	  Image1->Canvas->Brush->Color=clWhite;
	 }
	 double Sm=0;
	 double del=(b-a)/N;
	 for (double xi=a+del/2.; xi < b; xi+=del)
	 {
	   h= abs(F1(xi));
	   Sm+=h*(del);
	 }

	 Label3->Caption="S(x)="+FloatToStr(Sm);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
    Image1->Canvas->Rectangle(-4,-4,Image1->Width+3,Image1->Height+3);
	DrawcoordGrid(Image1);
     	a=StrToFloat(Edit1->Text);
	b=StrToFloat(Edit2->Text);
		 for (double xi = -30; xi <= 30; xi+=0.02) {
		 double dry=F2(xi);
	  WtS(Image1, xi, dry);
	  Image1->Canvas->Brush->Color=clGreen;
	  Image1->Canvas->Ellipse(xe-1, ye-1, xe+1, ye+1);
	  Image1->Canvas->Brush->Color=clWhite;
	 }
	 double Sm=0;
	 double del=(b-a)/N;
	for (double xi=a; xi < b; xi+=del)
	 {
	   Sm+=(F2(xi)+F2(xi+del))*del/2.;
	 }

	 Label3->Caption="S(x)="+FloatToStr(Sm);
}
//---------------------------------------------------------------------------
