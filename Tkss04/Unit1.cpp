//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    �y�o�׌����V�X�e���|����f�[�^�폜�z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �c���@�֎i
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
TForm1 *Form1;

int     USER_COD;
String  USER_NAM;
String  BUMO_COD;
String  BUMO_NAM;
bool    DataSave;

// ���b�Z�[�W
AnsiString MSG_01 = "�������ł�... ���΂炭���҂����������B" ;
AnsiString MSG_02 = "�������ʂO���B" ;
AnsiString MSG_09 = "��ʈ�����ł�... ���΂炭���҂����������B" ;

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
    Database1->Open();

	// �O���b�h�̏�����
    SGr_List->ColCount = 13;
    SGr_List->RowCount = 2;
	SGr_List->ColWidths[ 0] = 55;
	SGr_List->ColWidths[ 1] = 160;
	SGr_List->ColWidths[ 2] = 60;
	SGr_List->ColWidths[ 3] = 140;
	SGr_List->ColWidths[ 4] = 120;
	SGr_List->ColWidths[ 5] = 120;
	SGr_List->ColWidths[ 6] = 160;
	SGr_List->ColWidths[ 7] = 45;
	SGr_List->ColWidths[ 8] = 60;
	SGr_List->ColWidths[ 9] = 60;
	SGr_List->ColWidths[10] = 80;
	SGr_List->ColWidths[11] = 80;
	SGr_List->ColWidths[12] = 80;

	SGr_List->Cells[ 0][0] = "  N O";
	SGr_List->Cells[ 1][0] = "�i�@��";
	SGr_List->Cells[ 2][0] = "���b�gNO";
	SGr_List->Cells[ 3][0] = "���Еi��";
	SGr_List->Cells[ 4][0] = "�ށ@��";
	SGr_List->Cells[ 5][0] = "�i�@��";
	SGr_List->Cells[ 6][0] = "��\���Ӑ於";
	SGr_List->Cells[ 7][0] = "���ڐ�";
	SGr_List->Cells[ 8][0] = "�f�ޔ���";
	SGr_List->Cells[ 9][0] = "�o�ה���";
	SGr_List->Cells[10][0] = "�f�ޗp�����";
	SGr_List->Cells[11][0] = "�o�חp�����";
	SGr_List->Cells[12][0] = "��\�X�V��";


     // �{�^���̏�����
     BtnF01->Enabled = false;    //�J�[�\�����w��ʒu�̂Ƃ���True
     BtnF02->Enabled = false;
     BtnF03->Enabled = false;
     BtnF04->Enabled = false;
     BtnF05->Enabled = true;
     BtnF06->Enabled = false;
     BtnF07->Enabled = true;
     BtnF08->Enabled = true;
     BtnF09->Enabled = false;
     BtnF10->Enabled = false;
     BtnF11->Enabled = false;
     BtnF12->Enabled = true;

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
    //���[�U�R�[�h�A���[�U���A�����R�[�h�A������ ���o
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
//    OnClick�C�x���g	�F�u�e�P�F�ꗗ�����v�{�^�������������̏���
//
//  �@�\����
//    �ꗗ�����t�H�[���iForm2�j��\�����܂��B
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
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
    if( !BtnF01->Enabled )    return;

    ////////////////////
    // �ꗗ����
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
     SBr1->Panels->Items[0]->Text = MSG_09;
     SBr1->Update();

     Form1->Print();

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�V�F�����v�{�^�������������̏���
//
//  �@�\����
//    �w�肳�ꂽ���Ӑ�i�ԁA���b�gNO�����Ɍ����������J�n���܂�
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
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
     int iRow,i;
     AnsiString sYMD;
     AnsiString sBuf;

     if( !BtnF07->Enabled )    return;

    // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = MSG_01;
     SBr1->Update();

     //SGr_List������
     Form1->SGr_List->RowCount = 2;      //�ŏ�s�̓R�����g�s
     iRow = Form1->SGr_List->RowCount;

     // �ŏ�s���N���A�[
     for( i = 0; i < Form1->SGr_List->ColCount; i++)
     {
         Form1->SGr_List->Cells[i][1]  = "";
     }

     // �ŉ��s���N���A�[
     for( i = 0; i < Form1->SGr_List->ColCount; i++)
     {
         Form1->SGr_List->Cells[i][iRow]  = "";
     }


     //�g�����U�N�V�����J�n
     if ( MAIN_Serch01() == 0 )
     {
     	//�������� �O��
        // �X�e�[�^�X���b�Z�[�W
        Beep();
        SBr1->Panels->Items[0]->Text = "���Ӑ�i�Ԃ����i�K�i�}�X�^�ɓo�^����Ă��܂���";
        SBr1->Update();
        EdtHIN->SetFocus();
        return;
     }

     iRow = Form1->SGr_List->RowCount - 1;
     // �ŉ��s���N���A�[
     for( i = 0; i < Form1->SGr_List->ColCount; i++) {
         Form1->SGr_List->Cells[i][iRow]  = "";
     }

     // �I���s��I�����Ȃ����܂��B
	 SGr_ListClick(SGr_List);

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     Form1->SGr_List->SetFocus();


     // �{�^����Ԃ̕ύX
     BtnF02->Enabled = false;
     BtnF03->Enabled = false;
     BtnF09->Enabled = false;
     BtnF10->Enabled = false;

     if(Form1->SGr_List->RowCount  > 2)
     {
        BtnF02->Enabled = true;
        BtnF03->Enabled = true;
     }
     if(Form1->SGr_List->RowCount > 2)
     {
        BtnF09->Enabled = true;
        BtnF10->Enabled = true;
     }

     BtnF01->Enabled = false;
     SGr_List->Row = 1;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�O�F�폜�v�{�^�������������̏���
//
//  �@�\����
//    �I����������f�[�^(KSD01,KSD02,KSD03,KSD11,KSD12)���폜���܂�
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
    int i,k,m;
    int	iMovRow;

    if( !BtnF10->Enabled )    return;

    if( SGr_List->Cells[1][SGr_List->Row] == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�폜�Ώۂł͂���܂���B";
        SBr1->Update();
        SGr_List->SetFocus();
        return;
    }

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "�폜���ł��D�D�D���΂炭���҂��������B";
    SBr1->Update();

	// �I������Ă���͈͂��������Ɋi�[���܂�
    for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
    	if( SGr_List->Cells[1][i] != "" && SGr_List->Cells[2][i] != "" ){
                //20170406 Y.Onishi �u�폜�v���s���A���Еi�Ԃ��l��
    		//if( DelData(SGr_List->Cells[1][i], SGr_List->Cells[2][i]) == False ){
    		if( DelData(SGr_List->Cells[1][i], SGr_List->Cells[2][i], SGr_List->Cells[3][i]) == False ){
	        	//return;
        	}
    	}
    }

    iMovRow = (iRowSelBottom - iRowSelTop) + 1;
  	if( SGr_List->Cells[1][iRowSelBottom] == "" && SGr_List->Cells[2][iRowSelBottom] == "" ){
    	if( iMovRow >= 2 )	iMovRow--;
    }

	// �O���b�h�̍s����s��ɃR�s�[���܂��B
    for( k = iRowSelTop; k < (SGr_List->RowCount - iMovRow); k++) {
       	for( m = 1; m <= 12; m++) {
           	SGr_List->Cells[m][k] = SGr_List->Cells[m][k+iMovRow];
       	}
    }
    SGr_List->Cells[0][k-1] = "";

    // ��s���炷
    SGr_List->RowCount = SGr_List->RowCount - iMovRow;

    // �V�����s��I��
    if( SGr_List->RowCount <= SGr_List->Row) {
        if( SGr_List->Row - iMovRow > 1 ){
        	SGr_List->Row = SGr_List->Row - iMovRow;
    	} else {
        	SGr_List->Row = 1;
        }
    }
    else {
        SGr_List->Row = SGr_List->Row;
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // �f�[�^��ύX�����t���O
    DataSave = true;
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�P�F�ۑ��v�{�^�������������̏���
//
//  �@�\����
//    �X�V�f�[�^���m��(Commit)���܂�
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
     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�ۑ����ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // �ύX�C�}���C�폜���i���I�ɕۑ����C���݂̃g�����U�N�V�������I��
     if( Database1->InTransaction == True ){
         Database1->Commit();
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
         case VK_F1:  BtnF01Click(Sender);    Key = 0; break;
         case VK_F2:  BtnF02Click(Sender);    Key = 0; break;
         case VK_F3:  BtnF03Click(Sender);    Key = 0; break;
         case VK_F5:  BtnF05Click(Sender);    Key = 0; break;
         case VK_F7:  BtnF07Click(Sender);    Key = 0; break;
         case VK_F10: BtnF10Click(Sender);    Key = 0; break;
         case VK_F11: BtnF11Click(Sender);    Key = 0; break;
         case VK_F12: BtnF12Click(Sender);    Key = 0; break;


         // �O��
         case VK_UP:
         case VK_LEFT:
                if(EdtHIN->Focused() && EdtHIN->SelStart == 0 && EdtHIN->SelLength == 0){
                    BtnF01->Enabled = true;
                    break;
                }
                if(EdtLOT->Focused() && EdtLOT->SelStart == 0 && EdtLOT->SelLength == 0){
                    BtnF01->Enabled = true;
                    EdtHIN->SetFocus();
                    break;
                }
                break;

         // ����
         case VK_DOWN:
         case VK_RIGHT:
                if(EdtHIN->Focused() && EdtHIN->SelStart == EdtHIN->Text.Length()  && EdtHIN->SelLength == 0){
                    BtnF01->Enabled = true;
                    //���Ӑ�i�Ԃ��琻�i�K�i�����߂�
                    EdtLOT->SetFocus();
                    break;
                }
                if(EdtLOT->Focused() && EdtLOT->SelStart == EdtLOT->Text.Length()  && EdtLOT->SelLength == 0){
                    BtnF01->Enabled = true;
                    break;
                }

                break;


         // Enter
         case VK_RETURN:
                if( EdtHIN->Focused() || SGr_List->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( EdtLOT->Focused() ){
                    BtnF07Click(Sender);
                    break;
                }
                break;

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
     EdtKeyPress(Sender,Key);
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
                if( Database1->InTransaction == True )  Database1->Commit();
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
void __fastcall TForm1::AllKeyEnter(TObject *Sender)
{
    if(EdtHIN->Focused()){
        BtnF01->Enabled = true;
        return;
    }

//    if(EdtLOT->Focused()){
//        BtnF01->Enabled = true;
//        return;
//    }

    BtnF01->Enabled = false;

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
void __fastcall TForm1::EdtKeyPress(TObject *Sender, char &Key)
{
    switch(Key)
    {
        // ���^�[��
        case VK_RETURN:
            Key = 0;
            break;
    }
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

    // Initial Query
    Form1->Query2->Close();
    Form1->Query2->SQL->Clear();

    // �⍇�����쐬
	sBuf = "SELECT TANNAM FROM SM12S";
	sBuf += " WHERE TANSYA=" + strTANSYA;

    Form1->Query2->SQL->Add(sBuf);
    Form1->Query2->Open();
    Form1->Query2->Active = true;

    if ( Form1->Query2->Bof == true && Form1->Query2->Eof == true)
    {
       return strTANSYA;
		//return " ";
    }
    else
    {
        Form1->Query2->First();
        sBuf = Form1->Query2->FieldValues["TANNAM"];
        return sBuf;
    }
}


//---------------------------------------------------------------------------
//
//  �T�v
//    OnEnter�C�x���g	�F�e�R���g���[�����t�H�[�J�X�擾�����Ƃ�
//
//  �@�\����
//    �uF1�F�ꗗ�����v�{�^���̗L���^������ݒ肵�܂�
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
void __fastcall TForm1::FormEnter(TObject *Sender)
{

    if( SGr_List->Tag == 1 )    return;
    if( BtnF01->Focused() )    return;


    // ���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
    if( EdtHIN->Focused() )
    {
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 1;
        return;
    }

    // ���b�g�Ƀt�H�[�J�X���L��ꍇ
    if( EdtLOT->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 2;
        return;
    }

    // �uF1�F�ꗗ�����v�{�^�����g���Ȃ��悤�ɂ���
    BtnF01->Enabled = false;
    BtnF01->Tag = 0;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnActivate�C�x���g	�F�t�H�[�����A�N�e�B�u�ɂȂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �����t�H�[�J�X�̈ʒu��ݒ肵�܂�
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
	EdtHIN->SetFocus();
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

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�FStringGrid��I���������ɔ������܂��B
//
//  �@�\����
//    �I���i�͈͑I���j���ꂽTop��Bottom���L�����܂�
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


