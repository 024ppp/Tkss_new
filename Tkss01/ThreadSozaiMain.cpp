//---------------------------------------------------------------------------
//
//  ThreadSozaiMain.cpp
//    【出荷検査システム－素材読み取りメイン】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    市川　和弘
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include "ThreadSozaiMain.h"
#include "ThreadSozaiRire.h"
#include "Tkss01.h"               
#include "Unit1.h"
#include "Unit8.h"
#include "UnitDataAccess.h"
#pragma package(smart_init)
// k.y 2003.05.17
//extern HANDLE hSOZAI_OR_DATA;

// k.y 2003.05.17
//extern KSM02_DATA *pSOZAI_OR_DATA;         // 素材のＯＲデータ
extern KSM02_DATA pSOZAI_OR_DATA[100];

// k.y 2003.05.17
//extern HANDLE hKSM01_DATA;

// k.y 2003.05.17
//extern KSM01_DATA *pKSM01_DATA;				//製品規格マスター
extern KSM01_DATA pKSM01_DATA;
extern int iDEBUG;
extern bool bLOTCHANGE;						//ロット割り当て画面との通信用フラグ

// k.y 2003.05.17
//HANDLE hSOZAI_OR_DATA2;
// k.y 2003.05.17
//KSM02_DATA *pSOZAI_OR_DATA2;        // 素材のＯＲデータ（素材メインで作成）
KSM02_DATA pSOZAI_OR_DATA2[100];

// k.y 2003.05.17
//HANDLE hSOZAI_SYKA_DATA;

// k.y 2003.05.17
//KSM02_DATA *pSOZAI_SYKA_DATA;
KSM02_DATA pSOZAI_SYKA_DATA[100];

// k.y 2003.05.17
//HANDLE hSOZAI_RIRE_DATA;
// k.y 2003.05.17
//KSD02_DATA *pSOZAI_RIRE_DATA;
KSD02_DATA pSOZAI_RIRE_DATA[100];

// k.y 2003.05.17
//HANDLE hSOZAI_RIRE_LOT;

// k.y 2003.05.17
//KSD01_DATA *pSOZAI_RIRE_LOT;
KSD01_DATA pSOZAI_RIRE_LOT[100];

// k.y 2003.05.17
//extern HANDLE	   hTEMPORDATA;

// k.y 2003.05.17
//extern KSM02_DATA  *pTEMPORDATA;
extern KSM02_DATA  pTEMPORDATA[100];

extern int iSOZAI_KOMKCNT;
extern int iSOZAI_CONT_CONT;
extern int iSOZAI_RIRE_LOT;
extern int iSOZAI_ORCNT;
extern int iSOZAI_SOKUCNT;													//ソート時使用する重み計算用バッファ
extern HANDLE hSOKU_KSD01_DATA;
extern KSD01_DATA *pSOKU_KSD01_DATA;
extern HANDLE hRIRE_KSD01_DATA;
extern KSD01_DATA *pRIRE_KSD01_DATA;
	int iRow,i1,i2,i3,i4;
    //int iRIRE_CNT;
    int iKOMK_CNT;
    int iKOMK_NUM;
    int iSOKU_SU;
    int iLOT_CNT;
    int iPanelNum,iKikiNum,iSokuGoukei;
    int iPutKiki;
    int iSyukaWait,iRireWait;
    int iCel;
	int iSOZAI_SYKA_KOMKCNT;
	int iSOZAI_RIRE_KOMKCNT;
	int iSOZAI_SYKACNT;
	int iSOZAI_RIRECNT;
  	int iSOZAI_ORCNT2;
	int	iSOZAI_KOMKCNT2;
    int iSYKAWAIT,iRIREWAIT;
    int iSOZAI_RireCnt,iSOZAI_SyukaCnt,iSOZAI_SokuCnt,iSOZAI_ContCnt,iSOZAI_KikiCnt;
//動的パネル数（素材用）
    int iPnl_SOZAI_InsNoCnt;
    int iPnl_SOZAI_InsNameCnt;
    int iPnl_SOZAI_InsKikiNameCnt;
    int iPnl_SOZAI_InsSubBaseCnt;
    int iSOZAI_RecordCount;
    int iSOZAI_SokuSuu;
    int iSOZAI_KikiCount;
    int iSOZAI_RotCount;                  //入力ロット数
extern    int iSOZAI_DEL_OrCnt;                     //Or表示数
extern    int iSOZAI_DEL_SokuCnt;                     //Or表示数

/* k.k 2003.05.17 DELETE
__fastcall ThreadSozaiMain::ThreadSozaiMain(bool CreateSuspended)
	: TThread(CreateSuspended)
{
  Priority = tpIdle;
}
//---------------------------------------------------------------------------
//素材の表示
//---------------------------------------------------------------------------
void __fastcall ThreadSozaiMain::Execute()
{
//	Synchronize(SOZAI_PROCESS);
	SOZAI_PROCESS();

    // 検索終了フラグ
    Form1->bNowF7 = false;

	if( Terminated ) return;
}
*/
//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材読み取りメイン。
//
//  機能説明
//    素材を読み取るためのＯＲテーブルを作成する。
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
void __fastcall TForm1::SOZAI_PROCESS(void)
{
	AnsiString sBuf,sLot,sTempBuf,sTempLot;
    bool bSOZAI_LOT;                        //素材ロット指示有り／無しフラグ
    int iRow,iRowCount;
//素材読み取り時使用するメモリの確保
    memset(pSOZAI_OR_DATA2,0x00,sizeof(pSOZAI_OR_DATA2));
    memset(pSOZAI_RIRE_LOT,0x00,sizeof(pSOZAI_RIRE_LOT));
    memset(&pSOZAI_SYKA_DATA,(int)NULL,sizeof(pSOZAI_SYKA_DATA));
    memset(pSOZAI_RIRE_DATA,0x00,sizeof(pSOZAI_RIRE_DATA));
    if(bNowF7 == true)      //検索キーでの検索か
    {
    	iSOZAI_SYKA_KOMKCNT = 0;
	    iSOZAI_RIRE_KOMKCNT = 0;
    	iSOZAI_SYKACNT		= 0;
	    iSOZAI_RIRECNT		= 0;
      	iSOZAI_ORCNT		= 0;
  	    iSOZAI_ORCNT2		= 0;
    	iSOZAI_KOMKCNT2		= 0;
        iTHREAD_CNT			= 0;

        // 2003/11/18 A.Tamura マスターKSM02を中心に素材データORを作成しています
        //                     ですが、このままだと、
        //                     画面に表示したいロットが測定済みのみの場合、
        //                     [測定済みロットの素材用品番]と
        //                     [マスターに登録されている素材用品番]が
        //                     異なると
        //                     [マスターに登録されている素材用品番]の
        //                     測定項目(横一行)が【測定可能なセル全て無し】で
        //                     表示されるので以下の関数内の処理を改造しました。  ←このバグは、2003/11/17発生!!
        //                     ①表示しようとしているロットが全て測定済みかどうか判断
        //                     ②新規ロットを含んでいる場合は、KSM02(測定項目)を中心とした処理を行なう。
        //                     ③全て測定済みロットの場合は、測定Grid一番左のロット(測定項目)を中心に処理を行なう。
        //                     ※中心となる測定項目はあくまで処理の始まりで
        //                     　以後、ORデータ作成で埋め尽くされます
        //
    	//マスターデータを読み取ります
        GET_SOZAI_KSM02();

        iLOT_CNT    = 0;
        Form1->iSOZAI_RIREKI_KOMKCNT = 0;
	//2003.05.12 E.Takase Add↓
	//if(Form1->bNowRIRE == true)

		//過去に測定したかどうかを調べます
    	//履歴を見てあれば読み取ります
        GET_SOZAI_KSD01();
        GET_SOZAI_KSD02();
        if(Form1->iRIRE_CNT != 0)
    	//2003.05.12 E.Takase Add↑
	    {
            SGr_vRIRE_SOZAI->Visible = true;
    	}
        else
        {
            SGr_vRIRE_SOZAI->Visible = false;
        }
        iSOZAI_SYKACNT 	= 0;
        iSOZAI_RIRECNT 	= 0;
        iSOZAI_ORCNT 	= 0;


    	// 2003/10/20 A.Tamura 比較条件に単位を追加します（前後の関係も修正済み）
    	//                     KSM02にブラシ厚さ[mm][Cpk]が無い時に、
    	//                     KSD02にこの２つがあると正しく表示されないエラーを回避
    	AnsiString KOMK_NM,KOMK_SUB,TANI,HINBAN_SK;
        AnsiString KIKI_NO,KOMK_NO,SOKU_SU;
    //素材用のＯＲテーブルを作成します
        for(i1 = 0;i1 < iSOZAI_SYKA_KOMKCNT;i1++)
        {
        	KOMK_NM   = pSOZAI_SYKA_DATA[i1].KOMK_NM;
            KOMK_SUB  = pSOZAI_SYKA_DATA[i1].KOMK_SUB;
            TANI      = pSOZAI_SYKA_DATA[i1].TANI;
            HINBAN_SK = pSOZAI_SYKA_DATA[i1].HINBAN_SK;
            KOMK_NO = AnsiString(pSOZAI_SYKA_DATA[i1].KOMK_NO).ToIntDef(0);
            KIKI_NO = AnsiString(pSOZAI_SYKA_DATA[i1].KIKI_NO).ToIntDef(0);
            SOKU_SU = AnsiString(pSOZAI_SYKA_DATA[i1].SOKU_SU).ToIntDef(0);
            for( i2 = 0;i2 < iSOZAI_RIRE_KOMKCNT ; i2++)
            {
                //マスターと履歴の最大数を比較し大きいほうをＯＲテーブルに代入します。
            	if(AnsiString(pSOZAI_RIRE_DATA[i2].KIKI_NO).ToIntDef(0) != 9999)
                {
                    if((KOMK_NO.ToIntDef(0) == AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_NO).ToIntDef(0))
                    && (KIKI_NO.ToIntDef(0) == AnsiString(pSOZAI_RIRE_DATA[i2].KIKI_NO).ToIntDef(0))
                    && (KOMK_NM 			== AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_NM))
                	&& (KOMK_SUB	 		== AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_SUB))
                	&& (TANI	 			== AnsiString(pSOZAI_RIRE_DATA[i2].TANI))
                    // 2003/11/24 A.Tamura テスト的にコメント
                    && (HINBAN_SK 			== AnsiString(pSOZAI_RIRE_DATA[i2].HINBAN_SK)))
                    {
                    	if(SOKU_SU.ToIntDef(0) <  AnsiString(pSOZAI_RIRE_DATA[i2].SOKU_SU).ToIntDef(0))
                        {
                        	SOKU_SU = AnsiString(pSOZAI_RIRE_DATA[i2].SOKU_SU).ToIntDef(0);
                        }
                        strcpy(pSOZAI_RIRE_DATA[i2].KIKI_NO,"9999");
                    }
                }
            }
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KIKI_NO	,KIKI_NO.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_NM	,KOMK_NM.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_NO	,KOMK_NO.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_SUB	,KOMK_SUB.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].TANI		,TANI.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].SOKU_SU	,SOKU_SU.c_str());
            strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].HINBAN_SK	,HINBAN_SK.c_str());
            iSOZAI_ORCNT++;
        }
        for( i1 = 0;i1 < iSOZAI_RIRE_KOMKCNT ; i1++)
        {
        	if(AnsiString(pSOZAI_RIRE_DATA[i1].KIKI_NO).ToIntDef(0) != 9999)
            {
            	KOMK_NM   = pSOZAI_RIRE_DATA[i1].KOMK_NM;
                KOMK_SUB  = pSOZAI_RIRE_DATA[i1].KOMK_SUB;
                TANI      = pSOZAI_RIRE_DATA[i1].TANI;
                HINBAN_SK = pSOZAI_RIRE_DATA[i1].HINBAN_SK;
                KOMK_NO = AnsiString(pSOZAI_RIRE_DATA[i1].KOMK_NO).ToIntDef(0);
                KIKI_NO = AnsiString(pSOZAI_RIRE_DATA[i1].KIKI_NO).ToIntDef(0);
                SOKU_SU = AnsiString(pSOZAI_RIRE_DATA[i1].SOKU_SU).ToIntDef(0);

                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KIKI_NO	,KIKI_NO.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_NM	,KOMK_NM.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_NO	,KOMK_NO.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].KOMK_SUB	,KOMK_SUB.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].TANI		,TANI.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].SOKU_SU	,SOKU_SU.c_str());
                strcpy(pSOZAI_OR_DATA2[iSOZAI_ORCNT].HINBAN_SK	,HINBAN_SK.c_str());
                iSOZAI_ORCNT++;
            }
        }


// ---------------------------------------------------------
//現在の出荷用の項目と測定実績の項目の最大数のORを別メモリ上へ格納
//測定実績読み取り
//抽出ロットのｎ数のMAX値の抽出

        memset(pSOZAI_RIRE_DATA,0x00,sizeof(pSOZAI_RIRE_DATA));


//    if( Form1->iRIRE_CNT > 0 )          //過去履歴が0件でなければ
    	iSOZAI_KOMKCNT2 = 0;
        if( Form1->iRIRE_CNT > 0 )          //ロットがあれば
        {
        	GET_SOZAI_KSD02_SECOND();
        }
        memset(pSOZAI_OR_DATA,0x00,sizeof(pSOZAI_OR_DATA));

//現在の出荷用の項目と過去履歴の項目の最大数のORを別メモリ上へ格納
        iSOZAI_RIRECNT 	= 0;
        iSOZAI_SYKACNT 	= 0;
        iSOZAI_ORCNT2 	= 0;

        for(i1 = 0;i1 < iSOZAI_ORCNT;i1++)
        {
        	KOMK_NM   = pSOZAI_OR_DATA2[i1].KOMK_NM;
            KOMK_SUB  = pSOZAI_OR_DATA2[i1].KOMK_SUB;
            TANI      = pSOZAI_OR_DATA2[i1].TANI;
            HINBAN_SK = pSOZAI_OR_DATA2[i1].HINBAN_SK;
            KOMK_NO = AnsiString(pSOZAI_OR_DATA2[i1].KOMK_NO).ToIntDef(0);
            KIKI_NO = AnsiString(pSOZAI_OR_DATA2[i1].KIKI_NO).ToIntDef(0);
            SOKU_SU = AnsiString(pSOZAI_OR_DATA2[i1].SOKU_SU).ToIntDef(0);
            for( i2 = 0;i2 < iSOZAI_KOMKCNT2 ; i2++)
            {
            	if(AnsiString(pSOZAI_RIRE_DATA[i2].KIKI_NO).ToIntDef(0) != 9999)
                {
/*
    	        	if((KOMK_NM 			== AnsiString(pRIREKI_DATA[i2].KOMK_NM))
        	        &&(KOMK_SUB 			== AnsiString(pRIREKI_DATA[i2].KOMK_SUB))
        	        &&(TANI 				== AnsiString(pRIREKI_DATA[i2].TANI))
            	    &&(KOMK_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KOMK_NO).ToIntDef(0))
                	&&(KIKI_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KIKI_NO).ToIntDef(0)))
*/
                    if((KOMK_NO.ToIntDef(0) == AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_NO).ToIntDef(0))
                    && (KIKI_NO.ToIntDef(0) == AnsiString(pSOZAI_RIRE_DATA[i2].KIKI_NO).ToIntDef(0))
                    && (KOMK_NM 			== AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_NM))
                    && (KOMK_SUB 			== AnsiString(pSOZAI_RIRE_DATA[i2].KOMK_SUB))
                    && (TANI 				== AnsiString(pSOZAI_RIRE_DATA[i2].TANI))
                    // 2003/11/24 A.Tamura テスト的にコメント
                    && (HINBAN_SK 			== AnsiString(pSOZAI_RIRE_DATA[i2].HINBAN_SK)))
	    			{
                    	if(SOKU_SU.ToIntDef(0) <  AnsiString(pSOZAI_RIRE_DATA[i2].SOKU_SU).ToIntDef(0))
                        {
                    	SOKU_SU = AnsiString(pSOZAI_RIRE_DATA[i2].SOKU_SU).ToIntDef(0);
                        }
                        strcpy(pSOZAI_RIRE_DATA[i2].KIKI_NO,"9999");
                    }
                }
            }
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KIKI_NO	,KIKI_NO.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_NM	,KOMK_NM.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_NO	,KOMK_NO.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_SUB	,KOMK_SUB.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].TANI		,TANI.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].SOKU_SU	,SOKU_SU.c_str());
            strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].HINBAN_SK	,HINBAN_SK.c_str());
            iSOZAI_ORCNT2++;
        }
        for( i1 = 0;i1 < iSOZAI_KOMKCNT2 ; i1++)
        {
    	    if(AnsiString(pSOZAI_RIRE_DATA[i1].KIKI_NO).ToIntDef(0) != 9999)
            {
            	KOMK_NM   = pSOZAI_RIRE_DATA[i1].KOMK_NM;
                KOMK_SUB  = pSOZAI_RIRE_DATA[i1].KOMK_SUB;
                TANI      = pSOZAI_RIRE_DATA[i1].TANI;
                HINBAN_SK = pSOZAI_RIRE_DATA[i1].HINBAN_SK;
                KOMK_NO = AnsiString(pSOZAI_RIRE_DATA[i1].KOMK_NO).ToIntDef(0);
                KIKI_NO = AnsiString(pSOZAI_RIRE_DATA[i1].KIKI_NO).ToIntDef(0);
                SOKU_SU = AnsiString(pSOZAI_RIRE_DATA[i1].SOKU_SU).ToIntDef(0);

                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KIKI_NO	,KIKI_NO.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_NM	,KOMK_NM.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_NO	,KOMK_NO.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].KOMK_SUB	,KOMK_SUB.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].TANI		,TANI.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].SOKU_SU	,SOKU_SU.c_str());
                strcpy(pSOZAI_OR_DATA[iSOZAI_ORCNT2].HINBAN_SK	,HINBAN_SK.c_str());
                iSOZAI_ORCNT2++;
            }
        }
    	iSOZAI_ORCNT = iSOZAI_ORCNT2;

    	//ＯＲテーブルが完成したので単位などの情報を読み込みます。
    	// 2003/10/20 A.Tamura コメントだけ追加します
    	//                     「完成したＯＲテーブルのソート」や
    	//                     「規格表示に必要な動的コントロールの作成」もこの中で行なっている
        GET_SOZAI_TANI();
    }

	Form1->bLOT_LINK = true;
//	Synchronize(GET_SOZAI_TANI);
//	Synchronize(SetSYKA_Sozai);
//	GET_SOZAI_TANI();
    //素材出荷読み取りを行います。
	SetSYKA_Sozai();
    //素材履歴読み取りを行います。
    SetRIRE_Sozai();

    //データ読み取り後にロット割り当て画面を表示するかのフラグを作成します。
	if(bNowLotF7 == false )
	{
		if(Form1->iRIRE_CNT != 0)
		{
			//2003.05.12 E.Takase Add↓
            //履歴読み取り指示があり、履歴数が０でない時は履歴データの検索を行います
			if(Form1->bNowRIRE == true && Form1->iRIRE_CNT != 0)
			//2003.05.12 E.Takase Add↑
			{
 				for( i1 = 0;i1 < Form1->iRIRE_CNT ;i1++)
				{
					if(Form1->SGr_tRIRE->Cells[i1][0].Trim().Length() != 0 )
					{
                        bSOZAI_LOT = false;
                        iRowCount = Form1->SGr_vRIRE_SOZAI->RowCount;
                        for(iRow = 1;iRow < iRowCount ; iRow++)
                        {
                            //履歴の指示があるかどうかの判定
                            if(AnsiString(pCELLINFO_RIRE_SOZAI[i1*iRowCount+iRow].KOMK_NO).ToIntDef(0) != -999 )
                            {
                                bSOZAI_NASI = false;
                                //履歴の指示があったのでロットの指示を確認します
                                bSOZAI_LOT = true;
                                break;
                            }
                        }
                        if( bSOZAI_LOT == true )        //素材ロットの指示があれば
                        {
                            //ロットリンクを確認します
						    if(AnsiString(pRIRE_KSD01_DATA[i1].LOT_LINK_SZ).ToIntDef(0) == 0)
						    {
       						    Form1->bLOT_LINK = false;
							    break;
						    }
                        }
					}
			    }
			}
    	}
		for( i1 = 0;i1 < Form1->SGr_tSOKU->ColCount;i1++)
		{
			if(Form1->SGr_tSOKU->Cells[i1][0].Trim().Length() != 0 )
			{
    	    	while(!hSOKU_KSD01_DATA){}
                bSOZAI_LOT = false;
                iRowCount = Form1->SGr_vSOKU_SOZAI->RowCount;
                for(iRow = 1;iRow < iRowCount ; iRow++)
                {
                    if(AnsiString(pCELLINFO_SOKU_SOZAI[i1*iRowCount+iRow].KOMK_NO).ToIntDef(0) != -999 )
                    {
                        bSOZAI_NASI = false;
                        bSOZAI_LOT = true;
                        break;
                    }
                }
                if( bSOZAI_LOT == true )
                {
				    if(AnsiString(pSOKU_KSD01_DATA[i1].LOT_LINK_SZ).ToIntDef(0) == 0)
				    {
       				    Form1->bLOT_LINK = false;
				    	break;
				    }
                }
			}
	    }
	}
	Form1->SGr_vRIRE_SOZAI->Refresh();
	Form1->SGr_vSOKU_SOZAI->Refresh();
//    bLOT_LINK = true;
    bLOTCHANGE = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PLOT_FORM8(void)
{
	Form8->ShowModal();
}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：KSM02を読み取ります。
//
//  機能説明
//    マスターデータを読み込みマスターバッファに値を代入します。
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
void __fastcall TForm1::GET_SOZAI_KSM02(void)
{
	int i1;
	AnsiString  sDTKSHIN,sBuf;

    // 2003/11/18 A.Tamura 元々この処理は、KSM02からのみのデータ取得ですが、
    //                     このままだと、この関数を抜けた以降の処理が
    //                     マスターKSM02を中心に素材データORを作成してしまうと
    //                     画面に表示したいロットが測定済みのみの場合、
    //                     [測定済みロットの素材用品番]と
    //                     [マスターに登録されている素材用品番]が
    //                     異なると
    //                     [マスターに登録されている素材用品番]の
    //                     測定項目(横一行)が【測定可能なセル全て無し】で
    //                     表示されるので以下の処理を改造しました。  ←このバグは、2003/11/17発生!!
    //                     ①表示しようとしているロットが全て測定済みかどうか判断
    //                     ②新規ロットを含んでいる場合は、KSM02(測定項目)を中心とした処理を行なう。
    //                     ③全て測定済みロットの場合は、測定Grid一番左のロット(測定項目)を中心に処理を行なう。
    //                     ※中心となる測定項目はあくまで処理の始まりで
    //                     　以後、ORデータ作成で埋め尽くされます
    //
    //                     ※この関数では、[KSM02(測定項目)]から読込むか
    //                     　[測定Grid一番左のロット(測定項目)]から読込むかを判断して
    //                     　中心測定項目を決定します。
    AnsiString	sLot;
	int 		iCol;
    bool		bUseKSD01;
    AnsiString	sDTKSHIN1_SZ,sDTKSHIN2_SZ,sDTKSHIN3_SZ,sDTKSHIN4_SZ,sDTKSHIN5_SZ,sDTKSHIN6_SZ;
    AnsiString sLot_Where;

    sLot = "";
    for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
		if(  Form1->SGr_tSOKU->Cells[iCol][0].Trim().Length() != 0 )
		{
	    	sLot += "'" + Form1->SGr_tSOKU->Cells[iCol][0] + "',";
		}
	}
    sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
    for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
		if(  Form1->SGr_tSOKU->Cells[iCol][0].Trim().Length() != 0 )
		{
            sLot_Where += "( LOTNO='" + Form1->SGr_tSOKU->Cells[iCol][0] + "' AND ";
            sLot_Where += " HINBAN='" + Form1->SGr_tSOKU->Cells[iCol][1] + "') OR ";
		}
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

    sBuf = "SELECT * FROM KSD01 WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";
    //sBuf += " AND LOTNO IN (" + sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";

	// Initial Query
    Form1->Query3->Close();
    Form1->Query3->SQL->Clear();
    Form1->Query3->SQL->Add(sBuf);
    Form1->Query3->Open();
    Form1->Query3->Active = true;

    // 検索したロット数と検索結果のロット数が違えば未測定ロットが含まれていると判断する
    iCol = 0;
	while(Form1->Query3->Eof == false)
	{
		if(VarIsNull(Form1->Query3->FieldValues["LOTNO"])!=true)
       	{
		    iCol++ ;
		}
		Form1->Query3->Next();
	}

    if( iCol < Form1->SGr_tSOKU->ColCount ){
    	bUseKSD01 = false;
    }
    else {
    	bUseKSD01 = true;

		Form1->Query3->First();

        sLot = Form1->Query3->FieldValues["LOTNO"];

        sDTKSHIN1_SZ = "";
        sDTKSHIN2_SZ = "";
        sDTKSHIN3_SZ = "";
        sDTKSHIN4_SZ = "";
        sDTKSHIN5_SZ = "";
        sDTKSHIN6_SZ = "";
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN1_SZ"])!=true) {
		    sDTKSHIN1_SZ = Form1->Query3->FieldValues["DTKSHIN1_SZ"];
		}
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN2_SZ"])!=true) {
		    sDTKSHIN2_SZ = Form1->Query3->FieldValues["DTKSHIN2_SZ"];
		}
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN3_SZ"])!=true) {
		    sDTKSHIN3_SZ = Form1->Query3->FieldValues["DTKSHIN3_SZ"];
		}
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN4_SZ"])!=true) {
		    sDTKSHIN4_SZ = Form1->Query3->FieldValues["DTKSHIN4_SZ"];
		}
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN5_SZ"])!=true) {
		    sDTKSHIN5_SZ = Form1->Query3->FieldValues["DTKSHIN5_SZ"];
		}
		if(VarIsNull(Form1->Query3->FieldValues["DTKSHIN6_SZ"])!=true) {
		    sDTKSHIN6_SZ = Form1->Query3->FieldValues["DTKSHIN6_SZ"];
		}

    }

    Form1->Query3->Close();


    iSOZAI_SYKA_KOMKCNT = 0;
//事前に読み込んだKSM01の素材用得意先品番をKSM02の抽出条件に追加
	for(i1=0;i1<6;i1++)
	{
		switch( i1 )
		{
		case 0:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN1_SZ;
    		}
            else{
            	sDTKSHIN = pKSM01_DATA.DTKSHIN1_SZ;
			}
            break;
		case 1:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN2_SZ;
    		}
            else{
    			sDTKSHIN = pKSM01_DATA.DTKSHIN2_SZ;
			}
			break;
		case 2:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN3_SZ;
    		}
            else{
    			sDTKSHIN = pKSM01_DATA.DTKSHIN3_SZ;
			}
			break;
		case 3:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN4_SZ;
    		}
            else{
    			sDTKSHIN = pKSM01_DATA.DTKSHIN4_SZ;
			}
			break;
		case 4:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN5_SZ;
    		}
            else{
    			sDTKSHIN = pKSM01_DATA.DTKSHIN5_SZ;
			}
			break;
		case 5:
            if( bUseKSD01 ){
            	sDTKSHIN = sDTKSHIN6_SZ;
    		}
            else{
    			sDTKSHIN = pKSM01_DATA.DTKSHIN6_SZ;
			}
			break;
        default:
			break;
        }
		if( sDTKSHIN.Trim().Length() == 0 ) break;
//得意先品番をキーにして素材の項目数を抽出する
        if( bUseKSD01 ){
        	sBuf  = "SELECT * FROM KSD02";
			sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
			sBuf += " AND LOTNO ='" + sLot + "'";
			sBuf += " AND HINBAN_SK ='" + sDTKSHIN + "'";
    		sBuf += " AND SKB_NO = 1" ;                                      //素材検査項目
		}
        else {
        	sBuf  = "SELECT * FROM KSM02";
			sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
			sBuf += " AND HINBAN_SK ='" + sDTKSHIN + "'";
			sBuf += " AND REVCNT = 0" ;
    		sBuf += " AND SKB_NO = 1" ;                                      //素材検査項目
        }
		sBuf += " ORDER BY KIKI_NO, KOMK_NM, KOMK_SUB, UNQ_NO";

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
		Form1->Query3->Close();
		Form1->Query3->SQL->Clear();
		Form1->Query3->SQL->Add(sBuf);
		Form1->Query3->Open();
		Form1->Query3->Active = true;

//製品規格明細の読み取り
    	while( Form1->Query3->Eof == false )
	    {
        //品番
    	    if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
	        {
        	    sBuf  	= Form1->Query3->FieldValues["HINBAN_SK"];                        	//品番（出荷時はこれをキーにする）
        	    strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].HINBAN_SK  	,sBuf.c_str());
            }
        //測定項目Ｎｏ
    	    if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NO"]) != true )
	        {
    	        sBuf	= Form1->Query3->FieldValues["KOMK_NO"];
    	        strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KOMK_NO		,sBuf.c_str());
            }
        //測定項目名称
    	    if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NM"]) != true )
	        {
           		sBuf   	= Form1->Query3->FieldValues["KOMK_NM"];
	            strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KOMK_NM    	,sBuf.c_str());
            }
        //測定項目サブ名称
    	    if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
	        {
    	        sBuf = Form1->Query3->FieldValues["KOMK_SUB"];
        	    strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KOMK_SUB	,sBuf.c_str());
	        }
        //測定機器Ｎｏ
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NO"]) != true )
	        {
		        sBuf    = Form1->Query3->FieldValues["KIKI_NO"];
    		    strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKI_NO    ,sBuf.c_str());
	        }
        //測定機器名称
			if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NM"]) != true )
	        {
    	    	sBuf    = Form1->Query3->FieldValues["KIKI_NM"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKI_NM    ,sBuf.c_str());
	        }
        //単位
			if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["TANI"]) != true )
        	{
	        	sBuf   	= Form1->Query3->FieldValues["TANI"];
    	    	strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].TANI       ,sBuf.c_str());
			}
        //規格タイプ
	        if ( VarIsNull(Form1->Query3->FieldValues["KIKA_TYPE"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_TYPE"]) != true )
    	    {
        		sBuf  = Form1->Query3->FieldValues["KIKA_TYPE"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_TYPE  ,sBuf.c_str());
			}
        //規格種類
	        if ( VarIsNull(Form1->Query3->FieldValues["KIKA_KIND"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_KIND"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_KIND"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_KIND  ,sBuf.c_str());
			}
        //規格小数点以下桁数
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_DECI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_DECI"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_DECI"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_DECI  ,sBuf.c_str());
			}
        //規格値１
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM1"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_NUM1"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_NUM1  ,sBuf.c_str());
			}
        //規格値２
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM2"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_NUM2"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_NUM2 ,sBuf.c_str());
			}
        //規格値３
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM3"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_NUM3"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_NUM3  ,sBuf.c_str());
			}
        //規格値文字
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_STR"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_STR"]) != true )
	        {
    	    	sBuf   = Form1->Query3->FieldValues["KIKA_STR"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_STR   ,sBuf.c_str());
			}
        //規格値サブ１
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB1"]) != true )
	        {
    	    	sBuf  = Form1->Query3->FieldValues["KIKA_SUB1"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_SUB1  ,sBuf.c_str());
			}
        //規格値サブ２
    	    if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB2"]) != true )
        	{
		        sBuf  = Form1->Query3->FieldValues["KIKA_SUB2"];
    		    strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_SUB2  ,sBuf.c_str());
        	}
        //規格値サブ３
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB3"]) != true )
    	    {
        		sBuf  = Form1->Query3->FieldValues["KIKA_SUB3"];
        		strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].KIKA_SUB3  ,sBuf.c_str());
			}
        //測定指示ｎ数
    	    if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["SOKU_SU"]) != true )
        	{
	        	sBuf    = Form1->Query3->FieldValues["SOKU_SU"];
    	    	strcpy(pSOZAI_SYKA_DATA[iSOZAI_SYKA_KOMKCNT].SOKU_SU    ,sBuf.c_str());
			}
	        iSOZAI_SYKA_KOMKCNT ++;                                              //項目数
    	    Form1->Query3->Next();
		}
    }
	Form1->Query3->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：KSD01を読み取ります。
//
//  機能説明
//    測定実績データを読み取りバッファに値を代入します。
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
void __fastcall TForm1::GET_SOZAI_KSD01(void)
{
	AnsiString sTempLot,sBuf;
    iSOZAI_RIRE_LOT = 0;
    AnsiString sLot_Where;

    //出荷検査にあるロットを抽出してNOTの条件にする
	sTempLot = "";
    for( i1 = 0;i1 < Form1->iRIRE_CNT ; i1++)
	{
		sTempLot += "'" + Form1->sRIREKI_LOT->Strings[i1] + "',";
	}
    sTempLot = sTempLot.SubString(1,sTempLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
    for( i1 = 0;i1 < Form1->iRIRE_CNT ; i1++)
	{
        sLot_Where += "( LOTNO='" + Form1->sRIREKI_LOT->Strings[i1] + "' AND ";
        sLot_Where += " HINBAN='" + Form1->sRIREKI_HIN->Strings[i1] + "') OR ";
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

    //得意先品番をキーにして必要ロットの取得をする（履歴数分）
	sBuf = "SELECT * FROM KSD01";
    sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
    if( sTempLot.Length() > 3 ) {
    	//sBuf += " AND LOTNO IN ("+ sTempLot + ")";
        sBuf += " AND (";
        sBuf += sLot_Where;
        sBuf += " )";
    }
    sBuf += " ORDER BY UPDYMD, UPDTIM DESC";

    //For Debug
    if( iDEBUG == 1 )
    {
	    ClpBrd = Clipboard();
	    ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
	// Initial Query
    Form1->Query3->Close();
    Form1->Query3->SQL->Clear();
    Form1->Query3->SQL->Add(sBuf);
    Form1->Query3->Open();
    Form1->Query3->Active = true;

    //同一品番の過去履歴ロットの抽出
	iSOZAI_RIRE_LOT = 0;
    if( SGr_vSOKU_SOZAI->RowCount > 1 )
    {
        while( Form1->Query3->Eof == false )
        {
    	    strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN	,"");
           	strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].LOTNO	,"");

        //得意先品番
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN"]) != true)
            {
            	sBuf 	= Form1->Query3->FieldValues["DTKSHIN"];
	            strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN ,sBuf.c_str());
    		}
        //ロットＮｏ
            if ( VarIsNull(Form1->Query3->FieldValues["LOTNO"]) != true)
            {
    	        sBuf 	= Form1->Query3->FieldValues["LOTNO"];
            	strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].LOTNO ,sBuf.c_str());
	    	}
        //素材用得意先品番１
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN1_SZ"]) != true)
            {
	            sBuf 	= Form1->Query3->FieldValues["DTKSHIN1_SZ"];
    	        strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN1_SZ ,sBuf.c_str());
    		}
        //素材用得意先品番２
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN2_SZ"]) != true)
            {
        	    sBuf 	= Form1->Query3->FieldValues["DTKSHIN2_SZ"];
    	        strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN2_SZ ,sBuf.c_str());
	    	}
        //素材用得意先品番３
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN3_SZ"]) != true)
            {
        	    sBuf 	= Form1->Query3->FieldValues["DTKSHIN3_SZ"];
            	strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN3_SZ ,sBuf.c_str());
    		}
        //素材用得意先品番４
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN4_SZ"]) != true)
            {
	            sBuf 	= Form1->Query3->FieldValues["DTKSHIN4_SZ"];
        	    strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN4_SZ ,sBuf.c_str());
	    	}
        //素材用得意先品番５
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN5_SZ"]) != true)
            {
            	sBuf 	= Form1->Query3->FieldValues["DTKSHIN5_SZ"];
	            strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN5_SZ ,sBuf.c_str());
    		}
        //素材用得意先品番６
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN6_SZ"]) != true)
            {
    	        sBuf 	= Form1->Query3->FieldValues["DTKSHIN6_SZ"];
            	strcpy(pSOZAI_RIRE_LOT[iSOZAI_RIRE_LOT].DTKSHIN6_SZ ,sBuf.c_str());
	    	}
            iSOZAI_RIRE_LOT++;
            Form1->Query3->Next();
        }
    }
    Form1->Query3->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：KSD02を読み取ります。
//
//  機能説明
//    測定実績明細データを読み取りバッファに値を代入します。(ＯＲテーブル作成用)
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
void __fastcall TForm1::GET_SOZAI_KSD02(void)
{
    AnsiString sBuf,sLot;
	int iCol;
    AnsiString sLot_Where;

	sLot = "";
    for( iCol = 0;iCol < Form1->iRIRE_CNT ; iCol++)
    {
        sLot += "'" + Form1->sRIREKI_LOT->Strings[iCol] + "'," ;
    }
    for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
		if(  Form1->SGr_tSOKU->Cells[iCol][0].Trim().Length() != 0 )
		{
	    	sLot += "'" + Form1->SGr_tSOKU->Cells[iCol][0] + "',";
		}
	}
    sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
    for( iCol = 0;iCol < Form1->iRIRE_CNT ; iCol++)
    {
        sLot_Where += "( LOTNO='" + Form1->sRIREKI_LOT->Strings[iCol] + "' AND ";
        sLot_Where += " HINBAN='" + Form1->sRIREKI_HIN->Strings[iCol] + "') OR ";
    }
    for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
		if(  Form1->SGr_tSOKU->Cells[iCol][0].Trim().Length() != 0 )
		{
            sLot_Where += "( LOTNO='" + Form1->SGr_tSOKU->Cells[iCol][0] + "' AND ";
            sLot_Where += " HINBAN='" + Form1->SGr_tSOKU->Cells[iCol][1] + "') OR ";
		}
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

	sBuf = "SELECT KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK, MAX(SOKU_SU) AS SOKU_SU_MAX FROM KSD02";
    sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
    sBuf += " AND SKB_NO = 1";                        //出荷検査項目、材料証明項目
    //sBuf += " AND LOTNO IN (";
	//sBuf += sLot;
    //sBuf += " )";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";
    sBuf += " GROUP BY KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK";
    sBuf += " ORDER BY KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK";

    //For Debug
    if( iDEBUG == 1 )
    {
	    ClpBrd = Clipboard();
	    ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
    // Initial Query
	Form1->Query3->Close();
    Form1->Query3->SQL->Clear();
    Form1->Query3->SQL->Add(sBuf);
    Form1->Query3->Open();
    Form1->Query3->Active = true;

    //対象過去履歴の検索　STEP1
	iSOZAI_RIRE_KOMKCNT = 0;
    while( Form1->Query3->Eof == false )
    {
    //測定指示ｎ数（履歴最大件数）
    	if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU_MAX"]) != true)
        {
        	sBuf = Form1->Query3->FieldValues["SOKU_SU_MAX"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].SOKU_SU ,sBuf.c_str());
        }
    //測定機器Ｎｏ
        if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true)
        {
        	sBuf = Form1->Query3->FieldValues["KIKI_NO"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].KIKI_NO ,sBuf.c_str());
        }
    //測定項目Ｎｏ
        if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true)
        {
        	sBuf = Form1->Query3->FieldValues["KOMK_NO"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].KOMK_NO ,sBuf.c_str());
        }
    //測定項目名称
		if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true)
        {
        	sBuf = Form1->Query3->FieldValues["KOMK_NM"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].KOMK_NM ,sBuf.c_str());
        }
    //測定項目サブ名称
        if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
        {
        	sBuf = Form1->Query3->FieldValues["KOMK_SUB"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].KOMK_SUB ,sBuf.c_str());
        }
    //単位 2002/10/20 A.Tamura
        if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true )
        {
        	sBuf = Form1->Query3->FieldValues["TANI"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].TANI ,sBuf.c_str());
        }
    //品番
        if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
        {
        	sBuf = Form1->Query3->FieldValues["HINBAN_SK"];
            strcpy(pSOZAI_RIRE_DATA[iSOZAI_RIRE_KOMKCNT].HINBAN_SK ,sBuf.c_str());
        }
        iSOZAI_RIRE_KOMKCNT ++;                                              //項目数
        Form1->Query3->Next();
    }
    Form1->Query3->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：KSD02を読み取ります。(２回目）
//
//  機能説明
//    測定実績明細データを読み取りバッファに値を代入します。(ＯＲテーブル作成用)
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
void __fastcall TForm1::GET_SOZAI_KSD02_SECOND(void)
{
	AnsiString sLot,sBuf;
	int iCol;
    AnsiString sLot_Where;

	sLot = "";
    for( iCol = 0;iCol < Form1->iRIRE_CNT ; iCol++)
    {
        Form1->SGr_tRIRE->Cells[iCol][0] = Form1->sRIREKI_LOT->Strings[iCol];
    }
	for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
        if( Form1->SGr_tSOKU->Cells[iCol][0].Length() != 0 )
        {
    	    sLot += "'" + Form1->SGr_tSOKU->Cells[iCol][0] + "',";
        }
	}
    sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
	for(iCol = 0 ; iCol < Form1->SGr_tSOKU->ColCount ; iCol++)
	{
        if( Form1->SGr_tSOKU->Cells[iCol][0].Length() != 0 )
        {
            sLot_Where += "( LOTNO='" + Form1->SGr_tSOKU->Cells[iCol][0] + "' AND ";
            sLot_Where += " HINBAN='" + Form1->SGr_tSOKU->Cells[iCol][1] + "') OR ";
        }
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

    sBuf  = "SELECT KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK, MAX(SOKU_SU) AS SOKU_SU_MAX FROM KSD02";
    sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
    sBuf += " AND SKB_NO = 1";                        		//出荷検査項目、材料証明項目
    //sBuf += " AND LOTNO IN ("+ sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";
    sBuf += " GROUP BY KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK";
    sBuf += " ORDER BY KIKI_NO, KOMK_NO, KOMK_NM, KOMK_SUB, TANI, HINBAN_SK";

	//For Debug
        if( iDEBUG == 1 )
        {
		    ClpBrd = Clipboard();
		    ClpBrd->Open();
    	    ClpBrd->SetTextBuf(sBuf.c_str());
    	    ClpBrd->Close();
        }
	// Initial Query
        Form1->Query3->Close();
        Form1->Query3->SQL->Clear();
        Form1->Query3->SQL->Add(sBuf);
        Form1->Query3->Open();
        Form1->Query3->Active = true;

	//出荷検査ロット中で検査済みロットの検索
		iSOZAI_KOMKCNT2 = 0;
		while( Form1->Query3->Eof == false )
    	{
        	if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU_MAX"]) != true)
        	{
	    		sBuf = Form1->Query3->FieldValues["SOKU_SU_MAX"];
        		strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].SOKU_SU ,sBuf.c_str());
			}
        	if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true)
        	{
        		sBuf = Form1->Query3->FieldValues["KIKI_NO"];
        		strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].KIKI_NO ,sBuf.c_str());
			}
        	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true)
        	{
	        	sBuf = Form1->Query3->FieldValues["KOMK_NO"];
	        	strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].KOMK_NO ,sBuf.c_str());
			}

        	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true)
        	{
        		sBuf = Form1->Query3->FieldValues["KOMK_NM"];
            	strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].KOMK_NM ,sBuf.c_str());
        	}
        	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
        	{
        		sBuf = Form1->Query3->FieldValues["KOMK_SUB"];
            	strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].KOMK_SUB ,sBuf.c_str());
        	}
        	if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true )
        	{
        		sBuf = Form1->Query3->FieldValues["TANI"];
            	strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].TANI ,sBuf.c_str());
        	}
        	if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
        	{
        		sBuf = Form1->Query3->FieldValues["HINBAN_SK"];
            	strcpy(pSOZAI_RIRE_DATA[iSOZAI_KOMKCNT2].HINBAN_SK ,sBuf.c_str());
        	}
        	iSOZAI_KOMKCNT2 ++;                                              //項目数
        	Form1->Query3->Next();
    	}
    	Form1->Query3->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材検査項目の単位などの情報を読み取ります。
//
//  機能説明
//    ＯＲテーブルを参照しKSM02もしくはKSD02から単位、規格などの読み取りを行います。
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
void __fastcall TForm1::GET_SOZAI_TANI(void)
{
    AnsiString sBuf;
	AnsiString KOMK_NM,KIKI_NO;
    //double dMAX,dMIN;
	double dHalf1,dHalf2;       //最大最小で見るのではなく、規格の中心の値を見て判断

//総ｎ数の算出
    iSOZAI_SOKUCNT  = 0;
    for(i1=0 ; i1 < iSOZAI_ORCNT;i1++)
    {
        iSOZAI_SOKUCNT += AnsiString(pSOZAI_OR_DATA[i1].SOKU_SU).ToIntDef(0);
    }

//測定機器名称、項目名称、単位、規格の抽出（最新のものを表示する）

    for(i1=0;i1<iSOZAI_ORCNT;i1++)
    {
        sBuf = "SELECT * FROM KSM02";
        sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
        sBuf += " AND KIKI_NO = " + AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO);
        if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM).Length() != 0)
        {
            sBuf += " AND KOMK_NM ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM) + "'";
        }
        else
        {
            sBuf += " AND KOMK_NM IS NULL";
        }
        if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB).Length() != 0)
        {
            sBuf += " AND KOMK_SUB ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB) + "'";
        }
        else
        {
            sBuf += " AND KOMK_SUB IS NULL";
        }
        if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO).Length() != 0)
        {
            sBuf += " AND KOMK_NO ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO) + "'";
        }
        else
        {
            sBuf += " AND KOMK_NO IS NULL";
        }
        // 2003/10/20 A.Tamura 比較条件に単位を追加します（この前にORデータに単位も設定している）
        //                     KSM02にブラシ厚さ[mm][Cpk]が無い時に、
        //                     KSD02にこの２つがあると正しく表示されないエラーを回避
        if(AnsiString(pSOZAI_OR_DATA[i1].TANI).Length() != 0)
        {
            sBuf += " AND TANI ='"  + AnsiString(pSOZAI_OR_DATA[i1].TANI) + "'";
        }
        else
        {
            sBuf += " AND TANI IS NULL";
        }
//素材のHI、LOの見分けがつかなかったのでSQLを修正しました。
//REV. STEART

// 2003/11/24 A.Tamura テスト的にコメント
        if(AnsiString(pSOZAI_OR_DATA[i1].HINBAN_SK).Length() != 0)
        {
            sBuf += " AND HINBAN_SK ='"  + AnsiString(pSOZAI_OR_DATA[i1].HINBAN_SK) + "'";
        }
        else
        {
            sBuf += " AND HINBAN_SK IS NULL";
        }
//REV. END
		sBuf += " AND REVCNT = 0";
        sBuf += " AND SKB_NO = 1";                        //出荷検査項目、材料証明項目

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
        Form1->Query3->Close();
        Form1->Query3->SQL->Clear();
        Form1->Query3->SQL->Add(sBuf);
        Form1->Query3->Open();
        Form1->Query3->Active = true;
        if( Form1->Query3->Eof == false )
        {
        	if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN"]) != true)
			{
	        	sBuf 		= Form1->Query3->FieldValues["DTKSHIN"];		//得意先品番
    	    	strcpy(pSOZAI_OR_DATA[i1].DTKSHIN		,sBuf.c_str());
			}
        	if ( VarIsNull(Form1->Query3->FieldValues["REVCNT"]) != true)
			{
        		sBuf 		= Form1->Query3->FieldValues["REVCNT"];      	//改訂番号
	        	strcpy(pSOZAI_OR_DATA[i1].REVCNT		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["UNQ_NO"]) != true)
            {
				sBuf 		= Form1->Query3->FieldValues["UNQ_NO"];    		//明細NO
    	    	strcpy(pSOZAI_OR_DATA[i1].UNQ_NO		,sBuf.c_str());
			}
        	if ( VarIsNull(Form1->Query3->FieldValues["ORDER_NO"]) != true)
            {
				sBuf 		= Form1->Query3->FieldValues["ORDER_NO"];  		//表示・印刷順
        		strcpy(pSOZAI_OR_DATA[i1].ORDER_NO		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["SKB_NO"]) != true)
            {
				sBuf 		= Form1->Query3->FieldValues["SKB_NO"];    		//識別NO
        		strcpy(pSOZAI_OR_DATA[i1].SKB_NO		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["HINBAN_SK"];  	//品番
        		strcpy(pSOZAI_OR_DATA[i1].HINBAN_SK		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NO"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KOMK_NO"];   		//測定項目NO
        		strcpy(pSOZAI_OR_DATA[i1].KOMK_NO		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NM"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KOMK_NM"];  		//測定項目名称
				strcpy(pSOZAI_OR_DATA[i1].KOMK_NM		,sBuf.c_str());
            }
			if ( VarIsNull(Form1->Query3->FieldValues["KOMK_ENG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_ENG"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KOMK_ENG"]; 		//測定項目名称（英語）
				strcpy(pSOZAI_OR_DATA[i1].KOMK_ENG		,sBuf.c_str());
            }
			sBuf = " ";
        	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KOMK_SUB"];   	//測定項目サブ名称
				strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB		,sBuf.c_str());
            }
            sBuf = " ";
        	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KOMK_SUB_ENG"];	//測定項目サブ名称（英語）
				strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NO"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KIKI_NO"];     	//測定機器NO
				strcpy(pSOZAI_OR_DATA[i1].KIKI_NO		,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NM"]) != true )
            {
				sBuf 		= Form1->Query3->FieldValues["KIKI_NM"];  		//測定機器名称
				strcpy(pSOZAI_OR_DATA[i1].KIKI_NM		,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["TANI"]) != true )
            {
            	sBuf 		= Form1->Query3->FieldValues["TANI"];         	//単位
            	strcpy(pSOZAI_OR_DATA[i1].TANI			,sBuf.c_str());
   			}
            sBuf = " ";
           	if ( VarIsNull(Form1->Query3->FieldValues["KIKA_TYPE"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_TYPE"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_TYPE"];      	//規格タイプ
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_TYPE	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_KIND"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_KIND"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_KIND"];        	//規格種類
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_KIND	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_DECI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_DECI"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_DECI"];      	//規格小数点以下桁数
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_DECI	,sBuf.c_str());
			}
            sBuf = " ";
        	if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM1"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_NUM1"];     		//規格値１
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM1	,sBuf.c_str());
			}
            sBuf = " ";
        	if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM2"]) != true )
            {
	            sBuf 	= Form1->Query3->FieldValues["KIKA_NUM2"];        	//規格値２
    	        strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM2	,sBuf.c_str());
			}
            sBuf = " ";
        	if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM3"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_NUM3"];        	//規格値３
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM3	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_STR"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_STR"]) != true )
            {
            	sBuf  	= Form1->Query3->FieldValues["KIKA_STR"];        	//規格値文字
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_STR		,sBuf.c_str());
   			}
            sBuf = " ";
           	if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB1"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_SUB1"];       	//規格値サブ１
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB1	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB2"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_SUB2"];          //規格値サブ２
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB2	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB3"]) != true )
            {
            	sBuf 	= Form1->Query3->FieldValues["KIKA_SUB3"];         	//規格値サブ３
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB3	,sBuf.c_str());
            }
            sBuf = " ";
            //指示ｎ数は出来上がっているので読まない
			//if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["SOKU_SU"]) != true )
            //{
            // 	sBuf 	= Form1->Query3->FieldValues["SOKU_SU"];            //測定指示ｎ数
            //	strcpy(pSOZAI_OR_DATA[i1].SOKU_SU	,sBuf.c_str());
            //}
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["SOKU_FLG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["SOKU_FLG"]) != true )
            {
             	sBuf 	= Form1->Query3->FieldValues["SOKU_FLG"];        	//測定項目の有無
            	strcpy(pSOZAI_OR_DATA[i1].SOKU_FLG	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["TOKU_FLG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["TOKU_FLG"]) != true )
            {
             	sBuf 	= Form1->Query3->FieldValues["TOKU_FLG"];       	//特別項目の有無
            	strcpy(pSOZAI_OR_DATA[i1].TOKU_FLG	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["KIKA_PRT"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_PRT"]) != true )
            {
             	sBuf 	= Form1->Query3->FieldValues["KIKA_PRT"];     		//上限下限値の印刷
            	strcpy(pSOZAI_OR_DATA[i1].KIKA_PRT	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["VALUE_TYPE"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["VALUE_TYPE"]) != true )
            {
             	sBuf 	= Form1->Query3->FieldValues["VALUE_TYPE"];         //測定値表現
            	strcpy(pSOZAI_OR_DATA[i1].VALUE_TYPE	,sBuf.c_str());
            }
            sBuf = " ";
			if ( VarIsNull(Form1->Query3->FieldValues["VALUE_DECI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["VALUE_DECI"]) != true )
            {
             	sBuf 	= Form1->Query3->FieldValues["VALUE_DECI"];         //測定値小数点以下桁数
            	strcpy(pSOZAI_OR_DATA[i1].VALUE_DECI	,sBuf.c_str());
			}
        }
        else
        {
            sBuf = "SELECT * FROM KSD02";
			//2003.05.12 E.Takase Add↓
            sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
			//2003.05.12 E.Takase Add↑
			//2003.05.12 E.Takase Add コメント↓
            //sBuf += " WHERE DTKSHIN ='" + Form1->Cmb_DTKSHIN->Text + "'";
			//2003.05.12 E.Takase Add コメント↑
            sBuf += " AND KIKI_NO = " + AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO) ;
            if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM).Length() != 0)
            {
                sBuf += " AND KOMK_NM ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM) + "'";
            }
            else
            {
                sBuf += " AND KOMK_NM IS NULL";
            }
            if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB).Length() != 0)
            {
            	sBuf += " AND KOMK_SUB ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB) + "'";
// 2003/11/18 A.Tamura 以下の行はなぜコメントだったのでしょうか？
//                     サブ名称がHI,LOなどで分かれるとき、不具合が出ていますので
//                     以下の処理を上記コード(1行)に変更します。
//                sBuf += " AND KOMK_SUB ='"  + sBuf1 + "'";	//履歴のロットの集合sBuf1
            }
            else
            {
                sBuf += " AND KOMK_SUB IS NULL";
            }
            // 2003/10/20 A.Tamura 比較条件に単位を追加します（この前にORデータに単位も設定している）
            //                     KSM02にブラシ厚さ[mm][Cpk]が無い時に、
            //                     KSD02にこの２つがあると正しく表示されないエラーを回避
            if(AnsiString(pSOZAI_OR_DATA[i1].TANI).Length() != 0)
            {
                sBuf += " AND TANI ='"  + AnsiString(pSOZAI_OR_DATA[i1].TANI) + "'";
            }
            else
            {
                sBuf += " AND TANI IS NULL";
            }
            // 2003/11/24 A.Tamura 別のHINBAN_SKで上書きされてしまう測定項目が出ない
        	if(AnsiString(pSOZAI_OR_DATA[i1].HINBAN_SK).Length() != 0)
        	{
        	    sBuf += " AND HINBAN_SK ='"  + AnsiString(pSOZAI_OR_DATA[i1].HINBAN_SK) + "'";
        	}
        	else
        	{
        	    sBuf += " AND HINBAN_SK IS NULL";
        	}
            sBuf += " AND SKB_NO = 1";                        //出荷検査項目、材料証明項目
            sBuf += " ORDER BY UPDYMD DESC, UPDTIM DESC";

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
            Form1->Query3->Close();
            Form1->Query3->SQL->Clear();
            Form1->Query3->SQL->Add(sBuf);
            Form1->Query3->Open();
            Form1->Query3->Active = true;
		//KSM02に目的データがない場合は履歴読み込み（ＫＳＤ０２）
            if( Form1->Query3->Eof == false )
            {
				if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["DTKSHIN"]) != true )
				{
        			sBuf 		= Form1->Query3->FieldValues["DTKSHIN"];		//得意先品番
        			strcpy(pSOZAI_OR_DATA[i1].DTKSHIN		,sBuf.c_str());
				}
				if ( VarIsNull(Form1->Query3->FieldValues["UNQ_NO"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["UNQ_NO"]) != true )
				{
        			sBuf 		= Form1->Query3->FieldValues["UNQ_NO"];    		//明細NO
        			strcpy(pSOZAI_OR_DATA[i1].UNQ_NO		,sBuf.c_str());
				}
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["ORDER_NO"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["ORDER_NO"]) != true )
        	    {
        			sBuf 		= Form1->Query3->FieldValues["ORDER_NO"];  		//表示・印刷順
        			strcpy(pSOZAI_OR_DATA[i1].ORDER_NO		,sBuf.c_str());
				}
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["SKB_NO"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["SKB_NO"]) != true )
        	    {
        			sBuf 		= Form1->Query3->FieldValues["SKB_NO"];    		//識別NO
        			strcpy(pSOZAI_OR_DATA[i1].SKB_NO		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
        	    {
        			sBuf 		= Form1->Query3->FieldValues["HINBAN_SK"];  	//品番
        			strcpy(pSOZAI_OR_DATA[i1].HINBAN_SK		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NO"]) != true )
        	    {
        			sBuf 		= Form1->Query3->FieldValues["KOMK_NO"];   		//測定項目NO
        			strcpy(pSOZAI_OR_DATA[i1].KOMK_NO		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NM"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KOMK_NM"];  		//測定項目名称
					strcpy(pSOZAI_OR_DATA[i1].KOMK_NM		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KOMK_ENG"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KOMK_ENG"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KOMK_ENG"]; 		//測定項目名称（英語）
					strcpy(pSOZAI_OR_DATA[i1].KOMK_ENG		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KOMK_SUB"];   	//測定項目サブ名称
					strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KOMK_SUB_ENG"];	//測定項目サブ名称（英語）
					strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NO"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KIKI_NO"];     	//測定機器NO
					strcpy(pSOZAI_OR_DATA[i1].KIKI_NO		,sBuf.c_str());
                }
				sBuf = " ";
                if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NM"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NM"]) != true )
        	    {
					sBuf 		= Form1->Query3->FieldValues["KIKI_NM"];  		//測定機器名称
					strcpy(pSOZAI_OR_DATA[i1].KIKI_NM		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["TANI"]) != true )
        	    {
            		sBuf 		= Form1->Query3->FieldValues["TANI"];         	//単位
            		strcpy(pSOZAI_OR_DATA[i1].TANI			,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_TYPE"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_TYPE"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_TYPE"];      	//規格タイプ
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_TYPE	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_KIND"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_KIND"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_KIND"];        	//規格種類
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_KIND	,sBuf.c_str());
				}
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_DECI"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_DECI"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_DECI"];      	//規格小数点以下桁数
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_DECI	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM1"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM1"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_NUM1"];     		//規格値１
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM1	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM2"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM2"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_NUM2"];        	//規格値２
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM2	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM3"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM3"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_NUM3"];        	//規格値３
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM3	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_STR"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_STR"]) != true )
        	    {
            		sBuf  	= Form1->Query3->FieldValues["KIKA_STR"];        	//規格値文字
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_STR		,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB1"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB1"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_SUB1"];       	//規格値サブ１
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB1	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB2"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB2"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_SUB2"];          //規格値サブ２
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB2	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB3"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB3"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_SUB3"];         	//規格値サブ３
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB3	,sBuf.c_str());
                }
				sBuf = " ";
				//if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU"]) != true
    	        //&& VarIsEmpty(Form1->Query3->FieldValues["SOKU_SU"]) != true )
        	    //{
            	//	sBuf 	= Form1->Query3->FieldValues["SOKU_SU"];            //測定指示ｎ数
            	//	strcpy(pSOZAI_OR_DATA[i1].SOKU_SU	,sBuf.c_str());
                //}
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["SOKU_FLG"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["SOKU_FLG"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["SOKU_FLG"];        	//測定項目の有無
            		strcpy(pSOZAI_OR_DATA[i1].SOKU_FLG	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["TOKU_FLG"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["TOKU_FLG"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["TOKU_FLG"];       	//特別項目の有無
            		strcpy(pSOZAI_OR_DATA[i1].TOKU_FLG	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["KIKA_PRT"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["KIKA_PRT"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["KIKA_PRT"];     		//上限下限値の印刷
            		strcpy(pSOZAI_OR_DATA[i1].KIKA_PRT	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["VALUE_TYPE"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["VALUE_TYPE"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["VALUE_TYPE"];         //測定値表現
            		strcpy(pSOZAI_OR_DATA[i1].VALUE_TYPE	,sBuf.c_str());
                }
				sBuf = " ";
				if ( VarIsNull(Form1->Query3->FieldValues["VALUE_DECI"]) != true
    	        && VarIsEmpty(Form1->Query3->FieldValues["VALUE_DECI"]) != true )
        	    {
            		sBuf 	= Form1->Query3->FieldValues["VALUE_DECI"];         //測定値小数点以下桁数
            		strcpy(pSOZAI_OR_DATA[i1].VALUE_DECI	,sBuf.c_str());
				}
            }
        }

/* 2003/11/24 A.Tamura テストコメント              上記の処理で設定済みでは...ないか？
        //一番左端の規格を読み取る
        sBuf = "SELECT * FROM KSD02";
        //2003.05.12 E.Takase Add↓
        sBuf += " WHERE DTKSHIN ='" + Form1->sNowDTKSHIN + "'";
        //2003.05.12 E.Takase Add↑
        //2003.05.12 E.Takase Add コメント↓
        //sBuf += " WHERE DTKSHIN ='" + Form1->Cmb_DTKSHIN->Text + "'";
        //2003.05.12 E.Takase Add コメント↑
        sBuf += " AND KIKI_NO = " + AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO) ;
        if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM).Length() != 0)
        {
            sBuf += " AND KOMK_NM ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NM) + "'";
        }
        else
        {
            sBuf += " AND KOMK_NM IS NULL";
        }
        if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB).Length() != 0)
        {
            sBuf += " AND KOMK_SUB ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB) + "'";
// 2003/11/18 A.Tamura 以下の行はなぜコメントだったのでしょうか？
//                     サブ名称がHI,LOなどで分かれるとき、不具合が出ていますので
//                     以下の処理を上記コード(1行)に変更します。
//                sBuf += " AND KOMK_SUB ='"  + sBuf1 + "'";	//履歴のロットの集合sBuf1
        }
        else
        {
            sBuf += " AND KOMK_SUB IS NULL";
        }
//単位が違う場合に対応(2003/09/01)
        if(AnsiString(pSOZAI_OR_DATA[i1].TANI).Length() != 0)
        {
            sBuf += " AND TANI ='"  + AnsiString(pSOZAI_OR_DATA[i1].TANI) + "'";
        }
        else
        {
            sBuf += " AND TANI IS NULL";
        }
        sBuf += " AND SKB_NO = 1";                        //出荷検査項目、材料証明項目
        sBuf += " AND LOTNO ='" + AnsiString(SGr_tSOKU->Cells[0][0]).Trim() + "'";
        sBuf += " ORDER BY UPDYMD DESC, UPDTIM DESC";

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
        Form1->Query3->Close();
        Form1->Query3->SQL->Clear();
        Form1->Query3->SQL->Add(sBuf);
        Form1->Query3->Open();
        Form1->Query3->Active = true;
		//KSM02に目的データがない場合は履歴読み込み（ＫＳＤ０２）
        if( Form1->Query3->Eof == false )
        {
            if ( VarIsNull(Form1->Query3->FieldValues["DTKSHIN"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["DTKSHIN"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["DTKSHIN"];		//得意先品番
                strcpy(pSOZAI_OR_DATA[i1].DTKSHIN		,sBuf.c_str());
            }
            if ( VarIsNull(Form1->Query3->FieldValues["UNQ_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["UNQ_NO"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["UNQ_NO"];    		//明細NO
                strcpy(pSOZAI_OR_DATA[i1].UNQ_NO		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["ORDER_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["ORDER_NO"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["ORDER_NO"];  		//表示・印刷順
                strcpy(pSOZAI_OR_DATA[i1].ORDER_NO		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["SKB_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["SKB_NO"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["SKB_NO"];    		//識別NO
                strcpy(pSOZAI_OR_DATA[i1].SKB_NO		,sBuf.c_str());
            }
            // 2003/11/24 A.Tamura テスト的にコメントする
            //sBuf = " ";
            //if ( VarIsNull(Form1->Query3->FieldValues["HINBAN_SK"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["HINBAN_SK"]) != true )
            //{
            //    sBuf 		= Form1->Query3->FieldValues["HINBAN_SK"];  	//品番
            //    strcpy(pSOZAI_OR_DATA[i1].HINBAN_SK		,sBuf.c_str());
            //}

            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NO"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KOMK_NO"];   		//測定項目NO
                strcpy(pSOZAI_OR_DATA[i1].KOMK_NO		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KOMK_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_NM"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KOMK_NM"];  		//測定項目名称
                strcpy(pSOZAI_OR_DATA[i1].KOMK_NM		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KOMK_ENG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_ENG"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KOMK_ENG"]; 		//測定項目名称（英語）
                strcpy(pSOZAI_OR_DATA[i1].KOMK_ENG		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KOMK_SUB"];   	//測定項目サブ名称
                strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB_ENG"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KOMK_SUB_ENG"];	//測定項目サブ名称（英語）
                strcpy(pSOZAI_OR_DATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NO"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NO"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KIKI_NO"];     	//測定機器NO
                strcpy(pSOZAI_OR_DATA[i1].KIKI_NO		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKI_NM"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKI_NM"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["KIKI_NM"];  		//測定機器名称
                strcpy(pSOZAI_OR_DATA[i1].KIKI_NM		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["TANI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["TANI"]) != true )
            {
                sBuf 		= Form1->Query3->FieldValues["TANI"];         	//単位
                strcpy(pSOZAI_OR_DATA[i1].TANI			,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_TYPE"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_TYPE"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_TYPE"];      	//規格タイプ
                strcpy(pSOZAI_OR_DATA[i1].KIKA_TYPE	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_KIND"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_KIND"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_KIND"];        	//規格種類
                strcpy(pSOZAI_OR_DATA[i1].KIKA_KIND	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_DECI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_DECI"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_DECI"];      	//規格小数点以下桁数
                strcpy(pSOZAI_OR_DATA[i1].KIKA_DECI	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM1"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_NUM1"];     		//規格値１
                strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM1	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM2"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_NUM2"];        	//規格値２
                strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM2	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_NUM3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_NUM3"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_NUM3"];        	//規格値３
                strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM3	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_STR"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_STR"]) != true )
            {
                sBuf  	= Form1->Query3->FieldValues["KIKA_STR"];        	//規格値文字
                strcpy(pSOZAI_OR_DATA[i1].KIKA_STR		,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB1"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB1"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_SUB1"];       	//規格値サブ１
                strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB1	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB2"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB2"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_SUB2"];          //規格値サブ２
                strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB2	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["KIKA_SUB3"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KIKA_SUB3"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["KIKA_SUB3"];         	//規格値サブ３
                strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB3	,sBuf.c_str());
            }
            sBuf = " ";
            //if ( VarIsNull(Form1->Query3->FieldValues["SOKU_SU"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["SOKU_SU"]) != true )
            //{
            //	sBuf 	= Form1->Query3->FieldValues["SOKU_SU"];            //測定指示ｎ数
            //	strcpy(pSOZAI_OR_DATA[i1].SOKU_SU	,sBuf.c_str());
            //}


            //sBuf = " ";
            //if ( VarIsNull(Form1->Query3->FieldValues["SOKU_FLG"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["SOKU_FLG"]) != true )
            //{
            //    sBuf 	= Form1->Query3->FieldValues["SOKU_FLG"];        	//測定項目の有無
            //    strcpy(pSOZAI_OR_DATA[i1].SOKU_FLG	,sBuf.c_str());
            //}
            //sBuf = " ";
            //if ( VarIsNull(Form1->Query3->FieldValues["TOKU_FLG"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["TOKU_FLG"]) != true )
            //{
            //    sBuf 	= Form1->Query3->FieldValues["TOKU_FLG"];       	//特別項目の有無
            //    strcpy(pSOZAI_OR_DATA[i1].TOKU_FLG	,sBuf.c_str());
            //}
            //sBuf = " ";
            //if ( VarIsNull(Form1->Query3->FieldValues["KIKA_PRT"]) != true
            //&& VarIsEmpty(Form1->Query3->FieldValues["KIKA_PRT"]) != true )
            //{
            //    sBuf 	= Form1->Query3->FieldValues["KIKA_PRT"];     		//上限下限値の印刷
            //    strcpy(pSOZAI_OR_DATA[i1].KIKA_PRT	,sBuf.c_str());
            //}
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["VALUE_TYPE"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["VALUE_TYPE"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["VALUE_TYPE"];         //測定値表現
                strcpy(pSOZAI_OR_DATA[i1].VALUE_TYPE	,sBuf.c_str());
            }
            sBuf = " ";
            if ( VarIsNull(Form1->Query3->FieldValues["VALUE_DECI"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["VALUE_DECI"]) != true )
            {
                sBuf 	= Form1->Query3->FieldValues["VALUE_DECI"];         //測定値小数点以下桁数
                strcpy(pSOZAI_OR_DATA[i1].VALUE_DECI	,sBuf.c_str());
            }
        }

        Form1->Query3->Close();
*/
    }

/////////////////////
//規格の読み込みが終了したので改めてソート（規格の昇順）を行う


/* A.T 2003/05/08
    // メモリの開放
    if( hTEMPORDATA ){
        GlobalUnlock( hTEMPORDATA );
        GlobalFree( hTEMPORDATA );
    }
	hTEMPORDATA = NULL;
    // メモリの確保
    hTEMPORDATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * 1 );
    if( hTEMPORDATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pTEMPORDATA = (struct KSM02_DATA *)GlobalLock(hTEMPORDATA);
    if( hTEMPORDATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
*/
    memset(&pTEMPORDATA,(int)NULL,sizeof(pTEMPORDATA));


/* k.y 2003.05.17
    // メモリの開放
    if( hTEMPORDATA ){
        GlobalUnlock( hTEMPORDATA );
        GlobalFree( hTEMPORDATA );
    }
	hTEMPORDATA = NULL;
    // メモリの確保
    hTEMPORDATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * 1 );
    if( hTEMPORDATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pTEMPORDATA = (struct KSM02_DATA *)GlobalLock(hTEMPORDATA);
    if( hTEMPORDATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
*/
    memset(pTEMPORDATA,0x00,sizeof(pTEMPORDATA));

//規格ソート
    //ORDER_NOで並び順のソートを行います
	for(i2 = 0; i2 < iSOZAI_ORCNT ; i2++)
	{
		for(i1 = 0; i1 < iSOZAI_ORCNT-1; i1++)
		{
//			if( AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO) == AnsiString(pSOZAI_OR_DATA[i1+1].KIKI_NO) )
//			if(1)
//			{
//    			GetSOZAI_KIKAKU(i1,&dMAX,&dMIN);
//				dHalf1 = dMAX - dMIN + dMIN;
//				dHalf1 = dMIN;
				dHalf1 = AnsiString(pSOZAI_OR_DATA[ i1 ].ORDER_NO).ToIntDef(0);
//   			GetSOZAI_KIKAKU(i1+1,&dMAX,&dMIN);
//				dHalf2 = dMAX - dMIN + dMIN;
//				dHalf2 = dMIN;
				dHalf2 = AnsiString(pSOZAI_OR_DATA[ i1+1 ].ORDER_NO).ToIntDef(0);
            if( dHalf1 > dHalf2 )
            {
			// dTEMPORDATA[0] <- dORDATA[i1]
                strcpy(pTEMPORDATA[ 0 ].DTKSHIN		, pSOZAI_OR_DATA[ i1 ].DTKSHIN);
                strcpy(pTEMPORDATA[ 0 ].UNQ_NO 		, pSOZAI_OR_DATA[ i1 ].UNQ_NO);
                strcpy(pTEMPORDATA[ 0 ].ORDER_NO 	, pSOZAI_OR_DATA[ i1 ].ORDER_NO);
			   	strcpy(pTEMPORDATA[ 0 ].SKB_NO 		, pSOZAI_OR_DATA[ i1 ].SKB_NO);
			  	strcpy(pTEMPORDATA[ 0 ].HINBAN_SK 	, pSOZAI_OR_DATA[ i1 ].HINBAN_SK);
			 	strcpy(pTEMPORDATA[ 0 ].KOMK_NO 	, pSOZAI_OR_DATA[ i1 ].KOMK_NO);
				strcpy(pTEMPORDATA[ 0 ].KOMK_NM 	, pSOZAI_OR_DATA[ i1 ].KOMK_NM);
		   		strcpy(pTEMPORDATA[ 0 ].KOMK_ENG 	, pSOZAI_OR_DATA[ i1 ].KOMK_ENG);
		  		strcpy(pTEMPORDATA[ 0 ].KOMK_SUB 	, pSOZAI_OR_DATA[ i1 ].KOMK_SUB);
		 		strcpy(pTEMPORDATA[ 0 ].KOMK_SUB_ENG, pSOZAI_OR_DATA[ i1 ].KOMK_SUB_ENG);
				strcpy(pTEMPORDATA[ 0 ].KIKI_NO 	, pSOZAI_OR_DATA[ i1 ].KIKI_NO);
	   			strcpy(pTEMPORDATA[ 0 ].KIKI_NM 	, pSOZAI_OR_DATA[ i1 ].KIKI_NM);
	  			strcpy(pTEMPORDATA[ 0 ].TANI 		, pSOZAI_OR_DATA[ i1 ].TANI);
			   	strcpy(pTEMPORDATA[ 0 ].KIKA_TYPE 	, pSOZAI_OR_DATA[ i1 ].KIKA_TYPE);
			  	strcpy(pTEMPORDATA[ 0 ].KIKA_KIND 	, pSOZAI_OR_DATA[ i1 ].KIKA_KIND);
			 	strcpy(pTEMPORDATA[ 0 ].KIKA_DECI 	, pSOZAI_OR_DATA[ i1 ].KIKA_DECI);
				strcpy(pTEMPORDATA[ 0 ].KIKA_NUM1 	, pSOZAI_OR_DATA[ i1 ].KIKA_NUM1);
		   		strcpy(pTEMPORDATA[ 0 ].KIKA_NUM2 	, pSOZAI_OR_DATA[ i1 ].KIKA_NUM2);
		  		strcpy(pTEMPORDATA[ 0 ].KIKA_NUM3 	, pSOZAI_OR_DATA[ i1 ].KIKA_NUM3);
		 		strcpy(pTEMPORDATA[ 0 ].KIKA_STR 	, pSOZAI_OR_DATA[ i1 ].KIKA_STR);
				strcpy(pTEMPORDATA[ 0 ].KIKA_SUB1 	, pSOZAI_OR_DATA[ i1 ].KIKA_SUB1);
	   			strcpy(pTEMPORDATA[ 0 ].KIKA_SUB2 	, pSOZAI_OR_DATA[ i1 ].KIKA_SUB2);
	  			strcpy(pTEMPORDATA[ 0 ].KIKA_SUB3 	, pSOZAI_OR_DATA[ i1 ].KIKA_SUB3);
	 			strcpy(pTEMPORDATA[ 0 ].SOKU_SU 	, pSOZAI_OR_DATA[ i1 ].SOKU_SU);
				strcpy(pTEMPORDATA[ 0 ].SOKU_FLG 	, pSOZAI_OR_DATA[ i1 ].SOKU_FLG);
   				strcpy(pTEMPORDATA[ 0 ].TOKU_FLG 	, pSOZAI_OR_DATA[ i1 ].TOKU_FLG);
		  		strcpy(pTEMPORDATA[ 0 ].KIKA_PRT 	, pSOZAI_OR_DATA[ i1 ].KIKA_PRT);
		 		strcpy(pTEMPORDATA[ 0 ].VALUE_TYPE 	, pSOZAI_OR_DATA[ i1 ].VALUE_TYPE);
				strcpy(pTEMPORDATA[ 0 ].VALUE_DECI 	, pSOZAI_OR_DATA[ i1 ].VALUE_DECI);

				// dORDATA[i1] <- dORDATA[i1+1]
		   		strcpy(pSOZAI_OR_DATA[ i1 ].DTKSHIN		, pSOZAI_OR_DATA[ i1+1 ].DTKSHIN);
		  		strcpy(pSOZAI_OR_DATA[ i1 ].UNQ_NO 		, pSOZAI_OR_DATA[ i1+1 ].UNQ_NO);
		 		strcpy(pSOZAI_OR_DATA[ i1 ].ORDER_NO 	, pSOZAI_OR_DATA[ i1+1 ].ORDER_NO);
				strcpy(pSOZAI_OR_DATA[ i1 ].SKB_NO 		, pSOZAI_OR_DATA[ i1+1 ].SKB_NO);
	   			strcpy(pSOZAI_OR_DATA[ i1 ].HINBAN_SK 	, pSOZAI_OR_DATA[ i1+1 ].HINBAN_SK);
	  			strcpy(pSOZAI_OR_DATA[ i1 ].KOMK_NO 	, pSOZAI_OR_DATA[ i1+1 ].KOMK_NO);
		   		strcpy(pSOZAI_OR_DATA[ i1 ].KOMK_NM 	, pSOZAI_OR_DATA[ i1+1 ].KOMK_NM);
		  		strcpy(pSOZAI_OR_DATA[ i1 ].KOMK_ENG 	, pSOZAI_OR_DATA[ i1+1 ].KOMK_ENG);
		 		strcpy(pSOZAI_OR_DATA[ i1 ].KOMK_SUB 	, pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB);
				strcpy(pSOZAI_OR_DATA[ i1 ].KOMK_SUB_ENG, pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB_ENG);
	   			strcpy(pSOZAI_OR_DATA[ i1 ].KIKI_NO 	, pSOZAI_OR_DATA[ i1+1 ].KIKI_NO);
	  			strcpy(pSOZAI_OR_DATA[ i1 ].KIKI_NM 	, pSOZAI_OR_DATA[ i1+1 ].KIKI_NM);
	 			strcpy(pSOZAI_OR_DATA[ i1 ].TANI 		, pSOZAI_OR_DATA[ i1+1 ].TANI);
				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_TYPE 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_TYPE);
   				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_KIND 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_KIND);
  				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_DECI 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_DECI);
 				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_NUM1 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM1);
		 		strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_NUM2 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM2);
				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_NUM3 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM3);
	   			strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_STR 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_STR);
	  			strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_SUB1 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB1);
	 			strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_SUB2 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB2);
				strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_SUB3 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB3);
   				strcpy(pSOZAI_OR_DATA[ i1 ].SOKU_SU 	, pSOZAI_OR_DATA[ i1+1 ].SOKU_SU);
  				strcpy(pSOZAI_OR_DATA[ i1 ].SOKU_FLG 	, pSOZAI_OR_DATA[ i1+1 ].SOKU_FLG);
				strcpy(pSOZAI_OR_DATA[ i1 ].TOKU_FLG 	, pSOZAI_OR_DATA[ i1+1 ].TOKU_FLG);
		   		strcpy(pSOZAI_OR_DATA[ i1 ].KIKA_PRT 	, pSOZAI_OR_DATA[ i1+1 ].KIKA_PRT);
		  		strcpy(pSOZAI_OR_DATA[ i1 ].VALUE_TYPE 	, pSOZAI_OR_DATA[ i1+1 ].VALUE_TYPE);
		 		strcpy(pSOZAI_OR_DATA[ i1 ].VALUE_DECI 	, pSOZAI_OR_DATA[ i1+1 ].VALUE_DECI);
				// dORDATA[i1+1] <- dTEMPORDATA[0]
				strcpy(pSOZAI_OR_DATA[ i1+1 ].DTKSHIN	, pTEMPORDATA[ 0 ].DTKSHIN);
		   		strcpy(pSOZAI_OR_DATA[ i1+1 ].UNQ_NO 	, pTEMPORDATA[ 0 ].UNQ_NO);
		  		strcpy(pSOZAI_OR_DATA[ i1+1 ].ORDER_NO 	, pTEMPORDATA[ 0 ].ORDER_NO);
		 		strcpy(pSOZAI_OR_DATA[ i1+1 ].SKB_NO 	, pTEMPORDATA[ 0 ].SKB_NO);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].HINBAN_SK , pTEMPORDATA[ 0 ].HINBAN_SK);
	   			strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_NO 	, pTEMPORDATA[ 0 ].KOMK_NO);
	  			strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_NM 	, pTEMPORDATA[ 0 ].KOMK_NM);
	 			strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_ENG 	, pTEMPORDATA[ 0 ].KOMK_ENG);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB 	, pTEMPORDATA[ 0 ].KOMK_SUB);
   				strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB_ENG , pTEMPORDATA[ 0 ].KOMK_SUB_ENG);
  				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKI_NO 	, pTEMPORDATA[ 0 ].KIKI_NO);
 				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKI_NM 	, pTEMPORDATA[ 0 ].KIKI_NM);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].TANI 		, pTEMPORDATA[ 0 ].TANI);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_TYPE , pTEMPORDATA[ 0 ].KIKA_TYPE);
		   		strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_KIND , pTEMPORDATA[ 0 ].KIKA_KIND);
		  		strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_DECI , pTEMPORDATA[ 0 ].KIKA_DECI);
		 		strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM1 , pTEMPORDATA[ 0 ].KIKA_NUM1);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM2 , pTEMPORDATA[ 0 ].KIKA_NUM2);
	   			strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM3 , pTEMPORDATA[ 0 ].KIKA_NUM3);
	  			strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_STR 	, pTEMPORDATA[ 0 ].KIKA_STR);
	 			strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB1 , pTEMPORDATA[ 0 ].KIKA_SUB1);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB2 , pTEMPORDATA[ 0 ].KIKA_SUB2);
   				strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB3 , pTEMPORDATA[ 0 ].KIKA_SUB3);
  				strcpy(pSOZAI_OR_DATA[ i1+1 ].SOKU_SU 	, pTEMPORDATA[ 0 ].SOKU_SU);
 				strcpy(pSOZAI_OR_DATA[ i1+1 ].SOKU_FLG 	, pTEMPORDATA[ 0 ].SOKU_FLG);
				strcpy(pSOZAI_OR_DATA[ i1+1 ].TOKU_FLG 	, pTEMPORDATA[ 0 ].TOKU_FLG);
		   		strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_PRT 	, pTEMPORDATA[ 0 ].KIKA_PRT);
		  		strcpy(pSOZAI_OR_DATA[ i1+1 ].VALUE_TYPE, pTEMPORDATA[ 0 ].VALUE_TYPE);
		  		strcpy(pSOZAI_OR_DATA[ i1+1 ].VALUE_DECI, pTEMPORDATA[ 0 ].VALUE_DECI);
            }
			//}
		}
	}

//同じ項目をまとめる
    //KOMK_NMとKIKI_NOが同じ項目があれば隣にまとめます。
	for(i1 = 0; i1 < iSOZAI_ORCNT; i1++)
	{
		KOMK_NM = pSOZAI_OR_DATA[ i1 ].KOMK_NM;
		KIKI_NO = pSOZAI_OR_DATA[ i1 ].KIKI_NO;
		for(i2 = i1+1; i2 < iSOZAI_ORCNT; i2++)
		{
			if((AnsiString(pSOZAI_OR_DATA[ i2 ].KOMK_NM) == KOMK_NM)
            && (AnsiString(pSOZAI_OR_DATA[ i2 ].KIKI_NO) == KIKI_NO))
			{
			// dTEMPORDATA[0] <- dORDATA[i1]
	            strcpy(pTEMPORDATA[ 0 ].DTKSHIN	    , pSOZAI_OR_DATA[ i2 ].DTKSHIN);
    	        strcpy(pTEMPORDATA[ 0 ].UNQ_NO 	    , pSOZAI_OR_DATA[ i2 ].UNQ_NO);
        	    strcpy(pTEMPORDATA[ 0 ].ORDER_NO 	, pSOZAI_OR_DATA[ i2 ].ORDER_NO);
            	strcpy(pTEMPORDATA[ 0 ].SKB_NO 	    , pSOZAI_OR_DATA[ i2 ].SKB_NO);
	            strcpy(pTEMPORDATA[ 0 ].HINBAN_SK 	, pSOZAI_OR_DATA[ i2 ].HINBAN_SK);
    	        strcpy(pTEMPORDATA[ 0 ].KOMK_NO 	, pSOZAI_OR_DATA[ i2 ].KOMK_NO);
        	    strcpy(pTEMPORDATA[ 0 ].KOMK_NM 	, pSOZAI_OR_DATA[ i2 ].KOMK_NM);
	            strcpy(pTEMPORDATA[ 0 ].KOMK_ENG 	, pSOZAI_OR_DATA[ i2 ].KOMK_ENG);
    	        strcpy(pTEMPORDATA[ 0 ].KOMK_SUB 	, pSOZAI_OR_DATA[ i2 ].KOMK_SUB);
        	    strcpy(pTEMPORDATA[ 0 ].KOMK_SUB_ENG , pSOZAI_OR_DATA[ i2 ].KOMK_SUB_ENG);
	            strcpy(pTEMPORDATA[ 0 ].KIKI_NO 	, pSOZAI_OR_DATA[ i2 ].KIKI_NO);
    	        strcpy(pTEMPORDATA[ 0 ].KIKI_NM 	, pSOZAI_OR_DATA[ i2 ].KIKI_NM);
        	    strcpy(pTEMPORDATA[ 0 ].TANI 		, pSOZAI_OR_DATA[ i2 ].TANI);
	            strcpy(pTEMPORDATA[ 0 ].KIKA_TYPE 	, pSOZAI_OR_DATA[ i2 ].KIKA_TYPE);
    	        strcpy(pTEMPORDATA[ 0 ].KIKA_KIND 	, pSOZAI_OR_DATA[ i2 ].KIKA_KIND);
        	    strcpy(pTEMPORDATA[ 0 ].KIKA_DECI 	, pSOZAI_OR_DATA[ i2 ].KIKA_DECI);
	            strcpy(pTEMPORDATA[ 0 ].KIKA_NUM1 	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM1);
    	        strcpy(pTEMPORDATA[ 0 ].KIKA_NUM2 	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM2);
        	    strcpy(pTEMPORDATA[ 0 ].KIKA_NUM3 	, pSOZAI_OR_DATA[ i2 ].KIKA_NUM3);
	            strcpy(pTEMPORDATA[ 0 ].KIKA_STR 	, pSOZAI_OR_DATA[ i2 ].KIKA_STR);
    	        strcpy(pTEMPORDATA[ 0 ].KIKA_SUB1 	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB1);
        	    strcpy(pTEMPORDATA[ 0 ].KIKA_SUB2 	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB2);
	            strcpy(pTEMPORDATA[ 0 ].KIKA_SUB3 	, pSOZAI_OR_DATA[ i2 ].KIKA_SUB3);
    	        strcpy(pTEMPORDATA[ 0 ].SOKU_SU 	, pSOZAI_OR_DATA[ i2 ].SOKU_SU);
        	    strcpy(pTEMPORDATA[ 0 ].SOKU_FLG 	, pSOZAI_OR_DATA[ i2 ].SOKU_FLG);
	            strcpy(pTEMPORDATA[ 0 ].TOKU_FLG 	, pSOZAI_OR_DATA[ i2 ].TOKU_FLG);
    	        strcpy(pTEMPORDATA[ 0 ].KIKA_PRT 	, pSOZAI_OR_DATA[ i2 ].KIKA_PRT);
        	    strcpy(pTEMPORDATA[ 0 ].VALUE_TYPE 	, pSOZAI_OR_DATA[ i2 ].VALUE_TYPE);
	            strcpy(pTEMPORDATA[ 0 ].VALUE_DECI 	, pSOZAI_OR_DATA[ i2 ].VALUE_DECI);
				for(i3 = i2-1;i3 > i1; i3--)
				{
					strcpy(pSOZAI_OR_DATA[ i3+1 ].DTKSHIN	, pSOZAI_OR_DATA[ i3 ].DTKSHIN);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].UNQ_NO 	, pSOZAI_OR_DATA[ i3 ].UNQ_NO);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].ORDER_NO	, pSOZAI_OR_DATA[ i3 ].ORDER_NO);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].SKB_NO 	, pSOZAI_OR_DATA[ i3 ].SKB_NO);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].HINBAN_SK, pSOZAI_OR_DATA[ i3 ].HINBAN_SK);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KOMK_NO 	, pSOZAI_OR_DATA[ i3 ].KOMK_NO);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KOMK_NM 	, pSOZAI_OR_DATA[ i3 ].KOMK_NM);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KOMK_ENG 	, pSOZAI_OR_DATA[ i3 ].KOMK_ENG);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KOMK_SUB 	, pSOZAI_OR_DATA[ i3 ].KOMK_SUB);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KOMK_SUB_ENG , pSOZAI_OR_DATA[ i3 ].KOMK_SUB_ENG);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKI_NO 	, pSOZAI_OR_DATA[ i3 ].KIKI_NO);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKI_NM 	, pSOZAI_OR_DATA[ i3 ].KIKI_NM);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].TANI 		, pSOZAI_OR_DATA[ i3 ].TANI);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_TYPE 	, pSOZAI_OR_DATA[ i3 ].KIKA_TYPE);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_KIND 	, pSOZAI_OR_DATA[ i3 ].KIKA_KIND);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_DECI 	, pSOZAI_OR_DATA[ i3 ].KIKA_DECI);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_NUM1 	, pSOZAI_OR_DATA[ i3 ].KIKA_NUM1);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_NUM2 	, pSOZAI_OR_DATA[ i3 ].KIKA_NUM2);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_NUM3 	, pSOZAI_OR_DATA[ i3 ].KIKA_NUM3);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_STR 	, pSOZAI_OR_DATA[ i3 ].KIKA_STR);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_SUB1 	, pSOZAI_OR_DATA[ i3 ].KIKA_SUB1);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_SUB2 	, pSOZAI_OR_DATA[ i3 ].KIKA_SUB2);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_SUB3 	, pSOZAI_OR_DATA[ i3 ].KIKA_SUB3);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].SOKU_SU 	, pSOZAI_OR_DATA[ i3 ].SOKU_SU);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].SOKU_FLG 	, pSOZAI_OR_DATA[ i3 ].SOKU_FLG);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].TOKU_FLG 	, pSOZAI_OR_DATA[ i3 ].TOKU_FLG);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].KIKA_PRT 	, pSOZAI_OR_DATA[ i3 ].KIKA_PRT);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].VALUE_TYPE 	, pSOZAI_OR_DATA[ i3 ].VALUE_TYPE);
					strcpy(pSOZAI_OR_DATA[ i3+1 ].VALUE_DECI 	, pSOZAI_OR_DATA[ i3 ].VALUE_DECI);
				}
			// dORDATA[i1+1] <- dTEMPORDATA[0]
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].DTKSHIN		, pTEMPORDATA[ 0 ].DTKSHIN);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].UNQ_NO 		, pTEMPORDATA[ 0 ].UNQ_NO);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].ORDER_NO 	    , pTEMPORDATA[ 0 ].ORDER_NO);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].SKB_NO 		, pTEMPORDATA[ 0 ].SKB_NO);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].HINBAN_SK 	, pTEMPORDATA[ 0 ].HINBAN_SK);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_NO 		, pTEMPORDATA[ 0 ].KOMK_NO);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_NM 		, pTEMPORDATA[ 0 ].KOMK_NM);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_ENG 	    , pTEMPORDATA[ 0 ].KOMK_ENG);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB 	    , pTEMPORDATA[ 0 ].KOMK_SUB);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].KOMK_SUB_ENG  , pTEMPORDATA[ 0 ].KOMK_SUB_ENG);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKI_NO 		, pTEMPORDATA[ 0 ].KIKI_NO);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKI_NM 		, pTEMPORDATA[ 0 ].KIKI_NM);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].TANI 		    , pTEMPORDATA[ 0 ].TANI);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_TYPE 	, pTEMPORDATA[ 0 ].KIKA_TYPE);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_KIND 	, pTEMPORDATA[ 0 ].KIKA_KIND);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_DECI 	, pTEMPORDATA[ 0 ].KIKA_DECI);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM1 	, pTEMPORDATA[ 0 ].KIKA_NUM1);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM2 	, pTEMPORDATA[ 0 ].KIKA_NUM2);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_NUM3 	, pTEMPORDATA[ 0 ].KIKA_NUM3);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_STR 	    , pTEMPORDATA[ 0 ].KIKA_STR);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB1 	, pTEMPORDATA[ 0 ].KIKA_SUB1);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB2 	, pTEMPORDATA[ 0 ].KIKA_SUB2);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_SUB3 	, pTEMPORDATA[ 0 ].KIKA_SUB3);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].SOKU_SU 		, pTEMPORDATA[ 0 ].SOKU_SU);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].SOKU_FLG 	    , pTEMPORDATA[ 0 ].SOKU_FLG);
        	    strcpy(pSOZAI_OR_DATA[ i1+1 ].TOKU_FLG 	    , pTEMPORDATA[ 0 ].TOKU_FLG);
            	strcpy(pSOZAI_OR_DATA[ i1+1 ].KIKA_PRT 	    , pTEMPORDATA[ 0 ].KIKA_PRT);
	            strcpy(pSOZAI_OR_DATA[ i1+1 ].VALUE_TYPE 	, pTEMPORDATA[ 0 ].VALUE_TYPE);
    	        strcpy(pSOZAI_OR_DATA[ i1+1 ].VALUE_DECI 	, pTEMPORDATA[ 0 ].VALUE_DECI);
        		break;
			}
		}
    }


/* k.y 2003.05.17
    // メモリの開放
    if( hTEMPORDATA ){
        GlobalUnlock( hTEMPORDATA );
        GlobalFree( hTEMPORDATA );
    }
	hTEMPORDATA = NULL;
*/
//    Synchronize(Set_SOZAI_GRID);
    Set_SOZAI_GRID();

}


//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：作成したＯＲテーブルを使い動的コントロールを生成して項目を作成します。
//
//  機能説明
//    ＯＲテーブルを参照し、動的コントロールを作成します。
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
void __fastcall TForm1::Set_SOZAI_GRID(void)
{
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

extern 	int iSOZAI_ORCNT;
extern	int iSOZAI_SOKUCNT;													//ソート時使用する重み計算用バッファ

AnsiString sBuf,sLot,sTempBuf;
AnsiString 	sDeci1;
//char cFormatBuf[20],c1[20],c2[10];

    //動的コントロールを削除します。
    for(i2=0 ;i2<iSOZAI_DEL_SokuCnt;i2++)
    {
        delete Form1->Pnl_SOZAI_InsNo[i2];
    }
    iSOZAI_DEL_SokuCnt = 0;
    for(i2=0 ;i2<iSOZAI_DEL_OrCnt;i2++)
    {
        delete Form1->Lab_SOZAI_KOMK_NM[i2];
        delete Form1->Lab_SOZAI_TANI[i2];
        delete Form1->Lab_SOZAI_KIKA[i2];
        delete Form1->Lab_SOZAI_UPKIKA[i2];
        delete Form1->Lab_SOZAI_LOKIKA[i2];
        delete Form1->Pnl_SOZAI_InsName[i2];
    }
    for(i2=0 ;i2<iSOZAI_DEL_OrCnt;i2++)
    {
        delete Form1->Pnl_SOZAI_SubBase[i2];
    }
    iSOZAI_DEL_OrCnt = 0;

    Form1->SGr_vRIRE_SOZAI->RowCount = 1;
    Form1->SGr_vSOKU_SOZAI->RowCount = 1;
    //Form1->SGr_vRIRE_SOZAI->Visible  = false;
    Form1->SGr_vSOKU_SOZAI->Visible  = false;

	Form1->Refresh();
// 動的コントロールの作成(必要数分の宣言）
    Form1->Pnl_SOZAI_SubBase    = new TPanel *[iSOZAI_ORCNT];
    Form1->Pnl_SOZAI_InsName    = new TPanel *[iSOZAI_ORCNT];
    Form1->Lab_SOZAI_KOMK_NM    = new TLabel *[iSOZAI_ORCNT];
    Form1->Lab_SOZAI_TANI       = new TLabel *[iSOZAI_ORCNT];
    Form1->Lab_SOZAI_KIKA       = new TLabel *[iSOZAI_ORCNT];
    Form1->Lab_SOZAI_UPKIKA     = new TLabel *[iSOZAI_ORCNT];
    Form1->Lab_SOZAI_LOKIKA     = new TLabel *[iSOZAI_ORCNT];
    Form1->Pnl_SOZAI_InsNo      = new TPanel *[iSOZAI_SOKUCNT];

    i2 = 0;
    i1 = 0;
    iSOZAI_ContCnt = 0;
    iPnl_SOZAI_InsNoCnt = 0;
	iSOZAI_SOKUCNT = 0;
    iPanelNum = 0;
    iSokuGoukei = 0;
    iPnl_SOZAI_InsNoCnt = 0;
	iPnl_SOZAI_InsNameCnt = 0;
    iPnl_SOZAI_InsSubBaseCnt = 0;
    iSOZAI_ContCnt = 0;

    //Form1->SGr_vRIRE_SOZAI->Visible  = true;
    Form1->SGr_vSOKU_SOZAI->Visible  = true;

    while( iSOZAI_ContCnt < iSOZAI_ORCNT )
    {
        iPutKiki = AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKI_NO).ToIntDef(0);
//同一機器の測定ループ
        while( iPutKiki == AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKI_NO).ToIntDef(0)
				&& iSOZAI_ContCnt < iSOZAI_ORCNT)
        {
//ベースパネルの描画
            sBuf = IntToStr(iSOZAI_ContCnt);
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt] = new TPanel(Form1->SBx_Left_SOZAI);
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Name = "Pnl_Sozai_SubBase" + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Parent = Form1->SBx_Left_SOZAI;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Left = Form1->Pnl_SOZAI_ORG_SUBBASE->Left;
            if( iSOZAI_ContCnt == 0 )
            {

                Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Top = 25;
            }
            else
            {
                Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Top = Form1-> Pnl_SOZAI_SubBase[iSOZAI_ContCnt - 1 ]->Top+Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt - 1 ]->Height;
            }
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Width = Form1->Pnl_SOZAI_ORG_SUBBASE->Width;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Height =
				24*(AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].SOKU_SU).ToIntDef(0))
				+(AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].SOKU_SU).ToIntDef(0));
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Ctl3D = true;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->BevelInner = bvNone;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->BevelOuter = bvNone;
            Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->BorderWidth = 0;
            iPnl_SOZAI_InsSubBaseCnt ++;
//測定項目表示パネルの描画
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt] = new TPanel(Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]);
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Name = "Pnl_SOZAI_InsName" + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Alignment = taLeftJustify;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Align =alLeft ;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Caption = "";
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Parent = Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt];
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Left = Form1->Pnl_SOZAI_ORG_INSNAME->Left;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Top = 0;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width = Form1->Pnl_SOZAI_ORG_INSNAME->Width;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Height = Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Height;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Color = (TColor)SOZAI_COLOR;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Ctl3D = false;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->BevelInner = bvNone;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->BevelOuter = bvRaised;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->BorderStyle = bsNone;
            Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->BorderWidth = 0;
            iPnl_SOZAI_InsNameCnt ++;
//測定項目の描画
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt] =  new TLabel(Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]);
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Parent = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt];
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->AutoSize = true;
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Top = 6;
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Left = 0;
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Height = Form1->Lab_BASESOZAIKOMK_NM->Height;
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Caption = AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KOMK_NM) + AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KOMK_SUB);
            Form1->Lab_SOZAI_KOMK_NM[iSOZAI_ContCnt]->Font->Size = 11;
//単位の描画
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt] =     new TLabel(Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]);
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Parent    = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt];
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->AutoSize = true;
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Caption = pSOZAI_OR_DATA[iSOZAI_ContCnt].TANI;
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Top = 6;
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Height = Form1->Lab_BASESOZAITANI->Height;
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Font->Size = 11;
            Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Left = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width-Form1->Lab_SOZAI_TANI[iSOZAI_ContCnt]->Width-2 ;
//ｎ数の表示
            iPanelNum = 0;
            for(i4=0 ; i4 < AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].SOKU_SU).ToIntDef(0);i4++)
            {
                sBuf = IntToStr(iPanelNum);
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]           = new TPanel(Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]);
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Name     = "Pnl_SOZAI_InsNo" + AnsiString::StringOfChar('0', 4-sBuf.Length()) + sBuf;
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Caption  = i4+1;
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Parent   = Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt];
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Left     = Form1->Pnl_SOZAI_ORG_INSNUM->Left;
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Top      = (Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Height)/AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].SOKU_SU).ToIntDef(0) * i4;
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Width    = Form1->Pnl_OrgInsNum->Width;
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Height   = (Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt]->Height)/AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].SOKU_SU).ToIntDef(0);
                Form1->Pnl_SOZAI_InsNo[iPnl_SOZAI_InsNoCnt]->Color    = (TColor)SOZAI_COLOR;
                iPanelNum ++;
                iSokuGoukei ++;
                iPnl_SOZAI_InsNoCnt ++;
                Form1->SGr_vRIRE_SOZAI->RowCount ++;
                Form1->SGr_vSOKU_SOZAI->RowCount ++;
            }
iSOZAI_SOKUCNT = iSokuGoukei;
//規格の表示
			Sleep(10);
    //規格値メインラベル
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt] =  new TLabel(Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]);
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Parent = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt];
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->ParentColor = false;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->AutoSize = true;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Top = Form1->Lab_BASESOZAIKIKA->Top;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Left =  Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width-Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Width;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Height =  Form1->Lab_BASESOZAIKIKA->Height ;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Font->Color = clBlack;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Font->Size = 11;
            Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Font->Name ="ＭＳ ゴシック";
    //規格値上限ラベル
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt] =  new TLabel(Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]);
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Parent = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt];
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->AutoSize = true;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Top = Form1->Lab_BASESOZAIUPKIKA->Top;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Left =  Form1->Lab_BASESOZAIUPKIKA->Left  ;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Height =  Form1->Lab_BASESOZAIUPKIKA->Height ;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Font->Color = clBlack;;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Font->Size = 9;
            Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Font->Name ="ＭＳ ゴシック";
    //規格値下限ラベル
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt] =  new TLabel(Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]);
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Parent = Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt];
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->AutoSize = true;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Top = Form1->Lab_BASESOZAILOKIKA->Top;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Left =  Form1->Lab_BASESOZAILOKIKA->Left  ;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Height =  Form1->Lab_BASESOZAILOKIKA->Height ;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Font->Color = clBlack;;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Font->Size = 9;
            Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Font->Name ="ＭＳ ゴシック";
    //規格表示色々
    //フォーマット指定（％*.*ｆ）
   			sDeci1 = "0";
			for(i1 = 0;i1 < AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_DECI).ToIntDef(0);i1++)
			{
				if(i1 == 0 ) sDeci1 += ".";
				sDeci1 +="0";
			}
            switch(AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_TYPE).ToIntDef(0))
            {
            case 1:
                switch(AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_KIND).ToIntDef(0))
                {
                case 1:
                     sBuf = FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM1).ToDouble());
                     sBuf +=  "～";
                     sBuf += FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM2).ToDouble());
                     Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Caption = sBuf;
                     break;
                case 2:
                     sBuf = FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM2).ToDouble());
                     Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Caption = sBuf +"以下";
                     break;
                case 3:
                     sBuf = FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM1).ToDouble());
                     Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Caption = sBuf +"以上";
                     break;
                default:
                    break;
                }
                Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Left =
                Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width-Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Width-2;
                Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Visible = false;
                Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Visible = false;
                break;
            case 2:
                sBuf = FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM1).ToDouble());
                Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Caption = sBuf;
                switch(AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_KIND).ToIntDef(0))
                {
                case 1:
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption =
                        FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM2).ToDouble());
                    Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption =
                        FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM3).ToDouble());
					if(Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption.ToDouble()>=0) Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption = "+" + Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption;
					if(Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption.ToDouble()>=0) Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption = "+" + Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption;
                    break;
                case 2:
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption =
                        FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM2).ToDouble());
                    Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption ="";
					if(Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption.ToDouble()>=0) Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption = "+" + Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption;
                    break;
                case 3:
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption = "";
                    Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption =
                        FormatFloat(sDeci1,AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_NUM3).ToDouble());
					if(Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption.ToDouble()>=0) Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption = "+" + Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption;
                    break;
                 default:
                    break;
                }
                if(Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Width >= Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Width)
                {
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Left =
                        Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width - Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Width -2;
                    Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Left = Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Left;
                }
                else
                {
                    Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Left =
                        Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width - Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Width -2;
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Left = Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Left;
                }
                Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Left =
                    Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Left-Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Width-2;
                break;
            case 3:
                Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Caption = AnsiString(pSOZAI_OR_DATA[iSOZAI_ContCnt].KIKA_STR);
                Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Caption ="";
                Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Caption ="";
                Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Left =
                Form1->Pnl_SOZAI_InsName[iSOZAI_ContCnt]->Width-Form1->Lab_SOZAI_KIKA[iSOZAI_ContCnt]->Width-2;
                Form1->Lab_SOZAI_UPKIKA[iSOZAI_ContCnt]->Visible = false;
                Form1->Lab_SOZAI_LOKIKA[iSOZAI_ContCnt]->Visible = false;
                break;
            default:
                break;
            }
            iSOZAI_ContCnt++;
        }
    }
    iSOZAI_DEL_SokuCnt  = 	iSOZAI_SOKUCNT;
    iSOZAI_DEL_OrCnt    =	iSOZAI_ORCNT;
	Form1->Panel27->Caption =AnsiString("素　材　検　査　（")+ iSOZAI_ContCnt +AnsiString("項）");
//セルと項目パネルのHEIGHTの調整のためDUMMYパネルを置きます
	if(iSOZAI_ContCnt > 0 )
	{
		Form1->Pnl_DUMMY2->Parent = Form1->SBx_Left_SOZAI;
		Form1->Pnl_DUMMY2->Top = Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt - 1]->Top+Form1->Pnl_SOZAI_SubBase[iSOZAI_ContCnt - 1]->Height;
	    Form1->Pnl_DUMMY2->Height = 39;		//グリッドにスクロールバーが出現/未出現で高さを変えたいが、手段が無いため中間の値をとる
	    Form1->Pnl_DUMMY2->Width = 1;
		Form1->Pnl_DUMMY2->Left = 0;
	    Form1->Pnl_DUMMY2->Ctl3D = false;
    	Form1->Pnl_DUMMY2->BevelInner = bvNone;
	    Form1->Pnl_DUMMY2->BevelOuter = bvRaised;
    	Form1->Pnl_DUMMY2->BorderStyle = bsNone;
	    Form1->Pnl_DUMMY2->BorderWidth = 0;
		Form1->Pnl_DUMMY2->Visible = true;
    }
}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：ＯＲデータからある項目規格のMIN,MAX値を返します。
//
//  機能説明
//    ＯＲデータから其の規格のMIN,MAX値を返します。
//
//  パラメタ説明
//    int iIndex	：ORデータの何番目を参照するか
//    double *dMAX  : MAX値を返します
//    double *dMIN  : MIN値を返します
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GetSOZAI_KIKAKU(int iIndex,double *dMAX,double *dMIN)
{
	double dSWAP;

	*dMAX = 0.0;
	*dMIN = 0.0;

	if(iDEBUG == 1) return;
    if( AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_TYPE).ToIntDef(0) != 3 )
    {
        //2003.05.08 E.Takase Add↓
       	*dMAX = Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM1,0.0);
       	*dMIN = Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM1,0.0);
        //2003.05.08 E.Takase Add↑
        //2003.05.08 E.Takase Add コメント↓
		//try{
    	//	*dMAX = AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM1).ToDouble();
        //	*dMIN = AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM1).ToDouble();
		//}
		//catch(EConvertError& e){
		//	return;
		//}
		//catch(...){
		//	return;
		//}
        //2003.05.08 E.Takase Add コメント↑
        switch(AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_TYPE).ToIntDef(0))
        {
        case 1:
        	switch(AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_KIND).ToIntDef(0))
            {
            case 1:
                //2003.05.08 E.Takase Add↓
            	*dMAX = Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM2,0.0);
                *dMIN = Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM1,0.0);
        		//2003.05.08 E.Takase Add↑
        		//2003.05.08 E.Takase Add コメント↓
				//try{
            	//	*dMAX = AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM2).ToDouble();
                //	*dMIN = AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM1).ToDouble();
                //}
				//catch(EConvertError& e){
				//	return;
				//}
				//catch(...){
				//	return;
				//}
        		//2003.05.08 E.Takase Add コメント↑
                break;
            case 2:
                //2003.05.08 E.Takase Add↓
                *dMAX = Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM2,0.0);
        		//2003.05.08 E.Takase Add↑
        		//2003.05.08 E.Takase Add コメント↓
				//try{
            	//	*dMAX = AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM2).ToDouble();
				//}
				//catch(EConvertError& e){
				//	return;
				//}
				//catch(...){
				//	return;
				//}
        		//2003.05.08 E.Takase Add コメント↑
                break;
            case 3:
            	break;
            default:
            	break;
            }
            break;
        case 2:
        	switch(AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_KIND).ToIntDef(0))
            {
            case 1:
            	//2003.05.08 E.Takase Add↓
            	*dMAX += Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM2,0.0);
               	*dMIN += Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM3,0.0);
        		//2003.05.08 E.Takase Add↑
        		//2003.05.08 E.Takase Add コメント↓
				//try{
            	//	*dMAX += AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM2).ToDouble();
                //	*dMIN += AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM3).ToDouble();
                //}
				//catch(EConvertError& e){
				//	return;
				//}
				//catch(...){
				//	return;
				//}
        		//2003.05.08 E.Takase Add コメント↑
                break;
            case 2:
            	//2003.05.08 E.Takase Add↓
            	*dMAX += Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM2,0.0);
        		//2003.05.08 E.Takase Add↑
        		//2003.05.08 E.Takase Add コメント↓
				//try{
            	//	*dMAX += AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM2).ToDouble();
                //}
				//catch(EConvertError& e){
				//	return;
				///}
				//catch(...){
				//	return;
				//}
        		//2003.05.08 E.Takase Add コメント↑
                break;
            case 3:
            	//2003.05.08 E.Takase Add↓
            	*dMIN += Form1->ConvDoubleDefD(pSOZAI_OR_DATA[iIndex].KIKA_NUM3,0.0);
        		//2003.05.08 E.Takase Add↑
        		//2003.05.08 E.Takase Add コメント↓
				//try{
            	// 	*dMIN += AnsiString(pSOZAI_OR_DATA[iIndex].KIKA_NUM3).ToDouble();
                //}
				//catch(EConvertError& e){
				//	return;
				//}
				//catch(...){
				//	return;
				//}
        		//2003.05.08 E.Takase Add コメント↑
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



