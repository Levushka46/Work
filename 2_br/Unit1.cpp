//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#include <string.h>
#include <cstring>
#include <vector>
#pragma hdrstop
#include "list"
#include <stack>
#include "Unit1.h"

using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int kolvo,i,j,len,st=0,st1=0,st2=0,st3=0;
AnsiString strcomment;
AnsiString perevod;
vector <AnsiString> str1;
vector <AnsiString> perenos;
vector <String> preparsing;
vector <String> token;
vector <String> converter;
int kolind=0;
int kolif=0;
int colcomment=0;
String pravila[] = {"{E}","E;","EE","E:E","E,E","I","integer","real","boolean","E=E","beginEend",
"if(E)E","if(E)EelseE","foreachIin(E)E","C","while(E)doE","readln(E)","write(E)","E,E","EZnakE"};
String matrix[24] = {"{", "}","I", "C", ":", ";", ",", "(", ")",
"if", "else", "while", "do", "foreach", "in", "readln", "write",
"integer", "real", "boolean", "Znak", "let", "=", "N"};
String keyword[11] = {"integer","real","boolean","let","while","if","readln","foreach","in","write","do"}; //ключевые слова  без Dim
String slip[] = {'{','}',"{/","/}",';',',','(',':',')','[',']','=',"==",'<','>',"<=",">="}; //разделители   18
char matr [24][24]={
{' ','<','<',' ','<','<','<',' ',' ','<',' ','<',' ','<',' ','<','<',' ',' ',' ',' ',' ','<',' '}, // {
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','>'}, //}
{' ',' ','<','<','>','>','>',' ','>',' ','>',' ',' ','=','=',' ',' ',' ',' ',' ','>',' ','>',' '},// I
{' ',' ',' ',' ',' ','>','=',' ','>',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ','=',' ',' ',' '},//c
{' ',' ',' ',' ',' ','>','>',' ',' ',' ','>',' ',' ',' ',' ',' ',' ','<','<','<',' ',' ',' ',' '},// :
{' ','>','>',' ',' ',' ',' ',' ',' ','>',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//;
{' ',' ','<','<','>',' ',' ',' ',' ','<',' ','<',' ','<',' ','<','<',' ',' ',' ',' ',' ',' ',' '},//,
{' ',' ','<','<',' ',' ',' ',' ','<','=',' ',' ',' ',' ',' ','=','=',' ',' ',' ','<',' ',' ',' '},//(
{' ','>','<',' ','<','>','>',' ',' ','<','>','<','=','<',' ','<','<',' ',' ',' ',' ','<',' ',' '},//)
{' ',' ',' ',' ',' ',' ',' ','=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},// if
{' ',' ','<',' ','<','>','>',' ',' ','<','>','<',' ','<',' ','<','<',' ',' ',' ',' ','<',' ',' '},// else
{' ',' ',' ',' ',' ',' ',' ','=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},// while
{' ','>','<',' ','<','>','>',' ',' ','<','>','<',' ','<',' ','<','<',' ',' ',' ',' ','<',' ',' '},//do
{' ',' ','=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//foreach
{' ',' ',' ',' ',' ',' ',' ','=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//in
{' ',' ',' ',' ',' ',' ',' ','=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},// readln
{' ',' ',' ',' ',' ',' ',' ','=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//write
{' ',' ',' ',' ',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//integer
{' ',' ',' ',' ',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},// real
{' ',' ',' ',' ',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//boolean
{' ',' ','<','<',' ',' ',' ',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//ZNAK
{' ',' ','=',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},// let
{' ',' ','<','<',' ','>','>',' ',' ',' ','>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},//=
{'<',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','<'}//N
};
bool svertka(vector<String> code){
bool flag = false;
int k = 0, l = 0, j = 0;
String word;
String slovo = code[0];
code.erase(code.begin());
code.push_back(slovo);
while(code[0] != 'N')
{
	if( (code[0] == ';') || (code[0]==')') || (code[0] == '{') || (code[0] == '}')  )
	{
		j++;
	}
	for(int i = 0; i < 24; i++)
	{
		if (code.back() != 'E')
		{
			if(code.back() == matrix[i])
			{
                k = i;
                break;
			}
		}
        else
		if(code[code.size()-2] == matrix[i])
		{
				k = i;
				break;
		}

	}
	for(int i = 0; i < 24; i++)
	{
		if (code[0] == 'K')
		{
			l = 23;
            break;
		}
		if (code[0] == matrix[i])
		{
			//if (code [0]==',')
			//{
			//	ShowMessage(k); строка
			//    ShowMessage(i);   столбца
			//	return 0;
			//}  Для поиска ошибок в матрице
			l = i;
			break;
		}
	}
	if(matr[k][l] == '<' || matr[k][l] == '=')
	{
		slovo = code[0];
		code.erase(code.begin());
		code.push_back(slovo);
	}
	if (matr[k][l] == '>')
	{
		while (code.back() != 'N')
		{
            word.Insert(code.back(),0);
            code.pop_back();
			/*if (word == "if(E)E")
			{
                code.push_back("if");
                code.push_back("E");
                word = "";
                break;  Для поиска ошибок в правилах
			}*/
            for(int i = 0; i < 20; i++)
				if(word == pravila[i])
				{
					code.push_back('E');
                    flag = true;
                    break;
				}
			if (flag)
			{
				word = "";
				flag = false;
				break;
			}
		}
		if(code.back() == 'N')
		{
			Form1->Memo3->Lines->Text = Form1->Memo3->Lines->Text +
			 "Возникла синтаксическая ошибка в " + j + " строке";
			 code.clear();
			return false;
		}
	}
	if (matr[k][l] == ' ')
	{
		 if (k == 23 && l == 1)
			 Form1->Memo3->Lines->Text = "Возникла синтаксическая ошибка в начале программы ";
		 else
		 {
			 //j++;
			 Form1->Memo3->Lines->Text = Form1->Memo3->Lines->Text +
			 "Возникла синтаксическая ошибка после "+ matrix[k] + " и перед " + matrix[l];
			 code.clear();
			 return false;
		 }
	}
}
code.clear();
return true;
}
//
char statstr [25];
int poscom1,poscom2,raz;
String delcom(AnsiString s1)       //  удаление комментариев
{
bool f1=0,f2=0;
strcomment=s1;
char* str=new char[strcomment.Length()+1];
  strcpy(str,strcomment.c_str());
  for (i = 0; i < strcomment.Length()-1; i++) {
	 if ((str[i]=='(')	&&	(str[i+1]=='*')) {
		poscom1=i;
		f1=1;
	 }
	 if ((str[i]=='*')	&&	(str[i+1]==')')) {
		poscom2=i+1;
		f2=1;
		if ((f1==1)&&(f2==1))
			{
			raz=poscom2-poscom1;
			for (j = poscom1; j < strcomment.Length()-raz; j++)
				{
				str[j]=str[j+raz+1];
				}
			str[j+1]='\0';
			f1=0;
			f2=0;
			i=poscom1-1;
			}
	 }
  }

	if ( ((f1==1)&&(f2==0)) || ((f1==0)&&(f2==1)) )
	{
	ShowMessage("ЗАКРОЙ КОММЕНТАРИЙ)");
	return NULL;
	}

	String vivod= (String) str;
	return(str);
};

int Find_keywordsl(AnsiString s2)
{
	int rez = -1;
	int n = 11;
	String mas[11];
	for (int i = 0; i<n; i++)
	{
		if (keyword[i] == s2)
			{
			rez = i;
			return rez;
			}
	}
    return rez;
};

int Find_Razdelitel(AnsiString s3)
{
  	int rez = -1;
	int n = 17;
	String mas[17];
	for (int i1 = 0; i1<n; i1++)
	{
		if (slip[i1] == s3)
			{
			rez = i1;
			return rez;
			}
	}
	return rez;
};

bool Ischislo(char* massm)
{
	i=0;
	bool flag=-1;
	while(massm[i]!='\0')
	{
		if ( (!isdigit(massm[i])) && ( massm[i]!='.' ) )
		{
		 return false;
		}
		else
		{
        flag=1;
		}
		i++;
	}
  return flag;
};

bool Isperemenya(char * mas ){
if(strlen(mas)<3) 	//AA1 ABB2 AABC1
{
	return false;
}
if (!isdigit(mas [0]))
{
	for (int i = 1; i<strlen(mas)-1; i++)
		{
		if (isdigit(mas [i]))
			{
			return false;

			}
		}
	if ( !isdigit(mas[strlen(mas)-1]) )
	{
	 return false;
	}
}
else
	{
	return false;
	}

return true;
};

int Find_KeyWord(String word){
    int rez = -1;
	int n = Form1->StringGrid2->RowCount;
	String *mas = new String [n];
    for(int i = 0; i<n; i++)
        mas[i] = Form1->StringGrid2->Cells[1][i];
    for (int i = 0; i<n; i++){
        if (mas[i] == word){
            rez = i;
			return rez;
            }
        }
	return rez;
};
//-------------------------------
int Find_Word(String word){
	int rez = -1;
	int n = Form1->StringGrid3->RowCount;
	String *mas = new String [n];
	for(int i = 0; i<n; i++)
		mas[i] = Form1->StringGrid3->Cells[1][i];
	for (int i = 0; i<n; i++){
		if (mas[i] == word){
			rez = i;
			return rez;
			}
		}
	return rez;
};
//-----------------------------
int Find_Slip(String word){ //разделитель -1 если нет в таблице или позицию в таблице
	int rez = -1;
	int n = Form1->StringGrid1->RowCount;
	String *mas = new String [n];
	for(int i = 0; i<n; i++)
		mas[i] = Form1->StringGrid1->Cells[1][i];
	for (int i = 0; i<n; i++){
		if (mas[i] == word)
			{
			rez = i;
			return rez;
			}
		}
	return rez;
};
//----------------------------
int Find_Num(String word){//числа
	int rez = -1;
	int n = Form1->StringGrid4->RowCount;
	String *mas = new String [n];
	for(int i = 0; i<n; i++)
		mas[i] = Form1->StringGrid4->Cells[1][i];
	for (int i = 0; i<n; i++){
		if (mas[i] == word){
			rez = i;
			return rez;
			}
		}
	return rez;
};

vector <String> Polizz;
void Poliz (vector <String> Leks)
{
stack <String> steck;
vector <String> stroka;
String snos;
String perv;
	stroka=Leks;
	int y=0;
	for (i = 0; i < stroka.size(); i++)
	{
		if (stroka[i]!=';' && stroka [i]!=')')
		{
			if (stroka[i]=='=')
			{
			 steck.push(stroka[i-1]);
			 steck.push(stroka[i+1]);
			 steck.push('=');
			}
			if (stroka[i] == "if")
			{
			 snos="mif";
			 steck.push(stroka[i+2]);
			 steck.push(stroka[i+4]);
			 steck.push(stroka[i+3]);
			 steck.push(snos);
			 kolif++;
			}
			if (stroka[i] == "write")
			{
			 snos="mwr";
			 steck.push(stroka[i+2]);
			 steck.push(snos);
			}
			if (stroka[i] == "readln")
			{
			 snos="mrd";
			 steck.push(stroka[i+2]);
			 steck.push(snos);
			}
            if (stroka[i] == "while")
			{
			 snos="mwhl";
			 steck.push(stroka[i+2]);
			 steck.push(stroka[i+4]);
			 steck.push(stroka[i+3]);
			 steck.push(snos);
			}
            if (stroka[i] == "foreach")
			{
			 snos="min";
			 steck.push(stroka[i+2]);
			 steck.push(snos);
			 steck.push(stroka[i+6]);
			 snos="mfrch";
			 steck.push(snos);
             y=0;
			}
		}
	}
	while(!steck.empty())
	{
        Polizz.push_back(steck.top());
        steck.pop();
	}
	for (int i = 0; i<= Polizz.size(); i++)
	{
		Form1->Memo4->Lines->Text = Form1->Memo4->Lines->Text + Polizz[Polizz.size()-i];
		if (i>0) {
		 Form1->Memo4->Lines->Text = Form1->Memo4->Lines->Text + " ";
        }
	}
};
vector <String> Assembler;
vector <String> Peremenya;
vector <String> Chisla;
void  AsmGen (vector <String> asmb)
{
int mar=kolif;
	for(int i=0;i<asmb.size()+1;i++)
	{
		for (int k=0; k < kolind ; k++)
		{
				if (asmb[i]==Peremenya[k] && asmb[i+2]=='=')
				{
				Assembler.push_back(asmb[i]);
				Assembler.push_back(" ");
				Assembler.push_back("db");
				Assembler.push_back(" ");
				Assembler.push_back(asmb[i+1]);
				Assembler.push_back("perexod");
				}
				if (asmb[i-1]==Peremenya[k] && asmb[i]=="mwr" && asmb[i-3]=="==")
				{
				Assembler.push_back("JE mif:");
				Assembler.push_back("perexod");
				Assembler.push_back("invoke MessageBox, 0, AX=BX, Meassage, MB_OK");
                Assembler.push_back("perexod");
				}
				if (asmb[i-1]==Peremenya[k] && asmb[i]=="mwr" && asmb[i-3]=="<")
				{
				Assembler.push_back("JL mif:");
				Assembler.push_back("perexod");
				Assembler.push_back("invoke MessageBox, 0, BX, Meassage, MB_OK");
				Assembler.push_back("perexod");
				}
				if (asmb[i-1]==Peremenya[k] && asmb[i]=="mwr" && asmb[i-3]==">")
				{
				Assembler.push_back("JG mif:");
                Assembler.push_back("perexod");
				Assembler.push_back("invoke MessageBox, 0, AX, Meassage, MB_OK");
				Assembler.push_back("perexod");
				}
		}
		if (asmb[i]=="mif" && asmb[i-1]=='>')
		{
		Assembler.push_back("MOV ");
		Assembler.push_back("AX,");
		Assembler.push_back(asmb[i-3]);
		Assembler.push_back("perexod");
		
		Assembler.push_back("MOV ");
		Assembler.push_back("BX,");
		Assembler.push_back(asmb[i-2]);
		Assembler.push_back("perexod");
			
		Assembler.push_back("CMP "); 
		Assembler.push_back("AX, BX"); 
		Assembler.push_back("perexod");

		Assembler.push_back("JG mif"+IntToStr(mar-kolif));
		kolif--;
		Assembler.push_back("perexod");
		}
		if (asmb[i]=="mif" && asmb[i-1]=='<')
		{
		Assembler.push_back("MOV ");
		Assembler.push_back("AX,");
		Assembler.push_back(asmb[i-3]);
		Assembler.push_back("perexod");

		Assembler.push_back("MOV ");
		Assembler.push_back("BX,");
		Assembler.push_back(asmb[i-2]);
		Assembler.push_back("perexod");

		Assembler.push_back("CMP ");
		Assembler.push_back("AX, BX");
		Assembler.push_back("perexod");

		Assembler.push_back("JL mif"+IntToStr(mar-kolif));
		kolif--;
		Assembler.push_back("perexod");
		}
        if (asmb[i]=="mif" && asmb[i-1]=="==")
		{
		Assembler.push_back("MOV ");
		Assembler.push_back("AX,");
		Assembler.push_back(asmb[i-3]);
		Assembler.push_back("perexod");

		Assembler.push_back("MOV ");
		Assembler.push_back("BX,");
		Assembler.push_back(asmb[i-2]);
		Assembler.push_back("perexod");

		Assembler.push_back("CMP ");
		Assembler.push_back("AX, BX");
		Assembler.push_back("perexod");

		Assembler.push_back("JE mif"+IntToStr(mar-kolif));
		kolif--;
		Assembler.push_back("perexod");
		}
         if (asmb[i]=="mwhl" && asmb[i-1]=='>')
		{
		Assembler.push_back("XOR CX, CX ");
		Assembler.push_back("WHL:");
		Assembler.push_back("perexod");
		Assembler.push_back("MOV CX, ");
		Assembler.push_back(asmb[i-3]);
		Assembler.push_back("perexod");
		Assembler.push_back("CMP CX, ");
		Assembler.push_back(asmb[i-2]);
		Assembler.push_back("perexod");
		Assembler.push_back("JMP WHND");
		Assembler.push_back("perexod");
		Assembler.push_back("JMP WHL");
		Assembler.push_back("perexod");
		Assembler.push_back("JMP WHND:");
        Assembler.push_back("perexod");
		}
    }
};
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  str1.clear();
  perenos.clear();
   AnsiString memovivod="";
  kolvo=Memo1->Lines->Count;
  Label1->Caption="Ваше количество строк "+IntToStr(kolvo);
  for (int chist=0; chist < StringGrid1->RowCount; chist++) {
   StringGrid1->Cols[chist]->Clear();
  }
  for (int chist=0; chist < StringGrid2->RowCount; chist++) {
   StringGrid2->Cols[chist]->Clear();
  }
  for (int chist=0; chist < StringGrid3->RowCount; chist++) {
   StringGrid3->Cols[chist]->Clear();
  }
  for (int chist=0; chist < StringGrid4->RowCount; chist++) {
   StringGrid4->Cols[chist]->Clear();
  }
  strcomment=Memo1->Text;
  memovivod=delcom(strcomment);
  char* strprob=new char[memovivod.Length()+1]; //isdigit
  char* strprob2=new char[memovivod.Length()+1];
  strcpy(strprob,memovivod.c_str());
  i=0;
  st=0;
  st1=0;
  st2=0;
  st3=0;
  j=0;
  Memo2->Clear();
  preparsing.push_back('N');
  while(strprob[0] != '\0')
  {												//       цикл)))
	while (strprob[j] != ' ' && strprob[j] != '\r' && strprob[j] != '\0')
	{
			statstr[j] = strprob[j];
			j++;
	}
		statstr[j] = '\0';
		strcpy(strprob2,statstr);//strprob было
		perevod = (AnsiString) statstr;
		strprob=strchr(strprob,strprob[j+1]);
		token.push_back(perevod);
        j=0;
		int l=Find_keywordsl(perevod);
		int l1=Find_Razdelitel(perevod);
	if(l1!=-1)
	{
		if(Find_Slip(perevod)==-1)
		{
		StringGrid1->Cells[1][st]=perevod;
		StringGrid1->Cells[0][st]=StrToInt(st+1);
        st++;
		l1++;
		Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + "(1, ";
		Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + IntToStr(st) + ") ";
		str1.push_back("(1, " +IntToStr(st) + ") ");
		}
		else
		{
		   int poz = Find_Slip(perevod)+1;
		   Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + "(1, ";
		   Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + IntToStr(poz) + ") ";
		   str1.push_back("(1, " +IntToStr(poz) + ") ");
		}

		if ((perevod=='>')||(perevod=='<')|| (perevod=="<=")|| (perevod==">=")||(perevod=="==")||(perevod=='+')
		||(perevod=='-')||(perevod=='*')||(perevod=='/')) {
		preparsing.push_back("Znak");
		}
		else
		{
		 preparsing.push_back(perevod);
        }
	}
	 if(l!=-1)
	{
		if(Find_KeyWord(perevod)==-1)
		{
		StringGrid2->Cells[1][st1]=perevod;
		StringGrid2->Cells[0][st1]=StrToInt(st1+1);
		st1++;
		l++;
			Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + "(2, ";
			Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + IntToStr(st1) + ") ";
			str1.push_back("(2, " +IntToStr(st1) + ") ");
		}
            else
		{
		   int poz1 = Find_KeyWord(perevod)+1;
		   Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + "(2, ";
		   Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + IntToStr(poz1) + ") ";
		   str1.push_back("(2, " +IntToStr(poz1) + ") ");
		}
		preparsing.push_back(perevod);
	}

    if (Isperemenya(strprob2))
	{
		if(Find_Word(perevod)==-1)
	 {
		StringGrid3->Cells[1][st2]=perevod;
		StringGrid3->Cells[0][st2]=StrToInt(st2+1);
		st2++;
			Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + "(3, ";
			Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + IntToStr(st2) + ") ";
			str1.push_back("(3, " +IntToStr(st2) + ") ");
			Peremenya.push_back(perevod);
	 }
	 else
	 {
		 int poz2 = Find_Word(perevod)+1;
		   Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + "(3, ";
		   Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + IntToStr(poz2) + ") ";
		   str1.push_back("(3, " +IntToStr(poz2) + ") ");
	 }
     preparsing.push_back('I');
	}

	if (Ischislo(strprob2))
	{
	 if(Find_Num(perevod)==-1)
	 {
	 StringGrid4->Cells[1][st3]=perevod;
	 StringGrid4->Cells[0][st3]=StrToInt(st3+1);
	 st3++;
			Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + "(4, ";
			Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + IntToStr(st3) + ") ";
			str1.push_back("(4, " +IntToStr(st3) + ") ");
			Chisla.push_back(perevod);
            preparsing.push_back('C');
	 }
	 else
	 {
		int poz3 = Find_Num(perevod)+1;
		   Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + "(4, ";
		   Form1->Memo2->Lines->Text = Form1->Memo2->Lines->Text + IntToStr(poz3) + ") ";
		   str1.push_back("(4, " +IntToStr(poz3) + ") ");
	 }
	}

	if (strprob != NULL)
		if (strprob[0] == '\n')
		{
			int k;
			for (k = 0; k < strlen(strprob); k++)
			strprob[k] = strprob[k + 1];
			strprob[k+1] = '\0';
		}
	perenos.push_back(perevod);
  }
  preparsing.push_back('K');

  int l=Peremenya.size();
  bool slipov=0;
  for (int i = 0; i < perenos.size(); i++)
  {
	if (perenos[i]=="" || perenos[i]==' ')
	{
	 perenos.erase(perenos.begin() + i);
	 ShowMessage("Удален комментарий");
     colcomment++;
	}
  }
  for (int i = 0; i < perenos.size()-1; i++)
  {
	for (int y = 0; y < l; y++) {
	 if (perenos[i+1]==Peremenya[y] && perenos[i+3]==Peremenya[y])
	 {
	   ShowMessage("Возникла семантическая ошибка, объявление одинаковых переменных!");
	   break;
	 }
	}
	if (perenos[i]=="if")
	{

		for (int u = 0; u < 18; u++)
		{
			if (perenos[i+3]!='<' && perenos[i+3]!='>' && perenos[i+3]!="==" && perenos[i+3]!=">=" && perenos[i+3]!="<=")
			{
				ShowMessage("Возникла семантическая ошибка, ветвление if");
				break;
			}

		}
	}
  }
}


//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Form1->Memo3->Lines->Clear();
	if ( svertka(preparsing) )
	{
	Form1->Memo3->Lines->Text = Form1->Memo3->Lines->Text + "Синтаксических ошибок не обнаружено";
	}
	preparsing.clear();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
Polizz.clear();
Form1->Memo4->Lines->Clear();
int pozitia = 0;
	for (int y = 0 ; y < token.size(); y++)
	{
		if (token[y]=="integer" || token[y]=="real" || token[y]=="boolean")
		{
			pozitia = y+2;
		}
		if (token[y]=='{' || token[y]=='}')
		{
			token.erase(token.begin()+y);
		}
	}
	Poliz(token);
    token.clear();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
	kolind=Peremenya.size();
    int range=0;
	if (colcomment>0)
	{
	 range=0;
	}
	else
	range=1;
	for (int z=0; z <Polizz.size()+range; z++)
	{
     converter.push_back(Polizz[Polizz.size()-z]);
	}
	AsmGen(converter);

	Form1->Memo5->Lines->Add("format PE GUI 6.0");
	Form1->Memo5->Lines->Add("include 'C:\\FASM\\INCLUDE\\WIN32A.INC' ");
	Form1->Memo5->Lines->Add("entry start");
	Form1->Memo5->Lines->Add("section '.data' data readable writeable");
	for (int i=0; i < Assembler.size(); i++)
	{
		if (Assembler[i+2]=="db")
		{
			Form1->Memo5->Lines->Text = Form1->Memo5->Lines->Text + Assembler[i] +" "+ Assembler[i+2]+ " " + Assembler[i+4];
			Form1->Memo5->Lines->Text = Form1->Memo5->Lines->Text + '\n';
		}
	}
	Form1->Memo5->Lines->Add("section '.code' code readable writeable");
	Form1->Memo5->Lines->Add("entry start");
	for (int z=kolind*6 ;z < Assembler.size(); z++)     //kolind*6
	{
	if (Assembler[z]=="perexod")
		{
		Form1->Memo5->Lines->Text = Form1->Memo5->Lines->Text + '\n';
		}
        else
		Form1->Memo5->Lines->Text = Form1->Memo5->Lines->Text + Assembler[z];
	}
	Form1->Memo5->Lines->Add("XOR AX, AX");
	Form1->Memo5->Lines->Add("XOR BX, BX");
	Form1->Memo5->Lines->Add("XOR CX, CX");
	Form1->Memo5->Lines->Add("invoke ExitProcess,0");
	Form1->Memo5->Lines->Add("section '.idata' import data readable writeable");
	Form1->Memo5->Lines->Add("library kernel32,'KERNEL32.DLL'");
	Form1->Memo5->Lines->Add("include 'C:\\FASM\\INCLUDE\\API\\kernel32.inc'");
	Assembler.clear();
	converter.clear();
	colcomment=0;
}
//---------------------------------------------------------------------------

