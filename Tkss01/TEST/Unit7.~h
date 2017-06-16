//---------------------------------------------------------------------------
#ifndef Unit7H
#define Unit7H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <Clipbrd.hpp>
#include "NumberEdit.h"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TForm7 : public TForm
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
	TPanel *Pnl_List;
	TSplitter *Splitter1;
	TPanel *Panel1;
	TScrollBox *ScrollBox1;
	TPanel *Panel17;
	TPanel *Pnl_t05;
	TComboBox *Cbo_KOMK_NM;
	TPanel *Pnl_t15;
	TNumberEdit *Num_SOKU_SU;
	TPanel *Pnl_t01;
	TPanel *Pnl_HINBAN;
	TPanel *Panel2;
	TComboBox *Cbo_LOT;
	TStringGrid *SGr_vSOKUTEI;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Pnl_KIKAKU;
	TPanel *Panel7;
	TPanel *Pnl_TANI;
	TMaskEdit *MEdt_SOKU_DATE;
	TPanel *Panel10;
	TPanel *Pnl_KIKI;
	TLabel *Label1;
    TPanel *Panel12;
    TSplitter *Splitter2;
    TPanel *Panel16;
	TStringGrid *SGr_vSOKU_SYUKA;
	TStringGrid *SGr_vRIRE_SYUKA;
	TStringGrid *SGr_Title;
	TPanel *Panel13;
	TPanel *PnlTanName;
	TQuery *Query1;
	TQuery *Query2;
	TLabel *Lab_KIKAKU_UP;
	TLabel *Lab_KIKAKU_LOW;
	TLabel *Lab_KIKAKU;
    void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Get_KSD11(void);
	void __fastcall Cbo_Set(void);
	void __fastcall Cbo_KOMK_NMChange(TObject *Sender);
	void __fastcall Set_LOT_GRID(void);
	void __fastcall FormSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
	void __fastcall BtnF08Click(TObject *Sender);
	void __fastcall SGr_vRIRE_SYUKATopLeftChanged(TObject *Sender);
	void __fastcall BtnF05Click(TObject *Sender);
	void __fastcall BtnF07Click(TObject *Sender);
	void __fastcall BtnF11Click(TObject *Sender);
	void __fastcall BtnF09Click(TObject *Sender);
	void __fastcall BtnF10Click(TObject *Sender);
	AnsiString __fastcall GetTANTO(AnsiString CODE);
	void __fastcall Cbo_LOTChange(TObject *Sender);
	void __fastcall GetKIKAKU(int iIndex,double *dMAX,double *dMIN);
	void __fastcall Num_SOKU_SUExit(TObject *Sender);
	void __fastcall Num_SOKU_SUKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall SGr_vSOKU_SYUKAExit(TObject *Sender);
	void __fastcall SGr_vRIRE_SYUKAExit(TObject *Sender);
	void __fastcall SGr_vSOKUTEIExit(TObject *Sender);
	void __fastcall GRID_INIT(void);
	void __fastcall SGr_vSOKU_SYUKATopLeftChanged(TObject *Sender);
	void __fastcall GRID_DrawCell(TObject *Sender, int ACol,int ARow, TRect &Rect, TGridDrawState State);
	bool __fastcall NEW_INSPECT_SETOK( int iINSPECT_NO );
    int __fastcall  GET_NSU( void );
    int __fastcall GET_HANTEI(void);

//2003.05.12 E.Takase Add
	AnsiString __fastcall GetTANTO2(AnsiString CODE);
	void __fastcall SGr_vSOKUTEIKeyPress(TObject *Sender, char &Key);
	void __fastcall BtnF04Click(TObject *Sender);
    void __fastcall MEdt_SOKU_DATEExit(TObject *Sender);
    void __fastcall SGr_vSOKUTEISelectCell(TObject *Sender, int ACol,int ARow, bool &CanSelect);
    void __fastcall Num_SOKU_SUEnter(TObject *Sender);
    void __fastcall SGr_vSOKUTEIEnter(TObject *Sender);
    void __fastcall SGr_vSOKU_SYUKAEnter(TObject *Sender);
    void __fastcall SGr_vRIRE_SYUKAEnter(TObject *Sender);
    void __fastcall Cbo_KOMK_NMEnter(TObject *Sender);
    void __fastcall Cbo_KOMK_NMExit(TObject *Sender);
    void __fastcall MEdt_SOKU_DATEEnter(TObject *Sender);

//2003.10.7 A.Tamura Add
    int  __fastcall GetSOKUTEI_KOMK_MORE(int iCBO_INDEX);
	void __fastcall GetKIKAKU2(int iIndex,double *dMAX,double *dMIN);

private:	// ユーザー宣言
public:		// ユーザー宣言
    TClipboard *ClpBrd;
    bool fFind;
    __fastcall TForm7(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm7 *Form7;
//---------------------------------------------------------------------------
#endif
