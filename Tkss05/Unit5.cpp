//---------------------------------------------------------------------------
//
//  Unit5.cpp
//    �y�o�׌����V�X�e���|���i�K�i�}�X�^�[�z
//    �ꗗ�����t�H�[���iTForm5�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �c���@�֎i
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
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
void __fastcall TForm5::BtnF02Click(TObject *Sender)
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
void __fastcall TForm5::BtnF03Click(TObject *Sender)
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
void __fastcall TForm5::BtnF04Click(TObject *Sender)
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
void __fastcall TForm5::BtnF12Click(TObject *Sender)
{
     Close();
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
void __fastcall TForm5::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;
         case VK_RETURN:
              SGr1->Tag = 1;    // �I���t���OON
              Close();
              break;
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
void __fastcall TForm5::FormActivate(TObject *Sender)
{

     int i;
     int iRow;
     AnsiString sBuf;

     SGr1->Tag = 0;    // �I���t���OOFF

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     SGr1->Row = 1;     // �I���s�̏�����

     switch( Form1->BtnF01->Tag ){

        // �������@���Ӑ�R�[�h�Ƀt�H�[�J�X���L��ꍇ
        case 1:

            // �⍇�����s
            sBuf = "select DISTINCT DTKSCOD, DTKSNAM from KSM01";
            i = 0;
            if( Form1->Edt_COD1->Text != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->Edt_COD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD2->Text != "" ){
                // ���Ӑ�i��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->Edt_COD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD3->Text != "" ){
                // ���Еi��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->Edt_COD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD4->Text != "" ){
                // �ގ�����
                if( i == 1 ){   // ���Ӑ�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->Edt_COD4->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY DTKSCOD";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���Ӑ�R�[�h";
            SGr1->Cells[2][0] = "���Ӑ於��";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 80;
            SGr1->ColWidths[2] = 400;
            break;

        // �������@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
        case 2:

            // �⍇�����s
            sBuf = "select DISTINCT DTKSHIN, HINBAN, ZISNAM from KSM01";
            i = 0;
            if( Form1->Edt_COD1->Text != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->Edt_COD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD2->Text != "" ){
                // ���Ӑ�i��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->Edt_COD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD3->Text != "" ){
                // ���Еi��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->Edt_COD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD4->Text != "" ){
                // �ގ�����
                if( i == 1 ){   // ���Ӑ�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->Edt_COD4->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY DTKSHIN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "���Еi��";
            SGr1->Cells[3][0] = "�ގ�����";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            SGr1->ColWidths[3] = 180;
            break;

        // �������@���Еi�ԂɃt�H�[�J�X���L��ꍇ
        case 3:

            // �⍇�����s
            sBuf = "select DISTINCT HINBAN from KSM01";
            i = 0;
            if( Form1->Edt_COD1->Text != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->Edt_COD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD2->Text != "" ){
                // ���Ӑ�i��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->Edt_COD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD3->Text != "" ){
                // ���Еi��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->Edt_COD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD4->Text != "" ){
                // �ގ�����
                if( i == 1 ){   // ���Ӑ�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->Edt_COD4->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY HINBAN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���Еi��";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            break;

        // �������@�ގ����̂Ƀt�H�[�J�X���L��ꍇ
        case 4:

            // �⍇�����s
            sBuf = "select DISTINCT ZISNAM from KSM01";
            i = 0;
            if( Form1->Edt_COD1->Text != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->Edt_COD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD2->Text != "" ){
                // ���Ӑ�i��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->Edt_COD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD3->Text != "" ){
                // ���Еi��
                if( i == 1 ){   // ���Ӑ�i�Ԃ̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�i�Ԃ̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->Edt_COD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->Edt_COD4->Text != "" ){
                // �ގ�����
                if( i == 1 ){   // ���Ӑ�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->Edt_COD4->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY ZISNAM";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "�ގ�����";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            break;

        // �ڍו��@���Ӑ�R�[�h�A���Ӑ於�̂Ƀt�H�[�J�X���L��ꍇ
        case 5:
        case 6:

            // �⍇�����s
            sBuf = "select DISTINCT TRSCOD, TRSNAM from SM16S where TKSKBN=1";
            if( Trim(Form1->Edt_DTKSCOD->Text) != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " and TRSCOD like '";
                sBuf = sBuf + Form1->Edt_DTKSCOD->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY TRSCOD";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���Ӑ�R�[�h";
            SGr1->Cells[2][0] = "���Ӑ於��";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 100;
            SGr1->ColWidths[2] = 400;
            break;

        // �ڍו��@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
        case 7:
            // �⍇�����s
            sBuf = "select DISTINCT SD21S.DTKSHIN, SD21S.DTKSCOD, SM16S.TRSNAM, SD21S.HINBAN, SD21S.ZISNAM, SD21S.HINNAM";
            sBuf = sBuf + " from SD21S";
            sBuf = sBuf + " LEFT JOIN SM16S ON SD21S.DTKSCOD = SM16S.TRSCOD";
            //sBuf = sBuf + " where length(ltrim(rtrim(DTKSHIN)))>0";
            if( Trim(Form1->Edt_DTKSHIN->Text) != "" ){
                // ���Ӑ�i��
                sBuf = sBuf + " where SD21S.DTKSHIN like '";
                sBuf = sBuf + Form1->Edt_DTKSHIN->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY SD21S.DTKSHIN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 7;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "";
            SGr1->Cells[3][0] = "���Ӑ於��";
            SGr1->Cells[4][0] = "���Еi��";
            SGr1->Cells[5][0] = "�i�@��";
            SGr1->Cells[6][0] = "�i�@��";
            SGr1->ColWidths[0] = 36;
            SGr1->ColWidths[1] = 120;
            SGr1->ColWidths[2] = 0;
            SGr1->ColWidths[3] = 100;
            SGr1->ColWidths[4] = 90;
            SGr1->ColWidths[5] = 90;
            SGr1->ColWidths[6] = 100;
            break;

        // �ڍו��@���Еi�ԂɃt�H�[�J�X���L��ꍇ
        case 8:

            // �⍇�����s
            sBuf = "select DISTINCT DTKSHIN, HINBAN from SD21S where length(ltrim(rtrim(DTKSHIN)))>0";
            if( Trim(Form1->Edt_HINBAN->Text) != "" ){
                // ���Еi��
                sBuf = sBuf + " and HINBAN like '";
                sBuf = sBuf + Form1->Edt_HINBAN->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY DTKSHIN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "���Еi��";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // �ڍו��@�ގ����́i�i��j�Ƀt�H�[�J�X���L��ꍇ
        case 9:

            // �⍇�����s
            sBuf = "select DISTINCT ZISNAM, ZISCOD from KM03";
            if( Trim(Form1->Edt_ZISNAM->Text) != "" ){
                // �ގ�����
                sBuf = sBuf + " where ZISNAM like '";
                sBuf = sBuf + Form1->Edt_ZISNAM->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY ZISNAM";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "�ގ�����";
            SGr1->Cells[2][0] = "�ގ��R�[�h";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // �ڍו��@�i���Ƀt�H�[�J�X���L��ꍇ
        case 10:

            // �⍇�����s
            sBuf = "select DISTINCT HINNAM from SD21S where length(ltrim(rtrim(DTKSHIN)))>0";
            sBuf = sBuf + " ORDER BY HINNAM";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "�i��";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 400;
            break;

        // �f�ޗp�i�Ԃ́u�w��v�{�^���Ƀt�H�[�J�X���L��ꍇ
        case 11:

            // �⍇�����s
    		sBuf = "select DISTINCT DTKSHIN, min(DTKSNAM) AS DTKSNAM_MIN,";
    		sBuf = sBuf + " max(SKTYMD) AS SKTYMD_MAN, count(LOTNO) AS LOTNO_CNT ";
    		sBuf = sBuf + "from KSD21 group by DTKSHIN order by DTKSHIN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 5;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "�f�ޑ���ϕi��";
            SGr1->Cells[2][0] = "��\���Ӑ於";
            SGr1->Cells[3][0] = "�ŏI�����";
            SGr1->Cells[4][0] = "����ۯĐ�";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            SGr1->ColWidths[3] = 70;
            SGr1->ColWidths[4] = 60;
            break;
    }

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;

    iRow = 0;
    while( !Query1->Eof ){

        if( !VarIsNull(Query1->Fields->Fields[0]->AsString) ){
        	if( Trim(AnsiString(Query1->Fields->Fields[0]->AsString)) == "" ){
        		// �J�[�\�������ɃZ�b�g����
        		Query1->Next();
        		continue;
            }
        }
        else {
        	// �J�[�\�������ɃZ�b�g����
        	Query1->Next();
        	continue;
        }

        iRow += 1;

        // �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
        if( iRow >= SGr1->RowCount ){
            SGr1->RowCount = iRow;
        }

        // �O���b�h�Ƀf�[�^���Z�b�g���܂��B

        // NO
        sBuf = iRow;
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;

        // �f�[�^
        for( i=1; i<SGr1->ColCount; i++){
            sBuf = Query1->Fields->Fields[i-1]->AsString;
            if( Form1->BtnF01->Tag == 11 && i == 3 ){
            	// ���t�t�H�[�}�b�g�ɕϊ�
                sBuf.Insert("/",5);
                sBuf.Insert("/",8);
            }
            if( Form1->BtnF01->Tag == 11 && i == 4 ){
                // ���l�E��
                sBuf = AnsiString::StringOfChar(' ', 7-sBuf.Length()) + sBuf;
            }
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
    }
    SGr1->Row = 1;
    SGr1->SetFocus();
    SGr1Click( SGr1 );

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
void __fastcall TForm5::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    int			i;
    AnsiString	sBuf;


    if( !fFind )   return;

    // �I���t���OON�̎�
    if( SGr1->Tag ){

        switch( Form1->BtnF01->Tag ){

            // �������@���Ӑ�R�[�h�Ƀt�H�[�J�X���L��ꍇ
            case 1:
                Form1->Edt_COD1->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�R�[�h
                Form1->Edt_COD1->SetFocus();
                Form1->Edt_COD1->SelectAll();
                break;

            // �������@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
            case 2:
                Form1->Edt_COD2->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�i��
                Form1->Edt_COD3->Text = SGr1->Cells[2][SGr1->Row];      // ���Еi��
                Form1->Edt_COD4->Text = SGr1->Cells[3][SGr1->Row];      // �ގ�����
                Form1->Edt_COD2->SetFocus();
                Form1->Edt_COD2->SelectAll();
                break;

            // �������@���Еi�ԂɃt�H�[�J�X���L��ꍇ
            case 3:
                Form1->Edt_COD3->Text = SGr1->Cells[1][SGr1->Row];      // ���Еi��
                Form1->Edt_COD3->SetFocus();
                Form1->Edt_COD3->SelectAll();
                break;

            // �������@�ގ����̂Ƀt�H�[�J�X���L��ꍇ
            case 4:
                Form1->Edt_COD4->Text = SGr1->Cells[1][SGr1->Row];      // �ގ�����
                Form1->Edt_COD4->SetFocus();
                Form1->Edt_COD4->SelectAll();
                break;

            // �ڍו��@���Ӑ�R�[�h�A���Ӑ於�̂Ƀt�H�[�J�X���L��ꍇ
            case 5:
            case 6:
                Form1->Edt_DTKSCOD->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�R�[�h
                Form1->Edt_DTKSNAM->Text = SGr1->Cells[2][SGr1->Row];      // ���Ӑ於��
                if( Form1->BtnF01->Tag == 5 ){
                    Form1->Edt_DTKSCOD->SetFocus();
                    Form1->Edt_DTKSCOD->SelectAll();
                }
                if( Form1->BtnF01->Tag == 6 ){
                    Form1->Edt_DTKSNAM->SetFocus();
                    Form1->Edt_DTKSNAM->SelectAll();
                }
                break;

            // �ڍו��@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
            // �ڍו��@���Еi�ԂɃt�H�[�J�X���L��ꍇ
            case 7:
                Form1->Edt_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�i��
                Form1->Edt_DTKSCOD->Text = SGr1->Cells[2][SGr1->Row];      // ���Ӑ�R�[�h
                Form1->Edt_DTKSNAM->Text = SGr1->Cells[3][SGr1->Row];      // ���Ӑ於��
                Form1->Edt_HINBAN->Text  = SGr1->Cells[4][SGr1->Row];      // ���Еi��
                Form1->Edt_ZISNAM->Text  = SGr1->Cells[5][SGr1->Row];      // �i��
                Form1->Edt_HINMEI->Text  = SGr1->Cells[6][SGr1->Row];      // �i��
                Form1->Edt_DTKSHIN->SetFocus();
                Form1->Edt_DTKSHIN->SelectAll();
                break;

            case 8:
                Form1->Edt_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�i��
                Form1->Edt_HINBAN->Text  = SGr1->Cells[2][SGr1->Row];      // ���Еi��
                Form1->Edt_HINBAN->SetFocus();
                Form1->Edt_HINBAN->SelectAll();
                break;

            // �ڍו��@�ގ����́i�i��j�Ƀt�H�[�J�X���L��ꍇ
            case 9:
                Form1->Edt_ZISNAM->Text = SGr1->Cells[1][SGr1->Row];      // �ގ�����
                Form1->Edt_ZISNAM->SetFocus();
                Form1->Edt_ZISNAM->SelectAll();
                break;

            // �ڍו��@�i���Ƀt�H�[�J�X���L��ꍇ
            case 10:
                Form1->Edt_HINMEI->Text = SGr1->Cells[1][SGr1->Row];      // �i��
                Form1->Edt_HINMEI->SetFocus();
                Form1->Edt_HINMEI->SelectAll();
                break;

            // �ڍו��@�f�ޗp�i�ԂɃt�H�[�J�X���L��ꍇ
            case 11:
    	        for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
                	sBuf = SGr1->Cells[1][i];
                    if( sBuf.Trim() != "" )	{
                	    if( Form1->Lbx_DTKSHIN_SZ->Items->Count >= 6 )	break;
                	    Form1->Lbx_DTKSHIN_SZ->Items->Add(sBuf);
                    }
                }
                Form1->Lbx_DTKSHIN_SZ->ItemIndex = Form1->Lbx_DTKSHIN_SZ->Items->Count - 1;
                Form1->Lbx_DTKSHIN_SZ->Selected[Form1->Lbx_DTKSHIN_SZ->ItemIndex-1] = true;
                Form1->Btn_DTKSHIN_SZ_ADD->SetFocus();

                // �f�[�^�ύX�t���O�̐ݒ�
                Form1->DataChange = 1;
                break;
        }
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
void __fastcall TForm5::SGr1Click(TObject *Sender)
{
   	iRowSelTop    = SGr1->Selection.Top;
   	iRowSelBottom = SGr1->Selection.Bottom;

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
void __fastcall TForm5::SGr1DblClick(TObject *Sender)
{
	BtnF04Click(BtnF04);
}


