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

    // ���ڕҏW��ʂ�\������O�̊m�F��ʂł��B

    // ���ڕҏW��ʂ������\�����鍀�ڃf�[�^�̕\���������肵�܂�
    if( Rdo_from_LOT->Checked == true ){
    	// 1=�I�����b�g����\��
    	Form3->iFROM_DATA = 1;
    }

    if( Rdo_from_MASTER->Checked == true ){
    	// 2=���i�K�i�}�X�^�[����\��
    	Form3->iFROM_DATA = 2;
    }

    Close();

}
//---------------------------------------------------------------------------

void __fastcall TForm10::FormActivate(TObject *Sender)
{
    // �I���t���O��������
	Form3->iFROM_DATA = 0;

    Lbl_Str1->Caption = "���ݑI������Ă��郍�b�g�m�n�́A�m" + Form3->sNOW_LOTNO + "�n�ł��B";

    Rdo_from_LOT->Checked = true;

}
//---------------------------------------------------------------------------
void __fastcall TForm10::Btn_CanselClick(TObject *Sender)
{

   	Form3->iFROM_DATA = 0;
    Close();

}
//---------------------------------------------------------------------------

