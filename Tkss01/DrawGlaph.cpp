//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DrawGlaph.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit7.h"
#include "Unit8.h"
#include "Unit9.h"
#include "Thread.h"
#include "CommThread.h"
#include "Tkss01.h"
#include "StdComm32.h"
#include <math.h>
#include "UnitDataAccess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#pragma link "PERFGRAP"
#pragma link "NumberEdit"
TForm1 *Form1;
*/
extern int iDEBUG;
// k.y 2003.05.17
//extern	HANDLE 	hInfoGlaph;

// k.y 2003.05.17
// extern 	GRAPH_DATA	*pInfoGlaph;
extern 	GRAPH_DATA	pInfoGlaph;
//KIKAKU KIKAKU_MOJI;
extern int iPORT_NO;
// k.y 2003.05.17
//extern HANDLE		hOldInfoGlaph;

// k.y 2003.05.17
//extern GRAPH_DATA	*pOldInfoGlaph;
extern GRAPH_DATA	pOldInfoGlaph;
extern bool bKASOU_MOVE;

//�Z�����
extern HANDLE hCELLINFO_SOKU_SYUKA;
extern HANDLE hCELLINFO_RIRE_SYUKA;
extern HANDLE hCELLINFO_SOKU_SOZAI;
extern HANDLE hCELLINFO_RIRE_SOZAI;
extern CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
extern CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;

extern int iSOZAI_ORCNT;

int iLotCol;

double dSiguma,dSigumaAve,dSigumaSum,dSigumaNum;
int iNowGrid;
bool bDrawGlaph;

//---------------------------------------------------------------------------

int __fastcall TForm1::WhereGrid(void)
{
	return(iNowGrid);
}
//---------------------------------------------------------------------------

int __fastcall TForm1::Get_GRAPHSTART_Info(int Row,int Col,int GridNo)
{
	int i1;//,i2;
	int iGraphRow;
    // k.y 2003.05.17
    //extern 	KSM02_DATA *pORDATA;
    //extern 	KSM02_DATA pORDATA[100];

// k.y 2003.05.17
	//extern KSM02_DATA *pSOZAI_OR_DATA;
    //extern KSM02_DATA pSOZAI_OR_DATA[100];
    bool bCopy;
    int iRowCount;

	bDrawGlaph = false;                      
	bCopy = false;
	iNowGrid = GridNo;
    iLotCol = Col;
    bCopy = true;

//�����͂������z�񂪊m�ۂ���Ă��Ȃ��ꍇ�ɔ����z��𒲂ז����ꍇ�͎Q�Ƃ𒆎~����
	switch(GridNo)
	{
	case 1:
		if( !hCELLINFO_SOKU_SYUKA ) return( 1 );
        if( SGr_vSOKU_SYUKA->RowCount < 2 ) return( 1 );
		break;
	case 2:
		if( !hCELLINFO_RIRE_SYUKA ) return( 1 );
        if( SGr_vRIRE_SYUKA->RowCount < 2 ) return( 1 );
        if( Form1->iRIRE_CNT  == 0 ) return( 1 );
		break;
	case 3:
		if( !hCELLINFO_SOKU_SOZAI ) return( 1 );
        if( SGr_vSOKU_SOZAI->RowCount < 2 ) return( 1 );
		break;
	case 4:
		if( !hCELLINFO_RIRE_SOZAI ) return( 1 );
        if( SGr_vRIRE_SOZAI->RowCount < 2 ) return( 1 );
        if( Form1->iRIRE_CNT  == 0 ) return( 1 );
		break;
    default:
    	break;
	}
	switch(GridNo)
	{
	case 1:
		iRowCount = Form1->SGr_vSOKU_SYUKA->RowCount;
    	strcpy(pInfoGlaph.KOMK_NM	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KOMK_NM);
        strcpy(pInfoGlaph.KOMK_NO	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KOMK_NO);
        strcpy(pInfoGlaph.KIKI_NO	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKI_NO);
        strcpy(pInfoGlaph.KIKI_NM	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKI_NM);
        strcpy(pInfoGlaph.KOMK_SUB	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KOMK_SUB);
        strcpy(pInfoGlaph.SOKU_SU	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].SOKU_SU);
        strcpy(pInfoGlaph.KIKA_TYPE	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_TYPE);
        strcpy(pInfoGlaph.KIKA_KIND ,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_KIND);
        strcpy(pInfoGlaph.KIKA_DECI	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_DECI);
        strcpy(pInfoGlaph.KIKA_NUM1	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_NUM1);
        strcpy(pInfoGlaph.KIKA_NUM2	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_NUM2);
        strcpy(pInfoGlaph.KIKA_NUM3	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_NUM3);
        strcpy(pInfoGlaph.KIKA_STR	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_STR);
        strcpy(pInfoGlaph.KIKA_SUB1	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_SUB1);
        strcpy(pInfoGlaph.KIKA_SUB2 ,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_SUB2);
        strcpy(pInfoGlaph.KIKA_SUB3	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_SUB3);
        strcpy(pInfoGlaph.VALUE_DECI,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].VALUE_DECI);
        strcpy(pInfoGlaph.SKB_NO	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].SKB_NO);
        strcpy(pInfoGlaph.UNQ_NO	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].UNQ_NO);
        strcpy(pInfoGlaph.HINBAN_SK	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].HINBAN_SK);
        pInfoGlaph.MAX				=pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].MAX;
        pInfoGlaph.MIN				=pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].MIN;
        pInfoGlaph.GMAX				=pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].GMAX;
        pInfoGlaph.GMIN				=pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].GMIN;
        strcpy(pInfoGlaph.UPDNAME 	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].UPDNAME);
        Get_GKIKAKU();
        break;
	case 2:
		iRowCount = Form1->SGr_vRIRE_SYUKA->RowCount;
    	strcpy(pInfoGlaph.KOMK_NM	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KOMK_NM);
        strcpy(pInfoGlaph.KOMK_NO	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KOMK_NO);
        strcpy(pInfoGlaph.KIKI_NO	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKI_NO);
        strcpy(pInfoGlaph.KIKI_NM	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKI_NM);
        strcpy(pInfoGlaph.KOMK_SUB	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KOMK_SUB);
        strcpy(pInfoGlaph.SOKU_SU	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].SOKU_SU);
        strcpy(pInfoGlaph.KIKA_TYPE	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_TYPE);
        strcpy(pInfoGlaph.KIKA_KIND ,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_KIND);
        strcpy(pInfoGlaph.KIKA_DECI	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_DECI);
        strcpy(pInfoGlaph.KIKA_NUM1	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_NUM1);
        strcpy(pInfoGlaph.KIKA_NUM2	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_NUM2);
        strcpy(pInfoGlaph.KIKA_NUM3	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_NUM3);
        strcpy(pInfoGlaph.KIKA_STR	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_STR);
        strcpy(pInfoGlaph.KIKA_SUB1	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_SUB1);
        strcpy(pInfoGlaph.KIKA_SUB2 ,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_SUB2);
        strcpy(pInfoGlaph.KIKA_SUB3	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_SUB3);
        strcpy(pInfoGlaph.VALUE_DECI,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].VALUE_DECI);
        strcpy(pInfoGlaph.SKB_NO	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].SKB_NO);
        strcpy(pInfoGlaph.UNQ_NO	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].UNQ_NO);
        strcpy(pInfoGlaph.HINBAN_SK	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].HINBAN_SK);
        pInfoGlaph.MAX				=pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].MAX;
        pInfoGlaph.MIN				=pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].MIN;
        pInfoGlaph.GMAX				=pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].GMAX;
        pInfoGlaph.GMIN				=pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].GMIN;
        strcpy(pInfoGlaph.UPDNAME  	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].UPDNAME);
        Get_GKIKAKU();
        break;
	case 3:
		iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;
    	strcpy(pInfoGlaph.KOMK_NM	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KOMK_NM);
        strcpy(pInfoGlaph.KOMK_NO	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KOMK_NO);
        strcpy(pInfoGlaph.KIKI_NO	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKI_NO);
        strcpy(pInfoGlaph.KIKI_NM	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKI_NM);
        strcpy(pInfoGlaph.KOMK_SUB	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KOMK_SUB);
        strcpy(pInfoGlaph.SOKU_SU	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].SOKU_SU);
        strcpy(pInfoGlaph.KIKA_TYPE	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_TYPE);
        strcpy(pInfoGlaph.KIKA_KIND ,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_KIND);
        strcpy(pInfoGlaph.KIKA_DECI	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_DECI);
        strcpy(pInfoGlaph.KIKA_NUM1	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_NUM1);
        strcpy(pInfoGlaph.KIKA_NUM2	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_NUM2);
        strcpy(pInfoGlaph.KIKA_NUM3	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_NUM3);
        strcpy(pInfoGlaph.KIKA_STR	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_STR);
        strcpy(pInfoGlaph.KIKA_SUB1	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_SUB1);
        strcpy(pInfoGlaph.KIKA_SUB2 ,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_SUB2);
        strcpy(pInfoGlaph.KIKA_SUB3	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_SUB3);
        strcpy(pInfoGlaph.VALUE_DECI,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].VALUE_DECI);
        strcpy(pInfoGlaph.SKB_NO	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].SKB_NO);
        strcpy(pInfoGlaph.UNQ_NO	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].UNQ_NO);
        strcpy(pInfoGlaph.HINBAN_SK	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].HINBAN_SK);
        pInfoGlaph.MAX				=pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].MAX;
        pInfoGlaph.MIN				=pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].MIN;
        pInfoGlaph.GMAX				=pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].GMAX;
        pInfoGlaph.GMIN				=pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].GMIN;
        strcpy(pInfoGlaph.UPDNAME	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].UPDNAME);
        Get_GKIKAKU();
        break;
	case 4:
		iRowCount = Form1->SGr_vRIRE_SOZAI->RowCount;
    	strcpy(pInfoGlaph.KOMK_NM	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KOMK_NM);
        strcpy(pInfoGlaph.KOMK_NO	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KOMK_NO);
        strcpy(pInfoGlaph.KIKI_NO	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKI_NO);
        strcpy(pInfoGlaph.KIKI_NM	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKI_NM);
        strcpy(pInfoGlaph.KOMK_SUB	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KOMK_SUB);
        strcpy(pInfoGlaph.SOKU_SU	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].SOKU_SU);
        strcpy(pInfoGlaph.KIKA_TYPE	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_TYPE);
        strcpy(pInfoGlaph.KIKA_KIND ,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_KIND);
        strcpy(pInfoGlaph.KIKA_DECI	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_DECI);
        strcpy(pInfoGlaph.KIKA_NUM1	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_NUM1);
        strcpy(pInfoGlaph.KIKA_NUM2	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_NUM2);
        strcpy(pInfoGlaph.KIKA_NUM3	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_NUM3);
        strcpy(pInfoGlaph.KIKA_STR	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_STR);
        strcpy(pInfoGlaph.KIKA_SUB1	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_SUB1);
        strcpy(pInfoGlaph.KIKA_SUB2 ,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_SUB2);
        strcpy(pInfoGlaph.KIKA_SUB3	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_SUB3);
        strcpy(pInfoGlaph.VALUE_DECI,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].VALUE_DECI);
        strcpy(pInfoGlaph.SKB_NO	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].SKB_NO);
        strcpy(pInfoGlaph.UNQ_NO	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].UNQ_NO);
        strcpy(pInfoGlaph.HINBAN_SK	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].HINBAN_SK);
        pInfoGlaph.MAX				=pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].MAX;
        pInfoGlaph.MIN				=pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].MIN;
        pInfoGlaph.GMAX				=pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].GMAX;
        pInfoGlaph.GMIN				=pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].GMIN;
        strcpy(pInfoGlaph.UPDNAME  	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].UPDNAME);
        Get_GKIKAKU();
        break;
	default:
		break;
	}
	switch(GridNo)
	{
	case 1:
    case 2:
		iGraphRow = 0;
		i1 = 0;
        while( i1 < iOrCnt )
		{
            iGraphRow += AnsiString(pORDATA[i1].SOKU_SU).ToIntDef(0);
			if( Row <= iGraphRow )
			{
				iGraphRow = iGraphRow - AnsiString(pORDATA[i1].SOKU_SU).ToIntDef(0);
				break;
			}
			else
			{
				i1 ++;
			}
        }
        break;
	case 3:
    case 4:
		iGraphRow = 0;
		i1 = 0;
		while( i1 < iSOZAI_ORCNT )
		{
			iGraphRow += AnsiString(pSOZAI_OR_DATA[i1].SOKU_SU).ToIntDef(0);
			if( Row <= iGraphRow )
			{
				iGraphRow = iGraphRow - AnsiString(pSOZAI_OR_DATA[i1].SOKU_SU).ToIntDef(0);
				break;
			}
			else
			{
				i1 ++;
			}
        }
		break;
	}
	pInfoGlaph.GRID_NO = GridNo;
	if(bCopy){
 			bDrawGlaph = true;
    }
	else
	{
    	bDrawGlaph = false;
	}
	return( iGraphRow );
}
//----------------------------------------------------------------
void __fastcall TForm1::Get_GRAPHLOT(int iGraphRow,int iGraphCol,int GridNo)
{
//�`��Ώۂ̓J�[�\�������郍�b�g1��+�ߋ�9���̌v10���b�g�i�d�l�ɂ�葝����\������j
//�������Ă��Ȃ����b�g�͔����čX�ɉߋ��ɂ����̂ڂ�̂ŘA�����Ă���Ƃ͌���Ȃ�
//�O���b�h�A�h���X�i�o�׌����@�{���F1�A�����F2�@�@�f�ތ����@�{���F3�A�����F4�j
	int i1,iRes;//i2
	int iRow,iCol,nCount;
    int nGridAddress;
	int iLotMax;
    int CharWidth;                                //Y�����W�l��`�悷�邽�߂̗]��
    int CharHeight;                               //X�����W�l��`�悷�邽�߂̗]��
	int ImageW;//ImageH,                            //�C���[�W�̍����A��
	int x,y,yst,iLoop;
	int iNCnt;
	int iNGCount;
	double d1,d2;
	double dSum,dMax,dMin;
	double dGMax,dGMin;
	AnsiString sBuf;
    bool bLot,bError,bGrid;	//bLot:�L�����b�g,bError:���l�ȊO,bGrid:�܂�����Grid�����邩
	bool bFirstNum;
	GRAPHADDRESS GraphLotAddress[10];	//�H������\���p�o�b�t�@������
   	double dSigumaRes[200];
	double dMaxMinHeight;
	double dOnePitch;
	double dR,dCp,dCpk,dK,dNGPercent;
	AnsiString 	sDeci1, sDeci2;

	AnsiString 	sBufConv;//2003.05.08 E.Takase Add
    bool bRtn;           //2003.05.08 E.Takase Add

//n���̎Z�o(�������i�\��܂ށj
//�L�����b�g�i�v���ς݁j�̒��o
	nGridAddress = GridNo;
    bGrid = true;
	iCol = iGraphCol;
	for( i1 = 0 ; i1 < 10; i1++)
	{
		GraphLotAddress[i1].COL = 0;
    }
//�L�����b�g�i�v���ς݁j�̒��o
	for(i1 = 0; i1 < 10; i1++)
	{
		if(!bGrid) break;
    		bLot = false;
		bError = false;

		switch(nGridAddress)
		{
		case 1:
			for(iRow = 0; iRow < AnsiString(pInfoGlaph.SOKU_SU).ToIntDef(0);iRow ++)
			{
            	sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iGraphRow+iRow+1].Trim();
				//2003.05.17 E.Takase Add��
                strcpy(GraphLotAddress[i1].LOTNAME , SGr_tSOKU->Cells[iCol][0].c_str());
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
                //GraphLotAddress[i1].LOTNAME = SGr_tSOKU->Cells[iCol][0];
				//2003.05.17 E.Takase Add �R�����g��
				if(sBuf.Length()!=0 && sBuf != "�s�v")
				{
                	//2003.05.08 E.Takase Add��
            	    bRtn = Form1->ConvDoubleDefS(sBuf,"0.00",sBuf,&sBufConv);
	                if ( bRtn )
					{
        	        	d1 = Form1->ConvDoubleDefD(sBuf,0.0);
	                }
					else
					{
            	    	bError = true;
                	}
                //2003.05.08 E.Takase Add��
                //2003.05.08 E.Takase Add �R�����g��
                	//try{
					//	d1 = FormatFloat(sBuf,0.00).ToDouble();
					//}
					//catch(EConvertError& e){
                	//	bError = true;
					//}
					//catch(...){
                	//	bError = true;
					//}
                //2003.05.08 E.Takase Add �R�����g��
	                if( !bError )
    	            {
        	        	bLot = true;
            	        GraphLotAddress[i1].GRID = nGridAddress;
                	    GraphLotAddress[i1].COL = iCol;
						//2003.05.17 E.Takase Add��
                    	strcpy(GraphLotAddress[i1].LOTNAME , SGr_tSOKU->Cells[iCol][0].c_str());
						//2003.05.17 E.Takase Add��
						//2003.05.17 E.Takase Add �R�����g��
                    	//GraphLotAddress[i1].LOTNAME = SGr_tSOKU->Cells[iCol][0];
						//2003.05.17 E.Takase Add �R�����g��
                	}
            	}
                if(bLot == true) break;
			}
            if( bError )
            {
            	bLot = true;
                GraphLotAddress[i1].GRID = nGridAddress;
                GraphLotAddress[i1].COL = 0;
				//2003.05.17 E.Takase Add��
                strcpy(GraphLotAddress[i1].LOTNAME , SGr_tSOKU->Cells[iCol][0].c_str());
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
                //GraphLotAddress[i1].LOTNAME = SGr_tSOKU->Cells[iCol][0];
				//2003.05.17 E.Takase Add �R�����g��
            }

			iCol --;
			if(iCol < 0 )		//�ΏۃO���b�h�������Ȃ���
			{
				nGridAddress = 2;
				iCol = Form1->SGr_vRIRE_SYUKA->ColCount-1;
			}
			break;
		case 2:
			for(iRow = 0; iRow < AnsiString(pInfoGlaph.SOKU_SU).ToIntDef(0);iRow ++)
			{
            	sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iGraphRow+iRow+1].Trim();
				//2003.05.17 E.Takase Add��
                strcpy(GraphLotAddress[i1].LOTNAME , SGr_tRIRE->Cells[iCol][0].c_str());
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
                //GraphLotAddress[i1].LOTNAME = SGr_tRIRE->Cells[iCol][0];
				//2003.05.17 E.Takase Add �R�����g��
				if(sBuf.Length()!=0 && sBuf != "�s�v")
				{
                    //2003.05.08 E.Takase Add��
                    bRtn = Form1->ConvDoubleDefS(sBuf,"0.00",sBuf,&sBufConv);
                    if ( bRtn ) {
                    	d1 = Form1->ConvDoubleDefD(sBuf,0.0);
                    } else {
                    	bError = true;
                    }
                    //2003.05.08 E.Takase Add��
                    //2003.05.08 E.Takase Add �R�����g��
                	//try{
                    //	d1 = FormatFloat(sBuf,0.00).ToDouble();
                    //}
					//catch(EConvertError& e){
                	//	bError = true;
					//}
                    //catch(...){
                    //	bError = true;
                    //}
                    //2003.05.08 E.Takase Add �R�����g��
                    if( !bError || bError)
                    {
                    	bLot = true;
                        GraphLotAddress[i1].GRID = nGridAddress;
                        GraphLotAddress[i1].COL = iCol;
						//2003.05.17 E.Takase Add��
                        strcpy(GraphLotAddress[i1].LOTNAME , SGr_tRIRE->Cells[iCol][0].c_str());
						//2003.05.17 E.Takase Add��
						//2003.05.17 E.Takase Add �R�����g��
                        //GraphLotAddress[i1].LOTNAME = SGr_tRIRE->Cells[iCol][0];
						//2003.05.17 E.Takase Add �R�����g��
                    }
				}
                if(bLot == true) break;
			}
			iCol --;
			if(iCol < 0 )		//�ΏۃO���b�h�������Ȃ���
			{
				bGrid = false;
			}
			break;
		case 3:
			for(iRow = 0; iRow < AnsiString(pInfoGlaph.SOKU_SU).ToIntDef(0);iRow ++)
			{
            	sBuf = SGr_vSOKU_SOZAI->Cells[iCol][iGraphRow+iRow+1].Trim();
				//2003.05.17 E.Takase Add��
                strcpy(GraphLotAddress[i1].LOTNAME , SGr_tSOKU->Cells[iCol][0].c_str());
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
                //GraphLotAddress[i1].LOTNAME = SGr_tSOKU->Cells[iCol][0];
				//2003.05.17 E.Takase Add �R�����g��
				if(sBuf.Length()!=0 && sBuf != "�s�v")
				{
                    //2003.05.08 E.Takase Add��
                    bRtn = Form1->ConvDoubleDefS(sBuf,"0.00",sBuf,&sBufConv);
                    if ( bRtn ) {
                    	d1 = Form1->ConvDoubleDefD(sBuf,0.0);
                    } else {
                    	bError = true;
                    }
                    //2003.05.08 E.Takase Add��
                    //2003.05.08 E.Takase Add �R�����g��
                	//try{
					//	d1 = FormatFloat(sBuf,0.00).ToDouble();
					//}
					//catch(EConvertError& e){
                	//	bError = true;
					//}
					//catch(...){
                	//	bError = true;
					//}
                    //2003.05.08 E.Takase Add �R�����g��
					if( !bError || bError)
					{
                		bLot = true;
						GraphLotAddress[i1].GRID = nGridAddress;
						GraphLotAddress[i1].COL = iCol;
						//2003.05.17 E.Takase Add��
						strcpy(GraphLotAddress[i1].LOTNAME , SGr_tSOKU->Cells[iCol][0].c_str());
						//2003.05.17 E.Takase Add��
						//2003.05.17 E.Takase Add �R�����g��
						//GraphLotAddress[i1].LOTNAME = SGr_tSOKU->Cells[iCol][0];
						//2003.05.17 E.Takase Add �R�����g��
					}
				}
                if(bLot == true) break;
			}
			iCol --;
			if(iCol < 0 )		//�ΏۃO���b�h�������Ȃ���
			{
				nGridAddress = 4;
				iCol = Form1->SGr_vRIRE_SOZAI->ColCount-1;
			}
			break;
		case 4:
			for(iRow = 0; iRow < AnsiString(pInfoGlaph.SOKU_SU).ToIntDef(0);iRow ++)
			{
            	sBuf = SGr_vRIRE_SOZAI->Cells[iCol][iGraphRow+iRow+1].Trim();
				//2003.05.17 E.Takase Add��
                strcpy(GraphLotAddress[i1].LOTNAME , SGr_tRIRE->Cells[iCol][0].c_str());
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
                //GraphLotAddress[i1].LOTNAME = SGr_tRIRE->Cells[iCol][0];
				//2003.05.17 E.Takase Add �R�����g��
				if(sBuf.Length()!=0 && sBuf != "�s�v")
				{
                    //2003.05.08 E.Takase Add��
                    bRtn = Form1->ConvDoubleDefS(sBuf,"0.00",sBuf,&sBufConv);
                    if ( bRtn ) {
                    	d1 = Form1->ConvDoubleDefD(sBuf,0.0);
                    } else {
                    	bError = true;
                    }
                    //2003.05.08 E.Takase Add��
                    //2003.05.08 E.Takase Add �R�����g��
                	//try{
					//	d1 = FormatFloat(sBuf,0.00).ToDouble();
					//}
					//catch(EConvertError& e){
                	//	bError = true;
					//}
					//catch(...){
                	//	bError = true;
					//}
                    //2003.05.08 E.Takase Add �R�����g��
					if( !bError || bError)
					{
                		bLot = true;
						GraphLotAddress[i1].GRID = nGridAddress;
						GraphLotAddress[i1].COL = iCol;
						//2003.05.17 E.Takase Add��
						strcpy(GraphLotAddress[i1].LOTNAME , SGr_tRIRE->Cells[iCol][0].c_str());
						//2003.05.17 E.Takase Add��
						//2003.05.17 E.Takase Add �R�����g��
						//GraphLotAddress[i1].LOTNAME = SGr_tRIRE->Cells[iCol][0];
						//2003.05.17 E.Takase Add �R�����g��
					}
				}
                if(bLot == true) break;
			}
			iCol --;
			if(iCol < 0 )		//�ΏۃO���b�h�������Ȃ���
			{
				bGrid = false;
			}
			break;
		default:
			break;
		}
	}
	iLotMax = i1;
//�L�����b�g�̒��̌X�̃��b�g�̍ő�^�ŏ��l�^���ϒl���o
	dSiguma = 0.0;
	dSigumaSum = 0.0;
	dSigumaAve = 0.0;
	dSigumaNum = 0.0;
	iRes = 0;
	nCount = 0;
	for(i1 = 0;i1 < iLotMax;i1++)
	{
    	GraphLotAddress[i1].MAX = 0.0;
        GraphLotAddress[i1].MIN = 0.0;
		dSum = 0;
		iNCnt = 0;
		bFirstNum = true;
        for(iRow = 0; iRow < AnsiString(pInfoGlaph.SOKU_SU).ToIntDef(0);iRow ++)
        {
			switch(GraphLotAddress[i1].GRID)
			{
        	case 1:
            	sBuf = SGr_vSOKU_SYUKA->Cells[GraphLotAddress[i1].COL][iGraphRow+iRow+1].Trim();
				if(sBuf.Length()!=0 && sBuf != "�s�v")
				{
                    //2003.05.08 E.Takase Add��
                    bRtn = Form1->ConvDoubleDefS(sBuf,"0.00",sBuf,&sBufConv);
                    if ( bRtn ) {
                    	d1 = Form1->ConvDoubleDefD(sBuf,0.0);
                    } else {
                    	bError = true;
                    }
                    //2003.05.08 E.Takase Add��
                    //2003.05.08 E.Takase Add �R�����g��
                	//try{
					//	d1 = sBuf.ToDouble();
					//}
					//catch(EConvertError& e){
                	//	bError = true;
					//}
					//catch(...){
                	//	bError = true;
					//}
                    //2003.05.08 E.Takase Add �R�����g��
					if( !bError)
					{
						nCount++;
						dSum += d1;
						iNCnt ++;
						dSigumaRes[ iRes ] = d1;
						iRes ++;
						if( bFirstNum == true )
						{
                        	GraphLotAddress[i1].MAX = d1;
                        	GraphLotAddress[i1].MIN = d1;
							bFirstNum = false;
						}
						else
						{
                        	if(GraphLotAddress[i1].MAX < d1) GraphLotAddress[i1].MAX = d1;
                        	if(GraphLotAddress[i1].MIN > d1) GraphLotAddress[i1].MIN = d1;
						}
					}
				}
				break;
        	case 2:
            	sBuf = SGr_vRIRE_SYUKA->Cells[GraphLotAddress[i1].COL][iGraphRow+iRow+1].Trim();
				if(sBuf.Length()!=0 && sBuf != "�s�v")
				{
                    //2003.05.08 E.Takase Add��
                    bRtn = Form1->ConvDoubleDefS(sBuf,"0.00",sBuf,&sBufConv);
                    if ( bRtn ) {
                    	d1 = Form1->ConvDoubleDefD(sBuf,0.0);
                    } else {
                    	bError = true;
                    }
                    //2003.05.08 E.Takase Add��
                    //2003.05.08 E.Takase Add �R�����g��
                	//try{
					//	d1 = sBuf.ToDouble();
					//}
					//catch(EConvertError& e){
                	//	bError = true;
					//}
					//catch(...){
                	//	bError = true;
					//}
                    //2003.05.08 E.Takase Add �R�����g��
					if( !bError)
					{
						dSum += d1;
 						nCount++;
						iNCnt ++;
						dSigumaRes[ iRes ] = d1;
						iRes ++;
						if( bFirstNum == true )
						{
                        	GraphLotAddress[i1].MAX = d1;
                        	GraphLotAddress[i1].MIN = d1;
							bFirstNum = false;
						}
						else
						{
                        	if(GraphLotAddress[i1].MAX < d1) GraphLotAddress[i1].MAX = d1;
                        	if(GraphLotAddress[i1].MIN > d1) GraphLotAddress[i1].MIN = d1;
						}
					}
				}
				break;
        	case 3:
            	sBuf = SGr_vSOKU_SOZAI->Cells[GraphLotAddress[i1].COL][iGraphRow+iRow+1].Trim();
				if(sBuf.Length()!=0 && sBuf != "�s�v")
				{
                    //2003.05.08 E.Takase Add��
                    bRtn = Form1->ConvDoubleDefS(sBuf,"0.00",sBuf,&sBufConv);
                    if ( bRtn ) {
                    	d1 = Form1->ConvDoubleDefD(sBuf,0.0);
                    } else {
                    	bError = true;
                    }
                    //2003.05.08 E.Takase Add��
                    //2003.05.08 E.Takase Add �R�����g��
                	//try{
					//	d1 = sBuf.ToDouble();
					//}
					//catch(EConvertError& e){
                	//	bError = true;
					//}
					//catch(...){
                	//	bError = true;
					//}
                    //2003.05.08 E.Takase Add �R�����g��
					if( !bError)
					{
						dSum += d1;
						nCount++;
						iNCnt ++;
						dSigumaRes[ iRes ] = d1;
						iRes ++;
						if( bFirstNum == true )
						{
                        	GraphLotAddress[i1].MAX = d1;
                        	GraphLotAddress[i1].MIN = d1;
							bFirstNum = false;
						}
						else
						{
                        	if(GraphLotAddress[i1].MAX < d1) GraphLotAddress[i1].MAX = d1;
                        	if(GraphLotAddress[i1].MIN > d1) GraphLotAddress[i1].MIN = d1;
						}
					}
				}
				break;
        	case 4:
            	sBuf = SGr_vRIRE_SOZAI->Cells[GraphLotAddress[i1].COL][iGraphRow+iRow+1].Trim();
				if(sBuf.Length()!=0 && sBuf != "�s�v")
				{
                    //2003.05.08 E.Takase Add��
                    bRtn = Form1->ConvDoubleDefS(sBuf,"0.00",sBuf,&sBufConv);
                    if ( bRtn ) {
                    	d1 = Form1->ConvDoubleDefD(sBuf,0.0);
                    } else {
                    	bError = true;
                    }
                    //2003.05.08 E.Takase Add��
                    //2003.05.08 E.Takase Add �R�����g��
                	//try{
					//	d1 = sBuf.ToDouble();
					//}
					//catch(EConvertError& e){
                	//	bError = true;
					//}
					//catch(...){
                	//	bError = true;
					//}
                    //2003.05.08 E.Takase Add �R�����g��
					if( !bError)
					{
						nCount++;
						dSum += d1;
						iNCnt ++;
						dSigumaRes[ iRes ] = d1;
						iRes ++;
						if( bFirstNum == true )
						{
                        	GraphLotAddress[i1].MAX = d1;
                        	GraphLotAddress[i1].MIN = d1;
							bFirstNum = false;
						}
						else
						{
                        	if(GraphLotAddress[i1].MAX < d1) GraphLotAddress[i1].MAX = d1;
                        	if(GraphLotAddress[i1].MIN > d1) GraphLotAddress[i1].MIN = d1;
						}
					}
				}
				break;
			default:
				break;
			}
		}
		GraphLotAddress[i1].SUM = dSum;
		GraphLotAddress[i1].NCNT = iNCnt;
		dSigumaSum += dSum;
		dSigumaNum += iNCnt;
		if(iNCnt != 0 )
		{
			GraphLotAddress[i1].AVE = dSum/iNCnt;
		}
		else
		{
			GraphLotAddress[i1].AVE = 0;
		}
		dSum = 0;
		iNCnt = 0;
    }

//�O���t�`��i���j

	if(bKASOU_MOVE == true ) return;



	CopyBeforeGlaph();				//������������O�ɃO���t�̕���
// 2003/05/19 A.Tamura
//	if(1)
//    {
        Form1->Lab_skInfo_Kikaku2->Caption = AnsiString(KIKAKU_MOJI.HANI);
		Form1->Lab_skInfo_KIKAKU2UP->Left = Form1->Lab_skInfo_Kikaku2->Width+Form1->Lab_skInfo_Kikaku2->Left;
        Form1->Lab_skInfo_KIKAKU2UP->Caption = AnsiString(KIKAKU_MOJI.UPLIMIT);
        Form1->Lab_skInfo_KIKAKU2LOW->Left = Form1->Lab_skInfo_Kikaku2->Width+Form1->Lab_skInfo_Kikaku2->Left;
        Form1->Lab_skInfo_KIKAKU2LOW->Caption = AnsiString(KIKAKU_MOJI.LOLIMIT);
		if( GridNo == 1 || GridNo == 3)
        {
        	Form1->Pnl_skInfo_vLOTBNG2->Caption = " " + Form1->SGr_tSOKU->Cells[iLotCol][0];
        }
        else
        {
        	Form1->Pnl_skInfo_vLOTBNG2->Caption = " " + Form1->SGr_tRIRE->Cells[iLotCol][0];
        }
        Form1->Pnl_skInfo_vKENSA2->Caption = " " + AnsiString(pInfoGlaph.KOMK_NM) + AnsiString(pInfoGlaph.KOMK_SUB);
        Form1->Pnl_skInfo_vKIKI2->Caption = " " + AnsiString(pInfoGlaph.KIKI_NM);
        // A.T 2003/05/07
    	Form1->Pnl_skInfo_vSOKUUSER2->Caption = AnsiString(pInfoGlaph.UPDNAME);
        // �^�C�g���F�ύX
		if( GridNo == 3 || GridNo == 4)
        {
            // �f�ލ���
        	Form1->Pnl_skInfo_tLOTBNG2->Color	= (TColor)0x0062FFFF;
        	Form1->Pnl_skInfo_tSOKUUSER2->Color	= (TColor)0x0062FFFF;
        	Form1->Pnl_skInfo_tKENSA2->Color	= (TColor)0x0062FFFF;
        	Form1->Pnl_skInfo_tKIKI2->Color		= (TColor)0x0062FFFF;
        	Form1->Pnl_skInfo_tKIKAKU2->Color	= (TColor)0x0062FFFF;
        }
        else
        {
            // �o�׍���
        	Form1->Pnl_skInfo_tLOTBNG2->Color	= (TColor)0x00FEE7BA;
        	Form1->Pnl_skInfo_tSOKUUSER2->Color	= (TColor)0x00FEE7BA;
        	Form1->Pnl_skInfo_tKENSA2->Color	= (TColor)0x00FEE7BA;
        	Form1->Pnl_skInfo_tKIKI2->Color		= (TColor)0x00FEE7BA;
        	Form1->Pnl_skInfo_tKIKAKU2->Color	= (TColor)0x00FEE7BA;
		}
// 2003/05/19 A.Tamura
//    }
	bDrawGlaph = false;

for(iLoop=0;iLoop < 2;iLoop++)
{
    ImgGlaphSYUKA->Canvas->Pen->Color = clBlack;
    ImgGlaphSYUKA->Canvas->Pen->Style = (TPenStyle)bsSolid;
    ImgGlaphSYUKA->Canvas->Pen->Width = 1;       //���̑���
    ImgGlaphSYUKA->Canvas->Font->Size = 7;       //�����̃T�C�Y

	ImgGlaphSYUKA->Canvas->Brush->Color = clWhite;
	ImgGlaphSYUKA->Canvas->Rectangle(0,0,ImgGlaphSYUKA->Width,ImgGlaphSYUKA->Height);

//�O���t�`��̍ۂɎg�p����萔�̐ݒ�
    CharWidth 	= ImgGlaphSYUKA->Canvas->Font->Height * 3;   //���[��Y���̊Ԃ̗]��
    CharHeight 	= ImgGlaphSYUKA->Canvas->Font->Height * 2;  //���[��X���̊Ԃ̗]��
    //FontHeight 	= ImgGlaphSYUKA->Canvas->Font->Height;      //�����̍���
	//ImageH = ImgGlaphSYUKA->Height - 2* CharHeight;
    ImageW = ImgGlaphSYUKA->Width - CharWidth;

//�O���t�̕`��
    ImgGlaphSYUKA->Canvas->Brush->Color =clWhite;
    ImgGlaphSYUKA->Canvas->Pen->Color =clGray;
    ImgGlaphSOZAI->Canvas->Brush->Color =clWhite;
    ImgGlaphSOZAI->Canvas->Pen->Color =clGray;

//������C��
    if( GridNo == 1 || GridNo == 2 || GridNo == 3 || GridNo == 4 ){
		if((AnsiString(pInfoGlaph.KIKA_TYPE).ToIntDef(0) == 1)
		&& (AnsiString(pInfoGlaph.KIKA_KIND).ToIntDef(0) == 3))
		{
			ImgGlaphSYUKA->Canvas->Pen->Color = clGray;
		}
		else
		{
			ImgGlaphSYUKA->Canvas->Pen->Color = clRed;
		}
    	y = 1 * (ImgGlaphSYUKA->Height/9);
		ImgGlaphSYUKA->Canvas->Rectangle(1,y-1,ImgGlaphSYUKA->Width-1,y);
    }

//��������̊ԃ��C��
    yst = 1 * (ImgGlaphSYUKA->Height/9);
	x=( 7 * (ImgGlaphSYUKA->Height/9) );
    if( GridNo == 1 || GridNo == 2 || GridNo == 3 || GridNo == 4 ){
    	for(i1=1;i1<8;i1++)
    	{
            if( i1 == 2 || i1 == 4 || i1 == 6 ) {
       			ImgGlaphSYUKA->Canvas->Pen->Color = clGray;
            } else {
       			ImgGlaphSYUKA->Canvas->Pen->Color = clSilver;
            }
            y = yst + ( i1 * (x/8) );
			ImgGlaphSYUKA->Canvas->Rectangle(1,y,ImgGlaphSYUKA->Width-1,y+1);
		}
    }

//�������C��
    if( GridNo == 1 || GridNo == 2 || GridNo == 3 || GridNo == 4 ){
		if((AnsiString(pInfoGlaph.KIKA_TYPE).ToIntDef(0) == 1)
		&& (AnsiString(pInfoGlaph.KIKA_KIND).ToIntDef(0) == 2))
		{
			ImgGlaphSYUKA->Canvas->Pen->Color = clGray;
		}
		else
		{
			ImgGlaphSYUKA->Canvas->Pen->Color = clRed;
		}
    	y = 8 * (ImgGlaphSYUKA->Height/9);
		ImgGlaphSYUKA->Canvas->Rectangle(1,y-1,ImgGlaphSYUKA->Width-1,y);
    }

//x�����C��
	ImgGlaphSYUKA->Canvas->Pen->Color = clGray;
	dMaxMinHeight = (ImgGlaphSYUKA->Height/9)*8 - (ImgGlaphSYUKA->Height/9);
	for(i1 = 0;i1 < 10;i1++)
	{
		x =	((ImageW) / 12) * (9-i1)+ImgGlaphSYUKA->Canvas->Font->Size+20;
		ImgGlaphSYUKA->Canvas->Rectangle(x+10,1,x+11,ImgGlaphSYUKA->Height-1);
	}

//�K�i�̕\��
	ImgGlaphSYUKA->Canvas->Font->Size = 9;
    if( pInfoGlaph.KIKA_DECI > 0 ){
    	sDeci1 = "0.0";
    	for(i1 = 1;i1 < AnsiString(pInfoGlaph.KIKA_DECI).ToIntDef(0);i1++)
    	{
    		sDeci1 +="0";
    	}
   		sDeci2 = sDeci1 + "0";
	}
    else {
    	sDeci1 = "0";
		sDeci2 = "0.0";
    }

    switch(AnsiString(pInfoGlaph.KIKA_TYPE).ToIntDef(0))
	{
	case 1:	//�͈͎w��̏ꍇ
    	switch(AnsiString(pInfoGlaph.KIKA_KIND).ToIntDef(0))
		{
        case 1:
		//�͈�
			dGMin = pInfoGlaph.MIN;
			dGMax = pInfoGlaph.MAX;
			dGMin = pInfoGlaph.GMIN;
			dGMax = pInfoGlaph.GMAX;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMax));		//���
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMin));     //����
			dR = dGMin + ((dGMax - dGMin) / 2);		// �K�i�̒��S
    		ImgGlaphSYUKA->Canvas->TextOutA(2,4.5*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci2,dR));     	//���S
			break;
		case 2:
		//�ȉ�
			dGMax = pInfoGlaph.MAX;
			dGMax = pInfoGlaph.GMAX;
            //2003.05.08 E.Takase Add��
            bRtn = Form1->ConvDoubleDefS(pnlSYUKAMin->Caption,"0.00",pnlSYUKAMin->Caption,&sBufConv);
            if ( bRtn ) {
            	dGMin = ((int)Form1->ConvDoubleDefD(pnlSYUKAMin->Caption,0.0))-1;
            	if( dGMax < dGMin ) dGMax = (int)(dGMax / 10);
            } else {
            	dGMin = 0.0;
            }
            //2003.05.08 E.Takase Add��
            //2003.05.08 E.Takase Add �R�����g��
			//try{
			//	dGMin = ((int)AnsiString(pnlSYUKAMin->Caption).ToDouble())-1;
            //    if( dGMax < dGMin ) dGMax = (int)(dGMax / 10);
			//}
			//catch(EConvertError& e){
            //    dGMin = 0.0;
			//}
			//catch(...){
            //    dGMin = 0.0;
			//}
            //2003.05.08 E.Takase Add �R�����g��
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMax));		//���
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMin));     //����
			dR = dGMin + ((dGMax - dGMin) / 2);		// �K�i�̒��S
    		ImgGlaphSYUKA->Canvas->TextOutA(2,4.5*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci2,dR));     	//���S
			break;
        case 3:
		//�ȏ�
			dGMin = pInfoGlaph.MIN;
			dGMin = pInfoGlaph.GMIN;
            //2003.05.08 E.Takase Add��
            bRtn = Form1->ConvDoubleDefS(pnlSYUKAMax->Caption,"0.00",pnlSYUKAMax->Caption,&sBufConv);
            if ( bRtn ) {
				dGMax = ((int)Form1->ConvDoubleDefD(pnlSYUKAMax->Caption,0.0))+1;
            	if( dGMax < dGMin ) dGMax = (int)(dGMin * 10);
            } else {
            	dGMax = 0.0;
            }
            //2003.05.08 E.Takase Add��
            //2003.05.08 E.Takase Add �R�����g��
			//try{
			//	dGMax = ((int)AnsiString(pnlSYUKAMax->Caption).ToDouble())+1;
            //    if( dGMax < dGMin ) dGMax = (int)(dGMin * 10);
			//}
			//catch(EConvertError& e){
            //    dGMax = 0.0;
			//}
			//catch(...){
            //    dGMax = 0.0;
			//}
            //2003.05.08 E.Takase Add �R�����g��
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMax));		//���
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMin));     //����
			dR = dGMin + ((dGMax - dGMin) / 2);		// �K�i�̒��S
    		ImgGlaphSYUKA->Canvas->TextOutA(2,4.5*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci2,dR));     	//���S
			break;
		default:
			break;
		}
        break;
	case 2:
		switch(AnsiString(pInfoGlaph.KIKA_KIND).ToIntDef(0))
		{
		case 1:
			dGMin = pInfoGlaph.MIN;
			dGMax = pInfoGlaph.MAX;
			dGMin = pInfoGlaph.GMIN;
			dGMax = pInfoGlaph.GMAX;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMax));		//���
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMin));		//����
			dR = dGMin + ((dGMax - dGMin) / 2);		// �K�i�̒��S
    		ImgGlaphSYUKA->Canvas->TextOutA(2,4.5*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci2,dR));     	//���S
            break;
		case 2:
			dGMin = pInfoGlaph.MIN;
			dGMax = pInfoGlaph.MAX;
			dGMin = pInfoGlaph.GMIN;
			dGMax = pInfoGlaph.GMAX;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMax));		//���
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMin));		//����
			dR = dGMin + ((dGMax - dGMin) / 2);		// �K�i�̒��S
    		ImgGlaphSYUKA->Canvas->TextOutA(2,4.5*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci2,dR));     	//���S
            break;
		case 3:
			dGMin = pInfoGlaph.MIN;
			dGMax = pInfoGlaph.MAX;
			dGMin = pInfoGlaph.GMIN;
			dGMax = pInfoGlaph.GMAX;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMax));		//���
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci1,dGMin));		//����
			dR = dGMin + ((dGMax - dGMin) / 2);		// �K�i�̒��S
    		ImgGlaphSYUKA->Canvas->TextOutA(2,4.5*(ImgGlaphSYUKA->Height/9)-6,FormatFloat(sDeci2,dR));     	//���S
            break;
		default:
			break;
		}
        break;
	case 3:
        //ImgGlaphSYUKA->Canvas->Brush->Color  = clWhite;
		//ImgGlaphSYUKA->Canvas->FloodFill(0,0,ImgGlaphSYUKA->Width,ImgGlaphSYUKA->Height);
		dGMax = 0.0;
		dGMin = 0.0;
        break;
	default:
		break;
	}
	ImgGlaphSYUKA->Canvas->Font->Size = 7;
	if(fabs(dGMax) < 0.01) dGMax = 0.0;
	if(fabs(dGMin) < 0.01) dGMin = 0.0;
	if(dGMax-dGMin == 0.0 )
	{
		if(AnsiString(pInfoGlaph.KIKA_TYPE).ToIntDef(0)!=3)
        {
			ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
		}

        // �H���\�͂̏�����
		Form1->pnlSYUKANCount->Caption 		= "0";
		Form1->pnlSYUKAMin->Caption 		= "0.00";
		Form1->pnlSYUKAMax->Caption 		= "0.00";
		Form1->pnlSYUKAAve->Caption 		= "0.000";
		Form1->pnlSYUKAR->Caption 			= "0.00000";
		Form1->pnlSYUKASiguma->Caption 		= "0.00000";
		Form1->pnlSYUKACp->Font->Color		= clBlack;
        Form1->pnlSYUKACp->Caption 			= "0.00";
        Form1->pnlSYUKACpk->Color			= clWindow;
        Form1->pnlSYUKACpk->Font->Color		= clBlack;
		Form1->pnlSYUKACpk->Caption			= "0.00";
        Form1->pnlSYUKAK->Color				= clWindow;
		Form1->pnlSYUKAK->Caption			= "0.000";
		Form1->pnlSYUKANGPercent->Caption 	= "0.000";

		return;
	}
	switch(GridNo)
	{
    case 1:
	case 2:
	case 3:
	case 4:
		dOnePitch = dMaxMinHeight * 1/(dGMax-dGMin);
		for(i1 = 0;i1 < iLotMax;i1++)
		{
			x =	((ImageW) / 12) * (9-i1)+ImgGlaphSYUKA->Canvas->Font->Size+20;
			if( i1 == 0 )
			{
            	ImgGlaphSYUKA->Canvas->Font->Color = clBlue;	//���݃J�[�\�������郍�b�g�Ȃ�F�\��
				ImgGlaphSYUKA->Canvas->Pen->Color = clBlue;
				ImgGlaphSYUKA->Canvas->Brush->Color = clWhite;
			}
			else
			{
				ImgGlaphSYUKA->Canvas->Font->Color = clBlack;	//���݃J�[�\�������郍�b�g�Ȃ�F�\��
				ImgGlaphSYUKA->Canvas->Pen->Color = clBlack;
				ImgGlaphSYUKA->Canvas->Brush->Color = clWhite;
            }
			ImgGlaphSYUKA->Canvas->TextOutA(x,114,GraphLotAddress[i1].LOTNAME);
//�͈͂̑уO���t�̕\��
			if( i1 == 0 )
			{
				ImgGlaphSYUKA->Canvas->Brush->Color = clBlue;
			}
			else
			{
				ImgGlaphSYUKA->Canvas->Brush->Color = clBlack;
            }
			d1 = GraphLotAddress[i1].MIN * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			d2 = GraphLotAddress[i1].MAX * dOnePitch * -1;
			d2 = dGMax * dOnePitch + d2+((ImgGlaphSYUKA->Height/9)-1);
			if( d1 < 0.001) d1 = 0;
			if( d2 < 0.001) d2 = 0;
			if( d1 > 9999999999 ) d1 = 9999999999;
			if( d2 > 9999999999 ) d2 = 9999999999;
            ImgGlaphSYUKA->Canvas->Rectangle(x+9,d2,x+11,d1);
//���ϒl�̕\��
			d1 = GraphLotAddress[i1].AVE * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			if( d1 < 0.001) d1 = 0;
			if( d1 > 9999999999 ) d1 = 9999999999;
			ImgGlaphSYUKA->Canvas->Rectangle(x+7,d1-2,x+13,d1+2);
//�ő�l�̕\��
			d1 = GraphLotAddress[i1].MAX * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			if( d1 < 0.001) d1 = 0;
			if( d1 > 9999999999 ) d1 = 9999999999;
			ImgGlaphSYUKA->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//�ŏ��l�̕\��
			d1 = GraphLotAddress[i1].MIN * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			if( d1 < 0.001) d1 = 0;
			if( d1 > 9999999999 ) d1 = 9999999999;
			ImgGlaphSYUKA->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//PENCOLOR���f�t�H���g�ɖ߂�
			ImgGlaphSYUKA->Canvas->Pen->Color = clBlack;
			ImgGlaphSYUKA->Canvas->Brush->Color = clWhite;
		}
        ImgGlaphSYUKA->Canvas->Brush->Color = clWhite;
		break;
 	default:
		break;
    }
	if(iLoop != 0) break;	//2��̃��[�v�̓O���t�`��̂���
//�V�O�}�̎Z�o
    dMax = dSigumaRes[ 0 ];
    dMin = dSigumaRes[ 0 ];
	dSiguma = 0;
	iNGCount = 0;
	if( nCount > 1 )		//2���ȏ�Ώۃ��b�g�����邩
	{
    	dSigumaAve = dSigumaSum / nCount;
    	for(i1 = 0;i1 < nCount;i1++)
		{
        	dSiguma += (dSigumaRes[ i1 ]-dSigumaAve)*(dSigumaRes[ i1 ]-dSigumaAve);
        	if(dMax <  dSigumaRes[ i1 ]) dMax = dSigumaRes[ i1 ];
        	if(dMin >  dSigumaRes[ i1 ]) dMin = dSigumaRes[ i1 ];
			if((dGMin > dSigumaRes[ i1 ]) || (dGMax < dSigumaRes[ i1 ])) iNGCount++;
		}
		dSiguma = sqrt(dSiguma / (nCount-1));
	}
	dR = dGMax - dGMin;		// �K�i�̕�
	if( dR != 0.0 )
	{
		dK = (fabs(dSigumaAve)-(fabs(dGMin)+fabs(dR/2)))/(dR/2);
	}
	if(double(nCount) != 0.0)
	{
		dNGPercent = (double(iNGCount)/double(nCount)) *100.0;
	}
	if(dSiguma != 0)
	{
		if( AnsiString(pInfoGlaph.KIKA_TYPE).ToIntDef(0) == 1 &&
			AnsiString(pInfoGlaph.KIKA_KIND).ToIntDef(0) == 2 ){
            // �ȉ�
            //2003.05.08 E.Takase Add��
            bRtn = Form1->ConvDoubleDefS(pInfoGlaph.KIKA_NUM2,"0.00",pInfoGlaph.KIKA_NUM2,&sBufConv);
            if ( bRtn ) {
            	dCp = (Form1->ConvDoubleDefD(pInfoGlaph.KIKA_NUM2,0.0) - dSigumaAve) / (3*dSiguma);
            } else {
            	dCp = 0.0;
            }
            //2003.05.08 E.Takase Add��
            //2003.05.08 E.Takase Add �R�����g��
			//try{
	        //    dCp = (AnsiString(pInfoGlaph.KIKA_NUM2).ToDouble() - dSigumaAve) / (3*dSiguma);
			//}
			//catch(EConvertError& e){
            //    dCp = 0.0;
			//}
			//catch(...){
            //    dCp = 0.0;
			//}
            //2003.05.08 E.Takase Add �R�����g��
			dCpk = 0.0;
		}
		else if( AnsiString(pInfoGlaph.KIKA_TYPE).ToIntDef(0) == 1 &&
			     AnsiString(pInfoGlaph.KIKA_KIND).ToIntDef(0) == 3 ){
            // �ȏ�
            //2003.05.08 E.Takase Add��
            bRtn = Form1->ConvDoubleDefS(pInfoGlaph.KIKA_NUM1,"0.00",pInfoGlaph.KIKA_NUM1,&sBufConv);
            if ( bRtn ) {
	            dCp = (dSigumaAve - Form1->ConvDoubleDefD(pInfoGlaph.KIKA_NUM1,0.0)) / (3*dSiguma);
            } else {
            	dCp = 0.0;
            }
            //2003.05.08 E.Takase Add��
            //2003.05.08 E.Takase Add �R�����g��
			//try{
            //	dCp = (dSigumaAve - AnsiString(pInfoGlaph.KIKA_NUM1).ToDouble()) / (3*dSiguma);
			//}
			//catch(EConvertError& e){
            //    dCp = 0.0;
			//}
			//catch(...){
            //    dCp = 0.0;
			//}
            //2003.05.08 E.Takase Add �R�����g��
			dCpk = 0.0;
		}
        else {
            // ����
        	dCp = dR / (6*dSiguma);
			dCpk = (1-dK)*dCp;
		}
	}
	else {
       	dCp = 0.0;
		dCpk = 0.0;
	}
	dR = dMax - dMin;		// ����l�̕�

//�H���\�͂̕\��

	switch(GridNo)
	{
    case 1:
	case 2:
	case 3:
	case 4:
        if( nCount > 0 ){
	        if( pInfoGlaph.VALUE_DECI > 0 ){
				sDeci1 = "0.0";
	        	for(i1 = 1;i1 < AnsiString(pInfoGlaph.VALUE_DECI).ToIntDef(0);i1++)
	        	{
	        		sDeci1 +="0";
	        	}
	       		sDeci2 = sDeci1 + "0";
	        }
	        else {
				sDeci1 = "0";
				sDeci2 = "0.0";
	        }

			Form1->pnlSYUKANCount->Caption 		= nCount;
			Form1->pnlSYUKAMin->Caption 		= FormatFloat(sDeci1,dMin);
			Form1->pnlSYUKAMax->Caption 		= FormatFloat(sDeci1,dMax);
			Form1->pnlSYUKAAve->Caption 		= FormatFloat(sDeci2,dSigumaAve);
			Form1->pnlSYUKAR->Caption 			= FormatFloat("0.00000",dR);
			Form1->pnlSYUKASiguma->Caption 		= FormatFloat("0.00000",dSiguma);

			if( dCp < 1.33 )	Form1->pnlSYUKACp->Font->Color = clRed;
			else				Form1->pnlSYUKACp->Font->Color = clBlack;
			Form1->pnlSYUKACp->Caption 			= FormatFloat("0.00",dCp);

			if( AnsiString(pInfoGlaph.KIKA_TYPE).ToIntDef(0) == 1 &&
				(AnsiString(pInfoGlaph.KIKA_KIND).ToIntDef(0) == 2 ||
				 AnsiString(pInfoGlaph.KIKA_KIND).ToIntDef(0) == 3 ) ){
	            Form1->pnlSYUKACpk->Color		= clBtnFace;
	            Form1->pnlSYUKAK->Color			= clBtnFace;
	            Form1->pnlSYUKACpk->Font->Color	= clBlack;
				Form1->pnlSYUKACpk->Caption		= "0.00";
				Form1->pnlSYUKAK->Caption		= "0.000";
	        }
	        else {
	            Form1->pnlSYUKACpk->Color		= clWindow;
	            Form1->pnlSYUKAK->Color			= clWindow;
				if( dCpk < 1.33 )	Form1->pnlSYUKACpk->Font->Color = clRed;
				else				Form1->pnlSYUKACpk->Font->Color = clBlack;
				Form1->pnlSYUKACpk->Caption		= FormatFloat("0.00",dCpk);
				Form1->pnlSYUKAK->Caption		= FormatFloat("0.000",dK);
	        }
			Form1->pnlSYUKANGPercent->Caption 	= FormatFloat("0.000",dNGPercent);
        }
        else {
			Form1->pnlSYUKANCount->Caption 		= "0";
			Form1->pnlSYUKAMin->Caption 		= sDeci1;
			Form1->pnlSYUKAMax->Caption 		= sDeci1;
			Form1->pnlSYUKAAve->Caption 		= sDeci2;
			Form1->pnlSYUKAR->Caption 			= "0.00000";
			Form1->pnlSYUKASiguma->Caption 		= "0.00000";
			Form1->pnlSYUKACp->Font->Color		= clBlack;
            Form1->pnlSYUKACp->Caption 			= "0.00";
            Form1->pnlSYUKACpk->Color			= clWindow;
            Form1->pnlSYUKACpk->Font->Color		= clBlack;
			Form1->pnlSYUKACpk->Caption			= "0.00";
            Form1->pnlSYUKAK->Color				= clWindow;
			Form1->pnlSYUKAK->Caption			= "0.000";
			Form1->pnlSYUKANGPercent->Caption 	= "0.000";
        }
		break;
    default:
		break;
	}
}
}
//---------------------------------------------------------------------------
//���O�̃O���t�̕`��i���݂̃O���t�̃R�s�[�j
void __fastcall TForm1::CopyBeforeGlaph(void)
{
	int i1;
	bool bMIDASI_OK;
 	TRect r;
	if( bKASOU_MOVE == true ) return;
// k.y 2003.05.17
//  if(!hOldInfoGlaph)
    if((AnsiString(pOldInfoGlaph.KOMK_NO).ToIntDef(0) != AnsiString(pInfoGlaph.KOMK_NO).ToIntDef(0))
    || (AnsiString(pOldInfoGlaph.KIKI_NO).ToIntDef(0) != AnsiString(pInfoGlaph.KIKI_NO).ToIntDef(0))
	|| (AnsiString(pOldInfoGlaph.UNQ_NO).ToIntDef(0)  != AnsiString(pInfoGlaph.UNQ_NO).ToIntDef(0))
	|| (AnsiString(pOldInfoGlaph.HINBAN_SK)			 != AnsiString(pInfoGlaph.HINBAN_SK))
	|| (AnsiString(pOldInfoGlaph.KOMK_NM)			 != AnsiString(pInfoGlaph.KOMK_NM))
	|| (AnsiString(pOldInfoGlaph.KOMK_SUB)			 != AnsiString(pInfoGlaph.KOMK_SUB)))
	{

    	Form1->pnlSOZAIAve->Caption 	= Form1->pnlSYUKAAve->Caption;
		Form1->pnlSOZAICp->Caption 		= Form1->pnlSYUKACp->Caption;
		Form1->pnlSOZAICpk->Caption 	= Form1->pnlSYUKACpk->Caption;
		Form1->pnlSOZAIK->Caption 		= Form1->pnlSYUKAK->Caption;
		Form1->pnlSOZAIMax->Caption 	= Form1->pnlSYUKAMax->Caption;
		Form1->pnlSOZAIMin->Caption 	= Form1->pnlSYUKAMin->Caption;
		Form1->pnlSOZAINCount->Caption 	= Form1->pnlSYUKANCount->Caption;
		Form1->pnlSOZAINGPercent->Caption = Form1->pnlSYUKANGPercent->Caption;   
		Form1->pnlSOZAIR->Caption 		= Form1->pnlSYUKAR->Caption;
		Form1->pnlSOZAISiguma->Caption 	= Form1->pnlSYUKASiguma->Caption;
		Form1->Pnl_skInfo_vKENSA1->Caption 	= Form1->Pnl_skInfo_vKENSA2->Caption;
		Form1->Pnl_skInfo_vKIKAKU1->Caption = Form1->Pnl_skInfo_vKIKAKU2->Caption;
		Form1->Pnl_skInfo_vKIKI1->Caption 	= Form1->Pnl_skInfo_vKIKI2->Caption;
		Form1->Pnl_skInfo_vLOTBNG1->Caption = Form1->Pnl_skInfo_vLOTBNG2->Caption;
		Form1->Pnl_skInfo_vSOKUUSER1->Caption = Form1->Pnl_skInfo_vSOKUUSER2->Caption;
		Form1->Lab_skInfo_Kikaku1->Caption = Form1->Lab_skInfo_Kikaku2->Caption;
    	Form1->Lab_skInfo_KIKAKU1UP->Left = Form1->Lab_skInfo_KIKAKU2UP->Left;
    	Form1->Lab_skInfo_KIKAKU1UP->Caption = Form1->Lab_skInfo_KIKAKU2UP->Caption ;
    	Form1->Lab_skInfo_KIKAKU1LOW->Left = Form1->Lab_skInfo_KIKAKU2LOW->Left;
    	Form1->Lab_skInfo_KIKAKU1LOW->Caption = Form1->Lab_skInfo_KIKAKU2LOW->Caption;
       	Form1->Pnl_skInfo_tLOTBNG1->Color	= Form1->Pnl_skInfo_tLOTBNG2->Color;
       	Form1->Pnl_skInfo_tSOKUUSER1->Color	= Form1->Pnl_skInfo_tSOKUUSER2->Color;
       	Form1->Pnl_skInfo_tKENSA1->Color	= Form1->Pnl_skInfo_tKENSA2->Color;
       	Form1->Pnl_skInfo_tKIKI1->Color		= Form1->Pnl_skInfo_tKIKI2->Color;
       	Form1->Pnl_skInfo_tKIKAKU1->Color	= Form1->Pnl_skInfo_tKIKAKU2->Color;
// k.y 2003.05.17
//      if(hOldInfoGlaph)
        r = Rect(0, 0, Form1->ImgGlaphSYUKA->Width, Form1->ImgGlaphSYUKA->Height);
        Form1->ImgGlaphSOZAI->Canvas->CopyRect(r,Form1->ImgGlaphSYUKA->Canvas,r);
        Form1->ImgGlaphSOZAI->Canvas->CopyMode = cmSrcCopy;
        Form1->ImgGlaphSOZAI->Canvas->Refresh();
		Form1->Refresh();
		KMCH_BEEP(0);
	//�V�������o���ʒu�̎Z�o
		i1 = 0;
		bMIDASI_OK = false;
        if(0 < iOrCnt)
		{
	        while(1)
    	    {	try{
        		if((AnsiString(pORDATA[i1].KOMK_NO).ToIntDef(0) == AnsiString(pInfoGlaph.KOMK_NO).ToIntDef(0))
            	&&(AnsiString(pORDATA[i1].KIKI_NO).ToIntDef(0) 	== AnsiString(pInfoGlaph.KIKI_NO).ToIntDef(0))
	            &&(AnsiString(pORDATA[i1].UNQ_NO).ToIntDef(0) 	== AnsiString(pInfoGlaph.UNQ_NO).ToIntDef(0))
				&&(AnsiString(pORDATA[i1].HINBAN_SK)     		== AnsiString(pInfoGlaph.HINBAN_SK))
	            &&(AnsiString(pORDATA[i1].KOMK_NM) 				== AnsiString(pInfoGlaph.KOMK_NM))
				&&(AnsiString(pORDATA[i1].KOMK_SUB)     		== AnsiString(pInfoGlaph.KOMK_SUB)))
				{
					NewMIDASI->Visible = true;
            		NewMIDASI->Parent = Pnl_InsName[i1];
	        		NewMIDASI->Left = Pnl_OrgInsName->Left;
    	    		NewMIDASI->Top = 0;
					NewMIDASI->Height = Pnl_InsName[i1]->Height-1;
					NewMIDASI->Width  = Pnl_InsName[i1]->Width-1;
					bMIDASI_OK = true;
	            	break;
				}
				}
				catch(...){
					NewMIDASI->Visible = false;
	            	break;
				}
				i1++;
				if(i1 >= iOrCnt){
					NewMIDASI->Visible = false;
	            	break;
				}
			}
		}
       	if(bMIDASI_OK != true )
        {
        	if(0 < iSOZAI_ORCNT)
			{
				i1 = 0;
                // k.y 2003.05.17
				//if(hSOZAI_OR_DATA)
                //if(1)
				//{
                while(1)                                     
                {
                    try{
						if((AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO).ToIntDef(0)	== AnsiString(pInfoGlaph.KOMK_NO).ToIntDef(0))
						&&( AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO).ToIntDef(0) 	== AnsiString(pInfoGlaph.KIKI_NO).ToIntDef(0))
        	    		&&( AnsiString(pSOZAI_OR_DATA[i1].UNQ_NO).ToIntDef(0) 	== AnsiString(pInfoGlaph.UNQ_NO).ToIntDef(0))
						&&( AnsiString(pSOZAI_OR_DATA[i1].HINBAN_SK)			 	== AnsiString(pInfoGlaph.HINBAN_SK))
						&&( AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM)			 	== AnsiString(pInfoGlaph.KOMK_NM))
						&&( AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB)			 	== AnsiString(pInfoGlaph.KOMK_SUB)))
						{
							NewMIDASI->Visible = true;
            				NewMIDASI->Parent = Pnl_SOZAI_InsName[i1];
	        				NewMIDASI->Left = 	Pnl_SOZAI_InsName[i1]->Left;
		        			NewMIDASI->Top = 0;
							NewMIDASI->Height = Pnl_SOZAI_InsName[i1]->Height-1;
							NewMIDASI->Width  = Pnl_SOZAI_InsName[i1]->Width-1;
        	    	        bMIDASI_OK = true;
	        	    		break;
						}
                    }
                    catch(...){
                        NewMIDASI->Visible = false;
                        break;
                    }
                    i1++;
                    if(i1 >= iSOZAI_ORCNT) {
                        NewMIDASI->Visible = false;
                        break;
                    }
                }
				//}
			}
		}
	//�V�������o���ʒu�̎Z�o
		i1 = 0;
		bMIDASI_OK = false;
        if(0 < iOrCnt)
		{
	        while(1)
    	    {
				try{
				if((AnsiString(pORDATA[i1].KOMK_NO).ToIntDef(0)	== AnsiString(pOldInfoGlaph.KOMK_NO).ToIntDef(0))
				&&(AnsiString( pORDATA[i1].KIKI_NO).ToIntDef(0) == AnsiString(pOldInfoGlaph.KIKI_NO).ToIntDef(0))
	            &&(AnsiString( pORDATA[i1].UNQ_NO).ToIntDef(0) 	== AnsiString(pOldInfoGlaph.UNQ_NO).ToIntDef(0))
				&&(AnsiString( pORDATA[i1].HINBAN_SK)			== AnsiString(pOldInfoGlaph.HINBAN_SK))
				&&(AnsiString( pORDATA[i1].KOMK_NM)				== AnsiString(pOldInfoGlaph.KOMK_NM))
				&&(AnsiString( pORDATA[i1].KOMK_SUB)			== AnsiString(pOldInfoGlaph.KOMK_SUB)))
				{
					OldMIDASI->Visible = true;
            		OldMIDASI->Parent = Pnl_InsName[i1];
	        		OldMIDASI->Left = Pnl_OrgInsName->Left;
    	    		OldMIDASI->Top = 0;
					OldMIDASI->Height = Pnl_InsName[i1]->Height-1;
					OldMIDASI->Width  = Pnl_InsName[i1]->Width-1;
					bMIDASI_OK = true;
	            	break;
				}
				}
				catch(...){
					OldMIDASI->Visible = false;
	            	break;
				}
				i1++;
				if(i1 >= iOrCnt){
					OldMIDASI->Visible = false;
	            	break;
				}
			}
        }
       	if(bMIDASI_OK != true )
        {
        	if(0 < iSOZAI_ORCNT)
			{
				i1 = 0;
                // k.y 2003.05.17
                //if(hSOZAI_OR_DATA)
                //if(1)
				//{                                               
                while(1)
                {
                    try{
                        if((AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO).ToIntDef(0) == AnsiString(pOldInfoGlaph.KOMK_NO).ToIntDef(0))
						&&(AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO).ToIntDef(0) == AnsiString(pOldInfoGlaph.KIKI_NO).ToIntDef(0))
        	    		&&(AnsiString(pSOZAI_OR_DATA[i1].UNQ_NO).ToIntDef(0) 	== AnsiString(pOldInfoGlaph.UNQ_NO).ToIntDef(0))
						&&(AnsiString(pSOZAI_OR_DATA[i1].HINBAN_SK)			 == AnsiString(pOldInfoGlaph.HINBAN_SK))
						&&(AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM)			 == AnsiString(pOldInfoGlaph.KOMK_NM))
						&&(AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB)			 == AnsiString(pOldInfoGlaph.KOMK_SUB)))
						{
							OldMIDASI->Visible = true;
            				OldMIDASI->Parent = Pnl_SOZAI_InsName[i1];
	        				OldMIDASI->Left = 	Pnl_SOZAI_InsName[i1]->Left;
		        			OldMIDASI->Top = 0;
							OldMIDASI->Height = Pnl_SOZAI_InsName[i1]->Height-1;
							OldMIDASI->Width  = Pnl_SOZAI_InsName[i1]->Width-1;
        	    	        bMIDASI_OK = true;
	        	    		break;
						}
                    }
                    catch(...){
                        OldMIDASI->Visible = false;
                        break;
                    }
                    i1++;
                    if(i1 >= iSOZAI_ORCNT){
                        OldMIDASI->Visible = false;
                        break;
                    }
                }
				//}
			}
		}
	//�@���CH�؂�ւ��^�C�~���O�͍��ڂ��ړ������Ƃ��ɔ�������
		if(AnsiString(pOldInfoGlaph.KIKI_NO) != AnsiString(pInfoGlaph.KIKI_NO))
		{
			switch(AnsiString(pInfoGlaph.KIKI_NO).ToIntDef(0))
    		{
	    	case 1:
	    		iPORT_NO = 0;
    	    	break;
	    	case 2:
    			iPORT_NO = 1;
	        	break;
		    default:
    			break;
			}
      	}                 
	}
    strcpy(pOldInfoGlaph.KOMK_NM,	pInfoGlaph.KOMK_NM	);
    strcpy(pOldInfoGlaph.KOMK_SUB,	pInfoGlaph.KOMK_SUB	);
    strcpy(pOldInfoGlaph.KOMK_NO,	pInfoGlaph.KOMK_NO	);
    strcpy(pOldInfoGlaph.KIKI_NO,	pInfoGlaph.KIKI_NO	);
    strcpy(pOldInfoGlaph.KIKI_NM,	pInfoGlaph.KIKI_NM	);
    strcpy(pOldInfoGlaph.SOKU_SU,	pInfoGlaph.SOKU_SU	);
    strcpy(pOldInfoGlaph.KIKA_TYPE,	pInfoGlaph.KIKA_TYPE	);
    strcpy(pOldInfoGlaph.KIKA_KIND,	pInfoGlaph.KIKA_KIND );
    strcpy(pOldInfoGlaph.KIKA_DECI,	pInfoGlaph.KIKA_DECI	);
    strcpy(pOldInfoGlaph.KIKA_NUM1,	pInfoGlaph.KIKA_NUM1	);
    strcpy(pOldInfoGlaph.KIKA_NUM2,	pInfoGlaph.KIKA_NUM2	);
    strcpy(pOldInfoGlaph.KIKA_NUM3,	pInfoGlaph.KIKA_NUM3	);
    strcpy(pOldInfoGlaph.SKB_NO,		pInfoGlaph.SKB_NO	);
    strcpy(pOldInfoGlaph.HINBAN_SK,	pInfoGlaph.HINBAN_SK	);
    strcpy(pOldInfoGlaph.UNQ_NO,		pInfoGlaph.UNQ_NO	);
}


//---------------------------------------------------------------------------
void __fastcall TForm1::Get_GKIKAKU(void)
{
    //char cFormatBuf[20],c1[20],c2[10];
    AnsiString sBuf,sDeci1;
	int i1;
    AnsiString sBufConv;	//2003.05.08 E.Takase Add
    bool bRtn;				//2003.05.08 E.Takase Add
    //double dBuf;			//2003.05.08 E.Takase Add

//�K�i�\���F�X
	sDeci1 = "0.0";
	if( iDEBUG == 1) return;
    for(i1 = 1;i1 < AnsiString(pInfoGlaph.KIKA_DECI).ToIntDef(0);i1++)
    {
    	sDeci1 +="0";
    }

	switch(AnsiString(pInfoGlaph.KIKA_TYPE).ToIntDef(0))
    {
    case 1:
    	switch(AnsiString(pInfoGlaph.KIKA_KIND).ToIntDef(0))
        {
        case 1:
            //2003.05.08 E.Takase Add��
			//2003.05.17 E.Takase Add��
            strcpy(KIKAKU_MOJI.HANI , "");
			//2003.05.17 E.Takase Add��
			//2003.05.17 E.Takase Add �R�����g��
            //KIKAKU_MOJI.HANI = "";
			//2003.05.17 E.Takase Add �R�����g��
            bRtn = Form1->ConvDoubleDefS(pInfoGlaph.KIKA_NUM1,sDeci1,pInfoGlaph.KIKA_NUM1,&sBufConv);
            if ( bRtn ) {
            	sBuf = sBufConv;
            	bRtn = Form1->ConvDoubleDefS(pInfoGlaph.KIKA_NUM2,sDeci1,pInfoGlaph.KIKA_NUM2,&sBufConv);
            	if ( bRtn ) {
                	sBuf +=  "�`";
                    sBuf += sBufConv;
					//2003.05.17 E.Takase Add��
                    strcpy(KIKAKU_MOJI.HANI , sBuf.c_str());
					//2003.05.17 E.Takase Add��
					//2003.05.17 E.Takase Add �R�����g��
                    //KIKAKU_MOJI.HANI = sBuf;
					//2003.05.17 E.Takase Add �R�����g��
                }
            }
            //2003.05.08 E.Takase Add��
            //2003.05.08 E.Takase Add �R�����g��
			//try{
        	//	sBuf = FormatFloat(sDeci1,AnsiString(pInfoGlaph.KIKA_NUM1).ToDouble());
        	//	sBuf +=  "�`";
        	//	sBuf += FormatFloat(sDeci1,AnsiString(pInfoGlaph.KIKA_NUM2).ToDouble());
        	//	KIKAKU_MOJI.HANI = sBuf;
			//}
			//catch(EConvertError& e){
			//	return;
			//}
			//catch(...){
			//	return;
			//}
            //2003.05.08 E.Takase Add �R�����g��
        	break;
        case 2:
            //2003.05.08 E.Takase Add��
			//2003.05.17 E.Takase Add��
            strcpy(KIKAKU_MOJI.HANI , "");
			//2003.05.17 E.Takase Add��
			//2003.05.17 E.Takase Add �R�����g��
            //KIKAKU_MOJI.HANI = "";
			//2003.05.17 E.Takase Add �R�����g��
            bRtn = Form1->ConvDoubleDefS(pInfoGlaph.KIKA_NUM2,sDeci1,pInfoGlaph.KIKA_NUM2,&sBufConv);
            if ( bRtn ) {
				//2003.05.17 E.Takase Add��
            	sBuf = sBufConv + "�ȉ�";
            	strcpy(KIKAKU_MOJI.HANI , sBuf.c_str());
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
            	//sBuf = sBufConv;
            	//KIKAKU_MOJI.HANI = sBuf +"�ȉ�";
				//2003.05.17 E.Takase Add �R�����g��
            }
            //2003.05.08 E.Takase Add��
            //2003.05.08 E.Takase Add �R�����g��
			//try{
        	//	sBuf = FormatFloat(sDeci1,AnsiString(pInfoGlaph.KIKA_NUM2).ToDouble());
            //}
			//catch(EConvertError& e){
			//	return;
			//}
			//catch(...){
			//	return;
			//}
			//KIKAKU_MOJI.HANI = sBuf +"�ȉ�";
            //2003.05.08 E.Takase Add �R�����g��
        	break;
        case 3:
            //2003.05.08 E.Takase Add��
			//2003.05.17 E.Takase Add��
            strcpy(KIKAKU_MOJI.HANI , "");
			//2003.05.17 E.Takase Add��
			//2003.05.17 E.Takase Add �R�����g��
            //KIKAKU_MOJI.HANI = "";
			//2003.05.17 E.Takase Add �R�����g��
            bRtn = Form1->ConvDoubleDefS(pInfoGlaph.KIKA_NUM1,sDeci1,pInfoGlaph.KIKA_NUM1,&sBufConv);
            if ( bRtn ) {
				//2003.05.17 E.Takase Add��
            	sBuf = sBufConv +"�ȏ�";
            	strcpy(KIKAKU_MOJI.HANI , sBuf.c_str());
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
            	//sBuf = sBufConv;
            	//KIKAKU_MOJI.HANI = sBuf +"�ȏ�";
				//2003.05.17 E.Takase Add �R�����g��
            }
            //2003.05.08 E.Takase Add��
            //2003.05.08 E.Takase Add �R�����g��
			//try{
        	//	sBuf = FormatFloat(sDeci1,AnsiString(pInfoGlaph.KIKA_NUM1).ToDouble());
            //}
			//catch(EConvertError& e){
			//	return;
			//}
			//catch(...){
			//	return;
			//}
        	//KIKAKU_MOJI.HANI = sBuf +"�ȏ�";
            //2003.05.08 E.Takase Add �R�����g��
        	break;
        default:
        	break;
        }
		//2003.05.17 E.Takase Add��
        strcpy(KIKAKU_MOJI.UPLIMIT ,"");
        strcpy(KIKAKU_MOJI.LOLIMIT ,"");
		//2003.05.17 E.Takase Add��
		//2003.05.17 E.Takase Add �R�����g��
        //KIKAKU_MOJI.UPLIMIT ="";
        //KIKAKU_MOJI.LOLIMIT ="";
		//2003.05.17 E.Takase Add �R�����g��
        break;
    case 2:
        //2003.05.08 E.Takase Add��
		//2003.05.17 E.Takase Add��
        strcpy(KIKAKU_MOJI.HANI , "");
        strcpy(KIKAKU_MOJI.UPLIMIT , "");
        strcpy(KIKAKU_MOJI.LOLIMIT , "");
		//2003.05.17 E.Takase Add��
		//2003.05.17 E.Takase Add �R�����g��
        //KIKAKU_MOJI.HANI = "";
        //KIKAKU_MOJI.UPLIMIT = "";
        //KIKAKU_MOJI.LOLIMIT = "";
		//2003.05.17 E.Takase Add �R�����g��
        bRtn = Form1->ConvDoubleDefS(pInfoGlaph.KIKA_NUM1,sDeci1,pInfoGlaph.KIKA_NUM1,&sBufConv);
        if ( bRtn ) {
         	sBuf = sBufConv;
			//2003.05.17 E.Takase Add��
          	strcpy(KIKAKU_MOJI.HANI , sBuf.c_str());
			//2003.05.17 E.Takase Add��
			//2003.05.17 E.Takase Add �R�����g��
          	//KIKAKU_MOJI.HANI = sBuf;
			//2003.05.17 E.Takase Add �R�����g��

        } else {
        	break;
        }
        //2003.05.08 E.Takase Add��
        //2003.05.08 E.Takase Add �R�����g��
    	//try{
        //	sBuf = FormatFloat(sDeci1,AnsiString(pInfoGlaph.KIKA_NUM1).ToDouble());
        //}
        //catch(EConvertError& e){
	   	//	return;
        //}
        //catch(...){
        //	return;
	   	//}
		//KIKAKU_MOJI.HANI = sBuf;
        //2003.05.08 E.Takase Add �R�����g��
        switch(AnsiString(pInfoGlaph.KIKA_KIND).ToIntDef(0))
        {
        case 1:
            //2003.05.08 E.Takase Add��
            bRtn = Form1->ConvDoubleDefS(pInfoGlaph.KIKA_NUM2,sDeci1,pInfoGlaph.KIKA_NUM2,&sBufConv);
            if ( bRtn ) {
         		sBuf = sBufConv;
				//2003.05.17 E.Takase Add��
                if( Form1->ConvDoubleDefD(sBuf,0.0) >= 0 ) {
                	sBuf = "+" + sBuf;
                }
           		strcpy(KIKAKU_MOJI.UPLIMIT , sBuf.c_str());

				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
           		//KIKAKU_MOJI.UPLIMIT = sBuf;
                //if( Form1->ConvDoubleDefD(KIKAKU_MOJI.UPLIMIT,0.0) >= 0 ) {
                //	KIKAKU_MOJI.UPLIMIT = "+" + KIKAKU_MOJI.UPLIMIT;
                //}
				//2003.05.17 E.Takase Add �R�����g��


            } else {
            	break;
            }
            bRtn = Form1->ConvDoubleDefS(pInfoGlaph.KIKA_NUM3,sDeci1,pInfoGlaph.KIKA_NUM3,&sBufConv);
            if ( bRtn ) {
         		sBuf = sBufConv;
				//2003.05.17 E.Takase Add��
                if( Form1->ConvDoubleDefD(sBuf,0.0) >= 0 ) {
                	sBuf = "+" + sBuf;
                }
           		strcpy(KIKAKU_MOJI.LOLIMIT , sBuf.c_str());

				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
           		//KIKAKU_MOJI.LOLIMIT = sBuf;
                //if( Form1->ConvDoubleDefD(KIKAKU_MOJI.LOLIMIT,0.0) >= 0 ) {
                //	KIKAKU_MOJI.LOLIMIT = "+" + KIKAKU_MOJI.LOLIMIT;
                //}
				//2003.05.17 E.Takase Add �R�����g��
            } else {
            	break;
            }
            //2003.05.08 E.Takase Add��
        	//2003.05.08 E.Takase Add �R�����g��
			//try{
        	//	KIKAKU_MOJI.UPLIMIT = FormatFloat(sDeci1,AnsiString(pInfoGlaph.KIKA_NUM2).ToDouble());
        	//	KIKAKU_MOJI.LOLIMIT = FormatFloat(sDeci1,AnsiString(pInfoGlaph.KIKA_NUM3).ToDouble());
			//	if(KIKAKU_MOJI.UPLIMIT.ToDouble() >= 0) KIKAKU_MOJI.UPLIMIT = "+" + KIKAKU_MOJI.UPLIMIT;
			//	if(KIKAKU_MOJI.LOLIMIT.ToDouble() >= 0) KIKAKU_MOJI.LOLIMIT = "+" + KIKAKU_MOJI.LOLIMIT;
            //}
	        //catch(EConvertError& e){
		   	//	return;
        	//}
	        //catch(...){
    	    //	return;
	   		//}
            //2003.05.08 E.Takase Add �R�����g��
			break;
        case 2:
            //2003.05.08 E.Takase Add��
			//2003.05.17 E.Takase Add��
            strcpy(KIKAKU_MOJI.UPLIMIT , "");
            strcpy(KIKAKU_MOJI.LOLIMIT , "");
			//2003.05.17 E.Takase Add��
			//2003.05.17 E.Takase Add �R�����g��
            //KIKAKU_MOJI.UPLIMIT = "";
            //KIKAKU_MOJI.LOLIMIT ="";
			//2003.05.17 E.Takase Add �R�����g��
            bRtn = Form1->ConvDoubleDefS(pInfoGlaph.KIKA_NUM2,sDeci1,pInfoGlaph.KIKA_NUM2,&sBufConv);
            if ( bRtn ) {
	         	sBuf = sBufConv;
				//2003.05.17 E.Takase Add��
                if( Form1->ConvDoubleDefD(sBuf,0.0) >= 0 ) {
                	sBuf = "+" + sBuf;
                }
            	strcpy(KIKAKU_MOJI.UPLIMIT , sBuf.c_str());
                strcpy(KIKAKU_MOJI.LOLIMIT , "");
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
            	//KIKAKU_MOJI.UPLIMIT = sBuf;
                //if( Form1->ConvDoubleDefD(KIKAKU_MOJI.UPLIMIT,0.0) >= 0 ) {
                //	KIKAKU_MOJI.UPLIMIT = "+" + KIKAKU_MOJI.UPLIMIT;
                //}
                //KIKAKU_MOJI.LOLIMIT ="";
				//2003.05.17 E.Takase Add �R�����g��
            }
            //2003.05.08 E.Takase Add��                 
        	//2003.05.08 E.Takase Add �R�����g��
			//try{
        	//	KIKAKU_MOJI.UPLIMIT = FormatFloat(sDeci1,AnsiString(pInfoGlaph.KIKA_NUM2).ToDouble());
        	//	KIKAKU_MOJI.LOLIMIT ="";
			//	if(KIKAKU_MOJI.UPLIMIT.ToDouble() >= 0) KIKAKU_MOJI.UPLIMIT = "+" + KIKAKU_MOJI.UPLIMIT;
            //}
	        //catch(EConvertError& e){
		   	//	return;
        	//}
	        //catch(...){
    	    //	return;
	   		//}
            //2003.05.08 E.Takase Add �R�����g��
        	break;
        case 3:
            //2003.05.08 E.Takase Add��
			//2003.05.17 E.Takase Add��
            strcpy(KIKAKU_MOJI.UPLIMIT , "");
            strcpy(KIKAKU_MOJI.LOLIMIT , "");
			//2003.05.17 E.Takase Add��
			//2003.05.17 E.Takase Add �R�����g��
            //KIKAKU_MOJI.UPLIMIT = "";
            //KIKAKU_MOJI.LOLIMIT ="";
			//2003.05.17 E.Takase Add �R�����g��
            bRtn = Form1->ConvDoubleDefS(pInfoGlaph.KIKA_NUM3,sDeci1,pInfoGlaph.KIKA_NUM3,&sBufConv);
            if ( bRtn ) {
	         	sBuf = sBufConv;
				//2003.05.17 E.Takase Add��
                if(Form1->ConvDoubleDefD(sBuf,0.0) >= 0) {
                	sBuf = "+" + sBuf;
                }
                strcpy(KIKAKU_MOJI.LOLIMIT , sBuf.c_str());
            	strcpy(KIKAKU_MOJI.UPLIMIT , "");
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
                //KIKAKU_MOJI.LOLIMIT =sBuf;
            	//KIKAKU_MOJI.UPLIMIT = "";
                //if(Form1->ConvDoubleDefD(KIKAKU_MOJI.LOLIMIT,0.0) >= 0) {
                //	KIKAKU_MOJI.LOLIMIT = "+" + KIKAKU_MOJI.LOLIMIT;
                //}
				//2003.05.17 E.Takase Add �R�����g��
            }
            //2003.05.08 E.Takase Add��
        	//2003.05.08 E.Takase Add �R�����g��
			//try{
        	//	KIKAKU_MOJI.UPLIMIT = "";
        	//	KIKAKU_MOJI.LOLIMIT = FormatFloat(sDeci1,AnsiString(pInfoGlaph.KIKA_NUM3).ToDouble());
			//	if(KIKAKU_MOJI.LOLIMIT.ToDouble() >= 0) KIKAKU_MOJI.LOLIMIT = "+" + KIKAKU_MOJI.LOLIMIT;
            //}
	        //catch(EConvertError& e){
		   	//	return;
        	//}
	        //catch(...){
    	    //	return;
	   		//}
            //2003.05.08 E.Takase Add �R�����g��
        	break;
        default:
        	break;
        }
        break;
    case 3:
		//2003.05.17 E.Takase Add��
    	strcpy(KIKAKU_MOJI.HANI , pInfoGlaph.KIKA_STR);
        strcpy(KIKAKU_MOJI.UPLIMIT ,"");
        strcpy(KIKAKU_MOJI.LOLIMIT ,"");
		//2003.05.17 E.Takase Add��
		//2003.05.17 E.Takase Add �R�����g��
    	//KIKAKU_MOJI.HANI = pInfoGlaph.KIKA_STR;
        //KIKAKU_MOJI.UPLIMIT ="";
        //KIKAKU_MOJI.LOLIMIT ="";
		//2003.05.17 E.Takase Add �R�����g��
        break;
    default:
    	break;
    }
}
//-------------------------------------------------------------------------
int __fastcall TForm1::Get_KASOUIDO_GRAPHSTART_Info(int Row,int Col,int GridNo)
{
	int i1;//,i2;
	int iGraphRow;
	int iRowCount;
    // k.y 2003.05.17
    //extern 	KSM02_DATA *pORDATA;
    extern 	KSM02_DATA pORDATA[100];

// k.y 2003.05.17
//	extern KSM02_DATA *pSOZAI_OR_DATA;
    extern KSM02_DATA pSOZAI_OR_DATA[100];
    bool bCopy;

	bDrawGlaph = false;                             
	bCopy = false;
	iNowGrid = GridNo;
    iLotCol = Col;
    bCopy = true;
//�����͂������z�񂪊m�ۂ���Ă��Ȃ��ꍇ�ɔ����z��𒲂ז����ꍇ�͎Q�Ƃ𒆎~����
	switch(GridNo)
	{
	case 1:
		if( !hCELLINFO_SOKU_SYUKA ) return( 1 );
        if( SGr_vSOKU_SYUKA->RowCount < 2 ) return( 1 );
		break;
	case 2:
		if( !hCELLINFO_RIRE_SYUKA ) return( 1 );
        if( SGr_vRIRE_SYUKA->RowCount < 2 ) return( 1 );
        if( Form1->iRIRE_CNT  == 0 ) return( 1 );
		break;
	case 3:
		if( !hCELLINFO_SOKU_SOZAI ) return( 1 );
        if( SGr_vSOKU_SOZAI->RowCount < 2 ) return( 1 );
		break;
	case 4:
		if( !hCELLINFO_RIRE_SOZAI ) return( 1 );
        if( SGr_vRIRE_SOZAI->RowCount < 2 ) return( 1 );
        if( Form1->iRIRE_CNT  == 0 ) return( 1 );
		break;
    default:
    	break;
	}
	switch(GridNo)
	{
	case 1:
		iRowCount = Form1->SGr_vSOKU_SYUKA->RowCount;
    	strcpy(pInfoGlaph.KOMK_NM	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KOMK_NM);
        strcpy(pInfoGlaph.KOMK_NO	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KOMK_NO);
        strcpy(pInfoGlaph.KIKI_NO	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKI_NO);
        strcpy(pInfoGlaph.KIKI_NM	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKI_NM);
        strcpy(pInfoGlaph.KOMK_SUB	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KOMK_SUB);
        strcpy(pInfoGlaph.SOKU_SU	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].SOKU_SU);
        strcpy(pInfoGlaph.KIKA_TYPE	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_TYPE);
        strcpy(pInfoGlaph.KIKA_KIND 	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_KIND);
        strcpy(pInfoGlaph.KIKA_DECI	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_DECI);
        strcpy(pInfoGlaph.KIKA_NUM1	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_NUM1);
        strcpy(pInfoGlaph.KIKA_NUM2	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_NUM2);
        strcpy(pInfoGlaph.KIKA_NUM3	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_NUM3);
        strcpy(pInfoGlaph.KIKA_STR	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_STR);
        strcpy(pInfoGlaph.KIKA_SUB1	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_SUB1);
        strcpy(pInfoGlaph.KIKA_SUB2  ,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_SUB2);
        strcpy(pInfoGlaph.KIKA_SUB3	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].KIKA_SUB3);
        strcpy(pInfoGlaph.VALUE_DECI	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].VALUE_DECI);
        strcpy(pInfoGlaph.SKB_NO		,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].SKB_NO);
        strcpy(pInfoGlaph.UNQ_NO		,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].UNQ_NO);
        strcpy(pInfoGlaph.HINBAN_SK		,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].HINBAN_SK);
        pInfoGlaph.MAX				=pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].MAX;
        pInfoGlaph.MIN				=pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].MIN;
        pInfoGlaph.GMAX				=pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].GMAX;
        pInfoGlaph.GMIN				=pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].GMIN;
		//2003.05.17 E.Takase Add��
        strcpy(pInfoGlaph.UPDNAME  	,pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].UPDNAME);
		//2003.05.17 E.Takase Add��
		//2003.05.17 E.Takase Add �R�����g��
        //pInfoGlaph.UPDNAME			=pCELLINFO_SOKU_SYUKA[Col*iRowCount+Row].UPDNAME;
		//2003.05.17 E.Takase Add �R�����g��
        break;
	case 2:
		iRowCount = Form1->SGr_vRIRE_SYUKA->RowCount;
    	strcpy(pInfoGlaph.KOMK_NM	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KOMK_NM);
        strcpy(pInfoGlaph.KOMK_NO	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KOMK_NO);
        strcpy(pInfoGlaph.KIKI_NO	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKI_NO);
        strcpy(pInfoGlaph.KIKI_NM	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKI_NM);
        strcpy(pInfoGlaph.KOMK_SUB	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KOMK_SUB);
        strcpy(pInfoGlaph.SOKU_SU	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].SOKU_SU);
        strcpy(pInfoGlaph.KIKA_TYPE	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_TYPE);
        strcpy(pInfoGlaph.KIKA_KIND 	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_KIND);
        strcpy(pInfoGlaph.KIKA_DECI	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_DECI);
        strcpy(pInfoGlaph.KIKA_NUM1	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_NUM1);
        strcpy(pInfoGlaph.KIKA_NUM2	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_NUM2);
        strcpy(pInfoGlaph.KIKA_NUM3	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_NUM3);
        strcpy(pInfoGlaph.KIKA_STR	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_STR);
        strcpy(pInfoGlaph.KIKA_SUB1	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_SUB1);
        strcpy(pInfoGlaph.KIKA_SUB2  ,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_SUB2);
        strcpy(pInfoGlaph.KIKA_SUB3	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].KIKA_SUB3);
        strcpy(pInfoGlaph.VALUE_DECI	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].VALUE_DECI);
        strcpy(pInfoGlaph.SKB_NO		,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].SKB_NO);
        strcpy(pInfoGlaph.UNQ_NO		,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].UNQ_NO);
        strcpy(pInfoGlaph.HINBAN_SK	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].HINBAN_SK);
        pInfoGlaph.MAX				=pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].MAX;
        pInfoGlaph.MIN				=pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].MIN;
        pInfoGlaph.GMAX				=pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].GMAX;
        pInfoGlaph.GMIN				=pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].GMIN;
		//2003.05.17 E.Takase Add��
        strcpy(pInfoGlaph.UPDNAME	,pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].UPDNAME);
		//2003.05.17 E.Takase Add��
		//2003.05.17 E.Takase Add �R�����g��
        //pInfoGlaph.UPDNAME			=pCELLINFO_RIRE_SYUKA[Col*iRowCount+Row].UPDNAME;
		//2003.05.17 E.Takase Add �R�����g��
        break;
	case 3:
		iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;
    	strcpy(pInfoGlaph.KOMK_NM	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KOMK_NM);
        strcpy(pInfoGlaph.KOMK_NO	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KOMK_NO);
        strcpy(pInfoGlaph.KIKI_NO	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKI_NO);
        strcpy(pInfoGlaph.KIKI_NM	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKI_NM);
        strcpy(pInfoGlaph.KOMK_SUB	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KOMK_SUB);
        strcpy(pInfoGlaph.SOKU_SU	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].SOKU_SU);
        strcpy(pInfoGlaph.KIKA_TYPE	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_TYPE);
        strcpy(pInfoGlaph.KIKA_KIND 	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_KIND);
        strcpy(pInfoGlaph.KIKA_DECI	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_DECI);
        strcpy(pInfoGlaph.KIKA_NUM1	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_NUM1);
        strcpy(pInfoGlaph.KIKA_NUM2	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_NUM2);
        strcpy(pInfoGlaph.KIKA_NUM3	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_NUM3);
        strcpy(pInfoGlaph.KIKA_STR	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_STR);
        strcpy(pInfoGlaph.KIKA_SUB1	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_SUB1);
        strcpy(pInfoGlaph.KIKA_SUB2  ,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_SUB2);
        strcpy(pInfoGlaph.KIKA_SUB3	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].KIKA_SUB3);
        strcpy(pInfoGlaph.VALUE_DECI	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].VALUE_DECI);
        strcpy(pInfoGlaph.SKB_NO		,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].SKB_NO);
        strcpy(pInfoGlaph.UNQ_NO		,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].UNQ_NO);
        strcpy(pInfoGlaph.HINBAN_SK	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].HINBAN_SK);
        pInfoGlaph.MAX				=pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].MAX;
        pInfoGlaph.MIN				=pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].MIN;
        pInfoGlaph.GMAX				=pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].GMAX;
        pInfoGlaph.GMIN				=pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].GMIN;
		//2003.05.17 E.Takase Add��
        strcpy(pInfoGlaph.UPDNAME 	,pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].UPDNAME);
		//2003.05.17 E.Takase Add��
		//2003.05.17 E.Takase Add �R�����g��
        //pInfoGlaph.UPDNAME			=pCELLINFO_SOKU_SOZAI[Col*iRowCount+Row].UPDNAME;
		//2003.05.17 E.Takase Add �R�����g��
        break;
	case 4:
		iRowCount = Form1->SGr_vRIRE_SOZAI->RowCount;
    	strcpy(pInfoGlaph.KOMK_NM	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KOMK_NM);
        strcpy(pInfoGlaph.KOMK_NO	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KOMK_NO);
        strcpy(pInfoGlaph.KIKI_NO	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKI_NO);
        strcpy(pInfoGlaph.KIKI_NM	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKI_NM);
        strcpy(pInfoGlaph.KOMK_SUB	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KOMK_SUB);
        strcpy(pInfoGlaph.SOKU_SU	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].SOKU_SU);
        strcpy(pInfoGlaph.KIKA_TYPE	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_TYPE);
        strcpy(pInfoGlaph.KIKA_KIND 	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_KIND);
        strcpy(pInfoGlaph.KIKA_DECI	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_DECI);
        strcpy(pInfoGlaph.KIKA_NUM1	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_NUM1);
        strcpy(pInfoGlaph.KIKA_NUM2	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_NUM2);
        strcpy(pInfoGlaph.KIKA_NUM3	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_NUM3);
        strcpy(pInfoGlaph.KIKA_STR	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_STR);
        strcpy(pInfoGlaph.KIKA_SUB1	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_SUB1);
        strcpy(pInfoGlaph.KIKA_SUB2  ,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_SUB2);
        strcpy(pInfoGlaph.KIKA_SUB3	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].KIKA_SUB3);
        strcpy(pInfoGlaph.VALUE_DECI	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].VALUE_DECI);
        strcpy(pInfoGlaph.SKB_NO		,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].SKB_NO);
        strcpy(pInfoGlaph.UNQ_NO		,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].UNQ_NO);
        strcpy(pInfoGlaph.HINBAN_SK	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].HINBAN_SK);
        pInfoGlaph.MAX				=pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].MAX;
        pInfoGlaph.MIN				=pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].MIN;
        pInfoGlaph.GMAX				=pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].GMAX;
        pInfoGlaph.GMIN				=pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].GMIN;
		//2003.05.17 E.Takase Add��
        strcpy(pInfoGlaph.UPDNAME	,pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].UPDNAME);
		//2003.05.17 E.Takase Add��
		//2003.05.17 E.Takase Add �R�����g��
        //pInfoGlaph.UPDNAME			=pCELLINFO_RIRE_SOZAI[Col*iRowCount+Row].UPDNAME;
		//2003.05.17 E.Takase Add �R�����g��
        break;
	default:
		break;                                       
	}
	iGraphRow = 0;
	switch(GridNo)
	{
	case 1:
    case 2:
		iGraphRow = 0;
		i1 = 0;
		while( 1 )
		{
			iGraphRow += AnsiString(pORDATA[i1].SOKU_SU).ToInt();
			if( Row <= iGraphRow )
			{
				iGraphRow = iGraphRow - AnsiString(pORDATA[i1].SOKU_SU).ToInt();
				break;
			}
			else
			{
				i1 ++;
			}
        }
        break;
	case 3:
    case 4:
		iGraphRow = 0;
		i1 = 0;
		while( 1 )
		{
			iGraphRow += AnsiString(pSOZAI_OR_DATA[i1].SOKU_SU).ToInt();
			if( Row <= iGraphRow )
			{
				iGraphRow = iGraphRow - AnsiString(pSOZAI_OR_DATA[i1].SOKU_SU).ToInt();
				break;
			}
			else
			{
				i1 ++;
			}
        }
		break;
	}
	pInfoGlaph.GRID_NO = GridNo;
	if(bCopy){
 			bDrawGlaph = true;
    }
	else
	{
    	bDrawGlaph = false;
	}
	return( iGraphRow );
}

void __fastcall TForm1::Glaph_Init(void)
{
//���x���N���A
    Form1->pnlSYUKAAve->Caption				="";
    Form1->pnlSYUKACp->Caption				="";
    Form1->pnlSYUKACpk->Caption				="";
    Form1->pnlSYUKAK->Caption				="";
    Form1->pnlSYUKAMax->Caption				="";
    Form1->pnlSYUKAMin->Caption				="";
    Form1->pnlSYUKANCount->Caption			="";
    Form1->pnlSYUKANGPercent->Caption		="";
    Form1->pnlSYUKAR->Caption				="";
    Form1->pnlSYUKASiguma->Caption			="";
    Form1->Pnl_skInfo_vKENSA2->Caption		="";
    Form1->Pnl_skInfo_vKIKAKU2->Caption		="";
    Form1->Pnl_skInfo_vKIKI2->Caption		="";
    Form1->Pnl_skInfo_vLOTBNG2->Caption		="";
    Form1->Pnl_skInfo_vSOKUUSER2->Caption	="";
    Form1->Lab_skInfo_Kikaku2->Caption		="";
    Form1->Lab_skInfo_KIKAKU2UP->Caption 	="";
    Form1->Lab_skInfo_KIKAKU2LOW->Caption	="";

    Form1->pnlSOZAIAve->Caption 			="";
   	Form1->pnlSOZAICp->Caption 				="";
  	Form1->pnlSOZAICpk->Caption 			="";
 	Form1->pnlSOZAIK->Caption 				="";
	Form1->pnlSOZAIMax->Caption 			="";
    Form1->pnlSOZAIMin->Caption 			="";
   	Form1->pnlSOZAINCount->Caption 			="";
  	Form1->pnlSOZAINGPercent->Caption 		="";
 	Form1->pnlSOZAIR->Caption 				="";
	Form1->pnlSOZAISiguma->Caption 			="";
    Form1->Pnl_skInfo_vKENSA1->Caption 		="";
   	Form1->Pnl_skInfo_vKIKAKU1->Caption 	="";
  	Form1->Pnl_skInfo_vKIKI1->Caption 		="";
 	Form1->Pnl_skInfo_vLOTBNG1->Caption 	="";
	Form1->Pnl_skInfo_vSOKUUSER1->Caption 	="";
    Form1->Lab_skInfo_Kikaku1->Caption 		="";
   	Form1->Lab_skInfo_KIKAKU1UP->Caption 	="";
   	Form1->Lab_skInfo_KIKAKU1LOW->Caption 	="";

	Form1->Pnl_skInfo->Refresh();

}



