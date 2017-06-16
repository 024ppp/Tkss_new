//---------------------------------------------------------------------------
#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "NumberEdit.h"
//---------------------------------------------------------------------------
class TForm6 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
    TPanel *Panel9;
    TPanel *Panel16;
	TPanel *Panel17;
	TPanel *Pnl_t01;
	TPanel *Pnl_HINBAN;
	TPanel *Pnl_t09;
	TPanel *Pnl_t08;
	TPanel *Pnl_t10;
	TPanel *Pnl_t11;
	TPanel *Pnl_t12;
	TPanel *Pnl_t14;
	TPanel *Pnl_t16;
	TPanel *Pnl_t17;
	TPanel *Pnl_t02;
	TPanel *Pnl_t04;
	TPanel *Pnl_t05;
	TPanel *Pnl_t06;
	TPanel *Pnl_t07;
	TPanel *Pnl_t03;
	TPanel *Pnl_t18;
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
	TPanel *Pnl_t15;
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
	TEdit *Edt_KIKAKU_STRING;
	TPanel *Pnl_MANMIN_PRT;
	TRadioButton *Rdo_MANMIN_PRT_ON;
	TRadioButton *Rdo_MANMIN_PRT_OFF;
	TPanel *Pnl_t13;
	TPanel *Pnl_VALUE;
	TRadioButton *Rdo_VALUE_NORMAL;
	TRadioButton *Rdo_VALUE_KAKUDO;
	TRadioButton *Rdo_VALUE_OK;
	TRadioButton *Rdo_VALUE_TEXT;
	TPanel *Pnl_t19;
	TNumberEdit *Nmb_KIKAKU_DOUBLE;
	TNumberEdit *Nmb_N;
	TNumberEdit *Nmb_VALUE_DOUBLE;
	TComboBox *Cmb_TANI;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Rdo_KIKAKU_SHITEI_HANIClick(TObject *Sender);
    void __fastcall Rdo_KIKAKU_SHITEI_KIJYUNClick(TObject *Sender);
    void __fastcall Rdo_KIKAKU_SHITEI_MOJIClick(TObject *Sender);
    void __fastcall Rdo_KIKAKU_SYURUI_MINMAXClick(TObject *Sender);
    void __fastcall Rdo_KIKAKU_SYURUI_MAXClick(TObject *Sender);
    void __fastcall Rdo_KIKAKU_SYURUI_MINClick(TObject *Sender);
    void __fastcall BtnF12Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Rdo_VALUE_NORMALClick(TObject *Sender);
	void __fastcall Rdo_VALUE_KAKUDOClick(TObject *Sender);
	void __fastcall Rdo_VALUE_OKClick(TObject *Sender);
	void __fastcall Rdo_VALUE_TEXTClick(TObject *Sender);
	void __fastcall Nmb_KIKAKU_DOUBLEExit(TObject *Sender);
	void __fastcall BtnF08Click(TObject *Sender);
	void __fastcall Edt_ALLChange(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall BtnF02Click(TObject *Sender);
	void __fastcall BtnF03Click(TObject *Sender);
private:	// ���[�U�[�錾
	void __fastcall SetColor( int iSKB_NO );
public:		// ���[�U�[�錾
    __fastcall TForm6(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif