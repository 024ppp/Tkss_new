//---------------------------------------------------------------------------
//
//  Unit2.cpp
//    �y�o�׌����V�X�e���|���|�[�g�o�́z
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
void __fastcall TForm2::FormActivate(TObject *Sender)
{

     int		i;
     int		iRow;
     int        iDateNo;
     AnsiString	sBuf;
	 AnsiString	sDTKSHIN_KEY;


     SGr1->Tag = 0;    // �I���t���OOFF

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     SGr1->Row = 1;     // �I���s�̏�����


     // �_�~�[�f�[�^�̃^�C�g�����Z�b�g
     SGr1->ColCount = 5;
     SGr1->Cells[0][0] = "   N O";
     SGr1->Cells[1][0] = "���Ӑ�i��";
     SGr1->Cells[2][0] = "���Еi��";
     SGr1->Cells[3][0] = "�i�@��";
     SGr1->Cells[4][0] = "���b�gNo";
     SGr1->ColWidths[0] = 55;
     SGr1->ColWidths[1] = 180;
     SGr1->ColWidths[2] = 160;
     SGr1->ColWidths[3] = 100;
     SGr1->ColWidths[4] = 80;


     switch( Form1->BtnF01->Tag ){

        // �u�������я��v�Ƀt�H�[�J�X���L��ꍇ
        case 1:
        case 2:
        	sDTKSHIN_KEY = Form1->Edt1_WHR_DTKSHIN->Text;
            break;
        // �u�������я��i���ʁj��v�Ƀt�H�[�J�X���L��ꍇ
        case 3:
        case 4:
        	sDTKSHIN_KEY = Form1->Edt2_WHR_DTKSHIN1->Text;
            break;
        // �u�������я��i���ʁj���v�Ƀt�H�[�J�X���L��ꍇ
        case 5:
        case 6:
        case 7:
        	sDTKSHIN_KEY = Form1->Edt2_WHR_DTKSHIN2->Text;
            break;
        // �u�ޗ��ؖ����v�Ƀt�H�[�J�X���L��ꍇ
        case 8:
        case 9:
        	sDTKSHIN_KEY = Form1->Edt3_WHR_DTKSHIN->Text;
            break;
        // �u�ޗ��ؖ����i���ʁj��v�Ƀt�H�[�J�X���L��ꍇ
        case 10:
        case 11:
        	sDTKSHIN_KEY = Form1->Edt4_WHR_DTKSHIN1->Text;
            break;
        // �u�ޗ��ؖ����i���ʁj���v�Ƀt�H�[�J�X���L��ꍇ
        case 12:
        case 13:
        case 14:
        	sDTKSHIN_KEY = Form1->Edt4_WHR_DTKSHIN2->Text;
            break;
        // �u�������ʎ��n��Ǘ��\�v�Ƀt�H�[�J�X���L��ꍇ
        case 15:
        case 16:
        case 31:
        case 32:
        	sDTKSHIN_KEY = Form1->Edt5_WHR_DTKSHIN1->Text;
            break;
        // �u�����o��[��v�Ƀt�H�[�J�X���L��ꍇ
        case 17:
        case 18:
        	sDTKSHIN_KEY = Form1->Edt6_WHR_DTKSHIN1->Text;
            break;
	 }

     switch( Form1->BtnF01->Tag ){

        // ���Ӑ�i�ԁ@�Ƀt�H�[�J�X���L��ꍇ
        case 1:
        case 3:
        case 5:
        case 8:
        case 10:
        case 12:
        case 15:

            // �⍇�����s
            sBuf  = "select DISTINCT DTKSHIN, ";
            sBuf +=        "Count(LOTNO) AS LOTNO_CNT, ";
            sBuf +=        "Max(SKTYMD) AS SKTYMD_MAX ";
            sBuf += "from KSD01 ";
            if( sDTKSHIN_KEY.Trim() != "" ){
                // ���Ӑ�i��
                sBuf = sBuf + " where DTKSHIN like '";
                sBuf = sBuf + sDTKSHIN_KEY.Trim() ;
                sBuf = sBuf + "%'";
            }
            sBuf += "group by DTKSHIN ";
            sBuf += "order by DTKSHIN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "����ςݓ��Ӑ�i��";
            SGr1->Cells[2][0] = "����LOT��";
            SGr1->Cells[3][0] = "�ŏI�����";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 200;
            SGr1->ColWidths[2] = 80;
            SGr1->ColWidths[3] = 90;
            iDateNo = 3;
            break;

        //2003/08/27 E.Takase
        //���肵�ĂȂ����b�g���o�͂ł���悤�ɂ���
        //�����Y�Ǘ��V�X�e�����猟������
        case 17:


            // �⍇�����s
            sBuf  = "select DISTINCT SD21S.DTKSHIN  AS DTKSHIN,  ";
            sBuf +=        "Count(SD21S.LOTBNG) AS LOTNO_CNT, ";
            sBuf +=        "Max(KSD01.SKTYMD) AS SKTYMD_MAX ";
            sBuf += "from SD21S, KSD01  ";
            sBuf += "where KSD01.LOTNO(+) = SD21S.LOTBNG  ";
            sBuf += "and KSD01.DTKSHIN(+) = SD21S.DTKSHIN  ";
            if( sDTKSHIN_KEY.Trim() != "" ){
                // ���Ӑ�i��
                sBuf = sBuf + " and SD21S.DTKSHIN like '";
                sBuf = sBuf + sDTKSHIN_KEY.Trim() ;
                sBuf = sBuf + "%'";
            }
            sBuf += "group by SD21S.DTKSHIN ";
            sBuf += "order by SD21S.DTKSHIN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "����ςݓ��Ӑ�i��";
            SGr1->Cells[2][0] = "����LOT��";
            SGr1->Cells[3][0] = "�ŏI�����";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 200;
            SGr1->ColWidths[2] = 80;
            SGr1->ColWidths[3] = 90;
            iDateNo = 3;
            break;

        // ���b�g�m���Ƀt�H�[�J�X���L��ꍇ
        case 2:
        case 4:
        case 9:
        case 11:
        case 16:

            // �⍇�����s
            sBuf = "select DTKSHIN, LOTNO, HINBAN, SKTYMD from KSD01 ";
            //if( sDTKSHIN_KEY.Trim() != "" ){
                // ���Ӑ�i��
                sBuf += "where DTKSHIN like '";
                sBuf += sDTKSHIN_KEY.Trim();
                sBuf += "%' ";
            //}
            sBuf += " AND  SKTYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi
            sBuf += "order by DTKSHIN, HINBAN, substr(LOTNO,2)";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 5;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "����ςݓ��Ӑ�i��";
            SGr1->Cells[2][0] = "����ς�LOTNO";
            SGr1->Cells[3][0] = "���Еi��";
            SGr1->Cells[4][0] = "�����";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 150;
            SGr1->ColWidths[2] = 100;
            SGr1->ColWidths[3] = 100;
            SGr1->ColWidths[4] = 90;
            iDateNo = 4;
            break;


        //2003/08/27 E.Takase
        //���肵�ĂȂ����b�g���o�͂ł���悤�ɂ���
        //�����Y�Ǘ��V�X�e�����猟������
        case 18:

            // �⍇�����s
            sBuf  = "select DISTINCT SD21S.DTKSHIN  AS DTKSHIN,  ";
            sBuf +=        "SD21S.LOTBNG AS LOTNO_CNT, ";
            sBuf +=        "KSD01.SKTYMD AS SKTYMD_MAX ";
            sBuf += "from SD21S, KSD01  ";
            sBuf += "where KSD01.LOTNO(+) = SD21S.LOTBNG  ";
            sBuf += "and KSD01.DTKSHIN(+) = SD21S.DTKSHIN  ";
            if( sDTKSHIN_KEY.Trim() != "" ){
                // ���Ӑ�i��
                sBuf = sBuf + " and SD21S.DTKSHIN like '";
                sBuf = sBuf + sDTKSHIN_KEY.Trim() ;
                sBuf = sBuf + "%'";
            }
            sBuf += "order by SD21S.DTKSHIN, substr(SD21S.LOTBNG,2)";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "����ςݓ��Ӑ�i��";
            SGr1->Cells[2][0] = "����ς�LOTNO";
            SGr1->Cells[3][0] = "�����";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 200;
            SGr1->ColWidths[2] = 100;
            SGr1->ColWidths[3] = 90;
            iDateNo = 3;
            break;

        // �o�ד��Ƀt�H�[�J�X���L��ꍇ
        case 6:
        case 7:
        case 13:
        case 14:
        case 31:
        case 32:

            // �⍇�����s
            sBuf  = "select DTKSHIN, LOTBNG, ESYUYMD from SD21S ";
            sBuf += "where ESYUYMD != '00000000' ";
            if( sDTKSHIN_KEY.Trim() != "" ){
                // ���Ӑ�i��
                sBuf += "and DTKSHIN like '";
                sBuf += sDTKSHIN_KEY.Trim();
                sBuf += "%' ";
            }
            sBuf += " AND  ESYUYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi
            sBuf += "order by DTKSHIN, ESYUYMD, substr(LOTBNG,2)";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "�o�׍ςݓ��Ӑ�i��";
            SGr1->Cells[2][0] = "�o�׍ς�LOTNO";
            SGr1->Cells[3][0] = "�o�ד�";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 200;
            SGr1->ColWidths[2] = 100;
            SGr1->ColWidths[3] = 90;
            iDateNo = 3;
            break;

        // �������Ƀt�H�[�J�X���L��ꍇ
        case 19:
        case 20:

            // �⍇�����s
            sBuf  = "select DISTINCT SKTYMD_PRT from KSD01 ";
            sBuf += "where SKTYMD_PRT >= '00000000' and SKTYMD_PRT <= '99999999' ";
            sBuf += "order by SKTYMD_PRT";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "   N O";
            SGr1->Cells[1][0] = "������";
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 100;
            iDateNo = 1;
            break;

        // ���|�[�g�p�Ж��i���{��j�Ƀt�H�[�J�X���L��ꍇ
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:

            // �⍇�����s
            sBuf  = "select CORP_NAME from KSM93 ";
            if( Form1->BtnF01->Tag == 21 ||
                Form1->BtnF01->Tag == 23 ||
                Form1->BtnF01->Tag == 25 ||
                Form1->BtnF01->Tag == 27 ||
                Form1->BtnF01->Tag == 29 ){
            	sBuf += "where ENG_FLG = 0 ";
            } else {
            	sBuf += "where ENG_FLG = 1 ";
            }
            sBuf += "order by ORDER_NO";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = "   N O";
            if( Form1->BtnF01->Tag == 21 ||
                Form1->BtnF01->Tag == 23 ||
                Form1->BtnF01->Tag == 25 ||
                Form1->BtnF01->Tag == 27 ||
                Form1->BtnF01->Tag == 29 ){
            	SGr1->Cells[1][0] = "�Ж��i���{��j";
            } else {
            	SGr1->Cells[1][0] = "�Ж��i�p��j";
            }
            SGr1->ColWidths[0] = 55;
            SGr1->ColWidths[1] = 400;
            iDateNo = 0;
            break;
        // ���̑�
        default:
            Close();
            return;
            break;
    }

    Query1->SQL->Add(sBuf);
    ClpBrd = Clipboard();
    ClpBrd->Open();
    ClpBrd->SetTextBuf(sBuf.c_str());
    ClpBrd->Close();
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
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 8-sBuf.Length()) + sBuf;

        // �f�[�^
        for( i=1; i<SGr1->ColCount; i++){
            sBuf = Query1->Fields->Fields[i-1]->AsString;
            if( i == iDateNo ){
            	// ���t�t�H�[�}�b�g�𐮂��܂�
                //2003/08/27 E.Takase ���t �󔒂̂Ƃ��� ���̂܂�
                if ( sBuf.Trim() != "" ) {
					sBuf = sBuf.Insert("/",5);
					sBuf = sBuf.Insert("/",8);
                }
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
    SGr1->SetFocus();

	if( Form1->BtnF01->Tag == 19 || Form1->BtnF01->Tag == 20 ){
    	SGr1->Row = SGr1->RowCount - 1;		// �Ō�̍s��I��
    } else {
    	SGr1->Row = 1;                  	// �ŏ��̍s��I��
    }
  	iRowSelTop    = SGr1->Row;
   	iRowSelBottom = SGr1->Row;

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
	AnsiString sBuf1;
	AnsiString sBuf2;

    if( !fFind )   return;

    // �I���t���OON�̎�
    if( SGr1->Tag ){

        // �͈͎w�莞�̃G���[�`�F�b�N
        switch( Form1->BtnF01->Tag ){
        	// ���b�g�m���Ƀt�H�[�J�X
            case 2:
        	case 4:
        	case 9:
        	case 11:
        	case 16:
        	case 18:
                if( SGr1->Cells[1][iRowSelTop] != SGr1->Cells[1][iRowSelBottom] ){
					MessageDlg("�قȂ链�Ӑ�i�ԓ��m�͎w��ł��܂���B", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
                    CanClose = false;
                	return;
                }
                if( SGr1->Cells[2][iRowSelTop] != SGr1->Cells[2][iRowSelBottom] ){
                    int	i;
                    sBuf1 = "";
	    	        for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
    	            	if( SGr1->Cells[2][i].Trim() != "" )	{
                            if( sBuf1.Length() > 0 )	sBuf1 = sBuf1 + ",";
                        	sBuf1 = sBuf1 + SGr1->Cells[2][i].Trim();
                    	}
                	}
                } else {
                    sBuf1 = SGr1->Cells[2][iRowSelTop];
                }
                break;

        	// �o�ד��Ƀt�H�[�J�X���L��ꍇ
        	case 6:
        	case 7:
        	case 13:
        	case 14:
        	case 31:
        	case 32:
                if( SGr1->Cells[1][iRowSelTop] != SGr1->Cells[1][iRowSelBottom] ){
					MessageDlg("�قȂ链�Ӑ�i�ԓ��m�͎w��ł��܂���B", mtWarning,
								TMsgDlgButtons() << mbOK , 0);
                    CanClose = false;
                	return;
                }
                sBuf1	= SGr1->Cells[3][iRowSelTop];		// �͈͑I���i�J�n�j
                sBuf2	= SGr1->Cells[3][iRowSelBottom];	// �͈͑I���i�I���j
                break;

        	// �������Ƀt�H�[�J�X���L��ꍇ
        	case 19:
        	case 20:
                sBuf1	= SGr1->Cells[1][iRowSelTop];		// �͈͑I���i�J�n�j
                sBuf2	= SGr1->Cells[1][iRowSelBottom];	// �͈͑I���i�I���j
				break;
        }

        // �w�肵���f�[�^���t�B�[���h�ɃZ�b�g���܂�
        switch( Form1->BtnF01->Tag ){

            case 1:		// �u�������я��v���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
                Form1->Edt1_WHR_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 2:		// �u�������я��v���b�g�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt1_WHR_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt1_WHR_LOTNO->Text = sBuf1;
                break;

            case 3:		// �u�������я�(����)�v���Ӑ�i�ԁi��j�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt2_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 4:		// �u�������я�(����)�v���b�g�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt2_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt2_WHR_LOTNO1->Text = sBuf1;
                break;

            case 5:		// �u�������я�(����)�v���Ӑ�i�ԁi���j�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt2_WHR_DTKSHIN2->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 6:		// �u�������я�(����)�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
            case 7:		// �u�������я�(����)�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt2_WHR_DTKSHIN2->Text = SGr1->Cells[1][SGr1->Row];
                if( sBuf1 == sBuf2 ){
                	if( Form1->BtnF01->Tag == 6 )	Form1->Edt2_WHR_SYUKADATE1->Text = sBuf1;
                	if( Form1->BtnF01->Tag == 7 )	Form1->Edt2_WHR_SYUKADATE2->Text = sBuf1;
                } else {
                	Form1->Edt2_WHR_SYUKADATE1->Text = sBuf1;
                	Form1->Edt2_WHR_SYUKADATE2->Text = sBuf2;
                }
                break;

            case 8:		// �u�ޗ��ؖ����v���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
                Form1->Edt3_WHR_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 9:		// �u�ޗ��ؖ����v���b�g�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt3_WHR_DTKSHIN->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt3_WHR_LOTNO->Text = sBuf1;
                break;

            case 10:	// �u�ޗ��ؖ���(����)�v���Ӑ�i�ԁi��j�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt4_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 11:	// �u�ޗ��ؖ���(����)�v���b�g�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt4_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt4_WHR_LOTNO1->Text = sBuf1;
                break;

            case 12:	// �u�ޗ��ؖ���(����)�v���Ӑ�i�ԁi���j�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt4_WHR_DTKSHIN2->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 13:	// �u�ޗ��ؖ���(����)�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
            case 14:	// �u�ޗ��ؖ���(����)�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt4_WHR_DTKSHIN2->Text = SGr1->Cells[1][SGr1->Row];
                if( sBuf1 == sBuf2 ){
                	if( Form1->BtnF01->Tag == 13 )	Form1->Edt4_WHR_SYUKADATE1->Text = sBuf1;
                	if( Form1->BtnF01->Tag == 14 )	Form1->Edt4_WHR_SYUKADATE2->Text = sBuf1;
                } else {
                	Form1->Edt4_WHR_SYUKADATE1->Text = sBuf1;
                	Form1->Edt4_WHR_SYUKADATE2->Text = sBuf2;
                }
                break;

            case 15:	// �u�������ʎ��n��Ǘ��\�v���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
                Form1->Edt5_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 16:	// �u�������ʎ��n��Ǘ��\�v���b�g�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt5_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt5_WHR_LOTNO->Text = sBuf1;
                break;

            case 17:	// �u�����o��[�v���Ӑ�i�ԁi��j�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt6_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 18:	// �u�����o��[�v���b�g�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt6_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
               	Form1->Edt6_WHR_LOTNO1->Text = sBuf1;
                break;

            case 19:	// �u�����o��[�v�������i���j�Ƀt�H�[�J�X���L��ꍇ
            case 20:	// �u�����o��[�v�������i���j�Ƀt�H�[�J�X���L��ꍇ
                if( sBuf1 == sBuf2 ){
                	if( Form1->BtnF01->Tag == 19 )	Form1->Edt6_WHR_KENSADATE1->Text = sBuf1;
                	if( Form1->BtnF01->Tag == 20 )	Form1->Edt6_WHR_KENSADATE2->Text = sBuf1;
                } else {
                	Form1->Edt6_WHR_KENSADATE1->Text = sBuf1;
                	Form1->Edt6_WHR_KENSADATE2->Text = sBuf2;
                }
                break;

        	case 21:	// �u�������я��v�Ж��Ƀt�H�[�J�X���L��ꍇ
        	case 22:
                Form1->Edt1_CHK_CUSTOMER->Text = SGr1->Cells[1][SGr1->Row];
                break;

        	case 23:  	// �u�������я�(����)�v�Ж��Ƀt�H�[�J�X���L��ꍇ
        	case 24:
                Form1->Edt2_CHK_CUSTOMER->Text = SGr1->Cells[1][SGr1->Row];
                break;

        	case 25:    // �u�ޗ��ؖ����v�Ж��Ƀt�H�[�J�X���L��ꍇ
        	case 26:
                Form1->Edt3_CHK_CUSTOMER->Text = SGr1->Cells[1][SGr1->Row];
                break;

        	case 27:    // �u�ޗ��ؖ���(����)�v�Ж��Ƀt�H�[�J�X���L��ꍇ
        	case 28:
                Form1->Edt4_CHK_CUSTOMER->Text = SGr1->Cells[1][SGr1->Row];
                break;

        	case 29:    // �u�������ʎ��n��Ǘ��\�v�Ж��i���{��j�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt5_CHK_CUSTOMER->Text = SGr1->Cells[1][SGr1->Row];
                break;

        	case 30:    // �u�������ʎ��n��Ǘ��\�v�Ж��i�p��j�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt5_CHK_CUSTOMER2->Text = SGr1->Cells[1][SGr1->Row];
                break;

            case 31:	// �u�������ʎ��n��Ǘ��\�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
            case 32:	// �u�������ʎ��n��Ǘ��\�v�o�ד��i���j�Ƀt�H�[�J�X���L��ꍇ
                Form1->Edt5_WHR_DTKSHIN1->Text = SGr1->Cells[1][SGr1->Row];
                if( sBuf1 == sBuf2 ){
                	if( Form1->BtnF01->Tag == 31 )	Form1->Edt5_WHR_SYUKADATE1->Text = sBuf1;
                	if( Form1->BtnF01->Tag == 32 )	Form1->Edt5_WHR_SYUKADATE2->Text = sBuf1;
                } else {
                	Form1->Edt5_WHR_SYUKADATE1->Text = sBuf1;
                	Form1->Edt5_WHR_SYUKADATE2->Text = sBuf2;
                }
                break;
        }

    }

}


