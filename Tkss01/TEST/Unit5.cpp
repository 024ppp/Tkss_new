//---------------------------------------------------------------------------
//
//  Unit5.cpp
//    �y�o�׌����V�X�e���|��������z
//    �f�ތ������ڃt�H�[���iTForm5�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �c���@�֎i
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
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
//    OnCreate�C�x���g	�FForm5���쐬�����Ƃ��ɔ������܂��B
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
void __fastcall TForm5::FormCreate(TObject *Sender)
{

	int				i, k;
    TStringGrid*	sg;

    for( i=1; i<=6; i++ ){
    	switch( i ){
        	case 1:	sg = dynamic_cast<TStringGrid*>(SGr_List1);
            		break;
        	case 2:	sg = dynamic_cast<TStringGrid*>(SGr_List2);
            		break;
        	case 3:	sg = dynamic_cast<TStringGrid*>(SGr_List3);
            		break;
        	case 4:	sg = dynamic_cast<TStringGrid*>(SGr_List4);
            		break;
        	case 5:	sg = dynamic_cast<TStringGrid*>(SGr_List5);
            		break;
        	case 6:	sg = dynamic_cast<TStringGrid*>(SGr_List6);
            		break;
        }

		// �^�C�g�����Z�b�g
		sg->ColCount = 23;
		sg->Cells[0][0] = " NO";
		sg->Cells[1][0] = "���荀��";
		sg->Cells[2][0] = "����@��";
		sg->Cells[3][0] = "�P��";
		sg->Cells[4][0] = "�K�i";
		sg->Cells[5][0] = "n��";
		sg->ColWidths[0] = 25;
		sg->ColWidths[1] = 160;
		sg->ColWidths[2] = 140;
		sg->ColWidths[3] = 60;
		sg->ColWidths[4] = 140;
		sg->ColWidths[5] = 25;
	    for( k=6; k<sg->ColCount; k++ ){
			sg->ColWidths[k] = 0;
        }
    }

    // �R���g���[���̍Ĕz�u
    Pnl_KIKAKU_KIJYUN->Left = Pnl_KIKAKU_HANI->Left;

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
void __fastcall TForm5::FormActivate(TObject *Sender)
{

	int			i, k;
	AnsiString	sBuf;
	AnsiString	sWhereIN;
    AnsiString	sDTKSHIN;
    bool blnHoge=true;


    sWhereIN = "";

	// �f�ޗp�i�ԂŎw�肳�ꂽ�i�Ԃ��擾���^�u��ݒ肵�܂�
    Form5->Tag = 1;
    Rdo_SOZAI_SELECT1->Checked = true;
    Rdo_SOZAI_SELECT2->Checked = true;
    Rdo_SOZAI_SELECT3->Checked = true;
    Rdo_SOZAI_SELECT4->Checked = true;
    Rdo_SOZAI_SELECT5->Checked = true;
    Rdo_SOZAI_SELECT6->Checked = true;
    PgCtr_List->ActivePage = TabSheet1;
    for( i=1; i<=Form3->Lbx_DTKSHIN_SZ->Items->Count; i++ ) {
        sBuf = Form3->Lbx_DTKSHIN_SZ->Items->Strings[i-1];
		if( i == 1 ){
        				TabSheet1->Caption = sBuf;
						TabSheet1->TabVisible = true;
		}
        if( i == 2 ){
        				TabSheet2->Caption = sBuf;
						TabSheet2->TabVisible = true;
		}
        if( i == 3 ){
        				TabSheet3->Caption = sBuf;
						TabSheet3->TabVisible = true;
		}
        if( i == 4 ){
        				TabSheet4->Caption = sBuf;
						TabSheet4->TabVisible = true;
		}
        if( i == 5 ){
        				TabSheet5->Caption = sBuf;
						TabSheet5->TabVisible = true;
		}if( i == 6 ){
        				TabSheet6->Caption = sBuf;
						TabSheet6->TabVisible = true;
        }
        if( sWhereIN != "")	sWhereIN = sWhereIN + ", ";
	    sWhereIN = sWhereIN + "'" + sBuf + "'";
    }
    // ���p���Ȃ��^�u���B���܂�
    for( i=Form3->Lbx_DTKSHIN_SZ->Items->Count + 1; i<=6; i++ ) {
		if( i == 1 )	TabSheet1->TabVisible = false;
		if( i == 2 )	TabSheet2->TabVisible = false;
		if( i == 3 )	TabSheet3->TabVisible = false;
		if( i == 4 )	TabSheet4->TabVisible = false;
		if( i == 5 )	TabSheet5->TabVisible = false;
		if( i == 6 )	TabSheet6->TabVisible = false;
    }
    Form5->Tag = 0;


    //----------------------------------------------
    // �f�ސ��i�K�i�}�X�^�[����

	// Initial Query
	Form3->Query1->Close();
	Form3->Query1->SQL->Clear();

	// �⍇�����s�i�f�ސ��i�K�i�}�X�^�[�j
	sBuf  = "SELECT *";
    sBuf += " FROM KM02";
    sBuf += " WHERE DTKSHIN IN( " + sWhereIN + ")";
    sBuf += " AND REVCNT=0";
    sBuf += " ORDER BY DTKSHIN";

	Form3->Query1->SQL->Add(sBuf);
	Form3->Query1->Open();
	Form3->Query1->Active = true;

    if( !Form3->Query1->Eof ){

        // �������m�ې����擾
		iKSM13_DATA_SEL_Cnt = Form3->Query1->RecordCount * 20;

    	// �������m��
    	hMemKSM13_DATA_SEL = GlobalAlloc( GHND, sizeof(struct KSM13_DATA) * iKSM13_DATA_SEL_Cnt );
    	if( hMemKSM13_DATA_SEL == NULL ){
        	Beep();
    		MessageDlg("�������̈���m�ۂł��܂���B(01)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        	return;
    	}
    	pKSM13_DATA_SEL = (struct KSM13_DATA *)GlobalLock(hMemKSM13_DATA_SEL);
    	if( hMemKSM13_DATA_SEL == NULL ){
        	Beep();
    		MessageDlg("�������̈���m�ۂł��܂���B(02)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        	return;
	    }
    }

    i = 0;
	while( !Form3->Query1->Eof ){

       	if( VarIsNull(Form3->Query1->FieldValues["DTKSHIN"]) ){
			sDTKSHIN = "";
		} else{
			sDTKSHIN = Form3->Query1->FieldValues["DTKSHIN"];			// ��\���Ӑ�i��
		}

        // ���[�h������
		sBuf = Form3->Query1->FieldValues["SK_LD_LNG"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
            sBuf = "11";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
            sBuf = "���[�h������";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
            sBuf = "L/W Length";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�m�M�X";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "mm";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["LD_LNG_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["LD_LNG_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_LD_LNG"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // �u���V���i�R���~�F���a�j
		sBuf = Form3->Query1->FieldValues["SK_BURASI"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            if( AnsiString(Form3->Query1->FieldValues["KEIJKBN"]) != "5" ){
            	sBuf = "2";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
                sBuf = "12";
				strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
            	sBuf = "�u���V��";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
            	sBuf = "Brush Width";
				strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            } else {
            	sBuf = "3";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
				sBuf = "14";
				strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
            	sBuf = "���a";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
            	sBuf = "";
				strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            }
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�}�C�N�����[�^";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "mm";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["BURASI_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["BURASI_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_BURASI"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // �u���V���c�����i�R���~�F�O�a�j
		sBuf = Form3->Query1->FieldValues["SK_BURASIT"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            if( AnsiString(Form3->Query1->FieldValues["KEIJKBN"]) != "5" ){
            	sBuf = "4";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
				sBuf = "13";
				strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
            	sBuf = "�u���V�� (�c����)";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
            	sBuf = "Brush Width A";
				strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            } else {
            	sBuf = "5";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
				sBuf = "15";
				strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
            	sBuf = "�O�a";
				strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
            	sBuf = "";
				strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            }
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�}�C�N�����[�^";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "mm";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["BURASIT_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["BURASIT_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_BURASIT"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // ���|��d
		sBuf = Form3->Query1->FieldValues["SK_BOTAI"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "6";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "���|��d";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Apparent Density";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�}�C�N�����[�^��V��";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["BOTAI_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["BOTAI_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_BOTAI"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // ���[�h����t���x
		sBuf = Form3->Query1->FieldValues["SK_LD_HP"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "7";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "10";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "���[�h����t���x";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Pull Strength";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "5";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�ޗ������@";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
			sBuf = Form3->Query1->FieldValues["LD_HP_TAN"];
            switch( sBuf.ToIntDef(1) ){
            	case 1:	sBuf = "kgf";	break;
                case 2:	sBuf = "N"	;	break;
                case 3:	sBuf = "MPa";	break;
            }
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["LD_HP_KYO"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_LD_HP"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // ���[�h����t��R
		sBuf = Form3->Query1->FieldValues["SK_LD_TR"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "8";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "9";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "���[�h����t��R";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Connection Drop";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "12";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "���[�h����t��R����@";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "mV/" + Form3->Query1->FieldValues["LD_TR_DENR"] + "A";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["LD_TR_DENA"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_LD_TR"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // ��R��
		sBuf = Form3->Query1->FieldValues["SK_KOYU"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "9";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "6";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "��R��";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Specific Resistance";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "11";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "��R������@";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "�ʃ��cm";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["KOYU_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["KOYU_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_KOYU"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // �Ȃ�����
		sBuf = Form3->Query1->FieldValues["SK_MAGE"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "10";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "7";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "�Ȃ�����";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Transverse Strength";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "5";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�ޗ������@";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
			sBuf = Form3->Query1->FieldValues["MAGE_TAN"];
            switch( sBuf.ToIntDef(1) ){
            	case 1:	sBuf = "kgf/c�u";	break;
                case 2:	sBuf = "N/c�u"	;	break;
                case 3:	sBuf = "MPa"	;	break;
                case 4:	sBuf = "N/m�u"	;	break;
            }
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["MAGE_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["MAGE_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_MAGE"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // �Ȃ������i�����j
		sBuf = Form3->Query1->FieldValues["SK_MAGEG"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "11";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "8";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "�Ȃ����� (����)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Transverse Strength(Genuine)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "5";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�ޗ������@";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
			sBuf = Form3->Query1->FieldValues["MAGE_TAN"];
            switch( sBuf.ToIntDef(1) ){
            	case 1:	sBuf = "kgf/c�u";	break;
                case 2:	sBuf = "N/c�u"	;	break;
                case 3:	sBuf = "MPa"	;	break;
                case 4:	sBuf = "N/m�u"	;	break;
            }
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["MAGEG_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["MAGEG_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_MAGEG"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // �d�x�g���b�i���ʁj
		sBuf = Form3->Query1->FieldValues["SK_HSC_A"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "12";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "�d�x (HsC ����)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Hardness(HsC P)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "9";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�V���A�d�x�v�b�^";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "HsC";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["HSC_A_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["HSC_A_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_HSC_A"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // �d�x�g���b�i���ʁj
		sBuf = Form3->Query1->FieldValues["SK_HSC_S"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "13";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "3";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "�d�x (HsC ����)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Hardness(HsC S)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "9";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�V���A�d�x�v�b�^";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "HsC";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["HSC_S_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["HSC_S_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_HSC_S"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }


        // �d�x�g���c�i���ʁj
		sBuf = Form3->Query1->FieldValues["SK_HSD_A"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "14";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "4";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "�d�x (HsD ����)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Hardness(HsD P)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "10";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�V���A�d�x�v�c�^";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "HsD";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["HSD_A_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["HSD_A_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_HSD_A"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // �d�x�g���c�i���ʁj
		sBuf = Form3->Query1->FieldValues["SK_HSD_S"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "15";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "5";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "�d�x (HsD ����)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Hardness(HsD S)";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "10";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�V���A�d�x�v�c�^";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "HsD";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["HSD_S_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["HSD_S_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_HSD_S"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // ����
		sBuf = Form3->Query1->FieldValues["SK_ZAKUT"];
        if( sBuf.ToIntDef(0) > 0 ){
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "16";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "16";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "����";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Crackforce";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "5";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�ޗ������@";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "N";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["ZAKUT_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["ZAKUT_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = Form3->Query1->FieldValues["SK_ZAKUT"];
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

        // �q�X�g�O����
		sBuf = Form3->Query1->FieldValues["HIST_SOKUT"];
        if( sBuf.ToIntDef(0) > 0 ){
            // �u���V�����imin�Amax�j
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "17";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "17";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "�u���V����";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Brush Thickness";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�}�C�N�����[�^";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "mm";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
            sBuf = Form3->Query1->FieldValues["HIST_KIKAK"];
            switch( sBuf.ToIntDef(1) ){
            	case 1:	sBuf = "1";		break;		// �����K�i
                case 2:	sBuf = "3";		break;		// �����K�i
                case 3:	sBuf = "2";		break;		// ����K�i
            }
			strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = Form3->Query1->FieldValues["HIST_MIN"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = Form3->Query1->FieldValues["HIST_MAX"];
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;

            // �u���V�����iCp�ACpk�j
			strcpy( pKSM13_DATA_SEL[i].DTKSHIN		,sDTKSHIN.c_str() );// ��\���Ӑ�i��
            sBuf = "18";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = "18";
			strcpy( pKSM13_DATA_SEL[i].ORDER_NO		,sBuf.c_str() );	// �\����
           	sBuf = "�u���V����";
			strcpy( pKSM13_DATA_SEL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j
           	sBuf = "Brush Thickness";
			strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO
            sBuf = "�}�C�N�����[�^";
			strcpy( pKSM13_DATA_SEL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��
            sBuf = "Cpk";
			strcpy( pKSM13_DATA_SEL[i].TANI			,sBuf.c_str() );	// �P��
            sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v
          	sBuf = "3";
            strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = "1.33";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( pKSM13_DATA_SEL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����
			sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = "1";
			strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = "0";
			strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��
            sBuf = "2";
			strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����
			i++;
        }

		// �J�[�\�������ɃZ�b�g����
		Form3->Query1->Next();

	}

    // �ēx�������ڐ���ݒ肵�܂�
    iKSM13_DATA_SEL_Cnt = i;

    // �\�����Ń\�[�g���s�Ȃ��܂�
	for( i = 0; i < iKSM13_DATA_SEL_Cnt - 1; i++ ){
	   	for( k = i + 1; k < iKSM13_DATA_SEL_Cnt; k++ ) {
	        if( AnsiString(pKSM13_DATA_SEL[i].ORDER_NO).ToIntDef(0) > AnsiString(pKSM13_DATA_SEL[k].ORDER_NO).ToIntDef(0) ){

				strcpy( tmpKSM13_DATA.KOMK_NM	, pKSM13_DATA_SEL[i].KOMK_NM	);  // ���荀��
				strcpy( tmpKSM13_DATA.KIKI_NM	, pKSM13_DATA_SEL[i].KIKI_NM	);  // ����@�햼��
				strcpy( tmpKSM13_DATA.TANI		, pKSM13_DATA_SEL[i].TANI		);  // �P��
				strcpy( tmpKSM13_DATA.SOKU_SU	, pKSM13_DATA_SEL[i].SOKU_SU	);  // ����w��n��
				strcpy( tmpKSM13_DATA.DTKSHIN	, pKSM13_DATA_SEL[i].DTKSHIN	);	// ��\���Ӑ�i�ԁi�f�ތ����̐��i�K�i�}�X�^�[�����̎����p�j
				strcpy( tmpKSM13_DATA.KOMK_NO	, pKSM13_DATA_SEL[i].KOMK_NO	);	// ����NO
				strcpy( tmpKSM13_DATA.ORDER_NO	, pKSM13_DATA_SEL[i].ORDER_NO	);	// �\����
				strcpy( tmpKSM13_DATA.KOMK_ENG	, pKSM13_DATA_SEL[i].KOMK_ENG	);	// ���荀�ږ��́i�p��j
				strcpy( tmpKSM13_DATA.KIKI_NO	, pKSM13_DATA_SEL[i].KIKI_NO	);	// ����@��NO
				strcpy( tmpKSM13_DATA.KIKA_TYPE	, pKSM13_DATA_SEL[i].KIKA_TYPE	);	// �K�i�^�C�v
				strcpy( tmpKSM13_DATA.KIKA_KIND	, pKSM13_DATA_SEL[i].KIKA_KIND	);	// �K�i���
				strcpy( tmpKSM13_DATA.KIKA_DECI	, pKSM13_DATA_SEL[i].KIKA_DECI	);	// �K�i�����_�ȉ�����
				strcpy( tmpKSM13_DATA.KIKA_NUM1	, pKSM13_DATA_SEL[i].KIKA_NUM1	);	// �K�i�l�P
				strcpy( tmpKSM13_DATA.KIKA_NUM2	, pKSM13_DATA_SEL[i].KIKA_NUM2	);	// �K�i�l�Q
				strcpy( tmpKSM13_DATA.KIKA_NUM3	, pKSM13_DATA_SEL[i].KIKA_NUM3	);	// �K�i�l�R
				strcpy( tmpKSM13_DATA.KIKA_STR	, pKSM13_DATA_SEL[i].KIKA_STR	);	// �K�i�l����
				strcpy( tmpKSM13_DATA.SOKU_FLG	, pKSM13_DATA_SEL[i].SOKU_FLG	);	// ���荀�ڂ̗L��
				strcpy( tmpKSM13_DATA.TOKU_FLG	, pKSM13_DATA_SEL[i].TOKU_FLG	);	// ���ʍ��ڂ̗L��
				strcpy( tmpKSM13_DATA.KIKA_PRT	, pKSM13_DATA_SEL[i].KIKA_PRT	);	// ��������l�̈��
				strcpy( tmpKSM13_DATA.VALUE_TYPE, pKSM13_DATA_SEL[i].VALUE_TYPE	);	// ����l�\��
				strcpy( tmpKSM13_DATA.VALUE_DECI, pKSM13_DATA_SEL[i].VALUE_DECI	);	// ����l�����_�ȉ�����

				strcpy( pKSM13_DATA_SEL[i].KOMK_NM		, pKSM13_DATA_SEL[k].KOMK_NM	);  // ���荀��
				strcpy( pKSM13_DATA_SEL[i].KIKI_NM		, pKSM13_DATA_SEL[k].KIKI_NM	);  // ����@�햼��
				strcpy( pKSM13_DATA_SEL[i].TANI			, pKSM13_DATA_SEL[k].TANI		);  // �P��
				strcpy( pKSM13_DATA_SEL[i].SOKU_SU		, pKSM13_DATA_SEL[k].SOKU_SU	);  // ����w��n��
				strcpy( pKSM13_DATA_SEL[i].DTKSHIN		, pKSM13_DATA_SEL[k].DTKSHIN	);	// ��\���Ӑ�i�ԁi�f�ތ����̐��i�K�i�}�X�^�[�����̎����p�j
				strcpy( pKSM13_DATA_SEL[i].KOMK_NO		, pKSM13_DATA_SEL[k].KOMK_NO	);	// ����NO
				strcpy( pKSM13_DATA_SEL[i].ORDER_NO		, pKSM13_DATA_SEL[k].ORDER_NO	);	// �\����
				strcpy( pKSM13_DATA_SEL[i].KOMK_ENG		, pKSM13_DATA_SEL[k].KOMK_ENG	);	// ���荀�ږ��́i�p��j
				strcpy( pKSM13_DATA_SEL[i].KIKI_NO		, pKSM13_DATA_SEL[k].KIKI_NO	);	// ����@��NO
				strcpy( pKSM13_DATA_SEL[i].KIKA_TYPE	, pKSM13_DATA_SEL[k].KIKA_TYPE	);	// �K�i�^�C�v
				strcpy( pKSM13_DATA_SEL[i].KIKA_KIND	, pKSM13_DATA_SEL[k].KIKA_KIND	);	// �K�i���
				strcpy( pKSM13_DATA_SEL[i].KIKA_DECI	, pKSM13_DATA_SEL[k].KIKA_DECI	);	// �K�i�����_�ȉ�����
				strcpy( pKSM13_DATA_SEL[i].KIKA_NUM1	, pKSM13_DATA_SEL[k].KIKA_NUM1	);	// �K�i�l�P
				strcpy( pKSM13_DATA_SEL[i].KIKA_NUM2	, pKSM13_DATA_SEL[k].KIKA_NUM2	);	// �K�i�l�Q
				strcpy( pKSM13_DATA_SEL[i].KIKA_NUM3	, pKSM13_DATA_SEL[k].KIKA_NUM3	);	// �K�i�l�R
				strcpy( pKSM13_DATA_SEL[i].KIKA_STR		, pKSM13_DATA_SEL[k].KIKA_STR	);	// �K�i�l����
				strcpy( pKSM13_DATA_SEL[i].SOKU_FLG		, pKSM13_DATA_SEL[k].SOKU_FLG	);	// ���荀�ڂ̗L��
				strcpy( pKSM13_DATA_SEL[i].TOKU_FLG		, pKSM13_DATA_SEL[k].TOKU_FLG	);	// ���ʍ��ڂ̗L��
				strcpy( pKSM13_DATA_SEL[i].KIKA_PRT		, pKSM13_DATA_SEL[k].KIKA_PRT	);	// ��������l�̈��
				strcpy( pKSM13_DATA_SEL[i].VALUE_TYPE	, pKSM13_DATA_SEL[k].VALUE_TYPE	);	// ����l�\��
				strcpy( pKSM13_DATA_SEL[i].VALUE_DECI	, pKSM13_DATA_SEL[k].VALUE_DECI	);	// ����l�����_�ȉ�����

				strcpy( pKSM13_DATA_SEL[k].KOMK_NM		, tmpKSM13_DATA.KOMK_NM		);  // ���荀��
				strcpy( pKSM13_DATA_SEL[k].KIKI_NM		, tmpKSM13_DATA.KIKI_NM		);  // ����@�햼��
				strcpy( pKSM13_DATA_SEL[k].TANI			, tmpKSM13_DATA.TANI		);  // �P��
				strcpy( pKSM13_DATA_SEL[k].SOKU_SU		, tmpKSM13_DATA.SOKU_SU		);  // ����w��n��
				strcpy( pKSM13_DATA_SEL[k].DTKSHIN		, tmpKSM13_DATA.DTKSHIN		);	// ��\���Ӑ�i�ԁi�f�ތ����̐��i�K�i�}�X�^�[�����̎����p�j
				strcpy( pKSM13_DATA_SEL[k].KOMK_NO		, tmpKSM13_DATA.KOMK_NO		);	// ����NO
				strcpy( pKSM13_DATA_SEL[k].ORDER_NO		, tmpKSM13_DATA.ORDER_NO	);	// �\����
				strcpy( pKSM13_DATA_SEL[k].KOMK_ENG		, tmpKSM13_DATA.KOMK_ENG	);	// ���荀�ږ��́i�p��j
				strcpy( pKSM13_DATA_SEL[k].KIKI_NO		, tmpKSM13_DATA.KIKI_NO	 	);	// ����@��NO
				strcpy( pKSM13_DATA_SEL[k].KIKA_TYPE	, tmpKSM13_DATA.KIKA_TYPE	);	// �K�i�^�C�v
				strcpy( pKSM13_DATA_SEL[k].KIKA_KIND	, tmpKSM13_DATA.KIKA_KIND	);	// �K�i���
				strcpy( pKSM13_DATA_SEL[k].KIKA_DECI	, tmpKSM13_DATA.KIKA_DECI	);	// �K�i�����_�ȉ�����
				strcpy( pKSM13_DATA_SEL[k].KIKA_NUM1	, tmpKSM13_DATA.KIKA_NUM1	);	// �K�i�l�P
				strcpy( pKSM13_DATA_SEL[k].KIKA_NUM2	, tmpKSM13_DATA.KIKA_NUM2	);	// �K�i�l�Q
				strcpy( pKSM13_DATA_SEL[k].KIKA_NUM3	, tmpKSM13_DATA.KIKA_NUM3	);	// �K�i�l�R
				strcpy( pKSM13_DATA_SEL[k].KIKA_STR		, tmpKSM13_DATA.KIKA_STR	);	// �K�i�l����
				strcpy( pKSM13_DATA_SEL[k].SOKU_FLG		, tmpKSM13_DATA.SOKU_FLG	);	// ���荀�ڂ̗L��
				strcpy( pKSM13_DATA_SEL[k].TOKU_FLG		, tmpKSM13_DATA.TOKU_FLG	);	// ���ʍ��ڂ̗L��
				strcpy( pKSM13_DATA_SEL[k].KIKA_PRT		, tmpKSM13_DATA.KIKA_PRT	);	// ��������l�̈��
				strcpy( pKSM13_DATA_SEL[k].VALUE_TYPE	, tmpKSM13_DATA.VALUE_TYPE	);	// ����l�\��
				strcpy( pKSM13_DATA_SEL[k].VALUE_DECI	, tmpKSM13_DATA.VALUE_DECI	);	// ����l�����_�ȉ�����
            }
		}
    }


	// StringGrid�Ƀf�[�^��\�����܂��B
    for( i=1; i<=Form3->Lbx_DTKSHIN_SZ->Items->Count; i++ ) {
		if( i == 1 )	DispSGr_List(TabSheet1,1);
		if( i == 2 )	DispSGr_List(TabSheet2,1);
		if( i == 3 )	DispSGr_List(TabSheet3,1);
		if( i == 4 )	DispSGr_List(TabSheet4,1);
		if( i == 5 )	DispSGr_List(TabSheet5,1);
		if( i == 6 )	DispSGr_List(TabSheet6,1);
    }

    //�P�s�ڂ������I�����܂�
    SGr_ListSelectCell( SGr_List1, 1, 1, blnHoge);
    SGr_ListClick( SGr_List1 );


    //----------------------------------------------
    // �f�ޑ��荀�ڑS�}�X�^�[����

	// Initial Query
	Form3->Query1->Close();
	Form3->Query1->SQL->Clear();

	// �⍇�����s�i�f�ޑ��荀�ڃ}�X�^�[�j
	//sBuf = "SELECT * FROM KSM13 ORDER BY ORDER_NO";
	sBuf  = "SELECT KOMK_NO, ORDER_NO, KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG,";
    sBuf +=       " KIKI_NO, KIKI_NM, TANI, KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1,";
    sBuf +=       " KIKA_NUM2, KIKA_NUM3, KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3,";
    sBuf +=       " SOKU_SU, SOKU_FLG, TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI";
    sBuf += " FROM KSM13";
    sBuf += " ORDER BY ORDER_NO";

	Form3->Query1->SQL->Add(sBuf);
	Form3->Query1->Open();
	Form3->Query1->Active = true;

    if( !Form3->Query1->Eof ){

        // �������m�ې����擾
		iKSM13_DATA_ALL_Cnt = Form3->Query1->RecordCount;

    	// �������m��
    	hMemKSM13_DATA_ALL = GlobalAlloc( GHND, sizeof(struct KSM13_DATA) * iKSM13_DATA_ALL_Cnt );
    	if( hMemKSM13_DATA_ALL == NULL ){
        	Beep();
    		MessageDlg("�������̈���m�ۂł��܂���B(01)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        	return;
    	}
    	pKSM13_DATA_ALL = (struct KSM13_DATA *)GlobalLock(hMemKSM13_DATA_ALL);
    	if( hMemKSM13_DATA_ALL == NULL ){
        	Beep();
    		MessageDlg("�������̈���m�ۂł��܂���B(02)", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        	return;
	    }
    }

    i = 0;
	while( !Form3->Query1->Eof ){

		// �������Ƀf�[�^���Z�b�g���܂��B
		sBuf = "";
		strcpy( pKSM13_DATA_ALL[i].DTKSHIN		,sBuf.c_str() );	// ��\���Ӑ�i��

		sBuf = Form3->Query1->FieldValues["KOMK_NO"];
		strcpy( pKSM13_DATA_ALL[i].KOMK_NO		,sBuf.c_str() );	// ����NO

		sBuf = Form3->Query1->FieldValues["ORDER_NO"];
		strcpy( pKSM13_DATA_ALL[i].ORDER_NO		,sBuf.c_str() );	// �\����

        if( VarIsNull(Form3->Query1->FieldValues["KOMK_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KOMK_NM"];
		}
		strcpy( pKSM13_DATA_ALL[i].KOMK_NM		,sBuf.c_str() );	// ���荀�ځi���{��j

        if( VarIsNull(Form3->Query1->FieldValues["KOMK_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KOMK_ENG"];
        }
		strcpy( pKSM13_DATA_ALL[i].KOMK_ENG		,sBuf.c_str() );	// ���荀�ځi�p��j

		sBuf = Form3->Query1->FieldValues["KIKI_NO"];
		strcpy( pKSM13_DATA_ALL[i].KIKI_NO		,sBuf.c_str() );	// ����@��NO

        if( VarIsNull(Form3->Query1->FieldValues["KIKI_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KIKI_NM"];
        }
		strcpy( pKSM13_DATA_ALL[i].KIKI_NM		,sBuf.c_str() );	// ����@�햼��

        if( VarIsNull(Form3->Query1->FieldValues["TANI"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["TANI"];
        }
		strcpy( pKSM13_DATA_ALL[i].TANI		,sBuf.c_str() );		// �P��

		sBuf = Form3->Query1->FieldValues["KIKA_TYPE"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_TYPE	,sBuf.c_str() );	// �K�i�^�C�v

		sBuf = Form3->Query1->FieldValues["KIKA_KIND"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_KIND	,sBuf.c_str() );	// �K�i���

		sBuf = Form3->Query1->FieldValues["KIKA_DECI"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_DECI	,sBuf.c_str() );	// �K�i�����_�ȉ�����

		sBuf = Form3->Query1->FieldValues["KIKA_NUM1"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_NUM1	,sBuf.c_str() );	// �K�i�l�P

		sBuf = Form3->Query1->FieldValues["KIKA_NUM2"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_NUM2	,sBuf.c_str() );	// �K�i�l�Q

		sBuf = Form3->Query1->FieldValues["KIKA_NUM3"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_NUM3	,sBuf.c_str() );	// �K�i�l�R

        if( VarIsNull(Form3->Query1->FieldValues["KIKA_STR"]) ){
			sBuf = "";
		} else{
			sBuf = Form3->Query1->FieldValues["KIKA_STR"];
        }
		strcpy( pKSM13_DATA_ALL[i].KIKA_STR		,sBuf.c_str() );	// �K�i����

		sBuf = Form3->Query1->FieldValues["SOKU_SU"];
		strcpy( pKSM13_DATA_ALL[i].SOKU_SU		,sBuf.c_str() );	// ����w��n��

		sBuf = Form3->Query1->FieldValues["SOKU_FLG"];
		strcpy( pKSM13_DATA_ALL[i].SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��

		sBuf = Form3->Query1->FieldValues["TOKU_FLG"];
		strcpy( pKSM13_DATA_ALL[i].TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��

		sBuf = Form3->Query1->FieldValues["KIKA_PRT"];
		strcpy( pKSM13_DATA_ALL[i].KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��

		sBuf = Form3->Query1->FieldValues["VALUE_TYPE"];
		strcpy( pKSM13_DATA_ALL[i].VALUE_TYPE	,sBuf.c_str() );	// �l�\��

		sBuf = Form3->Query1->FieldValues["VALUE_DECI"];
		strcpy( pKSM13_DATA_ALL[i].VALUE_DECI	,sBuf.c_str() );	// ����l�����_�ȉ�����

		// �J�[�\�������ɃZ�b�g����
		Form3->Query1->Next();

		i += 1;
	}

    // 2003/10/23 A.Tamura �T�u���̂������ݒ肷�鏈����ǉ����܂�
    SetSubName(PgCtr_List->ActivePage->Caption);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCloseQuery�C�x���g�FClose ���\�b�h���Ăяo���ꂽ�Ƃ��܂��̓��[�U�[��
//          �t�H�[���̃V�X�e�����j���[�Łm����n��I�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �������̊J�����s�Ȃ��܂��B
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
    // �������̊J��
    if( hMemKSM13_DATA_SEL ){
        GlobalUnlock( hMemKSM13_DATA_SEL );
        GlobalFree( hMemKSM13_DATA_SEL );
    }
    if( hMemKSM13_DATA_ALL ){
        GlobalUnlock( hMemKSM13_DATA_ALL );
        GlobalFree( hMemKSM13_DATA_ALL );
    }

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

    if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
		if(SGr_List1->Row > 1){
			SGr_List1->Row -= 1;
			SGr_List1->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
		if(SGr_List2->Row > 1){
			SGr_List2->Row -= 1;
			SGr_List2->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
		if(SGr_List3->Row > 1){
			SGr_List3->Row -= 1;
			SGr_List3->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
		if(SGr_List4->Row > 1){
			SGr_List4->Row -= 1;
			SGr_List4->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
		if(SGr_List5->Row > 1){
			SGr_List5->Row -= 1;
			SGr_List5->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
		if(SGr_List6->Row > 1){
			SGr_List6->Row -= 1;
			SGr_List6->SetFocus();
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
void __fastcall TForm5::BtnF03Click(TObject *Sender)
{

    if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
		if( (SGr_List1->RowCount-1) > SGr_List1->Row ){
			SGr_List1->Row += 1;
			SGr_List1->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
		if( (SGr_List2->RowCount-1) > SGr_List2->Row ){
			SGr_List2->Row += 1;
			SGr_List2->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
		if( (SGr_List3->RowCount-1) > SGr_List3->Row ){
			SGr_List3->Row += 1;
			SGr_List3->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
		if( (SGr_List4->RowCount-1) > SGr_List4->Row ){
			SGr_List4->Row += 1;
			SGr_List4->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
		if( (SGr_List5->RowCount-1) > SGr_List5->Row ){
			SGr_List5->Row += 1;
			SGr_List5->SetFocus();
		}
    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
		if( (SGr_List6->RowCount-1) > SGr_List6->Row ){
			SGr_List6->Row += 1;
			SGr_List6->SetFocus();
		}
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�W�F�ǉ��^�e�X�F�}���v�{�^�������������̏���
//
//  �@�\����
//    �����I�������ꍇ�́A�I�������s�����C���t�H�[���̑��荀��Grid�ɒǉ����͑}�����܂��B
//    1�I���̏ꍇ�́A��ʉ��̍��ړ��e�����C���t�H�[���̑��荀��Grid�ɒǉ����͑}�����܂��B
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
void __fastcall TForm5::BtnF08F09Click(TObject *Sender)
{

    int				i;
    int				iSKB_NO;
    AnsiString		sDTKSHIN;
    AnsiString		sBuf;
    TButton*		bt = dynamic_cast<TButton*>(Sender);
    TStringGrid*	sg;


    iSKB_NO = 1;
	if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
    	sDTKSHIN = TabSheet1->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List1);
    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
    	sDTKSHIN = TabSheet2->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List2);
    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
    	sDTKSHIN = TabSheet3->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List3);
    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
    	sDTKSHIN = TabSheet4->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List4);
    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
    	sDTKSHIN = TabSheet5->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List5);
    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
    	sDTKSHIN = TabSheet6->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List6);
    }

    if( iRowSelTop != iRowSelBottom ){
        // �����I���̎��́AStringGrid�̃f�[�^��ǉ��^�}�����܂�
    	for( i=iRowSelTop; i<=iRowSelBottom; i++ ) {
            if( sg->Cells[0][i].Trim() == "" ) continue;

            sBuf = Form3->Edt_DTKSHIN->Text;
			strcpy( Form3->tmpKSM02_DATA.DTKSHIN		,sBuf.c_str() );	// ��\���Ӑ�i��
            sBuf = "0";
			strcpy( Form3->tmpKSM02_DATA.REVCNT			,sBuf.c_str() );	// �����ԍ�
            //sBuf = iSOKUT_UNQ_NO_MAX++ ;
			//strcpy( Form3->tmpKSM02_DATA.UNQ_NO		,sBuf.c_str() );	// ����NO
            //sBuf = iSOKUT_ORDER_NO_MAX++ ;
			//strcpy( Form3->tmpKSM02_DATA.ORDER_NO		,sBuf.c_str() );	// �\����
            sBuf = iSKB_NO;
			strcpy( Form3->tmpKSM02_DATA.SKB_NO			,sBuf.c_str() );	// ����NO
            sBuf = sDTKSHIN;
			strcpy( Form3->tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// �i��
			sBuf = sg->Cells[7][i];
			strcpy( Form3->tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// ����NO
			sBuf = sg->Cells[1][i];
			strcpy( Form3->tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
			sBuf = sg->Cells[9][i];
			strcpy( Form3->tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
			sBuf = Edt_SKTKMK_JPN_SUB->Text;
			strcpy( Form3->tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// ���荀�ڃT�u���́i���{��j
			sBuf = Edt_SKTKMK_ENG_SUB->Text;
			strcpy( Form3->tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// ���荀�ڃT�u���́i�p��j
			sBuf = sg->Cells[10][i];
			strcpy( Form3->tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// ����@��NO
			sBuf = sg->Cells[2][i];
			strcpy( Form3->tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// ����@�햼��
			sBuf = sg->Cells[3][i];
			strcpy( Form3->tmpKSM02_DATA.TANI			,sBuf.c_str() );	// �P��
			sBuf = sg->Cells[11][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// �K�i�^�C�v
			sBuf = sg->Cells[12][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// �K�i���
			sBuf = sg->Cells[13][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// �K�i�����_�ȉ�����
			sBuf = sg->Cells[14][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// �K�i�l�P
			sBuf = sg->Cells[15][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// �K�i�l�Q
			sBuf = sg->Cells[16][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// �K�i�l�R
			sBuf = sg->Cells[17][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// �K�i�l����
			sBuf = sg->Cells[5][i];
			strcpy( Form3->tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// ����w��n��
			sBuf = sg->Cells[18][i];
			strcpy( Form3->tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
			sBuf = sg->Cells[19][i];
			strcpy( Form3->tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
			sBuf = sg->Cells[20][i];
			strcpy( Form3->tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
			sBuf = sg->Cells[21][i];
			strcpy( Form3->tmpKSM02_DATA.VALUE_TYPE		,sBuf.c_str() );	// ����l�\��
			sBuf = sg->Cells[22][i];
			strcpy( Form3->tmpKSM02_DATA.VALUE_DECI		,sBuf.c_str() );	// ����l�����_�ȉ�����

            // ����f�[�^��ǉ��^�}�����܂�
            if( bt->Name == "BtnF08" ){
                // �u�e�W�F�ǉ��v
                Form3->Ins_SGr_SOKUT(Form3->SGr_SOKUT->RowCount-1);
            }
            else {
                // �u�e�X�F�}���v
                Form3->Ins_SGr_SOKUT(Form3->SGr_SOKUT->Row);
            	if( i != iRowSelBottom )	Form3->SGr_SOKUT->Row = Form3->SGr_SOKUT->Row + 1;
            }
    	}

    }
    else {
        // ��s�I���̎��́A��ʉ����̃f�[�^��ǉ��^�}�����܂�

        // ���̓f�[�^�̃`�F�b�N
        if(Edt_SKTKMK_JPN->Text.IsEmpty()){
            MessageDlg("���荀�ږ�����͂��Ă��������B", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
            Edt_SKTKMK_JPN->SetFocus();
            return;
        }
        if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
            if( (Rdo_KIKAKU_SYURUI_MINMAX->Checked &&
                (Nmb_KIKAKU_HANI_MIN->Text.ToIntDef(0) >
                 Nmb_KIKAKU_HANI_MAX->Text.ToIntDef(0) )) ){
                MessageDlg("�K�i�͈͎̔w�肪����������܂���B", mtWarning
                                  ,TMsgDlgButtons() << mbOK, 0);
                Nmb_KIKAKU_HANI_MIN->SetFocus();
                return;
            }
        }

        sBuf = Form3->Edt_DTKSHIN->Text;
		strcpy( Form3->tmpKSM02_DATA.DTKSHIN		,sBuf.c_str() );	// ��\���Ӑ�i��
        sBuf = "0";
		strcpy( Form3->tmpKSM02_DATA.REVCNT			,sBuf.c_str() );	// �����ԍ�
        //sBuf = iSOKUT_UNQ_NO_MAX++ ;
		//strcpy( Form3->tmpKSM02_DATA.UNQ_NO		,sBuf.c_str() );	// ����NO
        //sBuf = iSOKUT_ORDER_NO_MAX++ ;
		//strcpy( Form3->tmpKSM02_DATA.ORDER_NO		,sBuf.c_str() );	// �\����
        sBuf = iSKB_NO;
		strcpy( Form3->tmpKSM02_DATA.SKB_NO			,sBuf.c_str() );	// ����NO
        sBuf = sDTKSHIN;
		strcpy( Form3->tmpKSM02_DATA.HINBAN_SK		,sBuf.c_str() );	// �i��
		sBuf = Edt_SKTKMK_JPN->Tag;
		strcpy( Form3->tmpKSM02_DATA.KOMK_NO		,sBuf.c_str() );	// ����NO
		sBuf = Edt_SKTKMK_JPN->Text;
		strcpy( Form3->tmpKSM02_DATA.KOMK_NM		,sBuf.c_str() );	// ���荀�ږ��́i���{��j
		sBuf = Edt_SKTKMK_ENG->Text;
		strcpy( Form3->tmpKSM02_DATA.KOMK_ENG		,sBuf.c_str() );	// ���荀�ږ��́i�p��j
		sBuf = Edt_SKTKMK_JPN_SUB->Text;
		strcpy( Form3->tmpKSM02_DATA.KOMK_SUB		,sBuf.c_str() );	// ���荀�ڃT�u���́i���{��j
		sBuf = Edt_SKTKMK_ENG_SUB->Text;
		strcpy( Form3->tmpKSM02_DATA.KOMK_SUB_ENG	,sBuf.c_str() );	// ���荀�ڃT�u���́i�p��j
		sBuf = IntToStr(Form3->iKIKI[Cmb_SKTKIKI->ItemIndex]);
		strcpy( Form3->tmpKSM02_DATA.KIKI_NO		,sBuf.c_str() );	// ����@��NO
		sBuf = Cmb_SKTKIKI->Text;
		strcpy( Form3->tmpKSM02_DATA.KIKI_NM		,sBuf.c_str() );	// ����@�햼��
		sBuf = Cmb_TANI->Text;
		strcpy( Form3->tmpKSM02_DATA.TANI			,sBuf.c_str() );	// �P��

        if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
			sBuf = Nmb_KIKAKU_HANI_MIN->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// �K�i�l�P
			sBuf = Nmb_KIKAKU_HANI_MAX->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// �K�i�l�Q
			sBuf = "0";
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( Form3->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// �K�i�l����
			sBuf = "1";
        } else if( Rdo_KIKAKU_SHITEI_KIJYUN->Checked ) {
			sBuf = Nmb_KIKAKU_KIJYUN_MID->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// �K�i�l�P
			sBuf = Nmb_KIKAKU_KIJYUN_MAX->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// �K�i�l�Q
			sBuf = Nmb_KIKAKU_KIJYUN_MIN->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// �K�i�l�R
			sBuf = "";
			strcpy( Form3->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// �K�i�l����
			sBuf = "2";
		} else {
			sBuf = "0";
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM1		,sBuf.c_str() );	// �K�i�l�P
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM2		,sBuf.c_str() );	// �K�i�l�Q
			strcpy( Form3->tmpKSM02_DATA.KIKA_NUM3		,sBuf.c_str() );	// �K�i�l�R
			sBuf = Edt_KIKAKU_STRING->Text;
			strcpy( Form3->tmpKSM02_DATA.KIKA_STR		,sBuf.c_str() );	// �K�i�l����
			sBuf = "3";
        }
		strcpy( Form3->tmpKSM02_DATA.KIKA_TYPE		,sBuf.c_str() );	// �K�i�^�C�v
        if( Rdo_KIKAKU_SYURUI_MINMAX->Checked )			sBuf = "1";
		else if( Rdo_KIKAKU_SYURUI_MAX->Checked )		sBuf = "2";
        else											sBuf = "3";
        strcpy( Form3->tmpKSM02_DATA.KIKA_KIND		,sBuf.c_str() );	// �K�i���
        sBuf = Nmb_KIKAKU_DOUBLE->Text;
		strcpy( Form3->tmpKSM02_DATA.KIKA_DECI		,sBuf.c_str() );	// �K�i�����_�ȉ�����
        sBuf = Nmb_N->Text;
		strcpy( Form3->tmpKSM02_DATA.SOKU_SU		,sBuf.c_str() );	// ����w��n��
        if( Rdo_SKTKMK_ON->Checked )			sBuf = "1";
		else									sBuf = "0";
		strcpy( Form3->tmpKSM02_DATA.SOKU_FLG		,sBuf.c_str() );	// ���荀�ڂ̗L��
		if( Rdo_TKBKMK_ON->Checked )			sBuf = "1";
		else									sBuf = "0";
		strcpy( Form3->tmpKSM02_DATA.TOKU_FLG		,sBuf.c_str() );	// ���ʍ��ڂ̗L��
		if( Rdo_MANMIN_PRT_ON->Checked )		sBuf = "1";
		else									sBuf = "0";
		strcpy( Form3->tmpKSM02_DATA.KIKA_PRT		,sBuf.c_str() );	// ��������l�̈��
		if( Rdo_VALUE_NORMAL->Checked )			sBuf = "0";
		else if( Rdo_VALUE_KAKUDO->Checked )	sBuf = "1";
		else if( Rdo_VALUE_OK->Checked )		sBuf = "2";
		else									sBuf = "3";
		strcpy( Form3->tmpKSM02_DATA.VALUE_TYPE		,sBuf.c_str() );	// ����l�\��
		sBuf = Nmb_VALUE_DOUBLE->Text;
		strcpy( Form3->tmpKSM02_DATA.VALUE_DECI		,sBuf.c_str() );	// ����l�����_�ȉ�����

        // ����f�[�^��ǉ��^�}�����܂�
        if( bt->Name == "BtnF08" ){
            // �u�e�W�F�ǉ��v
            Form3->Ins_SGr_SOKUT(Form3->SGr_SOKUT->RowCount-1);
        }
        else {
            // �u�e�X�F�}���v
            Form3->Ins_SGr_SOKUT(Form3->SGr_SOKUT->Row);
        }
    }

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
         case VK_F2:  BtnF02Click(BtnF02);		break;
         case VK_F3:  BtnF03Click(BtnF03);		break;
         case VK_F8:  BtnF08F09Click(BtnF08);	break;
         case VK_F9:  BtnF08F09Click(BtnF09);	break;
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
void __fastcall TForm5::Pnl_ListResize(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SHITEI_HANIClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SHITEI_KIJYUNClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SHITEI_MOJIClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SYURUI_MINMAXClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SYURUI_MAXClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_KIKAKU_SYURUI_MINClick(TObject *Sender)
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
//    OnChange�C�x���g	�F�V�����^�u���I�������Ɣ������܂��B
//
//  �@�\����
//    �y�[�W�R���g���[���ɂ��^�u�̐ؑ�
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
void __fastcall TForm5::PgCtr_ListChange(TObject *Sender)
{
    bool blnHoge=true;
	TPageControl *pPC = (TPageControl *)Sender;

	Pnl_HINBAN->Caption = pPC->ActivePage->Caption;

    // 2003/10/23 A.Tamura �T�u���̂������ݒ肷�鏈����ǉ����܂�
    SetSubName(pPC->ActivePage->Caption);

    if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
		if( Rdo_SOZAI_SELECT1->Checked == true ){
			DispSGr_List(TabSheet1,1);
		} else {
			DispSGr_List(TabSheet1,2);
		}
    	SGr_ListSelectCell( SGr_List1, 1, SGr_List1->Row, blnHoge);
	    SGr_ListClick( SGr_List1 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
		if( Rdo_SOZAI_SELECT2->Checked == true ){
			DispSGr_List(TabSheet2,1);
		} else {
			DispSGr_List(TabSheet2,2);
		}
    	SGr_ListSelectCell( SGr_List2, 1, SGr_List2->Row, blnHoge);
	    SGr_ListClick( SGr_List2 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
		if( Rdo_SOZAI_SELECT3->Checked == true ){
			DispSGr_List(TabSheet3,1);
		} else {
			DispSGr_List(TabSheet3,2);
		}
    	SGr_ListSelectCell( SGr_List3, 1, SGr_List3->Row, blnHoge);
	    SGr_ListClick( SGr_List3 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
		if( Rdo_SOZAI_SELECT4->Checked == true ){
			DispSGr_List(TabSheet4,1);
		} else {
			DispSGr_List(TabSheet4,2);
		}
    	SGr_ListSelectCell( SGr_List4, 1, SGr_List4->Row, blnHoge);
	    SGr_ListClick( SGr_List4 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
		if( Rdo_SOZAI_SELECT5->Checked == true ){
			DispSGr_List(TabSheet5,1);
		} else {
			DispSGr_List(TabSheet5,2);
		}
    	SGr_ListSelectCell( SGr_List5, 1, SGr_List5->Row, blnHoge);
	    SGr_ListClick( SGr_List5 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
		if( Rdo_SOZAI_SELECT6->Checked == true ){
			DispSGr_List(TabSheet6,1);
		} else {
			DispSGr_List(TabSheet6,2);
		}
    	SGr_ListSelectCell( SGr_List6, 1, SGr_List6->Row, blnHoge);
	    SGr_ListClick( SGr_List6 );

    }

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
void __fastcall TForm5::Rdo_VALUE_NORMALClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_VALUE_KAKUDOClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_VALUE_OKClick(TObject *Sender)
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
void __fastcall TForm5::Rdo_VALUE_TEXTClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled     = false;
    Nmb_VALUE_DOUBLE->Font->Color = clGray;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�w�肳�ꂽTabSheet�̃O���b�h�ɊY���f�[�^��\��
//
//  �@�\����
//    �w�肳�ꂽTabSheet�̃O���b�h�ɊY���f�[�^��\��(StringGrid)���܂�
//
//  �p�����^����
//    TTabSheet *ts		�F�Ώۂ�TabSheet
//    int	type		�F1 = �f�ތ����̐��i�K�i�}�X�^�[�Ŏw�肳��Ă��鑪�荀�ڂ���I��
//                        2 = �f�ތ����̑��荀�ڈꗗ����I��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm5::DispSGr_List(TTabSheet *ts, int	type)
{

    int             i;
    int				iDATA_Cnt;
    int				iRow;
    AnsiString		sDTKSHIN;
    AnsiString		sBuf;
    TStringGrid*	sg;


    // FormActive���͏������~
    if( Form5->Tag == 1 ) return;


    // �\������StringGrid���擾���܂�
	if( ts->Name == "TabSheet1" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List1);
    } else if( ts->Name == "TabSheet2" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List2);
    } else if( ts->Name == "TabSheet3" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List3);
    } else if( ts->Name == "TabSheet4" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List4);
    } else if( ts->Name == "TabSheet5" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List5);
    } else if( ts->Name == "TabSheet6" ){
    	sDTKSHIN = ts->Caption;
    	sg = dynamic_cast<TStringGrid*>(SGr_List6);
    }

    if( type == 1 ){
        // �f�ތ����̐��i�K�i�}�X�^�[�Ŏw�肳��Ă��鑪�荀�ڂ���I��
    	iDATA_Cnt = iKSM13_DATA_SEL_Cnt;
    } else {
		// �f�ތ����̑��荀�ڈꗗ����I��
    	iDATA_Cnt = iKSM13_DATA_ALL_Cnt;
    }

    // �f�[�^�̕\��
	iRow = 1;
	for( i=0; i<iDATA_Cnt; i++ ){

    	if( type == 1 ){
        	// �f�ތ����̐��i�K�i�}�X�^�[�Ŏw�肳��Ă��鑪�荀�ڂ���I��
			// �G���[�@memcpy( (char *)tmpKSM13_DATA, (char *)pKSM13_DATA_SEL[i], sizeof(tmpKSM13_DATA) );
			strcpy( tmpKSM13_DATA.KOMK_NM	, pKSM13_DATA_SEL[i].KOMK_NM	);  // ���荀��
			strcpy( tmpKSM13_DATA.KIKI_NM	, pKSM13_DATA_SEL[i].KIKI_NM	);  // ����@�햼��
			strcpy( tmpKSM13_DATA.TANI		, pKSM13_DATA_SEL[i].TANI		);  // �P��
			strcpy( tmpKSM13_DATA.SOKU_SU	, pKSM13_DATA_SEL[i].SOKU_SU	);  // ����w��n��
			strcpy( tmpKSM13_DATA.DTKSHIN	, pKSM13_DATA_SEL[i].DTKSHIN	);	// ��\���Ӑ�i�ԁi�f�ތ����̐��i�K�i�}�X�^�[�����̎����p�j
			strcpy( tmpKSM13_DATA.KOMK_NO	, pKSM13_DATA_SEL[i].KOMK_NO	);	// ����NO
			strcpy( tmpKSM13_DATA.ORDER_NO	, pKSM13_DATA_SEL[i].ORDER_NO	);	// �\����
			strcpy( tmpKSM13_DATA.KOMK_ENG	, pKSM13_DATA_SEL[i].KOMK_ENG	);	// ���荀�ږ��́i�p��j
			strcpy( tmpKSM13_DATA.KIKI_NO	, pKSM13_DATA_SEL[i].KIKI_NO	);	// ����@��NO
			strcpy( tmpKSM13_DATA.KIKA_TYPE	, pKSM13_DATA_SEL[i].KIKA_TYPE	);	// �K�i�^�C�v
			strcpy( tmpKSM13_DATA.KIKA_KIND	, pKSM13_DATA_SEL[i].KIKA_KIND	);	// �K�i���
			strcpy( tmpKSM13_DATA.KIKA_DECI	, pKSM13_DATA_SEL[i].KIKA_DECI	);	// �K�i�����_�ȉ�����
			strcpy( tmpKSM13_DATA.KIKA_NUM1	, pKSM13_DATA_SEL[i].KIKA_NUM1	);	// �K�i�l�P
			strcpy( tmpKSM13_DATA.KIKA_NUM2	, pKSM13_DATA_SEL[i].KIKA_NUM2	);	// �K�i�l�Q
			strcpy( tmpKSM13_DATA.KIKA_NUM3	, pKSM13_DATA_SEL[i].KIKA_NUM3	);	// �K�i�l�R
			strcpy( tmpKSM13_DATA.KIKA_STR	, pKSM13_DATA_SEL[i].KIKA_STR	);	// �K�i�l����
			strcpy( tmpKSM13_DATA.SOKU_FLG	, pKSM13_DATA_SEL[i].SOKU_FLG	);	// ���荀�ڂ̗L��
			strcpy( tmpKSM13_DATA.TOKU_FLG	, pKSM13_DATA_SEL[i].TOKU_FLG	);	// ���ʍ��ڂ̗L��
			strcpy( tmpKSM13_DATA.KIKA_PRT	, pKSM13_DATA_SEL[i].KIKA_PRT	);	// ��������l�̈��
			strcpy( tmpKSM13_DATA.VALUE_TYPE, pKSM13_DATA_SEL[i].VALUE_TYPE	);	// ����l�\��
			strcpy( tmpKSM13_DATA.VALUE_DECI, pKSM13_DATA_SEL[i].VALUE_DECI	);	// ����l�����_�ȉ�����
    	} else {
			// �f�ތ����̑��荀�ڈꗗ����I��
			// �G���[�@memcpy( (char *)tmpKSM13_DATA, (char *)pKSM13_DATA_ALL[i], sizeof(tmpKSM13_DATA) );
			strcpy( tmpKSM13_DATA.KOMK_NM	, pKSM13_DATA_ALL[i].KOMK_NM	);  // ���荀��
			strcpy( tmpKSM13_DATA.KIKI_NM	, pKSM13_DATA_ALL[i].KIKI_NM	);  // ����@�햼��
			strcpy( tmpKSM13_DATA.TANI		, pKSM13_DATA_ALL[i].TANI		);  // �P��
			strcpy( tmpKSM13_DATA.SOKU_SU	, pKSM13_DATA_ALL[i].SOKU_SU	);  // ����w��n��
			strcpy( tmpKSM13_DATA.DTKSHIN	, pKSM13_DATA_ALL[i].DTKSHIN	);	// ��\���Ӑ�i�ԁi�f�ތ����̐��i�K�i�}�X�^�[�����̎����p�j
			strcpy( tmpKSM13_DATA.KOMK_NO	, pKSM13_DATA_ALL[i].KOMK_NO	);	// ����NO
			strcpy( tmpKSM13_DATA.ORDER_NO	, pKSM13_DATA_ALL[i].ORDER_NO	);	// �\����
			strcpy( tmpKSM13_DATA.KOMK_ENG	, pKSM13_DATA_ALL[i].KOMK_ENG	);	// ���荀�ږ��́i�p��j
			strcpy( tmpKSM13_DATA.KIKI_NO	, pKSM13_DATA_ALL[i].KIKI_NO	);	// ����@��NO
			strcpy( tmpKSM13_DATA.KIKA_TYPE	, pKSM13_DATA_ALL[i].KIKA_TYPE	);	// �K�i�^�C�v
			strcpy( tmpKSM13_DATA.KIKA_KIND	, pKSM13_DATA_ALL[i].KIKA_KIND	);	// �K�i���
			strcpy( tmpKSM13_DATA.KIKA_DECI	, pKSM13_DATA_ALL[i].KIKA_DECI	);	// �K�i�����_�ȉ�����
			strcpy( tmpKSM13_DATA.KIKA_NUM1	, pKSM13_DATA_ALL[i].KIKA_NUM1	);	// �K�i�l�P
			strcpy( tmpKSM13_DATA.KIKA_NUM2	, pKSM13_DATA_ALL[i].KIKA_NUM2	);	// �K�i�l�Q
			strcpy( tmpKSM13_DATA.KIKA_NUM3	, pKSM13_DATA_ALL[i].KIKA_NUM3	);	// �K�i�l�R
			strcpy( tmpKSM13_DATA.KIKA_STR	, pKSM13_DATA_ALL[i].KIKA_STR	);	// �K�i�l����
			strcpy( tmpKSM13_DATA.SOKU_FLG	, pKSM13_DATA_ALL[i].SOKU_FLG	);	// ���荀�ڂ̗L��
			strcpy( tmpKSM13_DATA.TOKU_FLG	, pKSM13_DATA_ALL[i].TOKU_FLG	);	// ���ʍ��ڂ̗L��
			strcpy( tmpKSM13_DATA.KIKA_PRT	, pKSM13_DATA_ALL[i].KIKA_PRT	);	// ��������l�̈��
			strcpy( tmpKSM13_DATA.VALUE_TYPE, pKSM13_DATA_ALL[i].VALUE_TYPE	);	// ����l�\��
			strcpy( tmpKSM13_DATA.VALUE_DECI, pKSM13_DATA_ALL[i].VALUE_DECI	);	// ����l�����_�ȉ�����
    	}

        // �s�v�ȃf�[�^��Skip���܂�
    	if( type == 1 ){
            if( sDTKSHIN != AnsiString(tmpKSM13_DATA.DTKSHIN) )	continue;
        }

    	// �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
		if( iRow >= sg->RowCount ){
			sg->RowCount = iRow + 1;
		}

		// �O���b�h�Ƀf�[�^���Z�b�g���܂��B
		sBuf = iRow ;
		sg->Cells[0][iRow] = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;    //No
        sg->Cells[1][iRow] = tmpKSM13_DATA.KOMK_NM		;   // ���荀��
		sg->Cells[2][iRow] = tmpKSM13_DATA.KIKI_NM		;   // ����@�햼��
		sg->Cells[3][iRow] = tmpKSM13_DATA.TANI			;   // �P��
		sg->Cells[4][iRow] = ""							;   // �K�i�@���ĕ`�悷��ׂɕK�v�ł��B
		sg->Cells[5][iRow] = tmpKSM13_DATA.SOKU_SU		;   // ����w��n��
		sg->Cells[6][iRow] = tmpKSM13_DATA.DTKSHIN		;	// ��\���Ӑ�i�ԁi�f�ތ����̐��i�K�i�}�X�^�[�����̎����p�j
		sg->Cells[7][iRow] = tmpKSM13_DATA.KOMK_NO		;	// ����NO
		sg->Cells[8][iRow] = tmpKSM13_DATA.ORDER_NO		;	// �\����
		sg->Cells[9][iRow] = tmpKSM13_DATA.KOMK_ENG		;	// ���荀�ږ��́i�p��j
		sg->Cells[10][iRow] = tmpKSM13_DATA.KIKI_NO		;	// ����@��NO
		sg->Cells[11][iRow] = tmpKSM13_DATA.KIKA_TYPE	;	// �K�i�^�C�v
		sg->Cells[12][iRow] = tmpKSM13_DATA.KIKA_KIND	;	// �K�i���
		sg->Cells[13][iRow] = tmpKSM13_DATA.KIKA_DECI	;	// �K�i�����_�ȉ�����
		sg->Cells[14][iRow] = tmpKSM13_DATA.KIKA_NUM1	;	// �K�i�l�P
		sg->Cells[15][iRow] = tmpKSM13_DATA.KIKA_NUM2	;	// �K�i�l�Q
		sg->Cells[16][iRow] = tmpKSM13_DATA.KIKA_NUM3	;	// �K�i�l�R
		sg->Cells[17][iRow] = tmpKSM13_DATA.KIKA_STR	;	// �K�i�l����
		sg->Cells[18][iRow] = tmpKSM13_DATA.SOKU_FLG	;	// ���荀�ڂ̗L��
		sg->Cells[19][iRow] = tmpKSM13_DATA.TOKU_FLG	;	// ���ʍ��ڂ̗L��
		sg->Cells[20][iRow] = tmpKSM13_DATA.KIKA_PRT	;	// ��������l�̈��
		sg->Cells[21][iRow] = tmpKSM13_DATA.VALUE_TYPE	;	// ����l�\��
		sg->Cells[22][iRow] = tmpKSM13_DATA.VALUE_DECI	;	// ����l�����_�ȉ�����

		iRow++;
    }

    // �Ō�̍s�͋󔒍s�Ƃ��܂�
    sg->RowCount = iRow + 1;
	for( i=0; i<sg->ColCount; i++ ){
		sg->Cells[i][iRow] = "";
	}

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
void __fastcall TForm5::SGr_ListClick(TObject *Sender)
{
    TStringGrid* sg = dynamic_cast<TStringGrid*>(Sender);

   	iRowSelTop    = sg->Selection.Top;
   	iRowSelBottom = sg->Selection.Bottom;

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
void __fastcall TForm5::SGr_ListDrawCell(TObject *Sender, int ACol,
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
//   else if(State.Contains(gdFocused))
//       SGr1->Canvas->Brush->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlight: SGr1->Color;
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

       sg->Canvas->Font->Color= clHighlightText;
   }
   //�I������Ă���Z���̕����F���Z�b�g
   else if(State.Contains(gdSelected))
       sg->Canvas->Font->Color= clHighlightText;
   //���ʂ̃Z���̕����F���Z�b�g
   else
       sg->Canvas->Font->Color= sg->Font->Color;

   //�e�L�X�g�\���̈�̐ݒ�
   InflateRect(&r,-2,-2);

   if( ARow > 0 && ACol == 4 ){

        // �K�i�^�C�v���̕\��
        switch( sg->Cells[11][ARow].ToIntDef(0) ){
            case 1: // �͈͎w��

                    // �����_�ȉ������̃t�H�[�}�b�g������
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",sg->Cells[13][ARow].ToIntDef(0) );
            		strcat(c1,c2);

			        switch( sg->Cells[12][ARow].ToIntDef(0) ){
            			case 1: // �����������
                                sValue = sg->Cells[14][ARow];
                                //2003.05.08 E.Takase Add��
			                    sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			        			//2003.05.08 E.Takase Add �R�����g��
			                    //sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
                     			sBuf = cFormatBuf;
                     			sBuf +=  "�`";
                                sValue = sg->Cells[15][ARow];
                                //2003.05.08 E.Takase Add��
                     			sprintf(cFormatBuf, c1,  Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			        			//2003.05.08 E.Takase Add �R�����g��
                     			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
                     			sBuf += cFormatBuf ;
			            		break;

            			case 2: // ����̂�
                                sValue = sg->Cells[15][ARow];
                                //2003.05.08 E.Takase Add��
                     			sprintf(cFormatBuf, c1,  Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			        			//2003.05.08 E.Takase Add �R�����g��
                     			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
                     			sBuf = cFormatBuf ;
                     			sBuf += "�ȉ�";
			            		break;
            			case 3: // �����̂�
                                sValue = sg->Cells[14][ARow];
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
					DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //����
            		break;

            case 2: // ��l�w��

                    // �����_�ȉ������̃t�H�[�}�b�g������
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",sg->Cells[13][ARow].ToIntDef(0) );
            		strcat(c1,c2);

                    sValue = sg->Cells[14][ARow];
                    //2003.05.08 E.Takase Add��
                    sprintf(cFormatBuf, c1,  Form1->ConvDoubleDefD(sValue,0.0) );
                    //2003.05.08 E.Takase Add��
			        //2003.05.08 E.Takase Add �R�����g��
                    //sprintf(cFormatBuf, c1, sValue.ToDouble() );
                    //2003.05.08 E.Takase Add �R�����g��
                    sBuf = cFormatBuf ;
        			sg->Canvas->TextOut( r.left +  0, r.top + 0, sBuf );
                    iPos = sBuf.Length() * 8;

        			// �t�H���g�i���j�̐ݒ�
        			Form3->OrgFont = SelectObject( sg->Canvas->Handle, Form3->MyFont );

			        switch( sg->Cells[12][ARow].ToIntDef(0) ){
            			case 1: // �����������
                    			sValue = sg->Cells[15][ARow];
                                //2003.05.08 E.Takase Add��
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			        			//2003.05.08 E.Takase Add �R�����g��
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                               	//2003.05.08 E.Takase Add �R�����g��
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
                                sg->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
                     			sValue = sg->Cells[16][ARow];
                                //2003.05.08 E.Takase Add��
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			        			//2003.05.08 E.Takase Add �R�����g��
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						sg->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;

            			case 2: // ����̂�
			                    sValue = sg->Cells[15][ARow];
                                //2003.05.08 E.Takase Add��
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			        			//2003.05.08 E.Takase Add �R�����g��
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
			        			sg->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
			            		break;
            			case 3: // �����̂�
                     			sValue = sg->Cells[16][ARow];
                                //2003.05.08 E.Takase Add��
                    			sprintf(cFormatBuf, c1, Form1->ConvDoubleDefD(sValue,0.0) );
                                //2003.05.08 E.Takase Add��
			        			//2003.05.08 E.Takase Add �R�����g��
                    			//sprintf(cFormatBuf, c1, sValue.ToDouble() );
                                //2003.05.08 E.Takase Add �R�����g��
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						sg->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;
                    }

        			// ���̃t�H���g�ɖ߂��܂�
        			SelectObject( sg->Canvas->Handle, Form3->OrgFont );

                    break;

        	case 3: // ����
					DrawText(sg->Canvas->Handle,sg->Cells[17][ARow].c_str(),-1,&r,0); //����
                    break;
        }

   } else if( ARow > 0 && ACol == 5 ){
        // ����
		DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //�E��

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
void __fastcall TForm5::SGr_ListKeyPress(TObject *Sender, char &Key)
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
void __fastcall TForm5::SGr_ListSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{

    int			i, k;
    AnsiString	sBuf;
	TStringGrid *sg = (TStringGrid *)Sender;


    if(ARow == 0) ARow = 1;

    // �i��
    if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
    	sBuf = TabSheet1->Caption;
    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
    	sBuf = TabSheet2->Caption;
    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
    	sBuf = TabSheet3->Caption;
    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
    	sBuf = TabSheet4->Caption;
    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
    	sBuf = TabSheet5->Caption;
    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
    	sBuf = TabSheet6->Caption;
    }
    Pnl_HINBAN->Caption = sBuf;

    // ����NO
    Edt_SKTKMK_JPN->Tag = sg->Cells[7][ARow].ToIntDef(0);

    // ���荀�ځi���{��j
    Edt_SKTKMK_JPN->Text = sg->Cells[1][ARow];

    // ���ږ��i�p��j
    Edt_SKTKMK_ENG->Text = sg->Cells[9][ARow];

    // ����@��
    k = sg->Cells[10][ARow].ToIntDef(-1);
    if( k == -1 ){
	    Cmb_SKTKIKI->ItemIndex = 0;
    }
    else {
    	for( i = 0; i < Form3->iKIKI_Cnt; i++){
    		if( Form3->iKIKI[i] == k ){
			    Cmb_SKTKIKI->ItemIndex = i;
            	break;
        	}
    	}
    }

    // �P��
    Cmb_TANI->Text = sg->Cells[3][ARow];

	// ���荀�ڂƂ��Ă̈���
    switch( sg->Cells[18][ARow].ToIntDef(-1) ){
		case 0: Rdo_SKTKMK_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_SKTKMK_ON->Checked = true;
          		break;
   	}

	// ���ʍ��ڂƂ��Ă̈���
    switch( sg->Cells[19][ARow].ToIntDef(-1) ){
		case 1: Rdo_TKBKMK_ON->Checked = true;
				break;
		case 0:
        default:Rdo_TKBKMK_OFF->Checked = true;
          		break;
   	}

	// �K�i�i�w����@�j
    switch( sg->Cells[11][ARow].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SHITEI_MOJI->Checked = true;
				break;
		case 2: Rdo_KIKAKU_SHITEI_KIJYUN->Checked = true;
				break;
		case 1:
        default:Rdo_KIKAKU_SHITEI_HANI->Checked = true;
          		break;
   	}

	// �K�i�i��ށj
    switch( sg->Cells[12][ARow].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SYURUI_MIN->Checked = true;
				break;
		case 2: Rdo_KIKAKU_SYURUI_MAX->Checked = true;
				break;
		case 1:
        default:Rdo_KIKAKU_SYURUI_MINMAX->Checked = true;
          		break;
   	}

	// �K�i�i��������l�̈���j
    switch( sg->Cells[20][ARow].ToIntDef(-1) ){
		case 0: Rdo_MANMIN_PRT_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_MANMIN_PRT_ON->Checked = true;
          		break;
   	}

	// �K�i�i�����_�ȉ������j
    Nmb_KIKAKU_DOUBLE->Text = IntToStr(sg->Cells[13][ARow].ToIntDef(0));

	// �K�i�l�i�͈͎w��j
    Nmb_KIKAKU_HANI_MIN->FPos = sg->Cells[13][ARow].ToIntDef(0);
    Nmb_KIKAKU_HANI_MAX->FPos = sg->Cells[13][ARow].ToIntDef(0);
    Nmb_KIKAKU_HANI_MIN->Text = sg->Cells[14][ARow];
    if( sg->Cells[11][ARow].ToIntDef(-1) == 1 ){
	    Nmb_KIKAKU_HANI_MAX->Text = sg->Cells[15][ARow];
    }
    else {
	    Nmb_KIKAKU_HANI_MAX->Text = "0";
    }

	// �K�i�l�i��l�w��j
    Nmb_KIKAKU_KIJYUN_MID->FPos = sg->Cells[13][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MAX->FPos = sg->Cells[13][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MIN->FPos = sg->Cells[13][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MID->Text = sg->Cells[14][ARow];
    if( sg->Cells[11][ARow].ToIntDef(-1) == 2 ){
    	Nmb_KIKAKU_KIJYUN_MAX->Text = sg->Cells[15][ARow];
    	Nmb_KIKAKU_KIJYUN_MIN->Text = sg->Cells[16][ARow];
    }
    else {
    	Nmb_KIKAKU_KIJYUN_MAX->Text = "0";
    	Nmb_KIKAKU_KIJYUN_MIN->Text = "0";
    }

	// �K�i�l�i�����w��j
    Edt_KIKAKU_STRING->Text = sg->Cells[27][ARow];

	// ����l�i�l�\���j
    switch( sg->Cells[21][ARow].ToIntDef(-1) ){
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
    Nmb_VALUE_DOUBLE->Text = IntToStr(sg->Cells[22][ARow].ToIntDef(0));

	// ����l�i���悎���j
    Nmb_N->Text = IntToStr(sg->Cells[5][ARow].ToIntDef(2));

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�f�ތ����̑��荀�ڕ\���Ώۂ��N���b�N�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �u�f�ތ����̐��i�K�i�}�X�^�[�Ŏw�肳��Ă��鑪�荀�ڂ���I���v
//    �u�f�ތ����̑��荀�ڈꗗ����I���v
//    �̃��W�I�{�^����؂�ւ����Ƃ���StringGrid�̕\�����e�����ւ��܂�
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
void __fastcall TForm5::Rdo_SOZAI_Click(TObject *Sender)
{
    bool blnHoge=true;
	TRadioButton	*rdo = (TRadioButton *)Sender;

    if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT1" ){
			DispSGr_List(TabSheet1,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL1" ){
			DispSGr_List(TabSheet1,2);
		}
    	SGr_ListSelectCell( SGr_List1, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List1 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet2" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT2" ){
			DispSGr_List(TabSheet2,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL2" ){
			DispSGr_List(TabSheet2,2);
		}
    	SGr_ListSelectCell( SGr_List2, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List2 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet3" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT3" ){
			DispSGr_List(TabSheet3,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL3" ){
			DispSGr_List(TabSheet3,2);
		}
    	SGr_ListSelectCell( SGr_List3, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List3 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet4" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT4" ){
			DispSGr_List(TabSheet4,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL4" ){
			DispSGr_List(TabSheet4,2);
		}
    	SGr_ListSelectCell( SGr_List4, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List4 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet5" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT5" ){
			DispSGr_List(TabSheet5,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL5" ){
			DispSGr_List(TabSheet5,2);
		}
    	SGr_ListSelectCell( SGr_List5, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List5 );

    } else if( PgCtr_List->ActivePage->Name == "TabSheet6" ){
		if( rdo->Name == "Rdo_SOZAI_SELECT6" ){
			DispSGr_List(TabSheet6,1);
		} else if( rdo->Name == "Rdo_SOZAI_ALL6" ){
			DispSGr_List(TabSheet6,2);
		}
    	SGr_ListSelectCell( SGr_List6, 1, 1, blnHoge);
	    SGr_ListClick( SGr_List6 );

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
void __fastcall TForm5::Edt_ALLChange(TObject *Sender)
{
	Form3->Edt_ALLChange( Sender );
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
void __fastcall TForm5::Nmb_KIKAKU_DOUBLEExit(TObject *Sender)
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
//    ����֐�			�F�w�肳�ꂽ�f�ޗp�i�Ԃ���T�u���̂��Z�b�g���܂�
//
//  �@�\����
//    �w�肳�ꂽ�f�ޗp�i�Ԃ���󔒂�T���o���A�󔒈ȍ~�̕�����
//    �T�u���̂Ƃ��ăZ�b�g���܂�
//
//  �p�����^����
//    AnsiString sHINBAN�F�f�ޗp�i��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm5::SetSubName( AnsiString sHINBAN )
{
    AnsiString	sBuf;
    int			i;

    sBuf = sHINBAN;
    sBuf = sBuf.Trim();
    i = sBuf.AnsiPos(" ");
    if( i > 0 && i < sBuf.Length() ){
        sBuf = sBuf.SubString( i+1, sBuf.Length()-i );
    	Edt_SKTKMK_JPN_SUB->Text = sBuf;
        Edt_SKTKMK_ENG_SUB->Text = sBuf;
    }

}



