//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    �y�o�׌����V�X�e���|���荀�ڃ}�X�^�[�z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �c���@�֎i
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma link "PERFGRAP"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{

    // �������t�H�[����\�����܂�
    Form2 = new TForm2(this);
	Form2->Show();
	Form2->Refresh();

    // �f�[�^�x�[�X������
    Database1->Open();

	// �O���b�h�̏�����
	SGr_List->ColCount = 30;
	SGr_List->ColWidths[0] = 34;
	SGr_List->ColWidths[1] = 175;
	SGr_List->ColWidths[2] = 160;
	SGr_List->ColWidths[3] = 102;
	SGr_List->ColWidths[4] = 50;
	SGr_List->ColWidths[5] = 156;
	SGr_List->ColWidths[6] = 25;
	SGr_List->ColWidths[7] = 55;
	SGr_List->ColWidths[8] = 30;
	SGr_List->ColWidths[9] = 30;
	SGr_List->ColWidths[10] = 78;
	SGr_List->ColWidths[11] = 50;
	SGr_List->ColWidths[12] = 0;
	SGr_List->ColWidths[13] = 0;
	SGr_List->ColWidths[14] = 0;
	SGr_List->ColWidths[15] = 0;
	SGr_List->ColWidths[16] = 0;
	SGr_List->ColWidths[17] = 0;
	SGr_List->ColWidths[18] = 0;
	SGr_List->ColWidths[19] = 0;
	SGr_List->ColWidths[20] = 0;
	SGr_List->ColWidths[21] = 0;
	SGr_List->ColWidths[22] = 0;
	SGr_List->ColWidths[23] = 0;
	SGr_List->ColWidths[24] = 0;
	SGr_List->ColWidths[25] = 0;
	SGr_List->ColWidths[26] = 0;
	SGr_List->ColWidths[27] = 0;
	SGr_List->ColWidths[28] = 0;
	SGr_List->ColWidths[29] = 0;

	SGr_List->Cells[0][0] = "  NO";
	SGr_List->Cells[1][0] = "���荀��";
	SGr_List->Cells[2][0] = "���荀��(English)";
	SGr_List->Cells[3][0] = "����@��";
	SGr_List->Cells[4][0] = "�P��";
	SGr_List->Cells[5][0] = "�K�i(��{)";
	SGr_List->Cells[6][0] = "n��(��{)";
	SGr_List->Cells[7][0] = "�l�\��";
	SGr_List->Cells[8][0] = "����";
	SGr_List->Cells[9][0] = "����";
	SGr_List->Cells[10][0] = "�X�V��";
	SGr_List->Cells[11][0] = "�X�V��";

	SGr_List2->ColCount = 30;
	SGr_List2->ColWidths[0] = 34;
	SGr_List2->ColWidths[1] = 175;
	SGr_List2->ColWidths[2] = 160;
	SGr_List2->ColWidths[3] = 102;
	SGr_List2->ColWidths[4] = 50;
	SGr_List2->ColWidths[5] = 156;
	SGr_List2->ColWidths[6] = 25;
	SGr_List2->ColWidths[7] = 55;
	SGr_List2->ColWidths[8] = 30;
	SGr_List2->ColWidths[9] = 30;
	SGr_List2->ColWidths[10] = 78;
	SGr_List2->ColWidths[11] = 50;
	SGr_List2->ColWidths[12] = 0;
	SGr_List2->ColWidths[13] = 0;
	SGr_List2->ColWidths[14] = 0;
	SGr_List2->ColWidths[15] = 0;
	SGr_List2->ColWidths[16] = 0;
	SGr_List2->ColWidths[17] = 0;
	SGr_List2->ColWidths[18] = 0;
	SGr_List2->ColWidths[19] = 0;
	SGr_List2->ColWidths[20] = 0;
	SGr_List2->ColWidths[21] = 0;
	SGr_List2->ColWidths[22] = 0;
	SGr_List2->ColWidths[23] = 0;
	SGr_List2->ColWidths[24] = 0;
	SGr_List2->ColWidths[25] = 0;
	SGr_List2->ColWidths[26] = 0;
	SGr_List2->ColWidths[27] = 0;
	SGr_List2->ColWidths[28] = 0;
	SGr_List2->ColWidths[29] = 0;

	SGr_List2->Cells[0][0] = "  NO";
	SGr_List2->Cells[1][0] = "���荀��";
	SGr_List2->Cells[2][0] = "���荀��(English)";
	SGr_List2->Cells[3][0] = "����@��";
	SGr_List2->Cells[4][0] = "�P��";
	SGr_List2->Cells[5][0] = "�K�i(��{)";
	SGr_List2->Cells[6][0] = "n��(��{)";
	SGr_List2->Cells[7][0] = "�l�\��";
	SGr_List2->Cells[8][0] = "����";
	SGr_List2->Cells[9][0] = "����";
	SGr_List2->Cells[10][0] = "�X�V��";
	SGr_List2->Cells[11][0] = "�X�V��";

    Pnl_KIKAKU_KIJYUN->Left = Pnl_KIKAKU_MOJI->Left;

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

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnActivate�C�x���g	�F�t�H�[�����A�N�e�B�u�ɂȂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �����\���ɕK�v�ȃf�[�^���������܂�
//    ���������(Form2)����܂�
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
void __fastcall TForm1::FormActivate(TObject *Sender)
{

	int iRow;
	AnsiString sBuf;

   	// �V�����g�����U�N�V�������J�n
    if( Database1->InTransaction == false ){
        Database1->StartTransaction();
        DataSave = false;
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
        SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
        SBr1->Update();
        Beep();
        return;
    }
    iKIKI = (int *)GlobalLock(hMemKIKI);
    if( hMemKIKI == NULL ){
        SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
        SBr1->Update();
        Beep();
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
	while( !Query1->Eof ){

        // �@�햼���R���{�{�b�N�X�ɒǉ�
		sBuf = Query1->FieldValues["KIKI_NM"];
        Cmb_SKTKIKI->Items->Add(sBuf);

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

    Cmb_TANI->Clear();
	while( !Query1->Eof ){

        // �@�햼���R���{�{�b�N�X�ɒǉ�
		sBuf = Query1->FieldValues["TANI"];
        Cmb_TANI->Items->Add(sBuf);

		// �J�[�\�������ɃZ�b�g����
		Query1->Next();
    }


    //----------------------------------------------
    // ���荀�ڃ}�X�^�[����

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s�i���荀�ڃ}�X�^�[�j
	//sBuf = "SELECT * FROM KSM11 ORDER BY ORDER_NO";
	sBuf  = "SELECT KSM11.KOMK_NO, KSM11.ORDER_NO, KSM11.KOMK_NM,";
    sBuf +=       " KSM11.KOMK_ENG, KSM11.KOMK_SUB, KSM11.KOMK_SUB_ENG,";
    sBuf +=       " KSM11.KIKI_NO, KSM11.KIKI_NM, KSM11.TANI, KSM11.KIKA_TYPE,";
    sBuf +=       " KSM11.KIKA_KIND, KSM11.KIKA_DECI, KSM11.KIKA_NUM1,";
    sBuf +=       " KSM11.KIKA_NUM2, KSM11.KIKA_NUM3, KSM11.KIKA_STR,";
    sBuf +=       " KSM11.KIKA_SUB1, KSM11.KIKA_SUB2, KSM11.KIKA_SUB3,";
    sBuf +=       " KSM11.SOKU_SU, KSM11.SOKU_FLG, KSM11.TOKU_FLG,";
    sBuf +=       " KSM11.KIKA_PRT, KSM11.VALUE_TYPE, KSM11.VALUE_DECI,";
    sBuf +=       " KSM11.ADDYMD, KSM11.ADDTIM, KSM11.UPDYMD, KSM11.UPDTIM,";
    sBuf +=       " KSM11.UPDCHR, KSM11.UPDCNT, SM12S.TANNAM";
    sBuf += " FROM KSM11 LEFT JOIN SM12S ON KSM11.UPDCHR = SM12S.TANSYA";
    sBuf += " ORDER BY KSM11.ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	iRow = 1;
    iSOKUT_KMK_NO_MAX = 0;

	while( !Query1->Eof ){

		// �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
		if( iRow >= SGr_List->RowCount ){
			SGr_List->RowCount = iRow + 1;
		}

		// �O���b�h�Ƀf�[�^���Z�b�g���܂��B
		sBuf = iRow ;
		SGr_List->Cells[0][iRow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

        if( VarIsNull(Query1->FieldValues["KOMK_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_NM"];
		}
        SGr_List->Cells[1][iRow] = sBuf;   //���荀�ځi���{��j

        if( VarIsNull(Query1->FieldValues["KOMK_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_ENG"];
        }
        SGr_List->Cells[2][iRow] = sBuf;   //���荀�ځi�p��j

		sBuf = Query1->FieldValues["KIKI_NM"];
		SGr_List->Cells[3][iRow] = sBuf;   //����@�햼��

        if( VarIsNull(Query1->FieldValues["TANI"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["TANI"];
        }
		SGr_List->Cells[4][iRow] = sBuf;   //�P��

		SGr_List->Cells[5][iRow] = "";     //�K�i�i��{�j   ���ĕ`�悷��ׂɕK�v�ł��B

		sBuf = Query1->FieldValues["SOKU_SU"];
		SGr_List->Cells[6][iRow] = sBuf;   //�����i��{�j

		sBuf = Query1->FieldValues["VALUE_TYPE"];
		SGr_List->Cells[7][iRow] = sBuf;   //�l�\��

		sBuf = Query1->FieldValues["SOKU_FLG"];
		SGr_List->Cells[8][iRow] = sBuf;   //���荀�ڂ̗L��

		sBuf = Query1->FieldValues["TOKU_FLG"];
		SGr_List->Cells[9][iRow] = sBuf;   //���ʍ��ڂ̗L��

		sBuf = Query1->FieldValues["UPDYMD"];
        SGr_List->Cells[10][iRow] = sBuf;   //�ύX��

		sBuf = Query1->FieldValues["UPDCHR"];
		SGr_List->Cells[12][iRow] = sBuf;   //�X�V��(�S���҃R�[�h)

        if( VarIsNull(Query1->FieldValues["TANNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["TANNAM"];
        }
		SGr_List->Cells[11][iRow] = sBuf;   //�X�V��

		sBuf = Query1->FieldValues["KOMK_NO"];
		SGr_List->Cells[13][iRow] = sBuf;   //����NO
        // �ő�̍���NO���擾���܂�
	    if( StrToInt(sBuf) > iSOKUT_KMK_NO_MAX ){
        	iSOKUT_KMK_NO_MAX = StrToInt(sBuf);
        }

		sBuf = Query1->FieldValues["ORDER_NO"];
		SGr_List->Cells[14][iRow] = sBuf;   //�\����

		sBuf = Query1->FieldValues["KIKI_NO"];
		SGr_List->Cells[15][iRow] = sBuf;   //����@��NO

		sBuf = Query1->FieldValues["KIKA_TYPE"];
		SGr_List->Cells[16][iRow] = sBuf;   //�K�i�^�C�v

		sBuf = Query1->FieldValues["KIKA_KIND"];
		SGr_List->Cells[17][iRow] = sBuf;   //�K�i���

		sBuf = Query1->FieldValues["KIKA_DECI"];
		SGr_List->Cells[18][iRow] = sBuf;   //�K�i�����_�ȉ�����

		sBuf = Query1->FieldValues["KIKA_NUM1"];
		SGr_List->Cells[19][iRow] = sBuf;   //�K�i�l�P

		sBuf = Query1->FieldValues["KIKA_NUM2"];
		SGr_List->Cells[20][iRow] = sBuf;   //�K�i�l�Q

		sBuf = Query1->FieldValues["KIKA_NUM3"];
		SGr_List->Cells[21][iRow] = sBuf;   //�K�i�l�R

        if( VarIsNull(Query1->FieldValues["KIKA_STR"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KIKA_STR"];
        }
		SGr_List->Cells[22][iRow] = sBuf;   //�K�i����

		sBuf = Query1->FieldValues["KIKA_PRT"];
		SGr_List->Cells[23][iRow] = sBuf;   //��������l�̈��

		sBuf = Query1->FieldValues["VALUE_DECI"];
		SGr_List->Cells[24][iRow] = sBuf;   //����l�����_�ȉ�����

		sBuf = Query1->FieldValues["ADDYMD"];
		SGr_List->Cells[25][iRow] = sBuf;   //�o�^��

		sBuf = Query1->FieldValues["ADDTIM"];
		SGr_List->Cells[26][iRow] =  sBuf;  //�o�^����

		sBuf = Query1->FieldValues["UPDTIM"];
		SGr_List->Cells[27][iRow] = sBuf;   //�X�V����

		sBuf = Query1->FieldValues["UPDCNT"];
		SGr_List->Cells[28][iRow] = sBuf;   //�X�V��

		SGr_List->Cells[29][iRow] = "0";    //�X�V�t���O

		// �J�[�\�������ɃZ�b�g����
		Query1->Next();

		iRow += 1;
	}

    // �f�[�^������\�����܂�
    sBuf = iRow-1;
    LblListCnt->Caption = "�����F" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

    SGr_List->RowCount = iRow + 1;
    SGr_List->Cells[0][iRow] = "";
    SGr_List->Cells[1][iRow] = "";
    SGr_List->Cells[2][iRow] = "";
    SGr_List->Cells[3][iRow] = "";
    SGr_List->Cells[4][iRow] = "";
    SGr_List->Cells[5][iRow] = "";
    SGr_List->Cells[6][iRow] = "";
    SGr_List->Cells[7][iRow] = "";
    SGr_List->Cells[8][iRow] = "";
    SGr_List->Cells[9][iRow] = "";
    SGr_List->Cells[10][iRow] = "";
    SGr_List->Cells[11][iRow] = "";
    SGr_List->Cells[12][iRow] = "";
    SGr_List->Cells[13][iRow] = "";
    SGr_List->Cells[14][iRow] = "";
    SGr_List->Cells[15][iRow] = "";
    SGr_List->Cells[16][iRow] = "";
    SGr_List->Cells[17][iRow] = "";
    SGr_List->Cells[18][iRow] = "";
    SGr_List->Cells[19][iRow] = "";
    SGr_List->Cells[20][iRow] = "";
    SGr_List->Cells[21][iRow] = "";
    SGr_List->Cells[22][iRow] = "";
    SGr_List->Cells[23][iRow] = "";
    SGr_List->Cells[24][iRow] = "";
    SGr_List->Cells[25][iRow] = "";
    SGr_List->Cells[26][iRow] = "";
    SGr_List->Cells[27][iRow] = "";
    SGr_List->Cells[28][iRow] = "";
    SGr_List->Cells[29][iRow] = "";


    //----------------------------------------------
    // �ޗ��ؖ����ڃ}�X�^�[����

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s�i���荀�ڃ}�X�^�[�j
	//sBuf = "SELECT * FROM KSM12 ORDER BY ORDER_NO";
	sBuf  = "SELECT KSM12.KOMK_NO, KSM12.ORDER_NO, KSM12.KOMK_NM,";
    sBuf +=       " KSM12.KOMK_ENG, KSM12.KOMK_SUB, KSM12.KOMK_SUB_ENG,";
    sBuf +=       " KSM12.KIKI_NO, KSM12.KIKI_NM, KSM12.TANI, KSM12.KIKA_TYPE,";
    sBuf +=       " KSM12.KIKA_KIND, KSM12.KIKA_DECI, KSM12.KIKA_NUM1,";
    sBuf +=       " KSM12.KIKA_NUM2, KSM12.KIKA_NUM3, KSM12.KIKA_STR,";
    sBuf +=       " KSM12.KIKA_SUB1, KSM12.KIKA_SUB2, KSM12.KIKA_SUB3,";
    sBuf +=       " KSM12.SOKU_SU, KSM12.SOKU_FLG, KSM12.TOKU_FLG,";
    sBuf +=       " KSM12.KIKA_PRT, KSM12.VALUE_TYPE, KSM12.VALUE_DECI,";
    sBuf +=       " KSM12.ADDYMD, KSM12.ADDTIM, KSM12.UPDYMD, KSM12.UPDTIM,";
    sBuf +=       " KSM12.UPDCHR, KSM12.UPDCNT, SM12S.TANNAM";
    sBuf += " FROM KSM12 LEFT JOIN SM12S ON KSM12.UPDCHR = SM12S.TANSYA";
    sBuf += " ORDER BY KSM12.ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	iRow = 1;
    iZAIRY_KMK_NO_MAX = 0;

	while( !Query1->Eof ){

		// �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
		if( iRow >= SGr_List2->RowCount ){
			SGr_List2->RowCount = iRow + 1;
		}

		// �O���b�h�Ƀf�[�^���Z�b�g���܂��B
		sBuf = iRow ;
		SGr_List2->Cells[0][iRow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

        if( VarIsNull(Query1->FieldValues["KOMK_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_NM"];
		}
        SGr_List2->Cells[1][iRow] = sBuf;   //���荀�ځi���{��j

        if( VarIsNull(Query1->FieldValues["KOMK_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_ENG"];
        }
        SGr_List2->Cells[2][iRow] = sBuf;   //���荀�ځi�p��j

		sBuf = Query1->FieldValues["KIKI_NM"];
		SGr_List2->Cells[3][iRow] = sBuf;   //����@�햼��

        if( VarIsNull(Query1->FieldValues["TANI"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["TANI"];
		}
        SGr_List2->Cells[4][iRow] = sBuf;   //�P��

		SGr_List2->Cells[5][iRow] = "";     //�K�i�i��{�j   ���ĕ`�悷��ׂɕK�v�ł��B

		sBuf = Query1->FieldValues["SOKU_SU"];
		SGr_List2->Cells[6][iRow] = sBuf;   //�����i��{�j

		sBuf = Query1->FieldValues["VALUE_TYPE"];
		SGr_List2->Cells[7][iRow] = sBuf;   //�l�\��

		sBuf = Query1->FieldValues["SOKU_FLG"];
		SGr_List2->Cells[8][iRow] = sBuf;   //���荀�ڂ̗L��

		sBuf = Query1->FieldValues["TOKU_FLG"];
		SGr_List2->Cells[9][iRow] = sBuf;   //���ʍ��ڂ̗L��

		sBuf = Query1->FieldValues["UPDYMD"];
        SGr_List2->Cells[10][iRow] = sBuf;   //�ύX��

		sBuf = Query1->FieldValues["UPDCHR"];
		SGr_List2->Cells[12][iRow] = sBuf;   //�X�V��(�S���҃R�[�h)

        if( VarIsNull(Query1->FieldValues["TANNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["TANNAM"];
        }
		SGr_List2->Cells[11][iRow] = sBuf;   //�X�V��

		sBuf = Query1->FieldValues["KOMK_NO"];
		SGr_List2->Cells[13][iRow] = sBuf;   //����NO
        // �ő�̍���NO���擾���܂�
	    if( StrToInt(sBuf) > iZAIRY_KMK_NO_MAX ){
        	iZAIRY_KMK_NO_MAX = StrToInt(sBuf);
        }

		sBuf = Query1->FieldValues["ORDER_NO"];
		SGr_List2->Cells[14][iRow] = sBuf;   //�\����

		sBuf = Query1->FieldValues["KIKI_NO"];
		SGr_List2->Cells[15][iRow] = sBuf;   //����@��NO

		sBuf = Query1->FieldValues["KIKA_TYPE"];
		SGr_List2->Cells[16][iRow] = sBuf;   //�K�i�^�C�v

		sBuf = Query1->FieldValues["KIKA_KIND"];
		SGr_List2->Cells[17][iRow] = sBuf;   //�K�i���

		sBuf = Query1->FieldValues["KIKA_DECI"];
		SGr_List2->Cells[18][iRow] = sBuf;   //�K�i�����_�ȉ�����

		sBuf = Query1->FieldValues["KIKA_NUM1"];
		SGr_List2->Cells[19][iRow] = sBuf;   //�K�i�l�P

		sBuf = Query1->FieldValues["KIKA_NUM2"];
		SGr_List2->Cells[20][iRow] = sBuf;   //�K�i�l�Q

		sBuf = Query1->FieldValues["KIKA_NUM3"];
		SGr_List2->Cells[21][iRow] = sBuf;   //�K�i�l�R

        if( VarIsNull(Query1->FieldValues["KIKA_STR"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KIKA_STR"];
		}
        SGr_List2->Cells[22][iRow] = sBuf;   //�K�i����

		sBuf = Query1->FieldValues["KIKA_PRT"];
		SGr_List2->Cells[23][iRow] = sBuf;   //��������l�̈��

		sBuf = Query1->FieldValues["VALUE_DECI"];
		SGr_List2->Cells[24][iRow] = sBuf;   //����l�����_�ȉ�����

		sBuf = Query1->FieldValues["ADDYMD"];
		SGr_List2->Cells[25][iRow] = sBuf;   //�o�^��

		sBuf = Query1->FieldValues["ADDTIM"];
		SGr_List2->Cells[26][iRow] =  sBuf;  //�o�^����

		sBuf = Query1->FieldValues["UPDTIM"];
		SGr_List2->Cells[27][iRow] = sBuf;   //�X�V����

		sBuf = Query1->FieldValues["UPDCNT"];
		SGr_List2->Cells[28][iRow] = sBuf;   //�X�V��

		SGr_List2->Cells[29][iRow] = "0";    //�X�V�t���O

		// �J�[�\�������ɃZ�b�g����
		Query1->Next();

		iRow += 1;
	}

    // �f�[�^������\�����܂�
    sBuf = iRow-1;
    LblListCnt2->Caption = "�����F" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

    SGr_List2->RowCount = iRow + 1;
    SGr_List2->Cells[0][iRow] = "";
    SGr_List2->Cells[1][iRow] = "";
    SGr_List2->Cells[2][iRow] = "";
    SGr_List2->Cells[3][iRow] = "";
    SGr_List2->Cells[4][iRow] = "";
    SGr_List2->Cells[5][iRow] = "";
    SGr_List2->Cells[6][iRow] = "";
    SGr_List2->Cells[7][iRow] = "";
    SGr_List2->Cells[8][iRow] = "";
    SGr_List2->Cells[9][iRow] = "";
    SGr_List2->Cells[10][iRow] = "";
    SGr_List2->Cells[11][iRow] = "";
    SGr_List2->Cells[12][iRow] = "";
    SGr_List2->Cells[13][iRow] = "";
    SGr_List2->Cells[14][iRow] = "";
    SGr_List2->Cells[15][iRow] = "";
    SGr_List2->Cells[16][iRow] = "";
    SGr_List2->Cells[17][iRow] = "";
    SGr_List2->Cells[18][iRow] = "";
    SGr_List2->Cells[19][iRow] = "";
    SGr_List2->Cells[20][iRow] = "";
    SGr_List2->Cells[21][iRow] = "";
    SGr_List2->Cells[22][iRow] = "";
    SGr_List2->Cells[23][iRow] = "";
    SGr_List2->Cells[24][iRow] = "";
    SGr_List2->Cells[25][iRow] = "";
    SGr_List2->Cells[26][iRow] = "";
    SGr_List2->Cells[27][iRow] = "";
    SGr_List2->Cells[28][iRow] = "";
    SGr_List2->Cells[29][iRow] = "";

    //�P�s�ڂ������I�����܂�
    SGr_ListSelectCell( SGr_List, 1, 1, true);
    SGr_ListClick( SGr_List );

	Form2->Close();
	Form2->Refresh();
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
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    AnsiString sBuf;
    // �X�e�[�^�X���b�Z�[�W
    if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
    }

     switch(Key)
     {
         case VK_F2:  BtnF02Click(BtnF02);    Key = 0; break;
         case VK_F3:  BtnF03Click(BtnF03);    Key = 0; break;
         case VK_F4:  BtnF04Click(BtnF04);    Key = 0; break;
         case VK_F5:  BtnF05Click(BtnF05);    Key = 0; break;
         case VK_F8:  BtnF08Click(BtnF08);    Key = 0; break;
         case VK_F9:  BtnF09Click(BtnF09);    Key = 0; break;
         case VK_F10: BtnF10Click(BtnF10);    Key = 0; break;
         case VK_F11: BtnF11Click(BtnF11);    Key = 0; break;
         case VK_F12: BtnF12Click(BtnF12);    Key = 0; break;

         // Enter
         case VK_RETURN:
                // �ڍו�
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
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    // �f�[�^��ύX�������ǂ����̃t���O�`�F�b�N
    if( DataSave ){
        switch( MessageDlg( "�f�[�^���ҏW����Ă��܂��B\n�ۑ����܂����H",
                           mtConfirmation, mbYesNoCancel, 0) ){
            // �uYes�v      �ۑ�
            case mrYes:
	            BtnF11Click(Sender);
                break;
            // �uNo�v       �ύX��j��
            case mrNo:
                if( Database1->InTransaction == True )  Database1->Rollback();
                break;
            // �uCancel�v   �L�����Z��
            case mrCancel:
                CanClose = false;
                return;
        }
    }
    else{
        if( Database1->InTransaction == True )  Database1->Rollback();
    }

	// �f�[�^�x�[�X�ڑ����J�����܂�
    Query1->Close();
    //Query2->Close();

	Database1->Close();

    // �������̊J��
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
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    if( !BtnF02->Enabled )    return;
	if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
	    if(SGr_List->Row > 1){
        	SGr_List->Row -= 1;
        	SGr_List->SetFocus();
    	}
	} else{
	    if(SGr_List2->Row > 1){
        	SGr_List2->Row -= 1;
        	SGr_List2->SetFocus();
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
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    if( !BtnF03->Enabled )    return;
	if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
    	if( (SGr_List->RowCount-1) > SGr_List->Row ){
        	SGr_List->Row += 1;
        	SGr_List->SetFocus();
    	}
	} else{
    	if( (SGr_List2->RowCount-1) > SGr_List2->Row ){
        	SGr_List2->Row += 1;
        	SGr_List2->SetFocus();
    	}
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�S�F�ؑցv�{�^�������������̏���
//
//  �@�\����
//    �I���^�u�i�o�׌������ږ��͍ޗ��ؖ����ځj��؂�ւ��܂�
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
void __fastcall TForm1::BtnF04Click(TObject *Sender)
{
    if( !BtnF04->Enabled )    return;
	if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
	  	PgCtr_List->SelectNextPage(true);
	} else{
	  	PgCtr_List->SelectNextPage(false);
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
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{
    if( !BtnF05->Enabled )    return;

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "��ʈ�����ł�... ���΂炭���҂����������B";
    SBr1->Update();

    Form1->Print();

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�W�F�V�K�o�^�v�{�^�������������̏���
//
//  �@�\����
//    ��ʉ��ɓ��͂��ꂽ���ڂ��e�[�u���iKSM11,KSM12�j�ɓo�^���܂�
//    StringGrid�Ɉ�s�ǉ����܂�
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
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
    AnsiString sBuf;
    int i, k;
    int iRow;
    int iORDER_NO;
    int nRet;
    int iKMK_NO_MAX;

    TButton *btn = (TButton *)Sender;

    if( !BtnF08->Enabled )    return;

    // ���̓f�[�^�̃`�F�b�N
    if(Edt_SKTKMK_JPN->Text.IsEmpty()){
        MessageDlg("���ږ�����͂��Ă��������B", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
        Edt_SKTKMK_JPN->SetFocus();
        return;
    }

    if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
        if( Nmb_KIKAKU_HANI_MIN->Text.ToIntDef(0) >
            Nmb_KIKAKU_HANI_MAX->Text.ToIntDef(0) ){
            MessageDlg("�K�i�͈͎̔w�肪����������܂���B", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
            Nmb_KIKAKU_HANI_MIN->SetFocus();
            return;
        }
    }

    // ���ɓo�^����Ă��鍀�ږ����`�F�b�N���܂�
    if( Rdo_TYPE_SYUKA->Checked == true ){

        // �o�׌�������p����
        for( i = 1; i < SGr_List->RowCount; i++ ){
            sBuf = SGr_List->Cells[1][i];
	    	if( Edt_SKTKMK_JPN->Text == sBuf ){
		        nRet = MessageDlg("���ɓ������荀�ڂ��o�^����Ă��܂��B�o�^���܂���낵���ł���?", mtConfirmation,
        				TMsgDlgButtons() << mbYes << mbNo, 0);
        		if(nRet == mrNo ) {
        		    return;
        		}
                else {
                	break;
                }
            }
        }

        // �V�K�o�^�s�����肵�܂�
        // ���荀�ڃ}�X�^�[��
        iRow = SGr_List->Row + 1;
        if( Rdo_List1_Order2->Checked ){
            // ���荀�ږ��̏�
			for( i = 1, iRow = 1; i < SGr_List->RowCount - 1; i++ ){
	            if( SGr_List->Cells[1][i] > Edt_SKTKMK_JPN->Text ){
                    break;
                }
	    	}
			iRow = i;
        } else if( Rdo_List1_Order3->Checked ){
            // ����@��E���荀�ږ��̏�
			sBuf = Edt_SKTKMK_JPN->Text;
			for( i = 1, iRow = 1; i < SGr_List->RowCount - 1; i++ ){
	            if( SGr_List->Cells[15][i].ToIntDef(0) > iKIKI[Cmb_SKTKIKI->ItemIndex] ){
                    break;
				} else {
					if( SGr_List->Cells[15][i].ToIntDef(0) == iKIKI[Cmb_SKTKIKI->ItemIndex] &&
		                SGr_List->Cells[1][i].ToIntDef(0) > Edt_SKTKMK_JPN->Text ){
                    	break;
					}
                }
	    	}
			iRow = i;
        }
       	if( iRow >= SGr_List->RowCount ){
       		iRow--;
		}

        // �V�K�o�^����f�[�^�̕\���������肵�܂�
       	iORDER_NO = SGr_List->Cells[14][SGr_List->Row].ToIntDef(-1) + 1;
    	if( iORDER_NO <= 0 ){
        	iORDER_NO = SGr_List->Cells[14][SGr_List->RowCount-2].ToInt() + 1;
    	}

	    // �ő區��NO��+1���܂�
        iSOKUT_KMK_NO_MAX++;
        iKMK_NO_MAX = iSOKUT_KMK_NO_MAX;
    }
    else {

        // �ޗ��ؖ��p����
        for( i = 1; i < SGr_List2->RowCount; i++ ){
            sBuf = SGr_List2->Cells[1][i];
	    	if( Edt_SKTKMK_JPN->Text == sBuf ){
		        nRet = MessageDlg("���ɓ������荀�ڂ��o�^����Ă��܂��B�o�^���܂���낵���ł���?", mtConfirmation,
        				TMsgDlgButtons() << mbYes << mbNo, 0);
        		if(nRet == mrNo ) {
        		    return;
        		}
                else {
                	break;
                }
            }
        }

        // �V�K�o�^�s�����肵�܂�
        // ���荀�ڃ}�X�^�[��
        iRow = SGr_List2->Row + 1;
        if( Rdo_List2_Order2->Checked ){
            // ���荀�ږ��̏�
			for( i = 1, iRow = 1; i < SGr_List2->RowCount - 1; i++ ){
	            if( SGr_List2->Cells[1][i] > Edt_SKTKMK_JPN->Text ){
                    break;
                }
	    	}
			iRow = i;
        } else if( Rdo_List2_Order3->Checked ){
            // ����@��E���荀�ږ��̏�
			sBuf = Edt_SKTKMK_JPN->Text;
			for( i = 1, iRow = 1; i < SGr_List2->RowCount - 1; i++ ){
	            if( SGr_List2->Cells[15][i].ToIntDef(0) > iKIKI[Cmb_SKTKIKI->ItemIndex] ){
                    break;
				} else {
					if( SGr_List2->Cells[15][i].ToIntDef(0) == iKIKI[Cmb_SKTKIKI->ItemIndex] &&
		                SGr_List2->Cells[1][i].ToIntDef(0) > Edt_SKTKMK_JPN->Text ){
                    	break;
					}
                }
	    	}
			iRow = i;
        }
       	if( iRow >= SGr_List2->RowCount ){
       		iRow--;
		}

        // �V�K�o�^����f�[�^�̕\���������肵�܂�
       	iORDER_NO = SGr_List2->Cells[14][SGr_List2->Row].ToIntDef(-1) + 1;
    	if( iORDER_NO <= 0 ){
        	iORDER_NO = SGr_List2->Cells[14][SGr_List2->RowCount-2].ToInt() + 1;
    	}

	    // �ő區��NO��+1���܂�
        iZAIRY_KMK_NO_MAX++;
        iKMK_NO_MAX = iZAIRY_KMK_NO_MAX;
    }

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "�V�K�o�^���ł��D�D�D���΂炭���҂��������B";
    SBr1->Update();


    sBuf = IntToStr(iKMK_NO_MAX);
    strcpy( tmpKSM11_12_DATA.KOMK_NO		,sBuf.c_str() );	// ����NO
    sBuf = IntToStr(iORDER_NO);
    strcpy( tmpKSM11_12_DATA.ORDER_NO		,sBuf.c_str() );	// �\����
    sBuf = Edt_SKTKMK_JPN->Text;
    strcpy( tmpKSM11_12_DATA.KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
    sBuf = Edt_SKTKMK_ENG->Text;
    strcpy( tmpKSM11_12_DATA.KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
    sBuf = IntToStr(iKIKI[Cmb_SKTKIKI->ItemIndex]);
    strcpy( tmpKSM11_12_DATA.KIKI_NO		,sBuf.c_str() );	// ����@��NO
    sBuf = Cmb_SKTKIKI->Text;
    strcpy( tmpKSM11_12_DATA.KIKI_NM		,sBuf.c_str() );	// ����@�햼��
    sBuf = Cmb_TANI->Text;
    strcpy( tmpKSM11_12_DATA.TANI			,sBuf.c_str() );	// �P��
    if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
    	sBuf = Nmb_KIKAKU_HANI_MIN->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
    	sBuf = Nmb_KIKAKU_HANI_MAX->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
    	sBuf = "0";
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
    	sBuf = "";
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// �K�i�l����
    	sBuf = "1";
    } else if( Rdo_KIKAKU_SHITEI_KIJYUN->Checked ) {
    	sBuf = Nmb_KIKAKU_KIJYUN_MID->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
    	sBuf = Nmb_KIKAKU_KIJYUN_MAX->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
    	sBuf = Nmb_KIKAKU_KIJYUN_MIN->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
    	sBuf = "";
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// �K�i�l����
    	sBuf = "2";
    } else {
    	sBuf = "0";
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
    	sBuf = Edt_KIKAKU_STRING->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// �K�i�l����
    	sBuf = "3";
    }
    strcpy( tmpKSM11_12_DATA.KIKA_TYPE		,sBuf.c_str() );	// �K�i�^�C�v
    if( Rdo_KIKAKU_SYURUI_MINMAX->Checked )			sBuf = "1";
    else if( Rdo_KIKAKU_SYURUI_MAX->Checked )		sBuf = "2";
    else											sBuf = "3";
    strcpy( tmpKSM11_12_DATA.KIKA_KIND		,sBuf.c_str() );	// �K�i���
    sBuf = Nmb_KIKAKU_DOUBLE->Text;
    strcpy( tmpKSM11_12_DATA.KIKA_DECI		,sBuf.c_str() );	// �K�i�����_�ȉ�����
    sBuf = Nmb_N->Text;
    strcpy( tmpKSM11_12_DATA.SOKU_SU		,sBuf.c_str() );	// ����w��n��
    if( Rdo_SKTKMK_ON->Checked )			sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
    if( Rdo_TKBKMK_ON->Checked )			sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
    if( Rdo_MANMIN_PRT_ON->Checked )		sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
    if( Rdo_VALUE_NORMAL->Checked )			sBuf = "0";
    else if( Rdo_VALUE_KAKUDO->Checked )	sBuf = "1";
    else if( Rdo_VALUE_OK->Checked )		sBuf = "2";
    else									sBuf = "3";
    strcpy( tmpKSM11_12_DATA.VALUE_TYPE		,sBuf.c_str() );	// ����l�̕\��
    sBuf = Nmb_VALUE_DOUBLE->Text;
    strcpy( tmpKSM11_12_DATA.VALUE_DECI		,sBuf.c_str() );	// ����l�����_�ȉ�����
    sBuf = FormatDateTime("yyyymmdd",Date());
    strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );		// �o�^��
    strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );		// �ύX��
    sBuf = FormatDateTime("hhmm",TDateTime::CurrentTime());
    strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );		// �o�^����
    strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );		// �ύX����
    sBuf = IntToStr(USER_COD);
    strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );		// �X�V�ҁi�R�[�h�j
    sBuf = USER_NAM;
    strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );		// �X�V�ҁi���́j
    sBuf = "0";
    strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );		// �X�V��

    // �V�K�f�[�^�̑}�����V�K�f�[�^�s�ȉ��̍s�����炵�܂�
    if( Rdo_TYPE_SYUKA->Checked ){

	    // �f�[�^�V�K�o�^����
 		if( AddData("KSM11") == False )	return;

	    // ��s���₷
    	SGr_List->RowCount = SGr_List->RowCount + 1;
        // �sNo��t����
		sBuf = IntToStr(SGr_List->RowCount-2);
		SGr_List->Cells[0][SGr_List->RowCount-2] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
	    // �ŉ��s���N���A�[
    	for( k = 0; k < SGr_List->ColCount; k++) {
			SGr_List->Cells[k][SGr_List->RowCount-1] = "";
    	}
        // �ǉ��f�[�^�̕\������蓯�����傫������\�����{�P���܂�
    	for( i = 1; i < SGr_List->RowCount - 1; i++) {
            if( SGr_List->Cells[14][i].ToIntDef(0) >= iORDER_NO ){
				SGr_List->Cells[14][i] = IntToStr(SGr_List->Cells[14][i].ToIntDef(0) + 1);
				SGr_List->Cells[29][i] = "1";		// �X�V�t���O��ON
        	}
    	}

        // �V�K�f�[�^�s�ȉ��̍s�����炵�܂�
    	for( i = SGr_List->RowCount - 2; i > iRow; i--) {
    		for( k = 1; k < SGr_List->ColCount; k++) {
				SGr_List->Cells[k][i] = SGr_List->Cells[k][i-1];
        	}
    	}

	    // �f�[�^������\�����܂�
    	sBuf = SGr_List->RowCount-2;
    	LblListCnt->Caption = "�����F" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

	    //�V�K�f�[�^��SGr_List�ɕ\��
    	// �O���b�h�Ƀf�[�^���Z�b�g���܂��B
		GridLinePaste( SGr_List, iRow, "0");

	} else {

	    // �f�[�^�V�K�o�^����
 		if( AddData("KSM12") == False )	return;

	    // ��s���₷
    	SGr_List2->RowCount = SGr_List2->RowCount + 1;
        // �sNo��t����
		sBuf = IntToStr(SGr_List2->RowCount-2);
		SGr_List2->Cells[0][SGr_List2->RowCount-2] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
	    // �ŉ��s���N���A�[
    	for( k = 0; k < SGr_List2->ColCount; k++) {
			SGr_List2->Cells[k][SGr_List2->RowCount-1] = "";
    	}
        // �ǉ��f�[�^�̕\������蓯�����傫������\�����{�P���܂�
    	for( i = 1; i < SGr_List2->RowCount - 1; i++) {
            if( SGr_List2->Cells[14][i].ToIntDef(0) >= iORDER_NO ){
				SGr_List2->Cells[14][i] = IntToStr(SGr_List2->Cells[14][i].ToIntDef(0) + 1);
				SGr_List2->Cells[29][i] = "1";		// �X�V�t���O��ON
        	}
    	}

        // �V�K�f�[�^�s�ȉ��̍s�����炵�܂�
    	for( i = SGr_List2->RowCount - 2; i > iRow; i--) {
    		for( k = 1; k < SGr_List2->ColCount; k++) {
				SGr_List2->Cells[k][i] = SGr_List2->Cells[k][i-1];
        	}
    	}

	    // �f�[�^������\�����܂�
    	sBuf = SGr_List2->RowCount-2;
    	LblListCnt2->Caption = "�����F" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

	    //�V�K�f�[�^��SGr_List�ɕ\��
    	// �O���b�h�Ƀf�[�^���Z�b�g���܂��B
		GridLinePaste( SGr_List2, iRow, "0");

    }


    // �C���{�^������Ăяo�����ꍇ������i�o�׌������ڂƑf�ތ������ڂ̓���ւ��j�̂�
    // �Ăяo�����{�^���𔻒肵�Ă��܂��B
    if( btn->Name == "BtnF08" ){

    	// �o�^���ڂɂ��킹�ăO���b�h�̕\����؂�ւ��܂�
    	if( Rdo_TYPE_SYUKA->Checked ){
    		if( PgCtr_List->ActivePage->Name != "TabSheet1" ){
    			BtnF04Click(BtnF04);
    	    }
    		// �V�����s��I��
            SGr_List->Row = iRow;
    		SGr_List->SetFocus();
    		SGr_ListSelectCell(SGr_List,1,iRow,true);
    	} else {
    		if( PgCtr_List->ActivePage->Name != "TabSheet2" ){
    			BtnF04Click(BtnF04);
    	    }
    		// �V�����s��I��
            SGr_List2->Row = iRow;
    		SGr_List2->SetFocus();
    		SGr_ListSelectCell(SGr_List2,1,iRow,true);
    	}
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // �f�[�^��ύX�����t���O
    DataSave = true;

    // �{�^���̏�����
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�X�F�C���v�{�^�������������̏���
//
//  �@�\����
//    StringGrid�őI�����ꂽ�f�[�^�ɑ΂��ĉ�ʉ��ɓ��͂��ꂽ���ڂɍX�V���܂�
//    �e�[�u���iKSM11,KSM12�j���X�V���܂�
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
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{

    AnsiString sBuf;
    int i;
    int nRet;

    if( !BtnF09->Enabled )    return;

    if( PnlUPDYMD->Tag == -1){
    	MessageDlg("�C����������܂���B�f�[�^��I�����Ă��������B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    if( Rdo_TYPE_SYUKA->Checked && SGr_List->Cells[13][SGr_List->Row].ToIntDef(0) == 1){
        // �X�e�[�^�X���b�Z�[�W
    	MessageDlg("�C���o���Ȃ����ڂł��B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    // �\������Ă���O���b�h�ƏC�����鍀�ڂ��Ⴄ�ꍇ�A�m�F���s���������܂��B
    if( Rdo_TYPE_SYUKA->Checked ){
    	if( PgCtr_List->ActivePage->Name != "TabSheet1" ){
        	nRet = MessageDlg("�ޗ��ؖ��p���ڂ��A�o�׌������ڂƂ��ďC������悤�Ƃ��Ă��܂��B��낵���ł���?", mtConfirmation,
        			TMsgDlgButtons() << mbYes << mbNo, 0);
        	if(nRet == mrNo ) {
        	    return;
        	}

            // �o�׌������ڂ֐V�K�o�^���܂�
            BtnF08Click(BtnF09);

            // �ޗ��ؖ������ڂ̑I�����ڂ��폜���܂�
            BtnF10Click(BtnF09);

            // �I���^�u�̐ؑ�
			BtnF04Click(BtnF04);

            return;
        }
    } else {
    	if( PgCtr_List->ActivePage->Name != "TabSheet2" ){
        	nRet = MessageDlg("�o�׌������ڂ��A�ޗ��ؖ��p���ڂƂ��ďC������悤�Ƃ��Ă��܂��B��낵���ł���?", mtConfirmation,
        			TMsgDlgButtons() << mbYes << mbNo, 0);
        	if(nRet == mrNo ) {
        	    return;
        	}

            // �ޗ��ؖ������ڂ֐V�K�o�^���܂�
            BtnF08Click(BtnF09);

            // �o�׌������ڂ̑I�����ڂ��폜���܂�
            BtnF10Click(BtnF09);

            // �I���^�u�̐ؑ�
			BtnF04Click(BtnF04);

            return;
        }
    }

    // ���ɓo�^����Ă��鍀�ږ����`�F�b�N���܂�
    if( Rdo_TYPE_SYUKA->Checked == true ){

        // �o�׌�������p����
        for( i = 1; i < SGr_List->RowCount; i++ ){
            sBuf = SGr_List->Cells[1][i];
	    	if( Edt_SKTKMK_JPN->Text == sBuf && i != SGr_List->Row ){
		        nRet = MessageDlg("���ɓ������荀�ڂ��o�^����Ă��܂��B�o�^���܂���낵���ł���?", mtConfirmation,
        				TMsgDlgButtons() << mbYes << mbNo, 0);
        		if(nRet == mrNo ) {
        		    return;
        		}
                else {
                	break;
                }
            }
        }
    }
    else {

        // �ޗ��ؖ��p����
        for( i = 1; i < SGr_List2->RowCount; i++ ){
            sBuf = SGr_List2->Cells[1][i];
	    	if( Edt_SKTKMK_JPN->Text == sBuf && i != SGr_List2->Row ){
		        nRet = MessageDlg("���ɓ������荀�ڂ��o�^����Ă��܂��B�o�^���܂���낵���ł���?", mtConfirmation,
        				TMsgDlgButtons() << mbYes << mbNo, 0);
        		if(nRet == mrNo ) {
        		    return;
        		}
                else {
                	break;
                }
            }
        }
    }

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "�C�����ł��D�D�D���΂炭���҂��������B";
    SBr1->Update();


    // �f�[�^���o�b�t�@�Ɋi�[���܂��B
    sBuf = IntToStr(PnlUPDYMD->Tag);
    strcpy( tmpKSM11_12_DATA.KOMK_NO		,sBuf.c_str() );	// ����NO
    sBuf = SGr_List->Cells[14][SGr_List->Row];
    strcpy( tmpKSM11_12_DATA.ORDER_NO		,sBuf.c_str() );	// �\����
    sBuf = Edt_SKTKMK_JPN->Text;
    strcpy( tmpKSM11_12_DATA.KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
    sBuf = Edt_SKTKMK_ENG->Text;
    strcpy( tmpKSM11_12_DATA.KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
    sBuf = IntToStr(iKIKI[Cmb_SKTKIKI->ItemIndex]);
    strcpy( tmpKSM11_12_DATA.KIKI_NO		,sBuf.c_str() );	// ����@��NO
    sBuf = Cmb_SKTKIKI->Text;
    strcpy( tmpKSM11_12_DATA.KIKI_NM		,sBuf.c_str() );	// ����@�햼��
    sBuf = Cmb_TANI->Text;
    strcpy( tmpKSM11_12_DATA.TANI			,sBuf.c_str() );	// �P��
    if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
    	sBuf = Nmb_KIKAKU_HANI_MIN->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
    	sBuf = Nmb_KIKAKU_HANI_MAX->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
    	sBuf = "0";
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
    	sBuf = "";
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// �K�i�l����
    	sBuf = "1";
    } else if( Rdo_KIKAKU_SHITEI_KIJYUN->Checked ) {
    	sBuf = Nmb_KIKAKU_KIJYUN_MID->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
    	sBuf = Nmb_KIKAKU_KIJYUN_MAX->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
    	sBuf = Nmb_KIKAKU_KIJYUN_MIN->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
    	sBuf = "";
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// �K�i�l����
    	sBuf = "2";
    } else {
    	sBuf = "0";
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
    	sBuf = Edt_KIKAKU_STRING->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// �K�i�l����
    	sBuf = "3";
    }
    strcpy( tmpKSM11_12_DATA.KIKA_TYPE		,sBuf.c_str() );	// �K�i�^�C�v
    if( Rdo_KIKAKU_SYURUI_MINMAX->Checked )			sBuf = "1";
    else if( Rdo_KIKAKU_SYURUI_MAX->Checked )		sBuf = "2";
    else											sBuf = "3";
    strcpy( tmpKSM11_12_DATA.KIKA_KIND		,sBuf.c_str() );	// �K�i���
    sBuf = Nmb_KIKAKU_DOUBLE->Text;
    strcpy( tmpKSM11_12_DATA.KIKA_DECI		,sBuf.c_str() );	// �K�i�����_�ȉ�����
    sBuf = Nmb_N->Text;
    strcpy( tmpKSM11_12_DATA.SOKU_SU		,sBuf.c_str() );	// ����w��n��
    if( Rdo_SKTKMK_ON->Checked )			sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
    if( Rdo_TKBKMK_ON->Checked )			sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
    if( Rdo_MANMIN_PRT_ON->Checked )		sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
    if( Rdo_VALUE_NORMAL->Checked )			sBuf = "0";
    else if( Rdo_VALUE_KAKUDO->Checked )	sBuf = "1";
    else if( Rdo_VALUE_OK->Checked )		sBuf = "2";
    else									sBuf = "3";
    strcpy( tmpKSM11_12_DATA.VALUE_TYPE		,sBuf.c_str() );	// ����l�̕\��
    sBuf = Nmb_VALUE_DOUBLE->Text;
    strcpy( tmpKSM11_12_DATA.VALUE_DECI		,sBuf.c_str() );	// ����l�����_�ȉ�����
    sBuf = FormatDateTime("yyyymmdd",Date());
    //strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );		// �o�^��
    strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );		// �ύX��
    sBuf = FormatDateTime("hhmm",TDateTime::CurrentTime());
    //strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );		// �o�^����
    strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );		// �ύX����
    sBuf = IntToStr(USER_COD);
    strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );		// �X�V�ҁi�R�[�h�j
    sBuf = USER_NAM;
    strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );		// �X�V�ҁi���́j
    sBuf = IntToStr(PnlUPDCHR->Tag + 1);
    strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );		// �X�V��

    // �C���f�[�^��SGr_List�ɕ\��
    // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
    if( Rdo_TYPE_SYUKA->Checked ){
		// �f�[�^�C��
		if( UpdData("KSM11") == False )	return;

        sBuf = tmpKSM11_12_DATA.KOMK_NO;

        // �C���f�[�^��Grid�ɃZ�b�g���܂�
		GridLinePaste( SGr_List, ROWPOINT, "");

        // �C����̃f�[�^��I�����܂�
        SGr_List->SetFocus();
   		SGr_ListSelectCell( SGr_List, 1, SGr_List->Row, true);
        if( Rdo_List1_Order1->Checked ){
	    	// ���荀�ڃ}�X�^�[��
        } else if( Rdo_List1_Order2->Checked ){
	    	// ���荀�ږ��̏�
        	Rdo_List1_OrderClick( Rdo_List1_Order2 );
	        for( i = 1; i < SGr_List->RowCount; i++ ){
				if( SGr_List->Cells[13][i] == sBuf ){
                    SGr_List->Row = i;
		    		SGr_ListSelectCell( SGr_List, 1, i, true);
					break;
                }
			}
        } else {
	    	// ����@��E���荀�ږ��̏�
        	Rdo_List1_OrderClick( Rdo_List1_Order3 );
	        for( i = 1; i < SGr_List->RowCount; i++ ){
				if( SGr_List->Cells[13][i] == sBuf ){
                    SGr_List->Row = i;
		    		SGr_ListSelectCell( SGr_List, 1, i, true);
					break;
                }
			}
        }

	} else {
		// �f�[�^�C��
		if( UpdData("KSM12") == False )	return;

        sBuf = tmpKSM11_12_DATA.KOMK_NO;

        // �C���f�[�^��Grid�ɃZ�b�g���܂�
		GridLinePaste( SGr_List2, ROWPOINT, "");

        // �C����̃f�[�^��I�����܂�
    	SGr_List2->SetFocus();
    	SGr_ListSelectCell( SGr_List2, 1, SGr_List2->Row, true);
        if( Rdo_List2_Order1->Checked ){
	    	// ���荀�ڃ}�X�^�[��
        } else if( Rdo_List2_Order2->Checked ){
	    	// ���荀�ږ��̏�
        	Rdo_List2_OrderClick( Rdo_List2_Order2 );
	        for( i = 1; i < SGr_List2->RowCount; i++ ){
				if( SGr_List2->Cells[13][i] == sBuf ){
                    SGr_List2->Row = i;
		    		SGr_ListSelectCell( SGr_List2, 1, i, true);
					break;
                }
			}
        } else {
	    	// ����@��E���荀�ږ��̏�
        	Rdo_List2_OrderClick( Rdo_List2_Order3 );
	        for( i = 1; i < SGr_List2->RowCount; i++ ){
				if( SGr_List2->Cells[13][i] == sBuf ){
                    SGr_List2->Row = i;
		    		SGr_ListSelectCell( SGr_List2, 1, i, true);
					break;
                }
			}
        }
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // �f�[�^��ύX�����t���O
    DataSave = true;

    // �{�^���̏�����
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�O�F�폜�v�{�^�������������̏���
//
//  �@�\����
//    StringGrid�őI�����ꂽ�f�[�^���폜���܂�
//    �e�[�u���iKSM11,KSM12�j�̃��R�[�h���폜���܂�
//    StringGrid�̑I���s���폜���܂�
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
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
    int			i, k;
    AnsiString	sBuf;

    TButton *btn = (TButton *)Sender;

    if( !BtnF10->Enabled )    return;

    if( Rdo_TYPE_SYUKA->Checked && SGr_List->Cells[13][SGr_List->Row].ToIntDef(0) == 1){
        // �X�e�[�^�X���b�Z�[�W
    	MessageDlg("�폜�o���Ȃ����ڂł��B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    if( PnlUPDYMD->Tag == -1){
        // �X�e�[�^�X���b�Z�[�W
    	MessageDlg("�폜�Ώۂł͂���܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "�폜���ł��D�D�D���΂炭���҂��������B";
    SBr1->Update();

    // �f�[�^���o�b�t�@�Ɋi�[���܂��B
    sBuf = IntToStr(PnlUPDYMD->Tag);
    strcpy( tmpKSM11_12_DATA.KOMK_NO		,sBuf.c_str() );		// ����NO

    if( (btn->Name == "BtnF10" &&  Rdo_TYPE_SYUKA->Checked) ||
    	(btn->Name != "BtnF10" && !Rdo_TYPE_SYUKA->Checked) ){

    	// �I�������f�[�^���폜���܂�
    	if( DelData("KSM11") == False )	return;

        // �ǉ��f�[�^�̕\������蓯�����傫������\�����|�P���܂�
    	for( i = 1; i < SGr_List->RowCount - 1; i++) {
            if( SGr_List->Cells[14][i].ToIntDef(0) >= SGr_List->Cells[14][SGr_List->Row].ToIntDef(0) ){
				SGr_List->Cells[14][i] = IntToStr(SGr_List->Cells[14][i].ToIntDef(-1) - 1);
				SGr_List->Cells[29][i] = "1";		// �X�V�t���O��ON
        	}
    	}

        // �V�K�f�[�^�s�ȉ��̍s�����炵�܂�
    	for( i = SGr_List->Row; i < (SGr_List->RowCount - 1); i++) {
    		for( k = 1; k < SGr_List->ColCount; k++) {
				SGr_List->Cells[k][i] = SGr_List->Cells[k][i+1];
        	}
    	}

    	// ��s���炷
    	SGr_List->RowCount = SGr_List->RowCount - 1;
   		// �ŉ��s���N���A�[
   		for( k = 0; k < SGr_List->ColCount; k++) {
			SGr_List->Cells[k][SGr_List->RowCount - 1] = "";
   		}

        // �C���{�^������Ăяo�����ꍇ������i�o�׌������ڂƑf�ތ������ڂ̓���ւ��j�̂�
        // �Ăяo�����{�^���𔻒肵�Ă��܂��B
        if( btn->Name == "BtnF10" ){
    		// �V�����s��I��
    		if( SGr_List->RowCount == SGr_List->Row){
    		    SGr_List->Row = SGr_List->Row - 1;
    		}

    		// �V�����s��I��
    		SGr_List->SetFocus();
    		SGr_ListSelectCell(SGr_List,1,SGr_List->Row,true);
        }

	    // �f�[�^������\�����܂�
    	sBuf = SGr_List->RowCount-2;
    	LblListCnt->Caption = "�����F" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

    } else {

    	// �I�������f�[�^���폜���܂�
    	if( DelData("KSM12") == False )	return;

        // �ǉ��f�[�^�̕\������蓯�����傫������\�����|�P���܂�
    	for( i = 1; i < SGr_List2->RowCount - 1; i++) {
            if( SGr_List2->Cells[14][i].ToIntDef(0) >= SGr_List2->Cells[14][SGr_List2->Row].ToIntDef(0) ){
				SGr_List2->Cells[14][i] = IntToStr(SGr_List2->Cells[14][i].ToIntDef(-1) - 1);
				SGr_List2->Cells[29][i] = "1";		// �X�V�t���O��ON
        	}
    	}

        // �V�K�f�[�^�s�ȉ��̍s�����炵�܂�
    	for( i = SGr_List2->Row; i < (SGr_List2->RowCount - 1); i++) {
    		for( k = 1; k < SGr_List2->ColCount; k++) {
				SGr_List2->Cells[k][i] = SGr_List2->Cells[k][i+1];
        	}
    	}

    	// ��s���炷
    	SGr_List2->RowCount = SGr_List2->RowCount - 1;
   		// �ŉ��s���N���A�[
   		for( k = 0; k < SGr_List2->ColCount; k++) {
			SGr_List2->Cells[k][SGr_List2->RowCount - 1] = "";
   		}

        // �C���{�^������Ăяo�����ꍇ������i�o�׌������ڂƑf�ތ������ڂ̓���ւ��j�̂�
        // �Ăяo�����{�^���𔻒肵�Ă��܂��B
        if( btn->Name == "BtnF10" ){
    		// �V�����s��I��
    		if( SGr_List2->RowCount == SGr_List2->Row){
    		    SGr_List2->Row = SGr_List2->Row - 1;
    		}

    		// �V�����s��I��
    		SGr_List2->SetFocus();
    		SGr_ListSelectCell(SGr_List2,1,SGr_List2->Row,true);
        }

	    // �f�[�^������\�����܂�
    	sBuf = SGr_List2->RowCount-2;
    	LblListCnt2->Caption = "�����F" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // �f�[�^��ύX�����t���O
    DataSave = true;

    // �{�^���̏�����
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�P�F�ۑ��v�{�^�������������̏���
//
//  �@�\����
//    �X�V�̗L�����f�[�^���m��iCommit�j���܂�
//    �\�������ύX���ꂽ���ڂ��X�V���Ȃ����܂�
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
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{
    int		i;

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "�ۑ����ł��D�D�D���΂炭���҂��������B";
    SBr1->Update();

    // �ύX�C�}���C�폜���i���I�ɕۑ����C���݂̃g�����U�N�V�������I��
    if( Database1->InTransaction == True ){
        Database1->Commit();

    	// ���ёւ���ꂽ�\������ۑ����܂��B
    	for( i = 1; i < SGr_List->RowCount; i++) {
    		if( SGr_List->Cells[29][i] == "1" ){
                UpdData_ORDER_NO( "KSM11", SGr_List->Cells[13][i],SGr_List->Cells[14][i]);
        	}
    	}

    	// ���ёւ���ꂽ�\������ۑ����܂��B
    	for( i = 1; i < SGr_List2->RowCount; i++) {
    		if( SGr_List2->Cells[29][i] == "1" ){
                UpdData_ORDER_NO( "KSM12", SGr_List2->Cells[13][i],SGr_List2->Cells[14][i]);
        	}
    	}

        // �V�����g�����U�N�V�������J�n
        Database1->StartTransaction();
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // �f�[�^��ύX�����t���O
    DataSave = false;
    BtnF11->Enabled = false;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�Q�F�I���v�{�^�������������̏���
//
//  �@�\����
//    �X�V����Ă��邩�ǂ����m�F���A
//    �X�V����Ă���ꍇ�́u�e�P�P�F�ۑ��v���Ăяo��
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
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
     int nRet;
     if( DataSave == true )
     {
         nRet = MessageDlg("�ҏW����Ă��܂��B�ۑ����܂���?", mtConfirmation,
                TMsgDlgButtons() << mbYes << mbCancel << mbNo, 0);
         if(nRet == mrYes )
         {
              BtnF11Click(Sender);
              Close();
         }
         else if(nRet == mrCancel)
         {
         }
         else
         {
              DataSave = false;
              Close();
         }
     }
     else
     {
         Close();
     }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnDrawCell�C�x���g�F�O���b�h���̃Z����`�悷��K�v������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �O���b�h���̃Z���`����R���g���[�����܂�
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
void __fastcall TForm1::SGr_ListDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{

   AnsiString	sBuf, sValue;
   char 		cFormatBuf[20], c1[20], c2[10];
   long			iPos;

   TStringGrid *sg = (TStringGrid *)Sender;

   RECT r=RECT(Rect);

   //�Œ�Z���̔w�i�F���Z�b�g
   if(State.Contains(gdFixed))
       sg->Canvas->Brush->Color= sg->FixedColor;
   //�t�H�[�J�X�̂���Z���̔w�i�F���Z�b�g
   //else if(State.Contains(gdFocused)){
   //�I������Ă���Z���̔w�i�F���Z�b�g
   else if(State.Contains(gdSelected))
       sg->Canvas->Brush->Color= clHighlight;
   //���ʂ̃Z���̔w�i�F���Z�b�g
   else
       sg->Canvas->Brush->Color= sg->Color;

   //�w�i�F�ŏ���
   sg->Canvas->FillRect(Rect);

   //�Œ�Z���̗��̘g��`��
   if(sg->Ctl3D&&State.Contains(gdFixed))
       DrawEdge(sg->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);

   //�t�H�[�J�X�̂���Z���̕����F���Z�b�g
   if(State.Contains(gdFocused)){
//       SGr1->Canvas->Font->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlightText: SGr1->Font->Color;
//       //�t�H�[�J�X�g��`��
//       DrawFocusRect(SGr1->Canvas->Handle,&r);
	   //�I������Ă���Z���̕����F���Z�b�g
       //if(State.Contains(gdSelected))

       //�C���E�폜�s�\�f�[�^�̏ꍇ�̕����F���Z�b�g
       if( sg->Name == "SGr_List" && ACol > 0 && SGr_List->Cells[13][ARow].ToIntDef(0) == 1 )
           sg->Canvas->Font->Color = clRed;
       else
           sg->Canvas->Font->Color= clHighlightText;
   }
   //�I������Ă���Z���̕����F���Z�b�g
   else if(State.Contains(gdSelected))
       if( sg->Name == "SGr_List" && ACol > 0 && SGr_List->Cells[13][ARow].ToIntDef(0) == 1 )
           sg->Canvas->Font->Color = clRed;
       else
           sg->Canvas->Font->Color= clHighlightText;
   //�C���E�폜�s�\�f�[�^�̏ꍇ�̕����F���Z�b�g
   else if( sg->Name == "SGr_List" && ACol > 0 && sg->Cells[13][ARow].ToIntDef(0) == 1 )
       sg->Canvas->Font->Color = clRed;
   //���ʂ̃Z���̕����F���Z�b�g
   else
       sg->Canvas->Font->Color= sg->Font->Color;

   //�e�L�X�g�\���̈�̐ݒ�
   InflateRect(&r,-2,-2);

   if( ARow > 0 && ACol == 5 ){

        // �K�i�^�C�v���̕\��
        switch( sg->Cells[16][ARow].ToIntDef(0) ){
            case 1: // �͈͎w��

                    // �����_�ȉ������̃t�H�[�}�b�g������
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",sg->Cells[18][ARow].ToIntDef(0) );
            		strcat(c1,c2);

			        switch( sg->Cells[17][ARow].ToIntDef(0) ){
            			case 1: // �����������
                                sValue = sg->Cells[19][ARow];
			                    sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf = cFormatBuf;
                     			sBuf +=  "�`";
                                sValue = sg->Cells[20][ARow];
                     			sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf += cFormatBuf ;
			            		break;

            			case 2: // ����̂�
                                sValue = sg->Cells[20][ARow];
                     			sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf = cFormatBuf ;
                     			sBuf += "�ȉ�";
			            		break;
            			case 3: // �����̂�
                                sValue = sg->Cells[19][ARow];
                     			sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf = cFormatBuf ;
                     			sBuf += "�ȏ�";
			            		break;
                    }
					DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //����
            		break;

            case 2: // ��l�w��

                    // �����_�ȉ������̃t�H�[�}�b�g������
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",sg->Cells[18][ARow].ToIntDef(0) );
            		strcat(c1,c2);

                    sValue = sg->Cells[19][ARow];
                    sprintf(cFormatBuf, c1, sValue.ToDouble() );
                    sBuf = cFormatBuf ;
        			sg->Canvas->TextOut( r.left +  0, r.top + 0, sBuf );
                    iPos = sBuf.Length() * 8;

        			// �t�H���g�i���j�̐ݒ�
        			OrgFont = SelectObject( sg->Canvas->Handle, MyFont );

			        switch( sg->Cells[17][ARow].ToIntDef(0) ){
            			case 1: // �����������
                    			sValue = sg->Cells[20][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
                                sg->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
                     			sValue = sg->Cells[21][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						sg->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;

            			case 2: // ����̂�
			                    sValue = sg->Cells[20][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
			        			sg->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
			            		break;
            			case 3: // �����̂�
                     			sValue = sg->Cells[21][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						sg->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;
                    }

        			// ���̃t�H���g�ɖ߂��܂�
        			SelectObject( sg->Canvas->Handle, OrgFont );

                    break;

        	case 3: // ����
					DrawText(sg->Canvas->Handle,sg->Cells[22][ARow].c_str(),-1,&r,0); //����
                    break;
        }

   } else if( ARow > 0 && ACol == 6 ){
        // ����
		DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //�E��

   } else if( ARow > 0 && ACol == 7 ){
        // �l�\��
        switch( sg->Cells[ACol][ARow].ToIntDef(-1) ){
   			case 0: // �����E����(99.99)
                    if( sg->Cells[24][ARow].ToIntDef(0) > 0 ){
                    	sBuf = "9." + AnsiString::StringOfChar('9', sg->Cells[24][ARow].ToIntDef(0));
            		} else{
                    	sBuf = "9";
                    }
                    DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //����
            		break;
   			case 1: // �p�x(99�K99')
                    if( sg->Cells[24][ARow].ToIntDef(0) > 0 ){
	                    sBuf = "9��" + AnsiString::StringOfChar('9', sg->Cells[24][ARow].ToIntDef(0)) + "'";
            		} else{
                    	sBuf = "9��";
                    }
            		DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //����
            		break;
   			case 2: // ��(OK)�^��(NG)
            		DrawText(sg->Canvas->Handle,"��/��",-1,&r,0); //����
            		break;
   			case 3: // ����
            		DrawText(sg->Canvas->Handle,"����",-1,&r,0); //����
            		break;
       	}

   } else if( ARow > 0 && (ACol == 8 || ACol == 9) ){
        // ���荀�ڂ̗L���A���ʍ��ڂ̗L��
        switch( sg->Cells[ACol][ARow].ToIntDef(-1) ){
   			case 0: DrawText(sg->Canvas->Handle,"��",-1,&r,0); //����
            		break;
   			case 1: DrawText(sg->Canvas->Handle,"�L",-1,&r,0); //����
            		break;
       	}

   } else if( ARow > 0 && ACol == 10 ){
        // �X�V��
        sBuf = sg->Cells[10][ARow];
        if( sBuf.Length() == 8 ){
        	sBuf.Insert("/",5);
       		sBuf.Insert("/",8);
   			DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //����
        }

   } else{
		//�e�L�X�g�̕\��
		DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,0); //����
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //�E��
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER); //�����񂹁i�����j
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_VCENTER|DT_SINGLELINE); //�����񂹁i�����j
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_BOTTOM|DT_SINGLELINE); //����
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE); //����������Ƃ�������
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_WORDBREAK); //�����s�\��
   }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�[�^��ǉ����܂��B
//
//  �@�\����
//    �u�e�W�F�V�K�o�^�v���̃f�[�^�ǉ��iKSM11,KSM12�j����
//
//  �p�����^����
//    AnsiString sTBL_NM�F�ۑ���̃e�[�u�����iKSM11,KSM12�̂ǂ��炩�j
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::AddData(AnsiString sTBL_NM)
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf = "insert into " + sTBL_NM + "(";
    sBuf += " KOMK_NO, ORDER_NO, KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI,";
    sBuf += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, KIKA_STR,";
    sBuf += " SOKU_SU, SOKU_FLG, TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI,";
    sBuf += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT )";

    sBuf += " VALUES(";
	sBuf += AnsiString(tmpKSM11_12_DATA.KOMK_NO)	+  "," ;	// ����NO
	sBuf += AnsiString(tmpKSM11_12_DATA.ORDER_NO)	+  ",'";	// �\����
	sBuf += AnsiString(tmpKSM11_12_DATA.KOMK_NM)	+ "','";	// ���荀�ږ��́i���{��j
	sBuf += AnsiString(tmpKSM11_12_DATA.KOMK_ENG)	+ "','";	// ���荀�ږ��́i�p��j
	sBuf += 										  "','";	// ���荀�ڃT�u���́i���{��j
	sBuf += 										  "'," ;	// ���荀�ڃT�u���́i�p��j
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKI_NO)	+  ",'";	// ����@��NO
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKI_NM)	+ "','";	// ����@�햼��
	sBuf += AnsiString(tmpKSM11_12_DATA.TANI)		+ "'," ;	// �P��
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_TYPE)	+  "," ;	// �K�i�^�C�v
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_KIND)	+  "," ;	// �K�i���
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_DECI)	+  "," ;	// �K�i�����_�ȉ�����
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_NUM1)	+  "," ;	// �K�i�l�P
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_NUM2)	+  "," ;	// �K�i�l�Q
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_NUM3)	+  ",'";	// �K�i�l�R
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_STR)	+ "'," ;	// �K�i�l����
	sBuf += AnsiString(tmpKSM11_12_DATA.SOKU_SU)	+  "," ;	// ����w��n��
	sBuf += AnsiString(tmpKSM11_12_DATA.SOKU_FLG)	+  "," ;	// ���荀�ڂ̗L��
	sBuf += AnsiString(tmpKSM11_12_DATA.TOKU_FLG)	+  "," ;	// ���ʍ��ڂ̗L��
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_PRT)	+  "," ;	// ��������l�̈��
	sBuf += AnsiString(tmpKSM11_12_DATA.VALUE_TYPE)	+  "," ;	// ����l�\��
	sBuf += AnsiString(tmpKSM11_12_DATA.VALUE_DECI)	+  ",'";	// ����l�����_�ȉ�����
	sBuf += AnsiString(tmpKSM11_12_DATA.ADDYMD)		+ "','";	// �o�^��
	sBuf += AnsiString(tmpKSM11_12_DATA.ADDTIM)		+ "','";	// �o�^����
	sBuf += AnsiString(tmpKSM11_12_DATA.UPDYMD)		+ "','";	// �ύX��
	sBuf += AnsiString(tmpKSM11_12_DATA.UPDTIM)		+ "'," ;	// �ύX����
	sBuf += AnsiString(tmpKSM11_12_DATA.UPDCHR)		+  "," ;	// �X�V��
	sBuf += AnsiString(tmpKSM11_12_DATA.UPDCNT)		+  ")" ;	// �X�V��

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }

    return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�[�^���C�����܂��B
//
//  �@�\����
//    �u�e�X�F�C���v���̃f�[�^�X�V�iKSM21�j����
//
//  �p�����^����
//    AnsiString sTBL_NM�F�ۑ���̃e�[�u�����iKSM11,KSM12�̂ǂ��炩�j
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::UpdData(AnsiString sTBL_NM)
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf  = "update " + sTBL_NM + " set";
	sBuf += " KOMK_NM='"	+ AnsiString(tmpKSM11_12_DATA.KOMK_NM)		+ "',";	// ���荀�ږ��́i���{��j
	sBuf += " KOMK_ENG='"	+ AnsiString(tmpKSM11_12_DATA.KOMK_ENG)		+ "',";	// ���荀�ږ��́i�p��j
	sBuf += " KOMK_SUB='',"		;												// ���荀�ڃT�u���́i���{��j
	sBuf += " KOMK_SUB_ENG='',"	;												// ���荀�ڃT�u���́i�p��j
	sBuf += " KIKI_NO="		+ AnsiString(tmpKSM11_12_DATA.KIKI_NO)		+  ",";	// ����@��NO
	sBuf += " KIKI_NM='"	+ AnsiString(tmpKSM11_12_DATA.KIKI_NM)		+ "',";	// ����@�햼��
	sBuf += " TANI='"		+ AnsiString(tmpKSM11_12_DATA.TANI)			+ "',";	// �P��
	sBuf += " KIKA_TYPE="	+ AnsiString(tmpKSM11_12_DATA.KIKA_TYPE)	+  ",";	// �K�i�^�C�v
	sBuf += " KIKA_KIND="	+ AnsiString(tmpKSM11_12_DATA.KIKA_KIND)	+  ",";	// �K�i���
	sBuf += " KIKA_DECI="	+ AnsiString(tmpKSM11_12_DATA.KIKA_DECI)	+  ",";	// �K�i�����_�ȉ�����
	sBuf += " KIKA_NUM1="	+ AnsiString(tmpKSM11_12_DATA.KIKA_NUM1)	+  ",";	// �K�i�l�P
	sBuf += " KIKA_NUM2="	+ AnsiString(tmpKSM11_12_DATA.KIKA_NUM2)	+  ",";	// �K�i�l�Q
	sBuf += " KIKA_NUM3="	+ AnsiString(tmpKSM11_12_DATA.KIKA_NUM3)	+  ",";	// �K�i�l�R
	sBuf += " KIKA_STR='"	+ AnsiString(tmpKSM11_12_DATA.KIKA_STR)		+ "',";	// �K�i�l����
	sBuf += " SOKU_SU="		+ AnsiString(tmpKSM11_12_DATA.SOKU_SU)		+  ",";	// ����w��n��
	sBuf += " SOKU_FLG="	+ AnsiString(tmpKSM11_12_DATA.SOKU_FLG)		+  ",";	// ���荀�ڂ̗L��
	sBuf += " TOKU_FLG="	+ AnsiString(tmpKSM11_12_DATA.TOKU_FLG)		+  ",";	// ���ʍ��ڂ̗L��
	sBuf += " KIKA_PRT="	+ AnsiString(tmpKSM11_12_DATA.KIKA_PRT)		+  ",";	// ��������l�̈��
	sBuf += " VALUE_TYPE="	+ AnsiString(tmpKSM11_12_DATA.VALUE_TYPE)	+  ",";	// ����l�\��
	sBuf += " VALUE_DECI="	+ AnsiString(tmpKSM11_12_DATA.VALUE_DECI)	+  ",";	// ����l�����_�ȉ�����
	sBuf += " UPDYMD='"		+ AnsiString(tmpKSM11_12_DATA.UPDYMD)		+ "',";	// �ύX��
	sBuf += " UPDTIM='"		+ AnsiString(tmpKSM11_12_DATA.UPDTIM)		+ "',";	// �ύX����
	sBuf += " UPDCHR="		+ AnsiString(tmpKSM11_12_DATA.UPDCHR)		+  ",";	// �X�V��
	sBuf += " UPDCNT="		+ AnsiString(tmpKSM11_12_DATA.UPDCNT)			  ;	// �X�V��
    sBuf += " WHERE KOMK_NO="+ AnsiString(tmpKSM11_12_DATA.KOMK_NO)			  ; // ����NO

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }

    return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�[�^���C�����܂��B�i�\�����̂݁j
//
//  �@�\����
//    �u�e�P�P�F�ۑ��v���̕\�����X�V�iKSM21�j����
//
//  �p�����^����
//    AnsiString sTBL_NM�F�ۑ���̃e�[�u�����iKSM11,KSM12�̂ǂ��炩�j
//    AnsiString sKMK_NO�F�C���Ώۂ̍���NO
//    AnsiString sORDER_NO�F�V�����\����NO
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::UpdData_ORDER_NO(AnsiString sTBL_NM, AnsiString sKMK_NO, AnsiString sORDER_NO)
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf  = "update " + sTBL_NM + " set";
    sBuf += " ORDER_NO="		+ Trim(sORDER_NO)	  ;	//�\����
    sBuf += " WHERE KOMK_NO="	+ Trim(sKMK_NO)		  ; //����NO

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }

    return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�[�^���폜���܂��B
//
//  �@�\����
//    �u�e�P�O�F�폜�v���̃f�[�^�폜�iKSM21�j����
//
//  �p�����^����
//    AnsiString sTBL_NM�F�ۑ���̃e�[�u�����iKSM11,KSM12�̂ǂ��炩�j
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::DelData(AnsiString sTBL_NM)
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf = "select * from " + sTBL_NM;
    sBuf += " WHERE KOMK_NO="+ AnsiString(tmpKSM11_12_DATA.KOMK_NO)  ; //����NO

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->Open();
        Query1->Active = true;
        if( Query1->Eof == True &&  Query1->Bof == True ) {
            SBr1->Panels->Items[0]->Text = "�Y���̃f�[�^��������܂���B�폜�ł��܂���ł����B";
            SBr1->Update();
            return(False);
        }
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf = "DELETE from " + sTBL_NM;
    sBuf += " WHERE KOMK_NO="+ AnsiString(tmpKSM11_12_DATA.KOMK_NO)		  ; //����NO

    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    return(True);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnResize�C�x���g	�F�R���g���[���̃T�C�Y���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    Panel�̃T�C�Y�ɍ��킹��StringGrid�̃T�C�Y���ύX���܂�
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
void __fastcall TForm1::Pnl_ListResize(TObject *Sender)
{
    int iBMarg;

    // �e���x�����猩���e�R���g���[���̉��[�]��
    iBMarg = 6;


    // �������X�g
	if( PgCtr_List->Top < Pnl_List->Height &&
        Pnl_List->Height - PgCtr_List->Top - iBMarg > 0 ){
		PgCtr_List->Height = Pnl_List->Height - PgCtr_List->Top - iBMarg;
	} else{
		PgCtr_List->Height = 0;
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
void __fastcall TForm1::SGr_ListKeyPress(TObject *Sender, char &Key)
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
//    OnClick�C�x���g	�F�u��ֈړ��v�{�^�������������̏���
//
//  �@�\����
//    StringGrid�őI�����ꂽ�s��1��̍s�Ɠ���ւ��܂��B
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
void __fastcall TForm1::Btn_UpClick(TObject *Sender)
{
    int			i, k;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;
    TStringGrid *sg;

	TBitBtn		*btn = (TBitBtn *)Sender;
    if( btn->Name == "Btn_UP1" ){
	    sg = dynamic_cast<TStringGrid*>(SGr_List);
    } else {
	    sg = dynamic_cast<TStringGrid*>(SGr_List2);
    }

    iChgRow1 = sg->Selection.Top;
    iChgRow2 = sg->Selection.Top - 1;
    iChgRow3 = sg->Selection.Bottom;

    if( iChgRow1 <= 1) return;
    if( iChgRow1 >= sg->RowCount - 1) return;

    if( iChgRow3 >= sg->RowCount - 1)
    	iChgRow3 = sg->Selection.Bottom = sg->RowCount - 2;

    // ���\����Cells[14]�͓���ւ������ɂ��̑��̍��ڂ����ւ��A�X�V�t���O(Cells[29])��ON�ɂ��܂��B

    // ����ւ���̃f�[�^���o�b�N�A�b�v
	sBuf = sg->Cells[1][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_NM	,sBuf.c_str() );	//���荀�ځi���{��j
	sBuf = sg->Cells[2][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_ENG	,sBuf.c_str() );	//���荀�ځi�p��j
	sBuf = sg->Cells[3][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKI_NM	,sBuf.c_str() );	//����@�햼��
	sBuf = sg->Cells[4][iChgRow2];
    strcpy( tmpKSM11_12_DATA.TANI		,sBuf.c_str() );	//�P��
	sBuf = sg->Cells[6][iChgRow2];
    strcpy( tmpKSM11_12_DATA.SOKU_SU	,sBuf.c_str() );	//�����i��{�j
	sBuf = sg->Cells[7][iChgRow2];
    strcpy( tmpKSM11_12_DATA.VALUE_TYPE	,sBuf.c_str() );	//�l�\��
	sBuf = sg->Cells[8][iChgRow2];
    strcpy( tmpKSM11_12_DATA.SOKU_FLG	,sBuf.c_str() );	//���荀�ڂ̗L��
	sBuf = sg->Cells[9][iChgRow2];
    strcpy( tmpKSM11_12_DATA.TOKU_FLG	,sBuf.c_str() );	//���ʍ��ڂ̗L��
	sBuf = sg->Cells[10][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );	//�ύX��
	sBuf = sg->Cells[12][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );	//�X�V�ҁi�S���҃R�[�h�j
	sBuf = sg->Cells[11][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );	//�X�V�ҁi���́j
	sBuf = sg->Cells[13][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_NO	,sBuf.c_str() );	//����NO
	sBuf = sg->Cells[15][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKI_NO	,sBuf.c_str() );	//����@��NO
	sBuf = sg->Cells[16][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_TYPE	,sBuf.c_str() );	//�K�i�^�C�v
	sBuf = sg->Cells[17][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_KIND	,sBuf.c_str() );	//�K�i���
	sBuf = sg->Cells[18][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_DECI	,sBuf.c_str() );	//�K�i�����_�ȉ�����
	sBuf = sg->Cells[19][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	//�K�i�l�P
	sBuf = sg->Cells[20][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	//�K�i�l�Q
	sBuf = sg->Cells[21][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	//�K�i�l�R
	sBuf = sg->Cells[22][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	//�K�i����
	sBuf = sg->Cells[23][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_PRT	,sBuf.c_str() );	//��������l�̈��
	sBuf = sg->Cells[24][iChgRow2];
    strcpy( tmpKSM11_12_DATA.VALUE_DECI	,sBuf.c_str() );	//����l�����_�ȉ�����
	sBuf = sg->Cells[25][iChgRow2];
    strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );	//�o�^��
	sBuf = sg->Cells[26][iChgRow2];
    strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );	//�o�^����
	sBuf = sg->Cells[27][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );	//�X�V����
	sBuf = sg->Cells[28][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );	//�X�V��

	// �㉺�����ւ��܂�
    for( i = iChgRow2; i < iChgRow3; i++ ) {
    	for( k = 1; k < sg->ColCount; k++ ) {
            if( k == 14 ){
                // �\�����́A����ւ����Ȃ�
    			// sg->Cells[k][i] = sg->Cells[k][i + 1];
            } else if( k == 29 ){
                // �X�V�t���O�̐ݒ�
				sg->Cells[k][i] = "1";
        	} else {
				sg->Cells[k][i] = sg->Cells[k][i + 1];
            }
		}
    }

    // �o�b�N�A�b�v�����f�[�^��߂��܂�
	sg->Cells[1][iChgRow3] = tmpKSM11_12_DATA.KOMK_NM	;	//���荀�ځi���{��j
	sg->Cells[2][iChgRow3] = tmpKSM11_12_DATA.KOMK_ENG	;	//���荀�ځi�p��j
	sg->Cells[3][iChgRow3] = tmpKSM11_12_DATA.KIKI_NM	;	//����@�햼��
	sg->Cells[4][iChgRow3] = tmpKSM11_12_DATA.TANI		;	//�P��
	sg->Cells[5][iChgRow3] = ""							;	//�K�i�i��{�j�@���ĕ`�悷��ׂɕK�v�ł��B
	sg->Cells[6][iChgRow3] = tmpKSM11_12_DATA.SOKU_SU	;	//�����i��{�j
	sg->Cells[7][iChgRow3] = tmpKSM11_12_DATA.VALUE_TYPE;	//�l�\��
	sg->Cells[8][iChgRow3] = tmpKSM11_12_DATA.SOKU_FLG	;	//���荀�ڂ̗L��
	sg->Cells[9][iChgRow3] = tmpKSM11_12_DATA.TOKU_FLG	;	//���ʍ��ڂ̗L��
	sg->Cells[10][iChgRow3] = tmpKSM11_12_DATA.UPDYMD	;	//�ύX��
	sg->Cells[11][iChgRow3] = tmpKSM11_12_DATA.UPDNAM	;	//�X�V�ҁi���́j
	sg->Cells[12][iChgRow3] = tmpKSM11_12_DATA.UPDCHR	;	//�X�V�ҁi�S���҃R�[�h�j
	sg->Cells[13][iChgRow3] = tmpKSM11_12_DATA.KOMK_NO	;	//����NO
	sg->Cells[15][iChgRow3] = tmpKSM11_12_DATA.KIKI_NO	;	//����@��NO
	sg->Cells[16][iChgRow3] = tmpKSM11_12_DATA.KIKA_TYPE;	//�K�i�^�C�v
	sg->Cells[17][iChgRow3] = tmpKSM11_12_DATA.KIKA_KIND;	//�K�i���
	sg->Cells[18][iChgRow3] = tmpKSM11_12_DATA.KIKA_DECI;	//�K�i�����_�ȉ�����
	sg->Cells[19][iChgRow3] = tmpKSM11_12_DATA.KIKA_NUM1;	//�K�i�l�P
	sg->Cells[20][iChgRow3] = tmpKSM11_12_DATA.KIKA_NUM2;	//�K�i�l�Q
	sg->Cells[21][iChgRow3] = tmpKSM11_12_DATA.KIKA_NUM3;	//�K�i�l�R
	sg->Cells[22][iChgRow3] = tmpKSM11_12_DATA.KIKA_STR	;	//�K�i����
	sg->Cells[23][iChgRow3] = tmpKSM11_12_DATA.KIKA_PRT	;	//��������l�̈��
	sg->Cells[24][iChgRow3] = tmpKSM11_12_DATA.VALUE_DECI;	//����l�����_�ȉ�����
	sg->Cells[25][iChgRow3] = tmpKSM11_12_DATA.ADDYMD	;	//�o�^��
	sg->Cells[26][iChgRow3] = tmpKSM11_12_DATA.ADDTIM	;	//�o�^����
	sg->Cells[27][iChgRow3] = tmpKSM11_12_DATA.UPDTIM	;	//�X�V����
	sg->Cells[28][iChgRow3] = tmpKSM11_12_DATA.UPDCNT	;	//�X�V��
	sg->Cells[29][iChgRow3] = "1"						;	//�X�V�t���O�̐ݒ�

    // �I���J�[�\���������ɏ�Ɉړ����܂�
    sg->Row--;
	myRect.Left		= sg->Selection.Left;
	myRect.Top		= iChgRow1 - 1;
	myRect.Right	= sg->Selection.Right;
	myRect.Bottom	= iChgRow3 - 1;
    sg->Selection	= myRect;
    SGr_ListSelectCell(sg,1,sg->Row,true);

    // �f�[�^��ύX�����t���O
    DataSave = true;
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u���ֈړ��v�{�^�������������̏���
//
//  �@�\����
//    StringGrid�őI�����ꂽ�s��1���̍s�Ɠ���ւ��܂��B
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
void __fastcall TForm1::Btn_DownClick(TObject *Sender)
{
    int			i, k;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;
    TStringGrid *sg;

	TBitBtn		*btn = (TBitBtn *)Sender;
    if( btn->Name == "Btn_DOWN1" ){
	    sg = dynamic_cast<TStringGrid*>(SGr_List);
    } else {
	    sg = dynamic_cast<TStringGrid*>(SGr_List2);
    }

    iChgRow1 = sg->Selection.Top;
    iChgRow2 = sg->Selection.Bottom + 1;
    iChgRow3 = sg->Selection.Bottom;

    if( iChgRow2 >= sg->RowCount - 1) return;

    // ���\�����͓���ւ������ɂ��̑��̍��ڂ����ւ��A�X�V�t���O(Cells[14])��ON�ɂ��܂��B

    // ���\����Cells[14]�͓���ւ������ɂ��̑��̍��ڂ����ւ��A�X�V�t���O(Cells[29])��ON�ɂ��܂��B

    // ����ւ���̃f�[�^���o�b�N�A�b�v
	sBuf = sg->Cells[1][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_NM	,sBuf.c_str() );	//���荀�ځi���{��j
	sBuf = sg->Cells[2][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_ENG	,sBuf.c_str() );	//���荀�ځi�p��j
	sBuf = sg->Cells[3][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKI_NM	,sBuf.c_str() );	//����@�햼��
	sBuf = sg->Cells[4][iChgRow2];
    strcpy( tmpKSM11_12_DATA.TANI		,sBuf.c_str() );	//�P��
	sBuf = sg->Cells[6][iChgRow2];
    strcpy( tmpKSM11_12_DATA.SOKU_SU	,sBuf.c_str() );	//�����i��{�j
	sBuf = sg->Cells[7][iChgRow2];
    strcpy( tmpKSM11_12_DATA.VALUE_TYPE	,sBuf.c_str() );	//�l�\��
	sBuf = sg->Cells[8][iChgRow2];
    strcpy( tmpKSM11_12_DATA.SOKU_FLG	,sBuf.c_str() );	//���荀�ڂ̗L��
	sBuf = sg->Cells[9][iChgRow2];
    strcpy( tmpKSM11_12_DATA.TOKU_FLG	,sBuf.c_str() );	//���ʍ��ڂ̗L��
	sBuf = sg->Cells[10][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );	//�ύX��
	sBuf = sg->Cells[12][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );	//�X�V�ҁi�S���҃R�[�h�j
	sBuf = sg->Cells[11][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );	//�X�V�ҁi���́j
	sBuf = sg->Cells[13][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_NO	,sBuf.c_str() );	//����NO
	sBuf = sg->Cells[15][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKI_NO	,sBuf.c_str() );	//����@��NO
	sBuf = sg->Cells[16][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_TYPE	,sBuf.c_str() );	//�K�i�^�C�v
	sBuf = sg->Cells[17][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_KIND	,sBuf.c_str() );	//�K�i���
	sBuf = sg->Cells[18][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_DECI	,sBuf.c_str() );	//�K�i�����_�ȉ�����
	sBuf = sg->Cells[19][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	//�K�i�l�P
	sBuf = sg->Cells[20][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	//�K�i�l�Q
	sBuf = sg->Cells[21][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	//�K�i�l�R
	sBuf = sg->Cells[22][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	//�K�i����
	sBuf = sg->Cells[23][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_PRT	,sBuf.c_str() );	//��������l�̈��
	sBuf = sg->Cells[24][iChgRow2];
    strcpy( tmpKSM11_12_DATA.VALUE_DECI	,sBuf.c_str() );	//����l�����_�ȉ�����
	sBuf = sg->Cells[25][iChgRow2];
    strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );	//�o�^��
	sBuf = sg->Cells[26][iChgRow2];
    strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );	//�o�^����
	sBuf = sg->Cells[27][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );	//�X�V����
	sBuf = sg->Cells[28][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );	//�X�V��

	// �㉺�����ւ��܂�
    for( i=iChgRow2; i>iChgRow1 ; i-- ) {
    	for( k = 1; k < sg->ColCount; k++ ) {
            if( k == 14 ){
                // �\�����́A����ւ����Ȃ�
    			// sg->Cells[k][i] = sg->Cells[k][i - 1];
            } else if( k == 29 ){
                // �X�V�t���O�̐ݒ�
				sg->Cells[k][i] = "1";
        	} else {
				sg->Cells[k][i] = sg->Cells[k][i - 1];
            }
		}
    }

    // �o�b�N�A�b�v�����f�[�^��߂��܂�
	sg->Cells[1][iChgRow1] = tmpKSM11_12_DATA.KOMK_NM	;	//���荀�ځi���{��j
	sg->Cells[2][iChgRow1] = tmpKSM11_12_DATA.KOMK_ENG	;	//���荀�ځi�p��j
	sg->Cells[3][iChgRow1] = tmpKSM11_12_DATA.KIKI_NM	;	//����@�햼��
	sg->Cells[4][iChgRow1] = tmpKSM11_12_DATA.TANI		;	//�P��
	sg->Cells[5][iChgRow1] = ""							;	//�K�i�i��{�j�@���ĕ`�悷��ׂɕK�v�ł��B
	sg->Cells[6][iChgRow1] = tmpKSM11_12_DATA.SOKU_SU	;	//�����i��{�j
	sg->Cells[7][iChgRow1] = tmpKSM11_12_DATA.VALUE_TYPE;	//�l�\��
	sg->Cells[8][iChgRow1] = tmpKSM11_12_DATA.SOKU_FLG	;	//���荀�ڂ̗L��
	sg->Cells[9][iChgRow1] = tmpKSM11_12_DATA.TOKU_FLG	;	//���ʍ��ڂ̗L��
	sg->Cells[10][iChgRow1] = tmpKSM11_12_DATA.UPDYMD	;	//�ύX��
	sg->Cells[11][iChgRow1] = tmpKSM11_12_DATA.UPDNAM	;	//�X�V�ҁi���́j
	sg->Cells[12][iChgRow1] = tmpKSM11_12_DATA.UPDCHR	;	//�X�V�ҁi�S���҃R�[�h�j
	sg->Cells[13][iChgRow1] = tmpKSM11_12_DATA.KOMK_NO	;	//����NO
	sg->Cells[15][iChgRow1] = tmpKSM11_12_DATA.KIKI_NO	;	//����@��NO
	sg->Cells[16][iChgRow1] = tmpKSM11_12_DATA.KIKA_TYPE;	//�K�i�^�C�v
	sg->Cells[17][iChgRow1] = tmpKSM11_12_DATA.KIKA_KIND;	//�K�i���
	sg->Cells[18][iChgRow1] = tmpKSM11_12_DATA.KIKA_DECI;	//�K�i�����_�ȉ�����
	sg->Cells[19][iChgRow1] = tmpKSM11_12_DATA.KIKA_NUM1;	//�K�i�l�P
	sg->Cells[20][iChgRow1] = tmpKSM11_12_DATA.KIKA_NUM2;	//�K�i�l�Q
	sg->Cells[21][iChgRow1] = tmpKSM11_12_DATA.KIKA_NUM3;	//�K�i�l�R
	sg->Cells[22][iChgRow1] = tmpKSM11_12_DATA.KIKA_STR	;	//�K�i����
	sg->Cells[23][iChgRow1] = tmpKSM11_12_DATA.KIKA_PRT	;	//��������l�̈��
	sg->Cells[24][iChgRow1] = tmpKSM11_12_DATA.VALUE_DECI;	//����l�����_�ȉ�����
	sg->Cells[25][iChgRow1] = tmpKSM11_12_DATA.ADDYMD	;	//�o�^��
	sg->Cells[26][iChgRow1] = tmpKSM11_12_DATA.ADDTIM	;	//�o�^����
	sg->Cells[27][iChgRow1] = tmpKSM11_12_DATA.UPDTIM	;	//�X�V����
	sg->Cells[28][iChgRow1] = tmpKSM11_12_DATA.UPDCNT	;	//�X�V��
	sg->Cells[29][iChgRow1] = "1"						;	//�X�V�t���O�̐ݒ�

    // �I���J�[�\���������ɉ��Ɉړ����܂�
    sg->Row++;
	myRect.Left		= sg->Selection.Left;
	myRect.Top		= iChgRow1 + 1;
	myRect.Right	= sg->Selection.Right;
	myRect.Bottom	= iChgRow3 + 1;
    sg->Selection	= myRect;
    SGr_ListSelectCell(sg,1,sg->Row,true);

    // �f�[�^��ύX�����t���O
    DataSave = true;
    BtnF11->Enabled = true;

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
void __fastcall TForm1::SGr_ListClick(TObject *Sender)
{
    TStringGrid* sg = dynamic_cast<TStringGrid*>(Sender);

   	iRowSelTop    = sg->Selection.Top;
   	iRowSelBottom = sg->Selection.Bottom;
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
void __fastcall TForm1::SGr_ListRowMoved(TObject *Sender, int FromIndex,
      int ToIndex)
{

    int         i;
    int			k;
    int			m;
	int			CopyCnt;
    int			iStart;
    int			iEnd;
    int			iSkip;
    HANDLE  	hMemCopy;
    AnsiString  sBuf;
    KSM11_12_DATA  *pKSM11_12_DATA;
	TGridRect	myRect;
    TStringGrid* sg = dynamic_cast<TStringGrid*>(Sender);


    // �͈͑I���������̂Ǝ��ۂɈړ��������ꂽ�s�̎w��ʒu���قȂ鎞�́A�G���[
    if( FromIndex < iRowSelTop || FromIndex > iRowSelBottom ){
        RowExchange(sg, FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�I��͈͂�����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // �͈͑I�������ړ��悪�A���͈̔͑I����ւ̈ړ��̎��́A�G���[
    if( ToIndex >= iRowSelTop && ToIndex <= iRowSelBottom ){
        RowExchange(sg, FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�ړ��悪����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // �ŉ��s�̉��ֈړ��̎��́A�G���[
    if( ToIndex >= sg->RowCount - 1 ){
        RowExchange(sg, FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�ړ��悪����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // �͈͑I���������̂ɍŉ��s���܂ގ��́A�G���[
    if( sg->RowCount - 1 <= iRowSelBottom ){
        RowExchange(sg, FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�I��͈͂�����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    if( FromIndex < ToIndex ){
        iStart = iRowSelTop;
        iEnd   = ToIndex;

		// �\���������ւ��܂�
    	sBuf = sg->Cells[14][ToIndex];
		for( i = ToIndex; i > FromIndex; i-- ){
			sg->Cells[14][i] = sg->Cells[14][i-1];
    	}
    	sg->Cells[14][FromIndex] = sBuf;
    }
    else {
        iStart = ToIndex;
        iEnd   = iRowSelBottom;

		// �\���������ւ��܂�
        sBuf = sg->Cells[14][ToIndex];
		for( i = ToIndex; i < FromIndex; i++ ){
			sg->Cells[14][i] = sg->Cells[14][i+1];
    	}
    	sg->Cells[14][FromIndex] = sBuf;
    }

	// �sNo�����ɖ߂��܂�
	for( i = iStart; i <= iEnd; i++ ){
		sBuf = i ;
		if( i < sg->RowCount - 1 ){
			sg->Cells[0][i] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
   	    	sg->Cells[29][i] = "1";						// �X�V�t���OON
		}
        else{
			sg->Cells[0][i] = "";
   	    	sg->Cells[29][i] = "";
        }
    }

    // �R�s�[�̌����m�ۂ��܂�
    CopyCnt = iRowSelBottom - iRowSelTop;

    // �������̊m��
    hMemCopy = GlobalAlloc( GHND, sizeof(struct KSM11_12_DATA) * CopyCnt );
    if( hMemCopy == NULL ){
        SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pKSM11_12_DATA = (struct KSM11_12_DATA *)GlobalLock(hMemCopy);
    if( hMemCopy == NULL ){
        SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
        SBr1->Update();
        Beep();
        return;
    }

    if( FromIndex < ToIndex ){

	    // �I������Ă���͈͂��������Ɋi�[���܂�
    	for( i=iRowSelTop, k=0; i<iRowSelBottom; i++, k++ ) {
			sBuf = sg->Cells[1][i];
			strcpy( pKSM11_12_DATA[k].KOMK_NM		,sBuf.c_str() );	//���荀�ځi���{��j
			sBuf = sg->Cells[2][i];
			strcpy( pKSM11_12_DATA[k].KOMK_ENG		,sBuf.c_str() );	//���荀�ځi�p��j
			sBuf = sg->Cells[3][i];
			strcpy( pKSM11_12_DATA[k].KIKI_NM		,sBuf.c_str() );	//����@�햼��
			sBuf = sg->Cells[4][i];
			strcpy( pKSM11_12_DATA[k].TANI			,sBuf.c_str() );	//�P��
			sBuf = sg->Cells[6][i];
			strcpy( pKSM11_12_DATA[k].SOKU_SU		,sBuf.c_str() );	//�����i��{�j
			sBuf = sg->Cells[7][i];
			strcpy( pKSM11_12_DATA[k].VALUE_TYPE	,sBuf.c_str() );	//�l�\��
			sBuf = sg->Cells[8][i];
			strcpy( pKSM11_12_DATA[k].SOKU_FLG		,sBuf.c_str() );	//���荀�ڂ̗L��
			sBuf = sg->Cells[9][i];
			strcpy( pKSM11_12_DATA[k].TOKU_FLG		,sBuf.c_str() );	//���ʍ��ڂ̗L��
			sBuf = sg->Cells[10][i];
			strcpy( pKSM11_12_DATA[k].UPDYMD		,sBuf.c_str() );	//�ύX��
			sBuf = sg->Cells[12][i];
			strcpy( pKSM11_12_DATA[k].UPDCHR		,sBuf.c_str() );	//�X�V�ҁi�S���҃R�[�h�j
			sBuf = sg->Cells[11][i];
			strcpy( pKSM11_12_DATA[k].UPDNAM		,sBuf.c_str() );	//�X�V�ҁi���́j
			sBuf = sg->Cells[13][i];
			strcpy( pKSM11_12_DATA[k].KOMK_NO		,sBuf.c_str() );	//����NO
			sBuf = sg->Cells[15][i];
			strcpy( pKSM11_12_DATA[k].KIKI_NO		,sBuf.c_str() );	//����@��NO
			sBuf = sg->Cells[16][i];
			strcpy( pKSM11_12_DATA[k].KIKA_TYPE		,sBuf.c_str() );	//�K�i�^�C�v
			sBuf = sg->Cells[17][i];
			strcpy( pKSM11_12_DATA[k].KIKA_KIND		,sBuf.c_str() );	//�K�i���
			sBuf = sg->Cells[18][i];
			strcpy( pKSM11_12_DATA[k].KIKA_DECI		,sBuf.c_str() );	//�K�i�����_�ȉ�����
			sBuf = sg->Cells[19][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM1		,sBuf.c_str() );	//�K�i�l�P
			sBuf = sg->Cells[20][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM2		,sBuf.c_str() );	//�K�i�l�Q
			sBuf = sg->Cells[21][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM3		,sBuf.c_str() );	//�K�i�l�R
			sBuf = sg->Cells[22][i];
			strcpy( pKSM11_12_DATA[k].KIKA_STR		,sBuf.c_str() );	//�K�i����
			sBuf = sg->Cells[23][i];
			strcpy( pKSM11_12_DATA[k].KIKA_PRT		,sBuf.c_str() );	//��������l�̈��
			sBuf = sg->Cells[24][i];
			strcpy( pKSM11_12_DATA[k].VALUE_DECI	,sBuf.c_str() );	//����l�����_�ȉ�����
			sBuf = sg->Cells[25][i];
			strcpy( pKSM11_12_DATA[k].ADDYMD		,sBuf.c_str() );	//�o�^��
			sBuf = sg->Cells[26][i];
			strcpy( pKSM11_12_DATA[k].ADDTIM		,sBuf.c_str() );	//�o�^����
			sBuf = sg->Cells[27][i];
			strcpy( pKSM11_12_DATA[k].UPDTIM		,sBuf.c_str() );	//�X�V����
			sBuf = sg->Cells[28][i];
			strcpy( pKSM11_12_DATA[k].UPDCNT		,sBuf.c_str() );	//�X�V��
    	}

		// �����I����e���ړ����܂�
		for( i = iRowSelBottom; i <= ToIndex; i++ ){
	    	for( k = 1; k < sg->ColCount; k++ ) {
	            if( k == 14 ){
	                // �\�����́A����ւ����Ȃ�
	    			// sg->Cells[k][i-CopyCnt] = sg->Cells[k][i];
	        	} else {
					sg->Cells[k][i-CopyCnt] = sg->Cells[k][i];
	            }
			}
    	}

        // �����ړ����ꂽ�s�𐳂����ʒu�Ɉړ����܂��B
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
	    	for( k = 1; k < sg->ColCount; k++ ) {
	            if( k == 14 ){
	                // �\�����́A����ւ����Ȃ�
	    			// sg->Cells[k][ToIndex-CopyCnt+iSkip] = sg->Cells[k][ToIndex];
	        	} else {
					sg->Cells[k][ToIndex-CopyCnt+iSkip] = sg->Cells[k][ToIndex];
	            }
			}
        }

		// �������Ɋi�[�������e��߂��܂�
        i = ToIndex - CopyCnt;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
				sg->Cells[1][i+k] = pKSM11_12_DATA[m].KOMK_NM		;	//���荀�ځi���{��j
				sg->Cells[2][i+k] = pKSM11_12_DATA[m].KOMK_ENG		;	//���荀�ځi�p��j
				sg->Cells[3][i+k] = pKSM11_12_DATA[m].KIKI_NM		;	//����@�햼��
				sg->Cells[4][i+k] = pKSM11_12_DATA[m].TANI			;	//�P��
				sg->Cells[5][i+k] = ""								;	//�K�i�i��{�j�@���ĕ`�悷��ׂɕK�v�ł��B
				sg->Cells[6][i+k] = pKSM11_12_DATA[m].SOKU_SU		;	//�����i��{�j
				sg->Cells[7][i+k] = pKSM11_12_DATA[m].VALUE_TYPE	;	//�l�\��
				sg->Cells[8][i+k] = pKSM11_12_DATA[m].SOKU_FLG		;	//���荀�ڂ̗L��
				sg->Cells[9][i+k] = pKSM11_12_DATA[m].TOKU_FLG		;	//���ʍ��ڂ̗L��
				sg->Cells[10][i+k] = pKSM11_12_DATA[m].UPDYMD		;	//�ύX��
				sg->Cells[11][i+k] = pKSM11_12_DATA[m].UPDNAM		;	//�X�V�ҁi���́j
				sg->Cells[12][i+k] = pKSM11_12_DATA[m].UPDCHR		;	//�X�V�ҁi�S���҃R�[�h�j
				sg->Cells[13][i+k] = pKSM11_12_DATA[m].KOMK_NO		;	//����NO
				sg->Cells[15][i+k] = pKSM11_12_DATA[m].KIKI_NO		;	//����@��NO
				sg->Cells[16][i+k] = pKSM11_12_DATA[m].KIKA_TYPE	;	//�K�i�^�C�v
				sg->Cells[17][i+k] = pKSM11_12_DATA[m].KIKA_KIND	;	//�K�i���
				sg->Cells[18][i+k] = pKSM11_12_DATA[m].KIKA_DECI	;	//�K�i�����_�ȉ�����
				sg->Cells[19][i+k] = pKSM11_12_DATA[m].KIKA_NUM1	;	//�K�i�l�P
				sg->Cells[20][i+k] = pKSM11_12_DATA[m].KIKA_NUM2	;	//�K�i�l�Q
				sg->Cells[21][i+k] = pKSM11_12_DATA[m].KIKA_NUM3	;	//�K�i�l�R
				sg->Cells[22][i+k] = pKSM11_12_DATA[m].KIKA_STR		;	//�K�i����
				sg->Cells[23][i+k] = pKSM11_12_DATA[m].KIKA_PRT		;	//��������l�̈��
				sg->Cells[24][i+k] = pKSM11_12_DATA[m].VALUE_DECI	;	//����l�����_�ȉ�����
				sg->Cells[25][i+k] = pKSM11_12_DATA[m].ADDYMD		;	//�o�^��
				sg->Cells[26][i+k] = pKSM11_12_DATA[m].ADDTIM		;	//�o�^����
				sg->Cells[27][i+k] = pKSM11_12_DATA[m].UPDTIM		;	//�X�V����
				sg->Cells[28][i+k] = pKSM11_12_DATA[m].UPDCNT		;	//�X�V��
				sg->Cells[29][i+k] = "1"							;	//�X�V�t���O�̐ݒ�
				m++;
        	}
        }

    	// �ړ���̍s��I��͈͂����肵�܂�
		myRect.Left		= sg->Selection.Left;
		myRect.Top		= ToIndex - CopyCnt;
		myRect.Right	= sg->Selection.Right;
		myRect.Bottom	= myRect.Top + CopyCnt;
    }
    else {

	    // �I������Ă���͈͂��������Ɋi�[���܂�
    	for( i=iRowSelTop+1, k=0; i<=iRowSelBottom; i++, k++ ) {
			sBuf = sg->Cells[1][i];
			strcpy( pKSM11_12_DATA[k].KOMK_NM		,sBuf.c_str() );	//���荀�ځi���{��j
			sBuf = sg->Cells[2][i];
			strcpy( pKSM11_12_DATA[k].KOMK_ENG		,sBuf.c_str() );	//���荀�ځi�p��j
			sBuf = sg->Cells[3][i];
			strcpy( pKSM11_12_DATA[k].KIKI_NM		,sBuf.c_str() );	//����@�햼��
			sBuf = sg->Cells[4][i];
			strcpy( pKSM11_12_DATA[k].TANI			,sBuf.c_str() );	//�P��
			sBuf = sg->Cells[6][i];
			strcpy( pKSM11_12_DATA[k].SOKU_SU		,sBuf.c_str() );	//�����i��{�j
			sBuf = sg->Cells[7][i];
			strcpy( pKSM11_12_DATA[k].VALUE_TYPE	,sBuf.c_str() );	//�l�\��
			sBuf = sg->Cells[8][i];
			strcpy( pKSM11_12_DATA[k].SOKU_FLG		,sBuf.c_str() );	//���荀�ڂ̗L��
			sBuf = sg->Cells[9][i];
			strcpy( pKSM11_12_DATA[k].TOKU_FLG		,sBuf.c_str() );	//���ʍ��ڂ̗L��
			sBuf = sg->Cells[10][i];
			strcpy( pKSM11_12_DATA[k].UPDYMD		,sBuf.c_str() );	//�ύX��
			sBuf = sg->Cells[12][i];
			strcpy( pKSM11_12_DATA[k].UPDCHR		,sBuf.c_str() );	//�X�V�ҁi�S���҃R�[�h�j
			sBuf = sg->Cells[11][i];
			strcpy( pKSM11_12_DATA[k].UPDNAM		,sBuf.c_str() );	//�X�V�ҁi���́j
			sBuf = sg->Cells[13][i];
			strcpy( pKSM11_12_DATA[k].KOMK_NO		,sBuf.c_str() );	//����NO
			sBuf = sg->Cells[15][i];
			strcpy( pKSM11_12_DATA[k].KIKI_NO		,sBuf.c_str() );	//����@��NO
			sBuf = sg->Cells[16][i];
			strcpy( pKSM11_12_DATA[k].KIKA_TYPE		,sBuf.c_str() );	//�K�i�^�C�v
			sBuf = sg->Cells[17][i];
			strcpy( pKSM11_12_DATA[k].KIKA_KIND		,sBuf.c_str() );	//�K�i���
			sBuf = sg->Cells[18][i];
			strcpy( pKSM11_12_DATA[k].KIKA_DECI		,sBuf.c_str() );	//�K�i�����_�ȉ�����
			sBuf = sg->Cells[19][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM1		,sBuf.c_str() );	//�K�i�l�P
			sBuf = sg->Cells[20][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM2		,sBuf.c_str() );	//�K�i�l�Q
			sBuf = sg->Cells[21][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM3		,sBuf.c_str() );	//�K�i�l�R
			sBuf = sg->Cells[22][i];
			strcpy( pKSM11_12_DATA[k].KIKA_STR		,sBuf.c_str() );	//�K�i����
			sBuf = sg->Cells[23][i];
			strcpy( pKSM11_12_DATA[k].KIKA_PRT		,sBuf.c_str() );	//��������l�̈��
			sBuf = sg->Cells[24][i];
			strcpy( pKSM11_12_DATA[k].VALUE_DECI	,sBuf.c_str() );	//����l�����_�ȉ�����
			sBuf = sg->Cells[25][i];
			strcpy( pKSM11_12_DATA[k].ADDYMD		,sBuf.c_str() );	//�o�^��
			sBuf = sg->Cells[26][i];
			strcpy( pKSM11_12_DATA[k].ADDTIM		,sBuf.c_str() );	//�o�^����
			sBuf = sg->Cells[27][i];
			strcpy( pKSM11_12_DATA[k].UPDTIM		,sBuf.c_str() );	//�X�V����
			sBuf = sg->Cells[28][i];
			strcpy( pKSM11_12_DATA[k].UPDCNT		,sBuf.c_str() );	//�X�V��
    	}

		// �����I����e���ړ����܂�
		for( i = iRowSelTop; i >= ToIndex; i-- ){
	    	for( k = 1; k < sg->ColCount; k++ ) {
	            if( k == 14 ){
	                // �\�����́A����ւ����Ȃ�
	    			// sg->Cells[k][i+CopyCnt] = sg->Cells[k][i];
	        	} else {
					sg->Cells[k][i+CopyCnt] = sg->Cells[k][i];
	            }
			}
    	}

        // �����ړ����ꂽ�s�𐳂����ʒu�Ɉړ����܂��B
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
	    	for( k = 1; k < sg->ColCount; k++ ) {
	            if( k == 14 ){
	                // �\�����́A����ւ����Ȃ�
	    			// sg->Cells[k][ToIndex+iSkip] = sg->Cells[k][ToIndex];
	        	} else {
					sg->Cells[k][ToIndex+iSkip] = sg->Cells[k][ToIndex];
	            }
			}
        }

		// �������Ɋi�[�������e��߂��܂�
        i = ToIndex;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
				sg->Cells[1][i+k] = pKSM11_12_DATA[m].KOMK_NM		;	//���荀�ځi���{��j
				sg->Cells[2][i+k] = pKSM11_12_DATA[m].KOMK_ENG		;	//���荀�ځi�p��j
				sg->Cells[3][i+k] = pKSM11_12_DATA[m].KIKI_NM		;	//����@�햼��
				sg->Cells[4][i+k] = pKSM11_12_DATA[m].TANI			;	//�P��
				sg->Cells[5][i+k] = ""								;	//�K�i�i��{�j�@���ĕ`�悷��ׂɕK�v�ł��B
				sg->Cells[6][i+k] = pKSM11_12_DATA[m].SOKU_SU		;	//�����i��{�j
				sg->Cells[7][i+k] = pKSM11_12_DATA[m].VALUE_TYPE	;	//�l�\��
				sg->Cells[8][i+k] = pKSM11_12_DATA[m].SOKU_FLG		;	//���荀�ڂ̗L��
				sg->Cells[9][i+k] = pKSM11_12_DATA[m].TOKU_FLG		;	//���ʍ��ڂ̗L��
				sg->Cells[10][i+k] = pKSM11_12_DATA[m].UPDYMD		;	//�ύX��
				sg->Cells[11][i+k] = pKSM11_12_DATA[m].UPDNAM		;	//�X�V�ҁi���́j
				sg->Cells[12][i+k] = pKSM11_12_DATA[m].UPDCHR		;	//�X�V�ҁi�S���҃R�[�h�j
				sg->Cells[13][i+k] = pKSM11_12_DATA[m].KOMK_NO		;	//����NO
				sg->Cells[15][i+k] = pKSM11_12_DATA[m].KIKI_NO		;	//����@��NO
				sg->Cells[16][i+k] = pKSM11_12_DATA[m].KIKA_TYPE	;	//�K�i�^�C�v
				sg->Cells[17][i+k] = pKSM11_12_DATA[m].KIKA_KIND	;	//�K�i���
				sg->Cells[18][i+k] = pKSM11_12_DATA[m].KIKA_DECI	;	//�K�i�����_�ȉ�����
				sg->Cells[19][i+k] = pKSM11_12_DATA[m].KIKA_NUM1	;	//�K�i�l�P
				sg->Cells[20][i+k] = pKSM11_12_DATA[m].KIKA_NUM2	;	//�K�i�l�Q
				sg->Cells[21][i+k] = pKSM11_12_DATA[m].KIKA_NUM3	;	//�K�i�l�R
				sg->Cells[22][i+k] = pKSM11_12_DATA[m].KIKA_STR		;	//�K�i����
				sg->Cells[23][i+k] = pKSM11_12_DATA[m].KIKA_PRT		;	//��������l�̈��
				sg->Cells[24][i+k] = pKSM11_12_DATA[m].VALUE_DECI	;	//����l�����_�ȉ�����
				sg->Cells[25][i+k] = pKSM11_12_DATA[m].ADDYMD		;	//�o�^��
				sg->Cells[26][i+k] = pKSM11_12_DATA[m].ADDTIM		;	//�o�^����
				sg->Cells[27][i+k] = pKSM11_12_DATA[m].UPDTIM		;	//�X�V����
				sg->Cells[28][i+k] = pKSM11_12_DATA[m].UPDCNT		;	//�X�V��
				sg->Cells[29][i+k] = "1"							;	//�X�V�t���O�̐ݒ�
				m++;
        	}
        }

    	// �ړ���̍s��I��͈͂����肵�܂�
		myRect.Left		= sg->Selection.Left;
		myRect.Top		= ToIndex;
		myRect.Right	= sg->Selection.Right;
		myRect.Bottom	= ToIndex + CopyCnt;
    }

    // �������̊J��
    if( hMemCopy ){
        GlobalUnlock( hMemCopy );
        GlobalFree( hMemCopy );
    }


    // �ړ���̍s��I�����܂�
    sg->Row   		= myRect.Top;
    sg->Selection	= myRect;
    SGr_ListSelectCell(Sender,1,sg->Row,true);

    iRowSelTop    = sg->Selection.Top;
    iRowSelBottom = sg->Selection.Bottom;

    // �f�[�^��ύX�����t���O
    DataSave = true;
    BtnF11->Enabled = true;
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
//    TStringGrid* sg	�F�Ăяo������TStringGrid�I�u�W�F�N�g
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
void __fastcall TForm1::RowExchange(TStringGrid* sg, int FromIndex, int ToIndex)
{
    int			i, k;
	TGridRect	myRect;
    AnsiString	sBuf;
    AnsiString	sLineNo;

    // ����ւ���̃f�[�^���o�b�N�A�b�v
    sLineNo = sg->Cells[0][ToIndex];						//�s�ԍ�
	sBuf = sg->Cells[1][ToIndex];
    strcpy( tmpKSM11_12_DATA.KOMK_NM	,sBuf.c_str() );	//���荀�ځi���{��j
	sBuf = sg->Cells[2][ToIndex];
    strcpy( tmpKSM11_12_DATA.KOMK_ENG	,sBuf.c_str() );	//���荀�ځi�p��j
	sBuf = sg->Cells[3][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKI_NM	,sBuf.c_str() );	//����@�햼��
	sBuf = sg->Cells[4][ToIndex];
    strcpy( tmpKSM11_12_DATA.TANI		,sBuf.c_str() );	//�P��
	sBuf = sg->Cells[6][ToIndex];
    strcpy( tmpKSM11_12_DATA.SOKU_SU	,sBuf.c_str() );	//�����i��{�j
	sBuf = sg->Cells[7][ToIndex];
    strcpy( tmpKSM11_12_DATA.VALUE_TYPE	,sBuf.c_str() );	//�l�\��
	sBuf = sg->Cells[8][ToIndex];
    strcpy( tmpKSM11_12_DATA.SOKU_FLG	,sBuf.c_str() );	//���荀�ڂ̗L��
	sBuf = sg->Cells[9][ToIndex];
    strcpy( tmpKSM11_12_DATA.TOKU_FLG	,sBuf.c_str() );	//���ʍ��ڂ̗L��
	sBuf = sg->Cells[10][ToIndex];
    strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );	//�ύX��
	sBuf = sg->Cells[12][ToIndex];
    strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );	//�X�V�ҁi�S���҃R�[�h�j
	sBuf = sg->Cells[11][ToIndex];
    strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );	//�X�V�ҁi���́j
	sBuf = sg->Cells[13][ToIndex];
    strcpy( tmpKSM11_12_DATA.KOMK_NO	,sBuf.c_str() );	//����NO
	sBuf = sg->Cells[14][ToIndex];
    strcpy( tmpKSM11_12_DATA.ORDER_NO	,sBuf.c_str() );	//�\����
	sBuf = sg->Cells[15][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKI_NO	,sBuf.c_str() );	//����@��NO
	sBuf = sg->Cells[16][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_TYPE	,sBuf.c_str() );	//�K�i�^�C�v
	sBuf = sg->Cells[17][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_KIND	,sBuf.c_str() );	//�K�i���
	sBuf = sg->Cells[18][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_DECI	,sBuf.c_str() );	//�K�i�����_�ȉ�����
	sBuf = sg->Cells[19][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	//�K�i�l�P
	sBuf = sg->Cells[20][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	//�K�i�l�Q
	sBuf = sg->Cells[21][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	//�K�i�l�R
	sBuf = sg->Cells[22][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	//�K�i����
	sBuf = sg->Cells[23][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_PRT	,sBuf.c_str() );	//��������l�̈��
	sBuf = sg->Cells[24][ToIndex];
    strcpy( tmpKSM11_12_DATA.VALUE_DECI	,sBuf.c_str() );	//����l�����_�ȉ�����
	sBuf = sg->Cells[25][ToIndex];
    strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );	//�o�^��
	sBuf = sg->Cells[26][ToIndex];
    strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );	//�o�^����
	sBuf = sg->Cells[27][ToIndex];
    strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );	//�X�V����
	sBuf = sg->Cells[28][ToIndex];
    strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );	//�X�V��
	sBuf = sg->Cells[29][ToIndex];							//�X�V�t���O

    if( ToIndex > FromIndex ){
		// �㉺�����ւ��܂�
    	for( i=ToIndex; i>FromIndex; i-- ) {
	    	for( k = 0; k < sg->ColCount; k++ ) {
				sg->Cells[k][i] = sg->Cells[k][i-1];
			}
    	}
    }
    else{
		// �㉺�����ւ��܂�
    	for( i=ToIndex; i<FromIndex; i++ ) {
	    	for( k = 0; k < sg->ColCount; k++ ) {
				sg->Cells[k][i] = sg->Cells[k][i+1];
			}
    	}
    }

    // �o�b�N�A�b�v�����f�[�^�����ɂ��ǂ��܂��B
    sg->Cells[0][FromIndex] = sLineNo						;	//�s�ԍ�
	sg->Cells[1][FromIndex] = tmpKSM11_12_DATA.KOMK_NM		;	//���荀�ځi���{��j
	sg->Cells[2][FromIndex] = tmpKSM11_12_DATA.KOMK_ENG		;	//���荀�ځi�p��j
	sg->Cells[3][FromIndex] = tmpKSM11_12_DATA.KIKI_NM		;	//����@�햼��
	sg->Cells[4][FromIndex] = tmpKSM11_12_DATA.TANI			;	//�P��
	sg->Cells[5][FromIndex] = ""							;	//�K�i�i��{�j�@���ĕ`�悷��ׂɕK�v�ł��B
	sg->Cells[6][FromIndex] = tmpKSM11_12_DATA.SOKU_SU		;	//�����i��{�j
	sg->Cells[7][FromIndex] = tmpKSM11_12_DATA.VALUE_TYPE	;	//�l�\��
	sg->Cells[8][FromIndex] = tmpKSM11_12_DATA.SOKU_FLG		;	//���荀�ڂ̗L��
	sg->Cells[9][FromIndex] = tmpKSM11_12_DATA.TOKU_FLG		;	//���ʍ��ڂ̗L��
	sg->Cells[10][FromIndex] = tmpKSM11_12_DATA.UPDYMD		;	//�ύX��
	sg->Cells[11][FromIndex] = tmpKSM11_12_DATA.UPDNAM		;	//�X�V�ҁi���́j
	sg->Cells[12][FromIndex] = tmpKSM11_12_DATA.UPDCHR		;	//�X�V�ҁi�S���҃R�[�h�j
	sg->Cells[13][FromIndex] = tmpKSM11_12_DATA.KOMK_NO		;	//����NO
	sg->Cells[14][FromIndex] = tmpKSM11_12_DATA.ORDER_NO	;	//�\����
	sg->Cells[15][FromIndex] = tmpKSM11_12_DATA.KIKI_NO		;	//����@��NO
	sg->Cells[16][FromIndex] = tmpKSM11_12_DATA.KIKA_TYPE	;	//�K�i�^�C�v
	sg->Cells[17][FromIndex] = tmpKSM11_12_DATA.KIKA_KIND	;	//�K�i���
	sg->Cells[18][FromIndex] = tmpKSM11_12_DATA.KIKA_DECI	;	//�K�i�����_�ȉ�����
	sg->Cells[19][FromIndex] = tmpKSM11_12_DATA.KIKA_NUM1	;	//�K�i�l�P
	sg->Cells[20][FromIndex] = tmpKSM11_12_DATA.KIKA_NUM2	;	//�K�i�l�Q
	sg->Cells[21][FromIndex] = tmpKSM11_12_DATA.KIKA_NUM3	;	//�K�i�l�R
	sg->Cells[22][FromIndex] = tmpKSM11_12_DATA.KIKA_STR	;	//�K�i����
	sg->Cells[23][FromIndex] = tmpKSM11_12_DATA.KIKA_PRT	;	//��������l�̈��
	sg->Cells[24][FromIndex] = tmpKSM11_12_DATA.VALUE_DECI	;	//����l�����_�ȉ�����
	sg->Cells[25][FromIndex] = tmpKSM11_12_DATA.ADDYMD		;	//�o�^��
	sg->Cells[26][FromIndex] = tmpKSM11_12_DATA.ADDTIM		;	//�o�^����
	sg->Cells[27][FromIndex] = tmpKSM11_12_DATA.UPDTIM		;	//�X�V����
	sg->Cells[28][FromIndex] = tmpKSM11_12_DATA.UPDCNT		;	//�X�V��
	sg->Cells[29][FromIndex] = sBuf							;	//�X�V�t���O�̐ݒ�

    // �I���������܂�
    //SGr_List->Row	= iRowSelTop;
	myRect.Left		= sg->Selection.Left;
	myRect.Top		= iRowSelTop;
	myRect.Right	= sg->Selection.Right;
	myRect.Bottom	= iRowSelBottom;
    sg->Selection	= myRect;
    //SGr_ListSelectCell(Sender,1,sg->Row,true);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnSelectCell�C�x���g�FStringGrid�̃Z�����I�������O�ɔ������܂��B
//
//  �@�\����
//    StringGrid�őI�����ꂽ��A��ʉ�����TextBox�ɃZ�b�g���܂�
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol			�F�I�������̈ʒu
//    int ARow			�F�I������s�̈ʒu
//    bool &CanSelect	�F�I�����������ǂ����̃t���O
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_ListSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{

    int			i, k;
    AnsiString	sBuf;
	TStringGrid *sg = (TStringGrid *)Sender;


    if(ARow == 0) ARow = 1;
    ROWPOINT = ARow;

	// ���ڂ̎��
    if( sg->Name == "SGr_List" ){
        Rdo_TYPE_SYUKA->Checked = true;
	} else{
        Rdo_TYPE_ZAIRYO->Checked = true;
	}

    // ���荀�ځi���{��j
    Edt_SKTKMK_JPN->Text = sg->Cells[1][ARow];

    // ���ږ��i�p��j
    Edt_SKTKMK_ENG->Text = sg->Cells[2][ARow];

    // ����@��
    k = sg->Cells[15][ARow].ToIntDef(-1);
    if( k == -1 ){
	    Cmb_SKTKIKI->ItemIndex = 0;
    }
    else {
    	for( i = 0; i < iKIKI_Cnt; i++){
    		if( iKIKI[i] == k ){
			    Cmb_SKTKIKI->ItemIndex = i;
            	break;
        	}
    	}
    }

    // �P��
    Cmb_TANI->Text = sg->Cells[4][ARow];

	// ���荀�ڂƂ��Ă̈���
    switch( sg->Cells[8][ARow].ToIntDef(-1) ){
		case 0: Rdo_SKTKMK_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_SKTKMK_ON->Checked = true;
          		break;
   	}

	// ���ʍ��ڂƂ��Ă̈���
    switch( sg->Cells[9][ARow].ToIntDef(-1) ){
		case 1: Rdo_TKBKMK_ON->Checked = true;
				break;
		case 0:
        default:Rdo_TKBKMK_OFF->Checked = true;
          		break;
   	}

	// �K�i�i�w����@�j
    switch( sg->Cells[16][ARow].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SHITEI_MOJI->Checked = true;
				break;
		case 2: Rdo_KIKAKU_SHITEI_KIJYUN->Checked = true;
				break;
		case 1:
        default:Rdo_KIKAKU_SHITEI_HANI->Checked = true;
          		break;
   	}

	// �K�i�i��ށj
    switch( sg->Cells[17][ARow].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SYURUI_MIN->Checked = true;
				break;
		case 2: Rdo_KIKAKU_SYURUI_MAX->Checked = true;
				break;
		case 1:
        default:Rdo_KIKAKU_SYURUI_MINMAX->Checked = true;
          		break;
   	}

	// �K�i�i��������l�̈���j
    switch( sg->Cells[23][ARow].ToIntDef(-1) ){
		case 0: Rdo_MANMIN_PRT_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_MANMIN_PRT_ON->Checked = true;
          		break;
   	}

	// �K�i�i�����_�ȉ������j
    Nmb_KIKAKU_DOUBLE->Text = IntToStr(sg->Cells[18][ARow].ToIntDef(0));

	// �K�i�l�i�͈͎w��j
    Nmb_KIKAKU_HANI_MIN->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_HANI_MAX->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_HANI_MIN->Text = sg->Cells[19][ARow];
    if( sg->Cells[16][ARow].ToIntDef(-1) == 1 ){
	    Nmb_KIKAKU_HANI_MAX->Text = sg->Cells[20][ARow];
    }
    else {
	    Nmb_KIKAKU_HANI_MAX->Text = "0";
    }

	// �K�i�l�i��l�w��j
    Nmb_KIKAKU_KIJYUN_MID->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MAX->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MIN->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MID->Text = sg->Cells[19][ARow];
    if( sg->Cells[16][ARow].ToIntDef(-1) == 2 ){
    	Nmb_KIKAKU_KIJYUN_MAX->Text = sg->Cells[20][ARow];
    	Nmb_KIKAKU_KIJYUN_MIN->Text = sg->Cells[21][ARow];
    }
    else {
    	Nmb_KIKAKU_KIJYUN_MAX->Text = "0";
    	Nmb_KIKAKU_KIJYUN_MIN->Text = "0";
    }

	// �K�i�l�i�����w��j
    Edt_KIKAKU_STRING->Text = sg->Cells[22][ARow];

	// ����l�i�l�\���j
    switch( sg->Cells[7][ARow].ToIntDef(-1) ){
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
    Nmb_VALUE_DOUBLE->Text = IntToStr(sg->Cells[24][ARow].ToIntDef(0));

	// ����l�i���悎���j
    Nmb_N->Text = IntToStr(sg->Cells[6][ARow].ToIntDef(2));

    // �X�V��
    sBuf = sg->Cells[10][ARow];
    if( sBuf.Length() == 8 ){
    	sBuf.Insert("/",5);
       	sBuf.Insert("/",8);
	   	PnlUPDYMD->Caption = sBuf;
    }
    else {
	   	PnlUPDYMD->Caption = "";
    }

    // �X�V��
    PnlUPDCHR->Caption = sg->Cells[11][ARow];

    // �C����폜�ׂ̈Ɂu����No�v���L�����܂��B
    if( sg->Cells[13][ARow] == "" ){
        PnlUPDYMD->Tag = -1;
    }
    else {
        PnlUPDYMD->Tag = StrToInt(sg->Cells[13][ARow]);
    }

    // �X�V�񐔂��L�����܂��B
    if( sg->Cells[28][ARow] == "" ){
    	PnlUPDCHR->Tag = -1;
    }
    else {
    	PnlUPDCHR->Tag = StrToInt(sg->Cells[28][ARow]);
    }

    // �X�V�E�폜�s�\���ڂ̏ꍇ�A�C���E�폜�{�^���𗘗p�s�ɂ��܂��B
    if( SGr_List->Cells[13][ARow] == 1 || PnlUPDYMD->Tag == -1 ){
		BtnF09->Enabled = false;
		BtnF10->Enabled = false;
    }
    else{
		BtnF09->Enabled = true;
		BtnF10->Enabled = true;
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnChange�C�x���g	�F�V�����^�u���I�������Ɣ������܂��B
//
//  �@�\����
//    �y�[�W�R���g���[���ɂ��u�o�׌������荀�ځv�u�ޗ��ؖ����ځv�̐ؑ�
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
void __fastcall TForm1::PgCtr_ListChange(TObject *Sender)
{
	TPageControl *pPC = (TPageControl *)Sender;

	if( pPC->ActivePage->Name == "TabSheet1" ){
	    //�s�������I�����܂�
    	SGr_ListSelectCell( SGr_List, 1, SGr_List->Row, true);
	    SGr_ListClick( SGr_List );
	} else{
	    //�s�������I�����܂�
    	SGr_ListSelectCell( SGr_List2, 1, SGr_List2->Row, true);
	    SGr_ListClick( SGr_List2 );
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
void __fastcall TForm1::Nmb_KIKAKU_DOUBLEExit(TObject *Sender)
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

    // �u�K�i�l�v�̏����_�ȉ������̒l��ύX������
    // �w�肳��Ă���K�i�̏����_�ȉ������̒l�����킹�܂��B
    if( ne->Name == "Nmb_KIKAKU_DOUBLE" ){
    	AnsiString	sBuf;

        // �u����l�v�̏����_�ȉ������́{�P���܂��B
        sBuf = Nmb_KIKAKU_DOUBLE->Text;
        if( sBuf.ToIntDef(0) >= 0 && sBuf.ToIntDef(0) < 5 ){
        	sBuf = AnsiString(sBuf.ToIntDef(0) + 1);
        }
		Nmb_VALUE_DOUBLE->Text = sBuf;

		Nmb_KIKAKU_HANI_MIN->FPos   = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_HANI_MAX->FPos   = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MAX->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MID->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MIN->FPos = Nmb_KIKAKU_DOUBLE->Value;

        Nmb_KIKAKU_HANI_MIN->Text   = Nmb_KIKAKU_HANI_MIN->Text;
		Nmb_KIKAKU_HANI_MAX->Text   = Nmb_KIKAKU_HANI_MAX->Text;
		Nmb_KIKAKU_KIJYUN_MAX->Text = Nmb_KIKAKU_KIJYUN_MAX->Text;
		Nmb_KIKAKU_KIJYUN_MID->Text = Nmb_KIKAKU_KIJYUN_MID->Text;
		Nmb_KIKAKU_KIJYUN_MIN->Text = Nmb_KIKAKU_KIJYUN_MIN->Text;
    }

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
void __fastcall TForm1::Rdo_KIKAKU_SHITEI_HANIClick(TObject *Sender)
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
void __fastcall TForm1::Rdo_KIKAKU_SHITEI_KIJYUNClick(TObject *Sender)
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
void __fastcall TForm1::Rdo_KIKAKU_SHITEI_MOJIClick(TObject *Sender)
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
void __fastcall TForm1::Rdo_KIKAKU_SYURUI_MINMAXClick(TObject *Sender)
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
void __fastcall TForm1::Rdo_KIKAKU_SYURUI_MAXClick(TObject *Sender)
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
void __fastcall TForm1::Rdo_KIKAKU_SYURUI_MINClick(TObject *Sender)
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
//    OnClick�C�x���g	�F���ڂ̎�ށu�o�׌������ځv�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�׌������ڂƂ��ĉ�ʉ��������܂��i�F�ύX�����F�j
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
void __fastcall TForm1::Rdo_TYPE_SYUKAClick(TObject *Sender)
{
	Pnl_t01->Color = (TColor)0x00FFEEDD;
	Pnl_t02->Color = (TColor)0x00FFEEDD;
	Pnl_t03->Color = (TColor)0x00FFEEDD;
	Pnl_t04->Color = (TColor)0x00FFEEDD;
	Pnl_t05->Color = (TColor)0x00FFEEDD;
	Pnl_t06->Color = (TColor)0x00FFEEDD;
	Pnl_t07->Color = (TColor)0x00FFEEDD;
	Pnl_t08->Color = (TColor)0x00FFEEDD;
	Pnl_t09->Color = (TColor)0x00FFEEDD;
	Pnl_t10->Color = (TColor)0x00FFEEDD;
	Pnl_t11->Color = (TColor)0x00FFEEDD;
	Pnl_t12->Color = (TColor)0x00FFEEDD;
	Pnl_t13->Color = (TColor)0x00FFEEDD;
	Pnl_t14->Color = (TColor)0x00FFEEDD;
	Pnl_t15->Color = (TColor)0x00FFEEDD;
	Pnl_t16->Color = (TColor)0x00FFEEDD;
	Pnl_t17->Color = (TColor)0x00FFEEDD;
	Pnl_t18->Color = (TColor)0x00FFEEDD;
	Pnl_t19->Color = (TColor)0x00FFEEDD;
	Pnl_t20->Color = (TColor)0x00FFEEDD;
	Pnl_t21->Color = (TColor)0x00FFEEDD;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F���ڂ̎�ށu�ޗ��ؖ����ځv�N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �ޗ��ؖ����ڂƂ��ĉ�ʉ��������܂��i�F�ύX�����F�j
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
void __fastcall TForm1::Rdo_TYPE_ZAIRYOClick(TObject *Sender)
{
    Pnl_t01->Color = (TColor)0x00FFE1FD;
    Pnl_t02->Color = (TColor)0x00FFE1FD;
    Pnl_t03->Color = (TColor)0x00FFE1FD;
    Pnl_t04->Color = (TColor)0x00FFE1FD;
    Pnl_t05->Color = (TColor)0x00FFE1FD;
    Pnl_t06->Color = (TColor)0x00FFE1FD;
    Pnl_t07->Color = (TColor)0x00FFE1FD;
    Pnl_t08->Color = (TColor)0x00FFE1FD;
    Pnl_t09->Color = (TColor)0x00FFE1FD;
    Pnl_t10->Color = (TColor)0x00FFE1FD;
    Pnl_t11->Color = (TColor)0x00FFE1FD;
    Pnl_t12->Color = (TColor)0x00FFE1FD;
    Pnl_t13->Color = (TColor)0x00FFE1FD;
    Pnl_t14->Color = (TColor)0x00FFE1FD;
    Pnl_t15->Color = (TColor)0x00FFE1FD;
    Pnl_t16->Color = (TColor)0x00FFE1FD;
    Pnl_t17->Color = (TColor)0x00FFE1FD;
	Pnl_t18->Color = (TColor)0x00FFE1FD;
	Pnl_t19->Color = (TColor)0x00FFE1FD;
	Pnl_t20->Color = (TColor)0x00FFE1FD;
	Pnl_t21->Color = (TColor)0x00FFE1FD;

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
void __fastcall TForm1::Rdo_VALUE_NORMALClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled        = true;
	Nmb_VALUE_DOUBLE->Font->Color    = clBlack;

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
void __fastcall TForm1::Rdo_VALUE_KAKUDOClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled        = true;
	Nmb_VALUE_DOUBLE->Font->Color    = clBlack;

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
void __fastcall TForm1::Rdo_VALUE_OKClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled        = false;
	Nmb_VALUE_DOUBLE->Font->Color    = clGray;

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
void __fastcall TForm1::Rdo_VALUE_TEXTClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled        = false;
	Nmb_VALUE_DOUBLE->Font->Color    = clGray;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�o�׌����pStringGrid�̕\�����i�R��ށj���N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�׌����pStringGrid�̕\������ύX���܂�
//      �E���荀�ڃ}�X�^�[��
//      �E���荀�ږ��̏�
//      �E����@��E���荀�ږ��̏�
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
void __fastcall TForm1::Rdo_List1_OrderClick(TObject *Sender)
{
    int				i, k, m;
	AnsiString		sBuf;
	TRadioButton	*rdo = (TRadioButton *)Sender;

    if( rdo->Name == "Rdo_List1_Order1" ){
        // ON
		Btn_UP1->Enabled   = true;
		Btn_DOWN1->Enabled = true;
        SGr_List->Options = SGr_List->Options << goRowMoving;

	    // �\�����Ń\�[�g���s�Ȃ��܂�
		for( i = 1; i < SGr_List->RowCount - 2; i++ ){
	    	for( k = i + 1; k < SGr_List->RowCount - 1; k++ ) {
	            if( SGr_List->Cells[14][i].ToIntDef(0) > SGr_List->Cells[14][k].ToIntDef(0) ){
                    sBuf = GridLineCopy( SGr_List, i);
					for( m = 1; m < SGr_List->ColCount; m++ ) {
						SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
                    }
                    GridLinePaste( SGr_List, k, sBuf);
	            }
			}
    	}

	} else {
        // OFF
		Btn_UP1->Enabled   = false;
		Btn_DOWN1->Enabled = false;
        SGr_List->Options = SGr_List->Options >> goRowMoving;

	    if( rdo->Name == "Rdo_List1_Order2" ){

		    // ���荀�ڏ��Ń\�[�g���s�Ȃ��܂�
			for( i = 1; i < SGr_List->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List->RowCount - 1; k++ ) {
		            if( SGr_List->Cells[1][i] > SGr_List->Cells[1][k] ){
	                    sBuf = GridLineCopy( SGr_List, i);
						for( m = 1; m < SGr_List->ColCount; m++ ) {
							SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List, k, sBuf);
		            }
				}
	    	}
		} else {

		    // ����@��E���荀�ڏ��Ń\�[�g���s�Ȃ��܂�
			for( i = 1; i < SGr_List->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List->RowCount - 1; k++ ) {
		            if( SGr_List->Cells[15][i].ToIntDef(0) > SGr_List->Cells[15][k].ToIntDef(0) ){
	                    sBuf = GridLineCopy( SGr_List, i);
						for( m = 1; m < SGr_List->ColCount; m++ ) {
							SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List, k, sBuf);
		            } else {
		            	if( SGr_List->Cells[15][i] == SGr_List->Cells[15][k] &&
                        	SGr_List->Cells[1][i] > SGr_List->Cells[1][k] ){
	                    	sBuf = GridLineCopy( SGr_List, i);
							for( m = 1; m < SGr_List->ColCount; m++ ) {
								SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
	                    	}
	                    	GridLinePaste( SGr_List, k, sBuf);
						}
                    }
				}
	    	}
        }
    }

	SGr_ListSelectCell( SGr_List, 1, SGr_List->Row, true);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�ޗ��ؖ��pStringGrid�̕\�����i�R��ށj���N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �ޗ��ؖ��pStringGrid�̕\������ύX���܂�
//      �E���荀�ڃ}�X�^�[��
//      �E���荀�ږ��̏�
//      �E����@��E���荀�ږ��̏�
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
void __fastcall TForm1::Rdo_List2_OrderClick(TObject *Sender)
{
    int				i, k, m;
	AnsiString		sBuf;
	TRadioButton	*rdo = (TRadioButton *)Sender;

    if( rdo->Name == "Rdo_List2_Order1" ){
        // ON
		Btn_UP2->Enabled   = true;
		Btn_DOWN2->Enabled = true;
        SGr_List2->Options = SGr_List2->Options << goRowMoving;

	    // �\�����Ń\�[�g���s�Ȃ��܂�
		for( i = 1; i < SGr_List2->RowCount - 2; i++ ){
	    	for( k = i + 1; k < SGr_List2->RowCount - 1; k++ ) {
	            if( SGr_List2->Cells[14][i].ToIntDef(0) > SGr_List2->Cells[14][k].ToIntDef(0) ){
                    sBuf = GridLineCopy( SGr_List2, i);
					for( m = 1; m < SGr_List2->ColCount; m++ ) {
						SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
                    }
                    GridLinePaste( SGr_List2, k, sBuf);
	            }
			}
    	}

	} else {
        // OFF
		Btn_UP2->Enabled   = false;
		Btn_DOWN2->Enabled = false;
        SGr_List2->Options = SGr_List2->Options >> goRowMoving;

	    if( rdo->Name == "Rdo_List2_Order2" ){

		    // ���荀�ڏ��Ń\�[�g���s�Ȃ��܂�
			for( i = 1; i < SGr_List2->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List2->RowCount - 1; k++ ) {
		            if( SGr_List2->Cells[1][i] > SGr_List2->Cells[1][k] ){
	                    sBuf = GridLineCopy( SGr_List2, i);
						for( m = 1; m < SGr_List2->ColCount; m++ ) {
							SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List2, k, sBuf);
		            }
				}
	    	}
		} else {

		    // ����@��E���荀�ڏ��Ń\�[�g���s�Ȃ��܂�
			for( i = 1; i < SGr_List2->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List2->RowCount - 1; k++ ) {
		            if( SGr_List2->Cells[15][i].ToIntDef(0) > SGr_List2->Cells[15][k].ToIntDef(0) ){
	                    sBuf = GridLineCopy( SGr_List2, i);
						for( m = 1; m < SGr_List2->ColCount; m++ ) {
							SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List2, k, sBuf);
		            } else {
		            	if( SGr_List2->Cells[15][i] == SGr_List2->Cells[15][k] &&
                        	SGr_List2->Cells[1][i] > SGr_List2->Cells[1][k] ){
	                    	sBuf = GridLineCopy( SGr_List2, i);
							for( m = 1; m < SGr_List2->ColCount; m++ ) {
								SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
	                    	}
	                    	GridLinePaste( SGr_List2, k, sBuf);
						}
                    }
				}
	    	}
        }
    }
	SGr_ListSelectCell( SGr_List2, 1, SGr_List2->Row, true);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FStringGrid�̎w��s���o�b�t�@�ɕۑ����܂�
//
//  �@�\����
//    StringGrid�̎w��s���o�b�t�@�ɕۑ����܂�
//
//  �p�����^����
//    TStringGrid* sg	�F�Ăяo������TStringGrid�I�u�W�F�N�g
//    int iCpyIndex		�F���ʂ���sNO
//
//  �߂�l
//    AnsiString		�F�X�V�t���O�i���ʂ����s���X�V�ς݂��ǂ����j
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GridLineCopy( TStringGrid* sg, int iCpyIndex)
{
	AnsiString sBuf;

	sBuf = sg->Cells[1][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KOMK_NM	,sBuf.c_str() );	//���荀�ځi���{��j
	sBuf = sg->Cells[2][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KOMK_ENG	,sBuf.c_str() );	//���荀�ځi�p��j
	sBuf = sg->Cells[3][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKI_NM	,sBuf.c_str() );	//����@�햼��
	sBuf = sg->Cells[4][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.TANI		,sBuf.c_str() );	//�P��
	sBuf = sg->Cells[6][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.SOKU_SU	,sBuf.c_str() );	//�����i��{�j
	sBuf = sg->Cells[7][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.VALUE_TYPE	,sBuf.c_str() );	//�l�\��
	sBuf = sg->Cells[8][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.SOKU_FLG	,sBuf.c_str() );	//���荀�ڂ̗L��
	sBuf = sg->Cells[9][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.TOKU_FLG	,sBuf.c_str() );	//���ʍ��ڂ̗L��
	sBuf = sg->Cells[10][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );	//�ύX��
	sBuf = sg->Cells[12][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );	//�X�V�ҁi�S���҃R�[�h�j
	sBuf = sg->Cells[11][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );	//�X�V�ҁi���́j
	sBuf = sg->Cells[13][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KOMK_NO	,sBuf.c_str() );	//����NO
	sBuf = sg->Cells[14][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.ORDER_NO	,sBuf.c_str() );	//�\����
	sBuf = sg->Cells[15][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKI_NO	,sBuf.c_str() );	//����@��NO
	sBuf = sg->Cells[16][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_TYPE	,sBuf.c_str() );	//�K�i�^�C�v
	sBuf = sg->Cells[17][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_KIND	,sBuf.c_str() );	//�K�i���
	sBuf = sg->Cells[18][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_DECI	,sBuf.c_str() );	//�K�i�����_�ȉ�����
	sBuf = sg->Cells[19][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	//�K�i�l�P
	sBuf = sg->Cells[20][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	//�K�i�l�Q
	sBuf = sg->Cells[21][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	//�K�i�l�R
	sBuf = sg->Cells[22][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	//�K�i����
	sBuf = sg->Cells[23][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_PRT	,sBuf.c_str() );	//��������l�̈��
	sBuf = sg->Cells[24][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.VALUE_DECI	,sBuf.c_str() );	//����l�����_�ȉ�����
	sBuf = sg->Cells[25][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );	//�o�^��
	sBuf = sg->Cells[26][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );	//�o�^����
	sBuf = sg->Cells[27][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );	//�X�V����
	sBuf = sg->Cells[28][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );	//�X�V��
	sBuf = sg->Cells[29][iCpyIndex];						//�X�V�t���O
	
	return sBuf;	// �X�V�t���O
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�o�b�t�@�ɕۑ����ꂽStringGrid�f�[�^��StringGrid�̎w��s�ɕ������܂�
//
//  �@�\����
//    �o�b�t�@�ɕۑ����ꂽStringGrid�f�[�^��StringGrid�̎w��s�ɕ������܂�
//
//  �p�����^����
//    TStringGrid* sg	�F�Ăяo������TStringGrid�I�u�W�F�N�g
//    int iPstIndex		�F��������sNO
//    AnsiString sUpdFlg�F��������s�ɐݒ肷��X�V�t���O
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GridLinePaste( TStringGrid* sg, int iPstIndex, AnsiString sUpdFlg)
{

	sg->Cells[1][iPstIndex] = tmpKSM11_12_DATA.KOMK_NM		;	//���荀�ځi���{��j
	sg->Cells[2][iPstIndex] = tmpKSM11_12_DATA.KOMK_ENG		;	//���荀�ځi�p��j
	sg->Cells[3][iPstIndex] = tmpKSM11_12_DATA.KIKI_NM		;	//����@�햼��
	sg->Cells[4][iPstIndex] = tmpKSM11_12_DATA.TANI			;	//�P��
	sg->Cells[5][iPstIndex] = ""							;	//�K�i�i��{�j�@���ĕ`�悷��ׂɕK�v�ł��B
	sg->Cells[6][iPstIndex] = tmpKSM11_12_DATA.SOKU_SU		;	//�����i��{�j
	sg->Cells[7][iPstIndex] = tmpKSM11_12_DATA.VALUE_TYPE	;	//�l�\��
	sg->Cells[8][iPstIndex] = tmpKSM11_12_DATA.SOKU_FLG		;	//���荀�ڂ̗L��
	sg->Cells[9][iPstIndex] = tmpKSM11_12_DATA.TOKU_FLG		;	//���ʍ��ڂ̗L��
	sg->Cells[10][iPstIndex] = tmpKSM11_12_DATA.UPDYMD		;	//�ύX��
	sg->Cells[11][iPstIndex] = tmpKSM11_12_DATA.UPDNAM		;	//�X�V�ҁi���́j
	sg->Cells[12][iPstIndex] = tmpKSM11_12_DATA.UPDCHR		;	//�X�V�ҁi�S���҃R�[�h�j
	sg->Cells[13][iPstIndex] = tmpKSM11_12_DATA.KOMK_NO		;	//����NO
	sg->Cells[14][iPstIndex] = tmpKSM11_12_DATA.ORDER_NO	;	//�\����
	sg->Cells[15][iPstIndex] = tmpKSM11_12_DATA.KIKI_NO		;	//����@��NO
	sg->Cells[16][iPstIndex] = tmpKSM11_12_DATA.KIKA_TYPE	;	//�K�i�^�C�v
	sg->Cells[17][iPstIndex] = tmpKSM11_12_DATA.KIKA_KIND	;	//�K�i���
	sg->Cells[18][iPstIndex] = tmpKSM11_12_DATA.KIKA_DECI	;	//�K�i�����_�ȉ�����
	sg->Cells[19][iPstIndex] = tmpKSM11_12_DATA.KIKA_NUM1	;	//�K�i�l�P
	sg->Cells[20][iPstIndex] = tmpKSM11_12_DATA.KIKA_NUM2	;	//�K�i�l�Q
	sg->Cells[21][iPstIndex] = tmpKSM11_12_DATA.KIKA_NUM3	;	//�K�i�l�R
	sg->Cells[22][iPstIndex] = tmpKSM11_12_DATA.KIKA_STR	;	//�K�i����
	sg->Cells[23][iPstIndex] = tmpKSM11_12_DATA.KIKA_PRT	;	//��������l�̈��
	sg->Cells[24][iPstIndex] = tmpKSM11_12_DATA.VALUE_DECI	;	//����l�����_�ȉ�����
	sg->Cells[25][iPstIndex] = tmpKSM11_12_DATA.ADDYMD		;	//�o�^��
	sg->Cells[26][iPstIndex] = tmpKSM11_12_DATA.ADDTIM		;	//�o�^����
	sg->Cells[27][iPstIndex] = tmpKSM11_12_DATA.UPDTIM		;	//�X�V����
	sg->Cells[28][iPstIndex] = tmpKSM11_12_DATA.UPDCNT		;	//�X�V��
    if( sUpdFlg != "" ){
		sg->Cells[29][iPstIndex] = sUpdFlg				   	;	//�X�V�t���O�̐ݒ�
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�R�}���h���C�������𕪗��i�������A���[�U���Ȃǁj
//
//  �@�\����
//    �v���O�����N�����̃R�}���h���C�������𕪗����ϐ��ɐݒ肵�܂��B
//    ���[�U�R�[�h�A���[�U���A�����R�[�h�A�������𒊏o���܂�
//
//  �p�����^����
//    AnsiString str	�F�R�}���h���C��������
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �v���O�����N�����Ɏg�p
//
//---------------------------------------------------------------------------
void __fastcall TForm1::ExtractCode(AnsiString str)
{
    int i,n1,m,strlen;

    //������
    USER_COD = 0;
    USER_NAM = "";
    BUMO_COD = "";
    BUMO_NAM = "";

    strlen = str.Length();
    n1 = m = 1;

    for ( i = 1; i <= strlen; i++ ) {
        //��؂�L��","�̌���
        if ( str.SubString(i,1) == "," ) {
            if ( n1 < i ) {
            //n1=i�̎��͕�����NULL
                switch(m){
                //�ϐ��ɕ�������
                    case 1:
                    //USER_COD
                        USER_COD = StrToInt(str.SubString(n1,i - n1));
                        break;
                    case 2:
                    //USER_NAM
                        USER_NAM = str.SubString(n1,i - n1);
                        break;
                    case 3:
                    //BUMO_COD
                        BUMO_COD = str.SubString(n1,i - n1);
                        break;
                    case 4:
                    //BUMO_NAM
                        BUMO_NAM = str.SubString(n1,i - n1);
                        break;
                    default:
                        break;
                }

            }
            //���̕�����J�n�ʒu
            n1 = i + 1;
            m++;

        }
    }
    if ( m <= 4 ) {
        //BUMO_NAM
        BUMO_NAM = str.SubString(n1,strlen - n1 + 1);
    }

    // �������\��
    PnlBumCode->Caption = BUMO_COD;
    PnlBumName->Caption = BUMO_NAM;
    PnlTanCode->Caption = IntToStr(USER_COD);
    PnlTanName->Caption = USER_NAM;

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
void __fastcall TForm1::Edt_ALLChange(TObject *Sender)
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


