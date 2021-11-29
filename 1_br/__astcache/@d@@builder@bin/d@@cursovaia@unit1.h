//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.AppEvnts.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TStringGrid *StringGrid1;
	TLabel *Label1;
	TEdit *Edit1;
	TButton *Button1;
	TButton *Button2;
	TEdit *Edit3;
	TLabel *Label2;
	TEdit *Edit4;
	TButton *Button3;
	TLabel *Label3;
	TButton *Button4;
	TLabel *Label4;
	TButton *Button5;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *Edit5;
	TEdit *Edit6;
	TButton *Button8;
	TLabel *Label8;
	TButton *Button9;
	TLabel *Label9;
	TButton *Button10;
	TLabel *Label10;
	TButton *Button11;
	TOpenDialog *OpenDialog1;
	TOpenDialog *OpenDialog2;
	TOpenDialog *OpenDialog3;
	TButton *Button7;
	TButton *Button6;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
