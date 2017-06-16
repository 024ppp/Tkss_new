//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "KOUTEI.h"
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
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#pragma link "PERFGRAP"
#pragma link "NumberEdit"
TForm1 *Form1;
*/
extern	HANDLE 	hInfoGlaph;
extern 	KSM02_DATA	*pInfoGlaph;
extern KIKAKU KIKAKU_MOJI;
double dSiguma,dSigumaAve,dSigumaSum,dSigumaNum;


//---------------------------------------------------------------------------

int __fastcall TForm1::Get_GRAPHSTART_Info(int Row,int Col,int GridNo)
{
	int i1,i2;
	int iGraphRow;
	extern KSM02_DATA *pORDATA;
	extern KSM02_DATA *pSOZAI_OR_DATA;

    // �������̊m��
    hInfoGlaph = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * 1 );
    if( hInfoGlaph == NULL ){
        SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
        SBr1->Update();
        Beep();
        return(1);
    }
    pInfoGlaph = (struct KSM02_DATA *)GlobalLock(hInfoGlaph);
    if( hInfoGlaph == NULL ){
        SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
        SBr1->Update();
        Beep();
        return(1);
    }
	switch(GridNo)
	{
	case 1:
	case 2:
		i2 = 0;
		for(i1 = 0; i1 < iOrCount ; i1++)
		{
			i2 += AnsiString(pORDATA[i1].SOKU_SU).ToInt();
			if( Row <= i2 )
			{
				if( GridNo == 1 )
				{
					Form1->Pnl_skInfo_vLOTBNG2->Caption = Form1->SGr_tSOKU->Cells[Col][0];
				}
				else
				{
					Form1->Pnl_skInfo_vLOTBNG2->Caption = Form1->SGr_tRIRE->Cells[Col][0];
				}
				Form1->Pnl_skInfo_vKENSA2->Caption = pORDATA[i1].KOMK_NM;
				Form1->Pnl_skInfo_vKIKI2->Caption = pORDATA[i1].KIKI_NM;
				iGraphRow = i2 - AnsiString(pORDATA[i1].SOKU_SU).ToInt();
                strcpy(pInfoGlaph[0].KOMK_NM	,pORDATA[i1].KOMK_NM);
                strcpy(pInfoGlaph[0].KOMK_NO	,pORDATA[i1].KOMK_NO);
                strcpy(pInfoGlaph[0].KIKI_NO	,pORDATA[i1].KIKI_NO);
				strcpy(pInfoGlaph[0].KIKI_NM	,pORDATA[i1].KIKI_NM);
				strcpy(pInfoGlaph[0].SOKU_SU	,pORDATA[i1].SOKU_SU);
				strcpy(pInfoGlaph[0].KIKA_TYPE	,pORDATA[i1].KIKA_TYPE);
				strcpy(pInfoGlaph[0].KIKA_KIND 	,pORDATA[i1].KIKA_KIND);
				strcpy(pInfoGlaph[0].KIKA_DECI	,pORDATA[i1].KIKA_DECI);
				strcpy(pInfoGlaph[0].KIKA_NUM1	,pORDATA[i1].KIKA_NUM1);
				strcpy(pInfoGlaph[0].KIKA_NUM2	,pORDATA[i1].KIKA_NUM2);
				strcpy(pInfoGlaph[0].KIKA_NUM3	,pORDATA[i1].KIKA_NUM3);
				Get_KIKAKU();
                		Form1->Lab_skInfo_Kikaku2->Caption = KIKAKU_MOJI.HANI;
				Form1->Lab_skInfo_KIKAKU2UP->Left = Form1->Lab_skInfo_Kikaku2->Width+Form1->Lab_skInfo_Kikaku2->Left;
                		Form1->Lab_skInfo_KIKAKU2UP->Caption = KIKAKU_MOJI.UPLIMIT;
				Form1->Lab_skInfo_KIKAKU2LOW->Left = Form1->Lab_skInfo_Kikaku2->Width+Form1->Lab_skInfo_Kikaku2->Left;
                		Form1->Lab_skInfo_KIKAKU2LOW->Caption = KIKAKU_MOJI.LOLIMIT;
				break;
			}
		}
		break;
	case 3:
	case 4:
		i2 = 0;
		for(i1 = 0; i1 < iOrCount ; i1++)
		{
			i2 += AnsiString(pSOZAI_OR_DATA[i1].SOKU_SU).ToInt();
			if( Row <= i2 )
			{
				if( GridNo == 3 )
				{
					Form1->Pnl_skInfo_vLOTBNG1->Caption = Form1->SGr_tSOKU->Cells[Col][0];
				}
				else
				{
					Form1->Pnl_skInfo_vLOTBNG1->Caption = Form1->SGr_tRIRE->Cells[Col][0];
				}
				Form1->Pnl_skInfo_vKENSA1->Caption = pSOZAI_OR_DATA[i1].KOMK_NM;
				Form1->Pnl_skInfo_vKIKI1->Caption = pSOZAI_OR_DATA[i1].KIKI_NM;
				iGraphRow = i2 - AnsiString(pORDATA[i1].SOKU_SU).ToInt();
                strcpy(pInfoGlaph[0].KOMK_NM	,pSOZAI_OR_DATA[i1].KOMK_NM);
                strcpy(pInfoGlaph[0].KOMK_NO	,pSOZAI_OR_DATA[i1].KOMK_NO);
                strcpy(pInfoGlaph[0].KIKI_NO	,pSOZAI_OR_DATA[i1].KIKI_NO);
				strcpy(pInfoGlaph[0].KIKI_NM	,pSOZAI_OR_DATA[i1].KIKI_NM);
				strcpy(pInfoGlaph[0].SOKU_SU	,pSOZAI_OR_DATA[i1].SOKU_SU);
				strcpy(pInfoGlaph[0].KIKA_TYPE	,pSOZAI_OR_DATA[i1].KIKA_TYPE);
				strcpy(pInfoGlaph[0].KIKA_KIND	,pSOZAI_OR_DATA[i1].KIKA_KIND);
				strcpy(pInfoGlaph[0].KIKA_DECI	,pSOZAI_OR_DATA[i1].KIKA_DECI);
				strcpy(pInfoGlaph[0].KIKA_NUM1	,pSOZAI_OR_DATA[i1].KIKA_NUM1);
				strcpy(pInfoGlaph[0].KIKA_NUM2	,pSOZAI_OR_DATA[i1].KIKA_NUM2);
				strcpy(pInfoGlaph[0].KIKA_NUM3	,pSOZAI_OR_DATA[i1].KIKA_NUM3);
				Get_KIKAKU();
				Form1->Lab_skInfo_Kikaku1->Caption = KIKAKU_MOJI.HANI;

				Form1->Lab_skInfo_KIKAKU1UP->Left = Form1->Lab_skInfo_Kikaku1->Width+Form1->Lab_skInfo_Kikaku1->Left;
                		Form1->Lab_skInfo_KIKAKU1UP->Caption = KIKAKU_MOJI.UPLIMIT;
				Form1->Lab_skInfo_KIKAKU1LOW->Left = Form1->Lab_skInfo_Kikaku1->Width+Form1->Lab_skInfo_Kikaku1->Left;
                		Form1->Lab_skInfo_KIKAKU1LOW->Caption = KIKAKU_MOJI.LOLIMIT;

				break;
			}
		}
		break;
	default:
		break;
	}
	return( iGraphRow );
}
//----------------------------------------------------------------
void __fastcall TForm1::Get_GRAPHLOT(int iGraphRow,int iGraphCol,int GridNo)
{
//�`��Ώۂ̓J�[�\�������郍�b�g1��+�ߋ�9���̌v10���b�g�i�d�l�ɂ�葝����\������j
//�������Ă��Ȃ����b�g�͔����čX�ɉߋ��ɂ����̂ڂ�̂ŘA�����Ă���Ƃ͌���Ȃ�
//�O���b�h�A�h���X�i�o�׌����@�{���F1�A�����F2�@�@�f�ތ����@�{���F3�A�����F4�j
	int i1,i2,iRes;
	int iRow,iCol;
    int nGridAddress;
	int iLotMax;
	double d1,d2;
	double dSum,dAve,dMax,dMin;
	double dGMax,dGMin;
	int iNCnt;
	AnsiString sBuf;
    bool bLot,bError,bGrid;	//bLot:�L�����b�g,bError:���l�ȊO,bGrid:�܂�����Grid�����邩
	bool bFirstNum;
	GRAPHADDRESS GraphLotAddress[10];
   	double dSigumaRes[200];
	nGridAddress = GridNo;
    	bGrid = true;
	iCol = iGraphCol;
//�L�����b�g�i�v���ς݁j�̒��o
	for(i1 = 0; i1 < 10; i1++)
	{
		if(!bGrid) break;
    		bLot = false;
		bError = false;
		switch(nGridAddress)
		{
		case 1:
			for(iRow = 0; iRow < AnsiString(pInfoGlaph[0].SOKU_SU).ToInt();iRow ++)
			{
            	sBuf = SGr_vSOKU_SYUKA->Cells[iCol][iGraphRow+iRow+1].Trim();
				if(sBuf.Length()!=0)
				{
                	try{
						d1 = FormatFloat(sBuf,0.00).ToDouble();
					}
					catch(...){
                		bError = true;
					}
					if( !bError)
					{
                		bLot = true;
						GraphLotAddress[i1].GRID = nGridAddress;
						GraphLotAddress[i1].COL = iCol;
						GraphLotAddress[i1].LOTNAME = SGr_tSOKU->Cells[iCol][0];
					}
				}
                if(bLot == true) break;
			}
			iCol --;
			if(iCol < 0 )		//�ΏۃO���b�h�������Ȃ���
			{
				nGridAddress = 2;
				iCol = Form1->SGr_vRIRE_SYUKA->ColCount-1;
			}
			break;
		case 2:
			for(iRow = 0; iRow < AnsiString(pInfoGlaph[0].SOKU_SU).ToInt();iRow ++)
			{
            	sBuf = SGr_vRIRE_SYUKA->Cells[iCol][iGraphRow+iRow+1].Trim();
				if(sBuf.Length()!=0)
				{
                	try{
                    	d1 = FormatFloat(sBuf,0.00).ToDouble();
                    }
                    catch(...){
                    	bError = true;
                    }
                    if( !bError)
                    {
                    	bLot = true;
                        GraphLotAddress[i1].GRID = nGridAddress;
                        GraphLotAddress[i1].COL = iCol;
                        GraphLotAddress[i1].LOTNAME = SGr_tRIRE->Cells[iCol][0];
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
			for(iRow = 0; iRow < AnsiString(pInfoGlaph[0].SOKU_SU).ToInt();iRow ++)
			{
            	sBuf = SGr_vSOKU_SOZAI->Cells[iCol][iGraphRow+iRow+1].Trim();
				if(sBuf.Length()!=0)
				{
                	try{
						d1 = FormatFloat(sBuf,0.00).ToDouble();
					}
					catch(...){
                		bError = true;
					}
					if( !bError)
					{
                		bLot = true;
						GraphLotAddress[i1].GRID = nGridAddress;
						GraphLotAddress[i1].COL = iCol;
						GraphLotAddress[i1].LOTNAME = SGr_tSOKU->Cells[iCol][0];
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
			for(iRow = 0; iRow < AnsiString(pInfoGlaph[0].SOKU_SU).ToInt();iRow ++)
			{
            	sBuf = SGr_vRIRE_SOZAI->Cells[iCol][iGraphRow+iRow+1].Trim();
				if(sBuf.Length()!=0)
				{
                	try{
						d1 = FormatFloat(sBuf,0.00).ToDouble();
					}
					catch(...){
                		bError = true;
					}
					if( !bError)
					{
                		bLot = true;
						GraphLotAddress[i1].GRID = nGridAddress;
						GraphLotAddress[i1].COL = iCol;
						GraphLotAddress[i1].LOTNAME = SGr_tRIRE->Cells[iCol][0];
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
	for(i1 = 0;i1 < iLotMax;i1++)
	{
		dSum = 0;
		iNCnt = 0;
		bFirstNum = true;
        for(iRow = 0; iRow < AnsiString(pInfoGlaph[0].SOKU_SU).ToInt();iRow ++)
        {
			switch(GraphLotAddress[i1].GRID)
			{
        	case 1:
            	sBuf = SGr_vSOKU_SYUKA->Cells[GraphLotAddress[i1].COL][iGraphRow+iRow+1].Trim();
				if(sBuf.Length()!=0)
				{
                	try{
						d1 = sBuf.ToDouble();
					}
					catch(...){
                		bError = true;
					}
					if( !bError)
					{
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
				if(sBuf.Length()!=0)
				{
                	try{
						d1 = sBuf.ToDouble();
					}
					catch(...){
                		bError = true;
					}
					if( !bError)
					{
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
        	case 3:
            	sBuf = SGr_vSOKU_SOZAI->Cells[GraphLotAddress[i1].COL][iGraphRow+iRow+1].Trim();
				if(sBuf.Length()!=0)
				{
                	try{
						d1 = sBuf.ToDouble();
					}
					catch(...){
                		bError = true;
					}
					if( !bError)
					{
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
        	case 4:
            	sBuf = SGr_vRIRE_SOZAI->Cells[GraphLotAddress[i1].COL][iGraphRow+iRow+1].Trim();
				if(sBuf.Length()!=0)
				{
                	try{
						d1 = sBuf.ToDouble();
					}
					catch(...){
                		bError = true;
					}
					if( !bError)
					{
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
//�V�O�}�̎Z�o
	dSiguma = 0;
	if( dSigumaNum > 1 )		//2���ȏ�Ώۃ��b�g�����邩
	{
    	dSigumaAve = dSigumaSum / dSigumaNum;
    	for(i1 = 0;i1 < dSigumaNum;i1++)
		{
        	dSiguma += (dSigumaRes[ i1 ]-dSigumaAve)*(dSigumaRes[ i1 ]-dSigumaAve);
		}
		dSiguma = sqrt(dSiguma / (dSigumaNum-1));
	}
	sBuf = FormatFloat("0.00",dSiguma);
	switch(GraphLotAddress[0].GRID)
	{
    case 1:
	case 2:
		Form1->pnlSYUKASiguma->Caption = sBuf;
		break;
	case 3:
	case 4:
		Form1->pnlSOZAISiguma->Caption = sBuf;
		break;
    default:
		break;
	}
//�O���t�`��i���j
	int x,y;
   	double MaxY,MinY;                             //Y���@�ǂݍ��񂾃f�[�^�̒��̍ő�l�A�ŏ��l
    double ScaleMax,ScaleMin,ScaleVal, ScaleMid;   //�ڐ���̍ő�l�A�ŏ��l�A�Ԋu
	double dMaxMinHeight,dMaxMin;
	double dOnePitch;
    int ItemWidth;
    int CharWidth;                                //Y�����W�l��`�悷�邽�߂̗]��
    int CharHeight;                               //X�����W�l��`�悷�邽�߂̗]��
    int FontHeight;
	int ImageH,ImageW;                            //�C���[�W�̍����A��

    ImgGlaphSYUKA->Canvas->Pen->Color = clBlack;
    ImgGlaphSYUKA->Canvas->Pen->Style = bsSolid;
    ImgGlaphSYUKA->Canvas->Pen->Width = 1;       //���̑���
    ImgGlaphSYUKA->Canvas->Font->Size = 7;       //�����̃T�C�Y
	ImgGlaphSYUKA->Canvas->Brush->Color = clWhite;
	ImgGlaphSYUKA->Canvas->Rectangle(0,0,ImgGlaphSYUKA->Width,ImgGlaphSYUKA->Height);

//�O���t�`��̍ۂɎg�p����萔�̐ݒ�
    CharWidth 	= ImgGlaphSYUKA->Canvas->Font->Height * 3;   //���[��Y���̊Ԃ̗]��
    CharHeight 	= ImgGlaphSYUKA->Canvas->Font->Height * 2;  //���[��X���̊Ԃ̗]��
    FontHeight 	= ImgGlaphSYUKA->Canvas->Font->Height;      //�����̍���
	ImageH = ImgGlaphSYUKA->Height - 2* CharHeight;
    ImageW = ImgGlaphSYUKA->Width - CharWidth;

//�O���t�̕`��
    ImgGlaphSYUKA->Canvas->Brush->Color =clWhite;
    ImgGlaphSYUKA->Canvas->Pen->Color =clGray;
    ImgGlaphSOZAI->Canvas->Brush->Color =clWhite;
    ImgGlaphSOZAI->Canvas->Pen->Color =clGray;
    for(i1=0;i1<10;i1++)
    {
		switch(GridNo)
		{
		case 1:
		case 2:
//�O���t�O���b�h�̕\��
			if( i1 == 1 || i1 == 8)
			{
        		ImgGlaphSYUKA->Canvas->Pen->Color = clRed;
			}
			else
			{
        		ImgGlaphSYUKA->Canvas->Pen->Color = clGray;
			}
			ImgGlaphSYUKA->Canvas->Rectangle(0,(i1)*(ImgGlaphSYUKA->Height/9)-1,ImgGlaphSYUKA->Width,i1*(ImgGlaphSYUKA->Height/9));
			break;
		case 3:
		case 4:
//�O���t�O���b�h�̕\��
			if( i1 == 1 || i1 == 8)
			{
        		ImgGlaphSOZAI->Canvas->Pen->Color = clRed;
			}
			else
			{
        		ImgGlaphSOZAI->Canvas->Pen->Color = clGray;
			}
			ImgGlaphSOZAI->Canvas->Rectangle(0,(i1)*(ImgGlaphSOZAI->Height/9)-1,ImgGlaphSOZAI->Width,i1*(ImgGlaphSOZAI->Height/9));
			break;
		default:
			break;
		}
    }
	dMaxMinHeight = (ImgGlaphSYUKA->Height/9)*8 - (ImgGlaphSYUKA->Height/9);
//    ImgGlaphSYUKA->Canvas->Rectangle(20,0,21,ImgGlaphSYUKA->Height);
	for(i1 = 0;i1 < 10;i1++)
	{
		x =	((ImageW) / 12) * (9-i1)+ImgGlaphSYUKA->Canvas->Font->Size+20;
		ImgGlaphSYUKA->Canvas->Rectangle(x+10,0,x+11,ImgGlaphSYUKA->Height);
	}
//�K�i�̕\��
	ImgGlaphSYUKA->Canvas->Font->Size = 9;
	switch(AnsiString(pInfoGlaph[0].KIKA_TYPE).ToInt())
	{
	case 1:	//�͈͎w��̏ꍇ
    	switch(AnsiString(pInfoGlaph[0].KIKA_KIND).ToInt())
		{
        case 1:
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM2);
			try{
				dGMax = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMin = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-5,AnsiString(pInfoGlaph[0].KIKA_NUM2));		//���
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-5,AnsiString(pInfoGlaph[0].KIKA_NUM1));     //����
			dMaxMin = FormatFloat(AnsiString(pInfoGlaph[0].KIKA_NUM2),0.00) - FormatFloat(AnsiString(pInfoGlaph[0].KIKA_NUM1),0.00);
			break;
		case 2:
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM2);
			try{
				dGMax = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			dGMin = GraphLotAddress[0].MIN;
			for(i1=0;i1<iLotMax;i1++)
			{
				if(dGMin > GraphLotAddress[i1].MIN) dGMin = GraphLotAddress[i1].MIN;
			}
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-5,AnsiString(pInfoGlaph[0].KIKA_NUM2));		//���
			dMaxMin = FormatFloat(AnsiString(pInfoGlaph[0].KIKA_NUM2),0.00) - dGMin;
			break;
        case 3:
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMin = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			dGMax = GraphLotAddress[0].MAX;
			for(i1=0;i1<iLotMax;i1++)
			{
				if(dGMax < GraphLotAddress[i1].MAX) dGMax = GraphLotAddress[i1].MAX;
			}
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-5,AnsiString(pInfoGlaph[0].KIKA_NUM1));		//����
			dMaxMin = 0;
			break;
		default:
			break;
		}
        break;
	case 2:
		switch(AnsiString(pInfoGlaph[0].KIKA_KIND).ToInt())
		{
		case 1:
//����l�m��
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMax = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM2);
			try{
				dGMax += sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
//�����l�m��
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMin = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM3);
			try{
				dGMin += sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			if(dGMax< dGMin)
			{
				d1 = dGMax;
				dGMax = dGMin;
				dGMin = d1;
			}
			sBuf = dGMax;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//���
			sBuf = dGMin;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//����
            break;
		case 2:
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMax = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM2);
			try{
				dGMax += sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMin = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			if(dGMax< dGMin)
			{
				d1 = dGMax;
				dGMax = dGMin;
				dGMin = d1;
			}
			sBuf = dGMax;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//���
			sBuf = dGMin;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//����
            break;
		case 3:
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMax = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMin = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM3);
			try{
				dGMin += sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
				return;
            }
			if(dGMax< dGMin)
			{
				d1 = dGMax;
				dGMax = dGMin;
				dGMin = d1;
			}
			sBuf = dGMax;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//���
			sBuf = dGMin;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//����
            break;
		default:
			break;
		}
        break;
	default:
		break;
	}
	ImgGlaphSYUKA->Canvas->Font->Size = 7;
	if(fabs(dGMax) < 0.01) dGMax = 0.0;
	if(fabs(dGMin) < 0.01) dGMin = 0.0;
	if(dGMax-dGMin == 0.0)
	{
		ImgGlaphSYUKA->Canvas->TextOutA(50,70,"�K�i����͂��ĉ�����!!");
		return;
	}
	switch(GridNo)
	{
    case 1:
	case 2:
		dOnePitch = dMaxMinHeight * 1/(dGMax-dGMin);
		for(i1 = 0;i1 < iLotMax;i1++)
		{
			x =	((ImageW) / 12) * (9-i1)+ImgGlaphSYUKA->Canvas->Font->Size+20;
			ImgGlaphSYUKA->Canvas->TextOutA(x,114,GraphLotAddress[i1].LOTNAME);
//�͈͂̑уO���t�̕\��
			ImgGlaphSYUKA->Canvas->Pen->Color = clLime;
			ImgGlaphSYUKA->Canvas->Brush->Color = clLime;
			d1 = GraphLotAddress[i1].MIN * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			d2 = GraphLotAddress[i1].MAX * dOnePitch * -1;
			d2 = dGMax * dOnePitch + d2+((ImgGlaphSYUKA->Height/9)-1);
			ImgGlaphSYUKA->Canvas->Rectangle(x+7,d2,x+13,d1);
			ImgGlaphSYUKA->Canvas->Brush->Color = clWhite;
//���ϒl�̕\��
			ImgGlaphSYUKA->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].AVE * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			ImgGlaphSYUKA->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//�ő�l�̕\��
			ImgGlaphSYUKA->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].MAX * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			ImgGlaphSYUKA->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//�ŏ��l�̕\��
			ImgGlaphSYUKA->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].MIN * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			ImgGlaphSYUKA->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//PENCOLOR���f�t�H���g�ɖ߂�
			ImgGlaphSYUKA->Canvas->Pen->Color = clBlack;
			ImgGlaphSYUKA->Canvas->Brush->Color = clWhite;
		}
		break;
	case 3:
	case 4:
		dOnePitch = dMaxMinHeight * 1/(dGMax-dGMin);
		for(i1 = 0;i1 < iLotMax;i1++)
		{
			x =	((ImageW) / 12) * (9-i1)+ImgGlaphSYUKA->Canvas->Font->Size+20;
			ImgGlaphSOZAI->Canvas->TextOutA(x,114,GraphLotAddress[i1].LOTNAME);
//���ϒl�̕\��
			ImgGlaphSOZAI->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].AVE * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSOZAI->Height/9)-1);
			ImgGlaphSOZAI->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//�ő�l�̕\��
			ImgGlaphSOZAI->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].MAX * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSOZAI->Height/9)-1);
			ImgGlaphSOZAI->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//�ŏ��l�̕\��
			ImgGlaphSOZAI->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].MIN * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSOZAI->Height/9)-1);
			ImgGlaphSOZAI->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//PENCOLOR���f�t�H���g�ɖ߂�
			ImgGlaphSOZAI->Canvas->Pen->Color = clBlack;
		}
		break;
 	default:
		break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Get_KIKAKU(void)
{
    char cFormatBuf[20],c1[20],c2[10];
    AnsiString sBuf;

//�K�i�\���F�X
//�t�H�[�}�b�g�w��i��*.*���j
	sprintf(c1,"%0");
    sprintf(c2,"1.%df",AnsiString(pInfoGlaph[0].KIKA_DECI).ToInt());
    strcat(c1,c2);
//
	switch(AnsiString(pInfoGlaph[0].KIKA_TYPE).ToInt())
    {
    case 1:
    	switch(AnsiString(pInfoGlaph[0].KIKA_KIND).ToInt())
        {
        case 1:
        	sBuf = pInfoGlaph[0].KIKA_NUM1;
        	sBuf +=  "�`";
        	sBuf += pInfoGlaph[0].KIKA_NUM2;
        	KIKAKU_MOJI.HANI = sBuf;
        	break;
        case 2:
        	sBuf = pInfoGlaph[0].KIKA_NUM2 ;
        	KIKAKU_MOJI.HANI = sBuf +"�ȉ�";
        	break;
        case 3:
        	sBuf = pInfoGlaph[0].KIKA_NUM1 ;
        	KIKAKU_MOJI.HANI = sBuf +"�ȏ�";
        	break;
        default:
        	break;
        }
        KIKAKU_MOJI.UPLIMIT ="";
        KIKAKU_MOJI.LOLIMIT ="";
        break;
    case 2:
        sBuf = pInfoGlaph[0].KIKA_NUM1 ;
        KIKAKU_MOJI.HANI = sBuf;
        switch(AnsiString(pInfoGlaph[0].KIKA_KIND).ToInt())
        {
        case 1:
        	KIKAKU_MOJI.UPLIMIT = pInfoGlaph[0].KIKA_NUM2;
        	KIKAKU_MOJI.LOLIMIT = pInfoGlaph[0].KIKA_NUM3;
        	break;
        case 2:
        	KIKAKU_MOJI.UPLIMIT = pInfoGlaph[0].KIKA_NUM2;
        	KIKAKU_MOJI.LOLIMIT ="";
        	break;
        case 3:
        	KIKAKU_MOJI.UPLIMIT = "";
        	KIKAKU_MOJI.LOLIMIT = pInfoGlaph[0].KIKA_NUM3;
        	break;
        default:
        	break;
        }
        break;
    case 3:
    	KIKAKU_MOJI.HANI = pInfoGlaph[0].KIKA_STR;
        KIKAKU_MOJI.UPLIMIT ="";
        KIKAKU_MOJI.LOLIMIT ="";
        break;
    default:
    	break;
    }
}

