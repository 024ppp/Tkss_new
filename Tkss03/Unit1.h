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
#include <string.h>
#include <math.h>
#include "Tkss03.h"
#include "NumberEdit.h"
#include <Db.hpp>
#include <DBTables.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
    TPanel *Panel2;
    TPanel *Panel3;
    TPanel *Panel4;
    TPanel *Panel5;
    TPanel *Panel6;
    TPanel *PnlBumCode;
    TStatusBar *SBr1;
    TPanel *Panel9;
    TPanel *Panel1;
    TButton *BtnF01;
    TButton *BtnF02;
    TButton *BtnF03;
    TButton *BtnF04;
    TButton *BtnF05;
    TButton *BtnF06;
    TButton *BtnF07;
    TButton *BtnF08;
    TButton *BtnF09;
    TButton *BtnF10;
    TButton *BtnF11;
    TButton *BtnF12;
    TPanel *PnlBumName;
    TPanel *Panel24;
    TPanel *Panel22;
    TPanel *Panel12;
    TPanel *PnlTanName;
    TDatabase *Database1;
    TStringGrid *SGr_List;
    TEdit *EdtLOT;
    TEdit *EdtHIN;
    TEdit *EdtSETMEMO;
    TEdit *EdtSETHIN;
    TEdit *EdtSETLOT;
    TQuery *Query1;
    TQuery *Query2;
    TSplitter *Splitter1;
    TPanel *PnlTanCode;
    TPanel *PnlUPDCHR;
    TEdit *EdtSETBAN;
    TEdit *EdtMAXBAN;
    TPanel *Panel7;
    TQuery *Query3;
    TPanel *Panel8;
        TEdit *EdtUPDYMD;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall BtnF01Click(TObject *Sender);
    void __fastcall BtnF05Click(TObject *Sender);
    void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    void __fastcall BtnF08Click(TObject *Sender);
    void __fastcall BtnF09Click(TObject *Sender);
    void __fastcall BtnF10Click(TObject *Sender);
    void __fastcall BtnF11Click(TObject *Sender);
    void __fastcall BtnF07Click(TObject *Sender);
    void __fastcall SGr_ListSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall SGr_ListKeyPress(TObject *Sender, char &Key);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall AllKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall EdtKeyPress(TObject *Sender, char &Key);
    void __fastcall FormEnter(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Edt_ALLChange(TObject *Sender);
private:	// ユーザー宣言
    bool __fastcall AddData();
    bool __fastcall CollectData();
    bool __fastcall DelData();
    bool NotFound;
    int  __fastcall KSD91_Serch01(void);		// KSD91検索
    bool __fastcall KSD91_Serch02(void);	// KSD91 2重登録確認
    int  __fastcall MAIN_Serch01(void);
    void __fastcall Tmp_KSD91_SYOKIKA(void);

public:		// ユーザー宣言
    void __fastcall ExtractCode(AnsiString str);
    __fastcall TForm1(TComponent* Owner);
    long ROWPOINT;								//「戻る」のとき保存しないで終了にしたとき0
    AnsiString __fastcall DelSEPA(AnsiString sYMD);                             //20160804 年月日区切り文字除去関数
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
