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
#include "TKSS04.h"
#include "NumberEdit.h"
#include <Db.hpp>
#include <DBTables.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
    TPanel *Panel2;
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
    TPanel *Panel12;
    TPanel *PnlTanName;
    TDatabase *Database1;
    TStringGrid *SGr_List;
    TEdit *EdtLOT;
    TEdit *EdtHIN;
    TQuery *Query1;
    TQuery *Query2;
    TPanel *PnlTanCode;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall BtnF01Click(TObject *Sender);
    void __fastcall BtnF05Click(TObject *Sender);
    void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    void __fastcall BtnF10Click(TObject *Sender);
    void __fastcall BtnF11Click(TObject *Sender);
    void __fastcall BtnF07Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall SGr_ListKeyPress(TObject *Sender, char &Key);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall AllKeyEnter(TObject *Sender);
    void __fastcall EdtKeyPress(TObject *Sender, char &Key);
    void __fastcall FormEnter(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Edt_ALLChange(TObject *Sender);
	void __fastcall SGr_ListClick(TObject *Sender);
private:	// ユーザー宣言
    //20170406 Y.Onishi 「削除」実行時、自社品番を考慮
    //bool __fastcall DelData(AnsiString sDTKSHIN, AnsiString sLOTNO);
    bool __fastcall DelData(AnsiString sDTKSHIN, AnsiString sLOTNO, AnsiString sHINBAN);
    int __fastcall KSD01_Serch01(void);//KSD01検索
    int __fastcall MAIN_Serch01(void);

    int  iRowSelTop;
    int  iRowSelBottom;

public:		// ユーザー宣言
	AnsiString __fastcall GetTANNAM(AnsiString strTANSYA);
    void __fastcall ExtractCode(AnsiString str);
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
