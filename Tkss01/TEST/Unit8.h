//---------------------------------------------------------------------------
#ifndef Unit8H
#define Unit8H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TForm8 : public TForm
{
__published:	// IDE 管理のコンポーネント
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
    TPanel *Panel1;
    TPanel *Panel4;
    TPanel *Panel2;
    TPanel *Panel3;
    TPanel *Panel5;
    TPanel *Panel6;
	TStringGrid *SGr_vRIRE_SYUKA;
    TLabel *Label1;
    TSplitter *Splitter2;
    TLabel *Label2;
    TPanel *Pnl_TitleTopLeft;
    TPanel *Panel8;
	TQuery *Query1;
	TQuery *Query2;
	TStringGrid *SGr_vSOKU_SYUKA;
    void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Set_LOT_GRID(void);
	void __fastcall GET_KSD01(void);
	void __fastcall BtnF11Click(TObject *Sender);
	void __fastcall SGr_vRIRE_SYUKADrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall BtnF01Click(TObject *Sender);
	//void __fastcall BtnF02Click(TObject *Sender);
	//void __fastcall BtnF03Click(TObject *Sender);
	void __fastcall BtnF05Click(TObject *Sender);
	void __fastcall SGr_vRIRE_SYUKASelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
	void __fastcall SGr_vSOKU_SYUKASelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
	void __fastcall SGr_vSOKU_SYUKADrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall SGr_vSOKU_SYUKAExit(TObject *Sender);
	void __fastcall FormEnter(TObject *Sender);
	void __fastcall SGr_vRIRE_SYUKAExit(TObject *Sender);
	void __fastcall SET_INIT_FLAG(void);
    void __fastcall SGr_vRIRE_SYUKAKeyPress(TObject *Sender, char &Key);
    void __fastcall SGr_vSOKU_SYUKAKeyPress(TObject *Sender, char &Key);
private:	// ユーザー宣言
public:		// ユーザー宣言
    __fastcall TForm8(TComponent* Owner);
    bool fFind;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm8 *Form8;
//---------------------------------------------------------------------------
#endif
