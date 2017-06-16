//---------------------------------------------------------------------------
//
//  Unit7.cpp
//    �y�o�׌����V�X�e���|�����\�z
//    �����\�t�H�[���iTForm7�N���X�j�̃����o�֐��̒�`
//
//  �쐬��
//    �s��@�a�O
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit7.h"
#include "Unit9.h"
#include "Tkss01.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm7 *Form7;
//�Z�����
extern HANDLE hCELLINFO_SOKU_SYUKA;
extern HANDLE hCELLINFO_RIRE_SYUKA;
extern HANDLE hCELLINFO_SOKU_SOZAI;
extern HANDLE hCELLINFO_RIRE_SOZAI;
extern CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
extern CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
extern CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;
extern int iPnl_SOZAI_InsNoCnt;
extern int iPnl_SOZAI_InsNameCnt;
extern int iPnl_SOZAI_InsKikiNameCnt;
extern int iPnl_SOZAI_InsSubBaseCnt;

extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;

TCanvas *TempRireCanvas;
TCanvas *TempSokuCanvas;
TRect RireCellRect;
TRect SokuCellRect;
// k.y 2003.05.17
//extern HANDLE		hORDATA;

// k.y 2003.05.17
//extern KSM02_DATA 	*pORDATA;
//extern KSM02_DATA 	*pORDATA;

// k.y 2003.05.17
// extern	HANDLE 	hInfoGlaph;

// k.y 2003.05.17
//extern 	GRAPH_DATA	*pInfoGlaph;
extern 	GRAPH_DATA  pInfoGlaph;
extern int iPORT_NO;

// k.y 2003.06.03
extern int iDEBUG;

bool bNOW_SOKUTEI;
bool bNUM_SET;
bool bGRIDON;
bool bCALENDER;
HANDLE		hBUN_DATA;
BUN_DATA 	*pBUN_DATA;
// k.y 2003.05.17
//HANDLE		hTEMP_BUN_DATA;

// k.y 2003.05.17
//BUN_DATA	*pTEMP_BUN_DATA;
BUN_DATA	pTEMP_BUN_DATA;
BUN_DATA	pCBO_SELECT[99];
int	iDB_RECORD;
int iENA_GRID;
AnsiString sSYSTEM_DATE;
int iWriteRow;

//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�W�F�V�K�o�^�v�{�^�������������̏���
//
//  �@�\����
//    ���͂��ꂽ�o�׌������ڂƁA��ʏ�̃Z���ɑ΂��鍀�ڂ𒲂�
//  �@�����I�ɓK���Ȉʒu�̃Z�����̐V�K�o�^���s���܂��B
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
void __fastcall TForm7::BtnF08Click(TObject *Sender)
{
	int iRow,iCol,iSOKUCol;
	//int UNQ_NO,KOMK_NO;
	int iCBO_INDEX;
	AnsiString KOMK_NM,KOMK_SUB,TANI,sBuf,sRESULT_BUF;
	int i1,i2;
	AnsiString sDATE,sTIME;
	AnsiString sUPDCHR,sUPDCNT;
	AnsiString sSOKU_VAL_SU,sSOKU_VAL_AVE,sSOKU_VAL_MAX,sSOKU_VAL_MIN,sSOKU_OK;
    AnsiString dSOKU_VAL_AVE,dSOKU_VAL_MAX,dSOKU_VAL_MIN;
	double dMAX,dMIN,dAVE,dVAL;
	int iSOKU_SU;
	bool bVAL_FIRST;
	AnsiString sUPDNAME;	//2003.05.12 E.Takase Add
	TMsgDlgButtons MsgButton;

    sDATE = FormatDateTime("yyyymmdd",Date());
	sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
	sUPDCHR = AnsiString(Form1->USER_COD);
	sUPDCNT = AnsiString("0");

    //���t�̓p�\�R����̓��t�isDATE�j��o�^���A�ύX���ɓK�p
    //�{�V�X�e����̓��t�isSYSTEM_DATE�j�𑪒���ɓK�p
	//2003.05.12 E.Takase Add��
	sUPDNAME = GetTANTO2(AnsiString(Form1->USER_NAM));
	//2003.05.12 E.Takase Add��



	//���ϒl���̎Z�o
	bVAL_FIRST = true;
	iSOKU_SU = 0;
	dMAX = 0;
	dMIN = 0;
	dAVE = 0;
	dVAL = 0;

	iCBO_INDEX = Cbo_KOMK_NM->ItemIndex ;
	if(!NEW_INSPECT_SETOK( iCBO_INDEX ))
	{
        sBuf  = "�V�K�o�^�𓯈ꃍ�b�g�A���ꌟ���A�����ɂ͍s���܂���B";
        MsgButton << mbOK;
        MessageDlg( sBuf, mtWarning	, MsgButton, 0);
        return;
	}
	if(AnsiString(pCBO_SELECT[iCBO_INDEX].VALUE_TYPE).ToIntDef(0) != 3)
	{
		for(i1 = 0 ; i1< Num_SOKU_SU->Text.ToIntDef(0)  ; i1++)
		{
            sBuf = SGr_vSOKUTEI->Cells[1][i1];
            //2003.05.08 E.Takase Add��
            dVAL = Form1->ConvDoubleDefD(sBuf,0.0);
			if (sBuf == AnsiString(dVAL))
			{
				if( bVAL_FIRST == true )
    	        {
					dMAX = dVAL;
					dMIN = dVAL;
					bVAL_FIRST = false;
				}
	            iSOKU_SU ++;
				dAVE += dVAL;
				if( dMAX < dVAL ) dMAX = dVAL;
				if( dMIN > dVAL ) dMIN = dVAL;
            //2003.05.08 E.Takase Add��
			}
        }
		if( iSOKU_SU == 0 ) iSOKU_SU = 1;
        sSOKU_VAL_SU = AnsiString( iSOKU_SU );
		dSOKU_VAL_AVE = ( dAVE / iSOKU_SU );
		dSOKU_VAL_MAX = ( dMAX );
		dSOKU_VAL_MIN = ( dMIN );
	//�����`�F�b�N
        if( dSOKU_VAL_AVE > 9999999.999999 ) dSOKU_VAL_AVE  = 9999999.999999 ;
        if( dSOKU_VAL_MAX > 9999999.99999  ) dSOKU_VAL_MAX  = 9999999.99999 ;
        if( dSOKU_VAL_MIN > 9999999.99999  ) dSOKU_VAL_MIN  = 9999999.99999 ;

		sSOKU_VAL_SU  = sSOKU_VAL_SU.SubString(1,14);
		sSOKU_VAL_AVE = AnsiString(dSOKU_VAL_AVE).SubString(1,14);
		sSOKU_VAL_MAX = AnsiString(dSOKU_VAL_MAX).SubString(1,14);
		sSOKU_VAL_MIN = AnsiString(dSOKU_VAL_MIN).SubString(1,14);
    //�ǔ۔���
        sSOKU_OK = AnsiString(GET_HANTEI());
	}
	else
    {
		sSOKU_VAL_SU = AnsiString(Num_SOKU_SU->Text);
		sSOKU_VAL_AVE = "0";
		sSOKU_VAL_MAX = "0";
		sSOKU_VAL_MIN = "0";
        sSOKU_OK = AnsiString(GET_HANTEI());
	}

    iCBO_INDEX = Cbo_KOMK_NM->ItemIndex ;
//���荀��
	//UNQ_NO   = AnsiString(pCBO_SELECT[iCBO_INDEX].UNQ_NO).ToIntDef(0);
    //KOMK_NO  = AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_NO).ToIntDef(0);
    KOMK_NM  = AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_NM);
    KOMK_SUB = AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_SUB);
    TANI     = AnsiString(pCBO_SELECT[iCBO_INDEX].TANI);		// 2003/10/20 A.Tamura �R���{�����^�C�g�����ɒP�ʂ��ǉ�
	if( iENA_GRID == 0 )	//�V�K�o�^�ΏۃO���b�h�͗�������
	{
    	iRow = 1 ;
		iCol = SGr_vRIRE_SYUKA->Col ;
		while(iRow < SGr_vRIRE_SYUKA->RowCount)
		{
            //2003/12/11 E.Takse Trim�����ɂ���
			//if(SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0         //�O���b�h����
			//&& SGr_Title->Cells[0][iRow].Trim() == KOMK_NM.Trim()+KOMK_SUB.Trim()+" "+TANI.Trim())     //���ڂ�����
			//{
            //2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
            //                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
			//if(SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0         //�O���b�h����
			//&& SGr_Title->Cells[0][iRow] == KOMK_NM+KOMK_SUB+" "+TANI )     //���ڂ�����
			//{
            sBuf = KOMK_NM.Trim()+KOMK_SUB.Trim()+" "+TANI.Trim();
			if((SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0 )       //�O���b�h����
			&& (SGr_Title->Cells[0][iRow].Trim() == sBuf.Trim()))     			//���ڂ�����
			{
    	    	strcpy(pBUN_DATA[iCol*99+iRow].DTKSHIN		,pCBO_SELECT[iCBO_INDEX].DTKSHIN);
        	    strcpy(pBUN_DATA[iCol*99+iRow].LOTNO		,SGr_vRIRE_SYUKA->Cells[iCol][0].c_str());
        	    strcpy(pBUN_DATA[iCol*99+iRow].HINBAN		,SGr_vRIRE_SYUKA->Cells[iCol][1].c_str());
            	strcpy(pBUN_DATA[iCol*99+iRow].UNQ_NO		,pCBO_SELECT[iCBO_INDEX].UNQ_NO  	);
	            strcpy(pBUN_DATA[iCol*99+iRow].KOMK_NO		,pCBO_SELECT[iCBO_INDEX].KOMK_NO 	);
			   	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_NM		,pCBO_SELECT[iCBO_INDEX].KOMK_NM 	);
			  	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_ENG		,pCBO_SELECT[iCBO_INDEX].KOMK_ENG	);
		 		strcpy(pBUN_DATA[iCol*99+iRow].KOMK_SUB		,pCBO_SELECT[iCBO_INDEX].KOMK_SUB	);
				strcpy(pBUN_DATA[iCol*99+iRow].KOMK_SUB_ENG	,pCBO_SELECT[iCBO_INDEX].KOMK_SUB_ENG	);
		   		strcpy(pBUN_DATA[iCol*99+iRow].KIKI_NO		,pCBO_SELECT[iCBO_INDEX].KIKI_NO 	);
	  			strcpy(pBUN_DATA[iCol*99+iRow].KIKI_NM		,pCBO_SELECT[iCBO_INDEX].KIKI_NM 	);
	 			strcpy(pBUN_DATA[iCol*99+iRow].TANI			,pCBO_SELECT[iCBO_INDEX].TANI 	  );
				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_TYPE	,pCBO_SELECT[iCBO_INDEX].KIKA_TYPE );
   				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_KIND	,pCBO_SELECT[iCBO_INDEX].KIKA_KIND );
  				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_DECI	,pCBO_SELECT[iCBO_INDEX].KIKA_DECI );
 				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM1	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM1 );
				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM2	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM2 );
				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM3	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM3 );
        	    strcpy(pBUN_DATA[iCol*99+iRow].KIKA_STR		,pCBO_SELECT[iCBO_INDEX].KIKA_STR );
		   		strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB1	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB1 );
			  	strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB2	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB2 );
			 	strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB3	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB3 );
				strcpy(pBUN_DATA[iCol*99+iRow].SOKU_SU		,AnsiString(Num_SOKU_SU->Text).c_str());
	   			strcpy(pBUN_DATA[iCol*99+iRow].SOKU_FLG		,pCBO_SELECT[iCBO_INDEX].SOKU_FLG );
		  		strcpy(pBUN_DATA[iCol*99+iRow].TOKU_FLG		,pCBO_SELECT[iCBO_INDEX].TOKU_FLG );
				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_PRT 	,pCBO_SELECT[iCBO_INDEX].KIKA_PRT 	);
				strcpy(pBUN_DATA[iCol*99+iRow].VALUE_TYPE	,pCBO_SELECT[iCBO_INDEX].VALUE_TYPE 	);
			   	strcpy(pBUN_DATA[iCol*99+iRow].VALUE_DECI	,pCBO_SELECT[iCBO_INDEX].VALUE_DECI 	);
			   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_SU	,sSOKU_VAL_SU.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_AVE	,sSOKU_VAL_AVE.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MAX	,sSOKU_VAL_MAX.c_str());
		   		strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MIN	,sSOKU_VAL_MIN.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_OK		,sSOKU_OK.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].SKTYMD		,sSYSTEM_DATE.c_str()); //��ʏ�̓��t
			   	strcpy(pBUN_DATA[iCol*99+iRow].ADDYMD		,sDATE.c_str()); //��ʏ�̓��t
			   	strcpy(pBUN_DATA[iCol*99+iRow].ADDTIM		,sTIME.c_str());
		   		strcpy(pBUN_DATA[iCol*99+iRow].UPDYMD		,sDATE.c_str()); //��ʏ�̓��t
			   	strcpy(pBUN_DATA[iCol*99+iRow].UPDTIM		,sTIME.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].UPDCHR		,sUPDCHR.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].UPDCNT		,sUPDCNT.c_str());
				//2003.05.12 E.Takase Add��
				//2003.05.17 E.Takase Add��
				strcpy(pBUN_DATA[iCol*99+iRow].UPD_NAME   	,sUPDNAME.c_str());
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
				//pBUN_DATA[iCol*99+iRow].UPD_NAME 			= sUPDNAME;
				//2003.05.17 E.Takase Add �R�����g��
				//2003.05.12 E.Takase Add��
				//2003.05.12 E.Takase Add �R�����g��
				//pBUN_DATA[iCol*99+iRow].UPD_NAME 			= GetTANTO(AnsiString(pBUN_DATA[iCol*99+iRow].UPDCHR));
				//2003.05.12 E.Takase Add �R�����g��
	           	pBUN_DATA[iCol*99+iRow].MAX 				= pCBO_SELECT[iCBO_INDEX].MAX ;
    	       	pBUN_DATA[iCol*99+iRow].MIN 				= pCBO_SELECT[iCBO_INDEX].MIN ;
				for(i1 = 0 ; i1 < AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_SU).ToIntDef(0);i1++)
				{
					strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL[i1],SGr_vSOKUTEI->Cells[1][i1].c_str());
	            }
                SGr_vRIRE_SYUKA->Col = iCol;
                SGr_vRIRE_SYUKA->Row = iRow;
    	        SGr_vRIRE_SYUKA->Cells[iCol][iRow] = AnsiString(pBUN_DATA[iCol*99+iRow].SKTYMD).SubString(5,2)
            								  + "/" +AnsiString(pBUN_DATA[iCol*99+iRow].SKTYMD).SubString(7,2)
											  + " " +AnsiString(pBUN_DATA[iCol*99+iRow].UPD_NAME);//�f�o�b�O�p
                SGr_vRIRE_SYUKA->SetFocus();
                iWriteRow = iRow;
                break;
			}
			//2003/12/11 E.Takse Trim�����ɂ���
			//else if((SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0)	  //�O���b�h����
			//	 && (SGr_Title->Cells[0][iRow].Trim().Length() == 0  ))			  //���ڂ���
        	//{
            //2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
            //                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
	        //else if((SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0)	  //�O���b�h����
			//	 && (SGr_Title->Cells[0][iRow].Length() == 0  ))			  //���ڂ���
        	//{
			else if((SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0)	  //�O���b�h����
				 && (SGr_Title->Cells[0][iRow].Trim().Length() == 0  ))			  //���ڂ���
        	{
	            strcpy(pBUN_DATA[iCol*99+iRow].DTKSHIN		,pCBO_SELECT[iCBO_INDEX].DTKSHIN);
    	        strcpy(pBUN_DATA[iCol*99+iRow].LOTNO		,SGr_vRIRE_SYUKA->Cells[iCol][0].c_str());
    	        strcpy(pBUN_DATA[iCol*99+iRow].HINBAN		,SGr_vRIRE_SYUKA->Cells[iCol][1].c_str());
        	    strcpy(pBUN_DATA[iCol*99+iRow].UNQ_NO		,pCBO_SELECT[iCBO_INDEX].UNQ_NO  	);
            	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_NO		,pCBO_SELECT[iCBO_INDEX].KOMK_NO 	);
			   	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_NM		,pCBO_SELECT[iCBO_INDEX].KOMK_NM 	);
			  	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_ENG		,pCBO_SELECT[iCBO_INDEX].KOMK_ENG	);
			 	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_SUB		,pCBO_SELECT[iCBO_INDEX].KOMK_SUB	);
				strcpy(pBUN_DATA[iCol*99+iRow].KOMK_SUB_ENG	,pCBO_SELECT[iCBO_INDEX].KOMK_SUB_ENG	);
		   		strcpy(pBUN_DATA[iCol*99+iRow].KIKI_NO		,pCBO_SELECT[iCBO_INDEX].KIKI_NO 	);
		  		strcpy(pBUN_DATA[iCol*99+iRow].KIKI_NM		,pCBO_SELECT[iCBO_INDEX].KIKI_NM 	);
	 			strcpy(pBUN_DATA[iCol*99+iRow].TANI			,pCBO_SELECT[iCBO_INDEX].TANI 	  );
				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_TYPE	,pCBO_SELECT[iCBO_INDEX].KIKA_TYPE );
	   			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_KIND	,pCBO_SELECT[iCBO_INDEX].KIKA_KIND );
  				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_DECI	,pCBO_SELECT[iCBO_INDEX].KIKA_DECI );
 				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM1	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM1 );
				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM2	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM2 );
				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM3	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM3 );
    	        strcpy(pBUN_DATA[iCol*99+iRow].KIKA_STR		,pCBO_SELECT[iCBO_INDEX].KIKA_STR );
			   	strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB1	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB1 );
		  		strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB2	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB2 );
			 	strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB3	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB3 );
				strcpy(pBUN_DATA[iCol*99+iRow].SOKU_SU		,AnsiString(Num_SOKU_SU->Text).c_str());
	   			strcpy(pBUN_DATA[iCol*99+iRow].SOKU_FLG		,pCBO_SELECT[iCBO_INDEX].SOKU_FLG );
	  			strcpy(pBUN_DATA[iCol*99+iRow].TOKU_FLG		,pCBO_SELECT[iCBO_INDEX].TOKU_FLG );
				strcpy(pBUN_DATA[iCol*99+iRow].KIKA_PRT 	,pCBO_SELECT[iCBO_INDEX].KIKA_PRT 	);
				strcpy(pBUN_DATA[iCol*99+iRow].VALUE_TYPE	,pCBO_SELECT[iCBO_INDEX].VALUE_TYPE 	);
			   	strcpy(pBUN_DATA[iCol*99+iRow].VALUE_DECI	,pCBO_SELECT[iCBO_INDEX].VALUE_DECI 	);
			   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_SU	,sSOKU_VAL_SU.c_str());
		   		strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_AVE	,sSOKU_VAL_AVE.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MAX	,sSOKU_VAL_MAX.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MIN	,sSOKU_VAL_MIN.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_OK		,sSOKU_OK.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].SKTYMD		,sSYSTEM_DATE.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].ADDYMD		,sDATE.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].ADDTIM		,sTIME.c_str());
		   		strcpy(pBUN_DATA[iCol*99+iRow].UPDYMD		,sDATE.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].UPDTIM		,sTIME.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].UPDCHR		,sUPDCHR.c_str());
			   	strcpy(pBUN_DATA[iCol*99+iRow].UPDCNT		,sUPDCNT.c_str());
				//2003.05.12 E.Takase Add��
				//2003.05.17 E.Takase Add��
  				strcpy(pBUN_DATA[iCol*99+iRow].UPD_NAME 	,sUPDNAME.c_str());
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
  				//pBUN_DATA[iCol*99+iRow].UPD_NAME 			= sUPDNAME;
				//2003.05.17 E.Takase Add �R�����g��
				//2003.05.12 E.Takase Add��
				//2003.05.12 E.Takase Add �R�����g��
  				//pBUN_DATA[iCol*99+iRow].UPD_NAME 			= GetTANTO(AnsiString(pBUN_DATA[iCol*99+iRow].UPDCHR));
				//2003.05.12 E.Takase Add �R�����g��
	           	pBUN_DATA[iCol*99+iRow].MAX 				= pCBO_SELECT[iCBO_INDEX].MAX ;
    	       	pBUN_DATA[iCol*99+iRow].MIN 				= pCBO_SELECT[iCBO_INDEX].MIN ;
				for(i1 = 0 ; i1 < AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_SU).ToIntDef(0);i1++)
				{
					strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL[i1],SGr_vSOKUTEI->Cells[1][i1].c_str());
    	        }
                SGr_vRIRE_SYUKA->Col = iCol;
                SGr_vRIRE_SYUKA->Row = iRow;
        	    SGr_Title->Cells[0][iRow] = AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_NM) + AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_SUB) + " " + AnsiString(pCBO_SELECT[iCBO_INDEX].TANI);
				SGr_Title->Cells[1][iRow] = AnsiString(iCBO_INDEX);
				SGr_vRIRE_SYUKA->Cells[iCol][iRow] = AnsiString(pBUN_DATA[iCol*99+iRow].SKTYMD).SubString(5,2)
            								  + "/" +AnsiString(pBUN_DATA[iCol*99+iRow].SKTYMD).SubString(7,2)
											  + " "+ AnsiString(pBUN_DATA[iCol*99+iRow].UPD_NAME);			//�f�o�b�O�p
                SGr_vRIRE_SYUKA->SetFocus();
                iWriteRow = iRow;
				break;
			}
			iRow ++;
		}
        if( SGr_Title->RowCount <= iRow )
        {
            strcpy(pBUN_DATA[iCol*99+iRow].DTKSHIN		,pCBO_SELECT[iCBO_INDEX].DTKSHIN);
            strcpy(pBUN_DATA[iCol*99+iRow].LOTNO		,SGr_vRIRE_SYUKA->Cells[iCol][0].c_str());
            strcpy(pBUN_DATA[iCol*99+iRow].HINBAN		,SGr_vRIRE_SYUKA->Cells[iCol][1].c_str());
            strcpy(pBUN_DATA[iCol*99+iRow].UNQ_NO		,pCBO_SELECT[iCBO_INDEX].UNQ_NO  	);
            strcpy(pBUN_DATA[iCol*99+iRow].KOMK_NO		,pCBO_SELECT[iCBO_INDEX].KOMK_NO 	);
		   	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_NM		,pCBO_SELECT[iCBO_INDEX].KOMK_NM 	);
		  	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_ENG		,pCBO_SELECT[iCBO_INDEX].KOMK_ENG	);
		 	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_SUB		,pCBO_SELECT[iCBO_INDEX].KOMK_SUB	);
			strcpy(pBUN_DATA[iCol*99+iRow].KOMK_SUB_ENG	,pCBO_SELECT[iCBO_INDEX].KOMK_SUB_ENG	);
	   		strcpy(pBUN_DATA[iCol*99+iRow].KIKI_NO		,pCBO_SELECT[iCBO_INDEX].KIKI_NO 	);
	  		strcpy(pBUN_DATA[iCol*99+iRow].KIKI_NM		,pCBO_SELECT[iCBO_INDEX].KIKI_NM 	);
	 		strcpy(pBUN_DATA[iCol*99+iRow].TANI			,pCBO_SELECT[iCBO_INDEX].TANI 	  );
			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_TYPE	,pCBO_SELECT[iCBO_INDEX].KIKA_TYPE );
   			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_KIND	,pCBO_SELECT[iCBO_INDEX].KIKA_KIND );
  			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_DECI	,pCBO_SELECT[iCBO_INDEX].KIKA_DECI );
 			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM1	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM1 );
			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM2	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM2 );
			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM3	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM3 );
            strcpy(pBUN_DATA[iCol*99+iRow].KIKA_STR		,pCBO_SELECT[iCBO_INDEX].KIKA_STR );
		   	strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB1	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB1 );
		  	strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB2	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB2 );
		 	strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB3	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB3 );
			strcpy(pBUN_DATA[iCol*99+iRow].SOKU_SU		,AnsiString(Num_SOKU_SU->Text).c_str());
	   		strcpy(pBUN_DATA[iCol*99+iRow].SOKU_FLG		,pCBO_SELECT[iCBO_INDEX].SOKU_FLG );
	  		strcpy(pBUN_DATA[iCol*99+iRow].TOKU_FLG		,pCBO_SELECT[iCBO_INDEX].TOKU_FLG );
			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_PRT 	,pCBO_SELECT[iCBO_INDEX].KIKA_PRT 	);
			strcpy(pBUN_DATA[iCol*99+iRow].VALUE_TYPE	,pCBO_SELECT[iCBO_INDEX].VALUE_TYPE 	);
		   	strcpy(pBUN_DATA[iCol*99+iRow].VALUE_DECI	,pCBO_SELECT[iCBO_INDEX].VALUE_DECI 	);
		   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_SU	,sSOKU_VAL_SU.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_AVE	,sSOKU_VAL_AVE.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MAX	,sSOKU_VAL_MAX.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MIN	,sSOKU_VAL_MIN.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_OK		,sSOKU_OK.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].SKTYMD		,sSYSTEM_DATE.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].ADDYMD		,sDATE.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].ADDTIM		,sTIME.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].UPDYMD		,sDATE.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].UPDTIM		,sTIME.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].UPDCHR		,sUPDCHR.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].UPDCNT		,sUPDCNT.c_str());
			//2003.05.12 E.Takase Add��
			//2003.05.17 E.Takase Add��
  			strcpy(pBUN_DATA[iCol*99+iRow].UPD_NAME 	,sUPDNAME.c_str());
			//2003.05.17 E.Takase Add��
			//2003.05.17 E.Takase Add �R�����g��
  			//pBUN_DATA[iCol*99+iRow].UPD_NAME 			= sUPDNAME;
			//2003.05.17 E.Takase Add �R�����g��
			//2003.05.12 E.Takase Add��
			//2003.05.12 E.Takase Add �R�����g��
  			//pBUN_DATA[iCol*99+iRow].UPD_NAME 			= GetTANTO(AnsiString(pBUN_DATA[iCol*99+iRow].UPDCHR));
			//2003.05.12 E.Takase Add �R�����g��
           	pBUN_DATA[iCol*99+iRow].MAX 				= pCBO_SELECT[iCBO_INDEX].MAX ;
           	pBUN_DATA[iCol*99+iRow].MIN 				= pCBO_SELECT[iCBO_INDEX].MIN ;
			for(i2 = 0 ; i2 < AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_SU).ToIntDef(0);i2++)
			{
				strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL[i2],SGr_vSOKUTEI->Cells[1][i2].c_str());
            }
        	//�q�n�v�̒ǉ��i��ɍs���Ɠ��̓Z���̓��e���N���A����̂ōŌ�ɍs�����Ƃɂ���j
        	SGr_Title->RowCount ++;
            SGr_vSOKU_SYUKA->RowCount ++;
            SGr_vRIRE_SYUKA->RowCount ++;
            SGr_vRIRE_SYUKA->Row = iRow;
            SGr_vRIRE_SYUKA->Col = iCol;

            SGr_Title->Cells[0][iRow] 			= AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_NM) + AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_SUB) + " " + AnsiString(pCBO_SELECT[iCBO_INDEX].TANI);
			SGr_Title->Cells[1][iRow] 			= AnsiString(iCBO_INDEX);
			SGr_vRIRE_SYUKA->Cells[iCol][iRow]      = AnsiString(pBUN_DATA[iCol*99+iRow].SKTYMD).SubString(5,2)
            								  + "/" + AnsiString(pBUN_DATA[iCol*99+iRow].SKTYMD).SubString(7,2)
											  + " " + AnsiString(pBUN_DATA[iCol*99+iRow].UPD_NAME);			//�f�o�b�O�p
            iWriteRow = iRow;
		}
        SGr_vRIRE_SYUKA->SetFocus();
        SGr_vRIRE_SYUKA->Refresh();
	}
	else
	{
    	iRow = 1 ;
		iCol = SGr_vSOKU_SYUKA->Col ;
		iSOKUCol = SGr_vRIRE_SYUKA->ColCount;
		while( iRow < SGr_vSOKU_SYUKA->RowCount)
		{
        	//�O���b�h����Ń^�C�g���������ꍇ
            //2003/12/11 E.Takse Trim�����ɂ���
			//if((SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0)						//�O���b�h����
    	    //&& (SGr_Title->Cells[0][iRow].Trim() == KOMK_NM.Trim()+KOMK_SUB.Trim()+" "+TANI.Trim()))   	//���ڂ�����
			//{
            //2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
            //                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
			//if((SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0)						//�O���b�h����
    	    //&& (SGr_Title->Cells[0][iRow] == KOMK_NM+KOMK_SUB+" "+TANI))   	//���ڂ�����
			//{
            sBuf = KOMK_NM.Trim()+KOMK_SUB.Trim()+" "+TANI.Trim();
			if((SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0)						//�O���b�h����
    	    && (SGr_Title->Cells[0][iRow].Trim() == sBuf.Trim()))   	//���ڂ�����
			{
                strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].DTKSHIN		,pCBO_SELECT[iCBO_INDEX].DTKSHIN);
    	        strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].LOTNO			,SGr_vSOKU_SYUKA->Cells[iCol][0].c_str());
    	        strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].HINBAN		,SGr_vSOKU_SYUKA->Cells[iCol][1].c_str());
        	    strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UNQ_NO		,pCBO_SELECT[iCBO_INDEX].UNQ_NO  	);
            	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_NO		,pCBO_SELECT[iCBO_INDEX].KOMK_NO 	);
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_NM		,pCBO_SELECT[iCBO_INDEX].KOMK_NM 	);
			  	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_ENG		,pCBO_SELECT[iCBO_INDEX].KOMK_ENG	);
			 	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_SUB		,pCBO_SELECT[iCBO_INDEX].KOMK_SUB	);
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_SUB_ENG	,pCBO_SELECT[iCBO_INDEX].KOMK_SUB_ENG	);
		   		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKI_NO		,pCBO_SELECT[iCBO_INDEX].KIKI_NO 	);
		  		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKI_NM		,pCBO_SELECT[iCBO_INDEX].KIKI_NM 	);
	 			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].TANI			,pCBO_SELECT[iCBO_INDEX].TANI 	  );
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_TYPE		,pCBO_SELECT[iCBO_INDEX].KIKA_TYPE );
	   			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_KIND		,pCBO_SELECT[iCBO_INDEX].KIKA_KIND );
  				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_DECI		,pCBO_SELECT[iCBO_INDEX].KIKA_DECI );
 				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM1		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM1 );
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM2		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM2 );
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM3		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM3 );
    	        strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_STR		,pCBO_SELECT[iCBO_INDEX].KIKA_STR );
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB1		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB1 );
		  		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB2		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB2 );
			 	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB3		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB3 );
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_SU		,AnsiString(Num_SOKU_SU->Text).c_str());
	   			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_FLG		,pCBO_SELECT[iCBO_INDEX].SOKU_FLG );
	  			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].TOKU_FLG		,pCBO_SELECT[iCBO_INDEX].TOKU_FLG );
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_PRT	    ,pCBO_SELECT[iCBO_INDEX].KIKA_PRT 	);
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].VALUE_TYPE	,pCBO_SELECT[iCBO_INDEX].VALUE_TYPE 	);
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].VALUE_DECI	,pCBO_SELECT[iCBO_INDEX].VALUE_DECI 	);
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_SU	,sSOKU_VAL_SU.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_AVE	,sSOKU_VAL_AVE.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_MAX	,sSOKU_VAL_MAX.c_str());
		   		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_MIN	,sSOKU_VAL_MIN.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_OK		,sSOKU_OK.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD		,sSYSTEM_DATE.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].ADDYMD		,sDATE.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].ADDTIM		,sTIME.c_str());
		   		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDYMD		,sDATE.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDTIM		,sTIME.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDCHR		,sUPDCHR.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDCNT		,sUPDCNT.c_str());
				//2003.05.12 E.Takase Add��
				//2003.05.17 E.Takase Add��
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME 		,sUPDNAME.c_str());
				//2003.05.17 E.Takase Add��
				//2003.05.17 E.Takase Add �R�����g��
				//pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME 			= sUPDNAME;
				//2003.05.17 E.Takase Add �R�����g��
				//2003.05.12 E.Takase Add��
				//2003.05.12 E.Takase Add �R�����g��
				//pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME 			= GetTANTO(AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDCHR));
				//2003.05.12 E.Takase Add �R�����g��
	           	pBUN_DATA[(iSOKUCol+iCol)*99+iRow].MAX 				= pCBO_SELECT[iCBO_INDEX].MAX ;
    	       	pBUN_DATA[(iSOKUCol+iCol)*99+iRow].MIN 				= pCBO_SELECT[iCBO_INDEX].MIN ;
				for(i1 = 0 ; i1 < AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_SU).ToIntDef(0);i1++)
				{
					strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL[i1],SGr_vSOKUTEI->Cells[1][i1].c_str());
	            }
				SGr_vSOKU_SYUKA->Cells[iCol][iRow] = AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD).SubString(5,2)
            								  + "/" +AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD).SubString(7,2)
											  + " " +AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME);			//�f�o�b�O�p
                SGr_vSOKU_SYUKA->Col = iCol;
                SGr_vSOKU_SYUKA->Row = iRow;
                SGr_vSOKU_SYUKA->SetFocus();
                iWriteRow = iRow;
				break;
        	}
            //2003/12/11 E.Takse Trim�����ɂ���
	        //else if((SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0)		//�O���b�h����
			//	 && (SGr_Title->Cells[0][iRow].Trim().Length() == 0  ))		//���ڂ���
        	//{
            //2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
            //                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
	        //else if((SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0)		//�O���b�h����
			//	 && (SGr_Title->Cells[0][iRow].Length() == 0  ))		//���ڂ���
        	//{
	        else if((SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0)		//�O���b�h����
				 && (SGr_Title->Cells[0][iRow].Trim().Length() == 0  ))		//���ڂ���
        	{
	        	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].DTKSHIN		,pCBO_SELECT[iCBO_INDEX].DTKSHIN);
    	        strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].LOTNO			,SGr_vSOKU_SYUKA->Cells[iCol][0].c_str());
    	        strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].HINBAN		,SGr_vSOKU_SYUKA->Cells[iCol][1].c_str());
        	    strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UNQ_NO		,pCBO_SELECT[iCBO_INDEX].UNQ_NO  	);
            	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_NO		,pCBO_SELECT[iCBO_INDEX].KOMK_NO 	);
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_NM		,pCBO_SELECT[iCBO_INDEX].KOMK_NM 	);
			  	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_ENG		,pCBO_SELECT[iCBO_INDEX].KOMK_ENG	);
			 	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_SUB		,pCBO_SELECT[iCBO_INDEX].KOMK_SUB	);
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_SUB_ENG	,pCBO_SELECT[iCBO_INDEX].KOMK_SUB_ENG	);
		   		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKI_NO		,pCBO_SELECT[iCBO_INDEX].KIKI_NO 	);
		  		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKI_NM		,pCBO_SELECT[iCBO_INDEX].KIKI_NM 	);
	 			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].TANI			,pCBO_SELECT[iCBO_INDEX].TANI 	  );
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_TYPE		,pCBO_SELECT[iCBO_INDEX].KIKA_TYPE );
	   			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_KIND		,pCBO_SELECT[iCBO_INDEX].KIKA_KIND );
  				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_DECI		,pCBO_SELECT[iCBO_INDEX].KIKA_DECI );
 				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM1		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM1 );
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM2		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM2 );
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM3		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM3 );
    	        strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_STR		,pCBO_SELECT[iCBO_INDEX].KIKA_STR );
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB1		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB1 );
		  		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB2		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB2 );
			 	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB3		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB3 );
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_SU		,AnsiString(Num_SOKU_SU->Text).c_str());
	   			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_FLG		,pCBO_SELECT[iCBO_INDEX].SOKU_FLG );
	  			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].TOKU_FLG		,pCBO_SELECT[iCBO_INDEX].TOKU_FLG );
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_PRT	    ,pCBO_SELECT[iCBO_INDEX].KIKA_PRT 	);
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].VALUE_TYPE	,pCBO_SELECT[iCBO_INDEX].VALUE_TYPE 	);
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].VALUE_DECI	,pCBO_SELECT[iCBO_INDEX].VALUE_DECI 	);

			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_SU	,sSOKU_VAL_SU.c_str());
		   		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_AVE	,sSOKU_VAL_AVE.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_MAX	,sSOKU_VAL_MAX.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_MIN	,sSOKU_VAL_MIN.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_OK		,sSOKU_OK.c_str());

			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD		,sSYSTEM_DATE.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].ADDYMD		,sDATE.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].ADDTIM		,sTIME.c_str());
		   		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDYMD		,sDATE.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDTIM		,sTIME.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDCHR		,sUPDCHR.c_str());
			   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDCNT		,sUPDCNT.c_str());
				//2003.05.12 E.Takase Add��
				//2003.05.17 E.Takase Add��
  				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME		,sUPDNAME.c_str());
				//2003.05.17 E.Takase Add��
	           	pBUN_DATA[(iSOKUCol+iCol)*99+iRow].MAX 				= pCBO_SELECT[iCBO_INDEX].MAX ;
    	       	pBUN_DATA[(iSOKUCol+iCol)*99+iRow].MIN 				= pCBO_SELECT[iCBO_INDEX].MIN ;
				for(i1 = 0 ; i1 < AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_SU).ToIntDef(0);i1++)
				{
					strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL[i1],SGr_vSOKUTEI->Cells[1][i1].c_str());
    	        }
        	    SGr_Title->Cells[0][iRow] = AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_NM) + AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_SUB) + " " + AnsiString(pCBO_SELECT[iCBO_INDEX].TANI);
				SGr_Title->Cells[1][iRow] 			= AnsiString(iCBO_INDEX);
				SGr_vSOKU_SYUKA->Cells[iCol][iRow] = AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD).SubString(5,2)
            								  + "/" +AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD).SubString(7,2)
											  + " "+ AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME);			//�f�o�b�O�p
                SGr_vSOKU_SYUKA->Col = iCol;
                SGr_vSOKU_SYUKA->Row = iRow;
                SGr_vSOKU_SYUKA->SetFocus();
                iWriteRow = iRow;
				break;
			}
			iRow ++;
		}
        if( SGr_Title->RowCount <= iRow )
        {
        	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].DTKSHIN		,pCBO_SELECT[iCBO_INDEX].DTKSHIN);
            strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].LOTNO			,SGr_vSOKU_SYUKA->Cells[iCol][0].c_str());
            strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].HINBAN		,SGr_vSOKU_SYUKA->Cells[iCol][1].c_str());
            strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UNQ_NO		,pCBO_SELECT[iCBO_INDEX].UNQ_NO  	);
            strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_NO		,pCBO_SELECT[iCBO_INDEX].KOMK_NO 	);
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_NM		,pCBO_SELECT[iCBO_INDEX].KOMK_NM 	);
		  	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_ENG		,pCBO_SELECT[iCBO_INDEX].KOMK_ENG	);
		 	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_SUB		,pCBO_SELECT[iCBO_INDEX].KOMK_SUB	);
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_SUB_ENG	,pCBO_SELECT[iCBO_INDEX].KOMK_SUB_ENG	);
	   		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKI_NO		,pCBO_SELECT[iCBO_INDEX].KIKI_NO 	);
	  		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKI_NM		,pCBO_SELECT[iCBO_INDEX].KIKI_NM 	);
	 		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].TANI			,pCBO_SELECT[iCBO_INDEX].TANI 	  );
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_TYPE		,pCBO_SELECT[iCBO_INDEX].KIKA_TYPE );
   			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_KIND		,pCBO_SELECT[iCBO_INDEX].KIKA_KIND );
  			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_DECI		,pCBO_SELECT[iCBO_INDEX].KIKA_DECI );
 			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM1		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM1 );
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM2		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM2 );
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM3		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM3 );
            strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_STR		,pCBO_SELECT[iCBO_INDEX].KIKA_STR );
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB1		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB1 );
		  	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB2		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB2 );
		 	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB3		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB3 );
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_SU		,AnsiString(Num_SOKU_SU->Text).c_str());
	   		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_FLG		,pCBO_SELECT[iCBO_INDEX].SOKU_FLG );
	  		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].TOKU_FLG		,pCBO_SELECT[iCBO_INDEX].TOKU_FLG );
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_PRT	    ,pCBO_SELECT[iCBO_INDEX].KIKA_PRT 	);
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].VALUE_TYPE	,pCBO_SELECT[iCBO_INDEX].VALUE_TYPE 	);
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].VALUE_DECI	,pCBO_SELECT[iCBO_INDEX].VALUE_DECI 	);
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_SU	,sSOKU_VAL_SU.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_AVE	,sSOKU_VAL_AVE.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_MAX	,sSOKU_VAL_MAX.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_MIN	,sSOKU_VAL_MIN.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_OK		,sSOKU_OK.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD		,sSYSTEM_DATE.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].ADDYMD		,sDATE.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].ADDTIM		,sTIME.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDYMD		,sDATE.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDTIM		,sTIME.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDCHR		,sUPDCHR.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDCNT		,sUPDCNT.c_str());
			//2003.05.12 E.Takase Add��
			//2003.05.17 E.Takase Add��
  			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME 	 ,sUPDNAME.c_str());
			//2003.05.17 E.Takase Add��
			//2003.05.17 E.Takase Add �R�����g��
  			//pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME 	 = sUPDNAME;
			//2003.05.17 E.Takase Add �R�����g��
			//2003.05.12 E.Takase Add��
			//2003.05.12 E.Takase Add �R�����g��
  			//pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME 	 = GetTANTO(AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDCHR));
			//2003.05.12 E.Takase Add �R�����g��
           	pBUN_DATA[(iSOKUCol+iCol)*99+iRow].MAX 					= pCBO_SELECT[iCBO_INDEX].MAX ;
           	pBUN_DATA[(iSOKUCol+iCol)*99+iRow].MIN 					= pCBO_SELECT[iCBO_INDEX].MIN ;
			for(i2 = 0 ; i2 < AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_SU).ToIntDef(0);i2++)
			{
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL[i2],SGr_vSOKUTEI->Cells[1][i2].c_str());
            }
        //��ɃO���b�h�̒ǉ����s���Ɠ��͂������ʂ��N���A����Ă��܂��̂ł��ƂɎ����Ă���
        	SGr_Title->RowCount ++;
            SGr_vRIRE_SYUKA->RowCount ++;
            SGr_vSOKU_SYUKA->RowCount ++;
            SGr_vSOKU_SYUKA->Row = iRow;
            SGr_vSOKU_SYUKA->Col = iCol;

            SGr_Title->Cells[0][iRow] = AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_NM) + AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_SUB) + " " + AnsiString(pCBO_SELECT[iCBO_INDEX].TANI);
			SGr_Title->Cells[1][iRow] = AnsiString(iCBO_INDEX);
			SGr_vSOKU_SYUKA->Cells[iCol][iRow] =     AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD).SubString(5,2)
            								  + "/" +AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD).SubString(7,2)
											  + " "+ AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME);			//�f�o�b�O�p
            iWriteRow = iRow;
		}
        SGr_vSOKU_SYUKA->SetFocus();
        SGr_vSOKU_SYUKA->Refresh();
	}
    i1 = iRow;

//�����p����NO�̍쐬
	if( iENA_GRID == 1 )	iCol += iSOKUCol;
    sBuf = "SELECT * FROM KSD11";
    sBuf += " WHERE DTKSHIN = '" + AnsiString(pBUN_DATA[iCol*99+i1].DTKSHIN) + "'";
    sBuf += " AND   HINBAN = '"  + AnsiString(pBUN_DATA[iCol*99+i1].HINBAN) + "'";
    sBuf += " AND   LOTNO = '" 	 + AnsiString(pBUN_DATA[iCol*99+i1].LOTNO) + "'";
    sBuf += " ORDER BY BNKT_UNQ_NO DESC ";
// Initial Query
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    Form1->Query1->Active = true;
	if( Form1->Query1->Eof == true )
	{
		strcpy(pBUN_DATA[iCol*99+i1].BNKT_UNQ_NO,"0000");
    }
	else
	{
		sBuf = Form1->Query1->FieldValues["BNKT_UNQ_NO"];
		sBuf = sBuf.ToIntDef(0) + 1;
		sBuf = AnsiString::StringOfChar('0', 4-sBuf.Length())+sBuf;
		strcpy(pBUN_DATA[iCol*99+i1].BNKT_UNQ_NO,sBuf.c_str());
    }
    Form1->Query1->Close();

    sBuf = "insert into KSD11(";
    sBuf += " DTKSHIN, HINBAN, LOTNO, BNKT_UNQ_NO, UNQ_NO,";
	sBuf += " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG,";
	sBuf += " KIKI_NO, KIKI_NM, TANI, KIKA_TYPE, KIKA_KIND,";
	sBuf += " KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, KIKA_STR,";
	sBuf += " KIKA_SUB1, KIKA_SUB2, KIKA_SUB3,";
	sBuf += " SOKU_SU, SOKU_FLG, TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI,";
	sBuf += " SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05,";
	sBuf += " SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,";
	sBuf += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK,";
    sBuf += " SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT)";

    sBuf += " VALUES('";
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].DTKSHIN)		+ "','";	//	���Ӑ�i��
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].HINBAN)		+ "','";	//	���b�gNO
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].LOTNO)		+ "',";	//	���b�gNO
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].BNKT_UNQ_NO)	+ ",";	//
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].UNQ_NO)		+ ",";	//

    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KOMK_NO)  	+ " ,'";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KOMK_NM)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KOMK_ENG)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KOMK_SUB)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KOMK_SUB_ENG)+ "', ";	//	�����

    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKI_NO)  	+ " ,'";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKI_NM)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].TANI)  		+ "', ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKA_TYPE)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKA_KIND)  	+ " , ";	//	�����

    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKA_DECI)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKA_NUM1)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKA_NUM2)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKA_NUM3)  	+ " ,'";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKA_STR)  	+ "','";	//	�����

    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKA_SUB1)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKA_SUB2)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKA_SUB3)  	+ "', ";	//	�����

    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].SOKU_SU)  	    + " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].SOKU_FLG)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].TOKU_FLG)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].KIKA_PRT)      + " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].VALUE_TYPE)    + " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].VALUE_DECI)    + " ,'";	//	�����

    for( i2 = 0; i2 <  10 ;i2++)
	{
		if(  AnsiString(pBUN_DATA[iCol*99+i1].SOKU_VAL[i2]).Length() == 0 )
		{
			sBuf += " ','";
		}
		else
		{
    		//sBuf += AnsiString(pBUN_DATA[iCol*99+i1].SOKU_VAL[i2])  + "','";	//	�o�^��
        // ��������
		    sRESULT_BUF = AnsiString(pBUN_DATA[iCol*99+i1].SOKU_VAL[i2]);
            if( sRESULT_BUF.Length() >= 14 ){
    		    if ( sRESULT_BUF.ByteType( 14 ) == mbLeadByte ){
				    sRESULT_BUF = sRESULT_BUF.SubString(1,13);
                }
            }
            sBuf += sRESULT_BUF + "','";
    	}
	}
    sBuf = sBuf.SubString(1,sBuf.Length()-1);
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].SOKU_VAL_SU)  	    + " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].SOKU_VAL_AVE)  	+ " , ";	//	�o�^��
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].SOKU_VAL_MAX)  	+ " , ";	//	�o�^����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].SOKU_VAL_MIN)  	+ " , ";	//	�ύX��
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].SOKU_OK)  	        + " ,'";	//	�ύX��
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].SKTYMD)  	        + "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].ADDYMD)  	        + "','";	//	�o�^��
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].ADDTIM)  	        + "','";	//	�o�^����
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].UPDYMD)  	        + "','";	//	�ύX��
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].UPDTIM)  	        + "','";	//	�ύX����
	sBuf += AnsiString(pBUN_DATA[iCol*99+i1].UPDCHR)		    + "','";	//  �S���҃R�[�h
    sBuf += AnsiString(pBUN_DATA[iCol*99+i1].UPDCNT)            + "'";  	//	�X�V��
    sBuf += ")";
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
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);

// �₢�������̎��s
	try
    {
    	Query1->ExecSQL();
    }
    catch(EDatabaseError& e)
    {
    	Form1->SBr1->Panels->Items[0]->Text = e.Message;
        Form1->SBr1->Update();
        return;
    }
    catch(Exception& e)
    {
    	Form1->SBr1->Panels->Items[0]->Text = e.Message;
        Form1->SBr1->Update();
        return;
    }
    BtnF11->Enabled = true;

//��O�f�[�^�̏���
    if(AnsiString(pBUN_DATA[iCol*99+i1].SOKU_SU).ToIntDef(0) < 11 ) return;
//�ȑO�̃f�[�^������
    sBuf = "DELETE from KSD12";
    sBuf += " where DTKSHIN='" + AnsiString(pBUN_DATA[iCol*99+i1].DTKSHIN)  + "'";	// ���Ӑ�i��
    sBuf += " and HINBAN='" + AnsiString(pBUN_DATA[iCol*99+i1].HINBAN) + "'";			// ���b�gNO
    sBuf += " and LOTNO='" + AnsiString(pBUN_DATA[iCol*99+i1].LOTNO) + "'";			// ���b�gNO
    sBuf += " and BNKT_UNQ_NO='" + AnsiString(pBUN_DATA[iCol*99+i1].BNKT_UNQ_NO)   + "'";	//	�����p����NO

// Initial Query
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
	   	MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
	  	return;
    }
    catch(Exception& e) {
        MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return;
    }

//��O�f�[�^�̏�������
    for(i2 = 10 ; i2 < AnsiString(pBUN_DATA[iCol*99+i1].SOKU_SU).ToIntDef(0) ; i2++)
    {
        sBuf = "insert into KSD12(";
        sBuf += " DTKSHIN, HINBAN, LOTNO, BNKT_UNQ_NO, SOKU_NO, SOKU_VAL )";

        sBuf += " VALUES('";
        sBuf += AnsiString(pBUN_DATA[iCol*99+i1].DTKSHIN)	    + "','";	//	���Ӑ�i��
        sBuf += AnsiString(pBUN_DATA[iCol*99+i1].HINBAN)		+ "','";	//	���Ӑ�i��
        sBuf += AnsiString(pBUN_DATA[iCol*99+i1].LOTNO)		    + "', ";	//	���Ӑ�i��
        sBuf += AnsiString(pBUN_DATA[iCol*99+i1].BNKT_UNQ_NO)   + " , ";	//	���Ӑ�i��
        sBuf += AnsiString(i2+1)		                        + " ,'";	//	���Ӑ�i��
        if(  AnsiString(pBUN_DATA[iCol*99+i1].SOKU_VAL[i2]).Length() == 0 )
        {
            sBuf += " ')";
        }
		else
		{
    		//sBuf += AnsiString(pBUN_DATA[iCol*99+i1].SOKU_VAL[i2])  + "')";	//	�o�^��
        // ��������
		    sRESULT_BUF = AnsiString(pBUN_DATA[iCol*99+i1].SOKU_VAL[i2]);
            if( sRESULT_BUF.Length() >= 14 ){
    		    if ( sRESULT_BUF.ByteType( 14 ) == mbLeadByte ){
				    sRESULT_BUF = sRESULT_BUF.SubString(1,13);
                }
            }
            sBuf += sRESULT_BUF + "')";
    	}
    // Initial Query
        Query1->Close();
        Query1->SQL->Clear();
        Query1->SQL->Add(sBuf);

        // �₢�������̎��s
        try {
            Query1->ExecSQL();
        }
        catch(EDatabaseError& e) {
	   	    MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
	  	    return;
        }
        catch(Exception& e) {
            MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
            return;
        }
    }
    Query1->Close();
	return;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�Q�F�߂�v�{�^�������������̏���
//
//  �@�\����
//    ��ʂ���A������ʂɖ߂�܂��B
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
void __fastcall TForm7::BtnF12Click(TObject *Sender)
{
     Close();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyDown �C�x���g    �F�R���g���[���Ƀt�H�[�J�X������ԂɃ��[�U�[���C�ӂ̃L�[�������Ɣ������܂��B
//
//  �@�\����
//    �@�f�[�^���͒����𒲂בS�f�[�^���͎��͎����I�Ɂu�V�K�o�^�v�u�C���v���s���܂��B
//    �A�t�@���N�V�����L�[���̓C�x���g�𔭐������܂��B
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    WORD &Key         �F���͂��ꂽ���j�[�N�ȃL�[�R�[�h
//  �@TShiftState Shift �FShift�CAlt�CCtrl�L�[���L�[�X�g���[�N�Ɍ��ѕt�����Ă��邩�ǂ����������܂��B
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm7::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    int iCol,iRow;
    bool bINPUT_DATA;
    int iNSU;

	if(Sender == SGr_vSOKUTEI )
	{
        bNOW_SOKUTEI = true;
        iCol = SGr_vSOKUTEI->Col;
        iRow = SGr_vSOKUTEI->Row;
        //SGr_vSOKUTEISelectCell(Sender, iCol,iRow, true);
		if(Key == VK_RETURN)
		{
//�v�]�ɂ��ǉ��i�f�[�^���͌㎩���o�^�@�\�j
            bINPUT_DATA = true;
            //�S�Ẵf�[�^���͂������������𒲂ׂ܂�
            for(iRow = 0; iRow < SGr_vSOKUTEI->RowCount; iRow++)
            {
                if(SGr_vSOKUTEI->Cells[1][iRow].Trim().Length() == 0)
                {
                    bINPUT_DATA = false;
                    break;
                }
            }
//����O���b�h�ɑS�ăf�[�^�����͂���Ă��āA��ԉ��̃O���b�h��Enter�������ꂽ�ꍇ�͓o�^���s���܂�
            if( bINPUT_DATA == true &&  SGr_vSOKUTEI->Row == SGr_vSOKUTEI->RowCount - 1)
            {
                if(iENA_GRID == 0)
                {
                    iCol = SGr_vRIRE_SYUKA->Col;
                    iRow = SGr_vRIRE_SYUKA->Row;
                }
                else
                {
                    iCol = SGr_vSOKU_SYUKA->Col;
                    iRow = SGr_vSOKU_SYUKA->Row;
                }

                //iSOKU_SU = Num_SOKU_SU->Text.ToIntDef(0);
	    	    if(iENA_GRID == 0)											//���ݑI�𒆂̃O���b�h��ۑ�
                {
                    if(SGr_vRIRE_SYUKA->Cells[iCol][iRow].Length() == 0)
                    {
                        //���O�Ƀf�[�^���Ȃ���ΐV�K�o�^�ł�
                        BtnF08Click(Sender);
                    }
                    else
                    {
                        //���O�Ƀf�[�^������ΏC���ł�
                        BtnF09Click(Sender);
                    }
                    //�Z�[�u��Ɏ��̍��ڂɈړ����܂�
                    if( SGr_vRIRE_SYUKA->RowCount-1 > SGr_vRIRE_SYUKA->Row)
                    {
                        SGr_vRIRE_SYUKA->Row ++;
                        SGr_vRIRE_SYUKA->SetFocus();
                    }
                    else if( SGr_vRIRE_SYUKA->ColCount-1 > SGr_vRIRE_SYUKA->Col)
                    {
                        SGr_vRIRE_SYUKA->Col ++;
                        SGr_vRIRE_SYUKA->Row = 1;
                    }
                    else
                    {
                        SGr_vSOKU_SYUKA->Col = 0;
                        SGr_vSOKU_SYUKA->Row = 1;
                        SGr_vSOKU_SYUKA->SetFocus();
                        return;
                    }
                    iCol = SGr_vRIRE_SYUKA->Col;
                    iRow = SGr_vRIRE_SYUKA->Row;
                    //�ȑO�̓o�^���Ȃ���΂����̒��o��A�����ʂ�\�����Ȃ����܂��B
                    if(SGr_vRIRE_SYUKA->Cells[iCol][iRow].Length() == 0 )
                    {
                        iNSU = GET_NSU();
                        if( iNSU != 9999 )
                        {
                            Num_SOKU_SU->Text = AnsiString(iNSU);
                            SGr_vSOKUTEI->Col = 1;
                            SGr_vSOKUTEI->Row = 0;
                            SGr_vSOKUTEISelectCell(Sender,1 , 0 , true);
                        }
                        else
                        {
                            Num_SOKU_SU->SetFocus();
                        }
                    }
                    else
                    {
                    //�ȑO�̃f�[�^������Α���O���b�h�̈ړ������s���܂�
                        SGr_vSOKUTEI->Col = 1;
                        SGr_vSOKUTEI->Row = 0;
                        SGr_vSOKUTEISelectCell(Sender,1 , 0 , true);
                        SGr_vSOKUTEI->SetFocus();
                    }

                }
	    	    else											//���ݑI�𒆂̃O���b�h��ۑ�
                {
                    if(SGr_vSOKU_SYUKA->Cells[iCol][iRow].Length() == 0)
                    {
                        BtnF08Click(Sender);
                    }
                    else
                    {
                        BtnF09Click(Sender);
                    }
                    if( SGr_vSOKU_SYUKA->RowCount-1 > SGr_vSOKU_SYUKA->Row)
                    {
                        SGr_vSOKU_SYUKA->Row ++;
                        SGr_vSOKU_SYUKA->SetFocus();
                    }
                    else if( SGr_vSOKU_SYUKA->ColCount-1 > SGr_vSOKU_SYUKA->Col)
                    {
                        SGr_vSOKU_SYUKA->Col ++;
                        SGr_vSOKU_SYUKA->Row = 1;
                    }
                    iCol = SGr_vSOKU_SYUKA->Col;
                    iRow = SGr_vSOKU_SYUKA->Row;
                    //�ȑO�̓o�^���Ȃ���΂����̒��o��A�����ʂ�\�����Ȃ����܂��B
                    if(SGr_vSOKU_SYUKA->Cells[iCol][iRow].Length() == 0 )
                    {
                        iNSU = GET_NSU();
                        if( iNSU != 9999 )
                        {
                            Num_SOKU_SU->Text = AnsiString(iNSU);
                            SGr_vSOKUTEI->Col = 1;
                            SGr_vSOKUTEI->Row = 0;
                            SGr_vSOKUTEI->SetFocus();
                        }
                        else
                        {
                            Num_SOKU_SU->SetFocus();
                        }
                    }
                    else
                    {
                    //�ȑO�̃f�[�^������Α���O���b�h�̈ړ������s���܂�
                        SGr_vSOKUTEI->Col = 1;
                        SGr_vSOKUTEI->Row = 0;
                        SGr_vSOKUTEISelectCell(Sender,1 , 0 , true);
                        SGr_vSOKUTEI->SetFocus();
                    }
                }
            }
            else
            {
			    if( SGr_vSOKUTEI->RowCount - 1 >  SGr_vSOKUTEI->Row)
			    {
            	    SGr_vSOKUTEI->Row ++;      
			    }
		    	else
                {
            	    SGr_vSOKUTEI->Row = 0;
			    }
            }
        }
        bNOW_SOKUTEI = false;
	}
	else
	{
     	switch(Key)
     	{
         	case VK_F5	: BtnF05Click(Sender);    return; break;
            case VK_F7	: BtnF07Click(Sender);    return; break;
         	case VK_F8	: BtnF08Click(Sender);    return; break;
         	case VK_F9	: BtnF09Click(Sender);    return; break;
         	// 2003/05/19 A.Tamura
         	case VK_F10 : BtnF10Click(Sender);
            			  Key = 0;
                          return;
					  	  break;
            //2003.05.17 E.Takase �R�����g��
         	//case VK_F11	: BtnF11Click(Sender);    break;
            //2003.05.17 E.Takase �R�����g��
            case VK_ESCAPE:
         	case VK_F12	: BtnF12Click(Sender);    return; break;
     	}
        if(( Sender == SGr_vRIRE_SYUKA || Sender == SGr_vSOKU_SYUKA)
        && (Key >= VK_SPACE)
        && (Key != VK_UP)
        && (Key != VK_RIGHT)
        && (Key != VK_LEFT)
        && (Key != VK_DOWN))
        {
            if( Sender == SGr_vRIRE_SYUKA )
            {
                iRow = SGr_vRIRE_SYUKA->Row;
                iCol = SGr_vRIRE_SYUKA->Col;
                SGr_vRIRE_SYUKA->SetFocus();
            }
            else
            {
                iRow = SGr_vSOKU_SYUKA->Row;
                iCol = SGr_vSOKU_SYUKA->Col;
                SGr_vSOKU_SYUKA->SetFocus();
            }
            if(Sender == SGr_vRIRE_SYUKA )
            {
                if( SGr_vRIRE_SYUKA->Cells[iCol][iRow].Length() == 0)
                {
                    iNSU = GET_NSU();
                    if( iNSU != 9999 )
                    {
                        Num_SOKU_SU->Text = AnsiString(iNSU);
                        SGr_vSOKUTEI->Col = 1;
                        SGr_vSOKUTEI->Row = 0;
                        SGr_vSOKUTEI->SetFocus();
                        keybd_event(Key,0,0,0);
                        SGr_vSOKUTEISelectCell(SGr_vSOKUTEI,1 , 0 , true);
                    }
                    else
                    {
                        Num_SOKU_SU->SetFocus();
                    }
                }
                else
                {
                    SGr_vSOKUTEI->Col = 1;
                    SGr_vSOKUTEI->Row = 0;
                    SGr_vSOKUTEI->SetFocus();
                    keybd_event(Key,0,0,0);
                    SGr_vSOKUTEISelectCell(SGr_vSOKUTEI,1 , 0 , true);
                }
            }
            else
            {
                if( SGr_vSOKU_SYUKA->Cells[iCol][iRow].Length() == 0)
                {
                    iNSU = GET_NSU();
                    if( iNSU != 9999 )
                    {
                        Num_SOKU_SU->Text = AnsiString(iNSU);
                        SGr_vSOKUTEI->Col = 1;
                        SGr_vSOKUTEI->Row = 0;
                        SGr_vSOKUTEI->SetFocus();
                        keybd_event(Key,0,0,0);
                        SGr_vSOKUTEISelectCell(SGr_vSOKUTEI,1 , 0 , true);
                    }
                    else
                    {
                        Num_SOKU_SU->SetFocus();
                    }
                }
                else
                {
                    SGr_vSOKUTEI->Col = 1;
                    SGr_vSOKUTEI->Row = 0;
                    SGr_vSOKUTEI->SetFocus();
                    keybd_event(Key,0,0,0);
                    SGr_vSOKUTEISelectCell(SGr_vSOKUTEI,1 , 0 , true);
                }
            }
        }
	}

}

//---------------------------------------------------------------------------
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
void __fastcall TForm7::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if( !fFind )   return;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnCreate�C�x���g	�FForm7���쐬�����Ƃ��ɔ������܂��B
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
void __fastcall TForm7::FormCreate(TObject *Sender)
{

	// �_�~�[���b�g�ԍ��̐ݒ�
	SGr_Title->ColCount = 2;
	SGr_Title->Cells[0][0] = "���荀��";
    SGr_Title->ColWidths[0] = 150;
    SGr_Title->Width  = SGr_Title->ColWidths[0] + 5;

	SGr_vRIRE_SYUKA->ColCount = 2;
	SGr_vSOKU_SYUKA->ColCount = 2;

    SGr_vSOKUTEI->ColCount = 2;
    SGr_vSOKUTEI->RowCount = 2;
    Num_SOKU_SU->Text = "1";
    SGr_vSOKUTEI->ColWidths[0] = 30;
    SGr_vSOKUTEI->ColWidths[1] = 80;
	SGr_vSOKUTEI->Cells[0][0] = " 1";
	SGr_vSOKUTEI->Cells[0][1] = " 2";
    BtnF11->Enabled = false;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnActivate �C�x���g�FForm7���A�N�e�B�u�ɂȂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    Form7�̏����ݒ���s���܂��B
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
void __fastcall TForm7::FormActivate(TObject *Sender)
{
    bNOW_SOKUTEI = false;
    bNUM_SET = false;
    bGRIDON = false;
    SGr_vRIRE_SYUKA->Col = 0;
    SGr_vRIRE_SYUKA->Row = 1;
    SGr_vSOKU_SYUKA->Col = 0;
    SGr_vSOKU_SYUKA->Row = 1;
    memset(&pInfoGlaph,(int)NULL,sizeof(pInfoGlaph));

    memset(&pTEMP_BUN_DATA,(int)NULL,sizeof(pTEMP_BUN_DATA));
    Cbo_KOMK_NM->Clear();
    GRID_INIT();
	//2003.05.12 E.Takase Add��
	Pnl_HINBAN->Caption = Form1->sNowDTKSHIN;
	//2003.05.12 E.Takase Add��
	PnlTanName->Caption = Form1->USER_NAM;
	Cbo_Set();

	SGr_vRIRE_SYUKA->RowCount = 2;
	SGr_vSOKU_SYUKA->RowCount = 2;
	SGr_Title->RowCount = 2;

	Get_KSD11();
	Set_LOT_GRID();
	Cbo_LOT->ItemIndex = 0;
	Cbo_KOMK_NM->ItemIndex = 0;
	pInfoGlaph.GRID_NO = 5;					//�v����Ƃ̒ʐM�����̃t�H�[���ɂ܂킵�܂�.
	Cbo_KOMK_NMChange(Cbo_KOMK_NM);
    sSYSTEM_DATE = FormatDateTime("yyyymmdd",Date());
	MEdt_SOKU_DATE->Text = sSYSTEM_DATE.SubString(1,4) + "/"
                         + sSYSTEM_DATE.SubString(5,2) + "/"
                         + sSYSTEM_DATE.SubString(7,2);
	PnlTanName->Caption = Form1->USER_NAM;
    SGr_vRIRE_SYUKA->Tag = 0;
    SGr_vSOKU_SYUKA->SetFocus();
    FormSelectCell(SGr_vSOKU_SYUKA,SGr_vSOKU_SYUKA->Col,SGr_vSOKU_SYUKA->Row,true);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��FStringGrid�̏������ƃR���{�{�b�N�X�i���b�g�j�̏��������s���܂��B
//
//  �@�\����
//    StringGrid�̏������ƃR���{�{�b�N�X�i���b�g�j�̏��������s���܂��B
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
void __fastcall TForm7::Cbo_Set(void)
{
	int iCol;//,iRow;
	int i1;
    i1 = 0;

	Cbo_LOT->Clear();
//����l�ꗗ�i�����j�̃��b�g�Z�b�g
	SGr_vRIRE_SYUKA->ColCount = Form1->SGr_vRIRE_SYUKA->ColCount;
    if(Form1->iRIRE_CNT != 0)
    {
    	for(iCol = 0;iCol < Form1->SGr_vRIRE_SYUKA->ColCount;iCol++)
        {
		    if( Form1->SGr_tRIRE->Cells[iCol][0].Trim().Length() != 0 )
    		{
	    		SGr_vRIRE_SYUKA->Cells[iCol][0] = Form1->SGr_tRIRE->Cells[iCol][0];
	    		SGr_vRIRE_SYUKA->Cells[iCol][1] = Form1->SGr_tRIRE->Cells[iCol][1];
		    	Cbo_LOT->Items->Insert(i1,Form1->SGr_tRIRE->Cells[iCol][0]);
			    i1 ++;
    		}
	    }
    }
	if(SGr_vRIRE_SYUKA->Cells[0][0].Trim().Length() == 0)
	{
		SGr_vRIRE_SYUKA->Visible = false;
	}
    else
    {
		SGr_vRIRE_SYUKA->Visible = true;
    }
//����l�ꗗ�i����)�̃��b�g�Z�b�g
	SGr_vSOKU_SYUKA->ColCount = Form1->SGr_vSOKU_SYUKA->ColCount;
	for(iCol = 0;iCol < Form1->SGr_vSOKU_SYUKA->ColCount;iCol++)
    {
		if( Form1->SGr_tSOKU->Cells[iCol][0].Trim().Length() != 0 )
		{
			SGr_vSOKU_SYUKA->Cells[iCol][0] = Form1->SGr_tSOKU->Cells[iCol][0];
			SGr_vSOKU_SYUKA->Cells[iCol][1] = Form1->SGr_tSOKU->Cells[iCol][1];
			Cbo_LOT->Items->Insert(i1,Form1->SGr_tSOKU->Cells[iCol][0]);
        	i1++;
		}
    }
	if(SGr_vSOKU_SYUKA->Cells[0][0].Trim().Length() == 0)
	{
		SGr_vSOKU_SYUKA->Visible = false;
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��F�o�׌������ڂ̃R�s�[��KSD11�̓ǂݍ��ݕ\�����s���܂��B
//
//  �@�\����
//    �@�o�׌������ځi�K�i�܂ށj�̃R�s�[�i�R���{�{�b�N�X�ɘA���j�B
//    �AKSD11�i������ѕ����f�[�^�j�AKSD12�i������ѕ�����O�f�[�^�j�ǂݍ��ݕ\��
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
void __fastcall TForm7::Get_KSD11(void)
{
	AnsiString sBuf,sBuf2,sLot,KOMK_NM,KOMK_SUB,TANI;
	int iCol,iRow;
	//int iRowCount;
    int iSOKUCol,iBUNCol;
    int i1,i2,i3;
	iDB_RECORD = 0;
    //int SOKU_SU,KOMK_NO,UNQ_NO;
    int iIndex;
	double dMIN,dMAX;
	bool bSearch,bMIDASI;
	int iCBO_INDEX;
	AnsiString sSelectLot;
    AnsiString sLot_Where;

    // �������̊m��
	iSOKUCol 	= SGr_vRIRE_SYUKA->ColCount ;
	iBUNCol 	= SGr_vSOKU_SYUKA->ColCount ;

    // �������̊J��
    if( hBUN_DATA ){
        GlobalUnlock( hBUN_DATA );
        hBUN_DATA = GlobalFree( hBUN_DATA );
    }

    hBUN_DATA = GlobalAlloc( GHND, sizeof(struct BUN_DATA) * ((iSOKUCol + iBUNCol + 1) * 99 ));
    if( hBUN_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pBUN_DATA = (struct BUN_DATA *)GlobalLock(hBUN_DATA);
    if( hBUN_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
//�����ʂ̃f�[�^�ǂݍ���
	iCBO_INDEX = 0;
//�R���{�{�b�N�X�I��p�f�[�^�쐬
    for(i2= 0;i2< Form1->iOrCount;i2++)
    {
        strcpy(pCBO_SELECT[iCBO_INDEX].DTKSHIN 		, pORDATA[i2].DTKSHIN);
        //strcpy(pCBO_SELECT[iCBO_INDEX].LOTNO 	   	, pORDATA[i2].LOTNO);
        strcpy(pCBO_SELECT[iCBO_INDEX].UNQ_NO  		, pORDATA[i2].UNQ_NO);
        strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_NO 		, pORDATA[i2].KOMK_NO);
        strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_NM 		, pORDATA[i2].KOMK_NM);
        strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_ENG		, pORDATA[i2].KOMK_ENG);
        strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_SUB		, pORDATA[i2].KOMK_SUB);
        strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_SUB_ENG	, pORDATA[i2].KOMK_SUB_ENG);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKI_NO 		, pORDATA[i2].KIKI_NO);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKI_NM 		, pORDATA[i2].KIKI_NM);
        strcpy(pCBO_SELECT[iCBO_INDEX].TANI 	   	, pORDATA[i2].TANI);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_TYPE 	, pORDATA[i2].KIKA_TYPE);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_KIND 	, pORDATA[i2].KIKA_KIND);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_DECI 	, pORDATA[i2].KIKA_DECI);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_NUM1 	, pORDATA[i2].KIKA_NUM1);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_NUM2 	, pORDATA[i2].KIKA_NUM2);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_NUM3 	, pORDATA[i2].KIKA_NUM3);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_STR 	, pORDATA[i2].KIKA_STR);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_SUB1 	, pORDATA[i2].KIKA_SUB1);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_SUB2 	, pORDATA[i2].KIKA_SUB2);
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_SUB3 	, pORDATA[i2].KIKA_SUB3);
        strcpy(pCBO_SELECT[iCBO_INDEX].SOKU_SU 		, pORDATA[i2].SOKU_SU);
    //���b�g���ɔ��f����ɂ͂ǂ����邩�H
        strcpy(pCBO_SELECT[iCBO_INDEX].SOKU_FLG 	, "1");
        strcpy(pCBO_SELECT[iCBO_INDEX].TOKU_FLG 	, "0");
        strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_PRT 	, pORDATA[i2].KIKA_PRT);
        strcpy(pCBO_SELECT[iCBO_INDEX].VALUE_TYPE 	, pORDATA[i2].VALUE_TYPE);
        strcpy(pCBO_SELECT[iCBO_INDEX].VALUE_DECI 	, pORDATA[i2].VALUE_DECI);
        Form1->GetKIKAKU(i2,&dMAX,&dMIN);
        pCBO_SELECT[iCBO_INDEX].MAX 				= dMAX ;
        pCBO_SELECT[iCBO_INDEX].MIN 				= dMIN ;
        //���ڑI���R���{�ւ̏�������
        Cbo_KOMK_NM->Items->Insert(iCBO_INDEX,AnsiString(pCBO_SELECT[i2].KOMK_NM)+AnsiString(pCBO_SELECT[i2].KOMK_SUB)+" "+AnsiString(pCBO_SELECT[i2].TANI));
        iCBO_INDEX ++;
    }

    // 2003/10/7 A.Tamura
	//  ����֐��@�F���݂�KSD02����͂��łɊO���ꂽ���荀�ڂ𕜊�������ׁA
	//              ���݂�KSD02�ɂ͓o�^����Ă��Ȃ����荀�ڂ�KSD11����擾���A
	//              �R���{�{�b�N�X�ɓo�^���܂��B
	//
	//  �@�\����  �F�R���{�{�b�N�X��pCBO_SELECT�ɍ��ړo�^���邾���ŁA�Ȍ�̏����͒����ė��܂��B
    iCBO_INDEX = GetSOKUTEI_KOMK_MORE(iCBO_INDEX);


	//iRowCount = Form1->SGr_vSOKU_SYUKA->RowCount;
///////////////////////////////////////////////////////////////////////////////////////////////////////
//�o�׌�����ʁi���C����ʁj�̏��͔j�����邽�߁A�������̍ăC�j�V�����C�Y
    // �������̊m��
	iSOKUCol 	= SGr_vRIRE_SYUKA->ColCount ;
	iBUNCol 	= SGr_vSOKU_SYUKA->ColCount ;

    // �������̊J��
    if( hBUN_DATA ){
        GlobalUnlock( hBUN_DATA );
        hBUN_DATA = GlobalFree( hBUN_DATA );
    }

    hBUN_DATA = GlobalAlloc( GHND, sizeof(struct BUN_DATA) * ((iSOKUCol + iBUNCol + 1) * 99 ));
    if( hBUN_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pBUN_DATA = (struct BUN_DATA *)GlobalLock(hBUN_DATA);
    if( hBUN_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
/////////////////////////////////////////////////////////////////////////////////////////////////
//���ڐ���iCBO_INDEX�ɓ����Ă���̂ŁA������肪����Ƀf�[�^�����[�h����
//sLot �Ɂ@�����\�ő��肷�郍�b�g�������A���������邩�𒲂ׂ�
//
//�����\�ߋ����т̃��[�h���z����
	sLot = "";
//�����\�ő��肳�ꂽ���b�g�̓ǂݍ���
    for(iCol = 0; iCol < SGr_vRIRE_SYUKA->ColCount;iCol++)
    {
		if(SGr_vRIRE_SYUKA->Cells[iCol][0].Length() !=0)
		{
			sLot += "'" + SGr_vRIRE_SYUKA->Cells[iCol][0] + "',";
		}
	}
    for(iCol = 0; iCol < SGr_vSOKU_SYUKA->ColCount;iCol++)
    {
		if(SGr_vSOKU_SYUKA->Cells[iCol][0].Length() !=0)
		{
			sLot += "'" + SGr_vSOKU_SYUKA->Cells[iCol][0] + "',";
		}
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi��
    // ���b�g��������������
    sLot_Where = "";
    for(iCol = 0; iCol < SGr_vRIRE_SYUKA->ColCount;iCol++)
    {
		if(SGr_vRIRE_SYUKA->Cells[iCol][0].Length() !=0)
		{
            sLot_Where += "( LOTNO='" + SGr_vRIRE_SYUKA->Cells[iCol][0] + "' AND ";
            sLot_Where += " HINBAN='" + SGr_vRIRE_SYUKA->Cells[iCol][1] + "') OR ";
		}
	}
    for(iCol = 0; iCol < SGr_vSOKU_SYUKA->ColCount;iCol++)
    {
		if(SGr_vSOKU_SYUKA->Cells[iCol][0].Length() !=0)
		{
            sLot_Where += "( LOTNO='" + SGr_vSOKU_SYUKA->Cells[iCol][0] + "' AND ";
            sLot_Where += " HINBAN='" + SGr_vSOKU_SYUKA->Cells[iCol][1] + "') OR ";
		}
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi��

	for(i2 = 0;i2 < iCBO_INDEX;i2++)
	{
		sBuf  = "SELECT  KSD11.*, SM12S.TANNAM As UPDNAME ";
		sBuf += " FROM KSD11 LEFT JOIN SM12S ON KSD11.UPDCHR = SM12S.TANSYA ";
	    sBuf += " WHERE DTKSHIN ='" + Pnl_HINBAN->Caption + "'";

        // 2003/10/20 A.Tamura ����SQL�����s��ɁA����ɒP�ʂł���r���Ȃ��瓯�ꍀ�ڂ�T���܂�
		// 2003/10/7 A.Tamura ����ł�UNQ_NO��������KOMK_NO���ς����������OUT�Ȃ̂ō��ږ��́{SUB�ŒT���܂�
		sBuf += " AND KOMK_NM = '" + AnsiString(pCBO_SELECT[i2].KOMK_NM) + "'";

		if( sLot.Length() > 3 ) {
    		//sBuf += " AND LOTNO IN ("+ sLot + ")";
            sBuf += " AND (";
            sBuf += sLot_Where;
            sBuf += " )";
		}
		sBuf += " ORDER BY LOTNO,KSD11.UPDYMD,KSD11.UPDTIM";

		// Initial Query
	    Query1->Close();
    	Query1->SQL->Clear();
    	Query1->SQL->Add(sBuf);
    	Query1->Open();
    	Query1->Active = true;

    	while( Query1->Eof == false )
    	{

            // 2003/10/8 A.Tamura �����Ӗ�������̂ł��傤���H �R�����g�ɂ��܂���
			//sSelectLot = Query1->FieldValues["LOTNO"];
			//while((sSelectLot == AnsiString(Query1->FieldValues["LOTNO"]))
			//	&& (Query1->Eof == false))
			//{
            KOMK_SUB = "";
			if( VarIsNull(Query1->FieldValues["KOMK_SUB"])!=true)
			{
        		sBuf = Query1->FieldValues["KOMK_SUB"];
    	    	KOMK_SUB = sBuf.Trim();
    	    }

            // 2003/10/20 A.Tamura ����ɒP�ʂł���r���Ȃ��瓯�ꍀ�ڂ�T���܂�
            TANI = "";
			if( VarIsNull(Query1->FieldValues["TANI"])!=true)
			{
        		sBuf = Query1->FieldValues["TANI"];
    	    	TANI = sBuf.Trim();
    	    }

            sBuf  = AnsiString(pCBO_SELECT[i2].KOMK_SUB);
            sBuf2 = AnsiString(pCBO_SELECT[i2].TANI);
            if( KOMK_SUB == sBuf.Trim() && TANI == sBuf2.Trim() ){
				iCol = 0;
    		    sBuf = Query1->FieldValues["LOTNO"];
				bSearch = false;
                if(Form1->iRIRE_CNT != 0)
                {
	        	    for( i1 = 0; i1 < SGr_vRIRE_SYUKA->ColCount;i1++)
	    	        {
                        if(SGr_vRIRE_SYUKA->Cells[iCol][0].Trim().Length()!=0)
                        {
    	    		        if(SGr_vRIRE_SYUKA->Cells[iCol][0] == sBuf)
					        {
						        bSearch = true;
					 	        break;
					        }
                        }
    	        	    iCol ++;
	    	        }
                }
    	    	if( bSearch == false )
				{
					iCol = 0;
					for( i1 = 0; i1 < SGr_vSOKU_SYUKA->ColCount;i1++)
					{
                        if(SGr_vSOKU_SYUKA->Cells[iCol][0].Trim().Length()!=0)
                        {
    		    		    if(SGr_vSOKU_SYUKA->Cells[iCol][0] == sBuf)
						    {
							    break;
						    }
                        }
						iCol ++;
					}
				}
				//�ڈ�̋z�o��
                /*
				if( VarIsNull(Query1->FieldValues["KOMK_NO"])!=true)
				{
        			sBuf = Query1->FieldValues["KOMK_NO"];
        			KOMK_NO = sBuf.ToIntDef(0);
				}
				if( VarIsNull(Query1->FieldValues["UNQ_NO"])!=true)
				{
	        		sBuf = Query1->FieldValues["UNQ_NO"];
	    	    	UNQ_NO = sBuf.ToIntDef(0);
	    	    }
                */
				if( VarIsNull(Query1->FieldValues["KOMK_NM"])!=true)
				{
		    	    sBuf = Query1->FieldValues["KOMK_NM"];
    		    	KOMK_NM = sBuf;
				}
				if( VarIsNull(Query1->FieldValues["KOMK_SUB"])!=true)
				{
	        		sBuf = Query1->FieldValues["KOMK_SUB"];
	    	    	KOMK_SUB = sBuf;
	    	    }
				bMIDASI = false;
				if( bSearch == true )
				{
    		        sBuf = Query1->FieldValues["LOTNO"];
                    for( iCol = 0;iCol < SGr_vRIRE_SYUKA->ColCount;iCol++)
                    {
                        if( SGr_vRIRE_SYUKA->Cells[iCol][0] == sBuf ) break;
                    }
            		for( iRow = 0;iRow < SGr_vRIRE_SYUKA->RowCount;iRow++)
					{
						//�^�C�g���i�������ځj������A�O���b�h���󂾂����ꍇ
                        //2003/12/11 E.Takse Trim�����ɂ���
						//if((SGr_Title->Cells[0][iRow] == KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim())
						//&& (SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						//{
            			//2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
            			//                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
						//if((SGr_Title->Cells[0][iRow] == KOMK_NM + KOMK_SUB + " " + TANI)
						//&& (SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						//{
                        sBuf = KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim();
						if((SGr_Title->Cells[0][iRow].Trim() == sBuf.Trim())
						&& (SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						{
							if( VarIsNull(Query1->FieldValues["SKTYMD"])!=true)
							{
	        					sBuf = Query1->FieldValues["SKTYMD"];
	    	    				SGr_vRIRE_SYUKA->Cells[iCol][iRow] = sBuf.SubString(5,2) +"/"+sBuf.SubString(7,2);
	    	    			}
							//2003.05.12 E.Takase Add��
							if( VarIsNull(Query1->FieldValues["UPDNAME"])!=true)
							{
	        					sBuf = Query1->FieldValues["UPDNAME"];
                        		sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow] + " " + GetTANTO2(sBuf);
                        		SGr_vRIRE_SYUKA->Cells[iCol][iRow] = sBuf;
    	    				}
							//2003.05.12 E.Takase Add��
							//2003.05.12 E.Takase Add �R�����g��
							//if( VarIsNull(Query1->FieldValues["UPDCHR"])!=true)
							//{
	        				//	sBuf = Query1->FieldValues["UPDCHR"];
                        	//	sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow] + " " + GetTANTO(sBuf);
                        	//	SGr_vRIRE_SYUKA->Cells[iCol][iRow] = sBuf;
    	    				//}
							//2003.05.12 E.Takase Add �R�����g��

							bMIDASI = true;
							break;
						}
						//�^�C�g���������ăO���b�h�����o�^�������ꍇ
                        //2003/12/11 E.Takse Trim�����ɂ���
						//else if((SGr_Title->Cells[0][iRow].Trim().Length() == 0)
						//&& (SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						//{
            			//2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
            			//                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
						//else if((SGr_Title->Cells[0][iRow].Length() == 0)
						//&& (SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						//{
						else if((SGr_Title->Cells[0][iRow].Trim().Length() == 0)
						&& (SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						{
                            //2003/12/11 E.Takse Trim�����ɂ���
							//SGr_Title->Cells[0][iRow]=KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim();
            				//2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
            				//                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
							//SGr_Title->Cells[0][iRow]=KOMK_NM + KOMK_SUB + " " + TANI;
							SGr_Title->Cells[0][iRow]=KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim();
							SGr_Title->Cells[1][iRow]= AnsiString(i2);
							if( VarIsNull(Query1->FieldValues["SKTYMD"])!=true)
							{
	    	    				sBuf = Query1->FieldValues["SKTYMD"];
	    		    			SGr_vRIRE_SYUKA->Cells[iCol][iRow] = sBuf.SubString(5,2) +"/"+sBuf.SubString(7,2);
    	    				}
							//2003.05.12 E.Takase Add��
							if( VarIsNull(Query1->FieldValues["UPDNAME"])!=true)
							{
	        					sBuf = Query1->FieldValues["UPDNAME"];
                        		sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow] + " " + GetTANTO2(sBuf);
                        		SGr_vRIRE_SYUKA->Cells[iCol][iRow] = sBuf;
    		    			}
							//2003.05.12 E.Takase Add��
							//2003.05.12 E.Takase Add �R�����g��
							//if( VarIsNull(Query1->FieldValues["UPDCHR"])!=true)
							//{
	        				//	sBuf = Query1->FieldValues["UPDCHR"];
                        	//	sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow] + " " + GetTANTO(sBuf);
                        	//	SGr_vRIRE_SYUKA->Cells[iCol][iRow] = sBuf;
    		    			//}
							//2003.05.12 E.Takase Add �R�����g��
                            bMIDASI = true;
                            break;
						}
					}
                	if( bMIDASI == false )
					{
    	            	SGr_Title->RowCount ++;
        	        	SGr_vRIRE_SYUKA->RowCount ++;
            	    	SGr_vSOKU_SYUKA->RowCount ++;
                        //2003/12/11 E.Takse Trim�����ɂ���
						//SGr_Title->Cells[0][iRow]=KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim();
           				//2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
           				//                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
						//SGr_Title->Cells[0][iRow]=KOMK_NM + KOMK_SUB + " " + TANI;
						SGr_Title->Cells[0][iRow]=KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim();
						SGr_Title->Cells[1][iRow]= AnsiString(i2);
					}
    	            iIndex = (iCol*99)+iRow;
                    if( VarIsNull(Query1->FieldValues["SKTYMD"])!=true)
                    {
                    	sBuf = Query1->FieldValues["SKTYMD"];
                        SGr_vRIRE_SYUKA->Cells[iCol][iRow] = sBuf.SubString(5,2) +"/"+sBuf.SubString(7,2);
                    }
					//2003.05.12 E.Takase Add��
                    if( VarIsNull(Query1->FieldValues["UPDNAME"])!=true)
                    {
                    	sBuf = Query1->FieldValues["UPDNAME"];
                        sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow] + " " +  GetTANTO2(sBuf);
                        SGr_vRIRE_SYUKA->Cells[iCol][iRow] = sBuf;
                    }
					//2003.05.12 E.Takase Add��
					//2003.05.12 E.Takase Add �R�����g��
                    //if( VarIsNull(Query1->FieldValues["UPDCHR"])!=true)
                    //{
                    //	sBuf = Query1->FieldValues["UPDCHR"];
                    //    sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iRow] + " " + GetTANTO(sBuf);
                    //    SGr_vRIRE_SYUKA->Cells[iCol][iRow] = sBuf;
                    //}
					//2003.05.12 E.Takase Add �R�����g��
				}
				else
				{
    	        	for( iRow = 0;iRow < SGr_vSOKU_SYUKA->RowCount;iRow++)
					{
    		            sBuf = Query1->FieldValues["LOTNO"];
                        for( iCol = 0;iCol < SGr_vSOKU_SYUKA->ColCount;iCol++)
                        {
                            if( SGr_vSOKU_SYUKA->Cells[iCol][0] == sBuf ) break;
                        }
						//�^�C�g���Ɠ���̍��ڂŃO���b�h���󂾂����ꍇ
                        //2003/12/11 E.Takse Trim�����ɂ���
						//if((SGr_Title->Cells[0][iRow].Trim() == KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim())
						//&& (SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						//{
           				//2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
           				//                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
						//if((SGr_Title->Cells[0][iRow] == KOMK_NM + KOMK_SUB + " " + TANI)
						//&& (SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						//{
                        sBuf = KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim();
						if((SGr_Title->Cells[0][iRow].Trim() == sBuf.Trim())
						&& (SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						{
							if( VarIsNull(Query1->FieldValues["SKTYMD"])!=true)
							{
	    	    				sBuf = Query1->FieldValues["SKTYMD"];
	    		    			SGr_vSOKU_SYUKA->Cells[iCol][iRow] = sBuf.SubString(5,2) +"/"+sBuf.SubString(7,2);
    	    				}
							//2003.05.12 E.Takase Add��
							if( VarIsNull(Query1->FieldValues["UPDNAME"])!=true)
							{
	        					sBuf = Query1->FieldValues["UPDNAME"];
		    	    			sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow] + " " +  GetTANTO2(sBuf);
                                SGr_vSOKU_SYUKA->Cells[iCol][iRow] = sBuf;
    		    			}
							//2003.05.12 E.Takase Add��
							//2003.05.12 E.Takase Add �R�����g��
							//if( VarIsNull(Query1->FieldValues["UPDCHR"])!=true)
							//{
	        				//	sBuf = Query1->FieldValues["UPDCHR"];
		    	    		//	sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow] + " " + GetTANTO(sBuf);
                            //    SGr_vSOKU_SYUKA->Cells[iCol][iRow] = sBuf;
    		    			//}
							//2003.05.12 E.Takase Add �R�����g��
                            bMIDASI = true;
                            break;
						}
						//�^�C�g���������ăO���b�h�����o�^�������ꍇ
                        //2003/12/11 E.Takse Trim�����ɂ���
						//else if((SGr_Title->Cells[0][iRow].Trim().Length() == 0)
						//&& (SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						//{
           				//2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
           				//                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
						//else if((SGr_Title->Cells[0][iRow].Length() == 0)
						//&& (SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						//{
						else if((SGr_Title->Cells[0][iRow].Trim().Length() == 0)
						&& (SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0))
						{
                            //2003/12/11 E.Takse Trim�����ɂ���
							//SGr_Title->Cells[0][iRow]=KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim();
	           				//2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
	           				//                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
							//SGr_Title->Cells[0][iRow]=KOMK_NM + KOMK_SUB + " " + TANI;
							SGr_Title->Cells[0][iRow]=KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim();
							SGr_Title->Cells[1][iRow]= AnsiString(i2);
							if( VarIsNull(Query1->FieldValues["SKTYMD"])!=true)
							{
	    	    				sBuf = Query1->FieldValues["SKTYMD"];
	    		    			SGr_vSOKU_SYUKA->Cells[iCol][iRow] = sBuf.SubString(5,2) +"/"+sBuf.SubString(7,2);
    	    				}
							//2003.05.12 E.Takase Add��
							if( VarIsNull(Query1->FieldValues["UPDNAME"])!=true)
							{
	        					sBuf = Query1->FieldValues["UPDNAME"];
		    	    			sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow] + " " +  GetTANTO2(sBuf);
                                SGr_vSOKU_SYUKA->Cells[iCol][iRow] = sBuf;
    		    			}
							//2003.05.12 E.Takase Add��
							//2003.05.12 E.Takase Add �R�����g��
							//if( VarIsNull(Query1->FieldValues["UPDCHR"])!=true)
							//{
	        				//	sBuf = Query1->FieldValues["UPDCHR"];
		    	    		//	sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow] + " " + GetTANTO(sBuf);
                            //    SGr_vSOKU_SYUKA->Cells[iCol][iRow] = sBuf;
    		    			//}
							//2003.05.12 E.Takase Add �R�����g��
                            bMIDASI = true;
                            break;
						}

					}
                	if( bMIDASI == false )
					{
						SGr_Title->RowCount ++;
        	        	SGr_vRIRE_SYUKA->RowCount ++;
            	    	SGr_vSOKU_SYUKA->RowCount ++;
                        //2003/12/11 E.Takse Trim�����ɂ���
						//SGr_Title->Cells[0][iRow]=KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim();
           				//2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
           				//                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
						//SGr_Title->Cells[0][iRow]=KOMK_NM + KOMK_SUB + " " + TANI;
						SGr_Title->Cells[0][iRow]=KOMK_NM.Trim() + KOMK_SUB.Trim() + " " + TANI.Trim();
						SGr_Title->Cells[1][iRow] = AnsiString(i2);
                        if( VarIsNull(Query1->FieldValues["SKTYMD"])!=true)
                        {
	    	    	   		sBuf = Query1->FieldValues["SKTYMD"];
	    		      		SGr_vSOKU_SYUKA->Cells[iCol][iRow] = sBuf.SubString(5,2) +"/"+sBuf.SubString(7,2);
    	    		 	}
						//2003.05.12 E.Takase Add��
						if( VarIsNull(Query1->FieldValues["UPDNAME"])!=true)
				   		{
	        	  			sBuf = Query1->FieldValues["UPDNAME"];
                            sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow] + " " +  GetTANTO2(sBuf);
                            SGr_vSOKU_SYUKA->Cells[iCol][iRow] = sBuf;
    		    		}
						//2003.05.12 E.Takase Add��
						//2003.05.12 E.Takase Add �R�����g��
						//if( VarIsNull(Query1->FieldValues["UPDCHR"])!=true)
				   		//{
	        	  		//	sBuf = Query1->FieldValues["UPDCHR"];
                        //    sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iRow] + " " +GetTANTO(sBuf);
                        //    SGr_vSOKU_SYUKA->Cells[iCol][iRow] = sBuf;
    		    		//}
						//2003.05.12 E.Takase Add �R�����g��
					}
    	            iIndex = (SGr_vRIRE_SYUKA->ColCount * 99)+(iCol*99)+iRow;
				}
				//���̑��f�[�^���[�h
	            if ( VarIsNull(Query1->FieldValues["DTKSHIN"]) != true)
    	        {
        	    	sBuf = Query1->FieldValues["DTKSHIN"];
            	    strcpy(pBUN_DATA[iIndex].DTKSHIN		,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["LOTNO"]) != true )
        	    {
		   			sBuf = Query1->FieldValues["LOTNO"];
          			strcpy(pBUN_DATA[iIndex].LOTNO			,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["HINBAN"]) != true )
        	    {
		   			sBuf = Query1->FieldValues["HINBAN"];
          			strcpy(pBUN_DATA[iIndex].HINBAN			,sBuf.c_str());
	            }
				if ( VarIsNull(Query1->FieldValues["BNKT_UNQ_NO"]) != true )
        	    {
		   			sBuf = Query1->FieldValues["BNKT_UNQ_NO"];
          			strcpy(pBUN_DATA[iIndex].BNKT_UNQ_NO   	,sBuf.c_str());
	            }
		 		if ( VarIsNull(Query1->FieldValues["UNQ_NO"]) != true )
	    	    {
   					sBuf = Query1->FieldValues["UNQ_NO"];
       				strcpy(pBUN_DATA[iIndex].UNQ_NO			,sBuf.c_str());
	            }
			 	if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true )
	    	    {
	  				sBuf = Query1->FieldValues["KOMK_NO"];
       				strcpy(pBUN_DATA[iIndex].KOMK_NO		,sBuf.c_str());
	            }
			   	if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true )
	    	    {
            		sBuf = Query1->FieldValues["KOMK_NM"];
        	   		strcpy(pBUN_DATA[iIndex].KOMK_NM		,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["KOMK_ENG"]) != true )
        	    {
            		sBuf = Query1->FieldValues["KOMK_ENG"];
                	strcpy(pBUN_DATA[iIndex].KOMK_ENG		,sBuf.c_str());
	            }
    	        strcpy(pBUN_DATA[iIndex].KOMK_SUB		,"");
			   	if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true )
            	{
	            	sBuf = Query1->FieldValues["KOMK_SUB"];
    	            strcpy(pBUN_DATA[iIndex].KOMK_SUB		,sBuf.c_str());
        	    }

            	strcpy(pBUN_DATA[iIndex].KOMK_SUB_ENG		,"");
	            if ( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) != true)
    	        {
        	    	sBuf = Query1->FieldValues["KOMK_SUB_ENG"];
            	    strcpy(pBUN_DATA[iIndex].KOMK_SUB_ENG  	,sBuf.c_str());
	            }

        	    strcpy(pBUN_DATA[iIndex].KIKI_NO		,"");
            	if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true)
	            {
    	        	sBuf = Query1->FieldValues["KIKI_NO"];
        	        strcpy(pBUN_DATA[iIndex].KIKI_NO		,sBuf.c_str());
            	}

	            strcpy(pBUN_DATA[iIndex].KIKI_NM		,"");
    	        if ( VarIsNull(Query1->FieldValues["KIKI_NM"]) != true)
        	    {
            		sBuf = Query1->FieldValues["KIKI_NM"];
                	strcpy(pBUN_DATA[iIndex].KIKI_NM		,sBuf.c_str());
	            }

    	        strcpy(pBUN_DATA[iIndex].TANI		,"");
        	    if ( VarIsNull(Query1->FieldValues["TANI"]) != true)
            	{
            		sBuf = Query1->FieldValues["TANI"];
	                strcpy(pBUN_DATA[iIndex].TANI			,sBuf.c_str());
    	        }

        	    strcpy(pBUN_DATA[iIndex].KIKA_TYPE		,"");
            	if ( VarIsNull(Query1->FieldValues["KIKA_TYPE"]) != true)
	            {
    	        	sBuf = Query1->FieldValues["KIKA_TYPE"];
        	        strcpy(pBUN_DATA[iIndex].KIKA_TYPE		,sBuf.c_str());
            	}

	            strcpy(pBUN_DATA[iIndex].KIKA_KIND		,"");
    	        if ( VarIsNull(Query1->FieldValues["KIKA_KIND"]) != true )
        	    {
            		sBuf = Query1->FieldValues["KIKA_KIND"];
                	strcpy(pBUN_DATA[iIndex].KIKA_KIND		,sBuf.c_str());
	            }

    	        strcpy(pBUN_DATA[iIndex].KIKA_DECI		,"");
        	    if ( VarIsNull(Query1->FieldValues["KIKA_DECI"]) != true)
            	{
            		sBuf = Query1->FieldValues["KIKA_DECI"];
	                strcpy(pBUN_DATA[iIndex].KIKA_DECI		,sBuf.c_str());
    	        }

        	    strcpy(pBUN_DATA[iIndex].KIKA_NUM1		,"");
            	if ( VarIsNull(Query1->FieldValues["KIKA_NUM1"]) != true)
	            {
    	        	sBuf = Query1->FieldValues["KIKA_NUM1"];
        	        strcpy(pBUN_DATA[iIndex].KIKA_NUM1		,sBuf.c_str());
            	}

	            strcpy(pBUN_DATA[iIndex].KIKA_NUM2		,"");
    	        if ( VarIsNull(Query1->FieldValues["KIKA_NUM2"]) != true)
        	    {
            		sBuf = Query1->FieldValues["KIKA_NUM2"];
                	strcpy(pBUN_DATA[iIndex].KIKA_NUM2		,sBuf.c_str());
	            }

    	        strcpy(pBUN_DATA[iIndex].KIKA_NUM3		,"");
        	    if ( VarIsNull(Query1->FieldValues["KIKA_NUM3"]) != true)
            	{
            		sBuf = Query1->FieldValues["KIKA_NUM3"];
	                strcpy(pBUN_DATA[iIndex].KIKA_NUM3		,sBuf.c_str());
    	        }

            	strcpy(pBUN_DATA[iIndex].KIKA_STR		,"");
	            if ( VarIsNull(Query1->FieldValues["KIKA_STR"]) != true)
    	        {
        	    	sBuf = Query1->FieldValues["KIKA_STR"];
            	    strcpy(pBUN_DATA[iIndex].KIKA_STR		,sBuf.c_str());
	            }

    	        strcpy(pBUN_DATA[iIndex].KIKA_SUB1		,"");
        	    if ( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) != true)
            	{
            		sBuf = Query1->FieldValues["KIKA_SUB1"];
	                strcpy(pBUN_DATA[iIndex].KIKA_SUB1		,sBuf.c_str());
    	        }

        	    strcpy(pBUN_DATA[iIndex].KIKA_SUB2		,"");
            	if ( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) != true)
	            {
    	        	sBuf = Query1->FieldValues["KIKA_SUB2"];
    		       	strcpy(pBUN_DATA[iIndex].KIKA_SUB2		,sBuf.c_str());
            	}

	            strcpy(pBUN_DATA[iIndex].KIKA_SUB3		,"");
    	        if ( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) != true)
        	    {
            		sBuf = Query1->FieldValues["KIKA_SUB3"];
        	   		strcpy(pBUN_DATA[iIndex].KIKA_SUB3		,sBuf.c_str());
	            }

    	        strcpy(pBUN_DATA[iIndex].SOKU_SU		,"");
        	    if ( VarIsNull(Query1->FieldValues["SOKU_SU"]) != true)
            	{
            		sBuf = Query1->FieldValues["SOKU_SU"];
	                strcpy(pBUN_DATA[iIndex].SOKU_SU		,sBuf.c_str());
    	        }

            	strcpy(pBUN_DATA[iIndex].SOKU_FLG		,"");
	            if ( VarIsNull(Query1->FieldValues["SOKU_FLG"]) != true)
    	        {
        	    	sBuf = Query1->FieldValues["SOKU_FLG"];
            	    strcpy(pBUN_DATA[iIndex].SOKU_FLG		,sBuf.c_str());
	            }

    	        strcpy(pBUN_DATA[iIndex].TOKU_FLG		,"");
        	    if ( VarIsNull(Query1->FieldValues["TOKU_FLG"]) != true)
            	{
            		sBuf = Query1->FieldValues["TOKU_FLG"];
	                strcpy(pBUN_DATA[iIndex].TOKU_FLG		,sBuf.c_str());
    	        }

    	        strcpy(pBUN_DATA[iIndex].KIKA_PRT		,"");
        	    if ( VarIsNull(Query1->FieldValues["KIKA_PRT"]) != true)
            	{
            		sBuf = Query1->FieldValues["KIKA_PRT"];
	                strcpy(pBUN_DATA[iIndex].KIKA_PRT		,sBuf.c_str());
    	        }

        	    strcpy(pBUN_DATA[iIndex].VALUE_TYPE		,"");
            	if ( VarIsNull(Query1->FieldValues["VALUE_TYPE"]) != true)
	            {
    	        	sBuf = Query1->FieldValues["VALUE_TYPE"];
        	        strcpy(pBUN_DATA[iIndex].VALUE_TYPE		,sBuf.c_str());
            	}

	            strcpy(pBUN_DATA[iIndex].VALUE_DECI		,"");
    	        if ( VarIsNull(Query1->FieldValues["VALUE_DECI"]) != true)
        	    {
            		sBuf = Query1->FieldValues["VALUE_DECI"];
                	strcpy(pBUN_DATA[iIndex].VALUE_DECI		,sBuf.c_str());
	            }
    	        for( i3 = 0 ; i3 < 100 ; i3++)
                {
                    strcpy(pBUN_DATA[iIndex].SOKU_VAL[i3],"");
                }
    	        for( i3 = 0 ; i3 < AnsiString(pBUN_DATA[iIndex].SOKU_SU).ToIntDef(0) ; i3++)
        	    {
            		switch( i3 )
                	{
	                case 0:
    	            	sBuf = "";
					   	if ( VarIsNull(Query1->FieldValues["SOKU_VAL01"]) != true)
					  	{
					 		sBuf = Query1->FieldValues["SOKU_VAL01"];
						}
	                    break;
				  	case 1:
        	        	sBuf = "";
            	        if ( VarIsNull(Query1->FieldValues["SOKU_VAL02"]) != true)
                	    {
                    		sBuf = Query1->FieldValues["SOKU_VAL02"];
	                    }
    	                break;
        	        case 2:
            	    	sBuf = "";
                	    if ( VarIsNull(Query1->FieldValues["SOKU_VAL03"]) != true)
                    	{
                    		sBuf = Query1->FieldValues["SOKU_VAL03"];
	                    }
    	                break;
        	        case 3:
            	    	sBuf = "";
                	    if ( VarIsNull(Query1->FieldValues["SOKU_VAL04"]) != true)
                    	{
                    		sBuf = Query1->FieldValues["SOKU_VAL04"];
	                    }
    	                break;
        	        case 4:
            	    	sBuf = "";
                	    if ( VarIsNull(Query1->FieldValues["SOKU_VAL05"]) != true)
                    	{
	                    	sBuf = Query1->FieldValues["SOKU_VAL05"];
    	                }
        	            break;
            	    case 5:
                		sBuf = "";
                    	if ( VarIsNull(Query1->FieldValues["SOKU_VAL06"]) != true)
	                    {
    	                	sBuf = Query1->FieldValues["SOKU_VAL06"];
        	            }
            	        break;
                	case 6:
	                	sBuf = "";
    	                if ( VarIsNull(Query1->FieldValues["SOKU_VAL07"]) != true)
        	            {
            	        	sBuf = Query1->FieldValues["SOKU_VAL07"];
                	    }
                    	break;
	                case 7:
    	            	sBuf = "";
        	            if ( VarIsNull(Query1->FieldValues["SOKU_VAL08"]) != true)
            	        {
                	    	sBuf = Query1->FieldValues["SOKU_VAL08"];
                    	}
	                    break;
    	            case 8:
        	        	sBuf = "";
            	        if ( VarIsNull(Query1->FieldValues["SOKU_VAL09"]) != true)
                	    {
                    		sBuf = Query1->FieldValues["SOKU_VAL09"];
	                    }
    	                break;
        	        case 9:
            	    	sBuf = "";
                	    if ( VarIsNull(Query1->FieldValues["SOKU_VAL10"]) != true)
                    	{
	                    	sBuf = Query1->FieldValues["SOKU_VAL10"];
    	                }
        	            break;
            	    default:
                        //��O�f�[�^�S�Ă�����SQL�ŋz���o���܂��B
                		sBuf = "SELECT SOKU_NO, SOKU_VAL FROM KSD12";
                    	sBuf+= " WHERE DTKSHIN='" + AnsiString(pBUN_DATA[iIndex].DTKSHIN) + "'";
	                    sBuf+= " AND LOTNO='" + AnsiString(pBUN_DATA[iIndex].LOTNO) + "'";
    	                sBuf+= " AND BNKT_UNQ_NO=" + AnsiString(AnsiString(pBUN_DATA[iIndex].BNKT_UNQ_NO).ToIntDef(0)) ;
        	            //sBuf+= " AND SOKU_NO=" + AnsiString(i3) ;
            	        // Initial Query
                	    Query2->Close();
                    	Query2->SQL->Clear();
	                    Query2->SQL->Add(sBuf);
    	                Query2->Open();
        	            Query2->Active = true;
                        while(Query2->Eof == false)
                        {
                            sBuf = "";
                            sBuf = Query2->FieldValues["SOKU_VAL"];
                            i3 = AnsiString(Query2->FieldValues["SOKU_NO"]).ToIntDef(0);
    	                    strcpy(pBUN_DATA[iIndex].SOKU_VAL[i3-1],sBuf.c_str());
                            Query2->Next();
                        }
                	    Query2->Close();
                        i3 = 100;       //�ő匏��99������100��������Ίm���ɏI�����܂��B
                    	break;
	                }
                    if( i3 < 10 )
                    {
    	                strcpy(pBUN_DATA[iIndex].SOKU_VAL[i3],sBuf.c_str());
                    }
        	    }
	            if ( VarIsNull(Query1->FieldValues["SOKU_VAL_SU"]) != true)
    	        {
        	    	sBuf = Query1->FieldValues["SOKU_VAL_SU"];
            	    strcpy(pBUN_DATA[iIndex].SOKU_VAL_SU		,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["SOKU_VAL_AVE"]) != true)
        	    {
            		sBuf = Query1->FieldValues["SOKU_VAL_AVE"];
                	strcpy(pBUN_DATA[iIndex].SOKU_VAL_AVE		,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["SOKU_VAL_MAX"]) != true)
        	    {
            		sBuf = Query1->FieldValues["SOKU_VAL_MAX"];
                	strcpy(pBUN_DATA[iIndex].SOKU_VAL_MAX		,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["SOKU_VAL_MIN"]) != true)
        	    {
            		sBuf = Query1->FieldValues["SOKU_VAL_MIN"];
                	strcpy(pBUN_DATA[iIndex].SOKU_VAL_MIN		,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["SOKU_OK"]) != true)
        	    {
            		sBuf = Query1->FieldValues["SOKU_OK"];
                	strcpy(pBUN_DATA[iIndex].SOKU_OK			,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["SKTYMD"]) != true)
        	    {
            		sBuf = Query1->FieldValues["SKTYMD"];
                	strcpy(pBUN_DATA[iIndex].SKTYMD				,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["ADDYMD"]) != true)
        	    {
            		sBuf = Query1->FieldValues["ADDYMD"];
                	strcpy(pBUN_DATA[iIndex].ADDYMD				,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["ADDTIM"]) != true)
        	    {
            		sBuf = Query1->FieldValues["ADDTIM"];
                	strcpy(pBUN_DATA[iIndex].ADDTIM				,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["UPDYMD"]) != true)
        	    {
            		sBuf = Query1->FieldValues["UPDYMD"];
                	strcpy(pBUN_DATA[iIndex].UPDYMD				,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["UPDTIM"]) != true)
        	    {
            		sBuf = Query1->FieldValues["UPDTIM"];
                	strcpy(pBUN_DATA[iIndex].UPDTIM				,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["UPDCHR"]) != true)
        	    {
            		sBuf = Query1->FieldValues["UPDCHR"];
                	strcpy(pBUN_DATA[iIndex].UPDCHR				,sBuf.c_str());
	            }
    	        if ( VarIsNull(Query1->FieldValues["UPDCNT"]) != true)
        	    {
            		sBuf = Query1->FieldValues["UPDCNT"];
                	strcpy(pBUN_DATA[iIndex].UPDCNT				,sBuf.c_str());
	            }
    	        GetKIKAKU(iIndex, &dMAX, &dMIN);
				//2003.05.12 E.Takase Add��
    	        if ( VarIsNull(Query1->FieldValues["UPDNAME"]) != true)
        	    {
            		sBuf = Query1->FieldValues["UPDNAME"];
					//2003.05.17 E.Takase Add��
                	strcpy(pBUN_DATA[iIndex].UPD_NAME , AnsiString(GetTANTO2(sBuf)).c_str());
					//2003.05.17 E.Takase Add��
					//2003.05.17 E.Takase Add �R�����g��
                	//pBUN_DATA[iIndex].UPD_NAME =  GetTANTO2(sBuf);
					//2003.05.17 E.Takase Add �R�����g��
	            }
				//2003.05.12 E.Takase Add��
				//2003.05.12 E.Takase Add �R�����g��
        	    //pBUN_DATA[iIndex].UPD_NAME = GetTANTO(AnsiString(pBUN_DATA[iIndex].UPDCHR));
				//2003.05.12 E.Takase Add �R�����g��
            	pBUN_DATA[iIndex].MAX = dMAX;
	            pBUN_DATA[iIndex].MIN = dMIN;
			}
			Query1->Next();

		}
        Query1->Close();
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnChange �C�x���g �F�ҏW�̈�ɕ\�����ꂽ�e�L�X�g���ύX�����Ɣ������܂��B
//
//  �@�\����
//    ���ږ��̕ύX�ƘA�����P�ʁA�@�햼�́A�\���t�H�[�}�b�g���̕ύX���s���܂��B
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
void __fastcall TForm7::Cbo_KOMK_NMChange(TObject *Sender)
{
	AnsiString sMIN,sMAX,sDECI;
	AnsiString sDATE,sUPDNAME;
	AnsiString sDeci1;
	AnsiString sBuf;
	int i1;
	int iCbo_KOMK_NM_Pos;


	iCbo_KOMK_NM_Pos = Cbo_KOMK_NM->ItemIndex;

// ���荀�ڂɂ�葪��@��A�P�ʁA�K�i�̕ύX���s����
	Pnl_HINBAN->Caption = pCBO_SELECT[iCbo_KOMK_NM_Pos].DTKSHIN;
	Pnl_TANI->Caption = pCBO_SELECT[iCbo_KOMK_NM_Pos].TANI;
	Pnl_KIKI->Caption = pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKI_NM;
// �`�����l���؂�ւ�
	if((AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKI_NO).ToIntDef(0) == 1)
	||(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKI_NO).ToIntDef(0) == 2))
	{
		iPORT_NO = AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKI_NO).ToIntDef(0)-1;
	}

// �K�i�\���F�X
// �t�H�[�}�b�g�w��i��*.*���j
	sDeci1 = "0";
	for( i1 = 0; i1 < AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_DECI).ToIntDef(0); i1++ )
	{
		if( i1 == 0 ) sDeci1 += ".";
		sDeci1 += "0";
	}

	switch(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_TYPE).ToIntDef(0))
	{
	// �K�i�^�C�v�F�͈͎w��
	case 1:
		switch(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_KIND).ToIntDef(0))
		{
		// �K�i��ށF�����������
		case 1:
			sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_NUM1),0.0));
			sBuf +=	 "�`";
			sBuf += FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_NUM2),0.0));
			break;
		// �K�i��ށF����̂�
		case 2:
			sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_NUM2),0.0));
			sBuf += "�ȉ�";
			break;
		// �K�i��ށF�����̂�
		case 3:
			sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_NUM1),0.0));
			sBuf += "�ȏ�";
			break;
		default:
			sBuf = "";
			break;
		}
		Pnl_KIKAKU->Caption = sBuf;
		Lab_KIKAKU->Caption = sBuf;
		Lab_KIKAKU->Left = 0;
		Lab_KIKAKU->Parent=Pnl_KIKAKU;
		Lab_KIKAKU_UP->Caption = "";
		Lab_KIKAKU_UP->Left = Lab_KIKAKU->Left + Lab_KIKAKU->Width+20;
		Lab_KIKAKU_LOW->Caption = "";
		Lab_KIKAKU_LOW->Left = Lab_KIKAKU->Left + Lab_KIKAKU->Width+20;
		break;

	// �K�i�^�C�v�F��l�w��
	case 2:
		sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_NUM1),0.0));
		Pnl_KIKAKU->Caption = sBuf;
		Lab_KIKAKU->Caption = sBuf;
		Lab_KIKAKU->Left = 0;
		Lab_KIKAKU->Parent=Pnl_KIKAKU;
		
		switch(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_KIND).ToIntDef(0))
		{
		// �K�i��ށF�����������
		case 1:
			Lab_KIKAKU_UP->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_NUM2),0.0));
			Lab_KIKAKU_LOW->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_NUM3),0.0));
			if(Form1->ConvDoubleDefD(Lab_KIKAKU_UP->Caption,0.0) >=0) {
				Lab_KIKAKU_UP->Caption = "+"+Lab_KIKAKU_UP->Caption;
			}
			if(Form1->ConvDoubleDefD(Lab_KIKAKU_LOW->Caption,0.0) >=0) {
				Lab_KIKAKU_LOW->Caption = "+"+Lab_KIKAKU_LOW->Caption;
			}
			break;
		// �K�i��ށF����̂�
		case 2:
			Lab_KIKAKU_UP->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_NUM2),0.0));
			Lab_KIKAKU_LOW->Caption ="";
			if(Form1->ConvDoubleDefD(Lab_KIKAKU_UP->Caption,0.0) >=0) {
				Lab_KIKAKU_UP->Caption = "+"+Lab_KIKAKU_UP->Caption;
			}
			break;
		// �K�i��ށF�����̂�
		case 3:
			Lab_KIKAKU_UP->Caption = "";
			Lab_KIKAKU_LOW->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_NUM3),0.0));
			if(Form1->ConvDoubleDefD(Lab_KIKAKU_LOW->Caption,0.0) >=0) {
				Lab_KIKAKU_LOW->Caption = "+"+Lab_KIKAKU_LOW->Caption;
			}
			break;
		 default:
			break;
		}

		Lab_KIKAKU_UP->Left = Lab_KIKAKU->Left + Lab_KIKAKU->Width+20;
		Lab_KIKAKU_LOW->Left = Lab_KIKAKU->Left + Lab_KIKAKU->Width+20;

		break;

	// �K�i�^�C�v�F����
	case 3:
		//Pnl_KIKAKU->Caption = AnsiString(pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_STR);
		Lab_KIKAKU->Caption = pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_STR;
		Pnl_KIKAKU->Caption = pCBO_SELECT[iCbo_KOMK_NM_Pos].KIKA_STR;
		Lab_KIKAKU->Left = 0;
		Lab_KIKAKU->Parent=Pnl_KIKAKU;
		Lab_KIKAKU_UP->Caption = "" ;
		Lab_KIKAKU_UP->Left = Lab_KIKAKU->Left + Lab_KIKAKU->Width+20;
		Lab_KIKAKU_LOW->Caption = "";
		Lab_KIKAKU_LOW->Left = Lab_KIKAKU->Left + Lab_KIKAKU->Width+20;
		break;
	default:
		break;
	}
	
	//���ڑI�����s����ƁA�S���҂Ɠ��t�����݂̂��̂ɍX�V
	sSYSTEM_DATE = FormatDateTime("yyyymmdd",Date());
	sUPDNAME = GetTANTO2(AnsiString(Form1->USER_NAM));
	MEdt_SOKU_DATE->Text = sSYSTEM_DATE.SubString(1,4) +
							 "/" + sSYSTEM_DATE.SubString(5,2) +
							 "/" + sSYSTEM_DATE.SubString(7,2);
	PnlTanName->Caption = sUPDNAME;
	
}

///---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��@ �R���{�{�b�N�X�̕\���ʒu��擪�ɂ��܂��B
//
//  �@�\����
//    �R���{�{�b�N�X�̕\���ʒu��擪�ɂ��܂��B�B
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
void __fastcall TForm7::Set_LOT_GRID(void)
{
	//int iCol,iRow;
	//int i1;
	//int SOKU_SU;
	//int iSOKUCol;
	//bool bSearch;

//	SGr_vRIRE_SYUKA->RowCount = 2;

//	SGr_vSOKU_SYUKA->RowCount = 2;

	SGr_vRIRE_SYUKA->ColCount 	= Form1->SGr_vRIRE_SYUKA->ColCount;
	SGr_vSOKU_SYUKA->ColCount 	= Form1->SGr_vSOKU_SYUKA->ColCount;
//	SGr_Title->RowCount = 2;

	SGr_vSOKUTEI->RowCount = 1;

/*
	//�����ʎ��уO���b�h
	for(iCol = 0; iCol < SGr_vRIRE_SYUKA->ColCount ; iCol ++ )
    {

    	for(iRow = 1; iRow < 99 ;iRow++)
		{
		//���b�g�ɑΏۂ������ꍇ
            if(AnsiString(pBUN_DATA[(iCol)*99+iRow].KOMK_NM).Length()
              +AnsiString(pBUN_DATA[(iCol)*99+iRow].KOMK_SUB).Length() != 0 )
			{
				if(iRow> SGr_Title->RowCount )
				{
					SGr_Title->RowCount = iRow;
					SGr_vRIRE_SYUKA->RowCount = iRow;
				}
	            SGr_Title->Cells[0][iRow] = AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_NM)+AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_SUB);
    	        Cbo_KOMK_NM->Items->Insert(iRow-1,AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_NM)+AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_SUB));
        	    SGr_vRIRE_SYUKA->Cells[iCol][iRow] =
            		AnsiString(pBUN_DATA[iCol*99+iRow].UPDYMD).SubString(5,2)
                	+ "/" + AnsiString(pBUN_DATA[iCol*99+iRow].UPDYMD).SubString(7,2)
                	+ " " + pBUN_DATA[iCol*99+iRow].UPD_NAME;
            	bSearch = true;
        	}
		}
    }

	//�q�n�v�̒���
    SGr_vSOKU_SYUKA->RowCount = SGr_vRIRE_SYUKA->RowCount;
	iSOKUCol = SGr_vRIRE_SYUKA->ColCount ;

	for(iCol = 0; iCol < SGr_vSOKU_SYUKA->ColCount ; iCol ++ )
    {
    	for(iRow = 1;iRow < 99 ;iRow++)
		{
		//���b�g�ɑΏۂ������ꍇ
            if(AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_NM).Length()
              +AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_SUB).Length() != 0 )
			{
				if(iRow> SGr_Title->RowCount )
				{
					SGr_Title->RowCount = iRow;
					SGr_vSOKU_SYUKA->RowCount = iRow;
					SGr_vRIRE_SYUKA->RowCount = iRow;
				}
    	        SGr_Title->Cells[0][iRow] = AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_NM)+AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_SUB);
        	    Cbo_KOMK_NM->Items->Insert(iRow-1,AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_NM)+AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_SUB));
            	SGr_vSOKU_SYUKA->Cells[iCol][iRow] =
            		AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDYMD).SubString(5,2)
	                + "/" + AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDYMD).SubString(7,2)
    	            + " " + pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME;
        	    bSearch = true;
			}
        }
    }
*/

//���荀�ڃR���{�̏����l�i��ԏ�j�̃Z�b�g
		Cbo_KOMK_NM->ItemIndex = 0 ;
		Cbo_LOT->ItemIndex = 0;
}

///---------------------------------------------------------------------------
//
//  �T�v
//    OnSelectCell �C�x���g �F�O���b�h���̃Z�����I�������O�ɔ������܂��B
//
//  �@�\����
//    �I�����ꂽStringGrid��̃Z���ɂ��A����������ꍇ�͕\�����܂��B
//  �@������΃Z���̍��E�̏�񂩂瑪��w���������擾�����肵�܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol          �F�ΏۃZ����Col
//  �@int ARow          �F�ΏۃZ����Row
//  �@ bool &CanSelect  �Ftrue�F�Z���̑I�����Afalse�F�Z���̑I��s��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm7::FormSelectCell(TObject *Sender,
      int ACol, int ARow, bool &CanSelect)
{
	int i1,iCol,iCBO_CNT;
	int iSOKUCol;
	AnsiString sBuf,sCompBuf;
	AnsiString sLot,KOMK_NM,KOMK_SUB;

    sSYSTEM_DATE = FormatDateTime("yyyymmdd",Date());   //���t�����݂̂��̂ɍX�V
//�Z���N���A
	for(i1 = 0 ; i1 < SGr_vSOKUTEI->RowCount ; i1 ++)
    {
    	SGr_vSOKUTEI->Cells[1][i1] = "";
    }
	SGr_vSOKUTEI->RowCount = 1;
    Num_SOKU_SU->Text = 1;

	if(Sender == SGr_vRIRE_SYUKA )
	{
		iENA_GRID = 0;											//���ݑI�𒆂̃O���b�h��ۑ�
	//�R���{�{�b�N�X�Ƀ��b�g��\��
		sBuf = SGr_vRIRE_SYUKA->Cells[ACol][0].Trim();		//���b�g���̎��o��
		if(sBuf.Trim().Length() != 0 )
		{
			iCol = 0;
			while(1)
			{
				if(sBuf.Length() != 0 )
				{
    	    		if(Cbo_LOT->Items->Strings[iCol] == sBuf)
					{
						Cbo_LOT->ItemIndex = iCol;
						break;
					}
				}
				iCol++;
			}
		}
		if(SGr_vRIRE_SYUKA->Cells[ACol][ARow].Length() == 0)
		{
			iCBO_CNT = AnsiString(SGr_Title->Cells[1][ARow]).ToIntDef(-1);
			if(iCBO_CNT < 0 ) return;	//���荀�ږ���
            Cbo_KOMK_NM->ItemIndex = iCBO_CNT;
			Cbo_KOMK_NMChange(Sender);
            Num_SOKU_SU->Text = GET_NSU();
	        PnlTanName->Caption = Form1->USER_NAM;
			return;
		}
        Num_SOKU_SU->Text = AnsiString(pBUN_DATA[ACol*99+ARow].SOKU_SU).ToIntDef(1);
        for(i1 = 0 ; i1 < AnsiString(pBUN_DATA[ACol*99+ARow].SOKU_SU).ToIntDef(0) ; i1 ++)
        {
        	SGr_vSOKUTEI->Cells[1][i1] = AnsiString(pBUN_DATA[ACol*99+ARow].SOKU_VAL[i1]);
        }
        sBuf = SGr_Title->Cells[0][ARow];
		i1 = 0;
		while( 1 )
		{
        	//2004/04/27 A.Tamura  ��O�G���[�����������ׁA��65�s����//2003/12/11 E.Takase �̏����Ƃ��킹��
            if ( i1 >= 99 ) {
                Cbo_KOMK_NM->ItemIndex = -1;
            	break;
            }
			sCompBuf = AnsiString(pCBO_SELECT[i1].KOMK_NM)+AnsiString(pCBO_SELECT[i1].KOMK_SUB)+" "+AnsiString(pCBO_SELECT[i1].TANI);
			if(sCompBuf.Trim() == sBuf.Trim())
            {
				Cbo_KOMK_NM->ItemIndex = i1;
                break;
			}
			i1++;
		}
        //2004/04/27 A.Tamura  ��O�G���[�����������ׁA��65�s����//2003/12/11 E.Takase �̏����Ƃ��킹��
        //Cbo_KOMK_NM->ItemIndex = i1;
        Cbo_KOMK_NMChange(Sender);
		Cbo_LOT->ItemIndex 	= ACol;
		MEdt_SOKU_DATE->Text =          AnsiString(pBUN_DATA[ACol*99+ARow].SKTYMD).SubString(1,4)
        						+ "/" + AnsiString(pBUN_DATA[ACol*99+ARow].SKTYMD).SubString(5,2)
        						+ "/" + AnsiString(pBUN_DATA[ACol*99+ARow].SKTYMD).SubString(7,2);
        sSYSTEM_DATE = AnsiString(pBUN_DATA[ACol*99+ARow].SKTYMD);  //����������ꍇ�͗�����t�ɏC��
		PnlTanName->Caption = AnsiString(pBUN_DATA[ACol*99+ARow].UPD_NAME);
	}
	else if(Sender == SGr_vSOKU_SYUKA)
	{
    	iENA_GRID = 1;											    //���ݑI�𒆂̃O���b�h��ۑ�
		iSOKUCol = SGr_vRIRE_SYUKA->ColCount;
	//�R���{�{�b�N�X�Ƀ��b�g��\��
		sBuf = SGr_vSOKU_SYUKA->Cells[ACol][0].Trim();		        //���b�g���̎��o��
		if(sBuf.Trim().Length() != 0 )
		{
			iCol = 0;
			while(1)
			{
				if(sBuf.Length() != 0 )
				{
    	    		if(Cbo_LOT->Items->Strings[iCol] == sBuf)
					{
						Cbo_LOT->ItemIndex = iCol;
						break;
					}
				}
				iCol++;
			}
		}
    //�Z�����󔒂̏ꍇ
		if(SGr_vSOKU_SYUKA->Cells[ACol][ARow].Trim().Length() == 0)
		{
			iCBO_CNT = AnsiString(SGr_Title->Cells[1][ARow]).ToIntDef(-1);
			if(iCBO_CNT < 0 ) return;	//���荀�ږ���
            Cbo_KOMK_NM->ItemIndex = iCBO_CNT;
			Cbo_KOMK_NMChange(Sender);
            Num_SOKU_SU->Text = GET_NSU();
	        PnlTanName->Caption = Form1->USER_NAM;
			return;
		}
        Num_SOKU_SU->Text = AnsiString(pBUN_DATA[(iSOKUCol+ACol)*99+ARow].SOKU_SU).ToIntDef(1);
        for(i1 = 0 ; i1 < AnsiString(pBUN_DATA[(iSOKUCol+ACol)*99+ARow].SOKU_SU).ToIntDef(0) ; i1 ++)
        {
        	SGr_vSOKUTEI->Cells[1][i1] = AnsiString(pBUN_DATA[(iSOKUCol+ACol)*99+ARow].SOKU_VAL[i1]);
        }
        sBuf = SGr_Title->Cells[0][ARow];
		i1 = 0;
		while( 1 )
		{
        	//2003/12/11 E.Takase
            if ( i1 >= 99 ) {
                Cbo_KOMK_NM->ItemIndex = -1;
            	break;
            }
			sCompBuf = Trim(AnsiString(pCBO_SELECT[i1].KOMK_NM))+Trim(AnsiString(pCBO_SELECT[i1].KOMK_SUB))+" "+Trim(AnsiString(pCBO_SELECT[i1].TANI));
            //2003/12/11 E.Takse Trim�����ɂ���
			//if(sCompBuf.Trim() == sBuf.Trim())
            //2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
            //                    �O�ς�"��/��"�̕\�������܂��o���Ȃ��̂ł���ς�Trim����
			//if(sCompBuf == sBuf)
			if(sCompBuf.Trim() == sBuf.Trim())
            {
				Cbo_KOMK_NM->ItemIndex = i1;
                break;
			}
			i1++;
		}
        //2003/12/11 E.Takase
        //Cbo_KOMK_NM->ItemIndex = i1;
        Cbo_KOMK_NMChange(Sender);
		MEdt_SOKU_DATE->Text =          AnsiString(pBUN_DATA[(iSOKUCol+ACol)*99+ARow].SKTYMD).SubString(1,4)
        						+ "/" + AnsiString(pBUN_DATA[(iSOKUCol+ACol)*99+ARow].SKTYMD).SubString(5,2)
        						+ "/" + AnsiString(pBUN_DATA[(iSOKUCol+ACol)*99+ARow].SKTYMD).SubString(7,2);
        sSYSTEM_DATE = AnsiString(pBUN_DATA[(iSOKUCol+ACol)*99+ARow].SKTYMD);
		PnlTanName->Caption = AnsiString(pBUN_DATA[(iSOKUCol+ACol)*99+ARow].UPD_NAME);
	}

}

///---------------------------------------------------------------------------
//
//  �T�v
//    OnDrawCell �C�x���g�F�@�O���b�h���̃Z����`�悷��K�v������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �Z���̒��g�����ڂɍ��킹���t�H�[�}�b�g�ŕ\���B
//  �@�K�i����l�𔻒肵��OK�Ȃ�clBlack�ANG�Ȃ�clRed�ŕ\������B
//
//  �p�����^����
//    TObject *Sender	    �F�Ăяo������VCL�I�u�W�F�N�g
//    int ACol              �F�ΏۃZ����Col
//  �@int ARow              �F�ΏۃZ����Row
//  �@TRect &Rect           �F�Z���̈ʒu���
//  �@TGridDrawState State  �F�Z���̏��
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
//
//  �T�v
//    OnTopLeftChanged �C�x���g�FTopRow �v���p�e�B�܂��� LeftCol �v���p�e�B���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    GRIDON�t���O��True�ɂ��܂��B
//
//  �p�����^����
//    TObject *Sender	    �F�Ăяo������VCL�I�u�W�F�N�g
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
void __fastcall TForm7::SGr_vRIRE_SYUKATopLeftChanged(TObject *Sender)
{
    bGRIDON = true;

    //2003/12/10 E.Takase
    SGr_vSOKU_SYUKA->TopRow  = SGr_vRIRE_SYUKA->TopRow;
    SGr_Title->TopRow  = SGr_vRIRE_SYUKA->TopRow;



}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�T�F�b�g�ؑցv�{�^�������������̏���
//
//  �@�\����
//    COM1�ɐڑ�����Ă���؂�ւ��@�̃`�����l����1�C���N�������g���܂��B
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
void __fastcall TForm7::BtnF05Click(TObject *Sender)
{
	////////////////////
    // Ch�ؑ�
    iPORT_NO ++;
    if( iPORT_NO> 4 ) iPORT_NO = 0;


}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�V�F�t�r�q�ؑցv�{�^�������������̏���
//
//  �@�\����
//    �S���Ґؑ։�ʁiForm9�j��\�����܂�
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
//
//---------------------------------------------------------------------------
void __fastcall TForm7::BtnF07Click(TObject *Sender)
{
	////////////////////
	// �S���Ґؑ�
	Form9->ShowModal();
	PnlTanName->Caption = Form1->USER_NAM;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�P�F�v�{�^�������������̏���
//
//  �@�\����
//    �_�~�[�֐��H
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
//
//---------------------------------------------------------------------------
void __fastcall TForm7::BtnF11Click(TObject *Sender)
{

//2003.05.17 E.Takase �R�����g��
//     // �X�e�[�^�X���b�Z�[�W
//     Form1->SBr1->Panels->Items[0]->Text = "�ۑ����ł��D�D�D���΂炭���҂��������B";
//     Form1->SBr1->Update();
//
//     // �ύX�C�}���C�폜���i���I�ɕۑ����C���݂̃g�����U�N�V�������I��
//     if( Form1->Database1->InTransaction == True ){
//         Form1->Database1->Commit();
//         // �V�����g�����U�N�V�������J�n
//         Form1->Database1->StartTransaction();
//     }
//     Form1->SBr1->Panels->Items[0]->Text = "";
//     Form1->SBr1->Update();
//
//     // �f�[�^��ύX�����t���O
////     DataSave = false;
//     BtnF11->Enabled = false;
//
//2003.05.17 E.Takase �R�����g��

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�X�F�C���v�{�^�������������̏���
//
//  �@�\����
//    �Z���̏����C�����A�f�[�^�x�[�X�ɓo�^���܂��B
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
//
//---------------------------------------------------------------------------
void __fastcall TForm7::BtnF09Click(TObject *Sender)
{

	int iRow,iCol,iSOKUCol;
	//int UNQ_NO,KOMK_NO;
	int iCBO_INDEX;
	AnsiString KOMK_NM,KOMK_SUB,TANI,sBuf,sRESULT_BUF;
	int i1,i2;
	AnsiString sDATE,sTIME;
	AnsiString sUPDCHR,sUPDCNT;
	AnsiString sSOKU_VAL_SU,sSOKU_VAL_AVE,sSOKU_VAL_MAX,sSOKU_VAL_MIN,sSOKU_OK;
	AnsiString dSOKU_VAL_AVE,dSOKU_VAL_MAX,dSOKU_VAL_MIN;
	double dMAX,dMIN,dAVE,dVAL;
	int iSOKU_SU;
	bool bVAL_FIRST;
	AnsiString  BNKT_UNQ_NO;
	AnsiString  sUPDNAME;	//2003.05.12 E.Takase Add
	TMsgDlgButtons MsgButton;

	sDATE = FormatDateTime("yyyymmdd",Date());
	sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
	sUPDCHR = AnsiString(Form1->USER_COD);
	sUPDCNT = AnsiString("0");

	//2003.05.12 E.Takase Add��
    sUPDNAME = GetTANTO2(AnsiString(Form1->USER_NAM));
	//2003.05.12 E.Takase Add��

//�C���ł��邩�𒲂ׂ�
	if(iENA_GRID == 0)
	{
        iRow = SGr_vRIRE_SYUKA->Row ;
        iCol = SGr_vRIRE_SYUKA->Col ;
		if( SGr_vRIRE_SYUKA->Cells[iCol][iRow].Trim().Length() == 0)
		{
            MessageDlg("�ȑO�̃f�[�^�������̂ŁA�C���ł��܂���B", mtWarning , TMsgDlgButtons() << mbOK , 0);
			return;
        }
	}
	else
	{
        iRow = SGr_vSOKU_SYUKA->Row ;
        iCol = SGr_vSOKU_SYUKA->Col ;
		if( SGr_vSOKU_SYUKA->Cells[iCol][iRow].Trim().Length() == 0)
		{
            MessageDlg("�ȑO�̃f�[�^�������̂ŁA�C���ł��܂���B", mtWarning , TMsgDlgButtons() << mbOK , 0);
			return;
        }
	}
    //2003/12/11 E.Takse Trim�����ɂ���
	//if(Cbo_KOMK_NM->Text.Trim() != SGr_Title->Cells[0][iRow].Trim())
	//2004/03/27 A.Tamura �Ȃ�ł����Trim�����ɂ����񂾂낤�A
	//                    �O�ςŒl�̏C�������܂������Ȃ��̂ł���ς�Trim����
	//if(Cbo_KOMK_NM->Text != SGr_Title->Cells[0][iRow])
	if(Cbo_KOMK_NM->Text.Trim() != SGr_Title->Cells[0][iRow].Trim())
	{

            //MessageDlg("�������ڂ��Ⴄ�̂ŁA�C���ł��܂���B", mtWarning , TMsgDlgButtons() << mbOK , 0);
            sBuf  = "���ڂ��Ⴄ�̂ŐV�K�o�^���s���܂��B";
            sBuf += "\n[�́@��] �V�K�o�^���s�����s���܂��B";
            sBuf += "\n[�L�����Z��] �V�K�o�^�̎������B";
            MsgButton << mbYes << mbCancel;
            switch( MessageDlg( sBuf, mtWarning	, MsgButton, 0) ){
            // �uYes�v      �ۑ�
            case mrYes:
                BtnF08Click(Sender);
                break;
            // �uCancel�v   �L�����Z��
            case mrCancel:
                return;
            }
			return;

	}
//���ϒl���̎Z�o
	bVAL_FIRST = true;
	iSOKU_SU = 0;
	dMAX = 0;
	dMIN = 0;
	dAVE = 0;
	dVAL = 0;
    iCBO_INDEX = Cbo_KOMK_NM->ItemIndex;
	if(AnsiString(pCBO_SELECT[iCBO_INDEX].VALUE_TYPE).ToIntDef(0) != 3)
	{
		for(i1 = 0 ; i1< Num_SOKU_SU->Text.ToIntDef(0)  ; i1++)
		{
            sBuf = SGr_vSOKUTEI->Cells[1][i1];
            //2003.05.08 E.Takase Add��
            dVAL = Form1->ConvDoubleDefD(sBuf,0.0);
			if( sBuf == AnsiString(dVAL))
			{
				if( bVAL_FIRST == true )
    	        {
					dMAX = dVAL;
					dMIN = dVAL;
					bVAL_FIRST = false;
				}
    	        iSOKU_SU ++;
				dAVE += dVAL;
				if( dMAX < dVAL ) dMAX = dVAL;
				if( dMIN > dVAL ) dMIN = dVAL;
            //2003.05.08 E.Takase Add��
    		}
        }
		if( iSOKU_SU == 0 ) iSOKU_SU = 1;
        sSOKU_VAL_SU = AnsiString( iSOKU_SU );
		dSOKU_VAL_AVE = ( dAVE / iSOKU_SU );
		dSOKU_VAL_MAX = ( dMAX );
		dSOKU_VAL_MIN = ( dMIN );
	//�����`�F�b�N
        if( dSOKU_VAL_AVE > 9999999.999999 ) dSOKU_VAL_AVE  = 9999999.999999 ;
        if( dSOKU_VAL_MAX > 9999999.99999  ) dSOKU_VAL_MAX  = 9999999.99999 ;
        if( dSOKU_VAL_MIN > 9999999.99999  ) dSOKU_VAL_MIN  = 9999999.99999 ;

		sSOKU_VAL_SU  = sSOKU_VAL_SU.SubString(1,14);
		sSOKU_VAL_AVE = AnsiString(dSOKU_VAL_AVE).SubString(1,14);
		sSOKU_VAL_MAX = AnsiString(dSOKU_VAL_MAX).SubString(1,14);
		sSOKU_VAL_MIN = AnsiString(dSOKU_VAL_MIN).SubString(1,14);
        sSOKU_OK = AnsiString(GET_HANTEI());
	}
	else
    {
		sSOKU_VAL_SU = AnsiString(Num_SOKU_SU->Text);
		sSOKU_VAL_AVE = "0";
		sSOKU_VAL_MAX = "0";
		sSOKU_VAL_MIN = "0";
        sSOKU_OK = AnsiString(GET_HANTEI());
	}

    iCBO_INDEX = Cbo_KOMK_NM->ItemIndex ;
//���荀��
	//UNQ_NO =  AnsiString(pCBO_SELECT[iCBO_INDEX].UNQ_NO).ToIntDef(0);
    //KOMK_NO = AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_NO).ToIntDef(0);
    KOMK_NM  = AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_NM);
    KOMK_SUB = AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_SUB);
    TANI     = AnsiString(pCBO_SELECT[iCBO_INDEX].TANI);
	if( iENA_GRID == 0 )	//�V�K�o�^�ΏۃO���b�h�͏o�׌���
	{
    	iRow = SGr_vRIRE_SYUKA->Row ;
		iCol = SGr_vRIRE_SYUKA->Col ;
		if(SGr_vRIRE_SYUKA->Cells[iCol][iRow].Length() != 0)         //�O���b�h����
		{
        	strcpy(pBUN_DATA[iCol*99+iRow].DTKSHIN		,pCBO_SELECT[iCBO_INDEX].DTKSHIN);
            strcpy(pBUN_DATA[iCol*99+iRow].LOTNO		,SGr_vRIRE_SYUKA->Cells[iCol][0].c_str());
            strcpy(pBUN_DATA[iCol*99+iRow].HINBAN		,SGr_vRIRE_SYUKA->Cells[iCol][1].c_str());
            strcpy(pBUN_DATA[iCol*99+iRow].UNQ_NO		,pCBO_SELECT[iCBO_INDEX].UNQ_NO  	);
            strcpy(pBUN_DATA[iCol*99+iRow].KOMK_NO		,pCBO_SELECT[iCBO_INDEX].KOMK_NO 	);
		   	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_NM		,pCBO_SELECT[iCBO_INDEX].KOMK_NM 	);
		  	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_ENG		,pCBO_SELECT[iCBO_INDEX].KOMK_ENG	);
		 	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_SUB		,pCBO_SELECT[iCBO_INDEX].KOMK_SUB	);
			strcpy(pBUN_DATA[iCol*99+iRow].KOMK_SUB_ENG	,pCBO_SELECT[iCBO_INDEX].KOMK_SUB_ENG	);
	   		strcpy(pBUN_DATA[iCol*99+iRow].KIKI_NO		,pCBO_SELECT[iCBO_INDEX].KIKI_NO 	);
	  		strcpy(pBUN_DATA[iCol*99+iRow].KIKI_NM		,pCBO_SELECT[iCBO_INDEX].KIKI_NM 	);
	 		strcpy(pBUN_DATA[iCol*99+iRow].TANI			,pCBO_SELECT[iCBO_INDEX].TANI 	  );
			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_TYPE	,pCBO_SELECT[iCBO_INDEX].KIKA_TYPE );
   			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_KIND	,pCBO_SELECT[iCBO_INDEX].KIKA_KIND );
  			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_DECI	,pCBO_SELECT[iCBO_INDEX].KIKA_DECI );
 			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM1	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM1 );
			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM2	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM2 );
			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM3	,pCBO_SELECT[iCBO_INDEX].KIKA_NUM3 );
            strcpy(pBUN_DATA[iCol*99+iRow].KIKA_STR		,pCBO_SELECT[iCBO_INDEX].KIKA_STR );
		   	strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB1	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB1 );
		  	strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB2	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB2 );
		 	strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB3	,pCBO_SELECT[iCBO_INDEX].KIKA_SUB3 );
			strcpy(pBUN_DATA[iCol*99+iRow].SOKU_SU		,AnsiString(Num_SOKU_SU->Text).c_str());
	   		strcpy(pBUN_DATA[iCol*99+iRow].SOKU_FLG		,pCBO_SELECT[iCBO_INDEX].SOKU_FLG );
	  		strcpy(pBUN_DATA[iCol*99+iRow].TOKU_FLG		,pCBO_SELECT[iCBO_INDEX].TOKU_FLG );
			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_PRT 	,pCBO_SELECT[iCBO_INDEX].KIKA_PRT 	);
			strcpy(pBUN_DATA[iCol*99+iRow].VALUE_TYPE	,pCBO_SELECT[iCBO_INDEX].VALUE_TYPE 	);
		   	strcpy(pBUN_DATA[iCol*99+iRow].VALUE_DECI	,pCBO_SELECT[iCBO_INDEX].VALUE_DECI 	);
		   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_SU	,sSOKU_VAL_SU.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_AVE	,sSOKU_VAL_AVE.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MAX	,sSOKU_VAL_MAX.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MIN	,sSOKU_VAL_MIN.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_OK		,sSOKU_OK.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].SKTYMD		,sSYSTEM_DATE.c_str());     //��ʏ�̓��t(�Z���ɕ`�悳�����t�͂�����Q�Ɓj
		   	//strcpy(pBUN_DATA[iCol*99+iRow].ADDYMD		,sDATE.c_str());            //��ʏ�̓��t
		   	//strcpy(pBUN_DATA[iCol*99+iRow].ADDTIM		,sTIME.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].UPDYMD		,sDATE.c_str());            //��ʏ�̓��t
		   	strcpy(pBUN_DATA[iCol*99+iRow].UPDTIM		,sTIME.c_str());
		   	strcpy(pBUN_DATA[iCol*99+iRow].UPDCHR		,sUPDCHR.c_str());
		   	sUPDCNT = pBUN_DATA[iCol*99+iRow].UPDCNT;
		   	strcpy(pBUN_DATA[iCol*99+iRow].UPDCNT		,AnsiString(sUPDCNT.ToIntDef(0)+1).c_str());
           	pBUN_DATA[iCol*99+iRow].MAX 				= pCBO_SELECT[iCBO_INDEX].MAX ;
           	pBUN_DATA[iCol*99+iRow].MIN 				= pCBO_SELECT[iCBO_INDEX].MIN ;
			//2003.05.12 E.Takase Add��
			//2003.05.17 E.Takase Add��
            strcpy(pBUN_DATA[iCol*99+iRow].UPD_NAME 	,sUPDNAME.c_str());
			//2003.05.17 E.Takase Add��
			for(i1 = 0 ; i1 < AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_SU).ToIntDef(0);i1++)
			{
				strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL[i1],SGr_vSOKUTEI->Cells[1][i1].c_str());
            }
            SGr_vRIRE_SYUKA->Cells[iCol][iRow] = AnsiString(pBUN_DATA[iCol*99+iRow].SKTYMD).SubString(5,2)
            								  + "/" +AnsiString(pBUN_DATA[iCol*99+iRow].SKTYMD).SubString(7,2)
											  + " " +AnsiString(pBUN_DATA[iCol*99+iRow].UPD_NAME);//�f�o�b�O�p
		}
		else
		{
            MessageDlg("�ȑO�̃f�[�^�������̂ŁA�C���ł��܂���B", mtWarning , TMsgDlgButtons() << mbOK , 0);
            return;
		}
	}
	else
	{
    	iRow = SGr_vSOKU_SYUKA->Row ;
		iCol = SGr_vSOKU_SYUKA->Col ;
		iSOKUCol = SGr_vRIRE_SYUKA->ColCount;
		if(SGr_vSOKU_SYUKA->Cells[iCol][iRow].Length() != 0)         //�O���b�h����
		{
        	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].DTKSHIN		,pCBO_SELECT[iCBO_INDEX].DTKSHIN);
            strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].LOTNO			,SGr_vSOKU_SYUKA->Cells[iCol][0].c_str());
            strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].HINBAN			,SGr_vSOKU_SYUKA->Cells[iCol][1].c_str());
            strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UNQ_NO		,pCBO_SELECT[iCBO_INDEX].UNQ_NO  	);
            strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_NO		,pCBO_SELECT[iCBO_INDEX].KOMK_NO 	);
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_NM		,pCBO_SELECT[iCBO_INDEX].KOMK_NM 	);
		  	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_ENG		,pCBO_SELECT[iCBO_INDEX].KOMK_ENG	);
		 	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_SUB		,pCBO_SELECT[iCBO_INDEX].KOMK_SUB	);
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KOMK_SUB_ENG	,pCBO_SELECT[iCBO_INDEX].KOMK_SUB_ENG	);
	   		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKI_NO		,pCBO_SELECT[iCBO_INDEX].KIKI_NO 	);
	  		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKI_NM		,pCBO_SELECT[iCBO_INDEX].KIKI_NM 	);
	 		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].TANI			,pCBO_SELECT[iCBO_INDEX].TANI 	  );
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_TYPE		,pCBO_SELECT[iCBO_INDEX].KIKA_TYPE );
   			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_KIND		,pCBO_SELECT[iCBO_INDEX].KIKA_KIND );
  			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_DECI		,pCBO_SELECT[iCBO_INDEX].KIKA_DECI );
 			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM1		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM1 );
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM2		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM2 );
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_NUM3		,pCBO_SELECT[iCBO_INDEX].KIKA_NUM3 );
            strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_STR		,pCBO_SELECT[iCBO_INDEX].KIKA_STR );
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB1		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB1 );
		  	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB2		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB2 );
		 	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_SUB3		,pCBO_SELECT[iCBO_INDEX].KIKA_SUB3 );
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_SU		,AnsiString(Num_SOKU_SU->Text).c_str());
	   		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_FLG		,pCBO_SELECT[iCBO_INDEX].SOKU_FLG );
	  		strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].TOKU_FLG		,pCBO_SELECT[iCBO_INDEX].TOKU_FLG );
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].KIKA_PRT	    ,pCBO_SELECT[iCBO_INDEX].KIKA_PRT 	);
			strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].VALUE_TYPE	,pCBO_SELECT[iCBO_INDEX].VALUE_TYPE 	);
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].VALUE_DECI	,pCBO_SELECT[iCBO_INDEX].VALUE_DECI 	);
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_SU	,sSOKU_VAL_SU.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_AVE	,sSOKU_VAL_AVE.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_MAX	,sSOKU_VAL_MAX.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL_MIN	,sSOKU_VAL_MIN.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_OK		,sSOKU_OK.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD		,sSYSTEM_DATE.c_str());
		   	//strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].ADDYMD		,sDATE.c_str());
		   	//strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].ADDTIM		,sTIME.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDYMD		,sDATE.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDTIM		,sTIME.c_str());
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDCHR		,sUPDCHR.c_str());
		   	sUPDCNT = pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDCNT;
		   	strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPDCNT		,AnsiString(sUPDCNT.ToIntDef(0)+1).c_str());
           	pBUN_DATA[(iSOKUCol+iCol)*99+iRow].MAX 					= pCBO_SELECT[iCBO_INDEX].MAX ;
           	pBUN_DATA[(iSOKUCol+iCol)*99+iRow].MIN 					= pCBO_SELECT[iCBO_INDEX].MIN ;
			//2003.05.12 E.Takase Add��
			//2003.05.17 E.Takase Add��
            strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME 	  	,sUPDNAME.c_str());
			//2003.05.17 E.Takase Add��
			for(i1 = 0 ; i1 < AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_SU).ToIntDef(0);i1++)
			{
				strcpy(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SOKU_VAL[i1],SGr_vSOKUTEI->Cells[1][i1].c_str());
            }
            SGr_vSOKU_SYUKA->Cells[iCol][iRow] 	   = AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD).SubString(5,2)
            								  + "/" +AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].SKTYMD).SubString(7,2)
											  + " " +AnsiString(pBUN_DATA[(iSOKUCol+iCol)*99+iRow].UPD_NAME);//�f�o�b�O�p
			iCol += iSOKUCol;
		}
		else
		{
            MessageDlg("�ȑO�̃f�[�^�������̂ŁA�C���ł��܂���B", mtWarning , TMsgDlgButtons() << mbOK , 0);
			return;
		}
	}


	sBuf = "delete FROM KSD11 WHERE";
	sBuf += " DTKSHIN='"	    +	AnsiString(pBUN_DATA[iCol*99+iRow].DTKSHIN)	  + "'";
	sBuf += " AND HINBAN='"	    +	AnsiString(pBUN_DATA[iCol*99+iRow].HINBAN) + "'";
	sBuf += " AND LOTNO='"	    +	AnsiString(pBUN_DATA[iCol*99+iRow].LOTNO) + "'";
	sBuf += " AND BNKT_UNQ_NO=" +	AnsiString(pBUN_DATA[iCol*99+iRow].BNKT_UNQ_NO) ;
//���R�[�h�̍폜
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
	Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);
// �₢�������̎��s                                  
	try
    {
    	Query1->ExecSQL();
    }
    catch(EDatabaseError& e)
    {
    	Form1->SBr1->Panels->Items[0]->Text = e.Message;
        Form1->SBr1->Update();
        return;
    }
    catch(Exception& e)
    {
    	Form1->SBr1->Panels->Items[0]->Text = e.Message;
        Form1->SBr1->Update();
        return;
    }

    sBuf = "insert into KSD11(";
    sBuf += " DTKSHIN, HINBAN, LOTNO, BNKT_UNQ_NO, UNQ_NO,";
	sBuf += " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG,";
	sBuf += " KIKI_NO, KIKI_NM, TANI, KIKA_TYPE, KIKA_KIND,";
	sBuf += " KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, KIKA_STR,";
	sBuf += " KIKA_SUB1, KIKA_SUB2, KIKA_SUB3,";
	sBuf += " SOKU_SU, SOKU_FLG, TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI,";
	sBuf += " SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05,";
	sBuf += " SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,";
	sBuf += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK,";
    sBuf += " SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT)";

    sBuf += " VALUES('";
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].DTKSHIN)		+ "','";	//	���Ӑ�i��
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].HINBAN)		+ "','";	//	���Ӑ�i��
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].LOTNO)		+ "', ";	//	���b�gNO
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].BNKT_UNQ_NO)	+ " , ";	//
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].UNQ_NO)		+ " , ";	//

    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_NO)  	+ " ,'";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_NM)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_ENG)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_SUB)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_SUB_ENG)+ "', ";	//	�����

    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKI_NO)  	+ " ,'";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKI_NM)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].TANI)  		+ "', ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKA_TYPE)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKA_KIND)  	+ " , ";	//	�����

    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKA_DECI)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKA_NUM1)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKA_NUM2)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKA_NUM3)  	+ " ,'";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKA_STR)  	+ "','";	//	�����

    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKA_SUB1)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKA_SUB2)  	+ "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKA_SUB3)  	+ "', ";	//	�����

    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_SU)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_FLG)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].TOKU_FLG)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].KIKA_PRT)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].VALUE_TYPE)  + " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].VALUE_DECI)  + " ,'";	//	�����

    for( i2 = 0; i2 <  10 ;i2++)
	{
		if(  AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_VAL[i2]).Length() == 0 )
		{
			sBuf += " ','";
		}
		else
		{
    		//sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_VAL[i2])  + "','";	//	�o�^��
        // ��������
		    sRESULT_BUF = AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_VAL[i2]);
            if( sRESULT_BUF.Length() >= 14 ){
    		    if ( sRESULT_BUF.ByteType( 14 ) == mbLeadByte ){
				    sRESULT_BUF = sRESULT_BUF.SubString(1,13);
                }
            }
            sBuf += sRESULT_BUF + "','";
    	}
	}
    sBuf = sBuf.SubString(1,sBuf.Length()-1);
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_VAL_SU)  	+ " , ";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_VAL_AVE)  	+ " , ";	//	�o�^��
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MAX)  	+ " , ";	//	�o�^����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MIN)  	+ " , ";	//	�ύX��
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_OK)  	    + " ,'";	//	�ύX��
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].SKTYMD)  	    + "','";	//	�����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].ADDYMD)  	    + "','";	//	�o�^��
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].ADDTIM)  	    + "','";	//	�o�^����
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].UPDYMD)  	    + "','";	//	�ύX��
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].UPDTIM)  	    + "','";	//	�ύX����
	sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].UPDCHR)		    + "','";	//  �S���҃R�[�h
    sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].UPDCNT)          + "'";  	//	�X�V��
    sBuf += ")";
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
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);

// �₢�������̎��s
	try
    {
    	Query1->ExecSQL();

    }
    catch(EDatabaseError& e)
    {
    	Form1->SBr1->Panels->Items[0]->Text = e.Message;
        Form1->SBr1->Update();
        return;
    }
    catch(Exception& e)
    {
    	Form1->SBr1->Panels->Items[0]->Text = e.Message;
        Form1->SBr1->Update();
        return;
    }
    Query1->Close();

//��O�f�[�^�̏���
//�ȑO�̃f�[�^������
    sBuf = "DELETE from KSD12 where";
	sBuf += " DTKSHIN='"	    +	AnsiString(pBUN_DATA[iCol*99+iRow].DTKSHIN)	  + "'";
	sBuf += " AND HINBAN='"	    +	AnsiString(pBUN_DATA[iCol*99+iRow].HINBAN)	  + "'";
	sBuf += " AND LOTNO='"	    +	AnsiString(pBUN_DATA[iCol*99+iRow].LOTNO) + "'";

// Initial Query
    Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
	   	MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
	  	return;
    }
    catch(Exception& e) {
        MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
        return;
    }

//��O�f�[�^�̏�������
    for(i2 = 10 ; i2 < AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_SU).ToIntDef(0) ; i2++)
    {
        sBuf = "insert into KSD12(";
        sBuf += " DTKSHIN, HINBAN, LOTNO, BNKT_UNQ_NO, SOKU_NO, SOKU_VAL )";

        sBuf += " VALUES('";
        sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].DTKSHIN)	    + "','";	//	���Ӑ�i��
        sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].HINBAN)	    + "','";	//	���Ӑ�i��
        sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].LOTNO)		    + "', ";	//	���Ӑ�i��
        sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].BNKT_UNQ_NO)   + " , ";	//	���Ӑ�i��
        sBuf += AnsiString(i2+1)		                            + " ,'";	//	���Ӑ�i��
        if(  AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_VAL[i2]).Length() == 0 )
        {
            sBuf += " ')";
        }
		else
		{
    		//sBuf += AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_VAL[i2])  + "')";	//	�o�^��
        // ��������
		    sRESULT_BUF = AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_VAL[i2]);
            if( sRESULT_BUF.Length() >= 14 ){
    		    if ( sRESULT_BUF.ByteType( 14 ) == mbLeadByte ){
				    sRESULT_BUF = sRESULT_BUF.SubString(1,13);
                }
            }
            sBuf += sRESULT_BUF + "')";
    	}
    // Initial Query
        Query1->Close();
        Query1->SQL->Clear();
        Query1->SQL->Add(sBuf);

        // �₢�������̎��s
        try {
            Query1->ExecSQL();
        }
        catch(EDatabaseError& e) {
	   	    MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
	  	    return;
        }
        catch(Exception& e) {
            MessageDlg( e.Message, mtWarning, TMsgDlgButtons() << mbOK , 0);
            return;
        }
    }
    Query1->Close();
    BtnF11->Enabled = true;
	return;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�P�O�F�폜�v�{�^�������������̏���
//
//  �@�\����
//    �Z���̏����폜���A�f�[�^�x�[�X������폜���܂��B
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
//
//---------------------------------------------------------------------------
void __fastcall TForm7::BtnF10Click(TObject *Sender)
{
	AnsiString sBuf;
    AnsiString sLOT,sDTKSHIN,sHINBAN;
    AnsiString sUPDYMD,sUPDTIM;
    int iRow,iCol,i1;

	if( iENA_GRID == 0 )	//�V�K�o�^�ΏۃO���b�h�͏o�׌���
	{
		iRow = SGr_vRIRE_SYUKA->Row;
		iCol = SGr_vRIRE_SYUKA->Col;
		if(SGr_vRIRE_SYUKA->Cells[iCol][iRow].Length() != 0)
		{
			sLOT 		= AnsiString(pBUN_DATA[iCol*99+iRow].LOTNO);
			sDTKSHIN 	= AnsiString(pBUN_DATA[iCol*99+iRow].DTKSHIN);
			sHINBAN 	= AnsiString(pBUN_DATA[iCol*99+iRow].HINBAN);
			sUPDYMD 	= AnsiString(pBUN_DATA[iCol*99+iRow].UPDYMD);
			sUPDTIM 	= AnsiString(pBUN_DATA[iCol*99+iRow].UPDTIM);
			SGr_vRIRE_SYUKA->Cells[iCol][iRow] = "";
            //�z��̏���
            strcpy(pBUN_DATA[iCol*99+iRow].DTKSHIN		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].HINBAN		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].LOTNO		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].UNQ_NO		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].KOMK_NO		,"");
	    strcpy(pBUN_DATA[iCol*99+iRow].KOMK_NM		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].KOMK_ENG		,"");
		   	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_SUB		,"");
		  	strcpy(pBUN_DATA[iCol*99+iRow].KOMK_SUB_ENG	,"");
            strcpy(pBUN_DATA[iCol*99+iRow].KIKI_NO		,"");
	  		strcpy(pBUN_DATA[iCol*99+iRow].KIKI_NM		,"");
	   		strcpy(pBUN_DATA[iCol*99+iRow].TANI			,"");
	  		strcpy(pBUN_DATA[iCol*99+iRow].KIKA_TYPE	,"");
   	 		strcpy(pBUN_DATA[iCol*99+iRow].KIKA_KIND	,"");
  			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_DECI	,"");
   			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM1	,"");
  			strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM2	,"");
            strcpy(pBUN_DATA[iCol*99+iRow].KIKA_NUM3	,"");
            strcpy(pBUN_DATA[iCol*99+iRow].KIKA_STR		,"");
		   	strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB1	,"");
            strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB2	,"");
            strcpy(pBUN_DATA[iCol*99+iRow].KIKA_SUB3	,"");
            //SOKU_SU�������̑O��SOKU_SU���̏��������s��
            for(i1 = 0 ; i1 < AnsiString(pBUN_DATA[iCol*99+iRow].SOKU_SU).ToIntDef(0);i1++)
            {
                strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL[i1],"");
            }
            strcpy(pBUN_DATA[iCol*99+iRow].SOKU_SU		,"");
	   	   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_FLG		,"");
		  	strcpy(pBUN_DATA[iCol*99+iRow].TOKU_FLG		,"");
		 	strcpy(pBUN_DATA[iCol*99+iRow].VALUE_TYPE	,"");
		   	strcpy(pBUN_DATA[iCol*99+iRow].VALUE_DECI	,"");
	   	   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_SU	,"");
	  	   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_AVE	,"");
	 	   	strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MAX	,"");
            strcpy(pBUN_DATA[iCol*99+iRow].SOKU_VAL_MIN	,"");
            strcpy(pBUN_DATA[iCol*99+iRow].SOKU_OK		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].SKTYMD		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].ADDYMD		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].ADDTIM		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].UPDYMD		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].UPDTIM		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].UPDCHR		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].UPDCNT		,"");
            strcpy(pBUN_DATA[iCol*99+iRow].UPD_NAME   	,"");
            pBUN_DATA[iCol*99+iRow].MAX 				= 0;
            pBUN_DATA[iCol*99+iRow].MIN 				= 0;
            /////////////////////////////
 		}
		else
		{
            MessageDlg("�ȑO�̃f�[�^�������̂ŁA�폜�ł��܂���B", mtWarning , TMsgDlgButtons() << mbOK , 0);
			return;
		}
	}
	else
	{
		iRow = SGr_vSOKU_SYUKA->Row;
		iCol = SGr_vSOKU_SYUKA->Col;
		if(SGr_vSOKU_SYUKA->Cells[iCol][iRow].Length() != 0)
		{
			sLOT 		= AnsiString(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].LOTNO);
			sDTKSHIN 	= AnsiString(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].DTKSHIN);
			sHINBAN 	= AnsiString(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].HINBAN);
			sUPDYMD 	= AnsiString(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].UPDYMD);
			sUPDTIM 	= AnsiString(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].UPDTIM);
			SGr_vSOKU_SYUKA->Cells[iCol][iRow] = "";
            //�z��̏���
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].DTKSHIN		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].HINBAN		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].LOTNO		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].UNQ_NO		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KOMK_NO		,"");
		   	strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KOMK_NM		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KOMK_ENG		,"");
		   	strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KOMK_SUB		,"");
		  	strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KOMK_SUB_ENG	,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKI_NO		,"");
	  		strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKI_NM		,"");
	   		strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].TANI			,"");
	  		strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKA_TYPE	,"");
   	 		strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKA_KIND	,"");
  			strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKA_DECI	,"");
   			strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKA_NUM1	,"");
  			strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKA_NUM2	,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKA_NUM3	,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKA_STR		,"");
		   	strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKA_SUB1	,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKA_SUB2	,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].KIKA_SUB3	,"");
            //SOKU_SU�������̑O��SOKU_SU���̏��������s��
            for(i1 = 0 ; i1 < AnsiString(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].SOKU_SU).ToIntDef(0);i1++)
            {
                strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].SOKU_VAL[i1],"");
            }
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].SOKU_SU		,"");
	   	   	strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].SOKU_FLG		,"");
		  	strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].TOKU_FLG		,"");
		 	strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].VALUE_TYPE	,"");
		   	strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].VALUE_DECI	,"");
	   	   	strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].SOKU_VAL_SU	,"");
	  	   	strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].SOKU_VAL_AVE	,"");
	 	   	strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].SOKU_VAL_MAX	,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].SOKU_VAL_MIN	,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].SOKU_OK		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].SKTYMD		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].ADDYMD		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].ADDTIM		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].UPDYMD		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].UPDTIM		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].UPDCHR		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].UPDCNT		,"");
            strcpy(pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].UPD_NAME   	,"");
            pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].MAX 				= 0;
            pBUN_DATA[(iCol+SGr_vRIRE_SYUKA->ColCount)*99+iRow].MIN 				= 0;
		}
		else
		{
            MessageDlg("�ȑO�̃f�[�^�������̂ŁA�폜�ł��܂���B", mtWarning , TMsgDlgButtons() << mbOK , 0);
			return;
		}
		iCol += SGr_vRIRE_SYUKA->ColCount;
	}
	sBuf ="delete FROM KSD11 WHERE";
	sBuf += " DTKSHIN='"	+	sDTKSHIN	+ "'";
	sBuf += " AND HINBAN='"	+	sHINBAN	+ "'";
	sBuf += " AND LOTNO='"	+	sLOT	+ "'";
	sBuf += " AND BNKT_UNQ_NO='" +	AnsiString(pBUN_DATA[iCol*99+iRow].BNKT_UNQ_NO) +"'";
//	sBuf += " AND UPDYMD ='" +  sUPDYMD	+ "'";
//	sBuf += " AND UPDTIM ='" +  sUPDTIM	+ "'";
//���R�[�h�̍폜
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
	Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);
// �₢�������̎��s
	try
    {
    	Query1->ExecSQL();
    }
    catch(EDatabaseError& e)
    {
    	Form1->SBr1->Panels->Items[0]->Text = e.Message;
        Form1->SBr1->Update();
        return;
    }
    catch(Exception& e)
    {
    	Form1->SBr1->Panels->Items[0]->Text = e.Message;
        Form1->SBr1->Update();
        return;
    }
	sBuf ="delete FROM KSD12 WHERE";
	sBuf += " DTKSHIN='"	+	sDTKSHIN	+ "'";
	sBuf += " AND HINBAN='"	+	sHINBAN	+ "'";
	sBuf += " AND LOTNO='"	+	sLOT	+ "'";
	sBuf += " AND BNKT_UNQ_NO='" +	AnsiString(pBUN_DATA[iCol*99+iRow].BNKT_UNQ_NO) +"'";
//���R�[�h�̍폜
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
	Query1->Close();
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);
// �₢�������̎��s
	try
    {
    	Query1->ExecSQL();
    }
    catch(EDatabaseError& e)
    {
    	Form1->SBr1->Panels->Items[0]->Text = e.Message;
        Form1->SBr1->Update();
        return;
    }
    catch(Exception& e)
    {
    	Form1->SBr1->Panels->Items[0]->Text = e.Message;
        Form1->SBr1->Update();
        return;
    }
    BtnF11->Enabled = true;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�	�F���[�U�[�R�[�h����O���b�h�ɕ\�����閼�O���o�͂���
//
//  �@�\����
//    ���[�U�[�R�[�h����O���b�h�ɕ\�����閼�O���o�͂���B
//
//  �p�����^����
//    AnsiString CODE	�F���[�U�[�R�[�h
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm7::GetTANTO(AnsiString CODE)
{
     //���[�U�[������

	AnsiString sBuf;
    int i1;

	if( CODE.Length() == 0 ) return(Form1->USER_NAM);

	// �⍇�����s(�S���҃R�[�h)
    sBuf = "SELECT TANSYA, TANNAM FROM SM12S WHERE TANSYA = ";
    sBuf += CODE ;

    // Initial Query
    Query2->Close();
    Query2->SQL->Clear();
    Query2->SQL->Add(sBuf);
    Query2->Open();
    Query2->Active = true;

    //�S���҃R�[�h������
    if ( Query2->Bof == true && Query2->Eof ) {
    //�������� �O��
		sBuf = Form1->USER_NAM;
    }
    else
    {
		sBuf = Query2->FieldValues["TANNAM"];
    }
	Query2->Close();

     for(i1=1;i1<sBuf.Length();i1++)
     {
		if(sBuf.SubString(i1,2) == "�@")
		{
			sBuf = sBuf.SubString(1,i1-1);
			break;
		}
	}
    return(sBuf);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�	�F���[�U�[������O���b�h�ɕ\�����閼�O���o�͂���B
//
//  �@�\����
//    StringGrid�̑傫���̐���ŁA�Z���ɕ\�����閼�O�͕c���ƂȂ����̂Œ��o�֐��ł��B
//
//  �p�����^����
//    AnsiString CODE	�F���[�U�[�R�[�h
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm7::GetTANTO2(AnsiString CODE)
{
     //���[�U�[������

	AnsiString sBuf;
    int i1;

	if( CODE.Length() == 0 ) return(Form1->USER_NAM);

	//2003.05.12 E.Takase Add��
    sBuf = CODE;
	//2003.05.12 E.Takase Add��
	//2003.05.12 E.Takase Add �R�����g��
	/// �⍇�����s(�S���҃R�[�h)
    //sBuf = "SELECT TANSYA, TANNAM FROM SM12S WHERE TANSYA = ";
    //sBuf += CODE ;
    //
    //// Initial Query
    //Query2->Close();
    //Query2->SQL->Clear();
    //Query2->SQL->Add(sBuf);
    //Query2->Open();
    //Query2->Active = true;
    //
    ////�S���҃R�[�h������
    //if ( Query2->Bof == true && Query2->Eof ) {
    ////�������� �O��
	//	sBuf = Form1->USER_NAM;
    //}
    //else
    //{
	//	sBuf = Query2->FieldValues["TANNAM"];
    //}
	//Query2->Close();
	//2003.05.12 E.Takase Add �R�����g��

     for(i1=1;i1<sBuf.Length();i1++)
     {
		if(sBuf.SubString(i1,2) == "�@")
		{
			sBuf = sBuf.SubString(1,i1-1);
			break;
		}
	}
    return(sBuf);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnChange �C�x���g�F�ҏW�̈�ɕ\�����ꂽ�e�L�X�g���ύX�����Ɣ������܂��B
//
//  �@�\����
//    �R���{�{�b�N�X�̃��b�g���ύX�����Ɣ������܂��B�A������StringGrid�̃Z���̈ړ����s���܂��B
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
//
//---------------------------------------------------------------------------
void __fastcall TForm7::Cbo_LOTChange(TObject *Sender)
{
	AnsiString sBuf;
    int iCol;
    bool bRIRESearch ;
    bool bSOKUSearch ;
	sBuf = Cbo_LOT->Text ;
    bRIRESearch = false;
    bSOKUSearch = false;

    for(iCol = 0; iCol < SGr_vRIRE_SYUKA->ColCount; iCol++)
    {
    	if(SGr_vRIRE_SYUKA->Cells[iCol][0] == sBuf )
	   	{
	  		bRIRESearch =true;
	 		break;
		}
  	}
	if(bRIRESearch == false )
	{
	    for(iCol = 0; iCol < SGr_vSOKU_SYUKA->ColCount; iCol++)
		{
   			if(SGr_vSOKU_SYUKA->Cells[iCol][0] == sBuf )
	  		{
 				bSOKUSearch =true;
				break;
		   	}
    	}
	}
	if(bRIRESearch == true )
	{
		for( iCol = 0 ; iCol < SGr_vRIRE_SYUKA->ColCount ; iCol++)
		{
			if(SGr_vRIRE_SYUKA->Cells[iCol][0] == sBuf  )
			{
				SGr_vRIRE_SYUKA->Col = iCol;
				SGr_vRIRE_SYUKA->SetFocus();
				break;
			}
		}
	}
	else
	{
		for( iCol = 0 ; iCol < SGr_vSOKU_SYUKA->ColCount ; iCol++)
		{
			if(SGr_vSOKU_SYUKA->Cells[iCol][0] == sBuf  )
			{
				SGr_vSOKU_SYUKA->Col = iCol;
				SGr_vSOKU_SYUKA->SetFocus();
				break;
			}
		}
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��@�F�K�i���Z�o���܂��B
//
//  �@�\����
//    ���̃Z���Ɍ��������K�i�lMAX�AMIN�̎擾���s���B
//
//  �p�����^����
//    int iIndex    �F�ǂ̍��ڂ��ΏۂȂ̂��������C���f�b�N�X�ł��B
//  �@double *dMAX  �F�K�iMAX�l���������܂��B
//  �@double *dMIN  �F�K�iMIN�l���������܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//
//---------------------------------------------------------------------------
void __fastcall TForm7::GetKIKAKU(int iIndex,double *dMAX,double *dMIN)
{
	double dSWAP;

//	if(iDEBUG == 1)return;
//    if( AnsiString(pORDATA[iIndex].KIKA_TYPE).ToIntDef(0) != 3 )
    if( AnsiString(pBUN_DATA[iIndex].KIKA_TYPE).ToIntDef(0) != 3 )
    {
        //2003.05.08 E.Takase Add��
        *dMAX = Form1->ConvDoubleDefD(pBUN_DATA[iIndex].KIKA_NUM1,0.0);
        *dMIN = Form1->ConvDoubleDefD(pBUN_DATA[iIndex].KIKA_NUM1,0.0);
        //2003.05.08 E.Takase Add��
        //2003.05.08 E.Takase Add �R�����g��
    	//try{
    	//	*dMAX = AnsiString(pBUN_DATA[iIndex].KIKA_NUM1).ToDouble();
        //	*dMIN = AnsiString(pBUN_DATA[iIndex].KIKA_NUM1).ToDouble();
        //}
		//catch(EConvertError& e){
		//	*dMAX=0.0;
		//	*dMIN=0.0;
		//	return;
		//}
		//catch(...){
		//	*dMAX=0.0;
		//	*dMIN=0.0;
		//	return;
		//}
        //2003.05.08 E.Takase Add �R�����g��
		switch(AnsiString(pBUN_DATA[iIndex].KIKA_TYPE).ToIntDef(0))
        {
        case 1:
        	switch(AnsiString(pBUN_DATA[iIndex].KIKA_KIND).ToIntDef(0))
            {
            case 1:
                //2003.05.08 E.Takase Add��
        		*dMAX = Form1->ConvDoubleDefD(pBUN_DATA[iIndex].KIKA_NUM2,0.0);
        		*dMIN = Form1->ConvDoubleDefD(pBUN_DATA[iIndex].KIKA_NUM1,0.0);
                //2003.05.08 E.Takase Add��
       			//2003.05.08 E.Takase Add �R�����g��
				//try{
            	//	*dMAX = AnsiString(pBUN_DATA[iIndex].KIKA_NUM2).ToDouble();
                //	*dMIN = AnsiString(pBUN_DATA[iIndex].KIKA_NUM1).ToDouble();
				//}
				//catch(EConvertError& e){
				//	*dMAX=0.0;
				//	*dMIN=0.0;
				//	return;
				//}
				//catch(...){
				//	*dMAX=0.0;
				//	*dMIN=0.0;
				//	return;
				//}
                //2003.05.08 E.Takase Add �R�����g��
                break;
            case 2:
                //2003.05.08 E.Takase Add��
        		*dMAX = Form1->ConvDoubleDefD(pBUN_DATA[iIndex].KIKA_NUM2,0.0);
                //2003.05.08 E.Takase Add��
       			//2003.05.08 E.Takase Add �R�����g��
				//try{
            	//	*dMAX = AnsiString(pBUN_DATA[iIndex].KIKA_NUM2).ToDouble();
                //}
				//catch(EConvertError& e){
				//	*dMAX=0.0;
				//	*dMIN=0.0;
				//	return;
				//}
				//catch(...){
				//	*dMAX=0.0;
				//	*dMIN=0.0;
				//	return;
				//}
                //2003.05.08 E.Takase Add �R�����g��
                break;
            case 3:
            	break;
            default:
            	break;
            }
            break;
        case 2:
        	switch(AnsiString(pBUN_DATA[iIndex].KIKA_KIND).ToIntDef(0))
            {
            case 1:
            	//2003.05.08 E.Takase Add��
           		*dMAX += Form1->ConvDoubleDefD(pBUN_DATA[iIndex].KIKA_NUM2,0.0);
               	*dMIN += Form1->ConvDoubleDefD(pBUN_DATA[iIndex].KIKA_NUM3,0.0);
                //2003.05.08 E.Takase Add��
       			//2003.05.08 E.Takase Add �R�����g��
				//try{
            	//	*dMAX += AnsiString(pBUN_DATA[iIndex].KIKA_NUM2).ToDouble();
                //	*dMIN += AnsiString(pBUN_DATA[iIndex].KIKA_NUM3).ToDouble();
                //}
				//catch(EConvertError& e){
				//	*dMAX=0.0;
				//	*dMIN=0.0;
				//	return;
				//}
				//catch(...){
				//	*dMAX=0.0;
				//	*dMIN=0.0;
				//	return;
				//}
                //2003.05.08 E.Takase Add �R�����g��
                break;
            case 2:
            	//2003.05.08 E.Takase Add��
                *dMAX += Form1->ConvDoubleDefD(pBUN_DATA[iIndex].KIKA_NUM2,0.0);
                //2003.05.08 E.Takase Add��
       			//2003.05.08 E.Takase Add �R�����g��
				//try{
            	//	*dMAX += AnsiString(pBUN_DATA[iIndex].KIKA_NUM2).ToDouble();
                //}
				//catch(EConvertError& e){
				//	*dMAX=0.0;
				//	*dMIN=0.0;
				//	return;
				//}
				//catch(...){
				//	*dMAX=0.0;
				//	*dMIN=0.0;
				//	return;
				//}
                //2003.05.08 E.Takase Add �R�����g��
                break;
            case 3:
            	//2003.05.08 E.Takase Add��
                *dMIN += Form1->ConvDoubleDefD(pBUN_DATA[iIndex].KIKA_NUM3,0.0);
                //2003.05.08 E.Takase Add��
       			//2003.05.08 E.Takase Add �R�����g��
				//try{
            	//	*dMIN += AnsiString(pBUN_DATA[iIndex].KIKA_NUM3).ToDouble();
                //}
				//catch(EConvertError& e){
				//	*dMAX=0.0;
				//	*dMIN=0.0;
				//	return;
				//}
				//catch(...){
				//	*dMAX=0.0;
				//	*dMIN=0.0;
				//	return;
				//}
                //2003.05.08 E.Takase Add �R�����g��
                break;
            default:
            	break;
            }
            break;
        default:
        	break;
        }
		if( *dMAX < *dMIN )
		{
			dSWAP = *dMIN;
			*dMIN = *dMAX;
			*dMAX = dSWAP;
		}
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit �C�x���g�F���̓t�H�[�J�X���R���g���[������ʂ̃R���g���[���ֈڂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���肎�����Q�Ƃ��O���b�h�̏����������s���܂��B
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
//
//---------------------------------------------------------------------------
void __fastcall TForm7::Num_SOKU_SUExit(TObject *Sender)
{
//������肎���̓���
	int i1;

    for(i1 = 0 ; i1 < SGr_vSOKUTEI->RowCount ; i1++)
    {
    	SGr_vSOKUTEI->Cells[1][i1] = "";
    }
    SGr_vSOKUTEI->RowCount = Num_SOKU_SU->Value;
    for( i1=0;i1 < Num_SOKU_SU->Value  ; i1++)
    {
    	SGr_vSOKUTEI->Cells[0][i1] = i1+1;
    }
    bNUM_SET = false;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnKeyDown �C�x���g�F�R���g���[���Ƀt�H�[�J�X������ԂɃ��[�U�[���C�ӂ̃L�[�������Ɣ������܂��B
//
//  �@�\����
//    Enter�L�[�̓��͂��Ď����AEnter�L�[�̓��͂�����Ǝ����I��SGr_vSOKUTEI�O���b�h�փt�H�[�J�X���ڂ�܂��B
//
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
//
//---------------------------------------------------------------------------
void __fastcall TForm7::Num_SOKU_SUKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if(Key == VK_RETURN) SGr_vSOKUTEI->SetFocus();
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit �C�x���g�F���̓t�H�[�J�X���R���g���[������ʂ̃R���g���[���ֈڂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    StringGrid�o�ׁi����j�̏I���������s���A�����I��DrawCell�C�x���g�𔭐������܂��B
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
//
//---------------------------------------------------------------------------
void __fastcall TForm7::SGr_vSOKU_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;
    SGr_vSOKU_SYUKA->Tag = 0;
    GRID_DrawCell( 	Sender,
    				SGr_vSOKU_SYUKA->Col,
                    SGr_vSOKU_SYUKA->Row,
                    SGr_vSOKU_SYUKA->CellRect(SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row),
                    State);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit �C�x���g�F���̓t�H�[�J�X���R���g���[������ʂ̃R���g���[���ֈڂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    StringGrid�o�ׁi�����j�̏I���������s���A�����I��DrawCell�C�x���g�𔭐������܂��B
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
//
//---------------------------------------------------------------------------
void __fastcall TForm7::SGr_vRIRE_SYUKAExit(TObject *Sender)
{
    TGridDrawState State;
    SGr_vRIRE_SYUKA->Tag = 0;
    GRID_DrawCell( 	Sender,
    				SGr_vRIRE_SYUKA->Col,
                    SGr_vRIRE_SYUKA->Row,
                    SGr_vRIRE_SYUKA->CellRect(SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row),
                    State);
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnDrawCell �C�x���g�́C�O���b�h���̃Z����`�悷��K�v������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �@�o�׃O���b�h�͗����Ƒ��肪�r���I�Ƀn�C���C�g�\�����s����悤�ɍ쐬���Ă���܂��B
//  �@�A�@�\�I�ɂ͒l����͂���Z���ł����A�K�i�̔�����ԉ��̃O���b�h�̓��͂ŕۑ��������o����悤�ɍ쐬���Ă���܂��B
//
//  �p�����^����
//    TObject *Sender	�F�Ăяo������VCL�I�u�W�F�N�g
//  �@int ACol          �F
//    int ARow          �F
//    TRect &Rect
//    TGridDrawState State
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//
//---------------------------------------------------------------------------
void __fastcall TForm7::GRID_DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
    AnsiString	sDeci1,sTemp,sResult,sBuf;
	int i1;
    int iROW,iCOL;
	int iKIKA_KIND;
	RECT r;
	AnsiString VALUE_TYPE,VALUE_DECI;
	double dMAX,dMIN;		//�K�i
	int iCBO_INDEX;
    bool bRtn;		//2003.05.08 E.Takase Add
    double dBuf;	//2003.05.08 E.Takase Add
    RECT cr;

	if( (Sender == SGr_vRIRE_SYUKA || Sender == SGr_vSOKU_SYUKA) )
    {
        if((SGr_vSOKUTEI->EditorMode                //����l���͒�
        || bNUM_SET == true                         //n�����͒�
        || SGr_vSOKUTEI->Tag == 1                   //����l
        || Cbo_KOMK_NM->Tag == 1
        || bCALENDER == true )
        && State.Contains(gdFocused)!= true ) return;          //�o�׍��ڑI��
		if(Sender == SGr_vRIRE_SYUKA )
		{
			iENA_GRID = 0;
		}
		else
		{
			iENA_GRID = 1;
		}
		if(State.Contains(gdFixed))
		{
		    switch( iENA_GRID )
			{
			case 0:
    			SGr_vRIRE_SYUKA->Canvas->Brush->Color= clGray;
				break;
			case 1:
    			SGr_vSOKU_SYUKA->Canvas->Brush->Color= clGray;
				break;
			}
    	}
	    else
		{
            switch( iENA_GRID )
            {
            case 0:
    			//�I�𒆂̓n�C���C�g�\��

                if(State.Contains(gdFocused) && SGr_vRIRE_SYUKA->Tag == 1 )
                {
                    r=RECT(Rect);
                    FormSelectCell(SGr_vRIRE_SYUKA,ACol,ARow,true);
                    SGr_vRIRE_SYUKA->Canvas->Font->Color= clHighlightText;
                    SGr_vRIRE_SYUKA->Canvas->Brush->Color= clNavy;
                    sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
                    SGr_vRIRE_SYUKA->Canvas->FillRect(Rect);
                    InflateRect(&r,-2,-2);
                    DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //�E��
                    if(ARow == SGr_vRIRE_SYUKA->Row && ACol == SGr_vRIRE_SYUKA->Col)
                    {
                        RireCellRect = Rect;
                        TempRireCanvas = (TCanvas *)SGr_vRIRE_SYUKA->Canvas;
                    }
                    if(TempSokuCanvas)
                    {
                        cr = RECT(SokuCellRect);
                        iCOL = SGr_vSOKU_SYUKA->Col;
                        iROW = SGr_vSOKU_SYUKA->Row;
                        sBuf = SGr_vSOKU_SYUKA->Cells[iCOL][iROW];
                        TempSokuCanvas->Font->Color= clBlack;
                        TempSokuCanvas->Brush->Color= SGr_vSOKU_SYUKA->Color;
                        TempSokuCanvas->FillRect(SokuCellRect);
                        InflateRect(&cr,-2,-2);
                        DrawText(TempSokuCanvas->Handle,sBuf.c_str(),-1,&cr,DT_LEFT); //�E��
                        TempSokuCanvas = NULL;
                    }

                }
                else
                {
                    r=RECT(Rect);
                    SGr_vRIRE_SYUKA->Canvas->Font->Color = clBlack;
                    SGr_vRIRE_SYUKA->Canvas->Brush->Color= SGr_vRIRE_SYUKA->Color;
                    sBuf = SGr_vRIRE_SYUKA->Cells[ACol][ARow];
                    SGr_vRIRE_SYUKA->Canvas->FillRect(Rect);
                    InflateRect(&r,-2,-2);
                    DrawText(SGr_vRIRE_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //�E��
                    if(ARow == SGr_vRIRE_SYUKA->Row && ACol == SGr_vRIRE_SYUKA->Col)
                    {
                        RireCellRect = Rect;
                        TempRireCanvas = (TCanvas *)SGr_vRIRE_SYUKA->Canvas;
                    }
                    TempRireCanvas = NULL;
                }
                break;
            case 1:
		    	//�I�𒆂̓n�C���C�g�\��
                if(State.Contains(gdFocused) && SGr_vSOKU_SYUKA->Tag == 1)
                {
                    r=RECT(Rect);
                    FormSelectCell(SGr_vSOKU_SYUKA,ACol,ARow,true);
                    SGr_vSOKU_SYUKA->Canvas->Font->Color= clHighlightText;
                    SGr_vSOKU_SYUKA->Canvas->Brush->Color = clNavy;
                    sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
                    SGr_vSOKU_SYUKA->Canvas->FillRect(Rect);
                    InflateRect(&r,-2,-2);
                    DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //�E��
                    if(ARow == SGr_vSOKU_SYUKA->Row && ACol == SGr_vSOKU_SYUKA->Col)
                    {
                        SokuCellRect = Rect;
                        TempSokuCanvas = (TCanvas *)SGr_vSOKU_SYUKA->Canvas;
                    }

                    if(TempRireCanvas)
                    {
                        cr = RECT(RireCellRect);
                        iCOL = SGr_vRIRE_SYUKA->Col;
                        iROW = SGr_vRIRE_SYUKA->Row;
                        sBuf = SGr_vRIRE_SYUKA->Cells[iCOL][iROW];
                        TempRireCanvas->Font->Color= clBlack;
                        TempRireCanvas->Brush->Color= SGr_vRIRE_SYUKA->Color;
                        TempRireCanvas->FillRect(RireCellRect);
                        InflateRect(&cr,-2,-2);
                        DrawText(TempRireCanvas->Handle,sBuf.c_str(),-1,&cr,DT_LEFT); //�E��
                        TempRireCanvas = NULL;
                    }
                }
                else
                {
                    r=RECT(Rect);
                    SGr_vSOKU_SYUKA->Canvas->Font->Color= clBlack;
                    SGr_vSOKU_SYUKA->Canvas->Brush->Color = SGr_vSOKU_SYUKA->Color;
                    sBuf = SGr_vSOKU_SYUKA->Cells[ACol][ARow];
                    SGr_vSOKU_SYUKA->Canvas->FillRect(Rect);
                    InflateRect(&r,-2,-2);
                    DrawText(SGr_vSOKU_SYUKA->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //�E��
                    if(ARow == SGr_vSOKU_SYUKA->Row && ACol == SGr_vSOKU_SYUKA->Col)
                    {
                        SokuCellRect = Rect;
                        TempSokuCanvas = (TCanvas *)SGr_vSOKU_SYUKA->Canvas;
                    }
                    TempSokuCanvas = NULL;
                }
                break;
            }
		}
	}
	else
//����O���b�h�R�[�h
	{
		if(State.Contains(gdFixed))
		{
        	SGr_vSOKUTEI->Canvas->Font->Color= clBlack;
        	SGr_vSOKUTEI->Canvas->Brush->Color= clBtnFace;
    	}
	    else
		{
			//�I�𒆂̓n�C���C�g�\��
            if(State.Contains(gdFocused))
            {
            	SGr_vSOKUTEI->Canvas->Font->Color= clHighlightText;
                SGr_vSOKUTEI->Canvas->Brush->Color= clNavy;
            }
            else
            {
            	SGr_vSOKUTEI->Canvas->Font->Color = clBlack;
                SGr_vSOKUTEI->Canvas->Brush->Color= SGr_vSOKUTEI->Color;
            }
		}
		if(ACol != 1 )
        {
            r=RECT(Rect);
            sBuf = SGr_vSOKUTEI->Cells[ACol][ARow];
            SGr_vSOKUTEI->Canvas->FillRect(Rect);
            InflateRect(&r,-2,-2);
            DrawText(SGr_vSOKUTEI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_RIGHT); //������͂�NO�͉E��
            return;
        }
        r=RECT(Rect);
		iCBO_INDEX = Cbo_KOMK_NM->ItemIndex;
		if(iENA_GRID == 0)			//���ݏo�׌����p�O���b�h�I��
	    {
			iCOL = SGr_vRIRE_SYUKA->Col;
			iROW = SGr_vRIRE_SYUKA->Row-1;
	    	VALUE_TYPE = AnsiString(pCBO_SELECT[iCBO_INDEX].VALUE_TYPE);
    		VALUE_DECI = AnsiString(pCBO_SELECT[iCBO_INDEX].VALUE_DECI);
            dMAX = 	pCBO_SELECT[iCBO_INDEX].MAX;
			dMIN = 	pCBO_SELECT[iCBO_INDEX].MIN;
		}
		else
    	{
			iCOL = SGr_vSOKU_SYUKA->Col+SGr_vRIRE_SYUKA->ColCount;
			iROW = SGr_vSOKU_SYUKA->Row-1;
    		VALUE_TYPE = AnsiString(pCBO_SELECT[iCBO_INDEX].VALUE_TYPE);
	    	VALUE_DECI = AnsiString(pCBO_SELECT[iCBO_INDEX].VALUE_DECI);
			dMAX = 	pCBO_SELECT[iCBO_INDEX].MAX;
			dMIN = 	pCBO_SELECT[iCBO_INDEX].MIN;
		}
		sBuf = SGr_vSOKUTEI->Cells[1][ARow];
//�t�H�[�}�b�g����
		switch(AnsiString(VALUE_TYPE).ToIntDef(0))
    	{
    	case 0:		//�����E����
        	sDeci1 = "0";
            for(i1 = 0;i1 < AnsiString(VALUE_DECI).ToIntDef(0);i1++)
            {
				if( sDeci1.Length()==1) sDeci1 += ".";
            	sDeci1 +="0";
            }
            break;
        case 1:		//�p�x
        	sDeci1 = "0";
            for(i1 = 0;i1 < AnsiString(VALUE_DECI).ToIntDef(0);i1++)
            {
				if( sDeci1.Length()==1) sDeci1 += ".";
            	sDeci1 +="0";
            }
            break;
        case 2:  	//�ǁE��
        	break;
        default:	//����
        	break;
	    }
	//�ȏ�ȉ��̋K�i�̏ꍇ�΍�
        iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
		if(AnsiString(pCBO_SELECT[iCBO_INDEX].KIKA_TYPE) == 1)
        {
			if(AnsiString(pCBO_SELECT[iCBO_INDEX].KIKA_KIND) == 2)
			{
				iKIKA_KIND = 2;
			}
			else if(AnsiString(pCBO_SELECT[iCBO_INDEX].KIKA_KIND) == 3)
			{
				iKIKA_KIND = 3;
			}
		}
    	switch(AnsiString(VALUE_TYPE).ToIntDef(0))
	    {
    	case 0:
	    	if(sBuf.Length() == 0) break;
    	    //2003.05.08 E.Takase Add��
        	bRtn = Form1->ConvDoubleDefS(SGr_vSOKUTEI->Cells[1][ARow],sDeci1,SGr_vSOKUTEI->Cells[1][ARow],&sBuf);
	        //2003.05.08 E.Takase Add��

	        //�Z�����͂��o�b�t�@�Ɏ�荞��
    	    //�ǔ۔���
        	//2003.05.08 E.Takase Add��
	        if ( bRtn ) {
    	        dBuf = Form1->ConvDoubleDefD(sBuf,0.0);
				switch( iKIKA_KIND)
				{
                case 2:
                	if( dBuf <= dMAX  )
                    {
                    	SGr_vSOKUTEI->Canvas->Font->Color = clBlack;
                    }
                    else
                    {
                    	SGr_vSOKUTEI->Canvas->Font->Color = clRed;
                    }
                    break;
                case 3:
                	if( dBuf >= dMIN )
                    {
                    	SGr_vSOKUTEI->Canvas->Font->Color = clBlack;
                    }
                    else
                    {
                    	SGr_vSOKUTEI->Canvas->Font->Color = clRed;
                    }
                    break;
				default:
        			if( dBuf <= dMAX && dBuf >= dMIN)
            		{
	            		SGr_vSOKUTEI->Canvas->Font->Color = clBlack;
    	        	}
        	   	 	else
            		{
            			SGr_vSOKUTEI->Canvas->Font->Color = clRed;
	            	}
					break;
				}
    	    } else {
        		sBuf = SGr_vSOKUTEI->Cells[1][ARow];
	        }
	        //2003.05.08 E.Takase Add��
	        sResult = sBuf;
    	    break;
	    case 1:
    	    //2003.05.08 E.Takase Add��
        	bRtn = Form1->ConvDoubleDefS(SGr_vSOKUTEI->Cells[1][ARow],sDeci1,SGr_vSOKUTEI->Cells[1][ARow],&sBuf);
	        //2003.05.08 E.Takase Add��
    	    //2003.05.08 E.Takase Add �R�����g��
    		//try{
	        //	sBuf = FormatFloat(sDeci1,SGr_vSOKUTEI->Cells[1][ARow].ToDouble());
    	    //}
        	//catch(EConvertError& e){
	        //	sBuf = SGr_vSOKUTEI->Cells[1][ARow];
    	    //    break;
        	//}
	        //catch(...){
    	    //	sBuf = SGr_vSOKUTEI->Cells[1][ARow];
        	//    break;
	        //}
    	    //2003.05.08 E.Takase Add �R�����g��

	        //�ǔ۔���
    	    //2003.05.08 E.Takase Add��
        	if ( bRtn ) {
	            dBuf = Form1->ConvDoubleDefD(sBuf,0.0);
    	    	if( dBuf <= dMAX && dBuf >= dMIN)
        	    {
            		SGr_vSOKUTEI->Canvas->Font->Color = clBlack;
	            }
    	        else
        	    {
            		SGr_vSOKUTEI->Canvas->Font->Color = clRed;
	            }
    	    } else {
        		sBuf = SGr_vSOKUTEI->Cells[1][ARow];
	        }
    	    //2003.05.08 E.Takase Add��
  	        sResult = sBuf;
        	//�Z�����͂��o�b�t�@�Ɏ�荞��
			if( sBuf.Trim().Length() != 0)
    	    {
	    	    i1 = strcspn(sBuf.c_str(),".");
    	    	sTemp = sBuf.SubString(1,i1);
	        	sTemp += "��";
                if(sBuf.SubString(i1+2,sBuf.Length() - i1).Length()!=0)
                {
                	sTemp += sBuf.SubString(i1+2,sBuf.Length() - i1);
                    sTemp += "'";
                }
        		sBuf = sTemp;
			}
    	    break;
		case 2:
    		sBuf = SGr_vSOKUTEI->Cells[1][ARow];
            sBuf = sBuf.Trim();
            if( sBuf == 0 || sBuf == "��")
            {
            	sBuf ="��";
            }
            else if( sBuf.Length() != 0)
            {
            	sBuf = "��";
            }
            if( sBuf == "��" )
            {
            	SGr_vSOKUTEI->Canvas->Font->Color = clRed;
            }
            else
            {
            	SGr_vSOKUTEI->Canvas->Font->Color = clBlack;
            }
        	sResult = sBuf;
            break;
	    default:
    		sBuf = SGr_vSOKUTEI->Cells[1][ARow];
        	sResult = sBuf;
	        break;
    	}
		//�I�𒆂̓n�C���C�g�\��
		if(State.Contains(gdFocused))
		{
    		SGr_vSOKUTEI->Canvas->Font->Color= clHighlightText;
			SGr_vSOKUTEI->Canvas->Brush->Color = clNavy;
		}
        SGr_vSOKUTEI->Canvas->FillRect(Rect);
	    InflateRect(&r,-2,-2);

    	DrawText(SGr_vSOKUTEI->Canvas->Handle,"         ",-1,&r,DT_LEFT); //�Z�������
		switch(AnsiString(VALUE_TYPE).ToIntDef(0))
        {
        case 0:		//�����E����
        case 1:		//�p�x
        	DrawText(SGr_vSOKUTEI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_RIGHT); //�E��
            break;
        case 2:  	//�ǁE��
        	DrawText(SGr_vSOKUTEI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_CENTER); //������
            break;
        default:	//����
        	DrawText(SGr_vSOKUTEI->Canvas->Handle,sBuf.c_str(),-1,&r,DT_LEFT); //����
            break;
        }
    	sBuf = sResult;
        // ��������
		sBuf = sBuf.SubString(1,14);
        if( sBuf.Length() >= 14 ){
    		if ( sBuf.ByteType( 14 ) == mbLeadByte ){
				sBuf = sBuf.SubString(1,13);
            }
        }
		//���͒l�̑��
    	strcpy(pTEMP_BUN_DATA.SOKU_VAL[ARow],sBuf.c_str());
	}
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnExit �C�x���g�F���̓t�H�[�J�X���R���g���[������ʂ̃R���g���[���ֈڂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    SGr_vSOKUTEI�i���̓O���b�h�j���瑼�̃R���g���[�����ڂ����ꍇ�̌㏈�����s���܂��B
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
void __fastcall TForm7::SGr_vSOKUTEIExit(TObject *Sender)
{
    TGridDrawState State;
    SGr_vSOKUTEI->Tag = 0;
    GRID_DrawCell( Sender,
                             SGr_vSOKUTEI->Col,
                             SGr_vSOKUTEI->Row,
                             SGr_vSOKUTEI->CellRect(SGr_vSOKUTEI->Col, SGr_vSOKUTEI->Row),
                             State);

}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��F�O���b�h�̃C�j�V���������B
//
//  �@�\����
//    �Q��ȏ�̌����̍ہA�O�̃O���b�h�������Ă��܂��B
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
void __fastcall TForm7::GRID_INIT(void)
{
	int iCol,iRow;
	for(iRow = 1;iRow < SGr_Title->RowCount ;iRow++)
	{
    	SGr_Title->Cells[0][iRow] = "";
    	SGr_Title->Cells[1][iRow] = "";
	}
	for(iCol = 0; iCol < SGr_vRIRE_SYUKA->ColCount ;iCol++)
	{
		for(iRow = 0; iRow < SGr_vRIRE_SYUKA->RowCount ;iRow++)
		{
			SGr_vRIRE_SYUKA->Cells[iCol][iRow] = "";
		}
    }

	for(iCol = 0; iCol < SGr_vSOKU_SYUKA->ColCount ;iCol++)
	{
		for(iRow = 0; iRow < SGr_vSOKU_SYUKA->RowCount ;iRow++)
		{
			SGr_vSOKU_SYUKA->Cells[iCol][iRow] = "";
		}
    }

	for(iRow = 0; iRow < SGr_vSOKUTEI->RowCount; iRow++)
	{
		SGr_vSOKUTEI->Cells[0][iRow] = "";
		SGr_vSOKUTEI->Cells[1][iRow] = "";
	}
	SGr_vSOKUTEI->RowCount = 1;
	Num_SOKU_SU->Text = 1;
}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnTopLeftChanged �C�x���g�FTopRow �v���p�e�B�܂��� LeftCol �v���p�e�B���ύX���ꂽ����ɔ������܂��B
//
//  �@�\����
//    ��GRIDON�t���O��true�ɂ��܂��B
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
void __fastcall TForm7::SGr_vSOKU_SYUKATopLeftChanged(TObject *Sender)
{
    bGRIDON = true;

    //2003/12/10 E.Takase
    SGr_vRIRE_SYUKA->TopRow  = SGr_vSOKU_SYUKA->TopRow;
    SGr_Title->TopRow  = SGr_vSOKU_SYUKA->TopRow;

}

//---------------------------------------------------------------------------
//
//  �T�v
//  OnKeyPress �C�x���g�́C���[�U�[���P��̕����L�[���������Ƃ��ɔ������܂��B
//
//  �@�\����
//    �P��̃L�[�������ꂽ���ʂƂ��ĉ�������������Ƃ��Ɏg���܂��B
//  �@���̓Z���ɕs���ȓ��͂����������`�F�b�N���܂��B
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
void __fastcall TForm7::SGr_vSOKUTEIKeyPress(TObject *Sender, char &Key)
{
	int iRow,iCol;
	int iCBO_INDEX;
    int iLen;
    AnsiString sBuf;

    bNOW_SOKUTEI = true;
    iCBO_INDEX = Cbo_KOMK_NM->ItemIndex;
	iCol = SGr_vSOKUTEI->Col;
	iRow = SGr_vSOKUTEI->Row;
    sBuf = SGr_vSOKUTEI->Cells[iCol][iRow];
	if( iCol == 0 || Key == VK_RETURN )
    {
        bNOW_SOKUTEI = false;
        return;
    }
    //2003.05.15 E.Takase Add��
	int iVALUE_TYPE = AnsiString(pCBO_SELECT[iCBO_INDEX].VALUE_TYPE).ToIntDef(0);
    switch( iVALUE_TYPE)
    {
    case 2:
        iLen = 1;
        break;
    default:
        iLen = 14;
        break;
    }
    Form1->ChkInputData( sBuf, iVALUE_TYPE, Sender, Key, iLen);
	//2003.05.15 E.Takase Add��

	iCol = SGr_vSOKU_SYUKA->Col;
	iRow = SGr_vSOKU_SYUKA->Row;
//	AllGRID_SelectCell(Sender,iCol,iRow, true);
    bNOW_SOKUTEI = false;

}

//---------------------------------------------------------------------------
//
//  �T�v
//    OnClick�C�x���g	�F�u�e�S�F����v�{�^�������������̏���
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
void __fastcall TForm7::BtnF04Click(TObject *Sender)
{
	////////////////////
    // ��ʈ��
    Form7->Print();

}

//---------------------------------------------------------------------------
//
//  �T�v
//   ����֐��F���ꃍ�b�g�ɓ����A���i�Ԃ����������`�F�b�N���܂��B
//
//  �@�\����
//    ���ꃍ�b�g�ɓ����A���i�Ԃ����������`�F�b�N���܂��B
//
//  �p�����^����
//    int iINSPECT_NO	�F�I�𒆂̍���Index
//
//  �߂�l
//    false     �F�i�ԗL��
//    true      �F�i�Ԗ���
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
bool __fastcall TForm7::NEW_INSPECT_SETOK( int iINSPECT_NO )
{
	AnsiString	sDATE;
	int			iCol,iRow;
    int			iKOMK_NO;
    AnsiString	sUNQ_NO;
    AnsiString	sKOMK_NM;
    AnsiString	sKOMK_SUB;
    AnsiString	sTANI;

	if(iENA_GRID == 0)
	{
		iCol = SGr_vRIRE_SYUKA->Col;
    }
	else
	{
		iCol = SGr_vSOKU_SYUKA->Col;
		iCol += SGr_vRIRE_SYUKA->ColCount;
    }

    // 2003/10/7 A.Tamura ��r�L�[�̓��e��ύX���܂��i�C���O��[KOMK_NO]��[���t]�ł��j
    iKOMK_NO  = AnsiString(pCBO_SELECT[iINSPECT_NO].KOMK_NO).ToIntDef(0);
    sUNQ_NO   = AnsiString(pCBO_SELECT[iINSPECT_NO].UNQ_NO);
    sKOMK_NM  = AnsiString(pCBO_SELECT[iINSPECT_NO].KOMK_NM);
    sKOMK_SUB = AnsiString(pCBO_SELECT[iINSPECT_NO].KOMK_SUB);
    sTANI     = AnsiString(pCBO_SELECT[iINSPECT_NO].TANI);

//	sDATE = FormatDateTime("yyyymmdd",Date());
    sDATE = sSYSTEM_DATE;
	for(iRow = 1; iRow < SGr_Title->RowCount ; iRow++)
	{
    	if( (iKOMK_NO  == AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_NO).ToIntDef(0))
         && (sDATE     == AnsiString(pBUN_DATA[iCol*99+iRow].SKTYMD))
         && (sUNQ_NO   == AnsiString(pBUN_DATA[iCol*99+iRow].UNQ_NO))
         && (sKOMK_NM  == AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_NM))
         && (sKOMK_SUB == AnsiString(pBUN_DATA[iCol*99+iRow].KOMK_SUB))
         && (sTANI     == AnsiString(pBUN_DATA[iCol*99+iRow].TANI)) )
			return( false );
    }
	return( true );
}

//---------------------------------------------------------------------------
//
//  �T�v
//   OnExit �C�x���g�@�F���̓t�H�[�J�X���R���g���[������ʂ̃R���g���[���ֈڂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���t�̓��͂���������ƁASYSTEM_DATE�i�ۑ����g�p�j�̏����������s���܂��B
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
void __fastcall TForm7::MEdt_SOKU_DATEExit(TObject *Sender)
{
    bCALENDER = false;
    sSYSTEM_DATE = MEdt_SOKU_DATE->Text;
    sSYSTEM_DATE =   sSYSTEM_DATE.SubString(1,4)
                    +sSYSTEM_DATE.SubString(6,2)
                    +sSYSTEM_DATE.SubString(9,2);
    MEdt_SOKU_DATE->Text = sSYSTEM_DATE.SubString(1,4) + "/"
                        + sSYSTEM_DATE.SubString(5,2) + "/"
                        + sSYSTEM_DATE.SubString(7,2);
}

//---------------------------------------------------------------------------
//
//  �T�v
//   ����֐��@�F����w���������Z�o���܂��B
//
//  �@�\����
//    �V�����Z�����I�������ƁA����Row�i�������ځj�̑���w���������݂ăf�t�H���g�l�ɍ̗p����B
//
//  �p�����^����
//    �Ȃ��B
//
//  �߂�l
//    ����w�������B
//
//  ���l
//    �Ȃ��B
//
//---------------------------------------------------------------------------
int __fastcall TForm7::GET_NSU( void )
{
    int i1;
    int iRow,iCol;
    int iRESULT;
    int iRIRE_COL;
    AnsiString sBuf;
    iRIRE_COL = SGr_vRIRE_SYUKA->ColCount;

    if(iENA_GRID == 0)
    {
        iCol = SGr_vRIRE_SYUKA->Col;
        iRow = SGr_vRIRE_SYUKA->Row;
    }
    else
    {
        iCol = SGr_vSOKU_SYUKA->Col;
        iRow = SGr_vSOKU_SYUKA->Row;
    }

    iRESULT = 9999;
    if(iENA_GRID == 0)
    {
        for( i1 = iCol-1; i1 >= 0 ; i1--)
        {
            if(SGr_vRIRE_SYUKA->Cells[i1][iRow].Length() != 0 )
            {
                iRESULT = AnsiString(pBUN_DATA[i1*99+iRow].SOKU_SU).ToIntDef(0);
                break;
            }
        }
        if(iRESULT == 9999)
        {
            for( i1 = iCol+1; i1 < SGr_vRIRE_SYUKA->ColCount ; i1++)
            {
                if(SGr_vRIRE_SYUKA->Cells[i1][iRow].Length() != 0 )
                {
                    iRESULT = AnsiString(pBUN_DATA[i1*99+iRow].SOKU_SU).ToIntDef(0);
                    break;
                }
            }
        }
        if(iRESULT == 9999)
        {
            for( i1 = 0; i1 < SGr_vSOKU_SYUKA->ColCount ; i1++)
            {
                if(SGr_vSOKU_SYUKA->Cells[i1][iRow].Length() != 0 )
                {
                    iRESULT = AnsiString(pBUN_DATA[(iRIRE_COL+i1)*99+iRow].SOKU_SU).ToIntDef(0);
                    break;
                }
            }
        }
    }
    else
    {
        for( i1 = iCol-1; i1 >= 0 ; i1--)
        {
            if(SGr_vSOKU_SYUKA->Cells[i1][iRow].Trim().Length() != 0 )
            {
                sBuf = SGr_vSOKU_SYUKA->Cells[i1][iRow];
                iRESULT = AnsiString(pBUN_DATA[(iRIRE_COL+i1)*99+iRow].SOKU_SU).ToIntDef(0);
                break;
            }
        }
        if(iRESULT == 9999)
        {
            for( i1 = iCol+1; i1 < SGr_vSOKU_SYUKA->ColCount ; i1++)
            {
                if(SGr_vSOKU_SYUKA->Cells[i1][iRow].Trim().Length() != 0 )
                {
                    iRESULT = AnsiString(pBUN_DATA[(iRIRE_COL+i1)*99+iRow].SOKU_SU).ToIntDef(0);
                    break;
                }
            }
        }
        if(iRESULT == 9999)
        {
            for( i1 = SGr_vRIRE_SYUKA->ColCount-1 ; i1 >= 0 ; i1--)
            {
                if(SGr_vRIRE_SYUKA->Cells[i1][iRow].Trim().Length() != 0 )
                {
                    iRESULT = AnsiString(pBUN_DATA[i1*99+iRow].SOKU_SU).ToIntDef(0);
                    break;
                }
            }
        }
    }
    if(iRESULT == 9999 ) iRESULT = 1;
    return( iRESULT );
}

//---------------------------------------------------------------------------
//
//  �T�v
//   OnSelectCell �C�x���g�F�@�O���b�h���̃Z�����I�������O�ɔ������܂��B
//
//  �@�\����
//    �����I��DrawCell�C�x���g�𔭐����܂��B
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
void __fastcall TForm7::SGr_vSOKUTEISelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
    TGridDrawState State;
    AnsiString sBuf;

    GRID_DrawCell( Sender,
                             SGr_vSOKUTEI->Col,
                             SGr_vSOKUTEI->Row,
                             SGr_vSOKUTEI->CellRect(SGr_vSOKUTEI->Col, SGr_vSOKUTEI->Row),
                             State);

}

//---------------------------------------------------------------------------
//
//  �T�v
//   OnEnter �C�x���g�F�@�R���g���[�������̓t�H�[�J�X���󂯎�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    bNUM_SET�t���O��true�ɂ��܂��B
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
void __fastcall TForm7::Num_SOKU_SUEnter(TObject *Sender)
{
    bNUM_SET = true;
}

//---------------------------------------------------------------------------
//
//  �T�v
//   OnEnter �C�x���g�F�@�R���g���[�������̓t�H�[�J�X���󂯎�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    SGr_vSOKUTEI�R���g���[���̃^�O���P�ɂ��܂��B
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
void __fastcall TForm7::SGr_vSOKUTEIEnter(TObject *Sender)
{
    SGr_vSOKUTEI->Tag = 1;
}

//---------------------------------------------------------------------------
//
//  �T�v
//   OnEnter �C�x���g�F�@�R���g���[�������̓t�H�[�J�X���󂯎�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�ׁi����j�O���b�h���t�H�[�J�X���󂯎��ƁA�ʒu���Ȃǂ̍X�V���s���܂��B
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
void __fastcall TForm7::SGr_vSOKU_SYUKAEnter(TObject *Sender)
{
    AnsiString sBuf;
    SGr_vSOKU_SYUKA->Tag = 1;
    SGr_vRIRE_SYUKA->Tag = 0;
    iENA_GRID = 1;
    FormSelectCell(Sender,SGr_vSOKU_SYUKA->Col, SGr_vSOKU_SYUKA->Row, true);
    SGr_vSOKU_SYUKA->SetFocus();
    SGr_vRIRE_SYUKA->Refresh();
    SGr_vSOKU_SYUKA->Refresh();

}

//---------------------------------------------------------------------------
//
//  �T�v
//   OnEnter �C�x���g�F�@�R���g���[�������̓t�H�[�J�X���󂯎�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�ׁi�����j�O���b�h���t�H�[�J�X���󂯎��ƁA�ʒu���Ȃǂ̍X�V���s���܂��B
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
void __fastcall TForm7::SGr_vRIRE_SYUKAEnter(TObject *Sender)
{
    AnsiString sBuf;

    SGr_vRIRE_SYUKA->Tag = 1;
    SGr_vSOKU_SYUKA->Tag = 0;
    iENA_GRID = 0;
     FormSelectCell(Sender,SGr_vRIRE_SYUKA->Col, SGr_vRIRE_SYUKA->Row, true);
    SGr_vRIRE_SYUKA->SetFocus();
    SGr_vSOKU_SYUKA->Refresh();
    SGr_vRIRE_SYUKA->Refresh();

}

//---------------------------------------------------------------------------
//
//  �T�v
//   OnEnter �C�x���g�F�@�R���g���[�������̓t�H�[�J�X���󂯎�����Ƃ��ɔ������܂��B
//
//  �@�\����
//    ���ڃR���{���t�H�[�J�X���󂯎��ƁA�^�O���P�ɂ��܂��B
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
void __fastcall TForm7::Cbo_KOMK_NMEnter(TObject *Sender)
{
    Cbo_KOMK_NM->Tag = 1;    
}

//---------------------------------------------------------------------------
//
//  �T�v
//   OnExit �C�x���g�F�@���̓t�H�[�J�X���R���g���[������ʂ̃R���g���[���ֈڂ����Ƃ��ɔ������܂��B
//
//  �@�\����
//    �o�ׁi�����j�O���b�h����t�H�[�J�X��������ƁA�^�O���O�ɂ��܂��B
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
void __fastcall TForm7::Cbo_KOMK_NMExit(TObject *Sender)
{
    Cbo_KOMK_NM->Tag =0;    
}

//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐�			�F�ۑ����Ɏg�p���郍�b�g���̔�����s���܂��B
//
//  �@�\����
//    ���b�g�̔��������������ɔ��f���܂��B
//    �|�P�F������A�O�F�n�j�A�P�F�m�f�A�Q�F�w������
//  �@�D��x�́@�����聄�m�f���n�j���w�������ł�
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
int __fastcall TForm7::GET_HANTEI(void)
{
	int iKIKA_KIND,iCBO_INDEX;
    int iRow,iRowCount,i1;
    int iSOKU_JUDGE;
    AnsiString  VALUE_TYPE,VALUE_DECI;
	AnsiString sBuf,sRESULT,sTEMP_RESULT;
	AnsiString sDECI,sDeci1;
	double dMAX,dMIN,dBuf;
	bool bRtn;
	iRowCount = 0;
	iRow = 0;
    sBuf ="";

    iRowCount = SGr_vSOKUTEI->RowCount;
    iCBO_INDEX = Cbo_KOMK_NM->ItemIndex;
    VALUE_TYPE = AnsiString(pCBO_SELECT[iCBO_INDEX].VALUE_TYPE);
    VALUE_DECI = AnsiString(pCBO_SELECT[iCBO_INDEX].VALUE_DECI);
    dMAX = 	pCBO_SELECT[iCBO_INDEX].MAX;
    dMIN = 	pCBO_SELECT[iCBO_INDEX].MIN;

	//�ȏ�ȉ��̋K�i�̏ꍇ�΍�
    iKIKA_KIND = 1;		//�f�t�H���g�͏㉺���Ŕ���
    if(AnsiString(pCBO_SELECT[iCBO_INDEX].KIKA_TYPE) == 1)
    {
        if(AnsiString(pCBO_SELECT[iCBO_INDEX].KIKA_KIND) == 2)
        {
            iKIKA_KIND = 2;
        }
        else if(AnsiString(pCBO_SELECT[iCBO_INDEX].KIKA_KIND) == 3)
        {
            iKIKA_KIND = 3;
        }
    }
    //�t�H�[�}�b�g����
    sDeci1 = "";
    switch(AnsiString(VALUE_TYPE).ToIntDef(0))
    {
    case 0:		//�����E����
    case 1:		//�p�x
        sDeci1 = "0";
        for(i1 = 0;i1 < AnsiString(VALUE_DECI).ToIntDef(0);i1++)
        {
            if( sDeci1.Length()==1) sDeci1 += ".";
            sDeci1 +="0";
        }
        break;
    case 2:  	//�ǁE��
        break;
    default:	//����
        break;
    }
    iSOKU_JUDGE = 2;                            //�����l�͑���w������

    for( iRow = 0;iRow < iRowCount;iRow++)
    {
		sBuf = SGr_vSOKUTEI->Cells[1][iRow];
    	switch(AnsiString(VALUE_TYPE).ToIntDef(0))
	    {
    	case 0:
	    	if(sBuf.Length() == 0) break;
    	    //2003.05.08 E.Takase Add��
        	bRtn = Form1->ConvDoubleDefS(SGr_vSOKUTEI->Cells[1][iRow],sDeci1,SGr_vSOKUTEI->Cells[1][iRow],&sBuf);
	        //2003.05.08 E.Takase Add��

	        //�Z�����͂��o�b�t�@�Ɏ�荞��
    	    //�ǔ۔���
        	//2003.05.08 E.Takase Add��
	        if ( bRtn )
            {
    	        dBuf = Form1->ConvDoubleDefD(sBuf,0.0);
	        //2003.05.08 E.Takase Add��
				switch( iKIKA_KIND)
				{
                case 2:
                	if( dBuf <= dMAX  )
                    {
                        if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                    }
                    else
                    {
                        if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
                    }
                    break;
                case 3:
                	if( dBuf >= dMIN )
                    {
                        if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
                    }
                    else
                    {
                        if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
                    }
                    break;
				default:
        			if( dBuf <= dMAX && dBuf >= dMIN)
            		{
                        if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
    	        	}
        	   	 	else
            		{
                        if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
	            	}
					break;
				}
    	    }
            else
            {
        		iSOKU_JUDGE = -1;
	        }
    	    break;
	    case 1:
    	    //2003.05.08 E.Takase Add��
        	bRtn = Form1->ConvDoubleDefS(SGr_vSOKUTEI->Cells[1][iRow],sDeci1,SGr_vSOKUTEI->Cells[1][iRow],&sBuf);
	        //2003.05.08 E.Takase Add��
	        //�ǔ۔���
    	    //2003.05.08 E.Takase Add��
        	if ( bRtn )
            {
	            dBuf = Form1->ConvDoubleDefD(sBuf,0.0);
    	    	if( dBuf <= dMAX && dBuf >= dMIN)
        	    {
                        if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
	            }
    	        else
        	    {
                        if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
	            }
    	    }
            else
            {
        		iSOKU_JUDGE = -1;
	        }
    	    break;
		case 2:
            sBuf = sBuf.Trim();
            if( sBuf == 0 || sBuf == "��")
            {
                if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
            }
            else if(sBuf.Length() != 0)
            {
                if(iSOKU_JUDGE != -1 ) iSOKU_JUDGE = 1;
            }
           break;
	    default:
            if(sBuf.Length() != 0)
            {
                if(iSOKU_JUDGE == 2 ) iSOKU_JUDGE = 0;
            }
            else iSOKU_JUDGE = -1;
	        break;
    	}
	}
    return( iSOKU_JUDGE);
}



//---------------------------------------------------------------------------
void __fastcall TForm7::MEdt_SOKU_DATEEnter(TObject *Sender)
{
    bCALENDER = true;
}


//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��@�F���݂�KSD02����͂��łɊO���ꂽ���荀�ڂ𕜊�������ׁA
//                ���݂�KSD02�ɂ͓o�^����Ă��Ȃ����荀�ڂ�KSD11����擾���A
//                �R���{�{�b�N�X�ɓo�^���܂��B
//
//  �@�\����
//    �R���{�{�b�N�X��pCBO_SELECT�ɍ��ړo�^���邾���ŁA�Ȍ�̏����͒����ė��܂��B�i�c���j
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
//
//---------------------------------------------------------------------------
int __fastcall TForm7::GetSOKUTEI_KOMK_MORE(int iCBO_INDEX)
{
	AnsiString sLot;
	AnsiString sBuf;
	AnsiString sKOMK_NM;
	AnsiString sKOMK_SUB;
	AnsiString sTANI;
    bool bFind;
    int i2;
	double dMIN,dMAX;
    AnsiString sLot_Where;


	//�����\�ő��肳�ꂽ���b�g�̓ǂݍ���
	sLot = "";
    for(i2 = 0; i2 < SGr_vRIRE_SYUKA->ColCount;i2++) {
		if(SGr_vRIRE_SYUKA->Cells[i2][0].Length() !=0) {
			sLot += "'" + SGr_vRIRE_SYUKA->Cells[i2][0] + "',";
		}
	}
    for(i2 = 0; i2 < SGr_vSOKU_SYUKA->ColCount;i2++) {
		if(SGr_vSOKU_SYUKA->Cells[i2][0].Length() !=0) {
			sLot += "'" + SGr_vSOKU_SYUKA->Cells[i2][0] + "',";
		}
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi��
    // ���b�g��������������
    sLot_Where = "";
    for(i2 = 0; i2 < SGr_vRIRE_SYUKA->ColCount;i2++) {
		if(SGr_vRIRE_SYUKA->Cells[i2][0].Length() !=0) {
            sLot_Where += "( LOTNO='" + SGr_vRIRE_SYUKA->Cells[i2][0] + "' AND ";
            sLot_Where += " HINBAN='" + SGr_vRIRE_SYUKA->Cells[i2][1] + "') OR ";
		}
	}
    for(i2 = 0; i2 < SGr_vSOKU_SYUKA->ColCount;i2++) {
		if(SGr_vSOKU_SYUKA->Cells[i2][0].Length() !=0) {
            sLot_Where += "( LOTNO='" + SGr_vSOKU_SYUKA->Cells[i2][0] + "' AND ";
            sLot_Where += " HINBAN='" + SGr_vSOKU_SYUKA->Cells[i2][1] + "') OR ";
		}
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi��

	sBuf  = "SELECT *";
	sBuf += " FROM KSD11";
	sBuf += " WHERE DTKSHIN = '" + Pnl_HINBAN->Caption + "'";
	//sBuf += " AND LOTNO IN (" + sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";
	sBuf += " AND NOT(";
	for(i2 = 0;i2 < iCBO_INDEX;i2++)
	{
		if( i2 > 0 )	sBuf += " or";
		sBuf += " (";
		sBuf += " UNQ_NO=" + AnsiString(pCBO_SELECT[i2].UNQ_NO);
		sBuf += " AND KOMK_NO=" + AnsiString(pCBO_SELECT[i2].KOMK_NO);
		sBuf += " )";
	}
	sBuf += " )";
	sBuf += " ORDER BY LOTNO, BNKT_UNQ_NO";

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;
	
	while( Query1->Eof == false ) {

        // �����������R�[�h����[���荀�ږ���]��[���荀�ڃT�u����]���擾���܂�
        // ���ɓo�^����Ă���R���{�{�b�N�X�Ƃ̔�r�p
        sKOMK_NM  = "";
        sKOMK_SUB = "";
        sTANI     = "";
		if( VarIsNull(Query1->FieldValues["KOMK_NM"])!=true)	{
			sKOMK_NM = Query1->FieldValues["KOMK_NM"];
		}
		if( VarIsNull(Query1->FieldValues["KOMK_SUB"])!=true)	{
			sKOMK_SUB = Query1->FieldValues["KOMK_SUB"];
		}
		if( VarIsNull(Query1->FieldValues["TANI"])!=true)	{
			sTANI = Query1->FieldValues["TANI"];
		}
        sBuf = sKOMK_NM + sKOMK_SUB + " " + sTANI;

        // ���݂̃R���{�{�b�N�X�ɖ��o�^�̏ꍇ�����A�ǉ��ΏۂƂ��܂�
        bFind = false;
		for(i2 = 0;i2 < iCBO_INDEX;i2++) {
		    if( Cbo_KOMK_NM->Items->Strings[i2] == sBuf )	bFind = true;
		}

        // ���݂̃R���{�{�b�N�X�ɖ��o�^�̏ꍇ�����A�ǉ��ΏۂƂ��܂�
        if( !bFind ){
            strcpy(pCBO_SELECT[iCBO_INDEX].DTKSHIN		, "");
            if( VarIsNull(Query1->FieldValues["DTKSHIN"])!=true)	{
				sBuf = Query1->FieldValues["DTKSHIN"];
				strcpy(pCBO_SELECT[iCBO_INDEX].DTKSHIN		, sBuf.c_str());
	    }
            strcpy(pCBO_SELECT[iCBO_INDEX].UNQ_NO		, "");
			if( VarIsNull(Query1->FieldValues["UNQ_NO"])!=true)		{
				sBuf = Query1->FieldValues["UNQ_NO"];
				strcpy(pCBO_SELECT[iCBO_INDEX].UNQ_NO		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_NO		, "");
			if( VarIsNull(Query1->FieldValues["KOMK_NO"])!=true)	{
				sBuf = Query1->FieldValues["KOMK_NO"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_NO		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_NM		, "");
			if( VarIsNull(Query1->FieldValues["KOMK_NM"])!=true)	{
				sBuf = Query1->FieldValues["KOMK_NM"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_NM		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_ENG		, "");
			if( VarIsNull(Query1->FieldValues["KOMK_ENG"])!=true)	{
				sBuf = Query1->FieldValues["KOMK_ENG"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_ENG		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_SUB		, "");
			if( VarIsNull(Query1->FieldValues["KOMK_SUB"])!=true)	{
				sBuf = Query1->FieldValues["KOMK_SUB"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_SUB		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_SUB_ENG		, "");
			if( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"])!=true){
				sBuf = Query1->FieldValues["KOMK_SUB_ENG"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KOMK_SUB_ENG	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKI_NO		, "");
			if( VarIsNull(Query1->FieldValues["KIKI_NO"])!=true)	{
				sBuf = Query1->FieldValues["KIKI_NO"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKI_NO		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKI_NM		, "");
			if( VarIsNull(Query1->FieldValues["KIKI_NM"])!=true)	{
				sBuf = Query1->FieldValues["KIKI_NM"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKI_NM		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].TANI		, "");
			if( VarIsNull(Query1->FieldValues["TANI"])!=true)	{
				sBuf = Query1->FieldValues["TANI"];
				strcpy(pCBO_SELECT[iCBO_INDEX].TANI			, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_TYPE		, "");
			if( VarIsNull(Query1->FieldValues["KIKA_TYPE"])!=true)	{
				sBuf = Query1->FieldValues["KIKA_TYPE"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_TYPE	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_KIND		, "");
			if( VarIsNull(Query1->FieldValues["KIKA_KIND"])!=true)	{
				sBuf = Query1->FieldValues["KIKA_KIND"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_KIND	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_DECI		, "");
			if( VarIsNull(Query1->FieldValues["KIKA_DECI"])!=true)	{
				sBuf = Query1->FieldValues["KIKA_DECI"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_DECI	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_NUM1		, "");
			if( VarIsNull(Query1->FieldValues["KIKA_NUM1"])!=true)	{
				sBuf = Query1->FieldValues["KIKA_NUM1"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_NUM1	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_NUM2		, "");
			if( VarIsNull(Query1->FieldValues["KIKA_NUM2"])!=true)	{
				sBuf = Query1->FieldValues["KIKA_NUM2"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_NUM2	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_NUM3		, "");
			if( VarIsNull(Query1->FieldValues["KIKA_NUM3"])!=true)	{
				sBuf = Query1->FieldValues["KIKA_NUM3"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_NUM3	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_STR		, "");
			if( VarIsNull(Query1->FieldValues["KIKA_STR"])!=true)	{
				sBuf = Query1->FieldValues["KIKA_STR"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_STR		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_SUB1		, "");
			if( VarIsNull(Query1->FieldValues["KIKA_SUB1"])!=true)	{
				sBuf = Query1->FieldValues["KIKA_SUB1"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_SUB1	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_SUB2		, "");
			if( VarIsNull(Query1->FieldValues["KIKA_SUB2"])!=true)	{
				sBuf = Query1->FieldValues["KIKA_SUB2"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_SUB2	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_SUB3		, "");
			if( VarIsNull(Query1->FieldValues["KIKA_SUB3"])!=true)	{
				sBuf = Query1->FieldValues["KIKA_SUB3"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_SUB3	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].SOKU_SU		, "");
			if( VarIsNull(Query1->FieldValues["SOKU_SU"])!=true)	{
				sBuf = Query1->FieldValues["SOKU_SU"];
				strcpy(pCBO_SELECT[iCBO_INDEX].SOKU_SU		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].SOKU_FLG		, "");
			if( VarIsNull(Query1->FieldValues["SOKU_FLG"])!=true)	{
				sBuf = Query1->FieldValues["SOKU_FLG"];
				strcpy(pCBO_SELECT[iCBO_INDEX].SOKU_FLG		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].TOKU_FLG		, "");
			if( VarIsNull(Query1->FieldValues["TOKU_FLG"])!=true)	{
				sBuf = Query1->FieldValues["TOKU_FLG"];
				strcpy(pCBO_SELECT[iCBO_INDEX].TOKU_FLG		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_PRT		, "");
			if( VarIsNull(Query1->FieldValues["KIKA_PRT"])!=true)	{
				sBuf = Query1->FieldValues["KIKA_PRT"];
				strcpy(pCBO_SELECT[iCBO_INDEX].KIKA_PRT		, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].VALUE_TYPE		, "");
			if( VarIsNull(Query1->FieldValues["VALUE_TYPE"])!=true)	{
				sBuf = Query1->FieldValues["VALUE_TYPE"];
				strcpy(pCBO_SELECT[iCBO_INDEX].VALUE_TYPE	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].VALUE_DECI		, "");
			if( VarIsNull(Query1->FieldValues["VALUE_DECI"])!=true)	{
				sBuf = Query1->FieldValues["VALUE_DECI"];
				strcpy(pCBO_SELECT[iCBO_INDEX].VALUE_DECI	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].VALUE_TYPE		, "");
			if( VarIsNull(Query1->FieldValues["VALUE_TYPE"])!=true)	{
				sBuf = Query1->FieldValues["VALUE_TYPE"];
				strcpy(pCBO_SELECT[iCBO_INDEX].VALUE_TYPE	, sBuf.c_str());
			}
            strcpy(pCBO_SELECT[iCBO_INDEX].VALUE_DECI		, "");
			if( VarIsNull(Query1->FieldValues["VALUE_DECI"])!=true)	{
				sBuf = Query1->FieldValues["VALUE_DECI"];
				strcpy(pCBO_SELECT[iCBO_INDEX].VALUE_DECI	, sBuf.c_str());
			}

			// ��L�Ŏ擾�����K�i�l����ő�l�ƍŏ��l���擾���܂�
			Form7->GetKIKAKU2(iCBO_INDEX,&dMAX,&dMIN);
			pCBO_SELECT[iCBO_INDEX].MAX 				= dMAX ;
			pCBO_SELECT[iCBO_INDEX].MIN 				= dMIN ;
			
			//���ڑI���R���{�ւ̏�������
			Cbo_KOMK_NM->Items->Insert(iCBO_INDEX,AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_NM)+AnsiString(pCBO_SELECT[iCBO_INDEX].KOMK_SUB)+" "+AnsiString(pCBO_SELECT[iCBO_INDEX].TANI));
			iCBO_INDEX ++;

		}

		Query1->Next();
	}

	// Close Query
	Query1->Close();


    // �ǉ���̃R���{�{�b�N�X������߂��܂�
    return( iCBO_INDEX );
}



//---------------------------------------------------------------------------
//
//  �T�v
//    ����֐��@�F�K�i���Z�o���܂��B�ipCBO_SELECT�̎w�肳�ꂽ�K�i�l����쐬���܂��j
//
//  �@�\����
//    ���̃Z���Ɍ��������K�i�lMAX�AMIN�̎擾���s���B
//
//  �p�����^����
//    int iIndex    �F�ǂ̍��ڂ��ΏۂȂ̂��������C���f�b�N�X�ł��B
//  �@double *dMAX  �F�K�iMAX�l���������܂��B
//  �@double *dMIN  �F�K�iMIN�l���������܂��B
//
//  �߂�l
//    �Ȃ��B
//
//  ���l
//    �Ȃ��B
//
//
//---------------------------------------------------------------------------
void __fastcall TForm7::GetKIKAKU2(int iIndex,double *dMAX,double *dMIN)
{
	double dSWAP;

	if( AnsiString(pCBO_SELECT[iIndex].KIKA_TYPE).ToIntDef(0) != 3 )
	{
		*dMAX = Form1->ConvDoubleDefD(pCBO_SELECT[iIndex].KIKA_NUM1,0.0);
		*dMIN = Form1->ConvDoubleDefD(pCBO_SELECT[iIndex].KIKA_NUM1,0.0);
		switch(AnsiString(pCBO_SELECT[iIndex].KIKA_TYPE).ToIntDef(0))
		{
		case 1:
			switch(AnsiString(pCBO_SELECT[iIndex].KIKA_KIND).ToIntDef(0))
			{
			case 1:
				*dMAX = Form1->ConvDoubleDefD(pCBO_SELECT[iIndex].KIKA_NUM2,0.0);
				*dMIN = Form1->ConvDoubleDefD(pCBO_SELECT[iIndex].KIKA_NUM1,0.0);
				break;
			case 2:
				*dMAX = Form1->ConvDoubleDefD(pCBO_SELECT[iIndex].KIKA_NUM2,0.0);
				break;
			case 3:
				break;
			default:
				break;
			}
			break;
		case 2:
			switch(AnsiString(pCBO_SELECT[iIndex].KIKA_KIND).ToIntDef(0))
			{
			case 1:
				*dMAX += Form1->ConvDoubleDefD(pCBO_SELECT[iIndex].KIKA_NUM2,0.0);
				*dMIN += Form1->ConvDoubleDefD(pCBO_SELECT[iIndex].KIKA_NUM3,0.0);
				break;
			case 2:
				*dMAX += Form1->ConvDoubleDefD(pCBO_SELECT[iIndex].KIKA_NUM2,0.0);
				break;
			case 3:
				*dMIN += Form1->ConvDoubleDefD(pCBO_SELECT[iIndex].KIKA_NUM3,0.0);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		if( *dMAX < *dMIN )
		{
			dSWAP = *dMIN;
			*dMIN = *dMAX;
			*dMAX = dSWAP;
		}
	}

}


