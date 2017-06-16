//---------------------------------------------------------------------------
//
//  ThreadSozaiSyuka.cpp
//    【出荷検査システム−素材（履歴）データ読み取り】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    市川　和弘
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

extern HANDLE hCELLINFO_RIRE_SOZAI;
extern CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;

extern int iSOZAI_KOMKCNT;
extern int iSOZAI_CONT_CONT;
extern int iSOZAI_RIRE_LOT;
extern int iSOZAI_ORCNT;
extern int iSOZAI_SOKUCNT;													//ソート時使用する重み計算用バッファ
extern int iSOZAI_RireCnt,iSOZAI_SyukaCnt,iSOZAI_SokuCnt,iSOZAI_ContCnt,iSOZAI_KikiCnt;
extern int iSOZAI_ORCNT;

//ロット割り当て用（履歴検査）
extern HANDLE hRIRE_KSD01_DATA;
extern KSD01_DATA *pRIRE_KSD01_DATA;
extern bool bLOTCHANGE;						//ロット割り当て画面との通信用フラグ

// k.y 2003.06.03
extern int iDEBUG;

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材出荷履歴読み取りメイン。
//
//  機能説明
//    ＯＲテーブルを参照して素材出荷履歴を読み取る。
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
void __fastcall TForm1::SetRIRE_Sozai(void)
{
//Orテーブルが出来ているので履歴データの詳細を改めて読み込む
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
        //	履歴ロットの描画
      	//for( i1 = 0;i1 < Form1->iRIRE_CNT ; i1++)
	    //{
		//    Form1->SGr_tRIRE->Cells[i1][0] = Form1->sRIREKI_LOT->Strings[i1];
    	//}
/*
	    // メモリの開放
    	if( hRIRE_KSD01_DATA ){
    		GlobalUnlock( hRIRE_KSD01_DATA );
	        GlobalFree( hRIRE_KSD01_DATA );
    	}
        hRIRE_KSD01_DATA = NULL;
	    // メモリの確保
    	hRIRE_KSD01_DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * (Form1->SGr_tRIRE->ColCount + 1 ));
	    if( hRIRE_KSD01_DATA == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル01)";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    	pRIRE_KSD01_DATA = (struct KSD01_DATA *)GlobalLock(hRIRE_KSD01_DATA);
	    if( hRIRE_KSD01_DATA == NULL ){
    		Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル02)";
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

//出荷検査にあるロットを抽出してNOTの条件にする
AnsiString sSOZAI_RIRE_LOT;


	if( bNowLotF7 == false )		//ロット割り当て変更時は履歴データは関係ないから読まない
    {
        //SET_RIRE_KSD01();
		// メモリの開放
		if( hCELLINFO_RIRE_SOZAI ){
        	GlobalUnlock( hCELLINFO_RIRE_SOZAI );
	        GlobalFree( hCELLINFO_RIRE_SOZAI );
    	}
        hCELLINFO_RIRE_SOZAI = NULL;
	    // メモリの確保
    	hCELLINFO_RIRE_SOZAI = GlobalAlloc( GHND, sizeof(struct CELLINFO_DATA) * ((Form1->SGr_tRIRE->ColCount + 1) * iRowCount));
	    if( hCELLINFO_RIRE_SOZAI == NULL ){
    	    Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。((素材履歴))";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
    	pCELLINFO_RIRE_SOZAI = (struct CELLINFO_DATA *)GlobalLock(hCELLINFO_RIRE_SOZAI);
	    if( hCELLINFO_RIRE_SOZAI == NULL ){
    	    Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。((素材履歴))";
        	Form1->SBr1->Update();
	        Beep();
    	    return;
	    }
	}
    if(!hCELLINFO_RIRE_SOZAI) return;
//製品規格明細の各セル情報へのコピー
    //検索キーで検索中なので、セルインフォ初期値代入
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
						strcpy(pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].KOMK_NO 		, "-999");				//履歴は過去に計測しているので灰色表示含む
						pCELLINFO_RIRE_SOZAI[(i1 * iRowCount) + i4].INS_ON = false;				//履歴は過去に計測しているので灰色表示含む
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
    //ロット割り当て変更時は履歴データは関係ないから読まない
	if( bNowLotF7 == false )
    {
		Form1->Set_RIRE_SOZAIJISSEKI();
//		Synchronize(Form1->Set_RIRE_SOZAIJISSEKI);
	}
    //ロット割り当て変更時はKSD22からデータを読む
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
    //えらっそうな名前ですが、ただのセルへの表示を行っています。
	PUT_SOZAIRIRE_KSD02_DISP();
	iTHREAD_CNT ++;                 //スレッド処理の名残です。
}



//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：KSD01読み込み。
//
//  機能説明
//    ＯＲテーブルを参照して測定実績データを読み取る。
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
void __fastcall TForm1::SET_RIRE_KSD01(void)
{
//デフォルトの品番のセット
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
		strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK	 	,"0");					//デフォルトはＯＫ
		strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK_PRT	,"0");					//デフォルトはＯＫ
		strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK	 	,"0");					//デフォルトはＯＫ
		strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK_PRT	,"0");					//デフォルトはＯＫ
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

        // 2004.12.24(X'mas Eve) A.Tamura 最後までループ回ってない！！
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

    //履歴の有る物のセット
	sLot ="";
	for(iCol = 0;iCol<Form1->SGr_tRIRE->ColCount;iCol++)
	{
    	sLot += "'" + Form1->SGr_tRIRE->Cells[iCol][0] +"',";
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
	for(iCol = 0;iCol<Form1->SGr_tRIRE->ColCount;iCol++)
	{
        sLot_Where += "( LOTNO='" + Form1->SGr_tRIRE->Cells[iCol][0] + "' AND ";
        sLot_Where += " HINBAN='" + Form1->SGr_tRIRE->Cells[iCol][1] + "') OR ";
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

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
        //履歴測定実績データの読み込み
		for(iCol = 0;iCol<Form1->SGr_tRIRE->ColCount;iCol++)
		{
			if(Form1->SGr_tRIRE->Cells[iCol][0] == AnsiString(Form1->Query4->FieldValues["LOTNO"])) break;
		}

        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN"];						    //得意先品番
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN	 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].LOTNO		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO"];                     		//ロットNO
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO	 				,sBuf.c_str());
        }
        strcpy(pRIRE_KSD01_DATA[iCol].HINBAN		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN"];                     		//工管発行日 onishi
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN	 				,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].LOTNO1_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO1_SZ"];                 		//素材用ロット１
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO1_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].LOTNO2_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO2_SZ"];                         //素材用ロット２
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO2_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].LOTNO3_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO3_SZ"];                         //素材用ロット３
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO3_SZ	 	 		,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].LOTNO4_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO4_SZ"];                         //素材用ロット４
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO4_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].LOTNO5_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO5_SZ"];                         //素材用ロット５
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO5_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].LOTNO6_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO6_SZ"];                         //素材用ロット６
			strcpy(pRIRE_KSD01_DATA[iCol].LOTNO6_SZ	 	 		,sBuf.c_str());
		}
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN1_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN1_SZ"];                 		//素材用自社品番1
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN1_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN2_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN2_SZ"];                 		//素材用自社品番2
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN2_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN3_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN3_SZ"];                 		//素材用自社品番3
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN3_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN4_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN4_SZ"];                 		//素材用自社品番4
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN4_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN5_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN5_SZ"];                 		//素材用自社品番5
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN5_SZ	 	 	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].HINBAN6_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN6_SZ"];                 		//素材用自社品番6
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN6_SZ	 	 	,sBuf.c_str());
        }

        strcpy(pRIRE_KSD01_DATA[iCol].HINBAN		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN"];                       	//自社品番
			strcpy(pRIRE_KSD01_DATA[iCol].HINBAN	 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].DTKSCOD		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSCOD"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSCOD"];                      	//得意先コード
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSCOD	 	 		,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSNAM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSNAM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSNAM"];                      	//得意先名称
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSNAM	 	 		,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].ZISNAM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["ZISNAM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["ZISNAM"];                       	//材質名称
			strcpy(pRIRE_KSD01_DATA[iCol].ZISNAM	 	 		,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].HINMEI		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINMEI"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINMEI"];                      	//品名
			strcpy(pRIRE_KSD01_DATA[iCol].HINMEI	 	 		,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN1_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN1_SZ"];                  	//素材用得意先品番１
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN1_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN2_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN2_SZ"];                    //素材用得意先品番２
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN2_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN3_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN3_SZ"];                    //素材用得意先品番３
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN3_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN4_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN4_SZ"];                    //素材用得意先品番４
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN4_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN5_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN5_SZ"];                    //素材用得意先品番５
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN5_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN6_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN6_SZ"];                    //素材用得意先品番６
			strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN6_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].LOT_LINK_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOT_LINK_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOT_LINK_SZ"];                    //ロットリンク
			strcpy(pRIRE_KSD01_DATA[iCol].LOT_LINK_SZ			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].SOKUTEI_NUM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SOKUTEI_NUM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOKUTEI_NUM"];                    //測定項目数
			strcpy(pRIRE_KSD01_DATA[iCol].SOKUTEI_NUM			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SOZAI_OK"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOZAI_OK"];                       //素材判定
			strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK				,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK_PRT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SOZAI_OK_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOZAI_OK_PRT"];                   //素材判定印刷用
			strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK_PRT			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SYUKA_OK"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SYUKA_OK"];                       //出荷判定
			strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK				,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK_PRT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SYUKA_OK_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SYUKA_OK_PRT"];                   //出荷判定印刷用
			strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK_PRT			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE1		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE1"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE1"];                     //成績書タイトル出力項目１
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE1 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE2		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE2"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE2"];                     //成績書タイトル出力項目２
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE2 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE3		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE3"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE3"];                     //成績書タイトル出力項目３
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE3 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE4		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE4"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE4"];                     //成績書タイトル出力項目４
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE4 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE5		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE5"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE5"];                     //成績書タイトル出力項目５
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE5 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE6		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE6"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE6"];                     //成績書タイトル出力項目６
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE6 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE7		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE7"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE7"];                     //成績書タイトル出力項目７
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE7 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE8		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE8"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE8"];                     //成績書タイトル出力項目８
			strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE8 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].X_OUT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["X_OUT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["X_OUT"];                          //Ｘバー
			strcpy(pRIRE_KSD01_DATA[iCol].X_OUT 	 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].MEMO		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["MEMO"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["MEMO"];                           //備考
			strcpy(pRIRE_KSD01_DATA[iCol].MEMO 	 				,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_SZ"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_SZ"];                      //素材用測定日
			strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ 	 			,sBuf.c_str());
        }
        strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ_PRT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_SZ_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_SZ_PRT"];                  //素材用測定日（印刷用）
			strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ_PRT 	 	  	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD"];                         //出荷用測定日
			strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD 	 			,sBuf.c_str());
        }
        strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_PRT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SKTYMD_PRT"];                     //出荷用測定日（印刷用）
			strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_PRT 	 	  	,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].ADDYMD		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["ADDYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["ADDYMD"];                         //代表登録日
			strcpy(pRIRE_KSD01_DATA[iCol].ADDYMD 	 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].ADDTIM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["ADDTIM"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["ADDTIM"];                         //代表登録時間
			strcpy(pRIRE_KSD01_DATA[iCol].ADDTIM 	 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].UPDYMD		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["UPDYMD"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDYMD"];                         //代表変更日
			strcpy(pRIRE_KSD01_DATA[iCol].UPDYMD 	 			,sBuf.c_str());
        }
		strcpy(pRIRE_KSD01_DATA[iCol].UPDTIM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["UPDTIM"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDTIM"];                         //代表変更時間
			strcpy(pRIRE_KSD01_DATA[iCol].UPDTIM 	 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["UPDCHR"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDCHR"];                         //代表更新者
			strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR 	 			,sBuf.c_str());
		}
        strcpy(pRIRE_KSD01_DATA[iCol].UPDCNT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["UPDCNT"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDCNT"];                         //代表更新回数
			strcpy(pRIRE_KSD01_DATA[iCol].UPDCNT 	 			,sBuf.c_str());
		}
		Form1->Query4->Next();
	}
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：KSD22読み込み。
//
//  機能説明
//    事前に読み込んだKSM01を参照して素材測定実績明細データを読み取る。
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
void __fastcall TForm1::GET_RIRE_KSD22(void)
{
    AnsiString sBuf;
	//int iHINBAN;
//出荷素材測定の測定結果の読み込み
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
        //素材用得意先品番、出荷
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
            if(bLOTCHANGE == true && iLotChange == 0) break;	//ロット割り当て画面で「変更」が押されたが、
																//変更されていない場合は改めてデータをリードしない
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
//初期化
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
//  概要
//    自作関数			：素材（履歴）グリッド上に値を出力します。
//
//  機能説明
//    CELLINFOを参照しデータを出力します。
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


//シンクロナイズをするため置きました
void __fastcall TForm1::GET_SOZAIRIRE_KSD02(void)
{

	AnsiString sBuf;
	AnsiString sSOZAI_RIRE_LOT,sTempLot;
	sBuf = "SELECT *  FROM KSD02";
return;

}


