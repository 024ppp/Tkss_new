//---------------------------------------------------------------------------
//
//  ThreadSozaiSyuka.cpp
//    �y�o�׌����V�X�e���|�f�ށi�o�ׁj�f�[�^�ǂݎ��z
//    ���C���t�H�[���iTForm1�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �s��@�a�O
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "ThreadSozaiSyka.h"
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

extern HANDLE hCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;

extern int iSOZAI_KOMKCNT;
extern int iSOZAI_CONT_CONT;
extern int iSOZAI_RIRE_LOT;
extern int iSOZAI_ORCNT;
extern int iSOZAI_SOKUCNT;													//�\�[�g���g�p����d�݌v�Z�p�o�b�t�@
extern int iSOZAI_SYKA_KOMKCNT;

int nKENSAKU_KEY,nCOMP_KEY;
int iColCount,iRowCount;
extern int iSOZAI_RireCnt,iSOZAI_SyukaCnt,iSOZAI_SokuCnt,iSOZAI_ContCnt,iSOZAI_KikiCnt;

extern int iSOZAI_ORCNT;

// k.y 2005.05.17
//extern HANDLE 		hKSM01_DATA;
// k.y 2003.05.17
//extern KSM01_DATA 	*pKSM01_DATA;
extern KSM01_DATA 	pKSM01_DATA;
//���b�g���蓖�ėp�i�o�׌����j
extern HANDLE hSOKU_KSD01_DATA;
extern KSD01_DATA *pSOKU_KSD01_DATA;
extern bool bLOTCHANGE;						//���b�g���蓖�ĉ�ʂƂ̒ʐM�p�t���O
AnsiString USER_NAME,CHR_CODE;

// k.y 2003.06.03
extern int iDEBUG;

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ށi�o�ׁj������ʗp�f�[�^�ǂݎ��A�\���B
//
//  �@�\����
//    OR�e�[�u�����Q�Ƃ�CELLINFO�ɒl�����A�\�����s���܂��B
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
void __fastcall TForm1::SetSYKA_Sozai(void)
{
	AnsiString sBuf,sLot;
    //int nDRAW_GRID;
    //int nKENSAKU_KEY
    //int nCOMP_KEY;
	int iColCount,iRowCount;
    //nDRAW_GRID = 1;
	int i1,i2,i3,i4; //i5;
	//int iCol,iRow;
    int nDRAW_GRID;
	double dMAX,dMIN;//dSWAP;
    //�o�׌����̃O���b�h�����ׂĊD�F�ɂ���
    Form1->SGr_vSOKU_SOZAI->Refresh();

	iColCount = Form1->SGr_vSOKU_SOZAI->ColCount;
	iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;


	if(bNowF7 == true)      //�����L�[�ł̌�����
    {
	    // �������̊J��
    	if( hCELLINFO_SOKU_SOZAI ){
    		GlobalUnlock( hCELLINFO_SOKU_SOZAI );
	        GlobalFree( hCELLINFO_SOKU_SOZAI );
    	}
        hCELLINFO_SOKU_SOZAI = NULL;
	    // �������̊m��
    	hCELLINFO_SOKU_SOZAI = GlobalAlloc( GHND, sizeof(struct CELLINFO_DATA) * ((iColCount+1) * iRowCount));
	    if( hCELLINFO_SOKU_SOZAI == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(�o�ח����Z��01)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    	pCELLINFO_SOKU_SOZAI = (struct CELLINFO_DATA *)GlobalLock(hCELLINFO_SOKU_SOZAI);
	    if( hCELLINFO_SOKU_SOZAI == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(�o�ח����Z��02)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    }


	if( !hSOKU_KSD01_DATA && bNowF7 == true )
    {
	    // �������̊J��
    	if( hSOKU_KSD01_DATA ){
    		GlobalUnlock( hSOKU_KSD01_DATA );
	        GlobalFree( hSOKU_KSD01_DATA );
    	}
        hSOKU_KSD01_DATA = NULL;
	    // �������̊m��
    	hSOKU_KSD01_DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * (iColCount+1));
	    if( hSOKU_KSD01_DATA == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(�o�ח����Z��01)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    	pSOKU_KSD01_DATA = (struct KSD01_DATA *)GlobalLock(hSOKU_KSD01_DATA);
	    if( hSOKU_KSD01_DATA == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(�o�ח����Z��02)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    	SET_KSD01();
    }


    if(!hCELLINFO_SOKU_SOZAI) return;

	if( bNowF7 == true  )
    {
		for( i1 = 0; i1 < Form1->SGr_vSOKU_SOZAI->ColCount ; i1++)
    	{
			for(i2= 1; i2 <  Form1->SGr_vSOKU_SOZAI->RowCount ; i2++)
	        {

        	    Form1->SGr_vSOKU_SOZAI->Cells[i1][i2]="";
        		strcpy(pCELLINFO_SOKU_SOZAI[i1*Form1->SGr_vSOKU_SOZAI->RowCount+i2].RESULT,"");
	        	strcpy(pCELLINFO_SOKU_SOZAI[i1*Form1->SGr_vSOKU_SOZAI->RowCount+i2].DISP_RESULT,"");
                //strcpy(pCELLINFO_SOKU_SOZAI[i1*Form1->SGr_vSOKU_SOZAI->RowCount+i2].KOMK_NO,"-999");
    	        pCELLINFO_SOKU_SOZAI[i1*Form1->SGr_vSOKU_SOZAI->RowCount+i2].JUDGE = 2;
        	}
		}
    }

    //���i�K�i���ׂ̊e�Z�����ւ̃R�s�[
	if( bNowF7 == true  &&  bNowLotF7 == false )       //�����L�[�Ō������Ȃ̂ŁA�Z���C���t�H�����l���
    {
    	for(i1 = 0; i1 < iColCount ;i1++)
	    {
    	    i4 = 1;
    		for(i2=0 ; i2 < iSOZAI_ContCnt ; i2++)
	    	{
            	GetSOZAI_KIKAKU(i2,&dMAX,&dMIN);
			    for(i3=0;i3 < AnsiString(pSOZAI_OR_DATA[i2].SOKU_SU).ToIntDef(0);i3++)
    			{
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].DTKSHIN 		, pSOZAI_OR_DATA[ i2 ].DTKSHIN);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].LOTNO 		, Form1->SGr_tSOKU->Cells[i1][0].c_str());
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].HINBAN 		, Form1->SGr_tSOKU->Cells[i1][1].c_str());
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].UNQ_NO 		, pSOZAI_OR_DATA[ i2 ].UNQ_NO);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].ORDER_NO		, pSOZAI_OR_DATA[ i2 ].ORDER_NO);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].SKB_NO 		, pSOZAI_OR_DATA[ i2 ].SKB_NO);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].HINBAN_SK	, pSOZAI_OR_DATA[ i2 ].HINBAN_SK);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KOMK_NO 		, pSOZAI_OR_DATA[ i2 ].KOMK_NO);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KOMK_NO 		, "-999");
					pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].INS_ON = false;
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KOMK_NM 		, pSOZAI_OR_DATA[ i2 ].KOMK_NM);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KOMK_ENG		, pSOZAI_OR_DATA[ i2 ].KOMK_ENG);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KOMK_SUB		, pSOZAI_OR_DATA[ i2 ].KOMK_SUB);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KOMK_SUB_ENG , pSOZAI_OR_DATA[ i2 ].KOMK_SUB_ENG);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKI_NO 		, pSOZAI_OR_DATA[ i2 ].KIKI_NO);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKI_NM 		, pSOZAI_OR_DATA[ i2 ].KIKI_NM);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].TANI    		, pSOZAI_OR_DATA[ i2 ].TANI);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKA_TYPE	, pSOZAI_OR_DATA[ i2 ].KIKA_TYPE);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKA_KIND	, pSOZAI_OR_DATA[ i2 ].KIKA_KIND);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKA_DECI	, pSOZAI_OR_DATA[ i2 ].KIKA_DECI);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKA_NUM1	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM1);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKA_NUM2	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM2);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKA_NUM3	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM3);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKA_STR		, pSOZAI_OR_DATA[ i2 ].KIKA_STR);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKA_SUB1	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB1);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKA_SUB2	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB2);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKA_SUB3	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB3);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].SOKU_SU 		, pSOZAI_OR_DATA[ i2 ].SOKU_SU);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].SOKU_FLG		, pSOZAI_OR_DATA[ i2 ].SOKU_FLG);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].TOKU_FLG		, pSOZAI_OR_DATA[ i2 ].TOKU_FLG);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].KIKA_PRT		, pSOZAI_OR_DATA[ i2 ].KIKA_PRT);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].VALUE_TYPE	, pSOZAI_OR_DATA[ i2 ].VALUE_TYPE);
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].VALUE_DECI	, pSOZAI_OR_DATA[ i2 ].VALUE_DECI);
				    // �����
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].SKTYMD		,FormatDateTime("yyyymmdd",Date()).c_str());
				    // �o�^��
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].ADDYMD		,FormatDateTime("yyyymmdd",Date()).c_str());
				    // �o�^����
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].ADDTIM		,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
				    // �ύX��
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].UPDYMD		,FormatDateTime("yyyymmdd",Date()).c_str());
				    // �ύX����
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].UPDTIM		,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].UPDCHR		,pSOKU_KSD01_DATA[i1].UPDCHR);

					//2003.05.17 E.Takase Add��
                    strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].UPDNAME 		, pSOKU_KSD01_DATA[i1].UPDNAME);
					//2003.05.17 E.Takase Add��

				    // �K�i
                	pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].MAX = dMAX ;
                    pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].MIN = dMIN ;
                	pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].GMAX = dMAX ;
                    pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].GMIN = dMIN ;
					i4++;
	    		}
		    }
        }
        //�o�׌����\��̍��ڂ̔�����
    	for( i4 = 0; i4 < SGr_vSOKU_SOZAI->ColCount ; i4++)
        {
    	    for(i1 = 0; i1 < iSOZAI_SYKA_KOMKCNT;i1++)
    		{
        		nDRAW_GRID = 1;
		    	{
			    	for( i2 = 0; i2 < iSOZAI_ContCnt ; i2++)
				    {
                        //OR�e�[�u���̌��݂̋@��NO�ƍ���NO�𒊏o
     					if((AnsiString(pSOZAI_SYKA_DATA[i1].KIKI_NO).ToIntDef(0)    == AnsiString(pSOZAI_OR_DATA[i2].KIKI_NO).ToIntDef(0))
	    				&& (AnsiString(pSOZAI_SYKA_DATA[i1].KOMK_NM).Trim() 		== AnsiString(pSOZAI_OR_DATA[i2].KOMK_NM).Trim())
                        && (AnsiString(pSOZAI_SYKA_DATA[i1].KOMK_SUB).Trim() 	    == AnsiString(pSOZAI_OR_DATA[i2].KOMK_SUB).Trim())
                        && (AnsiString(pSOZAI_SYKA_DATA[i1].KOMK_NO).ToIntDef(0) 	== AnsiString(pSOZAI_OR_DATA[i2].KOMK_NO).ToIntDef(0))
                        && (AnsiString(pSOZAI_SYKA_DATA[i1].HINBAN_SK).Trim() 	    == AnsiString(pSOZAI_OR_DATA[i2].HINBAN_SK).Trim()))
			    		{
                    		for(i3 = 0;i3 < AnsiString(pSOZAI_SYKA_DATA[i1].SOKU_SU).ToIntDef(0);i3++)
                        	{
                    	    	//SGr_vSOKU_SYUKA->Cells[i4][nDRAW_GRID+i3]="" ;
        					    strcpy(pCELLINFO_SOKU_SOZAI[i4*SGr_vSOKU_SOZAI->RowCount+nDRAW_GRID+i3].RESULT,"");
            					strcpy(pCELLINFO_SOKU_SOZAI[i4*SGr_vSOKU_SOZAI->RowCount+nDRAW_GRID+i3].DISP_RESULT,"");
            					strcpy(pCELLINFO_SOKU_SOZAI[i4*SGr_vSOKU_SOZAI->RowCount+nDRAW_GRID+i3].KOMK_NO,pSOZAI_SYKA_DATA[i1].KOMK_NO);
            					pCELLINFO_SOKU_SOZAI[i4*SGr_vSOKU_SOZAI->RowCount+nDRAW_GRID+i3].INS_ON = true;
                        	}
			    			i2 = iSOZAI_ContCnt+1;
				    	}
                        nDRAW_GRID += AnsiString(pSOZAI_OR_DATA[ i2 ].SOKU_SU).ToIntDef(0);
    				}
	    		}
		    }
    	}
    }
    //���b�g���蓖�ĉ�ʂŁu�ύX�v�������̓t���O��true
    // 2003/11/18 A.Tamura �ȉ�if��(bNowF7 == true)��false�̊ԈႢ�H easy miss��?
	//if( bNowF7 == true || bLOTCHANGE == true )
	if( bNowF7 == true || bLOTCHANGE == true )
    {
    	GET_KSD22();        //�f�ތ��f�[�^�̓ǂݍ���(�I���W�i���j
    }
    //���b�g�`�F���W�t���O�̏�����
    for( i1 = 0; i1 < Form1->SGr_vSOKU_SOZAI->ColCount ; i1++)
    {
        strcpy(pSOKU_KSD01_DATA[i1].LOTNOCHANGE1_SZ,"0");
        strcpy(pSOKU_KSD01_DATA[i1].LOTNOCHANGE2_SZ,"0");
        strcpy(pSOKU_KSD01_DATA[i1].LOTNOCHANGE3_SZ,"0");
        strcpy(pSOKU_KSD01_DATA[i1].LOTNOCHANGE4_SZ,"0");
        strcpy(pSOKU_KSD01_DATA[i1].LOTNOCHANGE5_SZ,"0");
        strcpy(pSOKU_KSD01_DATA[i1].LOTNOCHANGE6_SZ,"0");
    }
	if( bNowF7 == true && bNowLotF7 == false )
	{
    //���b�g�`�F���W���Ȃ��̂ŕۑ��f�[�^������Ă���
    	//SET_KSD01();							//������ѓ��̎�荞��
        Set_SOKU_SOZAIJISSEKI();
	}
    for(i1 = 0; i1 < iColCount ;i1++)
    {
        i4 = 1;
        for(i2=0 ; i2 < iSOZAI_ContCnt ; i2++)
        {
            for(i3=0;i3 < AnsiString(pSOZAI_OR_DATA[i2].SOKU_SU).ToIntDef(0);i3++)
            {
                strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].SOKU_SU 		, pSOZAI_OR_DATA[ i2 ].SOKU_SU);
                i4++;
            }
        }
    }
	GET_SOZAI_KSD02_DISP();
    //K.ICHIKAWA Rev.2003.05.10
	iTHREAD_CNT++;
    //Rev.
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ށi�o�ׁj�f�[�^�̕\�����s���܂��B
//
//  �@�\����
//    CELLINFO�̏����l��\�����܂��B
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
void __fastcall TForm1::GET_SOZAI_KSD02_DISP(void)
{
    AnsiString sLot;
    //int i1,i2,i3,i4;
    int iCol,iRow;
    int iRowCount;
    iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;

    for(iCol = 0; iCol < Form1->SGr_vSOKU_SOZAI->ColCount;iCol++)
    {
	for(iRow = 1;iRow < Form1->SGr_vSOKU_SOZAI->RowCount ;iRow++)
	{
	    Form1->SGr_vSOKU_SOZAI->Cells[iCol][iRow] = pCELLINFO_SOKU_SOZAI[(iCol * iRowCount) + iRow].RESULT;
	}
    }
    //Form1->SGr_vRIRE_SYUKA->Refresh();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ށi�o�ׁj�f�[�^�̑f�ޑ�����і��׃f�[�^�̓ǂݍ��݂��s���B
//
//  �@�\����
//    ���蓖�čς݂̃��b�gNO���L�[�ɂ��đf�ށi�o�ׁj�f�[�^�̑f�ޑ�����і��׃f�[�^�̓ǂݍ��݂��s���B
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
void __fastcall TForm1::GET_KSD22(void)
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
	int		iLotChange;
    bool	bUseKSD02;
	sLot = "";


	for(iCol = 0; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
        bFirstDate = true;
    	for(i1 = 0;i1 < 6; i1++)
		{
			switch( i1 )
			{
			    case 0:
				    sHINBAN		= pSOKU_KSD01_DATA[iCol].HINBAN1_SZ;
				    sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO1_SZ;
				    sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;
				    sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO1_SZ;
				    sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM1_SZ;
				    iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE1_SZ).ToIntDef(0);
                    break;
                case 1:
				    sHINBAN		= pSOKU_KSD01_DATA[iCol].HINBAN2_SZ;
				    sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO2_SZ;
				    sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
				    sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO2_SZ;
				    sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM2_SZ;
				    iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE2_SZ).ToIntDef(0);
                    break;
                case 2:
				    sHINBAN		= pSOKU_KSD01_DATA[iCol].HINBAN3_SZ;
				    sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO3_SZ;
				    sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
				    sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO3_SZ;
				    sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM3_SZ;
				    iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE3_SZ).ToIntDef(0);
                    break;
                case 3:
				    sHINBAN		= pSOKU_KSD01_DATA[iCol].HINBAN4_SZ;
				    sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO4_SZ;
				    sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
				    sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO4_SZ;
				    sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM4_SZ;
				    iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE4_SZ).ToIntDef(0);
                    break;
                case 4:
				    sHINBAN		= pSOKU_KSD01_DATA[iCol].HINBAN5_SZ;
				    sLOTNO	 	= pSOKU_KSD01_DATA[iCol].LOTNO5_SZ;
				    sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
				    sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO5_SZ;
				    sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM5_SZ;
				    iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE5_SZ).ToIntDef(0);
                    break;
                case 5:
				    sHINBAN		= pSOKU_KSD01_DATA[iCol].HINBAN6_SZ;
				    sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO6_SZ;
				    sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
				    sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO6_SZ;
				    sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM6_SZ;
				    iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE6_SZ).ToIntDef(0);
                    break;
			}
//			sLOTNO = Form1->SGr_tSOKU->Cells[iCol][0];
            if(sDTKSHIN_SZ.Trim().Length() != 0 && sLOTNO.Trim().Length() != 0 )
			{
                if((bLOTCHANGE == true) && (iLotChange == 0))			//���b�g���蓖�ĉ�ʂŁu�ύX�v�������ꂽ���A
				{													//�ύX����Ă��Ȃ��ꍇ�͉��߂ăf�[�^�����[�h���Ȃ�
				}
				else
				{
				    // 2003/11/19 A.Tamura �w�肳�ꂽ���b�g������ς݂��ǂ����𔻒肵�A
				    //                     ����ς݂̏ꍇ��[KSD02]�{[KSD22]�őf�ރf�[�^���������܂�
				    //                     ������@�̏ꍇ��[KSM02]�{[KSD22]�őf�ރf�[�^���������܂�
				    sBuf = "SELECT LOTNO FROM KSD01 WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";
				    sBuf += " AND HINBAN ='" + AnsiString(pSOKU_KSD01_DATA[iCol].HINBAN) + "'";
				    sBuf += " AND LOTNO  ='" + AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO) + "'";

				    // Initial Query
				    Form1->Query4->Close();
				    Form1->Query4->SQL->Clear();
				    Form1->Query4->SQL->Add(sBuf);
				    Form1->Query4->Open();
				    Form1->Query4->Active = true;

				    if( Form1->Query4->Eof == true ){
                        // ������ׁ̈A[KSM02]+[KSD22]�őf�ރf�[�^���������܂�
					    sBuf  = " SELECT KSD22.LOTNO,KSD22.DTKSHIN,KSD22.HINBAN,KSD22.KOMK_NM,";
					    sBuf += "KSD22.KOMK_NO,KSD22.SKTYMD,KSD22.ADDYMD,KSD22.ADDTIM,";
					    sBuf += "KSD22.UPDYMD,KSD22.UPDTIM,KSD22.UPDCHR,KSD22.UPDCNT,";
					    sBuf += "KSD22.SOKU_VAL01,KSD22.SOKU_VAL02,KSD22.SOKU_VAL03,";
					    sBuf += "KSD22.SOKU_VAL04,KSD22.SOKU_VAL05,KSD22.SOKU_VAL06,";
					    sBuf += "KSD22.SOKU_VAL07,KSD22.SOKU_VAL08,KSD22.SOKU_VAL09,KSD22.SOKU_VAL10 ";

					    sBuf += " FROM KSM02 INNER JOIN KSD22 ON (KSM02.KOMK_NO = KSD22.KOMK_NO)";
					    sBuf += " AND (KSM02.HINBAN_SK = KSD22.DTKSHIN)";
					    sBuf += " WHERE ((KSM02.DTKSHIN)='" + Form1->sNowDTKSHIN + "')";
					    sBuf += " AND (KSM02.HINBAN_SK) = '" + sDTKSHIN_SZ + "'";
					    sBuf += " AND ((KSM02.REVCNT)=0)";
					    sBuf += " AND ((KSM02.SKB_NO)=1)";
					    sBuf += " AND ((KSD22.LOTNO)  = '" + sLOTNO + "')";
					    sBuf += " AND ((KSD22.HINBAN) = '" + sHINBAN + "')";
                        sBuf += " GROUP BY KSD22.LOTNO,KSD22.DTKSHIN,KSD22.HINBAN,KSD22.KOMK_NM,";
					    sBuf += "KSD22.KOMK_NO,KSD22.SKTYMD,KSD22.ADDYMD,KSD22.ADDTIM,";
					    sBuf += "KSD22.UPDYMD,KSD22.UPDTIM,KSD22.UPDCHR,KSD22.UPDCNT,";
					    sBuf += "KSD22.SOKU_VAL01,KSD22.SOKU_VAL02,KSD22.SOKU_VAL03,";
					    sBuf += "KSD22.SOKU_VAL04,KSD22.SOKU_VAL05,KSD22.SOKU_VAL06,";
					    sBuf += "KSD22.SOKU_VAL07,KSD22.SOKU_VAL08,KSD22.SOKU_VAL09,KSD22.SOKU_VAL10";
                    }
				    else {
                        // ����ςׁ݂̈A[KSD02]+[KSD22]�őf�ރf�[�^���������܂�
					    sBuf  = " SELECT KSD22.LOTNO,KSD22.DTKSHIN,KSD22.HINBAN,KSD22.KOMK_NM,";
					    sBuf += "KSD22.KOMK_NO,KSD22.SKTYMD,KSD22.ADDYMD,KSD22.ADDTIM,";
					    sBuf += "KSD22.UPDYMD,KSD22.UPDTIM,KSD22.UPDCHR,KSD22.UPDCNT,";
					    sBuf += "KSD22.SOKU_VAL01,KSD22.SOKU_VAL02,KSD22.SOKU_VAL03,";
					    sBuf += "KSD22.SOKU_VAL04,KSD22.SOKU_VAL05,KSD22.SOKU_VAL06,";
					    sBuf += "KSD22.SOKU_VAL07,KSD22.SOKU_VAL08,KSD22.SOKU_VAL09,KSD22.SOKU_VAL10 ";

					    sBuf += " FROM KSD02 INNER JOIN KSD22 ON (KSD02.KOMK_NO = KSD22.KOMK_NO)";
					    sBuf += " AND (KSD02.HINBAN_SK = KSD22.DTKSHIN)";
					    sBuf += " WHERE ((KSD02.DTKSHIN)='" + Form1->sNowDTKSHIN + "')";
					    sBuf += " AND (KSD02.HINBAN_SK) = '" + sDTKSHIN_SZ + "'";
					    sBuf += " AND ((KSD02.SKB_NO)=1)";
					    sBuf += " AND ((KSD22.LOTNO)  = '" + sLOTNO + "')";
					    sBuf += " AND ((KSD22.HINBAN) = '" + sHINBAN + "')";
                        sBuf += " GROUP BY KSD22.LOTNO,KSD22.DTKSHIN,KSD22.HINBAN,KSD22.KOMK_NM,";
					    sBuf += "KSD22.KOMK_NO,KSD22.SKTYMD,KSD22.ADDYMD,KSD22.ADDTIM,";
					    sBuf += "KSD22.UPDYMD,KSD22.UPDTIM,KSD22.UPDCHR,KSD22.UPDCNT,";
					    sBuf += "KSD22.SOKU_VAL01,KSD22.SOKU_VAL02,KSD22.SOKU_VAL03,";
					    sBuf += "KSD22.SOKU_VAL04,KSD22.SOKU_VAL05,KSD22.SOKU_VAL06,";
					    sBuf += "KSD22.SOKU_VAL07,KSD22.SOKU_VAL08,KSD22.SOKU_VAL09,KSD22.SOKU_VAL10";
                    }


				    //For Debug
                    // 2003.06.03 k.y
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
                        sDTKSHIN = "";
                        sKOMK_NM = "";
                        sKOMK_NO = "";
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
                        if( bFirstDate == true )
                        {
    					    strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ		,sSKTYMD.c_str());
	    				    strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT	,sSKTYMD.c_str());
                            strcpy(pSOKU_KSD01_DATA[iCol].UPDNAME 		,Form1->GetTANTO(sUPDCHR).c_str());
                            bFirstDate = false;
                        }
                        else
                        {
    				        if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ) < sSKTYMD)
                            {
    					        strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ		,sSKTYMD.c_str());
	    				        strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT	,sSKTYMD.c_str());
                                strcpy(pSOKU_KSD01_DATA[iCol].UPDNAME 		,Form1->GetTANTO(sUPDCHR).c_str());
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
                            //2003/12/10 E.Takase
                            //�����ǉ� pCELLINFO_SOKU_SOZAI���L�����H KOMK_NO��-999�ȊO�Ȃ�OK
						    //if((AnsiString(pSOZAI_OR_DATA[ i3 ].KOMK_NO) 	== sKOMK_NO)
						    //&& (AnsiString(pSOZAI_OR_DATA[ i3 ].HINBAN_SK) == sDTKSHIN))
						    //{
						    if((AnsiString(pSOZAI_OR_DATA[ i3 ].KOMK_NO) 	== sKOMK_NO)
						    && (AnsiString(pSOZAI_OR_DATA[ i3 ].HINBAN_SK) == sDTKSHIN)
                            && (strcmp(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow].KOMK_NO ,"-999" ) !=0 ) )
						    {
            	    		    for(i2 = 0 ; i2 < AnsiString(pSOZAI_OR_DATA[ i3 ].SOKU_SU).ToIntDef(0); i2++)
							    {
                				    switch( i2 )
                				    {
								        case 0:
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT			, sSOKU_VAL01.c_str());
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL01.c_str());
									        break;
                                        case 1:
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT			, sSOKU_VAL02.c_str());
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL02.c_str());
									        break;
                                        case 2:
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL03.c_str());
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL03.c_str());
									        break;
                                        case 3:
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL04.c_str());
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL04.c_str());
									        break;
                                        case 4:
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL05.c_str());
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL05.c_str());
									        break;
                                        case 5:
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL06.c_str());
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL06.c_str());
									        break;
                                        case 6:
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL07.c_str());
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL07.c_str());
									        break;
                                        case 7:
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL08.c_str());
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL08.c_str());
									        break;
                                        case 8:
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL09.c_str());
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL09.c_str());
									        break;
                                        case 9:
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL10.c_str());
									        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL10.c_str());
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
			}
 		}
		iRow += AnsiString(pSOZAI_OR_DATA[ i1 ].SOKU_SU).ToIntDef(0);
        Form1->Query4->Close();
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ށi�o�ׁj�f�[�^��KSM01��KSD01�ւ̏����l������s���B
//
//  �@�\����
//    �f�ށi�o�ׁj�f�[�^�̏����l�iKSM01�j�̑�����s�����b�g���ɍs���B
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
void __fastcall TForm1::SET_KSD01(void)
{
    //�f�t�H���g�̕i�Ԃ̃Z�b�g
	int iCol,i2;//i1,i3;
	AnsiString sBuf,sLot,sBuf2;
    AnsiString sLot_Where;

	for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
	{
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN	 ,Form1->sNowDTKSHIN.c_str());
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO	 	    ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN 	    ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
		//strcpy(pSOKU_KSD01_DATA[iCol].HINBAN	    ,pKSM01_DATA.HINBAN);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSCOD	    ,pKSM01_DATA.DTKSCOD);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSNAM	    ,pKSM01_DATA.DTKSNAM);
		strcpy(pSOKU_KSD01_DATA[iCol].ZISNAM	    ,pKSM01_DATA.ZISNAM);
		strcpy(pSOKU_KSD01_DATA[iCol].HINMEI	    ,pKSM01_DATA.HINMEI);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ   ,pKSM01_DATA.DTKSHIN1_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ   ,pKSM01_DATA.DTKSHIN2_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ   ,pKSM01_DATA.DTKSHIN3_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ   ,pKSM01_DATA.DTKSHIN4_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ   ,pKSM01_DATA.DTKSHIN5_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ   ,pKSM01_DATA.DTKSHIN6_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ   ,pKSM01_DATA.LOT_LINK_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].SOKUTEI_NUM   ,pKSM01_DATA.SOKUTEI_NUM);
		strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK	 	 ,"0");					//�f�t�H���g�͂n�j
		strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK_PRT	 ,"0");					//�f�t�H���g�͂n�j
		strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK	 	 ,"0");					//�f�t�H���g�͂n�j
		strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK_PRT	 ,"0");					//�f�t�H���g�͂n�j
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE1 ,pKSM01_DATA.OUT_TITLE1);
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE2 ,pKSM01_DATA.OUT_TITLE2);
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE3 ,pKSM01_DATA.OUT_TITLE3);
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE4 ,pKSM01_DATA.OUT_TITLE4);
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE5 ,pKSM01_DATA.OUT_TITLE5);
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE6 ,pKSM01_DATA.OUT_TITLE6);
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE7 ,pKSM01_DATA.OUT_TITLE7);
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE8 ,pKSM01_DATA.OUT_TITLE8);
		strcpy(pSOKU_KSD01_DATA[iCol].X_OUT 	 ,pKSM01_DATA.X_OUT);
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ 	 ,pKSM01_DATA.ADDYMD);
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT  ,pKSM01_DATA.ADDYMD);
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD 	 ,pKSM01_DATA.ADDYMD);
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT ,pKSM01_DATA.ADDYMD);
		strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD 	 ,pKSM01_DATA.ADDYMD);
		strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM 	 ,pKSM01_DATA.ADDTIM);
		strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD 	 ,pKSM01_DATA.UPDYMD);
		strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM 	 ,pKSM01_DATA.UPDTIM);
		strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 ,pKSM01_DATA.UPDCHR);
		strcpy(pSOKU_KSD01_DATA[iCol].UPDCNT 	 ,pKSM01_DATA.UPDCNT);
		pSOKU_KSD01_DATA[iCol].UPD_FLG = false;
		pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;

        // 2004.12.24(X'mas Eve) A.Tamura �Ō�܂Ń��[�v����ĂȂ��I�I
        //for(i2 = 0;i2 < 5;i2++)
        for(i2 = 0;i2 < 6;i2++)
        {
			//i3 = 0;
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
				        strcpy(pSOKU_KSD01_DATA[iCol].HINBAN1_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                        break;
                    case 1:
				        strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
				        strcpy(pSOKU_KSD01_DATA[iCol].HINBAN2_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                        break;
                    case 2:
                        strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
				        strcpy(pSOKU_KSD01_DATA[iCol].HINBAN3_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                        break;
                    case 3:
                        strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
				        strcpy(pSOKU_KSD01_DATA[iCol].HINBAN4_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                        break;
                    case 4:
                        strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
				        strcpy(pSOKU_KSD01_DATA[iCol].HINBAN5_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                        break;
                    case 5:
                        strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
				        strcpy(pSOKU_KSD01_DATA[iCol].HINBAN6_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                        break;
                }
			}
        }
	}
    //�����̗L�镨�̃Z�b�g
	sLot ="";
	for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
	{
    	sLot += "'" + Form1->SGr_tSOKU->Cells[iCol][0] +"',";
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi��
    // ���b�g��������������
    sLot_Where = "";
	for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
	{
        sLot_Where += "( LOTNO='" + Form1->SGr_tSOKU->Cells[iCol][0] + "' AND ";
        sLot_Where += " HINBAN='" + Form1->SGr_tSOKU->Cells[iCol][1] + "') OR ";

    	sLot += "'" + Form1->SGr_tSOKU->Cells[iCol][0] +"',";
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi��

	sBuf = "SELECT * FROM KSD01";
	sBuf += " WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";
	//sBuf += " AND LOTNO IN (" + sLot + ")";
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
		for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
		{
			if(Form1->SGr_tSOKU->Cells[iCol][0] == AnsiString(Form1->Query4->FieldValues["LOTNO"])) break;
		}

        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN"];						//���Ӑ�i��
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN	 			,sBuf.c_str());
		}
         strcpy(pSOKU_KSD01_DATA[iCol].LOTNO		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO"];                     		//���b�gNO
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO	 				,sBuf.c_str());
        }
         strcpy(pSOKU_KSD01_DATA[iCol].HINBAN		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN"];                     		//�H�ǔ��s�� onishi
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN	 				,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO1_SZ"];                 		//�f�ޗp���b�g�P
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO2_SZ"];                      //�f�ޗp���b�g�Q
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO3_SZ"];                      //�f�ޗp���b�g�R
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO4_SZ"];                      //�f�ޗp���b�g�S
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO5_SZ"];                      //�f�ޗp���b�g�T
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO6_SZ"];                      //�f�ޗp���b�g�U
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ	 	 		,sBuf.c_str());
		}
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN1_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN1_SZ"];                 	//�f�ޗp���Еi��1
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN1_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN2_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN2_SZ"];                 	//�f�ޗp���Еi��2
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN2_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN3_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN3_SZ"];                 	//�f�ޗp���Еi��3
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN3_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN4_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN4_SZ"];                 	//�f�ޗp���Еi��4
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN4_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN5_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN5_SZ"];                 	//�f�ޗp���Еi��5
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN5_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN6_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN6_SZ"];                 	//�f�ޗp���Еi��6
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN6_SZ	 	 	,sBuf.c_str());
        }

        strcpy(pSOKU_KSD01_DATA[iCol].HINBAN		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN"];                       	//���Еi��
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN	 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSCOD		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSCOD"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSCOD"];                      	//���Ӑ�R�[�h
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSCOD	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSNAM		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSNAM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSNAM"];                      	//���Ӑ於��
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSNAM	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].ZISNAM		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["ZISNAM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["ZISNAM"];                       	//�ގ�����
			strcpy(pSOKU_KSD01_DATA[iCol].ZISNAM	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].HINMEI		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["HINMEI"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINMEI"];                      	//�i��
			strcpy(pSOKU_KSD01_DATA[iCol].HINMEI	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN1_SZ"];                  	//�f�ޗp���Ӑ�i�ԂP
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN2_SZ"];                    //�f�ޗp���Ӑ�i�ԂQ
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN3_SZ"];                    //�f�ޗp���Ӑ�i�ԂR
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN4_SZ"];                    //�f�ޗp���Ӑ�i�ԂS
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN5_SZ"];                    //�f�ޗp���Ӑ�i�ԂT
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN6_SZ"];                    //�f�ޗp���Ӑ�i�ԂU
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["LOT_LINK_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOT_LINK_SZ"];                    //���b�g�����N
			strcpy(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].SOKUTEI_NUM		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["SOKUTEI_NUM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOKUTEI_NUM"];                    //���荀�ڐ�
			strcpy(pSOKU_KSD01_DATA[iCol].SOKUTEI_NUM			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["SOZAI_OK"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOZAI_OK"];                       //�f�ޔ���
			strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK				,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK_PRT		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["SOZAI_OK_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOZAI_OK_PRT"];                   //�f�ޔ������p
			strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK_PRT			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["SYUKA_OK"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SYUKA_OK"];                       //�o�ה���
			strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK				,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK_PRT		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["SYUKA_OK_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SYUKA_OK_PRT"];                   //�o�ה������p
			strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK_PRT			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE1		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE1"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE1"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE1 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE2		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE2"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE2"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE2 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE3		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE3"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE3"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE3 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE4		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE4"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE4"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE4 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE5		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE5"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE5"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE5 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE6		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE6"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE6"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE6 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE7		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE7"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE7"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE7 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE8		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE8"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE8"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE8 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].X_OUT		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["X_OUT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["X_OUT"];
			strcpy(pSOKU_KSD01_DATA[iCol].X_OUT 	 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].MEMO		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["MEMO"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["MEMO"];
			strcpy(pSOKU_KSD01_DATA[iCol].MEMO 	 				,sBuf.c_str());
        }

	    //�f�ޗp���������
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_SZ"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_SZ"];
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ 	 			,sBuf.c_str());
        }
		if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD,pKSM01_DATA.ADDYMD);
        }
	    //�f�ޗp����������i����p�j
        strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_SZ_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_SZ_PRT"];
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT 	 	  	,sBuf.c_str());
        }
		if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT,pKSM01_DATA.ADDYMD);
        }
	    //�o�חp���������
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD"];
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD 	 			,sBuf.c_str());
        }
		if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD,pKSM01_DATA.ADDYMD);
        }
	    //�o�חp����������i����p�j
        strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_PRT"];
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT 	 	  	,sBuf.c_str());
        }
		if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT,pKSM01_DATA.ADDYMD);
        }
	    //��\�o�^��
		strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["ADDYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["ADDYMD"];
			strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD 	 			,sBuf.c_str());
		}
		if(AnsiString(pSOKU_KSD01_DATA[iCol].ADDYMD).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD,pKSM01_DATA.ADDYMD);
        }
	    //��\�o�^����
        strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["ADDTIM"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["ADDTIM"];
			strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM 	 			,sBuf.c_str());
		}
		if(AnsiString(pSOKU_KSD01_DATA[iCol].ADDTIM).Trim().Length() != 4 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM,pKSM01_DATA.ADDTIM);
        }
	    //��\�ύX��
        strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["UPDYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDYMD"];
			strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD 	 			,sBuf.c_str());
        }
		if(AnsiString(pSOKU_KSD01_DATA[iCol].UPDYMD).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD,pKSM01_DATA.UPDYMD);
        }
	    //��\�ύX����
		strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["UPDTIM"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDTIM"];
			strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM 	 			,sBuf.c_str());
		}
		if(AnsiString(pSOKU_KSD01_DATA[iCol].UPDTIM).Trim().Length() != 4 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM,pKSM01_DATA.UPDTIM);
        }
	    //��\�X�V��
        strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["UPDCHR"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDCHR"];
			strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 			,sBuf.c_str());
		}
	    //��\�X�V��
        strcpy(pSOKU_KSD01_DATA[iCol].UPDCNT		,"");                      //�i��
        if ( VarIsNull(Form1->Query4->FieldValues["UPDCNT"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDCNT"];
			strcpy(pSOKU_KSD01_DATA[iCol].UPDCNT 	 			,sBuf.c_str());
		}
		Form1->Query4->Next();
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�f�ށi�o�ׁj�f�[�^�̑f�ޑ�����і��׃f�[�^�̓ǂݍ��݂��s���B
//
//  �@�\����
//    ���蓖�čς݂̃��b�gNO���L�[�ɂ��đf�ށi�o�ׁj�f�[�^�̑f�ޑ�����і��׃f�[�^�̓ǂݍ��݂��s���B
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
void __fastcall TForm1::GET_KSD22_AGAIN(void)
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
    sLot = "";

    for(iCol = 0; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
    {
        bFirstDate = true;
    	for(i1 = 0;i1 < 6; i1++)
        {
	        switch( i1 )
	        {
		        case 0:
                     sHINBAN 	= pSOKU_KSD01_DATA[iCol].HINBAN1_SZ;
                     sLOTNO 	= pSOKU_KSD01_DATA[iCol].LOTNO1_SZ;
		    	     sDTKSHIN_SZ= pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;
		    	     sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO1_SZ;
		    	     sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM1_SZ;
		    	     iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE1_SZ).ToIntDef(0);
                     break;
                case 1:
                     sHINBAN 	= pSOKU_KSD01_DATA[iCol].HINBAN2_SZ;
			         sLOTNO 	= pSOKU_KSD01_DATA[iCol].LOTNO2_SZ;
			         sDTKSHIN_SZ= pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
			         sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO2_SZ;
			         sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM2_SZ;
			         iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE2_SZ).ToIntDef(0);
                     break;
                case 2:
                     sHINBAN 	= pSOKU_KSD01_DATA[iCol].HINBAN3_SZ;
			         sLOTNO 	= pSOKU_KSD01_DATA[iCol].LOTNO3_SZ;
			         sDTKSHIN_SZ= pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
			         sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO3_SZ;
			         sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM3_SZ;
			         iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE3_SZ).ToIntDef(0);
                     break;
                case 3:
                     sHINBAN 	= pSOKU_KSD01_DATA[iCol].HINBAN4_SZ;
                     sLOTNO 	= pSOKU_KSD01_DATA[iCol].LOTNO4_SZ;
			         sDTKSHIN_SZ= pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
			         sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO4_SZ;
			         sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM4_SZ;
			         iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE4_SZ).ToIntDef(0);
                     break;
                case 4:
                     sHINBAN 	= pSOKU_KSD01_DATA[iCol].HINBAN5_SZ;
			         sLOTNO	 	= pSOKU_KSD01_DATA[iCol].LOTNO5_SZ;
			         sDTKSHIN_SZ= pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
			         sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO5_SZ;
			         sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM5_SZ;
			         iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE5_SZ).ToIntDef(0);
                     break;
                case 5:
                     sHINBAN 	= pSOKU_KSD01_DATA[iCol].HINBAN6_SZ;
			         sLOTNO 	= pSOKU_KSD01_DATA[iCol].LOTNO6_SZ;
                     sDTKSHIN_SZ= pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ;
			         sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO6_SZ;
			         sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM6_SZ;
			         iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE6_SZ).ToIntDef(0);
                     break;
            }
//			sLOTNO = Form1->SGr_tSOKU->Cells[iCol][0];
            if(sDTKSHIN_SZ.Trim().Length() != 0 && sLOTNO.Trim().Length() != 0 )
	        {
                if((bLOTCHANGE == true) && (iLotChange == 0))			//���b�g���蓖�ĉ�ʂŁu�ύX�v�������ꂽ���A
		        {		                                                //�ύX����Ă��Ȃ��ꍇ�͉��߂ăf�[�^�����[�h���Ȃ�
		        }
		        else
		        {
		            // 2003/11/19 A.Tamura �w�肳�ꂽ���b�g������ς݂��ǂ����𔻒肵�A
		            //                     ����ς݂̏ꍇ��[KSD02]�{[KSD22]�őf�ރf�[�^���������܂�
		            //                     ������@�̏ꍇ��[KSM02]�{[KSD22]�őf�ރf�[�^���������܂�
                    sBuf = "SELECT * FROM KSD01 WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";
                    sBuf += " AND HINBAN ='" + AnsiString(pSOKU_KSD01_DATA[iCol].HINBAN) + "'";
		            sBuf += " AND LOTNO  ='" + AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO) + "'";

                    // Initial Query
		            Form1->Query4->Close();
		            Form1->Query4->SQL->Clear();
		            Form1->Query4->SQL->Add(sBuf);
		            Form1->Query4->Open();
		            Form1->Query4->Active = true;

		            if( Form1->Query4->Eof == true ){
                        // ������ׁ̈A[KSM02]+[KSD22]�őf�ރf�[�^���������܂�
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
			            sBuf += " AND ((KSD22.LOTNO)  = '" + sLOTNO + "')";
			            sBuf += " AND ((KSD22.HINBAN) = '" + sHINBAN + "')";
	                    sBuf += " GROUP BY KSD22.LOTNO,KSD22.DTKSHIN,KSD22.HINBAN,KSD22.KOMK_NM,";
			            sBuf += "KSD22.KOMK_NO,KSD22.SKTYMD,KSD22.ADDYMD,KSD22.ADDTIM,";
			            sBuf += "KSD22.UPDYMD,KSD22.UPDTIM,KSD22.UPDCHR,KSD22.UPDCNT,";
			            sBuf += "KSD22.SOKU_VAL01,KSD22.SOKU_VAL02,KSD22.SOKU_VAL03,";
			            sBuf += "KSD22.SOKU_VAL04,KSD22.SOKU_VAL05,KSD22.SOKU_VAL06,";
			            sBuf += "KSD22.SOKU_VAL07,KSD22.SOKU_VAL08,KSD22.SOKU_VAL09,";
	                    sBuf += "KSD22.SOKU_VAL10";
		            }
		            else {
                        // ����ςׁ݂̈A[KSD02]+[KSD22]�őf�ރf�[�^���������܂�
			            sBuf  = "SELECT KSD22.LOTNO,KSD22.DTKSHIN,KSD22.HINBAN,KSD22.KOMK_NM,";
			            sBuf += "KSD22.KOMK_NO,KSD22.SKTYMD,KSD22.ADDYMD,KSD22.ADDTIM,";
			            sBuf += "KSD22.UPDYMD,KSD22.UPDTIM,KSD22.UPDCHR,KSD22.UPDCNT,";
			            sBuf += "KSD22.SOKU_VAL01,KSD22.SOKU_VAL02,KSD22.SOKU_VAL03,";
			            sBuf += "KSD22.SOKU_VAL04,KSD22.SOKU_VAL05,KSD22.SOKU_VAL06,";
			            sBuf += "KSD22.SOKU_VAL07,KSD22.SOKU_VAL08,KSD22.SOKU_VAL09,";
	                    sBuf += "KSD22.SOKU_VAL10 ";
			            sBuf += " FROM KSD02 INNER JOIN KSD22 ON (KSD02.KOMK_NO = KSD22.KOMK_NO)";
			            sBuf += " AND (KSD02.HINBAN_SK = KSD22.DTKSHIN)";
			            sBuf += " WHERE ((KSD02.DTKSHIN)='" + Form1->sNowDTKSHIN + "')";
			            sBuf += " AND (KSD02.HINBAN_SK) = '" + sDTKSHIN_SZ + "'";
			            sBuf += " AND ((KSD02.SKB_NO)=1)";
			            sBuf += " AND ((KSD22.LOTNO)  = '" + sLOTNO + "')";
			            sBuf += " AND ((KSD22.HINBAN) = '" + sHINBAN + "')";
	                    sBuf += " GROUP BY KSD22.LOTNO,KSD22.DTKSHIN,KSD22.HINBAN,KSD22.KOMK_NM,";
			            sBuf += "KSD22.KOMK_NO,KSD22.SKTYMD,KSD22.ADDYMD,KSD22.ADDTIM,";
			            sBuf += "KSD22.UPDYMD,KSD22.UPDTIM,KSD22.UPDCHR,KSD22.UPDCNT,";
			            sBuf += "KSD22.SOKU_VAL01,KSD22.SOKU_VAL02,KSD22.SOKU_VAL03,";
			            sBuf += "KSD22.SOKU_VAL04,KSD22.SOKU_VAL05,KSD22.SOKU_VAL06,";
			            sBuf += "KSD22.SOKU_VAL07,KSD22.SOKU_VAL08,KSD22.SOKU_VAL09,";
	                    sBuf += "KSD22.SOKU_VAL10";
		            }


		            //For Debug
                    // 2003.06.03 k.y
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
                        sDTKSHIN = "";
                        sKOMK_NM = "";
                        sKOMK_NO = "";
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
                        if( bFirstDate == true )
                        {
    			            strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ		,sSKTYMD.c_str());
	    		            strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT	,sSKTYMD.c_str());
                            strcpy(pSOKU_KSD01_DATA[iCol].UPDNAME 		,Form1->GetTANTO(sUPDCHR).c_str());
                            bFirstDate = false;
                        }
                        else
                        {
    			            if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ) < sSKTYMD)
                            {
    				            strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ		,sSKTYMD.c_str());
	    			            strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT	,sSKTYMD.c_str());
                                strcpy(pSOKU_KSD01_DATA[iCol].UPDNAME 		,Form1->GetTANTO(sUPDCHR).c_str());
                            }
                        }
			            sLOTNO 			    = "";
		                sSOKU_VAL01 	    = "";    		//�f�ޑ���l
    		            sSOKU_VAL02 		= "";    		//�f�ޑ���l
        		        sSOKU_VAL03 		= "";    		//�f�ޑ���l
            		    sSOKU_VAL04 		= "";    		//�f�ޑ���l
		                sSOKU_VAL05 		= "";    		//�f�ޑ���l
    		            sSOKU_VAL06 		= "";    		//�f�ޑ���l
        		        sSOKU_VAL07 		= "";    		//�f�ޑ���l
            		    sSOKU_VAL08 		= "";    		//�f�ޑ���l
	            	    sSOKU_VAL09 		= "";    		//�f�ޑ���l
	    	            sSOKU_VAL10 		= "";    		//�f�ޑ���l
			            sLOTNO 			    = Form1->Query4->FieldValues["LOTNO"];
			            sHINBAN			    = Form1->Query4->FieldValues["HINBAN"];
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
                            //2003/12/10 E.Takase
                            //�����ǉ� pCELLINFO_SOKU_SOZAI���L�����H KOMK_NO��-999�ȊO�Ȃ�OK
			                //if((AnsiString(pSOZAI_OR_DATA[ i3 ].KOMK_NO) 	== sKOMK_NO)
			                //&& (AnsiString(pSOZAI_OR_DATA[ i3 ].HINBAN_SK) == sDTKSHIN))
			                //{
			                if((AnsiString(pSOZAI_OR_DATA[ i3 ].KOMK_NO)   == sKOMK_NO)
			    	        && (AnsiString(pSOZAI_OR_DATA[ i3 ].HINBAN_SK) == sDTKSHIN)
                            && (strcmp(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow].KOMK_NO ,"-999" ) !=0 ) )
			                {
            	    		    for(i2 = 0 ; i2 < AnsiString(pSOZAI_OR_DATA[ i3 ].SOKU_SU).ToIntDef(0); i2++)
				                {
                                    //2003/12/10 E.Takase Test
                                    if ( sKOMK_NO == "7" ) {
                                	    sKOMK_NO = sKOMK_NO;
                                    }

                		            switch( i2 )
                		            {
					                    case 0:
					                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT			, sSOKU_VAL01.c_str());
                                            if(Trim(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT).Length() == 0)
                                            {
						                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL01.c_str());
                                            }
                                            break;
                                        case 1:
					                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT			, sSOKU_VAL02.c_str());
                                            if(Trim(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT).Length() == 0)
                                            {
                                                strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL02.c_str());
                                            }
                                            break;
                                        case 2:
					                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL03.c_str());
                                            if(Trim(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT).Length() == 0)
                                            {
						                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL03.c_str());
                                            }
                                            break;
                                        case 3:
					                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL04.c_str());
                                            if(Trim(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT).Length() == 0)
                                            {
						                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL04.c_str());
                                            }
                                            break;
                                        case 4:
					                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL05.c_str());
                                            if(Trim(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT).Length() == 0)
                                            {
						                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL05.c_str());
                                            }
                                            break;
                                        case 5:
					                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL06.c_str());
                                            if(Trim(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT).Length() == 0)
                                            {
						                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL06.c_str());
                                            }
                                            break;
                                        case 6:
					                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL07.c_str());
                                            if(Trim(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT).Length() == 0)
                                            {
						                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL07.c_str());
                                            }
                                            break;
                                        case 7:
					                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL08.c_str());
                                            if(Trim(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT).Length() == 0)
                                            {
						                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL08.c_str());
                                            }
                                            break;
                                        case 8:
					                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL09.c_str());
                                            if(Trim(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT).Length() == 0)
                                            {
						                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL09.c_str());
                                            }
                                            break;
                                        case 9:
					                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].RESULT 		, sSOKU_VAL10.c_str());
                                            if(Trim(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT).Length() == 0)
                                            {
						                        strcpy(pCELLINFO_SOKU_SOZAI[(iCol * Form1->SGr_vSOKU_SOZAI->RowCount) + iRow+i2].DISP_RESULT	, sSOKU_VAL10.c_str());
                                            }
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
            }
        }
        iRow += AnsiString(pSOZAI_OR_DATA[ i1 ].SOKU_SU).ToIntDef(0);
        Form1->Query4->Close();
    }
}







