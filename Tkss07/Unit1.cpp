//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    �y�o�׌����V�X�e���|�������я��p�^�C�g�����ڃ}�X�^�[�z
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

	SGr_List->ColWidths[0] = 30;		// NO
	SGr_List->ColWidths[1] = 200;       // ���ځi���{��j
	SGr_List->ColWidths[2] = 200;       // ���ځi�p��j
	SGr_List->ColWidths[3] = 493;       // �����ڂ��s���D�Ȃ̂Ńu�����N����쐬
	SGr_List->ColWidths[4] = 0;         // �X�V��
	SGr_List->ColWidths[5] = 0;         // �X�V��
	SGr_List->ColWidths[6] = 0;         // �X�V�ҁi�R�[�h�j
	SGr_List->ColWidths[7] = 0;         // �o�^��
	SGr_List->ColWidths[8] = 0;         // �o�^����
	SGr_List->ColWidths[9] = 0;         // �X�V����
	SGr_List->ColWidths[10] = 0;        // �X�V��
	SGr_List->ColWidths[11] = 0;        // �C����폜�s�t���O
	SGr_List->ColWidths[12] = 0;        // ����No
	SGr_List->ColWidths[13] = 0;        // �\����
	SGr_List->ColWidths[14] = 0;        // �X�V�t���O�i���ёւ����������������̃t���O��ON�ɂȂ�܂��B�j
    									//           �ۑ������̃t���O��ON�̂��̂�Update���܂��B
/*  �f�o�b�O�p
	SGr_List->ColWidths[3] = 0;       	 // �����ڂ��s���D�Ȃ̂Ńu�����N����쐬
	SGr_List->ColWidths[4] = 70;         // �X�V��
	SGr_List->ColWidths[5] = 50;         // �X�V��
	SGr_List->ColWidths[6] = 50;         // �X�V�ҁi�R�[�h�j
	SGr_List->ColWidths[7] = 70;         // �o�^��
	SGr_List->ColWidths[8] = 70;         // �o�^����
	SGr_List->ColWidths[9] = 70;         // �X�V����
	SGr_List->ColWidths[10] = 20;        // �X�V��
	SGr_List->ColWidths[11] = 20;        // �C����폜�s�t���O
	SGr_List->ColWidths[12] = 20;        // ����No
	SGr_List->ColWidths[13] = 20;        // �\����
	SGr_List->ColWidths[14] = 20;        // �X�V�t���O�i���ёւ����������������̃t���O��ON�ɂȂ�܂��B�j
    									 //           �ۑ������̃t���O��ON�̂��̂�Update���܂��B
*/

	SGr_List->Cells[0][0] = " NO";
	SGr_List->Cells[1][0] = "����(���{��)";
	SGr_List->Cells[2][0] = "����(English)";

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
    if( Database1->InTransaction == false )
    {
        Database1->StartTransaction();
        DataSave = false;
    }

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s
	sBuf = "SELECT * FROM KSM21 ORDER BY ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	iRow = 1;
    iKMK_NO_MAX = 0;

	while( !Query1->Eof ){

		// �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
		if( iRow >= SGr_List->RowCount ){
			SGr_List->RowCount = iRow + 1;
		}

		// �O���b�h�Ƀf�[�^���Z�b�g���܂��B
		sBuf = iRow ;
		SGr_List->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

        if( VarIsNull(Query1->FieldValues["KMK_NM_JPN"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KMK_NM_JPN"];
		}
        SGr_List->Cells[1][iRow] = sBuf;   //���ځi���{��j

        if( VarIsNull(Query1->FieldValues["KMK_NM_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KMK_NM_ENG"];
        }
        SGr_List->Cells[2][iRow] = sBuf;   //���ځi���{��j

		sBuf = Query1->FieldValues["UPDYMD"];
        sBuf = sBuf.Insert("/",5);
        sBuf = sBuf.Insert("/",8);
        SGr_List->Cells[4][iRow] = sBuf;   //�ύX��

		sBuf = Query1->FieldValues["UPDCHR"];
		SGr_List->Cells[6][iRow] = sBuf;   //�X�V��(�S���҃R�[�h)
        sBuf = GetTANNAM(sBuf);
		SGr_List->Cells[5][iRow] = sBuf;   //�X�V��

		sBuf = Query1->FieldValues["ADDYMD"];
		SGr_List->Cells[7][iRow] = sBuf;   //�o�^��

		sBuf = Query1->FieldValues["ADDTIM"];
		SGr_List->Cells[8][iRow] =  sBuf;  //�o�^����

		sBuf = Query1->FieldValues["UPDTIM"];
		SGr_List->Cells[9][iRow] = sBuf;   //�X�V����

		sBuf = Query1->FieldValues["UPDCNT"];
		SGr_List->Cells[10][iRow] = sBuf;  //�X�V��

		sBuf = Query1->FieldValues["NOUPD_FLG"];
		SGr_List->Cells[11][iRow] = sBuf;  //�C����폜�s�t���O

		sBuf = Query1->FieldValues["KMK_NO"];
		SGr_List->Cells[12][iRow] = sBuf;  //����No

        // �ő�̍���NO���擾���܂�
	    if( StrToInt(sBuf) > iKMK_NO_MAX ){
        	iKMK_NO_MAX = StrToInt(sBuf);
        }

		sBuf = Query1->FieldValues["ORDER_NO"];
		SGr_List->Cells[13][iRow] = sBuf;  //�\����

		SGr_List->Cells[14][iRow] = "0";   //�X�V�t���O

		// �J�[�\�������ɃZ�b�g����
		Query1->Next();

		iRow += 1;
	}

    // �f�[�^������\�����܂�
    sBuf = iRow-1;
    LblListCnt->Caption = "�����F" + AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;


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


    //�P�s�ڂ������I�����܂�
    SGr_ListSelectCell( SGr_List, 1, 0, true);
	SGr_ListClick( SGr_List );

	Form2->Close();
	Form2->Refresh();
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
    if(SGr_List->Row > 1)
    {
        SGr_List->Row -= 1;
        SGr_List->SetFocus();
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
    if( (SGr_List->RowCount-1) > SGr_List->Row )
    {
        SGr_List->Row += 1;
        SGr_List->SetFocus();
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
//    ��ʉ��ɓ��͂��ꂽ���ڂ��e�[�u���iKSM21�j�ɓo�^���܂�
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
    int i;
    int nRet;
    

    if( !BtnF08->Enabled )    return;

    // ���̓f�[�^�̃`�F�b�N
    if(EdtKMK_NM_JPN->Text.IsEmpty()){
        MessageDlg("���ږ�����͂��Ă��������B", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
        return;
    }

    // �f�[�^�ύX���s�Ȃ��Ă��Ȃ���
    if( EdtKMK_NM_JPN->Text == sEdtKMK_NM_JPN_Old &&
        EdtKMK_NM_ENG->Text == sEdtKMK_NM_ENG_Old ){
        nRet = MessageDlg("�����f�[�^���o�^����܂�����낵���ł���?", mtConfirmation,
               TMsgDlgButtons() << mbYes << mbNo, 0);
        if(nRet == mrNo ) {
            return;
        }
    }

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "�V�K�o�^���ł��D�D�D���΂炭���҂��������B";
    SBr1->Update();

    // �ő區��NO��+1���܂�
    iKMK_NO_MAX++ ;

    sBuf = IntToStr(iKMK_NO_MAX);
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// ����NO
    sBuf = IntToStr(SGr_List->RowCount);
    strcpy( tmpKSM21_DATA.ORDER_NO		,sBuf.c_str() );		// �\����
    sBuf = EdtKMK_NM_JPN->Text;
    strcpy( tmpKSM21_DATA.KMK_NM_JPN	,sBuf.c_str() );		// ���ږ��i���{��j
    sBuf = EdtKMK_NM_ENG->Text;
    strcpy( tmpKSM21_DATA.KMK_NM_ENG	,sBuf.c_str() );		// ���ږ��i�p��j
    sBuf = "0";
    strcpy( tmpKSM21_DATA.NOUPD_FLG		,sBuf.c_str() );		// �C����폜�s�\����
    sBuf = FormatDateTime("yyyymmdd",Date());
    strcpy( tmpKSM21_DATA.ADDYMD		,sBuf.c_str() );		// �o�^��
    strcpy( tmpKSM21_DATA.UPDYMD		,sBuf.c_str() );		// �ύX��
    sBuf = FormatDateTime("hhmm",TDateTime::CurrentTime());
    strcpy( tmpKSM21_DATA.ADDTIM		,sBuf.c_str() );		// �o�^����
    strcpy( tmpKSM21_DATA.UPDTIM		,sBuf.c_str() );		// �ύX����
    sBuf = IntToStr(USER_COD);
    strcpy( tmpKSM21_DATA.UPDCHR		,sBuf.c_str() );		// �X�V��
    sBuf = "0";
    strcpy( tmpKSM21_DATA.UPDCNT		,sBuf.c_str() );		// �X�V��

    //AddData
    if( AddData() == False ){
		return;
    }

    //�V�K�f�[�^��SGr_List�ɕ\��
    // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
    sBuf = SGr_List->RowCount-1;
    SGr_List->Cells[0][SGr_List->RowCount - 1] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No

    sBuf = tmpKSM21_DATA.KMK_NM_JPN;
	SGr_List->Cells[1][SGr_List->RowCount - 1] = sBuf;   //���ځi���{��j

    sBuf = tmpKSM21_DATA.KMK_NM_ENG;
	SGr_List->Cells[2][SGr_List->RowCount - 1] = sBuf;   //���ځi���{��j

	sBuf = tmpKSM21_DATA.UPDYMD;
    sBuf = sBuf.Insert("/",5);
    sBuf = sBuf.Insert("/",8);
    SGr_List->Cells[4][SGr_List->RowCount - 1] = sBuf;   //�ύX��

	sBuf = tmpKSM21_DATA.UPDCHR;
	SGr_List->Cells[6][SGr_List->RowCount - 1] = sBuf;   //�X�V��(�S���҃R�[�h)
    sBuf = GetTANNAM(sBuf);
	SGr_List->Cells[5][SGr_List->RowCount - 1] = sBuf;   //�X�V��

	sBuf = tmpKSM21_DATA.ADDYMD;
	SGr_List->Cells[7][SGr_List->RowCount - 1] = sBuf;   //�o�^��

	sBuf = tmpKSM21_DATA.ADDTIM;
	SGr_List->Cells[8][SGr_List->RowCount - 1] =  sBuf;  //�o�^����

	sBuf = tmpKSM21_DATA.UPDTIM;
	SGr_List->Cells[9][SGr_List->RowCount - 1] = sBuf;   //�X�V����

	sBuf = tmpKSM21_DATA.UPDCNT;
	SGr_List->Cells[10][SGr_List->RowCount - 1] = sBuf;  //�X�V��

	sBuf = tmpKSM21_DATA.NOUPD_FLG;
	SGr_List->Cells[11][SGr_List->RowCount - 1] = sBuf;  //�C����폜�s�t���O

	sBuf = tmpKSM21_DATA.KMK_NO;
	SGr_List->Cells[12][SGr_List->RowCount - 1] = sBuf;  //����No

	sBuf = tmpKSM21_DATA.ORDER_NO;
	SGr_List->Cells[13][SGr_List->RowCount - 1] = sBuf;  //�\����

	SGr_List->Cells[14][SGr_List->RowCount - 1] = "0";   //�X�V�t���O

    // ��s���₷
    SGr_List->RowCount = SGr_List->RowCount + 1;

    // �ŉ��s���N���A�[
    for( i = 0; i < SGr_List->ColCount; i++) {
		SGr_List->Cells[i][SGr_List->RowCount-1]  = "";
    }

    // �V�����s��I��
    SGr_List->Row = SGr_List->RowCount - 1;

    SGr_List->SetFocus();

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // �f�[�^��ύX�����t���O
    DataSave = true;
    SGr_ListSelectCell(Sender,1,SGr_List->RowCount-1,true);

    // �{�^���̏�����
    BtnF01->Enabled = false;
    BtnF02->Enabled = true;
    BtnF03->Enabled = true;
    BtnF04->Enabled = false;
    BtnF05->Enabled = true;
    BtnF06->Enabled = false;
    BtnF07->Enabled = false;
    BtnF08->Enabled = true;
    BtnF09->Enabled = true;
    BtnF10->Enabled = true;
    BtnF11->Enabled = true;
    BtnF12->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�X�F�C���v�{�^�������������̏���
//
//  �@�\����
//    StringGrid�őI�����ꂽ�f�[�^�ɑ΂��ĉ�ʉ��ɓ��͂��ꂽ���ڂɍX�V���܂�
//    �e�[�u���iKSM21�j���X�V���܂�
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

    if( !BtnF09->Enabled )    return;

    if( PnlUPDYMD->Tag == -1){
    	MessageDlg("�C����������܂���B�f�[�^��I�����Ă��������B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    // ���̓f�[�^�̃`�F�b�N
    if(EdtKMK_NM_JPN->Text.IsEmpty()){
        MessageDlg("���ږ�����͂��Ă��������B", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
        return;
    }

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "�C�����ł��D�D�D���΂炭���҂��������B";
    SBr1->Update();


    // �f�[�^���o�b�t�@�Ɋi�[���܂��B
    sBuf = IntToStr(PnlUPDYMD->Tag);
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// ����NO
    sBuf = IntToStr(SGr_List->RowCount);
    strcpy( tmpKSM21_DATA.ORDER_NO		,sBuf.c_str() );		// �\����
    sBuf = EdtKMK_NM_JPN->Text;
    strcpy( tmpKSM21_DATA.KMK_NM_JPN	,sBuf.c_str() );		// ���ږ��i���{��j
    sBuf = EdtKMK_NM_ENG->Text;
    strcpy( tmpKSM21_DATA.KMK_NM_ENG	,sBuf.c_str() );		// ���ږ��i�p��j
    sBuf = FormatDateTime("yyyymmdd",Date());
    strcpy( tmpKSM21_DATA.UPDYMD		,sBuf.c_str() );		// �ύX��
    sBuf = FormatDateTime("hhmm",TDateTime::CurrentTime());
    strcpy( tmpKSM21_DATA.UPDTIM		,sBuf.c_str() );		// �ύX����
    sBuf = IntToStr(USER_COD);
    strcpy( tmpKSM21_DATA.UPDCHR		,sBuf.c_str() );		// �X�V��
    sBuf = IntToStr(PnlUPDCHR->Tag + 1);
    strcpy( tmpKSM21_DATA.UPDCNT		,sBuf.c_str() );		// �X�V��

    //UpdData
    if( UpdData() == False ){
		return;
    }

    //�C���f�[�^��SGr_List�ɕ\��
    // �O���b�h�Ƀf�[�^���Z�b�g���܂��B

    sBuf = tmpKSM21_DATA.KMK_NM_JPN;
	SGr_List->Cells[1][ROWPOINT] = sBuf;   //���ځi���{��j

    sBuf = tmpKSM21_DATA.KMK_NM_ENG;
	SGr_List->Cells[2][ROWPOINT] = sBuf;   //���ځi�p��j

	sBuf = tmpKSM21_DATA.UPDYMD;
    sBuf = sBuf.Insert("/",5);
    sBuf = sBuf.Insert("/",8);
    SGr_List->Cells[4][ROWPOINT] = sBuf;   //�ύX��

	sBuf = tmpKSM21_DATA.UPDCHR;
	SGr_List->Cells[6][ROWPOINT] = sBuf;   //�X�V��(�S���҃R�[�h)
    sBuf = GetTANNAM(sBuf);
	SGr_List->Cells[5][ROWPOINT] = sBuf;   //�X�V��

	sBuf = tmpKSM21_DATA.UPDTIM;
	SGr_List->Cells[9][ROWPOINT] = sBuf;   //�X�V����

	sBuf = tmpKSM21_DATA.UPDCNT;
	SGr_List->Cells[10][ROWPOINT] = sBuf;  //�X�V��

    SGr_List->SetFocus();

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // �f�[�^��ύX�����t���O
    DataSave = true;
    SGr_ListSelectCell(Sender,1,ROWPOINT,true);

    // �{�^���̏�����
    BtnF01->Enabled = false;
    BtnF02->Enabled = true;
    BtnF03->Enabled = true;
    BtnF04->Enabled = false;
    BtnF05->Enabled = true;
    BtnF06->Enabled = false;
    BtnF07->Enabled = false;
    BtnF08->Enabled = true;
    BtnF09->Enabled = true;
    BtnF10->Enabled = true;
    BtnF11->Enabled = true;
    BtnF12->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�O�F�폜�v�{�^�������������̏���
//
//  �@�\����
//    StringGrid�őI�����ꂽ�f�[�^���폜���܂�
//    �e�[�u���iKSM21�j�̃��R�[�h���폜���܂�
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
    int			i;
    AnsiString	sBuf;

    if( !BtnF10->Enabled )    return;

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
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// ����NO

    // DelData
    if( DelData() == False ){
        return;
    }

    for( i = SGr_List->Row; i < (SGr_List->RowCount - 1); i++) {
        // �O���b�h�̈�s���폜���܂��B
        SGr_List->Cells[1][i] = SGr_List->Cells[1][i+1];
        SGr_List->Cells[2][i] = SGr_List->Cells[2][i+1];
        SGr_List->Cells[3][i] = SGr_List->Cells[3][i+1];
        SGr_List->Cells[4][i] = SGr_List->Cells[4][i+1];
        SGr_List->Cells[5][i] = SGr_List->Cells[5][i+1];
        SGr_List->Cells[6][i] = SGr_List->Cells[6][i+1];
        SGr_List->Cells[7][i] = SGr_List->Cells[7][i+1];
        SGr_List->Cells[8][i] = SGr_List->Cells[8][i+1];
        SGr_List->Cells[9][i] = SGr_List->Cells[9][i+1];
        SGr_List->Cells[10][i] = SGr_List->Cells[10][i+1];
        SGr_List->Cells[11][i] = SGr_List->Cells[11][i+1];
        SGr_List->Cells[12][i] = SGr_List->Cells[12][i+1];
        SGr_List->Cells[13][i] = SGr_List->Cells[13][i+1];
        SGr_List->Cells[14][i] = SGr_List->Cells[14][i+1];
    }

    // ��s���炷
    SGr_List->RowCount = SGr_List->RowCount - 1;
    SGr_List->Cells[1][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[2][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[3][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[4][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[5][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[6][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[7][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[8][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[9][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[10][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[11][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[12][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[13][SGr_List->RowCount - 1] = "";
    SGr_List->Cells[14][SGr_List->RowCount - 1] = "";

    // �V�����s��I��
    if( SGr_List->RowCount == SGr_List->Row){
        SGr_List->Row = SGr_List->Row - 1;
    }
    else {
        SGr_List->Row = SGr_List->Row;
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();
    SGr_ListSelectCell(Sender,1,SGr_List->Row,true);

    // �f�[�^��ύX�����t���O
    DataSave = true;

    // �{�^����Ԃ̕ύX
    BtnF01->Enabled = false;
    BtnF02->Enabled = true;
    BtnF03->Enabled = true;
    BtnF04->Enabled = false;
    BtnF05->Enabled = true;
    BtnF06->Enabled = false;
    BtnF07->Enabled = false;
    BtnF08->Enabled = true;
    BtnF09->Enabled = true;
    BtnF10->Enabled = true;
    BtnF11->Enabled = true;
    BtnF12->Enabled = true;

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
    		if( SGr_List->Cells[14][i] == "1" ){
                UpdData_ORDER_NO(SGr_List->Cells[12][i],SGr_List->Cells[13][i]);
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
//    OnCloseQuery�C�x���g�FClose ���\�b�h���Ăяo���ꂽ�Ƃ��܂��̓��[�U�[��
//          �t�H�[���̃V�X�e�����j���[�Łm����n��I�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �X�V�����f�[�^�����ۑ��̏ꍇ�A�ۑ����邩���Ȃ������m�F���܂��B
//    �ۑ�����ꍇ�́A�f�[�^���m��(Commit)���܂��B
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
    Query2->Close();

	Database1->Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�[�^��ǉ����܂��B
//
//  �@�\����
//    �u�e�W�F�V�K�o�^�v���̃f�[�^�ǉ��iKSM21�j����
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::AddData()
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf = "insert into KSM21(";
    sBuf += " KMK_NO, ORDER_NO, KMK_NM_JPN, KMK_NM_ENG, NOUPD_FLG, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
    sBuf += " )";

    sBuf += " VALUES(";
    sBuf += AnsiString(tmpKSM21_DATA.KMK_NO) 		+  "," ;	//����NO
    sBuf += AnsiString(tmpKSM21_DATA.ORDER_NO)		+  ",'";	//�\����
    sBuf += AnsiString(tmpKSM21_DATA.KMK_NM_JPN)	+ "','";	//���ږ��i���{��j
    sBuf += AnsiString(tmpKSM21_DATA.KMK_NM_ENG)	+ "'," ;	//���ږ��i�p��j
    sBuf += AnsiString(tmpKSM21_DATA.NOUPD_FLG)		+  ",'";	//�C���E�폜�s�t���O
    sBuf += AnsiString(tmpKSM21_DATA.ADDYMD)		+ "','";	//�o�^��
    sBuf += AnsiString(tmpKSM21_DATA.ADDTIM)		+ "','";	//�o�^����
    sBuf += Trim(AnsiString(tmpKSM21_DATA.UPDYMD))	+ "','";	//�X�V��
    sBuf += AnsiString(tmpKSM21_DATA.UPDTIM)		+ "'," ;	//�X�V����
    sBuf += AnsiString(tmpKSM21_DATA.UPDCHR)		+  "," ;	//�X�V��
    sBuf += AnsiString(tmpKSM21_DATA.UPDCNT)		+  ")" ;	//�X�V��

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
//    �Ȃ��B
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::UpdData()
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf  = "update KSM21 set";
    sBuf += " KMK_NM_JPN='"	+ AnsiString(tmpKSM21_DATA.KMK_NM_JPN)	+ "',";	//���ږ��i���{��j
    sBuf += " KMK_NM_ENG='"	+ AnsiString(tmpKSM21_DATA.KMK_NM_ENG)	+ "',";	//���ږ��i�p��j
    sBuf += " UPDYMD='"		+ Trim(AnsiString(tmpKSM21_DATA.UPDYMD))+ "',";	//�X�V��
    sBuf += " UPDTIM='"		+ AnsiString(tmpKSM21_DATA.UPDTIM)		+ "',";	//�X�V����
    sBuf += " UPDCHR="		+ AnsiString(tmpKSM21_DATA.UPDCHR)		+  ",";	//�X�V��
    sBuf += " UPDCNT="		+ AnsiString(tmpKSM21_DATA.UPDCNT)			  ;	//�X�V��
    sBuf += " WHERE KMK_NO="+ AnsiString(tmpKSM21_DATA.KMK_NO)			  ; //����NO

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
bool __fastcall TForm1::UpdData_ORDER_NO(AnsiString sKMK_NO, AnsiString sORDER_NO)
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf  = "update KSM21 set";
    sBuf += " ORDER_NO="		+ Trim(sORDER_NO)	  ;	//�\����
    sBuf += " WHERE KMK_NO="	+ Trim(sKMK_NO)		  ; //����NO

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
//    �Ȃ��B
//
//  �߂�l
//    bool				�Ftrue = �����Afalse = ���s
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::DelData()
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����쐬
    sBuf = "select * from KSM21 ";
    sBuf += " WHERE KMK_NO="+ AnsiString(tmpKSM21_DATA.KMK_NO)  ; //����NO

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
    sBuf = "DELETE from KSM21";
    sBuf += " WHERE KMK_NO="+ AnsiString(tmpKSM21_DATA.KMK_NO)		  ; //����NO

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
	if( SGr_List->Top < Pnl_List->Height &&
        Pnl_List->Height - SGr_List->Top - iBMarg > 0 ){
		SGr_List->Height = Pnl_List->Height - SGr_List->Top - iBMarg;
	} else{
		SGr_List->Height = 0;
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
void __fastcall TForm1::BtnListUpClick(TObject *Sender)
{
    int			i;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;


    iChgRow1 = SGr_List->Selection.Top;
    iChgRow2 = SGr_List->Selection.Top - 1;
    iChgRow3 = SGr_List->Selection.Bottom;

    if( iChgRow1 <= 1) return;
    if( iChgRow1 >= SGr_List->RowCount - 1) return;

    if( iChgRow3 >= SGr_List->RowCount - 1)
    	iChgRow3 = SGr_List->Selection.Bottom = SGr_List->RowCount - 2;

    // ���\�����͓���ւ������ɂ��̑��̍��ڂ����ւ��A�X�V�t���O(Cells[14])��ON�ɂ��܂��B

    // ����ւ���̃f�[�^���o�b�N�A�b�v
    sBuf = SGr_List->Cells[12][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// ����NO
    //sBuf = SGr_List->Cells[13][iChgRow2];
    //strcpy( tmpKSM21_DATA.ORDER_NO		,sBuf.c_str() );		// �\����
    sBuf = SGr_List->Cells[1][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NM_JPN	,sBuf.c_str() );		// ���ږ��i���{��j
    sBuf = SGr_List->Cells[2][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NM_ENG	,sBuf.c_str() );		// ���ږ��i�p��j
    sBuf = SGr_List->Cells[11][iChgRow2];
    strcpy( tmpKSM21_DATA.NOUPD_FLG		,sBuf.c_str() );		// �C����폜�s�\����
    sBuf = SGr_List->Cells[7][iChgRow2];
    strcpy( tmpKSM21_DATA.ADDYMD		,sBuf.c_str() );		// �o�^��
    sBuf = SGr_List->Cells[8][iChgRow2];
    strcpy( tmpKSM21_DATA.ADDTIM		,sBuf.c_str() );		// �o�^����
    sBuf = SGr_List->Cells[4][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDYMD		,sBuf.c_str() );		// �ύX��
    sBuf = SGr_List->Cells[9][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDTIM		,sBuf.c_str() );		// �ύX����
    sBuf = SGr_List->Cells[5][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDNAM		,sBuf.c_str() );		// �X�V�ҁi���́j
    sBuf = SGr_List->Cells[6][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDCHR		,sBuf.c_str() );		// �X�V�ҁi�R�[�h�j
    sBuf = SGr_List->Cells[10][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDCNT		,sBuf.c_str() );		// �X�V��

	// �㉺�����ւ��܂�
    for( i=iChgRow2; i<iChgRow3 ; i++ ) {
    	SGr_List->Cells[1][i] = SGr_List->Cells[1][i + 1];
    	SGr_List->Cells[2][i] = SGr_List->Cells[2][i + 1];
    	SGr_List->Cells[3][i] = SGr_List->Cells[3][i + 1];
    	SGr_List->Cells[4][i] = SGr_List->Cells[4][i + 1];
    	SGr_List->Cells[5][i] = SGr_List->Cells[5][i + 1];
    	SGr_List->Cells[6][i] = SGr_List->Cells[6][i + 1];
    	SGr_List->Cells[7][i] = SGr_List->Cells[7][i + 1];
    	SGr_List->Cells[8][i] = SGr_List->Cells[8][i + 1];
    	SGr_List->Cells[9][i] = SGr_List->Cells[9][i + 1];
    	SGr_List->Cells[10][i] = SGr_List->Cells[10][i + 1];
    	SGr_List->Cells[11][i] = SGr_List->Cells[11][i + 1];
    	SGr_List->Cells[12][i] = SGr_List->Cells[12][i + 1];
    	//SGr_List->Cells[13][iChgRow2] = SGr_List->Cells[13][i + 1];
		SGr_List->Cells[14][i] = "1";
    }

    // �o�b�N�A�b�v�����f�[�^��߂��܂�
	SGr_List->Cells[12][iChgRow3] = tmpKSM21_DATA.KMK_NO	;	// ����NO
	//SGr_List->Cells[13][iChgRow3] = tmpKSM21_DATA.ORDER_NO	;	// �\����
	SGr_List->Cells[1][iChgRow3]  = tmpKSM21_DATA.KMK_NM_JPN;	// ���ږ��i���{��j
	SGr_List->Cells[2][iChgRow3]  = tmpKSM21_DATA.KMK_NM_ENG;	// ���ږ��i�p��j
	SGr_List->Cells[11][iChgRow3] = tmpKSM21_DATA.NOUPD_FLG	;	// �C����폜�s�\����
	SGr_List->Cells[7][iChgRow3]  = tmpKSM21_DATA.ADDYMD	;	// �o�^��
	SGr_List->Cells[8][iChgRow3]  = tmpKSM21_DATA.ADDTIM	;	// �o�^����
	SGr_List->Cells[4][iChgRow3]  = tmpKSM21_DATA.UPDYMD	;	// �ύX��
	SGr_List->Cells[9][iChgRow3]  = tmpKSM21_DATA.UPDTIM	;	// �ύX����
	SGr_List->Cells[6][iChgRow3]  = tmpKSM21_DATA.UPDCHR	;	// �X�V�ҁi�R�[�h�j
	SGr_List->Cells[5][iChgRow3]  = tmpKSM21_DATA.UPDNAM	;	// �X�V�ҁi���́j
	SGr_List->Cells[10][iChgRow3] = tmpKSM21_DATA.UPDCNT	;	// �X�V��
	SGr_List->Cells[14][iChgRow3] = "1";

    // �I���J�[�\���������ɏ�Ɉړ����܂�
    SGr_List->Row--;
	myRect.Left		= SGr_List->Selection.Left;
	myRect.Top		= iChgRow1 - 1;
	myRect.Right	= SGr_List->Selection.Right;
	myRect.Bottom	= iChgRow3 - 1;
    SGr_List->Selection	= myRect;
    SGr_ListSelectCell(Sender,1,SGr_List->Row,true);

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
void __fastcall TForm1::BtnListDownClick(TObject *Sender)
{
    int			i;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;


    iChgRow1 = SGr_List->Selection.Top;
    iChgRow2 = SGr_List->Selection.Bottom + 1;
    iChgRow3 = SGr_List->Selection.Bottom;

    if( iChgRow2 >= SGr_List->RowCount - 1) return;

    // ���\�����͓���ւ������ɂ��̑��̍��ڂ����ւ��A�X�V�t���O(Cells[14])��ON�ɂ��܂��B

    // ����ւ���̃f�[�^���o�b�N�A�b�v
    sBuf = SGr_List->Cells[12][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// ����NO
    //sBuf = SGr_List->Cells[13][iChgRow2];
    //strcpy( tmpKSM21_DATA.ORDER_NO		,sBuf.c_str() );		// �\����
    sBuf = SGr_List->Cells[1][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NM_JPN	,sBuf.c_str() );		// ���ږ��i���{��j
    sBuf = SGr_List->Cells[2][iChgRow2];
    strcpy( tmpKSM21_DATA.KMK_NM_ENG	,sBuf.c_str() );		// ���ږ��i�p��j
    sBuf = SGr_List->Cells[11][iChgRow2];
    strcpy( tmpKSM21_DATA.NOUPD_FLG		,sBuf.c_str() );		// �C����폜�s�\����
    sBuf = SGr_List->Cells[7][iChgRow2];
    strcpy( tmpKSM21_DATA.ADDYMD		,sBuf.c_str() );		// �o�^��
    sBuf = SGr_List->Cells[8][iChgRow2];
    strcpy( tmpKSM21_DATA.ADDTIM		,sBuf.c_str() );		// �o�^����
    sBuf = SGr_List->Cells[4][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDYMD		,sBuf.c_str() );		// �ύX��
    sBuf = SGr_List->Cells[9][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDTIM		,sBuf.c_str() );		// �ύX����
    sBuf = SGr_List->Cells[5][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDNAM		,sBuf.c_str() );		// �X�V�ҁi���́j
    sBuf = SGr_List->Cells[6][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDCHR		,sBuf.c_str() );		// �X�V�ҁi�R�[�h�j
    sBuf = SGr_List->Cells[10][iChgRow2];
    strcpy( tmpKSM21_DATA.UPDCNT		,sBuf.c_str() );		// �X�V��

	// �㉺�����ւ��܂�
    for( i=iChgRow2; i>iChgRow1 ; i-- ) {
    	SGr_List->Cells[1][i] = SGr_List->Cells[1][i - 1];
    	SGr_List->Cells[2][i] = SGr_List->Cells[2][i - 1];
    	SGr_List->Cells[3][i] = SGr_List->Cells[3][i - 1];
    	SGr_List->Cells[4][i] = SGr_List->Cells[4][i - 1];
    	SGr_List->Cells[5][i] = SGr_List->Cells[5][i - 1];
    	SGr_List->Cells[6][i] = SGr_List->Cells[6][i - 1];
    	SGr_List->Cells[7][i] = SGr_List->Cells[7][i - 1];
    	SGr_List->Cells[8][i] = SGr_List->Cells[8][i - 1];
    	SGr_List->Cells[9][i] = SGr_List->Cells[9][i - 1];
    	SGr_List->Cells[10][i] = SGr_List->Cells[10][i - 1];
    	SGr_List->Cells[11][i] = SGr_List->Cells[11][i - 1];
    	SGr_List->Cells[12][i] = SGr_List->Cells[12][i - 1];
    	//SGr_List->Cells[13][iChgRow2] = SGr_List->Cells[13][i - 1];
		SGr_List->Cells[14][i] = "1";
    }

    // �㉺�����ւ��܂��B
	SGr_List->Cells[12][iChgRow1] = tmpKSM21_DATA.KMK_NO	;	// ����NO
	//SGr_List->Cells[13][iChgRow1] = tmpKSM21_DATA.ORDER_NO	;	// �\����
	SGr_List->Cells[1][iChgRow1]  = tmpKSM21_DATA.KMK_NM_JPN;	// ���ږ��i���{��j
	SGr_List->Cells[2][iChgRow1]  = tmpKSM21_DATA.KMK_NM_ENG;	// ���ږ��i�p��j
	SGr_List->Cells[11][iChgRow1] = tmpKSM21_DATA.NOUPD_FLG	;	// �C����폜�s�\����
	SGr_List->Cells[7][iChgRow1]  = tmpKSM21_DATA.ADDYMD	;	// �o�^��
	SGr_List->Cells[8][iChgRow1]  = tmpKSM21_DATA.ADDTIM	;	// �o�^����
	SGr_List->Cells[4][iChgRow1]  = tmpKSM21_DATA.UPDYMD	;	// �ύX��
	SGr_List->Cells[9][iChgRow1]  = tmpKSM21_DATA.UPDTIM	;	// �ύX����
	SGr_List->Cells[6][iChgRow1]  = tmpKSM21_DATA.UPDCHR	;	// �X�V�ҁi�R�[�h�j
	SGr_List->Cells[5][iChgRow1]  = tmpKSM21_DATA.UPDNAM	;	// �X�V�ҁi���́j
	SGr_List->Cells[10][iChgRow1] = tmpKSM21_DATA.UPDCNT	;	// �X�V��
    SGr_List->Cells[14][iChgRow1] = "1";

    // �I���J�[�\���������ɉ��Ɉړ����܂�
    SGr_List->Row++;
	myRect.Left		= SGr_List->Selection.Left;
	myRect.Top		= iChgRow1 + 1;
	myRect.Right	= SGr_List->Selection.Right;
	myRect.Bottom	= iChgRow3 + 1;
    SGr_List->Selection	= myRect;
    SGr_ListSelectCell(Sender,1,SGr_List->Row,true);

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
    iRowSelTop    = SGr_List->Selection.Top;
    iRowSelBottom = SGr_List->Selection.Bottom;
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
    KSM21_DATA  *pKSM21_DATA;
	TGridRect	myRect;


    // �͈͑I���������̂Ǝ��ۂɈړ��������ꂽ�s�̎w��ʒu���قȂ鎞�́A�G���[
    if( FromIndex < iRowSelTop || FromIndex > iRowSelBottom ){
        RowExchange(FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�I��͈͂�����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // �͈͑I�������ړ��悪�A���͈̔͑I����ւ̈ړ��̎��́A�G���[
    if( ToIndex >= iRowSelTop && ToIndex <= iRowSelBottom ){
        RowExchange(FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�ړ��悪����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // �ŉ��s�̉��ֈړ��̎��́A�G���[
    if( ToIndex >= SGr_List->RowCount - 1 ){
        RowExchange(FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�ړ��悪����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // �͈͑I���������̂ɍŉ��s���܂ގ��́A�G���[
    if( SGr_List->RowCount - 1 <= iRowSelBottom ){
        RowExchange(FromIndex,ToIndex);
        // �G���[���b�Z�[�W
    	MessageDlg("�I��͈͂�����������܂���B", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    if( FromIndex < ToIndex ){
        iStart = iRowSelTop;
        iEnd   = ToIndex;

		// �\���������ւ��܂�
    	sBuf = SGr_List->Cells[13][ToIndex];
		for( i = ToIndex; i > FromIndex; i-- ){
			SGr_List->Cells[13][i] = SGr_List->Cells[13][i-1];
    	}
    	SGr_List->Cells[13][FromIndex] = sBuf;
    }
    else {
        iStart = ToIndex;
        iEnd   = iRowSelBottom;

		// �\���������ւ��܂�
        sBuf = SGr_List->Cells[13][ToIndex];
		for( i = ToIndex; i < FromIndex; i++ ){
			SGr_List->Cells[13][i] = SGr_List->Cells[13][i+1];
    	}
    	SGr_List->Cells[13][FromIndex] = sBuf;
    }

	// �sNo�����ɖ߂��܂�
	for( i = iStart; i <= iEnd; i++ ){
		sBuf = i ;
		if( i < SGr_List->RowCount - 1 ){
			SGr_List->Cells[0][i] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;
   	    	SGr_List->Cells[14][i] = "1";						// �X�V�t���OON
		}
        else{
			SGr_List->Cells[0][i] = "";
   	    	SGr_List->Cells[14][i] = "";
        }
    }

    // �R�s�[�̌����m�ۂ��܂�
    CopyCnt = iRowSelBottom - iRowSelTop;

    // �������̊m��
    hMemCopy = GlobalAlloc( GHND, sizeof(struct KSM21_DATA) * CopyCnt );
    if( hMemCopy == NULL ){
        SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pKSM21_DATA = (struct KSM21_DATA *)GlobalLock(hMemCopy);
    if( hMemCopy == NULL ){
        SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
        SBr1->Update();
        Beep();
        return;
    }

    if( FromIndex < ToIndex ){

	    // �I������Ă���͈͂��������Ɋi�[���܂�
    	for( i=iRowSelTop, k=0; i<iRowSelBottom; i++, k++ ) {
    		sBuf = SGr_List->Cells[12][i];
    		strcpy( pKSM21_DATA[k].KMK_NO		,sBuf.c_str() );		// ����NO
    		//sBuf = SGr_List->Cells[13][i];
    		//strcpy( pKSM21_DATA[k].ORDER_NO		,sBuf.c_str() );		// �\����
    		sBuf = SGr_List->Cells[1][i];
    		strcpy( pKSM21_DATA[k].KMK_NM_JPN	,sBuf.c_str() );		// ���ږ��i���{��j
    		sBuf = SGr_List->Cells[2][i];
    		strcpy( pKSM21_DATA[k].KMK_NM_ENG	,sBuf.c_str() );		// ���ږ��i�p��j
    		sBuf = SGr_List->Cells[11][i];
    		strcpy( pKSM21_DATA[k].NOUPD_FLG	,sBuf.c_str() );		// �C����폜�s�\����
			sBuf = SGr_List->Cells[7][i];
    		strcpy( pKSM21_DATA[k].ADDYMD		,sBuf.c_str() );		// �o�^��
    		sBuf = SGr_List->Cells[8][i];
    		strcpy( pKSM21_DATA[k].ADDTIM		,sBuf.c_str() );		// �o�^����
    		sBuf = SGr_List->Cells[4][i];
    		strcpy( pKSM21_DATA[k].UPDYMD		,sBuf.c_str() );		// �ύX��
    		sBuf = SGr_List->Cells[9][i];
    		strcpy( pKSM21_DATA[k].UPDTIM		,sBuf.c_str() );		// �ύX����
    		sBuf = SGr_List->Cells[6][i];
    		strcpy( pKSM21_DATA[k].UPDCHR		,sBuf.c_str() );		// �X�V�ҁi�R�[�h�j
    		sBuf = SGr_List->Cells[5][i];
    		strcpy( pKSM21_DATA[k].UPDNAM		,sBuf.c_str() );		// �X�V�ҁi���́j
    		sBuf = SGr_List->Cells[10][i];
    		strcpy( pKSM21_DATA[k].UPDCNT		,sBuf.c_str() );		// �X�V��
    	}

		// �����I����e���ړ����܂�
		for( i = iRowSelBottom; i <= ToIndex; i++ ){
			SGr_List->Cells[1][i-CopyCnt] = SGr_List->Cells[1][i];
			SGr_List->Cells[2][i-CopyCnt] = SGr_List->Cells[2][i];
			SGr_List->Cells[3][i-CopyCnt] = SGr_List->Cells[3][i];
			SGr_List->Cells[4][i-CopyCnt] = SGr_List->Cells[4][i];
			SGr_List->Cells[5][i-CopyCnt] = SGr_List->Cells[5][i];
			SGr_List->Cells[6][i-CopyCnt] = SGr_List->Cells[6][i];
			SGr_List->Cells[7][i-CopyCnt] = SGr_List->Cells[7][i];
			SGr_List->Cells[8][i-CopyCnt] = SGr_List->Cells[8][i];
			SGr_List->Cells[9][i-CopyCnt] = SGr_List->Cells[9][i];
			SGr_List->Cells[10][i-CopyCnt] = SGr_List->Cells[10][i];
			SGr_List->Cells[11][i-CopyCnt] = SGr_List->Cells[11][i];
			SGr_List->Cells[12][i-CopyCnt] = SGr_List->Cells[12][i];
			//SGr_List->Cells[13][i-CopyCnt] = SGr_List->Cells[13][i];
			SGr_List->Cells[14][i-CopyCnt] = SGr_List->Cells[14][i];
    	}

        // �����ړ����ꂽ�s�𐳂����ʒu�Ɉړ����܂��B
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
			SGr_List->Cells[1][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[1][ToIndex];
			SGr_List->Cells[2][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[2][ToIndex];
			SGr_List->Cells[3][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[3][ToIndex];
			SGr_List->Cells[4][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[4][ToIndex];
			SGr_List->Cells[5][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[5][ToIndex];
			SGr_List->Cells[6][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[6][ToIndex];
			SGr_List->Cells[7][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[7][ToIndex];
			SGr_List->Cells[8][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[8][ToIndex];
			SGr_List->Cells[9][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[9][ToIndex];
			SGr_List->Cells[10][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[10][ToIndex];
			SGr_List->Cells[11][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[11][ToIndex];
			SGr_List->Cells[12][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[12][ToIndex];
			//SGr_List->Cells[13][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[13][ToIndex];
			SGr_List->Cells[14][ToIndex-CopyCnt+iSkip] = SGr_List->Cells[14][ToIndex];
        }

		// �������Ɋi�[�������e��߂��܂�
        i = ToIndex - CopyCnt;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
            	SGr_List->Cells[12][i+k] = pKSM21_DATA[m].KMK_NO		;		// ����NO
    			//SGr_List->Cells[13][i+k] = pKSM21_DATA[m].ORDER_NO		;		// �\����
    			SGr_List->Cells[1][i+k]  = pKSM21_DATA[m].KMK_NM_JPN	;		// ���ږ��i���{��j
    			SGr_List->Cells[2][i+k]  = pKSM21_DATA[m].KMK_NM_ENG	;		// ���ږ��i�p��j
    			SGr_List->Cells[11][i+k] = pKSM21_DATA[m].NOUPD_FLG		;		// �C����폜�s�\����
				SGr_List->Cells[7][i+k]  = pKSM21_DATA[m].ADDYMD		;		// �o�^��
    			SGr_List->Cells[8][i+k]  = pKSM21_DATA[m].ADDTIM		;		// �o�^����
    			SGr_List->Cells[4][i+k]  = pKSM21_DATA[m].UPDYMD		;		// �ύX��
    			SGr_List->Cells[9][i+k]  = pKSM21_DATA[m].UPDTIM		;		// �ύX����
    			SGr_List->Cells[6][i+k]  = pKSM21_DATA[m].UPDCHR		;		// �X�V�ҁi�R�[�h�j
    			SGr_List->Cells[5][i+k]  = pKSM21_DATA[m].UPDNAM		;		// �X�V�ҁi���́j
    			SGr_List->Cells[10][i+k] = pKSM21_DATA[m].UPDCNT		;		// �X�V��
            	SGr_List->Cells[14][i+k] = "1"							;
				m++;
        	}
        }

    	// �ړ���̍s��I��͈͂����肵�܂�
		myRect.Left		= SGr_List->Selection.Left;
		myRect.Top		= ToIndex - CopyCnt;
		myRect.Right	= SGr_List->Selection.Right;
		myRect.Bottom	= myRect.Top + CopyCnt;
    }
    else {

	    // �I������Ă���͈͂��������Ɋi�[���܂�
    	for( i=iRowSelTop+1, k=0; i<=iRowSelBottom; i++, k++ ) {
    		sBuf = SGr_List->Cells[12][i];
    		strcpy( pKSM21_DATA[k].KMK_NO		,sBuf.c_str() );		// ����NO
    		//sBuf = SGr_List->Cells[13][i];
    		//strcpy( pKSM21_DATA[k].ORDER_NO		,sBuf.c_str() );		// �\����
    		sBuf = SGr_List->Cells[1][i];
    		strcpy( pKSM21_DATA[k].KMK_NM_JPN	,sBuf.c_str() );		// ���ږ��i���{��j
    		sBuf = SGr_List->Cells[2][i];
    		strcpy( pKSM21_DATA[k].KMK_NM_ENG	,sBuf.c_str() );		// ���ږ��i�p��j
    		sBuf = SGr_List->Cells[11][i];
    		strcpy( pKSM21_DATA[k].NOUPD_FLG	,sBuf.c_str() );		// �C����폜�s�\����
			sBuf = SGr_List->Cells[7][i];
    		strcpy( pKSM21_DATA[k].ADDYMD		,sBuf.c_str() );		// �o�^��
    		sBuf = SGr_List->Cells[8][i];
    		strcpy( pKSM21_DATA[k].ADDTIM		,sBuf.c_str() );		// �o�^����
    		sBuf = SGr_List->Cells[4][i];
    		strcpy( pKSM21_DATA[k].UPDYMD		,sBuf.c_str() );		// �ύX��
    		sBuf = SGr_List->Cells[9][i];
    		strcpy( pKSM21_DATA[k].UPDTIM		,sBuf.c_str() );		// �ύX����
    		sBuf = SGr_List->Cells[6][i];
    		strcpy( pKSM21_DATA[k].UPDCHR		,sBuf.c_str() );		// �X�V�ҁi�R�[�h�j
    		sBuf = SGr_List->Cells[5][i];
    		strcpy( pKSM21_DATA[k].UPDNAM		,sBuf.c_str() );		// �X�V�ҁi���́j
    		sBuf = SGr_List->Cells[10][i];
    		strcpy( pKSM21_DATA[k].UPDCNT		,sBuf.c_str() );		// �X�V��
    	}

		// �����I����e���ړ����܂�
		for( i = iRowSelTop; i >= ToIndex; i-- ){
			SGr_List->Cells[1][i+CopyCnt] = SGr_List->Cells[1][i];
			SGr_List->Cells[2][i+CopyCnt] = SGr_List->Cells[2][i];
			SGr_List->Cells[3][i+CopyCnt] = SGr_List->Cells[3][i];
			SGr_List->Cells[4][i+CopyCnt] = SGr_List->Cells[4][i];
			SGr_List->Cells[5][i+CopyCnt] = SGr_List->Cells[5][i];
			SGr_List->Cells[6][i+CopyCnt] = SGr_List->Cells[6][i];
			SGr_List->Cells[7][i+CopyCnt] = SGr_List->Cells[7][i];
			SGr_List->Cells[8][i+CopyCnt] = SGr_List->Cells[8][i];
			SGr_List->Cells[9][i+CopyCnt] = SGr_List->Cells[9][i];
			SGr_List->Cells[10][i+CopyCnt] = SGr_List->Cells[10][i];
			SGr_List->Cells[11][i+CopyCnt] = SGr_List->Cells[11][i];
			SGr_List->Cells[12][i+CopyCnt] = SGr_List->Cells[12][i];
			//SGr_List->Cells[13][i+CopyCnt] = SGr_List->Cells[13][i];
			SGr_List->Cells[14][i+CopyCnt] = SGr_List->Cells[14][i];
    	}

        // �����ړ����ꂽ�s�𐳂����ʒu�Ɉړ����܂��B
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
			SGr_List->Cells[1][ToIndex+iSkip] = SGr_List->Cells[1][ToIndex];
			SGr_List->Cells[2][ToIndex+iSkip] = SGr_List->Cells[2][ToIndex];
			SGr_List->Cells[3][ToIndex+iSkip] = SGr_List->Cells[3][ToIndex];
			SGr_List->Cells[4][ToIndex+iSkip] = SGr_List->Cells[4][ToIndex];
			SGr_List->Cells[5][ToIndex+iSkip] = SGr_List->Cells[5][ToIndex];
			SGr_List->Cells[6][ToIndex+iSkip] = SGr_List->Cells[6][ToIndex];
			SGr_List->Cells[7][ToIndex+iSkip] = SGr_List->Cells[7][ToIndex];
			SGr_List->Cells[8][ToIndex+iSkip] = SGr_List->Cells[8][ToIndex];
			SGr_List->Cells[9][ToIndex+iSkip] = SGr_List->Cells[9][ToIndex];
			SGr_List->Cells[10][ToIndex+iSkip] = SGr_List->Cells[10][ToIndex];
			SGr_List->Cells[11][ToIndex+iSkip] = SGr_List->Cells[11][ToIndex];
			SGr_List->Cells[12][ToIndex+iSkip] = SGr_List->Cells[12][ToIndex];
			//SGr_List->Cells[13][ToIndex+iSkip] = SGr_List->Cells[13][ToIndex];
			SGr_List->Cells[14][ToIndex+iSkip] = SGr_List->Cells[14][ToIndex];
        }

		// �������Ɋi�[�������e��߂��܂�
        i = ToIndex;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
            	SGr_List->Cells[12][i+k] = pKSM21_DATA[m].KMK_NO		;		// ����NO
    			//SGr_List->Cells[13][i+k] = pKSM21_DATA[m].ORDER_NO		;		// �\����
    			SGr_List->Cells[1][i+k]  = pKSM21_DATA[m].KMK_NM_JPN	;		// ���ږ��i���{��j
    			SGr_List->Cells[2][i+k]  = pKSM21_DATA[m].KMK_NM_ENG	;		// ���ږ��i�p��j
    			SGr_List->Cells[11][i+k] = pKSM21_DATA[m].NOUPD_FLG		;		// �C����폜�s�\����
				SGr_List->Cells[7][i+k]  = pKSM21_DATA[m].ADDYMD		;		// �o�^��
    			SGr_List->Cells[8][i+k]  = pKSM21_DATA[m].ADDTIM		;		// �o�^����
    			SGr_List->Cells[4][i+k]  = pKSM21_DATA[m].UPDYMD		;		// �ύX��
    			SGr_List->Cells[9][i+k]  = pKSM21_DATA[m].UPDTIM		;		// �ύX����
    			SGr_List->Cells[6][i+k]  = pKSM21_DATA[m].UPDCHR		;		// �X�V�ҁi�R�[�h�j
    			SGr_List->Cells[5][i+k]  = pKSM21_DATA[m].UPDNAM		;		// �X�V�ҁi���́j
    			SGr_List->Cells[10][i+k] = pKSM21_DATA[m].UPDCNT		;		// �X�V��
            	SGr_List->Cells[14][i+k] = "1"							;
				m++;
        	}
        }

    	// �ړ���̍s��I��͈͂����肵�܂�
		myRect.Left		= SGr_List->Selection.Left;
		myRect.Top		= ToIndex;
		myRect.Right	= SGr_List->Selection.Right;
		myRect.Bottom	= ToIndex + CopyCnt;
    }

    // �������̊J��
    if( hMemCopy ){
        GlobalUnlock( hMemCopy );
        GlobalFree( hMemCopy );
    }


    // �ړ���̍s��I�����܂�
    SGr_List->Row   = myRect.Top;
    SGr_List->Selection	= myRect;
    SGr_ListSelectCell(Sender,1,SGr_List->Row,true);

    iRowSelTop    = SGr_List->Selection.Top;
    iRowSelBottom = SGr_List->Selection.Bottom;

    // �f�[�^��ύX�����t���O
    DataSave = true;
    BtnF11->Enabled = true;

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

    if(ARow == 0) ARow = 1;
    ROWPOINT = ARow;

    // ���ږ��i���{��j
    if ( Trim(SGr_List->Cells[1][ARow]) == "" ){
        EdtKMK_NM_JPN->Text = "";
    }
    else{
        EdtKMK_NM_JPN->Text = SGr_List->Cells[1][ARow];
    }

    // ���ږ��i�p��j
    if ( Trim(SGr_List->Cells[2][ARow]) == "" ){
        EdtKMK_NM_ENG->Text = "";
    }
    else{
        EdtKMK_NM_ENG->Text = SGr_List->Cells[2][ARow];
    }

    // �X�V��
    PnlUPDYMD->Caption = SGr_List->Cells[4][ARow];

    // �X�V��
    PnlUPDCHR->Caption = SGr_List->Cells[5][ARow];

    // �C����폜�ׂ̈Ɂu����No�v���L�����܂��B
    if( SGr_List->Cells[12][ARow] == "" ){
        PnlUPDYMD->Tag = -1;
    }
    else {
        PnlUPDYMD->Tag = StrToInt(SGr_List->Cells[12][ARow]);
    }

    // �X�V�񐔂��L�����܂��B
    if( SGr_List->Cells[10][ARow] == "" ){
    	PnlUPDCHR->Tag = -1;
    }
    else {
    	PnlUPDCHR->Tag = StrToInt(SGr_List->Cells[10][ARow]);
    }

    // �X�V�E�폜�s�\���ڂ̏ꍇ�A�C���E�폜�{�^���𗘗p�s�ɂ��܂��B
    if( SGr_List->Cells[11][ARow] == 1 || PnlUPDYMD->Tag == -1 ){
		BtnF09->Enabled = false;
		BtnF10->Enabled = false;
        /* �V�K�o�^���������̂�Edit�̗��p�s�͂�߂�
        EdtKMK_NM_JPN->ReadOnly = true;
        EdtKMK_NM_ENG->ReadOnly = true;
		EdtKMK_NM_JPN->Font->Color = clRed;
		EdtKMK_NM_ENG->Font->Color = clRed;
    	*/
    }
    else{
		BtnF09->Enabled = true;
		BtnF10->Enabled = true;
        /* �V�K�o�^���������̂�Edit�̗��p�s�͂�߂�
        EdtKMK_NM_JPN->ReadOnly = false;
        EdtKMK_NM_ENG->ReadOnly = false;
		EdtKMK_NM_JPN->Font->Color = clWindowText;
		EdtKMK_NM_ENG->Font->Color = clWindowText;
		*/
    }

    // �C���O�̒l��ۑ����܂�
    sEdtKMK_NM_JPN_Old = EdtKMK_NM_JPN->Text;
    sEdtKMK_NM_ENG_Old = EdtKMK_NM_ENG->Text;

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
         //case VK_F1:  BtnF01Click(Sender);    Key = 0; break;
         case VK_F2:  BtnF02Click(Sender);    Key = 0; break;
         case VK_F3:  BtnF03Click(Sender);    Key = 0; break;
         case VK_F5:  BtnF05Click(Sender);    Key = 0; break;
         //case VK_F7:  BtnF07Click(Sender);    Key = 0; break;
         case VK_F8:  BtnF08Click(Sender);    Key = 0; break;
         case VK_F9:  BtnF09Click(Sender);    Key = 0; break;
         case VK_F10: BtnF10Click(Sender);    Key = 0; break;
         case VK_F11: BtnF11Click(Sender);    Key = 0; break;
         case VK_F12: BtnF12Click(Sender);    Key = 0; break;

         // Enter
         case VK_RETURN:
                if( EdtKMK_NM_JPN->Focused() || SGr_List->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                // �ڍו�
                if( EdtKMK_NM_ENG->Focused() ){
                    BtnF08->SetFocus();
                    break;
                }
                break;

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

   RECT r=RECT(Rect);

   //�Œ�Z���̔w�i�F���Z�b�g
   if(State.Contains(gdFixed))
       SGr_List->Canvas->Brush->Color= SGr_List->FixedColor;
   //�t�H�[�J�X�̂���Z���̔w�i�F���Z�b�g
//   else if(State.Contains(gdFocused))
//       SGr1->Canvas->Brush->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlight: SGr1->Color;
   //�I������Ă���Z���̔w�i�F���Z�b�g
   else if(State.Contains(gdSelected))
       SGr_List->Canvas->Brush->Color= clHighlight;
   //���ʂ̃Z���̔w�i�F���Z�b�g
   else
       SGr_List->Canvas->Brush->Color= SGr_List->Color;

   //�w�i�F�ŏ���
   SGr_List->Canvas->FillRect(Rect);

   //�Œ�Z���̗��̘g��`��
   if(SGr_List->Ctl3D&&State.Contains(gdFixed))
       DrawEdge(SGr_List->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);

   //�t�H�[�J�X�̂���Z���̕����F���Z�b�g
   if(State.Contains(gdFocused)){
//       SGr1->Canvas->Font->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlightText: SGr1->Font->Color;
//       //�t�H�[�J�X�g��`��
//       DrawFocusRect(SGr1->Canvas->Handle,&r);
	   //�I������Ă���Z���̕����F���Z�b�g
       //if(State.Contains(gdSelected))

       //�C���E�폜�s�\�f�[�^�̏ꍇ�̕����F���Z�b�g
       if( ACol > 0 && SGr_List->Cells[11][ARow].ToIntDef(0) > 0 )
           SGr_List->Canvas->Font->Color = clRed;
       else
           SGr_List->Canvas->Font->Color= clHighlightText;
   }
   //�I������Ă���Z���̕����F���Z�b�g
   else if(State.Contains(gdSelected))
       if( ACol > 0 && SGr_List->Cells[11][ARow].ToIntDef(0) > 0 )
           SGr_List->Canvas->Font->Color = clRed;
       else
           SGr_List->Canvas->Font->Color= clHighlightText;
   //�C���E�폜�s�\�f�[�^�̏ꍇ�̕����F���Z�b�g
   else if( ACol > 0 && SGr_List->Cells[11][ARow].ToIntDef(0) > 0 )
       SGr_List->Canvas->Font->Color = clRed;
   //���ʂ̃Z���̕����F���Z�b�g
   else
       SGr_List->Canvas->Font->Color= SGr_List->Font->Color;

   //�e�L�X�g�\���̈�̐ݒ�
   InflateRect(&r,-2,-2);

   //�e�L�X�g�̕\��
   DrawText(SGr_List->Canvas->Handle,SGr_List->Cells[ACol][ARow].c_str(),-1,&r,0); //����

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
void __fastcall TForm1::RowExchange(int FromIndex, int ToIndex)
{
    int			i;
	TGridRect	myRect;
    AnsiString	sBuf;
    AnsiString	sLineNo;

    // ����ւ���̃f�[�^���o�b�N�A�b�v
    sLineNo = SGr_List->Cells[0][ToIndex];						// �s�ԍ�
    sBuf = SGr_List->Cells[12][ToIndex];
    strcpy( tmpKSM21_DATA.KMK_NO		,sBuf.c_str() );		// ����NO
    sBuf = SGr_List->Cells[13][ToIndex];
    strcpy( tmpKSM21_DATA.ORDER_NO		,sBuf.c_str() );		// �\����
    sBuf = SGr_List->Cells[1][ToIndex];
    strcpy( tmpKSM21_DATA.KMK_NM_JPN	,sBuf.c_str() );		// ���ږ��i���{��j
    sBuf = SGr_List->Cells[2][ToIndex];
    strcpy( tmpKSM21_DATA.KMK_NM_ENG	,sBuf.c_str() );		// ���ږ��i�p��j
    sBuf = SGr_List->Cells[11][ToIndex];
    strcpy( tmpKSM21_DATA.NOUPD_FLG		,sBuf.c_str() );		// �C����폜�s�\����
    sBuf = SGr_List->Cells[7][ToIndex];
    strcpy( tmpKSM21_DATA.ADDYMD		,sBuf.c_str() );		// �o�^��
    sBuf = SGr_List->Cells[8][ToIndex];
    strcpy( tmpKSM21_DATA.ADDTIM		,sBuf.c_str() );		// �o�^����
    sBuf = SGr_List->Cells[4][ToIndex];
    strcpy( tmpKSM21_DATA.UPDYMD		,sBuf.c_str() );		// �ύX��
    sBuf = SGr_List->Cells[9][ToIndex];
    strcpy( tmpKSM21_DATA.UPDTIM		,sBuf.c_str() );		// �ύX����
    sBuf = SGr_List->Cells[6][ToIndex];
    strcpy( tmpKSM21_DATA.UPDCHR		,sBuf.c_str() );		// �X�V�ҁi�R�[�h�j
    sBuf = SGr_List->Cells[5][ToIndex];
    strcpy( tmpKSM21_DATA.UPDNAM		,sBuf.c_str() );		// �X�V�ҁi���́j
    sBuf = SGr_List->Cells[10][ToIndex];
    strcpy( tmpKSM21_DATA.UPDCNT		,sBuf.c_str() );		// �X�V��
    sBuf = SGr_List->Cells[14][ToIndex];                        // �ύX�t���O

    if( ToIndex > FromIndex ){
		// �㉺�����ւ��܂�
    	for( i=ToIndex; i>FromIndex; i-- ) {
    		SGr_List->Cells[0][i] = SGr_List->Cells[0][i-1];
    		SGr_List->Cells[1][i] = SGr_List->Cells[1][i-1];
    		SGr_List->Cells[2][i] = SGr_List->Cells[2][i-1];
    		SGr_List->Cells[3][i] = SGr_List->Cells[3][i-1];
    		SGr_List->Cells[4][i] = SGr_List->Cells[4][i-1];
    		SGr_List->Cells[5][i] = SGr_List->Cells[5][i-1];
    		SGr_List->Cells[6][i] = SGr_List->Cells[6][i-1];
    		SGr_List->Cells[7][i] = SGr_List->Cells[7][i-1];
    		SGr_List->Cells[8][i] = SGr_List->Cells[8][i-1];
    		SGr_List->Cells[9][i] = SGr_List->Cells[9][i-1];
    		SGr_List->Cells[10][i] = SGr_List->Cells[10][i-1];
    		SGr_List->Cells[11][i] = SGr_List->Cells[11][i-1];
    		SGr_List->Cells[12][i] = SGr_List->Cells[12][i-1];
    		SGr_List->Cells[13][i] = SGr_List->Cells[13][i-1];
			SGr_List->Cells[14][i] = SGr_List->Cells[14][i-1];
    	}
    }
    else{
		// �㉺�����ւ��܂�
    	for( i=ToIndex; i<FromIndex; i++ ) {
    		SGr_List->Cells[0][i] = SGr_List->Cells[0][i+1];
    		SGr_List->Cells[1][i] = SGr_List->Cells[1][i+1];
    		SGr_List->Cells[2][i] = SGr_List->Cells[2][i+1];
    		SGr_List->Cells[3][i] = SGr_List->Cells[3][i+1];
    		SGr_List->Cells[4][i] = SGr_List->Cells[4][i+1];
    		SGr_List->Cells[5][i] = SGr_List->Cells[5][i+1];
    		SGr_List->Cells[6][i] = SGr_List->Cells[6][i+1];
    		SGr_List->Cells[7][i] = SGr_List->Cells[7][i+1];
    		SGr_List->Cells[8][i] = SGr_List->Cells[8][i+1];
    		SGr_List->Cells[9][i] = SGr_List->Cells[9][i+1];
    		SGr_List->Cells[10][i] = SGr_List->Cells[10][i+1];
    		SGr_List->Cells[11][i] = SGr_List->Cells[11][i+1];
    		SGr_List->Cells[12][i] = SGr_List->Cells[12][i+1];
    		SGr_List->Cells[13][i] = SGr_List->Cells[13][i+1];
			SGr_List->Cells[14][i] = SGr_List->Cells[14][i+1];
    	}
    }

    // �o�b�N�A�b�v�����f�[�^�����ɂ��ǂ��܂��B
    SGr_List->Cells[0][FromIndex]  = sLineNo					;	// �s�ԍ�
	SGr_List->Cells[12][FromIndex] = tmpKSM21_DATA.KMK_NO		;	// ����NO
	SGr_List->Cells[13][FromIndex] = tmpKSM21_DATA.ORDER_NO		;	// �\����
	SGr_List->Cells[1][FromIndex]  = tmpKSM21_DATA.KMK_NM_JPN	;	// ���ږ��i���{��j
	SGr_List->Cells[2][FromIndex]  = tmpKSM21_DATA.KMK_NM_ENG	;	// ���ږ��i�p��j
	SGr_List->Cells[11][FromIndex] = tmpKSM21_DATA.NOUPD_FLG	;	// �C����폜�s�\����
	SGr_List->Cells[7][FromIndex]  = tmpKSM21_DATA.ADDYMD		;	// �o�^��
	SGr_List->Cells[8][FromIndex]  = tmpKSM21_DATA.ADDTIM		;	// �o�^����
	SGr_List->Cells[4][FromIndex]  = tmpKSM21_DATA.UPDYMD		;	// �ύX��
	SGr_List->Cells[9][FromIndex]  = tmpKSM21_DATA.UPDTIM		;	// �ύX����
	SGr_List->Cells[6][FromIndex]  = tmpKSM21_DATA.UPDCHR		;	// �X�V�ҁi�R�[�h�j
	SGr_List->Cells[5][FromIndex]  = tmpKSM21_DATA.UPDNAM		;	// �X�V�ҁi���́j
	SGr_List->Cells[10][FromIndex] = tmpKSM21_DATA.UPDCNT		;	// �X�V��
    SGr_List->Cells[14][FromIndex] = sBuf						;	// �ύX�t���O

    // �I���������܂�
    //SGr_List->Row	= iRowSelTop;
	myRect.Left		= SGr_List->Selection.Left;
	myRect.Top		= iRowSelTop;
	myRect.Right	= SGr_List->Selection.Right;
	myRect.Bottom	= iRowSelBottom;
    SGr_List->Selection	= myRect;
    //SGr_ListSelectCell(Sender,1,SGr_List->Row,true);

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
//    AnsiString str	�F�Ώۂ̃V�[�gNO
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
//    ����֐�			�F�S���҃R�[�h����S���Җ�����������
//
//  �@�\����
//    �S���҃R�[�h����S���Җ�����������
//
//  �p�����^����
//    AnsiString strTANSYA�F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    AnsiString		�F���������S���Җ�
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetTANNAM(AnsiString strTANSYA)
{

    AnsiString sBuf;

    if( strTANSYA == "0" ){
    	return "�Ǘ���";
    }

    // Initial Query
    Query2->Close();
    Query2->SQL->Clear();

    // �⍇�����쐬
	sBuf = "SELECT TANNAM FROM SM12S";
	sBuf += " WHERE TANSYA=" + strTANSYA;

    Query2->SQL->Add(sBuf);
    Query2->Open();
    Query2->Active = true;

    if ( Query2->Bof == true && Query2->Eof == true)
    {
       return strTANSYA;
		//return " ";
    }
    else
    {
        Query2->First();
        sBuf = Form1->Query2->FieldValues["TANNAM"];
        return sBuf;
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnChange�C�x���g	�F�ҏW�R���g���[���̃e�L�X�g�ɕύX��������ꂽ�Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���͕���(�V���O���R�[�e�[�V����)�̃`�F�b�N���s�Ȃ��܂��B
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
}

