//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    �y�o�׌����V�X�e���|���C�����j���[�z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �����@�b��
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
int keyflag;    //1 : ������1�Ԗڂ̔ԍ�
                //2 : ������2�Ԗڂ̔ԍ�
                //3 : ������3�Ԗڂ̔ԍ�


AnsiString keystr;

char TKSS01FileName[MAX_PATH];
char TKSS02FileName[MAX_PATH];
char TKSS03FileName[MAX_PATH];
char TKSS04FileName[MAX_PATH];
char TKSS05FileName[MAX_PATH];
char TKSS06FileName[MAX_PATH];
char TKSS07FileName[MAX_PATH];
char TKSS08FileName[MAX_PATH];
char DEBUG_FLG[MAX_PATH];


TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    OnCreate�C�x���g	�FForm1���쐬�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ������ʂ̏�Ԃ�ݒ肵�܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �t�H�[�����쐬�����Ƃ��C�x���g���ȉ��̏����Ŕ������܂��B
//    OnCreate��OnShow��OnActivate��OnPaint
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    keyflag = 3;
    keystr = "";
    Read_Ini();
    BtnSetEnable();
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    OnClick�C�x���g	�F�{�^���iF12�ȊO�j�����������̏���
//
//  �@�\����
//    �e�{�^����ʂ𔻒肵�p�X���[�h���͉�ʕ\��
//    ���̌�A�e�v���O�������N�����܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::ButtonClick(TObject *Sender)
{
    if ( BtnTKSS01->Focused() && BtnTKSS01->Enabled == false )  return;
    if ( BtnTKSS02->Focused() && BtnTKSS02->Enabled == false )  return;
    if ( BtnTKSS03->Focused() && BtnTKSS03->Enabled == false )  return;
    if ( BtnTKSS04->Focused() && BtnTKSS04->Enabled == false )  return;
    if ( BtnTKSS05->Focused() && BtnTKSS05->Enabled == false )  return;
    if ( BtnTKSS06->Focused() && BtnTKSS06->Enabled == false )  return;
    if ( BtnTKSS07->Focused() && BtnTKSS07->Enabled == false )  return;

    //�p�X���[�h�`�F�b�N�Ȃ�
    if (BtnTKSS08->Focused()) {
        USER_COD=0;
        USER_NAM="";
        BUMO_COD="";
        BUMO_NAM="";
    	Form2->PGMStart(0);
        return;
    }
    keyflag = 3;
    keystr = "";
    Form2->Edit1->Text = "";
    //�p�X���[�h�f�t�H���g�l 01
    Form2->MaskEdit1->Text = "01";
    Form2->ShowModal();
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    OnEnter�C�x���g	�F�{�^�� �t�H�[�J�X�擾�����Ƃ�
//
//  �@�\����
//    �I���{�^���𔻒f���A�N���v���O�����𔻒肵�܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::AllKeyEnter(TObject *Sender)
{
    BtnGetFocus();
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    OnKeyDown�C�x���g	�F���[�U�[���C�ӂ̃L�[�������Ɣ������܂�
//
//  �@�\����
//    �t�@���N�V�����L�[�A���L�[�ɂ��{�^����I�����܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    WORD &Key			�F�L�[�R�[�h
//    TShiftState Shift	�F[Shift]�C[Alt]�C[Ctrl]�L�[�𔻒肵�܂�
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     // �X�e�[�^�X���b�Z�[�W

     if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
     }

     switch(Key){
        case VK_F12:
        case VK_RETURN:
                break;
        case VK_F1:
                BtnTKSS01->SetFocus();
                ButtonClick(Sender);
                break;
        case VK_F2:
                BtnTKSS02->SetFocus();
                ButtonClick(Sender);
                break;
        case VK_F3:
                BtnTKSS03->SetFocus();
                ButtonClick(Sender);
                break;
        case VK_F4:
                BtnTKSS04->SetFocus();
                ButtonClick(Sender);
                break;
        case VK_F5:
                BtnTKSS05->SetFocus();
                ButtonClick(Sender);
                break;
        case VK_F6:
                BtnTKSS06->SetFocus();
                ButtonClick(Sender);
                break;
        case VK_F7:
                BtnTKSS07->SetFocus();
                ButtonClick(Sender);
                break;
        case VK_F8:
                BtnTKSS08->SetFocus();
                ButtonClick(Sender);
                break;
        default:
                break;
     }
     switch(Key){
        case VK_RETURN:
                ButtonClick(Sender);
                break;
        case VK_F12:
            if ( keyflag == 1 )  keystr = " ";
            else  keystr += " ";
            BtnTKSS12Click(Sender);
            break;
         // ����
         case VK_DOWN:
         case VK_RIGHT:
            if ( BtnTKSS01->Enabled == true && BtnTKSS01->Focused())  BtnSetFocus("02");
            if ( BtnTKSS02->Enabled == true && BtnTKSS02->Focused())  BtnSetFocus("03");
            if ( BtnTKSS03->Enabled == true && BtnTKSS03->Focused())  BtnSetFocus("04");
            if ( BtnTKSS04->Enabled == true && BtnTKSS04->Focused())  BtnSetFocus("05");
            if ( BtnTKSS05->Enabled == true && BtnTKSS05->Focused())  BtnSetFocus("06");
            if ( BtnTKSS06->Enabled == true && BtnTKSS06->Focused())  BtnSetFocus("07");
            if ( BtnTKSS07->Enabled == true && BtnTKSS07->Focused())  BtnSetFocus("08");
            if ( BtnTKSS08->Enabled == true && BtnTKSS08->Focused())  BtnSetFocus("12");
            if ( BtnTKSS12->Enabled == true && BtnTKSS12->Focused())  BtnSetFocus("01");
            break;
         // �O��
         case VK_UP:
         case VK_LEFT:
            if ( BtnTKSS01->Enabled == true && BtnTKSS01->Focused())  BtnSetFocus("12");
            if ( BtnTKSS02->Enabled == true && BtnTKSS02->Focused())  BtnSetFocus("01");
            if ( BtnTKSS03->Enabled == true && BtnTKSS03->Focused())  BtnSetFocus("02");
            if ( BtnTKSS04->Enabled == true && BtnTKSS04->Focused())  BtnSetFocus("03");
            if ( BtnTKSS05->Enabled == true && BtnTKSS05->Focused())  BtnSetFocus("04");
            if ( BtnTKSS06->Enabled == true && BtnTKSS06->Focused())  BtnSetFocus("05");
            if ( BtnTKSS07->Enabled == true && BtnTKSS07->Focused())  BtnSetFocus("06");
            if ( BtnTKSS08->Enabled == true && BtnTKSS08->Focused())  BtnSetFocus("07");
            if ( BtnTKSS12->Enabled == true && BtnTKSS12->Focused())  BtnSetFocus("08");
            break;

        default :
        break;
     }
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�			�F�{�^���Ƀt�H�[�J�X���Z�b�g���܂�
//
//  �@�\����
//    �w�肳�ꂽ�@�\�ԍ��ɍ��킹�ă{�^���Ƀt�H�[�J�X���Z�b�g���܂�
//
//  �p�����^����
//    AnsiString str	�F�@�\�ԍ��i1�`8,12�j
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::BtnSetFocus(AnsiString str)
{
     switch(StrToInt(str)){
        case 01:  if( BtnTKSS01->Enabled ) BtnTKSS01->SetFocus();    break;
        case 02:  if( BtnTKSS02->Enabled ) BtnTKSS02->SetFocus();    break;
        case 03:  if( BtnTKSS03->Enabled ) BtnTKSS03->SetFocus();    break;
        case 04:  if( BtnTKSS04->Enabled ) BtnTKSS04->SetFocus();    break;
        case 05:  if( BtnTKSS05->Enabled ) BtnTKSS05->SetFocus();    break;
        case 06:  if( BtnTKSS06->Enabled ) BtnTKSS06->SetFocus();    break;
        case 07:  if( BtnTKSS07->Enabled ) BtnTKSS07->SetFocus();    break;
        case  8:  if( BtnTKSS08->Enabled ) BtnTKSS08->SetFocus();    break;
        case 12:  if( BtnTKSS12->Enabled ) BtnTKSS12->SetFocus();    break;
     }

}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�			�F�N������v���O�������̐ݒ�
//
//  �@�\����
//    �ǂ̃{�^���Ƀt�H�[�J�X������̂����f���ċN������v���O�������������܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::BtnGetFocus()
{
    sDEBUG = "";

    if ( BtnTKSS01->Focused() ) {
        strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKSS01FileName);
        sDEBUG = AnsiString(DEBUG_FLG);
        return;
    }
    if ( BtnTKSS02->Focused() ) {
        strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKSS02FileName);
        return;
    }
    if ( BtnTKSS03->Focused() ) {
        strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKSS03FileName);
        return;
    }
    if ( BtnTKSS04->Focused() ) {
        strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKSS04FileName);
        return;
    }
    if ( BtnTKSS05->Focused() ) {
        strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKSS05FileName);
        return;
    }
    if ( BtnTKSS06->Focused() ) {
        strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKSS06FileName);
        return;
    }
    if ( BtnTKSS07->Focused() ) {
        strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKSS07FileName);
        return;
    }
    if ( BtnTKSS08->Focused() ) {
        strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKSS08FileName);
        return;
    }
    if ( BtnTKSS12->Focused() ) {
        return;
    }
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�			�F�{�^����Enable��ݒ肵�܂�
//
//  �@�\����
//    �e�{�^����Enable��ݒ肵�܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::BtnSetEnable()
{
    if ( TKSS01FileName[0] == '\0' ) BtnTKSS01->Enabled = false;
    else                            BtnTKSS01->Enabled = true;
    if ( TKSS02FileName[0] == '\0' ) BtnTKSS02->Enabled = false;
    else                            BtnTKSS02->Enabled = true;
    if ( TKSS03FileName[0] == '\0' ) BtnTKSS03->Enabled = false;
    else                            BtnTKSS03->Enabled = true;
    if ( TKSS04FileName[0] == '\0' ) BtnTKSS04->Enabled = false;
    else                            BtnTKSS04->Enabled = true;
    if ( TKSS05FileName[0] == '\0' ) BtnTKSS05->Enabled = false;
    else                            BtnTKSS05->Enabled = true;
    if ( TKSS06FileName[0] == '\0' ) BtnTKSS06->Enabled = false;
    else                            BtnTKSS06->Enabled = true;
    if ( TKSS07FileName[0] == '\0' ) BtnTKSS07->Enabled = false;
    else                            BtnTKSS07->Enabled = true;
    if ( TKSS08FileName[0] == '\0' ) BtnTKSS08->Enabled = false;
    else                            BtnTKSS08->Enabled = true;
}

/*----------------------------------------------------------------------------*/
//
//  �T�v
//    ����֐�			�FINI�t�@�C���̓ǂݍ��ݏ���
//
//  �@�\����
//    INI�t�@�C����ǂݍ��ݗL���ȃv���O���������擾���܂�
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::Read_Ini()
{
     int getlen1;
     char windir[MAX_PATH];	//Windows Dir

     //�ݒ�t�@�C���@( "windows\TKSMAIN.ini" or "winnt\TKSMAIN.ini" )
     char INIname[MAX_PATH];

     /*Windows�ިڸ�؂����o*/
     getlen1 = GetWindowsDirectory((LPSTR)windir, sizeof(windir));
     if (getlen1 == 0){
     	ShowMessage("GetWindowsDirectory Fail");
     	return;
     }else {
     	//INI̧�ٖ����߽��ǉ�
     	wsprintf(INIname, "%s%s", windir, "\\TKSSMAIN.ini");	//file name
     }

     // INI̧�ق���̓ǂݍ���
     GetPrivateProfileString("FILE", "PATH", "", StartPATH, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKSS01", "", TKSS01FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKSS02", "", TKSS02FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKSS03", "", TKSS03FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKSS04", "", TKSS04FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKSS05", "", TKSS05FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKSS06", "", TKSS06FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKSS07", "", TKSS07FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKSS08", "", TKSS08FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "DEBUG", "", DEBUG_FLG, MAX_PATH, INIname);
}


/*----------------------------------------------------------------------------*/
//
//  �T�v
//    OnClick�C�x���g	�F�{�^���iF12�j�����������̏���
//
//  �@�\����
//    �v���O�������I�����܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::BtnTKSS12Click(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------










