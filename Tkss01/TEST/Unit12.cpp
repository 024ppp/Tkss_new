//---------------------------------------------------------------------------
//
//  Unit12.cpp
//    �y�o�׌����V�X�e���|��������z
//    �f�ރf�[�^�̎�蒼���t�H�[���iTForm12�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �s��@�a�O
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit12.h"
#include "Tkss01.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm12 *Form12;

extern CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
extern CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;
//���b�g���蓖�ā��j�r�c01
//���b�g���蓖��
extern HANDLE hSOKU_KSD01_DATA;
extern KSD01_DATA *pSOKU_KSD01_DATA;
extern HANDLE hRIRE_KSD01_DATA;
extern KSD01_DATA *pRIRE_KSD01_DATA;
//---------------------------------------------------------------------------
__fastcall TForm12::TForm12(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�n�j�v�{�^�������������̏���
//
//  �@�\����
//    RadioButton1Checked = true:����l�i�\�j�݂̂̎�荞�݂�f�ރf�[�^����s���܂��B
//            �V          = false:����l�i�\�j�A����l�i���j�̎�荞�݂�f�ރf�[�^����s���܂��B
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
void __fastcall TForm12::ButtonOKClick(TObject *Sender)
{
    // �ʏ�̑����ʂɕύX
    Form1->SGr_vRIRE_SOZAI->Color = (TColor)0x00D2FFFF;
    Form1->SGr_vSOKU_SOZAI->Color = (TColor)0x00D2FFFF;
    Form1->SGr_vRIRE_SYUKA->Color = (TColor)0x00FFEEDD;
    Form1->SGr_vSOKU_SYUKA->Color = clWindow;
    Form1->SCREEN_SET();
    Form1->Mem_vRIRE_MEMOORG->Color = (TColor)0x00FFEEDD;
    Form1->SBr1->Panels->Items[0]->Text = "�ʏ�̑����ʂł��B";
    InfoClear();

	// 2004.12.24(X'mas Eve) A.Tamura ��荞�ݗ\���LOTNO1_SZ�`LOTNO6_SZ���Đݒ肷��
    LOTNO1_SZ_Clear();

    if(Rdo_Button1->Checked == true)
    {
        Form1->GET_KSD22_AGAIN();
    }
    else
    {
        Form1->GET_KSD22();
    }
    Form1->GET_SOZAI_KSD02_DISP();
    Close();
}
//---------------------------------------------------------------------------
//
//  �T�v
//    OnActivate�C�x���g	�F�t�H�[�����A�N�e�B�u�ɂȂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �f�t�H���g�̃��W�I�{�^���Ƀ`�F�b�N�����܂��B
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
void __fastcall TForm12::FormActivate(TObject *Sender)
{
     Rdo_Button1->Checked = true;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�uCancel�v�{�^�������������̏���
//
//  �@�\����
//    Form����܂��B
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
void __fastcall TForm12::ButtonCancelClick(TObject *Sender)
{
    Close();    
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��FKSD01�Ɋi�[�����\���LOTNO1_SZ�`LOTNO6_SZ���Đݒ肵�܂��B
//
//  �@�\����
//    KSD01�Ɋi�[�����\���LOTNO1_SZ�`LOTNO6_SZ���Đݒ肵�܂��B
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm12::LOTNO1_SZ_Clear(void)
{
	int iCol,i2;
	AnsiString sBuf2;

    // �����ʑ�
	for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
	{
        for(i2 = 0;i2 < 6;i2++)
        {
        	switch( i2 )
            {
            case 0:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;
                break;
            case 1:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
                break;
            case 2:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
                break;
            case 3:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
                break;
            case 4:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
                break;
            case 5:
            	sBuf2 = pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
                break;
            }
	 		if(AnsiString(pKSM01_DATA.LOT_LINK_SZ) == 1 && sBuf2.Length() != 0)
			{
                switch( i2 )
                {
                case 0:
				    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                case 1:
				    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                case 2:
                    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                case 3:
                    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                case 4:
                    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                case 5:
                    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
                    break;
                }
			}
		}
	}


    // ������ʑ�
    if(Form1->iRIRE_CNT == 0 ) return;
	for(iCol = 0;iCol<Form1->SGr_tRIRE->ColCount;iCol++)
	{
        for(i2 = 0;i2 < 6;i2++)
        {
        	switch( i2 )
            {
            case 0:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN1_SZ;
                break;
            case 1:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN2_SZ;
                break;
            case 2:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN3_SZ;
                break;
            case 3:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN4_SZ;
                break;
            case 4:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN5_SZ;
                break;
            case 5:
            	sBuf2 = pRIRE_KSD01_DATA[iCol].DTKSHIN6_SZ;
                break;
            }
	 		if(AnsiString(pKSM01_DATA.LOT_LINK_SZ) == 1 && sBuf2.Length() != 0)
			{
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO1_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO2_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO3_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO4_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO5_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].LOTNO6_SZ,Form1->SGr_tRIRE->Cells[iCol][0].c_str());
			}
		}
	}

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ޑ���o�b�t�@���N���A���܂��B
//
//  �@�\����
//    �ǂݍ��ݑO�ɑf�ރo�b�t�@���N���A���܂��B
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm12::InfoClear(void)
{
    int i1,i2;
    for( i1 = 0; i1 < Form1->SGr_vSOKU_SOZAI->ColCount ; i1++)
    {
        for(i2= 1; i2 <  Form1->SGr_vSOKU_SOZAI->RowCount ; i2++)
        {
            Form1->SGr_vSOKU_SOZAI->Cells[i1][i2]="";
            strcpy(pCELLINFO_SOKU_SOZAI[i1*Form1->SGr_vSOKU_SOZAI->RowCount+i2].RESULT,"");
            if(Rdo_Button1->Checked == false)
            {
                strcpy(pCELLINFO_SOKU_SOZAI[i1*Form1->SGr_vSOKU_SOZAI->RowCount+i2].DISP_RESULT,"");
            }
            pCELLINFO_SOKU_SOZAI[i1*Form1->SGr_vSOKU_SOZAI->RowCount+i2].JUDGE = 2;
            //�V�K�Ɏ�蒼���̂ŋ����I��UPDATE�t���O��True�ɂ��ăZ�[�u���o����悤�ɂ��܂��B
            pSOKU_KSD01_DATA[i1].UPD_FLG = true;
        }
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�FLabel4(����p�l�i�\�j�ƈ���p�l�i���j�Ɏ�荞�݂��s���B)�����������̏���
//
//  �@�\����
//    Form����܂��B
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
void __fastcall TForm12::Label4Click(TObject *Sender)
{
    Rdo_Button2->Checked = true;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�FLabel2(����p�l�i�\�j�݂̂Ɏ�荞�݂��s���B)�����������̏���
//
//  �@�\����
//    Form����܂��B
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
void __fastcall TForm12::Label2Click(TObject *Sender)
{
    Rdo_Button1->Checked = true;

}
//---------------------------------------------------------------------------


