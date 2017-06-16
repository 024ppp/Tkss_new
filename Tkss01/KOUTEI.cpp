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

    // メモリの確保
    hInfoGlaph = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * 1 );
    if( hInfoGlaph == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return(1);
    }
    pInfoGlaph = (struct KSM02_DATA *)GlobalLock(hInfoGlaph);
    if( hInfoGlaph == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
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
//描画対象はカーソルがあるロット1件+過去9件の計10ロット（仕様により増える可能性あり）
//検査していないロットは抜いて更に過去にさかのぼるので連続しているとは限らない
//グリッドアドレス（出荷検査　本日：1、履歴：2　　素材検査　本日：3、履歴：4）
	int i1,i2,iRes;
	int iRow,iCol;
    int nGridAddress;
	int iLotMax;
	double d1,d2;
	double dSum,dAve,dMax,dMin;
	double dGMax,dGMin;
	int iNCnt;
	AnsiString sBuf;
    bool bLot,bError,bGrid;	//bLot:有効ロット,bError:数値以外,bGrid:まだ検索Gridがあるか
	bool bFirstNum;
	GRAPHADDRESS GraphLotAddress[10];
   	double dSigumaRes[200];
	nGridAddress = GridNo;
    	bGrid = true;
	iCol = iGraphCol;
//有効ロット（計測済み）の抽出
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
			if(iCol < 0 )		//対象グリッドが無くなった
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
			if(iCol < 0 )		//対象グリッドが無くなった
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
			if(iCol < 0 )		//対象グリッドが無くなった
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
			if(iCol < 0 )		//対象グリッドが無くなった
			{
				bGrid = false;
			}
			break;
		default:
			break;
		}
	}
	iLotMax = i1;
//有効ロットの中の個々のロットの最大／最小値／平均値抽出
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
//シグマの算出
	dSiguma = 0;
	if( dSigumaNum > 1 )		//2件以上対象ロットがあるか
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
//グラフ描画（仮）
	int x,y;
   	double MaxY,MinY;                             //Y軸　読み込んだデータの中の最大値、最小値
    double ScaleMax,ScaleMin,ScaleVal, ScaleMid;   //目盛りの最大値、最小値、間隔
	double dMaxMinHeight,dMaxMin;
	double dOnePitch;
    int ItemWidth;
    int CharWidth;                                //Y軸座標値を描画するための余白
    int CharHeight;                               //X軸座標値を描画するための余白
    int FontHeight;
	int ImageH,ImageW;                            //イメージの高さ、幅

    ImgGlaphSYUKA->Canvas->Pen->Color = clBlack;
    ImgGlaphSYUKA->Canvas->Pen->Style = bsSolid;
    ImgGlaphSYUKA->Canvas->Pen->Width = 1;       //線の太さ
    ImgGlaphSYUKA->Canvas->Font->Size = 7;       //文字のサイズ
	ImgGlaphSYUKA->Canvas->Brush->Color = clWhite;
	ImgGlaphSYUKA->Canvas->Rectangle(0,0,ImgGlaphSYUKA->Width,ImgGlaphSYUKA->Height);

//グラフ描画の際に使用する定数の設定
    CharWidth 	= ImgGlaphSYUKA->Canvas->Font->Height * 3;   //左端とY軸の間の余白
    CharHeight 	= ImgGlaphSYUKA->Canvas->Font->Height * 2;  //下端とX軸の間の余白
    FontHeight 	= ImgGlaphSYUKA->Canvas->Font->Height;      //文字の高さ
	ImageH = ImgGlaphSYUKA->Height - 2* CharHeight;
    ImageW = ImgGlaphSYUKA->Width - CharWidth;

//グラフの描画
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
//グラフグリッドの表示
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
//グラフグリッドの表示
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
//規格の表示
	ImgGlaphSYUKA->Canvas->Font->Size = 9;
	switch(AnsiString(pInfoGlaph[0].KIKA_TYPE).ToInt())
	{
	case 1:	//範囲指定の場合
    	switch(AnsiString(pInfoGlaph[0].KIKA_KIND).ToInt())
		{
        case 1:
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM2);
			try{
				dGMax = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMin = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-5,AnsiString(pInfoGlaph[0].KIKA_NUM2));		//上限
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-5,AnsiString(pInfoGlaph[0].KIKA_NUM1));     //下限
			dMaxMin = FormatFloat(AnsiString(pInfoGlaph[0].KIKA_NUM2),0.00) - FormatFloat(AnsiString(pInfoGlaph[0].KIKA_NUM1),0.00);
			break;
		case 2:
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM2);
			try{
				dGMax = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			dGMin = GraphLotAddress[0].MIN;
			for(i1=0;i1<iLotMax;i1++)
			{
				if(dGMin > GraphLotAddress[i1].MIN) dGMin = GraphLotAddress[i1].MIN;
			}
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-5,AnsiString(pInfoGlaph[0].KIKA_NUM2));		//上限
			dMaxMin = FormatFloat(AnsiString(pInfoGlaph[0].KIKA_NUM2),0.00) - dGMin;
			break;
        case 3:
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMin = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			dGMax = GraphLotAddress[0].MAX;
			for(i1=0;i1<iLotMax;i1++)
			{
				if(dGMax < GraphLotAddress[i1].MAX) dGMax = GraphLotAddress[i1].MAX;
			}
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-5,AnsiString(pInfoGlaph[0].KIKA_NUM1));		//下限
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
//上限値確定
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMax = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM2);
			try{
				dGMax += sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
//下限値確定
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMin = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM3);
			try{
				dGMin += sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			if(dGMax< dGMin)
			{
				d1 = dGMax;
				dGMax = dGMin;
				dGMin = d1;
			}
			sBuf = dGMax;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//上限
			sBuf = dGMin;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//下限
            break;
		case 2:
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMax = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM2);
			try{
				dGMax += sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMin = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			if(dGMax< dGMin)
			{
				d1 = dGMax;
				dGMax = dGMin;
				dGMin = d1;
			}
			sBuf = dGMax;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//上限
			sBuf = dGMin;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//下限
            break;
		case 3:
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMax = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM1);
			try{
				dGMin = sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			sBuf = AnsiString(pInfoGlaph[0].KIKA_NUM3);
			try{
				dGMin += sBuf.ToDouble();
			}
			catch(...){
				ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
				return;
            }
			if(dGMax< dGMin)
			{
				d1 = dGMax;
				dGMax = dGMin;
				dGMin = d1;
			}
			sBuf = dGMax;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,1*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//上限
			sBuf = dGMin;
    		ImgGlaphSYUKA->Canvas->TextOutA(2,8*(ImgGlaphSYUKA->Height/9)-5,sBuf);		//下限
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
		ImgGlaphSYUKA->Canvas->TextOutA(50,70,"規格を入力して下さい!!");
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
//範囲の帯グラフの表示
			ImgGlaphSYUKA->Canvas->Pen->Color = clLime;
			ImgGlaphSYUKA->Canvas->Brush->Color = clLime;
			d1 = GraphLotAddress[i1].MIN * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			d2 = GraphLotAddress[i1].MAX * dOnePitch * -1;
			d2 = dGMax * dOnePitch + d2+((ImgGlaphSYUKA->Height/9)-1);
			ImgGlaphSYUKA->Canvas->Rectangle(x+7,d2,x+13,d1);
			ImgGlaphSYUKA->Canvas->Brush->Color = clWhite;
//平均値の表示
			ImgGlaphSYUKA->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].AVE * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			ImgGlaphSYUKA->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//最大値の表示
			ImgGlaphSYUKA->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].MAX * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			ImgGlaphSYUKA->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//最小値の表示
			ImgGlaphSYUKA->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].MIN * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSYUKA->Height/9)-1);
			ImgGlaphSYUKA->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//PENCOLORをデフォルトに戻す
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
//平均値の表示
			ImgGlaphSOZAI->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].AVE * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSOZAI->Height/9)-1);
			ImgGlaphSOZAI->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//最大値の表示
			ImgGlaphSOZAI->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].MAX * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSOZAI->Height/9)-1);
			ImgGlaphSOZAI->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//最小値の表示
			ImgGlaphSOZAI->Canvas->Pen->Color = clBlue;
			d1 = GraphLotAddress[i1].MIN * dOnePitch * -1;
			d1 = dGMax * dOnePitch + d1+((ImgGlaphSOZAI->Height/9)-1);
			ImgGlaphSOZAI->Canvas->Rectangle(x+5,d1-1,x+15,d1+1);
//PENCOLORをデフォルトに戻す
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

//規格表示色々
//フォーマット指定（％*.*ｆ）
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
        	sBuf +=  "～";
        	sBuf += pInfoGlaph[0].KIKA_NUM2;
        	KIKAKU_MOJI.HANI = sBuf;
        	break;
        case 2:
        	sBuf = pInfoGlaph[0].KIKA_NUM2 ;
        	KIKAKU_MOJI.HANI = sBuf +"以下";
        	break;
        case 3:
        	sBuf = pInfoGlaph[0].KIKA_NUM1 ;
        	KIKAKU_MOJI.HANI = sBuf +"以上";
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

