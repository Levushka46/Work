//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TCheckBox *CAxis;
	TCheckBox *CGrid;
	TCheckBox *CScale;
	TEdit *EScaleY;
	TLabel *Label2;
	TLabel *Label3;
	TImage *Image;
	TEdit *EScaleX;
	TPanel *Panel1;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *EOXrate;
	TLabel *Label6;
	TImage *ImageRe;
	TRadioButton *RBInput;
	TRadioButton *RBVecOP;
	TLabel *LVecOP;
	TRadioButton *RBScaling;
	TRadioButton *RBTurn;
	TLabel *LTurn;
	TLabel *Label8;
	TEdit *ETurn;
	TRadioButton *RBReflection;
	TLabel *LReflection;
	TStringGrid *StringGrid;
	TButton *Button1;
	TButton *BCalc;
	TButton *BInputM;
	TLabel *Label7;
	TRadioButton *RBMatrix;
	TTimer *Timer1;
	TSpeedButton *SpeedButton1;
	TButton *Button2;
	TLabel *Label9;
	TButton *Button3;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall EScaleXChange(TObject *Sender);
	void __fastcall EScaleYChange(TObject *Sender);
	void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ETurnChange(TObject *Sender);
	void __fastcall BCalcClick(TObject *Sender);
	void __fastcall BInputMClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall RBVecOPClick(TObject *Sender);
	void __fastcall RBTurnClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
