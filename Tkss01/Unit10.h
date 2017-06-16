//---------------------------------------------------------------------------
#ifndef Unit10H
#define Unit10H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm10 : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *Panel2;
	TButton *Btn_OK;
	TButton *Btn_Cansel;
	TLabel *Lbl_Str1;
	TLabel *Lbl_Str2;
	TLabel *Lbl_Str3;
	TPanel *Panel1;
	TRadioButton *Rdo_from_LOT;
	TRadioButton *Rdo_from_MASTER;
	TLabel *Label3;
	void __fastcall Btn_OKClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Btn_CanselClick(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TForm10(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm10 *Form10;
//---------------------------------------------------------------------------
#endif
