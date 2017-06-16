//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
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
#include "NumberEdit.h"
//---------------------------------------------------------------------------
class TForm2 : public TForm
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
	TPanel *Pnl_List;
	TSplitter *Splitter1;
	TPanel *Panel3;
	TScrollBox *ScrollBox1;
	TPanel *Panel17;
	TPageControl *PgCtr_List;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TPanel *Pnl_t02;
	TPanel *Pnl_t04;
	TPanel *Pnl_t05;
	TPanel *Pnl_t06;
	TPanel *Pnl_t07;
	TPanel *Pnl_t03;
	TPanel *Pnl_t09;
	TPanel *Pnl_t08;
	TPanel *Pnl_t10;
	TPanel *Pnl_t11;
	TPanel *Pnl_t12;
	TPanel *Pnl_KIKAKU_HANI;
	TLabel *Label1;
	TNumberEdit *Nmb_KIKAKU_HANI_MIN;
	TNumberEdit *Nmb_KIKAKU_HANI_MAX;
	TPanel *Pnl_KIKAKU_KIJYUN;
	TNumberEdit *Nmb_KIKAKU_KIJYUN_MID;
	TNumberEdit *Nmb_KIKAKU_KIJYUN_MAX;
	TNumberEdit *Nmb_KIKAKU_KIJYUN_MIN;
	TPanel *Pnl_SYURUI;
	TRadioButton *Rdo_KIKAKU_SYURUI_MINMAX;
	TRadioButton *Rdo_KIKAKU_SYURUI_MAX;
	TRadioButton *Rdo_KIKAKU_SYURUI_MIN;
	TPanel *Panel21;
	TRadioButton *Rdo_KIKAKU_SHITEI_HANI;
	TRadioButton *Rdo_KIKAKU_SHITEI_KIJYUN;
	TRadioButton *Rdo_KIKAKU_SHITEI_MOJI;
	TPanel *Pnl_KIKAKU_MOJI;
	TPanel *Pnl_MANMIN_PRT;
	TRadioButton *Rdo_MANMIN_PRT_ON;
	TRadioButton *Rdo_MANMIN_PRT_OFF;
	TPanel *Pnl_t13;
	TPanel *Pnl_t18;
	TPanel *Pnl_t15;
	TPanel *Pnl_t14;
	TPanel *Pnl_VALUE;
	TRadioButton *Rdo_VALUE_NORMAL;
	TRadioButton *Rdo_VALUE_KAKUDO;
	TRadioButton *Rdo_VALUE_OK;
	TRadioButton *Rdo_VALUE_TEXT;
	TPanel *Pnl_t16;
	TPanel *Pnl_t19;
	TPanel *Pnl_t17;
	TPanel *Panel2;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *Panel7;
	TPanel *Pnl_t20;
	TPanel *PnlUPDYMD;
	TPanel *Pnl_t21;
	TPanel *PnlUPDCHR;
	TEdit *Edt_SKTKMK_JPN;
	TEdit *Edt_SKTKMK_ENG;
	TEdit *Edt_SKTKMK_ENG_SUB;
	TEdit *Edt_SKTKMK_JPN_SUB;
	TComboBox *Cmb_SKTKIKI;
	TPanel *Panel20;
	TRadioButton *Rdo_SKTKMK_ON;
	TRadioButton *Rdo_SKTKMK_OFF;
	TPanel *Panel4;
	TRadioButton *Rdo_TKBKMK_ON;
	TRadioButton *Rdo_TKBKMK_OFF;
	TEdit *Edt_KIKAKU_STRING;
	TNumberEdit *Nmb_KIKAKU_DOUBLE;
	TNumberEdit *Nmb_N;
	TNumberEdit *Nmb_VALUE_DOUBLE;
	TRadioButton *Rdo_List1_Order1;
	TRadioButton *Rdo_List1_Order2;
	TRadioButton *Rdo_List1_Order3;
	TStringGrid *SGr_List;
	TRadioButton *Rdo_List2_Order1;
	TRadioButton *Rdo_List2_Order2;
	TRadioButton *Rdo_List2_Order3;
	TStringGrid *SGr_List2;
	TComboBox *Cmb_TANI;
    void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Pnl_ListResize(TObject *Sender);
	void __fastcall Rdo_KIKAKU_SHITEI_HANIClick(TObject *Sender);
	void __fastcall Rdo_KIKAKU_SHITEI_KIJYUNClick(TObject *Sender);
	void __fastcall Rdo_KIKAKU_SHITEI_MOJIClick(TObject *Sender);
	void __fastcall Rdo_KIKAKU_SYURUI_MINMAXClick(TObject *Sender);
	void __fastcall Rdo_KIKAKU_SYURUI_MAXClick(TObject *Sender);
	void __fastcall Rdo_KIKAKU_SYURUI_MINClick(TObject *Sender);
	void __fastcall PgCtr_ListChange(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Rdo_VALUE_NORMALClick(TObject *Sender);
	void __fastcall Rdo_VALUE_KAKUDOClick(TObject *Sender);
	void __fastcall Rdo_VALUE_OKClick(TObject *Sender);
	void __fastcall Rdo_VALUE_TEXTClick(TObject *Sender);
	void __fastcall BtnF08F09Click(TObject *Sender);
	void __fastcall SGr_ListDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
	void __fastcall SGr_ListClick(TObject *Sender);
	void __fastcall SGr_ListKeyPress(TObject *Sender, char &Key);
	void __fastcall SGr_ListSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall Rdo_List1_OrderClick(TObject *Sender);
	void __fastcall Rdo_List2_OrderClick(TObject *Sender);
	void __fastcall Nmb_KIKAKU_DOUBLEExit(TObject *Sender);
	void __fastcall Edt_ALLChange(TObject *Sender);
private:	// ユーザー宣言

	//測定項目（材料証明項目）マスター
	struct KSM11_12_DATA {
		char	KOMK_NO[5];			// 項目NO
		char	ORDER_NO[5];		// 表示順
		char	KOMK_NM[41];		// 測定項目名称（日本語）
		char	KOMK_ENG[41];		// 測定項目名称（英語）
		char	KOMK_SUB[21];		// 測定項目サブ名称（日本語）
		char	KOMK_SUB_ENG[21];	// 測定項目サブ名称（英語）
		char	KIKI_NO[3];			// 測定機器NO
		char	KIKI_NM[41];		// 測定機器名称
		char    TANI[21];			// 単位
		char    KIKA_TYPE[2];		// 規格タイプ
		char    KIKA_KIND[2];		// 規格種類
		char    KIKA_DECI[2];		// 規格小数点以下桁数
		char    KIKA_NUM1[13];		// 規格値１
		char    KIKA_NUM2[13];		// 規格値２
		char    KIKA_NUM3[13];		// 規格値３
		char    KIKA_STR[41];		// 規格値文字
//		char    KIKA_SUB1[21];		// 規格値サブ１
//		char    KIKA_SUB2[21];		// 規格値サブ２
//		char    KIKA_SUB3[21];		// 規格値サブ３
		char    SOKU_SU[3];			// 測定指示n数
		char    SOKU_FLG[2];		// 測定項目の有無
		char    TOKU_FLG[2];		// 特別項目の有無
		char    KIKA_PRT[2];		// 上限下限値の印刷
		char    VALUE_TYPE[2];		// 測定値表現
		char    VALUE_DECI[2];		// 測定値小数点以下桁数
		char	ADDYMD[9];			// 登録日
		char	ADDTIM[5];			// 登録時間
		char	UPDYMD[11];			// 変更日
		char	UPDTIM[5];			// 変更時間
		char   	UPDCHR[7];			// 更新者（コード）
        char    UPDNAM[51];			// 更新者（名称）
		char   	UPDCNT[4];			// 更新回数
	} tmpKSM11_12_DATA;

    int  iRowSelTop;
    int  iRowSelBottom;

	AnsiString __fastcall GridLineCopy(TStringGrid* sg, int iCpyIndex);
	void __fastcall GridLinePaste( TStringGrid* sg, int iPstIndex, AnsiString sUpdFlg);

public:		// ユーザー宣言
    __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
