//https://abakbot.ru/online-2/91-rotate  - угол поворота по точке
//http://stratum.ac.ru/education/textbooks/kgrafic/lection01.html - матрицы
//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
int nX, nY; //размер Канвы
int Xnull, Ynull;  //начало координат
double Xmin, Xmax, Ymin, Ymax; //границы
int dX, dY; //масштаб
double AlfX, AlfY; //альфа

double Matrix[3][3];
vector <TPoint> Figure;  //кординаты фигуры
vector <TPoint> ReFigure;  //кординаты изменённой фигуры
vector <TPoint> DinFigure; //динамическая фигура
struct WPoint
{
double x;
double y;
WPoint (double X, double Y)
{x = X; y = Y;}
};
vector <WPoint> WFigure;
vector <WPoint> ReWFigure;
vector <WPoint> DinWFigure;
TPoint Tck; //выбранная точка
double OXrate; //коэф. масстабирования
int TopF;  //выбранная вершина
double Turn; //угол повторота
bool FlagPaint = false; //флаг рисования по матрице
bool StartPaint = false; //флаг рисования в динамике
bool PaintEnd = false; //флаг остановки рисования в динамике
//---------------------------------------------------------------------------
int W2Sx (double Xm) //К экранным Х
	{
	int Xe = round(AlfX*Xm)+Xnull;
	return Xe;
	}
int W2Sy (double Ym) //К экранным У
	{
	int Ye = (-1) * round(AlfY*Ym)+Ynull;
	return Ye;
	}

double S2Wx (int Xe) //К мировым Х
	{
	double Xm = (Xe-Xnull)/AlfX;
	return Xm;
	}
double S2Wy (int Ye) //К мировым Y
	{
	double Ym = -(Ye-Ynull)/AlfY;
	return Ym;
	}

//рисование линии Мировые
void LineW (TImage *I, double x1, double y1, double x2, double y2)
	{
	I->Canvas->MoveTo(W2Sx(x1),W2Sy(y1));
	I->Canvas->LineTo(W2Sx(x2),W2Sy(y2));
	}
//рисование линии Экранные
void LineS (TImage *I, double x1, double y1, double x2, double y2)
	{
	I->Canvas->MoveTo(x1,y1);
	I->Canvas->LineTo(x2,y2);
	}

//рисование осей
void PaintAxis (TImage *I)
	{
	I->Canvas->Pen->Width = 2;

	//ось Х
	LineS(I,0,Ynull,nX,Ynull);
	LineS(I,nX-15,Ynull+5,nX,Ynull);
	LineS(I,nX-15,Ynull-5,nX,Ynull);
	I->Canvas->TextOut(nX-10,Ynull-7-I->Canvas->TextHeight("X"),"X");
	//ось У
	LineS(I,Xnull,0,Xnull,nY);
	LineS(I,Xnull-5,0+15,Xnull,0);
	LineS(I,Xnull+5,0+15,Xnull,0);
	I->Canvas->TextOut(Xnull-12,0+15-I->Canvas->TextHeight("Y"),"Y");
	//подписть О
	I->Canvas->TextOut(Xnull-12,Ynull+15-I->Canvas->TextHeight(")"),"O");

	I->Canvas->Pen->Width = 1;
	}

//рисование сетки
void PaintGrid (TImage *I)
	{
	I->Canvas->Pen->Style = psDot;

	//линии Х
	for (int i = 0;i<nX;i++)
		LineW (I, Xmin + (i * dX), Ymin, Xmin + (i * dX), Ymax);
	//линии У
	for (int i = 0;i<nY;i++)
		LineW (I, Xmin, Ymin + (i * dY), Xmax, Ymin + (i * dY));

	I->Canvas->Pen->Style = psSolid;
	}

//рисование линейки
void PaintScale (TImage *I)
	{
	I->Canvas->Pen->Width = 2;

	//длина линий меток
	float Ys = Ymax / 30;
	float Xs = Xmax / 50;
	//линейка Х
	for (int i = 1;i<-Xmin+Xmax;i++)
		{
		if (Xmin + (i * dX) == 0) continue; //не писать 0
		LineW (I, Xmin + (i * dX), 0+Ys, Xmin + (i * dX), 0-Ys);
		I->Canvas->TextOut (W2Sx(Xmin + (i * dX)), W2Sy(0)+7, FloatToStrF(Xmin + (i * dX),ffFixed,10,0));
		}
	//линейка У
	for (int i = 0;i<-Ymin+Ymax;i++)
		{
		if (Ymin + (i * dY) == 0) continue; //не писать 0
		LineW (I, 0+Xs, Ymin + (i * dY), 0-Xs, Ymin + (i * dY));
		I->Canvas->TextOut (W2Sx(0)+7, W2Sy(Ymin + (i * dY)), FloatToStrF(Ymin + (i * dY),ffFixed,10,0));
		}

	I->Canvas->Pen->Width = 1;
	}

//рисование фигуры мышью
void PaintFigure (TImage *I, vector <TPoint>&Vec)
	{
	I->Canvas->Pen->Width = 3;
	I->Canvas->Pen->Color = clRed;
	I->Canvas->Brush->Style = bsClear;
	I->Canvas->Font->Color=clRed;

	if (Figure.size() == 1) //рисование точки
		{
		I->Canvas->Ellipse(Vec[0].x-1, Vec[0].y-1, Vec[0].x+1, Vec[0].y+1);
		I->Canvas->TextOut (Vec[0].x+7, Vec[0].y-15, "(" +
			FloatToStrF(S2Wx(Vec[0].x),ffFixed,10,2) + "; "+
			FloatToStrF(S2Wy(Vec[0].y),ffFixed,10,2) + ")");
		}
	else  //фигуры (минимум 2 точки)
		{
		TPoint Points[Vec.size()];
		for (int i = 0; i < Vec.size(); i++)
			{
			Points[i] = Vec[i];
			I->Canvas->TextOut (Vec[i].x+7, Vec[i].y-15, "(" +
				FloatToStrF(S2Wx(Vec[i].x),ffFixed,10,2) + "; "+
				FloatToStrF(S2Wy(Vec[i].y),ffFixed,10,2) + ")");
			}
		I->Canvas->Polygon(Points,Vec.size()-1);
		}

	I->Canvas->Pen->Width = 1;
	I->Canvas->Pen->Color = clBlack;
	I->Canvas->Brush->Style = bsSolid;
	I->Canvas->Font->Color=clBlack;
	}

//перенос
TPoint Transfer (TPoint P, double X, double Y)
	{
	Matrix[0][0] = 1; Matrix[0][1] = 0; Matrix[0][2] = 0;
	Matrix[1][0] = 0; Matrix[1][1] = 1; Matrix[1][2] = 0;
	Matrix[2][0] = X; Matrix[2][1] = Y; Matrix[2][2] = 1;

	double PM[3] = {S2Wx(P.x), S2Wy(P.y), 1};
	double RM[3];
	RM[0] = PM[0] * Matrix[0][0] + PM[1] * Matrix[1][0] + PM[2] * Matrix[2][0];
	RM[1] = PM[0] * Matrix[0][1] + PM[1] * Matrix[1][1] + PM[2] * Matrix[2][1];
	RM[2] = PM[0] * Matrix[0][2] + PM[1] * Matrix[1][2] + PM[2] * Matrix[2][2];
	P.x = W2Sx(RM[0]);
	P.y = W2Sy(RM[1]);

	return P;
	}

//перенос
TPoint TransferW (WPoint P, double X, double Y)
	{
	Matrix[0][0] = 1; Matrix[0][1] = 0; Matrix[0][2] = 0;
	Matrix[1][0] = 0; Matrix[1][1] = 1; Matrix[1][2] = 0;
	Matrix[2][0] = X; Matrix[2][1] = Y; Matrix[2][2] = 1;

	double PM[3] = {P.x, P.y, 1};
	double RM[3];
	RM[0] = PM[0] * Matrix[0][0] + PM[1] * Matrix[1][0] + PM[2] * Matrix[2][0];
	RM[1] = PM[0] * Matrix[0][1] + PM[1] * Matrix[1][1] + PM[2] * Matrix[2][1];
	RM[2] = PM[0] * Matrix[0][2] + PM[1] * Matrix[1][2] + PM[2] * Matrix[2][2];
	P.x = RM[0];
	P.y = RM[1];

	return P;
	}

//масштабирование	
TPoint Scaling (TPoint P, double Xrate)
	{
	Matrix[0][0] = Xrate; Matrix[0][1] = 0; Matrix[0][2] = 0;
	Matrix[1][0] = 0; Matrix[1][1] = 1; Matrix[1][2] = 0;
	Matrix[2][0] = 0; Matrix[2][1] = 0; Matrix[2][2] = 1;

	double PM[3] = {S2Wx(P.x), S2Wy(P.y), 1};
	PM[0] = StrToFloat(FloatToStrF(PM[0],ffFixed,10,5));
	double RM[3];
	RM[0] = PM[0] * Matrix[0][0] + PM[1] * Matrix[1][0] + PM[2] * Matrix[2][0];
	RM[1] = PM[0] * Matrix[0][1] + PM[1] * Matrix[1][1] + PM[2] * Matrix[2][1];
	RM[2] = PM[0] * Matrix[0][2] + PM[1] * Matrix[1][2] + PM[2] * Matrix[2][2];
	P.x = W2Sx(RM[0]);

	return P;
	}

//поворот
TPoint Turning (TPoint P, double Turn)
	{
	Matrix[0][0] = cos(Turn*(M_PI/180)); Matrix[0][1] = sin(Turn*(M_PI/180)); Matrix[0][2] = 0;
	Matrix[1][0] = -sin(Turn*(M_PI/180)); Matrix[1][1] = cos(Turn*(M_PI/180)); Matrix[1][2] = 0;
	Matrix[2][0] = 0; Matrix[2][1] = 0; Matrix[2][2] = 1;

	double PM[3] = {S2Wx(P.x), S2Wy(P.y), 1};
	PM[0] = StrToFloat(FloatToStrF(PM[0],ffFixed,10,12));
	PM[1] = StrToFloat(FloatToStrF(PM[1],ffFixed,10,12));
	double RM[3];
	RM[0] = PM[0] * Matrix[0][0] + PM[1] * Matrix[1][0] + PM[2] * Matrix[2][0];
	RM[1] = PM[0] * Matrix[0][1] + PM[1] * Matrix[1][1] + PM[2] * Matrix[2][1];
	RM[2] = PM[0] * Matrix[0][2] + PM[1] * Matrix[1][2] + PM[2] * Matrix[2][2];
	P.x = W2Sx(RM[0]);
	P.y = W2Sy(RM[1]);
	return P;
	}


void S2Wf (vector <TPoint> &S, vector <WPoint> &W)
{
	W.clear();
	for (int i = 0; i<S.size(); i++)
		{
		double X = S2Wx(S[i].x);
		double Y = S2Wy(S[i].y);
		WPoint WP(X,Y);
		W.push_back(WP);
		}
}
void W2Sf (vector <TPoint> &S, vector <WPoint> &W)
{
	S.clear();
	for (int i = 0; i<W.size(); i++)
		{
		int X = W2Sx(W[i].x);
		int Y = W2Sy(W[i].y);
		TPoint WP(X,Y);
		S.push_back(WP);
		}
}

//активация формы
void __fastcall TForm1::FormActivate(TObject *Sender)
{
//начальные параметры
nX = Image->Width; nY = Image->Height;
Xnull = nX / 2; Ynull = nY / 2;
Xmin = -5-1; Xmax = 5+1; Ymin = -5-1; Ymax = 5+1;
AlfX = nX /(Xmax-Xmin); AlfY = nY /(Ymax-Ymin);
dX = (Xmax-Xmin)/nX+1; dY = (Ymax-Ymin)/nY+1;

Tck = TPoint(Xnull,Ynull);
OXrate = 2;
TopF = 0;
Turn = 90;

Matrix[0][0] = 1; Matrix[0][1] = 0; Matrix[0][2] = 0;
Matrix[1][0] = 0; Matrix[1][1] = 1; Matrix[1][2] = 0;
Matrix[2][0] = 0; Matrix[2][1] = 0; Matrix[2][2] = 1;

BInputMClick(Sender);
Panel1->Repaint();
}
//---------------------------------------------------------------------------
//перерисовка формы
void __fastcall TForm1::FormPaint(TObject *Sender)
{
Image->Canvas->Pen->Color=clBlack; //Имейдж 1
Image->Canvas->Brush->Color=clWhite;
Image->Canvas->Rectangle(0,0,nX,nY);
ImageRe->Canvas->Pen->Color=clBlack; //Имейдж 2
ImageRe->Canvas->Brush->Color=clWhite;
ImageRe->Canvas->Rectangle(0,0,nX,nY);
//оси и сетка
if (CAxis->Checked) {PaintAxis(Image); PaintAxis(ImageRe);}
if (CGrid->Checked) {PaintGrid(Image); PaintGrid(ImageRe);}
if (CScale->Checked) {PaintScale(Image); PaintScale(ImageRe);}
//фигура и преобразования
PaintFigure (Image, Figure);

//таймер динамики
if (SpeedButton1->Down) { Timer1->Enabled = true; PaintEnd = false;}
else
	{
	Timer1->Enabled = false;
	DinFigure = Figure;
	S2Wf(Figure, DinWFigure);
	if (StartPaint) {DinFigure = ReFigure; PaintEnd = true;}
	}
if (RBInput->Checked) //ввод фигуры
	{
	PaintFigure (ImageRe, Figure);
	}
if (RBVecOP->Checked && !PaintEnd) //перенос
	{
	/*
	ReFigure.clear();
	for (int i = 0; i<DinFigure.size(); i++)
		{
		ReFigure.push_back(Transfer(DinFigure[i], S2Wx(Tck.x), S2Wy(Tck.y)));
		}
		*/
	ReWFigure.clear();
	for (int i = 0; i<DinWFigure.size(); i++)
		{
		ReWFigure.push_back(TransferW(DinWFigure[i], S2Wx(Tck.x), S2Wy(Tck.y)));
		}

	}
if (RBScaling->Checked && !PaintEnd) //маштабирование
	{
	ReFigure.clear();
	for (int i = 0; i<DinFigure.size(); i++)
		{
		ReFigure.push_back(Scaling(DinFigure[i], OXrate));
		}
	}
if (RBReflection->Checked && !PaintEnd) //отражение
	{
	ReFigure.clear();

	for (int i = 0; i<DinFigure.size(); i++)
		{
		TPoint P = DinFigure[i];
		if (TopF != i)
			{
			P = Transfer(P, -S2Wx(DinFigure[TopF].x), -S2Wy(DinFigure[TopF].y));
			P = Turning(P, 180);
			P = Transfer(P, S2Wx(DinFigure[TopF].x), S2Wy(DinFigure[TopF].y));
			}
		ReFigure.push_back(P);
		}

	//матрица отражения и переноса
	Matrix[0][0] = cos(180*(M_PI/180)); Matrix[0][1] = sin(180*(M_PI/180)); Matrix[0][2] = 0;
	Matrix[1][0] = -sin(180*(M_PI/180)); Matrix[1][1] = cos(180*(M_PI/180)); Matrix[1][2] = 0;
	Matrix[2][0] = S2Wx(DinFigure[TopF].x); Matrix[2][1] = S2Wy(DinFigure[TopF].y); Matrix[2][2] = 1;
	}
if (RBTurn->Checked && !PaintEnd) //поворот
	{
	ReFigure.clear();

	for (int i = 0; i<DinFigure.size(); i++)
		{
		TPoint P = DinFigure[i];
		P = Transfer(P, -S2Wx(Tck.x), -S2Wy(Tck.y));
		P = Turning(P, Turn);
		P = Transfer(P, S2Wx(Tck.x), S2Wy(Tck.y));
		ReFigure.push_back(P);
		}

	//матрица поворота и переноса
	Matrix[0][0] = cos(Turn*(M_PI/180)); Matrix[0][1] = sin(Turn*(M_PI/180)); Matrix[0][2] = 0;
	Matrix[1][0] = -sin(Turn*(M_PI/180)); Matrix[1][1] = cos(Turn*(M_PI/180)); Matrix[1][2] = 0;
	Matrix[2][0] = S2Wx(Tck.x); Matrix[2][1] = S2Wy(Tck.y); Matrix[2][2] = 1;
	}
if (((RBMatrix->Checked) && (FlagPaint)) && !PaintEnd) //по матрице
	{
	PaintFigure (ImageRe, ReFigure);
	}
if (ReFigure.size() != 0 && !RBMatrix->Checked)  //вывод преобразованной фигуры
	{
	PaintFigure (ImageRe, ReFigure);
	BInputMClick(Sender);
	}
}
//---------------------------------------------------------------------------
//изменение границ Х
void __fastcall TForm1::EScaleXChange(TObject *Sender)
{
if (EScaleX->Text != "")
	{
	Xmin = - StrToFloat(EScaleX->Text)-1;
	Xmax = StrToFloat(EScaleX->Text)+1;
	AlfX = nX /(Xmax-Xmin);
	dX = (Xmax-Xmin)/nX+1;
	Panel1->Repaint();
	}
}
//---------------------------------------------------------------------------
//изменение границ У
void __fastcall TForm1::EScaleYChange(TObject *Sender)
{
if (EScaleY->Text != "")
	{
	Ymin = - StrToFloat(EScaleY->Text)-1;
	Ymax = StrToFloat(EScaleY->Text)+1;
	AlfY = nY /(Ymax-Ymin);
	dY = (Ymax-Ymin)/nY+1;
	Panel1->Repaint();
	}
}
//---------------------------------------------------------------------------
//добавление точек, ввод P, выбор вершины, ввод Е
void __fastcall TForm1::ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int mX, int mY)
{
if (RBInput->Checked) //ввод фигуры
	{
	TPoint P(mX,mY);
	Figure.push_back(P);
	}
if (RBVecOP->Checked) //точка Р
	{
	Tck = TPoint(mX,mY);
	LVecOP->Caption = "Точка Р: (" + FloatToStrF(S2Wx(mX), ffFixed, 10, 2)
					  + "; " + FloatToStrF(S2Wy(mY), ffFixed, 10, 2) +")";
	}
if (RBReflection->Checked) //вершина
	{
	TPoint P(mX,mY);
	for (int i = 0; i<Figure.size();i++)
		{
		for (int rX = mX-30; rX<mX+30; rX++)
			{
			for (int rY = mY-10; rY<mY+10; rY++)
				{
				if ((rX == Figure[i].x)&&(rY == Figure[i].y))
					{
					LReflection->Caption = "Вершина: (" +
						FloatToStrF(S2Wx(rX), ffFixed, 10, 2)+ "; " +
						FloatToStrF(S2Wy(rY), ffFixed, 10, 2) +")";
					TopF = i;
					return;
					}
				}
			}
		}
	ShowMessage("Выберите вершину точнее!");
	}
if (RBTurn->Checked) //точка Е
	{
	Tck = TPoint(mX,mY);
	//строка с коодинатами точки Е
	LTurn->Caption = "Точка E: (" + FloatToStrF(S2Wx(mX), ffFixed, 10, 2)
					  + "; " + FloatToStrF(S2Wy(mY), ffFixed, 10, 2) +")";
	}
Panel1->Repaint();
}
//---------------------------------------------------------------------------
//коэф. мастабирования
void __fastcall TForm1::EOXrateChange(TObject *Sender)
{
if ((EOXrate->Text == "0,")||(EOXrate->Text == "0,0")||(EOXrate->Text == "0,00")
		||(EOXrate->Text == "0,000")) return;
if (EOXrate->Text != "")
	{
	OXrate = StrToFloat(EOXrate->Text);
	if (OXrate==0)
		{
		ShowMessage("Недопустимое значение!"); OXrate=0.1;
		EOXrate->Text = "1"; return;
		}
	Panel1->Repaint();
	}
}
//---------------------------------------------------------------------------
//угол повторота
void __fastcall TForm1::ETurnChange(TObject *Sender)
{
if (ETurn->Text != "")
	{
	Turn = StrToFloat(ETurn->Text);
	Panel1->Repaint();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BCalcClick(TObject *Sender)
{
//расчёт по матрице
if (RBMatrix->Checked)
	{
	//ввод из таблицы
	Matrix[0][0] = StrToFloat(StringGrid->Cells[0][0]);
	Matrix[0][1] = StrToFloat(StringGrid->Cells[1][0]);
	Matrix[0][2] = StrToFloat(StringGrid->Cells[2][0]);
	Matrix[1][0] = StrToFloat(StringGrid->Cells[0][1]);
	Matrix[1][1] = StrToFloat(StringGrid->Cells[1][1]);
	Matrix[1][2] = StrToFloat(StringGrid->Cells[2][1]);
	Matrix[2][0] = StrToFloat(StringGrid->Cells[0][2]);
	Matrix[2][1] = StrToFloat(StringGrid->Cells[1][2]);
	Matrix[2][2] = StrToFloat(StringGrid->Cells[2][2]);

	//расчёт
	ReFigure = DinFigure;

	for (int i = 0; i<DinFigure.size(); i++)
		{
		double PM[3] = {S2Wx(DinFigure[i].x), S2Wy(DinFigure[i].y), 1};
		double RM[3];
		RM[0] = PM[0] * Matrix[0][0] + PM[1] * Matrix[1][0] + PM[2] * Matrix[2][0];
		RM[1] = PM[0] * Matrix[0][1] + PM[1] * Matrix[1][1] + PM[2] * Matrix[2][1];
		RM[2] = PM[0] * Matrix[0][2] + PM[1] * Matrix[1][2] + PM[2] * Matrix[2][2];
		ReFigure[i].x = W2Sx(RM[0]);
		ReFigure[i].y = W2Sy(RM[1]);
		}

	FlagPaint = true;
	BInputMClick(Sender);
	}
}
//---------------------------------------------------------------------------
//вывод матрицы
void __fastcall TForm1::BInputMClick(TObject *Sender)
{
StringGrid->Cells[0][0] = FloatToStrF(Matrix[0][0], ffFixed, 10, 2);
StringGrid->Cells[1][0] = FloatToStrF(Matrix[0][1], ffFixed, 10, 2);
StringGrid->Cells[2][0] = FloatToStrF(Matrix[0][2], ffFixed, 10, 2);
StringGrid->Cells[0][1] = FloatToStrF(Matrix[1][0], ffFixed, 10, 2);
StringGrid->Cells[1][1] = FloatToStrF(Matrix[1][1], ffFixed, 10, 2);
StringGrid->Cells[2][1] = FloatToStrF(Matrix[1][2], ffFixed, 10, 2);
StringGrid->Cells[0][2] = FloatToStrF(Matrix[2][0], ffFixed, 10, 2);
StringGrid->Cells[1][2] = FloatToStrF(Matrix[2][1], ffFixed, 10, 2);
StringGrid->Cells[2][2] = FloatToStrF(Matrix[2][2], ffFixed, 10, 2);
}
//---------------------------------------------------------------------------
//выбор первой точки Р
void __fastcall TForm1::RBVecOPClick(TObject *Sender)
{
LVecOP->Caption = "Точка Р: (" + FloatToStrF(S2Wx(Tck.x), ffFixed, 10, 2)
					  + "; " + FloatToStrF(S2Wy(Tck.y), ffFixed, 10, 2) +")";
}
//---------------------------------------------------------------------------
//выбор первой вершины (0)
void __fastcall TForm1::RBReflectionClick(TObject *Sender)
{
LReflection->Caption = "Вершина: (" +
						FloatToStrF(S2Wx(Figure[0].x), ffFixed, 10, 2)+ "; " +
						FloatToStrF(S2Wy(Figure[0].y), ffFixed, 10, 2) +")";
TopF = 0;
}
//---------------------------------------------------------------------------
//выбор первой точки Е
void __fastcall TForm1::RBTurnClick(TObject *Sender)
{
LTurn->Caption = "Точка E: (" + FloatToStrF(S2Wx(Tck.x), ffFixed, 10, 2)
					  + "; " + FloatToStrF(S2Wy(Tck.y), ffFixed, 10, 2) +")";
}
//---------------------------------------------------------------------------
//стирание фигуры
void __fastcall TForm1::Button1Click(TObject *Sender)
{
Figure.clear();
ReFigure.clear();
RBInput->Checked = true;

Matrix[0][0] = 1; Matrix[0][1] = 0; Matrix[0][2] = 0;
Matrix[1][0] = 0; Matrix[1][1] = 1; Matrix[1][2] = 0;
Matrix[2][0] = 0; Matrix[2][1] = 0; Matrix[2][2] = 1;

BInputMClick(Sender);
}
//---------------------------------------------------------------------------
//динамика
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
DinFigure = ReFigure;
StartPaint = true;
Panel1->Repaint();
if (SpeedButton1->Down) BCalcClick(Sender);
}
//---------------------------------------------------------------------------
//сброс после динамики
void __fastcall TForm1::Button2Click(TObject *Sender)
{
StartPaint = false;
PaintEnd = false;
FlagPaint = false;
DinFigure = Figure;
if (RBMatrix->Checked) ReFigure = Figure;
Panel1->Repaint();
}
//---------------------------------------------------------------------------

