//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Grids.hpp>
#include <Graphics.hpp>
#include <Windows.h>
#include <string.h>


#define MAX_PATH 256
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
    TStatusBar *SBr1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TPanel *Panel1;
    TPanel *Panel2;
    TPanel *Panel3;
    TPanel *Panel4;
    TPanel *Panel5;
    TPanel *Panel6;
    TPanel *Panel9;
    TImage *Image1;
    TButton *BtnTKSS01;
    TButton *BtnTKSS02;
    TButton *BtnTKSS03;
    TButton *BtnTKSS05;
    TButton *BtnTKSS06;
    TButton *BtnTKSS07;
    TButton *BtnTKSS08;
	TButton *BtnTKSS04;
	TButton *BtnTKSS12;
	TLabel *Label6;
    void __fastcall ButtonClick(TObject *Sender);
    void __fastcall AllKeyEnter(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall BtnTKSS12Click(TObject *Sender);
private:	// ユーザー宣言

    void __fastcall BtnGetFocus();
    void __fastcall BtnSetFocus(AnsiString str);
    void __fastcall BtnSetEnable();
    void __fastcall Read_Ini();

public:		// ユーザー宣言
    __fastcall TForm1(TComponent* Owner);
    char StartFileName[MAX_PATH];
    char StartPATH[MAX_PATH];

    int     USER_COD;
    String  USER_NAM;
    String  BUMO_COD;
    String  BUMO_NAM;
    AnsiString	sDEBUG;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
