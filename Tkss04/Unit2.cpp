//---------------------------------------------------------------------------
//
//  Unit2.cpp
//    �y�o�׌����V�X�e���|����f�[�^�폜�z
//    �ꗗ�����t�H�[���iTForm2�N���X�j�̃����o�֐��̒�`
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
#pragma resource "*.dfm"
TForm2 *Form2;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
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
void __fastcall TForm2::BtnF02Click(TObject *Sender)
{
   if(SGr1->Row > 1){
        SGr1->Row -= 1;
        SGr1->SetFocus();
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
void __fastcall TForm2::BtnF03Click(TObject *Sender)
{
    if( (SGr1->RowCount-1) > SGr1->Row ){
        SGr1->Row += 1;
        SGr1->SetFocus();
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�S�F�I���v�{�^�������������̏���
//
//  �@�\����
//    �I���t���O��ON�ɂ��ăt�H�[����Close���R�[�����܂�
//    �iCloseQuery���őI���f�[�^�擾�������s�Ȃ��j
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
void __fastcall TForm2::BtnF04Click(TObject *Sender)
{
     SGr1->Tag = 1;    // �I���t���OON
     Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�Q�F�߂�v�{�^�������������̏���
//
//  �@�\����
//    �t�H�[����Close���R�[�����܂�
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
void __fastcall TForm2::BtnF12Click(TObject *Sender)
{
     Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnDblClick�C�x���g�FStringGrid�ō��{�^�����_�u���N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �u�e�S�F�I���v�{�^�����R�[�����܂�
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
void __fastcall TForm2::SGr1DblClick(TObject *Sender)
{
	BtnF04Click(BtnF04);
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
void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_RETURN:
         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnActivate�C�x���g	�F�t�H�[�����A�N�e�B�u�ɂȂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ������ԂŕK�v�Ȍ����������s�Ȃ��܂�
//    �y�ꗗ�f�[�^�̌��������z
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
void __fastcall TForm2::FormActivate(TObject *Sender)
{

    int i;
    int iRow;
    AnsiString sBuf;

    SGr1->Tag = 0;    // �I���t���OOFF

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    SGr1->Row = 1;     // �I���s�̏�����

	//�t�H�[�J�X�̈ʒu�ɂ��SQL�Ɖ�ʕ\���̕ύX
    switch( Form1->BtnF01->Tag )
    {
        case 1:
            sBuf  = "SELECT DISTINCT DTKSHIN, HINBAN, ZISNAM, HINMEI FROM KSD01";
            sBuf += " WHERE DTKSHIN LIKE '" + Form1->EdtHIN->Text + "%'";
            sBuf += " ORDER BY DTKSHIN";
            // �^�C�g�����Z�b�g
            SGr1->ColCount = 5;
            SGr1->Cells[0][0] = "  N O";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "���Еi��";
            SGr1->Cells[3][0] = "�i�@��";
            SGr1->Cells[4][0] = "�i�@��";
            SGr1->ColWidths[0] = 43;
            SGr1->ColWidths[1] = 163;
            SGr1->ColWidths[2] = 110;
            SGr1->ColWidths[3] = 110;
            SGr1->ColWidths[4] = 110;
            break;

        case 2:
            sBuf  = "SELECT DTKSHIN, LOTNO FROM KSD01";
            sBuf += " WHERE DTKSHIN LIKE '" + Form1->EdtHIN->Text + "%'";
            sBuf += " AND LOTNO LIKE '" + Form1->EdtLOT->Text + "%'";
            sBuf += " ORDER BY DTKSHIN, SUBSTR(LOTNO,2)";
            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  N O";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "���b�gNo";
            SGr1->ColWidths[0] = 43;
            SGr1->ColWidths[1] = 200;
            SGr1->ColWidths[2] = 100;
            break;

    }

    //�₢���������s
    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    iRow = 0;
    while( !Query1->Eof ){

        iRow += 1;

        // �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
        if( iRow >= SGr1->RowCount ){
            SGr1->RowCount = iRow;
        }

        // �O���b�h�Ƀf�[�^���Z�b�g���܂��B

        // NO
        sBuf = iRow;
        if( sBuf.Length() > 6 )	sBuf = sBuf.SubString( sBuf.Length() - 5, 6 );
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;

        // �f�[�^
        for( i=1; i<SGr1->ColCount; i++){
            sBuf = Query1->Fields->Fields[i-1]->AsString;
            SGr1->Cells[i][iRow] = sBuf;
        }

        // �J�[�\�������ɃZ�b�g����
        Query1->Next();
    }

    SGr1->RowCount = iRow + 1 ;

    fFind = true;
    if( iRow == 0 ){
        fFind = false;
        SGr1->RowCount = 2;
        SGr1->FixedRows = 1;
        // �������ʊY���Ȃ��̏ꍇ
        for( i=1; i<SGr1->ColCount; i++){
            SGr1->Cells[i][1] = "�Y������";
        }
        iRow = 1;
    }
    if( Form2->Tag == 2 ){
    	SGr1->Row = iRow;
    } else {
    	SGr1->Row = 1;
    }
    SGr1->SetFocus();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCloseQuery�C�x���g�FClose ���\�b�h���Ăяo���ꂽ�Ƃ��܂��̓��[�U�[��
//          �t�H�[���̃V�X�e�����j���[�Łm����n��I�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �I���t���OON�̎��A�I�������f�[�^�����܂�
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
void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{

    if( !fFind )   return;

    // �I���t���OON�̎�
    if( SGr1->Tag ){

        switch( Form1->BtnF01->Tag ){

            // �������@��\���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
            case 1:
                Form1->EdtHIN->Text = SGr1->Cells[1][SGr1->Row];      	// ���Ӑ�i��
                Form1->EdtHIN->SetFocus();
                Form1->EdtHIN->SelectAll();
                break;

            // �������@���b�gNO�Ƀt�H�[�J�X���L��ꍇ
            case 2:
                Form1->EdtHIN->Text = SGr1->Cells[1][SGr1->Row];      	// ���Ӑ�i��
                Form1->EdtLOT->Text = SGr1->Cells[2][SGr1->Row];      	// ���b�gNO
                Form1->EdtLOT->SetFocus();
                Form1->EdtLOT->SelectAll();
                break;

        }
    }

}
