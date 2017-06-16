//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>

#pragma hdrstop

#include "Unit1.h"
#include "Unit9.h"
#include <DBTables.hpp>
#include <winbase.h>
#include <shellapi.h>

//���[�U�[���
/*
extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;
*/
extern int KikiType;               // �@��ԍ�PC1,2,3,4
extern int PGNo;

extern char PC12FileName[MAX_PATH];
extern char PC34FileName[MAX_PATH];


int ExeFlag = 0;

int     OLDUSER_COD;
String  OLDUSER_NAM;
String  OLDBUMO_COD;
String  OLDBUMO_NAM;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm9 *Form9;
//---------------------------------------------------------------------------
__fastcall TForm9::TForm9(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//�t�H�[���L�[�_�E����
void __fastcall TForm9::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key){
         // �O��
         case VK_UP:
         case VK_LEFT:
                if( Edit1->Focused() && Edit1->SelStart == 0 && Edit1->SelLength == 0 ){
                    Button2->SetFocus();
                    break;
                }
                if( MaskEdit1->Focused() && MaskEdit1->SelStart == 0 && MaskEdit1->SelLength == 0 ){
                    Edit1->SetFocus();
                    break;
                }
                if( Button1->Focused() ) {
                    MaskEdit1->SetFocus();
                    break;
                }
                if( Button2->Focused() ) {
                    Button1->SetFocus();
                    break;
                }
                break;
         // ����
         case VK_DOWN:
         case VK_RIGHT:
                if( Edit1->Focused() && Edit1->SelStart == Edit1->Text.Length() && Edit1->SelLength == 0 ){
                    MaskEdit1->SetFocus();
                    break;
                }
                if( MaskEdit1->Focused() && MaskEdit1->SelStart == MaskEdit1->Text.Length() && MaskEdit1->SelLength == 0 ){
                    Button1->SetFocus();
                    break;
                }
                if( Button1->Focused() ) {
                    Button2->SetFocus();
                    break;
                }
                if( Button2->Focused() ) {
                    Edit1->SetFocus();
                    break;
                }
                break;

         case VK_RETURN:
                if( Edit1->Focused() ) {
                    MaskEdit1->SetFocus();
                    break;
                }
                if( MaskEdit1->Focused() ) {
                    //Button1->SetFocus();
                    OkClick(Sender);
                    break;
                }
                if( Button1->Focused() ) {
                    OkClick(Sender);
                    break;
                }
                if( Button2->Focused() ) {
                    CancleClick(Sender);
                    break;
                }

                break;
        case VK_ESCAPE:
                CancleClick(Sender);
                break;
        default:
                break;
     }

}
//---------------------------------------------------------------------------
//�L�����Z��
void __fastcall TForm9::CancleClick(TObject *Sender)
{
    //ShowMessage("CancleClick");
    Close();
    Form1->SetFocus();
}
//---------------------------------------------------------------------------
//�p�X���[�h�n�j�Ȃ� �v���O�������N��
void __fastcall TForm9::OkClick(TObject *Sender)
{
    int PassFlag;

	//���̃��[�U�[����ޔ�������
	OLDUSER_COD = Form1->USER_COD;
	OLDUSER_NAM = Form1->USER_NAM;
	OLDBUMO_COD = Form1->BUMO_COD;
	OLDBUMO_NAM = Form1->BUMO_NAM;
    //���[�U�[���A�p�X���[�h�̃`�F�b�N
    PassFlag = PasswordCheck();
	switch(PassFlag)
	{
    case 1:
    	ShowMessage("���[�U������͂��Ă�������");
        Edit1->SetFocus();
        break;

    case 2:
    	ShowMessage("���[�U�����Ԉ���Ă��܂�");
        Edit1->SetFocus();
        break;

    case 3:
    	ShowMessage("�p�X���[�h���Ԉ���Ă��܂�");
        MaskEdit1->SetFocus();
        break;

    case 4:
    	ShowMessage("�p�X���[�h���o�^����Ă��܂���");
        MaskEdit1->SetFocus();
        break;
	default:
		break;
    }
	switch(PassFlag)
	{
    case 1:
    case 2:
    case 3:
    case 4:
		//�O��̃��[�U�[���𕜋A
		Form1->USER_COD = OLDUSER_COD;
		Form1->USER_NAM = OLDUSER_NAM;
		Form1->BUMO_COD = OLDBUMO_COD;
		Form1->BUMO_NAM = OLDBUMO_NAM;
        break;
	default:
    	// �������\��
    	Form1->PnlBumCode->Caption = Form1->BUMO_COD;
    	Form1->PnlBumName->Caption = Form1->BUMO_NAM;
    	Form1->PnlTanCode->Caption = IntToStr(Form1->USER_COD);
    	Form1->PnlTanName->Caption = Form1->USER_NAM;
		Close();
	}
}

//---------------------------------------------------------------------------
//�p�X���[�h�̃`�F�b�N
int __fastcall TForm9::PasswordCheck()
{
     AnsiString sBuf;

     //���[�U�[������

     if ( Edit1->Text.IsEmpty() ) return(1);

     // Initial Query
     QueryUser->Close();
     QueryUser->SQL->Clear();

     // �⍇�����s(�S���҃R�[�h)
     sBuf = "SELECT TANSYA, TANNAM, SZKBSY FROM SM12S WHERE TANSYA = ";
     sBuf += Edit1->Text;

     QueryUser->SQL->Add(sBuf);
     QueryUser->Open();
     QueryUser->Active = true;

     //�S���҃R�[�h������
     if ( QueryUser->Bof == true && QueryUser->Eof ) {
     //�������� �O��
        return(2);
     }


     Form1->USER_COD = StrToInt(QueryUser->FieldValues["TANSYA"]);
     Form1->USER_NAM = QueryUser->FieldValues["TANNAM"];
     Form1->BUMO_COD = QueryUser->FieldValues["SZKBSY"];


     //����������
     // Initial Query
     QueryUser->Close();
     QueryUser->SQL->Clear();

     sBuf = "SELECT BSYCOD, BSYNAM FROM SM13S WHERE BSYCOD = '";

     sBuf += Form1->BUMO_COD + "'";


     QueryUser->SQL->Add(sBuf);
     QueryUser->Open();
     QueryUser->Active = true;

     if ( QueryUser->Bof == true && QueryUser->Eof ) {
     //�������� �O��
         Form1->BUMO_NAM = "";
     } else {
         Form1->BUMO_NAM = QueryUser->FieldValues["BSYNAM"];
     }

     //�p�X���[�h�̌���
     // Initial Query
     QueryUser->Close();
     QueryUser->SQL->Clear();


     sBuf = "SELECT USRID, PASSWD FROM KM11 WHERE USRID = ";
     sBuf = sBuf + IntToStr(Form1->USER_COD);
     sBuf = sBuf + " and ukoymd<='" + FormatDateTime("yyyymmdd",Date()) +"'";   // �L���N�����̔��f��ǉ�

     QueryUser->SQL->Add(sBuf);
     QueryUser->Open();
     QueryUser->Active = true;

     if ( QueryUser->Bof == true && QueryUser->Eof ) {
     //�������� �O��
        return(4);
     }
     //�p�X���[�h�̔�r
     if ( MaskEdit1->Text != QueryUser->FieldValues["PASSWD"] ) {
        //�p�X���[�h�Ԉ���Ă���
        return(3);
     }
     return(0);
}

//---------------------------------------------------------------------------
//�t�H�[���A�N�e�B�u��
void __fastcall TForm9::FormActivate(TObject *Sender)
{
    // 2003/05/13 A.Tamura�ǉ�
    MaskEdit1->Text = "01";
    Edit1->SetFocus();

}
//---------------------------------------------------------------------------
//�t�H�[���쐬��
void __fastcall TForm9::FormCreate(TObject *Sender)
{
    //Database1->Open();

}
//---------------------------------------------------------------------------




void __fastcall TForm9::FormKeyPress(TObject *Sender, char &Key)
{
     switch(Key){
         // �O��
         case VK_RETURN:
                Key = 0;
                break;
     }

}
//---------------------------------------------------------------------------

