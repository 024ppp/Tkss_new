//---------------------------------------------------------------------------
//
//  Thread.cpp
//    �y�o�׌����V�X�e���|�o�ח���ǂݎ��z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �s��@�a�O
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include "Thread.h"
#include "Tkss01.h"
#include "Unit1.h"
#pragma package(smart_init)

extern 	iContCnt;
// k.y 2003.05.17
//extern	HANDLE hORDATA;

// k.y 2003.05.17
//extern 	KSM02_DATA *pORDATA;
extern 	KSM02_DATA pORDATA[100];

// k.y 2003.05.17
//extern	HANDLE hRIREKI_DATA;
// k.y 2003.05.17
//extern	KSD02_DATA *pRIREKI_DATA;         // �ߋ������f�[�^
extern	KSD02_DATA pRIREKI_DATA[100];

extern	HANDLE hCELLINFO_RIRE_SYUKA;
extern 	CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;

extern HANDLE 		hRIRE_KSD01_DATA;
extern KSD01_DATA 	*pRIRE_KSD01_DATA;

//---------------------------------------------------------------------------
// ���ӁF�قȂ�X���b�h�����L���� VCL �̃��\�b�h/�֐�/�v���p�e�B��
//       �ʂ̃X���b�h�̒����爵���ꍇ�C�r�������̖�肪�������܂��B
//
//       ���C���X���b�h�̏��L����I�u�W�F�N�g�ɑ΂��Ă� Synchronize
//       ���\�b�h���g�������ł��܂��B���̃I�u�W�F�N�g���Q�Ƃ��邽��
//       �̃��\�b�h���X���b�h�N���X�ɒǉ����CSynchronize ���\�b�h��
//       �����Ƃ��ēn���܂��B
//
//       ���Ƃ��� UpdateCaption ���ȉ��̂悤�ɒ�`���A
//
//          void __fastcall MyThread::UpdateCaption()
//          {
//            Form1->Caption = "�X���b�h���珑�������܂���";
//          }
//
//       Execute ���\�b�h�̒��� Synchronize ���\�b�h�ɓn�����ƂŃ��C
//       ���X���b�h�����L���� Form1 �� Caption �v���p�e�B�����S�ɕ�
//       �X�ł��܂��B
//
//          Synchronize(UpdateCaption);
//
//---------------------------------------------------------------------------
/* k.k 2003.05.17 DELETE
__fastcall ThreadRIRE_SYUKA::ThreadRIRE_SYUKA(bool CreateSuspended)
	: TThread(CreateSuspended)
{
  Priority = tpIdle;
}
//---------------------------------------------------------------------------
//�X���b�h�o�ח���ǂݏo��
void __fastcall ThreadRIRE_SYUKA::Execute()
{
//	Synchronize(GET_RIRE_SYUKA);
	GET_RIRE_SYUKA();
	if( Terminated ) return;
}
*/
//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�o�ח����̃f�[�^�ǂݍ��ݑS�ʂ��s���܂��B
//
//  �@�\����
//    KSD02���Q�Ƃ��Z���C���t�H�ɑ�����܂��B
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
void __fastcall TForm1::GET_RIRE_SYUKA(void)
{
    int i1,i2,i3,i4;
    AnsiString sBuf,sTempLot,sRIRE_LOT;
    int iRireCnt;
    //int iColCnt;
    //int iCol,iRow;
	double dMAX,dMIN;//,dSWAP;
	int iRowCount,iColCount;
    //int nDRAW_GRID;
    //int nKENSAKU_KEY,nGridX,nGridY;

    iRireCnt = 0;
	//iColCnt = 0;
	//iCol = 0;
	//iRow = 0;
	iRireCnt = Form1->iRIRE_CNT;
 	GET_KSD01();


    //iColCnt = i1;
	Form1->SGr_tRIRE		->ColCount	= iRireCnt;
    Form1->SGr_vRIRE_SYUKA	->ColCount 	= iRireCnt;
    Form1->SGr_vRIRE_SOZAI	->ColCount 	= iRireCnt;


//	�������b�g�̕`��
	for( i1 = 0;i1 < Form1->iRIRE_CNT ; i1++)
	{
		Form1->SGr_tRIRE->Cells[i1][0] = Form1->sRIREKI_LOT->Strings[i1];
	}

//�Z����񃁃����ݒ�(�o�ח����j

	iRowCount = Form1->SGr_vRIRE_SYUKA->RowCount;
	iColCount = Form1->SGr_vRIRE_SYUKA->ColCount;


    //�����l���
    //KOMK_NO�ɂO�����邱�ƂŊD�F�\�����������܂��B
	for(i1=0;i1 < iColCount ;i1++)
    {
    	dMAX = 0;
        dMIN = 0;
        i4 = 1;
        for(i2=0 ; i2 < Form1->iOrCount ; i2++)
        {
        	Form1->GetKIKAKU(i2, &dMAX, &dMIN);
            for(i3=0 ; i3 < AnsiString(pORDATA[i2].SOKU_SU).ToIntDef(0);i3++)
			{
	        	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].DTKSHIN 		, pORDATA[ i2 ].DTKSHIN);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].LOTNO 		, Form1->SGr_tRIRE->Cells[i1][0].c_str());
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].UNQ_NO 		, pORDATA[ i2 ].UNQ_NO);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].ORDER_NO		, pORDATA[ i2 ].ORDER_NO);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].SKB_NO 		, pORDATA[ i2 ].SKB_NO);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].HINBAN_SK	, pORDATA[ i2 ].HINBAN_SK);
        	    //strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KOMK_NO 		, pORDATA[ i2 ].KOMK_NO);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KOMK_NO 		, AnsiString("-999").c_str());
        	    pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].INS_ON = false;
        		strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KOMK_NM 		, pORDATA[ i2 ].KOMK_NM);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KOMK_ENG		, pORDATA[ i2 ].KOMK_ENG);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KOMK_SUB		, pORDATA[ i2 ].KOMK_SUB);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KOMK_SUB_ENG , pORDATA[ i2 ].KOMK_SUB_ENG);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKI_NO 		, pORDATA[ i2 ].KIKI_NO);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKI_NM 		, pORDATA[ i2 ].KIKI_NM);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].TANI    		, pORDATA[ i2 ].TANI);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_TYPE	, pORDATA[ i2 ].KIKA_TYPE);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_KIND	, pORDATA[ i2 ].KIKA_KIND);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_DECI	, pORDATA[ i2 ].KIKA_DECI);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_NUM1	, pORDATA[ i2 ].KIKA_NUM1);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_NUM2	, pORDATA[ i2 ].KIKA_NUM2);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_NUM3	, pORDATA[ i2 ].KIKA_NUM3);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_STR		, pORDATA[ i2 ].KIKA_STR);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_SUB1	, pORDATA[ i2 ].KIKA_SUB1);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_SUB2	, pORDATA[ i2 ].KIKA_SUB2);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_SUB3	, pORDATA[ i2 ].KIKA_SUB3);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].SOKU_SU 		, pORDATA[ i2 ].SOKU_SU);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].SOKU_FLG		, pORDATA[ i2 ].SOKU_FLG);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].TOKU_FLG		, pORDATA[ i2 ].TOKU_FLG);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_PRT		, pORDATA[ i2 ].KIKA_PRT);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].VALUE_TYPE	, pORDATA[ i2 ].VALUE_TYPE);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].VALUE_DECI	, pORDATA[ i2 ].VALUE_DECI);
				//strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].RESULT,"�s�v");
	        	//strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].DISP_RESULT,"�s�v");
				strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].RESULT,"");
	        	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].DISP_RESULT,"");
    	    	pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].JUDGE = 2;
        	    pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].MAX = dMAX ;
            	pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].MIN = dMIN ;
        	    pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].GMAX = dMAX ;
            	pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].GMIN = dMIN ;
	            i4++;
			}
        }
    }
                                         

//�������b�g�̎��ѓǂݎ��
	Form1->Set_RIRE_SYUKAJISSEKI();
	for(i1=0;i1 < iColCount ;i1++)
    {
    	dMAX = 0;
        dMIN = 0;
        i4 = 1;
        //�w���������ő匏���Ƃ���Ă��Č�X�s��������邽�߁AORDATA�Ŏw���������㏑�����܂�
        for(i2=0 ; i2 < Form1->iOrCount ; i2++)
        {
            for(i3=0 ; i3 < AnsiString(pORDATA[i2].SOKU_SU).ToIntDef(0);i3++)
			{
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].SOKU_SU 		, pORDATA[ i2 ].SOKU_SU);
	            i4++;
			}
        }
    }
    //�f�[�^�̓ǂݍ��݂��I�������̂Ńf�[�^���Z����ɕ`�悵�܂��B
	for( i1 = 0; i1 < iColCount ; i1++)
    {
		for(i2= 1; i2 <  iRowCount ; i2++)
        {
        	Form1->SGr_vRIRE_SYUKA->Cells[i1][i2] = pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i2].RESULT;
		}
    }

//    Synchronize(Form1->Set_RIREMEMO);		//�����̕\��
    Form1->Set_RIREMEMO();		//�����̕\��
//    Synchronize(Form1->Get_KSD91_RIREKI);
    Form1->Get_KSD91_RIREKI();

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F������уf�[�^�̓ǂݍ��݁B
//
//  �@�\����
//    �������b�g���Q�Ƃ��AKSD01���e���b�g�̃������֑�����܂�
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
//�������b�g�̑�����уf�[�^���擾����
void __fastcall TForm1::GET_KSD01(void)
{
	int iCol;
	AnsiString sBuf,sLot,DTKSHIN;
	// �������̊J��
    if( hRIRE_KSD01_DATA ){
    	GlobalUnlock( hRIRE_KSD01_DATA );
        GlobalFree( hRIRE_KSD01_DATA );
    }
// k.y 2003.05.17
    //hRIREKI_DATA = NULL;
    // �������̊m��
    //hRIRE_KSD01_DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * Form1->SGr_tRIRE->ColCount+1 );

    // 2003/06/02 K.Yamada �T�C�Y�v�Z�~�X�̈׏C��
    //hRIRE_KSD01_DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * Form1->iRIRE_CNT+1 );
    hRIRE_KSD01_DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * (Form1->iRIRE_CNT+1) );
    if( hRIRE_KSD01_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(�����f�[�^01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pRIRE_KSD01_DATA = (struct KSD01_DATA *)GlobalLock(hRIRE_KSD01_DATA);
    if( hRIRE_KSD01_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(�����f�[�^02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    sLot = "";
   for(iCol=0;iCol < Form1->iRIRE_CNT ;iCol++ )
    {
        if(Form1->sRIREKI_LOT->Strings[iCol].Length()!=0)
        {
            sLot += "'" + Form1->sRIREKI_LOT->Strings[iCol] + "',";
        }
    }
	sLot = sLot.SubString(1,sLot.Length()-1);
	if( sLot.Length()<3 ) return;
	//2003.05.12 E.Takase Add��
    sBuf = "SELECT * FROM KSD01 WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";
	//2003.05.12 E.Takase Add��
    sBuf += " AND LOTNO IN (" + sLot + ")";
	sBuf += " ORDER BY LOTNO";

	// Initial Query
    Form1->Query2->Close();
    Form1->Query2->SQL->Clear();
    Form1->Query2->SQL->Add(sBuf);
    Form1->Query2->Open();
    Form1->Query2->Active = true;
	while(Form1->Query2->Eof == false)
	{
    	sBuf	= Form1->Query2->FieldValues["LOTNO"];
   		for(iCol=0;iCol < Form1->iRIRE_CNT ; iCol++)
		{
        	if( Form1->SGr_tRIRE->Cells[iCol][0]==sBuf) break;
		}
    //���Ӑ�i��
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN,sBuf.c_str());
		}
    //���b�gNO
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO,sBuf.c_str());
		}
    //�f�ޗp���b�gNo1
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO1_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO1_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO1_SZ,sBuf.c_str());
		}
    //�f�ޗp���b�gNo2
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO2_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO2_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO2_SZ,sBuf.c_str());
		}
    //�f�ޗp���b�gNo3
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO3_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO3_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO3_SZ,sBuf.c_str());
		}
    //�f�ޗp���b�gNo4
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO4_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO4_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO4_SZ,sBuf.c_str());
		}
    //�f�ޗp���b�gNo5
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO5_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO5_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO5_SZ,sBuf.c_str());
		}
    //�f�ޗp���b�gNo6
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO6_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO6_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO6_SZ,sBuf.c_str());
		}
    //���Еi��
		if(VarIsNull(Form1->Query2->FieldValues["HINBAN"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["HINBAN"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].HINBAN,sBuf.c_str());
		}
    //���Ӑ�R�[�h
		if(VarIsNull(Form1->Query2->FieldValues["DTKSCOD"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSCOD"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSCOD,sBuf.c_str());
		}
    //���Ӑ於��
		if(VarIsNull(Form1->Query2->FieldValues["DTKSNAM"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSNAM"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSNAM,sBuf.c_str());
		}
    //�ގ����́i�i��j
		if(VarIsNull(Form1->Query2->FieldValues["ZISNAM"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["ZISNAM"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].ZISNAM,sBuf.c_str());
		}
    //�i��
		if(VarIsNull(Form1->Query2->FieldValues["HINMEI"])!=true)
        {
    		sBuf	= Form1->Query2->FieldValues["HINMEI"];
	        strcpy(pRIRE_KSD01_DATA[iCol].HINMEI,sBuf.c_str());
		}
    //�f�ޗp���Ӑ�i�ԂP
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN1_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN1_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN1_SZ,sBuf.c_str());
		}
    //�f�ޗp���Ӑ�i�ԂQ
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN2_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN2_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN2_SZ,sBuf.c_str());
		}
    //�f�ޗp���Ӑ�i�ԂR
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN3_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN3_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN3_SZ,sBuf.c_str());
		}
    //�f�ޗp���Ӑ�i�ԂS
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN4_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN4_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN4_SZ,sBuf.c_str());
		}
    //�f�ޗp���Ӑ�i�ԂT
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN5_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN5_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN5_SZ,sBuf.c_str());
		}
    //�f�ޗp���Ӑ�i�ԂU
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN6_SZ"])!=true)
        {
    		sBuf	= Form1->Query2->FieldValues["DTKSHIN6_SZ"];
	        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN6_SZ,sBuf.c_str());
		}
    //�f�ޗp���b�g�̃����N
		if(VarIsNull(Form1->Query2->FieldValues["LOT_LINK_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOT_LINK_SZ"];
	        strcpy(pRIRE_KSD01_DATA[iCol].LOT_LINK_SZ,sBuf.c_str());
		}
    //���荀�ڐ�
		if(VarIsNull(Form1->Query2->FieldValues["SOKUTEI_NUM"])!=true)
        {
    		sBuf	= Form1->Query2->FieldValues["SOKUTEI_NUM"];
	        strcpy(pRIRE_KSD01_DATA[iCol].SOKUTEI_NUM,sBuf.c_str());
		}
    //�f�ޔ���
		if(VarIsNull(Form1->Query2->FieldValues["SOZAI_OK"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["SOZAI_OK"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK,sBuf.c_str());
		}
    //�f�ޔ������p
		if(VarIsNull(Form1->Query2->FieldValues["SOZAI_OK_PRT"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["SOZAI_OK_PRT"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK_PRT,sBuf.c_str());
		}
    //�o�ה���
		if(VarIsNull(Form1->Query2->FieldValues["SYUKA_OK"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["SYUKA_OK"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK,sBuf.c_str());
		}
    //�o�ה������p
		if(VarIsNull(Form1->Query2->FieldValues["SYUKA_OK_PRT"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["SYUKA_OK_PRT"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK_PRT,sBuf.c_str());
		}
    //���я��^�C�g���o�͍��ڂP
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE1"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE1"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE1,sBuf.c_str());
		}
    //���я��^�C�g���o�͍��ڂQ
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE2"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE2"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE2,sBuf.c_str());
		}
    //���я��^�C�g���o�͍��ڂR
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE3"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE3"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE3,sBuf.c_str());
		}
    //���я��^�C�g���o�͍��ڂS
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE4"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE4"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE4,sBuf.c_str());
		}
    //���я��^�C�g���o�͍��ڂT
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE5"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE5"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE5,sBuf.c_str());
		}
    //���я��^�C�g���o�͍��ڂU
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE6"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE6"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE6,sBuf.c_str());
		}
    //���я��^�C�g���o�͍��ڂV
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE7"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE7"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE7,sBuf.c_str());
		}
    //���я��^�C�g���o�͍��ڂW
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE8"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE8"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE8,sBuf.c_str());
		}
    //�w�o�[�̏o��
		if(VarIsNull(Form1->Query2->FieldValues["X_OUT"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["X_OUT"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].X_OUT,sBuf.c_str());
		}
    //���l
		if(VarIsNull(Form1->Query2->FieldValues["MEMO"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["MEMO"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].MEMO,sBuf.c_str());
		}
    //���蒆�Ȃ�{���ɓ��t��ύX����
        if(AnsiString(pRIRE_KSD01_DATA[iCol].SOZAI_OK).ToIntDef(0) == -1 )
        {
            strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ,FormatDateTime("yyyymmdd",Date()).c_str());
            strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ_PRT,FormatDateTime("yyyymmdd",Date()).c_str());
        }
        else
        {
        //�f�ޗp�����
	    	if(VarIsNull(Form1->Query2->FieldValues["SKTYMD_SZ"])!=true)
            {
	    	    sBuf	= Form1->Query2->FieldValues["SKTYMD_SZ"];
        	    strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ,sBuf.c_str());
	    	}
        //�f�ޗp������i����p�j
	    	if(VarIsNull(Form1->Query2->FieldValues["SKTYMD_SZ_PRT"])!=true)
            {
	    	    sBuf	= Form1->Query2->FieldValues["SKTYMD_SZ_PRT"];
        	    strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ_PRT,sBuf.c_str());
	    	}
        }
    //���蒆�Ȃ�{���ɓ��t��ύX����
        if(AnsiString(pRIRE_KSD01_DATA[iCol].SYUKA_OK).ToIntDef(0) == -1 )
        {
            strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD,FormatDateTime("yyyymmdd",Date()).c_str());
            strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_PRT,FormatDateTime("yyyymmdd",Date()).c_str());
        }
        else
        {
        //�o�חp�����
	    	if(VarIsNull(Form1->Query2->FieldValues["SKTYMD"])!=true)
            {
	    	    sBuf	= Form1->Query2->FieldValues["SKTYMD"];
        	    strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD,sBuf.c_str());
	    	}
        //�o�חp������i����p�j
	    	if(VarIsNull(Form1->Query2->FieldValues["SKTYMD_PRT"])!=true)
            {
	    	    sBuf	= Form1->Query2->FieldValues["SKTYMD_PRT"];
        	    strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_PRT,sBuf.c_str());
	    	}
        }
    //��\�o�^��
		if(VarIsNull(Form1->Query2->FieldValues["ADDYMD"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["ADDYMD"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].ADDYMD,sBuf.c_str());
		}
    //��\�o�^����
		if(VarIsNull(Form1->Query2->FieldValues["ADDTIM"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["ADDTIM"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].ADDTIM,sBuf.c_str());
		}
    //��\�ύX��
		if(VarIsNull(Form1->Query2->FieldValues["UPDYMD"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["UPDYMD"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].UPDYMD,sBuf.c_str());
		}
    //��\�ύX����
		if(VarIsNull(Form1->Query2->FieldValues["UPDTIM"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["UPDTIM"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].UPDTIM,sBuf.c_str());
		}
    //��\�X�V��
		if(VarIsNull(Form1->Query2->FieldValues["UPDCHR"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["UPDCHR"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR,sBuf.c_str());
		}
    //��\�X�V��
		if(VarIsNull(Form1->Query2->FieldValues["UPDCNT"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["UPDCNT"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].UPDCNT,sBuf.c_str());
		}
        pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
        pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
//���̃��R�[�h
		Form1->Query2->Next();
	}
    Form1->Query2->Close();
}

