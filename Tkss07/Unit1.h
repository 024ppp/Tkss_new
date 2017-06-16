//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "NumberEdit.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
    TPanel *Panel170;
    TPanel *Panel5;
    TPanel *Panel6;
	TPanel *PnlBumCode;
	TPanel *PnlBumName;
    TPanel *Panel1;
	TPanel *PnlTanCode;
	TPanel *PnlTanName;
    TStatusBar *SBr1;
    TPanel *Panel9;
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
    TPanel *Pnl_List;
    TStringGrid *SGr_List;
    TSplitter *Splitter1;
    TPanel *Panel3;
    TPanel *Panel27;
	TEdit *EdtKMK_NM_JPN;
    TPanel *Panel22;
	TEdit *EdtKMK_NM_ENG;
    TPanel *PnlUPDYMD1;
	TPanel *PnlUPDYMD;
    TPanel *PnlUPDCHR1;
	TPanel *PnlUPDCHR;
    TPanel *Panel2;
	TPanel *Panel28;
	TBitBtn *BtnListUp;
	TBitBtn *BtnListDown;
	TLabel *LblListCnt;
	TLabel *Label1;
	TDatabase *Database1;
	TQuery *Query1;
	TLabel *Label2;
	TQuery *Query2;
    void __fastcall Pnl_ListResize(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtnF05Click(TObject *Sender);
	void __fastcall BtnF02Click(TObject *Sender);
	void __fastcall BtnF03Click(TObject *Sender);
	void __fastcall SGr_ListKeyPress(TObject *Sender, char &Key);
	void __fastcall SGr_ListSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall SGr_ListDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtnF08Click(TObject *Sender);
	void __fastcall BtnF11Click(TObject *Sender);
	void __fastcall BtnF12Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtnF09Click(TObject *Sender);
	void __fastcall BtnF10Click(TObject *Sender);
	void __fastcall BtnListUpClick(TObject *Sender);
	void __fastcall BtnListDownClick(TObject *Sender);
	void __fastcall SGr_ListRowMoved(TObject *Sender, int FromIndex,
          int ToIndex);
	void __fastcall SGr_ListClick(TObject *Sender);
	void __fastcall Edt_ALLChange(TObject *Sender);

private:	// ユーザー宣言
	int     USER_COD;
	String  USER_NAM;
	String  BUMO_COD;
	String  BUMO_NAM;

	//タイトル項目マスター
	struct KSM21_DATA {
		char	KMK_NO[5];			// 項目NO
		char	ORDER_NO[5];		// 表示順
		char	KMK_NM_JPN[129];	// 項目名（日本語）
		char	KMK_NM_ENG[129];	// 項目名（英語）
		char	NOUPD_FLG[2];		// 修正･削除不可能項目
		char	ADDYMD[9];			// 登録日
		char	ADDTIM[5];			// 登録時間
		char	UPDYMD[11];			// 変更日
		char	UPDTIM[5];			// 変更時間
		char   	UPDCHR[7];			// 更新者（コード）
		char   	UPDNAM[51];			// 更新者（名称）
		char   	UPDCNT[4];			// 更新回数
	} tmpKSM21_DATA;

    int  iKMK_NO_MAX;
	int  ROWPOINT;
    int  iRowSelTop;
    int  iRowSelBottom;

    bool DataSave;

    AnsiString sEdtKMK_NM_JPN_Old;
    AnsiString sEdtKMK_NM_ENG_Old;

    void __fastcall RowExchange(int FromIndex, int ToIndex);
    bool __fastcall AddData();
    bool __fastcall UpdData();
	bool __fastcall UpdData_ORDER_NO(AnsiString sKMK_NO, AnsiString sORDER_NO);
    bool __fastcall DelData();

public:		// ユーザー宣言
    __fastcall TForm1(TComponent* Owner);

    void __fastcall ExtractCode(AnsiString str);
	AnsiString __fastcall GetTANNAM(AnsiString strTANSYA);
    
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
