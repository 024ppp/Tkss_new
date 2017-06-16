//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit10.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm10 *Form10;
//---------------------------------------------------------------------------
__fastcall TForm10::TForm10(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm10::Btn_OKClick(TObject *Sender)
{

    // 項目編集画面を表示する前の確認画面です。

    // 項目編集画面を初期表示する項目データの表示元を決定します
    if( Rdo_from_LOT->Checked == true ){
    	// 1=選択ロットから表示
    	Form3->iFROM_DATA = 1;
    }

    if( Rdo_from_MASTER->Checked == true ){
    	// 2=製品規格マスターから表示
    	Form3->iFROM_DATA = 2;
    }

    Close();

}
//---------------------------------------------------------------------------

void __fastcall TForm10::FormActivate(TObject *Sender)
{
    // 選択フラグを初期化
	Form3->iFROM_DATA = 0;

    Lbl_Str1->Caption = "現在選択されているロットＮＯは、［" + Form3->sNOW_LOTNO + "］です。";

    Rdo_from_LOT->Checked = true;

}
//---------------------------------------------------------------------------
void __fastcall TForm10::Btn_CanselClick(TObject *Sender)
{

   	Form3->iFROM_DATA = 0;
    Close();

}
//---------------------------------------------------------------------------

