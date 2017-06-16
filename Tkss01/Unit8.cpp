//---------------------------------------------------------------------------
//
//  Unit.cpp
//    �y�o�׌����V�X�e���|���b�g���蓖�āz
//    ���b�g���蓖�ăt�H�[���iTForm8�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �s��@�a�O
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit8.h"
#include "Tkss01.h"
#include "ThreadSozaiMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm8 *Form8;

//�Z�����
extern HANDLE hCELLINFO_SOKU_SYUKA;
extern HANDLE hCELLINFO_RIRE_SYUKA;
extern HANDLE hCELLINFO_SOKU_SOZAI;
extern HANDLE hCELLINFO_RIRE_SOZAI;
extern CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
extern CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;

HANDLE hCELLINFO_RIRELOT_SYUKA;
DTKSHIN_LOT *pCELLINFO_RIRELOT_SYUKA;
HANDLE hCELLINFO_SOKULOT_SYUKA;
DTKSHIN_LOT *pCELLINFO_SOKULOT_SYUKA;

//���i�K�i�}�X�^�[
// k.y 2003.05.17
//extern HANDLE hKSM01_DATA;

//extern KSM01_DATA *pKSM01_DATA;
extern	HANDLE 		hKSD01_DATA;
extern 	KSD01_DATA 	*pKSD01_DATA;

//���b�g���蓖�ėp�i�o�׌����j
extern HANDLE hSOKU_KSD01_DATA;
extern KSD01_DATA *pSOKU_KSD01_DATA;
extern HANDLE hRIRE_KSD01_DATA;
extern KSD01_DATA *pRIRE_KSD01_DATA;

extern bool bLOTCHANGE;				//�X���b�h�����Ƃ̒ʐM�p�t���O

int iWhereGrid;
bool bCELLWRITE;
//extern bool bNowLotF7;
//---------------------------------------------------------------------------
__fastcall TForm8::TForm8(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�Q�F�߂�v�{�^�������������̏���
//
//  �@�\����
//    ���b�g���蓖�ĉ�ʂ��I���������Ƃ�������NowLotF7�t���O��true�ɂ��܂��B(�f�ޓǂݍ��ݏ������Ɏg�p�j
//  �@�t�H�[��������C���t�H�[���ɖ߂�܂��B
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
void __fastcall TForm8::BtnF12Click(TObject *Sender)
{
    Form1->bNowLotF7 = true;
    Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyDown �C�x���g�F�@�R���g���[���Ƀt�H�[�J�X������ԂɃ��[�U�[���C�ӂ̃L�[�������Ɣ������܂��B
//
//  �@�\����
//    �t�@���N�V�����L�[�����C�x���g�𔭐������܂��B
//
//  �p�����^����
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    WORD &Key         �F���͂��ꂽ���j�[�N�ȃL�[�R�[�h
//  �@TShiftState Shift �FShift�CAlt�CCtrl�L�[���L�[�X�g���[�N�Ɍ��ѕt�����Ă��邩�ǂ����������܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm8::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    switch(Key)
    {
        case VK_F1:  BtnF01Click(Sender);    break;
        //case VK_F2:  BtnF02Click(Sender);    break;
        //case VK_F3:  BtnF03Click(Sender);    break;
        case VK_F5:  BtnF05Click(Sender);    break;
        // 2003/05/19 A.Tamura
        case VK_F10: Key = 0;
					 break;
        case VK_F11: BtnF11Click(Sender);    break;
        case VK_ESCAPE:
        case VK_F12: BtnF12Click(Sender);    break;
		//case VK_RETURN :  BtnF03Click(Sender);    break;
    }
}

//---------------------------------------------------------------------------  �@
//
//  �T�v
//    OnCloseQuery �C�x���g �FClose ���\�b�h���Ăяo���ꂽ�Ƃ��C�܂��̓��[�U�[���t�H�[����
//                          �@�V�X�e�����j���[�Łm����n��I�������Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���[�U�[���߂�{�^�����������C���t�H�[���̕���i�uX�v�{�^���j���������ɔ�������
//    ���b�Z�[�W���o�͂��܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    bool &CanClose    �F�t�H�[���̃N���[�Y���\���ǂ��������߂�_���^�ϐ�
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//�@  �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm8::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if( !fFind )   return;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCreate�C�x���g	�FForm8���쐬�����Ƃ��ɔ������܂��B
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
void __fastcall TForm8::FormCreate(TObject *Sender)
{

	// �_�~�[���b�g�ԍ��̐ݒ�


}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnActivate �C�x���g�F�@Form8���A�N�e�B�u�ɂȂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ������ʂ̃C�j�V�����C�Y���s���܂��B
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
void __fastcall TForm8::FormActivate(TObject *Sender)
{
	iWhereGrid = 0;			//0:�����A1�F����
    bCELLWRITE = false;
	Set_LOT_GRID();
	GET_KSD01();

	SET_INIT_FLAG();

    SGr_vRIRE_SYUKA->RowCount = SGr_vRIRE_SYUKA->RowCount + 1;
    SGr_vRIRE_SYUKA->Row = SGr_vRIRE_SYUKA->RowCount - 1;
    SGr_vRIRE_SYUKA->Row = 1;
    SGr_vRIRE_SYUKA->RowCount = SGr_vRIRE_SYUKA->RowCount - 1;
	if( SGr_vRIRE_SYUKA->Cells[1][1] == "�s�v" ){
        Form1->Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
    	BtnF01->Enabled = false;
    }else{
    	BtnF01->Enabled = true;
    }

    SGr_vSOKU_SYUKA->RowCount = SGr_vSOKU_SYUKA->RowCount + 1;
    SGr_vSOKU_SYUKA->Row = SGr_vSOKU_SYUKA->RowCount - 1;
    SGr_vSOKU_SYUKA->Row = 1;
    SGr_vSOKU_SYUKA->RowCount = SGr_vSOKU_SYUKA->RowCount - 1;
	if( SGr_vSOKU_SYUKA->Cells[0][1] == "�s�v" ){
        Form1->Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
    	BtnF01->Enabled = false;
    }else{
    	BtnF01->Enabled = true;
    }


    SGr_vRIRE_HINBAN->RowCount = SGr_vRIRE_HINBAN->RowCount + 1;
    SGr_vRIRE_HINBAN->Row = SGr_vRIRE_HINBAN->RowCount - 1;
    SGr_vRIRE_HINBAN->Row = 1;
    SGr_vRIRE_HINBAN->RowCount = SGr_vRIRE_HINBAN->RowCount - 1;

    SGr_vSOKU_HINBAN->RowCount = SGr_vSOKU_HINBAN->RowCount + 1;
    SGr_vSOKU_HINBAN->Row = SGr_vSOKU_HINBAN->RowCount - 1;
    SGr_vSOKU_HINBAN->Row = 1;
    SGr_vSOKU_HINBAN->RowCount = SGr_vSOKU_HINBAN->RowCount - 1;

    SGr_vSOKU_SYUKA->SetFocus();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��F�@StringGrid�̏����̏��������s���܂��B
//
//  �@�\����
//    StringGrid�̃C�j�V�����C�Y���s���܂��B
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
void __fastcall TForm8::Set_LOT_GRID(void)
{
	int iCol,iRow;

	for(iCol = 0;iCol < SGr_vRIRE_SYUKA->ColCount;iCol++ )
	{
		for(iRow = 0;iRow < SGr_vRIRE_SYUKA->RowCount;iRow++)
		{
			SGr_vRIRE_SYUKA->Cells[iCol][iRow] = "";
			SGr_vRIRE_HINBAN->Cells[iCol][iRow] = "";
		}
	}
	for(iCol = 0;iCol < SGr_vSOKU_SYUKA->ColCount;iCol++ )
	{
		for(iRow = 0;iRow < SGr_vSOKU_SYUKA->RowCount;iRow++)
		{
			SGr_vSOKU_SYUKA->Cells[iCol][iRow] = "";
			SGr_vSOKU_HINBAN->Cells[iCol][iRow] = "";
		}
	}

	SGr_vRIRE_SYUKA->RowCount = 2;
	SGr_vSOKU_SYUKA->RowCount = 2;
	SGr_vRIRE_SYUKA->ColCount = Form1->SGr_vRIRE_SYUKA->ColCount+1;
	SGr_vSOKU_SYUKA->ColCount = Form1->SGr_vSOKU_SYUKA->ColCount;

	SGr_vRIRE_HINBAN->RowCount = 2;
	SGr_vSOKU_HINBAN->RowCount = 2;
	SGr_vRIRE_HINBAN->ColCount = Form1->SGr_vRIRE_SYUKA->ColCount+1;
	SGr_vSOKU_HINBAN->ColCount = Form1->SGr_vSOKU_SYUKA->ColCount;

	//�o�׌��������b�gNO�\��
    SGr_vRIRE_SYUKA->ColWidths[0] = 170;
	SGr_vRIRE_SYUKA->Cells[0][0] = "�o�׌������i��";
    //���b�g�̕\��
	for(iCol = 1;iCol < SGr_vRIRE_SYUKA->ColCount+1;iCol++)           //onishi
    {
		SGr_vRIRE_SYUKA->Cells[iCol][0] = Form1->SGr_tRIRE->Cells[iCol-1][0];
		SGr_vRIRE_SYUKA->Cells[iCol][1] = Form1->SGr_tRIRE->Cells[iCol-1][1];

		SGr_vRIRE_HINBAN->Cells[iCol][0] = Form1->SGr_tRIRE->Cells[iCol-1][0];
	}
	for(iCol = 0;iCol < SGr_vSOKU_SYUKA->ColCount;iCol++)
    {
		SGr_vSOKU_SYUKA->Cells[iCol][0] = Form1->SGr_tSOKU->Cells[iCol][0];
		SGr_vSOKU_SYUKA->Cells[iCol][1] = Form1->SGr_tSOKU->Cells[iCol][1];

		SGr_vSOKU_HINBAN->Cells[iCol][0] = Form1->SGr_tSOKU->Cells[iCol][0];
    }

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��F�@�o�^�ς݂̃��b�g���O���b�h��ɕ\�����܂��B
//
//  �@�\����
//    �o�^�ς݂̃��b�g���O���b�h��ɕ\�����܂��B
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
void __fastcall TForm8::GET_KSD01(void)
{
	int iCol,iRow,iRow2;
	int i1;
    //int i2,i3;
    int iColCount;
    AnsiString sLot,sBuf,sHin;

    bCELLWRITE = true;
//�f�t�H���g�f�ޗp���Ӑ�i�Ԃ̕\��
/* 2003/11/18 A.Tamura �K���}�X�^�[�̑f�ޗp�i�Ԃ�\���H�@���ł͂Ȃ��ł��B
                       ���̃R�����g�̉��̃R�[�h�ɕύX���܂��B

	for(i1 = 0;i1 < 6;i1++)
    {
		switch( i1 )
		{
		case 0:
//			sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;	//�i��
			sBuf = pKSM01_DATA.DTKSHIN1_SZ;
			break;
		case 1:
			sBuf = pKSM01_DATA.DTKSHIN2_SZ;
			break;
		case 2:
			sBuf = pKSM01_DATA.DTKSHIN3_SZ;
			break;
		case 3:
			sBuf = pKSM01_DATA.DTKSHIN4_SZ;
			break;
		case 4:
			sBuf = pKSM01_DATA.DTKSHIN5_SZ;
			break;
		case 5:
			sBuf = pKSM01_DATA.DTKSHIN6_SZ;
			break;
        }
		if(sBuf.Trim().Length() == 0) break;
		for( iRow = 1; iRow < SGr_vRIRE_SYUKA->RowCount ; iRow++)
		{
        	if( SGr_vRIRE_SYUKA->Cells[0][iRow].Trim()  == sBuf ) break;
        	if( SGr_vRIRE_SYUKA->Cells[0][iRow].Trim().Length() == 0 )
			{
            	SGr_vRIRE_SYUKA->Cells[0][iRow] = sBuf;
                break;
        	}
		}
        if(iRow == SGr_vRIRE_SYUKA->RowCount)
		{
			SGr_vRIRE_SYUKA->RowCount ++;
			SGr_vSOKU_SYUKA->RowCount ++;
			SGr_vRIRE_SYUKA->Cells[0][iRow] = sBuf;
		}
    }
*/
    //�������b�g�p���b�gNO�̕\��
	if(hSOKU_KSD01_DATA )
    {
	   	iColCount = SGr_vSOKU_SYUKA->ColCount;
		for(iCol = 1;iCol < iColCount;iCol++)
		{
			//�f�t�H���g��KSM01�̑f�ޗp�i�Ԃ̕\��
			for(iRow = 0;iRow < 6;iRow++)
			{
				switch( iRow )
				{
				case 0:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN1_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO1_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN1_SZ;
					break;
				case 1:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN2_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO2_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN2_SZ;
					break;
				case 2:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN3_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO3_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN3_SZ;
					break;
				case 3:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN4_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO4_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN4_SZ;
					break;
				case 4:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN5_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO5_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN5_SZ;
					break;
				case 5:
					sBuf = pSOKU_KSD01_DATA[iCol-1].DTKSHIN6_SZ;
					sLot = pSOKU_KSD01_DATA[iCol-1].LOTNO6_SZ;
					sHin = pSOKU_KSD01_DATA[iCol-1].HINBAN6_SZ;
					break;
				}
    	        //if( sBuf.Trim().Length() == 0 || sLot.Trim().Length()==0 )
    	        if( sBuf.Trim().Length() == 0 )
				{
					iRow = 10;
        	    	break;
				}
	            for(iRow2 = 1;iRow2 < SGr_vRIRE_SYUKA->RowCount; iRow2++)
    	        {
            	    if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim() == sBuf.Trim())	//�����i�Ԃ���������
               		{
				  		if(AnsiString(pSOKU_KSD01_DATA[iCol-1].LOT_LINK_SZ).ToIntDef(0) == 1) 	//���b�g�����N���Ȃ��ꍇ��
				 		{
        	       			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = "�s�v";
            	       		break;
		   				}
		  				else
			 			{
    	           			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
    	           			SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
	   					}
					}
                    else if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim().Length() == 0)	//��i��
               		{
				  		if(AnsiString(pSOKU_KSD01_DATA[iCol-1].LOT_LINK_SZ).ToIntDef(0) == 1) 	//���b�g�����N���Ȃ��ꍇ��
				 		{
   	                        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
        	       			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = "�s�v";
            	       		break;
		   				}
		  				else
			 			{
   	                        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
    	           			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
    	           			SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
	   					}
					}

	           }
    	       if( iRow2 == SGr_vRIRE_SYUKA->RowCount)
        	   {
            		SGr_vRIRE_SYUKA->RowCount ++;
                	SGr_vSOKU_SYUKA->RowCount ++;
	                SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
    	            SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;

            		SGr_vRIRE_HINBAN->RowCount ++;
                	SGr_vSOKU_HINBAN->RowCount ++;
    	            SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
               }
           }
    	}
	}


    //�������b�g�p���b�gNO�̕\��
	if(hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)				//�����������
	{
	   	iColCount = SGr_vRIRE_SYUKA->ColCount;
		for(iCol = 1;iCol < iColCount;iCol++)
		{
			//�f�t�H���g��KSM01�̑f�ޗp�i�Ԃ̕\��
			for(iRow = 0;iRow < 6;iRow++)
			{
				switch( iRow )
				{
				case 0:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN1_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO1_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN1_SZ;
					break;
				case 1:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN2_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO2_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN2_SZ;
					break;
				case 2:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN3_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO3_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN3_SZ;
					break;
				case 3:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN4_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO4_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN4_SZ;
					break;
				case 4:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN5_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO5_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN5_SZ;
					break;
				case 5:
					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN6_SZ;
					sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO6_SZ;
					sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN6_SZ;
					break;
				}
    	        //if( sBuf.Trim().Length() == 0 || sLot.Trim().Length()==0 )
    	        if( sBuf.Trim().Length() == 0 )
				{
					iRow = 10;
        	    	break;
				}
	            for(iRow2 = 1;iRow2 < SGr_vRIRE_SYUKA->RowCount; iRow2++)
    	        {
            	    if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim() == sBuf.Trim())	//�����i�Ԃ���������
               		{
				  		if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOT_LINK_SZ).ToIntDef(0) == 1) 	//���b�g�����N���Ȃ��ꍇ��
				 		{
        	       			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = "�s�v";
            	       		break;
		   				}
		  				else
			 			{
    	           			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
    	           			SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
	   					}
					}
                    else if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim().Length() == 0)	//��i��
               		{
				  		if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOT_LINK_SZ).ToIntDef(0) == 1) 	//���b�g�����N���Ȃ��ꍇ��
				 		{
   	                        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
        	       			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = "�s�v";
            	       		break;
		   				}
		  				else
			 			{
   	                        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
    	           			SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
    	           			SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
	   					}
					}

	           }
    	       if( iRow2 == SGr_vRIRE_SYUKA->RowCount)
        	   {
            		SGr_vRIRE_SYUKA->RowCount ++;
                	SGr_vSOKU_SYUKA->RowCount ++;
	                SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
    	            SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;

            		SGr_vRIRE_HINBAN->RowCount ++;
                	SGr_vSOKU_HINBAN->RowCount ++;
    	            SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
               }
           }
    	}
	}

    //���胍�b�g�p���b�gNO�̕\��
   	iColCount = SGr_vSOKU_SYUKA->ColCount;
	for(iCol = 0;iCol < iColCount;iCol++)
	{
		//�f�t�H���g��KSM01�̑f�ޗp�i�Ԃ̕\��
		for(iRow = 0;iRow < 6;iRow++)
		{
			switch( iRow )
			{
			case 0:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO1_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN1_SZ;
				break;
			case 1:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO2_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN2_SZ;
				break;
			case 2:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO3_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN3_SZ;
				break;
			case 3:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO4_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN4_SZ;
				break;
			case 4:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO5_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN5_SZ;
				break;
			case 5:
				sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
				sLot = pSOKU_KSD01_DATA[iCol].LOTNO6_SZ;
				sHin = pSOKU_KSD01_DATA[iCol].HINBAN6_SZ;
				break;
			}
            //if( sBuf.Trim().Length() == 0 || sLot.Trim().Length()==0 )
            if( sBuf.Trim().Length() == 0 )
			{
			}
			else
			{
	            for(iRow2 = 1;iRow2 < SGr_vSOKU_SYUKA->RowCount; iRow2++)
    	        {
        	        if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim() == sBuf.Trim())	//�����i�Ԃ���������
            	   	{
			  			if(AnsiString(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ).ToIntDef(0) == 1)
			 			{
	               			SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = "�s�v";
    	               		break;
			   			}
		  				else
		 				{
               				SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;
               				SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
		   				}
					}
        	        else if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim().Length() == 0)	//�����i�Ԃ���������
            	   	{
			  			if(AnsiString(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ).ToIntDef(0) == 1)
			 			{
                	        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
	               			SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = "�s�v";
    	               		break;
			   			}
		  				else
		 				{
                	        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
               				SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;
               				SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
							break;
		   				}
					}
        	   	}
	           	if( iRow2 == SGr_vRIRE_SYUKA->RowCount)
    	       	{
        	    	SGr_vRIRE_SYUKA->RowCount ++;
            	    SGr_vSOKU_SYUKA->RowCount ++;
                	SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
	                SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;

        	    	SGr_vRIRE_HINBAN->RowCount ++;
            	    SGr_vSOKU_HINBAN->RowCount ++;
	                SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
    	       	}
			}
    	}
	}

    //�S�Ă̕\�����O���[�ɂ���
    for(iCol = 1;iCol < SGr_vRIRE_SYUKA->ColCount ;iCol++)
    {
        for(iRow = 1;iRow < SGr_vRIRE_SYUKA->RowCount ;iRow++)
        {
            SGr_vRIRE_SYUKA->Cells[iCol][iRow] = "�s�v";
        }
    }
    for(iCol = 0;iCol < SGr_vSOKU_SYUKA->ColCount ;iCol++)
    {
        for(iRow = 1;iRow < SGr_vSOKU_SYUKA->RowCount ;iRow++)
        {
            SGr_vSOKU_SYUKA->Cells[iCol][iRow] = "�s�v";
        }
    }

	// �������̊J��
	if( hCELLINFO_RIRELOT_SYUKA ){
        GlobalUnlock( hCELLINFO_RIRELOT_SYUKA );
        GlobalFree( hCELLINFO_RIRELOT_SYUKA );
    }
    hCELLINFO_RIRELOT_SYUKA = NULL;
    // �������̊m��
    hCELLINFO_RIRELOT_SYUKA = GlobalAlloc( GHND, sizeof(struct DTKSHIN_LOT) * ((SGr_vRIRE_SYUKA->ColCount+1) * SGr_vRIRE_SYUKA->RowCount));
    if( hCELLINFO_RIRELOT_SYUKA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pCELLINFO_RIRELOT_SYUKA = (struct DTKSHIN_LOT *)GlobalLock(hCELLINFO_RIRELOT_SYUKA);
    if( hCELLINFO_RIRELOT_SYUKA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }

	// �������̊J��
	if( hCELLINFO_SOKULOT_SYUKA ){
        GlobalUnlock( hCELLINFO_SOKULOT_SYUKA );
        GlobalFree( hCELLINFO_SOKULOT_SYUKA );
    }
    hCELLINFO_SOKULOT_SYUKA = NULL;
    // �������̊m��
    hCELLINFO_SOKULOT_SYUKA = GlobalAlloc( GHND, sizeof(struct DTKSHIN_LOT) * ((SGr_vSOKU_SYUKA->ColCount+1) * SGr_vSOKU_SYUKA->RowCount));
    if( hCELLINFO_SOKULOT_SYUKA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pCELLINFO_SOKULOT_SYUKA = (struct DTKSHIN_LOT *)GlobalLock(hCELLINFO_SOKULOT_SYUKA);
    if( hCELLINFO_SOKULOT_SYUKA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }

//�S�Ă̕\�����O���[�ɂ���
    for(iCol = 1;iCol < SGr_vRIRE_SYUKA->ColCount ;iCol++)
    {
        for(iRow = 1;iRow < SGr_vRIRE_SYUKA->RowCount ;iRow++)
        {
            strcpy(pCELLINFO_RIRELOT_SYUKA[iCol*SGr_vRIRE_SYUKA->RowCount+iRow].DTKSIN_SZ,AnsiString("�s�v").c_str());
        }
    }
    for(iCol = 0;iCol < SGr_vSOKU_SYUKA->ColCount ;iCol++)
    {
        for(iRow = 1;iRow < SGr_vSOKU_SYUKA->RowCount ;iRow++)
        {
            strcpy(pCELLINFO_SOKULOT_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount+iRow].DTKSIN_SZ,AnsiString("�s�v").c_str());
        }
    }



    //�������b�g�p���b�gNO�̕\��
	if(hRIRE_KSD01_DATA && Form1->iRIRE_CNT != 0)				//�����������
	{
	   	iColCount = SGr_vRIRE_SYUKA->ColCount;
		for(iCol = 1;iCol < iColCount;iCol++)
		{
            if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOT_LINK_SZ).ToIntDef(0) == 1) 	//���b�g�����N����ꍇ
            {
            }
            else
            {
    			//�f�t�H���g��KSM01�̑f�ޗp�i�Ԃ̕\��
	    		for(iRow = 0;iRow < 6;iRow++)
		    	{
			    	switch( iRow )
				    {
    				case 0:
	    				sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN1_SZ;
		    			sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO1_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN1_SZ;
			    		break;
    				case 1:
	    				sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN2_SZ;
		    			sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO2_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN2_SZ;
			    		break;
    				case 2:
	    				sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN3_SZ;
		    			sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO3_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN3_SZ;
			    		break;
				    case 3:
    					sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN4_SZ;
	    				sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO4_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN4_SZ;
		    			break;
			    	case 4:
				    	sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN5_SZ;
					    sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO5_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN5_SZ;
    					break;
	    			case 5:
		    			sBuf = pRIRE_KSD01_DATA[iCol-1].DTKSHIN6_SZ;
			    		sLot = pRIRE_KSD01_DATA[iCol-1].LOTNO6_SZ;
		    			sHin = pRIRE_KSD01_DATA[iCol-1].HINBAN6_SZ;
				    	break;
    				}
        	        if( sBuf.Trim().Length() == 0 )
	    			{
		    			iRow = 10;
        	        	break;
				    }
    	            for(iRow2 = 1;iRow2 < SGr_vRIRE_SYUKA->RowCount; iRow2++)
        	        {
                	    if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim() == sBuf.Trim())	//�����i�Ԃ���������
                   		{
                            SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
                            SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
                            strcpy(pCELLINFO_RIRELOT_SYUKA[iCol*SGr_vRIRE_SYUKA->RowCount+iRow2].DTKSIN_SZ,sLot.c_str());
                            break;
    					}
                        else if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim().Length() == 0)	//��̃Z������������
            	   	    {
                	        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
               				SGr_vRIRE_SYUKA->Cells[iCol][iRow2] = sLot;
               				SGr_vRIRE_HINBAN->Cells[iCol][iRow2] = sHin;
                            strcpy(pCELLINFO_RIRELOT_SYUKA[iCol*SGr_vRIRE_SYUKA->RowCount+iRow2].DTKSIN_SZ,sLot.c_str());
 							break;
		   				}
					}
   	                if( iRow2 == SGr_vRIRE_SYUKA->RowCount)
        	        {
            		    SGr_vRIRE_SYUKA->RowCount ++;
                	    SGr_vSOKU_SYUKA->RowCount ++;
	                    SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
    	                SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;

            		    SGr_vRIRE_HINBAN->RowCount ++;
                	    SGr_vSOKU_HINBAN->RowCount ++;
    	                SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
                    }
                }
    	    }
	    }
    }

    //���胍�b�g�p���b�gNO�̕\��
   	iColCount = SGr_vSOKU_SYUKA->ColCount;
	for(iCol = 0;iCol < iColCount;iCol++)
	{
        if(AnsiString(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ).ToIntDef(0) == 1)
        {
        }
        else
        {
    		//�f�t�H���g��KSM01�̑f�ޗp�i�Ԃ̕\��
	    	for(iRow = 0;iRow < 6;iRow++)
		    {
    			switch( iRow )
	    		{
		    	case 0:
			    	sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;
  				    sLot = pSOKU_KSD01_DATA[iCol].LOTNO1_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN1_SZ;
    				break;
	    		case 1:
		    		sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
			    	sLot = pSOKU_KSD01_DATA[iCol].LOTNO2_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN2_SZ;
				    break;
    			case 2:
	    			sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
		    		sLot = pSOKU_KSD01_DATA[iCol].LOTNO3_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN3_SZ;
			    	break;
    			case 3:
	    			sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
		    		sLot = pSOKU_KSD01_DATA[iCol].LOTNO4_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN4_SZ;
			    	break;
    			case 4:
	    			sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
		    		sLot = pSOKU_KSD01_DATA[iCol].LOTNO5_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN5_SZ;
			    	break;
    			case 5:
	    			sBuf = pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
		    		sLot = pSOKU_KSD01_DATA[iCol].LOTNO6_SZ;
  				    sHin = pSOKU_KSD01_DATA[iCol].HINBAN6_SZ;
			    	break;
    			}
                if( sBuf.Trim().Length() == 0 )
	    		{
		    	}
			    else
    			{
	                for(iRow2 = 1;iRow2 < SGr_vSOKU_SYUKA->RowCount; iRow2++)
    	            {
        	            if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim() == sBuf.Trim())	//�����i�Ԃ���������
            	       	{
               				SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;
               				SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
                            strcpy(pCELLINFO_SOKULOT_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount+iRow2].DTKSIN_SZ,sLot.c_str());
 							break;
		   				}
            	        else if(SGr_vRIRE_SYUKA->Cells[0][iRow2].Trim().Length() == 0)	//�����i�Ԃ���������
		 				{
                	        SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
               				SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;
               				SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
                            strcpy(pCELLINFO_SOKULOT_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount+iRow2].DTKSIN_SZ,sLot.c_str());
 							break;
		   				}
					}
    	           	if( iRow2 == SGr_vRIRE_SYUKA->RowCount)
        	       	{
            	    	SGr_vRIRE_SYUKA->RowCount ++;
                	    SGr_vSOKU_SYUKA->RowCount ++;
                    	SGr_vRIRE_SYUKA->Cells[0][iRow2] = sBuf;
	                    SGr_vSOKU_SYUKA->Cells[iCol][iRow2] = sLot;

            	    	SGr_vRIRE_HINBAN->RowCount ++;
                	    SGr_vSOKU_HINBAN->RowCount ++;
	                    SGr_vSOKU_HINBAN->Cells[iCol][iRow2] = sHin;
        	       	}
	    		}
    	    }
	    }
    }
    bCELLWRITE = false;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�P�F����v�{�^�������������̏���
//
//  �@�\����
//    �o�^����Ă��郍�b�g�Ɠ��͂��ꂽ���b�g���r���āA����Ă���Ƃ��͕ύX�t���O��true�ɂ��܂��B
//    ���̌�ŁA���̓��b�g��ǂݍ��݂܂��B
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
void __fastcall TForm8::BtnF11Click(TObject *Sender)
{
	int iCol,iRow,i1;
 	AnsiString sLot,sHin,sDTKSHIN,sDTKSHIN_SZ,sBuf,sMsg;
  	TMsgDlgButtons MsgButton;

    //���b�g���蓖�ă������֕ۑ�
    //����
	if( hRIRE_KSD01_DATA )
	{
		for(iCol=1;iCol<SGr_vRIRE_SYUKA->ColCount;iCol++)
    	{
			for(iRow=0;iRow<SGr_vRIRE_SYUKA->RowCount;iRow++)
			{
				sDTKSHIN = SGr_vRIRE_SYUKA->Cells[0][iRow+1];

				//if( SGr_vRIRE_SYUKA->Cells[iCol][iRow] != "�s�v" )
                sBuf = pCELLINFO_RIRELOT_SYUKA[(iCol)*SGr_vRIRE_SYUKA->RowCount+(iRow+1)].DTKSIN_SZ;
                if( sBuf.Trim() != "�s�v")
 				{
					for(i1 = 0;i1 < 6;i1++)
					{
	                	switch(i1)
						{
						    case 0:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN1_SZ;
							break;
						    case 1:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN2_SZ;
							break;
						    case 2:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN3_SZ;
							break;
					        case 3:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN4_SZ;
							break;
						    case 4:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN5_SZ;
							break;
						    case 5:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN6_SZ;
							break;
						}
						if(sDTKSHIN_SZ.Trim() == sDTKSHIN.Trim())
						{
							sLot = SGr_vRIRE_SYUKA->Cells[iCol][iRow+1];
							sHin = SGr_vRIRE_HINBAN->Cells[iCol][iRow+1];

                            //���b�g���͔���
                            if( sLot != ""  &&  sHin == "" )
	                        {
       	                        sMsg  = "�L���Ȏ��Еi�Ԃ��I������Ă��܂���P";
		                        MsgButton << mbOK;
                                MessageDlg( sMsg, mtWarning	, MsgButton, 0);
                                return;
                            }

							switch( i1 )
							{
							case 0:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO1_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE1_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE1_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO1_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN1_SZ,sHin.c_str());
								break;
							case 1:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO2_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE2_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE2_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO2_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN2_SZ,sHin.c_str());
								break;
							case 2:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO3_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE3_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE3_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO3_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN3_SZ,sHin.c_str());
								break;
							case 3:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO4_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE4_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE4_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO4_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN4_SZ,sHin.c_str());
								break;
							case 4:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO5_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE5_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE5_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO5_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN5_SZ,sHin.c_str());
								break;
							case 5:
								if(AnsiString(pRIRE_KSD01_DATA[iCol-1].LOTNO6_SZ) != sLot)
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE6_SZ,"1");
				                    pRIRE_KSD01_DATA[iCol-1].UPD_FLG = true;
                                    bLOTCHANGE = true;
								}
                                else
								{
									strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE6_SZ,"0");
								}
								strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNO6_SZ,sLot.c_str());
								strcpy(pRIRE_KSD01_DATA[iCol-1].HINBAN6_SZ,sHin.c_str());
								break;
							}
	                        break;
    	            	}
        	        }
				}
			}
		}
	}

    //����
	for(iCol=0;iCol<SGr_vSOKU_SYUKA->ColCount;iCol++)
    {
		for(iRow=1;iRow<SGr_vSOKU_SYUKA->RowCount;iRow++)
		{
			sDTKSHIN = SGr_vRIRE_SYUKA->Cells[0][iRow];			//�j�r�l01�ɓo�^����Ă���f�ޗp���Ӑ�i��

			//if( SGr_vSOKU_SYUKA->Cells[iCol][iRow] != "�s�v" )
            sBuf = pCELLINFO_SOKULOT_SYUKA[iCol*SGr_vSOKU_SYUKA->RowCount+iRow].DTKSIN_SZ;
            if( sBuf.Trim() != "�s�v")
			{
				for(i1 = 0;i1 < 6;i1++)
				{
                	switch(i1)
					{
					case 0:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;	//�i��
						break;
					case 1:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
						break;
					case 2:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
						break;
					case 3:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
						break;
					case 4:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
						break;
					case 5:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
						break;
					}
					if(sDTKSHIN_SZ.Trim() == sDTKSHIN.Trim())
					{
						sLot = SGr_vSOKU_SYUKA->Cells[iCol][iRow];
						sHin = SGr_vSOKU_HINBAN->Cells[iCol][iRow];

                        //���b�g���͔���
                        if( sLot != ""  &&  sHin == "" )
	                    {
       	                    sMsg  = "�L���Ȏ��Еi�Ԃ��I������Ă��܂���Q";
		                    MsgButton << mbOK;
                            MessageDlg( sMsg, mtWarning	, MsgButton, 0);
                            return;
                        }

						switch( i1 )
						{
						case 0:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE1_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE1_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN1_SZ,sHin.c_str());
							break;
						case 1:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE2_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE2_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN2_SZ,sHin.c_str());
							break;
						case 2:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE3_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE3_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN3_SZ,sHin.c_str());
							break;
						case 3:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE4_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE4_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN4_SZ,sHin.c_str());
							break;
						case 4:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE5_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE5_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN5_SZ,sHin.c_str());
							break;
						case 5:
                        	if(AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ) != sLot)
					   		{
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE6_SZ,"1");
                                pSOKU_KSD01_DATA[iCol].UPD_FLG = true;
                                bLOTCHANGE = true;
                            }
                            else
                            {
                            	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE6_SZ,"0");
                            }
							strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ,sLot.c_str());
							strcpy(pSOKU_KSD01_DATA[iCol].HINBAN6_SZ,sHin.c_str());
							break;
						}
                        break;
                	}
                }
			}
		}
	}
    Form1->bNowLotF7 = true;
	Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnDrawCell �C�x���g�F�O���b�h���̃Z����`�悷��K�v������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �O���b�h���̃Z����`����s���܂��B
//
//  �p�����^����
//    TObject *Sender	    �F�Ăяo������VCL�I�u�W�F�N�g
//  �@int ACol              �F�ΏۃZ����Col�ʒu
//    int ARow              �F�ΏۃZ����Row�ʒu
//    TRect &Rect           �F�Z���̈ʒu���
//    TGridDrawState State  �F�`��Z���̏��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vRIRE_SYUKADrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
	AnsiString asBuf;
	RECT r=RECT(Rect);

	asBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];		//���b�gNo
    SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;		//�s�v�Ȃ̂ŊD�F
	if(State.Contains(gdFixed))
	{
	}
	else if(asBuf == "�s�v")
	{
    	SGr_vRIRE_SYUKA->Canvas->Brush->Color= clGray;		//�s�v�Ȃ̂ŊD�F
    	SGr_vRIRE_SYUKA->Canvas->Font->Color = clGray;		//�s�v�Ȃ̂ŊD�F
    }
   	else if(State.Contains(gdFocused))
	{
    	SGr_vRIRE_SYUKA->Canvas->Brush->Color= clHighlight;	//�I��
    	SGr_vRIRE_SYUKA->Canvas->Font->Color= clHighlightText;
	}
   	else
    {
    	SGr_vRIRE_SYUKA->Canvas->Brush->Color= SGr_vRIRE_SYUKA->Color; //�m�[�}���F
		SGr_vRIRE_SYUKA->Canvas->Font->Color= SGr_vRIRE_SYUKA->Font->Color;
    }
/*
    //�I������Ă���Z���̕����F���Z�b�g
    if(State.Contains(gdFocused))
    {
    	SGr_vRIRE_SYUKA->Canvas->Font->Color= clHighlightText;
    }
   	else if(State.Contains(gdSelected))
   	{
   	//���ʂ̃Z���̕����F���Z�b�g
   	}
   	else
   	{
		SGr_vRIRE_SYUKA->Canvas->Font->Color= SGr_vRIRE_SYUKA->Font->Color;
   	}
*/
//�I�𒆂̓n�C���C�g�\��
	SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
	if(State.Contains(gdFocused))
	{
    	SGr_vRIRE_SYUKA->Canvas->Font->Color= clHighlightText;
    }
   	if(asBuf == "�s�v")
   	{
   		SGr_vRIRE_SYUKA->Canvas->Font->Color= clGray;
   	}
    SGr_vRIRE_SYUKA->Canvas->FillRect(Rect);
    InflateRect(&r,-2,-2);
    asBuf = asBuf.UpperCase();
   	DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,asBuf.c_str(),-1,&r,DT_CENTER); //�����񂹁i�����j

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�F�ꗗ�����v�{�^�������������̏���
//
//  �@�\����
//    �ꗗ������ʁiForm2�j��\�����܂�
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
void __fastcall TForm8::BtnF01Click(TObject *Sender)
{
	if( !BtnF01->Enabled ) return;

    ////////////////////
    // �ꗗ����
    if( BtnF01->Tag == 3 ){
		if( SGr_vRIRE_SYUKA->Cells[SGr_vRIRE_SYUKA->Col][SGr_vRIRE_SYUKA->Row] == "�s�v" ||
        	SGr_vRIRE_SYUKA->RowCount <= SGr_vRIRE_SYUKA->Row ||
            SGr_vRIRE_SYUKA->Col == 0 || SGr_vRIRE_SYUKA->Row == 0 )
            return;
    }
    if( BtnF01->Tag == 4 ){
		if( SGr_vSOKU_SYUKA->Cells[SGr_vSOKU_SYUKA->Col][SGr_vSOKU_SYUKA->Row] == "�s�v" ||
        	SGr_vSOKU_SYUKA->RowCount <= SGr_vSOKU_SYUKA->Row ||
            SGr_vSOKU_SYUKA->Row == 0 )
        	return;
    }
    Form2->Tag = BtnF01->Tag;
    Form2->ShowModal();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�T�F��ʈ���v�{�^�������������̏���
//
//  �@�\����
//    ��ʈ�����s���܂��B
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
void __fastcall TForm8::BtnF05Click(TObject *Sender)
{
//��ʈ��
	Form8->Print();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnSelectCell �C�x���g�F�@�O���b�h���̃Z�����I�������O�ɔ������܂��B
//
//  �@�\����
//    �o�ׁi�����j�O���b�h���̈ړ��̐������s���܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ����Col�ʒu
//    int ARow          �F�ΏۃZ����Row�ʒu
//  �@bool &CanSelect   �F�Z���̑I���A�L���^�������s���܂�
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vRIRE_SYUKASelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
    if(bCELLWRITE) return;
	iWhereGrid = 0;			//�����O���b�h�I��
   	SGr_vRIRE_SYUKA->Options << goEditing;
	//if( SGr_vRIRE_SYUKA->Cells[ACol][ARow] == "�s�v" ||
	//	SGr_vRIRE_SYUKA->RowCount <= SGr_vRIRE_SYUKA->Row ||
	//	SGr_vRIRE_SYUKA->Col == 0 || SGr_vRIRE_SYUKA->Row == 0 )
	if( SGr_vRIRE_SYUKA->Cells[ACol][ARow] == "�s�v" ||
		SGr_vRIRE_SYUKA->RowCount <= ARow ||
		ACol == 0 || ARow == 0 )                                
    {
    	CanSelect = false;
        Form1->Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
    	BtnF01->Enabled = false;
    }else{
    	BtnF01->Enabled = true;
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnSelectCell �C�x���g�F�@�O���b�h���̃Z�����I�������O�ɔ������܂��B
//
//  �@�\����
//    �o�ׁi����j�O���b�h���̈ړ��̐������s���܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ����Col�ʒu
//    int ARow          �F�ΏۃZ����Row�ʒu
//  �@bool &CanSelect   �F�Z���̑I���A�L���^�������s���܂�
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vSOKU_SYUKASelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
    if(bCELLWRITE) return;
	iWhereGrid = 1;		//����O���b�h�I��
   	SGr_vSOKU_SYUKA->Options << goEditing;
	//if( SGr_vSOKU_SYUKA->Cells[ACol][ARow] == "�s�v" ||
	//	SGr_vRIRE_SYUKA->RowCount <= SGr_vRIRE_SYUKA->Row ||
	//	SGr_vRIRE_SYUKA->Row == 0 )
	if( SGr_vSOKU_SYUKA->Cells[ACol][ARow] == "�s�v" ||
		SGr_vRIRE_SYUKA->RowCount <= ARow ||
		ARow == 0 )
    {
    	CanSelect = false;
        Form1->Delete_InplaceEdit(Sender);		// �ҏW�E�B���h�E�𖳌��ɂ��܂�
    	BtnF01->Enabled = false;
    }else{
    	BtnF01->Enabled = true;
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnDrawCell �C�x���g�F�@�O���b�h���̃Z����`�悷��K�v������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�ׁi����j�O���b�h���̈ړ��̐������s���܂��B
//
//  �p�����^����
//    TObject *Sender	    �F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol              �F�ΏۃZ����Col�ʒu
//    int ARow              �F�ΏۃZ����Row�ʒu
//    TRect &Rect           �F�ʒu���
//  �@TGridDrawState State   �F�`��Z���̏��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vSOKU_SYUKADrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
	AnsiString asBuf;
	RECT r=RECT(Rect);

	asBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];		//���b�gNo
    SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;		//�s�v�Ȃ̂ŊD�F
	if(State.Contains(gdFixed))
	{
	}
	else if(asBuf == "�s�v")
	{
    	SGr_vSOKU_SYUKA->Canvas->Brush->Color= clGray;		//�s�v�Ȃ̂ŊD�F
    	SGr_vSOKU_SYUKA->Canvas->Font->Color = clGray;		//�s�v�Ȃ̂ŊD�F
    }
   	else if(State.Contains(gdFocused))
	{
    	SGr_vSOKU_SYUKA->Canvas->Brush->Color= clHighlight;	//�I��
	}
   	else
    {
    	SGr_vSOKU_SYUKA->Canvas->Brush->Color= SGr_vSOKU_SYUKA->Color; //�m�[�}���F
    }
    //�I������Ă���Z���̕����F���Z�b�g
    if(State.Contains(gdFocused))
    {
    	SGr_vSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
    }
   	else if(State.Contains(gdSelected))
   	{
   	//���ʂ̃Z���̕����F���Z�b�g
   	}
   	else
   	{
		SGr_vSOKU_SYUKA->Canvas->Font->Color= SGr_vSOKU_SYUKA->Font->Color;
   	}
    SGr_vSOKU_SYUKA->Canvas->Font->Color = clBlack;
//�I�𒆂̓n�C���C�g�\��
	if(State.Contains(gdFocused))
	{
    	SGr_vSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
    }
   	if(asBuf == "�s�v")
   	{                                            
   		SGr_vSOKU_SYUKA->Canvas->Font->Color= clGray;
   	}

    SGr_vSOKU_SYUKA->Canvas->FillRect(Rect);
    InflateRect(&r,-2,-2);
    asBuf = asBuf.UpperCase();
   	DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,asBuf.c_str(),-1,&r,DT_CENTER); //�����񂹁i�����j

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit �C�x���g�F�@���̓t�H�[�J�X���R���g���[������ʂ̃R���g���[���ֈڂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//   �o�ׁi����j�O���b�h����t�H�[�J�X���������Ƃ��ɖ����I��DrawCell�C�x���g�𔭐����܂��B
//
//  �p�����^����
//    TObject *Sender	    �F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol              �F�ΏۃZ����Col�ʒu
//    int ARow              �F�ΏۃZ����Row�ʒu
//    TRect &Rect           �F�ʒu���
//  �@TGridDrawState State   �F�`��Z���̏��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vSOKU_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    SGr_vSOKU_SYUKADrawCell( Sender,
                             SGr_vSOKU_SYUKA->Col,
                             SGr_vSOKU_SYUKA->Row,
                             SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row),
                             State);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnEnter �C�x���g�F�@�R���g���[�������̓t�H�[�J�X���󂯎�����Ƃ��ɔ������܂��B
//
//  �@�\����
//   �o�ׁi����j�O���b�h�A�o�ׁi�����j�O���b�h�Ƀt�H�[�J�X������ꍇ�͂e�P�F�ꗗ�����{�^����L���ɂ���B�B
//
//  �p�����^����
//    TObject *Sender	    �F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol              �F�ΏۃZ����Col�ʒu
//    int ARow              �F�ΏۃZ����Row�ʒu
//    TRect &Rect           �F�ʒu���
//  �@TGridDrawState State   �F�`��Z���̏��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm8::FormEnter(TObject *Sender)
{
    AnsiString	sBuf;
    TComponent	*cmp	= dynamic_cast<TComponent*>(Sender);

    if( BtnF01->Focused() )		return;

    sBuf = cmp->Name;

    // StringGrid���@�������b�g�Ƀt�H�[�J�X���L��ꍇ
    if( SGr_vRIRE_SYUKA->Focused() || sBuf == "SGr_vRIRE_SYUKA" ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 3;
        return;
    }

    // StringGrid���@���胍�b�g�Ƀt�H�[�J�X���L��ꍇ
    if( SGr_vSOKU_SYUKA->Focused() || sBuf == "SGr_vSOKU_SYUKA" ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 4;
        return;
    }

    // �uF1�F�ꗗ�����v�{�^�����g���Ȃ��悤�ɂ���
    BtnF01->Enabled = false;
    BtnF01->Tag = 0;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit �C�x���g�F�@���̓t�H�[�J�X���R���g���[������ʂ̃R���g���[���ֈڂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//   �o�ׁi�����j�O���b�h����t�H�[�J�X���������Ƃ��ɖ����I��DrawCell�C�x���g�𔭐����܂��B
//
//  �p�����^����
//    TObject *Sender	    �F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol              �F�ΏۃZ����Col�ʒu
//    int ARow              �F�ΏۃZ����Row�ʒu
//    TRect &Rect           �F�ʒu���
//  �@TGridDrawState State   �F�`��Z���̏��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vRIRE_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;

    SGr_vRIRE_SYUKADrawCell( Sender,
                             SGr_vRIRE_SYUKA->Col,
                             SGr_vRIRE_SYUKA->Row,
                             SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row),
                             State);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��F�@���b�g�ύX�t���O�����������܂��B
//
//  �@�\����
//   ���b�g�ύX�t���O�����������܂��B
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
void __fastcall TForm8::SET_INIT_FLAG(void)
{
	int iCol,iRow,i1;
 	AnsiString sLot,sDTKSHIN,sDTKSHIN_SZ;
//���b�g���蓖�ă������֕ۑ�
//����
	if( hRIRE_KSD01_DATA )
	{
		for(iCol=1;iCol<SGr_vRIRE_SYUKA->ColCount;iCol++)
    	{
			for(iRow=0;iRow<SGr_vRIRE_SYUKA->RowCount;iRow++)
			{
				sDTKSHIN = SGr_vRIRE_SYUKA->Cells[0][iRow+1];
				if( SGr_vSOKU_SYUKA->Cells[iCol][iRow] != "�s�v" )
				{
					for(i1 = 0;i1 < 6;i1++)
					{
	                	switch(i1)
						{
						case 0:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN1_SZ;
							break;
						case 1:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN2_SZ;
							break;
						case 2:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN3_SZ;
							break;
						case 3:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN4_SZ;
							break;
						case 4:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN5_SZ;
							break;
						case 5:
							sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol-1].DTKSHIN6_SZ;
							break;
						}
						if(sDTKSHIN_SZ.Trim() == sDTKSHIN.Trim())
						{
							sLot = SGr_vRIRE_SYUKA->Cells[iCol][iRow+1];
							switch( i1 )
							{
							case 0:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE1_SZ,"0");
								break;
							case 1:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE2_SZ,"0");
								break;
							case 2:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE3_SZ,"0");
								break;
							case 3:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE4_SZ,"0");
								break;
							case 4:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE5_SZ,"0");
								break;
							case 5:
                            	strcpy(pRIRE_KSD01_DATA[iCol-1].LOTNOCHANGE6_SZ,"0");
								break;
							}
	                        break;
    	            	}
        	        }
				}
			}
		}                                             
	}
//����
	for(iCol=0;iCol<SGr_vSOKU_SYUKA->ColCount;iCol++)
    {
		for(iRow=1;iRow<SGr_vSOKU_SYUKA->RowCount;iRow++)
		{
			sDTKSHIN = SGr_vRIRE_SYUKA->Cells[0][iRow];			//�j�r�l01�ɓo�^����Ă���f�ޗp���Ӑ�i��

			if( SGr_vSOKU_SYUKA->Cells[iCol][iRow] != "�s�v" )
			{
				for(i1 = 0;i1 < 6;i1++)
				{
                	switch(i1)
					{
					case 0:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;	//�i��
						break;
					case 1:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
						break;
					case 2:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
						break;
					case 3:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
						break;
					case 4:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
						break;
					case 5:
						sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
						break;
					}
					if(sDTKSHIN_SZ.Trim() == sDTKSHIN.Trim())
					{
						sLot = SGr_vSOKU_SYUKA->Cells[iCol][iRow];
						switch( i1 )
						{
						case 0:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE1_SZ,"0");
							break;
						case 1:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE2_SZ,"0");
							break;
						case 2:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE3_SZ,"0");
							break;
						case 3:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE4_SZ,"0");
							break;
						case 4:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE5_SZ,"0");
							break;
						case 5:
                        	strcpy(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE6_SZ,"0");
							break;
						}
                        break;
                	}
                }
			}
		}
	}
    bLOTCHANGE = false;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyPress�C�x���g	�F���[�U�[���P��̕����L�[���������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�ׁi�����j�O���b�h�Ƀ��[�U�[�̓��͂����邽�тɓ��͕������L�����𒲂ׂ܂��B
//    �����񒷂̊m�F
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    char &Key         : char�^�̃L�[�R�[�h
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vRIRE_SYUKAKeyPress(TObject *Sender, char &Key)
{
    int iCol,iRow;
    AnsiString sBuf;

    iCol = SGr_vRIRE_SYUKA->Col;
    iRow = SGr_vRIRE_SYUKA->Row;
    sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow];
    Form1->ChkInputData( sBuf, 3, Sender, Key, 6);

    // ���͒l�i���p������a�`z�j�́A�����I�ɑ啶���ϊ����ăZ�b�g���܂�
    if( Key >= 0x61 && Key <= 0x7A ){
		Key -= 0x20;
    }
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyPress�C�x���g	�F���[�U�[���P��̕����L�[���������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�ׁi����j�O���b�h�Ƀ��[�U�[�̓��͂����邽�тɓ��͕������L�����𒲂ׂ܂��B
//    �����񒷂̊m�F
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    char &Key         : char�^�̃L�[�R�[�h
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm8::SGr_vSOKU_SYUKAKeyPress(TObject *Sender, char &Key)
{
    int iCol,iRow;
    AnsiString sBuf;

    iCol=SGr_vSOKU_SYUKA->Col;
    iRow=SGr_vSOKU_SYUKA->Row;
    sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow];
    Form1->ChkInputData( sBuf, 3 , Sender, Key, 6);

    // ���͒l�i���p������a�`z�j�́A�����I�ɑ啶���ϊ����ăZ�b�g���܂�
    if( Key >= 0x61 && Key <= 0x7A ){
		Key -= 0x20;
    }
}
//---------------------------------------------------------------------------

