//---------------------------------------------------------------------------
//
//  ThreadSozaiSyuka.cpp
//    �y�o�׌����V�X�e���|�f�ށi�����j�f�[�^�ǂݎ��z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �s��@�a�O
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "ThreadSozaiRire.h"
#include "ThreadSozaiMain.h"
#include "Tkss01.h"
#include "Unit1.h"
#pragma package(smart_init)

// k.y 2003.05.17
//extern HANDLE hSOZAI_OR_DATA;

// k.y 2003.05.17
//extern KSM02_DATA *pSOZAI_OR_DATA;         // �f�ނ̂n�q�f�[�^
extern KSM02_DATA pSOZAI_OR_DATA[100];

// k.y 2003.05.17
//extern HANDLE hSOZAI_OR_DATA2;

// k.y 2003.05.17
//extern KSM02_DATA *pSOZAI_OR_DATA2;        // �f�ނ̂n�q�f�[�^�i�f�ރ��C���ō쐬�j
extern KSM02_DATA pSOZAI_OR_DATA2[100];

// k.y 2003.05.17
//extern HANDLE hSOZAI_SYKA_DATA;

// k.y 2003.05.17
//extern KSM02_DATA *pSOZAI_SYKA_DATA;
extern KSM02_DATA pSOZAI_SYKA_DATA[100];

// k.y 2003.05.17
//extern HANDLE hSOZAI_RIRE_DATA;

// k.y 2003.05.17
//extern KSD02_DATA *pSOZAI_RIRE_DATA;
extern KSD02_DATA pSOZAI_RIRE_DATA[100];

// k.y 2003.05.17
//extern HANDLE hSOZAI_RIRE_LOT;
// k.y 2003.05.17
//extern KSD01_DATA *pSOZAI_RIRE_LOT;
extern KSD01_DATA pSOZAI_RIRE_LOT[100];

extern HANDLE hCELLINFO_RIRE_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;

extern int iSOZAI_KOMKCNT;
extern int iSOZAI_CONT_CONT;
extern int iSOZAI_RIRE_LOT;
extern int iSOZAI_ORCNT;
extern int iSOZAI_SOKUCNT;													//�\�[�g���g�p����d�݌v�Z�p�o�b�t�@
extern int iSOZAI_RireCnt,iSOZAI_SyukaCnt,iSOZAI_SokuCnt,iSOZAI_ContCnt,iSOZAI_KikiCnt;
extern int iSOZAI_ORCNT;

//���b�g���蓖�ėp�i���������j
extern HANDLE hRIRE_KSD01_DATA;
extern KSD01_DATA *pRIRE_KSD01_DATA;
extern bool bLOTCHANGE;						//���b�g���蓖�ĉ�ʂƂ̒ʐM�p�t���O

// k.y 2003.06.03
extern int iDEBUG;

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ޏo�ח���ǂݎ�胁�C���B
//
//  �@�\����
//    �n�q�e�[�u�����Q�Ƃ��đf�ޏo�ח�����ǂݎ��B
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
void __fastcall TForm1::SetRIRE_Sozai(void)
{
//Or�e�[�u�����o���Ă���̂ŗ����f�[�^�̏ڍׂ����߂ēǂݍ���
    int i1,i2,i3;
    AnsiString sBuf,sTempLot;
    //int iRireCnt = Form1->iRIRE_CNT;
    //int iColCnt;
    //int iCol,iRow;
	double dMAX,dMIN;//dSWAP;
	int i4,iRowCount,iColCount;

    iColCount = Form1->SGr_tRIRE->ColCount;
    iRowCount = SGr_vRIRE_SOZAI->RowCount;
	if( bNowLotF7 == false )
    {

        memset(pSOZAI_RIRE_DATA,0x00,sizeof(pSOZAI_RIRE_DATA));
    }

	if( bNowLotF7 == false && SGr_vRIRE_SYUKA->RowCount < 2)
    {
        //	�������b�g�̕`��
      	//for( i1 = 0;i1 < Form1->iRIRE_CNT ; i1++)
	    //{
		//    Form1->SGr_tRIRE->Cells[i1][0] = Form1->sRIREKI_LOT->Strings[i1];
    	//}
/*
	    // �������̊J��
    	if( hRIRE_KSD01_DATA ){
    		GlobalUnlock( hRIRE_KSD01_DATA );
	        GlobalFree( hRIRE_KSD01_DATA );
    	}
        hRIRE_KSD01_DATA = NULL;
	    // �������̊m��
    	hRIRE_KSD01_DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * (Form1->SGr_tRIRE->ColCount + 1 ));
	    if( hRIRE_KSD01_DATA == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(�o�ח����Z��01)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    	pRIRE_KSD01_DATA = (struct KSD01_DATA *)GlobalLock(hRIRE_KSD01_DATA);
	    if( hRIRE_KSD01_DATA == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(�o�ח����Z��02)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
*/
    	//Form1->SGr_tRIRE		->ColCount	= Form1->iRIRE_CNT;
        //Form1->SGr_vRIRE_SYUKA	->ColCount 	= Form1->iRIRE_CNT;
        //Form1->SGr_vRIRE_SOZAI	->ColCount 	= Form1->iRIRE_CNT;

     	//GET_KSD01();
        //iColCnt = i1;


    }

//�o�׌����ɂ��郍�b�g�𒊏o����NOT�̏����ɂ���
AnsiString sSOZAI_RIRE_LOT;


	if( bNowLotF7 == false )		//���b�g���蓖�ĕύX���͗����f�[�^�͊֌W�Ȃ�����ǂ܂Ȃ�
    {
        //SET_RIRE_KSD01();
		// �������̊J��
		if( hCELLINFO_RIRE_SOZAI ){
        	GlobalUnlock( hCELLINFO_RIRE_SOZAI );
	        GlobalFree( hCELLINFO_RIRE_SOZAI );
    	}
        hCELLINFO_RIRE_SOZAI = NULL;
	    // �������̊m��
    	hCELLINFO_RIRE_SOZAI = GlobalAlloc( GHND, sizeof(struct CELLINFO_DATA) * ((Form1->SGr_tRIRE->ColCount + 1) * iRowCount));
	    if( hCELLINFO_RIRE_SOZAI == NULL ){
    	    Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B((�f�ޗ���))";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    	pCELLINFO_RIRE_SOZAI = (struct CELLINFO_DATA *)GlobalLock(hCELLINFO_RIRE_SOZAI);
	    if( hCELLINFO_RIRE_SOZAI == NULL ){
    	    Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B((�f�ޗ���))";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
	}
    if(!hCELLINFO_RIRE_SOZAI) return;
//���i�K�i���ׂ̊e�Z�����ւ̃R�s�[
    //�����L�[�Ō������Ȃ̂ŁA�Z���C���t�H�����l���
	if( bNowF7 == true  )
    {
		for(i1=0; i1< Form1->SGr_tRIRE->ColCount ;i1++)
		{
    		i4 = 1;
			for(i2=0 ; i2 < iSOZAI_ContCnt ; i2++)
			{
				GetSOZAI_KIKAKU(i2,&dMAX,&dMIN);     
				if( hCELLINFO_RIRE_SOZAI )
				{
					for( i3 = 0;i3 < AnsiString(pSOZAI_OR_DATA[i2].SOKU_SU).ToIntDef(0);i3++)
					{
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].DTKSHIN 		, pSOZAI_OR_DATA[ i2 ].DTKSHIN);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].LOTNO 		, Form1->SGr_tSOKU->Cells[i1][0].c_str());
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].UNQ_NO 		, pSOZAI_OR_DATA[ i2 ].UNQ_NO);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].ORDER_NO		, pSOZAI_OR_DATA[ i2 ].ORDER_NO);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].SKB_NO 		, pSOZAI_OR_DATA[ i2 ].SKB_NO);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].HINBAN_SK	, pSOZAI_OR_DATA[ i2 ].HINBAN_SK);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KOMK_NO 		, pSOZAI_OR_DATA[ i2 ].KOMK_NO);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KOMK_NO 		, "-999");				//�����͉ߋ��Ɍv�����Ă���̂ŊD�F�\���܂�
						pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].INS_ON = false;				//�����͉ߋ��Ɍv�����Ă���̂ŊD�F�\���܂�
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KOMK_NM 		, pSOZAI_OR_DATA[ i2 ].KOMK_NM);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KOMK_ENG		, pSOZAI_OR_DATA[ i2 ].KOMK_ENG);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KOMK_SUB		, pSOZAI_OR_DATA[ i2 ].KOMK_SUB);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KOMK_SUB_ENG , pSOZAI_OR_DATA[ i2 ].KOMK_SUB_ENG);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKI_NO 		, pSOZAI_OR_DATA[ i2 ].KIKI_NO);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKI_NM 		, pSOZAI_OR_DATA[ i2 ].KIKI_NM);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].TANI    		, pSOZAI_OR_DATA[ i2 ].TANI);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKA_TYPE	, pSOZAI_OR_DATA[ i2 ].KIKA_TYPE);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKA_KIND	, pSOZAI_OR_DATA[ i2 ].KIKA_KIND);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKA_DECI	, pSOZAI_OR_DATA[ i2 ].KIKA_DECI);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKA_NUM1	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM1);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKA_NUM2	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM2);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKA_NUM3	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM3);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKA_STR		, pSOZAI_OR_DATA[ i2 ].KIKA_STR);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKA_SUB1	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB1);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKA_SUB2	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB2);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKA_SUB3	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB3);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].SOKU_SU 		, pSOZAI_OR_DATA[ i2 ].SOKU_SU);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].SOKU_FLG		, pSOZAI_OR_DATA[ i2 ].SOKU_FLG);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].TOKU_FLG		, pSOZAI_OR_DATA[ i2 ].TOKU_FLG);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KIKA_PRT		, pSOZAI_OR_DATA[ i2 ].KIKA_PRT);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].VALUE_TYPE	, pSOZAI_OR_DATA[ i2 ].VALUE_TYPE);
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].VALUE_DECI	, pSOZAI_OR_DATA[ i2 ].VALUE_DECI);
    	  				strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].RESULT		, AnsiString("").c_str());
    	  				strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].DISP_RESULT	, AnsiString("").c_str());
    	                pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].MAX = dMAX ;
        	            pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].MIN = dMIN ;
    	                pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].GMAX = dMAX ;
        	            pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].GMIN = dMIN ;
						i4++;
					}
				}
			}
	    }
	}
    //���b�g���蓖�ĕύX���͗����f�[�^�͊֌W�Ȃ�����ǂ܂Ȃ�
	if( bNowLotF7 == false )
    {
		Form1->Set_RIRE_SOZAIJISSEKI();
//		Synchronize(Form1->Set_RIRE_SOZAIJISSEKI);
	}
    //���b�g���蓖�ĕύX����KSD22����f�[�^��ǂ�
	if( bNowLotF7 == true && bLOTCHANGE == true )
    {
		GET_RIRE_KSD22();
	}
    for(i1=0; i1< Form1->SGr_tRIRE->ColCount ;i1++)
    {
        i4 = 1;
        for(i2=0 ; i2 < iSOZAI_ContCnt ; i2++)
        {
            if( hCELLINFO_RIRE_SOZAI )
            {
                for( i3 = 0;i3 < AnsiString(pSOZAI_OR_DATA[i2].SOKU_SU).ToIntDef(0);i3++)
                {
                    strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].SOKU_SU 		, pSOZAI_OR_DATA[ i2 ].SOKU_SU);
                    i4++;
                }
            }
        }
    }
//	Synchronize(PUT_SOZAIRIRE_KSD02_DISP);
    //����������Ȗ��O�ł����A�����̃Z���ւ̕\�����s���Ă��܂��B
	PUT_SOZAIRIRE_KSD02_DISP();
	iTHREAD_CNT ++;                 //�X���b�h�����̖��c�ł��B
}



//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FKSD01�ǂݍ��݁B
//
//  �@�\����
//    �n�q�e�[�u�����Q�Ƃ��đ�����уf�[�^��ǂݎ��B
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
void __fastcall TForm1::SET_RIRE_KSD01(void)
{
//�f�t�H���g�̕i�Ԃ̃Z�b�g
	int iCol,i2;//i1,i3;
	AnsiString sBuf,sLot,sBuf2;
    AnsiString sLot_Where;

    if(Form1->iRIRE_CNT == 0 ) return;
	for(iCol = 0;iCol<Form1->SGr_tRIRE->ColCount;iCol++)
	{
		strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN	 	,Form1->sNowDTKSHIN.c_str());
		strcpy(pRIRE_KSD01_DATA[iCol].LOTNO	 	 	,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN 	 	,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
		//strcpy(pRIRE_KSD01_DATA[iCol].HINBAN	 	,pKSM01_DATA.HINBAN);
		strcpy(pRIRE_KSD01_DATA[iCol].DTKSCOD	 	,pKSM01_DATA.DTKSCOD);
		strcpy(pRIRE_KSD01_DATA[iCol].DTKSNAM	 	,pKSM01_DATA.DTKSNAM);
		strcpy(pRIRE_KSD01_DATA[iCol].ZISNAM	 	,pKSM01_DATA.ZISNAM);
		strcpy(pRIRE_KSD01_DATA[iCol].HINMEI	 	,pKSM01_DATA.HINMEI);
		strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN1_SZ	,pKSM01_DATA.DTKSHIN1_SZ);
		strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN2_SZ	,pKSM01_DATA.DTKSHIN2_SZ);
		strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN3_SZ	,pKSM01_DATA.DTKSHIN3_SZ);
		strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN4_SZ	,pKSM01_DATA.DTKSHIN4_SZ);
		strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN5_SZ	,pKSM01_DATA.DTKSHIN5_SZ);
		strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN6_SZ	,pKSM01_DATA.DTKSHIN6_SZ);
		strcpy(pRIRE_KSD01_DATA[iCol].LOT_LINK_SZ	,pKSM01_DATA.LOT_LINK_SZ);
		strcpy(pRIRE_KSD01_DATA[iCol].SOKUTEI_NUM	,pKSM01_DATA.SOKUTEI_NUM);
		strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK	 	,"0");					//�f�t�H���g�͂n�j
		strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK_PRT	,"0");					//�f�t�H���g�͂n�j
		strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK	 	,"0");					//�f�t�H���g�͂n�j
		strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK_PRT	,"0");					//�f�t�H���g�͂n�j
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE1 	,pKSM01_DATA.OUT_TITLE1);
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE2 	,pKSM01_DATA.OUT_TITLE2);
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE3 	,pKSM01_DATA.OUT_TITLE3);
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE4 	,pKSM01_DATA.OUT_TITLE4);
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE5 	,pKSM01_DATA.OUT_TITLE5);
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE6 	,pKSM01_DATA.OUT_TITLE6);
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE7 	,pKSM01_DATA.OUT_TITLE7);
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE8 	,pKSM01_DATA.OUT_TITLE8);
		strcpy(pRIRE_KSD01_DATA[iCol].X_OUT 	 	,pKSM01_DATA.X_OUT);
		pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
		pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;

        // 2004.12.24(X'mas Eve) A.Tamura �Ō�܂Ń��[�v����ĂȂ��I�I
        // for(i2 = 0;i2 < 5;i2++)
        for(i2 = 0;i2 < 6;i2++)
        {
			//i3 = 0;
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

				strcpy(pRIRE_KSD01_DATA[iCol].HINBAN1_SZ,Form1->SGr_tRIRE->Cells[iCol][1].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].HINBAN2_SZ,Form1->SGr_tRIRE->Cells[iCol][1].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].HINBAN3_SZ,Form1->SGr_tRIRE->Cells[iCol][1].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].HINBAN4_SZ,Form1->SGr_tRIRE->Cells[iCol][1].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].HINBAN5_SZ,Form1->SGr_tRIRE->Cells[iCol][1].c_str());
				strcpy(pRIRE_KSD01_DATA[iCol].HINBAN6_SZ,Form1->SGr_tRIRE->Cells[iCol][1].c_str());
			}
        }
	}

    //�����̗L�镨�̃Z�b�g
	sLot ="";
	for(iCol = 0;iCol<Form1->SGr_tRIRE->ColCount;iCol++)
	{
    	sLot += "'" + Form1->SGr_tRIRE->Cells[iCol][0] +"',";
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi��
    // ���b�g��������������
    sLot_Where = "";
	for(iCol = 0;iCol<Form1->SGr_tRIRE->ColCount;iCol++)
	{
        sLot_Where += "( LOTNO='" + Form1->SGr_tRIRE->Cells[iCol][0] + "' AND ";
        sLot_Where += " HINBAN='" + Form1->SGr_tRIRE->Cells[iCol][1] + "') OR ";
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi��

	sBuf = "SELECT * FROM KSD01";
	sBuf += " WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";
	//sBuf += " AND   LOTNO IN (" + sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";
	sBuf += " ORDER BY LOTNO";

    //For Debug
    if( iDEBUG == 1 )
    {
	    ClpBrd = Clipboard();
	    ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
    // Initial Query
	Form1->Query4->Close();
    Form1->Query4->SQL->Clear();
    Form1->Query4->SQL->Add(sBuf);
    Form1->Query4->Open();
    Form1->Query4->Active = true;

	while(Form1->Query4->Eof != true)
	{
        //���𑪒���уf�[�^�̓ǂݍ���
		for(iCol = 0;iCol<Form1->SGr_tRIRE->ColCount;iCol++)
		{
			if(Form1->SGr_tRIRE->Cells[iCol][0] == AnsiString(Form1->Query4->FieldValues["LOTNO"])) break;
		}

        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN"];						    //���Ӑ�i��
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN	 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].LOTNO		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO"];                     		//���b�gNO
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO	 				,sBuf.c_str());
        }
        strcpy(pRIRE_KSD01_DATA[iCol].HINBAN		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN"];                     		//�H�ǔ��s�� onishi
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN	 				,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].LOTNO1_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO1_SZ"];                 		//�f�ޗp���b�g�P
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO1_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].LOTNO2_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO2_SZ"];                         //�f�ޗp���b�g�Q
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO2_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].LOTNO3_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO3_SZ"];                         //�f�ޗp���b�g�R
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO3_SZ	 	 		,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].LOTNO4_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO4_SZ"];                         //�f�ޗp���b�g�S
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO4_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].LOTNO5_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO5_SZ"];                         //�f�ޗp���b�g�T
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO5_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].LOTNO6_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO6_SZ"];                         //�f�ޗp���b�g�U
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO6_SZ	 	 		,sBuf.c_str());
		}
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN1_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN1_SZ"];                 		//�f�ޗp���Еi��1
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN1_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN2_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN2_SZ"];                 		//�f�ޗp���Еi��2
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN2_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN3_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN3_SZ"];                 		//�f�ޗp���Еi��3
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN3_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN4_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN4_SZ"];                 		//�f�ޗp���Еi��4
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN4_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN5_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN5_SZ"];                 		//�f�ޗp���Еi��5
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN5_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN6_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN6_SZ"];                 		//�f�ޗp���Еi��6
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN6_SZ	 	 	,sBuf.c_str());
        }

        strcpy(pRIRE_KSD01_DATA[iCol].HINBAN		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN"];                       	//���Еi��
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN	 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].DTKSCOD		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSCOD"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSCOD"];                      	//���Ӑ�R�[�h
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSCOD	 	 		,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSNAM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSNAM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSNAM"];                      	//���Ӑ於��
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSNAM	 	 		,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].ZISNAM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["ZISNAM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["ZISNAM"];                       	//�ގ�����
			strcpy(pRIRE_KSD01_DATA[iCol].ZISNAM	 	 		,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].HINMEI		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINMEI"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINMEI"];                      	//�i��
			strcpy(pRIRE_KSD01_DATA[iCol].HINMEI	 	 		,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN1_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN1_SZ"];                  	//�f�ޗp���Ӑ�i�ԂP
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN1_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN2_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN2_SZ"];                    //�f�ޗp���Ӑ�i�ԂQ
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN2_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN3_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN3_SZ"];                    //�f�ޗp���Ӑ�i�ԂR
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN3_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN4_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN4_SZ"];                    //�f�ޗp���Ӑ�i�ԂS
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN4_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN5_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN5_SZ"];                    //�f�ޗp���Ӑ�i�ԂT
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN5_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN6_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN6_SZ"];                    //�f�ޗp���Ӑ�i�ԂU
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN6_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].LOT_LINK_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOT_LINK_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOT_LINK_SZ"];                    //���b�g�����N
			strcpy(pRIRE_KSD01_DATA[iCol].LOT_LINK_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].SOKUTEI_NUM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SOKUTEI_NUM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOKUTEI_NUM"];                    //���荀�ڐ�
			strcpy(pRIRE_KSD01_DATA[iCol].SOKUTEI_NUM			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SOZAI_OK"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOZAI_OK"];                       //�f�ޔ���
			strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK				,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK_PRT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SOZAI_OK_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOZAI_OK_PRT"];                   //�f�ޔ������p
			strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK_PRT			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SYUKA_OK"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SYUKA_OK"];                       //�o�ה���
			strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK				,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK_PRT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SYUKA_OK_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SYUKA_OK_PRT"];                   //�o�ה������p
			strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK_PRT			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE1		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE1"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE1"];                     //���я��^�C�g���o�͍��ڂP
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE1 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE2		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE2"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE2"];                     //���я��^�C�g���o�͍��ڂQ
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE2 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE3		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE3"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE3"];                     //���я��^�C�g���o�͍��ڂR
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE3 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE4		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE4"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE4"];                     //���я��^�C�g���o�͍��ڂS
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE4 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE5		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE5"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE5"];                     //���я��^�C�g���o�͍��ڂT
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE5 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE6		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE6"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE6"];                     //���я��^�C�g���o�͍��ڂU
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE6 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE7		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE7"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE7"];                     //���я��^�C�g���o�͍��ڂV
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE7 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE8		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE8"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE8"];                     //���я��^�C�g���o�͍��ڂW
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE8 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].X_OUT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["X_OUT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["X_OUT"];                          //�w�o�[
			strcpy(pRIRE_KSD01_DATA[iCol].X_OUT 	 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].MEMO		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["MEMO"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["MEMO"];                           //���l
			strcpy(pRIRE_KSD01_DATA[iCol].MEMO 	 				,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_SZ"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_SZ"];                      //�f�ޗp�����
			strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ 	 			,sBuf.c_str());
        }
        strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ_PRT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_SZ_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_SZ_PRT"];                  //�f�ޗp������i����p�j
			strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ_PRT 	 	  	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD"];                         //�o�חp�����
			strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD 	 			,sBuf.c_str());
        }
        strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_PRT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_PRT"];                     //�o�חp������i����p�j
			strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_PRT 	 	  	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].ADDYMD		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["ADDYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["ADDYMD"];                         //��\�o�^��
			strcpy(pRIRE_KSD01_DATA[iCol].ADDYMD 	 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].ADDTIM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["ADDTIM"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["ADDTIM"];                         //��\�o�^����
			strcpy(pRIRE_KSD01_DATA[iCol].ADDTIM 	 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].UPDYMD		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["UPDYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDYMD"];                         //��\�ύX��
			strcpy(pRIRE_KSD01_DATA[iCol].UPDYMD 	 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].UPDTIM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["UPDTIM"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDTIM"];                         //��\�ύX����
			strcpy(pRIRE_KSD01_DATA[iCol].UPDTIM 	 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["UPDCHR"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDCHR"];                         //��\�X�V��
			strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR 	 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].UPDCNT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["UPDCNT"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDCNT"];                         //��\�X�V��
			strcpy(pRIRE_KSD01_DATA[iCol].UPDCNT 	 			,sBuf.c_str());
		}
		Form1->Query4->Next();
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�FKSD22�ǂݍ��݁B
//
//  �@�\����
//    ���O�ɓǂݍ���KSM01���Q�Ƃ��đf�ޑ�����і��׃f�[�^��ǂݎ��B
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
void __fastcall TForm1::GET_RIRE_KSD22(void)
{
    AnsiString sBuf;
	//int iHINBAN;
//�o�בf�ޑ���̑��茋�ʂ̓ǂݍ���
	int iCol,iRow,i1,i2,i3;
    bool bFirstDate;
	AnsiString sLot,sLOTNO,sHINBAN,sKOMK_NO,sKOMK_NM,sDTKSHIN,sDTKSHIN_SZ,sHINBAN_SK;
    AnsiString sSOKU_VAL01,sSOKU_VAL02,sSOKU_VAL03,sSOKU_VAL04,sSOKU_VAL05 ;
    AnsiString sSOKU_VAL06,sSOKU_VAL07,sSOKU_VAL08,sSOKU_VAL09,sSOKU_VAL10 ;
	AnsiString sSKTYMD,sADDYMD,sADDTIM,sUPDYMD,sUPDTIM,sUPDCHR,sUPDCNT;
	int iLotChange;
//return;
	Form1->SGr_tRIRE->Refresh();
	sLot = "";

	for(iCol = 0; iCol < Form1->SGr_tRIRE->ColCount ; iCol++)
	{
        bFirstDate = true;
        //�f�ޗp���Ӑ�i�ԁA�o��
    	for(i1 = 0;i1 < 6; i1++)
		{
			switch( i1 )
			{
			case 0:
				sHINBAN		= pRIRE_KSD01_DATA[iCol].HINBAN1_SZ;
				sLOTNO 		= pRIRE_KSD01_DATA[iCol].LOTNO1_SZ;
				sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol].DTKSHIN1_SZ;
				sKOMK_NO 	= pRIRE_KSD01_DATA[iCol].KOMKNO1_SZ;
				sKOMK_NM 	= pRIRE_KSD01_DATA[iCol].KOMKNM1_SZ;
				iLotChange	= AnsiString(pRIRE_KSD01_DATA[iCol].LOTNOCHANGE1_SZ).ToIntDef(0);
                break;
			case 1:
				sHINBAN		= pRIRE_KSD01_DATA[iCol].HINBAN2_SZ;
				sLOTNO 		= pRIRE_KSD01_DATA[iCol].LOTNO2_SZ;
				sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol].DTKSHIN2_SZ;
				sKOMK_NO 	= pRIRE_KSD01_DATA[iCol].KOMKNO2_SZ;
				sKOMK_NM 	= pRIRE_KSD01_DATA[iCol].KOMKNM2_SZ;
				iLotChange	= AnsiString(pRIRE_KSD01_DATA[iCol].LOTNOCHANGE2_SZ).ToIntDef(0);
                break;
			case 2:
				sHINBAN		= pRIRE_KSD01_DATA[iCol].HINBAN3_SZ;
				sLOTNO 		= pRIRE_KSD01_DATA[iCol].LOTNO3_SZ;
				sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol].DTKSHIN3_SZ;
				sKOMK_NO 	= pRIRE_KSD01_DATA[iCol].KOMKNO3_SZ;
				sKOMK_NM 	= pRIRE_KSD01_DATA[iCol].KOMKNM3_SZ;
				iLotChange	= AnsiString(pRIRE_KSD01_DATA[iCol].LOTNOCHANGE3_SZ).ToIntDef(0);
                break;
			case 3:
				sHINBAN		= pRIRE_KSD01_DATA[iCol].HINBAN4_SZ;
				sLOTNO 		= pRIRE_KSD01_DATA[iCol].LOTNO4_SZ;
				sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol].DTKSHIN4_SZ;
				sKOMK_NO 	= pRIRE_KSD01_DATA[iCol].KOMKNO4_SZ;
				sKOMK_NM 	= pRIRE_KSD01_DATA[iCol].KOMKNM4_SZ;
				iLotChange	= AnsiString(pRIRE_KSD01_DATA[iCol].LOTNOCHANGE4_SZ).ToIntDef(0);
                break;
			case 4:
				sHINBAN		= pRIRE_KSD01_DATA[iCol].HINBAN5_SZ;
				sLOTNO	 	= pRIRE_KSD01_DATA[iCol].LOTNO5_SZ;
				sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol].DTKSHIN5_SZ;
				sKOMK_NO 	= pRIRE_KSD01_DATA[iCol].KOMKNO5_SZ;
				sKOMK_NM 	= pRIRE_KSD01_DATA[iCol].KOMKNM5_SZ;
				iLotChange	= AnsiString(pRIRE_KSD01_DATA[iCol].LOTNOCHANGE5_SZ).ToIntDef(0);
                break;
			case 5:
				sHINBAN		= pRIRE_KSD01_DATA[iCol].HINBAN6_SZ;
				sLOTNO 		= pRIRE_KSD01_DATA[iCol].LOTNO6_SZ;
				sDTKSHIN_SZ = pRIRE_KSD01_DATA[iCol].DTKSHIN6_SZ;
				sKOMK_NO 	= pRIRE_KSD01_DATA[iCol].KOMKNO6_SZ;
				sKOMK_NM 	= pRIRE_KSD01_DATA[iCol].KOMKNM6_SZ;
				iLotChange	= AnsiString(pRIRE_KSD01_DATA[iCol].LOTNOCHANGE6_SZ).ToIntDef(0);
                break;
			}
            if(sDTKSHIN_SZ.Length() == 0) break;
            if(bLOTCHANGE == true && iLotChange == 0) break;	//���b�g���蓖�ĉ�ʂŁu�ύX�v�������ꂽ���A
																//�ύX����Ă��Ȃ��ꍇ�͉��߂ăf�[�^�����[�h���Ȃ�
			sBuf  = "SELECT KSD22.LOTNO,KSD22.DTKSHIN,KSD22.HINBAN,KSD22.KOMK_NM,";
			sBuf += "KSD22.KOMK_NO,KSD22.SKTYMD,KSD22.ADDYMD,KSD22.ADDTIM,";
			sBuf += "KSD22.UPDYMD,KSD22.UPDTIM,KSD22.UPDCHR,KSD22.UPDCNT,";
			sBuf += "KSD22.SOKU_VAL01,KSD22.SOKU_VAL02,KSD22.SOKU_VAL03,";
			sBuf += "KSD22.SOKU_VAL04,KSD22.SOKU_VAL05,KSD22.SOKU_VAL06,";
			sBuf += "KSD22.SOKU_VAL07,KSD22.SOKU_VAL08,KSD22.SOKU_VAL09,";
            sBuf += "KSD22.SOKU_VAL10 ";

			sBuf += " FROM KSM02 INNER JOIN KSD22 ON (KSM02.KOMK_NO = KSD22.KOMK_NO)";
			sBuf += " AND (KSM02.HINBAN_SK = KSD22.DTKSHIN)";
			sBuf += " WHERE ((KSM02.DTKSHIN)='" + Form1->sNowDTKSHIN + "')";
			sBuf += " AND (KSM02.HINBAN_SK) = '" + sDTKSHIN_SZ + "'";
			sBuf += " AND ((KSM02.REVCNT)=0)";
			sBuf += " AND ((KSM02.SKB_NO)=1)";
			sBuf += " AND (KSD22.LOTNO) In ('" + sLOTNO + "')";
			sBuf += " AND (KSD22.HINBAN) = '" + sHINBAN + "'";
            sBuf += " GROUP BY KSD22.LOTNO,KSD22.DTKSHIN,KSD22.HINBAN,KSD22.KOMK_NM,";
			sBuf += "KSD22.KOMK_NO,KSD22.SKTYMD,KSD22.ADDYMD,KSD22.ADDTIM,";
			sBuf += "KSD22.UPDYMD,KSD22.UPDTIM,KSD22.UPDCHR,KSD22.UPDCNT,";
			sBuf += "KSD22.SOKU_VAL01,KSD22.SOKU_VAL02,KSD22.SOKU_VAL03,";
			sBuf += "KSD22.SOKU_VAL04,KSD22.SOKU_VAL05,KSD22.SOKU_VAL06,";
			sBuf += "KSD22.SOKU_VAL07,KSD22.SOKU_VAL08,KSD22.SOKU_VAL09,";
            sBuf += "KSD22.SOKU_VAL10";

			//For Debug
            if( iDEBUG == 1 )
            {
			    ClpBrd = Clipboard();
			    ClpBrd->Open();
    		    ClpBrd->SetTextBuf(sBuf.c_str());
    		    ClpBrd->Close();
            }
			// Initial Query
			Form1->Query4->Close();
    	    Form1->Query4->SQL->Clear();
        	Form1->Query4->SQL->Add(sBuf);
	        Form1->Query4->Open();
    	    Form1->Query4->Active = true;


	        while( Form1->Query4->Eof == false )
        	{
//������
	    	    if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN"]) != true)
				{
					sDTKSHIN			=  Form1->Query4->FieldValues["DTKSHIN"];
                }
	    	    if ( VarIsNull(Form1->Query4->FieldValues["KOMK_NM"]) != true)
				{
					sKOMK_NM			=  Form1->Query4->FieldValues["KOMK_NM"];
				}
	    	    if ( VarIsNull(Form1->Query4->FieldValues["KOMK_NO"]) != true)
				{
					sKOMK_NO			=  Form1->Query4->FieldValues["KOMK_NO"];
                }
	    	    if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD"]) != true)
				{
					sSKTYMD				=  Form1->Query4->FieldValues["SKTYMD"];
                }
				if ( VarIsNull(Form1->Query4->FieldValues["ADDYMD"]) != true)
				{
					sADDYMD				=  Form1->Query4->FieldValues["ADDYMD"];
                }
				if ( VarIsNull(Form1->Query4->FieldValues["ADDTIM"]) != true)
				{
					sADDTIM				=  Form1->Query4->FieldValues["ADDTIM"];
                }
				if ( VarIsNull(Form1->Query4->FieldValues["UPDYMD"]) != true)
				{
					sUPDYMD				=  Form1->Query4->FieldValues["UPDYMD"];
                }
				if ( VarIsNull(Form1->Query4->FieldValues["UPDTIM"]) != true)
				{
					sUPDTIM				=  Form1->Query4->FieldValues["UPDTIM"];
                }
				if ( VarIsNull(Form1->Query4->FieldValues["UPDCHR"]) != true)
				{
					sUPDCHR				=  Form1->Query4->FieldValues["UPDCHR"];
                }
				if ( VarIsNull(Form1->Query4->FieldValues["UPDCNT"]) != true)
				{
					sUPDCNT				=  Form1->Query4->FieldValues["UPDCNT"];
                }
                if(bFirstDate == true )
                {
    				strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ		,sSKTYMD.c_str());
	    			strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ_PRT	,sSKTYMD.c_str());
		    		strcpy(pRIRE_KSD01_DATA[iCol].ADDYMD		,sADDYMD.c_str());
			    	strcpy(pRIRE_KSD01_DATA[iCol].ADDTIM		,sADDTIM.c_str());
				    strcpy(pRIRE_KSD01_DATA[iCol].UPDYMD		,sUPDYMD.c_str());
    				strcpy(pRIRE_KSD01_DATA[iCol].UPDTIM		,sUPDTIM.c_str());
	    			strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR		,sUPDCHR.c_str());
		    		strcpy(pRIRE_KSD01_DATA[iCol].UPDCNT		,sUPDCNT.c_str());
                    bFirstDate = false;
                }
                else
                {
    				if(AnsiString(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ) < sSKTYMD)
                    {
    				    strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ		,sSKTYMD.c_str());
	    			    strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ_PRT	,sSKTYMD.c_str());
		    		    strcpy(pRIRE_KSD01_DATA[iCol].ADDYMD		,sADDYMD.c_str());
			    	    strcpy(pRIRE_KSD01_DATA[iCol].ADDTIM		,sADDTIM.c_str());
				        strcpy(pRIRE_KSD01_DATA[iCol].UPDYMD		,sUPDYMD.c_str());
    				    strcpy(pRIRE_KSD01_DATA[iCol].UPDTIM		,sUPDTIM.c_str());
	    			    strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR		,sUPDCHR.c_str());
		    		    strcpy(pRIRE_KSD01_DATA[iCol].UPDCNT		,sUPDCNT.c_str());
                    }
                }
				sLOTNO 				= "";
	        	sSOKU_VAL01 		= "";    		//�f�ޑ���l
    	        sSOKU_VAL02 		= "";    		//�f�ޑ���l
        	    sSOKU_VAL03 		= "";    		//�f�ޑ���l
            	sSOKU_VAL04 		= "";    		//�f�ޑ���l
	            sSOKU_VAL05 		= "";    		//�f�ޑ���l
    	        sSOKU_VAL06 		= "";    		//�f�ޑ���l
        	    sSOKU_VAL07 		= "";    		//�f�ޑ���l
            	sSOKU_VAL08 		= "";    		//�f�ޑ���l
	            sSOKU_VAL09 		= "";    		//�f�ޑ���l
    	        sSOKU_VAL10 		= "";    		//�f�ޑ���l
				sLOTNO 				= Form1->Query4->FieldValues["LOTNO"];
	        	sSOKU_VAL01 		= Form1->Query4->FieldValues["SOKU_VAL01"];    		//�f�ޑ���l
    	        sSOKU_VAL02 		= Form1->Query4->FieldValues["SOKU_VAL02"];    		//�f�ޑ���l
        	    sSOKU_VAL03 		= Form1->Query4->FieldValues["SOKU_VAL03"];    		//�f�ޑ���l
            	sSOKU_VAL04 		= Form1->Query4->FieldValues["SOKU_VAL04"];    		//�f�ޑ���l
	            sSOKU_VAL05 		= Form1->Query4->FieldValues["SOKU_VAL05"];    		//�f�ޑ���l
    	        sSOKU_VAL06 		= Form1->Query4->FieldValues["SOKU_VAL06"];    		//�f�ޑ���l
        	    sSOKU_VAL07 		= Form1->Query4->FieldValues["SOKU_VAL07"];    		//�f�ޑ���l
            	sSOKU_VAL08 		= Form1->Query4->FieldValues["SOKU_VAL08"];    		//�f�ޑ���l
	            sSOKU_VAL09 		= Form1->Query4->FieldValues["SOKU_VAL09"];    		//�f�ޑ���l
    	        sSOKU_VAL10 		= Form1->Query4->FieldValues["SOKU_VAL10"];    		//�f�ޑ���l
				iRow = 1;																//�O�s�ڂ͓��t
				for( i3 = 0 ; i3 < iSOZAI_ORCNT ; i3++)
				{
					if((AnsiString(pSOZAI_OR_DATA[ i3 ].KOMK_NO) 	== sKOMK_NO)
					&&(AnsiString(pSOZAI_OR_DATA[ i3 ].HINBAN_SK) == sDTKSHIN))
					{
                		for(i2 = 0 ; i2 < AnsiString(pSOZAI_OR_DATA[ i3 ].SOKU_SU).ToIntDef(0); i2++)
						{
                			switch( i2 )
                			{
							case 0:
								Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] =  sSOKU_VAL01;
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].RESULT			, sSOKU_VAL01.c_str());
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL01.c_str());
								break;
							case 1:
								Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] =  sSOKU_VAL02;
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].RESULT			, sSOKU_VAL02.c_str());
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL02.c_str());
								break;
							case 2:
								Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] =  sSOKU_VAL03;
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL03.c_str());
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL03.c_str());
								break;
							case 3:
								Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] =  sSOKU_VAL04;
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL04.c_str());
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL04.c_str());
								break;
							case 4:
 								Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] =  sSOKU_VAL05;
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL05.c_str());
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL05.c_str());
								break;
							case 5:
								Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] =  sSOKU_VAL06;
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL06.c_str());
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL06.c_str());
								break;
							case 6:
								Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] =  sSOKU_VAL07;
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL07.c_str());
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL07.c_str());
								break;
							case 7:
								Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] =  sSOKU_VAL08;
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL08.c_str());
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL08.c_str());
								break;
							case 8:
								Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] =  sSOKU_VAL09;
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL09.c_str());
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL09.c_str());
								break;
							case 9:
								Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] =  sSOKU_VAL10;
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL10.c_str());
								strcpy(pCELLINFO_RIRE_SOZAI[(iCol * Form1->SGr_vRIRE_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL10.c_str());
								break;
							}
						}
						break;
					}
					else
					{
						iRow += AnsiString(pSOZAI_OR_DATA[ i3 ].SOKU_SU).ToIntDef(0);
					}
				}
            	Form1->Query4->Next();
			}
 		}
		iRow += AnsiString(pSOZAI_OR_DATA[ i1 ].SOKU_SU).ToIntDef(0);
        Form1->Query4->Close();
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ށi�����j�O���b�h��ɒl���o�͂��܂��B
//
//  �@�\����
//    CELLINFO���Q�Ƃ��f�[�^���o�͂��܂��B
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
void __fastcall TForm1::PUT_SOZAIRIRE_KSD02_DISP(void)
{
	AnsiString sLot;
	//int i1,i2,i3,i4;
	int iCol,iRow;
	int iRowCount;
	iRowCount = Form1->SGr_vRIRE_SOZAI->RowCount;
	for(iCol = 0; iCol < Form1->SGr_vRIRE_SOZAI->ColCount;iCol++)
    {
		for(iRow = 1;iRow < Form1->SGr_vRIRE_SOZAI->RowCount ;iRow++)
		{
			Form1->SGr_vRIRE_SOZAI->Cells[iCol][iRow] = pCELLINFO_RIRE_SOZAI[(iCol * iRowCount) + iRow].RESULT;
		}
    }
	Form1->SGr_vRIRE_SYUKA->Refresh();
}


//�V���N���i�C�Y�����邽�ߒu���܂���
void __fastcall TForm1::GET_SOZAIRIRE_KSD02(void)
{

	AnsiString sBuf;
	AnsiString sSOZAI_RIRE_LOT,sTempLot;
	sBuf = "SELECT *  FROM KSD02";
return;

}

