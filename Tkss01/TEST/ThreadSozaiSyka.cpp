//---------------------------------------------------------------------------
//
//  ThreadSozaiSyuka.cpp
//    【出荷検査システム−素材（出荷）データ読み取り】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    市川　和弘
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
//extern KSM02_DATA *pSOZAI_OR_DATA;         // 素材のＯＲデータ
extern KSM02_DATA pSOZAI_OR_DATA[100];

// k.y 2003.05.17
//extern HANDLE hSOZAI_OR_DATA2;

// k.y 2003.05.17
//extern KSM02_DATA *pSOZAI_OR_DATA2;        // 素材のＯＲデータ（素材メインで作成）
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
extern int iSOZAI_SOKUCNT;													//ソート時使用する重み計算用バッファ
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
//ロット割り当て用（出荷検査）
extern HANDLE hSOKU_KSD01_DATA;
extern KSD01_DATA *pSOKU_KSD01_DATA;
extern bool bLOTCHANGE;						//ロット割り当て画面との通信用フラグ
AnsiString USER_NAME,CHR_CODE;

// k.y 2003.06.03
extern int iDEBUG;

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材（出荷）初期画面用データ読み取り、表示。
//
//  機能説明
//    ORテーブルを参照しCELLINFOに値を代入、表示を行います。
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
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
//出荷検査のグリッドをすべて灰色にする
    Form1->SGr_vSOKU_SOZAI->Refresh();

	iColCount = Form1->SGr_vSOKU_SOZAI->ColCount;
	iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;


	if(bNowF7 == true)      //検索キーでの検索か
    {
	    // メモリの開放
    	if( hCELLINFO_SOKU_SOZAI ){
    		GlobalUnlock( hCELLINFO_SOKU_SOZAI );
	        GlobalFree( hCELLINFO_SOKU_SOZAI );
    	}
        hCELLINFO_SOKU_SOZAI = NULL;
	    // メモリの確保
    	hCELLINFO_SOKU_SOZAI = GlobalAlloc( GHND, sizeof(struct CELLINFO_DATA) * ((iColCount+1) * iRowCount));
	    if( hCELLINFO_SOKU_SOZAI == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル01)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    	pCELLINFO_SOKU_SOZAI = (struct CELLINFO_DATA *)GlobalLock(hCELLINFO_SOKU_SOZAI);
	    if( hCELLINFO_SOKU_SOZAI == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル02)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    }


	if( !hSOKU_KSD01_DATA && bNowF7 == true )
    {
	    // メモリの開放
    	if( hSOKU_KSD01_DATA ){
    		GlobalUnlock( hSOKU_KSD01_DATA );
	        GlobalFree( hSOKU_KSD01_DATA );
    	}
        hSOKU_KSD01_DATA = NULL;
	    // メモリの確保
    	hSOKU_KSD01_DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * (iColCount+1));
	    if( hSOKU_KSD01_DATA == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル01)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    	pSOKU_KSD01_DATA = (struct KSD01_DATA *)GlobalLock(hSOKU_KSD01_DATA);
	    if( hSOKU_KSD01_DATA == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル02)";
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

//製品規格明細の各セル情報へのコピー
	if( bNowF7 == true  &&  bNowLotF7 == false )       //検索キーで検索中なので、セルインフォ初期値代入
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
				// 測定日
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].SKTYMD		,FormatDateTime("yyyymmdd",Date()).c_str());
				// 登録日
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].ADDYMD		,FormatDateTime("yyyymmdd",Date()).c_str());
				// 登録時間
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].ADDTIM		,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
				// 変更日
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].UPDYMD		,FormatDateTime("yyyymmdd",Date()).c_str());
				// 変更時間
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].UPDTIM		,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
					strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].UPDCHR		,pSOKU_KSD01_DATA[i1].UPDCHR);

					//2003.05.17 E.Takase Add↓
                    strcpy(pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].UPDNAME 		, pSOKU_KSD01_DATA[i1].UPDNAME);
					//2003.05.17 E.Takase Add↑

				// 規格
                	pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].MAX = dMAX ;
                    pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].MIN = dMIN ;
                	pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].GMAX = dMAX ;
                    pCELLINFO_SOKU_SOZAI[(i1 * iRowCount) + i4].GMIN = dMIN ;
					i4++;
	    		}
		    }
        }
//出荷検査予定の項目の白抜き
    	for( i4 = 0; i4 < SGr_vSOKU_SOZAI->ColCount ; i4++)
        {
    	    for(i1 = 0; i1 < iSOZAI_SYKA_KOMKCNT;i1++)
    		{
        		nDRAW_GRID = 1;
		    	{
			    	for( i2 = 0; i2 < iSOZAI_ContCnt ; i2++)
				    {
//ORテーブルの現在の機器NOと項目NOを抽出
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
//ロット割り当て画面で「変更」押下時はフラグはtrue
    // 2003/11/18 A.Tamura 以下if文(bNowF7 == true)はfalseの間違い？ easy missか?
	//if( bNowF7 == true || bLOTCHANGE == true )
	if( bNowF7 == true || bLOTCHANGE == true )
    {
    	GET_KSD22();        //素材元データの読み込み(オリジナル）
    }
//ロットチェンジフラグの初期化
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
    //ロットチェンジがないので保存データを取ってくる
    	//SET_KSD01();							//測定実績等の取り込み
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
//  概要
//    自作関数			：素材（出荷）データの表示を行います。
//
//  機能説明
//    CELLINFOの初期値を表示します。
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
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
//  概要
//    自作関数			：素材（出荷）データの素材測定実績明細データの読み込みを行う。
//
//  機能説明
//    割り当て済みのロットNOをキーにして素材（出荷）データの素材測定実績明細データの読み込みを行う。
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GET_KSD22(void)
{
    AnsiString sBuf;
	//int iHINBAN;
//出荷素材測定の測定結果の読み込み
	int iCol,iRow,i1,i2,i3;
    bool bFirstDate;
	AnsiString sLot,sLOTNO,sKOMK_NO,sKOMK_NM,sDTKSHIN,sDTKSHIN_SZ,sHINBAN_SK;
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
				sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO1_SZ;
				sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;
				sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO1_SZ;
				sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM1_SZ;
				iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE1_SZ).ToIntDef(0);
                break;
			case 1:
				sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO2_SZ;
				sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
				sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO2_SZ;
				sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM2_SZ;
				iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE2_SZ).ToIntDef(0);
                break;
			case 2:
				sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO3_SZ;
				sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
				sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO3_SZ;
				sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM3_SZ;
				iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE3_SZ).ToIntDef(0);
                break;
			case 3:
				sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO4_SZ;
				sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
				sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO4_SZ;
				sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM4_SZ;
				iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE4_SZ).ToIntDef(0);
                break;
			case 4:
				sLOTNO	 	= pSOKU_KSD01_DATA[iCol].LOTNO5_SZ;
				sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
				sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO5_SZ;
				sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM5_SZ;
				iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE5_SZ).ToIntDef(0);
                break;
			case 5:
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
                if((bLOTCHANGE == true) && (iLotChange == 0))			//ロット割り当て画面で「変更」が押されたが、
				{													//変更されていない場合は改めてデータをリードしない
				}
				else
				{

				// 2003/11/19 A.Tamura 指定されたロットが測定済みかどうかを判定し、
				//                     測定済みの場合は[KSD02]＋[KSD22]で素材データを検索します
				//                     未測定　の場合は[KSM02]＋[KSD22]で素材データを検索します
/* 2005.09.26 Y.Sano 削除
				sBuf = "SELECT * FROM KSD01 WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";
*/
/* 2005.09.26 Y.Sano 追加     */
				sBuf = "SELECT LOTNO FROM KSD01 WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";

				sBuf += " AND LOTNO ='" + AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO) + "'";

				// Initial Query
				Form1->Query4->Close();
				Form1->Query4->SQL->Clear();
				Form1->Query4->SQL->Add(sBuf);
				Form1->Query4->Open();
				Form1->Query4->Active = true;

				if( Form1->Query4->Eof == true ){
                    // 未測定の為、[KSM02]+[KSD22]で素材データを検索します
/* 2005.09.26 Y.Sano 削除
					sBuf  = " SELECT KSD22.*";
*/
/* 2005.09.26 Y.Sano 追加         */
/* ＊でデータ取得すると必要のないデータを取ってくるため、*/
/* 以降での取得データの読み込みが遅くなるため、          */
/* 必要なデータだけを取得するようにする。                */
					sBuf  = " SELECT KSD22.LOTNO,KSD22.DTKSHIN,KSD22.KOMK_NM,";
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
					sBuf += " AND ((KSD22.LOTNO) = '" + sLOTNO + "')";
/* 2005.09.26 Y.Sano 削除
					sBuf += " ORDER BY KSM02.ORDER_NO";*/
/* 2005.09.26 Y.Sano 追加         */
/* INNER JOINの取得条件だと取得データに重複するため、   */
/* GROPU BYをかけて重複を取り除く                       */
/* 重複データが多すぎたため検索処理が遅くなっていたので */
/* これにより高速化した。                               */
                    sBuf += " GROUP BY KSD22.LOTNO,KSD22.DTKSHIN,KSD22.KOMK_NM,";
					sBuf += "KSD22.KOMK_NO,KSD22.SKTYMD,KSD22.ADDYMD,KSD22.ADDTIM,";
					sBuf += "KSD22.UPDYMD,KSD22.UPDTIM,KSD22.UPDCHR,KSD22.UPDCNT,";
					sBuf += "KSD22.SOKU_VAL01,KSD22.SOKU_VAL02,KSD22.SOKU_VAL03,";
					sBuf += "KSD22.SOKU_VAL04,KSD22.SOKU_VAL05,KSD22.SOKU_VAL06,";
					sBuf += "KSD22.SOKU_VAL07,KSD22.SOKU_VAL08,KSD22.SOKU_VAL09,KSD22.SOKU_VAL10";

				}
				else {
                    // 測定済みの為、[KSD02]+[KSD22]で素材データを検索します
/* 2005.09.26 Y.Sano 削除
					sBuf  = " SELECT KSD22.*";
*/
/* 2005.09.26 Y.Sano 追加         */
/* ＊でデータ取得すると必要のないデータを取ってくるため、*/
/* 以降での取得データの読み込みが遅くなるため、          */
/* 必要なデータだけを取得するようにする。                */
					sBuf  = " SELECT KSD22.LOTNO,KSD22.DTKSHIN,KSD22.KOMK_NM,";
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
					sBuf += " AND ((KSD22.LOTNO) = '" + sLOTNO + "')";
/* 2005.09.26 Y.Sano 削除
					sBuf += " ORDER BY KSD02.ORDER_NO";*/
/* 2005.09.26 Y.Sano 追加         */
/* INNER JOINの取得条件だと取得データに重複するため、   */
/* GROPU BYをかけて重複を取り除く                       */
/* 重複データが多すぎたため検索処理が遅くなっていたので */
/* これにより高速化した。                               */
                    sBuf += " GROUP BY KSD22.LOTNO,KSD22.DTKSHIN,KSD22.KOMK_NM,";
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
				//初期化
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
                        /* 2003/11/24 A.Tamura これはKSD22から代入したらダメだろう。
		    			strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD		,sADDYMD.c_str());
			    		strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM		,sADDTIM.c_str());
				    	strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD		,sUPDYMD.c_str());
					    strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM		,sUPDTIM.c_str());
    					strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR		,sUPDCHR.c_str());
	    				strcpy(pSOKU_KSD01_DATA[iCol].UPDCNT		,sUPDCNT.c_str());
                        */
					    //2003.05.12 E.Takase Add↓
					    //2003.05.17 E.Takase Add↓
                        strcpy(pSOKU_KSD01_DATA[iCol].UPDNAME 		,Form1->GetTANTO(sUPDCHR).c_str());
					    //2003.05.17 E.Takase Add↑
                        bFirstDate = false;
                    }
                    else
                    {
    				    if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ) < sSKTYMD)
                        {
    					    strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ		,sSKTYMD.c_str());
	    				    strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT	,sSKTYMD.c_str());
                        	/* 2003/11/24 A.Tamura これはKSD22から代入したらダメだろう。
		    			    strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD		,sADDYMD.c_str());
			    		    strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM		,sADDTIM.c_str());
				    	    strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD		,sUPDYMD.c_str());
					        strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM		,sUPDTIM.c_str());
    					    strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR		,sUPDCHR.c_str());
	    				    strcpy(pSOKU_KSD01_DATA[iCol].UPDCNT		,sUPDCNT.c_str());
                            */
					        //2003.05.12 E.Takase Add↓
					        //2003.05.17 E.Takase Add↓
                            strcpy(pSOKU_KSD01_DATA[iCol].UPDNAME 		,Form1->GetTANTO(sUPDCHR).c_str());
					        //2003.05.17 E.Takase Add↑
                        }
                    }
					sLOTNO 				= "";
		        	sSOKU_VAL01 		= "";    		//素材測定値
    		        sSOKU_VAL02 		= "";    		//素材測定値
        		    sSOKU_VAL03 		= "";    		//素材測定値
            		sSOKU_VAL04 		= "";    		//素材測定値
		            sSOKU_VAL05 		= "";    		//素材測定値
    		        sSOKU_VAL06 		= "";    		//素材測定値
        		    sSOKU_VAL07 		= "";    		//素材測定値
            		sSOKU_VAL08 		= "";    		//素材測定値
	            	sSOKU_VAL09 		= "";    		//素材測定値
	    	        sSOKU_VAL10 		= "";    		//素材測定値
					sLOTNO 				= Form1->Query4->FieldValues["LOTNO"];
	    	    	sSOKU_VAL01 		= Form1->Query4->FieldValues["SOKU_VAL01"];    		//素材測定値
    	    	    sSOKU_VAL02 		= Form1->Query4->FieldValues["SOKU_VAL02"];    		//素材測定値
        	    	sSOKU_VAL03 		= Form1->Query4->FieldValues["SOKU_VAL03"];    		//素材測定値
	            	sSOKU_VAL04 		= Form1->Query4->FieldValues["SOKU_VAL04"];    		//素材測定値
		            sSOKU_VAL05 		= Form1->Query4->FieldValues["SOKU_VAL05"];    		//素材測定値
    		        sSOKU_VAL06 		= Form1->Query4->FieldValues["SOKU_VAL06"];    		//素材測定値
        		    sSOKU_VAL07 		= Form1->Query4->FieldValues["SOKU_VAL07"];    		//素材測定値
            		sSOKU_VAL08 		= Form1->Query4->FieldValues["SOKU_VAL08"];    		//素材測定値
		            sSOKU_VAL09 		= Form1->Query4->FieldValues["SOKU_VAL09"];    		//素材測定値
    		        sSOKU_VAL10 		= Form1->Query4->FieldValues["SOKU_VAL10"];    		//素材測定値
					iRow = 1;																//０行目は日付
					for( i3 = 0 ; i3 < iSOZAI_ORCNT ; i3++)
					{
                        //2003/12/10 E.Takase
                        //条件追加 pCELLINFO_SOKU_SOZAIが有効か？ KOMK_NOが-999以外ならOK
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
//  概要
//    自作関数			：素材（出荷）データのKSM01→KSD01への初期値代入を行う。
//
//  機能説明
//    素材（出荷）データの初期値（KSM01）の代入を行うロット毎に行う。
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SET_KSD01(void)
{
//デフォルトの品番のセット
	int iCol,i2;//i1,i3;
	AnsiString sBuf,sLot,sBuf2;

	for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
	{
		//2003.05.12 E.Takase Add↓
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN	 ,Form1->sNowDTKSHIN.c_str());
		//2003.05.12 E.Takase Add↑
		//2003.05.12 E.Takase Add コメント↓
		//strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN	 ,Form1->Cmb_DTKSHIN->Text.c_str());
		//2003.05.12 E.Takase Add コメント↑
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO	 	    ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN	    ,pKSM01_DATA.HINBAN);
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
		strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK	 	 ,"0");					//デフォルトはＯＫ
		strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK_PRT	 ,"0");					//デフォルトはＯＫ
		strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK	 	 ,"0");					//デフォルトはＯＫ
		strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK_PRT	 ,"0");					//デフォルトはＯＫ
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

        // 2004.12.24(X'mas Eve) A.Tamura 最後までループ回ってない！！
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
//履歴の有る物のセット
	sLot ="";
	for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
	{
    	sLot += "'" + Form1->SGr_tSOKU->Cells[iCol][0] +"',";
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

	sBuf = "SELECT * FROM KSD01";
	//2003.05.12 E.Takase Add↓
	sBuf += " WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";
	//2003.05.12 E.Takase Add↑
	//2003.05.12 E.Takase Add コメント↓
	//sBuf += " WHERE DTKSHIN = '" + Form1->Cmb_DTKSHIN->Text + "'";
	//2003.05.12 E.Takase Add コメント↑
	sBuf += " AND LOTNO IN (" + sLot + ")";
	sBuf += " ORDER BY LOTNO";

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

	while(Form1->Query4->Eof != true)
	{
//履歴測定実績データの読み込み
		for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
		{
			if(Form1->SGr_tSOKU->Cells[iCol][0] == AnsiString(Form1->Query4->FieldValues["LOTNO"])) break;
		}

        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN"];						//得意先品番
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN	 			,sBuf.c_str());
		}
         strcpy(pSOKU_KSD01_DATA[iCol].LOTNO		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO"];                     		//ロットNO
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO	 				,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO1_SZ"];                 		//素材用ロット１
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO2_SZ"];                      //素材用ロット２
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO3_SZ"];                      //素材用ロット３
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO4_SZ"];                      //素材用ロット４
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO5_SZ"];                      //素材用ロット５
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO6_SZ"];                      //素材用ロット６
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].HINBAN		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN"];                       	//自社品番
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN	 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSCOD		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSCOD"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSCOD"];                      	//得意先コード
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSCOD	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSNAM		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSNAM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSNAM"];                      	//得意先名称
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSNAM	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].ZISNAM		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["ZISNAM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["ZISNAM"];                       	//材質名称
			strcpy(pSOKU_KSD01_DATA[iCol].ZISNAM	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].HINMEI		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["HINMEI"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINMEI"];                      	//品名
			strcpy(pSOKU_KSD01_DATA[iCol].HINMEI	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN1_SZ"];                  	//素材用得意先品番１
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN2_SZ"];                    //素材用得意先品番２
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN3_SZ"];                    //素材用得意先品番３
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN4_SZ"];                    //素材用得意先品番４
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN5_SZ"];                    //素材用得意先品番５
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN6_SZ"];                    //素材用得意先品番６
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["LOT_LINK_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOT_LINK_SZ"];                    //ロットリンク
			strcpy(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].SOKUTEI_NUM		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["SOKUTEI_NUM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOKUTEI_NUM"];                    //測定項目数
			strcpy(pSOKU_KSD01_DATA[iCol].SOKUTEI_NUM			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["SOZAI_OK"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOZAI_OK"];                       //素材判定
			strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK				,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK_PRT		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["SOZAI_OK_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOZAI_OK_PRT"];                   //素材判定印刷用
			strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK_PRT			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["SYUKA_OK"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SYUKA_OK"];                       //出荷判定
			strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK				,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK_PRT		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["SYUKA_OK_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SYUKA_OK_PRT"];                   //出荷判定印刷用
			strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK_PRT			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE1		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE1"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE1"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE1 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE2		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE2"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE2"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE2 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE3		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE3"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE3"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE3 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE4		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE4"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE4"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE4 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE5		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE5"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE5"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE5 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE6		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE6"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE6"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE6 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE7		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE7"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE7"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE7 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE8		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE8"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE8"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE8 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].X_OUT		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["X_OUT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["X_OUT"];
			strcpy(pSOKU_KSD01_DATA[iCol].X_OUT 	 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].MEMO		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["MEMO"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["MEMO"];
			strcpy(pSOKU_KSD01_DATA[iCol].MEMO 	 				,sBuf.c_str());
        }

	//素材用検査測定日
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_SZ"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_SZ"];
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ 	 			,sBuf.c_str());
        }
		if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD,pKSM01_DATA.ADDYMD);
        }
	//素材用検査測定日（印刷用）
        strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_SZ_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_SZ_PRT"];
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT 	 	  	,sBuf.c_str());
        }
		if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT,pKSM01_DATA.ADDYMD);
        }
	//出荷用検査測定日
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD"];
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD 	 			,sBuf.c_str());
        }
		if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD,pKSM01_DATA.ADDYMD);
        }
	//出荷用検査測定日（印刷用）
        strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_PRT"];
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT 	 	  	,sBuf.c_str());
        }
		if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT,pKSM01_DATA.ADDYMD);
        }
	//代表登録日
		strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["ADDYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["ADDYMD"];
			strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD 	 			,sBuf.c_str());
		}
		if(AnsiString(pSOKU_KSD01_DATA[iCol].ADDYMD).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD,pKSM01_DATA.ADDYMD);
        }
	//代表登録時間
        strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["ADDTIM"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["ADDTIM"];
			strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM 	 			,sBuf.c_str());
		}
		if(AnsiString(pSOKU_KSD01_DATA[iCol].ADDTIM).Trim().Length() != 4 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM,pKSM01_DATA.ADDTIM);
        }
	//代表変更日
        strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["UPDYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDYMD"];
			strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD 	 			,sBuf.c_str());
        }
		if(AnsiString(pSOKU_KSD01_DATA[iCol].UPDYMD).Trim().Length() != 8 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD,pKSM01_DATA.UPDYMD);
        }
	//代表変更時間
		strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["UPDTIM"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDTIM"];
			strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM 	 			,sBuf.c_str());
		}
		if(AnsiString(pSOKU_KSD01_DATA[iCol].UPDTIM).Trim().Length() != 4 )
		{
			strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM,pKSM01_DATA.UPDTIM);
        }
	//代表更新者
        strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR		,"");                      //品番
        if ( VarIsNull(Form1->Query4->FieldValues["UPDCHR"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDCHR"];
			strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 			,sBuf.c_str());
		}
	//代表更新回数
        strcpy(pSOKU_KSD01_DATA[iCol].UPDCNT		,"");                      //品番
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
//  概要
//    自作関数			：素材（出荷）データの素材測定実績明細データの読み込みを行う。
//
//  機能説明
//    割り当て済みのロットNOをキーにして素材（出荷）データの素材測定実績明細データの読み込みを行う。
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GET_KSD22_AGAIN(void)
{
    AnsiString sBuf;
	//int iHINBAN;
//出荷素材測定の測定結果の読み込み
	int iCol,iRow,i1,i2,i3;
    bool bFirstDate;
	AnsiString sLot,sLOTNO,sKOMK_NO,sKOMK_NM,sDTKSHIN,sDTKSHIN_SZ,sHINBAN_SK;
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
				sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO1_SZ;
				sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ;
				sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO1_SZ;
				sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM1_SZ;
				iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE1_SZ).ToIntDef(0);
                break;
			case 1:
				sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO2_SZ;
				sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ;
				sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO2_SZ;
				sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM2_SZ;
				iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE2_SZ).ToIntDef(0);
                break;
			case 2:
				sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO3_SZ;
				sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ;
				sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO3_SZ;
				sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM3_SZ;
				iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE3_SZ).ToIntDef(0);
                break;
			case 3:
				sLOTNO 		= pSOKU_KSD01_DATA[iCol].LOTNO4_SZ;
				sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ;
				sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO4_SZ;
				sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM4_SZ;
				iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE4_SZ).ToIntDef(0);
                break;
			case 4:
				sLOTNO	 	= pSOKU_KSD01_DATA[iCol].LOTNO5_SZ;
				sDTKSHIN_SZ = pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ;
				sKOMK_NO 	= pSOKU_KSD01_DATA[iCol].KOMKNO5_SZ;
				sKOMK_NM 	= pSOKU_KSD01_DATA[iCol].KOMKNM5_SZ;
				iLotChange	= AnsiString(pSOKU_KSD01_DATA[iCol].LOTNOCHANGE5_SZ).ToIntDef(0);
                break;
			case 5:
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
                if((bLOTCHANGE == true) && (iLotChange == 0))			//ロット割り当て画面で「変更」が押されたが、
				{													//変更されていない場合は改めてデータをリードしない
				}
				else
				{

				// 2003/11/19 A.Tamura 指定されたロットが測定済みかどうかを判定し、
				//                     測定済みの場合は[KSD02]＋[KSD22]で素材データを検索します
				//                     未測定　の場合は[KSM02]＋[KSD22]で素材データを検索します
				sBuf = "SELECT * FROM KSD01 WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";
				sBuf += " AND LOTNO ='" + AnsiString(pSOKU_KSD01_DATA[iCol].LOTNO) + "'";

				// Initial Query
				Form1->Query4->Close();
				Form1->Query4->SQL->Clear();
				Form1->Query4->SQL->Add(sBuf);
				Form1->Query4->Open();
				Form1->Query4->Active = true;

				if( Form1->Query4->Eof == true ){
                    // 未測定の為、[KSM02]+[KSD22]で素材データを検索します
/* 2005.09.27 Y.Sano 削除
					sBuf  = " SELECT KSD22.*";
*/
/* 2005.09.27 Y.Sano 追加         */
/* ＊でデータ取得すると必要のないデータを取ってくるため、*/
/* 以降での取得データの読み込みが遅くなるため、          */
/* 必要なデータだけを取得するようにする。                */
					sBuf  = "SELECT KSD22.LOTNO,KSD22.DTKSHIN,KSD22.KOMK_NM,";
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
					sBuf += " AND ((KSD22.LOTNO) = '" + sLOTNO + "')";
/* 2005.09.27 Y.Sano 削除
					sBuf += " ORDER BY KSD02.ORDER_NO";*/
/* 2005.09.27 Y.Sano 追加         */
/* INNER JOINの取得条件だと取得データに重複するため、   */
/* GROPU BYをかけて重複を取り除く                       */
/* 重複データが多すぎたため検索処理が遅くなっていたので */
/* これにより高速化した。                               */
		            sBuf += " GROUP BY KSD22.LOTNO,KSD22.DTKSHIN,KSD22.KOMK_NM,";
					sBuf += "KSD22.KOMK_NO,KSD22.SKTYMD,KSD22.ADDYMD,KSD22.ADDTIM,";
					sBuf += "KSD22.UPDYMD,KSD22.UPDTIM,KSD22.UPDCHR,KSD22.UPDCNT,";
					sBuf += "KSD22.SOKU_VAL01,KSD22.SOKU_VAL02,KSD22.SOKU_VAL03,";
					sBuf += "KSD22.SOKU_VAL04,KSD22.SOKU_VAL05,KSD22.SOKU_VAL06,";
					sBuf += "KSD22.SOKU_VAL07,KSD22.SOKU_VAL08,KSD22.SOKU_VAL09,";
		            sBuf += "KSD22.SOKU_VAL10";
				}
				else {
                    // 測定済みの為、[KSD02]+[KSD22]で素材データを検索します
/* 2005.09.27 Y.Sano 削除
					sBuf  = " SELECT KSD22.*";
*/
/* 2005.09.27 Y.Sano 追加         */
/* ＊でデータ取得すると必要のないデータを取ってくるため、*/
/* 以降での取得データの読み込みが遅くなるため、          */
/* 必要なデータだけを取得するようにする。                */
					sBuf  = "SELECT KSD22.LOTNO,KSD22.DTKSHIN,KSD22.KOMK_NM,";
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
					sBuf += " AND ((KSD22.LOTNO) = '" + sLOTNO + "')";
/* 2005.09.27 Y.Sano 削除
					sBuf += " ORDER BY KSD02.ORDER_NO";*/
/* 2005.09.27 Y.Sano 追加         */
/* INNER JOINの取得条件だと取得データに重複するため、   */
/* GROPU BYをかけて重複を取り除く                       */
/* 重複データが多すぎたため検索処理が遅くなっていたので */
/* これにより高速化した。                               */
		            sBuf += " GROUP BY KSD22.LOTNO,KSD22.DTKSHIN,KSD22.KOMK_NM,";
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
				//初期化
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
                        /* 2003/11/24 A.Tamura これはKSD22から代入したらダメだろう。
		    			strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD		,sADDYMD.c_str());
			    		strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM		,sADDTIM.c_str());
				    	strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD		,sUPDYMD.c_str());
					    strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM		,sUPDTIM.c_str());
    					strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR		,sUPDCHR.c_str());
	    				strcpy(pSOKU_KSD01_DATA[iCol].UPDCNT		,sUPDCNT.c_str());
                        */
					    //2003.05.12 E.Takase Add↓
					    //2003.05.17 E.Takase Add↓
                        strcpy(pSOKU_KSD01_DATA[iCol].UPDNAME 		,Form1->GetTANTO(sUPDCHR).c_str());
					    //2003.05.17 E.Takase Add↑
                        bFirstDate = false;
                    }
                    else
                    {
    				    if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ) < sSKTYMD)
                        {
    					    strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ		,sSKTYMD.c_str());
	    				    strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT	,sSKTYMD.c_str());
                            /* 2003/11/24 A.Tamura これはKSD22から代入したらダメだろう。
		    			    strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD		,sADDYMD.c_str());
			    		    strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM		,sADDTIM.c_str());
				    	    strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD		,sUPDYMD.c_str());
					        strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM		,sUPDTIM.c_str());
    					    strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR		,sUPDCHR.c_str());
	    				    strcpy(pSOKU_KSD01_DATA[iCol].UPDCNT		,sUPDCNT.c_str());
                            */
					        //2003.05.12 E.Takase Add↓
					        //2003.05.17 E.Takase Add↓
                            strcpy(pSOKU_KSD01_DATA[iCol].UPDNAME 		,Form1->GetTANTO(sUPDCHR).c_str());
					        //2003.05.17 E.Takase Add↑
                        }
                    }
					sLOTNO 				= "";
		        	sSOKU_VAL01 		= "";    		//素材測定値
    		        sSOKU_VAL02 		= "";    		//素材測定値
        		    sSOKU_VAL03 		= "";    		//素材測定値
            		sSOKU_VAL04 		= "";    		//素材測定値
		            sSOKU_VAL05 		= "";    		//素材測定値
    		        sSOKU_VAL06 		= "";    		//素材測定値
        		    sSOKU_VAL07 		= "";    		//素材測定値
            		sSOKU_VAL08 		= "";    		//素材測定値
	            	sSOKU_VAL09 		= "";    		//素材測定値
	    	        sSOKU_VAL10 		= "";    		//素材測定値
					sLOTNO 				= Form1->Query4->FieldValues["LOTNO"];
	    	    	sSOKU_VAL01 		= Form1->Query4->FieldValues["SOKU_VAL01"];    		//素材測定値
    	    	    sSOKU_VAL02 		= Form1->Query4->FieldValues["SOKU_VAL02"];    		//素材測定値
        	    	sSOKU_VAL03 		= Form1->Query4->FieldValues["SOKU_VAL03"];    		//素材測定値
	            	sSOKU_VAL04 		= Form1->Query4->FieldValues["SOKU_VAL04"];    		//素材測定値
		            sSOKU_VAL05 		= Form1->Query4->FieldValues["SOKU_VAL05"];    		//素材測定値
    		        sSOKU_VAL06 		= Form1->Query4->FieldValues["SOKU_VAL06"];    		//素材測定値
        		    sSOKU_VAL07 		= Form1->Query4->FieldValues["SOKU_VAL07"];    		//素材測定値
            		sSOKU_VAL08 		= Form1->Query4->FieldValues["SOKU_VAL08"];    		//素材測定値
		            sSOKU_VAL09 		= Form1->Query4->FieldValues["SOKU_VAL09"];    		//素材測定値
    		        sSOKU_VAL10 		= Form1->Query4->FieldValues["SOKU_VAL10"];    		//素材測定値
					iRow = 1;																//０行目は日付
					for( i3 = 0 ; i3 < iSOZAI_ORCNT ; i3++)
					{
                        //2003/12/10 E.Takase
                        //条件追加 pCELLINFO_SOKU_SOZAIが有効か？ KOMK_NOが-999以外ならOK
						//if((AnsiString(pSOZAI_OR_DATA[ i3 ].KOMK_NO) 	== sKOMK_NO)
						//&& (AnsiString(pSOZAI_OR_DATA[ i3 ].HINBAN_SK) == sDTKSHIN))
						//{
						if((AnsiString(pSOZAI_OR_DATA[ i3 ].KOMK_NO) 	== sKOMK_NO)
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








