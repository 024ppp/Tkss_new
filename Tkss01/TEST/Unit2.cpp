//---------------------------------------------------------------------------
//
//  Unit2.cpp
//    �y�o�׌����V�X�e���|��������z
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
#include "Unit3.h"
#include "Unit8.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
extern AnsiString sMEMO_NAME;
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
void __fastcall TForm2::SGr1Click(TObject *Sender)
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
void __fastcall TForm2::SGr1DblClick(TObject *Sender)
{
	BtnF04Click(BtnF04);
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
     AnsiString wLOTNO;
     AnsiString wLOTYY;

     SGr1->Tag = 0;    // �I���t���OOFF

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     SGr1->Row = 1;     // �I���s�̏�����

     switch( Form2->Tag ){

        // �m�����ʁn�������@��\���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
        case 1:

            // �⍇�����s
            sBuf  = "select DTKSHIN, HINBAN, ZISNAM, HINMEI from KSM01";
            sBuf += " where REVCNT = 0";
            if( Form1->Cmb_DTKSHIN->Text.Trim() != "" ){
                // ���Ӑ�i��
                sBuf += " and DTKSHIN like '" + Form1->Cmb_DTKSHIN->Text + "%'";
            }
            sBuf += " ORDER BY DTKSHIN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 5;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "���Еi��";
            SGr1->Cells[3][0] = "�i�@��";
            SGr1->Cells[4][0] = "�i�@��";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 166;
            SGr1->ColWidths[2] = 110;
            SGr1->ColWidths[3] = 110;
            SGr1->ColWidths[4] = 110;
            break;

        // �m�����ʁn�������@���b�gNO�Ƀt�H�[�J�X���L��ꍇ
        case 2:

            // �⍇�����s
            sBuf  = "select KSM01.DTKSHIN, SD21S.LOTBNG, SD21S.DENYMD, SD21S.KOKBNG from KSM01";
            sBuf += " inner join SD21S on KSM01.DTKSHIN = SD21S.DTKSHIN";
            sBuf += " where KSM01.REVCNT = 0";
            if( Form1->Cmb_DTKSHIN->Text.Trim() != "" ){
                // ���Ӑ�i��
                sBuf += " and KSM01.DTKSHIN like '" + Form1->Cmb_DTKSHIN->Text + "%'";
            }
            sBuf += " and length(ltrim(rtrim(SD21S.LOTBNG)))>0";
            //sBuf += " order by KSM01.DTKSHIN, substr(SD21S.LOTBNG,2)";
            sBuf += " order by KSM01.DTKSHIN, SD21S.LOTBNG";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "���b�gNO";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // �m���b�g������ʁnStringGrid���@�������b�g�Ƀt�H�[�J�X���L��ꍇ
        case 3:

            // �⍇�����s
            sBuf  = "select DTKSHIN, LOTNO from KSD21";
            if( Trim(Form8->SGr_vRIRE_SYUKA->Cells[0][Form8->SGr_vRIRE_SYUKA->Row]) != "" ){
            	sBuf += " where DTKSHIN = '";
            	sBuf += Trim(Form8->SGr_vRIRE_SYUKA->Cells[0][Form8->SGr_vRIRE_SYUKA->Row]);
				sBuf += "'";
            }
            sBuf += " ORDER BY DTKSHIN, SUBSTR(LOTNO,2)";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "���b�gNO";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // �m���b�g������ʁnStringGrid���@���胍�b�g�Ƀt�H�[�J�X���L��ꍇ
        case 4:

            // �⍇�����s
            sBuf  = "select DTKSHIN, LOTNO from KSD21";
            if( Trim(Form8->SGr_vRIRE_SYUKA->Cells[0][Form8->SGr_vSOKU_SYUKA->Row]) != "" ){
            	sBuf += " where DTKSHIN = '";
            	sBuf += Trim(Form8->SGr_vRIRE_SYUKA->Cells[0][Form8->SGr_vSOKU_SYUKA->Row]);
				sBuf += "'";
            }
            sBuf += " ORDER BY DTKSHIN, SUBSTR(LOTNO,2)";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "���b�gNO";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // �m���ڕҏW��ʁn�ڍו��@���Ӑ�R�[�h�A���Ӑ於�̂Ƀt�H�[�J�X���L��ꍇ
        case 5:
        case 6:

            // �⍇�����s
            sBuf = "select DISTINCT TRSCOD, TRSNAM from SM16S where TKSKBN=1";
            if( Form3->Edt_DTKSCOD->Text.Trim() != "" ){
                // ���Ӑ�R�[�h
                sBuf += " and TRSCOD like '" + Form3->Edt_DTKSCOD->Text + "%'";
            }
            sBuf += " ORDER BY TRSCOD";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���Ӑ�R�[�h";
            SGr1->Cells[2][0] = "���Ӑ於��";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 100;
            SGr1->ColWidths[2] = 400;
            break;

        // �m���ڕҏW��ʁn�ڍו��@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
        // �m���ڕҏW��ʁn�ڍו��@���Еi�ԂɃt�H�[�J�X���L��ꍇ
        case 7:
        case 8:

            // �⍇�����s
            sBuf = "select DISTINCT DTKSHIN, HINBAN from SD21S where length(ltrim(rtrim(DTKSHIN)))>0";
            if( Trim(Form3->Edt_DTKSCOD->Text) != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " and DTKSCOD like '";
                sBuf = sBuf + Form3->Edt_DTKSCOD->Text ;
                sBuf = sBuf + "%'";
            }
            if( Trim(Form3->Edt_DTKSHIN->Text) != "" ){
                // ���Ӑ�i��
                sBuf = sBuf + " and DTKSHIN like '";
                sBuf = sBuf + Form3->Edt_DTKSHIN->Text ;
                sBuf = sBuf + "%'";
            }
            if( Trim(Form3->Edt_HINBAN->Text) != "" ){
                // ���Еi��
                sBuf = sBuf + " and HINBAN like '";
                sBuf = sBuf + Form3->Edt_HINBAN->Text ;
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

        // �m���ڕҏW��ʁn�ڍו��@�ގ����́i�i��j�Ƀt�H�[�J�X���L��ꍇ
        case 9:

            // �⍇�����s
            sBuf = "select DISTINCT ZISNAM, ZISCOD from KM03";
            if( Trim(Form3->Edt_ZISNAM->Text) != "" ){
                // �ގ�����
                sBuf = sBuf + " where ZISNAM like '";
                sBuf = sBuf + Form3->Edt_ZISNAM->Text ;
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

        // �m���ڕҏW��ʁn�ڍו��@�i���Ƀt�H�[�J�X���L��ꍇ
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

        // �m���ڕҏW��ʁn�ڍו��@�f�ޗp�i�Ԃ́u�w��v�{�^���Ƀt�H�[�J�X���L��ꍇ
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
            //  [���l���n�Ƀt�H�[�J�X������ꍇ
        case 12:
            sBuf  = "SELECT MEMO from KSM91";
            sBuf += " ORDER BY MEMO_NO";
            // �^�C�g�����Z�b�g
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "  NO";
            SGr1->Cells[1][0] = "���@�l";
            SGr1->ColWidths[0] = 36;
            SGr1->ColWidths[1] = 500;
            break;
    }

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
        if( sBuf.Length() > 5 )	sBuf = sBuf.SubString( sBuf.Length() - 4, 5 );
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;

        // �f�[�^
        for( i=1; i<SGr1->ColCount; i++){
            sBuf = Query1->Fields->Fields[i-1]->AsString;
            if( Form2->Tag == 11 && i == 3 ){
            	// ���t�t�H�[�}�b�g�ɕϊ�
                sBuf.Insert("/",5);
                sBuf.Insert("/",8);
            }
            if( Form2->Tag == 11 && i == 4 ){
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
        iRow = 1;
    }
    if( Form2->Tag == 2 ){
    	SGr1->Row = iRow;
    } else {
    	SGr1->Row = 1;
    }
    SGr1->SetFocus();

  	iRowSelTop    = SGr1->Row;
   	iRowSelBottom = SGr1->Row;

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
    int			i;
    int			iCol,iRow;
    int         iNum;
    AnsiString	sBuf;


    if( !fFind )   return;

    // �I���t���OON�̎�
    if( SGr1->Tag ){

        switch( Form2->Tag ){

            // �m�����ʁn�������@��\���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
            case 1:
                Form1->Cmb_DTKSHIN->Items->Clear();
                Form1->Cmb_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];
                Form1->Cmb_DTKSHIN->SetFocus();
                Form1->Cmb_DTKSHIN->SelectAll();
                break;

            // �m�����ʁn�������@���b�gNO�Ƀt�H�[�J�X���L��ꍇ
            case 2:
                if( SGr1->Cells[1][iRowSelTop] != SGr1->Cells[1][iRowSelBottom] ){
					MessageDlg("�قȂ链�Ӑ�i�ԓ��m�͎w��ł��܂���B", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
                    CanClose = false;
                	return;
                }
                Form1->Cmb_DTKSHIN->Text = SGr1->Cells[1][iRowSelTop];
                if( iRowSelTop != iRowSelBottom ){
                    sBuf = "";
	    	        for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
    	            	if( SGr1->Cells[2][i].Trim() != "" )	{
                            if( sBuf.Length() > 0 )	sBuf = sBuf + ",";
                        	sBuf = sBuf + SGr1->Cells[2][i].Trim();
                    	}
                	}
                    Form1->Edt_LOTNO->Text = sBuf;
                	//Form1->Edt_LOTNO->Text = SGr1->Cells[2][iRowSelTop] + "-" + SGr1->Cells[2][iRowSelBottom];
                } else {
                	Form1->Edt_LOTNO->Text = SGr1->Cells[2][SGr1->Row];
                }
                Form1->Edt_LOTNO->SetFocus();
                Form1->Edt_LOTNO->SelectAll();
                break;

            // �m���b�g������ʁnStringGrid���@�������b�g�Ƀt�H�[�J�X���L��ꍇ
            case 3:
                iCol = Form8->SGr_vRIRE_SYUKA->Col;
                iRow = Form8->SGr_vRIRE_SYUKA->Row;
                Form8->SGr_vRIRE_SYUKA->Cells[iCol][iRow] = SGr1->Cells[2][SGr1->Row];
                Form8->SGr_vRIRE_SYUKA->SetFocus();
                break;

            // �m���b�g������ʁnStringGrid���@���胍�b�g�Ƀt�H�[�J�X���L��ꍇ
            case 4:
                iCol = Form8->SGr_vSOKU_SYUKA->Col;
                iRow = Form8->SGr_vSOKU_SYUKA->Row;
                Form8->SGr_vSOKU_SYUKA->Cells[iCol][iRow] = SGr1->Cells[2][SGr1->Row];
                Form8->SGr_vSOKU_SYUKA->SetFocus();
                break;

            // �m���ڕҏW��ʁn�ڍו��@���Ӑ�R�[�h�A���Ӑ於�̂Ƀt�H�[�J�X���L��ꍇ
            case 5:
            case 6:
                Form3->Edt_DTKSCOD->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�R�[�h
                Form3->Edt_DTKSNAM->Text = SGr1->Cells[2][SGr1->Row];      // ���Ӑ於��
                if( Form3->BtnF01->Tag == 5 ){
                    Form3->Edt_DTKSCOD->SetFocus();
                    Form3->Edt_DTKSCOD->SelectAll();
                }
                if( Form3->BtnF01->Tag == 6 ){
                    Form3->Edt_DTKSNAM->SetFocus();
                    Form3->Edt_DTKSNAM->SelectAll();
                }
                break;

            // �m���ڕҏW��ʁn�ڍו��@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
            // �m���ڕҏW��ʁn�ڍו��@���Еi�ԂɃt�H�[�J�X���L��ꍇ
            case 7:
            case 8:
                Form3->Edt_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�i��
                Form3->Edt_HINBAN->Text  = SGr1->Cells[2][SGr1->Row];      // ���Еi��
                if( Form3->BtnF01->Tag == 7 ){
                    Form3->Edt_DTKSHIN->SetFocus();
                    Form3->Edt_DTKSHIN->SelectAll();
                }
                if( Form3->BtnF01->Tag == 8 ){
                    Form3->Edt_HINBAN->SetFocus();
                    Form3->Edt_HINBAN->SelectAll();
                }
                break;

            // �m���ڕҏW��ʁn�ڍו��@�ގ����́i�i��j�Ƀt�H�[�J�X���L��ꍇ
            case 9:
                Form3->Edt_ZISNAM->Text = SGr1->Cells[1][SGr1->Row];      // �ގ�����
                Form3->Edt_ZISNAM->SetFocus();
                Form3->Edt_ZISNAM->SelectAll();
                break;

            // �m���ڕҏW��ʁn�ڍו��@�i���Ƀt�H�[�J�X���L��ꍇ
            case 10:
                Form3->Edt_HINMEI->Text = SGr1->Cells[1][SGr1->Row];      // �i��
                Form3->Edt_HINMEI->SetFocus();
                Form3->Edt_HINMEI->SelectAll();
                break;

            // �m���ڕҏW��ʁn�ڍו��@�f�ޗp�i�ԂɃt�H�[�J�X���L��ꍇ
            case 11:
    	        for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
                	sBuf = SGr1->Cells[1][i];
                    if( sBuf.Trim() != "" )	{
                	    if( Form3->Lbx_DTKSHIN_SZ->Items->Count >= 6 )	break;
                	    Form3->Lbx_DTKSHIN_SZ->Items->Add(sBuf);
                    }
                }
                Form3->Lbx_DTKSHIN_SZ->ItemIndex = Form3->Lbx_DTKSHIN_SZ->Items->Count - 1;
                Form3->Lbx_DTKSHIN_SZ->Selected[Form3->Lbx_DTKSHIN_SZ->ItemIndex-1] = true;
                Form3->Btn_DTKSHIN_SZ_ADD->SetFocus();

                // �f�[�^�ύX�t���O�̐ݒ�
                Form3->DataChange = 1;
                break;
            //  [���l��] �Ƀt�H�[�J�X������ꍇ
            case 12:
                iNum = sMEMO_NAME.SubString(15,sMEMO_NAME.Length()-14).ToIntDef(0);
                if(sMEMO_NAME.SubString(5,5) == "vRIRE" )
                {
                   Form1->Mem_vRIRE_MEMO[iNum]->Lines->Add(SGr1->Cells[1][SGr1->Row]);
                }
                else
                {
                   Form1->Mem_vSOKU_MEMO[iNum]->Lines->Add(SGr1->Cells[1][SGr1->Row]);
                }
                //Form1->ADD_MEMO->Text += '\n' + SGr1->Cells[1][SGr1->Row];
                //Form1->EdtSETMEMO->Text = SGr1->Cells[1][SGr1->Row];	// ���l
                //Form1->EdtSETMEMO->SetFocus();
                //Form1->EdtSETMEMO->SelectAll();
                break;
        }
    }
}


