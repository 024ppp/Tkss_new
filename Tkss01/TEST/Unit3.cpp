//---------------------------------------------------------------------------
//
//  Unit3.cpp
//    �y�o�׌����V�X�e���|��������z
//    ���ڕҏW���C���t�H�[���iTForm3�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �c���@�֎i
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "Tkss01.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


extern 	GRAPH_DATA	pInfoGlaph;
//���b�g���蓖�ėp�i�o�׌����j
extern HANDLE hSOKU_KSD01_DATA;
extern KSD01_DATA *pSOKU_KSD01_DATA;
extern HANDLE hRIRE_KSD01_DATA;
extern KSD01_DATA *pRIRE_KSD01_DATA;

TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCreate�C�x���g	�FForm3���쐬�����Ƃ��ɔ������܂��B
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
void __fastcall TForm3::FormCreate(TObject *Sender)
{

	// �O���b�h�̏������i���j
	SGr_SOKUT->ColWidths[0] = 18;
	SGr_SOKUT->ColWidths[1] = 120;
	SGr_SOKUT->ColWidths[2] = 140;
	SGr_SOKUT->ColWidths[3] = 45;
	SGr_SOKUT->ColWidths[4] = 105;
	SGr_SOKUT->ColWidths[5] = 50;
	SGr_SOKUT->ColWidths[6] = 120;
	SGr_SOKUT->ColWidths[7] = 25;
	SGr_SOKUT->ColWidths[8] = 50;
	SGr_SOKUT->ColWidths[9] = 100;
	SGr_SOKUT->ColWidths[10]= 18;
	SGr_SOKUT->ColWidths[11]= 18;
	SGr_SOKUT->ColWidths[12]= 0;
	SGr_SOKUT->ColWidths[13]= 0;
	SGr_SOKUT->ColWidths[14]= 0;
	SGr_SOKUT->ColWidths[15]= 0;
	SGr_SOKUT->ColWidths[16]= 0;
	SGr_SOKUT->ColWidths[17]= 0;
	SGr_SOKUT->ColWidths[18]= 0;
	SGr_SOKUT->ColWidths[19]= 0;
	SGr_SOKUT->ColWidths[20]= 0;
	SGr_SOKUT->ColWidths[20]= 0;
	SGr_SOKUT->ColWidths[21]= 0;
	SGr_SOKUT->ColWidths[22]= 0;
	SGr_SOKUT->ColWidths[23]= 0;
	SGr_SOKUT->ColWidths[24]= 0;
	SGr_SOKUT->ColWidths[25]= 0;
	SGr_SOKUT->ColWidths[26]= 0;
	SGr_SOKUT->ColWidths[27]= 0;
	SGr_SOKUT->ColWidths[28]= 0;
	SGr_SOKUT->ColWidths[29]= 0;
	SGr_SOKUT->ColWidths[30]= 0;
    /* �f�o�b�O����Grid�T�C�Y
    int		i;
    for( i=1; i<=30; i++ ){
		SGr_SOKUT->ColWidths[i]= 30;
    }
    SGr_SOKUT->Options << goColSizing;
    */

	SGr_SOKUT->Cells[0][0] = "NO";
	SGr_SOKUT->Cells[1][0] = "�i�@��";
	SGr_SOKUT->Cells[2][0] = "���荀��";
	SGr_SOKUT->Cells[3][0] = "SB����";      // �f�ނ���Q�i�ԁi�Q�w�j�I������K�v������̂ŕK�v�ł��B
	SGr_SOKUT->Cells[4][0] = "����(English)";
	SGr_SOKUT->Cells[5][0] = "�P��";
	SGr_SOKUT->Cells[6][0] = "�K�@�i";
	SGr_SOKUT->Cells[7][0] = "n��";
	SGr_SOKUT->Cells[8][0] = "�l�\��";
	SGr_SOKUT->Cells[9][0] = "����@��";
	SGr_SOKUT->Cells[10][0]= "��";
	SGr_SOKUT->Cells[11][0]= "��";

    // StringList������
	sDEL_UNQ_NO	= new TStringList;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnActivate�C�x���g	�F�t�H�[�����A�N�e�B�u�ɂȂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �����\���ɕK�v�ȃf�[�^���������܂�
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
void __fastcall TForm3::FormActivate(TObject *Sender)
{

    int			i;
    int			iRow;
	AnsiString	sBuf;
	AnsiString	sBufList[8];


    // Grid�p�t�H���g�̍쐬
    LogFont.lfHeight = 10;
    LogFont.lfWidth = 0;
    LogFont.lfEscapement = 0;
    LogFont.lfOrientation = 0;
    LogFont.lfWeight = FW_NORMAL;
    LogFont.lfItalic = 0;
    LogFont.lfUnderline = 0;
    LogFont.lfStrikeOut = 0;
    LogFont.lfCharSet = SHIFTJIS_CHARSET;
    LogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    LogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    LogFont.lfQuality = DEFAULT_QUALITY;
    LogFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    strcpy( LogFont.lfFaceName, "�l�r �S�V�b�N" );
    MyFont = CreateFontIndirect( &LogFont );


    //----------------------------------------------
    // �Ώۃ��b�gNo�̕\��
    Rdo_Object_NowLOT->Caption = "�I�𒆃��b�g[" + sNOW_LOTNO + "]�̂ݍX�V�i�����f�[�^�͍X�V���Ȃ��j";
    Rdo_Object_NowLOT_AndMASTER->Caption = "�I�𒆃��b�g[" + sNOW_LOTNO + "]�ȍ~�ƁA���̓��Ӑ�i�Ԃ̐��i�K�i�}�X�^�[���X�V";
    Rdo_Object_NowLOT->Checked = true;		// 2003/11/5 A.Tamura ������I��

    //----------------------------------------------
    // �������я��^�C�g�����o�͏��̌���

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����s�i�������я��^�C�g�����ڃ}�X�^�[�̌����擾�j
    sBuf = "SELECT COUNT(*) AS TITLE_NUM FROM KSM21";

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    if( !Query1->Eof ){
        iTITLE_Cnt = Query1->FieldValues["TITLE_NUM"];
    }
    else {
        iTITLE_Cnt = 50;
    }

    // �������̊m�ہi�������я��^�C�g�����ڃ}�X�^�[�̌������j
    hMemTITLE = GlobalAlloc( GHND, sizeof(int) * iTITLE_Cnt );
    if( hMemTITLE == NULL ){
    	MessageDlg("�������̈���m�ۂł��܂���B(01)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }
    iTITLE = (int *)GlobalLock(hMemTITLE);
    if( hMemTITLE == NULL ){
    	MessageDlg("�������̈���m�ۂł��܂���B(02)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����s�i�������я��^�C�g�����ڃ}�X�^�[�j
    sBuf = "SELECT KMK_NO, KMK_NM_JPN, KMK_NM_ENG FROM KSM21 ORDER BY ORDER_NO";

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    iRow = 0;
    Clb_OUT_TITLE->Clear();
    while( !Query1->Eof ){

        // �^�C�g�������`�F�b�N���X�g�{�b�N�X�ɒǉ�
        sBuf  = Query1->FieldValues["KMK_NM_JPN"];
        if( !VarIsNull(Query1->FieldValues["KMK_NM_ENG"]) ){
        	sBuf += "(" + AnsiString(Query1->FieldValues["KMK_NM_ENG"]) + ")";
        }
        Clb_OUT_TITLE->Items->Add(sBuf);

        // �^�C�g������No���L���i�z��ԍ��́A�`�F�b�N���X�g�{�b�N�X��Item�C���f�b�N�X�j
        iTITLE[iRow] = Query1->FieldValues["KMK_NO"];
        iRow++;

        // �J�[�\�������ɃZ�b�g����
        Query1->Next();
    }


    //----------------------------------------------
    // ����@�퍀�ڃ}�X�^�[�̌���

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s�i����@�퍀�ڃ}�X�^�[�̌����擾�j
	sBuf = "SELECT COUNT(*) AS KIKI_NUM FROM KSM14";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if( !Query1->Eof ){
        iKIKI_Cnt = Query1->FieldValues["KIKI_NUM"];
    }
    else {
        iKIKI_Cnt = 50;
    }

    // �������̊m�ہi����@�퍀�ڃ}�X�^�[�̌������j
    hMemKIKI = GlobalAlloc( GHND, sizeof(int) * iKIKI_Cnt );
    if( hMemKIKI == NULL ){
    	MessageDlg("�������̈���m�ۂł��܂���B(01)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }
    iKIKI = (int *)GlobalLock(hMemKIKI);
    if( hMemKIKI == NULL ){
    	MessageDlg("�������̈���m�ۂł��܂���B(02)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s�i����@�퍀�ڃ}�X�^�[�j
	sBuf = "SELECT KIKI_NO, KIKI_NM FROM KSM14 ORDER BY ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

    iRow = 0;
    Form4->Cmb_SKTKIKI->Clear();
    Form5->Cmb_SKTKIKI->Clear();
    Form6->Cmb_SKTKIKI->Clear();
	while( !Query1->Eof ){

        // �@�햼���R���{�{�b�N�X�ɒǉ�
		sBuf = Query1->FieldValues["KIKI_NM"];
        Form4->Cmb_SKTKIKI->Items->Add(sBuf);
        Form5->Cmb_SKTKIKI->Items->Add(sBuf);
        Form6->Cmb_SKTKIKI->Items->Add(sBuf);

        // �@��No���L���i�z��ԍ��́A�R���{�{�b�N�X��Item�C���f�b�N�X�j
        iKIKI[iRow] = Query1->FieldValues["KIKI_NO"];
        iRow++;

		// �J�[�\�������ɃZ�b�g����
		Query1->Next();
    }


    //----------------------------------------------
    // �P�ʃ}�X�^�[�̌���

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s�i�P�ʃ}�X�^�[�j
	sBuf = "SELECT TANI FROM KSM92 ORDER BY ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

    Form4->Cmb_TANI->Clear();
    Form5->Cmb_TANI->Clear();
    Form6->Cmb_TANI->Clear();
	while( !Query1->Eof ){

        // �@�햼���R���{�{�b�N�X�ɒǉ�
		sBuf = Query1->FieldValues["TANI"];
        Form4->Cmb_TANI->Items->Add(sBuf);
        Form5->Cmb_TANI->Items->Add(sBuf);
        Form6->Cmb_TANI->Items->Add(sBuf);

		// �J�[�\�������ɃZ�b�g����
		Query1->Next();
    }


    //-----------------------------------------------------------
    // ���i�K�i�}�X�^�[���������\��


    // �����\�����鍀�ڃf�[�^�̕\����
    if( iFROM_DATA == 1 ){
		// 1=�I�����b�g����\��
        Form3->Caption = "����ҏW�@�i������j�@�y�I�����b�g[" + sNOW_LOTNO + "]�̑��荀�ڂ�\���z";

        PnlMaster->Visible  = false;
        PnlUPDYMD1->Visible = false;
        PnlUPDCHR1->Visible = false;
        PnlUPDYMD2->Visible = false;
        PnlUPDCHR2->Visible = false;

    } else {
    	// 2=���i�K�i�}�X�^�[����\��
        Form3->Caption = "����ҏW�@�i������j�@�y���i�K�i�}�X�^�[�̑��荀�ڂ�\���z";

        PnlMaster->Visible  = true;
        PnlUPDYMD1->Visible = true;
        PnlUPDCHR1->Visible = true;
        PnlUPDYMD2->Visible = true;
        PnlUPDCHR2->Visible = true;

    }


	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s
    if( iFROM_DATA == 1 ){
		// ���荀�ڂ̕\���� 1=�I�����b�g����\��
		sBuf  = "select KSD01.DTKSHIN, KSD01.LOTNO, KSD01.HINBAN, KSD01.DTKSCOD,";
		sBuf += " KSD01.DTKSNAM, KSD01.ZISNAM, KSD01.HINMEI,";
		sBuf += " KSD01.DTKSHIN1_SZ, KSD01.DTKSHIN2_SZ, KSD01.DTKSHIN3_SZ,";
		sBuf += " KSD01.DTKSHIN4_SZ, KSD01.DTKSHIN5_SZ, KSD01.DTKSHIN6_SZ,";
		sBuf += " KSD01.LOT_LINK_SZ, KSD01.SOKUTEI_NUM,";
		sBuf += " KSD01.OUT_TITLE1, KSD01.OUT_TITLE2, KSD01.OUT_TITLE3,";
		sBuf += " KSD01.OUT_TITLE4, KSD01.OUT_TITLE5, KSD01.OUT_TITLE6,";
		sBuf += " KSD01.OUT_TITLE7, KSD01.OUT_TITLE8,";
		sBuf += " KSD01.X_OUT, KSD01.MEMO,";
		sBuf += " KSD01.ADDYMD, KSD01.ADDTIM, KSD01.UPDYMD,";
		sBuf += " KSD01.UPDTIM, KSD01.UPDCHR, KSD01.UPDCNT, SM12S.TANNAM";
		sBuf += " FROM KSD01 LEFT JOIN SM12S ON KSD01.UPDCHR = SM12S.TANSYA";
		sBuf += " where KSD01.DTKSHIN = '" + sNOW_DTKSHIN + "'";
		sBuf += " and KSD01.LOTNO = '" + sNOW_LOTNO + "'";
	} else {
    	// ���荀�ڂ̕\���� 2=���i�K�i�}�X�^�[����\��
		sBuf  = "select KSM01.DTKSHIN, KSM01.REVCNT, KSM01.HINBAN, KSM01.DTKSCOD,";
		sBuf += " KSM01.DTKSNAM, KSM01.ZISNAM, KSM01.HINMEI,";
		sBuf += " KSM01.DTKSHIN1_SZ, KSM01.DTKSHIN2_SZ, KSM01.DTKSHIN3_SZ,";
		sBuf += " KSM01.DTKSHIN4_SZ, KSM01.DTKSHIN5_SZ, KSM01.DTKSHIN6_SZ,";
		sBuf += " KSM01.LOT_LINK_SZ, KSM01.SOKUTEI_NUM,";
		sBuf += " KSM01.OUT_TITLE1, KSM01.OUT_TITLE2, KSM01.OUT_TITLE3,";
		sBuf += " KSM01.OUT_TITLE4, KSM01.OUT_TITLE5, KSM01.OUT_TITLE6,";
		sBuf += " KSM01.OUT_TITLE7, KSM01.OUT_TITLE8,";
		sBuf += " KSM01.X_OUT, KSM01.MEMO,";
		sBuf += " KSM01.ADDYMD, KSM01.ADDTIM, KSM01.UPDYMD,";
		sBuf += " KSM01.UPDTIM, KSM01.UPDCHR, KSM01.UPDCNT, SM12S.TANNAM";
		sBuf += " FROM KSM01 LEFT JOIN SM12S ON KSM01.UPDCHR = SM12S.TANSYA";
		sBuf += " where KSM01.DTKSHIN = '" + sNOW_DTKSHIN + "'";
		sBuf += " and KSM01.REVCNT = 0";
    }
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if( !Query1->Eof ){

		// ���Ӑ�R�[�h
		if( VarIsNull(Query1->FieldValues["DTKSCOD"]) ){
			 sBuf = "";
		} else{
			sBuf = Query1->FieldValues["DTKSCOD"];
		}
		Edt_DTKSCOD->Text = sBuf;

		// ���Ӑ於��
		if( VarIsNull(Query1->FieldValues["DTKSNAM"]) ){
			 sBuf = "";
		} else{
			sBuf = Query1->FieldValues["DTKSNAM"];
		}
		Edt_DTKSNAM->Text = sBuf;

		// ���Ӑ�i��
		sBuf = Query1->FieldValues["DTKSHIN"];
		Edt_DTKSHIN->Text = sBuf;

		// �f�ޗp���Ӑ�i��
		Lbx_DTKSHIN_SZ->Clear();

		// �f�ޗp�i�ԂP
		if( VarIsNull(Query1->FieldValues["DTKSHIN1_SZ"]) ){
			 sBuf = "";
		} else{
			sBuf = Query1->FieldValues["DTKSHIN1_SZ"];
		}
		if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);

		// �f�ޗp�i�ԂQ
		if( VarIsNull(Query1->FieldValues["DTKSHIN2_SZ"]) ){
			 sBuf = "";
		} else{
			sBuf = Query1->FieldValues["DTKSHIN2_SZ"];
		}
		if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);

		// �f�ޗp�i�ԂR
		if( VarIsNull(Query1->FieldValues["DTKSHIN3_SZ"]) ){
			 sBuf = "";
		} else{
			sBuf = Query1->FieldValues["DTKSHIN3_SZ"];
		}
		if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);

		// �f�ޗp�i�ԂS
		if( VarIsNull(Query1->FieldValues["DTKSHIN4_SZ"]) ){
			 sBuf = "";
		} else{
			sBuf = Query1->FieldValues["DTKSHIN4_SZ"];
		}
		if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);

		// �f�ޗp�i�ԂT
		if( VarIsNull(Query1->FieldValues["DTKSHIN5_SZ"]) ){
			 sBuf = "";
		} else{
			sBuf = Query1->FieldValues["DTKSHIN5_SZ"];
		}
		if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);

		// �f�ޗp�i�ԂU
		if( VarIsNull(Query1->FieldValues["DTKSHIN6_SZ"]) ){
			 sBuf = "";
		} else{
			sBuf = Query1->FieldValues["DTKSHIN6_SZ"];
		}
		if( sBuf.Trim() != "" )	Lbx_DTKSHIN_SZ->Items->Add(sBuf);

		// �f�ޗp���b�g�̃����N
		sBuf = Query1->FieldValues["LOT_LINK_SZ"];
		switch( sBuf.ToIntDef(-1) ){
			case 0: Rdo_LOT_LINK_SZ_OFF->Checked = true;
					break;
			case 1:
			default:Rdo_LOT_LINK_SZ_ON->Checked = true;
			  		break;
	   	}

		// ���Еi��
		if( VarIsNull(Query1->FieldValues["HINBAN"]) ){
			 sBuf = "";
		} else{
			sBuf = Query1->FieldValues["HINBAN"];
		}
		Edt_HINBAN->Text = sBuf;

		// �i��
		if( VarIsNull(Query1->FieldValues["ZISNAM"]) ){
			 sBuf = "";
		} else{
			sBuf = Query1->FieldValues["ZISNAM"];
		}
		Edt_ZISNAM->Text = sBuf;

		// �i��
		if( VarIsNull(Query1->FieldValues["HINMEI"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["HINMEI"];
		}
		Edt_HINMEI->Text = sBuf;

		// ���ڐ�
		if( VarIsNull(Query1->FieldValues["SOKUTEI_NUM"]) ){
			sBuf = "0";
		} else{
			sBuf = Query1->FieldValues["SOKUTEI_NUM"];
		}
		Pnl_SOKUTEI_NUM->Caption = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

		// ���l
		//if( VarIsNull(Query1->FieldValues["MEMO"]) ){
		//	sBuf = "";
		//} else{
		//	sBuf = Query1->FieldValues["MEMO"];
		//}
		//Edt_MEMO->Text = sBuf;

		// �������я��^�C�g�����o�͍���
		// ���я��^�C�g���o�͍��ڂP
		sBufList[0] = Query1->FieldValues["OUT_TITLE1"];
		// ���я��^�C�g���o�͍��ڂQ
		sBufList[1] = Query1->FieldValues["OUT_TITLE2"];
		// ���я��^�C�g���o�͍��ڂR
		sBufList[2] = Query1->FieldValues["OUT_TITLE3"];
		// ���я��^�C�g���o�͍��ڂS
		sBufList[3] = Query1->FieldValues["OUT_TITLE4"];
		// ���я��^�C�g���o�͍��ڂT
		sBufList[4] = Query1->FieldValues["OUT_TITLE5"];
		// ���я��^�C�g���o�͍��ڂU
		sBufList[5] = Query1->FieldValues["OUT_TITLE6"];
		// ���я��^�C�g���o�͍��ڂV
		sBufList[6] = Query1->FieldValues["OUT_TITLE7"];
		// ���я��^�C�g���o�͍��ڂW
		sBufList[7] = Query1->FieldValues["OUT_TITLE8"];

		for( i = 0; i < iTITLE_Cnt; i++){
			if( iTITLE[i] == sBufList[0].ToIntDef(-1)
			 || iTITLE[i] == sBufList[1].ToIntDef(-1)
			 || iTITLE[i] == sBufList[2].ToIntDef(-1)
			 || iTITLE[i] == sBufList[3].ToIntDef(-1)
			 || iTITLE[i] == sBufList[4].ToIntDef(-1)
			 || iTITLE[i] == sBufList[5].ToIntDef(-1)
			 || iTITLE[i] == sBufList[6].ToIntDef(-1)
			 || iTITLE[i] == sBufList[7].ToIntDef(-1) ){
				Clb_OUT_TITLE->Checked[i] = true;
			}
			else {
				Clb_OUT_TITLE->Checked[i] = false;
			}
		}

		// �w�̏o��
		sBuf = Query1->FieldValues["X_OUT"];
		switch( sBuf.ToIntDef(-1) ){
			case 1: Rdo_XOUT_ON->Checked = true;
					break;
			case 0:
			default:Rdo_XOUT_OFF->Checked = true;
			  		break;
	   	}

		// �ύX��
		if( VarIsNull(Query1->FieldValues["UPDYMD"]) ){
			 sBuf = "";
		} else{
			sBuf = Query1->FieldValues["UPDYMD"];
		}
		if( sBuf.Trim() != "" ){
			sBuf = sBuf.Insert("/",5);
			sBuf = sBuf.Insert("/",8);
			PnlUPDYMD2->Caption = sBuf;
		}
		else PnlUPDYMD2->Caption = "";

		//�X�V��
		if( VarIsNull(Query1->FieldValues["TANNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["TANNAM"];
		}
		PnlUPDCHR2->Caption = sBuf;

	} else {

        //----------------------------
        // �f�[�^��������Ȃ�������
    	MessageDlg("�Y���i�Ԃ̃f�[�^��������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
		Close();
        return;

	}


    //----------------------------------------------
    // ���荀�ڃ}�X�^�[����

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s�i���i�K�i���׃}�X�^�[�j
    if( iFROM_DATA == 1 ){
		// ���荀�ڂ̕\���� 1=�I�����b�g����\��
		sBuf  = "SELECT UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK,";
    	sBuf +=       " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB,";
    	sBuf +=       " KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI, KIKA_TYPE,";
    	sBuf +=       " KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2,";
    	sBuf +=       " KIKA_NUM3, KIKA_STR, KIKA_SUB1, KIKA_SUB2,";
    	sBuf +=       " KIKA_SUB3, SOKU_SU, SOKU_FLG, TOKU_FLG,";
    	sBuf +=       " KIKA_PRT, VALUE_TYPE, VALUE_DECI";
    	sBuf += " FROM KSD02";
    	// ���Ӑ�i��
    	sBuf += " WHERE DTKSHIN = '" + sNOW_DTKSHIN + "'";
    	// ���b�gNO
    	sBuf += " AND LOTNO = '" + sNOW_LOTNO + "'";
    	sBuf += " ORDER BY ORDER_NO";

	} else {
    	// ���荀�ڂ̕\���� 2=���i�K�i�}�X�^�[����\��

		sBuf  = "SELECT UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK,";
    	sBuf +=       " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB,";
    	sBuf +=       " KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI, KIKA_TYPE,";
    	sBuf +=       " KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2,";
    	sBuf +=       " KIKA_NUM3, KIKA_STR, KIKA_SUB1, KIKA_SUB2,";
    	sBuf +=       " KIKA_SUB3, SOKU_SU, SOKU_FLG, TOKU_FLG,";
    	sBuf +=       " KIKA_PRT, VALUE_TYPE, VALUE_DECI";
    	sBuf += " FROM KSM02";
    	// ���Ӑ�i��
    	sBuf += " WHERE DTKSHIN = '" + sNOW_DTKSHIN + "'";
    	// �����ԍ�
    	sBuf += " AND REVCNT = 0";
    	sBuf += " ORDER BY ORDER_NO";
    }

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	iRow = 1;
	while( !Query1->Eof ){

		// �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
		if( iRow >= SGr_SOKUT->RowCount ){
			SGr_SOKUT->RowCount = iRow + 1;
		}

		// �O���b�h�Ƀf�[�^���Z�b�g���܂��B
		sBuf = iRow ;
		SGr_SOKUT->Cells[0][iRow] = AnsiString::StringOfChar(' ', 2-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

        if( VarIsNull(Query1->FieldValues["HINBAN_SK"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["HINBAN_SK"];
		}
        SGr_SOKUT->Cells[1][iRow] = sBuf;   // �i��

        if( VarIsNull(Query1->FieldValues["KOMK_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_NM"];
		}
        SGr_SOKUT->Cells[2][iRow] = sBuf;   // ���荀�ځi���{��j

        if( VarIsNull(Query1->FieldValues["KOMK_SUB"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_SUB"];
		}
        SGr_SOKUT->Cells[3][iRow] = sBuf;   // ���荀�ڃT�u���́i���{��j

        if( VarIsNull(Query1->FieldValues["KOMK_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_ENG"];
        }
        SGr_SOKUT->Cells[4][iRow] = sBuf;   //���荀�ځi�p��j

        if( VarIsNull(Query1->FieldValues["TANI"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["TANI"];
        }
		SGr_SOKUT->Cells[5][iRow] = sBuf;   //�P��

		SGr_SOKUT->Cells[6][iRow] = "";     //�K�i�i��{�j   ���ĕ`�悷��ׂɕK�v�ł��B

		sBuf = Query1->FieldValues["SOKU_SU"];
		SGr_SOKUT->Cells[7][iRow] = sBuf;   //�����i��{�j

		sBuf = Query1->FieldValues["VALUE_TYPE"];
		SGr_SOKUT->Cells[8][iRow] = sBuf;   //�l�\��

        if( VarIsNull(Query1->FieldValues["KIKI_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KIKI_NM"];
        }
		SGr_SOKUT->Cells[9][iRow] = sBuf;   //����@�햼��

		sBuf = Query1->FieldValues["SOKU_FLG"];
		SGr_SOKUT->Cells[10][iRow] = sBuf;   //���荀�ڂ̗L��

		sBuf = Query1->FieldValues["TOKU_FLG"];
		SGr_SOKUT->Cells[11][iRow] = sBuf;   //���ʍ��ڂ̗L��

		sBuf = Query1->FieldValues["KOMK_NO"];
		SGr_SOKUT->Cells[12][iRow] = sBuf;   //����NO

		sBuf = Query1->FieldValues["UNQ_NO"];
		SGr_SOKUT->Cells[13][iRow] = sBuf;   //����NO
        // �ő�̍���NO���擾���܂�
	    //if( StrToInt(sBuf) > iSOKUT_UNQ_NO_MAX ){
        //	iSOKUT_UNQ_NO_MAX = StrToInt(sBuf);
        //}

		sBuf = Query1->FieldValues["ORDER_NO"];
		SGr_SOKUT->Cells[14][iRow] = sBuf;   //�\����

		sBuf = Query1->FieldValues["SKB_NO"];
		SGr_SOKUT->Cells[15][iRow] = sBuf;   //����NO

        if( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_SUB_ENG"];
        }
		SGr_SOKUT->Cells[16][iRow] = sBuf;   //���荀�ڃT�u���́i�p��j

		sBuf = Query1->FieldValues["KIKI_NO"];
		SGr_SOKUT->Cells[17][iRow] = sBuf;   //����@��NO

		sBuf = Query1->FieldValues["KIKA_TYPE"];
		SGr_SOKUT->Cells[18][iRow] = sBuf;   //�K�i�^�C�v

		sBuf = Query1->FieldValues["KIKA_KIND"];
		SGr_SOKUT->Cells[19][iRow] = sBuf;   //�K�i���

		sBuf = Query1->FieldValues["KIKA_DECI"];
		SGr_SOKUT->Cells[20][iRow] = sBuf;   //�K�i�����_�ȉ�����

		sBuf = Query1->FieldValues["KIKA_NUM1"];
		SGr_SOKUT->Cells[21][iRow] = sBuf;   //�K�i�l�P

		sBuf = Query1->FieldValues["KIKA_NUM2"];
		SGr_SOKUT->Cells[22][iRow] = sBuf;   //�K�i�l�Q

		sBuf = Query1->FieldValues["KIKA_NUM3"];
		SGr_SOKUT->Cells[23][iRow] = sBuf;   //�K�i�l�R

        if( VarIsNull(Query1->FieldValues["KIKA_STR"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KIKA_STR"];
        }
		SGr_SOKUT->Cells[24][iRow] = sBuf;   //�K�i����

        if( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KIKA_SUB1"];
        }
		SGr_SOKUT->Cells[25][iRow] = sBuf;   //�K�i�l�T�u�P

        if( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KIKA_SUB2"];
        }
		SGr_SOKUT->Cells[26][iRow] = sBuf;   //�K�i�l�T�u�Q

        if( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KIKA_SUB3"];
        }
		SGr_SOKUT->Cells[27][iRow] = sBuf;   //�K�i�l�T�u�R

		sBuf = Query1->FieldValues["KIKA_PRT"];
		SGr_SOKUT->Cells[28][iRow] = sBuf;   //��������l�̈��
	
		sBuf = Query1->FieldValues["VALUE_DECI"];
		SGr_SOKUT->Cells[29][iRow] = sBuf;   //����l�����_�ȉ�����

		SGr_SOKUT->Cells[30][iRow] = "0";    //�X�V�t���O

		// �J�[�\�������ɃZ�b�g����
		Query1->Next();

		iRow += 1;
	}

    // �ŉ��s���N���A�[
    SGr_SOKUT->RowCount = iRow + 1;
    for( i = 0; i < SGr_SOKUT->ColCount; i++) {
        SGr_SOKUT->Cells[i][iRow] = "";
    }

	// �V�����s��I��
    SGr_SOKUT->Row = 1;
	SGr_SOKUT->SetFocus();
    SGr_SOKUTClick( SGr_SOKUT );

    // �폜���X�g�̏�����
    sDEL_UNQ_NO->Clear();

    // �R�s�[�f�[�^�̏�����
    iCntCpyKSM02_DATA = 0;
    // �������̊J��
    if( hMemCpyKSM02_DATA ){
        GlobalUnlock( hMemCpyKSM02_DATA );
        GlobalFree( hMemCpyKSM02_DATA );
    }

	// �f�[�^�ύX�t���O�̏�����
	DataChange = 0;
    bDispRefresh = false;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCloseQuery�C�x���g�FClose ���\�b�h���Ăяo���ꂽ�Ƃ��܂��̓��[�U�[��
//          �t�H�[���̃V�X�e�����j���[�Łm����n��I�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �X�V�����f�[�^�����ۑ��̏ꍇ�A�ۑ����邩���Ȃ������m�F���܂��B
//    �ۑ�����ꍇ�́A�u�e�P�P�F�ۑ��v�{�^���������R�[�����f�[�^��ۑ����܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    bool &CanClose	�Ftrue  = ���̂܂܃t�H�[������܂�
//                        false = �t�H�[��Close���L�����Z�����܂�
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm3::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    // �f�[�^��ύX�������ǂ����̃t���O�`�F�b�N
    if( DataChange > 0 ){
        switch( MessageDlg( "�f�[�^���ҏW����Ă��܂��B\n�ۑ����܂����H",
                           mtConfirmation, mbYesNoCancel, 0) ){
            // �uYes�v      �ۑ�
            case mrYes:
	            BtnF11Click(Sender);
                break;
            // �uNo�v       �ύX��j��
            case mrNo:
                break;
            // �uCancel�v   �L�����Z��
            case mrCancel:
                CanClose = false;
                return;
        }
    }

    /*
    if( bDispRefresh ){
        MessageDlg( "���ڕҏW����܂����B\n�����ʂő���l���m�F��A�����ʂōēx�ۑ����ĉ������B",
                    mtInformation, TMsgDlgButtons() << mbOK, 0);
    }
    */

	// �f�[�^�x�[�X�ڑ����J�����܂�
    Query1->Close();

    // �������̊J��
    if( hMemTITLE ){
        GlobalUnlock( hMemTITLE );
        GlobalFree( hMemTITLE );
    }
    if( hMemKIKI ){
        GlobalUnlock( hMemKIKI );
        GlobalFree( hMemKIKI );
    }

    // Grid�p�t�H���g�̊J��
    DeleteObject( MyFont );

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�F�ꗗ�����v�{�^�������������̏���
//
//  �@�\����
//    �ꗗ������ʁiForm5�j��\�����܂�
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
void __fastcall TForm3::BtnF01Click(TObject *Sender)
{
    if( !BtnF01->Enabled )    return;
    // �ꗗ������ʂ̕\��
    Form2->Tag = BtnF01->Tag;
    Form2->ShowModal();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�Q�F�O���v�{�^�������������̏���
//
//  �@�\����
//    �I���s��1��Ɉړ����܂�
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
void __fastcall TForm3::BtnF02Click(TObject *Sender)
{
    if( !BtnF02->Enabled )    return;

    // ��ʉ�StringGrid
    if( SGr_SOKUT->Focused() ){
	    if( SGr_SOKUT->Row > 0 ){
    	    SGr_SOKUT->Row -= 1;
    	    SGr_SOKUT->SetFocus();
    	}
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�R�F�����v�{�^�������������̏���
//
//  �@�\����
//    �I���s��1���Ɉړ����܂�
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
void __fastcall TForm3::BtnF03Click(TObject *Sender)
{
    if( !BtnF03->Enabled )    return;

    // ��ʉ�StringGrid
    if( ( SGr_SOKUT->RowCount - 1 ) > SGr_SOKUT->Row ){
        SGr_SOKUT->Row += 1;
        SGr_SOKUT->SetFocus();
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�T�F��ʈ���v�{�^�������������̏���
//
//  �@�\����
//    ���C���t�H�[����������܂��B
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
void __fastcall TForm3::BtnF05Click(TObject *Sender)
{
	if( !BtnF05->Enabled ) return;

    ////////////////////
    // ��ʈ��
	Form3->Print();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�P�F�ۑ��v�{�^�������������̏���
//
//  �@�\����
//    �ҏW���ꂽ���ڂ��e�[�u���iKSD01,KSD02,KSD03����KSM01,KSM02�j�ɓo�^���܂�
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
void __fastcall TForm3::BtnF11Click(TObject *Sender)
{

     int		i, k, m;
     AnsiString sBuf;
     AnsiString sLOT_work;


     if( !BtnF11->Enabled )    return;

	 // StringGrid���ɓo�^���ꂽ���荀�ڂ̋K�i�l�̃`�F�b�N���s�Ȃ��܂�
     m = 0;
     for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
     	k = SGr_SOKUT->Cells[15][i].ToIntDef(-1);
		if( k == 1 || k == 2 || k == 3 ){
            m++;
			// 1:�f�ތ������ځA2:�o�׌������ځA3:�ޗ��ؖ����ڂ̏ꍇ�́A�`�F�b�N�Ώۂł��B
			k = SGr_SOKUT->Cells[18][i].ToIntDef(-1);
			if( k == 1 ){
				// 1:�͈͎w��̏ꍇ�́A�`�F�b�N�Ώۂł��B
				k = SGr_SOKUT->Cells[19][i].ToIntDef(-1);
				if( k == 1 ){
					// 1:������������̏ꍇ�́A�`�F�b�N�Ώۂł��B

                    double	Val1, Val2;

                    //2003.05.08 E.Takase Add��
                    Val1 = Form1->ConvDoubleDefD(SGr_SOKUT->Cells[21][i],0.0);
                    Val2 = Form1->ConvDoubleDefD(SGr_SOKUT->Cells[22][i],0.0);
		            //2003.05.08 E.Takase Add��
		            //2003.05.08 E.Takase Add �R�����g��
					//try {
					//	Val1 = SGr_SOKUT->Cells[21][i].ToDouble();
					//	Val2 = SGr_SOKUT->Cells[22][i].ToDouble();
					//} catch(EConvertError& e) {
					//	Val1 = 0;
					//	Val2 = 0;
					//} catch(Exception& e) {
					//	Val1 = 0;
					//	Val2 = 0;
					//}
                    //2003.05.08 E.Takase Add �R�����g��

					if( Val1 >= Val2 ){
                    	// �K�i�͈͎̔w�肪�s���ȏꍇ�́A�G���[�Ƃ��܂�
						Beep();
                        SGr_SOKUT->Row = i;
						MessageDlg("�K�i�͈͎̔w�肪����������܂���B", mtWarning,
							TMsgDlgButtons() << mbOK , 0);
						//SBr1->Panels->Items[0]->Text = "�K�i�͈͎̔w�肪����������܂���B";
						//SBr1->Update();
						//Beep();
						return;
					}
				}
        	}

            // 2003/06/02 A.Tamura
			// n����0�ȉ��i�s���j�ȏꍇ�́A�G���[�Ƃ��܂�
			if( SGr_SOKUT->Cells[7][i].ToIntDef(0) < 1 ){
				Beep();
                SGr_SOKUT->Row = i;
				MessageDlg("�����́A1�ȏ���w�肵�ĉ������B", mtWarning,
					TMsgDlgButtons() << mbOK , 0);
				return;
            }
		}
	 }
	 if( m == 0 ){
       	 // ���荀�ڂ��Ȃ����́A�G���[�Ƃ��܂�
		 Beep();
		 MessageDlg("���荀�ڂ��w�肵�ĉ������B", mtWarning,
			 TMsgDlgButtons() << mbOK , 0);
		 return;
	 }

     // ���荀�ڂ̏d�����������ǂ����`�F�b�N���܂�
     for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
     	k = SGr_SOKUT->Cells[15][i].ToIntDef(-1);
		if( k == 1 || k == 2 || k == 3 ){
            for( m = 1; m < SGr_SOKUT->RowCount - 1; m++) {
               // ��r����̂����������́A���̍��ڂ�
               if( m == i ) continue;
     	       k = SGr_SOKUT->Cells[15][m].ToIntDef(-1);
		       if( k == 1 || k == 2 || k == 3 ){
                   // ����敪NO��1�Ƃ���ȊO�̎��͕ʍ��ڂƂ��Ĉ����܂�
     	           if( (SGr_SOKUT->Cells[15][i].Trim() == "1" &&
                        SGr_SOKUT->Cells[15][m].Trim() != "1" ) ||
                       (SGr_SOKUT->Cells[15][i].Trim() != "1" &&
                        SGr_SOKUT->Cells[15][m].Trim() == "1" ) ){
                       continue;
                   }

                   // �i��or�f�ޗp�i��			�� �g�p���Ȃ� 2002/10/23 A.Tamura
                   // ���荀�ږ��́i���{��j
                   // ���荀�ڃT�u���́i���{��j
                   // ����NO					�� �g�p���Ȃ� 2002/10/20 A.Tamura
                   // ����@��NO				�� �g�p���Ȃ� 2002/10/20 A.Tamura
                   // �P��						�� �ǉ����܂� 2002/10/20 A.Tamura
                   // ���������͓̂o�^�ł��Ȃ��悤�ɂ��܂�
     	           if( //SGr_SOKUT->Cells[ 1][i].Trim() == SGr_SOKUT->Cells[ 1][m].Trim() &&
                       SGr_SOKUT->Cells[ 2][i].Trim() == SGr_SOKUT->Cells[ 2][m].Trim() &&
                       SGr_SOKUT->Cells[ 3][i].Trim() == SGr_SOKUT->Cells[ 3][m].Trim() &&
                       //SGr_SOKUT->Cells[12][i].Trim() == SGr_SOKUT->Cells[12][m].Trim() &&
                       //SGr_SOKUT->Cells[17][i].Trim() == SGr_SOKUT->Cells[17][m].Trim() ){
                       SGr_SOKUT->Cells[ 5][i].Trim() == SGr_SOKUT->Cells[ 5][m].Trim() ){
					   Beep();
                       SGr_SOKUT->Row = m;
					   MessageDlg("���荀�ڂ��d�����Ă��܂��B�ύX���ĉ������B", mtWarning,
					       TMsgDlgButtons() << mbOK , 0);
                       return;
                   }
               }
            }
        }
     }

     // �f�[�^���o�b�t�@�Ɋi�[���܂��B
     sBuf = Edt_DTKSHIN->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSHIN		,sBuf.c_str() );		// ���Ӑ�i��
     sBuf = "0";
     strcpy( tmpKSM01_DATA.REVCNT		,sBuf.c_str() );		// �����ԍ�
     sBuf = Edt_HINBAN->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.HINBAN		,sBuf.c_str() );		// ���Еi��
     sBuf = Edt_DTKSCOD->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSCOD		,sBuf.c_str() );		// ���Ӑ�R�[�h
     sBuf = Edt_DTKSNAM->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSNAM		,sBuf.c_str() );		// ���Ӑ於��
     sBuf = Edt_ZISNAM->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.ZISNAM		,sBuf.c_str() );		// �ގ����́i�i��j
     sBuf = Edt_HINMEI->Text;
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.HINMEI		,sBuf.c_str() );		// �i��
     sBuf = " ";
     strcpy( tmpKSM01_DATA.DTKSHIN1_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂP
     strcpy( tmpKSM01_DATA.DTKSHIN2_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂQ
     strcpy( tmpKSM01_DATA.DTKSHIN3_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂR
     strcpy( tmpKSM01_DATA.DTKSHIN4_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂS
     strcpy( tmpKSM01_DATA.DTKSHIN5_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂT
     strcpy( tmpKSM01_DATA.DTKSHIN6_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂU
     for( i = 0; i < Lbx_DTKSHIN_SZ->Items->Count; i++ ){
         sBuf = Lbx_DTKSHIN_SZ->Items->Strings[i];
         if( sBuf == "" )  sBuf = " ";
         if( i == 0 )  strcpy( tmpKSM01_DATA.DTKSHIN1_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂP
         if( i == 1 )  strcpy( tmpKSM01_DATA.DTKSHIN2_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂQ
         if( i == 2 )  strcpy( tmpKSM01_DATA.DTKSHIN3_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂR
         if( i == 3 )  strcpy( tmpKSM01_DATA.DTKSHIN4_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂS
         if( i == 4 )  strcpy( tmpKSM01_DATA.DTKSHIN5_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂT
         if( i == 5 )  strcpy( tmpKSM01_DATA.DTKSHIN6_SZ	,sBuf.c_str() );		// �f�ޗp���Ӑ�i�ԂU
     }
     if( Rdo_LOT_LINK_SZ_ON->Checked )		sBuf = "1";
     else									sBuf = "0";
     strcpy( tmpKSM01_DATA.LOT_LINK_SZ	,sBuf.c_str() );		// �f�ޗp���b�g�̃����N
     sBuf = Pnl_SOKUTEI_NUM->Caption.Trim();
     if( sBuf == "" )  sBuf = " ";
     strcpy( tmpKSM01_DATA.SOKUTEI_NUM	,sBuf.c_str() );		// ���荀�ڐ�
     sBuf = "0";
     strcpy( tmpKSM01_DATA.OUT_TITLE1	,sBuf.c_str() );		// ���я��^�C�g���o�͍���1
     strcpy( tmpKSM01_DATA.OUT_TITLE2	,sBuf.c_str() );		// ���я��^�C�g���o�͍���2
     strcpy( tmpKSM01_DATA.OUT_TITLE3	,sBuf.c_str() );		// ���я��^�C�g���o�͍���3
     strcpy( tmpKSM01_DATA.OUT_TITLE4	,sBuf.c_str() );		// ���я��^�C�g���o�͍���4
     strcpy( tmpKSM01_DATA.OUT_TITLE5	,sBuf.c_str() );		// ���я��^�C�g���o�͍���5
     strcpy( tmpKSM01_DATA.OUT_TITLE6	,sBuf.c_str() );		// ���я��^�C�g���o�͍���6
     strcpy( tmpKSM01_DATA.OUT_TITLE7	,sBuf.c_str() );		// ���я��^�C�g���o�͍���7
     strcpy( tmpKSM01_DATA.OUT_TITLE8	,sBuf.c_str() );		// ���я��^�C�g���o�͍���8
     k = 0;
     for( i = 0; i < iTITLE_Cnt; i++){
         if( Clb_OUT_TITLE->Checked[i] == true ){
             sBuf = IntToStr(iTITLE[i]);
             if( k == 0 )  strcpy( tmpKSM01_DATA.OUT_TITLE1	,sBuf.c_str() );	// ���я��^�C�g���o�͍���1
             if( k == 1 )  strcpy( tmpKSM01_DATA.OUT_TITLE2	,sBuf.c_str() );	// ���я��^�C�g���o�͍���2
             if( k == 2 )  strcpy( tmpKSM01_DATA.OUT_TITLE3	,sBuf.c_str() );	// ���я��^�C�g���o�͍���3
             if( k == 3 )  strcpy( tmpKSM01_DATA.OUT_TITLE4	,sBuf.c_str() );	// ���я��^�C�g���o�͍���4
             if( k == 4 )  strcpy( tmpKSM01_DATA.OUT_TITLE5	,sBuf.c_str() );	// ���я��^�C�g���o�͍���5
             if( k == 5 )  strcpy( tmpKSM01_DATA.OUT_TITLE6	,sBuf.c_str() );	// ���я��^�C�g���o�͍���6
             if( k == 6 )  strcpy( tmpKSM01_DATA.OUT_TITLE7	,sBuf.c_str() );	// ���я��^�C�g���o�͍���7
             if( k == 7 )  strcpy( tmpKSM01_DATA.OUT_TITLE8	,sBuf.c_str() );	// ���я��^�C�g���o�͍���8
             k++;
         }
     }
     if( Rdo_XOUT_ON->Checked )		sBuf = "1";
     else							sBuf = "0";
     strcpy( tmpKSM01_DATA.X_OUT		,sBuf.c_str() );		// �w�̏o��
     //sBuf = Edt_MEMO->Text;
     //if( sBuf == "" )  sBuf = " ";
     //strcpy( tmpKSM01_DATA.MEMO			,sBuf.c_str() );		// ���l
     sBuf = FormatDateTime("yyyymmdd",Date());
     strcpy( tmpKSM01_DATA.ADDYMD		,sBuf.c_str() );		// �o�^��
     strcpy( tmpKSM01_DATA.UPDYMD		,sBuf.c_str() );		// �ύX��
     sBuf = FormatDateTime("hhmm",TDateTime::CurrentTime());
     strcpy( tmpKSM01_DATA.ADDTIM		,sBuf.c_str() );		// �o�^����
     strcpy( tmpKSM01_DATA.UPDTIM		,sBuf.c_str() );		// �ύX����
     sBuf = IntToStr(Form1->USER_COD);
     strcpy( tmpKSM01_DATA.UPDCHR		,sBuf.c_str() );		// �X�V�ҁi�R�[�h�j
     sBuf = Form1->USER_NAM;
     strcpy( tmpKSM01_DATA.UPDNAM		,sBuf.c_str() );		// �X�V�ҁi���́j
     sBuf = "0";
     strcpy( tmpKSM01_DATA.UPDCNT		,sBuf.c_str() );		// �X�V��


     // KSM01����KSD01�փR�s�[���܂�
	 strcpy( tmpKSD01_DATA.DTKSHIN		,tmpKSM01_DATA.DTKSHIN		);	// ���Ӑ�i��
	 strcpy( tmpKSD01_DATA.LOTNO		,sNOW_LOTNO.c_str()			);	// ���b�gNO
	 sBuf = " ";
     strcpy( tmpKSD01_DATA.LOTNO1_SZ	,sBuf.c_str()				);	// �f�ޗp���b�gNO1
	 strcpy( tmpKSD01_DATA.LOTNO2_SZ	,sBuf.c_str()				);	// �f�ޗp���b�gNO2
	 strcpy( tmpKSD01_DATA.LOTNO3_SZ	,sBuf.c_str()				);	// �f�ޗp���b�gNO3
	 strcpy( tmpKSD01_DATA.LOTNO4_SZ	,sBuf.c_str()				);	// �f�ޗp���b�gNO4
	 strcpy( tmpKSD01_DATA.LOTNO5_SZ	,sBuf.c_str()				);	// �f�ޗp���b�gNO5
	 strcpy( tmpKSD01_DATA.LOTNO6_SZ	,sBuf.c_str()				);	// �f�ޗp���b�gNO6
	 strcpy( tmpKSD01_DATA.HINBAN		,tmpKSM01_DATA.HINBAN		);	// ���Еi��
	 strcpy( tmpKSD01_DATA.DTKSCOD		,tmpKSM01_DATA.DTKSCOD		);	// ���Ӑ�R�[�h
	 strcpy( tmpKSD01_DATA.DTKSNAM		,tmpKSM01_DATA.DTKSNAM		);	// ���Ӑ於��
	 strcpy( tmpKSD01_DATA.ZISNAM		,tmpKSM01_DATA.ZISNAM		);	// �ގ����́i�i��j
	 strcpy( tmpKSD01_DATA.HINMEI		,tmpKSM01_DATA.HINMEI		);	// �i��
	 strcpy( tmpKSD01_DATA.DTKSHIN1_SZ	,tmpKSM01_DATA.DTKSHIN1_SZ	);	// �f�ޗp���Ӑ�i��1
	 strcpy( tmpKSD01_DATA.DTKSHIN2_SZ	,tmpKSM01_DATA.DTKSHIN2_SZ	);	// �f�ޗp���Ӑ�i��2
	 strcpy( tmpKSD01_DATA.DTKSHIN3_SZ	,tmpKSM01_DATA.DTKSHIN3_SZ	);	// �f�ޗp���Ӑ�i��3
	 strcpy( tmpKSD01_DATA.DTKSHIN4_SZ	,tmpKSM01_DATA.DTKSHIN4_SZ	);	// �f�ޗp���Ӑ�i��4
	 strcpy( tmpKSD01_DATA.DTKSHIN5_SZ	,tmpKSM01_DATA.DTKSHIN5_SZ	);	// �f�ޗp���Ӑ�i��5
	 strcpy( tmpKSD01_DATA.DTKSHIN6_SZ	,tmpKSM01_DATA.DTKSHIN6_SZ	);	// �f�ޗp���Ӑ�i��6
	 strcpy( tmpKSD01_DATA.LOT_LINK_SZ	,tmpKSM01_DATA.LOT_LINK_SZ	);	// �f�ޗp���b�g�̃����N
	 strcpy( tmpKSD01_DATA.SOKUTEI_NUM	,tmpKSM01_DATA.SOKUTEI_NUM	);	// ���荀�ڐ�
	 sBuf = "0";
	 strcpy( tmpKSD01_DATA.SOZAI_OK		,sBuf.c_str()				);	// �f�ޔ���
	 strcpy( tmpKSD01_DATA.SOZAI_OK_PRT	,sBuf.c_str()				);	// �f�ޔ��� ����p
	 strcpy( tmpKSD01_DATA.SYUKA_OK		,sBuf.c_str()				);	// �o�ה���
	 strcpy( tmpKSD01_DATA.SYUKA_OK_PRT	,sBuf.c_str()				);	// �o�ה��� ����p
	 strcpy( tmpKSD01_DATA.OUT_TITLE1	,tmpKSM01_DATA.OUT_TITLE1	);	// ���я��^�C�g���o�͍���1
	 strcpy( tmpKSD01_DATA.OUT_TITLE2	,tmpKSM01_DATA.OUT_TITLE2	);	// ���я��^�C�g���o�͍���2
	 strcpy( tmpKSD01_DATA.OUT_TITLE3	,tmpKSM01_DATA.OUT_TITLE3	);	// ���я��^�C�g���o�͍���3
	 strcpy( tmpKSD01_DATA.OUT_TITLE4	,tmpKSM01_DATA.OUT_TITLE4	);	// ���я��^�C�g���o�͍���4
	 strcpy( tmpKSD01_DATA.OUT_TITLE5	,tmpKSM01_DATA.OUT_TITLE5	);	// ���я��^�C�g���o�͍���5
	 strcpy( tmpKSD01_DATA.OUT_TITLE6	,tmpKSM01_DATA.OUT_TITLE6	);	// ���я��^�C�g���o�͍���6
	 strcpy( tmpKSD01_DATA.OUT_TITLE7	,tmpKSM01_DATA.OUT_TITLE7	);	// ���я��^�C�g���o�͍���7
	 strcpy( tmpKSD01_DATA.OUT_TITLE8	,tmpKSM01_DATA.OUT_TITLE8	);	// ���я��^�C�g���o�͍���8
	 strcpy( tmpKSD01_DATA.X_OUT		,tmpKSM01_DATA.X_OUT		);	// �w�̏o��
	 strcpy( tmpKSD01_DATA.MEMO			,tmpKSM01_DATA.MEMO			);	// ���l
	 sBuf = " ";
	 strcpy( tmpKSD01_DATA.SKTYMD		,sBuf.c_str()				);	// �����
	 strcpy( tmpKSD01_DATA.SKTYMD_PRT	,sBuf.c_str()				);	// ����� ����p
	 strcpy( tmpKSD01_DATA.ADDYMD		,sBuf.c_str()				);	// �o�^��
	 strcpy( tmpKSD01_DATA.ADDTIM		,sBuf.c_str()				);	// �o�^����
	 strcpy( tmpKSD01_DATA.UPDYMD		,sBuf.c_str()				);	// �ύX��
	 strcpy( tmpKSD01_DATA.UPDTIM		,sBuf.c_str()				);	// �ύX����
	 strcpy( tmpKSD01_DATA.UPDCHR		,sBuf.c_str()				);	// �X�V�ҁi�R�[�h�j
	 sBuf = "0";
     strcpy( tmpKSD01_DATA.UPDNAM		,sBuf.c_str()				);	// �X�V�ҁi���́j
	 strcpy( tmpKSD01_DATA.UPDCNT		,sBuf.c_str()				);	// �X�V��


     //-------------------------------------------------------------------------
     // �m�Ώہn���蒆���b�g�̂ݍX�V
     if( Rdo_Object_NowLOT->Checked == true ){

         //-----------------------------------------
         // ������уf�[�^(KSD01,KSD02,KSD03)���X�V

     	 // ������уf�[�^�̍X�V
         if( UpdData_KSD01(sNOW_LOTNO) == False ){
     		 return;
         }

         // ������і��ׁi��O�j�f�[�^�̍X�V
         if( UpdData_Details_KSD02_03(sNOW_LOTNO) == False ){
         	 return;
     	 }

     //-------------------------------------------------------------------------
     // �m�Ώہn���蒆���b�g�ȍ~�ƁA���i�K�i�}�X�^�[���X�V����
     } else {

         //-----------------------------------------
         // ������уf�[�^(KSD01,KSD02,KSD03)���X�V

		 // ���蒆���b�g�ȍ~�̑Ώۃ��b�g������
         Query3->Close();
		 Query3->SQL->Clear();

		 // �⍇�����s
		 sBuf = "SELECT LOTNO FROM KSD01";
		 sBuf += " WHERE DTKSHIN = '" + sNOW_DTKSHIN + "'";
         if( sNOW_LOTNO.Length() == 5 ){
		 	sBuf += " AND SUBSTR(LOTNO,2) >= '" + sNOW_LOTNO.SubString(2,5) + "'";
		 	sBuf += " ORDER BY SUBSTR(LOTNO,2)";
         } else {
		 	sBuf += " AND LOTNO >= '" + sNOW_LOTNO + "'";
		 	sBuf += " ORDER BY LOTNO";
         }
		 Query3->SQL->Add(sBuf);
		 Query3->Open();
		 Query3->Active = true;
		 while( !Query3->Eof ){

			 sLOT_work = Query3->FieldValues["LOTNO"];

     	 	 // ������уf�[�^�̍X�V
         	 if( UpdData_KSD01(sLOT_work) == False ){
     		 	 return;
         	 }

         	 // ������і��ׁi��O�j�f�[�^�̍X�V
         	 if( UpdData_Details_KSD02_03(sLOT_work) == False ){
         	 	 return;
     	 	 }

			 // �J�[�\�������ɃZ�b�g����
			 Query3->Next();
		 }

		 Query3->Close();
		 Query3->SQL->Clear();


         //-----------------------------------------
         // ���i�K�i�}�X�^�[(KSM01,KSM02)���X�V

         // �ȑO�̐��i�K�i�}�X�^�[�̉����ԍ����X�V(+1)���܂�
     	 UpdKaiteiNo_KSM01_02(Edt_DTKSHIN->Text);

     	 // ���i�K�i�}�X�^�[�̓o�^
     	 if( AddData_KSM01(1) == False ){
     		 return;
         }

         // ���i�K�i���׃}�X�^�[�̓o�^
         if( AddData_Details_KSM02(1) == False ){
         	 return;
     	 }
	 }

     // �폜���X�g�̏�����
     sDEL_UNQ_NO->Clear();

     // �f�[�^�ύX�t���O�̏�����
     DataChange = 0;

     bDispRefresh = true;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�Q�F�߂�v�{�^�������������̏���
//
//  �@�\����
//    ���C���t�H�[����Close���R�[�����܂�
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
void __fastcall TForm3::BtnF12Click(TObject *Sender)
{
     Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�f�ޒǉ��v�{�^�������������̏���
//
//  �@�\����
//    �f�ތ������荀�ڑI����ʂ̕\��
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
void __fastcall TForm3::Btn_ADD_SZClick(TObject *Sender)
{
    // �f�ތ������荀�ڑI����ʂ̕\��
    if( Lbx_DTKSHIN_SZ->Items->Count > 0 ){
    	Form5->ShowModal();
	}
    else {
    	MessageDlg("�f�ޗp�i�Ԃ��w�肳��Ă��܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	Btn_DTKSHIN_SZ_ADD->SetFocus();
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�o�גǉ��v�{�^�������������̏���
//
//  �@�\����
//    �o�׌������荀�ڑI����ʂ̕\��
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
void __fastcall TForm3::Btn_ADD_SKClick(TObject *Sender)
{
    // �o�׌������荀�ڑI����ʂ̕\��
    Form4->ShowModal();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�uSpace�ǉ��v�{�^�������������̏���
//
//  �@�\����
//    StringGrid�i���j�őI�����ꂽ�s��Space�i�󔒍s�j��}�����܂�
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
void __fastcall TForm3::Btn_ADD_SPClick(TObject *Sender)
{

	AnsiString	sBuf;

	// �u�X�y�[�X�v�f�[�^�̍쐬
    sBuf = Edt_DTKSHIN->Text;
	strcpy( tmpKSM02_DATA.DTKSHIN		,sBuf.c_str() );	// ��\���Ӑ�i��
    sBuf = "0";
	strcpy( tmpKSM02_DATA.REVCNT		,sBuf.c_str() );	// �����ԍ�
    //sBuf = iSOKUT_UNQ_NO_MAX++ ;
	//strcpy( tmpKSM02_DATA.UNQ_NO		,sBuf.c_str() );	// ����NO
    //sBuf = iSOKUT_ORDER_NO_MAX++ ;
	//strcpy( tmpKSM02_DATA.ORDER_NO	,sBuf.c_str() );	// �\����
    sBuf = "9";
	strcpy( tmpKSM02_DATA.SKB_NO		,sBuf.c_str() );	// ����NO
    sBuf = " ";
	strcpy( tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// �i��
	sBuf = "0";
	strcpy( tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// ����NO
    sBuf = " ";
	strcpy( tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
    sBuf = " ";
	strcpy( tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
	sBuf = "";
	strcpy( tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// ���荀�ڃT�u���́i���{��j
	sBuf = "";
	strcpy( tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// ���荀�ڃT�u���́i�p��j
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// ����@��NO
    sBuf = " ";
	strcpy( tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// ����@�햼��
    sBuf = " ";
	strcpy( tmpKSM02_DATA.TANI			,sBuf.c_str() );	// �P��
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// �K�i�^�C�v
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// �K�i���
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// �K�i�����_�ȉ�����
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// �K�i�l�P
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// �K�i�l�Q
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// �K�i�l�R
    sBuf = " ";
	strcpy( tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// �K�i�l����
    sBuf = "0";
	strcpy( tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// ����w��n��
    sBuf = "0";
	strcpy( tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
    sBuf = "0";
	strcpy( tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
    sBuf = "0";
	strcpy( tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
    sBuf = "0";
	strcpy( tmpKSM02_DATA.VALUE_TYPE	,sBuf.c_str() );	// ����l�\��
    sBuf = "0";
	strcpy( tmpKSM02_DATA.VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����

    // �󔒂�}�����܂�
    Ins_SGr_SOKUT(SGr_SOKUT->Row);

	// �V�����s��I��
	SGr_SOKUT->SetFocus();
    SGr_SOKUTClick( SGr_SOKUT );

    // �f�[�^�ύX�t���O�̐ݒ�
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�ҏW�v�{�^�������������̏���
//
//  �@�\����
//    �I�����ꂽ�������荀�ڂɑ΂��ĕҏW��ʂ�\�����܂�
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
void __fastcall TForm3::Btn_EDITClick(TObject *Sender)
{
	TGridRect	myRect;


	// �����I�������ꍇ������̂ŁA�P�s�I���Ƃ��đI�����Ȃ����܂�
    myRect.Left				= SGr_SOKUT->Selection.Left;
	myRect.Top				= iRowSelTop;
	myRect.Right			= SGr_SOKUT->Selection.Right;
	myRect.Bottom			= iRowSelTop;
    SGr_SOKUT->Selection	= myRect;
	SGr_SOKUT->Row = iRowSelTop;
	SGr_SOKUT->SetFocus();
    SGr_SOKUTClick( SGr_SOKUT );

    // �ҏW�Ώۂ̍s���`�F�b�N���܂��B�iSpace�s�͏������~�j
    if( SGr_SOKUT->Cells[15][SGr_SOKUT->Row].ToIntDef(9) == 9 ){
    	MessageDlg("�ҏW�ł��܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    // ���荀�ڕҏW��ʂ̕\��
    Form6->ShowModal();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�FStringGrid��I���������ɔ������܂��B
//
//  �@�\����
//    �I���i�͈͑I���j���ꂽTop��Bottom���L�����܂��iSGr_ListRowMoved�ŗ��p�����j
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
void __fastcall TForm3::SGr_SOKUTClick(TObject *Sender)
{
   	iRowSelTop    = SGr_SOKUT->Selection.Top;
   	iRowSelBottom = SGr_SOKUT->Selection.Bottom;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u��ֈړ��v�{�^�������������̏���
//
//  �@�\����
//    StringGrid�i���j�őI�����ꂽ�s��1��̍s�Ɠ���ւ��܂��B
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
void __fastcall TForm3::Btn_UPClick(TObject *Sender)
{
    int			i, k;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;


    iChgRow1 = SGr_SOKUT->Selection.Top;
    iChgRow2 = SGr_SOKUT->Selection.Top - 1;
    iChgRow3 = SGr_SOKUT->Selection.Bottom;

    if( iChgRow1 <= 1) return;
    if( iChgRow1 >= SGr_SOKUT->RowCount - 1) return;

    if( iChgRow3 >= SGr_SOKUT->RowCount - 1)
    	iChgRow3 = SGr_SOKUT->Selection.Bottom = SGr_SOKUT->RowCount - 2;

    // ���\����Cells[14]�͓���ւ������ɂ��̑��̍��ڂ����ւ��A�X�V�t���O(Cells[30])��ON�ɂ��܂��B

    // ����ւ���̃f�[�^���o�b�N�A�b�v
	sBuf = SGr_SOKUT_GridLineCopy( iChgRow2 );

	// �㉺�����ւ��܂�
    for( i = iChgRow2; i < iChgRow3; i++ ) {
    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
            if( k == 14 ){
                // �\�����́A����ւ����Ȃ�
    			// SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i + 1];
            } else if( k == 30 ){
                // �X�V�t���O�̐ݒ�
				SGr_SOKUT->Cells[k][i] = "1";
        	} else {
				SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i + 1];
            }
		}
    }

    // �o�b�N�A�b�v�����f�[�^��߂��܂��i�\�����͖߂��Ȃ��j
	SGr_SOKUT_GridLinePaste( iChgRow3, "1", false );

    // �I���J�[�\���������ɏ�Ɉړ����܂�
    SGr_SOKUT->Row--;
	myRect.Left		= SGr_SOKUT->Selection.Left;
	myRect.Top		= iChgRow1 - 1;
	myRect.Right	= SGr_SOKUT->Selection.Right;
	myRect.Bottom	= iChgRow3 - 1;
    SGr_SOKUT->Selection	= myRect;
    //SGr_SOKUTSelectCell(SGr_SOKUT,1,SGr_SOKUT->Row,true);

    // �f�[�^�ύX�t���O�̐ݒ�
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u���ֈړ��v�{�^�������������̏���
//
//  �@�\����
//    StringGrid�i���j�őI�����ꂽ�s��1���̍s�Ɠ���ւ��܂��B
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
void __fastcall TForm3::Btn_DOWNClick(TObject *Sender)
{
    int			i, k;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;


    iChgRow1 = SGr_SOKUT->Selection.Top;
    iChgRow2 = SGr_SOKUT->Selection.Bottom + 1;
    iChgRow3 = SGr_SOKUT->Selection.Bottom;

    if( iChgRow2 >= SGr_SOKUT->RowCount - 1) return;

    // ���\����Cells[14]�͓���ւ������ɂ��̑��̍��ڂ����ւ��A�X�V�t���O(Cells[30])��ON�ɂ��܂��B

    // ����ւ���̃f�[�^���o�b�N�A�b�v
	sBuf = SGr_SOKUT_GridLineCopy( iChgRow2 );

	// �㉺�����ւ��܂�
    for( i=iChgRow2; i>iChgRow1 ; i-- ) {
    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
            if( k == 14 ){
                // �\�����́A����ւ����Ȃ�
    			// SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i - 1];
            } else if( k == 30 ){
                // �X�V�t���O�̐ݒ�
				SGr_SOKUT->Cells[k][i] = "1";
        	} else {
				SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i - 1];
            }
		}
    }

    // �o�b�N�A�b�v�����f�[�^��߂��܂��i�\�����͖߂��Ȃ��j
	SGr_SOKUT_GridLinePaste( iChgRow1, "1", false );

    // �I���J�[�\���������ɉ��Ɉړ����܂�
    SGr_SOKUT->Row++;
	myRect.Left		= SGr_SOKUT->Selection.Left;
	myRect.Top		= iChgRow1 + 1;
	myRect.Right	= SGr_SOKUT->Selection.Right;
	myRect.Bottom	= iChgRow3 + 1;
    SGr_SOKUT->Selection	= myRect;
    //SGr_SOKUTSelectCell(SGr_SOKUT,1,SGr_SOKUT->Row,true);

    // �f�[�^�ύX�t���O�̐ݒ�
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FStringGrid�̎w��s���o�b�t�@�ɕۑ����܂�
//
//  �@�\����
//    StringGrid�i���j�̎w��s���o�b�t�@�ɕۑ����܂�
//
//  �p�����^����
//    int iCpyIndex		�F���ʂ���sNO
//
//  �߂�l
//    AnsiString		�F�X�V�t���O�i���ʂ����s���X�V�ς݂��ǂ����j
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm3::SGr_SOKUT_GridLineCopy( int iCpyIndex)
{
	AnsiString sBuf;

	//strcpy( tmpKSM02_DATA.DTKSHIN		,sBuf.c_str() );	// ��\���Ӑ�i��
	//strcpy( tmpKSM02_DATA.REVCNT		,sBuf.c_str() );	// �����ԍ�
	sBuf = SGr_SOKUT->Cells[13][iCpyIndex];
	strcpy( tmpKSM02_DATA.UNQ_NO		,sBuf.c_str() );	// ����NO
	sBuf = SGr_SOKUT->Cells[14][iCpyIndex];
	strcpy( tmpKSM02_DATA.ORDER_NO		,sBuf.c_str() );	// �\����
	sBuf = SGr_SOKUT->Cells[15][iCpyIndex];
	strcpy( tmpKSM02_DATA.SKB_NO		,sBuf.c_str() );	// ����NO
	sBuf = SGr_SOKUT->Cells[1][iCpyIndex];
	strcpy( tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// �i��
	sBuf = SGr_SOKUT->Cells[12][iCpyIndex];
	strcpy( tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// ����NO
	sBuf = SGr_SOKUT->Cells[2][iCpyIndex];
	strcpy( tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
	sBuf = SGr_SOKUT->Cells[4][iCpyIndex];
	strcpy( tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
	sBuf = SGr_SOKUT->Cells[3][iCpyIndex];
	strcpy( tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// ���荀�ڃT�u���́i���{��j
	sBuf = SGr_SOKUT->Cells[16][iCpyIndex];
	strcpy( tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// ���荀�ڃT�u���́i�p��j
	sBuf = SGr_SOKUT->Cells[17][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// ����@��NO
	sBuf = SGr_SOKUT->Cells[9][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// ����@�햼��
	sBuf = SGr_SOKUT->Cells[5][iCpyIndex];
	strcpy( tmpKSM02_DATA.TANI			,sBuf.c_str() );	// �P��
	sBuf = SGr_SOKUT->Cells[18][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// �K�i�^�C�v
	sBuf = SGr_SOKUT->Cells[19][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// �K�i���
	sBuf = SGr_SOKUT->Cells[20][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// �K�i�����_�ȉ�����
	sBuf = SGr_SOKUT->Cells[21][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// �K�i�l�P
	sBuf = SGr_SOKUT->Cells[22][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// �K�i�l�Q
	sBuf = SGr_SOKUT->Cells[23][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// �K�i�l�R
	sBuf = SGr_SOKUT->Cells[24][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// �K�i�l����
	sBuf = SGr_SOKUT->Cells[25][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_SUB1		,sBuf.c_str() );	// �K�i�l�T�u�P
	sBuf = SGr_SOKUT->Cells[26][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_SUB2		,sBuf.c_str() );	// �K�i�l�T�u�Q
	sBuf = SGr_SOKUT->Cells[27][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_SUB3		,sBuf.c_str() );	// �K�i�l�T�u�R
	sBuf = SGr_SOKUT->Cells[7][iCpyIndex];
	strcpy( tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// ����w��n��
	sBuf = SGr_SOKUT->Cells[10][iCpyIndex];
	strcpy( tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
	sBuf = SGr_SOKUT->Cells[11][iCpyIndex];
	strcpy( tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
	sBuf = SGr_SOKUT->Cells[28][iCpyIndex];
	strcpy( tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
	sBuf = SGr_SOKUT->Cells[8][iCpyIndex];
	strcpy( tmpKSM02_DATA.VALUE_TYPE	,sBuf.c_str() );	// ����l�\��
	sBuf = SGr_SOKUT->Cells[29][iCpyIndex];
	strcpy( tmpKSM02_DATA.VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
	sBuf = SGr_SOKUT->Cells[30][iCpyIndex];					//�X�V�t���O

	return sBuf;	// �X�V�t���O
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�o�b�t�@�ɕۑ����ꂽStringGrid�f�[�^��StringGrid�̎w��s�ɕ������܂�
//
//  �@�\����
//    �o�b�t�@�ɕۑ����ꂽStringGrid�i���j�f�[�^��StringGrid�̎w��s�ɕ������܂�
//
//  �p�����^����
//    int iPstIndex		�F��������sNO
//    AnsiString sUpdFlg�F��������s�ɐݒ肷��X�V�t���O
//    bool iOrderNo_UP	�F�\����������ւ��邩�ǂ���
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm3::SGr_SOKUT_GridLinePaste( int iPstIndex, AnsiString sUpdFlg, bool iOrderNo_UP )
{

	//									tmpKSM02_DATA.DTKSHIN		;	// ��\���Ӑ�i��
	//									tmpKSM02_DATA.REVCNT		;	// �����ԍ�
	SGr_SOKUT->Cells[1][iPstIndex]	=	tmpKSM02_DATA.HINBAN_SK		;	// �i��
	SGr_SOKUT->Cells[2][iPstIndex]	=	tmpKSM02_DATA.KOMK_NM		;	// ���荀�ږ��́i���{��j
	SGr_SOKUT->Cells[3][iPstIndex]	=	tmpKSM02_DATA.KOMK_SUB		;	// ���荀�ڃT�u���́i���{��j
	SGr_SOKUT->Cells[4][iPstIndex]	=	tmpKSM02_DATA.KOMK_ENG		;	// ���荀�ږ��́i�p��j
	SGr_SOKUT->Cells[5][iPstIndex]	=	tmpKSM02_DATA.TANI			;	// �P��
	SGr_SOKUT->Cells[6][iPstIndex]	=	""							;	// �K�i�@���ĕ`�悷��ׂɕK�v�ł��B
	SGr_SOKUT->Cells[7][iPstIndex]	=	tmpKSM02_DATA.SOKU_SU		;	// ����w��n��
	SGr_SOKUT->Cells[8][iPstIndex]	=	tmpKSM02_DATA.VALUE_TYPE	;	// ����l�\��
	SGr_SOKUT->Cells[9][iPstIndex]	=	tmpKSM02_DATA.KIKI_NM		;	// ����@�햼��
	SGr_SOKUT->Cells[10][iPstIndex]	=	tmpKSM02_DATA.SOKU_FLG		;	// ���荀�ڂ̗L��
	SGr_SOKUT->Cells[11][iPstIndex]	=	tmpKSM02_DATA.TOKU_FLG		;	// ���ʍ��ڂ̗L��
	SGr_SOKUT->Cells[12][iPstIndex]	=	tmpKSM02_DATA.KOMK_NO		;	// ����NO
	SGr_SOKUT->Cells[13][iPstIndex]	=	tmpKSM02_DATA.UNQ_NO		;	// ����NO
    if( iOrderNo_UP ){
		SGr_SOKUT->Cells[14][iPstIndex]	=	tmpKSM02_DATA.ORDER_NO	;	// �\����
    }
	SGr_SOKUT->Cells[15][iPstIndex]	=	tmpKSM02_DATA.SKB_NO		;	// ����NO
	SGr_SOKUT->Cells[16][iPstIndex]	=	tmpKSM02_DATA.KOMK_SUB_ENG	;	// ���荀�ڃT�u���́i�p��j
	SGr_SOKUT->Cells[17][iPstIndex]	=	tmpKSM02_DATA.KIKI_NO		;	// ����@��NO
	SGr_SOKUT->Cells[18][iPstIndex]	=	tmpKSM02_DATA.KIKA_TYPE		;	// �K�i�^�C�v
	SGr_SOKUT->Cells[19][iPstIndex]	=	tmpKSM02_DATA.KIKA_KIND		;	// �K�i���
	SGr_SOKUT->Cells[20][iPstIndex]	=	tmpKSM02_DATA.KIKA_DECI		;	// �K�i�����_�ȉ�����
	SGr_SOKUT->Cells[21][iPstIndex]	=	tmpKSM02_DATA.KIKA_NUM1		;	// �K�i�l�P
	SGr_SOKUT->Cells[22][iPstIndex]	=	tmpKSM02_DATA.KIKA_NUM2		;	// �K�i�l�Q
	SGr_SOKUT->Cells[23][iPstIndex]	=	tmpKSM02_DATA.KIKA_NUM3		;	// �K�i�l�R
	SGr_SOKUT->Cells[24][iPstIndex]	=	tmpKSM02_DATA.KIKA_STR		;	// �K�i�l����
	SGr_SOKUT->Cells[25][iPstIndex]	=	tmpKSM02_DATA.KIKA_SUB1		;	// �K�i�l�T�u�P
	SGr_SOKUT->Cells[26][iPstIndex]	=	tmpKSM02_DATA.KIKA_SUB2		;	// �K�i�l�T�u�Q
	SGr_SOKUT->Cells[27][iPstIndex]	=	tmpKSM02_DATA.KIKA_SUB3		;	// �K�i�l�T�u�R
	SGr_SOKUT->Cells[28][iPstIndex]	=	tmpKSM02_DATA.KIKA_PRT		;	// ��������l�̈��
	SGr_SOKUT->Cells[29][iPstIndex]	=	tmpKSM02_DATA.VALUE_DECI	;	// ����l�����_�ȉ�����
    if( sUpdFlg != "" ){
		SGr_SOKUT->Cells[30][iPstIndex] = sUpdFlg				   	;	//�X�V�t���O�̐ݒ�
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�폜�v�{�^�������������̏���
//
//  �@�\����
//    StringGrid�i���j�őI�����ꂽ�s���폜���܂�
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
void __fastcall TForm3::Btn_DELClick(TObject *Sender)
{

    int			i, k;
    int			iDelCnt;
    AnsiString	sBuf;
	int			iChgRow1;
	int			iChgRow3;

    iChgRow1 = SGr_SOKUT->Selection.Top;
    iChgRow3 = SGr_SOKUT->Selection.Bottom;

    if( SGr_SOKUT->RowCount <= 2) return;
    if( iChgRow1 == SGr_SOKUT->RowCount - 1) return;

    if( iChgRow3 >= SGr_SOKUT->RowCount - 1)
    	iChgRow3 = SGr_SOKUT->Selection.Bottom = SGr_SOKUT->RowCount - 2;

    // �m�F���b�Z�[�W
    k = 0;
	for( i = iChgRow1; i < iChgRow3; i++) {
        if( SGr_SOKUT->Cells[15][i].ToIntDef(-1) == 1 ||
            SGr_SOKUT->Cells[15][i].ToIntDef(-1) == 2 ||
            SGr_SOKUT->Cells[15][i].ToIntDef(-1) == 3 ){
        	k = 1;		// �폜���悤�Ƃ����s�����荀�ڂ̏ꍇ�A�m�F���b�Z�[�W���o�͂��܂�
        }
	}
    if( k == 1 ){
		if( MessageDlg( "����ς݂̏ꍇ�A����f�[�^���폜����܂��B��낵���ł����H",
       		mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
       		return;
    	}
    }

    // �폜��������v�Z���܂�
    iDelCnt = (iChgRow3 - iChgRow1) + 1;

    // �폜���閾��NO��ۑ����܂�
	for( i = iChgRow1; i < iChgRow3; i++) {
        sBuf = SGr_SOKUT->Cells[13][i].ToIntDef(-1);
        sDEL_UNQ_NO->Add(sBuf);
	}

    // �ǉ��f�[�^�̕\������蓯�����傫������\�����|�P���܂�
	for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
        if( SGr_SOKUT->Cells[14][i].ToIntDef(0) >= SGr_SOKUT->Cells[14][iChgRow1].ToIntDef(0) ){
			SGr_SOKUT->Cells[14][i] = IntToStr(SGr_SOKUT->Cells[14][i].ToIntDef(-1) - iDelCnt);
			SGr_SOKUT->Cells[30][i] = "1";		// �X�V�t���O��ON
    	}
	}

    // �폜�s�ȉ��̍s��1��ɂ��炵�܂�
	for( i = iChgRow1; i < (SGr_SOKUT->RowCount - iDelCnt); i++) {
		for( k = 1; k < SGr_SOKUT->ColCount; k++) {
			SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i+iDelCnt];
    	}
	}

	// ��s���炷
	SGr_SOKUT->RowCount = SGr_SOKUT->RowCount - iDelCnt;
	// �ŉ��s���N���A�[
	for( k = 0; k < SGr_SOKUT->ColCount; k++) {
		SGr_SOKUT->Cells[k][SGr_SOKUT->RowCount - 1] = "";
	}

	// �V�����s��I��
	SGr_SOKUT->SetFocus();
    SGr_SOKUTClick( SGr_SOKUT );

    // �f�[�^������\�����܂�
	sBuf = IntToStr(SGr_SOKUT->RowCount-2);
    Pnl_SOKUTEI_NUM->Caption = sBuf;		// ���ڐ��̍X�V

    // �f�[�^�ύX�t���O�̐ݒ�
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F��StringGrid�Ń}�E�X�̍��{�^�����_�u���N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �u�ҏW�v�{�^���������Ăяo���܂�
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
void __fastcall TForm3::SGr_SOKUTDblClick(TObject *Sender)
{
    // ���荀�ڕҏW��ʂ̕\��
    Btn_EDITClick( Btn_EDIT );
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnChange�C�x���g	�F�ҏW�R���g���[���̃e�L�X�g�ɕύX��������ꂽ�Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���͕���(�V���O���R�[�e�[�V�����A���p�J���})�̃`�F�b�N���s�Ȃ��܂��B
//    ���͕����̃`�F�b�N�O�̕ύX�t���O��ݒ肵�܂��B
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
void __fastcall TForm3::Edt_ALLChange_Base(TObject *Sender)
{

	Edt_ALLChange( Sender );

    // �f�[�^�ύX�t���O�̐ݒ�
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnChange�C�x���g	�F�ҏW�R���g���[���̃e�L�X�g�ɕύX��������ꂽ�Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���͕���(�V���O���R�[�e�[�V�����A���p�J���})�̃`�F�b�N���s�Ȃ��܂��B
//    ���͕����̃`�F�b�N�O�̕ύX�t���O��ݒ肵�܂��B�i���Ӑ�i�ԗp�j
//    ��StringGrid�̓��Ӑ�i�Ԃ������ɍX�V���܂��B
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
void __fastcall TForm3::Edt_ALLChange_DTKSHIN(TObject *Sender)
{
	int			i, k;
    AnsiString	sBuf;
    TEdit* edt = dynamic_cast<TEdit*>(Sender);


	Edt_ALLChange( Sender );

    // �f�[�^�ύX�t���O�̐ݒ�
    DataChange = 1;

   	// StringGrid���̏o�׌������ځA�ޗ��ؖ����ڂ̕i�Ԃ𓯎��ɕύX���܂�
    sBuf = edt->Text;
    for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
        k = SGr_SOKUT->Cells[15][i].ToIntDef(-1);
        if( k == 2 || k == 3 ){
	        SGr_SOKUT->Cells[1][i] = sBuf;   // �i��
    	}
	}

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
void __fastcall TForm3::Edt_ALLChange(TObject *Sender)
{

    int			i;
    AnsiString	sBuf;
    TEdit* edt = dynamic_cast<TEdit*>(Sender);


    sBuf = edt->Text;

    // �V���O���R�[�e�[�V�����͂c�a�o�^���ɃG���[����������
    // �̂őS�p�̃V���O���R�[�e�[�V�����ɕϊ����܂�
    i = sBuf.AnsiPos("'");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( edt->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("�f",i);
    	}
        edt->Text = sBuf;
        edt->SelStart = i + 1;
    }

    // ���p�J���}�͂c�a�o�^���ɃG���[����������
    // �̂őS�p�̃J���}�ɕϊ����܂�
    i = sBuf.AnsiPos(",");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( edt->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("�C",i);
    	}
        edt->Text = sBuf;
        edt->SelStart = i + 1;
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnEnter�C�x���g	�F�e�R���g���[�����t�H�[�J�X���擾������
//
//  �@�\����
//    �t�H�[�J�X��Ԃ𔻒f���A�u�e�P�F�ꗗ�����v�{�^���̗L���^������؂�ւ��܂�
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
void __fastcall TForm3::FormEnter(TObject *Sender)
{
    if( BtnF01->Focused() )		return;

    // �ڍו��@���Ӑ�R�[�h�Ƀt�H�[�J�X���L��ꍇ
    if( Edt_DTKSCOD->Focused() && Edt_DTKSCOD->ReadOnly == false ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 5;
        return;
    }

    // �ڍו��@���Ӑ於�̂Ƀt�H�[�J�X���L��ꍇ
    if( Edt_DTKSNAM->Focused() && Edt_DTKSNAM->ReadOnly == false  ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 6;
        return;
    }

    // �ڍו��@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
    if( Edt_DTKSHIN->Focused() && Edt_DTKSHIN->ReadOnly == false  ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 7;
        return;
    }

    // �ڍו��@���Еi�ԂɃt�H�[�J�X���L��ꍇ
    if( Edt_HINBAN->Focused() && Edt_HINBAN->ReadOnly == false  ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 8;
        return;
    }

    // �ڍו��@�ގ����̂Ƀt�H�[�J�X���L��ꍇ
    if( Edt_ZISNAM->Focused() && Edt_ZISNAM->ReadOnly == false  ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 9;
        return;
    }

    // �ڍו��@�i���Ƀt�H�[�J�X���L��ꍇ
    if( Edt_HINMEI->Focused() && Edt_HINMEI->ReadOnly == false  ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 10;
        return;
    }

    // �ڍו��@�f�ޗp�i�ԁu���X�g�{�b�N�X�v�u�I���v�u�폜�v�{�^���Ƀt�H�[�J�X���L��ꍇ
    if( Lbx_DTKSHIN_SZ->Focused() ||
        Btn_DTKSHIN_SZ_ADD->Focused() ||
        Btn_DTKSHIN_SZ_DEL->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 11;
        return;
    }

    // �uF1�F�ꗗ�����v�{�^�����g���Ȃ��悤�ɂ���
    BtnF01->Enabled = false;
    BtnF01->Tag = 0;


}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyDown�C�x���g	�F���[�U�[���C�ӂ̃L�[�������Ɣ������܂�
//
//  �@�\����
//    �t�@���N�V�����L�[�A���L�[�AEnter�L�[�ɂ��{�^����I�����܂�
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
void __fastcall TForm3::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

     switch(Key){
         case VK_F1:  BtnF01Click(Sender);    break;
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
         // 2003/05/19 A.Tamura
         case VK_F10: Key = 0;
					  break;
         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;

         // �O��
         case VK_UP:
         case VK_LEFT:
                break;


         // ����
         case VK_DOWN:
         case VK_RIGHT:
                break;


         // Enter
         case VK_RETURN:
                // �ڍו�
                if( Edt_DTKSHIN->Focused() ){
                    SetDTKSHIN_SZ( Edt_DTKSHIN->Text );
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                	break;
                }
                if( Edt_DTKSCOD->Focused() ){
                    SetDTKSNAM( Edt_DTKSCOD->Text );
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                	break;
                }
                if( Edt_DTKSCOD->Focused() ||
                	Edt_DTKSNAM->Focused() ||
                    Lbx_DTKSHIN_SZ->Focused() ||
                    Rdo_LOT_LINK_SZ_ON->Focused() ||
                    Rdo_LOT_LINK_SZ_OFF->Focused() ||
                    Edt_HINBAN->Focused() ||
                    Edt_ZISNAM->Focused() ||
                    Edt_HINMEI->Focused() ||
                    Clb_OUT_TITLE->Focused() ||
                    Rdo_XOUT_ON->Focused() ||
                    Rdo_XOUT_OFF->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( SGr_SOKUT->Focused() ){
				    // ���荀�ڕҏW��ʂ̕\��
				    Form6->ShowModal();
                	break;
				}
                break;


         // [c]�L�[
         case 67:
				// [Ctrl]�L�[���������� �� ���荀�ڈꗗ�Ƀt�H�[�J�X�����鎞�@
				if( Shift.Contains(ssCtrl) && SGr_SOKUT->Focused() ){
                	// �s�̃R�s�[
                    if( SGr_SOKUT_GridMultiLineCopy() ){
						//SBr1->Panels->Items[0]->Text = "�s���R�s�[���܂����B";
                		//SBr1->Update();
                    }
				}
                break;


         // [v]�L�[
         case 86:
				// [Ctrl]�L�[���������� �� ���荀�ڈꗗ�Ƀt�H�[�J�X�����鎞�@
				if( Shift.Contains(ssCtrl) && SGr_SOKUT->Focused() ){
                	// �s�̓\��t��
                    if( SGr_SOKUT_GridMultiLinePaste() ){
                		//SBr1->Panels->Items[0]->Text = "�s��\��t���܂����B";
                		//SBr1->Update();
                    }
				}
                break;


         // Delete
         case VK_DELETE:
				// ���荀�ڈꗗ�Ƀt�H�[�J�X�����鎞�@
				if( SGr_SOKUT->Focused() ){
                	Btn_DELClick(Sender);
                }
                break;

     }


}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyPress�C�x���g�F�P��̕����L�[���������Ƃ��ɔ������܂��B
//
//  �@�\����
//    RETURN�R�[�h���N���A�[���܂�
//    �r�[�v���Ȃ炳�Ȃ��悤�ɂ���
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    char &Key			�F�L�[�R�[�h
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm3::FormKeyPress(TObject *Sender, char &Key)
{
    if( Key == VK_RETURN )   Key = 0;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ޗp�i�Ԃ́u�w��v�{�^�������������ɔ������܂�
//
//  �@�\����
//    �f�ޗp�i�Ԃ��ꗗ������ʂ���I���w�肵�܂�
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
void __fastcall TForm3::Btn_DTKSHIN_SZ_ADDClick(TObject *Sender)
{
	BtnF01->Enabled = true;
    BtnF01->Tag = 11;
    BtnF01Click( BtnF01 );
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ޗp�i�Ԃ́u�폜�v�{�^�������������ɔ������܂�
//
//  �@�\����
//    �f�ޗp�i�Ԉꗗ�őI������Ă��鍀�ڂ��폜���܂�
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
void __fastcall TForm3::Btn_DTKSHIN_SZ_DELClick(TObject *Sender)
{
    int		i, k;
    int		iCnt;
    bool    fFind;


    fFind = false;

	// �폜���悤�Ƃ���f�ޗp�i�Ԃ����ɓo�^�ς݂��ǂ����`�F�b�N���܂�
	for( i = Lbx_DTKSHIN_SZ->Items->Count - 1; i >= 0; i-- ){
		if( Lbx_DTKSHIN_SZ->Selected[i] ){
			for( k = 1; k < SGr_SOKUT->RowCount - 1; k++ ){
            	if( SGr_SOKUT->Cells[15][k].ToIntDef(2) == 1 && Lbx_DTKSHIN_SZ->Items->Strings[i] == SGr_SOKUT->Cells[1][k] ){
					fFind = true;
                    break;
                }
        	}
			if(	fFind ) break;
		}
	}

	// �폜���悤�Ƃ���f�ޗp�i�Ԃ����ɓo�^����Ă����ꍇ
	if( fFind ){
		if( MessageDlg( "�o�^�ς݂̑f�ޗp���荀�ڂ��폜����܂��B��낵���ł����H",
        	mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
        	return;
        }

        // �w�肳�ꂽ�o�^�ς݂̑f�ޗp���荀�ڂ��폜���܂�
		for( i = Lbx_DTKSHIN_SZ->Items->Count - 1; i >= 0; i-- ){
			if( Lbx_DTKSHIN_SZ->Selected[i] ){
				for( k = SGr_SOKUT->RowCount - 2; k >= 1 ; k-- ){
	            	if( SGr_SOKUT->Cells[15][k].ToIntDef(2) == 1
                        && Lbx_DTKSHIN_SZ->Items->Strings[i] == SGr_SOKUT->Cells[1][k] ){

                        // �폜����
                        SGr_SOKUT->Row	= k;
                        iRowSelTop		= k;
                        iRowSelBottom	= k;
                    	Btn_DELClick(Btn_DEL);
	                }
	        	}
			}
		}
	}

    iCnt = Lbx_DTKSHIN_SZ->Items->Count;

    // �f�ޗp�i�Ԃ��폜���܂�
	for( i = Lbx_DTKSHIN_SZ->Items->Count - 1; i >= 0; i-- ){
    	if( Lbx_DTKSHIN_SZ->Selected[i] ){
        	Lbx_DTKSHIN_SZ->Items->Delete(i);
        }
    }
    if( Lbx_DTKSHIN_SZ->Items->Count >= 1 ){
    	Lbx_DTKSHIN_SZ->Selected[Lbx_DTKSHIN_SZ->Items->Count - 1] = true;
    }

    if( iCnt != Lbx_DTKSHIN_SZ->Items->Count ){
    	// �f�[�^�ύX�t���O�̐ݒ�
    	DataChange = 1;
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F���W�I�{�^�����N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���͕����̃`�F�b�N�O�̕ύX�t���O��ݒ肵�܂��B
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
void __fastcall TForm3::Rdo_AllClick(TObject *Sender)
{

	// �f�[�^�ύX�t���O�̐ݒ�
    DataChange = 1;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�^�C�g�����o�͏��v
//    ���[�U�[�����ڂ̃`�F�b�N�{�b�N�X��I���܂��͑I�����������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �^�C�g�����o�͏��̍��ڑI�𐔂𐧌����܂��B
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
void __fastcall TForm3::Clb_OUT_TITLEClickCheck(TObject *Sender)
{
    int		i, k;

    k = 0;
    for( i = 0; i < iTITLE_Cnt; i++){
        if( Clb_OUT_TITLE->Checked[i] == true ){
            k++;
        }
    }

    if( k > 8 ){
    	Clb_OUT_TITLE->Checked[Clb_OUT_TITLE->ItemIndex] = false;
    } else {
        // �f�[�^�ύX�t���O�̐ݒ�
        DataChange = 1;
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnDrawCell�C�x���g�F�O���b�h���i���j�̃Z����`�悷��K�v������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �O���b�h���i���j�̃Z���`����R���g���[�����܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol			�F�I�������̈ʒu
//    int ARow			�F�I������s�̈ʒu
//    TRect &Rect		�F�`��Z���̍�����ƉE�����̍��W
//    TGridDrawState State�F�`��Z���̏��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm3::SGr_SOKUTDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{

   AnsiString	sBuf, sValue;
   char 		cFormatBuf[20], c1[20], c2[10];
   long			iPos;

   RECT r=RECT(Rect);

   //�Œ�Z���̔w�i�F���Z�b�g
   if(State.Contains(gdFixed))
       SGr_SOKUT->Canvas->Brush->Color= SGr_SOKUT->FixedColor;
   //�t�H�[�J�X�̂���Z���̔w�i�F���Z�b�g
//   else if(State.Contains(gdFocused))
//       SGr_SOKUTr1->Canvas->Brush->Color= SGr_SOKUTr1->Options.Contains(goDrawFocusSelected)? clHighlight: SGr_SOKUTr1->Color;
   //�I������Ă���Z���̔w�i�F���Z�b�g
   else if(State.Contains(gdSelected))
       SGr_SOKUT->Canvas->Brush->Color= clHighlight;
   //���ʂ̃Z���̔w�i�F���Z�b�g
   else {
       if( ARow > 0 ){
           switch( SGr_SOKUT->Cells[15][ARow].ToIntDef(9) ){
               case 1: // �f�ތ�������
                       SGr_SOKUT->Canvas->Brush->Color = (TColor)0x00D2FFFF;
                       break;
               case 2: // �o�׌�������
                       SGr_SOKUT->Canvas->Brush->Color = (TColor)0x00FFEEDD;
                       break;
               case 3: // �ޗ��ؖ�����
                       SGr_SOKUT->Canvas->Brush->Color = (TColor)0x00FFE1FD;
                       break;
               case 9: // �X�y�[�X
               default:
                       SGr_SOKUT->Canvas->Brush->Color = SGr_SOKUT->Color;
                       break;
           }
       }
   }
   //�w�i�F�ŏ���
   SGr_SOKUT->Canvas->FillRect(Rect);

   //�Œ�Z���̗��̘g��`��
   if(SGr_SOKUT->Ctl3D&&State.Contains(gdFixed))
       DrawEdge(SGr_SOKUT->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);

   //�t�H�[�J�X�̂���Z���̕����F���Z�b�g
   if(State.Contains(gdFocused)){
//       SGr_SOKUTr1->Canvas->Font->Color= SGr_SOKUTr1->Options.Contains(goDrawFocusSelected)? clHighlightText: SGr_SOKUTr1->Font->Color;
//       //�t�H�[�J�X�g��`��
//       DrawFocusRect(SGr_SOKUTr1->Canvas->Handle,&r);
	   //�I������Ă���Z���̕����F���Z�b�g
       //if(State.Contains(gdSelected))

       SGr_SOKUT->Canvas->Font->Color= clHighlightText;
   }
   //�I������Ă���Z���̕����F���Z�b�g
   else if(State.Contains(gdSelected))
       SGr_SOKUT->Canvas->Font->Color= clHighlightText;
   //���ʂ̃Z���̕����F���Z�b�g
   else
       SGr_SOKUT->Canvas->Font->Color= SGr_SOKUT->Font->Color;

   //�e�L�X�g�\���̈�̐ݒ�
   InflateRect(&r,-2,-2);

   if( ARow > 0 && ACol == 6 ){

        // �K�i�^�C�v���̕\��
        switch( SGr_SOKUT->Cells[18][ARow].ToIntDef(0) ){
            case 1: // �͈͎w��

                    // �����_�ȉ������̃t�H�[�}�b�g������
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",SGr_SOKUT->Cells[20][ARow].ToIntDef(0) );
            		strcat(c1,c2);

			        switch( SGr_SOKUT->Cells[19][ARow].ToIntDef(0) ){
            			case 1: // �����������
                                sValue = SGr_SOKUT->Cells[21][ARow];
                                //2003.05.08 E.Takase Add��
                                sprintf(cFormatBuf, c1,  Form1->ConvDoubleDefD(sValue,0.0) );
			                    //2003.05.08 E.Takase Add��
			                    //2003.05.08 E.Takase Add �R�����g��
			                    //sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
                     			sBuf = cFormatBuf;
                     			sBuf +=  "�`";
                                sValue = SGr_SOKUT->Cells[22][ARow];
                                //2003.05.08 E.Takase Add��
                                sprintf(cFormatBuf, c1,  Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			                    //2003.05.08 E.Takase Add �R�����g��
                     			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
                     			sBuf += cFormatBuf ;
                                double	Val1, Val2;
                                //2003.05.08 E.Takase Add��
                                Val1 = Form1->ConvDoubleDefD(SGr_SOKUT->Cells[21][ARow],0.0);
                                Val2 = Form1->ConvDoubleDefD(SGr_SOKUT->Cells[22][ARow],0.0);
                                //2003.05.08 E.Takase Add��
			                    //2003.05.08 E.Takase Add �R�����g��
								//try {
								//	Val1 = SGr_SOKUT->Cells[21][ARow].ToDouble();
								//	Val2 = SGr_SOKUT->Cells[22][ARow].ToDouble();
								//} catch(EConvertError& e) {
                                //	Val1 = 0;
                                //	Val2 = 0;
								//} catch(Exception& e) {
                                //	Val1 = 0;
                                //	Val2 = 0;
								//}
                                //2003.05.08 E.Takase Add �R�����g��
								if( Val1 >= Val2 ){
                                    // �K�i�͈͎̔w�肪�s���ȏꍇ�́A�ԐF�ŕ\�����܂�
									SGr_SOKUT->Canvas->Font->Color= clRed;
								}
			            		break;

            			case 2: // ����̂�
                                sValue = SGr_SOKUT->Cells[22][ARow];
                                //2003.05.08 E.Takase Add��
                                sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			                    //2003.05.08 E.Takase Add �R�����g��
                     			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
                     			sBuf = cFormatBuf ;
                     			sBuf += "�ȉ�";
			            		break;
            			case 3: // �����̂�
                                sValue = SGr_SOKUT->Cells[21][ARow];
                                //2003.05.08 E.Takase Add��
                                sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			                    //2003.05.08 E.Takase Add �R�����g��
                     			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
                     			sBuf = cFormatBuf ;
                     			sBuf += "�ȏ�";
			            		break;
                    }
					DrawText(SGr_SOKUT->Canvas->Handle,sBuf.c_str(),-1,&r,0); //����
            		break;

            case 2: // ��l�w��

                    // �����_�ȉ������̃t�H�[�}�b�g������
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",SGr_SOKUT->Cells[20][ARow].ToIntDef(0) );
            		strcat(c1,c2);

                    sValue = SGr_SOKUT->Cells[21][ARow];
                    //2003.05.08 E.Takase Add��
                    sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                    //2003.05.08 E.Takase Add��
			        //2003.05.08 E.Takase Add �R�����g��
                    //sprintf(cFormatBuf, c1, sValue.ToDouble() );
                    //2003.05.08 E.Takase Add �R�����g��
                    sBuf = cFormatBuf ;
        			SGr_SOKUT->Canvas->TextOut( r.left +  0, r.top + 0, sBuf );
                    iPos = sBuf.Length() * 8;

        			// �t�H���g�i���j�̐ݒ�
        			OrgFont = SelectObject( SGr_SOKUT->Canvas->Handle, MyFont );

			        switch( SGr_SOKUT->Cells[19][ARow].ToIntDef(0) ){
            			case 1: // �����������
                    			sValue = SGr_SOKUT->Cells[22][ARow];
                                //2003.05.08 E.Takase Add��
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			        			//2003.05.08 E.Takase Add �R�����g��
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
                                SGr_SOKUT->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
                     			sValue = SGr_SOKUT->Cells[23][ARow];
                                //2003.05.08 E.Takase Add��
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                    			//2003.05.08 E.Takase Add��
			        			//2003.05.08 E.Takase Add �R�����g��
                                //sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						SGr_SOKUT->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;

            			case 2: // ����̂�
			                    sValue = SGr_SOKUT->Cells[22][ARow];
                                //2003.05.08 E.Takase Add��
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			        			//2003.05.08 E.Takase Add �R�����g��
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
			        			SGr_SOKUT->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
			            		break;
            			case 3: // �����̂�
                     			sValue = SGr_SOKUT->Cells[23][ARow];
                                //2003.05.08 E.Takase Add��
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			        			//2003.05.08 E.Takase Add �R�����g��
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						SGr_SOKUT->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;
                    }

        			// ���̃t�H���g�ɖ߂��܂�
        			SelectObject( SGr_SOKUT->Canvas->Handle, OrgFont );

                    break;

        	case 3: // ����
					DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[24][ARow].c_str(),-1,&r,0); //����
                    break;
        }

   } else if( ARow > 0 && ACol == 7 ){
        // ����
        if( SGr_SOKUT->Cells[15][ARow].ToIntDef(0) != 9 ){
            // 2003/06/02 A.Tamura
			if( SGr_SOKUT->Cells[ACol][ARow].ToIntDef(0) < 1 ){
				// n����0�ȉ��i�s���j�ȏꍇ�́A�ԐF�ŕ\�����܂�
				SGr_SOKUT->Canvas->Font->Color= clRed;
            }
		    DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //�E��
        }

   } else if( ARow > 0 && ACol == 8 ){
        // �l�\��
        if( SGr_SOKUT->Cells[15][ARow].ToIntDef(0) != 9 ){
            switch( SGr_SOKUT->Cells[ACol][ARow].ToIntDef(-1) ){
   	   			case 0: // �����E����(99.99)
                        if( SGr_SOKUT->Cells[29][ARow].ToIntDef(0) > 0 ){
                        	sBuf = "9." + AnsiString::StringOfChar('9', SGr_SOKUT->Cells[29][ARow].ToIntDef(0));
                		} else{
                        	sBuf = "9";
                        }
                        DrawText(SGr_SOKUT->Canvas->Handle,sBuf.c_str(),-1,&r,0); //����
                		break;
   	   			case 1: // �p�x(99�K99')
                        if( SGr_SOKUT->Cells[29][ARow].ToIntDef(0) > 0 ){
		                    sBuf = "9��" + AnsiString::StringOfChar('9', SGr_SOKUT->Cells[29][ARow].ToIntDef(0)) + "'";
                		} else{
                        	sBuf = "9��";
                        }
                		DrawText(SGr_SOKUT->Canvas->Handle,sBuf.c_str(),-1,&r,0); //����
                		break;
   	   			case 2: // ��(OK)�^��(NG)
                		DrawText(SGr_SOKUT->Canvas->Handle,"��/��",-1,&r,0); //����
                		break;
   	   			case 3: // ����
                		DrawText(SGr_SOKUT->Canvas->Handle,"����",-1,&r,0); //����
                		break;
           	}
        }

   } else if( ARow > 0 && (ACol == 10 || ACol == 11) ){
        // ���荀�ڂ̗L���A���ʍ��ڂ̗L��
        if( SGr_SOKUT->Cells[15][ARow].ToIntDef(0) != 9 ){
            switch( SGr_SOKUT->Cells[ACol][ARow].ToIntDef(-1) ){
   		    	case 0: DrawText(SGr_SOKUT->Canvas->Handle,"��",-1,&r,DT_CENTER); //�����񂹁i�����j
                		break;
       			case 1: DrawText(SGr_SOKUT->Canvas->Handle,"�L",-1,&r,DT_CENTER); //�����񂹁i�����j
                		break;
            }
       	}

   } else{
		//�e�L�X�g�̕\��
		DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,0); //����
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //�E��
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER); //�����񂹁i�����j
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_VCENTER|DT_SINGLELINE); //�����񂹁i�����j
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_BOTTOM|DT_SINGLELINE); //����
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE); //����������Ƃ�������
		//DrawText(SGr_SOKUT->Canvas->Handle,SGr_SOKUT->Cells[ACol][ARow].c_str(),-1,&r,DT_WORDBREAK); //�����s�\��
   }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyPress�C�x���g�FStringGrid�ŃL�[���������Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���L�[�ɂ��{�^����I�����܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    char &Key			�F�L�[�R�[�h
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm3::SGr_ListKeyPress(TObject *Sender, char &Key)
{
     switch(Key)
     {
         // �O��
         case VK_UP:
         case VK_LEFT:  BtnF02Click(Sender);    break;

         // ����
         case VK_DOWN:
         case VK_RIGHT: BtnF03Click(Sender);    break;

     }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�FStringGrid�̍s�̈ʒu���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    StringGrid�ōs���ړ����ꂽ�i�h���b�O�j���̕����s�Ή�����
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int FromIndex		�F�ړ����̍s�ʒu
//    int ToIndex		�F�ړ���̍s�ʒu
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm3::SGr_SOKUTRowMoved(TObject *Sender, int FromIndex,
      int ToIndex)
{

    int         i, k, m;
	int			CopyCnt;
    int			iStart;
    int			iEnd;
    int			iSkip;
    HANDLE  	hMemCopy;
    AnsiString  sBuf;
    KSM02_DATA  *pKSM02_DATA;
	TGridRect	myRect;


    // �͈͑I���������̂Ǝ��ۂɈړ��������ꂽ�s�̎w��ʒu���قȂ鎞�́A�G���[
    if( FromIndex < iRowSelTop || FromIndex > iRowSelBottom ){
        RowExchange( FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�I��͈͂�����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // �͈͑I�������ړ��悪�A���͈̔͑I����ւ̈ړ��̎��́A�G���[
    if( ToIndex >= iRowSelTop && ToIndex <= iRowSelBottom ){
        RowExchange( FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�ړ��悪����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // �ŉ��s�̉��ֈړ��̎��́A�G���[
    if( ToIndex >= SGr_SOKUT->RowCount - 1 ){
        RowExchange( FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�ړ��悪����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // �͈͑I���������̂ɍŉ��s���܂ގ��́A�G���[
    if( SGr_SOKUT->RowCount - 1 <= iRowSelBottom ){
        RowExchange( FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�I��͈͂�����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    if( FromIndex < ToIndex ){
        iStart = iRowSelTop;
        iEnd   = ToIndex;

		// �\���������ւ��܂�
    	sBuf = SGr_SOKUT->Cells[14][ToIndex];
		for( i = ToIndex; i > FromIndex; i-- ){
			SGr_SOKUT->Cells[14][i] = SGr_SOKUT->Cells[14][i-1];
    	}
    	SGr_SOKUT->Cells[14][FromIndex] = sBuf;
    }
    else {
        iStart = ToIndex;
        iEnd   = iRowSelBottom;

		// �\���������ւ��܂�
        sBuf = SGr_SOKUT->Cells[14][ToIndex];
		for( i = ToIndex; i < FromIndex; i++ ){
			SGr_SOKUT->Cells[14][i] = SGr_SOKUT->Cells[14][i+1];
    	}
    	SGr_SOKUT->Cells[14][FromIndex] = sBuf;
    }

	// �sNo�����ɖ߂��܂�
	for( i = iStart; i <= iEnd; i++ ){
		sBuf = i ;
		if( i < SGr_SOKUT->RowCount - 1 ){
			SGr_SOKUT->Cells[0][i] = AnsiString::StringOfChar(' ', 2-sBuf.Length()) + sBuf;
   	    	SGr_SOKUT->Cells[30][i] = "1";						// �X�V�t���OON
		}
        else{
			SGr_SOKUT->Cells[0][i] = "";
   	    	SGr_SOKUT->Cells[30][i] = "";
        }
    }

    // �R�s�[�̌����m�ۂ��܂�
    CopyCnt = iRowSelBottom - iRowSelTop;

    // �������̊m��
    hMemCopy = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * CopyCnt );
    if( hMemCopy == NULL ){
    	MessageDlg("�������̈���m�ۂł��܂���B(01)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }
    pKSM02_DATA = (struct KSM02_DATA *)GlobalLock(hMemCopy);
    if( hMemCopy == NULL ){
    	MessageDlg("�������̈���m�ۂł��܂���B(02)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    if( FromIndex < ToIndex ){

	    // �I������Ă���͈͂��������Ɋi�[���܂�
    	for( i=iRowSelTop, k=0; i<iRowSelBottom; i++, k++ ) {
			//strcpy( pKSM02_DATA[k].DTKSHIN	,sBuf.c_str() );	// ��\���Ӑ�i��
			//strcpy( pKSM02_DATA[k].REVCNT		,sBuf.c_str() );	// �����ԍ�
			sBuf = SGr_SOKUT->Cells[13][i];
			strcpy( pKSM02_DATA[k].UNQ_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[14][i];
			strcpy( pKSM02_DATA[k].ORDER_NO		,sBuf.c_str() );	// �\����
			sBuf = SGr_SOKUT->Cells[15][i];
			strcpy( pKSM02_DATA[k].SKB_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[1][i];
			strcpy( pKSM02_DATA[k].HINBAN_SK	,sBuf.c_str() );	// �i��
			sBuf = SGr_SOKUT->Cells[12][i];
			strcpy( pKSM02_DATA[k].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[2][i];
			strcpy( pKSM02_DATA[k].KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
			sBuf = SGr_SOKUT->Cells[4][i];
			strcpy( pKSM02_DATA[k].KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
			sBuf = SGr_SOKUT->Cells[3][i];
			strcpy( pKSM02_DATA[k].KOMK_SUB		,sBuf.c_str() );	// ���荀�ڃT�u���́i���{��j
			sBuf = SGr_SOKUT->Cells[16][i];
			strcpy( pKSM02_DATA[k].KOMK_SUB_ENG	,sBuf.c_str() );	// ���荀�ڃT�u���́i�p��j
			sBuf = SGr_SOKUT->Cells[17][i];
			strcpy( pKSM02_DATA[k].KIKI_NO		,sBuf.c_str() );	// ����@��NO
			sBuf = SGr_SOKUT->Cells[9][i];
			strcpy( pKSM02_DATA[k].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
			sBuf = SGr_SOKUT->Cells[5][i];
			strcpy( pKSM02_DATA[k].TANI			,sBuf.c_str() );	// �P��
			sBuf = SGr_SOKUT->Cells[18][i];
			strcpy( pKSM02_DATA[k].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
			sBuf = SGr_SOKUT->Cells[19][i];
			strcpy( pKSM02_DATA[k].KIKA_KIND	,sBuf.c_str() );	// �K�i���
			sBuf = SGr_SOKUT->Cells[20][i];
			strcpy( pKSM02_DATA[k].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = SGr_SOKUT->Cells[21][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = SGr_SOKUT->Cells[22][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = SGr_SOKUT->Cells[23][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = SGr_SOKUT->Cells[24][i];
			strcpy( pKSM02_DATA[k].KIKA_STR		,sBuf.c_str() );	// �K�i�l����
			sBuf = SGr_SOKUT->Cells[25][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB1	,sBuf.c_str() );	// �K�i�l�T�u�P
			sBuf = SGr_SOKUT->Cells[26][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB2	,sBuf.c_str() );	// �K�i�l�T�u�Q
			sBuf = SGr_SOKUT->Cells[27][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB3	,sBuf.c_str() );	// �K�i�l�T�u�R
			sBuf = SGr_SOKUT->Cells[7][i];
			strcpy( pKSM02_DATA[k].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = SGr_SOKUT->Cells[10][i];
			strcpy( pKSM02_DATA[k].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = SGr_SOKUT->Cells[11][i];
			strcpy( pKSM02_DATA[k].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = SGr_SOKUT->Cells[28][i];
			strcpy( pKSM02_DATA[k].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = SGr_SOKUT->Cells[8][i];
			strcpy( pKSM02_DATA[k].VALUE_TYPE	,sBuf.c_str() );	// ����l�\��
			sBuf = SGr_SOKUT->Cells[29][i];
			strcpy( pKSM02_DATA[k].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
    	}

		// �����I����e���ړ����܂�
		for( i = iRowSelBottom; i <= ToIndex; i++ ){
	    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
	            if( k == 14 ){
	                // �\�����́A����ւ����Ȃ�
	    			// SGr_SOKUT->Cells[k][i-CopyCnt] = SGr_SOKUT->Cells[k][i];
	        	} else {
					SGr_SOKUT->Cells[k][i-CopyCnt] = SGr_SOKUT->Cells[k][i];
	            }
			}
    	}

        // �����ړ����ꂽ�s�𐳂����ʒu�Ɉړ����܂��B
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
	    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
	            if( k == 14 ){
	                // �\�����́A����ւ����Ȃ�
	    			// SGr_SOKUT->Cells[k][ToIndex-CopyCnt+iSkip] = SGr_SOKUT->Cells[k][ToIndex];
	        	} else {
					SGr_SOKUT->Cells[k][ToIndex-CopyCnt+iSkip] = SGr_SOKUT->Cells[k][ToIndex];
	            }
			}
        }

		// �������Ɋi�[�������e��߂��܂�
        i = ToIndex - CopyCnt;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
				//								pKSM02_DATA[m].DTKSHIN		;	// ��\���Ӑ�i��
				//								pKSM02_DATA[m].REVCNT		;	// �����ԍ�
				SGr_SOKUT->Cells[1][i+k]	=	pKSM02_DATA[m].HINBAN_SK	;	// �i��
				SGr_SOKUT->Cells[2][i+k]	=	pKSM02_DATA[m].KOMK_NM		;	// ���荀�ږ��́i���{��j
				SGr_SOKUT->Cells[3][i+k]	=	pKSM02_DATA[m].KOMK_SUB		;	// ���荀�ڃT�u���́i���{��j
				SGr_SOKUT->Cells[4][i+k]	=	pKSM02_DATA[m].KOMK_ENG		;	// ���荀�ږ��́i�p��j
				SGr_SOKUT->Cells[5][i+k]	=	pKSM02_DATA[m].TANI			;	// �P��
				SGr_SOKUT->Cells[6][i+k]	=	""							;	// �K�i�@���ĕ`�悷��ׂɕK�v�ł��B
				SGr_SOKUT->Cells[7][i+k]	=	pKSM02_DATA[m].SOKU_SU		;	// ����w��n��
				SGr_SOKUT->Cells[8][i+k]	=	pKSM02_DATA[m].VALUE_TYPE	;	// ����l�\��
				SGr_SOKUT->Cells[9][i+k]	=	pKSM02_DATA[m].KIKI_NM		;	// ����@�햼��
				SGr_SOKUT->Cells[10][i+k]	=	pKSM02_DATA[m].SOKU_FLG		;	// ���荀�ڂ̗L��
				SGr_SOKUT->Cells[11][i+k]	=	pKSM02_DATA[m].TOKU_FLG		;	// ���ʍ��ڂ̗L��
				SGr_SOKUT->Cells[12][i+k]	=	pKSM02_DATA[m].KOMK_NO		;	// ����NO
				SGr_SOKUT->Cells[13][i+k]	=	pKSM02_DATA[m].UNQ_NO		;	// ����NO
				//SGr_SOKUT->Cells[14][i+k]	=	pKSM02_DATA[m].ORDER_NO		;	// �\����
				SGr_SOKUT->Cells[15][i+k]	=	pKSM02_DATA[m].SKB_NO		;	// ����NO
				SGr_SOKUT->Cells[16][i+k]	=	pKSM02_DATA[m].KOMK_SUB_ENG	;	// ���荀�ڃT�u���́i�p��j
				SGr_SOKUT->Cells[17][i+k]	=	pKSM02_DATA[m].KIKI_NO		;	// ����@��NO
				SGr_SOKUT->Cells[18][i+k]	=	pKSM02_DATA[m].KIKA_TYPE	;	// �K�i�^�C�v
				SGr_SOKUT->Cells[19][i+k]	=	pKSM02_DATA[m].KIKA_KIND	;	// �K�i���
				SGr_SOKUT->Cells[20][i+k]	=	pKSM02_DATA[m].KIKA_DECI	;	// �K�i�����_�ȉ�����
				SGr_SOKUT->Cells[21][i+k]	=	pKSM02_DATA[m].KIKA_NUM1	;	// �K�i�l�P
				SGr_SOKUT->Cells[22][i+k]	=	pKSM02_DATA[m].KIKA_NUM2	;	// �K�i�l�Q
				SGr_SOKUT->Cells[23][i+k]	=	pKSM02_DATA[m].KIKA_NUM3	;	// �K�i�l�R
				SGr_SOKUT->Cells[24][i+k]	=	pKSM02_DATA[m].KIKA_STR		;	// �K�i�l����
				SGr_SOKUT->Cells[25][i+k]	=	pKSM02_DATA[m].KIKA_SUB1	;	// �K�i�l�T�u�P
				SGr_SOKUT->Cells[26][i+k]	=	pKSM02_DATA[m].KIKA_SUB2	;	// �K�i�l�T�u�Q
				SGr_SOKUT->Cells[27][i+k]	=	pKSM02_DATA[m].KIKA_SUB3	;	// �K�i�l�T�u�R
				SGr_SOKUT->Cells[28][i+k]	=	pKSM02_DATA[m].KIKA_PRT		;	// ��������l�̈��
				SGr_SOKUT->Cells[29][i+k]	=	pKSM02_DATA[m].VALUE_DECI	;	// ����l�����_�ȉ�����
				SGr_SOKUT->Cells[30][i+k]	=	"1"							;	//�X�V�t���O�̐ݒ�
				m++;
        	}
        }

    	// �ړ���̍s��I��͈͂����肵�܂�
		myRect.Left		= SGr_SOKUT->Selection.Left;
		myRect.Top		= ToIndex - CopyCnt;
		myRect.Right	= SGr_SOKUT->Selection.Right;
		myRect.Bottom	= myRect.Top + CopyCnt;
    }
    else {

	    // �I������Ă���͈͂��������Ɋi�[���܂�
    	for( i=iRowSelTop+1, k=0; i<=iRowSelBottom; i++, k++ ) {
			//strcpy( pKSM02_DATA[k].DTKSHIN	,sBuf.c_str() );	// ��\���Ӑ�i��
			//strcpy( pKSM02_DATA[k].REVCNT		,sBuf.c_str() );	// �����ԍ�
			sBuf = SGr_SOKUT->Cells[13][i];
			strcpy( pKSM02_DATA[k].UNQ_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[14][i];
			strcpy( pKSM02_DATA[k].ORDER_NO		,sBuf.c_str() );	// �\����
			sBuf = SGr_SOKUT->Cells[15][i];
			strcpy( pKSM02_DATA[k].SKB_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[1][i];
			strcpy( pKSM02_DATA[k].HINBAN_SK	,sBuf.c_str() );	// �i��
			sBuf = SGr_SOKUT->Cells[12][i];
			strcpy( pKSM02_DATA[k].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[2][i];
			strcpy( pKSM02_DATA[k].KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
			sBuf = SGr_SOKUT->Cells[4][i];
			strcpy( pKSM02_DATA[k].KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
			sBuf = SGr_SOKUT->Cells[3][i];
			strcpy( pKSM02_DATA[k].KOMK_SUB		,sBuf.c_str() );	// ���荀�ڃT�u���́i���{��j
			sBuf = SGr_SOKUT->Cells[16][i];
			strcpy( pKSM02_DATA[k].KOMK_SUB_ENG	,sBuf.c_str() );	// ���荀�ڃT�u���́i�p��j
			sBuf = SGr_SOKUT->Cells[17][i];
			strcpy( pKSM02_DATA[k].KIKI_NO		,sBuf.c_str() );	// ����@��NO
			sBuf = SGr_SOKUT->Cells[9][i];
			strcpy( pKSM02_DATA[k].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
			sBuf = SGr_SOKUT->Cells[5][i];
			strcpy( pKSM02_DATA[k].TANI			,sBuf.c_str() );	// �P��
			sBuf = SGr_SOKUT->Cells[18][i];
			strcpy( pKSM02_DATA[k].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
			sBuf = SGr_SOKUT->Cells[19][i];
			strcpy( pKSM02_DATA[k].KIKA_KIND	,sBuf.c_str() );	// �K�i���
			sBuf = SGr_SOKUT->Cells[20][i];
			strcpy( pKSM02_DATA[k].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = SGr_SOKUT->Cells[21][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = SGr_SOKUT->Cells[22][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = SGr_SOKUT->Cells[23][i];
			strcpy( pKSM02_DATA[k].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = SGr_SOKUT->Cells[24][i];
			strcpy( pKSM02_DATA[k].KIKA_STR		,sBuf.c_str() );	// �K�i�l����
			sBuf = SGr_SOKUT->Cells[25][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB1	,sBuf.c_str() );	// �K�i�l�T�u�P
			sBuf = SGr_SOKUT->Cells[26][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB2	,sBuf.c_str() );	// �K�i�l�T�u�Q
			sBuf = SGr_SOKUT->Cells[27][i];
			strcpy( pKSM02_DATA[k].KIKA_SUB3	,sBuf.c_str() );	// �K�i�l�T�u�R
			sBuf = SGr_SOKUT->Cells[7][i];
			strcpy( pKSM02_DATA[k].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = SGr_SOKUT->Cells[10][i];
			strcpy( pKSM02_DATA[k].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = SGr_SOKUT->Cells[11][i];
			strcpy( pKSM02_DATA[k].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = SGr_SOKUT->Cells[28][i];
			strcpy( pKSM02_DATA[k].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = SGr_SOKUT->Cells[8][i];
			strcpy( pKSM02_DATA[k].VALUE_TYPE	,sBuf.c_str() );	// ����l�\��
			sBuf = SGr_SOKUT->Cells[29][i];
			strcpy( pKSM02_DATA[k].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
    	}

		// �����I����e���ړ����܂�
		for( i = iRowSelTop; i >= ToIndex; i-- ){
	    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
	            if( k == 14 ){
	                // �\�����́A����ւ����Ȃ�
	    			// SGr_SOKUT->Cells[k][i+CopyCnt] = SGr_SOKUT->Cells[k][i];
	        	} else {
					SGr_SOKUT->Cells[k][i+CopyCnt] = SGr_SOKUT->Cells[k][i];
	            }
			}
    	}

        // �����ړ����ꂽ�s�𐳂����ʒu�Ɉړ����܂��B
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
	    	for( k = 1; k < SGr_SOKUT->ColCount; k++ ) {
	            if( k == 14 ){
	                // �\�����́A����ւ����Ȃ�
	    			// SGr_SOKUT->Cells[k][ToIndex+iSkip] = SGr_SOKUT->Cells[k][ToIndex];
	        	} else {
					SGr_SOKUT->Cells[k][ToIndex+iSkip] = SGr_SOKUT->Cells[k][ToIndex];
	            }
			}
        }

		// �������Ɋi�[�������e��߂��܂�
        i = ToIndex;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
				//								pKSM02_DATA[m].DTKSHIN		;	// ��\���Ӑ�i��
				//								pKSM02_DATA[m].REVCNT		;	// �����ԍ�
				SGr_SOKUT->Cells[1][i+k]	=	pKSM02_DATA[m].HINBAN_SK	;	// �i��
				SGr_SOKUT->Cells[2][i+k]	=	pKSM02_DATA[m].KOMK_NM		;	// ���荀�ږ��́i���{��j
				SGr_SOKUT->Cells[3][i+k]	=	pKSM02_DATA[m].KOMK_SUB		;	// ���荀�ڃT�u���́i���{��j
				SGr_SOKUT->Cells[4][i+k]	=	pKSM02_DATA[m].KOMK_ENG		;	// ���荀�ږ��́i�p��j
				SGr_SOKUT->Cells[5][i+k]	=	pKSM02_DATA[m].TANI			;	// �P��
				SGr_SOKUT->Cells[6][i+k]	=	""							;	// �K�i�@���ĕ`�悷��ׂɕK�v�ł��B
				SGr_SOKUT->Cells[7][i+k]	=	pKSM02_DATA[m].SOKU_SU		;	// ����w��n��
				SGr_SOKUT->Cells[8][i+k]	=	pKSM02_DATA[m].VALUE_TYPE	;	// ����l�\��
				SGr_SOKUT->Cells[9][i+k]	=	pKSM02_DATA[m].KIKI_NM		;	// ����@�햼��
				SGr_SOKUT->Cells[10][i+k]	=	pKSM02_DATA[m].SOKU_FLG		;	// ���荀�ڂ̗L��
				SGr_SOKUT->Cells[11][i+k]	=	pKSM02_DATA[m].TOKU_FLG		;	// ���ʍ��ڂ̗L��
				SGr_SOKUT->Cells[12][i+k]	=	pKSM02_DATA[m].KOMK_NO		;	// ����NO
				SGr_SOKUT->Cells[13][i+k]	=	pKSM02_DATA[m].UNQ_NO		;	// ����NO
				//SGr_SOKUT->Cells[14][i+k]	=	pKSM02_DATA[m].ORDER_NO		;	// �\����
				SGr_SOKUT->Cells[15][i+k]	=	pKSM02_DATA[m].SKB_NO		;	// ����NO
				SGr_SOKUT->Cells[16][i+k]	=	pKSM02_DATA[m].KOMK_SUB_ENG	;	// ���荀�ڃT�u���́i�p��j
				SGr_SOKUT->Cells[17][i+k]	=	pKSM02_DATA[m].KIKI_NO		;	// ����@��NO
				SGr_SOKUT->Cells[18][i+k]	=	pKSM02_DATA[m].KIKA_TYPE	;	// �K�i�^�C�v
				SGr_SOKUT->Cells[19][i+k]	=	pKSM02_DATA[m].KIKA_KIND	;	// �K�i���
				SGr_SOKUT->Cells[20][i+k]	=	pKSM02_DATA[m].KIKA_DECI	;	// �K�i�����_�ȉ�����
				SGr_SOKUT->Cells[21][i+k]	=	pKSM02_DATA[m].KIKA_NUM1	;	// �K�i�l�P
				SGr_SOKUT->Cells[22][i+k]	=	pKSM02_DATA[m].KIKA_NUM2	;	// �K�i�l�Q
				SGr_SOKUT->Cells[23][i+k]	=	pKSM02_DATA[m].KIKA_NUM3	;	// �K�i�l�R
				SGr_SOKUT->Cells[24][i+k]	=	pKSM02_DATA[m].KIKA_STR		;	// �K�i�l����
				SGr_SOKUT->Cells[25][i+k]	=	pKSM02_DATA[m].KIKA_SUB1	;	// �K�i�l�T�u�P
				SGr_SOKUT->Cells[26][i+k]	=	pKSM02_DATA[m].KIKA_SUB2	;	// �K�i�l�T�u�Q
				SGr_SOKUT->Cells[27][i+k]	=	pKSM02_DATA[m].KIKA_SUB3	;	// �K�i�l�T�u�R
				SGr_SOKUT->Cells[28][i+k]	=	pKSM02_DATA[m].KIKA_PRT		;	// ��������l�̈��
				SGr_SOKUT->Cells[29][i+k]	=	pKSM02_DATA[m].VALUE_DECI	;	// ����l�����_�ȉ�����
				SGr_SOKUT->Cells[30][i+k]	=	"1"							;	//�X�V�t���O�̐ݒ�
				m++;
        	}
        }

    	// �ړ���̍s��I��͈͂����肵�܂�
		myRect.Left		= SGr_SOKUT->Selection.Left;
		myRect.Top		= ToIndex;
		myRect.Right	= SGr_SOKUT->Selection.Right;
		myRect.Bottom	= ToIndex + CopyCnt;
    }

    // �������̊J��
    if( hMemCopy ){
        GlobalUnlock( hMemCopy );
        GlobalFree( hMemCopy );
    }


    // �ړ���̍s��I�����܂�
    SGr_SOKUT->Row   		= myRect.Top;
    SGr_SOKUT->Selection	= myRect;
    //SGr_ListSelectCell(Sender,1,SGr_SOKUT->Row,true);

    iRowSelTop    = SGr_SOKUT->Selection.Top;
    iRowSelBottom = SGr_SOKUT->Selection.Bottom;

    // �f�[�^�ύX�t���O�̐ݒ�
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F��s�����s�̓���ւ��������s�Ȃ��܂��B
//
//  �@�\����
//    �w�肵���s���m�̓���ւ��������s�Ȃ��܂�
//
//  �p�����^����
//    int FromIndex		�F�ړ����̍s�ʒu
//    int ToIndex		�F�ړ���̍s�ʒu
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm3::RowExchange( int FromIndex, int ToIndex)
{
    int			i, k;
	TGridRect	myRect;
    AnsiString	sBuf;
    AnsiString	sLineNo;


    // ����ւ���̃f�[�^���o�b�N�A�b�v
    sLineNo = SGr_SOKUT->Cells[0][ToIndex];						//�s�ԍ�
	sBuf = SGr_SOKUT_GridLineCopy( ToIndex );

    if( ToIndex > FromIndex ){
		// �㉺�����ւ��܂�
    	for( i=ToIndex; i>FromIndex; i-- ) {
	    	for( k = 0; k < SGr_SOKUT->ColCount; k++ ) {
				SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i-1];
			}
    	}
    }
    else{
		// �㉺�����ւ��܂�
    	for( i=ToIndex; i<FromIndex; i++ ) {
	    	for( k = 0; k < SGr_SOKUT->ColCount; k++ ) {
				SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i+1];
			}
    	}
    }

    // �o�b�N�A�b�v�����f�[�^��߂��܂��i�\�������߂��܂��j
    SGr_SOKUT->Cells[0][FromIndex] = sLineNo						;	//�s�ԍ�
	SGr_SOKUT_GridLinePaste( FromIndex, sBuf, true );


    // �I���������܂�
    //SGr_List->Row	= iRowSelTop;
	myRect.Left		= SGr_SOKUT->Selection.Left;
	myRect.Top		= iRowSelTop;
	myRect.Right	= SGr_SOKUT->Selection.Right;
	myRect.Bottom	= iRowSelBottom;
    SGr_SOKUT->Selection	= myRect;
    //SGr_ListSelectCell(Sender,1,SGr_SOKUT->Row,true);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FStringGrid�i���j�Ƀf�[�^��ǉ����܂�
//
//  �@�\����
//    StringGrid�i���j��KSM02�\���̂̃f�[�^���w�肵���sNo(iRow)�ɒǉ����܂�
//
//  �p�����^����
//    int iRow			�F�ǉ���̈ʒu
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm3::Ins_SGr_SOKUT(int iRow)
{

    int			i, k;
    int			iSOKUT_UNQ_NO_MAX;
    int			iSOKUT_ORDER_NO_MAX;
    AnsiString	sBuf;


    // �ő�o�^�����̃`�F�b�N
    if( SGr_SOKUT->RowCount - 2 >= 99 ){
        MessageDlg( "�ő呪�荀��99���𒴂��Ă��܂��B�o�^�ł��܂���B",
                    mtWarning	, TMsgDlgButtons() << mbOK, 0);
    	return;
    }

    // ��s���₷
	SGr_SOKUT->RowCount = SGr_SOKUT->RowCount + 1;

    // �sNo��t����
	sBuf = IntToStr(SGr_SOKUT->RowCount-2);
	SGr_SOKUT->Cells[0][SGr_SOKUT->RowCount-2] = AnsiString::StringOfChar(' ', 2-sBuf.Length()) + sBuf;
    Pnl_SOKUTEI_NUM->Caption = sBuf;		// ���ڐ��̍X�V

    // �ŉ��s���N���A�[
	for( k = 0; k < SGr_SOKUT->ColCount; k++) {
		SGr_SOKUT->Cells[k][SGr_SOKUT->RowCount-1] = "";
	}

    // �V�����ǉ�����s�́u����NO�v�Ɓu�\�����v�����肵�܂�
    iSOKUT_UNQ_NO_MAX = 0;
    iSOKUT_ORDER_NO_MAX = 0;
    for( i = 1; i < SGr_SOKUT->RowCount - 1; i++ ){
   	    // �ő�̖���NO���擾���܂�
        sBuf = SGr_SOKUT->Cells[13][i];
   	    if( sBuf.ToIntDef(0) > iSOKUT_UNQ_NO_MAX ){
   	        iSOKUT_UNQ_NO_MAX = sBuf.ToIntDef(0);
   	    }
   	    // �ő�̕\�������擾���܂�
        sBuf = Form3->SGr_SOKUT->Cells[14][i];
   	    if( sBuf.ToIntDef(0) > iSOKUT_ORDER_NO_MAX ){
   	        iSOKUT_ORDER_NO_MAX = sBuf.ToIntDef(0);
   	    }
    }

    // �u����NO�v�����肵�܂�
    iSOKUT_UNQ_NO_MAX++;
    sBuf = IntToStr(iSOKUT_UNQ_NO_MAX);
	strcpy( tmpKSM02_DATA.UNQ_NO, sBuf.c_str() );

    // �u�\�����v�̌���ƁA�ǉ��s�ȉ��̃f�[�^���ړ����܂�
    if( iRow >= SGr_SOKUT->RowCount - 2 ){
        // �ǉ�����f�[�^���ŉ��s�̎�

        // �u�\�����v�����肵�܂�
        iSOKUT_ORDER_NO_MAX++;
        sBuf = IntToStr(iSOKUT_ORDER_NO_MAX);
	    strcpy( tmpKSM02_DATA.ORDER_NO, sBuf.c_str() );

    }
    else {
        // �ǉ�����f�[�^�������f�[�^�r���ւ̑}���̎�

        // �u�\�����v�����肵�܂�
        k = SGr_SOKUT->Cells[14][iRow].ToIntDef(0);
        sBuf = k;
	    strcpy( tmpKSM02_DATA.ORDER_NO, sBuf.c_str() );

        // �ǉ��f�[�^�̕\������蓯�����傫������\�����{�P���܂�
	    for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
            if( SGr_SOKUT->Cells[14][i].ToIntDef(0) >= k ){
			    SGr_SOKUT->Cells[14][i] = IntToStr(SGr_SOKUT->Cells[14][i].ToIntDef(0) + 1);
			    SGr_SOKUT->Cells[30][i] = "1";		// �X�V�t���O��ON
    	    }
	    }

        // �V�K�f�[�^�s�ȉ��̍s�����炵�܂�
	    for( i = SGr_SOKUT->RowCount - 2; i > iRow; i--) {
		    for( k = 1; k < SGr_SOKUT->ColCount; k++) {
			    SGr_SOKUT->Cells[k][i] = SGr_SOKUT->Cells[k][i-1];
    	    }
	    }

    }

    // �o�b�N�A�b�v�����f�[�^��߂��܂��i�\�������߂��܂��j
	SGr_SOKUT_GridLinePaste( iRow, "1", true );

    SGr_SOKUT->Row = iRow;

    // �f�[�^�ύX�t���O�̐ݒ�
    DataChange = 1;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�w�肳�ꂽ���Ӑ�i�Ԃ���f�ޗp�i�Ԃ������A�ǉ����܂��B
//
//  �@�\����
//    �o�חp�i�Ԏw���AEnter�L�[�ł��̃R�[�h�����s����܂�
//    �o�חp�i�ԂƓ����f�ޗp�i�Ԃ�����Αf�ޗp�i�Ԉꗗ�ɒǉ����܂�
//
//  �p�����^����
//    AnsiString sDTKSHIN�F���Ӑ�i��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm3::SetDTKSHIN_SZ( AnsiString sDTKSHIN )
{
    int			i, k, m;
    AnsiString	sBuf, sList;


    // �w�蕶����������Ώ����𒆒f���܂�
    if( sDTKSHIN.Trim() == "" )		return;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����s
    sBuf  = "select DISTINCT DTKSHIN from KSD21";
    sBuf += " where DTKSHIN like '" + sDTKSHIN + "%'";
    sBuf += " order by DTKSHIN";

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try
    {
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True ){
            // �������ʖ���
            Beep();
    		MessageDlg("�Y���̑f�ޗp�i�Ԃ�������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
            return;
        }
        else{
            // �������ʗL��

            sList = "";
            while( !Query1->Eof ){

                if( VarIsNull(Query1->FieldValues["DTKSHIN"]) ){
		            sBuf = "";
                } else{
                    sBuf = Query1->FieldValues["DTKSHIN"];
                }
                if( sBuf.Trim() != "" )	{
                    if( sList != "" )	sList = sList + ",";
                    sList = sList + sBuf;
                }
                // �J�[�\�������ɃZ�b�g����
                Query1->Next();
            }

            // ���ɑf�ޕi�Ԃ������������������b�Z�[�W���o���܂�
            m = 0;
			for( i = Lbx_DTKSHIN_SZ->Items->Count - 1; i >= 0; i-- ){
				for( k = SGr_SOKUT->RowCount - 2; k >= 1 ; k-- ){
	            	if( SGr_SOKUT->Cells[15][k].ToIntDef(2) == 1
                        && Lbx_DTKSHIN_SZ->Items->Strings[i] == SGr_SOKUT->Cells[1][k] ){
                        sBuf  = "�f�ޗp�i�Ԃ������������܂����B[" + sList + "]\n";
                        sBuf += "�f�ޗp�i�ԂɃZ�b�g���Ă�낵���ł����H�i�o�^�ς݂̑f�ޗp���荀�ڂ͍폜����܂��B�j";
						if( MessageDlg( sBuf, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo ){
        					return;
        				}
                        m = 1;
                    	break;
	                }
	        	}
                if( m == 1 ) break;
			}

        	// �w�肳�ꂽ�o�^�ς݂̑f�ޗp���荀�ڂ��폜���܂�
			for( i = Lbx_DTKSHIN_SZ->Items->Count - 1; i >= 0; i-- ){
				for( k = SGr_SOKUT->RowCount - 2; k >= 1 ; k-- ){
	            	if( SGr_SOKUT->Cells[15][k].ToIntDef(2) == 1
                        && Lbx_DTKSHIN_SZ->Items->Strings[i] == SGr_SOKUT->Cells[1][k] ){

                        // �폜����
                        SGr_SOKUT->Row	= k;
                        iRowSelTop		= k;
                        iRowSelBottom	= k;
                    	Btn_DELClick(Btn_DEL);
	                }
	        	}
			}

            Lbx_DTKSHIN_SZ->Clear();
            Query1->First();
            while( !Query1->Eof ){

                if( VarIsNull(Query1->FieldValues["DTKSHIN"]) ){
		            sBuf = "";
                } else{
                    sBuf = Query1->FieldValues["DTKSHIN"];
                }
                if( sBuf.Trim() != "" )	{
                	Lbx_DTKSHIN_SZ->Items->Add(sBuf);
                	if( Lbx_DTKSHIN_SZ->Items->Count >= 6 )	break;
                }
                // �J�[�\�������ɃZ�b�g����
                Query1->Next();
            }
            return;
        }
    }
    catch(EDatabaseError& e)
    {
        Beep();
    	MessageDlg(e.Message, mtWarning,
                   TMsgDlgButtons() << mbOK , 0);
        return;
    }
    catch(Exception& e)
    {
        Beep();
    	MessageDlg(e.Message, mtWarning,
                   TMsgDlgButtons() << mbOK , 0);
        return;
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�w�肳�ꂽ���Ӑ�R�[�h���瓾�Ӑ於�̂������A�ǉ����܂��B
//
//  �@�\����
//    ���Ӑ�R�[�h�w���AEnter�L�[�ł��̃R�[�h�����s����܂�
//    �Y�����链�Ӑ�R�[�h������Γ��Ӑ於�̂�ݒ肵�܂�
//
//  �p�����^����
//    AnsiString sDTKSCOD�F���Ӑ�R�[�h
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm3::SetDTKSNAM( AnsiString sDTKSCOD )
{
    AnsiString	sBuf;


    // �w�蕶����������Ώ����𒆒f���܂�
    if( sDTKSCOD.Trim() == "" )		return;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����s
    sBuf = "select TRSNAM from SM16S where TKSKBN=1";
    sBuf = sBuf + " and TRSCOD = '" + sDTKSCOD + "'";

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try
    {
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True ){
            // �������ʖ���
            Beep();
    	    MessageDlg("�Y���̓��Ӑ於�̂�������܂���B", mtWarning,
                   TMsgDlgButtons() << mbOK , 0);
            return;
        }
        else{
            // �������ʗL��
            Edt_DTKSNAM->Text = Query1->FieldValues["TRSNAM"];
            return;
        }
    }
    catch(EDatabaseError& e)
    {
        Beep();
    	MessageDlg(e.Message, mtWarning,
                   TMsgDlgButtons() << mbOK , 0);
        return;
    }
    catch(Exception& e)
    {
        Beep();
    	MessageDlg(e.Message, mtWarning,
                   TMsgDlgButtons() << mbOK , 0);
        return;
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�[�^���X�V�iKSD01�j���܂��B
//
//  �@�\����
//    �u�e�P�P�F�ۑ��v���̃f�[�^�X�V�iKSD01�j����
//    �w�胍�b�gNO���̏���
//
//  �p�����^����
//    AnsiString sLOTNO	�F���b�gNO
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm3::UpdData_KSD01( AnsiString sLOTNO )
{
    AnsiString sBuf;
    int iCol;

    // 2004/08/27 A.Tamura ���ڕҏW��ʂ̏I����ɑΏۂ̃��b�g��ۑ�����ׁA
    //                     �����ōX�V�t���O���Z�b�g���܂��B

	// �ύX�Ώۂ̃��b�g��ۑ��ΏۂƂ��Đݒ肵�܂�
	switch(pInfoGlaph.GRID_NO) {
	case 1:
	case 3:
		if( hSOKU_KSD01_DATA) {
			for(iCol = 0; iCol < Form1->SGr_tSOKU->ColCount; iCol++) {
				sBuf = Form1->SGr_tSOKU->Cells[iCol][0];
				if( sBuf.Trim() == sLOTNO ){
					pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
					pSOKU_KSD01_DATA[iCol].SAVE_FLG = false;
				}
			}
		}
		break;
	case 2:
	case 4:
		if( hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)
		{
			for(iCol = 0; iCol < Form1->SGr_tRIRE->ColCount; iCol++)
			{
				sBuf = Form1->SGr_tRIRE->Cells[iCol][0];
				if( sBuf.Trim() == sLOTNO ){
					pRIRE_KSD01_DATA[iCol].UPD_FLG = true;
					pRIRE_KSD01_DATA[iCol].SAVE_FLG = false;
				}
			}
		}
		break;
	}

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf  = "select DTKSHIN from KSD01";
    sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN) + "'";	// ���Ӑ�i��
    sBuf += " and LOTNO='" + sLOTNO + "'";									// ���b�gNO

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True && Query1->Bof == True ){
			MessageDlg("�Ώۃf�[�^(�i��=[" + AnsiString(tmpKSD01_DATA.DTKSHIN) +
                       "],���b�gNO=[" + sLOTNO + "])��������܂���B\n" +
                       "�����𒆒f���܂��B",
                       mtWarning, TMsgDlgButtons() << mbOK , 0);
            return(False);
        }
    }
    catch(EDatabaseError& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }
    catch(Exception& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf  = "update KSD01 set";
    if( AnsiString(tmpKSD01_DATA.DTKSHIN1_SZ).Trim() == "" )    sBuf += " LOTNO1_SZ=' ',";
    if( AnsiString(tmpKSD01_DATA.DTKSHIN2_SZ).Trim() == "" )    sBuf += " LOTNO2_SZ=' ',";
    if( AnsiString(tmpKSD01_DATA.DTKSHIN3_SZ).Trim() == "" )    sBuf += " LOTNO3_SZ=' ',";
    if( AnsiString(tmpKSD01_DATA.DTKSHIN4_SZ).Trim() == "" )    sBuf += " LOTNO4_SZ=' ',";
    if( AnsiString(tmpKSD01_DATA.DTKSHIN5_SZ).Trim() == "" )    sBuf += " LOTNO5_SZ=' ',";
    if( AnsiString(tmpKSD01_DATA.DTKSHIN6_SZ).Trim() == "" )    sBuf += " LOTNO6_SZ=' ',";
    sBuf += " HINBAN='"		+ AnsiString(tmpKSD01_DATA.HINBAN)		+ "',";
    sBuf += " DTKSCOD='"	+ AnsiString(tmpKSD01_DATA.DTKSCOD)		+ "',";
    sBuf += " DTKSNAM='"	+ AnsiString(tmpKSD01_DATA.DTKSNAM)		+ "',";
    sBuf += " ZISNAM='"		+ AnsiString(tmpKSD01_DATA.ZISNAM)		+ "',";
    sBuf += " HINMEI='"		+ AnsiString(tmpKSD01_DATA.HINMEI)		+ "',";
    sBuf += " DTKSHIN1_SZ='"+ AnsiString(tmpKSD01_DATA.DTKSHIN1_SZ)	+ "',";
    sBuf += " DTKSHIN2_SZ='"+ AnsiString(tmpKSD01_DATA.DTKSHIN2_SZ)	+ "',";
    sBuf += " DTKSHIN3_SZ='"+ AnsiString(tmpKSD01_DATA.DTKSHIN3_SZ)	+ "',";
    sBuf += " DTKSHIN4_SZ='"+ AnsiString(tmpKSD01_DATA.DTKSHIN4_SZ)	+ "',";
    sBuf += " DTKSHIN5_SZ='"+ AnsiString(tmpKSD01_DATA.DTKSHIN5_SZ)	+ "',";
    sBuf += " DTKSHIN6_SZ='"+ AnsiString(tmpKSD01_DATA.DTKSHIN6_SZ)	+ "',";
    sBuf += " LOT_LINK_SZ="	+ AnsiString(tmpKSD01_DATA.LOT_LINK_SZ)	+  ",";
    sBuf += " SOKUTEI_NUM=" + AnsiString(tmpKSD01_DATA.SOKUTEI_NUM)	+  ",";
    sBuf += " OUT_TITLE1="	+ AnsiString(tmpKSD01_DATA.OUT_TITLE1)	+  ",";
    sBuf += " OUT_TITLE2="	+ AnsiString(tmpKSD01_DATA.OUT_TITLE2)	+  ",";
    sBuf += " OUT_TITLE3="	+ AnsiString(tmpKSD01_DATA.OUT_TITLE3)	+  ",";
    sBuf += " OUT_TITLE4="	+ AnsiString(tmpKSD01_DATA.OUT_TITLE4)	+  ",";
    sBuf += " OUT_TITLE5="	+ AnsiString(tmpKSD01_DATA.OUT_TITLE5)	+  ",";
    sBuf += " OUT_TITLE6="	+ AnsiString(tmpKSD01_DATA.OUT_TITLE6)	+  ",";
    sBuf += " OUT_TITLE7="	+ AnsiString(tmpKSD01_DATA.OUT_TITLE7)	+  ",";
    sBuf += " OUT_TITLE8="	+ AnsiString(tmpKSD01_DATA.OUT_TITLE8)	+  ",";
    sBuf += " X_OUT="		+ AnsiString(tmpKSD01_DATA.X_OUT)		+  " ";
    sBuf += "where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN)	+  "'";	// ���Ӑ�i��
    sBuf += " and LOTNO='"	+ sLOTNO + "'";									// ���b�gNO

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }
    catch(Exception& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }

    return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�[�^���X�V�iKSD02,KSD03�j���܂��B
//
//  �@�\����
//    �u�e�P�P�F�ۑ��v���̃f�[�^�X�V�iKSD02,KSD03�j����
//    �w�胍�b�gNO���̏���
//
//  �p�����^����
//    AnsiString sLOTNO	�F���b�gNO
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm3::UpdData_Details_KSD02_03( AnsiString sLOTNO )
{
    int			i;
    int			iSOKU_SU;
    int			iSOKU_VAL_SU;
    int			iDISP_VAL_SU;
    AnsiString	sBuf;
    AnsiString	sBuf_DEL_UNQ;
    AnsiString	sBuf_DEL_BNKT_UNQ;


/* 2003/10/8 A.Tamura ���̃R�����g�𔲂������ƁA�����悤�ȏ��������Ă���̂ł����̓R�����g�ɂ��܂����B
    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf  = "select DTKSHIN from KSD02";
    sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN) + "'";	// ���Ӑ�i��
    sBuf += " and LOTNO='" + sLOTNO + "'";									// ���b�gNO

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True && Query1->Bof == True) ){

            //if( iUpd == 0 ){
            //	SBr1->Panels->Items[0]->Text = "���ɓo�^����Ă��܂��B�@�V�K�o�^�����͒��f����܂����B";
            //} else {
            //	SBr1->Panels->Items[0]->Text = "���ɓo�^����Ă��܂��B�@�C�������͒��f����܂����B";
            //}
            //SBr1->Update();
            //Beep();
            //return(False);

            // �폜��������NO��KSD02�ɂ���ꍇ�́A�폜���܂�
            if( sDEL_UNQ_NO->Count > 0 ) {

                sBuf_DEL_UNQ = "";
                for( i = 0; i < sDEL_UNQ_NO->Count; i++ ){
                    if( i > 0 )	sBuf_DEL_UNQ += ", ";
                	sBuf_DEL_UNQ += sDEL_UNQ_NO->Strings[i];
                }

                //--------------------------------------------------------------
                // ������і��׃f�[�^�iKSD02�j�̍폜

				// Initial Query
				Query2->Close();
				Query2->SQL->Clear();

				// �⍇�����쐬
				sBuf = "DELETE from KSD02";
				sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN)	+ "'"	;	// ���Ӑ�i��
				sBuf += " and LOTNO='" + sLOTNO + "'";										// ���b�gNO
				sBuf += " and UNQ_NO IN (" + sBuf_DEL_UNQ + ")";							// ����NO									// ���b�gNO

				Query2->SQL->Add(sBuf);

				// �₢�������̎��s
				try {
					Query2->ExecSQL();
				}
				catch(EDatabaseError& e) {
					MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
					return(False);
				}
				catch(Exception& e) {
					MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
					return(False);
				}

                //--------------------------------------------------------------
                // ������ї�O�f�[�^�iKSD03�j�̍폜

				// Initial Query
				Query2->Close();
				Query2->SQL->Clear();

				// �⍇�����쐬
				sBuf = "DELETE from KSD03";
				sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN)	+ "'"	;	// ���Ӑ�i��
				sBuf += " and LOTNO='" + sLOTNO + "'";										// ���b�gNO
				sBuf += " and UNQ_NO IN (" + sBuf_DEL_UNQ + ")";							// ����NO									// ���b�gNO

				Query2->SQL->Add(sBuf);

				// �₢�������̎��s
				try {
					Query2->ExecSQL();
				}
				catch(EDatabaseError& e) {
					MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
					return(False);
				}
				catch(Exception& e) {
					MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
					return(False);
				}

                //--------------------------------------------------------------
                // ������ѕ����f�[�^�iKSD11�j���L�邩�ǂ������f���܂�
                //     �Y���f�[�^���������ꍇ[BNKT_UNQ_NO]���L������
                //     �Ɠ����ɁAKSD11,KSD12���폜���܂��B
                //                                            2003/10/8 A.Tamura

				// Initial Query
				Query2->Close();
				Query2->SQL->Clear();

				// �⍇�����쐬
				sBuf  = "select BNKT_UNQ_NO from KSD11";
				sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN) + "'";	// ���Ӑ�i��
				sBuf += " and LOTNO='" + sLOTNO + "'";									// ���b�gNO
				sBuf += " and UNQ_NO IN (" + sBuf_DEL_UNQ + ")";							// ����NO									// ���b�gNO

				Query2->SQL->Add(sBuf);
				Query2->Open();
				Query2->Active = true;

				sBuf_DEL_BNKT_UNQ = "";

				while( !Query2->Eof ){
					if( sBuf_DEL_BNKT_UNQ != "" ) sBuf_DEL_BNKT_UNQ += ", ";
					sBuf_DEL_BNKT_UNQ += Query2->FieldValues["BNKT_UNQ_NO"];

					// �J�[�\�������ɃZ�b�g����
					Query2->Next();
				}

                // �Y���f�[�^���������ꍇ�AKSD11,KSD12���폜���܂��B
				if( sBuf_DEL_BNKT_UNQ != "" ){

                	//--------------------------------------------------------------
                	// ������ѕ����f�[�^�iKSD11�j�̍폜

					// Initial Query
					Query2->Close();
					Query2->SQL->Clear();

					// �⍇�����쐬
					sBuf = "DELETE from KSD11";
					sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN)	+ "'"	;	// ���Ӑ�i��
					sBuf += " and LOTNO='" + sLOTNO + "'";										// ���b�gNO
					sBuf += " and UNQ_NO IN (" + sBuf_DEL_UNQ + ")";							// ����NO									// ���b�gNO

					Query2->SQL->Add(sBuf);

					// �₢�������̎��s
					try {
						Query2->ExecSQL();
					}
					catch(EDatabaseError& e) {
						MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
						return(False);
					}
					catch(Exception& e) {
						MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
						return(False);
					}

	                //--------------------------------------------------------------
	                // ������ѕ�����O�f�[�^�iKSD12�j�̍폜

					// Initial Query
					Query2->Close();
					Query2->SQL->Clear();

					// �⍇�����쐬
					sBuf = "DELETE from KSD12";
					sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN)	+ "'"	;	// ���Ӑ�i��
					sBuf += " and LOTNO='" + sLOTNO + "'";										// ���b�gNO
					sBuf += " and BNKT_UNQ_NO IN (" + sBuf_DEL_BNKT_UNQ + ")";					// ����NO									// ���b�gNO

					Query2->SQL->Add(sBuf);

					// �₢�������̎��s
					try {
						Query2->ExecSQL();
					}
					catch(EDatabaseError& e) {
						MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
						return(False);
					}
					catch(Exception& e) {
						MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
						return(False);
					}
                }
			}
        }
    }
    catch(EDatabaseError& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }
    catch(Exception& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }
*/

    //--------------------------------------------------------------
   	// �ΏۊO�̖���NO�́A�폜���܂�
    sBuf_DEL_UNQ = "";
    for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
        if( SGr_SOKUT->Cells[15][i].ToIntDef(-1) >= 0 ){
            if( sBuf_DEL_UNQ != "" ) sBuf_DEL_UNQ += ", ";
            sBuf_DEL_UNQ += SGr_SOKUT->Cells[13][i];
    	}
	}
    if( sBuf_DEL_UNQ != "" ){

        //--------------------------------------------------------------
        // ������і��׃f�[�^�iKSD02�j�̍폜

		// Initial Query
		Query2->Close();
		Query2->SQL->Clear();

		// �⍇�����쐬
		sBuf = "DELETE from KSD02";
		sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN)	+ "'";	// ���Ӑ�i��
		sBuf += " and LOTNO='" + sLOTNO + "'";									// ���b�gNO
		sBuf += " and UNQ_NO NOT IN (" + sBuf_DEL_UNQ + ")";					// ����NO									// ���b�gNO

		Query2->SQL->Add(sBuf);

		// �₢�������̎��s
		try {
			Query2->ExecSQL();
		}
		catch(EDatabaseError& e) {
			MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
			return(False);
		}
		catch(Exception& e) {
			MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
			return(False);
		}

        //--------------------------------------------------------------
        // ������ї�O�f�[�^�iKSD03�j�̍폜

		// Initial Query
		Query2->Close();
		Query2->SQL->Clear();

		// �⍇�����쐬
		sBuf = "DELETE from KSD03";
		sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN)	+ "'";	// ���Ӑ�i��
		sBuf += " and LOTNO='" + sLOTNO + "'";									// ���b�gNO
		sBuf += " and UNQ_NO NOT IN (" + sBuf_DEL_UNQ + ")";					// ����NO									// ���b�gNO

		Query2->SQL->Add(sBuf);

		// �₢�������̎��s
		try {
			Query2->ExecSQL();
		}
		catch(EDatabaseError& e) {
			MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
			return(False);
		}
		catch(Exception& e) {
			MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
			return(False);
		}

        //--------------------------------------------------------------
        // ������ѕ����f�[�^�iKSD11�j���L�邩�ǂ������f���܂�
        //     �Y���f�[�^���������ꍇ[BNKT_UNQ_NO]���L������
        //     �Ɠ����ɁAKSD11,KSD12���폜���܂��B
        //                                            2003/10/8 A.Tamura

		// Initial Query
		Query2->Close();
		Query2->SQL->Clear();

		// �⍇�����쐬
		sBuf  = "select BNKT_UNQ_NO from KSD11";
		sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN) + "'";	// ���Ӑ�i��
		sBuf += " and LOTNO='" + sLOTNO + "'";									// ���b�gNO
		sBuf += " and UNQ_NO NOT IN (" + sBuf_DEL_UNQ + ")";					// ����NO									// ���b�gNO

		Query2->SQL->Add(sBuf);
		Query2->Open();
		Query2->Active = true;

		sBuf_DEL_BNKT_UNQ = "";

		while( !Query2->Eof ){
			if( sBuf_DEL_BNKT_UNQ != "" ) sBuf_DEL_BNKT_UNQ += ", ";
			sBuf_DEL_BNKT_UNQ += Query2->FieldValues["BNKT_UNQ_NO"];

			// �J�[�\�������ɃZ�b�g����
			Query2->Next();
		}

        // �Y���f�[�^���������ꍇ�AKSD11,KSD12���폜���܂��B
		if( sBuf_DEL_BNKT_UNQ != "" ){

        	//--------------------------------------------------------------
        	// ������ѕ����f�[�^�iKSD11�j�̍폜

			// Initial Query
			Query2->Close();
			Query2->SQL->Clear();

			// �⍇�����쐬
			sBuf = "DELETE from KSD11";
			sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN)	+ "'"	;	// ���Ӑ�i��
			sBuf += " and LOTNO='" + sLOTNO + "'";										// ���b�gNO
			sBuf += " and UNQ_NO NOT IN (" + sBuf_DEL_UNQ + ")";						// ����NO									// ���b�gNO

			Query2->SQL->Add(sBuf);

			// �₢�������̎��s
			try {
				Query2->ExecSQL();
			}
			catch(EDatabaseError& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}
			catch(Exception& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}

            //--------------------------------------------------------------
            // ������ѕ�����O�f�[�^�iKSD12�j�̍폜

			// Initial Query
			Query2->Close();
			Query2->SQL->Clear();

			// �⍇�����쐬
			sBuf = "DELETE from KSD12";
			sBuf += " where DTKSHIN='" + AnsiString(tmpKSD01_DATA.DTKSHIN)	+ "'"	;	// ���Ӑ�i��
			sBuf += " and LOTNO='" + sLOTNO + "'";										// ���b�gNO
			sBuf += " and BNKT_UNQ_NO IN (" + sBuf_DEL_BNKT_UNQ + ")";					// ����NO									// ���b�gNO

			Query2->SQL->Add(sBuf);

			// �₢�������̎��s
			try {
				Query2->ExecSQL();
			}
			catch(EDatabaseError& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}
			catch(Exception& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}
        }
    }


   	// StringGrid���̃f�[�^��S�ēo�^���܂�
    for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
        if( SGr_SOKUT->Cells[15][i].ToIntDef(-1) >= 0 ){

            //----------------------------------------------------------
        	// StringGrid����KSD02�\���̂ɒl���R�s�[���܂�
			strcpy( tmpKSD02_DATA.DTKSHIN		,tmpKSD01_DATA.DTKSHIN );	// ��\���Ӑ�i��
            strcpy( tmpKSD02_DATA.LOTNO			,sLOTNO.c_str()	);			// ���b�gNO
			sBuf = SGr_SOKUT->Cells[13][i];
			strcpy( tmpKSD02_DATA.UNQ_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[14][i];
			strcpy( tmpKSD02_DATA.ORDER_NO		,sBuf.c_str() );	// �\����
			sBuf = SGr_SOKUT->Cells[15][i];
			strcpy( tmpKSD02_DATA.SKB_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[1][i];
			strcpy( tmpKSD02_DATA.HINBAN_SK		,sBuf.c_str() );	// �i��
			sBuf = SGr_SOKUT->Cells[12][i];
			strcpy( tmpKSD02_DATA.KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[2][i];
			strcpy( tmpKSD02_DATA.KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
			sBuf = SGr_SOKUT->Cells[4][i];
			strcpy( tmpKSD02_DATA.KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
			sBuf = SGr_SOKUT->Cells[3][i].Trim();
			strcpy( tmpKSD02_DATA.KOMK_SUB		,sBuf.c_str() );	// ���荀�ڃT�u���́i���{��j
			sBuf = SGr_SOKUT->Cells[16][i].Trim();
			strcpy( tmpKSD02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// ���荀�ڃT�u���́i�p��j
			sBuf = SGr_SOKUT->Cells[17][i];
			strcpy( tmpKSD02_DATA.KIKI_NO		,sBuf.c_str() );	// ����@��NO
			sBuf = SGr_SOKUT->Cells[9][i];
			strcpy( tmpKSD02_DATA.KIKI_NM		,sBuf.c_str() );	// ����@�햼��
			sBuf = SGr_SOKUT->Cells[5][i];
			strcpy( tmpKSD02_DATA.TANI			,sBuf.c_str() );	// �P��
			sBuf = SGr_SOKUT->Cells[18][i];
			strcpy( tmpKSD02_DATA.KIKA_TYPE		,sBuf.c_str() );	// �K�i�^�C�v
			sBuf = SGr_SOKUT->Cells[19][i];
			strcpy( tmpKSD02_DATA.KIKA_KIND		,sBuf.c_str() );	// �K�i���
			sBuf = SGr_SOKUT->Cells[20][i];
			strcpy( tmpKSD02_DATA.KIKA_DECI		,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = SGr_SOKUT->Cells[21][i];
			strcpy( tmpKSD02_DATA.KIKA_NUM1		,sBuf.c_str() );	// �K�i�l�P
			sBuf = SGr_SOKUT->Cells[22][i];
			strcpy( tmpKSD02_DATA.KIKA_NUM2		,sBuf.c_str() );	// �K�i�l�Q
			sBuf = SGr_SOKUT->Cells[23][i];
			strcpy( tmpKSD02_DATA.KIKA_NUM3		,sBuf.c_str() );	// �K�i�l�R
			sBuf = SGr_SOKUT->Cells[24][i];
			strcpy( tmpKSD02_DATA.KIKA_STR		,sBuf.c_str() );	// �K�i�l����
			sBuf = SGr_SOKUT->Cells[25][i];
			strcpy( tmpKSD02_DATA.KIKA_SUB1		,sBuf.c_str() );	// �K�i�l�T�u�P
			sBuf = SGr_SOKUT->Cells[26][i];
			strcpy( tmpKSD02_DATA.KIKA_SUB2		,sBuf.c_str() );	// �K�i�l�T�u�Q
			sBuf = SGr_SOKUT->Cells[27][i];
			strcpy( tmpKSD02_DATA.KIKA_SUB3		,sBuf.c_str() );	// �K�i�l�T�u�R
			sBuf = SGr_SOKUT->Cells[7][i];
			strcpy( tmpKSD02_DATA.SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = SGr_SOKUT->Cells[10][i];
			strcpy( tmpKSD02_DATA.SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = SGr_SOKUT->Cells[11][i];
			strcpy( tmpKSD02_DATA.TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = SGr_SOKUT->Cells[28][i];
			strcpy( tmpKSD02_DATA.KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = SGr_SOKUT->Cells[8][i];
			strcpy( tmpKSD02_DATA.VALUE_TYPE	,sBuf.c_str() );	// ����l�\��
			sBuf = SGr_SOKUT->Cells[29][i];
			strcpy( tmpKSD02_DATA.VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����


            //----------------------------------------------------------
            // �����̖��׃f�[�^�����邩�ǂ����̊m�F

			// Initial Query
			Query1->Close();
			Query1->SQL->Clear();

			// �⍇�����쐬
			sBuf  = "select * from KSD02";
			sBuf += " where DTKSHIN='" + AnsiString(tmpKSD02_DATA.DTKSHIN) + "'";	// ���Ӑ�i��
			sBuf += " and LOTNO='" + AnsiString(tmpKSD02_DATA.LOTNO) + "'";			// ���b�gNO
			sBuf += " and UNQ_NO=" + AnsiString(tmpKSD02_DATA.UNQ_NO);				// ����NO									// ���b�gNO

			Query1->SQL->Add(sBuf);

			// �₢�������̎��s
			try {
				Query1->Open();
				Query1->Active = true;

				if( Query1->Eof == True && Query1->Bof == True ){
                    //----------------------------------------------------------
                	// ���R�[�h��������Ȃ����i����l�Ȃ��ŋ�f�[�^���쐬���܂��j
                    sBuf = " ";
					strcpy( tmpKSD02_DATA.SOKU_VAL01	,sBuf.c_str() );	// ����l1
					strcpy( tmpKSD02_DATA.SOKU_VAL02	,sBuf.c_str() );	// ����l2
					strcpy( tmpKSD02_DATA.SOKU_VAL03	,sBuf.c_str() );	// ����l3
					strcpy( tmpKSD02_DATA.SOKU_VAL04	,sBuf.c_str() );	// ����l4
					strcpy( tmpKSD02_DATA.SOKU_VAL05	,sBuf.c_str() );	// ����l5
					strcpy( tmpKSD02_DATA.SOKU_VAL06	,sBuf.c_str() );	// ����l6
					strcpy( tmpKSD02_DATA.SOKU_VAL07	,sBuf.c_str() );	// ����l7
					strcpy( tmpKSD02_DATA.SOKU_VAL08	,sBuf.c_str() );	// ����l8
					strcpy( tmpKSD02_DATA.SOKU_VAL09	,sBuf.c_str() );	// ����l9
					strcpy( tmpKSD02_DATA.SOKU_VAL10	,sBuf.c_str() );	// ����l10
                    sBuf = "0";
					strcpy( tmpKSD02_DATA.SOKU_VAL_SU	,sBuf.c_str() );	// ������т���
					strcpy( tmpKSD02_DATA.SOKU_VAL_AVE	,sBuf.c_str() );	// ���蕽�ϒl
					strcpy( tmpKSD02_DATA.SOKU_VAL_MAX	,sBuf.c_str() );	// ����ő�l
					strcpy( tmpKSD02_DATA.SOKU_VAL_MIN	,sBuf.c_str() );	// ����ŏ��l
					strcpy( tmpKSD02_DATA.SOKU_OK		,sBuf.c_str() );	// ����l����
                    sBuf = " ";
					strcpy( tmpKSD02_DATA.DISP_VAL01	,sBuf.c_str() );	// ����l1 ����p
					strcpy( tmpKSD02_DATA.DISP_VAL02	,sBuf.c_str() );	// ����l2 ����p
					strcpy( tmpKSD02_DATA.DISP_VAL03	,sBuf.c_str() );	// ����l3 ����p
					strcpy( tmpKSD02_DATA.DISP_VAL04	,sBuf.c_str() );	// ����l4 ����p
					strcpy( tmpKSD02_DATA.DISP_VAL05	,sBuf.c_str() );	// ����l5 ����p
					strcpy( tmpKSD02_DATA.DISP_VAL06	,sBuf.c_str() );	// ����l6 ����p
					strcpy( tmpKSD02_DATA.DISP_VAL07	,sBuf.c_str() );	// ����l7 ����p
					strcpy( tmpKSD02_DATA.DISP_VAL08	,sBuf.c_str() );	// ����l8 ����p
					strcpy( tmpKSD02_DATA.DISP_VAL09	,sBuf.c_str() );	// ����l9 ����p
					strcpy( tmpKSD02_DATA.DISP_VAL10	,sBuf.c_str() );	// ����l10 ����p
                    sBuf = "0";
					strcpy( tmpKSD02_DATA.DISP_VAL_SU	,sBuf.c_str() );	// ������т��� ����p
					strcpy( tmpKSD02_DATA.DISP_VAL_AVE	,sBuf.c_str() );	// ���蕽�ϒl ����p
					strcpy( tmpKSD02_DATA.DISP_VAL_MAX	,sBuf.c_str() );	// ����ő�l ����p
					strcpy( tmpKSD02_DATA.DISP_VAL_MIN	,sBuf.c_str() );	// ����ŏ��l ����p
					strcpy( tmpKSD02_DATA.DISP_OK		,sBuf.c_str() );	// ����l���� ����p
                    sBuf = " ";
					strcpy( tmpKSD02_DATA.SKTYMD		,sBuf.c_str() );	// �����
					strcpy( tmpKSD02_DATA.ADDYMD		,sBuf.c_str() );	// �o�^��
					strcpy( tmpKSD02_DATA.ADDTIM		,sBuf.c_str() );	// �o�^����
					strcpy( tmpKSD02_DATA.UPDYMD		,sBuf.c_str() );	// �ύX��
					strcpy( tmpKSD02_DATA.UPDTIM		,sBuf.c_str() );	// �ύX����
                    sBuf = "0";
					strcpy( tmpKSD02_DATA.UPDCHR		,sBuf.c_str() );	// �X�V�ҁi�R�[�h�j
					strcpy( tmpKSD02_DATA.UPDCNT		,sBuf.c_str() );	// �X�V��

                } else {
                    //----------------------------------------------------------
                	// ���R�[�h�������������i���̑���l���擾���܂��j

					if( VarIsNull(Query1->FieldValues["SOKU_VAL01"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["SOKU_VAL01"];
					strcpy( tmpKSD02_DATA.SOKU_VAL01	,sBuf.c_str() );	// ����l1
					if( VarIsNull(Query1->FieldValues["SOKU_VAL02"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["SOKU_VAL02"];
					strcpy( tmpKSD02_DATA.SOKU_VAL02	,sBuf.c_str() );	// ����l2
					if( VarIsNull(Query1->FieldValues["SOKU_VAL03"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["SOKU_VAL03"];
					strcpy( tmpKSD02_DATA.SOKU_VAL03	,sBuf.c_str() );	// ����l3
					if( VarIsNull(Query1->FieldValues["SOKU_VAL04"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["SOKU_VAL04"];
					strcpy( tmpKSD02_DATA.SOKU_VAL04	,sBuf.c_str() );	// ����l4
					if( VarIsNull(Query1->FieldValues["SOKU_VAL05"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["SOKU_VAL05"];
					strcpy( tmpKSD02_DATA.SOKU_VAL05	,sBuf.c_str() );	// ����l5
					if( VarIsNull(Query1->FieldValues["SOKU_VAL06"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["SOKU_VAL06"];
					strcpy( tmpKSD02_DATA.SOKU_VAL06	,sBuf.c_str() );	// ����l6
					if( VarIsNull(Query1->FieldValues["SOKU_VAL07"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["SOKU_VAL07"];
					strcpy( tmpKSD02_DATA.SOKU_VAL07	,sBuf.c_str() );	// ����l7
					if( VarIsNull(Query1->FieldValues["SOKU_VAL08"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["SOKU_VAL08"];
					strcpy( tmpKSD02_DATA.SOKU_VAL08	,sBuf.c_str() );	// ����l8
					if( VarIsNull(Query1->FieldValues["SOKU_VAL09"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["SOKU_VAL09"];
					strcpy( tmpKSD02_DATA.SOKU_VAL09	,sBuf.c_str() );	// ����l9
					if( VarIsNull(Query1->FieldValues["SOKU_VAL10"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["SOKU_VAL10"];
					strcpy( tmpKSD02_DATA.SOKU_VAL10	,sBuf.c_str() );	// ����l10
                    sBuf = Query1->FieldValues["SOKU_VAL_SU"];
                    strcpy( tmpKSD02_DATA.SOKU_VAL_SU	,sBuf.c_str() );	// ������т���
                    sBuf = Query1->FieldValues["SOKU_VAL_AVE"];
					strcpy( tmpKSD02_DATA.SOKU_VAL_AVE	,sBuf.c_str() );	// ���蕽�ϒl
                    sBuf = Query1->FieldValues["SOKU_VAL_MAX"];
					strcpy( tmpKSD02_DATA.SOKU_VAL_MAX	,sBuf.c_str() );	// ����ő�l
                    sBuf = Query1->FieldValues["SOKU_VAL_MIN"];
					strcpy( tmpKSD02_DATA.SOKU_VAL_MIN	,sBuf.c_str() );	// ����ŏ��l
                    sBuf = Query1->FieldValues["SOKU_OK"];
					strcpy( tmpKSD02_DATA.SOKU_OK		,sBuf.c_str() );	// ����l����
					if( VarIsNull(Query1->FieldValues["DISP_VAL01"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["DISP_VAL01"];
					strcpy( tmpKSD02_DATA.DISP_VAL01	,sBuf.c_str() );	// ����l1 ����p
					if( VarIsNull(Query1->FieldValues["DISP_VAL02"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["DISP_VAL02"];
					strcpy( tmpKSD02_DATA.DISP_VAL02	,sBuf.c_str() );	// ����l2 ����p
					if( VarIsNull(Query1->FieldValues["DISP_VAL03"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["DISP_VAL03"];
					strcpy( tmpKSD02_DATA.DISP_VAL03	,sBuf.c_str() );	// ����l3 ����p
					if( VarIsNull(Query1->FieldValues["DISP_VAL04"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["DISP_VAL04"];
					strcpy( tmpKSD02_DATA.DISP_VAL04	,sBuf.c_str() );	// ����l4 ����p
					if( VarIsNull(Query1->FieldValues["DISP_VAL05"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["DISP_VAL05"];
					strcpy( tmpKSD02_DATA.DISP_VAL05	,sBuf.c_str() );	// ����l5 ����p
					if( VarIsNull(Query1->FieldValues["DISP_VAL06"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["DISP_VAL06"];
					strcpy( tmpKSD02_DATA.DISP_VAL06	,sBuf.c_str() );	// ����l6 ����p
					if( VarIsNull(Query1->FieldValues["DISP_VAL07"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["DISP_VAL07"];
					strcpy( tmpKSD02_DATA.DISP_VAL07	,sBuf.c_str() );	// ����l7 ����p
					if( VarIsNull(Query1->FieldValues["DISP_VAL08"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["DISP_VAL08"];
					strcpy( tmpKSD02_DATA.DISP_VAL08	,sBuf.c_str() );	// ����l8 ����p
					if( VarIsNull(Query1->FieldValues["DISP_VAL09"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["DISP_VAL09"];
					strcpy( tmpKSD02_DATA.DISP_VAL09	,sBuf.c_str() );	// ����l9 ����p
					if( VarIsNull(Query1->FieldValues["DISP_VAL10"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["DISP_VAL10"];
					strcpy( tmpKSD02_DATA.DISP_VAL10	,sBuf.c_str() );	// ����l10 ����p
                    sBuf = Query1->FieldValues["DISP_VAL_SU"];
					strcpy( tmpKSD02_DATA.DISP_VAL_SU	,sBuf.c_str() );	// ������т��� ����p
                    sBuf = Query1->FieldValues["DISP_VAL_AVE"];
					strcpy( tmpKSD02_DATA.DISP_VAL_AVE	,sBuf.c_str() );	// ���蕽�ϒl ����p
                    sBuf = Query1->FieldValues["DISP_VAL_MAX"];
					strcpy( tmpKSD02_DATA.DISP_VAL_MAX	,sBuf.c_str() );	// ����ő�l ����p
                    sBuf = Query1->FieldValues["DISP_VAL_MIN"];
					strcpy( tmpKSD02_DATA.DISP_VAL_MIN	,sBuf.c_str() );	// ����ŏ��l ����p
                    sBuf = Query1->FieldValues["DISP_OK"];
					strcpy( tmpKSD02_DATA.DISP_OK		,sBuf.c_str() );	// ����l���� ����p
					if( VarIsNull(Query1->FieldValues["SKTYMD"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["SKTYMD"];
					strcpy( tmpKSD02_DATA.SKTYMD		,sBuf.c_str() );	// �����
					if( VarIsNull(Query1->FieldValues["ADDYMD"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["ADDYMD"];
					strcpy( tmpKSD02_DATA.ADDYMD		,sBuf.c_str() );	// �o�^��
					if( VarIsNull(Query1->FieldValues["ADDTIM"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["ADDTIM"];
					strcpy( tmpKSD02_DATA.ADDTIM		,sBuf.c_str() );	// �o�^����
					if( VarIsNull(Query1->FieldValues["UPDYMD"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["UPDYMD"];
					strcpy( tmpKSD02_DATA.UPDYMD		,sBuf.c_str() );	// �ύX��
					if( VarIsNull(Query1->FieldValues["UPDTIM"]) )	sBuf = " ";
					else												sBuf = Query1->FieldValues["UPDTIM"];
					strcpy( tmpKSD02_DATA.UPDTIM		,sBuf.c_str() );	// �ύX����
                    sBuf = Query1->FieldValues["UPDCHR"];
					strcpy( tmpKSD02_DATA.UPDCHR		,sBuf.c_str() );	// �X�V�ҁi�R�[�h�j
                    sBuf = Query1->FieldValues["UPDCNT"];
					strcpy( tmpKSD02_DATA.UPDCNT		,sBuf.c_str() );	// �X�V��


                    //----------------------------------------------------------
                    // ������̐�������ۂ��܂��B����O��鑪��ς݃f�[�^�̓N���A���܂�
                    // �i�ő�l�A�ŏ��l�A���ϒl�A�K�i����́A�����ʂōs�Ȃ��܂��j

                    iSOKU_SU = AnsiString(tmpKSD02_DATA.SOKU_SU).ToIntDef(0);
                    iSOKU_VAL_SU = AnsiString(tmpKSD02_DATA.SOKU_VAL_SU).ToIntDef(0);
                    iDISP_VAL_SU = AnsiString(tmpKSD02_DATA.DISP_VAL_SU).ToIntDef(0);
                    if( iSOKU_VAL_SU > iSOKU_SU ){
                    	iSOKU_VAL_SU = iSOKU_SU;
                    	sBuf = iSOKU_VAL_SU;
                    	strcpy( tmpKSD02_DATA.SOKU_VAL_SU	,sBuf.c_str() );	// ������т���
                    }
                    if( iDISP_VAL_SU > iSOKU_SU ){
                    	iDISP_VAL_SU = iSOKU_SU;
                    	sBuf = iDISP_VAL_SU;
                    	strcpy( tmpKSD02_DATA.DISP_VAL_SU	,sBuf.c_str() );	// ������т��� ����p
                    }
                    // ������ѐ�����O�ꂽ����l�́A�N���A�[���܂�
                    sBuf = " ";
                    if( iSOKU_VAL_SU <  1 )	strcpy( tmpKSD02_DATA.SOKU_VAL01, sBuf.c_str() );	// ����l1
                    if( iSOKU_VAL_SU <  2 )	strcpy( tmpKSD02_DATA.SOKU_VAL02, sBuf.c_str() );	// ����l2
                    if( iSOKU_VAL_SU <  3 )	strcpy( tmpKSD02_DATA.SOKU_VAL03, sBuf.c_str() );	// ����l3
                    if( iSOKU_VAL_SU <  4 )	strcpy( tmpKSD02_DATA.SOKU_VAL04, sBuf.c_str() );	// ����l4
                    if( iSOKU_VAL_SU <  5 )	strcpy( tmpKSD02_DATA.SOKU_VAL05, sBuf.c_str() );	// ����l5
                    if( iSOKU_VAL_SU <  6 )	strcpy( tmpKSD02_DATA.SOKU_VAL06, sBuf.c_str() );	// ����l6
                    if( iSOKU_VAL_SU <  7 )	strcpy( tmpKSD02_DATA.SOKU_VAL07, sBuf.c_str() );	// ����l7
                    if( iSOKU_VAL_SU <  8 )	strcpy( tmpKSD02_DATA.SOKU_VAL08, sBuf.c_str() );	// ����l8
                    if( iSOKU_VAL_SU <  9 )	strcpy( tmpKSD02_DATA.SOKU_VAL09, sBuf.c_str() );	// ����l9
                    if( iSOKU_VAL_SU < 10 )	strcpy( tmpKSD02_DATA.SOKU_VAL10, sBuf.c_str() );	// ����l10
                    if( iDISP_VAL_SU <  1 )	strcpy( tmpKSD02_DATA.DISP_VAL01, sBuf.c_str() );	// ����p ����l1
                    if( iDISP_VAL_SU <  2 )	strcpy( tmpKSD02_DATA.DISP_VAL02, sBuf.c_str() );	// ����p ����l2
                    if( iDISP_VAL_SU <  3 )	strcpy( tmpKSD02_DATA.DISP_VAL03, sBuf.c_str() );	// ����p ����l3
                    if( iDISP_VAL_SU <  4 )	strcpy( tmpKSD02_DATA.DISP_VAL04, sBuf.c_str() );	// ����p ����l4
                    if( iDISP_VAL_SU <  5 )	strcpy( tmpKSD02_DATA.DISP_VAL05, sBuf.c_str() );	// ����p ����l5
                    if( iDISP_VAL_SU <  6 )	strcpy( tmpKSD02_DATA.DISP_VAL06, sBuf.c_str() );	// ����p ����l6
                    if( iDISP_VAL_SU <  7 )	strcpy( tmpKSD02_DATA.DISP_VAL07, sBuf.c_str() );	// ����p ����l7
                    if( iDISP_VAL_SU <  8 )	strcpy( tmpKSD02_DATA.DISP_VAL08, sBuf.c_str() );	// ����p ����l8
                    if( iDISP_VAL_SU <  9 )	strcpy( tmpKSD02_DATA.DISP_VAL09, sBuf.c_str() );	// ����p ����l9
                    if( iDISP_VAL_SU < 10 )	strcpy( tmpKSD02_DATA.DISP_VAL10, sBuf.c_str() );	// ����p ����l10


                    //----------------------------------------------------------
                    // �ύX�O�̑�����і��׃f�[�^(KSD02)�͍폜���܂�

					// Initial Query
					Query2->Close();
					Query2->SQL->Clear();

					// �⍇�����쐬
					sBuf = "DELETE from KSD02";
					sBuf += " where DTKSHIN='" + AnsiString(tmpKSD02_DATA.DTKSHIN) + "'";	// ���Ӑ�i��
					sBuf += " and LOTNO='" + AnsiString(tmpKSD02_DATA.LOTNO) + "'";			// ���b�gNO
					sBuf += " and UNQ_NO=" + AnsiString(tmpKSD02_DATA.UNQ_NO);				// ����NO									// ���b�gNO

					Query2->SQL->Add(sBuf);

					// �₢�������̎��s
					try {
						Query2->ExecSQL();
					}
					catch(EDatabaseError& e) {
						MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
						return(False);
					}
					catch(Exception& e) {
						MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
						return(False);
					}


                    //----------------------------------------------------------
                    // �ύX�O�̑�����ї�O�f�[�^(KSD03)�͍폜���܂�
                    // �y�w��n�����[����NO(SOKU_SU)]���傫�����R�[�h�����z

					// Initial Query
					Query2->Close();
					Query2->SQL->Clear();

					// �⍇�����쐬
					sBuf = "DELETE from KSD03";
					sBuf += " where DTKSHIN='" + AnsiString(tmpKSD02_DATA.DTKSHIN) + "'";	// ���Ӑ�i��
					sBuf += " and LOTNO='" + AnsiString(tmpKSD02_DATA.LOTNO) + "'";			// ���b�gNO
					sBuf += " and UNQ_NO=" + AnsiString(tmpKSD02_DATA.UNQ_NO);				// ����NO									// ���b�gNO
                    sBuf += " and SOKU_NO>" + AnsiString(tmpKSD02_DATA.SOKU_SU);			// ����NO									// ���b�gNO

					Query2->SQL->Add(sBuf);

					// �₢�������̎��s
					try {
						Query2->ExecSQL();
					}
					catch(EDatabaseError& e) {
						MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
						return(False);
					}
					catch(Exception& e) {
						MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
						return(False);
					}
                }
            }
			catch(EDatabaseError& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}
			catch(Exception& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}


            //----------------------------------------------------------
            // ������і��׃f�[�^(KSD02)�Ƀf�[�^�o�^

			// Initial Query
			Query1->Close();
			Query1->SQL->Clear();

			// �⍇�����s
			sBuf  = "insert into KSD02(";
			sBuf += " DTKSHIN, LOTNO, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK,";
			sBuf += " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG,";
			sBuf += " KIKI_NO, KIKI_NM, TANI, KIKA_TYPE, KIKA_KIND,";
			sBuf += " KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3,";
			sBuf += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3,";
			sBuf += " SOKU_SU, SOKU_FLG, TOKU_FLG, KIKA_PRT,";
			sBuf += " VALUE_TYPE, VALUE_DECI,";
			sBuf += " SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05,";
			sBuf += " SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,";
			sBuf += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK,";
			sBuf += " DISP_VAL01, DISP_VAL02, DISP_VAL03, DISP_VAL04, DISP_VAL05,";
			sBuf += " DISP_VAL06, DISP_VAL07, DISP_VAL08, DISP_VAL09, DISP_VAL10,";
			sBuf += " DISP_VAL_SU, DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, DISP_OK,";
			sBuf += " SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT )";

			sBuf += " VALUES( '";
			sBuf += AnsiString(tmpKSD02_DATA.DTKSHIN)		+ "','" ;	// ��\���Ӑ�i��
			sBuf += AnsiString(tmpKSD02_DATA.LOTNO)			+ "'," ;	// ���b�gNO
			sBuf += AnsiString(tmpKSD02_DATA.UNQ_NO)		+  "," ;	// ����NO
			sBuf += AnsiString(tmpKSD02_DATA.ORDER_NO)		+  "," ;	// �\����
			sBuf += AnsiString(tmpKSD02_DATA.SKB_NO)		+  ",'";	// ����NO
			sBuf += AnsiString(tmpKSD02_DATA.HINBAN_SK)		+ "'," ;	// �i��
			sBuf += AnsiString(tmpKSD02_DATA.KOMK_NO)		+  ",'";	// ����NO
			sBuf += AnsiString(tmpKSD02_DATA.KOMK_NM)		+ "','";	// ���荀�ږ��́i���{��j
			sBuf += AnsiString(tmpKSD02_DATA.KOMK_ENG)		+ "','";	// ���荀�ږ��́i�p��j
			sBuf += AnsiString(tmpKSD02_DATA.KOMK_SUB)		+ "','";	// ���荀�ڃT�u���́i���{��j
			sBuf += AnsiString(tmpKSD02_DATA.KOMK_SUB_ENG)	+ "'," ;	// ���荀�ڃT�u���́i�p��j
			sBuf += AnsiString(tmpKSD02_DATA.KIKI_NO)		+  ",'";	// ����@��NO
			sBuf += AnsiString(tmpKSD02_DATA.KIKI_NM)		+ "','";	// ����@�햼��
			sBuf += AnsiString(tmpKSD02_DATA.TANI)			+ "'," ;	// �P��
			sBuf += AnsiString(tmpKSD02_DATA.KIKA_TYPE)		+  "," ;	// �K�i�^�C�v
			sBuf += AnsiString(tmpKSD02_DATA.KIKA_KIND)		+  "," ;	// �K�i���
			sBuf += AnsiString(tmpKSD02_DATA.KIKA_DECI)		+  "," ;	// �K�i�����_�ȉ�����
			sBuf += AnsiString(tmpKSD02_DATA.KIKA_NUM1)		+  "," ;	// �K�i�l�P
			sBuf += AnsiString(tmpKSD02_DATA.KIKA_NUM2)		+  "," ;	// �K�i�l�Q
			sBuf += AnsiString(tmpKSD02_DATA.KIKA_NUM3)		+  ",'";	// �K�i�l�R
			sBuf += AnsiString(tmpKSD02_DATA.KIKA_STR)		+ "','";	// �K�i�l����
			sBuf += AnsiString(tmpKSD02_DATA.KIKA_SUB1)		+ "','";	// �K�i�l�T�u�P
			sBuf += AnsiString(tmpKSD02_DATA.KIKA_SUB2)		+ "','";	// �K�i�l�T�u�Q
			sBuf += AnsiString(tmpKSD02_DATA.KIKA_SUB3)		+ "'," ;	// �K�i�l�T�u�R
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_SU)		+  "," ;	// ����w��n��
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_FLG)		+  "," ;	// ���荀�ڂ̗L��
			sBuf += AnsiString(tmpKSD02_DATA.TOKU_FLG)		+  "," ;	// ���ʍ��ڂ̗L��
			sBuf += AnsiString(tmpKSD02_DATA.KIKA_PRT)		+  "," ;	// ��������l�̈��
			sBuf += AnsiString(tmpKSD02_DATA.VALUE_TYPE)	+  "," ;	// ����l�\��
			sBuf += AnsiString(tmpKSD02_DATA.VALUE_DECI)	+  ",'";	// ����l�����_�ȉ�����
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL01)	+ "','";	// ����l1
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL02)	+ "','";	// ����l2
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL03)	+ "','";	// ����l3
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL04)	+ "','";	// ����l4
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL05)	+ "','";	// ����l5
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL06)	+ "','";	// ����l6
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL07)	+ "','";	// ����l7
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL08)	+ "','";	// ����l8
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL09)	+ "','";	// ����l9
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL10)	+ "'," ;	// ����l10
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL_SU)	+  "," ;	// ������т���
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL_AVE)	+  "," ;	// ���蕽�ϒl
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL_MAX)	+  "," ;	// ����ő�l
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_VAL_MIN)	+  "," ;	// ����ŏ��l
			sBuf += AnsiString(tmpKSD02_DATA.SOKU_OK)		+  ",'";	// ����l����
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL01)	+ "','";	// ����l1 ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL02)	+ "','";	// ����l2 ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL03)	+ "','";	// ����l3 ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL04)	+ "','";	// ����l4 ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL05)	+ "','";	// ����l5 ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL06)	+ "','";	// ����l6 ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL07)	+ "','";	// ����l7 ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL08)	+ "','";	// ����l8 ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL09)	+ "','";	// ����l9 ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL10)	+ "'," ;	// ����l10 ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL_SU)	+  "," ;	// ������т��� ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL_AVE)	+  "," ;	// ���蕽�ϒl ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL_MAX)	+  "," ;	// ����ő�l ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_VAL_MIN)	+  "," ;	// ����ŏ��l ����p
			sBuf += AnsiString(tmpKSD02_DATA.DISP_OK)		+  ",'";	// ����l���� ����p
			sBuf += AnsiString(tmpKSD02_DATA.SKTYMD)		+ "','";	// �����
			sBuf += AnsiString(tmpKSD02_DATA.ADDYMD)		+ "','";	// �o�^��
			sBuf += AnsiString(tmpKSD02_DATA.ADDTIM)		+ "','";	// �o�^����
			sBuf += AnsiString(tmpKSD02_DATA.UPDYMD)		+ "','";	// �ύX��
			sBuf += AnsiString(tmpKSD02_DATA.UPDTIM)		+ "'," ;	// �ύX����
			sBuf += AnsiString(tmpKSD02_DATA.UPDCHR)		+  "," ;	// �X�V�ҁi�R�[�h�j
			sBuf += AnsiString(tmpKSD02_DATA.UPDCNT)		+  ")" ;	// �X�V��

			Query1->SQL->Add(sBuf);

			// �₢�������̎��s
			try {
				Query1->ExecSQL();
			}
			catch(EDatabaseError& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}
			catch(Exception& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}

            //----------------------------------------------------------
            // ������ѕ����f�[�^(KSD11)�̃f�[�^���X�V���܂�
            //                                        2003/10/8 A.Tamura

			// Initial Query
			Query1->Close();
			Query1->SQL->Clear();

			// �⍇�����s
			sBuf  = "UPDATE KSD11 SET";
			sBuf += " KOMK_NO="			+ AnsiString(tmpKSD02_DATA.KOMK_NO)			+  ",";	// ����NO
			sBuf += " KOMK_NM='"		+ AnsiString(tmpKSD02_DATA.KOMK_NM)			+ "',";	// ���荀�ږ��́i���{��j
			sBuf += " KOMK_ENG='"		+ AnsiString(tmpKSD02_DATA.KOMK_ENG)		+ "',";	// ���荀�ږ��́i�p��j
			sBuf += " KOMK_SUB='"		+ AnsiString(tmpKSD02_DATA.KOMK_SUB)		+ "',";	// ���荀�ڃT�u���́i���{��j
			sBuf += " KOMK_SUB_ENG='"	+ AnsiString(tmpKSD02_DATA.KOMK_SUB_ENG)	+ "',";	// ���荀�ڃT�u���́i�p��j
			sBuf += " KIKI_NO="			+ AnsiString(tmpKSD02_DATA.KIKI_NO)			+  ",";	// ����@��NO
			sBuf += " KIKI_NM='"		+ AnsiString(tmpKSD02_DATA.KIKI_NM)			+ "',";	// ����@�햼��
			sBuf += " TANI='"			+ AnsiString(tmpKSD02_DATA.TANI)			+ "',";	// �P��
			sBuf += " KIKA_TYPE="		+ AnsiString(tmpKSD02_DATA.KIKA_TYPE)		+  ",";	// �K�i�^�C�v
			sBuf += " KIKA_KIND="		+ AnsiString(tmpKSD02_DATA.KIKA_KIND)		+  ",";	// �K�i���
			sBuf += " KIKA_DECI="		+ AnsiString(tmpKSD02_DATA.KIKA_DECI)		+  ",";	// �K�i�����_�ȉ�����
			sBuf += " KIKA_NUM1="		+ AnsiString(tmpKSD02_DATA.KIKA_NUM1)		+  ",";	// �K�i�l�P
			sBuf += " KIKA_NUM2="		+ AnsiString(tmpKSD02_DATA.KIKA_NUM2)		+  ",";	// �K�i�l�Q
			sBuf += " KIKA_NUM3="		+ AnsiString(tmpKSD02_DATA.KIKA_NUM3)		+  ",";	// �K�i�l�R
			sBuf += " KIKA_STR='"		+ AnsiString(tmpKSD02_DATA.KIKA_STR)		+ "',";	// �K�i�l����
			sBuf += " KIKA_SUB1='"		+ AnsiString(tmpKSD02_DATA.KIKA_SUB1)		+ "',";	// �K�i�l�T�u�P
			sBuf += " KIKA_SUB2='"		+ AnsiString(tmpKSD02_DATA.KIKA_SUB2)		+ "',";	// �K�i�l�T�u�Q
			sBuf += " KIKA_SUB3='"		+ AnsiString(tmpKSD02_DATA.KIKA_SUB3)		+ "',";	// �K�i�l�T�u�R

            // ����w�������͍X�V���܂���B�i�s�No43�̑Ή��j
            // 2004/08/26 A.Tamura
			// sBuf += " SOKU_SU="			+ AnsiString(tmpKSD02_DATA.SOKU_SU)			+  ",";	// ����w��n��
			sBuf += " SOKU_FLG="		+ AnsiString(tmpKSD02_DATA.SOKU_FLG)		+  ",";	// ���荀�ڂ̗L��
			sBuf += " TOKU_FLG="		+ AnsiString(tmpKSD02_DATA.TOKU_FLG)		+  ",";	// ���ʍ��ڂ̗L��
			sBuf += " KIKA_PRT="		+ AnsiString(tmpKSD02_DATA.KIKA_PRT)		+  ",";	// ��������l�̈��
			sBuf += " VALUE_TYPE="		+ AnsiString(tmpKSD02_DATA.VALUE_TYPE)		+  ",";	// ����l�\��
			sBuf += " VALUE_DECI="		+ AnsiString(tmpKSD02_DATA.VALUE_DECI)			  ;	// ����l�����_�ȉ�����

			sBuf += " where DTKSHIN='"	+ AnsiString(tmpKSD02_DATA.DTKSHIN)			+  "'";	// ���Ӑ�i��
			sBuf += " and LOTNO='"		+ AnsiString(tmpKSD02_DATA.LOTNO)			+  "'";	// ���b�gNO
			sBuf += " and UNQ_NO="		+ AnsiString(tmpKSD02_DATA.UNQ_NO)				  ;	// ����NO									// ���b�gNO

			Query1->SQL->Add(sBuf);

			// �₢�������̎��s
			try {
				Query1->ExecSQL();
			}
			catch(EDatabaseError& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}
			catch(Exception& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}

    	}
	}

    return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�[�^��ǉ��iKSM01�j���܂��B
//
//  �@�\����
//    �u�e�P�P�F�ۑ��v���̃f�[�^�ǉ��iKSM01�j����
//
//  �p�����^����
//    int iUpd			�F0 = �V�K�o�^��
//                        1 = �C����
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm3::AddData_KSM01( int iUpd )
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf  = "select DTKSHIN from KSM01";
    sBuf += " where DTKSHIN='" + AnsiString(tmpKSM01_DATA.DTKSHIN) + "'";	// ���Ӑ�i��
    sBuf += " and REVCNT=" + AnsiString(tmpKSM01_DATA.REVCNT);				// �����ԍ�

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True && Query1->Bof == True) ){
            if( iUpd == 0 ){
            	//SBr1->Panels->Items[0]->Text = "���ɓo�^����Ă��܂��B�@�V�K�o�^�����͒��f����܂����B";
				MessageDlg("���ɓo�^����Ă��܂��B�@���i�K�i�}�X�^�[�̍X�V�����͒��f����܂����B", mtWarning,
					TMsgDlgButtons() << mbOK , 0);
            } else {
				//SBr1->Panels->Items[0]->Text = "���ɓo�^����Ă��܂��B�@�C�������͒��f����܂����B";
				MessageDlg("���ɓo�^����Ă��܂��B�@���i�K�i�}�X�^�[�̍X�V�����͒��f����܂����B", mtWarning,
					TMsgDlgButtons() << mbOK , 0);
            }
            return(False);
        }
    }
    catch(EDatabaseError& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }
    catch(Exception& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf = "insert into KSM01(";
    sBuf += " DTKSHIN, REVCNT, HINBAN, DTKSCOD, DTKSNAM, ZISNAM, HINMEI,";
    sBuf += " DTKSHIN1_SZ, DTKSHIN2_SZ, DTKSHIN3_SZ, DTKSHIN4_SZ, DTKSHIN5_SZ,";
    sBuf += " DTKSHIN6_SZ, LOT_LINK_SZ, SOKUTEI_NUM,";
    sBuf += " OUT_TITLE1, OUT_TITLE2, OUT_TITLE3, OUT_TITLE4,";
    sBuf += " OUT_TITLE5, OUT_TITLE6, OUT_TITLE7, OUT_TITLE8,";
    sBuf += " X_OUT, MEMO, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT )";

    sBuf += " VALUES( '";
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN)		+ "'," ;	// ���Ӑ�i��
	sBuf += AnsiString(tmpKSM01_DATA.REVCNT)		+  ",'";	// �����ԍ�
	sBuf += AnsiString(tmpKSM01_DATA.HINBAN)		+ "','";	// ���Еi��
	sBuf += AnsiString(tmpKSM01_DATA.DTKSCOD)		+ "','";	// ���Ӑ�R�[�h
	sBuf += AnsiString(tmpKSM01_DATA.DTKSNAM)		+ "','";	// ���Ӑ於��
	sBuf += AnsiString(tmpKSM01_DATA.ZISNAM)		+ "','";	// �ގ����́i�i��j
	sBuf += AnsiString(tmpKSM01_DATA.HINMEI)		+ "','";	// �i��
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN1_SZ)	+ "','";	// �f�ޗp���Ӑ�i��1
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN2_SZ)	+ "','";	// �f�ޗp���Ӑ�i��2
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN3_SZ)	+ "','";	// �f�ޗp���Ӑ�i��3
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN4_SZ)	+ "','";	// �f�ޗp���Ӑ�i��4
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN5_SZ)	+ "','";	// �f�ޗp���Ӑ�i��5
	sBuf += AnsiString(tmpKSM01_DATA.DTKSHIN6_SZ)	+ "'," ;	// �f�ޗp���Ӑ�i��6
	sBuf += AnsiString(tmpKSM01_DATA.LOT_LINK_SZ)	+  "," ;	// �f�ޗp���b�g�̃����N
	sBuf += AnsiString(tmpKSM01_DATA.SOKUTEI_NUM)	+  "," ;	// ���荀�ڐ�
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE1)	+  "," ;	// ���я��^�C�g���o�͍���1
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE2)	+  "," ;	// ���я��^�C�g���o�͍���2
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE3)	+  "," ;	// ���я��^�C�g���o�͍���3
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE4)	+  "," ;	// ���я��^�C�g���o�͍���4
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE5)	+  "," ;	// ���я��^�C�g���o�͍���5
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE6)	+  "," ;	// ���я��^�C�g���o�͍���6
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE7)	+  "," ;	// ���я��^�C�g���o�͍���7
	sBuf += AnsiString(tmpKSM01_DATA.OUT_TITLE8)	+  "," ;	// ���я��^�C�g���o�͍���8
	sBuf += AnsiString(tmpKSM01_DATA.X_OUT)			+  ",'";	// �w�̏o��
	sBuf += AnsiString(tmpKSM01_DATA.MEMO)			+ "','";	// ���l
	sBuf += AnsiString(tmpKSM01_DATA.ADDYMD)		+ "','";	// �o�^��
	sBuf += AnsiString(tmpKSM01_DATA.ADDTIM)		+ "','";	// �o�^����
	sBuf += AnsiString(tmpKSM01_DATA.UPDYMD)		+ "','";	// �ύX��
	sBuf += AnsiString(tmpKSM01_DATA.UPDTIM)		+ "'," ;	// �ύX����
	sBuf += AnsiString(tmpKSM01_DATA.UPDCHR)		+  "," ;	// �X�V�ҁi�R�[�h�j
	sBuf += AnsiString(tmpKSM01_DATA.UPDCNT)		+  ")" ;	// �X�V��

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }
    catch(Exception& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }

    return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�[�^��ǉ��iKSM02�j���܂��B
//
//  �@�\����
//    �u�e�P�P�F�ۑ��v���̃f�[�^�ǉ��iKSM02�j����
//
//  �p�����^����
//    int iUpd			�F0 = �V�K�o�^��
//                        1 = �C����
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm3::AddData_Details_KSM02( int iUpd )
{
    int			i;
    AnsiString	sBuf;


    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf  = "select DTKSHIN from KSM02";
    sBuf += " where DTKSHIN='" + AnsiString(tmpKSM01_DATA.DTKSHIN) + "'";	// ���Ӑ�i��
    sBuf += " and REVCNT=" + AnsiString(tmpKSM01_DATA.REVCNT);				// �����ԍ�

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True && Query1->Bof == True) ){

            //if( iUpd == 0 ){
            //	SBr1->Panels->Items[0]->Text = "���ɓo�^����Ă��܂��B�@�V�K�o�^�����͒��f����܂����B";
            //} else {
            //	SBr1->Panels->Items[0]->Text = "���ɓo�^����Ă��܂��B�@�C�������͒��f����܂����B";
            //}
            //SBr1->Update();
            //Beep();
            //return(False);

            // �����f�[�^��KSM01�ɂ���ꍇ�́A�폜���܂�

			// Initial Query
			Query1->Close();
			Query1->SQL->Clear();

			// �⍇�����쐬
			sBuf = "DELETE from KSM02";
			sBuf += " where DTKSHIN='" + AnsiString(tmpKSM01_DATA.DTKSHIN)	+ "'"	;	// ���Ӑ�i��
			sBuf += " and REVCNT=" + AnsiString(tmpKSM01_DATA.REVCNT)				;	// �����ԍ�

			Query1->SQL->Add(sBuf);

			// �₢�������̎��s
			try {
				Query1->ExecSQL();
			}
			catch(EDatabaseError& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}
			catch(Exception& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}

        }
    }
    catch(EDatabaseError& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }
    catch(Exception& e) {
		MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return(False);
    }


   	// StringGrid���̃f�[�^��S�ēo�^���܂�
    for( i = 1; i < SGr_SOKUT->RowCount - 1; i++) {
        if( SGr_SOKUT->Cells[15][i].ToIntDef(-1) >= 0 ){

        	// StringGrid����KSM02�\���̂ɒl���R�s�[���܂�
			strcpy( tmpKSM02_DATA.DTKSHIN		,tmpKSM01_DATA.DTKSHIN );	// ��\���Ӑ�i��
			strcpy( tmpKSM02_DATA.REVCNT		,tmpKSM01_DATA.REVCNT );	// �����ԍ�
			sBuf = SGr_SOKUT->Cells[13][i];
			strcpy( tmpKSM02_DATA.UNQ_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[14][i];
			strcpy( tmpKSM02_DATA.ORDER_NO		,sBuf.c_str() );	// �\����
			sBuf = SGr_SOKUT->Cells[15][i];
			strcpy( tmpKSM02_DATA.SKB_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[1][i];
			strcpy( tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// �i��
			sBuf = SGr_SOKUT->Cells[12][i];
			strcpy( tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = SGr_SOKUT->Cells[2][i];
			strcpy( tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
			sBuf = SGr_SOKUT->Cells[4][i];
			strcpy( tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
			sBuf = SGr_SOKUT->Cells[3][i].Trim();
			strcpy( tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// ���荀�ڃT�u���́i���{��j
			sBuf = SGr_SOKUT->Cells[16][i].Trim();
			strcpy( tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// ���荀�ڃT�u���́i�p��j
			sBuf = SGr_SOKUT->Cells[17][i];
			strcpy( tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// ����@��NO
			sBuf = SGr_SOKUT->Cells[9][i];
			strcpy( tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// ����@�햼��
			sBuf = SGr_SOKUT->Cells[5][i];
			strcpy( tmpKSM02_DATA.TANI			,sBuf.c_str() );	// �P��
			sBuf = SGr_SOKUT->Cells[18][i];
			strcpy( tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// �K�i�^�C�v
			sBuf = SGr_SOKUT->Cells[19][i];
			strcpy( tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// �K�i���
			sBuf = SGr_SOKUT->Cells[20][i];
			strcpy( tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = SGr_SOKUT->Cells[21][i];
			strcpy( tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// �K�i�l�P
			sBuf = SGr_SOKUT->Cells[22][i];
			strcpy( tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// �K�i�l�Q
			sBuf = SGr_SOKUT->Cells[23][i];
			strcpy( tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// �K�i�l�R
			sBuf = SGr_SOKUT->Cells[24][i];
			strcpy( tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// �K�i�l����
			sBuf = SGr_SOKUT->Cells[25][i];
			strcpy( tmpKSM02_DATA.KIKA_SUB1		,sBuf.c_str() );	// �K�i�l�T�u�P
			sBuf = SGr_SOKUT->Cells[26][i];
			strcpy( tmpKSM02_DATA.KIKA_SUB2		,sBuf.c_str() );	// �K�i�l�T�u�Q
			sBuf = SGr_SOKUT->Cells[27][i];
			strcpy( tmpKSM02_DATA.KIKA_SUB3		,sBuf.c_str() );	// �K�i�l�T�u�R
			sBuf = SGr_SOKUT->Cells[7][i];
			strcpy( tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = SGr_SOKUT->Cells[10][i];
			strcpy( tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = SGr_SOKUT->Cells[11][i];
			strcpy( tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = SGr_SOKUT->Cells[28][i];
			strcpy( tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = SGr_SOKUT->Cells[8][i];
			strcpy( tmpKSM02_DATA.VALUE_TYPE	,sBuf.c_str() );	// ����l�\��
			sBuf = SGr_SOKUT->Cells[29][i];
			strcpy( tmpKSM02_DATA.VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����



			// Initial Query
			Query1->Close();
			Query1->SQL->Clear();

			// �⍇�����s�i���i�K�i���׃}�X�^�[�j
			sBuf  = "insert into KSM02(";
			sBuf += " DTKSHIN, REVCNT, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK,";
			sBuf += " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG,";
			sBuf += " KIKI_NO, KIKI_NM, TANI, KIKA_TYPE, KIKA_KIND,";
			sBuf += " KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3,";
			sBuf += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3,";
			sBuf += " SOKU_SU, SOKU_FLG, TOKU_FLG, KIKA_PRT,";
			sBuf += " VALUE_TYPE, VALUE_DECI )";

			sBuf += " VALUES( '";
			sBuf += AnsiString(tmpKSM02_DATA.DTKSHIN)		+ "'," ;	// ��\���Ӑ�i��
			sBuf += AnsiString(tmpKSM02_DATA.REVCNT)		+  "," ;	// �����ԍ�
			sBuf += AnsiString(tmpKSM02_DATA.UNQ_NO)		+  "," ;	// ����NO
			sBuf += AnsiString(tmpKSM02_DATA.ORDER_NO)		+  "," ;	// �\����
			sBuf += AnsiString(tmpKSM02_DATA.SKB_NO)		+  ",'";	// ����NO
			sBuf += AnsiString(tmpKSM02_DATA.HINBAN_SK)		+ "'," ;	// �i��
			sBuf += AnsiString(tmpKSM02_DATA.KOMK_NO)		+  ",'";	// ����NO
			sBuf += AnsiString(tmpKSM02_DATA.KOMK_NM)		+ "','";	// ���荀�ږ��́i���{��j
			sBuf += AnsiString(tmpKSM02_DATA.KOMK_ENG)		+ "','";	// ���荀�ږ��́i�p��j
			sBuf += AnsiString(tmpKSM02_DATA.KOMK_SUB)		+ "','";	// ���荀�ڃT�u���́i���{��j
			sBuf += AnsiString(tmpKSM02_DATA.KOMK_SUB_ENG)	+ "'," ;	// ���荀�ڃT�u���́i�p��j
			sBuf += AnsiString(tmpKSM02_DATA.KIKI_NO)		+  ",'";	// ����@��NO
			sBuf += AnsiString(tmpKSM02_DATA.KIKI_NM)		+ "','";	// ����@�햼��
			sBuf += AnsiString(tmpKSM02_DATA.TANI)			+ "'," ;	// �P��
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_TYPE)		+  "," ;	// �K�i�^�C�v
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_KIND)		+  "," ;	// �K�i���
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_DECI)		+  "," ;	// �K�i�����_�ȉ�����
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_NUM1)		+  "," ;	// �K�i�l�P
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_NUM2)		+  "," ;	// �K�i�l�Q
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_NUM3)		+  ",'";	// �K�i�l�R
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_STR)		+ "','";	// �K�i�l����
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_SUB1)		+ "','";	// �K�i�l�T�u�P
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_SUB2)		+ "','";	// �K�i�l�T�u�Q
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_SUB3)		+ "'," ;	// �K�i�l�T�u�R
			sBuf += AnsiString(tmpKSM02_DATA.SOKU_SU)		+  "," ;	// ����w��n��
			sBuf += AnsiString(tmpKSM02_DATA.SOKU_FLG)		+  "," ;	// ���荀�ڂ̗L��
			sBuf += AnsiString(tmpKSM02_DATA.TOKU_FLG)		+  "," ;	// ���ʍ��ڂ̗L��
			sBuf += AnsiString(tmpKSM02_DATA.KIKA_PRT)		+  "," ;	// ��������l�̈��
			sBuf += AnsiString(tmpKSM02_DATA.VALUE_TYPE)	+  "," ;	// ����l�\��
			sBuf += AnsiString(tmpKSM02_DATA.VALUE_DECI)	+  ")" ;	// ����l�����_�ȉ�����

			Query1->SQL->Add(sBuf);

			// �₢�������̎��s
			try {
				Query1->ExecSQL();
			}
			catch(EDatabaseError& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}
			catch(Exception& e) {
				MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
				return(False);
			}

    	}
	}

    return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�������R�[�h�̉����ԍ����X�V���܂��B
//
//  �@�\����
//    �������R�[�h�iKSM01,KSM02�j�̉����ԍ����X�V�i�{�P�j����B
//    �����ԍ�0�̃f�[�^�͍X�V�����X�V
//
//  �p�����^����
//    AnsiString sDTKSHIN�F�X�V�Ώۂ̑�\���Ӑ�i��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm3::UpdKaiteiNo_KSM01_02( AnsiString sDTKSHIN )
{
    int iREVCNT;
    AnsiString sBuf;
    AnsiString sUpdBuf;

    //*** KSM01�̃��R�[�h�X�V
    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����s
    sBuf = "SELECT REVCNT FROM KSM01 ";
    sBuf = sBuf + "WHERE DTKSHIN='" + sDTKSHIN + "'";
    sBuf = sBuf + "ORDER BY REVCNT DESC";

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;
    while( !Query1->Eof ){
        iREVCNT = Query1->Fields->Fields[0]->AsInteger;

        //�����ԍ� �X�V
        sUpdBuf = " UPDATE KSM01 SET REVCNT = " + IntToStr( iREVCNT + 1 ) ;
        if ( iREVCNT == 0 ) {
            sUpdBuf = sUpdBuf + ", UPDYMD = '" + FormatDateTime("yyyymmdd",Date()) + "'";
            sUpdBuf = sUpdBuf + ", UPDTIM = '" + FormatDateTime("hhmm",TDateTime::CurrentTime()) + "'";
        }
        sUpdBuf = sUpdBuf + " WHERE DTKSHIN = '" + sDTKSHIN + "'";
        sUpdBuf = sUpdBuf + " AND REVCNT = " + IntToStr( iREVCNT ) ;

        // Initial Query
        Query2->Close();
        Query2->SQL->Clear();

	    Query2->SQL->Add(sUpdBuf);

	    // �₢�������̎��s
	    try {
	        Query2->ExecSQL();
	    }
	    catch(EDatabaseError& e) {
			MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
	    }
	    catch(Exception& e) {
			MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
	    }

        // �J�[�\�������ɃZ�b�g����
        Query1->Next();
    }


    //*** KSM02�̃��R�[�h�X�V
    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����s
    sBuf = "SELECT REVCNT FROM KSM02 ";
    sBuf = sBuf + "WHERE DTKSHIN='" + sDTKSHIN + "'";
    sBuf = sBuf + "ORDER BY REVCNT DESC";

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;
    while( !Query1->Eof ){
        iREVCNT = Query1->Fields->Fields[0]->AsInteger;

        //�����ԍ� �X�V
        sUpdBuf = "UPDATE KSM02 SET REVCNT = " + IntToStr( iREVCNT + 1 ) ;
        sUpdBuf = sUpdBuf + " WHERE DTKSHIN = '" + sDTKSHIN + "'";
        sUpdBuf = sUpdBuf + " AND REVCNT = " + IntToStr( iREVCNT );

        // Initial Query
        Query2->Close();
        Query2->SQL->Clear();

	    Query2->SQL->Add(sUpdBuf);

	    // �₢�������̎��s
	    try {
	        Query2->ExecSQL();
	    }
	    catch(EDatabaseError& e) {
			MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
	    }
	    catch(Exception& e) {
			MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
	    }

        // �J�[�\�������ɃZ�b�g����
        Query1->Next();
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnResize�C�x���g	�F�R���g���[���̃T�C�Y���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    Panel�̃T�C�Y�ɍ��킹�ĉ�StringGrid�̃T�C�Y���ύX���܂�
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
void __fastcall TForm3::Pnl_SOKUTResize(TObject *Sender)
{
    int iBMarg;

    // �e���x�����猩���e�R���g���[���̉��[�]��
    iBMarg = 2;


    // �������X�g
	if( SGr_SOKUT->Top < Pnl_SOKUT->Height &&
        Pnl_SOKUT->Height - SGr_SOKUT->Top - iBMarg > 0 ){
		SGr_SOKUT->Height = Pnl_SOKUT->Height - SGr_SOKUT->Top - iBMarg;
	} else{
		SGr_SOKUT->Height = 0;
	}

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FStringGrid�i���j�̃f�[�^���R�s�[���܂��i�����s�Ή��j
//
//  �@�\����
//    StringGrid�i���j�̑��荀�ڃf�[�^��cpyKSM02_DATA�ɃR�s�[���܂�
//    ���荀��StringGrid��[Ctrl]+[C]�����������̑��荀�ڃf�[�^�̃R�s�[����
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    bool				�Ftrue  = �R�s�[����
//						�@false = �R�s�[���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm3::SGr_SOKUT_GridMultiLineCopy()
{

    int         i;
    int			cnt;
    AnsiString  sBuf;


    // �͈͑I���������̂ɍŉ��s���܂ގ��́A�G���[����-1
    if( SGr_SOKUT->RowCount - 1 <= iRowSelBottom ){
        if( iRowSelTop > (iRowSelBottom - 1) ){
        	// �G���[���b�Z�[�W
    		MessageDlg("�R�s�[�Ώۂ̍s�ł͂���܂���B", mtWarning,
        	            TMsgDlgButtons() << mbOK , 0);
    		return(false);
        }
        iRowSelBottom = iRowSelBottom - 1;
    }

    // �R�s�[�̌����m�ۂ��܂�
    iCntCpyKSM02_DATA = iRowSelBottom - iRowSelTop + 1;

    if( iCntCpyKSM02_DATA == 0 )	return(false);

    // �������̊m��
    if( hMemCpyKSM02_DATA ){
        GlobalUnlock( hMemCpyKSM02_DATA );
        GlobalFree( hMemCpyKSM02_DATA );
    }
    hMemCpyKSM02_DATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * iCntCpyKSM02_DATA );
    if( hMemCpyKSM02_DATA == NULL ){
    	MessageDlg("�������̈���m�ۂł��܂���B(01)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return(false);
    }
    cpyKSM02_DATA = (struct KSM02_DATA *)GlobalLock(hMemCpyKSM02_DATA);
    if( hMemCpyKSM02_DATA == NULL ){
    	MessageDlg("�������̈���m�ۂł��܂���B(02)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return(false);
    }

    // �I������Ă���͈͂��������Ɋi�[���܂�
    for( i=iRowSelTop, cnt=0; i<=iRowSelBottom; i++, cnt++ ) {
		//strcpy( cpyKSM02_DATA[cnt].DTKSHIN	,sBuf.c_str() );	// ��\���Ӑ�i��
		//strcpy( cpyKSM02_DATA[cnt].REVCNT		,sBuf.c_str() );	// �����ԍ�
		sBuf = SGr_SOKUT->Cells[13][i];
		strcpy( cpyKSM02_DATA[cnt].UNQ_NO		,sBuf.c_str() );	// ����NO
		sBuf = SGr_SOKUT->Cells[14][i];
		strcpy( cpyKSM02_DATA[cnt].ORDER_NO		,sBuf.c_str() );	// �\����
		sBuf = SGr_SOKUT->Cells[15][i];
		strcpy( cpyKSM02_DATA[cnt].SKB_NO		,sBuf.c_str() );	// ����NO
		sBuf = SGr_SOKUT->Cells[1][i];
		strcpy( cpyKSM02_DATA[cnt].HINBAN_SK	,sBuf.c_str() );	// �i��
		sBuf = SGr_SOKUT->Cells[12][i];
		strcpy( cpyKSM02_DATA[cnt].KOMK_NO		,sBuf.c_str() );	// ����NO
		sBuf = SGr_SOKUT->Cells[2][i];
		strcpy( cpyKSM02_DATA[cnt].KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
		sBuf = SGr_SOKUT->Cells[4][i];
		strcpy( cpyKSM02_DATA[cnt].KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
		sBuf = SGr_SOKUT->Cells[3][i];
		strcpy( cpyKSM02_DATA[cnt].KOMK_SUB		,sBuf.c_str() );	// ���荀�ڃT�u���́i���{��j
		sBuf = SGr_SOKUT->Cells[16][i];
		strcpy( cpyKSM02_DATA[cnt].KOMK_SUB_ENG	,sBuf.c_str() );	// ���荀�ڃT�u���́i�p��j
		sBuf = SGr_SOKUT->Cells[17][i];
		strcpy( cpyKSM02_DATA[cnt].KIKI_NO		,sBuf.c_str() );	// ����@��NO
		sBuf = SGr_SOKUT->Cells[9][i];
		strcpy( cpyKSM02_DATA[cnt].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
		sBuf = SGr_SOKUT->Cells[5][i];
		strcpy( cpyKSM02_DATA[cnt].TANI			,sBuf.c_str() );	// �P��
		sBuf = SGr_SOKUT->Cells[18][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
		sBuf = SGr_SOKUT->Cells[19][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_KIND	,sBuf.c_str() );	// �K�i���
		sBuf = SGr_SOKUT->Cells[20][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
		sBuf = SGr_SOKUT->Cells[21][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
		sBuf = SGr_SOKUT->Cells[22][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
		sBuf = SGr_SOKUT->Cells[23][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
		sBuf = SGr_SOKUT->Cells[24][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_STR		,sBuf.c_str() );	// �K�i�l����
		sBuf = SGr_SOKUT->Cells[25][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_SUB1	,sBuf.c_str() );	// �K�i�l�T�u�P
		sBuf = SGr_SOKUT->Cells[26][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_SUB2	,sBuf.c_str() );	// �K�i�l�T�u�Q
		sBuf = SGr_SOKUT->Cells[27][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_SUB3	,sBuf.c_str() );	// �K�i�l�T�u�R
		sBuf = SGr_SOKUT->Cells[7][i];
		strcpy( cpyKSM02_DATA[cnt].SOKU_SU		,sBuf.c_str() );	// ����w��n��
		sBuf = SGr_SOKUT->Cells[10][i];
		strcpy( cpyKSM02_DATA[cnt].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
		sBuf = SGr_SOKUT->Cells[11][i];
		strcpy( cpyKSM02_DATA[cnt].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
		sBuf = SGr_SOKUT->Cells[28][i];
		strcpy( cpyKSM02_DATA[cnt].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
		sBuf = SGr_SOKUT->Cells[8][i];
		strcpy( cpyKSM02_DATA[cnt].VALUE_TYPE	,sBuf.c_str() );	// ����l�\��
		sBuf = SGr_SOKUT->Cells[29][i];
		strcpy( cpyKSM02_DATA[cnt].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
    }

    return(true);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�R�s�[���ꂽ�f�[�^��StringGrid�i���j�ɓ\��t���܂��i�����s�Ή��j
//
//  �@�\����
//    cpyKSM02_DATA�ɃR�s�[���ꂽ���荀�ڃf�[�^��StringGrid�i���j�ɓ\��t���܂�
//    ���荀��StringGrid��[Ctrl]+[V]�����������̑��荀�ڃf�[�^�̓\��t������
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    bool				�Ftrue  = �\��t������
//						�@false = �\��t�����s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm3::SGr_SOKUT_GridMultiLinePaste()
{
	int	cnt;

    if( iCntCpyKSM02_DATA == 0 )	return(false);

	for( cnt=0; cnt<iCntCpyKSM02_DATA; cnt++ ) {
		strcpy( tmpKSM02_DATA.DTKSHIN		, cpyKSM02_DATA[cnt].DTKSHIN		);	// ��\���Ӑ�i��
		strcpy( tmpKSM02_DATA.REVCNT		, cpyKSM02_DATA[cnt].REVCNT			);	// �����ԍ�
		//strcpy( tmpKSM02_DATA.UNQ_NO		, cpyKSM02_DATA[cnt].UNQ_NO			);	// ����NO
		//strcpy( tmpKSM02_DATA.ORDER_NO	, cpyKSM02_DATA[cnt].ORDER_NO		);	// �\����
		strcpy( tmpKSM02_DATA.SKB_NO		, cpyKSM02_DATA[cnt].SKB_NO			);	// ����NO
		strcpy( tmpKSM02_DATA.HINBAN_SK		, cpyKSM02_DATA[cnt].HINBAN_SK		);	// �i��
		strcpy( tmpKSM02_DATA.KOMK_NO		, cpyKSM02_DATA[cnt].KOMK_NO		);	// ����NO
		strcpy( tmpKSM02_DATA.KOMK_NM		, cpyKSM02_DATA[cnt].KOMK_NM		);	// ���荀�ږ��́i���{��j
		strcpy( tmpKSM02_DATA.KOMK_ENG		, cpyKSM02_DATA[cnt].KOMK_ENG		);	// ���荀�ږ��́i�p��j
		strcpy( tmpKSM02_DATA.KOMK_SUB		, cpyKSM02_DATA[cnt].KOMK_SUB		);	// ���荀�ڃT�u���́i���{��j
		strcpy( tmpKSM02_DATA.KOMK_SUB_ENG	, cpyKSM02_DATA[cnt].KOMK_SUB_ENG	);	// ���荀�ڃT�u���́i�p��j
		strcpy( tmpKSM02_DATA.KIKI_NO		, cpyKSM02_DATA[cnt].KIKI_NO		);	// ����@��NO
		strcpy( tmpKSM02_DATA.KIKI_NM		, cpyKSM02_DATA[cnt].KIKI_NM		);	// ����@�햼��
		strcpy( tmpKSM02_DATA.TANI			, cpyKSM02_DATA[cnt].TANI			);	// �P��
		strcpy( tmpKSM02_DATA.KIKA_TYPE		, cpyKSM02_DATA[cnt].KIKA_TYPE		);	// �K�i�^�C�v
		strcpy( tmpKSM02_DATA.KIKA_KIND		, cpyKSM02_DATA[cnt].KIKA_KIND		);	// �K�i���
		strcpy( tmpKSM02_DATA.KIKA_DECI		, cpyKSM02_DATA[cnt].KIKA_DECI		);	// �K�i�����_�ȉ�����
		strcpy( tmpKSM02_DATA.KIKA_NUM1		, cpyKSM02_DATA[cnt].KIKA_NUM1		);	// �K�i�l�P
		strcpy( tmpKSM02_DATA.KIKA_NUM2		, cpyKSM02_DATA[cnt].KIKA_NUM2		);	// �K�i�l�Q
		strcpy( tmpKSM02_DATA.KIKA_NUM3		, cpyKSM02_DATA[cnt].KIKA_NUM3		);	// �K�i�l�R
		strcpy( tmpKSM02_DATA.KIKA_STR		, cpyKSM02_DATA[cnt].KIKA_STR		);	// �K�i�l����
		strcpy( tmpKSM02_DATA.SOKU_SU		, cpyKSM02_DATA[cnt].SOKU_SU		);	// ����w��n��
		strcpy( tmpKSM02_DATA.SOKU_FLG		, cpyKSM02_DATA[cnt].SOKU_FLG		);	// ���荀�ڂ̗L��
		strcpy( tmpKSM02_DATA.TOKU_FLG		, cpyKSM02_DATA[cnt].TOKU_FLG		);	// ���ʍ��ڂ̗L��
		strcpy( tmpKSM02_DATA.KIKA_PRT		, cpyKSM02_DATA[cnt].KIKA_PRT		);	// ��������l�̈��
		strcpy( tmpKSM02_DATA.VALUE_TYPE	, cpyKSM02_DATA[cnt].VALUE_TYPE		);	// ����l�\��
		strcpy( tmpKSM02_DATA.VALUE_DECI	, cpyKSM02_DATA[cnt].VALUE_DECI		);	// ����l�����_�ȉ�����

		// ����f�[�^��ǉ����܂�
		Ins_SGr_SOKUT(SGr_SOKUT->Row);
		SGr_SOKUT->Row = SGr_SOKUT->Row + 1;
	}

    return(true);
}

