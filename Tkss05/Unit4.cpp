//---------------------------------------------------------------------------
//
//  Unit4.cpp
//    �y�o�׌����V�X�e���|���i�K�i�}�X�^�[�z
//    ���荀�ڕҏW�t�H�[���iTForm4�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �c���@�֎i
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCreate�C�x���g	�FForm4���쐬�����Ƃ��ɔ������܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm4::FormCreate(TObject *Sender)
{
    Pnl_KIKAKU_KIJYUN->Left = Pnl_KIKAKU_HANI->Left;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnActivate�C�x���g	�F�t�H�[�����A�N�e�B�u�ɂȂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �����\���ɕK�v�ȃf�[�^��ݒ肵�܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::FormActivate(TObject *Sender)
{

    int			i, k;
    AnsiString	sBuf;


    // �i��
	Pnl_HINBAN->Caption = Form1->SGr_SOKUT->Cells[1][Form1->SGr_SOKUT->Row];

    // ���荀�ځi���{��j
    Edt_SKTKMK_JPN->Text = Form1->SGr_SOKUT->Cells[2][Form1->SGr_SOKUT->Row];

    // ���ږ��i�p��j
    Edt_SKTKMK_ENG->Text = Form1->SGr_SOKUT->Cells[4][Form1->SGr_SOKUT->Row];

    // ���荀�ڃT�u���́i���{��j
    Edt_SKTKMK_JPN_SUB->Text = Form1->SGr_SOKUT->Cells[3][Form1->SGr_SOKUT->Row];

    // ���荀�ڃT�u���́i�p��j
    Edt_SKTKMK_ENG_SUB->Text = Form1->SGr_SOKUT->Cells[16][Form1->SGr_SOKUT->Row];

    // ����@��
    k = Form1->SGr_SOKUT->Cells[17][Form1->SGr_SOKUT->Row].ToIntDef(-1);
    if( k == -1 ){
	    Cmb_SKTKIKI->ItemIndex = 0;
    }
    else {
    	for( i = 0; i < Form1->iKIKI_Cnt; i++){
    		if( Form1->iKIKI[i] == k ){
			    Cmb_SKTKIKI->ItemIndex = i;
            	break;
        	}
    	}
    }

    // �P��
    Cmb_TANI->Text = Form1->SGr_SOKUT->Cells[5][Form1->SGr_SOKUT->Row];

	// ���荀�ڂƂ��Ă̈���
    switch( Form1->SGr_SOKUT->Cells[10][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 0: Rdo_SKTKMK_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_SKTKMK_ON->Checked = true;
          		break;
   	}

	// ���ʍ��ڂƂ��Ă̈���
    switch( Form1->SGr_SOKUT->Cells[11][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 1: Rdo_TKBKMK_ON->Checked = true;
				break;
		case 0:
        default:Rdo_TKBKMK_OFF->Checked = true;
          		break;
   	}

	// �K�i�i�w����@�j
    switch( Form1->SGr_SOKUT->Cells[18][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SHITEI_MOJI->Checked = true;
                Rdo_KIKAKU_SHITEI_MOJIClick( Rdo_KIKAKU_SHITEI_MOJI );
				break;
		case 2: Rdo_KIKAKU_SHITEI_KIJYUN->Checked = true;
                Rdo_KIKAKU_SHITEI_KIJYUNClick( Rdo_KIKAKU_SHITEI_KIJYUN );
				break;
		case 1:
        default:Rdo_KIKAKU_SHITEI_HANI->Checked = true;
                Rdo_KIKAKU_SHITEI_HANIClick( Rdo_KIKAKU_SHITEI_HANI );
          		break;
   	}

	// �K�i�i��ށj
    switch( Form1->SGr_SOKUT->Cells[19][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SYURUI_MIN->Checked = true;
        		Rdo_KIKAKU_SYURUI_MINClick( Rdo_KIKAKU_SYURUI_MIN );
				break;
		case 2: Rdo_KIKAKU_SYURUI_MAX->Checked = true;
        		Rdo_KIKAKU_SYURUI_MAXClick( Rdo_KIKAKU_SYURUI_MAX );
				break;
		case 1:
        default:Rdo_KIKAKU_SYURUI_MINMAX->Checked = true;
        		Rdo_KIKAKU_SYURUI_MINMAXClick( Rdo_KIKAKU_SYURUI_MINMAX );
          		break;
   	}

	// �K�i�i��������l�̈���j
    switch( Form1->SGr_SOKUT->Cells[28][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 0: Rdo_MANMIN_PRT_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_MANMIN_PRT_ON->Checked = true;
          		break;
   	}

	// �K�i�i�����_�ȉ������j
    Nmb_KIKAKU_DOUBLE->Text = IntToStr(Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0));

	// �K�i�l�i�͈͎w��j
    Nmb_KIKAKU_HANI_MIN->FPos = Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0);
    Nmb_KIKAKU_HANI_MAX->FPos = Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0);
    Nmb_KIKAKU_HANI_MIN->Text = Form1->SGr_SOKUT->Cells[21][Form1->SGr_SOKUT->Row];
    if( Form1->SGr_SOKUT->Cells[18][Form1->SGr_SOKUT->Row].ToIntDef(-1) == 1 ){
	    Nmb_KIKAKU_HANI_MAX->Text = Form1->SGr_SOKUT->Cells[22][Form1->SGr_SOKUT->Row];
    }
    else {
	    Nmb_KIKAKU_HANI_MAX->Text = "0";
    }

	// �K�i�l�i��l�w��j
    Nmb_KIKAKU_KIJYUN_MID->FPos = Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MAX->FPos = Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MIN->FPos = Form1->SGr_SOKUT->Cells[20][Form1->SGr_SOKUT->Row].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MID->Text = Form1->SGr_SOKUT->Cells[21][Form1->SGr_SOKUT->Row];
    if( Form1->SGr_SOKUT->Cells[18][Form1->SGr_SOKUT->Row].ToIntDef(-1) == 2 ){
    	Nmb_KIKAKU_KIJYUN_MAX->Text = Form1->SGr_SOKUT->Cells[22][Form1->SGr_SOKUT->Row];
    	Nmb_KIKAKU_KIJYUN_MIN->Text = Form1->SGr_SOKUT->Cells[23][Form1->SGr_SOKUT->Row];
    }
    else {
    	Nmb_KIKAKU_KIJYUN_MAX->Text = "0";
    	Nmb_KIKAKU_KIJYUN_MIN->Text = "0";
    }

	// �K�i�l�i�����w��j
    Edt_KIKAKU_STRING->Text = Form1->SGr_SOKUT->Cells[24][Form1->SGr_SOKUT->Row];

	// ����l�i�l�\���j
    switch( Form1->SGr_SOKUT->Cells[8][Form1->SGr_SOKUT->Row].ToIntDef(-1) ){
		case 3: Rdo_VALUE_TEXT->Checked = true;
				break;
		case 2: Rdo_VALUE_OK->Checked = true;
				break;
		case 1: Rdo_VALUE_KAKUDO->Checked = true;
				break;
		case 0:
        default:Rdo_VALUE_NORMAL->Checked = true;
          		break;
   	}

	// ����l�i�����_�ȉ������j
    Nmb_VALUE_DOUBLE->Text = IntToStr(Form1->SGr_SOKUT->Cells[29][Form1->SGr_SOKUT->Row].ToIntDef(0));

	// ����l�i���悎���j
    Nmb_N->Text = IntToStr(Form1->SGr_SOKUT->Cells[7][Form1->SGr_SOKUT->Row].ToIntDef(2));

    // ���x���̐F��ݒ肵�܂�
    SetColor(Form1->SGr_SOKUT->Cells[15][Form1->SGr_SOKUT->Row].ToIntDef(2));

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�Q�F�O���v�{�^�������������̏���
//
//  �@�\����
//    �t�H�[�J�X��1�O�Ɉړ����܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::BtnF02Click(TObject *Sender)
{
	keybd_event(VK_SHIFT,0,0,0);
	keybd_event(VK_TAB,0,0,0);
	keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
	keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�R�F�����v�{�^�������������̏���
//
//  �@�\����
//    �t�H�[�J�X��1���Ɉړ����܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::BtnF03Click(TObject *Sender)
{
	keybd_event(VK_TAB,0,0,0);
	keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�W�F�ݒ�v�{�^�������������̏���
//
//  �@�\����
//    �C���������e�����C���t�H�[���̑��荀��Grid�ɐݒ肵�܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm4::BtnF08Click(TObject *Sender)
{

    AnsiString		sBuf;


    // ���̓f�[�^�̃`�F�b�N
    if(Edt_SKTKMK_JPN->Text.IsEmpty()){
        MessageDlg("���荀�ږ�����͂��Ă��������B", mtWarning
                          ,TMsgDlgButtons() << mbOK, 0);
        Edt_SKTKMK_JPN->SetFocus();
        return;
    }
    if( Rdo_KIKAKU_SHITEI_HANI->Checked && Rdo_KIKAKU_SYURUI_MINMAX->Checked ) {
        if( Nmb_KIKAKU_HANI_MIN->Text.ToIntDef(0) >
            Nmb_KIKAKU_HANI_MAX->Text.ToIntDef(0) ){
            MessageDlg("�K�i�͈͎̔w�肪����������܂���B", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
            Nmb_KIKAKU_HANI_MIN->SetFocus();
            return;
        }
    }

    sBuf = Form1->Edt_DTKSHIN->Text;
	strcpy( Form1->tmpKSM02_DATA.DTKSHIN		,sBuf.c_str() );	// ��\���Ӑ�i��
    sBuf = "0";
	strcpy( Form1->tmpKSM02_DATA.REVCNT			,sBuf.c_str() );	// �����ԍ�
    sBuf = Form1->SGr_SOKUT->Cells[13][Form1->SGr_SOKUT->Row];
	strcpy( Form1->tmpKSM02_DATA.UNQ_NO			,sBuf.c_str() );	// ����NO
    sBuf = Form1->SGr_SOKUT->Cells[14][Form1->SGr_SOKUT->Row];
	strcpy( Form1->tmpKSM02_DATA.ORDER_NO		,sBuf.c_str() );	// �\����
    sBuf = Form1->SGr_SOKUT->Cells[15][Form1->SGr_SOKUT->Row];
	strcpy( Form1->tmpKSM02_DATA.SKB_NO			,sBuf.c_str() );	// ����NO
    sBuf = Pnl_HINBAN->Caption;
	strcpy( Form1->tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// �i��
	sBuf = Form1->SGr_SOKUT->Cells[12][Form1->SGr_SOKUT->Row];
	strcpy( Form1->tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// ����NO
	sBuf = Edt_SKTKMK_JPN->Text;
	strcpy( Form1->tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
	sBuf = Edt_SKTKMK_ENG->Text;
	strcpy( Form1->tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
	sBuf = Edt_SKTKMK_JPN_SUB->Text;
	strcpy( Form1->tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// ���荀�ڃT�u���́i���{��j
	sBuf = Edt_SKTKMK_ENG_SUB->Text;
	strcpy( Form1->tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// ���荀�ڃT�u���́i�p��j
	sBuf = IntToStr(Form1->iKIKI[Cmb_SKTKIKI->ItemIndex]);
	strcpy( Form1->tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// ����@��NO
	sBuf = Cmb_SKTKIKI->Text;
	strcpy( Form1->tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// ����@�햼��
	sBuf = Cmb_TANI->Text;
	strcpy( Form1->tmpKSM02_DATA.TANI			,sBuf.c_str() );	// �P��

    if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
		sBuf = Nmb_KIKAKU_HANI_MIN->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// �K�i�l�P
		sBuf = Nmb_KIKAKU_HANI_MAX->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// �K�i�l�Q
		sBuf = "0";
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// �K�i�l�R
		sBuf = "";
		strcpy( Form1->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// �K�i�l����
		sBuf = "1";
    } else if( Rdo_KIKAKU_SHITEI_KIJYUN->Checked ) {
		sBuf = Nmb_KIKAKU_KIJYUN_MID->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// �K�i�l�P
		sBuf = Nmb_KIKAKU_KIJYUN_MAX->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// �K�i�l�Q
		sBuf = Nmb_KIKAKU_KIJYUN_MIN->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// �K�i�l�R
		sBuf = "";
		strcpy( Form1->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// �K�i�l����
		sBuf = "2";
	} else {
		sBuf = "0";
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// �K�i�l�P
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// �K�i�l�Q
		strcpy( Form1->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// �K�i�l�R
		sBuf = Edt_KIKAKU_STRING->Text;
		strcpy( Form1->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// �K�i�l����
		sBuf = "3";
    }
	strcpy( Form1->tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// �K�i�^�C�v
    if( Rdo_KIKAKU_SYURUI_MINMAX->Checked )			sBuf = "1";
	else if( Rdo_KIKAKU_SYURUI_MAX->Checked )		sBuf = "2";
    else											sBuf = "3";
    strcpy( Form1->tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// �K�i���
    sBuf = Nmb_KIKAKU_DOUBLE->Text;
	strcpy( Form1->tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// �K�i�����_�ȉ�����
    sBuf = Nmb_N->Text;
	strcpy( Form1->tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// ����w��n��
    if( Rdo_SKTKMK_ON->Checked )			sBuf = "1";
	else									sBuf = "0";
	strcpy( Form1->tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
	if( Rdo_TKBKMK_ON->Checked )			sBuf = "1";
	else									sBuf = "0";
	strcpy( Form1->tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
	if( Rdo_MANMIN_PRT_ON->Checked )		sBuf = "1";
	else									sBuf = "0";
	strcpy( Form1->tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
	if( Rdo_VALUE_NORMAL->Checked )			sBuf = "0";
	else if( Rdo_VALUE_KAKUDO->Checked )	sBuf = "1";
	else if( Rdo_VALUE_OK->Checked )		sBuf = "2";
	else									sBuf = "3";
	strcpy( Form1->tmpKSM02_DATA.VALUE_TYPE		,sBuf.c_str() );	// ����l�\��
	sBuf = Nmb_VALUE_DOUBLE->Text;
	strcpy( Form1->tmpKSM02_DATA.VALUE_DECI		,sBuf.c_str() );	// ����l�����_�ȉ�����


    // �C����̒l�����̉�ʂɐݒ肵�܂�
    Form1->SGr_SOKUT_GridLinePaste( Form1->SGr_SOKUT->Row, "1", true );

    // �f�[�^�ύX�t���O�̐ݒ�
    Form1->DataChange = 1;

    // �߂�
    BtnF12Click( BtnF12 );

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�Q�F�߂�v�{�^�������������̏���
//
//  �@�\����
//    ���̃t�H�[������܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::BtnF12Click(TObject *Sender)
{
    Close();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�K�i�̎w����@�u�͈͎w��v�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �֘A����R���g���[���̗L���^�����𐧌䂵�܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::Rdo_KIKAKU_SHITEI_HANIClick(TObject *Sender)
{
    Pnl_KIKAKU_HANI->Visible   = true;
    Pnl_KIKAKU_KIJYUN->Visible = false;
    Pnl_KIKAKU_MOJI->Visible   = false;
    Pnl_SYURUI->Enabled        = true;
	Pnl_MANMIN_PRT->Enabled    = false;
    Nmb_KIKAKU_DOUBLE->Enabled = true;
    //Pnl_VALUE->Enabled         = true;
    Rdo_KIKAKU_SYURUI_MINMAX->Font->Color = clBlack;
    Rdo_KIKAKU_SYURUI_MAX->Font->Color    = clBlack;
    Rdo_KIKAKU_SYURUI_MIN->Font->Color    = clBlack;
	Rdo_MANMIN_PRT_ON->Font->Color        = clGray;
	Rdo_MANMIN_PRT_OFF->Font->Color       = clGray;
	Nmb_KIKAKU_DOUBLE->Font->Color        = clBlack;
    //Rdo_VALUE_NORMAL->Font->Color         = clBlack;
    //Rdo_VALUE_KAKUDO->Font->Color         = clBlack;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�K�i�̎w����@�u��w��v�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �֘A����R���g���[���̗L���^�����𐧌䂵�܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::Rdo_KIKAKU_SHITEI_KIJYUNClick(TObject *Sender)
{
    Pnl_KIKAKU_HANI->Visible   = false;
    Pnl_KIKAKU_KIJYUN->Visible = true;
    Pnl_KIKAKU_MOJI->Visible   = false;
    Pnl_SYURUI->Enabled        = true;
	Pnl_MANMIN_PRT->Enabled    = true;
    Nmb_KIKAKU_DOUBLE->Enabled = true;
    //Pnl_VALUE->Enabled         = true;
    Rdo_KIKAKU_SYURUI_MINMAX->Font->Color = clBlack;
    Rdo_KIKAKU_SYURUI_MAX->Font->Color    = clBlack;
    Rdo_KIKAKU_SYURUI_MIN->Font->Color    = clBlack;
	Rdo_MANMIN_PRT_ON->Font->Color        = clBlack;
	Rdo_MANMIN_PRT_OFF->Font->Color       = clBlack;
	Nmb_KIKAKU_DOUBLE->Font->Color        = clBlack;
    //Rdo_VALUE_NORMAL->Font->Color         = clBlack;
    //Rdo_VALUE_KAKUDO->Font->Color         = clBlack;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�K�i�̎w����@�u�����w��v�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �֘A����R���g���[���̗L���^�����𐧌䂵�܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::Rdo_KIKAKU_SHITEI_MOJIClick(TObject *Sender)
{
    Pnl_KIKAKU_HANI->Visible   = false;
    Pnl_KIKAKU_KIJYUN->Visible = false;
    Pnl_KIKAKU_MOJI->Visible   = true;
    Pnl_SYURUI->Enabled        = false;
	Pnl_MANMIN_PRT->Enabled    = false;
    Nmb_KIKAKU_DOUBLE->Enabled = false;
    //Pnl_VALUE->Enabled         = false;
    Rdo_KIKAKU_SYURUI_MINMAX->Font->Color = clGray;
    Rdo_KIKAKU_SYURUI_MAX->Font->Color    = clGray;
    Rdo_KIKAKU_SYURUI_MIN->Font->Color    = clGray;
	Rdo_MANMIN_PRT_ON->Font->Color        = clGray;
	Rdo_MANMIN_PRT_OFF->Font->Color       = clGray;
	Nmb_KIKAKU_DOUBLE->Font->Color        = clGray;
    //Rdo_VALUE_NORMAL->Font->Color         = clGray;
    //Rdo_VALUE_KAKUDO->Font->Color         = clGray;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�K�i�̎�ށu������������v�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �֘A����R���g���[���̗L���^�����𐧌䂵�܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::Rdo_KIKAKU_SYURUI_MINMAXClick(TObject *Sender)
{
    Nmb_KIKAKU_HANI_MIN->Enabled	= true;
    Nmb_KIKAKU_HANI_MAX->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MIN->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MAX->Enabled	= true;
    Nmb_KIKAKU_HANI_MIN->Color		= clWindow;
    Nmb_KIKAKU_HANI_MAX->Color		= clWindow;
    Nmb_KIKAKU_KIJYUN_MIN->Color	= clWindow;
    Nmb_KIKAKU_KIJYUN_MAX->Color	= clWindow;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�K�i�̎�ށu����̂݁v�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �֘A����R���g���[���̗L���^�����𐧌䂵�܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::Rdo_KIKAKU_SYURUI_MAXClick(TObject *Sender)
{
    Nmb_KIKAKU_HANI_MIN->Enabled	= false;
    Nmb_KIKAKU_HANI_MAX->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MIN->Enabled	= false;
    Nmb_KIKAKU_KIJYUN_MAX->Enabled	= true;
    Nmb_KIKAKU_HANI_MIN->Color		= clBtnFace;
    Nmb_KIKAKU_HANI_MAX->Color		= clWindow;
    Nmb_KIKAKU_KIJYUN_MIN->Color	= clBtnFace;
    Nmb_KIKAKU_KIJYUN_MAX->Color	= clWindow;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�K�i�̎�ށu�����̂݁v�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �֘A����R���g���[���̗L���^�����𐧌䂵�܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::Rdo_KIKAKU_SYURUI_MINClick(TObject *Sender)
{
    Nmb_KIKAKU_HANI_MIN->Enabled	= true;
    Nmb_KIKAKU_HANI_MAX->Enabled	= false;
    Nmb_KIKAKU_KIJYUN_MIN->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MAX->Enabled	= false;
    Nmb_KIKAKU_HANI_MIN->Color		= clWindow;
    Nmb_KIKAKU_HANI_MAX->Color		= clBtnFace;
    Nmb_KIKAKU_KIJYUN_MIN->Color	= clWindow;
    Nmb_KIKAKU_KIJYUN_MAX->Color	= clBtnFace;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F����l�̒l�\���u�����v�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �֘A����R���g���[���̗L���^�����𐧌䂵�܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::Rdo_VALUE_NORMALClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled     = true;
    Nmb_VALUE_DOUBLE->Font->Color = clBlack;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F����l�̒l�\���u�p�x�v�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �֘A����R���g���[���̗L���^�����𐧌䂵�܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::Rdo_VALUE_KAKUDOClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled     = true;
    Nmb_VALUE_DOUBLE->Font->Color = clBlack;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F����l�̒l�\���u��/�ہv�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �֘A����R���g���[���̗L���^�����𐧌䂵�܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::Rdo_VALUE_OKClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled     = false;
    Nmb_VALUE_DOUBLE->Font->Color = clGray;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F����l�̒l�\���u�����v�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �֘A����R���g���[���̗L���^�����𐧌䂵�܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::Rdo_VALUE_TEXTClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled     = false;
    Nmb_VALUE_DOUBLE->Font->Color = clGray;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyDown�C�x���g	�F���[�U�[���C�ӂ̃L�[�������Ɣ������܂�
//
//  �@�\����
//    �t�@���N�V�����L�[�AEnter�L�[�ɂ��{�^����I�����܂�
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
//---------------------------------------------------------------------------
void __fastcall TForm4::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F2:  BtnF02Click(BtnF02);		break;
         case VK_F3:  BtnF03Click(BtnF03);		break;
         case VK_F8:  BtnF08Click(BtnF08);		break;
         case VK_F12: BtnF12Click(Sender);		break;
         case VK_RETURN:
                // Enter
                if( Nmb_N->Focused() ){
                    BtnF08->SetFocus();
                    break;
                }
                else {
                	keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }

     }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit�C�x���g	�F���̓t�H�[�J�X���ʂ̃R���g���[���ֈڂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �K�i�̏����_�ȉ������Ƒ���l�̏����_�ȉ������ɓ����l��ݒ肵�܂��B
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
//---------------------------------------------------------------------------
void __fastcall TForm4::Nmb_KIKAKU_DOUBLEExit(TObject *Sender)
{

	TNumberEdit *ne = (TNumberEdit *)Sender;

    // �l�͈̔̓`�F�b�N���s�Ȃ��܂�
    if( ne->Value > 5 || ne->Value < 0 ){
    	MessageDlg("�����_�ȉ������̎w��͈͂́A0�`5�ȓ��ł��B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        if( ne->Value > 5 ){
            if( ne->Name == "Nmb_KIKAKU_DOUBLE" ){
        		Nmb_KIKAKU_DOUBLE->Text = "5";
			}
        	else {
        		Nmb_VALUE_DOUBLE->Text = "5";
        	}
        }
        else {
            if( ne->Name == "Nmb_KIKAKU_DOUBLE" ){
        		Nmb_KIKAKU_DOUBLE->Text = "0";
			}
        	else {
        		Nmb_VALUE_DOUBLE->Text = "0";
        	}
        }
    }

    // �u�K�i�l�v�l��ύX������u����l�v�̒l�𓯂��l�ɕύX���܂�
    if( ne->Name == "Nmb_KIKAKU_DOUBLE" ){
    	AnsiString	sBuf;

        // �u����l�v�̏����_�ȉ������́{�P���܂��B
        sBuf = Nmb_KIKAKU_DOUBLE->Text;
        if( sBuf.ToIntDef(0) >= 0 && sBuf.ToIntDef(0) < 5 ){
        	sBuf = AnsiString(sBuf.ToIntDef(0) + 1);
        }
		Nmb_VALUE_DOUBLE->Text = sBuf;

		Nmb_KIKAKU_HANI_MIN->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_HANI_MAX->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MAX->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MID->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MIN->FPos = Nmb_KIKAKU_DOUBLE->Value;
    	Nmb_KIKAKU_HANI_MIN->Text = Nmb_KIKAKU_HANI_MIN->Text;
    	Nmb_KIKAKU_HANI_MAX->Text = Nmb_KIKAKU_HANI_MAX->Text;
    	Nmb_KIKAKU_KIJYUN_MAX->Text = Nmb_KIKAKU_KIJYUN_MAX->Text;
    	Nmb_KIKAKU_KIJYUN_MID->Text = Nmb_KIKAKU_KIJYUN_MID->Text;
    	Nmb_KIKAKU_KIJYUN_MIN->Text = Nmb_KIKAKU_KIJYUN_MIN->Text;
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F���x���̐F��ݒ肵�܂��B
//
//  �@�\����
//    ���x���̐F��ݒ肵�܂��B
//
//  �p�����^����
//    int iSKB_NO		�F����NO
//                        1 = �f�ތ������ځi���F�j
//                        2 = �o�׌������ځi���F�j
//                        3 = �ޗ��ؖ����ځi���F�j
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm4::SetColor( int iSKB_NO )
{

	TColor		iColor;

    switch( iSKB_NO ){
    	case 1: // �f�ތ�������
        		iColor = (TColor)0x00D2FFFF;
                break;
        case 2: // �o�׌�������
        		iColor = (TColor)0x00FFEEDD;
                break;

        case 3: // �ޗ��ؖ�����
        		iColor = (TColor)0x00FFE1FD;
                break;
    }

    //�F�ύX
	Pnl_t01->Color = iColor;
	Pnl_t02->Color = iColor;
	Pnl_t03->Color = iColor;
	Pnl_t04->Color = iColor;
	Pnl_t05->Color = iColor;
	Pnl_t06->Color = iColor;
	Pnl_t07->Color = iColor;
	Pnl_t08->Color = iColor;
	Pnl_t09->Color = iColor;
	Pnl_t10->Color = iColor;
	Pnl_t11->Color = iColor;
	Pnl_t12->Color = iColor;
	Pnl_t13->Color = iColor;
	Pnl_t14->Color = iColor;
	Pnl_t15->Color = iColor;
	Pnl_t16->Color = iColor;
	Pnl_t17->Color = iColor;
	Pnl_t18->Color = iColor;
	Pnl_t19->Color = iColor;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnChange�C�x���g	�F�ҏW�R���g���[���̃e�L�X�g�ɕύX��������ꂽ�Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���͕���(�V���O���R�[�e�[�V�����A���p�J���})�̃`�F�b�N���s�Ȃ��܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �V���O���R�[�e�[�V�����͂c�a�o�^���ɃG���[����������
//    �̂őS�p�̃V���O���R�[�e�[�V�����ɕϊ����܂�
//
//---------------------------------------------------------------------------
void __fastcall TForm4::Edt_ALLChange(TObject *Sender)
{
	Form1->Edt_ALLChange( Sender );
}


