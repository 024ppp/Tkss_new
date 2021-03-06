//---------------------------------------------------------------------------
//
//  UnitDataAcccess.cpp
//    【出荷検査システム−主にデータベース読み書き】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    市川　和弘
//
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Thread.h"
#include "ThreadSozaiMain.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Unit8.h"
#include "Tkss01.h"
#include "UnitDataAccess.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
extern int iDEBUG;
extern int iSOZAI_ContCnt;

KSM01_DATA 	pKSM01_DATA;

KSM02_DATA 	pORDATA[100];

KSM02_DATA  pSOZAI_OR_DATA[100];

KSM02_DATA 	pTEMPORDATA[100];

HANDLE		hSOZAI_RIREKI_DATA;   	// 過去履歴対象ロットデータ
KSD02_DATA 	*pSOZAI_RIREKI_DATA;   	// 過去履歴対象ロットデータ

KSD02_DATA 	pRIREKI_DATA[100];      	// 過去履歴対象ロットデータ

KSM02_DATA 	pSYUKA_DATA[100];       	// 出荷用データ

HANDLE 		hSOZAI_SYUKA_DATA;
KSM02_DATA 	*pSOZAI_SYUKA_DATA;

KSM02_DATA  pSPACE_DATA[100];

HANDLE 		hKSD01_DATA;
KSD01_DATA 	*pKSD01_DATA;

//測定実績データ用メモリ
HANDLE 		hRIRE_KSD01DATA;
KSD01_DATA 	*pRIRE_KSD01DATA;
HANDLE 		hSOKU_KSD01DATA;
KSD01_DATA 	*pSOKU_KSD01DATA;

GRAPH_DATA	pOldInfoGlaph;

//ロット割り当て
HANDLE hRIRE_LOTWARI_DATA;
LOTWARI_DATA *pRIRE_LOTWARI_DATA;
HANDLE hSOKU_LOTWARI_DATA;
LOTWARI_DATA *pSOKU_LOTWARI_DATA;

//ロット割り当て
HANDLE hSOKU_KSD01_DATA;
KSD01_DATA *pSOKU_KSD01_DATA;
HANDLE hRIRE_KSD01_DATA;
KSD01_DATA *pRIRE_KSD01_DATA;

bool bLOTCHANGE; 		//スレッド（素材）との通信用
//スペース
int iSPACE_COUNT;
//素材
int iSOZAI_KOMKCNT;
int iSOZAI_CONT_CONT;
int iSOZAI_RIRE_LOT;
int iSOZAI_ORCNT;
int iSOZAI_SOKUCNT;													//ソート時使用する重み計算用バッファ
//

extern int	iContCnt;               //出荷検査項目
int 		iSYUKA_KOMKCNT;         //出荷検査の項目数
int 		iRIREKI_KOMKCNT;        //履歴の項目数
int 		iSOKU_KOMKCNT;
KSD02_DATA	*pRIREKI;
HANDLE  	hRIREKI; 				//履歴データ読取りよう
KSD02_DATA	*pJISSEKI;
HANDLE		hJISSEKI;           	//実績データ読取りよう
int iOrCnt2;
int iSyukaCnt2;
extern iRIRE_MEMO_CNT;


//セル情報
HANDLE hCELLINFO_SOKU_SYUKA;
HANDLE hCELLINFO_RIRE_SYUKA;
HANDLE hCELLINFO_SOKU_SOZAI;
HANDLE hCELLINFO_RIRE_SOZAI;
CELLINFO_DATA *pCELLINFO_SOKU_SYUKA;
CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;
CELLINFO_DATA *pCELLINFO_SOKU_SOZAI;
CELLINFO_DATA *pCELLINFO_RIRE_SOZAI;

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：製品規格マスターの読み込み。
//
//  機能説明
//    製品規格マスターを読み込みバッファへ展開する。
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
bool __fastcall TForm1::Get_KSM01(void)
{
	AnsiString sBuf;

    memset(&pKSM01_DATA,(int)NULL,sizeof(pKSM01_DATA));

//得意先品番をキーにして素材用製品規格マスターを抽出
	sBuf  = "SELECT  KSM01.*, SM12S.TANNAM As UPDNAME ";
	sBuf += " FROM KSM01 LEFT JOIN SM12S ON KSM01.UPDCHR = SM12S.TANSYA ";
	sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
	sBuf += " AND   REVCNT = 0" ;

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if( Query1->Eof == true ) return(false);					//マスター登録されていないので素材は表示できない

    strcpy(pKSM01_DATA.DTKSHIN		,"");
    if ( VarIsNull(Query1->FieldValues["DTKSHIN"]) != true
    &&  VarIsEmpty(Query1->FieldValues["DTKSHIN"]) != true )
    {
    	sBuf  	= Query1->FieldValues["DTKSHIN"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.DTKSHIN  	,sBuf.c_str());
	}

    strcpy(pKSM01_DATA.REVCNT		,"");
    if ( VarIsNull(Query1->FieldValues["REVCNT"]) != true
    &&  VarIsEmpty(Query1->FieldValues["REVCNT"]) != true )
    {
	    sBuf  	= Query1->FieldValues["REVCNT"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.REVCNT  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.HINBAN		,"");
    if ( VarIsNull(Query1->FieldValues["HINBAN"]) != true
    &&  VarIsEmpty(Query1->FieldValues["HINBAN"]) != true )
    {
	    sBuf  	= Query1->FieldValues["HINBAN"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.HINBAN  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.DTKSCOD		,"");
    if ( VarIsNull(Query1->FieldValues["DTKSCOD"]) != true
    &&  VarIsEmpty(Query1->FieldValues["DTKSCOD"]) != true )
    {
	    sBuf  	= Query1->FieldValues["DTKSCOD"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.DTKSCOD  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.DTKSNAM		,"");
    if ( VarIsNull(Query1->FieldValues["DTKSNAM"]) != true
    &&  VarIsEmpty(Query1->FieldValues["DTKSNAM"]) != true )
    {
	    sBuf  	= Query1->FieldValues["DTKSNAM"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.DTKSNAM  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.ZISNAM		,"");
    if ( VarIsNull(Query1->FieldValues["ZISNAM"]) != true
    &&  VarIsEmpty(Query1->FieldValues["ZISNAM"]) != true )
    {
	    sBuf  	= Query1->FieldValues["ZISNAM"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.ZISNAM  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.HINMEI		,"");
    if ( VarIsNull(Query1->FieldValues["HINMEI"]) != true
    &&  VarIsEmpty(Query1->FieldValues["HINMEI"]) != true )
    {
	    sBuf  	= Query1->FieldValues["HINMEI"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.HINMEI  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.DTKSHIN1_SZ		,"");
    if ( VarIsNull(Query1->FieldValues["DTKSHIN1_SZ"]) != true
    &&  VarIsEmpty(Query1->FieldValues["DTKSHIN1_SZ"]) != true )
    {
	    sBuf  	= Query1->FieldValues["DTKSHIN1_SZ"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.DTKSHIN1_SZ  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.DTKSHIN2_SZ		,"");
    if ( VarIsNull(Query1->FieldValues["DTKSHIN2_SZ"]) != true
    &&  VarIsEmpty(Query1->FieldValues["DTKSHIN2_SZ"]) != true )
    {
	    sBuf  	= Query1->FieldValues["DTKSHIN2_SZ"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.DTKSHIN2_SZ  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.DTKSHIN3_SZ		,"");
    if ( VarIsNull(Query1->FieldValues["DTKSHIN3_SZ"]) != true
    &&  VarIsEmpty(Query1->FieldValues["DTKSHIN3_SZ"]) != true )
    {
	    sBuf  	= Query1->FieldValues["DTKSHIN3_SZ"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.DTKSHIN3_SZ  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.DTKSHIN4_SZ		,"");
    if ( VarIsNull(Query1->FieldValues["DTKSHIN4_SZ"]) != true
    &&  VarIsEmpty(Query1->FieldValues["DTKSHIN4_SZ"]) != true )
    {
	    sBuf  	= Query1->FieldValues["DTKSHIN4_SZ"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.DTKSHIN4_SZ  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.DTKSHIN5_SZ		,"");
    if ( VarIsNull(Query1->FieldValues["DTKSHIN5_SZ"]) != true
    &&  VarIsEmpty(Query1->FieldValues["DTKSHIN5_SZ"]) != true )
    {
	    sBuf  	= Query1->FieldValues["DTKSHIN5_SZ"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.DTKSHIN5_SZ  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.DTKSHIN6_SZ		,"");
    if ( VarIsNull(Query1->FieldValues["DTKSHIN6_SZ"]) != true
    &&  VarIsEmpty(Query1->FieldValues["DTKSHIN6_SZ"]) != true )
    {
	    sBuf  	= Query1->FieldValues["DTKSHIN6_SZ"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.DTKSHIN6_SZ  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.LOT_LINK_SZ		,"");
    if ( VarIsNull(Query1->FieldValues["LOT_LINK_SZ"]) != true
    &&  VarIsEmpty(Query1->FieldValues["LOT_LINK_SZ"]) != true )
    {
	    sBuf  	= Query1->FieldValues["LOT_LINK_SZ"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.LOT_LINK_SZ  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.SOKUTEI_NUM		,"");
    if ( VarIsNull(Query1->FieldValues["SOKUTEI_NUM"]) != true
    &&  VarIsEmpty(Query1->FieldValues["SOKUTEI_NUM"]) != true )
    {
	    sBuf  	= Query1->FieldValues["SOKUTEI_NUM"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.SOKUTEI_NUM  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.OUT_TITLE1		,"");
    if ( VarIsNull(Query1->FieldValues["OUT_TITLE1"]) != true
    &&  VarIsEmpty(Query1->FieldValues["OUT_TITLE1"]) != true )
    {
	    sBuf  	= Query1->FieldValues["OUT_TITLE1"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.OUT_TITLE1  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.OUT_TITLE2		,"");
    if ( VarIsNull(Query1->FieldValues["OUT_TITLE2"]) != true
    &&  VarIsEmpty(Query1->FieldValues["OUT_TITLE2"]) != true )
    {
	    sBuf  	= Query1->FieldValues["OUT_TITLE2"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.OUT_TITLE2  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.OUT_TITLE3		,"");
    if ( VarIsNull(Query1->FieldValues["OUT_TITLE3"]) != true
    &&  VarIsEmpty(Query1->FieldValues["OUT_TITLE3"]) != true )
    {
	    sBuf  	= Query1->FieldValues["OUT_TITLE3"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.OUT_TITLE3  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.OUT_TITLE4		,"");
    if ( VarIsNull(Query1->FieldValues["OUT_TITLE4"]) != true
    &&  VarIsEmpty(Query1->FieldValues["OUT_TITLE4"]) != true )
    {
	    sBuf  	= Query1->FieldValues["OUT_TITLE4"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.OUT_TITLE4  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.OUT_TITLE5		,"");
    if ( VarIsNull(Query1->FieldValues["OUT_TITLE5"]) != true
    &&  VarIsEmpty(Query1->FieldValues["OUT_TITLE5"]) != true )
    {
	    sBuf  	= Query1->FieldValues["OUT_TITLE5"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.OUT_TITLE5  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.OUT_TITLE6		,"");
    if ( VarIsNull(Query1->FieldValues["OUT_TITLE6"]) != true
    &&  VarIsEmpty(Query1->FieldValues["OUT_TITLE6"]) != true )
    {
	    sBuf  	= Query1->FieldValues["OUT_TITLE6"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.OUT_TITLE6  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.OUT_TITLE7		,"");
    if ( VarIsNull(Query1->FieldValues["OUT_TITLE7"]) != true
    &&  VarIsEmpty(Query1->FieldValues["OUT_TITLE7"]) != true )
    {
	    sBuf  	= Query1->FieldValues["OUT_TITLE7"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.OUT_TITLE7  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.OUT_TITLE8		,"");
    if ( VarIsNull(Query1->FieldValues["OUT_TITLE8"]) != true
    &&  VarIsEmpty(Query1->FieldValues["OUT_TITLE8"]) != true )
    {
	    sBuf  	= Query1->FieldValues["OUT_TITLE8"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.OUT_TITLE8  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.X_OUT		,"");
    if ( VarIsNull(Query1->FieldValues["X_OUT"]) != true
    &&  VarIsEmpty(Query1->FieldValues["X_OUT"]) != true )
    {
	    sBuf  	= Query1->FieldValues["X_OUT"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.X_OUT  		,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.MEMO		,"");
    if ( VarIsNull(Query1->FieldValues["MEMO"]) != true
    &&  VarIsEmpty(Query1->FieldValues["MEMO"]) != true )
    {
	    sBuf  	= Query1->FieldValues["MEMO"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.MEMO  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.ADDYMD		,"");
    if ( VarIsNull(Query1->FieldValues["ADDYMD"]) != true
    &&  VarIsEmpty(Query1->FieldValues["ADDYMD"]) != true )
    {
	    sBuf  	= Query1->FieldValues["ADDYMD"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.ADDYMD  	,sBuf.c_str());
    }
	if(AnsiString(pKSM01_DATA.ADDYMD).Length()!=8)
	{
		strcpy(pKSM01_DATA.ADDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
	}

    strcpy(pKSM01_DATA.ADDTIM		,"");
    if ( VarIsNull(Query1->FieldValues["ADDTIM"]) != true
    &&  VarIsEmpty(Query1->FieldValues["ADDTIM"]) != true )
    {
	    sBuf  	= Query1->FieldValues["ADDTIM"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.ADDTIM  	,sBuf.c_str());
    }
	if(AnsiString(pKSM01_DATA.ADDTIM).Length()!=4)
	{
		strcpy(pKSM01_DATA.ADDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
	}
    strcpy(pKSM01_DATA.UPDYMD		,"");
    if ( VarIsNull(Query1->FieldValues["UPDYMD"]) != true
    &&  VarIsEmpty(Query1->FieldValues["UPDYMD"]) != true )
    {
	    sBuf  	= Query1->FieldValues["UPDYMD"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.UPDYMD  	,sBuf.c_str());
    }
	if(AnsiString(pKSM01_DATA.UPDYMD).Length()!=8)
	{
		strcpy(pKSM01_DATA.UPDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
	}

    strcpy(pKSM01_DATA.UPDTIM		,"");
    if ( VarIsNull(Query1->FieldValues["UPDTIM"]) != true
    &&  VarIsEmpty(Query1->FieldValues["UPDTIM"]) != true )
    {
	    sBuf  	= Query1->FieldValues["UPDTIM"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.UPDTIM  	,sBuf.c_str());
    }
	if(AnsiString(pKSM01_DATA.UPDTIM).Length()!=4)
	{
		strcpy(pKSM01_DATA.UPDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
	}

    strcpy(pKSM01_DATA.UPDCHR		,"");
    if ( VarIsNull(Query1->FieldValues["UPDCHR"]) != true
    &&  VarIsEmpty(Query1->FieldValues["UPDCHR"]) != true )
    {
	    sBuf  	= Query1->FieldValues["UPDCHR"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.UPDCHR  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.UPDCNT		,"");
    if ( VarIsNull(Query1->FieldValues["UPDCNT"]) != true
    &&  VarIsEmpty(Query1->FieldValues["UPDCNT"]) != true )
    {
    	sBuf  	= Query1->FieldValues["UPDCNT"];                        	//品番（出荷時はこれをキーにする）
	    strcpy(pKSM01_DATA.UPDCNT  	,sBuf.c_str());
    }

    strcpy(pKSM01_DATA.UPDNAME , "");
    if ( VarIsNull(Query1->FieldValues["UPDNAME"]) != true
    &&  VarIsEmpty(Query1->FieldValues["UPDNAME"]) != true )
    {
	    sBuf  	= Query1->FieldValues["UPDNAME"];                        	//更新者
    	strcpy(pKSM01_DATA.UPDNAME , sBuf.c_str());
    }


    // 2003/10/06 A.Tamura 海老様の要望により「外観＝良（デフォルト値）」を取りやめました。
    //                     と同時に、デフォルト測定者を製品規格マスターの担当者から表示するのを止めました。
    strcpy(pKSM01_DATA.UPDCHR	,"0");
	strcpy(pKSM01_DATA.UPDNAME	,"");

    strcpy(pKSM01_DATA.SOKCHR		,"");
    if ( VarIsNull(Query1->FieldValues["SOKCHR"]) != true
    &&  VarIsEmpty(Query1->FieldValues["SOKCHR"]) != true )
    {
	    sBuf  	= Query1->FieldValues["SOKCHR"];                        	//品番（出荷時はこれをキーにする）
    	strcpy(pKSM01_DATA.SOKCHR  	,sBuf.c_str());
    }
    
	Query1->Close();
	return( true );
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：製品規格明細マスターの読み込み。
//
//  機能説明
//    製品規格明細マスター（出荷）を読み込みバッファへ展開する。
//  　同時に空白行も読み込む
//    (ここで読み込まれた結果で出荷（測定）の白抜きが行われます）
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
void __fastcall TForm1::Get_KSM02(void)
{
	int i1;
	AnsiString sBuf,sDTKSHIN,sLot;
    iSYUKA_KOMKCNT = 0;

    memset(&pSYUKA_DATA,(int)NULL,sizeof(pSYUKA_DATA));

    GET_SPACE();


    for( i1 = 0; i1 < 1; i1++ )
    {
		switch(i1)
		{
		case 0:
			sDTKSHIN = pKSM01_DATA.DTKSHIN1_SZ;
			break;
		case 1:
			sDTKSHIN = pKSM01_DATA.DTKSHIN2_SZ;
			break;
		case 2:
			sDTKSHIN = pKSM01_DATA.DTKSHIN3_SZ;
			break;
		case 3:
			sDTKSHIN = pKSM01_DATA.DTKSHIN4_SZ;
			break;
		case 4:
			sDTKSHIN = pKSM01_DATA.DTKSHIN5_SZ;
			break;
		case 5:
			sDTKSHIN = pKSM01_DATA.DTKSHIN6_SZ;
			break;
   		}

	    sBuf = "SELECT * FROM KSM02";
    	sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
	    sBuf += " AND   REVCNT = 0" ;
	    sBuf += " AND   SKB_NO IN (2 , 3 )";                        //出荷検査項目、材料証明項目
    	sBuf += " ORDER BY KIKI_NO, KOMK_NM, KOMK_SUB, UNQ_NO ";

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
    	Query1->Open();
    	Query1->Active = true;

	    while( Query1->Eof == false )
    	{
   	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].DTKSHIN		,"");
	        if ( VarIsNull(Query1->FieldValues["DTKSHIN"]) != true
            && VarIsEmpty(Query1->FieldValues["DTKSHIN"]) != true )
            {
	        	sBuf = Query1->FieldValues["DTKSHIN"];						//得意先品番
    	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].DTKSHIN	,sBuf.c_str());
            }
   	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].REVCNT		,"");
	        if ( VarIsNull(Query1->FieldValues["REVCNT"]) != true
            && VarIsEmpty(Query1->FieldValues["REVCNT"]) != true )
            {
        		sBuf = Query1->FieldValues["REVCNT"];                     	//改訂番号
	        	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].REVCNT	,sBuf.c_str());
            }
   	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].UNQ_NO		,"");
	        if ( VarIsNull(Query1->FieldValues["UNQ_NO"]) != true
            && VarIsEmpty(Query1->FieldValues["UNQ_NO"]) != true )
            {
    	    	sBuf = Query1->FieldValues["UNQ_NO"];                    	//明細識別番号
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].UNQ_NO	,sBuf.c_str());
            }
   	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].ORDER_NO		,"");
	        if ( VarIsNull(Query1->FieldValues["ORDER_NO"]) != true
            && VarIsEmpty(Query1->FieldValues["ORDER_NO"]) != true )
            {
	        	sBuf = Query1->FieldValues["ORDER_NO"];                    	//表示
    	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].ORDER_NO	,sBuf.c_str());
            }
   	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].SKB_NO		,"");
	        if ( VarIsNull(Query1->FieldValues["SKB_NO"]) != true
            && VarIsEmpty(Query1->FieldValues["SKB_NO"]) != true )
            {
        		sBuf = Query1->FieldValues["SKB_NO"];
	        	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].SKB_NO	,sBuf.c_str());
			}

   	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].HINBAN_SK		,"");
	        if ( VarIsNull(Query1->FieldValues["HINBAN_SK"]) != true
            && VarIsEmpty(Query1->FieldValues["HINBAN_SK"]) != true )
            {
	        	sBuf = Query1->FieldValues["HINBAN_SK"];
    	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].HINBAN_SK	,sBuf.c_str());
            }

   	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KOMK_NO		,"");
	        if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true
            && VarIsEmpty(Query1->FieldValues["KOMK_NO"]) != true )
            {
	        	sBuf   = Query1->FieldValues["KOMK_NO"];
		        strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KOMK_NO		,sBuf.c_str());
            }
        	sBuf = "";
   	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KOMK_NM		,"");
	        if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true
            && VarIsEmpty(Query1->FieldValues["KOMK_NM"]) != true )
            {
			    sBuf   = Query1->FieldValues["KOMK_NM"];
    	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KOMK_NM		,sBuf.c_str());
			}

   	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KOMK_ENG		,"");
	        if ( VarIsNull(Query1->FieldValues["KOMK_ENG"]) != true
            && VarIsEmpty(Query1->FieldValues["KOMK_ENG"]) != true )
            {
		        sBuf = Query1->FieldValues["KOMK_ENG"];
    	    	strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KOMK_ENG		,sBuf.c_str());
            }
        	sBuf = "";
            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KOMK_SUB		,"");
	        if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true
            && VarIsEmpty(Query1->FieldValues["KOMK_SUB"]) != true )
        	{
            	sBuf = Query1->FieldValues["KOMK_SUB"];
	            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KOMK_SUB		,sBuf.c_str());
    	    }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KOMK_SUB_ENG		,"");
	       	if ( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) != true
            && VarIsEmpty(Query1->FieldValues["KOMK_SUB_ENG"]) != true )
	        {
    	    	sBuf   = Query1->FieldValues["KOMK_SUB_ENG"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KOMK_SUB_ENG		,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKI_NO		,"");
    	    if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKI_NO"]) != true )
        	{
        		sBuf   = Query1->FieldValues["KIKI_NO"];
				strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKI_NO		,sBuf.c_str());
    	    }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKI_NM		,"");
			if ( VarIsNull(Query1->FieldValues["KIKI_NM"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKI_NM"]) != true )
	        {
    	    	sBuf   = Query1->FieldValues["KIKI_NM"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKI_NM   	,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].TANI		,"");
    	    if ( VarIsNull(Query1->FieldValues["TANI"]) != true
            && VarIsEmpty(Query1->FieldValues["TANI"]) != true )
			{
    	    	sBuf      = Query1->FieldValues["TANI"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].TANI      	,sBuf.c_str());
	        }
            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_TYPE		,"");
    	    if ( VarIsNull(Query1->FieldValues["KIKA_TYPE"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKA_TYPE"]) != true )
	        {
				sBuf = Query1->FieldValues["KIKA_TYPE"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_TYPE 	,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_KIND		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_KIND"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKA_KIND"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["KIKA_KIND"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_KIND 	,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_DECI		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_DECI"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKA_DECI"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["KIKA_DECI"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_DECI 	,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_NUM1		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_NUM1"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKA_NUM1"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["KIKA_NUM1"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_NUM1 	,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_NUM2		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_NUM2"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKA_NUM2"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["KIKA_NUM2"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_NUM2 	,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_NUM3		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_NUM3"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKA_NUM3"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["KIKA_NUM3"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_NUM3 	,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_STR		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_STR"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKA_STR"]) != true )
	        {
    	    	sBuf  = Query1->FieldValues["KIKA_STR"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_STR  	,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_SUB1		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKA_SUB1"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["KIKA_SUB1"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_SUB1 	,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_SUB2		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKA_SUB2"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["KIKA_SUB2"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_SUB2 	,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_SUB3		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKA_SUB3"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["KIKA_SUB3"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_SUB3 	,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].SOKU_SU		,"");
			if ( VarIsNull(Query1->FieldValues["SOKU_SU"]) != true
            && VarIsEmpty(Query1->FieldValues["SOKU_SU"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["SOKU_SU"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].SOKU_SU		,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].SOKU_FLG		,"");
			if ( VarIsNull(Query1->FieldValues["SOKU_FLG"]) != true
            && VarIsEmpty(Query1->FieldValues["SOKU_FLG"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["SOKU_FLG"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].SOKU_FLG		,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].TOKU_FLG		,"");
			if ( VarIsNull(Query1->FieldValues["TOKU_FLG"]) != true
            && VarIsEmpty(Query1->FieldValues["TOKU_FLG"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["TOKU_FLG"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].TOKU_FLG		,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_PRT		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_PRT"]) != true
            && VarIsEmpty(Query1->FieldValues["KIKA_PRT"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["KIKA_PRT"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].KIKA_PRT		,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].VALUE_TYPE		,"");
			if ( VarIsNull(Query1->FieldValues["VALUE_TYPE"]) != true
            && VarIsEmpty(Query1->FieldValues["VALUE_TYPE"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["VALUE_TYPE"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].VALUE_TYPE		,sBuf.c_str());
	        }

            strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].VALUE_DECI		,"");
			if ( VarIsNull(Query1->FieldValues["VALUE_DECI"]) != true
            && VarIsEmpty(Query1->FieldValues["VALUE_DECI"]) != true )
	        {
    	    	sBuf = Query1->FieldValues["VALUE_DECI"];
        		strcpy(pSYUKA_DATA[iSYUKA_KOMKCNT].VALUE_DECI		,sBuf.c_str());
	        }
        	iSYUKA_KOMKCNT ++;                                              //項目数
        	Query1->Next();
    	}
	}
    Query1->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：測定実績データ（KSD01）から実在する履歴ロットを読み込む
//
//  機能説明
//    測定実績データ（KSD01）の読み込み。
//    AnsiString　  ：sRIREKI_LOT へ履歴ロット文字列が入力されます。
//    iLOT_CNT      ：履歴ロット数が入ります。
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
void __fastcall TForm1::Get_RIRELOT(void)
{
    int i1,iLOT_CNT;
    AnsiString sBuf,sBuf1;


    //得意先品番をキーにして必要ロットの取得をする（履歴数分）
    sBuf =  "SELECT KSD01.LOTNO, KSD01.HINBAN FROM KSD01";
    sBuf += " inner join SD21S on KSD01.DTKSHIN = SD21S.DTKSHIN and KSD01.LOTNO = SD21S.LOTBNG and KSD01.HINBAN = SD21S.HINBAN";
    sBuf += " WHERE KSD01.DTKSHIN ='" + sNowDTKSHIN + "'";
    sBuf += " and   SD21S.DENYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";

    if( SGr_tSOKU->Cells[0][0].Length() == 5 ){
	    // 国内ロット（5桁）に対応
    	sBuf += " AND SUBSTR(KSD01.LOTNO,2) < '" + SGr_tSOKU->Cells[0][0].SubString(2,5) + "'";
		sBuf += " ORDER BY SUBSTR(KSD01.LOTNO,2) DESC";
	} else {
	    // 海外ロット（6桁）に対応
    	sBuf += " AND KSD01.LOTNO < '" + SGr_tSOKU->Cells[0][0] + "'";
		sBuf += " ORDER BY KSD01.LOTNO DESC";
	}

    iLOT_CNT = 0;         //全ロット数
	sRIREKI_LOT->Clear();
	sRIREKI_HIN->Clear();

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
    Query1->Open();
    Query1->Active = true;


    //ロットの抽出
    if( Query1->Eof == false ){

	    // 表示する履歴ロット数を決定します
	    iLOT_CNT = iNowRIRE_NUM;
	    i1 = Query1->RecordCount;
		if( i1 < iLOT_CNT ){
	    	iLOT_CNT = i1;
	    }

        // 表示する先頭ロットにレコードカーソルを移動します
        if( iLOT_CNT - 1 > 0 )	Query1->MoveBy(iLOT_CNT - 1);

        // 古い履歴ロットから順に取り出します。
        do
        {
        	sRIREKI_LOT->Add(Query1->FieldValues["LOTNO"]);
        	sRIREKI_HIN->Add(Query1->FieldValues["HINBAN"]);        //onishi
	        Query1->Prior();
	    }
        while( Query1->Bof == false );

    }
    Query1->Close();

	iRIRE_CNT = iLOT_CNT;			//履歴ロット数
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：検索処理メイン関数
//
//  機能説明
//    �@ORテーブルを作成します。
//    �A出荷（測定）のデータを読み込み表示します。
//    �B出荷（履歴）、素材（測定）、素材（履歴）読込／表示関数を呼び出します。
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
void __fastcall TForm1::Set_Ins_Disp(void)
{
    int i1,i2,i3,i4,iCol;
    int iPanelNum,iSokuGoukei;
    int iSokuCnt;
    int iPutKiki;
    AnsiString sBuf,sLot,sTempBuf,sBuf1;
    AnsiString sLot_Where;
    int nDRAW_GRID;
    double dMAX,dMIN;					//規格ソートに使用
    extern int iKikiCnt;
    AnsiString sHinban;	//20170616 Y.Onishi

    //ORテーブル作成用
    AnsiString KOMK_NM,KOMK_SUB,HINBAN_SK,TANI;
    AnsiString KIKI_NO,KOMK_NO,SOKU_SU,SKB_NO;

    iSokuGoukei = 0;
    //動的コントロールの開放
    DynamicCtrl_Free();

    memset(&pOldInfoGlaph,(int)NULL,sizeof(pOldInfoGlaph));

    //抽出ロットのｎ数のMAX値の抽出
    //履歴ロットの描画
    for( i1 = 0;i1 < Form1->iRIRE_CNT ; i1++)
    {
	    Form1->SGr_tRIRE->Cells[i1][0] = Form1->sRIREKI_LOT->Strings[i1];
	    Form1->SGr_tRIRE->Cells[i1][1] = Form1->sRIREKI_HIN->Strings[i1];          //onishi
    }

    iRIREKI_KOMKCNT = 0;

    // 測定（右側）ロットリストの作成
    sLot = "";
    for(i1 = 0; i1 < SGr_tSOKU->ColCount ; i1++)
    {
	    sLot += "'" + SGr_tSOKU->Cells[i1][0] + "',";
    }

    // 履歴（左側）ロットリストの作成
    for(i1=0;i1 < Form1->iRIRE_CNT ;i1++ )
    {
        sLot += "'" + Form1->sRIREKI_LOT->Strings[i1] + "',";
    }
    sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
    for(i1 = 0; i1 < SGr_tSOKU->ColCount ; i1++)
    {
        sLot_Where += "( LOTNO='" + SGr_tSOKU->Cells[i1][0] + "' AND ";
        sLot_Where += " HINBAN='" + SGr_tSOKU->Cells[i1][1] + "') OR ";
        sHinban = SGr_tSOKU->Cells[i1][1];	//20170616 Y.Onishi
    }

    for(i1=0;i1 < Form1->iRIRE_CNT ;i1++ )
    {
        sLot_Where += "( LOTNO='" + Form1->sRIREKI_LOT->Strings[i1] + "' AND ";
        sLot_Where += " HINBAN='" + Form1->sRIREKI_HIN->Strings[i1] + "') OR ";
    }
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↑

    SGr_vRIRE_SOZAI->RowCount = 1;
    SGr_vRIRE_SYUKA->RowCount = 1;

    sBuf = "SELECT KIKI_NO, KOMK_NM, KOMK_SUB, KOMK_NO, TANI, MAX(SOKU_SU) AS SOKU_SU_MAX FROM KSD02";
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
    sBuf += " AND SKB_NO IN ( 2 , 3 )";                        //出荷検査項目、材料証明項目
    //sBuf += " AND LOTNO IN (";
    //sBuf += sLot;
    //sBuf += " )";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";
    sBuf += " GROUP BY KIKI_NO, KOMK_NM, KOMK_SUB, KOMK_NO, TANI";
    sBuf += " ORDER BY KIKI_NO, KOMK_NM, KOMK_SUB, KOMK_NO, TANI";

    //履歴データ格納用メモリの宣言
    memset(&pRIREKI_DATA,(int)NULL,sizeof(pRIREKI_DATA));

    //For Debug
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
    Query1->Open();
    Query1->Active = true;

    //対象過去履歴の検索　STEP1

    while( Query1->Eof != true )
    {
        if ( VarIsNull(Query1->FieldValues["SOKU_SU_MAX"]) != true)
        {
            sBuf = Query1->FieldValues["SOKU_SU_MAX"];
            strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].SOKU_SU 	,sBuf.c_str());
	    }
        if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true)
        {
	        sBuf = Query1->FieldValues["KIKI_NO"];
            strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].KIKI_NO 	,sBuf.c_str());
	    }
        if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true)
        {
	        sBuf = Query1->FieldValues["KOMK_NM"];
    	    strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].KOMK_NM 	,sBuf.c_str());
        }
        if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true)
        {
	        sBuf = Query1->FieldValues["KOMK_SUB"];
            strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].KOMK_SUB	,sBuf.c_str());
        }
        if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true)
        {
	        sBuf = Query1->FieldValues["KOMK_NO"];
            strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].KOMK_NO	,sBuf.c_str());
        }
        if ( VarIsNull(Query1->FieldValues["TANI"]) != true)
        {
	    sBuf = Query1->FieldValues["TANI"];
            strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT].TANI		,sBuf.c_str());
        }
        iRIREKI_KOMKCNT ++;                                              //項目数
        Query1->Next();
    }
    Query1->Close();

    //現在の出荷用の項目と過去履歴の項目の最大数のORを別メモリ上へ格納
    iOrCnt = 0;

    memset(pTEMPORDATA,0x00,sizeof(pTEMPORDATA));

    //ORテーブル作成　Part1
    bool bALL_RIRE_DATA;				//履歴データフラグ
    bALL_RIRE_DATA = ALL_RIRE_DATA();	//新規ロットがあるかどうかを調べるだけの関数

    if(!bALL_RIRE_DATA)
    {
    	for(i1 = 0;i1 < iSYUKA_KOMKCNT;i1++)
	{
    	KOMK_NM 	= pSYUKA_DATA[i1].KOMK_NM;
	    KOMK_SUB 	= pSYUKA_DATA[i1].KOMK_SUB;
	    TANI 		= pSYUKA_DATA[i1].TANI;
    	HINBAN_SK 	= pSYUKA_DATA[i1].HINBAN_SK;
	    KOMK_NO 	= AnsiString(pSYUKA_DATA[i1].KOMK_NO).ToIntDef(0);
    	KIKI_NO 	= AnsiString(pSYUKA_DATA[i1].KIKI_NO).ToIntDef(0);
        SOKU_SU 	= AnsiString(pSYUKA_DATA[i1].SOKU_SU).ToIntDef(0);
	    for( i2 = 0;i2 < iRIREKI_KOMKCNT ; i2++)
    	{
        	if(AnsiString(pRIREKI_DATA[i2].KIKI_NO).ToIntDef(0) != 9999)
	        {
    	        if((KOMK_NM 			== AnsiString(pRIREKI_DATA[i2].KOMK_NM))
        	    &&(KOMK_SUB 			== AnsiString(pRIREKI_DATA[i2].KOMK_SUB))
        	    &&(TANI 				== AnsiString(pRIREKI_DATA[i2].TANI))
            	&&(KOMK_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KOMK_NO).ToIntDef(0))
                &&(KIKI_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KIKI_NO).ToIntDef(0)))
	            {
    	            	if(SOKU_SU.ToIntDef(0) <  AnsiString(pRIREKI_DATA[i2].SOKU_SU).ToIntDef(0))
        	            {
            	        	SOKU_SU = AnsiString(pRIREKI_DATA[i2].SOKU_SU).ToIntDef(0);
                	    }
	                    strcpy(pRIREKI_DATA[i2].KIKI_NO,"9999");
                    }
                }
    	    }
            strcpy(pTEMPORDATA[iOrCnt].KIKI_NO	,KIKI_NO.c_str());
            strcpy(pTEMPORDATA[iOrCnt].KOMK_NM	,KOMK_NM.c_str());
            strcpy(pTEMPORDATA[iOrCnt].KOMK_NO	,KOMK_NO.c_str());
            strcpy(pTEMPORDATA[iOrCnt].KOMK_SUB	,KOMK_SUB.c_str());
            strcpy(pTEMPORDATA[iOrCnt].TANI		,TANI.c_str());
            strcpy(pTEMPORDATA[iOrCnt].SOKU_SU	,SOKU_SU.c_str());
            strcpy(pTEMPORDATA[iOrCnt].HINBAN_SK,HINBAN_SK.c_str());
            iOrCnt++;
    	}
    }
    for( i1 = 0;i1 < iRIREKI_KOMKCNT ; i1++)
    {
    	if(AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0) != 9999)
	{
    	    KOMK_NM = pRIREKI_DATA[i1].KOMK_NM;
            KOMK_SUB =pRIREKI_DATA[i1].KOMK_SUB;
            TANI =pRIREKI_DATA[i1].TANI;
            HINBAN_SK =pRIREKI_DATA[i1].HINBAN_SK;
	        KOMK_NO = AnsiString(pRIREKI_DATA[i1].KOMK_NO).ToIntDef(0);
    	    KIKI_NO = AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0);
            SOKU_SU = AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0);

	        strcpy(pTEMPORDATA[iOrCnt].KIKI_NO	,KIKI_NO.c_str());
    	        strcpy(pTEMPORDATA[iOrCnt].KOMK_NM	,KOMK_NM.c_str());
                strcpy(pTEMPORDATA[iOrCnt].KOMK_NO	,KOMK_NO.c_str());
            	strcpy(pTEMPORDATA[iOrCnt].KOMK_SUB	,KOMK_SUB.c_str());
            	strcpy(pTEMPORDATA[iOrCnt].TANI		,TANI.c_str());
	        strcpy(pTEMPORDATA[iOrCnt].SOKU_SU	,SOKU_SU.c_str());
    	        strcpy(pTEMPORDATA[iOrCnt].HINBAN_SK,HINBAN_SK.c_str());
                iOrCnt++;
	}
    }

// ---------------------------------------------------------
//現在の出荷用の項目と測定実績の項目の最大数のORを別メモリ上へ格納
//測定実績読み取り
//抽出ロットのｎ数のMAX値の抽出
    memset(pRIREKI_DATA,0x00,sizeof(pRIREKI_DATA));

    int iRIREKI_KOMKCNT2;
    iRIREKI_KOMKCNT2 = 0;
    sLot ="";
    for(i1 = 0;i1 <= SGr_tRIRE->ColCount ; i1++)
    {
    	if(SGr_tRIRE->Cells[i1][0].Trim().Length() != 0)
    	{
        	sLot += "'" + SGr_tRIRE->Cells[i1][0] + "'" + ",";
    	}
    }
    sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
    for(i1 = 0;i1 <= SGr_tRIRE->ColCount ; i1++)
    {
    	if(SGr_tRIRE->Cells[i1][0].Trim().Length() != 0)
    	{
            sLot_Where += "( LOTNO='" + SGr_tRIRE->Cells[i1][0] + "' AND ";
            sLot_Where += " HINBAN='" + SGr_tRIRE->Cells[i1][1] + "') OR ";
    	}
    }
    sLot_Where = sLot.SubString(1,sLot.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

    if( sLot > 3 )          //ロットがあれば
    {
        SGr_vRIRE_SOZAI->RowCount = 1;
        SGr_vRIRE_SYUKA->RowCount = 1;

        sBuf  = "SELECT KIKI_NO, KOMK_NM, KOMK_SUB, TANI, KOMK_NO,";
		sBuf += " MAX(SOKU_SU) AS SOKU_SU_MAX FROM KSD02";
        sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
        sBuf += " AND (SKB_NO = 2 OR SKB_NO = 3 )";                        //出荷検査項目、材料証明項目
        //sBuf += " AND LOTNO IN (" + sLot + ")";
        sBuf += " AND (";
        sBuf += sLot_Where;
        sBuf += " )";
        sBuf += " GROUP BY KIKI_NO, KOMK_NM, KOMK_SUB, TANI, KOMK_NO";
        sBuf += " ORDER BY KIKI_NO, KOMK_NM, KOMK_SUB, TANI, KOMK_NO";

        //For Debug
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
        Query1->Open();
        Query1->Active = true;

        //出荷検査ロット中で検査済みロットの検索
		while( Query1->Eof == false )
    	{
    		sBuf = Query1->FieldValues["SOKU_SU_MAX"];
        	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].SOKU_SU		,sBuf.c_str());

        	sBuf = Query1->FieldValues["KIKI_NO"];
        	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KIKI_NO		,sBuf.c_str());

        	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KOMK_NM 		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true
        	&& VarIsEmpty(Query1->FieldValues["KOMK_NM"]) != true )
        	{
        		sBuf = Query1->FieldValues["KOMK_NM"];
        		strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KOMK_NM 		,sBuf.c_str());
			}
        	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KOMK_SUB 		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true
        	&& VarIsEmpty(Query1->FieldValues["KOMK_SUB"]) != true )
        	{
        		sBuf = Query1->FieldValues["KOMK_SUB"];
            	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KOMK_SUB	,sBuf.c_str());
        	}
        	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].TANI 		,"");
        	if ( VarIsNull(Query1->FieldValues["TANI"]) != true
        	&& VarIsEmpty(Query1->FieldValues["TANI"]) != true )
        	{
        		sBuf = Query1->FieldValues["TANI"];
            	strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].TANI	,sBuf.c_str());
        	}
            if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true)
            {
				sBuf = Query1->FieldValues["KOMK_NO"];
                strcpy(pRIREKI_DATA[iRIREKI_KOMKCNT2].KOMK_NO	,sBuf.c_str());
            }
        	iRIREKI_KOMKCNT2 ++;                                              //項目数
        	Query1->Next();
    	}
    	Query1->Close();
    }

    memset(pORDATA,0x00,sizeof(pORDATA));

    iOrCnt2	 	= 0;
    //iRireCnt 	= 0;
    iSyukaCnt2 	= 0;

//ORデータ作成Part2
    for(i1 = 0;i1 < iOrCnt;i1++)
    {
    	KOMK_NM 	= pTEMPORDATA[i1].KOMK_NM;
        KOMK_SUB 	= pTEMPORDATA[i1].KOMK_SUB;
        TANI 		= pTEMPORDATA[i1].TANI;
        HINBAN_SK 	= pTEMPORDATA[i1].HINBAN_SK;
        KOMK_NO 	= AnsiString(pTEMPORDATA[i1].KOMK_NO).ToIntDef(0);
        KIKI_NO 	= AnsiString(pTEMPORDATA[i1].KIKI_NO).ToIntDef(0);
        SOKU_SU 	= AnsiString(pTEMPORDATA[i1].SOKU_SU).ToIntDef(0);
        for( i2 = 0;i2 < iRIREKI_KOMKCNT2 ; i2++)
        {
        	if(AnsiString(pRIREKI_DATA[i2].KIKI_NO).ToIntDef(0) != 9999)
            {
            	if((KOMK_NM 			== AnsiString(pRIREKI_DATA[i2].KOMK_NM))
                &&(KOMK_SUB 			== AnsiString(pRIREKI_DATA[i2].KOMK_SUB))
                &&(TANI 				== AnsiString(pRIREKI_DATA[i2].TANI))
                &&(KOMK_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KOMK_NO).ToIntDef(0))
                &&(KIKI_NO.ToIntDef(0) 	== AnsiString(pRIREKI_DATA[i2].KIKI_NO).ToIntDef(0)))
                {
                	if(SOKU_SU.ToIntDef(0) <  AnsiString(pRIREKI_DATA[i2].SOKU_SU).ToIntDef(0))
                    {
                    	SOKU_SU = AnsiString(pRIREKI_DATA[i2].SOKU_SU).ToIntDef(0);
                    }
                    strcpy(pRIREKI_DATA[i2].KIKI_NO,"9999");
                }
            }
        }
        strcpy(pORDATA[iOrCnt2].KIKI_NO	,KIKI_NO.c_str());
        strcpy(pORDATA[iOrCnt2].KOMK_NM	,KOMK_NM.c_str());
        strcpy(pORDATA[iOrCnt2].KOMK_NO	,KOMK_NO.c_str());
        strcpy(pORDATA[iOrCnt2].KOMK_SUB,KOMK_SUB.c_str());
        strcpy(pORDATA[iOrCnt2].TANI	,TANI.c_str());
        strcpy(pORDATA[iOrCnt2].SOKU_SU	,SOKU_SU.c_str());
        strcpy(pORDATA[iOrCnt2].HINBAN_SK,HINBAN_SK.c_str());
        iOrCnt2++;
    }
    for( i1 = 0;i1 < iRIREKI_KOMKCNT2 ; i1++)
    {
    	if(AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0) != 9999)
        {
        	KOMK_NM 	= pRIREKI_DATA[i1].KOMK_NM;
            KOMK_SUB	= pRIREKI_DATA[i1].KOMK_SUB;
            TANI 		= pRIREKI_DATA[i1].TANI;
            HINBAN_SK	= pRIREKI_DATA[i1].HINBAN_SK;
            KOMK_NO		= AnsiString(pRIREKI_DATA[i1].KOMK_NO).ToIntDef(0);
            KIKI_NO		= AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0);
            SOKU_SU		= AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0);

            strcpy(pORDATA[iOrCnt2].KIKI_NO	,KIKI_NO.c_str());
            strcpy(pORDATA[iOrCnt2].KOMK_NM	,KOMK_NM.c_str());
            strcpy(pORDATA[iOrCnt2].KOMK_NO	,KOMK_NO.c_str());
            strcpy(pORDATA[iOrCnt2].KOMK_SUB,KOMK_SUB.c_str());
            strcpy(pORDATA[iOrCnt2].TANI	,TANI.c_str());
            strcpy(pORDATA[iOrCnt2].SOKU_SU	,SOKU_SU.c_str());
            strcpy(pORDATA[iOrCnt2].HINBAN_SK	,HINBAN_SK.c_str());
            iOrCnt2++;
        }
    }
	iOrCnt = iOrCnt2;

// ---------------------------------------------------------


//総ｎ数の算出
    iSokuCnt = 0;
    for(i1=0;i1<iOrCnt;i1++)
    {
		sBuf = pORDATA[i1].SOKU_SU;
        iSokuCnt += sBuf.ToIntDef(0);
    }

//測定機器名称、項目名称、単位、規格の抽出（最新のものを表示する）
    for(i1=0;i1<iOrCnt;i1++)
    {
        //マスターから読み込み
        sBuf = "SELECT * FROM KSM02";
        sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
        sBuf += " AND KIKI_NO = " + AnsiString(pORDATA[i1].KIKI_NO);

        // 2003/11/19 A.Tamura 【同じ項目で利用可能とならない問題】の対応
        sBuf += " AND KOMK_NO = " + AnsiString(pORDATA[i1].KOMK_NO);

        if(AnsiString(pORDATA[i1].KOMK_NM).Length() != 0)
        {
            sBuf += " AND KOMK_NM ='"  + AnsiString(pORDATA[i1].KOMK_NM) + "'";
        }
        else
        {
            sBuf += " AND KOMK_NM IS NULL";
        }
        if(AnsiString(pORDATA[i1].KOMK_SUB).Length() != 0)
        {
            sBuf += " AND KOMK_SUB ='"  + AnsiString(pORDATA[i1].KOMK_SUB) + "'";
        }
        else
        {
            sBuf += " AND KOMK_SUB IS NULL";
        }
        if(AnsiString(pORDATA[i1].TANI).Length() != 0)
        {
            sBuf += " AND TANI ='"  + AnsiString(pORDATA[i1].TANI) + "'";
        }
        else
        {
            sBuf += " AND TANI IS NULL";
        }
		sBuf += " AND REVCNT = 0";
        sBuf += " AND (SKB_NO = 2 OR SKB_NO = 3)";                        //出荷検査項目、材料証明項目

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
        Query1->Open();
        Query1->Active = true;

// 2003/11/19 A.Tamura 【同じ項目で利用可能とならない問題】
// この検索は、必ずKSM02でHITするのでKOMK_NOが必ずKSM02から作成される
// 品番[1584320575]　ロット[80293]以前と[90294]以降を比べると出荷検査項目[外観]が
// ダブり表示される(ロット[80293]以前の[外観]は測定可能とならない)のは、KSM02のKOMK_NOで
// ORDATAが作成されるからである
// 対策は、
// �@検索キーにKOMK_NOを付ける事で、明確にKSM02又はKSD02から検索する様に修正する
// �AKSM02(主)+KSD02(副)でラベル表示（左端の動的ラベル）が作成されるのではなく（←現在の処理）
//   測定Grid右側の左端ロットKSD02orKSM02(主)+KSD02(副)が最優先...
//　【�Aは「現在の処理」にした方が処理がシンプル＆現在問題となっていないので《対応しない方が良い》
//　　と、このコメントを書いている時の判断でした。＝�Aの対策は不要!! 】
        if( Query1->Eof == false )
        {

            strcpy(pORDATA[i1].DTKSHIN		,"");
        	if ( VarIsNull(Query1->FieldValues["DTKSHIN"]) != true )
            {
	        	sBuf 		= Query1->FieldValues["DTKSHIN"];			//得意先品番
    	    	strcpy(pORDATA[i1].DTKSHIN		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].REVCNT		,"");
        	if ( VarIsNull(Query1->FieldValues["REVCNT"]) != true  )
            {
        		sBuf 		= Query1->FieldValues["REVCNT"];      		//改訂番号
        		strcpy(pORDATA[i1].REVCNT		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].UNQ_NO		,"");
        	if ( VarIsNull(Query1->FieldValues["UNQ_NO"]) != true  )
            {
	        	sBuf 		= Query1->FieldValues["UNQ_NO"];    		//明細NO
    	    	strcpy(pORDATA[i1].UNQ_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].ORDER_NO		,"");
        	if ( VarIsNull(Query1->FieldValues["ORDER_NO"]) != true )
            {
        		sBuf 		= Query1->FieldValues["ORDER_NO"];  		//表示・印刷順
        		strcpy(pORDATA[i1].ORDER_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].SKB_NO		,"");
        	if ( VarIsNull(Query1->FieldValues["SKB_NO"]) != true   )
            {
	        	sBuf 		= Query1->FieldValues["SKB_NO"];    		//識別NO
    	    	strcpy(pORDATA[i1].SKB_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].HINBAN_SK		,"");
        	if ( VarIsNull(Query1->FieldValues["HINBAN_SK"]) != true)
            {
        		sBuf 		= Query1->FieldValues["HINBAN_SK"];  	//品番
        		strcpy(pORDATA[i1].HINBAN_SK		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_NO		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true  )
            {
	        	sBuf 		= Query1->FieldValues["KOMK_NO"];   		//測定項目NO
    	    	strcpy(pORDATA[i1].KOMK_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_NM		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true  )
            {
				sBuf 		= Query1->FieldValues["KOMK_NM"];  		//測定項目名称
				strcpy(pORDATA[i1].KOMK_NM		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_ENG		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_ENG"]) != true )
            {
				sBuf 		= Query1->FieldValues["KOMK_ENG"]; 		//測定項目名称（英語）
				strcpy(pORDATA[i1].KOMK_ENG		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_SUB		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true )
            {
				sBuf 		= Query1->FieldValues["KOMK_SUB"];   	//測定項目サブ名称
				strcpy(pORDATA[i1].KOMK_SUB		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_SUB_ENG		,"");
        	if ( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) != true )
            {
				sBuf 		= Query1->FieldValues["KOMK_SUB_ENG"];	//測定項目サブ名称（英語）
				strcpy(pORDATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKI_NO		,"");
			if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true )
            {
				sBuf 		= Query1->FieldValues["KIKI_NO"];     	//測定機器NO
				strcpy(pORDATA[i1].KIKI_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKI_NM		,"");
			if ( VarIsNull(Query1->FieldValues["KIKI_NM"]) != true )
            {
				sBuf 		= Query1->FieldValues["KIKI_NM"];  		//測定機器名称
				strcpy(pORDATA[i1].KIKI_NM		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].TANI		,"");
			if ( VarIsNull(Query1->FieldValues["TANI"]) != true    )
            {
            	sBuf 		= Query1->FieldValues["TANI"];         	//単位
            	strcpy(pORDATA[i1].TANI			,sBuf.c_str());
   			}
            strcpy(pORDATA[i1].KIKA_TYPE		,"");
           	if ( VarIsNull(Query1->FieldValues["KIKA_TYPE"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_TYPE"];      	//規格タイプ
            	strcpy(pORDATA[i1].KIKA_TYPE	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_KIND		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_KIND"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_KIND"];        	//規格種類
            	strcpy(pORDATA[i1].KIKA_KIND	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_DECI		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_DECI"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_DECI"];      	//規格小数点以下桁数
            	strcpy(pORDATA[i1].KIKA_DECI	,sBuf.c_str());
			}
            strcpy(pORDATA[i1].KIKA_NUM1		,"");
        	if ( VarIsNull(Query1->FieldValues["KIKA_NUM1"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_NUM1"];     		//規格値１
            	strcpy(pORDATA[i1].KIKA_NUM1	,sBuf.c_str());
			}
            strcpy(pORDATA[i1].KIKA_NUM2		,"");
        	if ( VarIsNull(Query1->FieldValues["KIKA_NUM2"]) != true )
            {
	            sBuf 	= Query1->FieldValues["KIKA_NUM2"];        	//規格値２
    	        strcpy(pORDATA[i1].KIKA_NUM2	,sBuf.c_str());
			}
            strcpy(pORDATA[i1].KIKA_NUM3		,"");
        	if ( VarIsNull(Query1->FieldValues["KIKA_NUM3"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_NUM3"];        	//規格値３
            	strcpy(pORDATA[i1].KIKA_NUM3	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_STR		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_STR"]) != true  )
            {
            	sBuf  	= Query1->FieldValues["KIKA_STR"];        	//規格値文字
            	strcpy(pORDATA[i1].KIKA_STR		,sBuf.c_str());
   			}
            strcpy(pORDATA[i1].KIKA_SUB1		,"");
           	if ( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_SUB1"];       	//規格値サブ１
            	strcpy(pORDATA[i1].KIKA_SUB1	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_SUB2		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_SUB2"];          //規格値サブ２
            	strcpy(pORDATA[i1].KIKA_SUB2	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_SUB3		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) != true )
            {
            	sBuf 	= Query1->FieldValues["KIKA_SUB3"];         	//規格値サブ３
            	strcpy(pORDATA[i1].KIKA_SUB3	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].SOKU_FLG		,"");
			if ( VarIsNull(Query1->FieldValues["SOKU_FLG"]) != true  )
            {
             	sBuf 	= Query1->FieldValues["SOKU_FLG"];        	//測定項目の有無
            	strcpy(pORDATA[i1].SOKU_FLG	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].TOKU_FLG		,"");
			if ( VarIsNull(Query1->FieldValues["TOKU_FLG"]) != true  )
            {
             	sBuf 	= Query1->FieldValues["TOKU_FLG"];       	//特別項目の有無
            	strcpy(pORDATA[i1].TOKU_FLG	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_PRT		,"");
			if ( VarIsNull(Query1->FieldValues["KIKA_PRT"]) != true  )
            {
             	sBuf 	= Query1->FieldValues["KIKA_PRT"];     		//上限下限値の印刷
            	strcpy(pORDATA[i1].KIKA_PRT	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].VALUE_TYPE		,"");
            if ( VarIsNull(Query1->FieldValues["VALUE_TYPE"]) != true)
            {
             	sBuf 	= Query1->FieldValues["VALUE_TYPE"];         //測定値表現
            	strcpy(pORDATA[i1].VALUE_TYPE	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].VALUE_DECI		,"");
			if ( VarIsNull(Query1->FieldValues["VALUE_DECI"]) != true)
            {
             	sBuf 	= Query1->FieldValues["VALUE_DECI"];         //測定値小数点以下桁数
            	strcpy(pORDATA[i1].VALUE_DECI	,sBuf.c_str());
			}
        }
        else
        {
			//2003.05.10 E.Takase Add↓
			sBuf  = "SELECT  KSD02.*, SM12S.TANNAM As UPDNAME ";
			sBuf += " FROM KSD02 LEFT JOIN SM12S ON KSD02.UPDCHR = SM12S.TANSYA ";
            sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
            sBuf += " AND KIKI_NO = " + AnsiString(pORDATA[i1].KIKI_NO) ;

        	// 2003/11/19 A.Tamura 【同じ項目で利用可能とならない問題】の対応
        	sBuf += " AND KOMK_NO = " + AnsiString(pORDATA[i1].KOMK_NO);

            if(AnsiString(pORDATA[i1].KOMK_NM).Length() != 0)
            {
                sBuf += " AND KOMK_NM ='"  + AnsiString(pORDATA[i1].KOMK_NM) + "'";
            }
            else
            {
                sBuf += " AND KOMK_NM IS NULL";
            }
            if(AnsiString(pORDATA[i1].KOMK_SUB).Length() != 0)
            {
                sBuf += " AND KOMK_SUB ='"  + AnsiString(pORDATA[i1].KOMK_SUB) + "'";
            }
            else
            {
                sBuf += " AND KOMK_SUB IS NULL";
            }
            if(AnsiString(pORDATA[i1].TANI).Length() != 0)
            {
                sBuf += " AND TANI ='"  + AnsiString(pORDATA[i1].TANI) + "'";
            }
            else
            {
                sBuf += " AND TANI IS NULL";
            }
            sBuf += " AND SKB_NO IN ( 2 , 3) ";                        //出荷検査項目、材料証明項目
            //20170616 Y.Onishi
            sBuf += " AND KSD02.HINBAN = '" + sHinban + "' ";
            
            sBuf += " ORDER BY KSD02.UPDYMD DESC, KSD02.UPDTIM DESC";

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
            Query1->Open();
            Query1->Active = true;
		//履歴読み込み（ＫＳＤ０２）
            if( Query1->Eof == false )
            {
	            strcpy(pORDATA[i1].DTKSHIN		,"");
    	    	if ( VarIsNull(Query1->FieldValues["DTKSHIN"]) != true )
            	{
		        	sBuf 		= Query1->FieldValues["DTKSHIN"];		//得意先品番
    		    	strcpy(pORDATA[i1].DTKSHIN		,sBuf.c_str());
				}
				strcpy(pORDATA[i1].UNQ_NO		,"");
    	    	if ( VarIsNull(Query1->FieldValues["UNQ_NO"]) != true  )
            	{
	        		sBuf 		= Query1->FieldValues["UNQ_NO"];    		//明細NO
    	    		strcpy(pORDATA[i1].UNQ_NO		,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].ORDER_NO		,"");
    	    	if ( VarIsNull(Query1->FieldValues["ORDER_NO"]) != true )
            	{
        			sBuf 		= Query1->FieldValues["ORDER_NO"];  		//表示・印刷順
	        		strcpy(pORDATA[i1].ORDER_NO		,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].SKB_NO		,"");
    	    	if ( VarIsNull(Query1->FieldValues["SKB_NO"]) != true  )
            	{
    	    		sBuf 		= Query1->FieldValues["SKB_NO"];    		//識別NO
        			strcpy(pORDATA[i1].SKB_NO		,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].HINBAN_SK		,"");
    	    	if ( VarIsNull(Query1->FieldValues["HINBAN_SK"]) != true)
            	{
        			sBuf 		= Query1->FieldValues["HINBAN_SK"];  	//品番
	        		strcpy(pORDATA[i1].HINBAN_SK		,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].KOMK_NO		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true )
            	{
    	    		sBuf 		= Query1->FieldValues["KOMK_NO"];   		//測定項目NO
        			strcpy(pORDATA[i1].KOMK_NO		,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].KOMK_NM		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true )
            	{
					sBuf 		= Query1->FieldValues["KOMK_NM"];  		//測定項目名称
					strcpy(pORDATA[i1].KOMK_NM		,sBuf.c_str());
                }
	            strcpy(pORDATA[i1].KOMK_ENG		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KOMK_ENG"]) != true )
            	{
					sBuf 		= Query1->FieldValues["KOMK_ENG"]; 		//測定項目名称（英語）
					strcpy(pORDATA[i1].KOMK_ENG		,sBuf.c_str());
                }
	            strcpy(pORDATA[i1].KOMK_SUB		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true )
            	{
					sBuf 		= Query1->FieldValues["KOMK_SUB"];   	//測定項目サブ名称
					strcpy(pORDATA[i1].KOMK_SUB		,sBuf.c_str());
    	        }
	            strcpy(pORDATA[i1].KOMK_SUB_ENG		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) != true )
            	{
					sBuf 		= Query1->FieldValues["KOMK_SUB_ENG"];	//測定項目サブ名称（英語）
					strcpy(pORDATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
        	    }
	            strcpy(pORDATA[i1].KIKI_NO		,"");
				if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true )
	            {
					sBuf 		= Query1->FieldValues["KIKI_NO"];     	//測定機器NO
					strcpy(pORDATA[i1].KIKI_NO		,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKI_NM		,"");
				if ( VarIsNull(Query1->FieldValues["KIKI_NM"]) != true )
	            {
					sBuf 		= Query1->FieldValues["KIKI_NM"];  		//測定機器名称
					strcpy(pORDATA[i1].KIKI_NM		,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].TANI		,"");
				if ( VarIsNull(Query1->FieldValues["TANI"]) != true )
	            {
    	        	sBuf 		= Query1->FieldValues["TANI"];         	//単位
        	    	strcpy(pORDATA[i1].TANI			,sBuf.c_str());
	   			}
    	        strcpy(pORDATA[i1].KIKA_TYPE		,"");
        	   	if ( VarIsNull(Query1->FieldValues["KIKA_TYPE"]) != true )
	            {
    	        	sBuf 	= Query1->FieldValues["KIKA_TYPE"];      	//規格タイプ
        	    	strcpy(pORDATA[i1].KIKA_TYPE	,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKA_KIND		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_KIND"]) != true )
	            {
    	        	sBuf 	= Query1->FieldValues["KIKA_KIND"];        	//規格種類
        	    	strcpy(pORDATA[i1].KIKA_KIND	,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKA_DECI		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_DECI"]) != true )
	            {
    	        	sBuf 	= Query1->FieldValues["KIKA_DECI"];      	//規格小数点以下桁数
        	    	strcpy(pORDATA[i1].KIKA_DECI	,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].KIKA_NUM1		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KIKA_NUM1"]) != true )
            	{
	            	sBuf 	= Query1->FieldValues["KIKA_NUM1"];     		//規格値１
    	        	strcpy(pORDATA[i1].KIKA_NUM1	,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].KIKA_NUM2		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KIKA_NUM2"]) != true )
            	{
		            sBuf 	= Query1->FieldValues["KIKA_NUM2"];        	//規格値２
    		        strcpy(pORDATA[i1].KIKA_NUM2	,sBuf.c_str());
				}
	            strcpy(pORDATA[i1].KIKA_NUM3		,"");
    	    	if ( VarIsNull(Query1->FieldValues["KIKA_NUM3"]) != true )
            	{
	            	sBuf 	= Query1->FieldValues["KIKA_NUM3"];        	//規格値３
    	        	strcpy(pORDATA[i1].KIKA_NUM3	,sBuf.c_str());
        	    }
	            strcpy(pORDATA[i1].KIKA_STR		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_STR"]) != true  )
            	{
            		sBuf  	= Query1->FieldValues["KIKA_STR"];        	//規格値文字
	            	strcpy(pORDATA[i1].KIKA_STR		,sBuf.c_str());
   				}
        	    strcpy(pORDATA[i1].KIKA_SUB1		,"");
           		if ( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) != true )
    	        {
        	    	sBuf 	= Query1->FieldValues["KIKA_SUB1"];       	//規格値サブ１
            		strcpy(pORDATA[i1].KIKA_SUB1	,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKA_SUB2		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) != true )
	            {
    	        	sBuf 	= Query1->FieldValues["KIKA_SUB2"];          //規格値サブ２
        	    	strcpy(pORDATA[i1].KIKA_SUB2	,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKA_SUB3		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) != true )
	            {
    	        	sBuf 	= Query1->FieldValues["KIKA_SUB3"];         	//規格値サブ３
        	    	strcpy(pORDATA[i1].KIKA_SUB3	,sBuf.c_str());
	            }
	            strcpy(pORDATA[i1].SOKU_FLG		,"");
				if ( VarIsNull(Query1->FieldValues["SOKU_FLG"]) != true )
            	{
	             	sBuf 	= Query1->FieldValues["SOKU_FLG"];        	//測定項目の有無
    	        	strcpy(pORDATA[i1].SOKU_FLG	,sBuf.c_str());
        	    }
	            strcpy(pORDATA[i1].TOKU_FLG		,"");
				if ( VarIsNull(Query1->FieldValues["TOKU_FLG"]) != true )
	            {
    	         	sBuf 	= Query1->FieldValues["TOKU_FLG"];       	//特別項目の有無
        	    	strcpy(pORDATA[i1].TOKU_FLG	,sBuf.c_str());
	            }
    	        strcpy(pORDATA[i1].KIKA_PRT		,"");
				if ( VarIsNull(Query1->FieldValues["KIKA_PRT"]) != true )
	            {
    	         	sBuf 	= Query1->FieldValues["KIKA_PRT"];     		//上限下限値の印刷
        	    	strcpy(pORDATA[i1].KIKA_PRT	,sBuf.c_str());
            	}
	            strcpy(pORDATA[i1].VALUE_TYPE		,"");
    	        if ( VarIsNull(Query1->FieldValues["VALUE_TYPE"]) != true)
            	{
	             	sBuf 	= Query1->FieldValues["VALUE_TYPE"];         //測定値表現
    	        	strcpy(pORDATA[i1].VALUE_TYPE	,sBuf.c_str());
        	    }
	            strcpy(pORDATA[i1].VALUE_DECI		,"");
				if ( VarIsNull(Query1->FieldValues["VALUE_DECI"]) != true )
            	{
             		sBuf 	= Query1->FieldValues["VALUE_DECI"];         //測定値小数点以下桁数
	            	strcpy(pORDATA[i1].VALUE_DECI	,sBuf.c_str());
				}

            }
        }

        sBuf  = "SELECT  KSD02.*, SM12S.TANNAM As UPDNAME ";
        sBuf += " FROM KSD02 LEFT JOIN SM12S ON KSD02.UPDCHR = SM12S.TANSYA ";
        sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
        sBuf += " AND   KIKI_NO = " + AnsiString(pORDATA[i1].KIKI_NO) ;

        // 2003/11/19 A.Tamura 【同じ項目で利用可能とならない問題】の対応
        sBuf += " AND KOMK_NO = " + AnsiString(pORDATA[i1].KOMK_NO);

        if(AnsiString(pORDATA[i1].KOMK_NM).Length() != 0)
        {
            sBuf += " AND KOMK_NM ='"  + AnsiString(pORDATA[i1].KOMK_NM) + "'";
        }
        else
        {
            sBuf += " AND KOMK_NM IS NULL";
        }
        if(AnsiString(pORDATA[i1].KOMK_SUB).Length() != 0)
        {
            sBuf += " AND KOMK_SUB ='"  + AnsiString(pORDATA[i1].KOMK_SUB) + "'";
        }
        else
        {
            sBuf += " AND KOMK_SUB IS NULL";
        }
//単位が違う場合に対応(2003/09/01)
        if(AnsiString(pORDATA[i1].TANI).Length() != 0)
        {
            sBuf += " AND TANI ='"  + AnsiString(pORDATA[i1].TANI) + "'";
        }
        else
        {
            sBuf += " AND TANI IS NULL";
        }
        sBuf += " AND SKB_NO IN ( 2 , 3) ";                        //出荷検査項目、材料証明項目
        sBuf += " AND LOTNO ='" + AnsiString(SGr_tSOKU->Cells[0][0]).Trim() + "'";
        //20170616 Y.Onishi
        sBuf += " AND KSD02.HINBAN = '" + sHinban + "' ";

        sBuf += " ORDER BY KSD02.UPDYMD DESC, KSD02.UPDTIM DESC";
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
        Query1->Open();
        Query1->Active = true;
        if( Query1->Eof == false )
        {
            strcpy(pORDATA[i1].DTKSHIN		,"");
            if ( VarIsNull(Query1->FieldValues["DTKSHIN"]) != true )
            {
                sBuf 		= Query1->FieldValues["DTKSHIN"];		//得意先品番
                strcpy(pORDATA[i1].DTKSHIN		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].UNQ_NO		,"");
            if ( VarIsNull(Query1->FieldValues["UNQ_NO"]) != true  )
            {
                sBuf 		= Query1->FieldValues["UNQ_NO"];    		//明細NO
                strcpy(pORDATA[i1].UNQ_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].ORDER_NO		,"");
            if ( VarIsNull(Query1->FieldValues["ORDER_NO"]) != true )
            {
                sBuf 		= Query1->FieldValues["ORDER_NO"];  		//表示・印刷順
                strcpy(pORDATA[i1].ORDER_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].SKB_NO		,"");
            if ( VarIsNull(Query1->FieldValues["SKB_NO"]) != true  )
            {
                sBuf 		= Query1->FieldValues["SKB_NO"];    		//識別NO
                strcpy(pORDATA[i1].SKB_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].HINBAN_SK		,"");
            if ( VarIsNull(Query1->FieldValues["HINBAN_SK"]) != true)
            {
                sBuf 		= Query1->FieldValues["HINBAN_SK"];  	//品番
                strcpy(pORDATA[i1].HINBAN_SK		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_NO		,"");
            if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true )
            {
                sBuf 		= Query1->FieldValues["KOMK_NO"];   		//測定項目NO
                strcpy(pORDATA[i1].KOMK_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_NM		,"");
            if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true )
            {
                sBuf 		= Query1->FieldValues["KOMK_NM"];  		//測定項目名称
                strcpy(pORDATA[i1].KOMK_NM		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_ENG		,"");
            if ( VarIsNull(Query1->FieldValues["KOMK_ENG"]) != true )
            {
                sBuf 		= Query1->FieldValues["KOMK_ENG"]; 		//測定項目名称（英語）
                strcpy(pORDATA[i1].KOMK_ENG		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_SUB		,"");
            if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true )
            {
                sBuf 		= Query1->FieldValues["KOMK_SUB"];   	//測定項目サブ名称
                strcpy(pORDATA[i1].KOMK_SUB		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KOMK_SUB_ENG		,"");
            if ( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) != true )
            {
                sBuf 		= Query1->FieldValues["KOMK_SUB_ENG"];	//測定項目サブ名称（英語）
                strcpy(pORDATA[i1].KOMK_SUB_ENG		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKI_NO		,"");
            if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true )
            {
                sBuf 		= Query1->FieldValues["KIKI_NO"];     	//測定機器NO
                strcpy(pORDATA[i1].KIKI_NO		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKI_NM		,"");
            if ( VarIsNull(Query1->FieldValues["KIKI_NM"]) != true )
            {
                sBuf 		= Query1->FieldValues["KIKI_NM"];  		//測定機器名称
                strcpy(pORDATA[i1].KIKI_NM		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].TANI		,"");
            if ( VarIsNull(Query1->FieldValues["TANI"]) != true )
            {
                sBuf 		= Query1->FieldValues["TANI"];         	//単位
                strcpy(pORDATA[i1].TANI			,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_TYPE		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_TYPE"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_TYPE"];      	//規格タイプ
                strcpy(pORDATA[i1].KIKA_TYPE	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_KIND		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_KIND"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_KIND"];        	//規格種類
                strcpy(pORDATA[i1].KIKA_KIND	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_DECI		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_DECI"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_DECI"];      	//規格小数点以下桁数
                strcpy(pORDATA[i1].KIKA_DECI	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_NUM1		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_NUM1"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_NUM1"];     		//規格値１
                strcpy(pORDATA[i1].KIKA_NUM1	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_NUM2		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_NUM2"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_NUM2"];        	//規格値２
                strcpy(pORDATA[i1].KIKA_NUM2	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_NUM3		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_NUM3"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_NUM3"];        	//規格値３
                strcpy(pORDATA[i1].KIKA_NUM3	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_STR		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_STR"]) != true  )
            {
                sBuf  	= Query1->FieldValues["KIKA_STR"];        	//規格値文字
                strcpy(pORDATA[i1].KIKA_STR		,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_SUB1		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_SUB1"];       	//規格値サブ１
                strcpy(pORDATA[i1].KIKA_SUB1	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_SUB2		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_SUB2"];          //規格値サブ２
                strcpy(pORDATA[i1].KIKA_SUB2	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].KIKA_SUB3		,"");
            if ( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) != true )
            {
                sBuf 	= Query1->FieldValues["KIKA_SUB3"];         	//規格値サブ３
                strcpy(pORDATA[i1].KIKA_SUB3	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].VALUE_TYPE		,"");
            if ( VarIsNull(Query1->FieldValues["VALUE_TYPE"]) != true)
            {
                sBuf 	= Query1->FieldValues["VALUE_TYPE"];         //測定値表現
                strcpy(pORDATA[i1].VALUE_TYPE	,sBuf.c_str());
            }
            strcpy(pORDATA[i1].VALUE_DECI		,"");
            if ( VarIsNull(Query1->FieldValues["VALUE_DECI"]) != true )
            {
                sBuf 	= Query1->FieldValues["VALUE_DECI"];         //測定値小数点以下桁数
                strcpy(pORDATA[i1].VALUE_DECI	,sBuf.c_str());
            }

        }


        Query1->Close();
    }
	iOrCount = iOrCnt;


//規格の読み込みが終了したので改めてソート（規格の昇順）を行う

	double dHalf1,dHalf2;

    memset(pTEMPORDATA,0x00,sizeof(pTEMPORDATA));

//2003.05.15 M.HIRAI 修正 ↓
	for(i2 = 0; i2 < iOrCount-1; i2++)
	{
		for(i1 = i2+1; i1 < iOrCount; i1++)
		{
            //出荷検査項目と素材検査項目とを分ける
			//if( AnsiString(pORDATA[i2].SKB_NO) > AnsiString(pORDATA[i1].SKB_NO) )
			if( AnsiString(pORDATA[i2].SKB_NO).ToIntDef(0) > AnsiString(pORDATA[i1].SKB_NO).ToIntDef(0) )
			{
 			    Replace_ORData(i2, i1);
			}
		    //同一識別NO（同一検査項目）
			else if( AnsiString(pORDATA[i2].SKB_NO) == AnsiString(pORDATA[i1].SKB_NO) )
			{
                //機器別ソート
			    //if( AnsiString(pORDATA[i2].KIKI_NO) > AnsiString(pORDATA[i1].KIKI_NO) )
                if( AnsiString(pORDATA[i2].KIKI_NO).ToIntDef(0) > AnsiString(pORDATA[i1].KIKI_NO).ToIntDef(0) )
                {
     			    Replace_ORData(i2, i1);
                }
		        //同一機器NO（同一機器）検査
                else if( AnsiString(pORDATA[i2].KIKI_NO) == AnsiString(pORDATA[i1].KIKI_NO) )
                {
                    //規格ソート
        			GetKIKAKU(i2,&dMAX,&dMIN);
	    			dHalf1 = dMIN;
    	    		GetKIKAKU(i1,&dMAX,&dMIN);
			    	dHalf2 = dMIN;
				    if( dHalf1 > dHalf2 )
				    {
     			        Replace_ORData(i2, i1);
                    }
                }
            }
		}
	}

    //外観検査項目NO＝1を一番上に上げる
	for(i1 = 0; i1 < iOrCount; i1++)
	{
		if(AnsiString(pORDATA[ i1 ].KOMK_NO).ToIntDef(0) == 1)
		{
			// dTEMPORDATA[0] <- dORDATA[i1]
            ORData_To_Tmp(i1);
            //１つずつ下げる
			for(i2 = i1-1;i2 >= 0; i2--)
			{
			    // dORDATA[i2+1] <- dORDATA[i2]
                ORData_To_ORData( i2+1, i2 );
			}
			// dORDATA[0] <- dTEMPORDATA[0]
            Tmp_To_ORData(0);
            break;
		}
	}

    //同じ項目をまとめる
	for(i1 = 1; i1 < iOrCount-1; i1++)
	{
		KOMK_NM 	= pORDATA[ i1 ].KOMK_NM;
		KIKI_NO 	= pORDATA[ i1 ].KIKI_NO;
		KOMK_SUB	= pORDATA[ i1 ].KOMK_SUB;
		TANI		= pORDATA[ i1 ].TANI;
		SKB_NO 		= pORDATA[ i1 ].SKB_NO;
		for(i2 = i1+1; i2 < iOrCount; i2++)
		{
			if((AnsiString(pORDATA[ i2 ].KOMK_NM) == KOMK_NM)
            && (AnsiString(pORDATA[ i2 ].KIKI_NO) == KIKI_NO)
            && (AnsiString(pORDATA[ i2 ].SKB_NO) == SKB_NO))
			{
			    // dTEMPORDATA[0] <- dORDATA[i2]
                ORData_To_Tmp(i2);
			    //１つずつ下げる
				for(i3 = i2-1; i3 > i1; i3--)
				{
    			    // pORDATA[i3+1] <- pORDATA[i3]
                    ORData_To_ORData( i3+1, i3 );
				}
    			// dORDATA[i1+1] <- dTEMPORDATA[0]
                Tmp_To_ORData(i1+1);
        		break;
			}
		}
    }
//2003.05.15 M.HIRAI 修正 ↑


//総機器数の算出
    iKikiCnt = 1;
    i2 = AnsiString(pORDATA[0].KIKI_NO).ToIntDef(0);
    for(i1 = 0;i1 < iOrCnt ; i1++)
    {
        if(i2 != AnsiString(pORDATA[i1].KIKI_NO).ToIntDef(0))
        {
            i2 = AnsiString(pORDATA[i1].KIKI_NO).ToIntDef(0);
            iKikiCnt ++;
        }
    }

// 動的コントロールの作成(必要数分の宣言）
//外観検査はコントロールを使わないので数を１引く（外観検査は１項目として考える）
    if(AnsiString(pORDATA[0].KOMK_NO).ToIntDef(0) == 1)
    {
//        iOrCnt--;
//        iSokuCnt -= AnsiString(pORDATA[0].SOKU_SU).ToIntDef(0);
//        iKikiCnt--;
    }
    Pnl_SubBase 	= new TPanel *[iOrCount];
    Pnl_InsName  	= new TPanel *[iOrCount];
    Lab_KOMK_NM  	= new TLabel *[iOrCount];
    Lab_TANI     	= new TLabel *[iOrCount];
    Lab_KIKA     	= new TLabel *[iOrCount];
    Lab_UPKIKA   	= new TLabel *[iOrCount];
    Lab_LOKIKA   	= new TLabel *[iOrCount];
    Pnl_InsNo    	= new TPanel *[iSokuCnt];
    Pnl_InsKikiName = new TPanel *[iKikiCnt];
    Lab_KIKI_NM  	= new TLabel *[iKikiCnt];
    i2 = 0;
    i1 = 0;
    iContCnt = 0;
    iPnl_InsNoCnt = 0;
	iPnl_InsKikiNameCnt = 0;

    iPanelNum 			= 0;
    iSokuGoukei 		= 0;
    iPnl_InsNoCnt 		= 0;
    iPnl_InsNameCnt 	= 0;
    iPanelNum 			= 0;
    iSokuGoukei 		= 0;
    iPnl_InsNoCnt 		= 0;
    iContCnt			= 0;
    iPnl_InsKikiNameCnt = 0;


    SGr_vRIRE_SYUKA->RowCount = 1;
    SGr_vSOKU_SYUKA->RowCount = 1;
    PnlGAIKAN->Visible = false;
    bGAIKAN = false;

    Form1->Refresh();

    int nKIKIPNL_HIGHT;
	while( iContCnt < iOrCnt )
    {
    	SBx_Left_SYUKA->Refresh();
        iPutKiki = AnsiString(pORDATA[iContCnt].KIKI_NO).ToIntDef(0);
		nKIKIPNL_HIGHT = 0;
//同一機器の測定ループ
        while( iPutKiki == AnsiString(pORDATA[iContCnt].KIKI_NO).ToIntDef(0) && iContCnt < iOrCnt)
        {
//ベースパネルの描画
            sBuf = IntToStr(iContCnt);
            Pnl_SubBase[iContCnt] = new TPanel(SBx_Left_SYUKA);
            Pnl_SubBase[iContCnt]->Name = "Pnl_SubBase" + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
            Pnl_SubBase[iContCnt]->Parent = SBx_Left_SYUKA;
            Pnl_SubBase[iContCnt]->Left = Pnl_OriginalSubBase->Left;
//外観検査パネルなら
			if(AnsiString(pORDATA[iContCnt].KOMK_NO).ToIntDef(0) == 1)
			{
            	Pnl_SubBase[iContCnt]->Left = 0;
				PnlGAIKAN->Caption = AnsiString(pORDATA[iContCnt].KOMK_NM) + AnsiString(pORDATA[iContCnt].KIKA_STR);
			}
            if( iContCnt == 0 )
            {
                Pnl_SubBase[iContCnt]->Top = PnlGAIKAN->Top;
            }
            else
            {
                Pnl_SubBase[iContCnt]->Top =  Pnl_SubBase[iContCnt - 1 ]->Top+Pnl_SubBase[ iContCnt - 1 ]->Height; ;
            }
            Pnl_SubBase[iContCnt]->Width = Pnl_OriginalSubBase->Width;
//外観検査パネルなら
			if(AnsiString(pORDATA[iContCnt].KOMK_NO).ToIntDef(0) == 1)
			{
            	Pnl_SubBase[iContCnt]->Width = Pnl_SOKUHAN->Width ;
			}
            Pnl_SubBase[iContCnt]->Height =
				24*(AnsiString(pORDATA[iContCnt].SOKU_SU).ToIntDef(0))+(AnsiString(pORDATA[iContCnt].SOKU_SU).ToIntDef(0));
            Pnl_SubBase[iContCnt]->Ctl3D = true;
            Pnl_SubBase[iContCnt]->BevelInner = bvNone;
            Pnl_SubBase[iContCnt]->BevelOuter = bvNone;
            Pnl_SubBase[iContCnt]->BorderWidth = 0;
			nKIKIPNL_HIGHT += Pnl_SubBase[iContCnt]->Height;
            iPnl_InsSubBaseCnt ++;
//測定項目表示パネルの描画
            Pnl_InsName[iContCnt] = new TPanel(Pnl_SubBase[iContCnt]);
            Pnl_InsName[iContCnt]->Name = "Pnl_InsName" + AnsiString::StringOfChar('0', 2-sBuf.Length()) + sBuf;
            Pnl_InsName[iContCnt]->Alignment = taLeftJustify;
            Pnl_InsName[iContCnt]->Align =alLeft ;
            Pnl_InsName[iContCnt]->Caption = "";
            Pnl_InsName[iContCnt]->Parent = Pnl_SubBase[iContCnt];
            Pnl_InsName[iContCnt]->Left = Pnl_OrgInsName->Left;
            Pnl_InsName[iContCnt]->Top = 0;
            Pnl_InsName[iContCnt]->Width = Pnl_OrgInsName->Width;
			if(AnsiString(pORDATA[iContCnt].KOMK_NO).ToIntDef(0) == 1)
			{
            	Pnl_InsName[iContCnt]->Width = Pnl_SOKUHAN->Width ;
			}
            Pnl_InsName[iContCnt]->Height = Pnl_SubBase[iContCnt]->Height;
            Pnl_InsName[iContCnt]->Color = (TColor)GAIKAN_NAME_COLOR;
            Pnl_InsName[iContCnt]->Ctl3D = false;
            Pnl_InsName[iContCnt]->BevelInner = bvNone;
            Pnl_InsName[iContCnt]->BevelOuter = bvRaised;
            Pnl_InsName[iContCnt]->BorderStyle = bsNone;
            Pnl_InsName[iContCnt]->BorderWidth = 0;
			if(AnsiString(pORDATA[iContCnt].SKB_NO) == 3 )
			{
				Pnl_InsName[iContCnt]->Color = (TColor)0x00FFE1FD;
			}
            iPnl_InsNameCnt ++;
//測定項目+単位の描画
            Lab_KOMK_NM[iContCnt] =  new TLabel(Pnl_InsName[iContCnt]);
            Lab_KOMK_NM[iContCnt]->Parent = Pnl_InsName[iContCnt];
            Lab_KOMK_NM[iContCnt]->AutoSize = true;
            Lab_KOMK_NM[iContCnt]->Top = 6;
            Lab_KOMK_NM[iContCnt]->Left = 0;
            Lab_KOMK_NM[iContCnt]->Height = Lab_BASEKOMK_NM->Height;
            Lab_KOMK_NM[iContCnt]->Caption =
				AnsiString(pORDATA[iContCnt].KOMK_NM) + AnsiString(pORDATA[iContCnt].KOMK_SUB);
			if(AnsiString(pORDATA[iContCnt].KIKA_TYPE).ToIntDef(0) == 3)  Lab_KOMK_NM[iContCnt]->Caption += pORDATA[iContCnt].KIKA_STR;
            Lab_KOMK_NM[iContCnt]->Font->Size = 11;
//単位の描画
            Lab_TANI[iContCnt] =     new TLabel(Pnl_InsName[iContCnt]);
            Lab_TANI[iContCnt]->Parent    = Pnl_InsName[iContCnt];
            Lab_TANI[iContCnt]->AutoSize = true;
            Lab_TANI[iContCnt]->Caption = pORDATA[iContCnt].TANI;
            Lab_TANI[iContCnt]->Top = 6;
            Lab_TANI[iContCnt]->Height = Lab_BASETANI->Height;
            Lab_TANI[iContCnt]->Font->Size = 11;
            Lab_TANI[iContCnt]->Left = Pnl_InsName[iContCnt]->Width-Lab_TANI[iContCnt]->Width-2 ;
//ｎ数の表示
            iPanelNum = 0;
            for(i4=0 ; i4 < AnsiString(pORDATA[iContCnt].SOKU_SU).ToIntDef(0);i4++)
            {
                sBuf = IntToStr(iPanelNum);
                Pnl_InsNo[iPnl_InsNoCnt] = new TPanel(Pnl_SubBase[iContCnt]);
                Pnl_InsNo[iPnl_InsNoCnt]->Name = "Pnl_InsNo" + AnsiString::StringOfChar('0', 4-sBuf.Length()) + sBuf;
                Pnl_InsNo[iPnl_InsNoCnt]->Caption = i4+1;
                Pnl_InsNo[iPnl_InsNoCnt]->Parent = Pnl_SubBase[iContCnt];
                Pnl_InsNo[iPnl_InsNoCnt]->Left = Pnl_OrgInsNum->Left;
                Pnl_InsNo[iPnl_InsNoCnt]->Top = (Pnl_SubBase[iContCnt]->Height)/AnsiString(pORDATA[iContCnt].SOKU_SU).ToIntDef(0) * i4;
                Pnl_InsNo[iPnl_InsNoCnt]->Width = Pnl_OrgInsNum->Width;
                Pnl_InsNo[iPnl_InsNoCnt]->Height = (Pnl_SubBase[iContCnt]->Height)/AnsiString(pORDATA[iContCnt].SOKU_SU).ToIntDef(0);
                Pnl_InsNo[iPnl_InsNoCnt]->Color = (TColor)GAIKAN_NAME_COLOR;
//素材検査ならパネルの色を変える
				if(AnsiString(pORDATA[iContCnt].SKB_NO) == 3 )
				{
					Pnl_InsNo[iPnl_InsNoCnt]->Color = (TColor)0x00FFE1FD;
				}
//外観検査項目なら
				if(AnsiString(pORDATA[iContCnt].KOMK_NO).ToIntDef(0) == 1 )
				{
 					Pnl_InsNo[iPnl_InsNoCnt]->Visible = false;
				}
                iPanelNum ++;
                iSokuGoukei ++;
                iPnl_InsNoCnt ++;
                SGr_vRIRE_SYUKA->RowCount ++;
                SGr_vSOKU_SYUKA->RowCount ++;
            }
//規格の表示
//規格値メインラベル
            Lab_KIKA[iContCnt] =  new TLabel(Pnl_InsName[iContCnt]);
            Lab_KIKA[iContCnt]->Parent = Pnl_InsName[iContCnt];
            Lab_KIKA[iContCnt]->ParentColor = false;
            Lab_KIKA[iContCnt]->AutoSize = true;
            Lab_KIKA[iContCnt]->Top = Lab_BASEKIKA->Top;
            Lab_KIKA[iContCnt]->Left =  Pnl_InsName[iContCnt]->Width-Lab_KIKA[iContCnt]->Width;
            Lab_KIKA[iContCnt]->Height =  Lab_BASEKIKA->Height ;
            Lab_KIKA[iContCnt]->Font->Color = clBlack;
            Lab_KIKA[iContCnt]->Font->Size = 11;
            Lab_KIKA[iContCnt]->Font->Name ="ＭＳ ゴシック";
//規格値上限ラベル
            Lab_UPKIKA[iContCnt] =  new TLabel(Pnl_InsName[iContCnt]);
            Lab_UPKIKA[iContCnt]->Parent = Pnl_InsName[iContCnt];
            Lab_UPKIKA[iContCnt]->AutoSize = true;
            Lab_UPKIKA[iContCnt]->Top = Lab_BASEUPKIKA->Top;
            Lab_UPKIKA[iContCnt]->Left =  Lab_BASEUPKIKA->Left  ;
            Lab_UPKIKA[iContCnt]->Height =  Lab_BASEUPKIKA->Height ;
            Lab_UPKIKA[iContCnt]->Font->Color = clBlack;;
            Lab_UPKIKA[iContCnt]->Font->Size = 9;
            Lab_KIKA[iContCnt]->Font->Name ="ＭＳ ゴシック";
//規格値下限ラベル
            Lab_LOKIKA[iContCnt] =  new TLabel(Pnl_InsName[iContCnt]);
            Lab_LOKIKA[iContCnt]->Parent = Pnl_InsName[iContCnt];
            Lab_LOKIKA[iContCnt]->AutoSize = true;
            Lab_LOKIKA[iContCnt]->Top = Lab_BASELOKIKA->Top;
            Lab_LOKIKA[iContCnt]->Left =  Lab_BASELOKIKA->Left  ;
            Lab_LOKIKA[iContCnt]->Height =  Lab_BASELOKIKA->Height ;
            Lab_LOKIKA[iContCnt]->Font->Color = clBlack;;
            Lab_LOKIKA[iContCnt]->Font->Size = 9;
            Lab_KIKA[iContCnt]->Font->Name ="ＭＳ ゴシック";
//規格表示色々
//フォーマット指定（％*.*ｆ）
			AnsiString 	sDeci1;
   			sDeci1 = "0";
			for(i1 = 0;i1 < AnsiString(pORDATA[iContCnt].KIKA_DECI).ToIntDef(0);i1++)
			{
				if( i1 == 0 ) sDeci1 += ".";
				sDeci1 +="0";
			}

            switch(AnsiString(pORDATA[iContCnt].KIKA_TYPE).ToIntDef(0))
            {
            case 1:
                switch(AnsiString(pORDATA[iContCnt].KIKA_KIND).ToIntDef(0))
                {
                case 1:
                	//2003.05.08 E.Takase Add↓
                	sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM1),0.0));
                    sBuf +=  "〜";
                    sBuf += FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM2),0.0));
                    //2003.05.08 E.Takase Add↑
                    //2003.05.08 E.Takase Add コメント↓
                	//sBuf = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM1).ToDouble());
                    //sBuf +=  "〜";
                    //sBuf += FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM2).ToDouble());
                    //2003.05.08 E.Takase Add コメント↑
                    Lab_KIKA[iContCnt]->Caption = sBuf;
					break;
                case 2:
                    //2003.05.08 E.Takase Add↓
                    sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM2),0.0));
                    //2003.05.08 E.Takase Add↑
                    //2003.05.08 E.Takase Add コメント↓
                	//sBuf = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM2).ToDouble());
                    //2003.05.08 E.Takase Add コメント↑
                   	Lab_KIKA[iContCnt]->Caption = sBuf +"以下";
                    break;
                case 3:
                    //2003.05.08 E.Takase Add↓
                	sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM1),0.0));
                    //2003.05.08 E.Takase Add↑
                    //2003.05.08 E.Takase Add コメント↓
                	//sBuf = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM1).ToDouble());
                    //2003.05.08 E.Takase Add コメント↑
                    Lab_KIKA[iContCnt]->Caption = sBuf +"以上";
                    break;
                default:
                    break;
                }
                Lab_KIKA[iContCnt]->Left =
                Pnl_InsName[iContCnt]->Width-Lab_KIKA[iContCnt]->Width-2;
                Lab_UPKIKA[iContCnt]->Visible = false;
                Lab_LOKIKA[iContCnt]->Visible = false;
                break;
            case 2:
            	//2003.05.08 E.Takase Add↓
                sBuf = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM1),0.0));
                //2003.05.08 E.Takase Add↑
                //2003.05.08 E.Takase Add コメント↓
                //sBuf = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM1).ToDouble());
                //2003.05.08 E.Takase Add コメント↑
                Lab_KIKA[iContCnt]->Caption = sBuf;
                switch(AnsiString(pORDATA[iContCnt].KIKA_KIND).ToIntDef(0))
                {
                case 1:
                	//2003.05.08 E.Takase Add↓
                	Lab_UPKIKA[iContCnt]->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM2),0.0));
                	Lab_LOKIKA[iContCnt]->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM3),0.0));
					if(Form1->ConvDoubleDefD(Lab_UPKIKA[iContCnt]->Caption,0.0) >=0) {
                    	Lab_UPKIKA[iContCnt]->Caption = "+"+Lab_UPKIKA[iContCnt]->Caption;
                    }
					if(Form1->ConvDoubleDefD(Lab_LOKIKA[iContCnt]->Caption,0.0) >=0) {
                    	Lab_LOKIKA[iContCnt]->Caption = "+"+Lab_LOKIKA[iContCnt]->Caption;
                    }
                	//2003.05.08 E.Takase Add↑
                	//2003.05.08 E.Takase Add コメント↓
                	//Lab_UPKIKA[iContCnt]->Caption = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM2).ToDouble());
                	//Lab_LOKIKA[iContCnt]->Caption = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM3).ToDouble());
					//if(Lab_UPKIKA[iContCnt]->Caption.ToDouble() >=0) Lab_UPKIKA[iContCnt]->Caption = "+"+Lab_UPKIKA[iContCnt]->Caption;
					//if(Lab_LOKIKA[iContCnt]->Caption.ToDouble() >=0) Lab_LOKIKA[iContCnt]->Caption = "+"+Lab_LOKIKA[iContCnt]->Caption;
                    //2003.05.08 E.Takase Add コメント↑
                    break;
                case 2:
                    //2003.05.08 E.Takase Add↓
                    Lab_UPKIKA[iContCnt]->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM2),0.0));
                    Lab_LOKIKA[iContCnt]->Caption ="";
					if(Form1->ConvDoubleDefD(Lab_UPKIKA[iContCnt]->Caption,0.0) >=0) {
                    	Lab_UPKIKA[iContCnt]->Caption = "+"+Lab_UPKIKA[iContCnt]->Caption;
                    }
                	//2003.05.08 E.Takase Add↑
                	//2003.05.08 E.Takase Add コメント↓
                    //Lab_UPKIKA[iContCnt]->Caption = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM2).ToDouble());
                    //Lab_LOKIKA[iContCnt]->Caption ="";
					//if(Lab_UPKIKA[iContCnt]->Caption.ToDouble() >=0) Lab_UPKIKA[iContCnt]->Caption = "+"+Lab_UPKIKA[iContCnt]->Caption;
                    //2003.05.08 E.Takase Add コメント↑
                    break;
                case 3:
                    //2003.05.08 E.Takase Add↓
                    Lab_UPKIKA[iContCnt]->Caption = "";
                    Lab_LOKIKA[iContCnt]->Caption = FormatFloat(sDeci1,Form1->ConvDoubleDefD(AnsiString(pORDATA[iContCnt].KIKA_NUM3),0.0));
					if(Form1->ConvDoubleDefD(Lab_LOKIKA[iContCnt]->Caption,0.0) >=0) {
                    	Lab_LOKIKA[iContCnt]->Caption = "+"+Lab_LOKIKA[iContCnt]->Caption;
                    }
                	//2003.05.08 E.Takase Add↑
                	//2003.05.08 E.Takase Add コメント↓
                    //Lab_UPKIKA[iContCnt]->Caption = "";
                    //Lab_LOKIKA[iContCnt]->Caption = FormatFloat(sDeci1,AnsiString(pORDATA[iContCnt].KIKA_NUM3).ToDouble());
					//if(Lab_LOKIKA[iContCnt]->Caption.ToDouble() >=0) Lab_LOKIKA[iContCnt]->Caption = "+"+Lab_LOKIKA[iContCnt]->Caption;
                    //2003.05.08 E.Takase Add コメント↑
                    break;
                 default:
                    break;
                }
                if(Lab_UPKIKA[iContCnt]->Width >= Lab_LOKIKA[iContCnt]->Width)
                {
                    Lab_UPKIKA[iContCnt]->Left =
                        Pnl_InsName[iContCnt]->Width - Lab_UPKIKA[iContCnt]->Width -2;
                    Lab_LOKIKA[iContCnt]->Left = Lab_UPKIKA[iContCnt]->Left;
                }
                else
                {
                    Lab_LOKIKA[iContCnt]->Left =
                        Pnl_InsName[iContCnt]->Width - Lab_LOKIKA[iContCnt]->Width -2;
                    Lab_UPKIKA[iContCnt]->Left = Lab_LOKIKA[iContCnt]->Left;
                }
                Lab_KIKA[iContCnt]->Left =
                    Lab_UPKIKA[iContCnt]->Left-Lab_KIKA[iContCnt]->Width-2;
                break;
            case 3:
                Lab_KIKA[iContCnt]->Caption = pORDATA[iContCnt].KIKA_STR;
                Lab_UPKIKA[iContCnt]->Caption ="";
                Lab_LOKIKA[iContCnt]->Caption ="";
                Lab_KIKA[iContCnt]->Left =
                Pnl_InsName[iContCnt]->Width-Lab_KIKA[iContCnt]->Width-2;
				Lab_KIKA[iContCnt]->Visible = true;
                Lab_UPKIKA[iContCnt]->Visible = false;
                Lab_LOKIKA[iContCnt]->Visible = false;
                break;
            default:
                break;
            }
//グリッドの拡大
            iContCnt++;
        }
//機器名称の表示
        sBuf = IntToStr(iPnl_InsKikiNameCnt);
        Pnl_InsKikiName[iPnl_InsKikiNameCnt] = new TPanel(SBx_Left_SYUKA);
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Parent = SBx_Left_SYUKA;
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Name = "Pnl_InsKikiName" + AnsiString::StringOfChar('0', 4-sBuf.Length()) + sBuf;
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Caption = "";
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Left = Pnl_OrgKikiName->Left;
        if(iPnl_InsKikiNameCnt == 0 )
        {
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Top = Pnl_SubBase[0]->Top;
        }
        else
        {
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Top = Pnl_InsKikiName[iPnl_InsKikiNameCnt-1]->Top+Pnl_InsKikiName[iPnl_InsKikiNameCnt-1]->Height;
        }
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Width = Pnl_OrgKikiName->Width;
        Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Height = nKIKIPNL_HIGHT;
        switch(AnsiString(pORDATA[iContCnt-1].KIKI_NO).ToIntDef(0))
        {
        case 1:
            //マイクロメータ
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)MICROMETER_COLOR;
            break;
        case 2:
            //ノギス
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)NOGISU_COLOR;
            break;
        case 3:
            //マイクロメータ／天秤
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)MICROTENBIN_COLOR;
            break;
        case 4:
            //天秤
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)TENBIN_COLOR;
            break;
        case 5:
            //材料試験機
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)ZAIRYOU_COLOR;
            break;
        case 6:
            //投影機
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)TOUEIKI_COLOR;
            break;
        case 7:
            //顕微鏡
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)KENBIKYO_COLOR;
            break;
        case 8:
            //面粗度計
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)MENARAKEI_COLOR;
            break;
        case 9:
            //シュア硬度形C型
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)KOUDOKEI_C_COLOR;
            break;
        case 10:
            //シュア硬度形D型
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)KOUDOKEI_D_COLOR;
            break;
        case 11:
            //抵抗率測定器
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)TEIKOU_COLOR;
            break;
        case 12:
            //リード線取付抵抗測定機
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)READTEIKOU_COLOR;
            break;
        case 99:
        default:
            //その他
            Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Color = (TColor)ETC_COLOR;
            break;
        }
        Lab_KIKI_NM[iPnl_InsKikiNameCnt] = new TLabel(Pnl_InsKikiName[iPnl_InsKikiNameCnt]);
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Name = "Lab_KIKI_NM" + AnsiString::StringOfChar('0', 4-sBuf.Length()) + sBuf;
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Caption = pORDATA[iContCnt-1].KIKI_NM;
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Parent = Pnl_InsKikiName[iPnl_InsKikiNameCnt];
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Left = LabBASEKIKI_NM->Left;
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Width = LabBASEKIKI_NM->Width;
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->WordWrap = True;
        Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Top =
            (Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Height-Lab_KIKI_NM[iPnl_InsKikiNameCnt]->Height)/2;
//	外観検査なら機器名称の表示は不要なのでコントロールを見えなくします
        if(AnsiString(pORDATA[iContCnt-1].KOMK_NO).ToIntDef(0) == 1)
		{
			Pnl_InsKikiName[iPnl_InsKikiNameCnt]->Visible = false;
		}
        iPnl_InsKikiNameCnt ++;
    }
//セルと項目パネルのHEIGHTの調整のためDUMMYパネルを置きます
	if(iContCnt > 0 )
	{
		Pnl_DUMMY->Parent = SBx_Left_SYUKA;
		Pnl_DUMMY->Top = Pnl_SubBase[iContCnt - 1]->Top+Pnl_SubBase[iContCnt - 1]->Height;
	    Pnl_DUMMY->Height = 39;		//グリッドにスクロールバーが出現/未出現で高さを変えたいが、手段が無いため中間の値をとる
	    Pnl_DUMMY->Width = 1;
		Pnl_DUMMY->Left = 0;
	    Pnl_DUMMY->Ctl3D = false;
    	Pnl_DUMMY->BevelInner = bvNone;
	    Pnl_DUMMY->BevelOuter = bvRaised;
    	Pnl_DUMMY->BorderStyle = bsNone;
	    Pnl_DUMMY->BorderWidth = 0;
		Pnl_DUMMY->Visible = true;
    }
	SGr_vSOKU_SYUKA->Refresh();
//出荷検査項目総数
	Panel33->Caption = AnsiString("出　荷　検　査　（") + iContCnt + AnsiString("項）");
//セル情報メモリ設定(測定実績明細データ）
	// メモリの開放
	if( hCELLINFO_SOKU_SYUKA ){
        GlobalUnlock( hCELLINFO_SOKU_SYUKA );
        GlobalFree( hCELLINFO_SOKU_SYUKA );
    }
    hCELLINFO_SOKU_SYUKA = NULL;
    // メモリの確保
	SBx_Left_SYUKA->Refresh();
	SGr_tSOKU->Refresh();
	SGr_vSOKU_SYUKA->Refresh();
    hCELLINFO_SOKU_SYUKA = GlobalAlloc( GHND, sizeof(struct CELLINFO_DATA) * ((SGr_vSOKU_SYUKA->ColCount+1) * SGr_vSOKU_SYUKA->RowCount));
    if( hCELLINFO_SOKU_SYUKA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pCELLINFO_SOKU_SYUKA = (struct CELLINFO_DATA *)GlobalLock(hCELLINFO_SOKU_SYUKA);
    if( hCELLINFO_SOKU_SYUKA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }


//製品規格マスター(測定実績データ用）
	// メモリの開放
	if( hSOKU_KSD01DATA ){
        GlobalUnlock( hSOKU_KSD01DATA );
        GlobalFree( hSOKU_KSD01DATA );
    }
    hSOKU_KSD01DATA = NULL;
    // メモリの確保
    hSOKU_KSD01DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * ((SGr_vSOKU_SYUKA->ColCount+1)));
    if( hSOKU_KSD01DATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pSOKU_KSD01DATA = (struct KSD01_DATA *)GlobalLock(hSOKU_KSD01DATA);
    if( hSOKU_KSD01DATA == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }

//ディフォルトのKSM01を各ロットに割り当て
	for(iCol = 0 ; iCol < SGr_tSOKU_SYUKA->ColCount ; iCol++)
	{
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN,pKSM01_DATA.DTKSHIN);
		strcpy(pSOKU_KSD01DATA[iCol].HINBAN,pKSM01_DATA.HINBAN);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSCOD,pKSM01_DATA.DTKSCOD);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSNAM,pKSM01_DATA.DTKSNAM);
		strcpy(pSOKU_KSD01DATA[iCol].ZISNAM,pKSM01_DATA.ZISNAM);
		strcpy(pSOKU_KSD01DATA[iCol].HINMEI,pKSM01_DATA.HINMEI);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN1_SZ,pKSM01_DATA.DTKSHIN1_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN2_SZ,pKSM01_DATA.DTKSHIN2_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN3_SZ,pKSM01_DATA.DTKSHIN3_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN4_SZ,pKSM01_DATA.DTKSHIN4_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN5_SZ,pKSM01_DATA.DTKSHIN5_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].DTKSHIN6_SZ,pKSM01_DATA.DTKSHIN6_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].LOT_LINK_SZ,pKSM01_DATA.LOT_LINK_SZ);
		strcpy(pSOKU_KSD01DATA[iCol].SOKUTEI_NUM,pKSM01_DATA.SOKUTEI_NUM);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE1,pKSM01_DATA.OUT_TITLE1);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE2,pKSM01_DATA.OUT_TITLE2);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE3,pKSM01_DATA.OUT_TITLE3);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE4,pKSM01_DATA.OUT_TITLE4);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE5,pKSM01_DATA.OUT_TITLE5);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE6,pKSM01_DATA.OUT_TITLE6);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE7,pKSM01_DATA.OUT_TITLE7);
		strcpy(pSOKU_KSD01DATA[iCol].OUT_TITLE8,pKSM01_DATA.OUT_TITLE8);
		strcpy(pSOKU_KSD01DATA[iCol].X_OUT,pKSM01_DATA.X_OUT);
		strcpy(pSOKU_KSD01DATA[iCol].MEMO,pKSM01_DATA.MEMO);
		strcpy(pSOKU_KSD01DATA[iCol].ADDYMD,pKSM01_DATA.ADDYMD);
		strcpy(pSOKU_KSD01DATA[iCol].ADDTIM,pKSM01_DATA.ADDTIM);
		strcpy(pSOKU_KSD01DATA[iCol].UPDYMD,pKSM01_DATA.UPDYMD);
		strcpy(pSOKU_KSD01DATA[iCol].UPDTIM,pKSM01_DATA.UPDTIM);
		strcpy(pSOKU_KSD01DATA[iCol].UPDCHR,pKSM01_DATA.UPDCHR);
		strcpy(pSOKU_KSD01DATA[iCol].UPDCNT,pKSM01_DATA.UPDCNT);
		strcpy(pSOKU_KSD01DATA[iCol].UPDNAME , pKSM01_DATA.UPDNAME);
        pSOKU_KSD01DATA[iCol].UPD_FLG = false;
        pSOKU_KSD01DATA[iCol].SAVE_FLG = true;
    }

//未使用のグリッド（検査しない）のバックカラーを灰色にする
//出荷検査
    nDRAW_GRID = 1;
    //int nKENSAKU_KEY,nCOMP_KEY;
//出荷検査のグリッドをすべて灰色にする
	for( i1 = 0; i1 < SGr_vSOKU_SYUKA->ColCount ; i1++)
    {
		for(i2= 0; i2 <  SGr_vSOKU_SYUKA->RowCount ; i2++)
        {
        	strcpy(pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].RESULT,"");
        	strcpy(pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].DISP_RESULT,"");
        	pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].JUDGE = 2;
		//灰色表示を実現する為項目NOの初期値は0としています。
        	strcpy(pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].KOMK_NO , "-999");
            pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].INS_ON = false;
        }
    }
//製品規格明細の各セル情報へのコピー
	if(hCELLINFO_SOKU_SYUKA)
	{
		for(i1=0;i1<(SGr_vSOKU_SYUKA->ColCount) ;i1++)
		{
			dMAX = 0;
			dMIN = 0;
    		i4 = 1;
			for(i2=0 ; i2 < iOrCount ; i2++)
			{
    			GetKIKAKU(i2, &dMAX, &dMIN);
				for(i3=0;i3 < AnsiString(pORDATA[i2].SOKU_SU).ToIntDef(0);i3++)
				{
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].DTKSHIN 		, pORDATA[ i2 ].DTKSHIN);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].LOTNO 		, SGr_tSOKU->Cells[i1][0].c_str());
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].HINBAN 		, SGr_tSOKU->Cells[i1][1].c_str());
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UNQ_NO 		, pORDATA[ i2 ].UNQ_NO);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].ORDER_NO		, pORDATA[ i2 ].ORDER_NO);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].SKB_NO 		, pORDATA[ i2 ].SKB_NO);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].HINBAN_SK	, pORDATA[ i2 ].HINBAN_SK);
 					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_NO 		, "-999");
 					pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].INS_ON = false;
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_NM 		, pORDATA[ i2 ].KOMK_NM);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_ENG		, pORDATA[ i2 ].KOMK_ENG);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_SUB		, pORDATA[ i2 ].KOMK_SUB);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_SUB_ENG , pORDATA[ i2 ].KOMK_SUB_ENG);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKI_NO 		, pORDATA[ i2 ].KIKI_NO);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKI_NM 		, pORDATA[ i2 ].KIKI_NM);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].TANI    		, pORDATA[ i2 ].TANI);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_TYPE	, pORDATA[ i2 ].KIKA_TYPE);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_KIND	, pORDATA[ i2 ].KIKA_KIND);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_DECI	, pORDATA[ i2 ].KIKA_DECI);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_NUM1	, pORDATA[ i2 ].KIKA_NUM1);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_NUM2	, pORDATA[ i2 ].KIKA_NUM2);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_NUM3	, pORDATA[ i2 ].KIKA_NUM3);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_STR		, pORDATA[ i2 ].KIKA_STR);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_SUB1	, pORDATA[ i2 ].KIKA_SUB1);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_SUB2	, pORDATA[ i2 ].KIKA_SUB2);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_SUB3	, pORDATA[ i2 ].KIKA_SUB3);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].SOKU_SU 		, pORDATA[ i2 ].SOKU_SU);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].SOKU_FLG		, pORDATA[ i2 ].SOKU_FLG);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].TOKU_FLG		, pORDATA[ i2 ].TOKU_FLG);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KIKA_PRT		, pORDATA[ i2 ].KIKA_PRT);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].VALUE_TYPE	, pORDATA[ i2 ].VALUE_TYPE);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].VALUE_DECI	, pORDATA[ i2 ].VALUE_DECI);
				// 測定日
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].SKTYMD,FormatDateTime("yyyymmdd",Date()).c_str());
				// 測定日（印刷用）
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].DISP_SKTYMD,FormatDateTime("yyyymmdd",Date()).c_str());
				// 登録日
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].ADDYMD,pSOKU_KSD01DATA[i1].ADDYMD);
				// 登録時間
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].ADDTIM,pSOKU_KSD01DATA[i1].ADDTIM);
				// 変更日
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDYMD,pSOKU_KSD01DATA[i1].UPDYMD);
				// 変更時間
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDTIM,pSOKU_KSD01DATA[i1].UPDTIM);
				// 更新回数
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDCNT,pSOKU_KSD01DATA[i1].UPDCNT);
				//製品規格マスターを使いましょう
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDCHR,pSOKU_KSD01DATA[i1].UPDCHR);
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].UPDNAME , pSOKU_KSD01DATA[i1].UPDNAME);
				//規格
                    pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].MAX = dMAX ;
                    pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].MIN = dMIN ;
                    pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].GMAX = dMAX ;
                    pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].GMIN = dMIN ;
					//外観検査は初期化時は良を代入
					if(AnsiString(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].KOMK_NO).ToIntDef(0) == 1 )
					{
                        // 2003/10/06 A.Tamura 海老様の要望により「外観＝良（デフォルト値）」を取りやめました。
                    	//strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].RESULT,"0");
                    	//strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].DISP_RESULT,"0");
					}
					i4++;
				}
			}
    	}
//出荷検査予定の項目の白抜き
    	for( i4 = 0; i4 < SGr_vSOKU_SYUKA->ColCount ; i4++)
        {
    	    for(i1 = 0; i1 < iSYUKA_KOMKCNT;i1++)
    		{
                nDRAW_GRID = 1;
                for( i2 = 0; i2 < iOrCount ; i2++)
                {
//ORテーブルの現在の機器NOと項目NOを抽出
                    if((AnsiString(pSYUKA_DATA[i1].KIKI_NO).ToIntDef(0) == AnsiString(pORDATA[i2].KIKI_NO).ToIntDef(0))
                    && (AnsiString(pSYUKA_DATA[i1].KOMK_NM).Trim() 		== AnsiString(pORDATA[i2].KOMK_NM).Trim())
                    && (AnsiString(pSYUKA_DATA[i1].KOMK_SUB).Trim() 	== AnsiString(pORDATA[i2].KOMK_SUB).Trim())
                    && (AnsiString(pSYUKA_DATA[i1].TANI).Trim() 		== AnsiString(pORDATA[i2].TANI).Trim()))
                    {
                        for(i3 = 0;i3 < AnsiString(pSYUKA_DATA[i1].SOKU_SU).ToIntDef(0);i3++)
                        {
                            strcpy(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].RESULT,"");
                            strcpy(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].DISP_RESULT,"");
                            strcpy(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].KOMK_NO,pSYUKA_DATA[i1].KOMK_NO);
                            pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].INS_ON = true;
                            if(AnsiString(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].KOMK_NO).ToIntDef(0) == 1 )
					        {
                        		// 2003/10/06 A.Tamura 海老様の要望により「外観＝良（デフォルト値）」を取りやめました。
                    	        //strcpy(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].RESULT,"0");
                    	        //strcpy(pCELLINFO_SOKU_SYUKA[i4*SGr_vSOKU_SYUKA->RowCount+nDRAW_GRID+i3].DISP_RESULT,"0");
					        }
                        }
		    				//i2 = iOrCount+1;
			    			//break;
                        break;
                    }
                    nDRAW_GRID += AnsiString(pORDATA[ i2 ].SOKU_SU).ToIntDef(0);
                }
		    }
    	}
		Set_SYUKAJISSEKI();
		Get_KSD91_SHUKA();						//備考欄表示

//製品規格明細の各セル情報へのコピー
		for(i1=0;i1<(SGr_vSOKU_SYUKA->ColCount) ;i1++)
		{
    		i4 = 1;
			for(i2=0 ; i2 < iOrCount ; i2++)
			{
				for(i3=0;i3 < AnsiString(pORDATA[i2].SOKU_SU).ToIntDef(0);i3++)
				{
					strcpy(pCELLINFO_SOKU_SYUKA[(i1 * SGr_vSOKU_SYUKA->RowCount) + i4].SOKU_SU 		, pORDATA[ i2 ].SOKU_SU);
					i4++;
				}
			}
    	}
//出荷検査の表示（4回目）
		for( i1 = 0; i1 < SGr_vSOKU_SYUKA->ColCount ; i1++)
    	{
			for(i2= 0; i2 <  SGr_vSOKU_SYUKA->RowCount ; i2++)
        	{
	            SGr_vSOKU_SYUKA->Cells[i1][i2]= pCELLINFO_SOKU_SYUKA[i1*SGr_vSOKU_SYUKA->RowCount+i2].RESULT;
	        }
    	}
/////////////////////////////
	    // メモリの開放
    	if( hSOKU_KSD01_DATA ){
    		GlobalUnlock( hSOKU_KSD01_DATA );
	        GlobalFree( hSOKU_KSD01_DATA );
    	}
        hSOKU_KSD01_DATA = NULL;
	    // メモリの確保
    	hSOKU_KSD01_DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * (SGr_vSOKU_SYUKA->ColCount+1));
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
    	SET_KSD01();							//測定実績等の取り込み
////////////////////////////////
	}
//出荷データ中で履歴データが有る物の表示

 	if(bNowRIRE == true)
	{
		int iRowCount,iColCount;
		SGr_tRIRE->Refresh();
        SGr_vRIRE_SYUKA->Refresh();
		iRowCount = SGr_vRIRE_SYUKA->RowCount;
		iColCount = SGr_vRIRE_SYUKA->ColCount;
		// メモリの開放
		if( hCELLINFO_RIRE_SYUKA ){
        	GlobalUnlock( hCELLINFO_RIRE_SYUKA );
        	GlobalFree( hCELLINFO_RIRE_SYUKA );
    	}
        hCELLINFO_RIRE_SYUKA = NULL;
    	// メモリの確保
    	hCELLINFO_RIRE_SYUKA = GlobalAlloc( GHND, sizeof(struct CELLINFO_DATA) * ((iColCount+1) * iRowCount));
    	if( hCELLINFO_RIRE_SYUKA == NULL ){
        	SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル01)";
        	SBr1->Update();
        	Beep();
        	return;
    	}
    	pCELLINFO_RIRE_SYUKA = (struct CELLINFO_DATA *)GlobalLock(hCELLINFO_RIRE_SYUKA);
    	if( hCELLINFO_RIRE_SYUKA == NULL ){
        	SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル02)";
        	SBr1->Update();
        	Beep();
        	return;
    	}

        if(hCELLINFO_RIRE_SYUKA)
		{

            // スレッド出荷履歴読み出し
        	GET_RIRE_SYUKA();

		}
	}
	else
	{
		SGr_tRIRE->Cells[0][0]="";
	}
	bLOTCHANGE = false;
    // 素材の表示
	SOZAI_PROCESS();

    // 検索終了フラグ
    Form1->bNowF7 = false;
    //------------------------

    if(bLOT_LINK == false)
	{
        // ロット割り当て画面　呼び出し
		OldMIDASI->Visible = false;
		NewMIDASI->Visible = false;
        OldMIDASI->Parent = SBx_Left_SYUKA;
        NewMIDASI->Parent = SBx_Left_SYUKA;

        // 分割票入力
		if(SGr_tSOKU->Cells[0][0].Trim().Length() != 0
		|| SGr_tRIRE->Cells[0][0].Trim().Length() != 0)
        {
	        Form8->ShowModal();
            // k.k 2003.05.17 DELETE ----
            // 素材の表示
    	    SOZAI_PROCESS();
            bNowLotF7 = false;
	        bLOT_LINK = false;

            // 検索終了フラグ
            Form1->bNowF7 = false;
            //---------------------------
        }
	}

//最初のグリッドセット
    if(hCELLINFO_SOKU_SYUKA && SGr_vSOKU_SYUKA->RowCount > 1 )
    {
        // 2003/10/14 A.Tamura 外観はデフォルト空となるため、最初のカーソルは、Grid右下の一番上固定となります。
   		Form1->SGr_vSOKU_SYUKA->Row =1;
	    Form1->SGr_vSOKU_SYUKA->Col =0;
       	Form1->SGr_vSOKU_SYUKA->SetFocus();
        AllGRID_SelectCell(SGr_vSOKU_SYUKA,SGr_vSOKU_SYUKA->Col,SGr_vSOKU_SYUKA->Row,true);
    }
    else if(hCELLINFO_SOKU_SOZAI && SGr_vSOKU_SOZAI->RowCount > 1)
    {
        Form1->SGr_vSOKU_SOZAI->Col =0;
        Form1->SGr_vSOKU_SOZAI->Row =1;
        Form1->SGr_vSOKU_SOZAI->SetFocus();
        AllGRID_SelectCell(SGr_vSOKU_SOZAI,SGr_vSOKU_SOZAI->Col,SGr_vSOKU_SOZAI->Row,true);
    }

}
//2003.05.15 M.HIRAI
//---------------------------------------------------------------------------
//ORデータの入れ替え
//---------------------------------------------------------------------------
void __fastcall TForm1::Replace_ORData(int x, int y)
{
	// dTEMPORDATA[0] <- dORDATA[x]
    ORData_To_Tmp(x);
	// dORDATA[x] <- dORDATA[y]
    ORData_To_ORData(x, y);
    // dORDATA[y] <- dTEMPORDATA[0]
    Tmp_To_ORData(y);
}
void __fastcall TForm1::ORData_To_Tmp(int x)
{
    // dTEMPORDATA[0] <- dORDATA[x]
    strcpy(pTEMPORDATA[ 0 ].DTKSHIN	    , pORDATA[ x ].DTKSHIN);
    strcpy(pTEMPORDATA[ 0 ].UNQ_NO 	    , pORDATA[ x ].UNQ_NO);
	strcpy(pTEMPORDATA[ 0 ].ORDER_NO 	, pORDATA[ x ].ORDER_NO);
	strcpy(pTEMPORDATA[ 0 ].SKB_NO 	    , pORDATA[ x ].SKB_NO);
	strcpy(pTEMPORDATA[ 0 ].HINBAN_SK 	, pORDATA[ x ].HINBAN_SK);
	strcpy(pTEMPORDATA[ 0 ].KOMK_NO 	, pORDATA[ x ].KOMK_NO);
	strcpy(pTEMPORDATA[ 0 ].KOMK_NM 	, pORDATA[ x ].KOMK_NM);
	strcpy(pTEMPORDATA[ 0 ].KOMK_ENG 	, pORDATA[ x ].KOMK_ENG);
	strcpy(pTEMPORDATA[ 0 ].KOMK_SUB 	, pORDATA[ x ].KOMK_SUB);
	strcpy(pTEMPORDATA[ 0 ].KOMK_SUB_ENG, pORDATA[ x ].KOMK_SUB_ENG);
	strcpy(pTEMPORDATA[ 0 ].KIKI_NO 	, pORDATA[ x ].KIKI_NO);
	strcpy(pTEMPORDATA[ 0 ].KIKI_NM 	, pORDATA[ x ].KIKI_NM);
	strcpy(pTEMPORDATA[ 0 ].TANI 		, pORDATA[ x ].TANI);
	strcpy(pTEMPORDATA[ 0 ].KIKA_TYPE 	, pORDATA[ x ].KIKA_TYPE);
   	strcpy(pTEMPORDATA[ 0 ].KIKA_KIND 	, pORDATA[ x ].KIKA_KIND);
	strcpy(pTEMPORDATA[ 0 ].KIKA_DECI 	, pORDATA[ x ].KIKA_DECI);
	strcpy(pTEMPORDATA[ 0 ].KIKA_NUM1 	, pORDATA[ x ].KIKA_NUM1);
	strcpy(pTEMPORDATA[ 0 ].KIKA_NUM2 	, pORDATA[ x ].KIKA_NUM2);
	strcpy(pTEMPORDATA[ 0 ].KIKA_NUM3 	, pORDATA[ x ].KIKA_NUM3);
	strcpy(pTEMPORDATA[ 0 ].KIKA_STR 	, pORDATA[ x ].KIKA_STR);
	strcpy(pTEMPORDATA[ 0 ].KIKA_SUB1 	, pORDATA[ x ].KIKA_SUB1);
	strcpy(pTEMPORDATA[ 0 ].KIKA_SUB2 	, pORDATA[ x ].KIKA_SUB2);
	strcpy(pTEMPORDATA[ 0 ].KIKA_SUB3 	, pORDATA[ x ].KIKA_SUB3);
	strcpy(pTEMPORDATA[ 0 ].SOKU_SU 	, pORDATA[ x ].SOKU_SU);
	strcpy(pTEMPORDATA[ 0 ].SOKU_FLG 	, pORDATA[ x ].SOKU_FLG);
	strcpy(pTEMPORDATA[ 0 ].TOKU_FLG 	, pORDATA[ x ].TOKU_FLG);
	strcpy(pTEMPORDATA[ 0 ].KIKA_PRT 	, pORDATA[ x ].KIKA_PRT);
   	strcpy(pTEMPORDATA[ 0 ].VALUE_TYPE 	, pORDATA[ x ].VALUE_TYPE);
  	strcpy(pTEMPORDATA[ 0 ].VALUE_DECI 	, pORDATA[ x ].VALUE_DECI);
}
void __fastcall TForm1::ORData_To_ORData(int x, int y)
{
    // dORDATA[x] <- dORDATA[y]
  	strcpy(pORDATA[ x ].DTKSHIN	        , pORDATA[ y ].DTKSHIN);
	strcpy(pORDATA[ x ].UNQ_NO 	        , pORDATA[ y ].UNQ_NO);
	strcpy(pORDATA[ x ].ORDER_NO 	    , pORDATA[ y ].ORDER_NO);
	strcpy(pORDATA[ x ].SKB_NO 	        , pORDATA[ y ].SKB_NO);
	strcpy(pORDATA[ x ].HINBAN_SK 	    , pORDATA[ y ].HINBAN_SK);
	strcpy(pORDATA[ x ].KOMK_NO 	    , pORDATA[ y ].KOMK_NO);
	strcpy(pORDATA[ x ].KOMK_NM 	    , pORDATA[ y ].KOMK_NM);
	strcpy(pORDATA[ x ].KOMK_ENG 	    , pORDATA[ y ].KOMK_ENG);
	strcpy(pORDATA[ x ].KOMK_SUB 	    , pORDATA[ y ].KOMK_SUB);
	strcpy(pORDATA[ x ].KOMK_SUB_ENG    , pORDATA[ y ].KOMK_SUB_ENG);
	strcpy(pORDATA[ x ].KIKI_NO 	    , pORDATA[ y ].KIKI_NO);
	strcpy(pORDATA[ x ].KIKI_NM 	    , pORDATA[ y ].KIKI_NM);
	strcpy(pORDATA[ x ].TANI 		    , pORDATA[ y ].TANI);
	strcpy(pORDATA[ x ].KIKA_TYPE 	    , pORDATA[ y ].KIKA_TYPE);
	strcpy(pORDATA[ x ].KIKA_KIND 	    , pORDATA[ y ].KIKA_KIND);
	strcpy(pORDATA[ x ].KIKA_DECI 	    , pORDATA[ y ].KIKA_DECI);
	strcpy(pORDATA[ x ].KIKA_NUM1 	    , pORDATA[ y ].KIKA_NUM1);
	strcpy(pORDATA[ x ].KIKA_NUM2 	    , pORDATA[ y ].KIKA_NUM2);
	strcpy(pORDATA[ x ].KIKA_NUM3 	    , pORDATA[ y ].KIKA_NUM3);
	strcpy(pORDATA[ x ].KIKA_STR 	    , pORDATA[ y ].KIKA_STR);
   	strcpy(pORDATA[ x ].KIKA_SUB1 	    , pORDATA[ y ].KIKA_SUB1);
  	strcpy(pORDATA[ x ].KIKA_SUB2 	    , pORDATA[ y ].KIKA_SUB2);
 	strcpy(pORDATA[ x ].KIKA_SUB3 	    , pORDATA[ y ].KIKA_SUB3);
	strcpy(pORDATA[ x ].SOKU_SU 	    , pORDATA[ y ].SOKU_SU);
	strcpy(pORDATA[ x ].SOKU_FLG 	    , pORDATA[ y ].SOKU_FLG);
	strcpy(pORDATA[ x ].TOKU_FLG 	    , pORDATA[ y ].TOKU_FLG);
	strcpy(pORDATA[ x ].KIKA_PRT 	    , pORDATA[ y ].KIKA_PRT);
	strcpy(pORDATA[ x ].VALUE_TYPE 	    , pORDATA[ y ].VALUE_TYPE);
	strcpy(pORDATA[ x ].VALUE_DECI 	    , pORDATA[ y ].VALUE_DECI);
}
void __fastcall TForm1::Tmp_To_ORData(int x)
{
    // dORDATA[x] <- dTEMPORDATA[0]
	strcpy(pORDATA[ x ].DTKSHIN		    , pTEMPORDATA[ 0 ].DTKSHIN);
	strcpy(pORDATA[ x ].UNQ_NO 		    , pTEMPORDATA[ 0 ].UNQ_NO);
	strcpy(pORDATA[ x ].ORDER_NO 	    , pTEMPORDATA[ 0 ].ORDER_NO);
	strcpy(pORDATA[ x ].SKB_NO 		    , pTEMPORDATA[ 0 ].SKB_NO);
	strcpy(pORDATA[ x ].HINBAN_SK 	    , pTEMPORDATA[ 0 ].HINBAN_SK);
	strcpy(pORDATA[ x ].KOMK_NO 		, pTEMPORDATA[ 0 ].KOMK_NO);
	strcpy(pORDATA[ x ].KOMK_NM 		, pTEMPORDATA[ 0 ].KOMK_NM);
   	strcpy(pORDATA[ x ].KOMK_ENG 	    , pTEMPORDATA[ 0 ].KOMK_ENG);
  	strcpy(pORDATA[ x ].KOMK_SUB 	    , pTEMPORDATA[ 0 ].KOMK_SUB);
 	strcpy(pORDATA[ x ].KOMK_SUB_ENG    , pTEMPORDATA[ 0 ].KOMK_SUB_ENG);
	strcpy(pORDATA[ x ].KIKI_NO 		, pTEMPORDATA[ 0 ].KIKI_NO);
	strcpy(pORDATA[ x ].KIKI_NM 		, pTEMPORDATA[ 0 ].KIKI_NM);
	strcpy(pORDATA[ x ].TANI 		    , pTEMPORDATA[ 0 ].TANI);
	strcpy(pORDATA[ x ].KIKA_TYPE 	    , pTEMPORDATA[ 0 ].KIKA_TYPE);
	strcpy(pORDATA[ x ].KIKA_KIND 	    , pTEMPORDATA[ 0 ].KIKA_KIND);
	strcpy(pORDATA[ x ].KIKA_DECI 	    , pTEMPORDATA[ 0 ].KIKA_DECI);
	strcpy(pORDATA[ x ].KIKA_NUM1 	    , pTEMPORDATA[ 0 ].KIKA_NUM1);
	strcpy(pORDATA[ x ].KIKA_NUM2 	    , pTEMPORDATA[ 0 ].KIKA_NUM2);
	strcpy(pORDATA[ x ].KIKA_NUM3 	    , pTEMPORDATA[ 0 ].KIKA_NUM3);
	strcpy(pORDATA[ x ].KIKA_STR 	    , pTEMPORDATA[ 0 ].KIKA_STR);
   	strcpy(pORDATA[ x ].KIKA_SUB1 	    , pTEMPORDATA[ 0 ].KIKA_SUB1);
	strcpy(pORDATA[ x ].KIKA_SUB2 	    , pTEMPORDATA[ 0 ].KIKA_SUB2);
	strcpy(pORDATA[ x ].KIKA_SUB3 	    , pTEMPORDATA[ 0 ].KIKA_SUB3);
	strcpy(pORDATA[ x ].SOKU_SU 		, pTEMPORDATA[ 0 ].SOKU_SU);
	strcpy(pORDATA[ x ].SOKU_FLG 	    , pTEMPORDATA[ 0 ].SOKU_FLG);
	strcpy(pORDATA[ x ].TOKU_FLG 	    , pTEMPORDATA[ 0 ].TOKU_FLG);
	strcpy(pORDATA[ x ].KIKA_PRT 	    , pTEMPORDATA[ 0 ].KIKA_PRT);
	strcpy(pORDATA[ x ].VALUE_TYPE 	    , pTEMPORDATA[ 0 ].VALUE_TYPE);
	strcpy(pORDATA[ x ].VALUE_DECI 	    , pTEMPORDATA[ 0 ].VALUE_DECI);
}
//---------------------------------------------------------------------------
//測定実績データの新規登録＆更新（対象データベースはKSD001&KSD002）
//---------------------------------------------------------------------------
bool __fastcall TForm1::Set_DB_SOKU(void)
{
    int i1,i2,i3,i4;
    int iUNQNO;
    int iKIKA_KIND;

    //セーブ時使用変数一覧
	int iRow,iCol;
	int iRowCount;
    int iSOKUSU;
	int VALUE_TYPE;
	int iKOMK_NO;
	int SOKU_VAL_SU,DISP_VAL_SU;
    int iSOKU_VAL_SU,iDISP_VAL_SU;
    int iSIJI_NSU;
    AnsiString RESULT_BUF,DISP_RESULT_BUF,sMEMO;
	double SOKU_VAL_AVE,SOKU_VAL_MAX,SOKU_VAL_MIN;
	double DISP_VAL_AVE,DISP_VAL_MAX,DISP_VAL_MIN;
	double RESULT,GOUKEI_RESULT,DISP_RESULT,DISP_GOUKEI_RESULT;
    double SOKU_MAX,SOKU_MIN;
    double DISP_MAX,DISP_MIN;
    int iRESULT,iDISP_RESULT;
    int iOK_FLG,iDISP_OK_FLG;       //新OKフラグ
	bool FIRST_FLG,DISP_FIRST_FLG;
	bool bNEW;						//新規追加フラグ
	bool bHANTEI,bDISP_HANTEI;					//前詰フラグ
	HANDLE hSetJissekiData;
	KSD01_DATA  *pSetJissekiData;

    bool bRtn;		//2003.05.08 E.Takase Add
	AnsiString sBufConv;

    AnsiString sBuf,sLot,sTempBuf;
    KSD02_DATA SetData;

    //出荷検査
    //KSD01の更新

	// メモリの開放

    if( hSetJissekiData ){
    	GlobalUnlock( hSetJissekiData );
        //20170509 Y.Onishi
        //Memory Address '00000032'時にコケる不具合を修正
        //GlobalFree( hSetJissekiData );
    }
    hSetJissekiData = NULL;

    // メモリの確保
    hSetJissekiData = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * 1);
    if( hSetJissekiData == NULL ){
    	SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル01)";
        SBr1->Update();
        Beep();
        return(false);
    }
    pSetJissekiData = (struct KSD01_DATA *)GlobalLock(hSetJissekiData);
    if( hSetJissekiData == NULL ){
    	SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル02)";
        SBr1->Update();
        Beep();
        return(false);
    }

    for(i2 = 0;i2 < SGr_vSOKU_SYUKA->ColCount;i2++)
    {
    	strcpy(pSetJissekiData[0].DTKSHIN	  ,sNowDTKSHIN.c_str());
        strcpy(pSetJissekiData[0].LOTNO		  ,SGr_tSOKU->Cells[i2][0].c_str());
        strcpy(pSetJissekiData[0].HINBAN	  ,SGr_tSOKU->Cells[i2][1].c_str());                //onishi

		strcpy(pSetJissekiData[0].LOTNO1_SZ	  ,pSOKU_KSD01_DATA[i2].LOTNO1_SZ);
		strcpy(pSetJissekiData[0].LOTNO2_SZ	  ,pSOKU_KSD01_DATA[i2].LOTNO2_SZ);
		strcpy(pSetJissekiData[0].LOTNO3_SZ	  ,pSOKU_KSD01_DATA[i2].LOTNO3_SZ);
		strcpy(pSetJissekiData[0].LOTNO4_SZ	  ,pSOKU_KSD01_DATA[i2].LOTNO4_SZ);
		strcpy(pSetJissekiData[0].LOTNO5_SZ	  ,pSOKU_KSD01_DATA[i2].LOTNO5_SZ);
		strcpy(pSetJissekiData[0].LOTNO6_SZ	  ,pSOKU_KSD01_DATA[i2].LOTNO6_SZ);

		strcpy(pSetJissekiData[0].HINBAN1_SZ  ,pSOKU_KSD01_DATA[i2].HINBAN1_SZ);
		strcpy(pSetJissekiData[0].HINBAN2_SZ  ,pSOKU_KSD01_DATA[i2].HINBAN2_SZ);
		strcpy(pSetJissekiData[0].HINBAN3_SZ  ,pSOKU_KSD01_DATA[i2].HINBAN3_SZ);
		strcpy(pSetJissekiData[0].HINBAN4_SZ  ,pSOKU_KSD01_DATA[i2].HINBAN4_SZ);
		strcpy(pSetJissekiData[0].HINBAN5_SZ  ,pSOKU_KSD01_DATA[i2].HINBAN5_SZ);
		strcpy(pSetJissekiData[0].HINBAN6_SZ  ,pSOKU_KSD01_DATA[i2].HINBAN6_SZ);

		strcpy(pSetJissekiData[0].DTKSCOD	  ,pSOKU_KSD01_DATA[i2].DTKSCOD);
		strcpy(pSetJissekiData[0].DTKSNAM	  ,pSOKU_KSD01_DATA[i2].DTKSNAM);
		strcpy(pSetJissekiData[0].ZISNAM	  ,pSOKU_KSD01_DATA[i2].ZISNAM);
		strcpy(pSetJissekiData[0].HINMEI	  ,pSOKU_KSD01_DATA[i2].HINMEI);

		strcpy(pSetJissekiData[0].DTKSHIN1_SZ ,pSOKU_KSD01_DATA[i2].DTKSHIN1_SZ);
		strcpy(pSetJissekiData[0].DTKSHIN2_SZ ,pSOKU_KSD01_DATA[i2].DTKSHIN2_SZ);
		strcpy(pSetJissekiData[0].DTKSHIN3_SZ ,pSOKU_KSD01_DATA[i2].DTKSHIN3_SZ);
		strcpy(pSetJissekiData[0].DTKSHIN4_SZ ,pSOKU_KSD01_DATA[i2].DTKSHIN4_SZ);
		strcpy(pSetJissekiData[0].DTKSHIN5_SZ ,pSOKU_KSD01_DATA[i2].DTKSHIN5_SZ);
		strcpy(pSetJissekiData[0].DTKSHIN6_SZ ,pSOKU_KSD01_DATA[i2].DTKSHIN6_SZ);

		strcpy(pSetJissekiData[0].LOT_LINK_SZ ,pSOKU_KSD01_DATA[i2].LOT_LINK_SZ);
		strcpy(pSetJissekiData[0].SOKUTEI_NUM ,pSOKU_KSD01_DATA[i2].SOKUTEI_NUM);
		strcpy(pSetJissekiData[0].SOZAI_OK	  ,pSOKU_KSD01_DATA[i2].SOZAI_OK);
		strcpy(pSetJissekiData[0].SOZAI_OK_PRT,pSOKU_KSD01_DATA[i2].SOZAI_OK_PRT);
		strcpy(pSetJissekiData[0].SYUKA_OK	  ,pSOKU_KSD01_DATA[i2].SYUKA_OK);
		strcpy(pSetJissekiData[0].SYUKA_OK_PRT,pSOKU_KSD01_DATA[i2].SYUKA_OK_PRT);

		strcpy(pSetJissekiData[0].OUT_TITLE1  ,pSOKU_KSD01_DATA[i2].OUT_TITLE1);
		strcpy(pSetJissekiData[0].OUT_TITLE2  ,pSOKU_KSD01_DATA[i2].OUT_TITLE2);
		strcpy(pSetJissekiData[0].OUT_TITLE3  ,pSOKU_KSD01_DATA[i2].OUT_TITLE3);
		strcpy(pSetJissekiData[0].OUT_TITLE4  ,pSOKU_KSD01_DATA[i2].OUT_TITLE4);
		strcpy(pSetJissekiData[0].OUT_TITLE5  ,pSOKU_KSD01_DATA[i2].OUT_TITLE5);
		strcpy(pSetJissekiData[0].OUT_TITLE6  ,pSOKU_KSD01_DATA[i2].OUT_TITLE6);
		strcpy(pSetJissekiData[0].OUT_TITLE7  ,pSOKU_KSD01_DATA[i2].OUT_TITLE7);
		strcpy(pSetJissekiData[0].OUT_TITLE8  ,pSOKU_KSD01_DATA[i2].OUT_TITLE8);

		strcpy(pSetJissekiData[0].X_OUT	,pSOKU_KSD01_DATA[i2].X_OUT);
		sMEMO = GetValidityData(Form1->Mem_vSOKU_MEMO[i2]->Text,128);
		if(sMEMO.Length() == 0 ) sMEMO = " ";
		strcpy(pSetJissekiData[0].MEMO	,sMEMO.c_str());
        //更新フラグをみて、更新されていなければ保存を行わない。
		if(pSOKU_KSD01_DATA[i2].UPD_FLG == false)
		{
		}
		else
		{
            //KSD01に対し新規追加か更新かをチェックする
    		sBuf = "SELECT * FROM KSD01";
            sBuf += " WHERE DTKSHIN = '" + AnsiString(pSetJissekiData[0].DTKSHIN) 	+ "'";
            sBuf += " AND   LOTNO 	= '" + AnsiString(pSetJissekiData[0].LOTNO) 	+ "'";
            sBuf += " AND   HINBAN 	= '" + AnsiString(pSetJissekiData[0].HINBAN) 	+ "'";
            // Initial Query
            Query1->Close();
            Query1->SQL->Clear();
            Query1->SQL->Add(sBuf);
            Query1->Open();
            Query1->Active = true;
    		bNEW = false;
            if( Query1->Eof == true ) bNEW = true;
            Query1->Close();
            if(bNEW == true )
	    	{
                //時間データを取得する
		    	if(AnsiString(pSOKU_KSD01_DATA[i2].SKTYMD_SZ).Trim().Length() == 0)
			    {
				    strcpy(pSOKU_KSD01_DATA[i2].SKTYMD_SZ		,FormatDateTime("yyyymmdd",Date()).c_str());			//測定日
                }
	    		if(AnsiString(pSOKU_KSD01_DATA[i2].SKTYMD_SZ_PRT).Trim().Length() == 0)
		    	{
			    	strcpy(pSOKU_KSD01_DATA[i2].SKTYMD_SZ_PRT	,FormatDateTime("yyyymmdd",Date()).c_str()); 			//測定日印刷用
    			}
	    		if(AnsiString(pSOKU_KSD01_DATA[i2].SKTYMD).Trim().Length() == 0)
		    	{
			    	strcpy(pSOKU_KSD01_DATA[i2].SKTYMD			,FormatDateTime("yyyymmdd",Date()).c_str());			//測定日
                }
	    		if(AnsiString(pSOKU_KSD01_DATA[i2].SKTYMD_PRT).Trim().Length() == 0)
		    	{
			    	strcpy(pSOKU_KSD01_DATA[i2].SKTYMD_PRT		,FormatDateTime("yyyymmdd",Date()).c_str()); 			//測定日印刷用
    			}
	    		if(AnsiString(pSOKU_KSD01_DATA[i2].ADDYMD).Trim().Length() == 0)
		    	{
			    	strcpy(pSOKU_KSD01_DATA[i2].ADDYMD			,FormatDateTime("yyyymmdd",Date()).c_str());			//代表登録日
                }
	    		if(AnsiString(pSOKU_KSD01_DATA[i2].ADDTIM).Trim().Length() == 0)
		    	{
			    	strcpy(pSOKU_KSD01_DATA[i2].ADDTIM			,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());  	//代表登録時間
                }
    			strcpy(pSOKU_KSD01_DATA[i2].UPDYMD		,FormatDateTime("yyyymmdd",Date()).c_str()); 			    //代表変更日
	    		strcpy(pSOKU_KSD01_DATA[i2].UPDTIM		,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str()); 	//代表変更時間
		    	strcpy(pSOKU_KSD01_DATA[i2].UPDCNT      ,"0");														//代表更新回数
			    strcpy(pSetJissekiData[0].SKTYMD_SZ		,pSOKU_KSD01_DATA[i2].SKTYMD_SZ);
    			strcpy(pSetJissekiData[0].SKTYMD_SZ_PRT	,pSOKU_KSD01_DATA[i2].SKTYMD_SZ_PRT);
	    		strcpy(pSetJissekiData[0].SKTYMD		,pSOKU_KSD01_DATA[i2].SKTYMD);
		    	strcpy(pSetJissekiData[0].SKTYMD_PRT	,pSOKU_KSD01_DATA[i2].SKTYMD_PRT);
			    strcpy(pSetJissekiData[0].ADDYMD		,pSOKU_KSD01_DATA[i2].ADDYMD);
    			strcpy(pSetJissekiData[0].ADDTIM		,pSOKU_KSD01_DATA[i2].ADDTIM);
	    		strcpy(pSetJissekiData[0].UPDYMD		,pSOKU_KSD01_DATA[i2].UPDYMD);
		    	strcpy(pSetJissekiData[0].UPDTIM		,pSOKU_KSD01_DATA[i2].UPDTIM);
			    strcpy(pSetJissekiData[0].UPDCHR		,pSOKU_KSD01_DATA[i2].UPDCHR);
    			strcpy(pSetJissekiData[0].UPDCNT		,pSOKU_KSD01_DATA[i2].UPDCNT);
///////////////////////
        	    sBuf = "insert into KSD01(";
            	sBuf += " DTKSHIN, LOTNO, HINBAN,";                                                        //onishi
		    	sBuf += " LOTNO1_SZ, LOTNO2_SZ, LOTNO3_SZ, LOTNO4_SZ, LOTNO5_SZ, LOTNO6_SZ,";
		    	sBuf += " HINBAN1_SZ, HINBAN2_SZ, HINBAN3_SZ, HINBAN4_SZ, HINBAN5_SZ, HINBAN6_SZ,";
			    sBuf += " DTKSCOD, DTKSNAM, ZISNAM, HINMEI,";
    			sBuf += " DTKSHIN1_SZ, DTKSHIN2_SZ, DTKSHIN3_SZ,";
	    		sBuf += " DTKSHIN4_SZ, DTKSHIN5_SZ, DTKSHIN6_SZ,";
		    	sBuf += " LOT_LINK_SZ, SOKUTEI_NUM, SOZAI_OK, SOZAI_OK_PRT,";
			    sBuf += " SYUKA_OK, SYUKA_OK_PRT,";
    			sBuf += " OUT_TITLE1, OUT_TITLE2, OUT_TITLE3, OUT_TITLE4,";
	    		sBuf += " OUT_TITLE5, OUT_TITLE6, OUT_TITLE7, OUT_TITLE8,";
		    	sBuf += " X_OUT, MEMO,";
	            sBuf += " SKTYMD_SZ, SKTYMD_SZ_PRT, SKTYMD, SKTYMD_PRT,ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
        	    sBuf += " )";
            	sBuf += " VALUES('";
	            sBuf += AnsiString(pSetJissekiData[0].DTKSHIN)		+ "','";	//	得意先品番
    	        sBuf += AnsiString(pSetJissekiData[0].LOTNO)		+ "','";	//	ロットNO
    	        sBuf += AnsiString(pSetJissekiData[0].HINBAN)		+ "','";	//	自社品番 onishi
    			sBuf += AnsiString(pSetJissekiData[0].LOTNO1_SZ) 	+ "','";
	    		sBuf += AnsiString(pSetJissekiData[0].LOTNO2_SZ) 	+ "','";
		    	sBuf += AnsiString(pSetJissekiData[0].LOTNO3_SZ) 	+ "','";
			    sBuf += AnsiString(pSetJissekiData[0].LOTNO4_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].LOTNO5_SZ) 	+ "','";
	    		sBuf += AnsiString(pSetJissekiData[0].LOTNO6_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN1_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN2_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN3_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN4_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN5_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN6_SZ) 	+ "','";
			    sBuf += AnsiString(pSetJissekiData[0].DTKSCOD) 		+ "','";
     			sBuf += AnsiString(pSetJissekiData[0].DTKSNAM) 		+ "','";
	    		sBuf += AnsiString(pSetJissekiData[0].ZISNAM) 		+ "','";
		    	sBuf += AnsiString(pSetJissekiData[0].HINMEI) 		+ "','";
			    sBuf += AnsiString(pSetJissekiData[0].DTKSHIN1_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].DTKSHIN2_SZ) 	+ "','";
	    		sBuf += AnsiString(pSetJissekiData[0].DTKSHIN3_SZ) 	+ "','";
		    	sBuf += AnsiString(pSetJissekiData[0].DTKSHIN4_SZ) 	+ "','";
			    sBuf += AnsiString(pSetJissekiData[0].DTKSHIN5_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].DTKSHIN6_SZ) 	+ "', ";
	    		sBuf += AnsiString(pSetJissekiData[0].LOT_LINK_SZ) 	+ " , ";
		    	sBuf += AnsiString(pSetJissekiData[0].SOKUTEI_NUM) 	+ " , ";
			    sBuf += AnsiString(pSetJissekiData[0].SOZAI_OK) 	+ " , ";
    			sBuf += AnsiString(pSetJissekiData[0].SOZAI_OK_PRT) + " , ";
	    		sBuf += AnsiString(pSetJissekiData[0].SYUKA_OK) 	+ " , ";
		    	sBuf += AnsiString(pSetJissekiData[0].SYUKA_OK_PRT) + " , ";
			    sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE1) 	+ " ,";
    			sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE2) 	+ " , ";
	    		sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE3) 	+ " , ";
		    	sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE4) 	+ " , ";
			    sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE5) 	+ " , ";
    			sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE6) 	+ " , ";
	    		sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE7) 	+ " , ";
		    	sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE8) 	+ " , ";
			    sBuf += AnsiString(pSetJissekiData[0].X_OUT) 	 	+ " ,'";
    			sBuf += AnsiString(pSetJissekiData[0].MEMO) 		+ "','";
	            sBuf += AnsiString(pSetJissekiData[0].SKTYMD_SZ)  	+ "','";	//	測定日
    	        sBuf += AnsiString(pSetJissekiData[0].SKTYMD_SZ_PRT)+ "','";	//	測定日
	            sBuf += AnsiString(pSetJissekiData[0].SKTYMD)  		+ "','";	//	測定日
        	    sBuf += AnsiString(pSetJissekiData[0].SKTYMD_PRT)  	+ "','";	//	測定日
            	sBuf += AnsiString(pSetJissekiData[0].ADDYMD)  		+ "','";	//	登録日
	            sBuf += AnsiString(pSetJissekiData[0].ADDTIM)  		+ "','";	//	登録時間
    	        sBuf += AnsiString(pSetJissekiData[0].UPDYMD)  		+ "','";	//	変更日
            	sBuf += AnsiString(pSetJissekiData[0].UPDTIM)  		+ "', " ;	//	変更時間
	    		if(AnsiString(pSetJissekiData[0].UPDCHR).Trim().Length() == 0)
                {
    	        	strcpy(pSetJissekiData[0].UPDCHR,AnsiString(Form1->USER_COD).c_str());
			    }
    	        sBuf += AnsiString(pSetJissekiData[0].UPDCHR)  				+ " , " ;	//	更新者
        	    sBuf += AnsiString(pSetJissekiData[0].UPDCNT);  	         				//	更新回数
            	sBuf += ")";
    		}
	    	else
		    {
    			if(AnsiString(pSOKU_KSD01_DATA[i2].SKTYMD_SZ).Trim().Length() == 0)
	    		{
		    		strcpy(pSOKU_KSD01_DATA[i2].SKTYMD_SZ		,FormatDateTime("yyyymmdd",Date()).c_str());			//測定日
                }
    			if(AnsiString(pSOKU_KSD01_DATA[i2].SKTYMD_SZ_PRT).Trim().Length() == 0)
	    		{
		    		strcpy(pSOKU_KSD01_DATA[i2].SKTYMD_SZ_PRT	,FormatDateTime("yyyymmdd",Date()).c_str()); 			//測定日印刷用
			    }
    			if(AnsiString(pSOKU_KSD01_DATA[i2].SKTYMD).Trim().Length() == 0)
	    		{
		    		strcpy(pSOKU_KSD01_DATA[i2].SKTYMD			,FormatDateTime("yyyymmdd",Date()).c_str());			//測定日
                }
    			if(AnsiString(pSOKU_KSD01_DATA[i2].SKTYMD_PRT).Trim().Length() == 0)
	    		{
		    		strcpy(pSOKU_KSD01_DATA[i2].SKTYMD_PRT		,FormatDateTime("yyyymmdd",Date()).c_str()); 			//測定日印刷用
			    }
    			if(AnsiString(pSOKU_KSD01_DATA[i2].ADDYMD).Trim().Length() == 0)
	    		{
		    		strcpy(pSOKU_KSD01_DATA[i2].ADDYMD			,FormatDateTime("yyyymmdd",Date()).c_str());			//代表登録日
                }
    			if(AnsiString(pSOKU_KSD01_DATA[i2].ADDTIM).Trim().Length() == 0)
	    		{
		    		strcpy(pSOKU_KSD01_DATA[i2].ADDTIM			,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());  	//代表登録時間
                }
    			strcpy(pSOKU_KSD01_DATA[i2].UPDYMD		,FormatDateTime("yyyymmdd",Date()).c_str()); 			//代表変更日
	    		strcpy(pSOKU_KSD01_DATA[i2].UPDTIM		,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str()); 	//代表変更時間
                // 更新回数////////////
			    i1 = AnsiString(pSOKU_KSD01_DATA[i2].UPDCNT).ToIntDef(0);
                i1 ++;
    			strcpy(pSOKU_KSD01_DATA[i2].UPDCNT	,AnsiString(i1).c_str());
                //////////////////////
    			strcpy(pSetJissekiData[0].SKTYMD_SZ		,pSOKU_KSD01_DATA[i2].SKTYMD_SZ);
	    		strcpy(pSetJissekiData[0].SKTYMD_SZ_PRT	,pSOKU_KSD01_DATA[i2].SKTYMD_SZ_PRT);
		    	strcpy(pSetJissekiData[0].SKTYMD		,pSOKU_KSD01_DATA[i2].SKTYMD);
			    strcpy(pSetJissekiData[0].SKTYMD_PRT	,pSOKU_KSD01_DATA[i2].SKTYMD_PRT);
    			strcpy(pSetJissekiData[0].ADDYMD		,pSOKU_KSD01_DATA[i2].ADDYMD);
	    		strcpy(pSetJissekiData[0].ADDTIM		,pSOKU_KSD01_DATA[i2].ADDTIM);
		    	strcpy(pSetJissekiData[0].UPDYMD		,pSOKU_KSD01_DATA[i2].UPDYMD);
			    strcpy(pSetJissekiData[0].UPDTIM		,pSOKU_KSD01_DATA[i2].UPDTIM);
    			strcpy(pSetJissekiData[0].UPDCHR		,pSOKU_KSD01_DATA[i2].UPDCHR);
	    		strcpy(pSetJissekiData[0].UPDCNT		,pSOKU_KSD01_DATA[i2].UPDCNT);
                // 問合せ文作成
         		sBuf = "update KSD01 set ";
            	sBuf += " DTKSHIN ='" 		+ AnsiString(pSetJissekiData[0].DTKSHIN)	   + "',";	//	得意先品番
		    	sBuf += " LOTNO ='" 		+ AnsiString(pSetJissekiData[0].LOTNO)	   	   + "',";	//	得意先品番
		    	sBuf += " HINBAN ='" 		+ AnsiString(pSetJissekiData[0].HINBAN)	   	   + "',";	//	工管発行日 onishi
			    sBuf += " LOTNO1_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO1_SZ)	   + "',";	//	得意先品番
    			sBuf += " LOTNO2_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO2_SZ)	   + "',";	//	得意先品番
	    		sBuf += " LOTNO3_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO3_SZ)	   + "',";	//	得意先品番
		    	sBuf += " LOTNO4_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO4_SZ)	   + "',";	//	得意先品番
			    sBuf += " LOTNO5_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO5_SZ)	   + "',";	//	得意先品番
    			sBuf += " LOTNO6_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO6_SZ)	   + "',";	//	得意先品番
			    sBuf += " HINBAN1_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN1_SZ)	   + "',";	//	得意先品番
			    sBuf += " HINBAN2_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN2_SZ)	   + "',";	//	得意先品番
			    sBuf += " HINBAN3_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN3_SZ)	   + "',";	//	得意先品番
			    sBuf += " HINBAN4_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN4_SZ)	   + "',";	//	得意先品番
			    sBuf += " HINBAN5_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN5_SZ)	   + "',";	//	得意先品番
			    sBuf += " HINBAN6_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN6_SZ)	   + "',";	//	得意先品番
		    	sBuf += " DTKSCOD ='"		+ AnsiString(pSetJissekiData[0].DTKSCOD)	   + "',";	//	得意先品番
			    sBuf += " DTKSNAM ='" 		+ AnsiString(pSetJissekiData[0].DTKSNAM)	   + "',";	//	得意先品番
    			sBuf += " ZISNAM ='" 		+ AnsiString(pSetJissekiData[0].ZISNAM)	   	   + "',";	//	得意先品番
	    		sBuf += " HINMEI ='" 		+ AnsiString(pSetJissekiData[0].HINMEI)	   	   + "',";	//	得意先品番
		    	sBuf += " DTKSHIN1_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN1_SZ)   + "',";	//	得意先品番
			    sBuf += " DTKSHIN2_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN2_SZ)   + "',";	//	得意先品番
    			sBuf += " DTKSHIN3_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN3_SZ)   + "',";	//	得意先品番
	    		sBuf += " DTKSHIN4_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN4_SZ)   + "',";	//	得意先品番
		    	sBuf += " DTKSHIN5_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN5_SZ)   + "',";	//	得意先品番
                sBuf += " DTKSHIN6_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN6_SZ)   + "',";	//	得意先品番
    			sBuf += " LOT_LINK_SZ =" 	+ AnsiString(pSetJissekiData[0].LOT_LINK_SZ)   + ",";	//	得意先品番
	    		sBuf += " SOKUTEI_NUM =" 	+ AnsiString(pSetJissekiData[0].SOKUTEI_NUM)   + ",";	//	得意先品番
		    	sBuf += " SOZAI_OK ="	 	+ AnsiString(pSetJissekiData[0].SOZAI_OK)	   + ",";	//	得意先品番
			    sBuf += " SOZAI_OK_PRT ="	+ AnsiString(pSetJissekiData[0].SOZAI_OK_PRT)  + ",";	//	得意先品番
    			sBuf += " SYUKA_OK =" 		+ AnsiString(pSetJissekiData[0].SYUKA_OK)	   + ",";	//	得意先品番
	    		sBuf += " SYUKA_OK_PRT =" 	+ AnsiString(pSetJissekiData[0].SYUKA_OK_PRT)  + ",";	//	得意先品番
		    	sBuf += " OUT_TITLE1 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE1)	   + ",";	//	得意先品番
			    sBuf += " OUT_TITLE2 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE2)	   + ",";	//	得意先品番
    			sBuf += " OUT_TITLE3 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE3)	   + ",";	//	得意先品番
	    		sBuf += " OUT_TITLE4 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE4)	   + ",";	//	得意先品番
		    	sBuf += " OUT_TITLE5 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE5)	   + ",";	//	得意先品番
			    sBuf += " OUT_TITLE6 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE6)	   + ",";	//	得意先品番
    			sBuf += " OUT_TITLE7 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE7)	   + ",";	//	得意先品番
	    		sBuf += " OUT_TITLE8 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE8)	   + ",";	//	得意先品番
		    	sBuf += " X_OUT =" 			+ AnsiString(pSetJissekiData[0].X_OUT)	   	   + ",";	//	得意先品番
			    sBuf += " MEMO ='" 			+ AnsiString(pSetJissekiData[0].MEMO)	   	   + "',";	//	得意先品番
    	        sBuf += " SKTYMD_SZ ='" 	+ AnsiString(pSetJissekiData[0].SKTYMD_SZ)	   + "',";	//	得意先品番
	    		sBuf += " SKTYMD_SZ_PRT ='"	+ AnsiString(pSetJissekiData[0].SKTYMD_SZ_PRT) + "',";	//	得意先品番
	            sBuf += " SKTYMD ='" 		+ AnsiString(pSetJissekiData[0].SKTYMD)	   	   + "',";	//	得意先品番
			    sBuf += " SKTYMD_PRT ='"	+ AnsiString(pSetJissekiData[0].SKTYMD_PRT)	   + "',";	//	得意先品番
    			sBuf += " ADDYMD ='" 		+ AnsiString(pSetJissekiData[0].ADDYMD)	   	   + "',";	//	得意先品番
	    		sBuf += " ADDTIM ='" 		+ AnsiString(pSetJissekiData[0].ADDTIM)	   	   + "',";	//	得意先品番
		    	sBuf += " UPDYMD ='" 		+ AnsiString(pSetJissekiData[0].UPDYMD)	   	   + "',";	//	得意先品番
			    sBuf += " UPDTIM ='" 		+ AnsiString(pSetJissekiData[0].UPDTIM)	   	   + "',";	//	得意先品番
    			sBuf += " UPDCHR =" 		+ AnsiString(pSetJissekiData[0].UPDCHR)	   	   + ",";	//	得意先品番
	    		sBuf += " UPDCNT =" 		+ AnsiString(pSetJissekiData[0].UPDCNT)	   	   + " ";	//	得意先品番
     	    	sBuf += " WHERE DTKSHIN='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN)+ "'";
     		    sBuf += " AND   LOTNO='" 	+ AnsiString(pSetJissekiData[0].LOTNO)  + "'";
     		    sBuf += " AND   HINBAN='" 	+ AnsiString(pSetJissekiData[0].HINBAN) + "'";          //onishi
     		}

            //For Debug
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
            // 問い合せ文の実行
    		try
            {
            	Query1->ExecSQL();
            }
            catch(EDatabaseError& e)
            {
            	SBr1->Panels->Items[0]->Text = e.Message;
                SBr1->Update();
                return(false);
            }
            catch(Exception& e)
            {
            	SBr1->Panels->Items[0]->Text = e.Message;
                SBr1->Update();
                return(false);
            }
        }
    }

    //KSD02の更新(新規登録の場合)

	iRowCount = SGr_vSOKU_SYUKA->RowCount;
    if( iRowCount < 2 ) return(true);         //出荷データがない
	for(iCol = 0; iCol < SGr_vSOKU_SYUKA->ColCount;iCol++)
	{
        //更新フラグをみて、更新されていなければ保存を行わない。
		if(pSOKU_KSD01_DATA[iCol].UPD_FLG == false)
		{
		}
		else
		{
    		for( iRow = 1;iRow < iRowCount; iRow=iRow)
	    	{
		    	iSOKUSU 	= AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);
			    VALUE_TYPE 	= AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0);
    			iUNQNO = 	AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UNQ_NO).ToIntDef(0);
	    		iKOMK_NO = 	AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KOMK_NO).ToIntDef(0);
		    	if(iKOMK_NO == -999)
			    {
    			}
	    		else
		    	{
                    //実際の指示数を検出します
                    iSIJI_NSU = 0;
                    for(i3=0; i3 < AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);i3++)
                    {
                        if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].KOMK_NO).ToIntDef(0) == -999) break;
                        iSIJI_NSU ++;
                    }
                    iSOKUSU=iSIJI_NSU;
                    //KSD03（例外データ）削除
                    sBuf = "";
                    sBuf = "DELETE FROM KSD03";
	        		sBuf +=	" where DTKSHIN='" + AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].DTKSHIN)+ "'";
                    sBuf += " and   LOTNO  ='" + AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].LOTNO)  + "'";
                    sBuf += " and   HINBAN ='" + AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].HINBAN) + "'";
                    sBuf += " and   UNQ_NO = " + AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UNQ_NO) ;
                    //For Debug
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
                    // 問い合せ文の実行
                    try{
                        Query1->ExecSQL();
                    }
                    catch(EDatabaseError& e)
                    {
                        SBr1->Panels->Items[0]->Text = e.Message;
                        SBr1->Update();
                        return(false);
                    }
                    catch(Exception& e)
                    {
                        SBr1->Panels->Items[0]->Text = e.Message;
                        SBr1->Update();
                        return(false);
                    }
                    ///////////////////////////////////////////////
        			SOKU_VAL_SU = 0;
	        		DISP_VAL_SU = 0;
		        	iSOKU_VAL_SU = 0;
			        iDISP_VAL_SU = 0;
                    GOUKEI_RESULT = 0;
                    DISP_GOUKEI_RESULT = 0;
		        	SOKU_MAX = 0.0;
			        DISP_MAX = 0.0;
    			    SOKU_MIN = 0.0;
    	    		DISP_MIN = 0.0;
	    	    	SOKU_VAL_MAX = 0;
		    	    SOKU_VAL_MIN = 0;
    		    	DISP_VAL_MAX = 0;
	    		    DISP_VAL_MIN = 0;
    	    		FIRST_FLG 	    = true;
	    	    	DISP_FIRST_FLG  = true;
		    	    RESULT          = 0;
    			    DISP_RESULT     = 0;
                    iOK_FLG         = 2;
                    iDISP_OK_FLG    = 2;
                    //測定値初期化
    	    		strcpy(SetData.SOKU_VAL01 , "");
	    	    	strcpy(SetData.SOKU_VAL02 , "");
		    	    strcpy(SetData.SOKU_VAL03 , "");
    			    strcpy(SetData.SOKU_VAL04 , "");
        			strcpy(SetData.SOKU_VAL05 , "");
	        		strcpy(SetData.SOKU_VAL06 , "");
		        	strcpy(SetData.SOKU_VAL07 , "");
			        strcpy(SetData.SOKU_VAL08 , "");
        			strcpy(SetData.SOKU_VAL09 , "");
	        		strcpy(SetData.SOKU_VAL10 , "");
                    //印刷値初期化
    		    	strcpy(SetData.DISP_VAL01 , "");
	    		    strcpy(SetData.DISP_VAL02 , "");
    		    	strcpy(SetData.DISP_VAL03 , "");
	    		    strcpy(SetData.DISP_VAL04 , "");
	        		strcpy(SetData.DISP_VAL05 , "");
    		    	strcpy(SetData.DISP_VAL06 , "");
    			    strcpy(SetData.DISP_VAL07 , "");
    	    		strcpy(SetData.DISP_VAL08 , "");
	    	    	strcpy(SetData.DISP_VAL09 , "");
		    	    strcpy(SetData.DISP_VAL10 , "");

        			i4 = 0;
                    for( i3 = 0; i3 < iSOKUSU;i3++)
                    {
			        	bHANTEI = true;
    			    	bDISP_HANTEI = true;
                        //以上以下の規格の場合対策 ///////////////////////////////////////////
                        iKIKA_KIND = 1;		//デフォルトは上下限で判定
	            	    if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].KIKA_TYPE) == 1)
                        {
			                if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].KIKA_KIND) == 2)
			                {
				                iKIKA_KIND = 2;
            			    }
                			else if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].KIKA_KIND) == 3)
	                		{
		                		iKIKA_KIND = 3;
			                }
            		    }
                        ////////////////////////////////////////////////////////////////////
                        //測定用データ
		    	    	switch( VALUE_TYPE )
			    	    {
				        case 0:						//整数or少数
    				    case 1:						//角度
    				    	SOKU_MAX = pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].MAX;
	    				    SOKU_MIN = pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].MIN;
    		    			if(iDEBUG != 1)
	    		    		{
                                bRtn = Form1->ConvDoubleDefS(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].RESULT),
                        								"0.00",
                                                        AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].RESULT),
                                                        &sBufConv);
                                if ( bRtn ) {
                            	    RESULT = Form1->ConvDoubleDefD(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].RESULT),0.0);
                                }
	    					    else
    		    				{
	    		    				RESULT = 0.0;
		    		    			bHANTEI = false;
                                }
        					}
        					if( bRtn && AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0) != 0)
	        				{
                                switch(iKIKA_KIND)
                                {
                                case 1:
					        	    if( RESULT > SOKU_MAX || RESULT < SOKU_MIN )
                                    {
                                        if( iOK_FLG != -1 )
                                        {
                                            iOK_FLG = 1;
                                        }
                                    }
                                    else
                                    {
                                        if( iOK_FLG == 2 )
                                        {
                                            iOK_FLG = 0;
                                        }
                                    }
                                    break;
        						case 2:
	                            	if( RESULT > SOKU_MAX  )
                                    {
                                        if( iOK_FLG != -1 )
                                        {
                                            iOK_FLG = 1;
                                        }
                                    }
                                    else
                                    {
                                        if( iOK_FLG == 2 )
                                        {
                                            iOK_FLG = 0;
                                        }
                                    }
                                    break;
			        			case 3:
	                            	if( RESULT < SOKU_MIN )
                                    {
                                        if( iOK_FLG != -1 )
                                        {
                                            iOK_FLG = 1;
                                        }
                                    }
                                    else
                                    {
                                        if( iOK_FLG == 2 )
                                        {
                                            iOK_FLG = 0;
                                        }
                                    }
                                    break;
                                }
        						if( FIRST_FLG == true )
                                {
	        						SOKU_VAL_MAX = RESULT;
		        					SOKU_VAL_MIN = RESULT;
			        				FIRST_FLG = false;
				        		}
					        	else
    						    {
	    						    if( RESULT > SOKU_VAL_MAX ) SOKU_VAL_MAX = RESULT;
		    					    if( RESULT < SOKU_VAL_MIN ) SOKU_VAL_MIN = RESULT;
			    			    }
				    		    GOUKEI_RESULT += RESULT;
                                iSOKU_VAL_SU ++;
					        }
                            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0) != 0)
                            {
                                SOKU_VAL_SU ++;
                                if( !bRtn ) iOK_FLG = -1;
                            }
				        	break;
                        case 2:						//良、否
                            try{
                                // 良/否判定も未入力のまま保存させたいので RESULT_BUF を使って処理する
                                RESULT_BUF = AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].RESULT);
                            }
                            catch(EConvertError& e){
                                bHANTEI = false;
                            }
                            catch(...){
                                bHANTEI = false;
                            }
	    				    if(bHANTEI && AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0) != 0)
    		    			{
                                // 良/否判定も未入力のまま保存させたいので RESULT_BUF を使って処理する
                                if( RESULT_BUF.ToIntDef(0) == 1 )
                                {
                                    //OK_FLG = false;
                                    if( iOK_FLG != -1 ) iOK_FLG = 1;
                                }
                                iSOKU_VAL_SU ++;
			    		    }
                            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0) != 0)
                            {
                                SOKU_VAL_SU ++;
                                if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].RESULT).Trim().Length() == 0)
                                {
                                    iOK_FLG = -1;
                                }
                            }
	    			    	break;
                     	case 3:
	    		    		RESULT_BUF = GetValidityData(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].RESULT),14);
                            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0) != 0)
                            {
                           	    SOKU_VAL_SU ++;
                                iSOKU_VAL_SU ++;
                                if((RESULT_BUF.Trim().Length() != 0 ) && iOK_FLG == 2) iOK_FLG = 0;
                                if(RESULT_BUF.Trim().Length() != 0 ) iOK_FLG = -1;
                            }
                       	    break;
        				}

                        //表示用データの加工
			    	    switch( VALUE_TYPE )
    			    	{
	    			    case 0:						//整数or少数
		    	    	case 1:						//角度
    		    			DISP_MAX = pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].MAX;
	    		    		DISP_MIN = pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].MIN;
		    		    	if(iDEBUG != 1)
			    		    {
                                bRtn = Form1->ConvDoubleDefS(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT),
                           								"0.00",
                                                        AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT),
                                                        &sBufConv);
                                if ( bRtn ) {
                            	    DISP_RESULT = Form1->ConvDoubleDefD(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT),0.0);
                                } else {
			    				    DISP_RESULT = 0.0;
    			    				bDISP_HANTEI = false;
                                }
    		    			}
	    		    		if( bRtn && AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0) != 0)
		    		    	{
                                switch(iKIKA_KIND)
                                {
                                case 1:
	    				    	    if( DISP_RESULT > DISP_MAX || DISP_RESULT < DISP_MIN )
                                    {
                                        if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                    }
                                    else
                                    {
                                        if( iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                    }
                                    break;
    			    			case 2:
	                            	if( DISP_RESULT > DISP_MAX  )
                                    {
                                        if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                    }
                                    else
                                    {
                                        if( iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                    }
                                    break;
			    			    case 3:
    	                        	if( DISP_RESULT < DISP_MIN )
                                    {
                                        if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                    }
                                    else
                                    {
                                        if( iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                    }
                                    break;
                                }
			    			    if( DISP_FIRST_FLG == true )
                                {
    				    			DISP_VAL_MAX = DISP_RESULT;
	    				    		DISP_VAL_MIN = DISP_RESULT;
		    				    	DISP_FIRST_FLG = false;
    		    				}
	    		    			else
		    		    		{
			    		    		if( DISP_RESULT > DISP_VAL_MAX ) DISP_VAL_MAX = DISP_RESULT;
				    		    	if( DISP_RESULT < DISP_VAL_MIN ) DISP_VAL_MIN = DISP_RESULT;
    					    	}
                                iDISP_VAL_SU ++;
    	    					DISP_GOUKEI_RESULT += DISP_RESULT;
                            }
                            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0) != 0)
                            {
                                DISP_VAL_SU ++;
                                if( !bRtn ) iDISP_OK_FLG = -1;
                            }
	    	    			break;
                        case 2:						//良、否
	    	    			if(iDEBUG != 1)
		    	    		{
	                    		try{
                                	// 良/否判定も未入力のまま保存させたいので DISP_RESULT_BUF を使って処理する
				    	    		DISP_RESULT_BUF = AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT);
					    	    }
        						catch(EConvertError& e){
 	        						bDISP_HANTEI = false;
			        			}
				        		catch(...){
					        		bHANTEI = false;
    						    }
                            }
        					if(bDISP_HANTEI && AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0) != 0)
	        				{
                               	// 良/否判定も未入力のまま保存させたいので DISP_RESULT_BUF を使って処理する
                            	if( DISP_RESULT_BUF.ToIntDef(0) == 1 )
                                {
                                    if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                }
                                else
                                {
                                    if( iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                }
                            }
                            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0) != 0)
                            {
                                DISP_VAL_SU ++;
                                iDISP_VAL_SU ++;
                                if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT).Trim().Length() == 0)
                                {
                                    iDISP_OK_FLG = -1;
                                }
                            }
		        			break;
                     	case 3:
    				    	DISP_RESULT_BUF = GetValidityData(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT),14);
                            if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0) != 0)
                            {
                           	    DISP_VAL_SU ++;
                                iDISP_VAL_SU ++;
                                if( iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT).Trim().Length() == 0)
                                {
                                    iDISP_OK_FLG = -1;
                                }

                            }
                           	break;
    	    			}

                        // 良/否判定も未入力のまま保存させたいので VALUE_TYPE = 2 の時でも RESULT_BUF を使って処理する
                        // イコール　case 2はコメント
                        switch( VALUE_TYPE )
                        {
                        case 0:
                        case 1:
    		    			if( bHANTEI ) RESULT_BUF 		= AnsiString(RESULT);
	    		    		if( !bHANTEI ) RESULT_BUF 		= "";
                            break;
                        default:
                        	break;
                        }
	    			    switch( VALUE_TYPE )
                        {
                        case 0:
                        case 1:
			    	    	if( bDISP_HANTEI ) DISP_RESULT_BUF 		= AnsiString(DISP_RESULT);
				    	    if( !bDISP_HANTEI ) DISP_RESULT_BUF 		= "";
                            break;
                        default:
                        	break;
                        }

    	    			if(bHANTEI == true || bHANTEI == false)
	    	    		{
	                        switch( i4 )
    	                    {
        	                case 0:
                    	    	strcpy(SetData.SOKU_VAL01 , AnsiString(RESULT_BUF).c_str());
	        		   			strcpy(SetData.DISP_VAL01 , AnsiString(DISP_RESULT_BUF).c_str());
		        		  		break;
    	                    case 1:
				           		strcpy(SetData.SOKU_VAL02 , AnsiString(RESULT_BUF).c_str());
                                strcpy(SetData.DISP_VAL02 , AnsiString(DISP_RESULT_BUF).c_str());
				 		        break;
        					case 2:
	        		   			strcpy(SetData.SOKU_VAL03 , AnsiString(RESULT_BUF).c_str());
		          				strcpy(SetData.DISP_VAL03 , AnsiString(DISP_RESULT_BUF).c_str());
		 	        			break;
				        	case 3:
		   			        	strcpy(SetData.SOKU_VAL04 , AnsiString(RESULT_BUF).c_str());
	  					        strcpy(SetData.DISP_VAL04 , AnsiString(DISP_RESULT_BUF).c_str());
    	 					    break;
        					case 4:
   	        					strcpy(SetData.SOKU_VAL05 , AnsiString(RESULT_BUF).c_str());
  		        				strcpy(SetData.DISP_VAL05 , AnsiString(DISP_RESULT_BUF).c_str());
 			        			break;
	                        case 5:
				   	        	strcpy(SetData.SOKU_VAL06 , AnsiString(RESULT_BUF).c_str());
				  		        strcpy(SetData.DISP_VAL06 , AnsiString(DISP_RESULT_BUF).c_str());
    				 		    break;
    	    				case 6:
	    	    	   			strcpy(SetData.SOKU_VAL07 , AnsiString(RESULT_BUF).c_str());
		    	      			strcpy(SetData.DISP_VAL07 , AnsiString(DISP_RESULT_BUF).c_str());
		 	    	    		break;
				    	    case 7:
    		   		    		strcpy(SetData.SOKU_VAL08 , AnsiString(RESULT_BUF).c_str());
	      				    	strcpy(SetData.DISP_VAL08 , AnsiString(DISP_RESULT_BUF).c_str());
	 	    				    break;
    			    		case 8:
   	    			    		strcpy(SetData.SOKU_VAL09 , AnsiString(RESULT_BUF).c_str());
  		    			    	strcpy(SetData.DISP_VAL09 , AnsiString(DISP_RESULT_BUF).c_str());
 			    			    break;
    	                    case 9:
	    			       		strcpy(SetData.SOKU_VAL10 , AnsiString(RESULT_BUF).c_str());
		    		  	    	strcpy(SetData.DISP_VAL10 , AnsiString(DISP_RESULT_BUF).c_str());
			    	 		    break;
    				    	default:  								//例外データ用ルーチンを考える
            				    //KSD03に対し新規追加か更新かをチェックする
	            				sBuf = "SELECT * FROM KSD03";
			        			sBuf += " WHERE DTKSHIN = '" + AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].DTKSHIN)+ "'";
        	                    sBuf += " AND LOTNO = '"  	 + AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].LOTNO) 	+ "'";
        	                    sBuf += " AND HINBAN = '"  	 + AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].HINBAN) + "'";
					        	sBuf += " AND UNQ_NO = " 	 + AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UNQ_NO)  ;
     					        sBuf += " AND SOKU_NO = " 	 + AnsiString(i3+1) ;
                			    // Initial Query
	        	    			Query1->Close();
    	    	    			Query1->SQL->Clear();
        	    	    		Query1->SQL->Add(sBuf);
    			    	    	Query1->Open();
    				    	    Query1->Active = true;

        		            	bNEW = false;
	        		    		if( Query1->Eof == true ) bNEW = true;
	            				Query1->Close();
			        			if( bNEW == true )
				        		{
	                                //新規登録
        							strcpy(SetData.DTKSHIN		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].DTKSHIN);
            		        		strcpy(SetData.LOTNO		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].LOTNO);
            		        		strcpy(SetData.HINBAN		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].HINBAN);
                		    		strcpy(SetData.UNQ_NO		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UNQ_NO);
			        				sBuf = "insert into KSD03(";
    	                			sBuf += " DTKSHIN, LOTNO, HINBAN, UNQ_NO, SOKU_NO, SOKU_VAL, DISP_VAL";
        	    	        		sBuf += " )";
		            	        	sBuf += " VALUES('";
			            	        sBuf += AnsiString(SetData.DTKSHIN)           	+ "','";	//	得意先品番
        			        	    sBuf += AnsiString(SetData.LOTNO)	       		+ "','";	//	ロットNO
        			        	    sBuf += AnsiString(SetData.HINBAN)	       		+ "', ";	//	工管発行日 onishi
                			    	sBuf += AnsiString(SetData.UNQ_NO)  			+ " , ";	//	明細NO
	    	    					sBuf += AnsiString(i3+1)						+ " ,'";	//	測定NO
		    	    				sBuf += AnsiString(RESULT_BUF)                  + "','";	//	測定値
			    	    			sBuf += AnsiString(DISP_RESULT_BUF)				+ "') "; 	//	印刷用測定値
				    	    	}
					    	    else
    					    	{
                                    //更新
        							strcpy(SetData.DTKSHIN		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].DTKSHIN);
            		        		strcpy(SetData.LOTNO		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].LOTNO);
            		        		strcpy(SetData.HINBAN		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].HINBAN);
                		    		strcpy(SetData.UNQ_NO		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UNQ_NO);
			        				sBuf = "update KSD03 set ";
    			        	        sBuf += " DTKSHIN  = '" 	+ AnsiString(SetData.DTKSHIN) 	+ "',"	;
					        		sBuf += " LOTNO    = '" 	+ AnsiString(SetData.LOTNO) 	+ "',"	;
					        		sBuf += " HINBAN   = '" 	+ AnsiString(SetData.HINBAN) 	+ "',"	;
						        	sBuf += " UNQ_NO   =  " 	+ AnsiString(SetData.UNQ_NO) 	+ ","	;
			              	        sBuf += " SOKU_NO  =  "		+ AnsiString(i3+1) 			   	+ " , " ;
        			        	    sBuf += " SOKU_VAL = '"		+ AnsiString(RESULT_BUF) 		+ "'," ;
                			    	sBuf += " DISP_VAL = '"		+ AnsiString(DISP_RESULT_BUF) 	+ "'" ;
	    	    					sBuf += " WHERE DTKSHIN = '" + AnsiString(SetData.DTKSHIN)	+ "'";
                        	    	sBuf += " AND   LOTNO   = '" + AnsiString(SetData.LOTNO) 	+ "'";
                        	    	sBuf += " AND   HINBAN  = '" + AnsiString(SetData.HINBAN) 	+ "'";
			    	    			sBuf += " AND   UNQ_NO  =  " + AnsiString(SetData.UNQ_NO) 	 	 ;
     			    	    		sBuf += " AND   SOKU_NO =  " + AnsiString(i3+1) ;
					    	    }
                                //For Debug
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
    			    		    // 問い合せ文の実行
	    		            	try{
    	        		        	Query1->ExecSQL();
			                    }
            	    		    catch(EDatabaseError& e)
	    	            	    {
	            		        	SBr1->Panels->Items[0]->Text = e.Message;
    	                	    	SBr1->Update();
			                        return(false);
            			        }
        		        	    catch(Exception& e)
                		    	{
		        	            	SBr1->Panels->Items[0]->Text = e.Message;
    	            		        SBr1->Update();
        	                		return(false);
		    	                }
        		   				break;
	        	  			}
		        			i4 ++;
			        	}
                    }
                    //１項目のセーブ実行
        			strcpy(SetData.DTKSHIN		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].DTKSHIN);
                    strcpy(SetData.LOTNO		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].LOTNO);
                    strcpy(SetData.HINBAN		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].HINBAN);      //onishi
                    strcpy(SetData.UNQ_NO		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UNQ_NO);
                    strcpy(SetData.ORDER_NO		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ORDER_NO);
                    strcpy(SetData.SKB_NO		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKB_NO);
                    strcpy(SetData.HINBAN_SK	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].HINBAN_SK);
                    strcpy(SetData.KOMK_NO		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KOMK_NO);
                    strcpy(SetData.KOMK_NM		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KOMK_NM);
                    strcpy(SetData.KOMK_ENG		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KOMK_ENG);
                    strcpy(SetData.KOMK_SUB		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KOMK_SUB);
                    strcpy(SetData.KOMK_SUB_ENG	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KOMK_SUB_ENG);
                    strcpy(SetData.KIKI_NO		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKI_NO);
                    strcpy(SetData.KIKI_NM		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKI_NM);
                    strcpy(SetData.TANI			,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].TANI);
                    strcpy(SetData.KIKA_TYPE	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKA_TYPE);
                    strcpy(SetData.KIKA_KIND	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKA_KIND);
                    strcpy(SetData.KIKA_DECI	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKA_DECI);
                    strcpy(SetData.KIKA_NUM1	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKA_NUM1);
                    strcpy(SetData.KIKA_NUM2	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKA_NUM2);
                    strcpy(SetData.KIKA_NUM3	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKA_NUM3);
                    strcpy(SetData.KIKA_STR		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKA_STR);
                    strcpy(SetData.KIKA_SUB1	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKA_SUB1);
                    strcpy(SetData.KIKA_SUB2	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKA_SUB2);
                    strcpy(SetData.KIKA_SUB3	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKA_SUB3);
                    strcpy(SetData.SOKU_SU	    ,AnsiString(iSIJI_NSU).c_str());
                    strcpy(SetData.SOKU_FLG		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SOKU_FLG);
                    strcpy(SetData.TOKU_FLG		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].TOKU_FLG);
                    strcpy(SetData.KIKA_PRT		,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].KIKA_PRT);
                    strcpy(SetData.VALUE_TYPE	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].VALUE_TYPE);
                    strcpy(SetData.VALUE_DECI	,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].VALUE_DECI);
                    //指示数と実績数を同じにする
                    strcpy(SetData.SOKU_VAL_SU	    ,AnsiString(iSIJI_NSU).c_str());
    		    	if( iSOKU_VAL_SU > 0)
	    		    {
		    		    SOKU_VAL_AVE = GOUKEI_RESULT / iSOKU_VAL_SU;
    			    }
                    else
	        		{
		        		SOKU_VAL_AVE = 0;
                    }
        			if( SOKU_VAL_AVE > 9999999.999999 ) SOKU_VAL_AVE = 9999999.999999;
	        		if( SOKU_VAL_MAX > 9999999.99999  ) SOKU_VAL_MAX = 9999999.99999 ;
		        	if( SOKU_VAL_MIN > 9999999.99999  ) SOKU_VAL_MIN = 9999999.99999 ;
    		    	strcpy(SetData.SOKU_VAL_AVE	,AnsiString(SOKU_VAL_AVE).SubString(1,14).c_str());
	    		    strcpy(SetData.SOKU_VAL_MAX ,AnsiString(SOKU_VAL_MAX).SubString(1,14).c_str());
    		    	strcpy(SetData.SOKU_VAL_MIN ,AnsiString(SOKU_VAL_MIN).SubString(1,14).c_str());
                    strcpy(SetData.SOKU_OK,AnsiString(iOK_FLG).c_str());
                    //指示数と実績数を同じにする
                    strcpy(SetData.DISP_VAL_SU	    ,AnsiString(iSIJI_NSU).c_str());
        			if( iDISP_VAL_SU > 0)
	        		{
		        		DISP_VAL_AVE = DISP_GOUKEI_RESULT / iDISP_VAL_SU;
			        }
    			    else
    	    		{
	    	    		DISP_VAL_AVE = 0;
		    	    }
    		    	if( DISP_VAL_AVE > 9999999.999999 ) DISP_VAL_AVE = 9999999.999999;
	    		    if( DISP_VAL_MAX > 9999999.99999  ) DISP_VAL_MAX = 9999999.99999 ;
    		    	if( DISP_VAL_MIN > 9999999.99999  ) DISP_VAL_MIN = 9999999.99999 ;
        			strcpy(SetData.DISP_VAL_AVE	,AnsiString(DISP_VAL_AVE).SubString(1,14).c_str());
	        		strcpy(SetData.DISP_VAL_MAX ,AnsiString(DISP_VAL_MAX).SubString(1,14).c_str());
		        	strcpy(SetData.DISP_VAL_MIN ,AnsiString(DISP_VAL_MIN).SubString(1,14).c_str());
                    strcpy(SetData.DISP_OK,AnsiString(iDISP_OK_FLG).c_str());
        			i4 = AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCNT).ToIntDef(0)+1;
	        		strcpy(SetData.UPDCNT ,AnsiString(i4).c_str());
		        	//この項目が実際にあったのかを判断し項目NO＝-999なら保存しない 2003/05/13追加
    			    if(AnsiString(SetData.KOMK_NO).ToIntDef(0) !=-999)
                    {
	    	    		//KSD02に対し新規追加か更新かをチェックする
    	    	    	sBuf = "SELECT * FROM KSD02";
    			    	sBuf += " WHERE DTKSHIN = '" + sNowDTKSHIN + "'";
    		    		sBuf += " AND   UNQ_NO  = " + AnsiString(iUNQNO) ;
        		    	sBuf += " AND   SKB_NO  IN ( 2 , 3 )";                        //出荷検査項目、材料証明項目
    	    		    sBuf += " AND   LOTNO   = '" + AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].LOTNO) + "'";
    	    		    sBuf += " AND   HINBAN  = '" + AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].HINBAN) + "'";
    			    	// Initial Query
        		    	Query1->Close();
            			Query1->SQL->Clear();
                		Query1->SQL->Add(sBuf);
    		        	Query1->Open();
	    		        Query1->Active = true;

            	        bNEW = false;
	            		if( Query1->Eof == true ) bNEW = true;
	            		Query1->Close();
			        	if( bNEW == true )										//新規登録
				        {
    				        // 測定日(検査中にも測定日は検査毎に書き換えているが、DBへの保存時を時刻とする）
	    				    strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKTYMD,FormatDateTime("yyyymmdd",Date()).c_str());
                            // 登録日
	    		    		strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
                            // 登録時間
    		    			strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
                            // 変更日
		    		    	strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
                            // 変更時間
	    			    	strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
                            // 更新者
	    	    			if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCHR).Trim().Length() == 0)
                            {
    	        	    	    strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCHR,AnsiString(Form1->USER_COD).c_str());
				    	    }
                            // 更新回数
	    				    strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCNT,"0");
                            //セーブ用バッファにコピー
                            // 測定日
				    	    strcpy(SetData.SKTYMD,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKTYMD);
                            // 登録日
					        strcpy(SetData.ADDYMD,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDYMD);
                            // 登録時間
	    				    strcpy(SetData.ADDTIM,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDTIM);
                            // 変更日
			    		    strcpy(SetData.UPDYMD,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDYMD);
                            // 変更時間
					        strcpy(SetData.UPDTIM,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDTIM);
                            // 更新者
	    				    strcpy(SetData.UPDCHR,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCHR);
                            // 更新回数
			    		    strcpy(SetData.UPDCNT,pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCNT);

                            // 問合せ文作成(KSD02)
    				    	sBuf = "insert into KSD02(";
            		        sBuf += " DTKSHIN, LOTNO, HINBAN, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK, KOMK_NO, KOMK_NM,";
                		    sBuf += " KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI,";
	                	    sBuf += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3,";
    	                	sBuf += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3, SOKU_SU, SOKU_FLG,";
	        	            sBuf += " TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI,";
        	            	sBuf += " SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05,";
	        	            sBuf += " SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,";
        	        	    sBuf += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK,";
            	        	sBuf += " DISP_VAL01, DISP_VAL02, DISP_VAL03, DISP_VAL04, DISP_VAL05,";
	                    	sBuf += " DISP_VAL06, DISP_VAL07, DISP_VAL08, DISP_VAL09, DISP_VAL10,";
		                    sBuf += " DISP_VAL_SU, DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, DISP_OK,";
        		            sBuf += " SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
            		        sBuf += " )";
                		    sBuf += " VALUES('";
    		                sBuf += AnsiString(SetData.DTKSHIN)           	+ "','";	//	得意先品番
        		            sBuf += AnsiString(SetData.LOTNO)	       		+ "','";	//	ロットNO
        		            sBuf += AnsiString(SetData.HINBAN)	       		+ "', ";	//	工管発行日 onishi
            		        sBuf += AnsiString(SetData.UNQ_NO)  			+ " , ";	//	明細NO
                    		sBuf += AnsiString(SetData.ORDER_NO)  			+ " , ";	//	明細NO
	                    	sBuf += AnsiString(SetData.SKB_NO)  			+ " ,'";	//	識別NO
	        	            sBuf += AnsiString(SetData.HINBAN_SK) 			+ "', ";
    	        	        sBuf += AnsiString(SetData.KOMK_NO) 			+ " ,'";	//	測定項目NO
    	    	            sBuf += AnsiString(SetData.KOMK_NM)	       		+ "','";	//	測定項目名称
        	    	        sBuf += AnsiString(SetData.KOMK_ENG)       		+ "','";
                	    	sBuf += AnsiString(SetData.KOMK_SUB)	   		+ "','";	//	測定項目名称
	                    	sBuf += AnsiString(SetData.KOMK_SUB_ENG)   		+ "', ";	//	測定項目名称
		                    sBuf += AnsiString(SetData.KIKI_NO) 			+ " ,'";	//	測定機器NO
    		                sBuf += AnsiString(SetData.KIKI_NM)	       		+ "','";	//	測定機器名称
        		            sBuf += AnsiString(SetData.TANI)   	       		+ "', ";	//	単位
                		    sBuf += AnsiString(SetData.KIKA_TYPE)           + " , ";
	        	            sBuf += AnsiString(SetData.KIKA_KIND)           + " , ";
                            sBuf += AnsiString(SetData.KIKA_DECI)           + " , ";
                		    sBuf += AnsiString(SetData.KIKA_NUM1)           + " , ";
                    		sBuf += AnsiString(SetData.KIKA_NUM2)           + " , ";
	                    	sBuf += AnsiString(SetData.KIKA_NUM3)           + " ,'";
	    	                sBuf += AnsiString(SetData.KIKA_STR)            + "','";
        	    	        sBuf += AnsiString(SetData.KIKA_SUB1)           + "','";
            	    	    sBuf += AnsiString(SetData.KIKA_SUB2)           + "','";
    	            	    sBuf += AnsiString(SetData.KIKA_SUB3)           + "', ";
        	            	sBuf += AnsiString(SetData.SOKU_SU) 	        + " , ";	//  測定指示ｎ数
	                	    sBuf += AnsiString(SetData.SOKU_FLG) 	        + " , ";	//  測定指示ｎ数
    	                	sBuf += AnsiString(SetData.TOKU_FLG) 	        + " , ";	//  測定指示ｎ数
	    	                sBuf += AnsiString(SetData.KIKA_PRT) 	        + " , ";	//  測定指示ｎ数
        	    	        sBuf += AnsiString(SetData.VALUE_TYPE)          + " , ";	//  測定指示ｎ数
                	    	sBuf += AnsiString(SetData.VALUE_DECI)          + " ,'";	//  測定指示ｎ数
	                    	sBuf += AnsiString(SetData.SOKU_VAL01)        	+ "','";	//	測定値１
		                    sBuf += AnsiString(SetData.SOKU_VAL02)        	+ "','";	//  測定値２　　　
    		                sBuf += AnsiString(SetData.SOKU_VAL03)        	+ "','";	//	測定値３
        		            sBuf += AnsiString(SetData.SOKU_VAL04)        	+ "','";	//	測定値４
                		    sBuf += AnsiString(SetData.SOKU_VAL05)        	+ "','";	//	測定値５
    	    	            sBuf += AnsiString(SetData.SOKU_VAL06)        	+ "','";	//	測定値６
        	    	        sBuf += AnsiString(SetData.SOKU_VAL07)        	+ "','";	//	測定値７
            	    	    sBuf += AnsiString(SetData.SOKU_VAL08)        	+ "','";	//	測定値８
	            	        sBuf += AnsiString(SetData.SOKU_VAL09)        	+ "','";	//	測定値９
        	            	sBuf += AnsiString(SetData.SOKU_VAL10)        	+ "', ";	//	測定値１０
	            	        sBuf += AnsiString(SetData.SOKU_VAL_SU)         + " , ";	//  測定指示ｎ数
    	            	    sBuf += AnsiString(SetData.SOKU_VAL_AVE)        + " , ";	//  測定指示ｎ数
    	    	            sBuf += AnsiString(SetData.SOKU_VAL_MAX)        + " , ";	//  測定指示ｎ数
        	    	        sBuf += AnsiString(SetData.SOKU_VAL_MIN)        + " , ";	//  測定指示ｎ数
            	    	    sBuf += AnsiString(SetData.SOKU_OK)             + " ,'";	//	測定値１０
    	                	sBuf += AnsiString(SetData.DISP_VAL01)        	+ "','";	//	測定値１
	    	                sBuf += AnsiString(SetData.DISP_VAL02)        	+ "','";	//  測定値２　　　
    	    	            sBuf += AnsiString(SetData.DISP_VAL03)        	+ "','";	//	測定値３
        	    	        sBuf += AnsiString(SetData.DISP_VAL04)        	+ "','";	//	測定値４
                	    	sBuf += AnsiString(SetData.DISP_VAL05)        	+ "','";	//	測定値５
	    	                sBuf += AnsiString(SetData.DISP_VAL06)        	+ "','";	//	測定値６
            		        sBuf += AnsiString(SetData.DISP_VAL07)        	+ "','";	//	測定値７
                		    sBuf += AnsiString(SetData.DISP_VAL08)        	+ "','";	//	測定値８
                    		sBuf += AnsiString(SetData.DISP_VAL09)        	+ "','";	//	測定値９
	                    	sBuf += AnsiString(SetData.DISP_VAL10)        	+ "', ";	//	測定値１０
	    	                sBuf += AnsiString(SetData.DISP_VAL_SU)         + " , ";	//  測定指示ｎ数
            	    	    sBuf += AnsiString(SetData.DISP_VAL_AVE)        + " , ";	//  測定指示ｎ数
                	    	sBuf += AnsiString(SetData.DISP_VAL_MAX)        + " , ";	//  測定指示ｎ数
	                	    sBuf += AnsiString(SetData.DISP_VAL_MIN)        + " , ";	//  測定指示ｎ数
    	                	sBuf += AnsiString(SetData.DISP_OK)             + " ,'";	//	測定値１０
	        	            sBuf += AnsiString(SetData.SKTYMD)   	        + "','";	//	測定日
    	        	        sBuf += AnsiString(SetData.ADDYMD)   	        + "','";	//	登録日
    	    	            sBuf += AnsiString(SetData.ADDTIM)   	        + "','";	//	登録時間
            	    	    sBuf += AnsiString(SetData.UPDYMD)   	        + "','";	//	変更日
                	    	sBuf += AnsiString(SetData.UPDTIM)   	        + "', ";	//	変更時間
	                	    sBuf += AnsiString(SetData.UPDCHR)   	        + " , ";	//	変更時間
    	                	sBuf += AnsiString(SetData.UPDCNT);  	         	        //	更新回数
	    	                sBuf += ")";
    				    }
    	    			else
	    	    		{
                            //更新での登録
                            // 測定日（登録日と同じ)
    			    		strcpy(SetData.SKTYMD,AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SKTYMD).c_str());
                            // 登録日
        					strcpy(SetData.ADDYMD,AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDYMD).c_str());
                            // 登録時間
		    			    strcpy(SetData.ADDTIM,AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].ADDTIM).c_str());
                            // 変更日
				    	    strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
    				    	strcpy(SetData.UPDYMD,AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDYMD).c_str());
                            // 変更時間
	    				    strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
    	    				strcpy(SetData.UPDTIM,AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDTIM).c_str());
                            // 更新者
    			    		if(AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCHR).Length() == 0 )
	    			    	{
    		    				strcpy(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCHR,AnsiString(Form1->USER_COD).c_str());
	    		    		}
		    		    	strcpy(SetData.UPDCHR,AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].UPDCHR).c_str());
                            // 更新回数
				    	    sBuf = "update KSD02 set ";
                            //田村様の指示によりコメント
                            //sBuf += " DTKSHIN = '" 	+ AnsiString(SetData.DTKSHIN) + "',"	;
                            //sBuf += " LOTNO = '" 	+ AnsiString(SetData.LOTNO) + "',"	;
                            //sBuf += " UNQ_NO = " 	+ AnsiString(SetData.UNQ_NO) + ","	;
    		    			sBuf += " ORDER_NO = " + AnsiString(SetData.ORDER_NO) + ","	;
	    		    		sBuf += " SKB_NO = " 	+ AnsiString(SetData.SKB_NO) + ","	;
		    		    	sBuf += " HINBAN_SK = '" + AnsiString(SetData.HINBAN_SK) + "',"	;
			    		    sBuf += " KOMK_NO = " 	+ AnsiString(SetData.KOMK_NO) + ","	;
    				    	sBuf += " KOMK_NM = '" 	+ AnsiString(SetData.KOMK_NM) + "',"	;
            	    	    sBuf += " KOMK_ENG = '" + AnsiString(SetData.KOMK_ENG) + "',"	;
    	    				sBuf += " KOMK_SUB = '" + AnsiString(SetData.KOMK_SUB) + "',"	;
	    	    			sBuf += " KOMK_SUB_ENG = '" + AnsiString(SetData.KOMK_SUB_ENG) + "',"	;
		    	    		sBuf += " KIKI_NO = " 	+ AnsiString(SetData.KIKI_NO) + ","	;
			    	    	sBuf += " KIKI_NM = '" 	+ AnsiString(SetData.KIKI_NM) + "',"	;
				    	    sBuf += " TANI = '" + AnsiString(SetData.TANI) + "',"	;
        		            sBuf += " KIKA_TYPE = " + AnsiString(SetData.KIKA_TYPE) + ","	;
	        				sBuf += " KIKA_KIND = " + AnsiString(SetData.KIKA_KIND) + ","	;
		        			sBuf += " KIKA_DECI = " + AnsiString(SetData.KIKA_DECI) + ","	;
			        		sBuf += " KIKA_NUM1 = " + AnsiString(SetData.KIKA_NUM1) + ","	;
				        	sBuf += " KIKA_NUM2 = " + AnsiString(SetData.KIKA_NUM2) + ","	;
    				    	sBuf += " KIKA_NUM3 = " + AnsiString(SetData.KIKA_NUM3) + ","	;
        		            sBuf += " KIKA_STR = '"  + AnsiString(SetData.KIKA_STR) + "',"	;
    		    			sBuf += " KIKA_SUB1 = '" + AnsiString(SetData.KIKA_SUB1) + "',"	;
	    		    		sBuf += " KIKA_SUB2 = '" + AnsiString(SetData.KIKA_SUB2) + "',"	;
		    		    	sBuf += " KIKA_SUB3 = '" + AnsiString(SetData.KIKA_SUB3) + "',"	;
                            sBuf += " SOKU_SU = "	 + AnsiString(SetData.SOKU_SU) + ","	;
        	                sBuf += " SOKU_FLG = "  + AnsiString(SetData.SOKU_FLG) + ","	;
            		        sBuf += " TOKU_FLG = "  + AnsiString(SetData.TOKU_FLG) + ","	;
		    			    sBuf += " KIKA_PRT = "  + AnsiString(SetData.KIKA_PRT) + ","	;
    			    		sBuf += " VALUE_TYPE = " + AnsiString(SetData.VALUE_TYPE) + ","	;
	    			    	sBuf += " VALUE_DECI = " + AnsiString(SetData.VALUE_DECI) + ","	;
    	            	    sBuf += " SOKU_VAL01 = '" + AnsiString(SetData.SOKU_VAL01) + "',"	;
    		    			sBuf += " SOKU_VAL02 = '" + AnsiString(SetData.SOKU_VAL02) + "',"	;
	    		    		sBuf += " SOKU_VAL03 = '" + AnsiString(SetData.SOKU_VAL03) + "',"	;
		    		    	sBuf += " SOKU_VAL04 = '" + AnsiString(SetData.SOKU_VAL04) + "',"	;
			    		    sBuf += " SOKU_VAL05 = '" + AnsiString(SetData.SOKU_VAL05) + "',"	;
    		                sBuf += " SOKU_VAL06 = '" + AnsiString(SetData.SOKU_VAL06) + "',"	;
	    				    sBuf += " SOKU_VAL07 = '" + AnsiString(SetData.SOKU_VAL07) + "',"	;
    	    				sBuf += " SOKU_VAL08 = '" + AnsiString(SetData.SOKU_VAL08) + "',"	;
	    	    			sBuf += " SOKU_VAL09 = '" + AnsiString(SetData.SOKU_VAL09) + "',"	;
		    	    		sBuf += " SOKU_VAL10 = '" + AnsiString(SetData.SOKU_VAL10) + "',"	;
	    	                sBuf += " SOKU_VAL_SU = "  + AnsiString(SetData.SOKU_VAL_SU) + ","	;
				    	    sBuf += " SOKU_VAL_AVE = " + AnsiString(SetData.SOKU_VAL_AVE) + ","	;
    					    sBuf += " SOKU_VAL_MAX = " + AnsiString(SetData.SOKU_VAL_MAX) + ","	;
        					sBuf += " SOKU_VAL_MIN = " + AnsiString(SetData.SOKU_VAL_MIN) + ","	;
	        				sBuf += " SOKU_OK = " 	  + AnsiString(SetData.SOKU_OK) + ","	;
	                	    sBuf += " DISP_VAL01 = '" + AnsiString(SetData.DISP_VAL01) + "',"	;
			        		sBuf += " DISP_VAL02 = '" + AnsiString(SetData.DISP_VAL02) + "',"	;
				        	sBuf += " DISP_VAL03 = '" + AnsiString(SetData.DISP_VAL03) + "',"	;
					        sBuf += " DISP_VAL04 = '" + AnsiString(SetData.DISP_VAL04) + "',"	;
        					sBuf += " DISP_VAL05 = '" + AnsiString(SetData.DISP_VAL05) + "',"	;
	                    	sBuf += " DISP_VAL06 = '" + AnsiString(SetData.DISP_VAL06) + "',"	;
		        			sBuf += " DISP_VAL07 = '" + AnsiString(SetData.DISP_VAL07) + "',"	;
			        		sBuf += " DISP_VAL08 = '" + AnsiString(SetData.DISP_VAL08) + "',"	;
            	            sBuf += " DISP_VAL09 = '" + AnsiString(SetData.DISP_VAL09) + "',"	;
					        sBuf += " DISP_VAL10 = '" + AnsiString(SetData.DISP_VAL10) + "',"	;
    		                sBuf += " DISP_VAL_SU = "  + AnsiString(SetData.DISP_VAL_SU) + ","	;
    	    				sBuf += " DISP_VAL_AVE = " + AnsiString(SetData.DISP_VAL_AVE) + ","	;
	    	    			sBuf += " DISP_VAL_MAX = " + AnsiString(SetData.DISP_VAL_MAX) + ","	;
		    	    		sBuf += " DISP_VAL_MIN = " + AnsiString(SetData.DISP_VAL_MIN) + ","	;
			    	    	sBuf += " DISP_OK = " + AnsiString(SetData.DISP_OK) + ","	;
	    	                sBuf += " SKTYMD = '" + AnsiString(SetData.SKTYMD) + "',"	;
    				    	sBuf += " ADDYMD = '" + AnsiString(SetData.ADDYMD) + "',"	;
	    				    sBuf += " ADDTIM = '" + AnsiString(SetData.ADDTIM) + "',"	;
    		    			sBuf += " UPDYMD = '" + AnsiString(SetData.UPDYMD) + "',"	;
	    		    		sBuf += " UPDTIM = '" + AnsiString(SetData.UPDTIM) + "',"	;
		    		    	sBuf += " UPDCHR = " + AnsiString(SetData.UPDCHR) + ","	;
			    		    sBuf += " UPDCNT = " + AnsiString(SetData.UPDCNT) + " "	;
         		    		sBuf += " WHERE DTKSHIN='" 	+ AnsiString(SetData.DTKSHIN) + "'";
         			    	sBuf += " AND   LOTNO  ='" 	+ AnsiString(SetData.LOTNO)   + "'";
         			    	sBuf += " AND   HINBAN ='" 	+ AnsiString(SetData.HINBAN)  + "'";
     	    			    sBuf += " AND   UNQ_NO = " 	+ AnsiString(SetData.UNQ_NO) ;
    			    	}
        			    //For Debug
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
    			        // 問い合せ文の実行
            	    	try{
                	    	Query1->ExecSQL();
                    	}
	                    catch(EDatabaseError& e)
        	            {
            	        	SBr1->Panels->Items[0]->Text = e.Message;
                	        SBr1->Update();
                        	return(false);
	                    }
            	        catch(Exception& e)
                	    {
                    		SBr1->Panels->Items[0]->Text = e.Message;
                        	SBr1->Update();
	                        return(false);
            	        }
                    }
		    	}
                iRow +=  AnsiString(pCELLINFO_SOKU_SYUKA[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);
    		}
        }
	}
    Query1->Close();
	// メモリの開放
    if( hSetJissekiData ){
    	GlobalUnlock( hSetJissekiData );
        //20170509 Y.Onishi
        //Memory Address '00000032'時にコケる不具合を修正
        //GlobalFree( hSetJissekiData );
    }
	hSetJissekiData = NULL;
    return(true);
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
//測定実績データの新規登録＆更新（対象データベースはKSD001&KSD002、対照データは測定履歴）
//---------------------------------------------------------------------------
bool __fastcall TForm1::Set_DB_RIRE(void)
{
    int i1,i2,i3,i4;
    int iUNQNO;
    int iKIKA_KIND;
    //セーブ時使用変数一覧
	int iRow,iCol;
	int iRowCount;
    int iSOKUSU;
	int VALUE_TYPE;
	int SOKU_VAL_SU,DISP_VAL_SU;
	int iSOKU_VAL_SU,iDISP_VAL_SU;
    int iSIJI_NSU;
    AnsiString RESULT_BUF,DISP_RESULT_BUF,sMEMO;
	double SOKU_VAL_AVE,SOKU_VAL_MAX,SOKU_VAL_MIN;
	double DISP_VAL_AVE,DISP_VAL_MAX,DISP_VAL_MIN;
	double RESULT,GOUKEI_RESULT,DISP_RESULT,DISP_GOUKEI_RESULT;
    double SOKU_MAX,SOKU_MIN;
    double DISP_MAX,DISP_MIN;
    int iRESULT,iDISP_RESULT;
    int iOK_FLG,iDISP_OK_FLG;
	bool FIRST_FLG,DISP_FIRST_FLG;
	bool bNEW;						//新規追加フラグ
	HANDLE hSetJissekiData;
	KSD01_DATA  *pSetJissekiData;
	bool bHANTEI,bDISP_HANTEI;					//前詰フラグ
    bool bRtn;				//2003.05.08 E.Takase Add
    AnsiString sBufConv;	//2003.05.08 E.Takase Add


	TMsgDlgButtons MsgButton;


    AnsiString sBuf,sLot,sTempBuf;
    KSD02_DATA SetData;

	if(!hCELLINFO_RIRE_SYUKA) return(true);
	if(SGr_tRIRE->Cells[0][0].Length() == 0 ) return(true);
    if(Form1->iRIRE_CNT == 0 ) return(true);

    //出荷検査
    //KSD01の更新
	// メモリの開放
    if( hSetJissekiData ){
    	GlobalUnlock( hSetJissekiData );
        //20170509 Y.Onishi
        //Memory Address '00000032'時にコケる不具合を修正
        //GlobalFree( hSetJissekiData );
    }
	hSetJissekiData = NULL;

    // メモリの確保
    hSetJissekiData = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * ((SGr_vRIRE_SYUKA->ColCount+1)));
    if( hSetJissekiData == NULL ){
    	SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル01)";
        SBr1->Update();
        Beep();
        return(false);
    }
    pSetJissekiData = (struct KSD01_DATA *)GlobalLock(hSetJissekiData);
    if( hSetJissekiData == NULL ){
    	SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(出荷履歴セル02)";
        SBr1->Update();
        Beep();
        return(false);
    }

    for(i2 = 0;i2 < SGr_vRIRE_SYUKA->ColCount;i2++)
    {
    	strcpy(pSetJissekiData[0].DTKSHIN       ,sNowDTKSHIN.c_str());
        strcpy(pSetJissekiData[0].LOTNO         ,SGr_tRIRE->Cells[i2][0].c_str());
        strcpy(pSetJissekiData[0].HINBAN        ,SGr_tRIRE->Cells[i2][1].c_str());                     //onishi
		strcpy(pSetJissekiData[0].LOTNO1_SZ     ,pRIRE_KSD01_DATA[i2].LOTNO1_SZ);
		strcpy(pSetJissekiData[0].LOTNO2_SZ     ,pRIRE_KSD01_DATA[i2].LOTNO2_SZ);
		strcpy(pSetJissekiData[0].LOTNO3_SZ     ,pRIRE_KSD01_DATA[i2].LOTNO3_SZ);
		strcpy(pSetJissekiData[0].LOTNO4_SZ     ,pRIRE_KSD01_DATA[i2].LOTNO4_SZ);
		strcpy(pSetJissekiData[0].LOTNO5_SZ     ,pRIRE_KSD01_DATA[i2].LOTNO5_SZ);
		strcpy(pSetJissekiData[0].LOTNO6_SZ     ,pRIRE_KSD01_DATA[i2].LOTNO6_SZ);

		strcpy(pSetJissekiData[0].HINBAN1_SZ     ,pRIRE_KSD01_DATA[i2].HINBAN1_SZ);
		strcpy(pSetJissekiData[0].HINBAN2_SZ     ,pRIRE_KSD01_DATA[i2].HINBAN2_SZ);
		strcpy(pSetJissekiData[0].HINBAN3_SZ     ,pRIRE_KSD01_DATA[i2].HINBAN3_SZ);
		strcpy(pSetJissekiData[0].HINBAN4_SZ     ,pRIRE_KSD01_DATA[i2].HINBAN4_SZ);
		strcpy(pSetJissekiData[0].HINBAN5_SZ     ,pRIRE_KSD01_DATA[i2].HINBAN5_SZ);
		strcpy(pSetJissekiData[0].HINBAN6_SZ     ,pRIRE_KSD01_DATA[i2].HINBAN6_SZ);

		strcpy(pSetJissekiData[0].DTKSCOD	    ,pRIRE_KSD01_DATA[i2].DTKSCOD);
		strcpy(pSetJissekiData[0].DTKSNAM	    ,pRIRE_KSD01_DATA[i2].DTKSNAM);
		strcpy(pSetJissekiData[0].ZISNAM	    ,pRIRE_KSD01_DATA[i2].ZISNAM);
		strcpy(pSetJissekiData[0].HINMEI	    ,pRIRE_KSD01_DATA[i2].HINMEI);

		strcpy(pSetJissekiData[0].DTKSHIN1_SZ   ,pRIRE_KSD01_DATA[i2].DTKSHIN1_SZ);
		strcpy(pSetJissekiData[0].DTKSHIN2_SZ   ,pRIRE_KSD01_DATA[i2].DTKSHIN2_SZ);
		strcpy(pSetJissekiData[0].DTKSHIN3_SZ   ,pRIRE_KSD01_DATA[i2].DTKSHIN3_SZ);
		strcpy(pSetJissekiData[0].DTKSHIN4_SZ   ,pRIRE_KSD01_DATA[i2].DTKSHIN4_SZ);
		strcpy(pSetJissekiData[0].DTKSHIN5_SZ   ,pRIRE_KSD01_DATA[i2].DTKSHIN5_SZ);
		strcpy(pSetJissekiData[0].DTKSHIN6_SZ   ,pRIRE_KSD01_DATA[i2].DTKSHIN6_SZ);

		strcpy(pSetJissekiData[0].LOT_LINK_SZ 	,pRIRE_KSD01_DATA[i2].LOT_LINK_SZ);
		strcpy(pSetJissekiData[0].SOKUTEI_NUM 	,pRIRE_KSD01_DATA[i2].SOKUTEI_NUM);
		strcpy(pSetJissekiData[0].SOZAI_OK	 	,pRIRE_KSD01_DATA[i2].SOZAI_OK);
		strcpy(pSetJissekiData[0].SOZAI_OK_PRT	,pRIRE_KSD01_DATA[i2].SOZAI_OK_PRT);
		strcpy(pSetJissekiData[0].SYUKA_OK	 	,pRIRE_KSD01_DATA[i2].SYUKA_OK);
		strcpy(pSetJissekiData[0].SYUKA_OK_PRT	,pRIRE_KSD01_DATA[i2].SYUKA_OK_PRT);

		strcpy(pSetJissekiData[0].OUT_TITLE1	,pRIRE_KSD01_DATA[i2].OUT_TITLE1);
		strcpy(pSetJissekiData[0].OUT_TITLE2	,pRIRE_KSD01_DATA[i2].OUT_TITLE2);
		strcpy(pSetJissekiData[0].OUT_TITLE3	,pRIRE_KSD01_DATA[i2].OUT_TITLE3);
		strcpy(pSetJissekiData[0].OUT_TITLE4	,pRIRE_KSD01_DATA[i2].OUT_TITLE4);
		strcpy(pSetJissekiData[0].OUT_TITLE5	,pRIRE_KSD01_DATA[i2].OUT_TITLE5);
		strcpy(pSetJissekiData[0].OUT_TITLE6	,pRIRE_KSD01_DATA[i2].OUT_TITLE6);
		strcpy(pSetJissekiData[0].OUT_TITLE7	,pRIRE_KSD01_DATA[i2].OUT_TITLE7);
		strcpy(pSetJissekiData[0].OUT_TITLE8	,pRIRE_KSD01_DATA[i2].OUT_TITLE8);

		strcpy(pSetJissekiData[0].X_OUT			,pRIRE_KSD01_DATA[i2].X_OUT);
		sMEMO = GetValidityData(Form1->Mem_vRIRE_MEMO[i2]->Text,128);
		if(sMEMO.Length() == 0 ) sMEMO = " ";
		strcpy(pSetJissekiData[0].MEMO			,sMEMO.c_str());
		if(pRIRE_KSD01_DATA[i2].UPD_FLG == false)
		{
		}
		else
		{
	        //KSD01に対し新規追加か更新かをチェックする
        	sBuf = "SELECT * FROM KSD01";
           	sBuf += " WHERE DTKSHIN = '" + AnsiString(pSetJissekiData[0].DTKSHIN) 	+ "'";
            sBuf += " AND   LOTNO 	= '" + AnsiString(pSetJissekiData[0].LOTNO) 	+ "'";
            sBuf += " AND   HINBAN 	= '" + AnsiString(pSetJissekiData[0].HINBAN) 	+ "'";

            // Initial Query
           	Query2->Close();
            Query2->SQL->Clear();
            Query2->SQL->Add(sBuf);
           	Query2->Open();
	        Query2->Active = true;
    	    bNEW = false;
           	if( Query2->Eof == true ) bNEW = true;
            Query2->Close();
    	    if(bNEW == true )
    	   	{
                //時間データを取得する
		    	if(AnsiString(pRIRE_KSD01_DATA[i2].SKTYMD_SZ).Trim().Length() == 0)
		   	    {
		  		    strcpy(pRIRE_KSD01_DATA[i2].SKTYMD_SZ		,FormatDateTime("yyyymmdd",Date()).c_str());			//測定日
               	}
	    		if(AnsiString(pRIRE_KSD01_DATA[i2].SKTYMD_SZ_PRT).Trim().Length() == 0)
	   	    	{
	  		    	strcpy(pRIRE_KSD01_DATA[i2].SKTYMD_SZ_PRT	,FormatDateTime("yyyymmdd",Date()).c_str()); 			//測定日印刷用
    	 		}
	    		if(AnsiString(pRIRE_KSD01_DATA[i2].SKTYMD).Trim().Length() == 0)
   		    	{
  			    	strcpy(pRIRE_KSD01_DATA[i2].SKTYMD			,FormatDateTime("yyyymmdd",Date()).c_str());			//測定日
               	}
	    		if(AnsiString(pRIRE_KSD01_DATA[i2].SKTYMD_PRT).Trim().Length() == 0)
		    	{
			    	strcpy(pRIRE_KSD01_DATA[i2].SKTYMD_PRT		,FormatDateTime("yyyymmdd",Date()).c_str()); 			//測定日印刷用
    			}
	    		if(AnsiString(pRIRE_KSD01_DATA[i2].ADDYMD).Trim().Length() == 0)
		    	{
			    	strcpy(pRIRE_KSD01_DATA[i2].ADDYMD			,FormatDateTime("yyyymmdd",Date()).c_str());			//代表登録日
                }
	    		if(AnsiString(pRIRE_KSD01_DATA[i2].ADDTIM).Trim().Length() == 0)
		    	{
			    	strcpy(pRIRE_KSD01_DATA[i2].ADDTIM			,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());  	//代表登録時間
                }
	    		strcpy(pRIRE_KSD01_DATA[i2].UPDYMD		,FormatDateTime("yyyymmdd",Date()).c_str()); 			    //代表変更日
		    	strcpy(pRIRE_KSD01_DATA[i2].UPDTIM		,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str()); 	//代表変更時間
			    strcpy(pRIRE_KSD01_DATA[i2].UPDCNT      ,"0");														//代表更新回数
    			strcpy(pSetJissekiData[0].SKTYMD		,pRIRE_KSD01_DATA[i2].SKTYMD);
	    		strcpy(pSetJissekiData[0].SKTYMD_PRT	,pRIRE_KSD01_DATA[i2].SKTYMD_PRT);
		    	strcpy(pSetJissekiData[0].ADDYMD		,pRIRE_KSD01_DATA[i2].ADDYMD);
			    strcpy(pSetJissekiData[0].ADDTIM		,pRIRE_KSD01_DATA[i2].ADDTIM);
    			strcpy(pSetJissekiData[0].UPDYMD		,pRIRE_KSD01_DATA[i2].UPDYMD);
	    		strcpy(pSetJissekiData[0].UPDTIM		,pRIRE_KSD01_DATA[i2].UPDTIM);
		    	strcpy(pSetJissekiData[0].UPDCHR		,pRIRE_KSD01_DATA[i2].UPDCHR);
			    strcpy(pSetJissekiData[0].UPDCNT		,pRIRE_KSD01_DATA[i2].UPDCNT);

                ///////////////////////
        	    sBuf = "insert into KSD01(";
            	sBuf += " DTKSHIN, LOTNO, HINBAN,";
		    	sBuf += " LOTNO1_SZ, LOTNO2_SZ, LOTNO3_SZ, LOTNO4_SZ, LOTNO5_SZ, LOTNO6_SZ,";
		    	sBuf += " HINBAN1_SZ, HINBAN2_SZ, HINBAN3_SZ, HINBAN4_SZ, HINBAN5_SZ, HINBAN6_SZ,";
			    sBuf += " DTKSCOD, DTKSNAM, ZISNAM, HINMEI,";
    			sBuf += " DTKSHIN1_SZ, DTKSHIN2_SZ, DTKSHIN3_SZ,";
	    		sBuf += " DTKSHIN4_SZ, DTKSHIN5_SZ, DTKSHIN6_SZ,";
		    	sBuf += " LOT_LINK_SZ, SOKUTEI_NUM, SOZAI_OK, SOZAI_OK_PRT,";
			    sBuf += " SYUKA_OK, SYUKA_OK_PRT,";
    			sBuf += " OUT_TITLE1, OUT_TITLE2, OUT_TITLE3, OUT_TITLE4,";
	    		sBuf += " OUT_TITLE5, OUT_TITLE6, OUT_TITLE7, OUT_TITLE8,";
		    	sBuf += " X_OUT, MEMO,";
	            sBuf += " SKTYMD_SZ, SKTYMD_SZ_PRT, SKTYMD, SKTYMD_PRT,ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
        	    sBuf += " )";
            	sBuf += " VALUES('";
	            sBuf += AnsiString(pSetJissekiData[0].DTKSHIN)		+ "','";	//	得意先品番
    	        sBuf += AnsiString(pSetJissekiData[0].LOTNO)		+ "','";	//	ロットNO
    	        sBuf += AnsiString(pSetJissekiData[0].HINBAN)		+ "','";	//	工管発行日 onishi
    			sBuf += AnsiString(pSetJissekiData[0].LOTNO1_SZ) 	+ "','";
	    		sBuf += AnsiString(pSetJissekiData[0].LOTNO2_SZ) 	+ "','";
		    	sBuf += AnsiString(pSetJissekiData[0].LOTNO3_SZ) 	+ "','";
			    sBuf += AnsiString(pSetJissekiData[0].LOTNO4_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].LOTNO5_SZ) 	+ "','";
	    		sBuf += AnsiString(pSetJissekiData[0].LOTNO6_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN1_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN2_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN3_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN4_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN5_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].HINBAN6_SZ) 	+ "','";
			    sBuf += AnsiString(pSetJissekiData[0].DTKSCOD) 		+ "','";
     			sBuf += AnsiString(pSetJissekiData[0].DTKSNAM) 		+ "','";
	    		sBuf += AnsiString(pSetJissekiData[0].ZISNAM) 		+ "','";
		    	sBuf += AnsiString(pSetJissekiData[0].HINMEI) 		+ "','";
			    sBuf += AnsiString(pSetJissekiData[0].DTKSHIN1_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].DTKSHIN2_SZ) 	+ "','";
	    		sBuf += AnsiString(pSetJissekiData[0].DTKSHIN3_SZ) 	+ "','";
		    	sBuf += AnsiString(pSetJissekiData[0].DTKSHIN4_SZ) 	+ "','";
			    sBuf += AnsiString(pSetJissekiData[0].DTKSHIN5_SZ) 	+ "','";
    			sBuf += AnsiString(pSetJissekiData[0].DTKSHIN6_SZ) 	+ "', ";
	    		sBuf += AnsiString(pSetJissekiData[0].LOT_LINK_SZ) 	+ " , ";
		    	sBuf += AnsiString(pSetJissekiData[0].SOKUTEI_NUM) 	+ " , ";
			    sBuf += AnsiString(pSetJissekiData[0].SOZAI_OK) 	+ " , ";
    			sBuf += AnsiString(pSetJissekiData[0].SOZAI_OK_PRT) + " , ";
	    		sBuf += AnsiString(pSetJissekiData[0].SYUKA_OK) 	+ " , ";
		    	sBuf += AnsiString(pSetJissekiData[0].SYUKA_OK_PRT) + " , ";
			    sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE1) 	+ " , ";
    			sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE2) 	+ " , ";
	    		sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE3) 	+ " , ";
		    	sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE4) 	+ " , ";
			    sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE5) 	+ " , ";
    			sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE6) 	+ " , ";
	    		sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE7) 	+ " , ";
		    	sBuf += AnsiString(pSetJissekiData[0].OUT_TITLE8) 	+ " , ";
			    sBuf += AnsiString(pSetJissekiData[0].X_OUT) 	 	+ " ,'";
    			sBuf += AnsiString(pSetJissekiData[0].MEMO) 		+ "','";
	            sBuf += AnsiString(pSetJissekiData[0].SKTYMD_SZ)  	+ "','";	//	測定日
    	        sBuf += AnsiString(pSetJissekiData[0].SKTYMD_SZ_PRT)+ "','";	//	測定日
	            sBuf += AnsiString(pSetJissekiData[0].SKTYMD)  		+ "','";	//	測定日
        	    sBuf += AnsiString(pSetJissekiData[0].SKTYMD_PRT)  	+ "','";	//	測定日
            	sBuf += AnsiString(pSetJissekiData[0].ADDYMD)  		+ "','";	//	登録日
	            sBuf += AnsiString(pSetJissekiData[0].ADDTIM)  		+ "','";	//	登録時間
    	        sBuf += AnsiString(pSetJissekiData[0].UPDYMD)  		+ "','";	//	変更日
            	sBuf += AnsiString(pSetJissekiData[0].UPDTIM)  		+ "', " ;	//	変更時間
	    		if(AnsiString(pSetJissekiData[0].UPDTIM).Trim().Length() == 0){
    	        	strcpy(pSetJissekiData[0].UPDCHR,AnsiString(Form1->USER_COD).c_str());
			    }
    	        sBuf += AnsiString(pSetJissekiData[0].UPDCHR)  		+ " , " ;	//	更新者
        	    sBuf += AnsiString(pSetJissekiData[0].UPDCNT);  				//	更新回数
            	sBuf += ")";
    		}
	    	else
		    {
    		    //時間データを取得する
	    		if(AnsiString(pRIRE_KSD01_DATA[i2].SKTYMD_SZ).Trim().Length() == 0)
		    	{
			    	strcpy(pRIRE_KSD01_DATA[i2].SKTYMD_SZ		,FormatDateTime("yyyymmdd",Date()).c_str());			//測定日
                }
	    		if(AnsiString(pRIRE_KSD01_DATA[i2].SKTYMD_SZ_PRT).Trim().Length() == 0)
		    	{
			    	strcpy(pRIRE_KSD01_DATA[i2].SKTYMD_SZ_PRT	,FormatDateTime("yyyymmdd",Date()).c_str()); 			//測定日印刷用
    			}
	    		if(AnsiString(pRIRE_KSD01_DATA[i2].SKTYMD).Trim().Length() == 0)
		    	{
			    	strcpy(pRIRE_KSD01_DATA[i2].SKTYMD			,FormatDateTime("yyyymmdd",Date()).c_str());			//測定日
                }
	    		if(AnsiString(pRIRE_KSD01_DATA[i2].SKTYMD_PRT).Trim().Length() == 0)
		    	{
			    	strcpy(pRIRE_KSD01_DATA[i2].SKTYMD_PRT		,FormatDateTime("yyyymmdd",Date()).c_str()); 			//測定日印刷用
    			}
	    		if(AnsiString(pRIRE_KSD01_DATA[i2].ADDYMD).Trim().Length() == 0)
		    	{
			    	strcpy(pRIRE_KSD01_DATA[i2].ADDYMD			,FormatDateTime("yyyymmdd",Date()).c_str());			//代表登録日
                }
	    		if(AnsiString(pRIRE_KSD01_DATA[i2].ADDTIM).Trim().Length() == 0)
		    	{
			    	strcpy(pRIRE_KSD01_DATA[i2].ADDTIM			,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());  	//代表登録時間
                }
                // 変更日
    			strcpy(pRIRE_KSD01_DATA[i2].UPDYMD	,FormatDateTime("yyyymmdd",Date()).c_str());
	    	    // 変更時間
		    	strcpy(pRIRE_KSD01_DATA[i2].UPDTIM	,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
    		    // 更新回数
	    		i1 = AnsiString(pRIRE_KSD01_DATA[i2].UPDCNT).ToIntDef(0);
                i1 ++;
			    strcpy(pRIRE_KSD01_DATA[i2].UPDCNT	    ,AnsiString(i1).c_str());
     			strcpy(pSetJissekiData[0].SKTYMD_SZ		,pRIRE_KSD01_DATA[i2].SKTYMD_SZ);
	    		strcpy(pSetJissekiData[0].SKTYMD_SZ_PRT	,pRIRE_KSD01_DATA[i2].SKTYMD_SZ_PRT);
		    	strcpy(pSetJissekiData[0].SKTYMD		,pRIRE_KSD01_DATA[i2].SKTYMD);
			    strcpy(pSetJissekiData[0].SKTYMD_PRT	,pRIRE_KSD01_DATA[i2].SKTYMD_PRT);
    			strcpy(pSetJissekiData[0].ADDYMD		,pRIRE_KSD01_DATA[i2].ADDYMD);
	    		strcpy(pSetJissekiData[0].ADDTIM		,pRIRE_KSD01_DATA[i2].ADDTIM);
		    	strcpy(pSetJissekiData[0].UPDYMD		,pRIRE_KSD01_DATA[i2].UPDYMD);
			    strcpy(pSetJissekiData[0].UPDTIM		,pRIRE_KSD01_DATA[i2].UPDTIM);
    			strcpy(pSetJissekiData[0].UPDCHR		,pRIRE_KSD01_DATA[i2].UPDCHR);
	    		strcpy(pSetJissekiData[0].UPDCNT		,pRIRE_KSD01_DATA[i2].UPDCNT);

                // 問合せ文作成
     	    	sBuf = "update KSD01 set ";
        	    //sBuf += " DTKSHIN ='" 		+ AnsiString(pSetJissekiData[0].DTKSHIN)	   + "',";	//	得意先品番
    			//sBuf += " LOTNO ='" 		+ AnsiString(pSetJissekiData[0].LOTNO)	   	   + "',";	//	得意先品番
    			//sBuf += " HINBAN ='" 		+ AnsiString(pSetJissekiData[0].HINBAN)	   	   + "',";	//	工管発行日 onishi
	    		sBuf += " LOTNO1_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO1_SZ)	   + "',";
		    	sBuf += " LOTNO2_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO2_SZ)	   + "',";
			    sBuf += " LOTNO3_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO3_SZ)	   + "',";
    			sBuf += " LOTNO4_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO4_SZ)	   + "',";
	    		sBuf += " LOTNO5_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO5_SZ)	   + "',";
		    	sBuf += " LOTNO6_SZ ='" 	+ AnsiString(pSetJissekiData[0].LOTNO6_SZ)	   + "',";
	    		sBuf += " HINBAN1_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN1_SZ)	   + "',";
	    		sBuf += " HINBAN2_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN2_SZ)	   + "',";
	    		sBuf += " HINBAN3_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN3_SZ)	   + "',";
	    		sBuf += " HINBAN4_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN4_SZ)	   + "',";
	    		sBuf += " HINBAN5_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN5_SZ)	   + "',";
	    		sBuf += " HINBAN6_SZ ='" 	+ AnsiString(pSetJissekiData[0].HINBAN6_SZ)	   + "',";
    			sBuf += " DTKSCOD ='"		+ AnsiString(pSetJissekiData[0].DTKSCOD)	   + "',";
	    		sBuf += " DTKSNAM ='" 		+ AnsiString(pSetJissekiData[0].DTKSNAM)	   + "',";
		    	sBuf += " ZISNAM ='" 		+ AnsiString(pSetJissekiData[0].ZISNAM)	   	   + "',";
			    sBuf += " HINMEI ='" 		+ AnsiString(pSetJissekiData[0].HINMEI)	   	   + "',";
    			sBuf += " DTKSHIN1_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN1_SZ)   + "',";
	    		sBuf += " DTKSHIN2_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN2_SZ)   + "',";
		    	sBuf += " DTKSHIN3_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN3_SZ)   + "',";	//	得意先品番
			    sBuf += " DTKSHIN4_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN4_SZ)   + "',";	//	得意先品番
    			sBuf += " DTKSHIN5_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN5_SZ)   + "',";	//	得意先品番
                sBuf += " DTKSHIN6_SZ ='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN6_SZ)   + "',";	//	得意先品番
		    	sBuf += " LOT_LINK_SZ =" 	+ AnsiString(pSetJissekiData[0].LOT_LINK_SZ)   + ",";	//	得意先品番
			    sBuf += " SOKUTEI_NUM =" 	+ AnsiString(pSetJissekiData[0].SOKUTEI_NUM)   + ",";	//	得意先品番
    			sBuf += " SOZAI_OK ="	 	+ AnsiString(pSetJissekiData[0].SOZAI_OK)	   + ",";	//	得意先品番
	    		sBuf += " SOZAI_OK_PRT ="	+ AnsiString(pSetJissekiData[0].SOZAI_OK_PRT)  + ",";	//	得意先品番
		    	sBuf += " SYUKA_OK =" 		+ AnsiString(pSetJissekiData[0].SYUKA_OK)	   + ",";	//	得意先品番
			    sBuf += " SYUKA_OK_PRT =" 	+ AnsiString(pSetJissekiData[0].SYUKA_OK_PRT)  + ",";	//	得意先品番
    			sBuf += " OUT_TITLE1 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE1)	   + ",";	//	得意先品番
	    		sBuf += " OUT_TITLE2 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE2)	   + ",";	//	得意先品番
		    	sBuf += " OUT_TITLE3 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE3)	   + ",";	//	得意先品番
			    sBuf += " OUT_TITLE4 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE4)	   + ",";	//	得意先品番
    			sBuf += " OUT_TITLE5 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE5)	   + ",";	//	得意先品番
	    		sBuf += " OUT_TITLE6 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE6)	   + ",";	//	得意先品番
		    	sBuf += " OUT_TITLE7 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE7)	   + ",";	//	得意先品番
			    sBuf += " OUT_TITLE8 =" 	+ AnsiString(pSetJissekiData[0].OUT_TITLE8)	   + ",";	//	得意先品番
    			sBuf += " X_OUT =" 			+ AnsiString(pSetJissekiData[0].X_OUT)	   	   + ",";	//	得意先品番
	    		sBuf += " MEMO ='" 			+ AnsiString(pSetJissekiData[0].MEMO)	   	   + "',";	//	得意先品番
	            sBuf += " SKTYMD_SZ ='" 	+ AnsiString(pSetJissekiData[0].SKTYMD_SZ)	   + "',";	//	得意先品番
			    sBuf += " SKTYMD_SZ_PRT ='"	+ AnsiString(pSetJissekiData[0].SKTYMD_SZ_PRT) + "',";	//	得意先品番
    	        sBuf += " SKTYMD ='" 		+ AnsiString(pSetJissekiData[0].SKTYMD)	   	   + "',";	//	得意先品番
	    		sBuf += " SKTYMD_PRT ='"	+ AnsiString(pSetJissekiData[0].SKTYMD_PRT)	   + "',";	//	得意先品番
		    	sBuf += " ADDYMD ='" 		+ AnsiString(pSetJissekiData[0].ADDYMD)	   	   + "',";	//	得意先品番
			    sBuf += " ADDTIM ='" 		+ AnsiString(pSetJissekiData[0].ADDTIM)	   	   + "',";	//	得意先品番
    			sBuf += " UPDYMD ='" 		+ AnsiString(pSetJissekiData[0].UPDYMD)	   	   + "',";	//	得意先品番
	    		sBuf += " UPDTIM ='" 		+ AnsiString(pSetJissekiData[0].UPDTIM)	   	   + "',";	//	得意先品番
		    	sBuf += " UPDCHR =" 		+ AnsiString(pSetJissekiData[0].UPDCHR)	   	   + ",";	//	得意先品番
			    sBuf += " UPDCNT =" 		+ AnsiString(pSetJissekiData[0].UPDCNT)	   	   + " ";	//	得意先品番
         		sBuf += " WHERE DTKSHIN='" 	+ AnsiString(pSetJissekiData[0].DTKSHIN)       + "'";
         		sBuf += " AND   LOTNO  ='" 	+ AnsiString(pSetJissekiData[0].LOTNO)         + "'";
         		sBuf += " AND   HINBAN ='" 	+ AnsiString(pSetJissekiData[0].HINBAN)        + "'";         //onishi
 		    }
            //For Debug
            if( iDEBUG == 1 )
            {
         	    ClpBrd = Clipboard();
         	    ClpBrd->Open();
     	        ClpBrd->SetTextBuf(sBuf.c_str());
         	    ClpBrd->Close();
            }
            // Initial Query
		    Query2->Close();
            Query2->SQL->Clear();
            Query2->SQL->Add(sBuf);
            // 問い合せ文の実行
		    try
            {
        	    Query2->ExecSQL();
            }
            catch(EDatabaseError& e)
            {
        	    SBr1->Panels->Items[0]->Text = e.Message;
                SBr1->Update();
                return(false);
            }
            catch(Exception& e)
            {
            	SBr1->Panels->Items[0]->Text = e.Message;
                SBr1->Update();
                return(false);
            }
		}
    }

    //KSD02の更新(新規登録の場合)

	iRowCount = SGr_vRIRE_SYUKA->RowCount;
    if( iRowCount < 2 ) return(true);         //出荷データがない
	for(iCol = 0; iCol < SGr_vRIRE_SYUKA->ColCount;iCol++)
	{
    	if(pRIRE_KSD01_DATA[iCol].UPD_FLG == false)
		{
		}
		else
        {
		    for( iRow = 1;iRow < iRowCount; iRow=iRow)
		    {
                //実際の指示数を検出します
                iSIJI_NSU = 0;
                for(i3=0; i3 < AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);i3++)
                {
                    if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].KOMK_NO).ToIntDef(0) == -999) break;
                    iSIJI_NSU ++;
                }
                iSOKUSU=iSIJI_NSU;
                //KSD03（例外データ）削除
                sBuf = "";
                sBuf = "DELETE FROM KSD03";
                sBuf +=	" where DTKSHIN='" + AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].DTKSHIN) + "'";
                sBuf += " and   LOTNO  ='" + AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].LOTNO)   + "'";
                sBuf += " and   HINBAN ='" + AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].HINBAN)  + "'";
                sBuf += " and   UNQ_NO = " + AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UNQ_NO);
                //For Debug
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
                // 問い合せ文の実行
                try{
                    Query1->ExecSQL();
                }
                catch(EDatabaseError& e)
                {
                    SBr1->Panels->Items[0]->Text = e.Message;
                    SBr1->Update();
                    return(false);
                }
                catch(Exception& e)
                {
                    SBr1->Panels->Items[0]->Text = e.Message;
                    SBr1->Update();
                    return(false);
                }
                ///////////////////////////////////////////////
    			iSOKUSU 	= AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);
	    		VALUE_TYPE 	= AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0);
		    	iUNQNO 		= AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UNQ_NO).ToIntDef(0);
			    SOKU_VAL_SU = 0;
    			DISP_VAL_SU = 0;
	    		iSOKU_VAL_SU = 0;
		    	iDISP_VAL_SU = 0;
                GOUKEI_RESULT = 0;
                DISP_GOUKEI_RESULT = 0;
	    		SOKU_MAX = 0.0;
		    	DISP_MAX = 0.0;
			    SOKU_MIN = 0.0;
    			DISP_MIN = 0.0;
	    		SOKU_VAL_MAX = 0;
		    	SOKU_VAL_MIN = 0;
			    DISP_VAL_MAX = 0;
    			DISP_VAL_MIN = 0;
                iOK_FLG = 2;
                iDISP_OK_FLG = 2;
			    FIRST_FLG 	= true;
    			DISP_FIRST_FLG = true;
	    		RESULT = 0;
		    	DISP_RESULT = 0;
                //測定値初期化
    			strcpy(SetData.SOKU_VAL01 , "");
	    		strcpy(SetData.SOKU_VAL02 , "");
		    	strcpy(SetData.SOKU_VAL03 , "");
			    strcpy(SetData.SOKU_VAL04 , "");
    			strcpy(SetData.SOKU_VAL05 , "");
	    		strcpy(SetData.SOKU_VAL06 , "");
		    	strcpy(SetData.SOKU_VAL07 , "");
			    strcpy(SetData.SOKU_VAL08 , "");
	    		strcpy(SetData.SOKU_VAL09 , "");
    			strcpy(SetData.SOKU_VAL10 , "");
                //印刷値初期化
    			strcpy(SetData.DISP_VAL01 , "");
	    		strcpy(SetData.DISP_VAL02 , "");
		    	strcpy(SetData.DISP_VAL03 , "");
			    strcpy(SetData.DISP_VAL04 , "");
    			strcpy(SetData.DISP_VAL05 , "");
	    		strcpy(SetData.DISP_VAL06 , "");
		    	strcpy(SetData.DISP_VAL07 , "");
			    strcpy(SetData.DISP_VAL08 , "");
    			strcpy(SetData.DISP_VAL09 , "");
	    		strcpy(SetData.DISP_VAL10 , "");

        		i4 = 0;
                for( i3 = 0; i3 < iSOKUSU;i3++)
                {
                    //以上以下の規格の場合対策 ///////////////////////////////////////////
                    iKIKA_KIND = 1;		//デフォルトは上下限で判定
    	    	    if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].KIKA_TYPE) == 1)
                    {
		    	        if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].KIKA_KIND) == 2)
			            {
    				        iKIKA_KIND = 2;
        			    }
            			else if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].KIKA_KIND) == 3)
	            		{
		            		iKIKA_KIND = 3;
			            }
            		}
                    ////////////////////////////////////////////////////////////////////
                    //測定用データ
                    bHANTEI = true;
	    			bDISP_HANTEI = true;
		    		switch( VALUE_TYPE )
			    	{
				    case 0:						//整数or少数
	    			case 1:						//角度
    					SOKU_MAX = pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].MAX;
	    				SOKU_MIN = pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].MIN;
                        bRtn = Form1->ConvDoubleDefS(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].RESULT),
                        								"0.00",
                                                        AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].RESULT),
                                                        &sBufConv);
                        if ( bRtn ) {
                            RESULT = Form1->ConvDoubleDefD(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].RESULT),0.0);
                        } else {
                            RESULT = 0.0;
                            bHANTEI = false;
                        }
    					if( bRtn && AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0 )
	    				{
                            switch(iKIKA_KIND)
                            {
                            case 1:
					    	    if( RESULT > SOKU_MAX || RESULT < SOKU_MIN )
                                {
                                    if( iOK_FLG != -1 ) iOK_FLG = 1;
                                }
                                else
                                {
                                    if( iOK_FLG == 2 ) iOK_FLG = 0;
                                }
                                break;
    						case 2:
	                        	if( RESULT > SOKU_MAX  )
                                {
                                    if( iOK_FLG != -1 ) iOK_FLG = 1;
                                }
                                else
                                {
                                    if( iOK_FLG == 2 ) iOK_FLG = 0;
                                }
                                break;
			    			case 3:
	                        	if( RESULT < SOKU_MIN )
                                {
                                    if( iOK_FLG != -1 ) iOK_FLG = 1;
                                }
                                else
                                {
                                    if( iOK_FLG == 2 ) iOK_FLG = 0;
                                }
                                break;
                            }
    						if( FIRST_FLG == true ){
	    						SOKU_VAL_MAX = RESULT;
		    					SOKU_VAL_MIN = RESULT;
			    				FIRST_FLG = false;
				    		}
    						else
	    					{
		    					if( RESULT > SOKU_VAL_MAX ) SOKU_VAL_MAX = RESULT;
			    				if( RESULT < SOKU_VAL_MIN ) SOKU_VAL_MIN = RESULT;
				    		}
					    	GOUKEI_RESULT += RESULT;
                            iSOKU_VAL_SU ++;
                        }
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                        {
                            SOKU_VAL_SU ++;
                            if( !bRtn ) iOK_FLG = -1;
                        }
    					break;
                    case 2:						//良、否
    					if( iDEBUG != 1)
	    				{
    	            		try{
                                // 良/否判定も未入力のまま保存させたいので RESULT_BUF を使って処理する
                                RESULT_BUF = AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].RESULT);
		    				}
			    			catch(EConvertError& e){
				    			bHANTEI = false;
						    }
    						catch(...){
	    						bHANTEI = false;
			    			}
				    	}
    					if(bHANTEI && AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
	    				{
                            // 良/否判定も未入力のまま保存させたいので RESULT_BUF を使って処理する
                            if( RESULT_BUF.ToIntDef(0) == 1 )
                            {
                                //OK_FLG = false;
                                if( iOK_FLG != -1 ) iOK_FLG = 1;
                            }
                            else
                            {
                                if( iOK_FLG == 2 ) iOK_FLG = 2;
                            }
                        }
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                        {
                            SOKU_VAL_SU ++;
                            iSOKU_VAL_SU ++;
                            if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].RESULT).Trim().Length() == 0 )
                            {
                                iOK_FLG = -1;
                            }
                        }
		    			break;
             	    case 3:
	    				RESULT_BUF = GetValidityData(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].RESULT),14);
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                        {
                       	    SOKU_VAL_SU ++;
                            iSOKU_VAL_SU++;
                            if(iOK_FLG  == 2 ) iOK_FLG = 0;
                            if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].RESULT).Trim().Length() == 0 )
                            {
                                iOK_FLG = -1;
                            }
                        }
                   	    break;
    				}
                    //表示用データの加工
    				switch( VALUE_TYPE )
	    			{
		    		case 0:						//整数or少数
    				case 1:						//角度
			    		DISP_MAX = pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].MAX;
				    	DISP_MIN = pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].MIN;
                        bRtn = Form1->ConvDoubleDefS(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT),
                        								"0.00",
                                                        AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT),
                                                        &sBufConv);
                        if ( bRtn ) {
                        	DISP_RESULT = Form1->ConvDoubleDefD(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT),0.0);
                        } else {
							DISP_RESULT = 0.0;
							bDISP_HANTEI = false;
                        }
    					if( bRtn && AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
	    				{
                            switch(iKIKA_KIND)
                            {
                            case 1:
					    	    if( DISP_RESULT > DISP_MAX || DISP_RESULT < DISP_MIN )
                                {
                                    if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                }
                                else
                                {
                                    if( iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                }
                                break;
    						case 2:
	                        	if( DISP_RESULT > DISP_MAX  )
                                {
                                    if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                }
                                else
                                {
                                    if( iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                }
                                break;
			    			case 3:
	                        	if( DISP_RESULT < DISP_MIN )
                                {
                                    if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                }
                                else
                                {
                                    if( iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                }
                                break;
                            }
    						if( DISP_FIRST_FLG == true ){
	    						DISP_VAL_MAX = DISP_RESULT;
		    					DISP_VAL_MIN = DISP_RESULT;
			    				DISP_FIRST_FLG = false;
				    		}
					    	else
						    {
							    if( DISP_RESULT > DISP_VAL_MAX ) DISP_VAL_MAX = DISP_RESULT;
    							if( DISP_RESULT < DISP_VAL_MIN ) DISP_VAL_MIN = DISP_RESULT;
	    					}
		    				DISP_GOUKEI_RESULT += DISP_RESULT;
                            iDISP_VAL_SU ++;
				    	}
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                        {
                            DISP_VAL_SU ++;
                            if(!bRtn) iDISP_OK_FLG = -1;
                        }
				    	break;
                    case 2:						//良、否
                        if( iDEBUG != 1)
		    			{
	                    	try{
                                // 良/否判定も未入力のまま保存させたいので DISP_RESULT_BUF を使って処理する
				    	    	DISP_RESULT_BUF = AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT);
					    	}
						    catch(EConvertError& e){
    							bDISP_HANTEI = false;
		    				}
			    			catch(...){
				    			bDISP_HANTEI = false;
						    }
    					}
	    				if(bDISP_HANTEI && AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
		    			{
                            // 良/否判定も未入力のまま保存させたいので DISP_RESULT_BUF を使って処理する
                            if( DISP_RESULT_BUF.ToIntDef(0) == 1 )
                            {
                                if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                            }
                            else
                            {
                                if(iDISP_OK_FLG == 2 ) iDISP_OK_FLG =0;
                            }
                        }
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                        {
                            DISP_VAL_SU ++;
                            iDISP_VAL_SU ++;
                            if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT).Trim().Length() == 0 )
                            {
                                iDISP_OK_FLG = -1;
                            }
                        }
					    break;
                 	case 3:
	    				DISP_RESULT_BUF = GetValidityData(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT),14);
                        if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                        {
                       	    DISP_VAL_SU ++;
                            iDISP_VAL_SU ++;
                            if(iDISP_OK_FLG == 2 ) iDISP_OK_FLG =0;
                            if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow+i3].DISP_RESULT).Trim().Length() == 0 )
                            {
                                iDISP_OK_FLG = -1;
                            }
                        }
                   	    break;
    				}

                    // 良/否判定も未入力のまま保存させたいので VALUE_TYPE = 2 の時でも RESULT_BUF を使って処理する
                    // イコール　case 2はコメント
                    switch( VALUE_TYPE )
                    {
                    case 0:
                    case 1:
                    	if( bHANTEI ) RESULT_BUF 		= AnsiString(RESULT);
	    		    	if( !bHANTEI ) RESULT_BUF 		= "";
                        break;
                    default:
                    	break;
                    }
	    			switch( VALUE_TYPE )
                    {
                    case 0:
                    case 1:
                    	if( bDISP_HANTEI ) DISP_RESULT_BUF 		= AnsiString(DISP_RESULT);
				        if( !bDISP_HANTEI ) DISP_RESULT_BUF 		= "";
                        break;
                    default:
                    	break;
                    }

     				if(bHANTEI == true || bHANTEI == false)
	    			{
	                    switch( i4 )
    	                {
        	            case 0:
            	        	strcpy(SetData.SOKU_VAL01 , AnsiString(RESULT_BUF).c_str());
			   			    strcpy(SetData.DISP_VAL01 , AnsiString(DISP_RESULT_BUF).c_str());
    			  			break;
	                    case 1:
		    		   		strcpy(SetData.SOKU_VAL02 , AnsiString(RESULT_BUF).c_str());
			    	  		strcpy(SetData.DISP_VAL02 , AnsiString(DISP_RESULT_BUF).c_str());
				     		break;
					    case 2:
    			   			strcpy(SetData.SOKU_VAL03 , AnsiString(RESULT_BUF).c_str());
	    		  			strcpy(SetData.DISP_VAL03 , AnsiString(DISP_RESULT_BUF).c_str());
		     				break;
			    		case 3:
		   		    		strcpy(SetData.SOKU_VAL04 , AnsiString(RESULT_BUF).c_str());
	  				    	strcpy(SetData.DISP_VAL04 , AnsiString(DISP_RESULT_BUF).c_str());
	 					    break;
    					case 4:
   	    					strcpy(SetData.SOKU_VAL05 , AnsiString(RESULT_BUF).c_str());
  		    				strcpy(SetData.DISP_VAL05 , AnsiString(DISP_RESULT_BUF).c_str());
 			    			break;
	                    case 5:
				   	    	strcpy(SetData.SOKU_VAL06 , AnsiString(RESULT_BUF).c_str());
				  		    strcpy(SetData.DISP_VAL06 , AnsiString(DISP_RESULT_BUF).c_str());
    				 		break;
	    				case 6:
		    	   			strcpy(SetData.SOKU_VAL07 , AnsiString(RESULT_BUF).c_str());
			      			strcpy(SetData.DISP_VAL07 , AnsiString(DISP_RESULT_BUF).c_str());
		 		    		break;
					    case 7:
    		   				strcpy(SetData.SOKU_VAL08 , AnsiString(RESULT_BUF).c_str());
	      					strcpy(SetData.DISP_VAL08 , AnsiString(DISP_RESULT_BUF).c_str());
	 	    				break;
			    		case 8:
   				    		strcpy(SetData.SOKU_VAL09 , AnsiString(RESULT_BUF).c_str());
  					    	strcpy(SetData.DISP_VAL09 , AnsiString(DISP_RESULT_BUF).c_str());
 						    break;
    	                case 9:
	    			   		strcpy(SetData.SOKU_VAL10 , AnsiString(RESULT_BUF).c_str());
		    		  		strcpy(SetData.DISP_VAL10 , AnsiString(DISP_RESULT_BUF).c_str());
			    	 		break;
				    	default:  								//例外データ用ルーチンを考える
					        //KSD03に対し新規追加か更新かをチェックする
    	    				sBuf = "SELECT * FROM KSD03";
	    					sBuf += " WHERE DTKSHIN = '" + AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].DTKSHIN)+ "'";
            	            sBuf += " AND   LOTNO   = '" + AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].LOTNO) 	+ "'";
            	            sBuf += " AND   HINBAN  = '" + AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].HINBAN) + "'";
			    			sBuf += " AND   UNQ_NO  = "  + AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UNQ_NO)  ;
	     		    		sBuf += " AND   SOKU_NO = "  + AnsiString(i3+1) ;
    				        // Initial Query
    	    				Query7->Close();
        					Query7->SQL->Clear();
            				Query7->SQL->Add(sBuf);
    		    			Query7->Open();
	    		    		Query7->Active = true;

    	    	        	bNEW = false;
	    	    			if( Query7->Eof == true ) bNEW = true;
	        				Query7->Close();
			    			if( bNEW == true )
				    		{
    	                        //新規登録
    							strcpy(SetData.DTKSHIN		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].DTKSHIN);
        	    	    		strcpy(SetData.LOTNO		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].LOTNO);
        	    	    		strcpy(SetData.HINBAN		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].HINBAN);
            	    			strcpy(SetData.UNQ_NO		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UNQ_NO);
			    				sBuf = "insert into KSD03(";
	    	            		sBuf += " DTKSHIN, LOTNO, HINBAN, UNQ_NO, SOKU_NO, SOKU_VAL, DISP_VAL";
    	    	        		sBuf += " )";
	    	        	    	sBuf += " VALUES('";
		    	        	    sBuf += AnsiString(SetData.DTKSHIN)           	+ "','";	//	得意先品番
        		    	    	sBuf += AnsiString(SetData.LOTNO)	       		+ "','";	//	ロットNO
        		    	    	sBuf += AnsiString(SetData.HINBAN)	       		+ "', ";	//	工管発行日 onishi
            		    		sBuf += AnsiString(SetData.UNQ_NO)  			+ " , ";	//	明細NO
		    					sBuf += AnsiString(i3+1)						+ " ,'";	//	測定NO
			    				sBuf += AnsiString(RESULT_BUF)                  + "','";	//	測定値
				    			sBuf += AnsiString(DISP_RESULT_BUF)				+ "') "; 	//	印刷用測定値
					    	}
						    else
    						{
	                            //更新
    							strcpy(SetData.DTKSHIN		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].DTKSHIN);
        		        		strcpy(SetData.LOTNO		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].LOTNO);
        		        		strcpy(SetData.HINBAN		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].HINBAN);
            		    		strcpy(SetData.UNQ_NO		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UNQ_NO);
			    				sBuf = "update KSD03 set ";
    			        	    sBuf += " DTKSHIN = '" 		+ AnsiString(SetData.DTKSHIN) 	+ "',"	;
					    		sBuf += " LOTNO = 	'" 		+ AnsiString(SetData.LOTNO) 	+ "',"	;
					    		sBuf += " HINBAN = 	'" 		+ AnsiString(SetData.HINBAN) 	+ "',"	;
						    	sBuf += " UNQ_NO = 	 " 		+ AnsiString(SetData.UNQ_NO) 	+ ","	;
			              	    sBuf += " SOKU_NO =  "		+ AnsiString(i3+1) 			   	+ " , " ;
        			        	sBuf += " SOKU_VAL = '"		+ AnsiString(RESULT_BUF) 		+ "'," ;
            			    	sBuf += " DISP_VAL = '"		+ AnsiString(DISP_RESULT_BUF) 	+ "'" ;
		    					sBuf += " WHERE DTKSHIN = '" + AnsiString(SetData.DTKSHIN)	+ "'";
                        		sBuf += " AND   LOTNO   = '" + AnsiString(SetData.LOTNO) 	+ "'";
                        		sBuf += " AND   HINBAN  = '" + AnsiString(SetData.HINBAN) 	+ "'";
				    			sBuf += " AND   UNQ_NO  = "  + AnsiString(SetData.UNQ_NO) 	 	 ;
	     			    		sBuf += " AND   SOKU_NO = "  + AnsiString(i3+1) ;
						    }
    					    //For Debug
                            if( iDEBUG == 1 )
                            {
	    		        	    ClpBrd = Clipboard();
		    	     		    ClpBrd->Open();
     		    			    ClpBrd->SetTextBuf(sBuf.c_str());
		    	     		    ClpBrd->Close();
                            }
                            // Initial Query
    			        	Query7->Close();
	    		            Query7->SQL->Clear();
            			    Query7->SQL->Add(sBuf);
			    		    // 問い合せ文の実行
		    	        	try{
        			        	Query7->ExecSQL();
			                }
        	    		    catch(EDatabaseError& e)
	    		            {
            			    	SBr1->Panels->Items[0]->Text = e.Message;
                    			SBr1->Update();
		                	    return(false);
	        		        }
			                catch(Exception& e)
            			    {
	    	    	        	SBr1->Panels->Items[0]->Text = e.Message;
            			        SBr1->Update();
                    			return(false);
			                }
			   		    	break;
    			  		}
	    				i4 ++;				//判定が出来たセーブ数カウント
		    		}
			    }
                //１項目のセーブ実行
    			strcpy(SetData.DTKSHIN		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].DTKSHIN);
                strcpy(SetData.LOTNO		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].LOTNO);
                strcpy(SetData.HINBAN		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].HINBAN);
                strcpy(SetData.UNQ_NO		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UNQ_NO);
                strcpy(SetData.ORDER_NO		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ORDER_NO);
                strcpy(SetData.SKB_NO		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKB_NO);
                strcpy(SetData.HINBAN_SK	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].HINBAN_SK);
                strcpy(SetData.KOMK_NO		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KOMK_NO);
                strcpy(SetData.KOMK_NM		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KOMK_NM);
                strcpy(SetData.KOMK_ENG		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KOMK_ENG);
                strcpy(SetData.KOMK_SUB		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KOMK_SUB);
                strcpy(SetData.KOMK_SUB_ENG	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KOMK_SUB_ENG);
                strcpy(SetData.KIKI_NO		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKI_NO);
                strcpy(SetData.KIKI_NM		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKI_NM);
                strcpy(SetData.TANI			,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].TANI);
                strcpy(SetData.KIKA_TYPE	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKA_TYPE);
                strcpy(SetData.KIKA_KIND	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKA_KIND);
                strcpy(SetData.KIKA_DECI	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKA_DECI);
                strcpy(SetData.KIKA_NUM1	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKA_NUM1);
                strcpy(SetData.KIKA_NUM2	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKA_NUM2);
                strcpy(SetData.KIKA_NUM3	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKA_NUM3);
                strcpy(SetData.KIKA_STR		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKA_STR);
                strcpy(SetData.KIKA_SUB1	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKA_SUB1);
                strcpy(SetData.KIKA_SUB2	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKA_SUB2);
                strcpy(SetData.KIKA_SUB3	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKA_SUB3);
                strcpy(SetData.SOKU_SU		,AnsiString(iSIJI_NSU).c_str());
                strcpy(SetData.SOKU_FLG		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SOKU_FLG);
                strcpy(SetData.TOKU_FLG		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].TOKU_FLG);
                strcpy(SetData.KIKA_PRT		,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].KIKA_PRT);
                strcpy(SetData.VALUE_TYPE	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].VALUE_TYPE);
                strcpy(SetData.VALUE_DECI	,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].VALUE_DECI);
                strcpy(SetData.SOKU_VAL_SU		,AnsiString(iSIJI_NSU).c_str());
    			if( iSOKU_VAL_SU > 0) {
	    			SOKU_VAL_AVE = GOUKEI_RESULT / iSOKU_VAL_SU;
		    	}
                else {
				    SOKU_VAL_AVE = 0;
                }
    			if( SOKU_VAL_AVE > 9999999.999999 ) SOKU_VAL_AVE = 9999999.999999;
	    		if( SOKU_VAL_MAX > 9999999.99999  ) SOKU_VAL_MAX = 9999999.99999 ;
		    	if( SOKU_VAL_MIN > 9999999.99999  ) SOKU_VAL_MIN = 9999999.99999 ;
			    strcpy(SetData.SOKU_VAL_AVE	,AnsiString(SOKU_VAL_AVE).SubString(1,14).c_str());
    			strcpy(SetData.SOKU_VAL_MAX ,AnsiString(SOKU_VAL_MAX).SubString(1,14).c_str());
	    		strcpy(SetData.SOKU_VAL_MIN ,AnsiString(SOKU_VAL_MIN).SubString(1,14).c_str());
                strcpy(SetData.SOKU_OK,AnsiString(iOK_FLG).c_str());
                strcpy(SetData.DISP_VAL_SU		,AnsiString(iSIJI_NSU).c_str());
    			if( iDISP_VAL_SU > 0) {
	    			DISP_VAL_AVE = DISP_GOUKEI_RESULT / iDISP_VAL_SU;
		    	}
			    else
    			{
	    			DISP_VAL_AVE = 0;
		    	}
    			if( DISP_VAL_AVE > 9999999.999999 ) DISP_VAL_AVE = 9999999.999999;
	    		if( DISP_VAL_MAX > 9999999.99999  ) DISP_VAL_MAX = 9999999.99999 ;
		    	if( DISP_VAL_MIN > 9999999.99999  ) DISP_VAL_MIN = 9999999.99999 ;
			    strcpy(SetData.DISP_VAL_AVE	,AnsiString(DISP_VAL_AVE).SubString(1,14).c_str());
    			strcpy(SetData.DISP_VAL_MAX ,AnsiString(DISP_VAL_MAX).SubString(1,14).c_str());
	    		strcpy(SetData.DISP_VAL_MIN ,AnsiString(DISP_VAL_MIN).SubString(1,14).c_str());
                strcpy(SetData.DISP_OK,AnsiString(iDISP_OK_FLG).c_str());
	    		i4 = AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCNT).ToIntDef(0)+1;
		    	strcpy(SetData.UPDCNT ,AnsiString(i4).c_str());

                //測定項目がこのロットに対して存在してたのかを調べセーブの有無を判断する 2003/05/13
                if(AnsiString(SetData.KOMK_NO).ToIntDef(0) != -999 )
                {
		    		//KSD02に対し新規追加か更新かをチェックする
	    	    	sBuf = "SELECT * FROM KSD02";
    				sBuf += " WHERE DTKSHIN = '" + sNowDTKSHIN + "'";
    				sBuf += " AND UNQ_NO = " + AnsiString(iUNQNO) ;
	        		sBuf += " AND SKB_NO IN ( 2 , 3 )";                        //出荷検査項目、材料証明項目
    	    		sBuf += " AND LOTNO = '" + AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].LOTNO) + "'";
    	    		sBuf += " AND HINBAN= '" + AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].HINBAN) + "'";
			    	// Initial Query
    	    		Query2->Close();
	        		Query2->SQL->Clear();
    	        	Query2->SQL->Add(sBuf);
    		    	Query2->Open();
    			    Query2->Active = true;

    	            bNEW = false;
	    	    	if( Query2->Eof == true ) bNEW = true;
	        		Query2->Close();
			    	if( bNEW == true )										//新規登録
				    {
                        // 測定日
					    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKTYMD,FormatDateTime("yyyymmdd",Date()).c_str());
                        // 登録日
					    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
                        // 登録時間
					    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
                        // 変更日
					    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
                        // 変更時間
					    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
                        // 更新者
					    if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCHR).Length() == 0)
					    {
						    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCHR,AnsiString(Form1->USER_COD).c_str());
					    }
                        // 更新回数
					    strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCNT,"0");

                        //セーブ用バッファにコピー
                        // 測定日
					    strcpy(SetData.SKTYMD,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKTYMD);
                        // 登録日
					    strcpy(SetData.ADDYMD,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDYMD);
                        // 登録時間
					    strcpy(SetData.ADDTIM,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDTIM);
                        // 変更日
					    strcpy(SetData.UPDYMD,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDYMD);
                        // 変更時間
					    strcpy(SetData.UPDTIM,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDTIM);
                        // 更新者
					    strcpy(SetData.UPDCHR,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCHR);
                        // 更新回数
					    strcpy(SetData.UPDCNT,pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCNT);

                        // 問合せ文作成(KSD02)
    					sBuf = "insert into KSD02(";
	        	        sBuf += " DTKSHIN, LOTNO, HINBAN, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK, KOMK_NO, KOMK_NM,";
    	        	    sBuf += " KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI,";
	    	            sBuf += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3,";
    	    	        sBuf += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3, SOKU_SU, SOKU_FLG,";
        	    	    sBuf += " TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI,";
    	            	sBuf += " SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05,";
	    	            sBuf += " SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,";
    	    	        sBuf += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK,";
        	    	    sBuf += " DISP_VAL01, DISP_VAL02, DISP_VAL03, DISP_VAL04, DISP_VAL05,";
            	    	sBuf += " DISP_VAL06, DISP_VAL07, DISP_VAL08, DISP_VAL09, DISP_VAL10,";
		                sBuf += " DISP_VAL_SU, DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, DISP_OK,";
        		        sBuf += " SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
            		    sBuf += " )";
                		sBuf += " VALUES('";
	                	sBuf += AnsiString(SetData.DTKSHIN)           	+ "','";	//	得意先品番
	    	            sBuf += AnsiString(SetData.LOTNO)	       		+ "','";	//	ロットNO
	    	            sBuf += AnsiString(SetData.HINBAN)	       		+ "', ";	//	工管発行日 onishi
        	    	    sBuf += AnsiString(SetData.UNQ_NO)  			+ " , ";	//	明細NO
            	    	sBuf += AnsiString(SetData.ORDER_NO)  			+ " , ";	//	明細NO
	            	    sBuf += AnsiString(SetData.SKB_NO)  			+ " ,'";	//	識別NO
    	            	sBuf += AnsiString(SetData.HINBAN_SK) 			+ "', ";
	        	        sBuf += AnsiString(SetData.KOMK_NO) 			+ " ,'";	//	測定項目NO
		                sBuf += AnsiString(SetData.KOMK_NM)	       		+ "','";	//	測定項目名称
        		        sBuf += AnsiString(SetData.KOMK_ENG)       		+ "','";
            		    sBuf += AnsiString(SetData.KOMK_SUB)	   		+ "','";	//	測定項目名称
                		sBuf += AnsiString(SetData.KOMK_SUB_ENG)   		+ "', ";	//	測定項目名称
		                sBuf += AnsiString(SetData.KIKI_NO) 			+ " ,'";	//	測定機器NO
        		        sBuf += AnsiString(SetData.KIKI_NM)	       		+ "','";	//	測定機器名称
            		    sBuf += AnsiString(SetData.TANI)   	       		+ "', ";	//	単位
                		sBuf += AnsiString(SetData.KIKA_TYPE) + " , ";
	                	sBuf += AnsiString(SetData.KIKA_KIND) + " , ";
	    	            sBuf += AnsiString(SetData.KIKA_DECI) + " , ";
    	    	        sBuf += AnsiString(SetData.KIKA_NUM1) + " , ";
            	    	sBuf += AnsiString(SetData.KIKA_NUM2) + " , ";
	            	    sBuf += AnsiString(SetData.KIKA_NUM3) + " ,'";
    	            	sBuf += AnsiString(SetData.KIKA_STR)            + "','";
	            	    sBuf += AnsiString(SetData.KIKA_SUB1)           + "','";
    	            	sBuf += AnsiString(SetData.KIKA_SUB2)           + "','";
	    	            sBuf += AnsiString(SetData.KIKA_SUB3)           + "', ";
        	    	    sBuf += AnsiString(SetData.SOKU_SU) 	+ " , ";	//    　測定指示ｎ数
            	    	sBuf += AnsiString(SetData.SOKU_FLG) 	+ " , ";	//    　測定指示ｎ数
	                	sBuf += AnsiString(SetData.TOKU_FLG) 	+ " , ";	//    　測定指示ｎ数
		                sBuf += AnsiString(SetData.KIKA_PRT) 	+ " , ";	//    　測定指示ｎ数
    		            sBuf += AnsiString(SetData.VALUE_TYPE)+ " , ";	//    　測定指示ｎ数
        		        sBuf += AnsiString(SetData.VALUE_DECI)+ " ,'";	//    　測定指示ｎ数
                		sBuf += AnsiString(SetData.SOKU_VAL01)        	+ "','";	//	測定値１
	    	            sBuf += AnsiString(SetData.SOKU_VAL02)        	+ "','";	//      測定値２　　　
    	    	        sBuf += AnsiString(SetData.SOKU_VAL03)        	+ "','";	//	測定値３
        	    	    sBuf += AnsiString(SetData.SOKU_VAL04)        	+ "','";	//	測定値４
            	    	sBuf += AnsiString(SetData.SOKU_VAL05)        	+ "','";	//	測定値５
	            	    sBuf += AnsiString(SetData.SOKU_VAL06)        	+ "','";	//	測定値６
    	    	        sBuf += AnsiString(SetData.SOKU_VAL07)        	+ "','";	//	測定値７
        	    	    sBuf += AnsiString(SetData.SOKU_VAL08)        	+ "','";	//	測定値８
	        	        sBuf += AnsiString(SetData.SOKU_VAL09)        	+ "','";	//	測定値９
    	        	    sBuf += AnsiString(SetData.SOKU_VAL10)        	+ "', ";	//	測定値１０
        	        	sBuf += AnsiString(SetData.SOKU_VAL_SU)+ " , ";	//    　測定指示ｎ数
    	            	sBuf += AnsiString(SetData.SOKU_VAL_AVE)+ " , ";	//    　測定指示ｎ数
	    	            sBuf += AnsiString(SetData.SOKU_VAL_MAX)+ " , ";	//    　測定指示ｎ数
    	    	        sBuf += AnsiString(SetData.SOKU_VAL_MIN)+ " , ";	//    　測定指示ｎ数
        	    	    sBuf += AnsiString(SetData.SOKU_OK)   + " ,'";	//	測定値１０
            	    	sBuf += AnsiString(SetData.DISP_VAL01)        	+ "','";	//	測定値１
		                sBuf += AnsiString(SetData.DISP_VAL02)        	+ "','";	//      測定値２　　　
        		        sBuf += AnsiString(SetData.DISP_VAL03)        	+ "','";	//	測定値３
            		    sBuf += AnsiString(SetData.DISP_VAL04)        	+ "','";	//	測定値４
                		sBuf += AnsiString(SetData.DISP_VAL05)        	+ "','";	//	測定値５
	                	sBuf += AnsiString(SetData.DISP_VAL06)        	+ "','";	//	測定値６
	    	            sBuf += AnsiString(SetData.DISP_VAL07)        	+ "','";	//	測定値７
    	    	        sBuf += AnsiString(SetData.DISP_VAL08)        	+ "','";	//	測定値８
            	    	sBuf += AnsiString(SetData.DISP_VAL09)        	+ "','";	//	測定値９
	            	    sBuf += AnsiString(SetData.DISP_VAL10)        	+ "', ";	//	測定値１０
    	            	sBuf += AnsiString(SetData.DISP_VAL_SU)+ " , ";	//    　測定指示ｎ数
	            	    sBuf += AnsiString(SetData.DISP_VAL_AVE)+ " , ";	//    　測定指示ｎ数
    	            	sBuf += AnsiString(SetData.DISP_VAL_MAX)+ " , ";	//    　測定指示ｎ数
	    	            sBuf += AnsiString(SetData.DISP_VAL_MIN)+ " , ";	//    　測定指示ｎ数
        	    	    sBuf += AnsiString(SetData.DISP_OK)  + " ,'";	//	測定値１０
            	    	sBuf += AnsiString(SetData.SKTYMD)   	       + "','";	//	測定日
	                	sBuf += AnsiString(SetData.ADDYMD)   	       + "','";	//	登録日
		                sBuf += AnsiString(SetData.ADDTIM)   	       + "','";	//	登録時間
    		            sBuf += AnsiString(SetData.UPDYMD)   	       + "','";	//	変更日
        		        sBuf += AnsiString(SetData.UPDTIM)   	       + "',";	//	変更時間
    					sBuf += AnsiString(SetData.UPDCHR)			   + " ,";
	                	sBuf += AnsiString(SetData.UPDCNT);  	         	//	更新回数
		                sBuf += ")";
			    	}
				    else
    				{
                        // 測定日（登録日と同じ)
    					strcpy(SetData.SKTYMD,AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SKTYMD).c_str());
                        // 登録日
	    				strcpy(SetData.ADDYMD,AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDYMD).c_str());
                        // 登録時間
		    			strcpy(SetData.ADDTIM,AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].ADDTIM).c_str());
                        // 変更日
			    		strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
				    	strcpy(SetData.UPDYMD,AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDYMD).c_str());
                        // 変更時間
    					strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
	    				strcpy(SetData.UPDTIM,AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDTIM).c_str());
                        // 更新者
		    			if(AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCHR).Length() == 0)
			    		{
				    		strcpy(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCHR,AnsiString(Form1->USER_COD).c_str());
					    }
    					strcpy(SetData.UPDCHR,AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].UPDCHR).c_str());

                        // 更新回数
                        // strcpy(SetData.UPDCNT,"0");
	    				sBuf = "update KSD02 set ";
    	    	        //sBuf += " DTKSHIN  = '" 	+ AnsiString(SetData.DTKSHIN) + "',"	;
			    		//sBuf += " LOTNO    = '" 	+ AnsiString(SetData.LOTNO) + "',"	;
			    		//sBuf += " HINBAN   = '" 	+ AnsiString(SetData.HINBAN) + "',"	;
				    	sBuf += " UNQ_NO   = " 		+ AnsiString(SetData.UNQ_NO) + ","	;
					    sBuf += " ORDER_NO = " 		+ AnsiString(SetData.ORDER_NO) + ","	;
    					sBuf += " SKB_NO = " 		+ AnsiString(SetData.SKB_NO) + ","	;
	    				sBuf += " HINBAN_SK = '" 	+ AnsiString(SetData.HINBAN_SK) + "',"	;
		    			sBuf += " KOMK_NO = " 		+ AnsiString(SetData.KOMK_NO) + ","	;
			    		sBuf += " KOMK_NM = '" 		+ AnsiString(SetData.KOMK_NM) + "',"	;
        	        	sBuf += " KOMK_ENG = '" 	+ AnsiString(SetData.KOMK_ENG) + "',"	;
					    sBuf += " KOMK_SUB = '" 	+ AnsiString(SetData.KOMK_SUB) + "',"	;
    					sBuf += " KOMK_SUB_ENG = '" + AnsiString(SetData.KOMK_SUB_ENG) + "',"	;
	    				sBuf += " KIKI_NO = " 		+ AnsiString(SetData.KIKI_NO) + ","	;
		    			sBuf += " KIKI_NM = '" 		+ AnsiString(SetData.KIKI_NM) + "',"	;
			    		sBuf += " TANI = '" 		+ AnsiString(SetData.TANI) + "',"	;
		                sBuf += " KIKA_TYPE = " 	+ AnsiString(SetData.KIKA_TYPE) + ","	;
					    sBuf += " KIKA_KIND = " 	+ AnsiString(SetData.KIKA_KIND) + ","	;
    					sBuf += " KIKA_DECI = " 	+ AnsiString(SetData.KIKA_DECI) + ","	;
	    				sBuf += " KIKA_NUM1 = " 	+ AnsiString(SetData.KIKA_NUM1) + ","	;
		    			sBuf += " KIKA_NUM2 = " 	+ AnsiString(SetData.KIKA_NUM2) + ","	;
			    		sBuf += " KIKA_NUM3 = " 	+ AnsiString(SetData.KIKA_NUM3) + ","	;
    		            sBuf += " KIKA_STR = '"  	+ AnsiString(SetData.KIKA_STR) + "',"	;
					    sBuf += " KIKA_SUB1 = '" 	+ AnsiString(SetData.KIKA_SUB1) + "',"	;
    					sBuf += " KIKA_SUB2 = '" 	+ AnsiString(SetData.KIKA_SUB2) + "',"	;
	    				sBuf += " KIKA_SUB3 = '" 	+ AnsiString(SetData.KIKA_SUB3) + "',"	;
		    			sBuf += " SOKU_SU = " 	 	+ AnsiString(SetData.SOKU_SU) + ","	;
        	            sBuf += " SOKU_FLG = "  	+ AnsiString(SetData.SOKU_FLG) + ","	;
        		        sBuf += " TOKU_FLG = "  	+ AnsiString(SetData.TOKU_FLG) + ","	;
					    sBuf += " KIKA_PRT = "  	+ AnsiString(SetData.KIKA_PRT) + ","	;
    					sBuf += " VALUE_TYPE = " 	+ AnsiString(SetData.VALUE_TYPE) + ","	;
	    				sBuf += " VALUE_DECI = " 	+ AnsiString(SetData.VALUE_DECI) + ","	;
            	    	sBuf += " SOKU_VAL01 = '" 	+ AnsiString(SetData.SOKU_VAL01) + "',"	;
			    		sBuf += " SOKU_VAL02 = '" 	+ AnsiString(SetData.SOKU_VAL02) + "',"	;
				    	sBuf += " SOKU_VAL03 = '" 	+ AnsiString(SetData.SOKU_VAL03) + "',"	;
					    sBuf += " SOKU_VAL04 = '" 	+ AnsiString(SetData.SOKU_VAL04) + "',"	;
    					sBuf += " SOKU_VAL05 = '" 	+ AnsiString(SetData.SOKU_VAL05) + "',"	;
	        	        sBuf += " SOKU_VAL06 = '" 	+ AnsiString(SetData.SOKU_VAL06) + "',"	;
		    			sBuf += " SOKU_VAL07 = '" 	+ AnsiString(SetData.SOKU_VAL07) + "',"	;
			    		sBuf += " SOKU_VAL08 = '" 	+ AnsiString(SetData.SOKU_VAL08) + "',"	;
				    	sBuf += " SOKU_VAL09 = '" 	+ AnsiString(SetData.SOKU_VAL09) + "',"	;
					    sBuf += " SOKU_VAL10 = '" 	+ AnsiString(SetData.SOKU_VAL10) + "',"	;
        		        sBuf += " SOKU_VAL_SU = "  	+ AnsiString(SetData.SOKU_VAL_SU) + ","	;
	    				sBuf += " SOKU_VAL_AVE = " 	+ AnsiString(SetData.SOKU_VAL_AVE) + ","	;
		    			sBuf += " SOKU_VAL_MAX = " 	+ AnsiString(SetData.SOKU_VAL_MAX) + ","	;
			    		sBuf += " SOKU_VAL_MIN = " 	+ AnsiString(SetData.SOKU_VAL_MIN) + ","	;
				    	sBuf += " SOKU_OK = " 	  	+ AnsiString(SetData.SOKU_OK) + ","	;
        		        sBuf += " DISP_VAL01 = '" 	+ AnsiString(SetData.DISP_VAL01) + "',"	;
    					sBuf += " DISP_VAL02 = '" 	+ AnsiString(SetData.DISP_VAL02) + "',"	;
	    				sBuf += " DISP_VAL03 = '" 	+ AnsiString(SetData.DISP_VAL03) + "',"	;
		    			sBuf += " DISP_VAL04 = '" 	+ AnsiString(SetData.DISP_VAL04) + "',"	;
			    		sBuf += " DISP_VAL05 = '" 	+ AnsiString(SetData.DISP_VAL05) + "',"	;
        	        	sBuf += " DISP_VAL06 = '" 	+ AnsiString(SetData.DISP_VAL06) + "',"	;
					    sBuf += " DISP_VAL07 = '" 	+ AnsiString(SetData.DISP_VAL07) + "',"	;
    					sBuf += " DISP_VAL08 = '" 	+ AnsiString(SetData.DISP_VAL08) + "',"	;
	                    sBuf += " DISP_VAL09 = '" 	+ AnsiString(SetData.DISP_VAL09) + "',"	;
		    			sBuf += " DISP_VAL10 = '" 	+ AnsiString(SetData.DISP_VAL10) + "',"	;
	    	            sBuf += " DISP_VAL_SU = "  	+ AnsiString(SetData.DISP_VAL_SU) + ","	;
				    	sBuf += " DISP_VAL_AVE = " 	+ AnsiString(SetData.DISP_VAL_AVE) + ","	;
					    sBuf += " DISP_VAL_MAX = " 	+ AnsiString(SetData.DISP_VAL_MAX) + ","	;
    					sBuf += " DISP_VAL_MIN = " 	+ AnsiString(SetData.DISP_VAL_MIN) + ","	;
	    				sBuf += " DISP_OK = " 		+ AnsiString(SetData.DISP_OK) + ","	;
    	    	        sBuf += " SKTYMD = '" 		+ AnsiString(SetData.SKTYMD) + "',"	;
			    		sBuf += " ADDYMD = '" 		+ AnsiString(SetData.ADDYMD) + "',"	;
				    	sBuf += " ADDTIM = '" 		+ AnsiString(SetData.ADDTIM) + "',"	;
					    sBuf += " UPDYMD = '" 		+ AnsiString(SetData.UPDYMD) + "',"	;
    					sBuf += " UPDTIM = '" 		+ AnsiString(SetData.UPDTIM) + "',"	;
	    				sBuf += " UPDCHR = " 		+ AnsiString(SetData.UPDCHR) + ","	;
		    			sBuf += " UPDCNT = " 		+ AnsiString(SetData.UPDCNT) + " "	;
     		    		sBuf += " WHERE DTKSHIN='" 	+ AnsiString(SetData.DTKSHIN) + "'";
	     		    	sBuf += " AND   LOTNO  ='" 	+ AnsiString(SetData.LOTNO)   + "'";
	     		    	sBuf += " AND   HINBAN ='" 	+ AnsiString(SetData.HINBAN)  + "'";
    	 			    sBuf += " AND   UNQ_NO = " 	+ AnsiString(SetData.UNQ_NO) ;
    				}
	    	        //For Debug
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
        		    // 問い合せ文の実行
        		    try{
            		    Query1->ExecSQL();
    	            }
        	        catch(EDatabaseError& e)
            	    {
                		SBr1->Panels->Items[0]->Text = e.Message;
                    	SBr1->Update();
	                    return(false);
        	        }
            	    catch(Exception& e)
                	{
                		SBr1->Panels->Items[0]->Text = e.Message;
	                    SBr1->Update();
    	                return(false);
            	    }
	            }
                iRow +=  AnsiString(pCELLINFO_RIRE_SYUKA[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);
    		}
		}
	}
    Query2->Close();

	// メモリの開放
    if( hSetJissekiData ){
    	GlobalUnlock( hSetJissekiData );
        //20170509 Y.Onishi
        //Memory Address '00000032'時にコケる不具合を修正
        //GlobalFree( hSetJissekiData );
    }
	hSetJissekiData = NULL;
    return(true);
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
//測定実績データの新規登録＆更新（対象データベースはKSD001&KSD002、対照データは測定履歴）
//---------------------------------------------------------------------------
bool __fastcall TForm1::Set_DB_SOKU_SOZAI(void)
{
    int i3,i4;//i1,i2,
    int iUNQNO;
    int iKIKA_KIND;         //規格種類（中心、以上、以下）判断用
    //セーブ時使用変数一覧
	int iRow,iCol;
	int iRowCount;
    int iSOKUSU;
	int VALUE_TYPE;
	int SOKU_VAL_SU,DISP_VAL_SU;
	int iSOKU_VAL_SU,iDISP_VAL_SU;
    int iSIJI_NSU;
    AnsiString RESULT_BUF,DISP_RESULT_BUF,sMEMO;
	double SOKU_VAL_AVE,SOKU_VAL_MAX,SOKU_VAL_MIN;
	double DISP_VAL_AVE,DISP_VAL_MAX,DISP_VAL_MIN;
	double RESULT,GOUKEI_RESULT,DISP_RESULT,DISP_GOUKEI_RESULT;
    double SOKU_MAX,SOKU_MIN;
    double DISP_MAX,DISP_MIN;
    int iRESULT,iDISP_RESULT;
    //bool OK_FLG,DISP_OK_FLG;
    int iOK_FLG,iDISP_OK_FLG;
	bool FIRST_FLG,DISP_FIRST_FLG;
	bool bNEW;						//新規追加フラグ
	//HANDLE hSetJissekiData;
	//KSD01_DATA  *pSetJissekiData;
	bool bHANTEI,bDISP_HANTEI;
    bool bRtn;				//2003.05.08 E.Takase Add
    //double dBuf;			//2003.05.08 E.Takase Add
    AnsiString sBufConv;	//2003.05.08 E.Takase Add


    AnsiString sBuf,sLot,sTempBuf;
    KSD02_DATA SetData;


//KSD02の更新(新規登録の場合)

	iRowCount = SGr_vSOKU_SOZAI->RowCount;
	for(iCol = 0; iCol < SGr_vSOKU_SOZAI->ColCount;iCol++)
	{
        //更新フラグをみて、更新されていなければ保存を行わない。
		if(pSOKU_KSD01_DATA[iCol].UPD_FLG == false)
		{
		}
        else
        {
	    	for( iRow = 1;iRow < iRowCount; iRow=iRow)
		    {
    			iSOKUSU 	= AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);
	    		VALUE_TYPE 	= AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0);
		    	iUNQNO 		= AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UNQ_NO).ToIntDef(0);
			    if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KOMK_NO).ToIntDef(0) == -999)
    			{
	    		}
    			else
	    		{
                //実際の指示数を検出します
                    iSIJI_NSU = 0;
                    for(i3=0; i3 < AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);i3++)
                    {
                        if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].KOMK_NO).ToIntDef(0) == -999) break;
                        iSIJI_NSU ++;
                    }
                    iSOKUSU=iSIJI_NSU;
                    //KSD03（例外データ）削除
                    sBuf = "";
                    sBuf = "DELETE FROM KSD03";
                    sBuf +=	" where DTKSHIN='" + AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].DTKSHIN) + "'";
                    sBuf += " and   LOTNO  ='" + AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].LOTNO)   + "'";
                    sBuf += " and   HINBAN ='" + AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].HINBAN)  + "'";
                    sBuf += " and   UNQ_NO = " + AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UNQ_NO);
                    //For Debug
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
                    // 問い合せ文の実行
                    try{
                        Query1->ExecSQL();
                    }
                    catch(EDatabaseError& e)
                    {
                        SBr1->Panels->Items[0]->Text = e.Message;
                        SBr1->Update();
                        return(false);
                    }
                    catch(Exception& e)
                    {
                        SBr1->Panels->Items[0]->Text = e.Message;
                        SBr1->Update();
                        return(false);
                    }
                ///////////////////////////////////////////////
        			SOKU_VAL_SU = 0;
        			DISP_VAL_SU = 0;
		        	iSOKU_VAL_SU = 0;
        			iDISP_VAL_SU = 0;
                    GOUKEI_RESULT = 0;
                    DISP_GOUKEI_RESULT = 0;
		        	SOKU_MAX = 0.0;
        			DISP_MAX = 0.0;
		        	SOKU_MIN = 0.0;
        			DISP_MIN = 0.0;
		        	SOKU_VAL_MAX = 0;
        			SOKU_VAL_MIN = 0;
		        	DISP_VAL_MAX = 0;
        			DISP_VAL_MIN = 0;
                    iOK_FLG = 2;
                    iDISP_OK_FLG = 2;
		        	FIRST_FLG 	= true;
        			DISP_FIRST_FLG = true;
		        	RESULT = 0;
        			DISP_RESULT = 0;
                //測定値初期化
        			strcpy(SetData.SOKU_VAL01 , "");
		        	strcpy(SetData.SOKU_VAL02 , "");
        			strcpy(SetData.SOKU_VAL03 , "");
		        	strcpy(SetData.SOKU_VAL04 , "");
        			strcpy(SetData.SOKU_VAL05 , "");
		        	strcpy(SetData.SOKU_VAL06 , "");
        			strcpy(SetData.SOKU_VAL07 , "");
		        	strcpy(SetData.SOKU_VAL08 , "");
        			strcpy(SetData.SOKU_VAL09 , "");
        			strcpy(SetData.SOKU_VAL10 , "");
                //印刷値初期化
        			strcpy(SetData.DISP_VAL01 , "");
		        	strcpy(SetData.DISP_VAL02 , "");
        			strcpy(SetData.DISP_VAL03 , "");
		        	strcpy(SetData.DISP_VAL04 , "");
        			strcpy(SetData.DISP_VAL05 , "");
		        	strcpy(SetData.DISP_VAL06 , "");
        			strcpy(SetData.DISP_VAL07 , "");
		        	strcpy(SetData.DISP_VAL08 , "");
        			strcpy(SetData.DISP_VAL09 , "");
		        	strcpy(SetData.DISP_VAL10 , "");

                    i4 = 0;
                    for( i3 = 0; i3 < iSOKUSU;i3++)
                    {
                    //以上以下の規格の場合対策 ///////////////////////////////////////////
                        iKIKA_KIND = 1;		//デフォルトは上下限で判定
	            	    if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].KIKA_TYPE) == 1)
                        {
        			        if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].KIKA_KIND) == 2)
		        	        {
				                iKIKA_KIND = 2;
            			    }
                			else if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].KIKA_KIND) == 3)
	        	        	{
		        		        iKIKA_KIND = 3;
        			        }
                		}
                        ////////////////////////////////////////////////////////////////////
                        //測定用データ
        				bHANTEI = true;
                        bDISP_HANTEI = true;
        				switch( VALUE_TYPE )
		        		{
				        case 0:						//整数or少数
				        case 1:						//角度
        					SOKU_MAX = pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].MAX;
		        			SOKU_MIN = pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].MIN;
                            bRtn = Form1->ConvDoubleDefS(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].RESULT),
                        								"0.00",
                                                        AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].RESULT),
                                                        &sBufConv);
                            if ( bRtn ) {
                            	RESULT = Form1->ConvDoubleDefD(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].RESULT),0.0);
                            } else {
					    		RESULT = 0.0;
						    	bHANTEI = false;
                            }
                            if(bRtn && AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
				        	{
                                switch(iKIKA_KIND)
                                {
                                case 1:
				        		    if( RESULT > SOKU_MAX || RESULT < SOKU_MIN )
                                    {
                                        if( iOK_FLG != -1 ) iOK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iOK_FLG == 2 ) iOK_FLG = 0;
                                    }
                                    break;
        						case 2:
	                            	if( RESULT > SOKU_MAX  )
                                    {
                                        if( iOK_FLG != -1 ) iOK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iOK_FLG == 2 ) iOK_FLG = 0;
                                    }
                                    break;
        						case 3:
	                            	if( RESULT < SOKU_MIN )
                                    {
                                        if( iOK_FLG != -1 ) iOK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iOK_FLG == 2 ) iOK_FLG = 0;
                                    }
                                    break;
                                }
        						if( FIRST_FLG == true )
                                {
		        					SOKU_VAL_MAX = RESULT;
				        			SOKU_VAL_MIN = RESULT;
						        	FIRST_FLG = false;
        						}
		        				else
				        		{
						        	if( RESULT > SOKU_VAL_MAX ) SOKU_VAL_MAX = RESULT;
        							if( RESULT < SOKU_VAL_MIN ) SOKU_VAL_MIN = RESULT;
		        				}
				        		GOUKEI_RESULT += RESULT;
                                iSOKU_VAL_SU ++;
        					}
                            if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                                SOKU_VAL_SU ++;
                                if(!bRtn) iOK_FLG = -1;
                            }
		        			break;
                        case 2:						//良、否
        					if(iDEBUG != 1)
		        			{
	                    		try{
                                	// 良/否判定も未入力のまま保存させたいので RESULT_BUF を使って処理する
                                	RESULT_BUF = AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].RESULT);
        						}
		        				catch(EConvertError& e){
				        			bHANTEI = false;
        						}
		        				catch(...){
				        			bHANTEI = false;
        						}
                            }
        					if(bHANTEI && AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
		        			{
                               	// 良/否判定も未入力のまま保存させたいので RESULT_BUF を使って処理する
                            	if( RESULT_BUF.ToIntDef(0) == 1 )
                                {
                                    if( iOK_FLG != -1 ) iOK_FLG = 1;
                                }
                                else
                                {
                                    if(iOK_FLG == 2 ) iOK_FLG = 0;
                                }
                            }
                            if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                                SOKU_VAL_SU ++;
                                iSOKU_VAL_SU ++;
                                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].RESULT).Trim().Length() == 0 )
                                {
                                    iOK_FLG = -1;
                                }
                            }
				        	break;
                     	case 3:
				        	RESULT_BUF = GetValidityData(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].RESULT),14);
                            if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                   	            SOKU_VAL_SU ++;
                                iSOKU_VAL_SU ++;
                            }
                           	break;
        				}
                    //表示用データの加工
        				switch( VALUE_TYPE )
		        		{
        				case 0:						//整数or少数
        				case 1:						//角度
		        			DISP_MAX = pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].MAX;
				        	DISP_MIN = pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].MIN;
        					if( iDEBUG != 1)
		        			{
                                bRtn = Form1->ConvDoubleDefS(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT),
                        								"0.00",
                                                        AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT),
                                                        &sBufConv);
                                if ( bRtn ) {
                                	DISP_RESULT = Form1->ConvDoubleDefD(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT),0.0);
                                } else {
						        	DISP_RESULT = 0.0;
        							bDISP_HANTEI = false;
                                }
        					}
		        			if( bRtn && AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
				        	{
                                switch(iKIKA_KIND)
                                {
                                case 1:
						            if( DISP_RESULT > DISP_MAX || DISP_RESULT < DISP_MIN )
                                    {
                                        if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                    }
                                    break;
		        				case 2:
	                            	if( DISP_RESULT > DISP_MAX  )
                                    {
                                        if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                    }
                                    break;
        						case 3:
	                            	if( DISP_RESULT < DISP_MIN )
                                    {
                                        if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                    }
                                    break;
                                }
        						if( DISP_FIRST_FLG == true )
                                {
        							DISP_VAL_MAX = DISP_RESULT;
		        					DISP_VAL_MIN = DISP_RESULT;
				        			DISP_FIRST_FLG = false;
						        }
        						else
		        				{
				        			if( DISP_RESULT > DISP_VAL_MAX ) DISP_VAL_MAX = DISP_RESULT;
						        	if( DISP_RESULT < DISP_VAL_MIN ) DISP_VAL_MIN = DISP_RESULT;
        						}
		        				DISP_GOUKEI_RESULT += DISP_RESULT;
                                iDISP_VAL_SU ++;
                            }
                            if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                                DISP_VAL_SU ++;
                                if(!bRtn) iDISP_OK_FLG = -1;
                            }
				        	break;
                        case 2:						//良、否
        					if( iDEBUG != 1 )
		        			{
	                    		try{
                                	// 良/否判定も未入力のまま保存させたいので DISP_RESULT_BUF を使って処理する
                                	DISP_RESULT_BUF = AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT);
        						}
		        				catch(EConvertError& e){
				        			bDISP_HANTEI = false;
        						}
		        				catch(...){
				        			bDISP_HANTEI = false;
        						}
		        			}
				        	if(bDISP_HANTEI && AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
        					{
                                // 良/否判定も未入力のまま保存させたいので DISP_RESULT_BUF を使って処理する
                                if( DISP_RESULT_BUF.ToIntDef(0) == 1 )
                                {
                                    if(iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                }
                                else
                                {
                                    if(iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                }
                            }
                            if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                                DISP_VAL_SU ++;
                                iDISP_VAL_SU ++;
                                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT).Trim().Length() == 0)
                                {
                                    iDISP_OK_FLG = -1;
                                }
                            }
		        			break;
             	        case 3:
		        			DISP_RESULT_BUF = GetValidityData(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].RESULT),14);
                            if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                           	    DISP_VAL_SU ++;
                                iDISP_VAL_SU ++;
                                if( iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT).Trim().Length() == 0)
                                {
                                    iDISP_OK_FLG = -1;
                                }
                            }
                           	break;
				        }

                		// 良/否判定も未入力のまま保存させたいので VALUE_TYPE = 2 の時でも RESULT_BUF を使って処理する
                		// イコール　case 2はコメント
                        switch( VALUE_TYPE )
                		{
                		case 0:
                		case 1:
                			if( bHANTEI ) RESULT_BUF 		= AnsiString(RESULT);
	    					if( !bHANTEI ) RESULT_BUF 		= "";
                		    break;
                		default:
                			break;
                		}
	    				switch( VALUE_TYPE )
                		{
                		case 0:
                		case 1:
                			if( bDISP_HANTEI ) DISP_RESULT_BUF 		= AnsiString(DISP_RESULT);
						    if( !bDISP_HANTEI ) DISP_RESULT_BUF 		= "";
                		    break;
                		default:
                			break;
                		}

                        if(bHANTEI == true || bHANTEI == false)
		        		{
	                        switch( i4 )
            	            {
                	        case 0:
            	            	strcpy(SetData.SOKU_VAL01 , AnsiString(RESULT_BUF).c_str());
			   			        strcpy(SetData.DISP_VAL01 , AnsiString(DISP_RESULT_BUF).c_str());
        			  			break;
	                        case 1:
				           		strcpy(SetData.SOKU_VAL02 , AnsiString(RESULT_BUF).c_str());
				  		        strcpy(SetData.DISP_VAL02 , AnsiString(DISP_RESULT_BUF).c_str());
        				 		break;
		        			case 2:
			   	        		strcpy(SetData.SOKU_VAL03 , AnsiString(RESULT_BUF).c_str());
			  			        strcpy(SetData.DISP_VAL03 , AnsiString(DISP_RESULT_BUF).c_str());
        		 				break;
		        			case 3:
		   		        		strcpy(SetData.SOKU_VAL04 , AnsiString(RESULT_BUF).c_str());
		  				        strcpy(SetData.DISP_VAL04 , AnsiString(DISP_RESULT_BUF).c_str());
        	 					break;
		        			case 4:
   				        		strcpy(SetData.SOKU_VAL05 , AnsiString(RESULT_BUF).c_str());
  						        strcpy(SetData.DISP_VAL05 , AnsiString(DISP_RESULT_BUF).c_str());
        	 					break;
    	                    case 5:
				           		strcpy(SetData.SOKU_VAL06 , AnsiString(RESULT_BUF).c_str());
				  		        strcpy(SetData.DISP_VAL06 , AnsiString(DISP_RESULT_BUF).c_str());
        			 			break;
		        			case 6:
			   	        		strcpy(SetData.SOKU_VAL07 , AnsiString(RESULT_BUF).c_str());
			  			        strcpy(SetData.DISP_VAL07 , AnsiString(DISP_RESULT_BUF).c_str());
        		 				break;
		        			case 7:
		   		        		strcpy(SetData.SOKU_VAL08 , AnsiString(RESULT_BUF).c_str());
		  				        strcpy(SetData.DISP_VAL08 , AnsiString(DISP_RESULT_BUF).c_str());
        	 					break;
		        			case 8:
   				        		strcpy(SetData.SOKU_VAL09 , AnsiString(RESULT_BUF).c_str());
  						        strcpy(SetData.DISP_VAL09 , AnsiString(DISP_RESULT_BUF).c_str());
        	 					break;
    	                    case 9:
				           		strcpy(SetData.SOKU_VAL10 , AnsiString(RESULT_BUF).c_str());
				  		        strcpy(SetData.DISP_VAL10 , AnsiString(DISP_RESULT_BUF).c_str());
        			 			break;
		        			default:  								//例外データ用ルーチンを考える
				        	    //KSD03に対し新規追加か更新かをチェックする
    					        sBuf  = "SELECT * FROM KSD03";
        						sBuf += " WHERE DTKSHIN = '" + AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].DTKSHIN)+ "'";
                        	    sBuf += " AND   LOTNO   = '" + AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].LOTNO) 	+ "'";
                        	    sBuf += " AND   HINBAN  = '" + AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].HINBAN) + "'";
				        		sBuf += " AND   UNQ_NO  =  " + AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UNQ_NO) ;
	     				        sBuf += " AND   SOKU_NO =  " + AnsiString(i3+1) ;
            				    // Initial Query
	            				Query1->Close();
    			        		Query1->SQL->Clear();
        				        Query1->SQL->Add(sBuf);
        	    				Query1->Open();
    	        				Query1->Active = true;

		                    	bNEW = false;
			    		        if( Query1->Eof == true ) bNEW = true;
        	    				Query1->Close();
		        				if( bNEW == true )
				        		{
                      	            //新規登録
		        	  				strcpy(SetData.DTKSHIN		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].DTKSHIN);
    	    	            		strcpy(SetData.LOTNO		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].LOTNO);
    	    	            		strcpy(SetData.HINBAN		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].HINBAN);
        	    		        	strcpy(SetData.UNQ_NO		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UNQ_NO);
        							sBuf = "insert into KSD03(";
    	                			sBuf += " DTKSHIN, LOTNO, HINBAN, UNQ_NO, SOKU_NO, SOKU_VAL, DISP_VAL";
	        	            		sBuf += " )";
		            	        	sBuf += " VALUES('";
        			            	sBuf += AnsiString(SetData.DTKSHIN)           	+ "','";	//	得意先品番
    	        		        	sBuf += AnsiString(SetData.LOTNO)	       		+ "','";	//	ロットNO
    	        		        	sBuf += AnsiString(SetData.HINBAN)	       		+ "', ";	//	工管発行日 onishi
        		        	    	sBuf += AnsiString(SetData.UNQ_NO)  			+ " , ";	//	明細NO
						        	sBuf += AnsiString(i3+1)						+ " ,'";	//	測定NO
        							sBuf += AnsiString(RESULT_BUF)                  + "','";	//	測定値
		        					sBuf += AnsiString(DISP_RESULT_BUF)				+ "') "; 	//	印刷用測定値
				        		}
						        else
        						{
                    	            //更新
					        		strcpy(SetData.DTKSHIN		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].DTKSHIN);
            		        		strcpy(SetData.LOTNO		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].LOTNO);
            		        		strcpy(SetData.HINBAN		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].HINBAN);
                		    		strcpy(SetData.UNQ_NO		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UNQ_NO);
				        			sBuf = "update KSD03 set ";
    				                sBuf += " DTKSHIN = '" 		+ AnsiString(SetData.DTKSHIN) 	+ "',"	;
        							sBuf += " LOTNO = 	'" 		+ AnsiString(SetData.LOTNO) 	+ "',"	;
        							sBuf += " HINBAN = 	'" 		+ AnsiString(SetData.HINBAN) 	+ "',"	;
		        					sBuf += " UNQ_NO = 	 " 		+ AnsiString(SetData.UNQ_NO) 	+ ","	;
			                      	sBuf += " SOKU_NO =  "		+ AnsiString(i3+1) 			   	+ " , " ;
    			                	sBuf += " SOKU_VAL = '"		+ AnsiString(RESULT_BUF) 		+ "'," ;
                			    	sBuf += " DISP_VAL = '"		+ AnsiString(DISP_RESULT_BUF) 	+ "'" ;
		        					sBuf += " WHERE DTKSHIN = '" + AnsiString(SetData.DTKSHIN)	+ "'";
                        	    	sBuf += " AND   LOTNO   = '" + AnsiString(SetData.LOTNO) 	+ "'";
                        	    	sBuf += " AND   HINBAN  = '" + AnsiString(SetData.HINBAN) 	+ "'";
						        	sBuf += " AND   UNQ_NO  = "  + AnsiString(SetData.UNQ_NO) 	 	 ;
            	 					sBuf += " AND   SOKU_NO = "  + AnsiString(i3+1) ;
		        				}
				        		//For Debug
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
        						// 問い合せ文の実行
		        	        	try{
        		        	    	Query1->ExecSQL();
		    	                }
                			    catch(EDatabaseError& e)
		                    	{
        		            		SBr1->Panels->Items[0]->Text = e.Message;
	                	        	SBr1->Update();
        			                return(false);
                			    }
		    	                catch(Exception& e)
        			            {
        		            		SBr1->Panels->Items[0]->Text = e.Message;
                		        	SBr1->Update();
	                        		return(false);
			                    }
        			   			break;
		          			}
				        	i4++;
        				}
                    }
                    //１項目のセーブ実行
        			strcpy(SetData.DTKSHIN		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].DTKSHIN);
                    strcpy(SetData.LOTNO		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].LOTNO);
                    strcpy(SetData.HINBAN		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].HINBAN);
                    strcpy(SetData.UNQ_NO		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UNQ_NO);
                    strcpy(SetData.ORDER_NO		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ORDER_NO);
                    strcpy(SetData.SKB_NO		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKB_NO);
                    strcpy(SetData.HINBAN_SK	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].HINBAN_SK);
                    strcpy(SetData.KOMK_NO		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KOMK_NO);
                    strcpy(SetData.KOMK_NM		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KOMK_NM);
                    strcpy(SetData.KOMK_ENG		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KOMK_ENG);
                    strcpy(SetData.KOMK_SUB		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KOMK_SUB);
                    strcpy(SetData.KOMK_SUB_ENG	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KOMK_SUB_ENG);
                    strcpy(SetData.KIKI_NO		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKI_NO);
                    strcpy(SetData.KIKI_NM		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKI_NM);
                    strcpy(SetData.TANI			,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].TANI);
                    strcpy(SetData.KIKA_TYPE	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKA_TYPE);
                    strcpy(SetData.KIKA_KIND	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKA_KIND);
                    strcpy(SetData.KIKA_DECI	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKA_DECI);
                    strcpy(SetData.KIKA_NUM1	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKA_NUM1);
                    strcpy(SetData.KIKA_NUM2	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKA_NUM2);
                    strcpy(SetData.KIKA_NUM3	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKA_NUM3);
                    strcpy(SetData.KIKA_STR		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKA_STR);
                    strcpy(SetData.KIKA_SUB1	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKA_SUB1);
                    strcpy(SetData.KIKA_SUB2	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKA_SUB2);
                    strcpy(SetData.KIKA_SUB3	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKA_SUB3);
                    strcpy(SetData.SOKU_SU		,AnsiString(iSIJI_NSU).c_str());
                    strcpy(SetData.SOKU_FLG		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SOKU_FLG);
                    strcpy(SetData.TOKU_FLG		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].TOKU_FLG);
                    strcpy(SetData.KIKA_PRT		,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].KIKA_PRT);
                    strcpy(SetData.VALUE_TYPE	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].VALUE_TYPE);
                    strcpy(SetData.VALUE_DECI	,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].VALUE_DECI);
                    strcpy(SetData.SOKU_VAL_SU		,AnsiString(iSIJI_NSU).c_str());
        			if( iSOKU_VAL_SU > 0) {
		        		SOKU_VAL_AVE = GOUKEI_RESULT / iSOKU_VAL_SU;
        			}
                    else {
				        SOKU_VAL_AVE = 0;
                    }
		        	if( SOKU_VAL_AVE > 9999999.999999 ) SOKU_VAL_AVE = 9999999.999999;
        			if( SOKU_VAL_MAX > 9999999.99999  ) SOKU_VAL_MAX = 9999999.99999 ;
		        	if( SOKU_VAL_MIN > 9999999.99999  ) SOKU_VAL_MIN = 9999999.99999 ;
        			strcpy(SetData.SOKU_VAL_AVE	,AnsiString(SOKU_VAL_AVE).SubString(1,14).c_str());
		        	strcpy(SetData.SOKU_VAL_MAX ,AnsiString(SOKU_VAL_MAX).SubString(1,14).c_str());
        			strcpy(SetData.SOKU_VAL_MIN ,AnsiString(SOKU_VAL_MIN).SubString(1,14).c_str());
                    strcpy(SetData.SOKU_OK,AnsiString(iOK_FLG).c_str());
                    strcpy(SetData.DISP_VAL_SU	   ,AnsiString(iSIJI_NSU).c_str());
        			if( iDISP_VAL_SU > 0) {
		        		DISP_VAL_AVE = DISP_GOUKEI_RESULT / iDISP_VAL_SU;
			        }
        			else
		        	{
				        DISP_VAL_AVE = 0;
        			}
		        	if( DISP_VAL_AVE > 9999999.999999 ) DISP_VAL_AVE = 9999999.999999;
        			if( DISP_VAL_MAX > 9999999.99999  ) DISP_VAL_MAX = 9999999.99999 ;
		        	if( DISP_VAL_MIN > 9999999.99999  ) DISP_VAL_MIN = 9999999.99999 ;
        			strcpy(SetData.DISP_VAL_AVE	,AnsiString(DISP_VAL_AVE).SubString(1,14).c_str());
		        	strcpy(SetData.DISP_VAL_MAX ,AnsiString(DISP_VAL_MAX).SubString(1,14).c_str());
        			strcpy(SetData.DISP_VAL_MIN ,AnsiString(DISP_VAL_MIN).SubString(1,14).c_str());
                    strcpy(SetData.DISP_OK,AnsiString(iDISP_OK_FLG).c_str());
        			i4 = AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCNT).ToIntDef(0)+1;
        			strcpy(SetData.UPDCNT ,AnsiString(i4).c_str());
    		        sBuf = "SELECT * FROM KSD02";
		        	sBuf += " WHERE DTKSHIN = '" + sNowDTKSHIN + "'";
        			sBuf += " AND   UNQ_NO  = "  + AnsiString(iUNQNO) ;
    	        	sBuf += " AND   SKB_NO  = 1";                        //出荷検査項目、材料証明項目
    		        sBuf += " AND   LOTNO   = '" + AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].LOTNO) + "'";
    		        sBuf += " AND   HINBAN  = '" + AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].HINBAN) + "'";

			        // Initial Query
        	    	Query3->Close();
    	        	Query3->SQL->Clear();
                	Query3->SQL->Add(sBuf);
    	        	Query3->Open();
            		Query3->Active = true;

                    bNEW = false;
	    	        if( Query3->Eof == true ) bNEW = true;
	    	        Query3->Close();
			        if( bNEW == true )										//新規登録
                    {
                        // 測定日
				        strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKTYMD,FormatDateTime("yyyymmdd",Date()).c_str());
                        // 登録日
				        strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
                        // 登録時間
				        strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
                        // 変更日
        				strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
                        // 変更時間
        				strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
                        // 更新者
        				if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCHR).Trim().Length() == 0){
    	            		strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCHR,AnsiString(Form1->USER_COD).c_str());
				        }
                        // 更新回数
        				strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCNT,"0");

                        //セーブ用バッファにコピー
                        // 測定日
        				strcpy(SetData.SKTYMD,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKTYMD);
                        // 登録日
           				strcpy(SetData.ADDYMD,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDYMD);
                        // 登録時間
        				strcpy(SetData.ADDTIM,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDTIM);
                        // 変更日
        				strcpy(SetData.UPDYMD,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDYMD);
                        // 変更時間
        				strcpy(SetData.UPDTIM,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDTIM);
                        // 更新者
        				strcpy(SetData.UPDCHR,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCHR);
                        // 更新回数
        				strcpy(SetData.UPDCNT,pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCNT);
                        // 問合せ文作成(KSD02)
        				sBuf = "insert into KSD02(";
    	                sBuf += " DTKSHIN, LOTNO, HINBAN, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK, KOMK_NO, KOMK_NM,";
        	            sBuf += " KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI,";
        	            sBuf += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3,";
    	                sBuf += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3, SOKU_SU, SOKU_FLG,";
        	            sBuf += " TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI,";
                    	sBuf += " SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05,";
	                    sBuf += " SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,";
    	                sBuf += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK,";
                	    sBuf += " DISP_VAL01, DISP_VAL02, DISP_VAL03, DISP_VAL04, DISP_VAL05,";
                    	sBuf += " DISP_VAL06, DISP_VAL07, DISP_VAL08, DISP_VAL09, DISP_VAL10,";
	                    sBuf += " DISP_VAL_SU, DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, DISP_OK,";
            	        sBuf += " SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
                	    sBuf += " )";
            	        sBuf += " VALUES('";
        	            sBuf += AnsiString(SetData.DTKSHIN)           	+ "','";	//	得意先品番
    	                sBuf += AnsiString(SetData.LOTNO)	       		+ "','";	//	ロットNO
    	                sBuf += AnsiString(SetData.HINBAN)	       		+ "', ";	//	工管発行日 onishi
        	            sBuf += AnsiString(SetData.UNQ_NO)  			+ " , ";	//	明細NO
                    	sBuf += AnsiString(SetData.ORDER_NO)  			+ " , ";	//	明細NO
	                    sBuf += AnsiString(SetData.SKB_NO)  			+ " ,'";	//	識別NO
    	                sBuf += AnsiString(SetData.HINBAN_SK) 			+ "', ";
                	    sBuf += AnsiString(SetData.KOMK_NO) 			+ " ,'";	//	測定項目NO
	                    sBuf += AnsiString(SetData.KOMK_NM)	       		+ "','";	//	測定項目名称
    	                sBuf += AnsiString(SetData.KOMK_ENG)       		+ "','";
                	    sBuf += AnsiString(SetData.KOMK_SUB)	   		+ "','";	//	測定項目名称
                    	sBuf += AnsiString(SetData.KOMK_SUB_ENG)   		+ "', ";	//	測定項目名称
	                    sBuf += AnsiString(SetData.KIKI_NO) 			+ " ,'";	//	測定機器NO
            	        sBuf += AnsiString(SetData.KIKI_NM)	       		+ "','";	//	測定機器名称
                	    sBuf += AnsiString(SetData.TANI)   	       		+ "', ";	//	単位
            	        sBuf += AnsiString(SetData.KIKA_TYPE) + " , ";
        	            sBuf += AnsiString(SetData.KIKA_KIND) + " , ";
    	                sBuf += AnsiString(SetData.KIKA_DECI) + " , ";
        	            sBuf += AnsiString(SetData.KIKA_NUM1) + " , ";
                    	sBuf += AnsiString(SetData.KIKA_NUM2) + " , ";
	                    sBuf += AnsiString(SetData.KIKA_NUM3) + " ,'";
    	                sBuf += AnsiString(SetData.KIKA_STR)            + "','";
                	    sBuf += AnsiString(SetData.KIKA_SUB1)           + "','";
                    	sBuf += AnsiString(SetData.KIKA_SUB2)           + "','";
	                    sBuf += AnsiString(SetData.KIKA_SUB3)           + "', ";
            	        sBuf += AnsiString(SetData.SOKU_SU) 	+ " , ";	//    　測定指示ｎ数
                	    sBuf += AnsiString(SetData.SOKU_FLG) 	+ " , ";	//    　測定指示ｎ数
            	        sBuf += AnsiString(SetData.TOKU_FLG) 	+ " , ";	//    　測定指示ｎ数
        	            sBuf += AnsiString(SetData.KIKA_PRT) 	+ " , ";	//    　測定指示ｎ数
    	                sBuf += AnsiString(SetData.VALUE_TYPE)+ " , ";	//    　測定指示ｎ数
        	            sBuf += AnsiString(SetData.VALUE_DECI)+ " ,'";	//    　測定指示ｎ数
                    	sBuf += AnsiString(SetData.SOKU_VAL01)        	+ "','";	//	測定値１
	                    sBuf += AnsiString(SetData.SOKU_VAL02)        	+ "','";	//      測定値２　　　
    	                sBuf += AnsiString(SetData.SOKU_VAL03)        	+ "','";	//	測定値３
                	    sBuf += AnsiString(SetData.SOKU_VAL04)        	+ "','";	//	測定値４
                    	sBuf += AnsiString(SetData.SOKU_VAL05)        	+ "','";	//	測定値５
	                    sBuf += AnsiString(SetData.SOKU_VAL06)        	+ "','";	//	測定値６
            	        sBuf += AnsiString(SetData.SOKU_VAL07)        	+ "','";	//	測定値７
                	    sBuf += AnsiString(SetData.SOKU_VAL08)        	+ "','";	//	測定値８
	                    sBuf += AnsiString(SetData.SOKU_VAL09)        	+ "','";	//	測定値９
            	        sBuf += AnsiString(SetData.SOKU_VAL10)        	+ "', ";	//	測定値１０
                	    sBuf += AnsiString(SetData.SOKU_VAL_SU)+ " , ";	//    　測定指示ｎ数
            	        sBuf += AnsiString(SetData.SOKU_VAL_AVE)+ " , ";	//    　測定指示ｎ数
        	            sBuf += AnsiString(SetData.SOKU_VAL_MAX)+ " , ";	//    　測定指示ｎ数
    	                sBuf += AnsiString(SetData.SOKU_VAL_MIN)+ " , ";	//    　測定指示ｎ数
        	            sBuf += AnsiString(SetData.SOKU_OK)   + " ,'";	//	測定値１０
                    	sBuf += AnsiString(SetData.DISP_VAL01)        	+ "','";	//	測定値１
	                    sBuf += AnsiString(SetData.DISP_VAL02)        	+ "','";	//      測定値２　　　
    	                sBuf += AnsiString(SetData.DISP_VAL03)        	+ "','";	//	測定値３
                	    sBuf += AnsiString(SetData.DISP_VAL04)        	+ "','";	//	測定値４
                    	sBuf += AnsiString(SetData.DISP_VAL05)        	+ "','";	//	測定値５
	                    sBuf += AnsiString(SetData.DISP_VAL06)        	+ "','";	//	測定値６
            	        sBuf += AnsiString(SetData.DISP_VAL07)        	+ "','";	//	測定値７
                	    sBuf += AnsiString(SetData.DISP_VAL08)        	+ "','";	//	測定値８
            	        sBuf += AnsiString(SetData.DISP_VAL09)        	+ "','";	//	測定値９
        	            sBuf += AnsiString(SetData.DISP_VAL10)        	+ "', ";	//	測定値１０
    	                sBuf += AnsiString(SetData.DISP_VAL_SU)+ " , ";	//    　測定指示ｎ数
        	            sBuf += AnsiString(SetData.DISP_VAL_AVE)+ " , ";	//    　測定指示ｎ数
                    	sBuf += AnsiString(SetData.DISP_VAL_MAX)+ " , ";	//    　測定指示ｎ数
	                    sBuf += AnsiString(SetData.DISP_VAL_MIN)+ " , ";	//    　測定指示ｎ数
    	                sBuf += AnsiString(SetData.DISP_OK)  + " ,'";	//	測定値１０
                	    sBuf += AnsiString(SetData.SKTYMD)   	       + "','";	//	測定日
                    	sBuf += AnsiString(SetData.ADDYMD)   	       + "','";	//	登録日
	                    sBuf += AnsiString(SetData.ADDTIM)   	       + "','";	//	登録時間
            	        sBuf += AnsiString(SetData.UPDYMD)   	       + "','";	//	変更日
                	    sBuf += AnsiString(SetData.UPDTIM)   	       + "',";	//	変更時間
            	        sBuf += AnsiString(SetData.UPDCHR)  	       + ",";  	//	更新回数
                    	sBuf += AnsiString(SetData.UPDCNT);  	         		//	更新回数
	                    sBuf += ")";
        			}
        			else
		        	{
                        // 測定日（登録日と同じ)
        				strcpy(SetData.SKTYMD,AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SKTYMD).c_str());
                        // 登録日
        				strcpy(SetData.ADDYMD,AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDYMD).c_str());
                        // 登録時間
        				strcpy(SetData.ADDTIM,AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].ADDTIM).c_str());
                        // 変更日
        				strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
		        		strcpy(SetData.UPDYMD,AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDYMD).c_str());
                        // 変更時間
        				strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
		        		strcpy(SetData.UPDTIM,AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDTIM).c_str());
                        // 更新者
        				if(AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCHR).Length() == 0)
		        		{
    	    	        	strcpy(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCHR,AnsiString(Form1->USER_COD).c_str());
        				}
		        		strcpy(SetData.UPDCHR,AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].UPDCHR).c_str());
                        // 更新回数
                        //				strcpy(SetData.UPDCNT,"0");
				        sBuf = "update KSD02 set ";
                        //田村様の指示によりコメント
                        //sBuf += " DTKSHIN = '" 		+ AnsiString(SetData.DTKSHIN) + "',"	;
                        //sBuf += " LOTNO = '" 		+ AnsiString(SetData.LOTNO) + "',"	;
                        //sBuf += " UNQ_NO = " 		+ AnsiString(SetData.UNQ_NO) + ","	;
        				sBuf += " ORDER_NO = " 		+ AnsiString(SetData.ORDER_NO) + ","	;
		        		sBuf += " SKB_NO = " 		+ AnsiString(SetData.SKB_NO) + ","	;
				        sBuf += " HINBAN_SK = '" 	+ AnsiString(SetData.HINBAN_SK) + "',"	;
        				sBuf += " KOMK_NO = " 		+ AnsiString(SetData.KOMK_NO) + ","	;
		        		sBuf += " KOMK_NM = '" 		+ AnsiString(SetData.KOMK_NM) + "',"	;
        	            sBuf += " KOMK_ENG = '" 	+ AnsiString(SetData.KOMK_ENG) + "',"	;
        				sBuf += " KOMK_SUB = '" 	+ AnsiString(SetData.KOMK_SUB) + "',"	;
		        		sBuf += " KOMK_SUB_ENG = '" + AnsiString(SetData.KOMK_SUB_ENG) + "',"	;
				        sBuf += " KIKI_NO = " 		+ AnsiString(SetData.KIKI_NO) + ","	;
        				sBuf += " KIKI_NM = '" 		+ AnsiString(SetData.KIKI_NM) + "',"	;
		        		sBuf += " TANI = '" 		+ AnsiString(SetData.TANI) + "',"	;
	                    sBuf += " KIKA_TYPE = " 	+ AnsiString(SetData.KIKA_TYPE) + ","	;
        				sBuf += " KIKA_KIND = " 	+ AnsiString(SetData.KIKA_KIND) + ","	;
		        		sBuf += " KIKA_DECI = " 	+ AnsiString(SetData.KIKA_DECI) + ","	;
				        sBuf += " KIKA_NUM1 = " 	+ AnsiString(SetData.KIKA_NUM1) + ","	;
        				sBuf += " KIKA_NUM2 = " 	+ AnsiString(SetData.KIKA_NUM2) + ","	;
		        		sBuf += " KIKA_NUM3 = " 	+ AnsiString(SetData.KIKA_NUM3) + ","	;
    	                sBuf += " KIKA_STR = '"  	+ AnsiString(SetData.KIKA_STR) + "',"	;
        				sBuf += " KIKA_SUB1 = '" 	+ AnsiString(SetData.KIKA_SUB1) + "',"	;
		        		sBuf += " KIKA_SUB2 = '" 	+ AnsiString(SetData.KIKA_SUB2) + "',"	;
				        sBuf += " KIKA_SUB3 = '" 	+ AnsiString(SetData.KIKA_SUB3) + "',"	;
        				sBuf += " SOKU_SU = " 	 	+ AnsiString(SetData.SOKU_SU) + ","	;
                        sBuf += " SOKU_FLG = "  	+ AnsiString(SetData.SOKU_FLG) + ","	;
        	            sBuf += " TOKU_FLG = "  	+ AnsiString(SetData.TOKU_FLG) + ","	;
        				sBuf += " KIKA_PRT = "  	+ AnsiString(SetData.KIKA_PRT) + ","	;
		        		sBuf += " VALUE_TYPE = " 	+ AnsiString(SetData.VALUE_TYPE) + ","	;
				        sBuf += " VALUE_DECI = " 	+ AnsiString(SetData.VALUE_DECI) + ","	;
                    	sBuf += " SOKU_VAL01 = '" 	+ AnsiString(SetData.SOKU_VAL01) + "',"	;
		        		sBuf += " SOKU_VAL02 = '" 	+ AnsiString(SetData.SOKU_VAL02) + "',"	;
				        sBuf += " SOKU_VAL03 = '" 	+ AnsiString(SetData.SOKU_VAL03) + "',"	;
        				sBuf += " SOKU_VAL04 = '" 	+ AnsiString(SetData.SOKU_VAL04) + "',"	;
		        		sBuf += " SOKU_VAL05 = '" 	+ AnsiString(SetData.SOKU_VAL05) + "',"	;
	                    sBuf += " SOKU_VAL06 = '" 	+ AnsiString(SetData.SOKU_VAL06) + "',"	;
        				sBuf += " SOKU_VAL07 = '" 	+ AnsiString(SetData.SOKU_VAL07) + "',"	;
		        		sBuf += " SOKU_VAL08 = '" 	+ AnsiString(SetData.SOKU_VAL08) + "',"	;
				        sBuf += " SOKU_VAL09 = '" 	+ AnsiString(SetData.SOKU_VAL09) + "',"	;
        				sBuf += " SOKU_VAL10 = '" 	+ AnsiString(SetData.SOKU_VAL10) + "',"	;
    	                sBuf += " SOKU_VAL_SU = "  	+ AnsiString(SetData.SOKU_VAL_SU) + ","	;
				        sBuf += " SOKU_VAL_AVE = " 	+ AnsiString(SetData.SOKU_VAL_AVE) + ","	;
        				sBuf += " SOKU_VAL_MAX = " 	+ AnsiString(SetData.SOKU_VAL_MAX) + ","	;
		        		sBuf += " SOKU_VAL_MIN = " 	+ AnsiString(SetData.SOKU_VAL_MIN) + ","	;
				        sBuf += " SOKU_OK = " 	  	+ AnsiString(SetData.SOKU_OK) + ","	;
                	    sBuf += " DISP_VAL01 = '" 	+ AnsiString(SetData.DISP_VAL01) + "',"	;
		        		sBuf += " DISP_VAL02 = '" 	+ AnsiString(SetData.DISP_VAL02) + "',"	;
				        sBuf += " DISP_VAL03 = '" 	+ AnsiString(SetData.DISP_VAL03) + "',"	;
        				sBuf += " DISP_VAL04 = '" 	+ AnsiString(SetData.DISP_VAL04) + "',"	;
		        		sBuf += " DISP_VAL05 = '" 	+ AnsiString(SetData.DISP_VAL05) + "',"	;
            	        sBuf += " DISP_VAL06 = '" 	+ AnsiString(SetData.DISP_VAL06) + "',"	;
        				sBuf += " DISP_VAL07 = '" 	+ AnsiString(SetData.DISP_VAL07) + "',"	;
		        		sBuf += " DISP_VAL08 = '" 	+ AnsiString(SetData.DISP_VAL08) + "',"	;
                        sBuf += " DISP_VAL09 = '" 	+ AnsiString(SetData.DISP_VAL09) + "',"	;
        				sBuf += " DISP_VAL10 = '" 	+ AnsiString(SetData.DISP_VAL10) + "',"	;
	                    sBuf += " DISP_VAL_SU = "  	+ AnsiString(SetData.DISP_VAL_SU) + ","	;
				        sBuf += " DISP_VAL_AVE = " 	+ AnsiString(SetData.DISP_VAL_AVE) + ","	;
        				sBuf += " DISP_VAL_MAX = " 	+ AnsiString(SetData.DISP_VAL_MAX) + ","	;
		        		sBuf += " DISP_VAL_MIN = " 	+ AnsiString(SetData.DISP_VAL_MIN) + ","	;
				        sBuf += " DISP_OK = " 		+ AnsiString(SetData.DISP_OK) + ","	;
            	        sBuf += " SKTYMD = '" 		+ AnsiString(SetData.SKTYMD) + "',"	;
		        		sBuf += " ADDYMD = '" 		+ AnsiString(SetData.ADDYMD) + "',"	;
				        sBuf += " ADDTIM = '" 		+ AnsiString(SetData.ADDTIM) + "',"	;
        				sBuf += " UPDYMD = '" 		+ AnsiString(SetData.UPDYMD) + "',"	;
		        		sBuf += " UPDTIM = '" 		+ AnsiString(SetData.UPDTIM) + "',"	;
				        sBuf += " UPDCHR = " 		+ AnsiString(SetData.UPDCHR) + ","	;
        				sBuf += " UPDCNT = " 		+ AnsiString(SetData.UPDCNT) + " "	;
     	        		sBuf += " WHERE DTKSHIN='" 	+ AnsiString(SetData.DTKSHIN) + "'";
     			        sBuf += " AND   LOTNO  ='" 	+ AnsiString(SetData.LOTNO)  + "'";
     			        sBuf += " AND   HINBAN ='" 	+ AnsiString(SetData.HINBAN) + "'";
             			sBuf += " AND   UNQ_NO = " 	+ AnsiString(SetData.UNQ_NO) ;
		        	}
                    //For Debug
                    if( iDEBUG == 1 )
                    {
                	    ClpBrd = Clipboard();
     	        	    ClpBrd->Open();
             		    ClpBrd->SetTextBuf(sBuf.c_str());
     	        	    ClpBrd->Close();
                    }
        		    // Initial Query
                	Query3->Close();
                    Query3->SQL->Clear();
                    Query3->SQL->Add(sBuf);
        		    // 問い合せ文の実行
                    try{
            	        Query3->ExecSQL();
                    }
                    catch(EDatabaseError& e)
                    {
            	        SBr1->Panels->Items[0]->Text = e.Message;
                        SBr1->Update();
                        return(false);
                    }
                    catch(Exception& e)
                    {
                    	SBr1->Panels->Items[0]->Text = e.Message;
                        SBr1->Update();
                        return(false);
                    }
			    }
			    iRow +=  AnsiString(pCELLINFO_SOKU_SOZAI[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);
            }
        }
	}
    Query3->Close();
    return(true);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材（履歴）データ、データベース登録
//
//  機能説明
//    更新か新規かの確認を行った後でデータベースへの登録作業を行います。
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
bool __fastcall TForm1::Set_DB_RIRE_SOZAI(void)
{
    int i3,i4;//i1,i2,
    int iUNQNO;
    int iKIKA_KIND;
    //セーブ時使用変数一覧
	int iRow,iCol;
	int iRowCount;
    int iSOKUSU;
	int VALUE_TYPE;
	int SOKU_VAL_SU,DISP_VAL_SU;
	int iSOKU_VAL_SU,iDISP_VAL_SU;
    int iSIJI_NSU;
    AnsiString RESULT_BUF,DISP_RESULT_BUF,sMEMO;
	double SOKU_VAL_AVE,SOKU_VAL_MAX,SOKU_VAL_MIN;
	double DISP_VAL_AVE,DISP_VAL_MAX,DISP_VAL_MIN;
	double RESULT,GOUKEI_RESULT,DISP_RESULT,DISP_GOUKEI_RESULT;
    double SOKU_MAX,SOKU_MIN;
    double DISP_MAX,DISP_MIN;
    int iRESULT,iDISP_RESULT;
    int iOK_FLG,iDISP_OK_FLG;
	bool FIRST_FLG,DISP_FIRST_FLG;
	bool bNEW;						//新規追加フラグ
	bool bHANTEI,bDISP_HANTEI;
    bool bRtn;				//2003.05.08 E.Takase Add
    AnsiString sBufConv;	//2003.05.08 E.Takase Add


    AnsiString sBuf,sLot,sTempBuf;
    KSD02_DATA SetData;

	if(!hCELLINFO_RIRE_SOZAI) return(true);
	if(SGr_tRIRE->Cells[0][0].Length() == 0 ) return(true);
    if(Form1->iRIRE_CNT == 0 ) return(true);

    //KSD02の更新(新規登録の場合)

	iRowCount = SGr_vRIRE_SOZAI->RowCount;
	for(iCol = 0; iCol < SGr_vRIRE_SOZAI->ColCount;iCol++)
	{
		if(pRIRE_KSD01_DATA[iCol].UPD_FLG == false)
        {
		}
		else
		{
		pRIRE_KSD01_DATA[iCol].UPD_FLG == false;
		for( iRow = 1;iRow < iRowCount; iRow=iRow)
		{
			iSOKUSU 	= AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);
			VALUE_TYPE 	= AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].VALUE_TYPE).ToIntDef(0);
			iUNQNO 		= AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UNQ_NO).ToIntDef(0);
			if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KOMK_NO).ToIntDef(0)==-999)
			{
			}
			else
			{
            //実際の指示数を検出します
                iSIJI_NSU = 0;
                for(i3=0; i3 < AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);i3++)
                {
                    if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].KOMK_NO).ToIntDef(0) == -999) break;
                    iSIJI_NSU ++;
                }
                iSOKUSU=iSIJI_NSU;
                //KSD03（例外データ）削除
                sBuf = "";
                sBuf = "DELETE FROM KSD03";
                sBuf +=	" where DTKSHIN='" + AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].DTKSHIN)+ "'";
                sBuf += " and   LOTNO  ='" + AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].LOTNO)  + "'";
                sBuf += " and   HINBAN ='" + AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].HINBAN) + "'";
                sBuf += " and   UNQ_NO = " + AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UNQ_NO) ;
                //For Debug
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
                // 問い合せ文の実行
                try{
                    Query1->ExecSQL();
                }
                catch(EDatabaseError& e)
                {
                    SBr1->Panels->Items[0]->Text = e.Message;
                    SBr1->Update();
                    return(false);
                }
                catch(Exception& e)
                {
                    SBr1->Panels->Items[0]->Text = e.Message;
                    SBr1->Update();
                    return(false);
                }
                ///////////////////////////////////////////////
    			SOKU_VAL_SU = 0;
	    		DISP_VAL_SU = 0;
		    	iSOKU_VAL_SU = 0;
			    iDISP_VAL_SU = 0;
                GOUKEI_RESULT = 0;
                DISP_GOUKEI_RESULT = 0;
		    	SOKU_MAX = 0.0;
			    DISP_MAX = 0.0;
    			SOKU_MIN = 0.0;
	    		DISP_MIN = 0.0;
		    	SOKU_VAL_MAX = 0;
			    SOKU_VAL_MIN = 0;
    			DISP_VAL_MAX = 0;
	    		DISP_VAL_MIN = 0;
                iOK_FLG = 2;
                iDISP_OK_FLG = 2;
    			FIRST_FLG 	= true;
	    		DISP_FIRST_FLG = true;
		    	RESULT = 0;
			    DISP_RESULT = 0;
            //測定値初期化
    			strcpy(SetData.SOKU_VAL01 , "");
	    		strcpy(SetData.SOKU_VAL02 , "");
		    	strcpy(SetData.SOKU_VAL03 , "");
			    strcpy(SetData.SOKU_VAL04 , "");
    			strcpy(SetData.SOKU_VAL05 , "");
	    		strcpy(SetData.SOKU_VAL06 , "");
		    	strcpy(SetData.SOKU_VAL07 , "");
			    strcpy(SetData.SOKU_VAL08 , "");
    			strcpy(SetData.SOKU_VAL09 , "");
	    		strcpy(SetData.SOKU_VAL10 , "");
            //印刷値初期化
    			strcpy(SetData.DISP_VAL01 , "");
	    		strcpy(SetData.DISP_VAL02 , "");
		    	strcpy(SetData.DISP_VAL03 , "");
			    strcpy(SetData.DISP_VAL04 , "");
    			strcpy(SetData.DISP_VAL05 , "");
	    		strcpy(SetData.DISP_VAL06 , "");
		    	strcpy(SetData.DISP_VAL07 , "");
			    strcpy(SetData.DISP_VAL08 , "");
    			strcpy(SetData.DISP_VAL09 , "");
	    		strcpy(SetData.DISP_VAL10 , "");

                i4 = 0;
                for( i3 = 0; i3 < iSOKUSU;i3++)
                {
            //以上以下の規格の場合対策 ///////////////////////////////////////////
                    iKIKA_KIND = 1;		//デフォルトは上下限で判定
	        	    if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].KIKA_TYPE) == 1)
                    {
			            if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].KIKA_KIND) == 2)
			            {
				            iKIKA_KIND = 2;
        			    }
            			else if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].KIKA_KIND) == 3)
	            		{
		            		iKIKA_KIND = 3;
			            }
            		}
                    ////////////////////////////////////////////////////////////////////
                    //測定用データ
        				bHANTEI = true;
		        		bDISP_HANTEI = true;
				        switch( VALUE_TYPE )
        				{
		        		case 0:						//整数or少数
				        case 1:						//角度
				        	SOKU_MAX = pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].MAX;
        					SOKU_MIN = pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].MIN;
                            if( iDEBUG != 1 )
				        	{
                                bRtn = Form1->ConvDoubleDefS(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].RESULT),
                        								"0.00",
                                                        AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].RESULT),
                                                        &sBufConv);
                                if ( bRtn ) {
                        	        RESULT = Form1->ConvDoubleDefD(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].RESULT),0.0);
                                } else {
							        RESULT = 0.0;
							        bHANTEI = false;
                                }
					        }
        					if( bRtn && AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
		        			{
                                switch(iKIKA_KIND)
                                {
                                case 1:
				        		    if( RESULT > SOKU_MAX || RESULT < SOKU_MIN )
                                    {
                                        if(iOK_FLG != -1 ) iOK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iOK_FLG == 2 ) iOK_FLG = 0;
                                    }
                                    break;
        						case 2:
	                            	if( RESULT > SOKU_MAX  )
                                    {
                                        if(iOK_FLG != -1 ) iOK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iOK_FLG == 2 ) iOK_FLG = 0;
                                    }
                                    break;
						        case 3:
        	                    	if( RESULT < SOKU_MIN )
                                    {
                                        if(iOK_FLG != -1 ) iOK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iOK_FLG == 2 ) iOK_FLG = 0;
                                    }
                                    break;
                                }
						        if( FIRST_FLG == true ){
        							SOKU_VAL_MAX = RESULT;
		        					SOKU_VAL_MIN = RESULT;
				        			FIRST_FLG = false;
						        }
        						else
		        				{
				        			if( RESULT > SOKU_VAL_MAX ) SOKU_VAL_MAX = RESULT;
						        	if( RESULT < SOKU_VAL_MIN ) SOKU_VAL_MIN = RESULT;
        						}
		        				GOUKEI_RESULT += RESULT;
                                iSOKU_VAL_SU++;
                            }
                            if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                                SOKU_VAL_SU ++;
                                if(!bRtn) iOK_FLG = -1;
                            }
		        			break;
                        case 2:						//良、否
                            if(iDEBUG != 1)
				        	{
						        try{
                                	// 良/否判定も未入力のまま保存させたいので RESULT_BUF を使って処理する
                                	RESULT_BUF = AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].RESULT);
        						}
				        		catch(EConvertError& e){
						        	bHANTEI = false;
		        				}
				        		catch(...){
						        	bHANTEI = false;
		        				}
                            }
        					if(bHANTEI && AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
		        			{
                                // 良/否判定も未入力のまま保存させたいので RESULT_BUF を使って処理する
                                if( RESULT_BUF.ToIntDef(0) == 1 )
                                {
                                    if(iOK_FLG != -1 ) iOK_FLG = 1;
                                }
                                else
                                {
                                    if(iOK_FLG == 2 ) iOK_FLG = 0;
                                }
                            }
                            if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                                SOKU_VAL_SU ++;
                                iSOKU_VAL_SU ++;
                                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].RESULT).Trim().Length()==0)
                                {
                                    iOK_FLG = -1;
                                }
                            }
				        	break;
                     	case 3:
		        			RESULT_BUF = GetValidityData(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].RESULT),14);
                            if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                                SOKU_VAL_SU ++;
                                iSOKU_VAL_SU ++;
                                if( iOK_FLG == 2 ) iOK_FLG = 0;
                                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].RESULT).Trim().Length() == 0 )
                                {
                                    iOK_FLG = -1;
                                }
                            }
                           	break;
				        }
                    //表示用データの加工
        				switch( VALUE_TYPE )
		        		{
				        case 0:						//整数or少数
				        case 1:						//角度
        					DISP_MAX = pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].MAX;
		        			DISP_MIN = pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].MIN;
				        	if( iDEBUG != 1)
        					{
                                bRtn = Form1->ConvDoubleDefS(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT),
                        								"0.00",
                                                        AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT),
                                                        &sBufConv);
                                if ( bRtn ) {
                                	DISP_RESULT = Form1->ConvDoubleDefD(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT),0.0);
                                } else {
						        	DISP_RESULT = 0.0;
        							bDISP_HANTEI = false;
                                }
					        }
        					if( bRtn && AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
		        			{
                                switch(iKIKA_KIND)
                                {
                                case 1:
		        				    if( DISP_RESULT > DISP_MAX || DISP_RESULT < DISP_MIN )
                                    {
                                        if(iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                    }
                                    break;
						        case 2:
        	                    	if( DISP_RESULT > DISP_MAX  )
                                    {
                                        if(iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                    }
                                    break;
				        		case 3:
	                            	if( DISP_RESULT < DISP_MIN )
                                    {
                                        if(iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                    }
                                    else
                                    {
                                        if(iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                    }
                                    break;
                                }
        						if( DISP_FIRST_FLG == true ){
		        					DISP_VAL_MAX = DISP_RESULT;
				        			DISP_VAL_MIN = DISP_RESULT;
						        	DISP_FIRST_FLG = false;
        						}
		        				else
				        		{
						        	if( DISP_RESULT > DISP_VAL_MAX ) DISP_VAL_MAX = DISP_RESULT;
        							if( DISP_RESULT < DISP_VAL_MIN ) DISP_VAL_MIN = DISP_RESULT;
		        				}
				        		DISP_GOUKEI_RESULT += DISP_RESULT;
                                iDISP_VAL_SU ++;
        					}
                            if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                                DISP_VAL_SU ++;
                                if(!bRtn) iDISP_OK_FLG = -1;
                            }
		        			break;
                        case 2:						//良、否
        					if( iDEBUG != 1)
		        			{
	                    		try{
                                	// 良/否判定も未入力のまま保存させたいので DISP_RESULT_BUF を使って処理する
                                	DISP_RESULT_BUF = AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT);
        						}
		        				catch(EConvertError& e){
				        			bDISP_HANTEI = false;
        						}
		        				catch(...){
				        			bDISP_HANTEI = false;
        						}
		        			}
				        	if(bDISP_HANTEI && AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
        					{
                                // 良/否判定も未入力のまま保存させたいので DISP_RESULT_BUF を使って処理する
                                if( DISP_RESULT_BUF.ToIntDef(0) == 1 )
                                {
                                    //DISP_OK_FLG = false;
                                    if( iDISP_OK_FLG != -1 ) iDISP_OK_FLG = 1;
                                }
                                else
                                {
                                    if(iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                }
				        	}
                            if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                                DISP_VAL_SU ++;
                                iDISP_VAL_SU ++;
                                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT).Trim().Length() == 0 )
                                {
                                    iDISP_OK_FLG = -1;
                                }
                            }
		        			break;
             	        case 3:
		        			DISP_RESULT_BUF = GetValidityData(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT),14);
                           	if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].SOKU_FLG).ToIntDef(0)!=0)
                            {
                                DISP_VAL_SU ++;
                                iDISP_VAL_SU ++;
                                if(iDISP_OK_FLG == 2 ) iDISP_OK_FLG = 0;
                                if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow+i3].DISP_RESULT).Trim().Length() == 0 )
                                {
                                    iDISP_OK_FLG = -1;
                                }
                            }
                           	break;
				        }

                // 良/否判定も未入力のまま保存させたいので VALUE_TYPE = 2 の時でも RESULT_BUF を使って処理する
                // イコール　case 2はコメント
                switch( VALUE_TYPE )
                {
                case 0:
                case 1:
                	if( bHANTEI ) RESULT_BUF 		= AnsiString(RESULT);
	    			if( !bHANTEI ) RESULT_BUF 		= "";
                    break;
                default:
                	break;
                }
	    		switch( VALUE_TYPE )
                {
                case 0:
                case 1:
                	if( bDISP_HANTEI ) DISP_RESULT_BUF 		= AnsiString(DISP_RESULT);
				    if( !bDISP_HANTEI ) DISP_RESULT_BUF 		= "";
                    break;
                default:
                	break;
                }

                if(bHANTEI == true || bHANTEI == false)
				{
	                switch( i4 )
    	            {
        	        case 0:
            	    	strcpy(SetData.SOKU_VAL01 , AnsiString(RESULT_BUF).c_str());
			   			strcpy(SetData.DISP_VAL01 , AnsiString(DISP_RESULT_BUF).c_str());
			  			break;
	                case 1:
				   		strcpy(SetData.SOKU_VAL02 , AnsiString(RESULT_BUF).c_str());
				  		strcpy(SetData.DISP_VAL02 , AnsiString(DISP_RESULT_BUF).c_str());
				 		break;
					case 2:
			   			strcpy(SetData.SOKU_VAL03 , AnsiString(RESULT_BUF).c_str());
			  			strcpy(SetData.DISP_VAL03 , AnsiString(DISP_RESULT_BUF).c_str());
		 				break;
					case 3:
		   				strcpy(SetData.SOKU_VAL04 , AnsiString(RESULT_BUF).c_str());
		  				strcpy(SetData.DISP_VAL04 , AnsiString(DISP_RESULT_BUF).c_str());
	 					break;
					case 4:
   						strcpy(SetData.SOKU_VAL05 , AnsiString(RESULT_BUF).c_str());
  						strcpy(SetData.DISP_VAL05 , AnsiString(DISP_RESULT_BUF).c_str());
	 					break;
    	            case 5:
				   		strcpy(SetData.SOKU_VAL06 , AnsiString(RESULT_BUF).c_str());
				  		strcpy(SetData.DISP_VAL06 , AnsiString(DISP_RESULT_BUF).c_str());
			 			break;
					case 6:
			   			strcpy(SetData.SOKU_VAL07 , AnsiString(RESULT_BUF).c_str());
			  			strcpy(SetData.DISP_VAL07 , AnsiString(DISP_RESULT_BUF).c_str());
		 				break;
					case 7:
		   				strcpy(SetData.SOKU_VAL08 , AnsiString(RESULT_BUF).c_str());
		  				strcpy(SetData.DISP_VAL08 , AnsiString(DISP_RESULT_BUF).c_str());
	 					break;
					case 8:
   						strcpy(SetData.SOKU_VAL09 , AnsiString(RESULT_BUF).c_str());
  						strcpy(SetData.DISP_VAL09 , AnsiString(DISP_RESULT_BUF).c_str());
	 					break;
    	            case 9:
				   		strcpy(SetData.SOKU_VAL10 , AnsiString(RESULT_BUF).c_str());
				  		strcpy(SetData.DISP_VAL10 , AnsiString(DISP_RESULT_BUF).c_str());
			 			break;
					default:  								//例外データ用ルーチンを考える
					    //KSD03に対し新規追加か更新かをチェックする
    					sBuf = "SELECT * FROM KSD03";
						sBuf += " WHERE DTKSHIN = '" + AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].DTKSHIN)+ "'";
                	    sBuf += " AND   LOTNO   = '" + AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].LOTNO) 	+ "'";
                	    sBuf += " AND   HINBAN  = '" + AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].HINBAN) + "'";
						sBuf += " AND   UNQ_NO  =  " + AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UNQ_NO) ;
	     				sBuf += " AND   SOKU_NO =  " + AnsiString(i3+1) ;
    				    // Initial Query
	    				Query1->Close();
    					Query1->SQL->Clear();
        				Query1->SQL->Add(sBuf);
	    				Query1->Open();
    					Query1->Active = true;

		            	bNEW = false;
			    		if( Query1->Eof == true ) bNEW = true;
	    				Query1->Close();
						if( bNEW == true )
						{
              	            //新規登録
			  				strcpy(SetData.DTKSHIN		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].DTKSHIN);
    	    	    		strcpy(SetData.LOTNO		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].LOTNO);
    	    	    		strcpy(SetData.HINBAN		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].HINBAN);
        	    			strcpy(SetData.UNQ_NO		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UNQ_NO);
							sBuf = "insert into KSD03(";
    	        			sBuf += " DTKSHIN, LOTNO, HINBAN, UNQ_NO, SOKU_NO, SOKU_VAL, DISP_VAL";
	        	    		sBuf += " )";
		            		sBuf += " VALUES('";
			            	sBuf += AnsiString(SetData.DTKSHIN)           	+ "','";	//	得意先品番
    			        	sBuf += AnsiString(SetData.LOTNO)	       		+ "','";	//	ロットNO
    			        	sBuf += AnsiString(SetData.HINBAN)	       		+ "', ";	//	工管発行日 onishi
        			    	sBuf += AnsiString(SetData.UNQ_NO)  			+ " , ";	//	明細NO
							sBuf += AnsiString(i3+1)						+ " ,'";	//	測定NO
							sBuf += AnsiString(RESULT_BUF)                  + "','";	//	測定値
							sBuf += AnsiString(DISP_RESULT_BUF)				+ "') "; 	//	印刷用測定値
						}
						else
						{
        	                //更新
							strcpy(SetData.DTKSHIN		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].DTKSHIN);
    		        		strcpy(SetData.LOTNO		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].LOTNO);
    		        		strcpy(SetData.HINBAN		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].HINBAN);
        		    		strcpy(SetData.UNQ_NO		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UNQ_NO);
							sBuf = "update KSD03 set ";
    				        sBuf += " DTKSHIN = '" 		+ AnsiString(SetData.DTKSHIN) 	+ "',"	;
							sBuf += " LOTNO = 	'" 		+ AnsiString(SetData.LOTNO) 	+ "',"	;
							sBuf += " HINBAN = 	'" 		+ AnsiString(SetData.HINBAN) 	+ "',"	;
							sBuf += " UNQ_NO = 	 " 		+ AnsiString(SetData.UNQ_NO) 	+ ","	;
			              	sBuf += " SOKU_NO =  "		+ AnsiString(i3+1) 			   	+ " , " ;
    			        	sBuf += " SOKU_VAL = '"		+ AnsiString(RESULT_BUF) 		+ "'," ;
        			    	sBuf += " DISP_VAL = '"		+ AnsiString(DISP_RESULT_BUF) 	+ "'" ;
							sBuf += " WHERE DTKSHIN = '" + AnsiString(SetData.DTKSHIN)	+ "'";
                	    	sBuf += " AND   LOTNO   = '" + AnsiString(SetData.LOTNO) 	+ "'";
                	    	sBuf += " AND   HINBAN  = '" + AnsiString(SetData.HINBAN) 	+ "'";
							sBuf += " AND   UNQ_NO  = "  + AnsiString(SetData.UNQ_NO) 	 	 ;
    	 					sBuf += " AND   SOKU_NO = "  + AnsiString(i3+1) ;
						}
						//For Debug
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
						// 問い合せ文の実行
			        	try{
        			    	Query1->ExecSQL();
		    	        }
        			    catch(EDatabaseError& e)
		            	{
        		    		SBr1->Panels->Items[0]->Text = e.Message;
	                		SBr1->Update();
			                return(false);
        			    }
		    	        catch(Exception& e)
        			    {
		            		SBr1->Panels->Items[0]->Text = e.Message;
        		        	SBr1->Update();
	                		return(false);
			            }
			   			break;
		  			}
					i4++;
				}
            }
            //１項目のセーブ実行
			strcpy(SetData.DTKSHIN		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].DTKSHIN);
            strcpy(SetData.LOTNO		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].LOTNO);
            strcpy(SetData.HINBAN		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].HINBAN);      //onishi
            strcpy(SetData.UNQ_NO		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UNQ_NO);
            strcpy(SetData.ORDER_NO		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ORDER_NO);
            strcpy(SetData.SKB_NO		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKB_NO);
            strcpy(SetData.HINBAN_SK	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].HINBAN_SK);
            strcpy(SetData.KOMK_NO		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KOMK_NO);
            strcpy(SetData.KOMK_NM		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KOMK_NM);
            strcpy(SetData.KOMK_ENG		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KOMK_ENG);
            strcpy(SetData.KOMK_SUB		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KOMK_SUB);
            strcpy(SetData.KOMK_SUB_ENG	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KOMK_SUB_ENG);
            strcpy(SetData.KIKI_NO		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKI_NO);
            strcpy(SetData.KIKI_NM		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKI_NM);
            strcpy(SetData.TANI			,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].TANI);
            strcpy(SetData.KIKA_TYPE	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKA_TYPE);
            strcpy(SetData.KIKA_KIND	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKA_KIND);
            strcpy(SetData.KIKA_DECI	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKA_DECI);
            strcpy(SetData.KIKA_NUM1	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKA_NUM1);
            strcpy(SetData.KIKA_NUM2	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKA_NUM2);
            strcpy(SetData.KIKA_NUM3	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKA_NUM3);
            strcpy(SetData.KIKA_STR		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKA_STR);
            strcpy(SetData.KIKA_SUB1	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKA_SUB1);
            strcpy(SetData.KIKA_SUB2	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKA_SUB2);
            strcpy(SetData.KIKA_SUB3	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKA_SUB3);
            strcpy(SetData.SOKU_SU		,AnsiString(iSIJI_NSU).c_str());
            strcpy(SetData.SOKU_FLG		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SOKU_FLG);
            strcpy(SetData.TOKU_FLG		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].TOKU_FLG);
            strcpy(SetData.KIKA_PRT		,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].KIKA_PRT);
            strcpy(SetData.VALUE_TYPE	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].VALUE_TYPE);
            strcpy(SetData.VALUE_DECI	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].VALUE_DECI);
            strcpy(SetData.SOKU_VAL_SU		,AnsiString(iSIJI_NSU).c_str());
			if( iSOKU_VAL_SU > 0) {
				SOKU_VAL_AVE = GOUKEI_RESULT / iSOKU_VAL_SU;
			}
            else {
				SOKU_VAL_AVE = 0;
            }
			if( SOKU_VAL_AVE > 9999999.999999 ) SOKU_VAL_AVE = 9999999.999999;
			if( SOKU_VAL_MAX > 9999999.99999  ) SOKU_VAL_MAX = 9999999.99999 ;
			if( SOKU_VAL_MIN > 9999999.99999  ) SOKU_VAL_MIN = 9999999.99999 ;
			strcpy(SetData.SOKU_VAL_AVE	,AnsiString(SOKU_VAL_AVE).SubString(1,14).c_str());
			strcpy(SetData.SOKU_VAL_MAX ,AnsiString(SOKU_VAL_MAX).SubString(1,14).c_str());
			strcpy(SetData.SOKU_VAL_MIN ,AnsiString(SOKU_VAL_MIN).SubString(1,14).c_str());
            strcpy(SetData.SOKU_OK,AnsiString(iOK_FLG).c_str());
			//strcpy(SetData.DISP_VAL_SU  ,AnsiString(DISP_VAL_SU).c_str());
            strcpy(SetData.DISP_VAL_SU	,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SOKU_SU);
            strcpy(SetData.DISP_VAL_SU		,AnsiString(iSIJI_NSU).c_str());
			if( iDISP_VAL_SU > 0) {
				DISP_VAL_AVE = DISP_GOUKEI_RESULT / iDISP_VAL_SU;
			}
			else
			{
				DISP_VAL_AVE = 0;
			}
			if( DISP_VAL_AVE > 9999999.999999 ) DISP_VAL_AVE = 9999999.999999;
			if( DISP_VAL_MAX > 9999999.99999  ) DISP_VAL_MAX = 9999999.99999 ;
			if( DISP_VAL_MIN > 9999999.99999  ) DISP_VAL_MIN = 9999999.99999 ;
			strcpy(SetData.DISP_VAL_AVE	,AnsiString(DISP_VAL_AVE).SubString(1,14).c_str());
			strcpy(SetData.DISP_VAL_MAX ,AnsiString(DISP_VAL_MAX).SubString(1,14).c_str());
			strcpy(SetData.DISP_VAL_MIN ,AnsiString(DISP_VAL_MIN).SubString(1,14).c_str());
            strcpy(SetData.DISP_OK,AnsiString(iDISP_OK_FLG).c_str());
			i4 = AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDCNT).ToIntDef(0)+1;
			strcpy(SetData.UPDCNT ,AnsiString(i4).c_str());

	        //KSD02に対し新規追加か更新かをチェックする
    		sBuf = "SELECT * FROM KSD02";
			sBuf += " WHERE DTKSHIN = '" + sNowDTKSHIN + "'";
			sBuf += " AND   UNQ_NO  =  " + AnsiString(iUNQNO) ;
    		sBuf += " AND   SKB_NO  = 1";                        //出荷検査項目、材料証明項目
    		sBuf += " AND   LOTNO   = '" + AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].LOTNO) + "'";
    		sBuf += " AND   HINBAN  = '" + AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].HINBAN) + "'";
			// Initial Query
	    	Query1->Close();
    		Query1->SQL->Clear();
        	Query1->SQL->Add(sBuf);
    		Query1->Open();
    		Query1->Active = true;

            bNEW = false;
	    	if( Query1->Eof == true ) bNEW = true;
	    	Query1->Close();
			if( bNEW == true )										//新規登録
			{
// 測定日
//				strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKTYMD,FormatDateTime("yyyymmdd",Date()).c_str());
// 登録日
//				strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
// 登録時間
//				strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
// 変更日
				strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
// 変更時間
				strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
// 更新者
				if(AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDCHR).Trim().Length() == 0)
				{
					strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDCHR,AnsiString(Form1->USER_COD).c_str());
				}
// 更新回数
				strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDCNT,"0");

//セーブ用バッファにコピー
// 測定日
				strcpy(SetData.SKTYMD,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKTYMD);
// 登録日
				strcpy(SetData.ADDYMD,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDYMD);
// 登録時間
				strcpy(SetData.ADDTIM,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDTIM);
// 変更日
				strcpy(SetData.UPDYMD,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDYMD);
// 変更時間
				strcpy(SetData.UPDTIM,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDTIM);
// 更新者
				strcpy(SetData.UPDCHR,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDCHR);
// 更新回数
				strcpy(SetData.UPDCNT,pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDCNT);

                // 問合せ文作成(KSD02)
				sBuf = "insert into KSD02(";
    	        sBuf += " DTKSHIN, LOTNO, HINBAN, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK, KOMK_NO, KOMK_NM,";
        	    sBuf += " KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI,";
	            sBuf += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3,";
    	        sBuf += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3, SOKU_SU, SOKU_FLG,";
        	    sBuf += " TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI,";
            	sBuf += " SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05,";
	            sBuf += " SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,";
    	        sBuf += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK,";
        	    sBuf += " DISP_VAL01, DISP_VAL02, DISP_VAL03, DISP_VAL04, DISP_VAL05,";
            	sBuf += " DISP_VAL06, DISP_VAL07, DISP_VAL08, DISP_VAL09, DISP_VAL10,";
	            sBuf += " DISP_VAL_SU, DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, DISP_OK,";
    	        sBuf += " SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
        	    sBuf += " )";
            	sBuf += " VALUES('";
	            sBuf += AnsiString(SetData.DTKSHIN)           	+ "','";	//	得意先品番
    	        sBuf += AnsiString(SetData.LOTNO)	       		+ "','";	//	ロットNO
    	        sBuf += AnsiString(SetData.HINBAN)	       		+ "', ";	//	工管発行日 onishi
        	    sBuf += AnsiString(SetData.UNQ_NO)  			+ " , ";	//	明細NO
            	sBuf += AnsiString(SetData.ORDER_NO)  			+ " , ";	//	明細NO
	            sBuf += AnsiString(SetData.SKB_NO)  			+ " ,'";	//	識別NO
    	        sBuf += AnsiString(SetData.HINBAN_SK) 			+ "', ";
        	    sBuf += AnsiString(SetData.KOMK_NO) 			+ " ,'";	//	測定項目NO
	            sBuf += AnsiString(SetData.KOMK_NM)	       		+ "','";	//	測定項目名称
    	        sBuf += AnsiString(SetData.KOMK_ENG)       		+ "','";
        	    sBuf += AnsiString(SetData.KOMK_SUB)	   		+ "','";	//	測定項目名称
            	sBuf += AnsiString(SetData.KOMK_SUB_ENG)   		+ "', ";	//	測定項目名称
	            sBuf += AnsiString(SetData.KIKI_NO) 			+ " ,'";	//	測定機器NO
    	        sBuf += AnsiString(SetData.KIKI_NM)	       		+ "','";	//	測定機器名称
        	    sBuf += AnsiString(SetData.TANI)   	       		+ "', ";	//	単位
            	sBuf += AnsiString(SetData.KIKA_TYPE) + " , ";
	            sBuf += AnsiString(SetData.KIKA_KIND) + " , ";
    	        sBuf += AnsiString(SetData.KIKA_DECI) + " , ";
        	    sBuf += AnsiString(SetData.KIKA_NUM1) + " , ";
            	sBuf += AnsiString(SetData.KIKA_NUM2) + " , ";
	            sBuf += AnsiString(SetData.KIKA_NUM3) + " ,'";
    	        sBuf += AnsiString(SetData.KIKA_STR)            + "','";
        	    sBuf += AnsiString(SetData.KIKA_SUB1)           + "','";
            	sBuf += AnsiString(SetData.KIKA_SUB2)           + "','";
	            sBuf += AnsiString(SetData.KIKA_SUB3)           + "', ";
    	        sBuf += AnsiString(SetData.SOKU_SU) 	+ " , ";	//    　測定指示ｎ数
        	    sBuf += AnsiString(SetData.SOKU_FLG) 	+ " , ";	//    　測定指示ｎ数
            	sBuf += AnsiString(SetData.TOKU_FLG) 	+ " , ";	//    　測定指示ｎ数
	            sBuf += AnsiString(SetData.KIKA_PRT) 	+ " , ";	//    　測定指示ｎ数
    	        sBuf += AnsiString(SetData.VALUE_TYPE)+ " , ";	//    　測定指示ｎ数
        	    sBuf += AnsiString(SetData.VALUE_DECI)+ " ,'";	//    　測定指示ｎ数
            	sBuf += AnsiString(SetData.SOKU_VAL01)        	+ "','";	//	測定値１
	            sBuf += AnsiString(SetData.SOKU_VAL02)        	+ "','";	//      測定値２　　　
    	        sBuf += AnsiString(SetData.SOKU_VAL03)        	+ "','";	//	測定値３
        	    sBuf += AnsiString(SetData.SOKU_VAL04)        	+ "','";	//	測定値４
            	sBuf += AnsiString(SetData.SOKU_VAL05)        	+ "','";	//	測定値５
	            sBuf += AnsiString(SetData.SOKU_VAL06)        	+ "','";	//	測定値６
    	        sBuf += AnsiString(SetData.SOKU_VAL07)        	+ "','";	//	測定値７
        	    sBuf += AnsiString(SetData.SOKU_VAL08)        	+ "','";	//	測定値８
	            sBuf += AnsiString(SetData.SOKU_VAL09)        	+ "','";	//	測定値９
    	        sBuf += AnsiString(SetData.SOKU_VAL10)        	+ "', ";	//	測定値１０
        	    sBuf += AnsiString(SetData.SOKU_VAL_SU)+ " , ";	//    　測定指示ｎ数
            	sBuf += AnsiString(SetData.SOKU_VAL_AVE)+ " , ";	//    　測定指示ｎ数
	            sBuf += AnsiString(SetData.SOKU_VAL_MAX)+ " , ";	//    　測定指示ｎ数
    	        sBuf += AnsiString(SetData.SOKU_VAL_MIN)+ " , ";	//    　測定指示ｎ数
        	    sBuf += AnsiString(SetData.SOKU_OK)   + " ,'";	//	測定値１０
            	sBuf += AnsiString(SetData.DISP_VAL01)        	+ "','";	//	測定値１
	            sBuf += AnsiString(SetData.DISP_VAL02)        	+ "','";	//      測定値２　　　
    	        sBuf += AnsiString(SetData.DISP_VAL03)        	+ "','";	//	測定値３
        	    sBuf += AnsiString(SetData.DISP_VAL04)        	+ "','";	//	測定値４
            	sBuf += AnsiString(SetData.DISP_VAL05)        	+ "','";	//	測定値５
	            sBuf += AnsiString(SetData.DISP_VAL06)        	+ "','";	//	測定値６
    	        sBuf += AnsiString(SetData.DISP_VAL07)        	+ "','";	//	測定値７
        	    sBuf += AnsiString(SetData.DISP_VAL08)        	+ "','";	//	測定値８
            	sBuf += AnsiString(SetData.DISP_VAL09)        	+ "','";	//	測定値９
	            sBuf += AnsiString(SetData.DISP_VAL10)        	+ "', ";	//	測定値１０
    	        sBuf += AnsiString(SetData.DISP_VAL_SU)+ " , ";	//    　測定指示ｎ数
        	    sBuf += AnsiString(SetData.DISP_VAL_AVE)+ " , ";	//    　測定指示ｎ数
            	sBuf += AnsiString(SetData.DISP_VAL_MAX)+ " , ";	//    　測定指示ｎ数
	            sBuf += AnsiString(SetData.DISP_VAL_MIN)+ " , ";	//    　測定指示ｎ数
    	        sBuf += AnsiString(SetData.DISP_OK)  + " ,'";	//	測定値１０
        	    sBuf += AnsiString(SetData.SKTYMD)   	       + "','";	//	測定日
            	sBuf += AnsiString(SetData.ADDYMD)   	       + "','";	//	登録日
	            sBuf += AnsiString(SetData.ADDTIM)   	       + "','";	//	登録時間
    	        sBuf += AnsiString(SetData.UPDYMD)   	       + "','";	//	変更日
        	    sBuf += AnsiString(SetData.UPDTIM)   	       + "',";	//	変更時間
        	    sBuf += AnsiString(SetData.UPDCHR)   	       + " ,";	//	変更時間
            	sBuf += AnsiString(SetData.UPDCNT);  	         	//	更新回数
	            sBuf += ")";
			}
			else
			{
// 測定日（登録日と同じ)
				strcpy(SetData.SKTYMD,AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SKTYMD).c_str());
// 登録日
				strcpy(SetData.ADDYMD,AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDYMD).c_str());
// 登録時間
				strcpy(SetData.ADDTIM,AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].ADDTIM).c_str());
// 変更日
				strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDYMD,FormatDateTime("yyyymmdd",Date()).c_str());
				strcpy(SetData.UPDYMD,AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDYMD).c_str());
// 変更時間
				strcpy(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDTIM,FormatDateTime("hhmm",TDateTime::CurrentTime()).c_str());
				strcpy(SetData.UPDTIM,AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDTIM).c_str());
// 更新者
				strcpy(SetData.UPDCHR,AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].UPDCHR).c_str());
// 更新回数
//				strcpy(SetData.UPDCNT,"0");
				sBuf = "update KSD02 set ";
//田村様の指示によりコメント
//    	        sBuf += " DTKSHIN = '" 		+ AnsiString(SetData.DTKSHIN) + "',"	;
//				sBuf += " LOTNO = '" 		+ AnsiString(SetData.LOTNO) + "',"	;
//				sBuf += " UNQ_NO = " 		+ AnsiString(SetData.UNQ_NO) + ","	;
				sBuf += " ORDER_NO = " 		+ AnsiString(SetData.ORDER_NO) + ","	;
				sBuf += " SKB_NO = " 		+ AnsiString(SetData.SKB_NO) + ","	;
				sBuf += " HINBAN_SK = '" 	+ AnsiString(SetData.HINBAN_SK) + "',"	;
				sBuf += " KOMK_NO = " 		+ AnsiString(SetData.KOMK_NO) + ","	;
				sBuf += " KOMK_NM = '" 		+ AnsiString(SetData.KOMK_NM) + "',"	;
        	    sBuf += " KOMK_ENG = '" 	+ AnsiString(SetData.KOMK_ENG) + "',"	;
				sBuf += " KOMK_SUB = '" 	+ AnsiString(SetData.KOMK_SUB) + "',"	;
				sBuf += " KOMK_SUB_ENG = '" + AnsiString(SetData.KOMK_SUB_ENG) + "',"	;
				sBuf += " KIKI_NO = " 		+ AnsiString(SetData.KIKI_NO) + ","	;
				sBuf += " KIKI_NM = '" 		+ AnsiString(SetData.KIKI_NM) + "',"	;
				sBuf += " TANI = '" 		+ AnsiString(SetData.TANI) + "',"	;
	            sBuf += " KIKA_TYPE = " 	+ AnsiString(SetData.KIKA_TYPE) + ","	;
				sBuf += " KIKA_KIND = " 	+ AnsiString(SetData.KIKA_KIND) + ","	;
				sBuf += " KIKA_DECI = " 	+ AnsiString(SetData.KIKA_DECI) + ","	;
				sBuf += " KIKA_NUM1 = " 	+ AnsiString(SetData.KIKA_NUM1) + ","	;
				sBuf += " KIKA_NUM2 = " 	+ AnsiString(SetData.KIKA_NUM2) + ","	;
				sBuf += " KIKA_NUM3 = " 	+ AnsiString(SetData.KIKA_NUM3) + ","	;
    	        sBuf += " KIKA_STR = '"  	+ AnsiString(SetData.KIKA_STR) + "',"	;
				sBuf += " KIKA_SUB1 = '" 	+ AnsiString(SetData.KIKA_SUB1) + "',"	;
				sBuf += " KIKA_SUB2 = '" 	+ AnsiString(SetData.KIKA_SUB2) + "',"	;
				sBuf += " KIKA_SUB3 = '" 	+ AnsiString(SetData.KIKA_SUB3) + "',"	;
				sBuf += " SOKU_SU = " 	 	+ AnsiString(SetData.SOKU_SU) + ","	;
                sBuf += " SOKU_FLG = "  	+ AnsiString(SetData.SOKU_FLG) + ","	;
        	    sBuf += " TOKU_FLG = "  	+ AnsiString(SetData.TOKU_FLG) + ","	;
				sBuf += " KIKA_PRT = "  	+ AnsiString(SetData.KIKA_PRT) + ","	;
				sBuf += " VALUE_TYPE = " 	+ AnsiString(SetData.VALUE_TYPE) + ","	;
				sBuf += " VALUE_DECI = " 	+ AnsiString(SetData.VALUE_DECI) + ","	;
            	sBuf += " SOKU_VAL01 = '" 	+ AnsiString(SetData.SOKU_VAL01) + "',"	;
				sBuf += " SOKU_VAL02 = '" 	+ AnsiString(SetData.SOKU_VAL02) + "',"	;
				sBuf += " SOKU_VAL03 = '" 	+ AnsiString(SetData.SOKU_VAL03) + "',"	;
				sBuf += " SOKU_VAL04 = '" 	+ AnsiString(SetData.SOKU_VAL04) + "',"	;
				sBuf += " SOKU_VAL05 = '" 	+ AnsiString(SetData.SOKU_VAL05) + "',"	;
	            sBuf += " SOKU_VAL06 = '" 	+ AnsiString(SetData.SOKU_VAL06) + "',"	;
				sBuf += " SOKU_VAL07 = '" 	+ AnsiString(SetData.SOKU_VAL07) + "',"	;
				sBuf += " SOKU_VAL08 = '" 	+ AnsiString(SetData.SOKU_VAL08) + "',"	;
				sBuf += " SOKU_VAL09 = '" 	+ AnsiString(SetData.SOKU_VAL09) + "',"	;
				sBuf += " SOKU_VAL10 = '" 	+ AnsiString(SetData.SOKU_VAL10) + "',"	;
    	        sBuf += " SOKU_VAL_SU = "  	+ AnsiString(SetData.SOKU_VAL_SU) + ","	;
				sBuf += " SOKU_VAL_AVE = " 	+ AnsiString(SetData.SOKU_VAL_AVE) + ","	;
				sBuf += " SOKU_VAL_MAX = " 	+ AnsiString(SetData.SOKU_VAL_MAX) + ","	;
				sBuf += " SOKU_VAL_MIN = " 	+ AnsiString(SetData.SOKU_VAL_MIN) + ","	;
				sBuf += " SOKU_OK = " 	  	+ AnsiString(SetData.SOKU_OK) + ","	;
        	    sBuf += " DISP_VAL01 = '" 	+ AnsiString(SetData.DISP_VAL01) + "',"	;
				sBuf += " DISP_VAL02 = '" 	+ AnsiString(SetData.DISP_VAL02) + "',"	;
				sBuf += " DISP_VAL03 = '" 	+ AnsiString(SetData.DISP_VAL03) + "',"	;
				sBuf += " DISP_VAL04 = '" 	+ AnsiString(SetData.DISP_VAL04) + "',"	;
				sBuf += " DISP_VAL05 = '" 	+ AnsiString(SetData.DISP_VAL05) + "',"	;
            	sBuf += " DISP_VAL06 = '" 	+ AnsiString(SetData.DISP_VAL06) + "',"	;
				sBuf += " DISP_VAL07 = '" 	+ AnsiString(SetData.DISP_VAL07) + "',"	;
				sBuf += " DISP_VAL08 = '" 	+ AnsiString(SetData.DISP_VAL08) + "',"	;
                sBuf += " DISP_VAL09 = '" 	+ AnsiString(SetData.DISP_VAL09) + "',"	;
				sBuf += " DISP_VAL10 = '" 	+ AnsiString(SetData.DISP_VAL10) + "',"	;
	            sBuf += " DISP_VAL_SU = "  	+ AnsiString(SetData.DISP_VAL_SU) + ","	;
				sBuf += " DISP_VAL_AVE = " 	+ AnsiString(SetData.DISP_VAL_AVE) + ","	;
				sBuf += " DISP_VAL_MAX = " 	+ AnsiString(SetData.DISP_VAL_MAX) + ","	;
				sBuf += " DISP_VAL_MIN = " 	+ AnsiString(SetData.DISP_VAL_MIN) + ","	;
				sBuf += " DISP_OK = " 		+ AnsiString(SetData.DISP_OK) + ","	;
    	        sBuf += " SKTYMD = '" 		+ AnsiString(SetData.SKTYMD) + "',"	;
				sBuf += " ADDYMD = '" 		+ AnsiString(SetData.ADDYMD) + "',"	;
				sBuf += " ADDTIM = '" 		+ AnsiString(SetData.ADDTIM) + "',"	;
				sBuf += " UPDYMD = '" 		+ AnsiString(SetData.UPDYMD) + "',"	;
				sBuf += " UPDTIM = '" 		+ AnsiString(SetData.UPDTIM) + "',"	;
				sBuf += " UPDCHR = " 		+ AnsiString(SetData.UPDCHR) + ","	;
				sBuf += " UPDCNT = " 		+ AnsiString(SetData.UPDCNT) + " "	;
     			sBuf += " WHERE DTKSHIN='" 	+ AnsiString(SetData.DTKSHIN)+ "'";
     			sBuf += " AND   LOTNO='" 	+ AnsiString(SetData.LOTNO)  + "'";
     			sBuf += " AND   HINBAN='" 	+ AnsiString(SetData.HINBAN) + "'";
     			sBuf += " AND   UNQ_NO= " 	+ AnsiString(SetData.UNQ_NO) ;
			}
		    //For Debug
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
		    // 問い合せ文の実行
        	try{
            	Query1->ExecSQL();
            }
            catch(EDatabaseError& e)
            {
            	SBr1->Panels->Items[0]->Text = e.Message;
                SBr1->Update();
                return(false);
            }
            catch(Exception& e)
            {
            	SBr1->Panels->Items[0]->Text = e.Message;
                SBr1->Update();
                return(false);
            }
			}
			iRow +=  AnsiString(pCELLINFO_RIRE_SOZAI[iCol*iRowCount+iRow].SOKU_SU).ToIntDef(0);
        }
		}
	}
    Query1->Close();
    return(true);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：出荷（測定）の中で履歴があるもののデータの読み込み。
//
//  機能説明
//    出荷（測定）の履歴データを読み込み、CELLINFOに代入します。
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
void __fastcall TForm1::Set_SYUKAJISSEKI(void)
{
	int i1,i2,i3,i4;
	int iCol,iRow,iUNQNO;
    int iTempRow;
	AnsiString sLot,sUNQNO;
    AnsiString sBuf,sBuf1;
	AnsiString sDATE,sTIME;
    double dMAX,dMIN;
	AnsiString sLot_Where;

	sLot = "";
	sBuf = "";
	sBuf1 = "";
    sUNQNO ="";
    sDATE = FormatDateTime("yyyymmdd",Date());
    sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
	if(!hCELLINFO_SOKU_SYUKA) return;			//メモリが確保されていない時は処理を中止
	for(i1 = 0;i1 < SGr_tSOKU->ColCount ; i1++)
	{
		sLot += "'" + SGr_tSOKU->Cells[i1][0] + "'" + ",";
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
    for(i1 = 0; i1 < SGr_tSOKU->ColCount ; i1++)
    {
        sLot_Where += "( LOTNO='" + SGr_tSOKU->Cells[i1][0] + "' AND ";
        sLot_Where += " HINBAN='" + SGr_tSOKU->Cells[i1][1] + "') OR ";
    }
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

	i1 = 0;
	while( 1 )
	{
        if( i1 >= Form1->iOrCount ) break;
        iUNQNO = AnsiString(pORDATA[ i1 ].KOMK_NO).ToIntDef(0);
		sUNQNO += " " + AnsiString(pORDATA[ i1 ].KOMK_NO).Trim() + " " + ",";
		while(iUNQNO == AnsiString(pORDATA[ i1 ].KOMK_NO).ToIntDef(0))
		{
			i1++;
			if(i1 >= Form1->iOrCount ) break;
		}
	}
	sUNQNO = sUNQNO.SubString(1,sUNQNO.Length()-1);



    if(sLot.Length() < 3 ) return;		//ロットの入力がない場合


	sBuf  = "SELECT  KSD02.*, SM12S.TANNAM As UPDNAME ";
	sBuf += " FROM KSD02 LEFT JOIN SM12S ON KSD02.UPDCHR = SM12S.TANSYA ";
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
    sBuf += " AND   SKB_NO IN (2,3)";                        //出荷検査項目、材料証明項目
    //sBuf += " AND   LOTNO IN ("+ sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";

	if(sUNQNO.Length() > 3 )
	{
		sBuf += " AND KOMK_NO IN ("+ sUNQNO + ")";
	}
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
	Query1->Close();
	Query1->Active = false;
    Query1->SQL->Clear();
    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;


    //履歴データが有る出荷ロットが呼び出されているはず
	while(Query1->Eof != true )
    {
    	i1 = 0;
        sLot = Query1->FieldValues["LOTNO"];

        //ロット毎にメモリの初期化が必要
        memset(pRIREKI_DATA,0x00,sizeof(pRIREKI_DATA));

        while( sLot == Query1->FieldValues["LOTNO"] && Query1->Eof != true)
        {
            strcpy(pRIREKI_DATA[i1].DTKSHIN		,"");
            if ( VarIsNull(Query1->FieldValues["DTKSHIN"]) != true)
            {
	        	sBuf = Query1->FieldValues["DTKSHIN"];							    //得意先項目品番
    	        strcpy(pRIREKI_DATA[i1].DTKSHIN			,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].LOTNO		,"");
			if ( VarIsNull(Query1->FieldValues["LOTNO"]) != true )
            {
            	sBuf = Query1->FieldValues["LOTNO"];                   				//ロットNO
            	strcpy(pRIREKI_DATA[i1].LOTNO      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].HINBAN		,"");
			if ( VarIsNull(Query1->FieldValues["HINBAN"]) != true )
            {
            	sBuf = Query1->FieldValues["HINBAN"];                   			//工管発行日 onishi
            	strcpy(pRIREKI_DATA[i1].HINBAN      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UNQ_NO		,"");
			if ( VarIsNull(Query1->FieldValues["UNQ_NO"]) != true )
            {
            	sBuf = Query1->FieldValues["UNQ_NO"];                   			//明細NO
            	strcpy(pRIREKI_DATA[i1].UNQ_NO      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ORDER_NO		,"");
			if ( VarIsNull(Query1->FieldValues["ORDER_NO"]) != true)
            {
            	sBuf = Query1->FieldValues["ORDER_NO"];                   		  	//表示・印刷順
            	strcpy(pRIREKI_DATA[i1].ORDER_NO      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SKB_NO		,"");
			if ( VarIsNull(Query1->FieldValues["SKB_NO"]) != true )
            {
            	sBuf = Query1->FieldValues["SKB_NO"];                   		 	//識別NO
            	strcpy(pRIREKI_DATA[i1].SKB_NO      		,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].HINBAN_SK		,"");
            if ( VarIsNull(Query1->FieldValues["HINBAN_SK"]) != true)
            {
            	sBuf	= Query1->FieldValues["HINBAN_SK"];
                strcpy(pRIREKI_DATA[i1].HINBAN_SK	,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KOMK_NO		,"");
            if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true )
            {
	            sBuf    = Query1->FieldValues["KOMK_NO"];                           //測定項目NO
    	        strcpy(pRIREKI_DATA[i1].KOMK_NO			,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KOMK_NM,"");                 				//測定項目名称
            if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true )
            {
            	sBuf = Query1->FieldValues["KOMK_NM"];
                strcpy(pRIREKI_DATA[i1].KOMK_NM		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_ENG,"");                 				//測定項目名称（英語)
            if ( VarIsNull(Query1->FieldValues["KOMK_ENG"]) != true )
            {
            	sBuf = Query1->FieldValues["KOMK_ENG"];
                strcpy(pRIREKI_DATA[i1].KOMK_ENG		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_SUB,"");                     			//測定項目サブ名称
            if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true)
            {
            	sBuf = Query1->FieldValues["KOMK_SUB"];
                strcpy(pRIREKI_DATA[i1].KOMK_SUB	,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_SUB_ENG,"");                     	    //測定項目サブ名称(英語)
            if ( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) != true )
            {
            	sBuf = Query1->FieldValues["KOMK_SUB_ENG"];
                strcpy(pRIREKI_DATA[i1].KOMK_SUB_ENG	,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KIKI_NO,"");                     	    //測定項目サブ名称(英語)
            if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true )
            {
	            sBuf    = Query1->FieldValues["KIKI_NO"];                       	//測定機器NO
    	        strcpy(pRIREKI_DATA[i1].KIKI_NO			,sBuf.c_str());
         	}
            strcpy(pRIREKI_DATA[i1].KIKI_NM,"");
            if ( VarIsNull(Query1->FieldValues["KIKI_NM"]) != true )				//測定機器名称
            {
            	sBuf = Query1->FieldValues["KIKI_NM"];
                strcpy(pRIREKI_DATA[i1].KIKI_NM		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].TANI       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["TANI"]) != true  )
			{
            	sBuf       = Query1->FieldValues["TANI"];
            	strcpy(pRIREKI_DATA[i1].TANI       ,sBuf.c_str());
			}                                                           		//規格タイプ

            strcpy(pRIREKI_DATA[i1].KIKA_TYPE       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["KIKA_TYPE"]) != true )
			{
	            sBuf  = Query1->FieldValues["KIKA_TYPE"];
    	        strcpy(pRIREKI_DATA[i1].KIKA_TYPE  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_KIND       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["KIKA_KIND"]) != true  )
			{
            	sBuf  = Query1->FieldValues["KIKA_KIND"];              				//規格種類
            	strcpy(pRIREKI_DATA[i1].KIKA_KIND  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_DECI       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["KIKA_DECI"]) != true )
			{
            	sBuf  = Query1->FieldValues["KIKA_DECI"];                         	//規格小数点以下桁数
            	strcpy(pRIREKI_DATA[i1].KIKA_DECI  ,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].KIKA_NUM1       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["KIKA_NUM1"]) != true )
			{
            	sBuf  = Query1->FieldValues["KIKA_NUM1"];                         	//規格値１
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM1  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_NUM2       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["KIKA_NUM2"]) != true )
			{
            	sBuf  = Query1->FieldValues["KIKA_NUM2"];                      		//規格値２
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM2  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_NUM3       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["KIKA_NUM3"]) != true )
			{
            	sBuf  = Query1->FieldValues["KIKA_NUM3"];                       	//規格値３
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM3  ,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].KIKA_STR       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["KIKA_STR"]) != true  )
			{
            	sBuf   = Query1->FieldValues["KIKA_STR"];                        	//規格値文字
            	strcpy(pRIREKI_DATA[i1].KIKA_STR   ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB1       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) != true )
			{
            	sBuf  = Query1->FieldValues["KIKA_SUB1"];                       	//規格値サブ１
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB1  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB2       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) != true )
			{
            	sBuf  = Query1->FieldValues["KIKA_SUB2"];                         	//規格値サブ２
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB2  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB3       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) != true )
			{
            	sBuf  = Query1->FieldValues["KIKA_SUB3"];                        	//規格値サブ３
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB3  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_SU       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["SOKU_SU"]) != true  )
			{
            	sBuf    = Query1->FieldValues["SOKU_SU"];                   		//測定指示ｎ数
            	strcpy(pRIREKI_DATA[i1].SOKU_SU    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_FLG       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["SOKU_FLG"]) != true )
			{
            	sBuf    = Query1->FieldValues["SOKU_FLG"];                   		//測定項目の有無
            	strcpy(pRIREKI_DATA[i1].SOKU_FLG    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].TOKU_FLG       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["TOKU_FLG"]) != true )
			{
	            sBuf    = Query1->FieldValues["TOKU_FLG"];                   		//特別項目の有無
	            strcpy(pRIREKI_DATA[i1].TOKU_FLG    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_PRT       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["KIKA_PRT"]) != true )
			{
            	sBuf    = Query1->FieldValues["KIKA_PRT"];                   		//上限下限値の印刷
            	strcpy(pRIREKI_DATA[i1].KIKA_PRT    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].VALUE_TYPE       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["VALUE_TYPE"]) != true)
			{
            	sBuf    = Query1->FieldValues["VALUE_TYPE"];                   		//測定値表現
            	strcpy(pRIREKI_DATA[i1].VALUE_TYPE    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].VALUE_DECI       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["VALUE_DECI"]) != true )
			{
            	sBuf    = Query1->FieldValues["VALUE_DECI"];                   		//測定値小数点以下桁数
            	strcpy(pRIREKI_DATA[i1].VALUE_DECI    ,sBuf.c_str());
            }
            //測定日
            strcpy(pRIREKI_DATA[i1].SKTYMD       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["SKTYMD"]) != true )
			{
            	sBuf     = Query1->FieldValues["SKTYMD"];                       	//測定日
            	strcpy(pRIREKI_DATA[i1].SKTYMD     ,sBuf.c_str());
            }
			if(AnsiString(pRIREKI_DATA[i1].SKTYMD).Length() != 8)
			{
            	strcpy(pRIREKI_DATA[i1].SKTYMD,sDATE.c_str());
			}
		    //登録日
            strcpy(pRIREKI_DATA[i1].ADDYMD       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["ADDYMD"]) != true  )
			{
            	sBuf     = Query1->FieldValues["ADDYMD"];                      		//登録日
            	strcpy(pRIREKI_DATA[i1].ADDYMD     ,sBuf.c_str());
            }
			if(AnsiString(pRIREKI_DATA[i1].ADDYMD).Length() != 8)
			{
            	strcpy(pRIREKI_DATA[i1].ADDYMD,sDATE.c_str());
			}
		    //登録時間
            strcpy(pRIREKI_DATA[i1].ADDTIM       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["ADDTIM"]) != true )
			{
            	sBuf     = Query1->FieldValues["ADDTIM"];                       	//登録時間
            	strcpy(pRIREKI_DATA[i1].ADDTIM     ,sBuf.c_str());
            }
			if(AnsiString(pRIREKI_DATA[i1].ADDTIM).Length() != 4)
			{
            	strcpy(pRIREKI_DATA[i1].ADDTIM,sTIME.c_str());
			}
		    //変更日
            strcpy(pRIREKI_DATA[i1].UPDYMD       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["UPDYMD"]) != true )
			{
            	sBuf     = Query1->FieldValues["UPDYMD"];                         	//変更日
            	strcpy(pRIREKI_DATA[i1].UPDYMD     ,sBuf.c_str());
            }
			if(AnsiString(pRIREKI_DATA[i1].UPDYMD).Length() != 8)
			{
            	strcpy(pRIREKI_DATA[i1].UPDYMD,sTIME.c_str());
			}
            //変更時間
            strcpy(pRIREKI_DATA[i1].UPDTIM       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["UPDTIM"]) != true )
			{
            	sBuf     = Query1->FieldValues["UPDTIM"];                          	//変更時間
            	strcpy(pRIREKI_DATA[i1].UPDTIM     ,sBuf.c_str());
            }
			if(AnsiString(pRIREKI_DATA[i1].UPDTIM).Length() != 4)
			{
            	strcpy(pRIREKI_DATA[i1].UPDTIM,sTIME.c_str());
			}

            strcpy(pRIREKI_DATA[i1].UPDCHR       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["UPDCHR"]) != true )
			{
            	sBuf     = Query1->FieldValues["UPDCHR"];                      		//更新者
            	strcpy(pRIREKI_DATA[i1].UPDCHR     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDCNT       ,"");                    		//単位
            if ( VarIsNull(Query1->FieldValues["UPDCNT"]) != true )
			{
            	sBuf     = Query1->FieldValues["UPDCNT"];                         	//更新回数
            	strcpy(pRIREKI_DATA[i1].UPDCNT     ,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].UPDNAME , "");
            if ( VarIsNull(Query1->FieldValues["UPDNAME"]) != true )
			{
            	sBuf     = Query1->FieldValues["UPDNAME"];                      		//更新者
            	strcpy(pRIREKI_DATA[i1].UPDNAME , sBuf.c_str());
            }
            //SOKU Result Read ///////////////////////////////////////////////////////////////////////
			strcpy(pRIREKI_DATA[i1].SOKU_VAL01,"");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL01"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL01"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL01		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL02,"");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL02"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL02"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL02		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL03,"");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL03"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL03"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL03		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL04,"");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL04"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL04"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL04		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL05,"");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL05"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL05"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL05		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL06,"");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL06"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL06"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL06		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL07,"");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL07"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL07"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL07		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL08,"");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL08"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL08"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL08		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL09,"");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL09"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL09"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL09		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL10,"");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL10"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL10"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL10		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_SU,"1");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL_SU"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL_SU"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_SU		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_AVE,"0.0");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL_AVE"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL_AVE"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_AVE		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_MAX,"0.0");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL_MAX"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL_MAX"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_MAX		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_MIN,"0.0");
            if(VarIsNull(Query1->FieldValues["SOKU_VAL_MIN"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_VAL_MIN"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_MIN		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_OK,"0");
            if(VarIsNull(Query1->FieldValues["SOKU_OK"])!=true)
            {
            	sBuf = Query1->FieldValues["SOKU_OK"];
                strcpy(pRIREKI_DATA[i1].SOKU_OK		,sBuf.c_str());
            }
            //DISP Result Read ///////////////////////////////////////////////////////////////////////
			strcpy(pRIREKI_DATA[i1].DISP_VAL01,"");
            if(VarIsNull(Query1->FieldValues["DISP_VAL01"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL01"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL01		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL02,"");
            if(VarIsNull(Query1->FieldValues["DISP_VAL02"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL02"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL02		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL03,"");
            if(VarIsNull(Query1->FieldValues["DISP_VAL03"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL03"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL03		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL04,"");
            if(VarIsNull(Query1->FieldValues["DISP_VAL04"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL04"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL04		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL05,"");
            if(VarIsNull(Query1->FieldValues["DISP_VAL05"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL05"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL05		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL06,"");
            if(VarIsNull(Query1->FieldValues["DISP_VAL06"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL06"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL06		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL07,"");
            if(VarIsNull(Query1->FieldValues["DISP_VAL07"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL07"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL07		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL08,"");
            if(VarIsNull(Query1->FieldValues["DISP_VAL08"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL08"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL08		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL09,"");
            if(VarIsNull(Query1->FieldValues["DISP_VAL09"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL09"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL09		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL10,"");
            if(VarIsNull(Query1->FieldValues["DISP_VAL10"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL10"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL10		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_SU,"1");
            if(VarIsNull(Query1->FieldValues["DISP_VAL_SU"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL_SU"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_SU		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_AVE,"0.0");
            if(VarIsNull(Query1->FieldValues["DISP_VAL_AVE"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL_AVE"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_AVE		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_MAX,"0.0");
            if(VarIsNull(Query1->FieldValues["DISP_VAL_MAX"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL_MAX"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_MAX		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_MIN,"0.0");
            if(VarIsNull(Query1->FieldValues["DISP_VAL_MIN"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_VAL_MIN"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_MIN		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_OK,"0");
            if(VarIsNull(Query1->FieldValues["DISP_OK"])!=true)
            {
            	sBuf = Query1->FieldValues["DISP_OK"];
                strcpy(pRIREKI_DATA[i1].DISP_OK		,sBuf.c_str());
            }
            i1 ++;
            Query1->Next();
		}
        //存在するロットの測定実績データの読み込み完了
        //カラムの位置検索
		iCol = 0;

        while(iCol <= SGr_tSOKU->ColCount)
        {
        	if( SGr_tSOKU->Cells[iCol][0] == sLot) break;
			iCol++;
        }

        //出荷検査のグリッドをすべて灰色にする
		for(i2= 1; i2 <  SGr_vSOKU_SYUKA->RowCount ; i2++)
        {
        	SGr_vSOKU_SYUKA->Font->Color = clGray;
			strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + i2].KOMK_NO,"-999");
			strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + i2].RESULT,AnsiString("").c_str());
			strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + i2].DISP_RESULT,AnsiString("").c_str());
			pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + i2].INS_ON = false;;
        }
        //測定機器NO、測定項目NOの一致している場所を探索
		i4 = i1;
        iRow = 1;
        for( i1 = 0; i1 < i4;i1++)
        {
        	i2 = 0;
			iRow = 1;
            while( 1 )
            {
                //測定項目名+測定機器NO → 測定項目名+測定機器NO+単位
				sBuf = AnsiString(pORDATA[i2].KOMK_NM).Trim() + AnsiString(pORDATA[i2].KOMK_SUB).Trim();
				sBuf1 =AnsiString(pRIREKI_DATA[i1].KOMK_NM).Trim() + AnsiString(pRIREKI_DATA[i1].KOMK_SUB).Trim();
            	if((AnsiString(pORDATA[i2].KIKI_NO).ToIntDef(0) == AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0))
                && (sBuf == sBuf1)
            	&& (AnsiString(pORDATA[i2].KOMK_NO).ToIntDef(0) == AnsiString(pRIREKI_DATA[i1].KOMK_NO).ToIntDef(0))
            	&& (AnsiString(pORDATA[i2].TANI).Trim() == AnsiString(pRIREKI_DATA[i1].TANI).Trim())
                ) break;
                iRow += AnsiString(pORDATA[i2].SOKU_SU).ToIntDef(0);
                i2++;
				//無限ループ対策
				if( i2 >=iOrCnt ) break;
            }
            if( i2 >= iOrCnt ) break;
            //履歴データのデータ読み取り
            iTempRow = iRow;
            GetLotKIKAKU(i1, &dMAX, &dMIN);
            for(i3 = 0; i3 <  AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) ; i3++ )
            {
            	strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DTKSHIN 		, pRIREKI_DATA[i1].DTKSHIN);
                strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].LOTNO 		, pRIREKI_DATA[i1].LOTNO);
                strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].HINBAN 		, pRIREKI_DATA[i1].HINBAN);
			   	strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].UNQ_NO 		, pRIREKI_DATA[i1].UNQ_NO);
			  	strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].ORDER_NO		, pRIREKI_DATA[i1].ORDER_NO);
			 	strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].SKB_NO 		, pRIREKI_DATA[i1].SKB_NO);
				strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].HINBAN_SK	, pRIREKI_DATA[i1].HINBAN_SK);
		   		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KOMK_NO 		, pRIREKI_DATA[i1].KOMK_NO);
                pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].INS_ON = true;
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KOMK_NM 		, pRIREKI_DATA[i1].KOMK_NM);
		 		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KOMK_ENG		, pRIREKI_DATA[i1].KOMK_ENG);
				strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KOMK_SUB		, pRIREKI_DATA[i1].KOMK_SUB);
	   			strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KOMK_SUB_ENG , pRIREKI_DATA[i1].KOMK_SUB_ENG);
	  			strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKI_NO 		, pRIREKI_DATA[i1].KIKI_NO);
	 			strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKI_NM 		, pRIREKI_DATA[i1].KIKI_NM);
				strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].TANI    		, pRIREKI_DATA[i1].TANI);
			  	strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKA_TYPE	, pRIREKI_DATA[i1].KIKA_TYPE);
			 	strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKA_KIND	, pRIREKI_DATA[i1].KIKA_KIND);
				strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKA_DECI	, pRIREKI_DATA[i1].KIKA_DECI);
		   		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKA_NUM1	, pRIREKI_DATA[i1].KIKA_NUM1);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKA_NUM2	, pRIREKI_DATA[i1].KIKA_NUM2);
		 		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKA_NUM3	, pRIREKI_DATA[i1].KIKA_NUM3);
				strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKA_STR		, pRIREKI_DATA[i1].KIKA_STR);
	   			strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKA_SUB1	, pRIREKI_DATA[i1].KIKA_SUB1);
	  			strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKA_SUB2	, pRIREKI_DATA[i1].KIKA_SUB2);
	 			strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKA_SUB3	, pRIREKI_DATA[i1].KIKA_SUB3);
				strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].SOKU_SU 		, pRIREKI_DATA[i1].SOKU_SU);
   				strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].SOKU_FLG		, pRIREKI_DATA[i1].SOKU_FLG);
  				strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].TOKU_FLG		, pRIREKI_DATA[i1].TOKU_FLG);
				strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].KIKA_PRT		, pRIREKI_DATA[i1].KIKA_PRT);
		   		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].VALUE_TYPE	, pRIREKI_DATA[i1].VALUE_TYPE);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].VALUE_DECI	, pRIREKI_DATA[i1].VALUE_DECI);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].SOKU_VAL_SU	, pRIREKI_DATA[i1].SOKU_VAL_SU);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].SOKU_VAL_AVE	, pRIREKI_DATA[i1].SOKU_VAL_AVE);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].SOKU_VAL_MAX	, pRIREKI_DATA[i1].SOKU_VAL_MAX);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].SOKU_VAL_MIN	, pRIREKI_DATA[i1].SOKU_VAL_MIN);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].SOKU_OK		, pRIREKI_DATA[i1].SOKU_OK);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_VAL_SU	, pRIREKI_DATA[i1].DISP_VAL_SU);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_VAL_AVE	, pRIREKI_DATA[i1].DISP_VAL_AVE);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_VAL_MAX	, pRIREKI_DATA[i1].DISP_VAL_MAX);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_VAL_MIN	, pRIREKI_DATA[i1].DISP_VAL_MIN);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_OK		, pRIREKI_DATA[i1].DISP_OK);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].SKTYMD		, pRIREKI_DATA[i1].SKTYMD);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].ADDYMD		, pRIREKI_DATA[i1].ADDYMD);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].ADDTIM		, pRIREKI_DATA[i1].ADDTIM);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].UPDYMD		, pRIREKI_DATA[i1].UPDYMD);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].UPDTIM		, pRIREKI_DATA[i1].UPDTIM);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].UPDCHR		, pRIREKI_DATA[i1].UPDCHR);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].UPDCNT		, pRIREKI_DATA[i1].UPDCNT);
		  		strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].UPDNAME      , pRIREKI_DATA[i1].UPDNAME);
				//規格
                pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].MAX = dMAX ;
                pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].MIN = dMIN ;
                iRow++;
            }
            iRow = iTempRow;
            for(i3 = 0; i3 <  AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) ; i3++ )
            {
                switch( i3 )
                {
                case 0:
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL01);
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL01);
                    break;
                case 1:
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL02);
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL02);
                    break;
                case 2:
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL03);
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL03);
                    break;
                case 3:
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL04);
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL04);
                    break;
                case 4:
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL05);
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL05);
                    break;
                case 5:
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL06);
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL06);
                    break;
                case 6:
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL07);
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL07);
                    break;
                case 7:
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL08);
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL08);
                    break;
                case 8:
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL09);
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL09);
                    break;
                case 9:
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL10);
					strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL10);
                    break;
                default:
    				sBuf  = "SELECT * FROM KSD03";
    				sBuf += " WHERE DTKSHIN= '" + AnsiString(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DTKSHIN) 	+ "'";
    				sBuf += " AND   LOTNO  = '"	+ AnsiString(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].LOTNO) 	+ "'";
    				sBuf += " AND   HINBAN = '"	+ AnsiString(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].HINBAN) 	+ "'";
    				sBuf += " AND   UNQ_NO = "	+ AnsiString(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].UNQ_NO) 	+ " ";
    				sBuf += " ORDER BY SOKU_NO ASC ";                         //出荷検査項目、材料証明項目
					//For Debug
                    if( iDEBUG == 1 )
                    {
                        ClpBrd = Clipboard();
                        ClpBrd->Open();
     				    ClpBrd->SetTextBuf(sBuf.c_str());
     				    ClpBrd->Close();
                    }
					// Initial Query
					Form1->Query6->Close();
    				Form1->Query6->SQL->Clear();
    				Form1->Query6->SQL->Add(sBuf);
    				Form1->Query6->Open();
                    Form1->Query6->Active = true;
                    while( Query6->Eof != true)
                    {
    					sBuf = "";
                		if(VarIsNull(Query6->FieldValues["SOKU_NO"])!=true)
                		{
                        	sBuf = Query6->FieldValues["SOKU_NO"];
				    	}
                        if(AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) < sBuf.ToIntDef(0)) break;
					    i3 = sBuf.ToIntDef(11)-11;
    					sBuf = "";
                		if(VarIsNull(Query6->FieldValues["SOKU_VAL"])!=true)
                		{
                        	sBuf = Query6->FieldValues["SOKU_VAL"];
				    	}
					    strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow + i3 ].RESULT		, sBuf.c_str());
                        sBuf = "";
	    				if(VarIsNull(Query6->FieldValues["DISP_VAL"])!=true)
                		{
 	                        sBuf = Query6->FieldValues["DISP_VAL"];
                        }
                        strcpy(pCELLINFO_SOKU_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow + i3 ].DISP_RESULT	, sBuf.c_str());
                        Query6->Next();
                    }
                    i3 = AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0)+1;
					Form1->Query6->Close();
                	break;
                }
                iRow ++;
            }
            iRow = iTempRow + AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0);
        }
   	}
	Query1->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：出荷（履歴）データの読み込み。
//
//  機能説明
//    出荷（履歴）データを読み込み、CELLINFOに代入します。
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
void __fastcall TForm1::Set_RIRE_SYUKAJISSEKI(void)
{
	int i1,i2,i3,i4;
	int iCol,iRow,iUNQNO;
    int iTempRow;
	//double dMAX,dMIN;
	AnsiString sLot,sUNQNO;
    AnsiString sBuf,sBuf1;
    AnsiString sBufTANTO;  //2003.05.09　E.Takase Add　　
    double dMAX,dMIN;
	AnsiString sLot_Where;

	sLot = "";
	sBuf = "";
	sBuf1 = "";
    sUNQNO ="";

	if(!hCELLINFO_RIRE_SYUKA) return;			//メモリが確保されていない時は処理を中止
    for(i1=0;i1 < Form1->iRIRE_CNT ;i1++ )
    {
        sLot += "'" + Form1->sRIREKI_LOT->Strings[i1] + "',";
    }
	sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
    for(i1=0;i1 < Form1->iRIRE_CNT ;i1++ )
    {
        sLot_Where += "( LOTNO='" + Form1->sRIREKI_LOT->Strings[i1] + "' AND ";
        sLot_Where += " HINBAN='" + Form1->sRIREKI_HIN->Strings[i1] + "') OR ";
    }
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

	i1 = 0;
    //////////////////////////////////////////////////////////////
    //	UNQ_NOでは検索キーとして不適当なのでKOMK_NOに変更します
    //////////////////////////////////////////////////////////////
	while( 1 )
	{
        if( i1 >= Form1->iOrCount ) break;
        iUNQNO = AnsiString(pORDATA[ i1 ].KOMK_NO).ToIntDef(0);
		sUNQNO += " " + AnsiString(pORDATA[ i1 ].KOMK_NO).Trim() + " " + ",";
		while(iUNQNO == AnsiString(pORDATA[ i1 ].KOMK_NO).ToIntDef(0))
		{
			i1++;
			if(i1 >= Form1->iOrCount ) break;
		}
	}
	sUNQNO = sUNQNO.SubString(1,sUNQNO.Length()-1);



    if(Form1->iRIRE_CNT == 0 ) return;		//ロットの入力がない場合

	sBuf  = "SELECT  KSD02.*, SM12S.TANNAM As UPDNAME ";
	sBuf += " FROM KSD02 LEFT JOIN SM12S ON KSD02.UPDCHR = SM12S.TANSYA ";
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
    sBuf += " AND   SKB_NO IN (2,3)";                        //出荷検査項目、材料証明項目
    //sBuf += " AND   LOTNO IN ("+ sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";

	if(sUNQNO.Length() > 3 )
	{
		sBuf += " AND KOMK_NO IN ("+ sUNQNO + ")";
	}
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
	Query2->Close();
	Query2->Active = false;
    Query2->SQL->Clear();
    Query2->SQL->Add(sBuf);
    Query2->Open();
    Query2->Active = true;

//履歴データが有る出荷ロットが呼び出されているはず
	while(Query2->Eof != true )
    {
    	i1 = 0;
        sLot = Query2->FieldValues["LOTNO"];

        //ロット毎にメモリの初期化が必要
        memset(pRIREKI_DATA,0x00,sizeof(pRIREKI_DATA));

        while( sLot == Query2->FieldValues["LOTNO"] && Query2->Eof != true)
        {
            strcpy(pRIREKI_DATA[i1].DTKSHIN		,"");
            if ( VarIsNull(Query2->FieldValues["DTKSHIN"]) != true )
            {
	        	sBuf	= Query2->FieldValues["DTKSHIN"];							//得意先項目品番
    	        strcpy(pRIREKI_DATA[i1].DTKSHIN			,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].LOTNO		,"");
			if ( VarIsNull(Query2->FieldValues["LOTNO"]) != true )
            {
            	sBuf = Query2->FieldValues["LOTNO"];                   				//ロットNO
            	strcpy(pRIREKI_DATA[i1].LOTNO      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].HINBAN		,"");
			if ( VarIsNull(Query2->FieldValues["HINBAN"]) != true )
            {
            	sBuf = Query2->FieldValues["HINBAN"];                   			//工管発行日 onishi
            	strcpy(pRIREKI_DATA[i1].HINBAN      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UNQ_NO		,"");
			if ( VarIsNull(Query2->FieldValues["UNQ_NO"]) != true )
            {
            	sBuf = Query2->FieldValues["UNQ_NO"];                   			//明細NO
            	strcpy(pRIREKI_DATA[i1].UNQ_NO      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ORDER_NO		,"");
			if ( VarIsNull(Query2->FieldValues["ORDER_NO"]) != true )
            {
            	sBuf = Query2->FieldValues["ORDER_NO"];                   		  	//表示・印刷順
            	strcpy(pRIREKI_DATA[i1].ORDER_NO      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SKB_NO		,"");
			if ( VarIsNull(Query2->FieldValues["SKB_NO"]) != true )
            {
            	sBuf = Query2->FieldValues["SKB_NO"];                   		 	//識別NO
            	strcpy(pRIREKI_DATA[i1].SKB_NO      		,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].HINBAN_SK		,"");                      //品番
            if ( VarIsNull(Query2->FieldValues["HINBAN_SK"]) != true )
            {
            	sBuf	= Query2->FieldValues["HINBAN_SK"];
                strcpy(pRIREKI_DATA[i1].HINBAN_SK	,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KOMK_NO		,"");                      //品番
            if ( VarIsNull(Query2->FieldValues["KOMK_NO"]) != true )
            {
	            sBuf    = Query2->FieldValues["KOMK_NO"];                           //測定項目NO
    	        strcpy(pRIREKI_DATA[i1].KOMK_NO			,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KOMK_NM,"");                 				//測定項目名称
            if ( VarIsNull(Query2->FieldValues["KOMK_NM"]) != true )
            {
            	sBuf = Query2->FieldValues["KOMK_NM"];
                strcpy(pRIREKI_DATA[i1].KOMK_NM		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_ENG,"");                 				//測定項目名称（英語)
            if ( VarIsNull(Query2->FieldValues["KOMK_ENG"]) != true )
            {
            	sBuf = Query2->FieldValues["KOMK_ENG"];
                strcpy(pRIREKI_DATA[i1].KOMK_ENG		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_SUB,"");                     			//測定項目サブ名称
            if ( VarIsNull(Query2->FieldValues["KOMK_SUB"]) != true )
            {
            	sBuf = Query2->FieldValues["KOMK_SUB"];
                strcpy(pRIREKI_DATA[i1].KOMK_SUB	,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_SUB_ENG,"");                     	    //測定項目サブ名称(英語)
            if ( VarIsNull(Query2->FieldValues["KOMK_SUB_ENG"]) != true )
            {
            	sBuf = Query2->FieldValues["KOMK_SUB_ENG"];
                strcpy(pRIREKI_DATA[i1].KOMK_SUB_ENG	,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KIKI_NO,"");                     	    //測定項目サブ名称(英語)
            if ( VarIsNull(Query2->FieldValues["KIKI_NO"]) != true )
            {
	            sBuf    = Query2->FieldValues["KIKI_NO"];                       	//測定機器NO
    	        strcpy(pRIREKI_DATA[i1].KIKI_NO			,sBuf.c_str());
         	}
            strcpy(pRIREKI_DATA[i1].KIKI_NM,"");
            if ( VarIsNull(Query2->FieldValues["KIKI_NM"]) != true )				//測定機器名称
            {
            	sBuf = Query2->FieldValues["KIKI_NM"];
                strcpy(pRIREKI_DATA[i1].KIKI_NM		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].TANI       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["TANI"]) != true   )
			{
            	sBuf       = Query2->FieldValues["TANI"];
            	strcpy(pRIREKI_DATA[i1].TANI       ,sBuf.c_str());
			}                                                           		//規格タイプ

            strcpy(pRIREKI_DATA[i1].KIKA_TYPE       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["KIKA_TYPE"]) != true )
			{
	            sBuf  = Query2->FieldValues["KIKA_TYPE"];
    	        strcpy(pRIREKI_DATA[i1].KIKA_TYPE  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_KIND       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["KIKA_KIND"]) != true )
			{
            	sBuf  = Query2->FieldValues["KIKA_KIND"];              				//規格種類
            	strcpy(pRIREKI_DATA[i1].KIKA_KIND  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_DECI       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["KIKA_DECI"]) != true )
			{
            	sBuf  = Query2->FieldValues["KIKA_DECI"];                         	//規格小数点以下桁数
            	strcpy(pRIREKI_DATA[i1].KIKA_DECI  ,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].KIKA_NUM1       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["KIKA_NUM1"]) != true )
			{
            	sBuf  = Query2->FieldValues["KIKA_NUM1"];                         	//規格値１
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM1  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_NUM2       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["KIKA_NUM2"]) != true )
			{
            	sBuf  = Query2->FieldValues["KIKA_NUM2"];                      		//規格値２
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM2  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_NUM3       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["KIKA_NUM3"]) != true )
			{
            	sBuf  = Query2->FieldValues["KIKA_NUM3"];                       	//規格値３
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM3  ,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].KIKA_STR       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["KIKA_STR"]) != true )
			{
            	sBuf   = Query2->FieldValues["KIKA_STR"];                        	//規格値文字
            	strcpy(pRIREKI_DATA[i1].KIKA_STR   ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB1       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["KIKA_SUB1"]) != true )
			{
            	sBuf  = Query2->FieldValues["KIKA_SUB1"];                       	//規格値サブ１
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB1  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB2       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["KIKA_SUB2"]) != true )
			{
            	sBuf  = Query2->FieldValues["KIKA_SUB2"];                         	//規格値サブ２
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB2  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB3       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["KIKA_SUB3"]) != true )
			{
            	sBuf  = Query2->FieldValues["KIKA_SUB3"];                        	//規格値サブ３
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB3  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_SU       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["SOKU_SU"]) != true  )
			{
            	sBuf    = Query2->FieldValues["SOKU_SU"];                   		//測定指示ｎ数
            	strcpy(pRIREKI_DATA[i1].SOKU_SU    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_FLG       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["SOKU_FLG"]) != true )
			{
            	sBuf    = Query2->FieldValues["SOKU_FLG"];                   		//測定項目の有無
            	strcpy(pRIREKI_DATA[i1].SOKU_FLG    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].TOKU_FLG       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["TOKU_FLG"]) != true )
			{
	            sBuf    = Query2->FieldValues["TOKU_FLG"];                   		//特別項目の有無
	            strcpy(pRIREKI_DATA[i1].TOKU_FLG    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_PRT       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["KIKA_PRT"]) != true )
			{
            	sBuf    = Query2->FieldValues["KIKA_PRT"];                   		//上限下限値の印刷
            	strcpy(pRIREKI_DATA[i1].KIKA_PRT    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].VALUE_TYPE       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["VALUE_TYPE"]) != true )
			{
            	sBuf    = Query2->FieldValues["VALUE_TYPE"];                   		//測定値表現
            	strcpy(pRIREKI_DATA[i1].VALUE_TYPE    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].VALUE_DECI       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["VALUE_DECI"]) != true )
			{
            	sBuf    = Query2->FieldValues["VALUE_DECI"];                   		//測定値小数点以下桁数
            	strcpy(pRIREKI_DATA[i1].VALUE_DECI    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SKTYMD       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["SKTYMD"]) != true )
			{
            	sBuf     = Query2->FieldValues["SKTYMD"];                       	//測定日
            	strcpy(pRIREKI_DATA[i1].SKTYMD     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ADDYMD       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["ADDYMD"]) != true )
			{
            	sBuf     = Query2->FieldValues["ADDYMD"];                      		//登録日
            	strcpy(pRIREKI_DATA[i1].ADDYMD     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ADDTIM       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["ADDTIM"]) != true )
			{
            	sBuf     = Query2->FieldValues["ADDTIM"];                       	//登録時間
            	strcpy(pRIREKI_DATA[i1].ADDTIM     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDYMD       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["UPDYMD"]) != true )
			{
            	sBuf     = Query2->FieldValues["UPDYMD"];                         	//変更日
            	strcpy(pRIREKI_DATA[i1].UPDYMD     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDTIM       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["UPDTIM"]) != true )
			{
            	sBuf     = Query2->FieldValues["UPDTIM"];                          	//変更時間
            	strcpy(pRIREKI_DATA[i1].UPDTIM     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDCHR       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["UPDCHR"]) != true )
			{
            	sBuf     = Query2->FieldValues["UPDCHR"];                      		//更新者
            	strcpy(pRIREKI_DATA[i1].UPDCHR     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDCNT       ,"");                    		//単位
            if ( VarIsNull(Query2->FieldValues["UPDCNT"]) != true )
			{
            	sBuf     = Query2->FieldValues["UPDCNT"];                         	//更新回数
            	strcpy(pRIREKI_DATA[i1].UPDCNT     ,sBuf.c_str());
			}
//SOKU Result Read ///////////////////////////////////////////////////////////////////////
			strcpy(pRIREKI_DATA[i1].SOKU_VAL01,"");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL01"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL01"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL01		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL02,"");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL02"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL02"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL02		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL03,"");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL03"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL03"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL03		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL04,"");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL04"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL04"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL04		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL05,"");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL05"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL05"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL05		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL06,"");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL06"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL06"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL06		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL07,"");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL07"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL07"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL07		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL08,"");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL08"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL08"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL08		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL09,"");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL09"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL09"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL09		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL10,"");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL10"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL10"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL10		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_SU,"1");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL_SU"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL_SU"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_SU		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_AVE,"0.0");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL_AVE"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL_AVE"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_AVE		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_MAX,"0.0");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL_MAX"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL_MAX"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_MAX		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_MIN,"0.0");
            if(VarIsNull(Query2->FieldValues["SOKU_VAL_MIN"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_VAL_MIN"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_MIN		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_OK,"0");
            if(VarIsNull(Query2->FieldValues["SOKU_OK"])!=true)
            {
            	sBuf = Query2->FieldValues["SOKU_OK"];
                strcpy(pRIREKI_DATA[i1].SOKU_OK		,sBuf.c_str());
            }
//DISP Result Read ///////////////////////////////////////////////////////////////////////
			strcpy(pRIREKI_DATA[i1].DISP_VAL01,"");
            if(VarIsNull(Query2->FieldValues["DISP_VAL01"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL01"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL01		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL02,"");
            if(VarIsNull(Query2->FieldValues["DISP_VAL02"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL02"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL02		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL03,"");
            if(VarIsNull(Query2->FieldValues["DISP_VAL03"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL03"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL03		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL04,"");
            if(VarIsNull(Query2->FieldValues["DISP_VAL04"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL04"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL04		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL05,"");
            if(VarIsNull(Query2->FieldValues["DISP_VAL05"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL05"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL05		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL06,"");
            if(VarIsNull(Query2->FieldValues["DISP_VAL06"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL06"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL06		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL07,"");
            if(VarIsNull(Query2->FieldValues["DISP_VAL07"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL07"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL07		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL08,"");
            if(VarIsNull(Query2->FieldValues["DISP_VAL08"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL08"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL08		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL09,"");
            if(VarIsNull(Query2->FieldValues["DISP_VAL09"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL09"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL09		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL10,"");
            if(VarIsNull(Query2->FieldValues["DISP_VAL10"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL10"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL10		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_SU,"1");
            if(VarIsNull(Query2->FieldValues["DISP_VAL_SU"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL_SU"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_SU		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_AVE,"0.0");
            if(VarIsNull(Query2->FieldValues["DISP_VAL_AVE"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL_AVE"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_AVE		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_MAX,"0.0");
            if(VarIsNull(Query2->FieldValues["DISP_VAL_MAX"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL_MAX"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_MAX		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_MIN,"0.0");
            if(VarIsNull(Query2->FieldValues["DISP_VAL_MIN"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_VAL_MIN"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_MIN		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_OK,"0");
            if(VarIsNull(Query2->FieldValues["DISP_OK"])!=true)
            {
            	sBuf = Query2->FieldValues["DISP_OK"];
                strcpy(pRIREKI_DATA[i1].DISP_OK		,sBuf.c_str());
            }
//日付、時刻、更新者の読み取り
            strcpy(pRIREKI_DATA[i1].SKTYMD,"0");
            if(VarIsNull(Query2->FieldValues["SKTYMD"])!=true)
            {
            	sBuf = Query2->FieldValues["SKTYMD"];
                strcpy(pRIREKI_DATA[i1].SKTYMD		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ADDYMD,"0");
            if(VarIsNull(Query2->FieldValues["ADDYMD"])!=true)
            {
            	sBuf = Query2->FieldValues["ADDYMD"];
                strcpy(pRIREKI_DATA[i1].ADDYMD		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ADDTIM,"0");
            if(VarIsNull(Query2->FieldValues["ADDTIM"])!=true)
            {
            	sBuf = Query2->FieldValues["ADDTIM"];
                strcpy(pRIREKI_DATA[i1].ADDTIM		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDYMD,"0");
            if(VarIsNull(Query2->FieldValues["UPDYMD"])!=true)
            {
            	sBuf = Query2->FieldValues["UPDYMD"];
                strcpy(pRIREKI_DATA[i1].UPDYMD		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDTIM,"0");
            if(VarIsNull(Query2->FieldValues["UPDTIM"])!=true)
            {
            	sBuf = Query2->FieldValues["UPDTIM"];
                strcpy(pRIREKI_DATA[i1].UPDTIM		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDCHR,"0");
            if(VarIsNull(Query2->FieldValues["UPDCHR"])!=true)
            {
            	sBuf = Query2->FieldValues["UPDCHR"];
                strcpy(pRIREKI_DATA[i1].UPDCHR		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDCNT,"0");
            if(VarIsNull(Query2->FieldValues["UPDCNT"])!=true)
            {
            	sBuf = Query2->FieldValues["UPDCNT"];
                strcpy(pRIREKI_DATA[i1].UPDCNT		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].UPDNAME , "");
            if(VarIsNull(Query2->FieldValues["UPDNAME"])!=true)
            {
            	sBuf = Query2->FieldValues["UPDNAME"];
                strcpy(pRIREKI_DATA[i1].UPDNAME , sBuf.c_str());
            }

            i1 ++;
            Query2->Next();
		}
//存在するロットの測定実績データの読み込み完了
//カラムの位置検索
		iCol = 0;

        while(iCol <= SGr_tRIRE->ColCount)
        {
        	if( SGr_tRIRE->Cells[iCol][0] == sLot) break;
			iCol++;
        }

//出荷検査のグリッドをすべて灰色にする
		for(i2= 1; i2 <  SGr_vSOKU_SYUKA->RowCount ; i2++)
        {
        	SGr_vRIRE_SYUKA->Font->Color = clGray;
			strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount)+i2].RESULT,AnsiString("").c_str());	//項目NO=0なら項目が無い
			strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount)+i2].DISP_RESULT,AnsiString("").c_str());	//項目NO=0なら項目が無い
			strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount)+i2].KOMK_NO,"-999");	//項目NO=0なら項目が無い
        }
//測定機器NO、測定項目NOの一致している場所を探索
		i4 = i1;
        iRow = 1;
        for( i1 = 0; i1 < i4;i1++)
        {
        	i2 = 0;
			iRow = 1;
            while( 1 )
            {
                //測定項目名+測定機器NO → 測定項目名+測定機器NO+単位
				sBuf = AnsiString(pORDATA[i2].KOMK_NM).Trim() + AnsiString(pORDATA[i2].KOMK_SUB).Trim();
				sBuf1 =AnsiString(pRIREKI_DATA[i1].KOMK_NM).Trim() + AnsiString(pRIREKI_DATA[i1].KOMK_SUB).Trim();
            	if((AnsiString(pORDATA[i2].KIKI_NO).ToIntDef(0) == AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0))
                && (sBuf == sBuf1)
            	&& (AnsiString(pORDATA[i2].KOMK_NO).ToIntDef(0) == AnsiString(pRIREKI_DATA[i1].KOMK_NO).ToIntDef(0))
            	&& (AnsiString(pORDATA[i2].TANI).Trim() == AnsiString(pRIREKI_DATA[i1].TANI).Trim())
                ) break;
                iRow += AnsiString(pORDATA[i2].SOKU_SU).ToIntDef(0);
                i2++;
				if( i2 >= iOrCnt ) break;
            }
			if( i2 >= iOrCnt ) break;		//不正なデータと思われるのでbreak
//履歴データのデータ読み取り
            iTempRow = iRow;
            GetLotKIKAKU(i1, &dMAX, &dMIN);
            for(i3 = 0; i3 <  AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) ; i3++ )
            {
            	strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DTKSHIN 		, pRIREKI_DATA[i1].DTKSHIN);
                strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].LOTNO 		, pRIREKI_DATA[i1].LOTNO);
                strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].HINBAN 		, pRIREKI_DATA[i1].HINBAN);
			   	strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].UNQ_NO 		, pRIREKI_DATA[i1].UNQ_NO);
			  	strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].ORDER_NO		, pRIREKI_DATA[i1].ORDER_NO);
			 	strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].SKB_NO 		, pRIREKI_DATA[i1].SKB_NO);
				strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].HINBAN_SK	, pRIREKI_DATA[i1].HINBAN_SK);
		   		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KOMK_NO 		, pRIREKI_DATA[i1].KOMK_NO);
		   		pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].INS_ON = true;
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KOMK_NM 		, pRIREKI_DATA[i1].KOMK_NM);
		 		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KOMK_ENG		, pRIREKI_DATA[i1].KOMK_ENG);
				strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KOMK_SUB		, pRIREKI_DATA[i1].KOMK_SUB);
	   			strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KOMK_SUB_ENG , pRIREKI_DATA[i1].KOMK_SUB_ENG);
	  			strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKI_NO 		, pRIREKI_DATA[i1].KIKI_NO);
	 			strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKI_NM 		, pRIREKI_DATA[i1].KIKI_NM);
				strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].TANI    		, pRIREKI_DATA[i1].TANI);
			  	strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKA_TYPE	, pRIREKI_DATA[i1].KIKA_TYPE);
			 	strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKA_KIND	, pRIREKI_DATA[i1].KIKA_KIND);
				strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKA_DECI	, pRIREKI_DATA[i1].KIKA_DECI);
		   		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKA_NUM1	, pRIREKI_DATA[i1].KIKA_NUM1);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKA_NUM2	, pRIREKI_DATA[i1].KIKA_NUM2);
		 		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKA_NUM3	, pRIREKI_DATA[i1].KIKA_NUM3);
				strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKA_STR		, pRIREKI_DATA[i1].KIKA_STR);
	   			strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKA_SUB1	, pRIREKI_DATA[i1].KIKA_SUB1);
	  			strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKA_SUB2	, pRIREKI_DATA[i1].KIKA_SUB2);
	 			strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKA_SUB3	, pRIREKI_DATA[i1].KIKA_SUB3);
				strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].SOKU_SU 		, pRIREKI_DATA[i1].SOKU_SU);
   				strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].SOKU_FLG		, pRIREKI_DATA[i1].SOKU_FLG);
  				strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].TOKU_FLG		, pRIREKI_DATA[i1].TOKU_FLG);
				strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].KIKA_PRT		, pRIREKI_DATA[i1].KIKA_PRT);
		   		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].VALUE_TYPE	, pRIREKI_DATA[i1].VALUE_TYPE);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].VALUE_DECI	, pRIREKI_DATA[i1].VALUE_DECI);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].SOKU_VAL_SU	, pRIREKI_DATA[i1].SOKU_VAL_SU);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].SOKU_VAL_AVE	, pRIREKI_DATA[i1].SOKU_VAL_AVE);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].SOKU_VAL_MAX	, pRIREKI_DATA[i1].SOKU_VAL_MAX);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].SOKU_VAL_MIN	, pRIREKI_DATA[i1].SOKU_VAL_MIN);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].SOKU_OK		, pRIREKI_DATA[i1].SOKU_OK);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_VAL_SU	, pRIREKI_DATA[i1].DISP_VAL_SU);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_VAL_AVE	, pRIREKI_DATA[i1].DISP_VAL_AVE);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_VAL_MAX	, pRIREKI_DATA[i1].DISP_VAL_MAX);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_VAL_MIN	, pRIREKI_DATA[i1].DISP_VAL_MIN);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_OK		, pRIREKI_DATA[i1].DISP_OK);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].SKTYMD		, pRIREKI_DATA[i1].SKTYMD);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].ADDYMD		, pRIREKI_DATA[i1].ADDYMD);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].ADDTIM		, pRIREKI_DATA[i1].ADDTIM);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].UPDYMD		, pRIREKI_DATA[i1].UPDYMD);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].UPDTIM		, pRIREKI_DATA[i1].UPDTIM);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].UPDCHR		, pRIREKI_DATA[i1].UPDCHR);
		  		strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].UPDCNT		, pRIREKI_DATA[i1].UPDCNT);
                strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].UPDNAME ,  pRIREKI_DATA[i1].UPDNAME);
				//規格
                pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].MAX = dMAX ;
                pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].MIN = dMIN ;
                iRow++;
            }
            iRow = iTempRow;
            for(i3 = 0; i3 <  AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) ; i3++ )
            {
            	switch( i3 )
                {
                case 0:
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL01);
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL01);
                    break;
                case 1:
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL02);
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL02);
                    break;
                case 2:
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL03);
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL03);
                    break;
                case 3:
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL04);
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL04);
                    break;
                case 4:
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL05);
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL05);
                    break;
                case 5:
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL06);
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL06);
                    break;
                case 6:
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL07);
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL07);
                    break;
                case 7:
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL08);
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vSOKU_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL08);
                    break;
                case 8:
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL09);
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL09);
                    break;
                case 9:
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL10);
					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL10);
                    break;
                default:
    				sBuf  = "SELECT * FROM KSD03";
    				sBuf += " WHERE DTKSHIN = '" + AnsiString(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].DTKSHIN) 	+ "'";
    				sBuf += " AND LOTNO  = '"	 + AnsiString(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].LOTNO) 	+ "'";                        //出荷検査項目、材料証明項目
    				sBuf += " AND HINBAN = '"	 + AnsiString(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].HINBAN) 	+ "'";                        //出荷検査項目、材料証明項目
    				sBuf += " AND UNQ_NO =  "	 + AnsiString(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow].UNQ_NO) 	+ " ";                        //出荷検査項目、材料証明項目
    				sBuf += " ORDER BY SOKU_NO";                                      //出荷検査項目、材料証明項目
					//For Debug
                    if( iDEBUG == 1 )
                    {
                        ClpBrd = Clipboard();
                        ClpBrd->Open();
     				    ClpBrd->SetTextBuf(sBuf.c_str());
     				    ClpBrd->Close();
                    }
					// Initial Query
					Query6->Close();
    				Query6->SQL->Clear();
    				Query6->SQL->Add(sBuf);
    				Query6->Open();
                    Query6->Active = true;
                    while(Query6->Eof != true )
                    {
    					sBuf = "";
                		if(VarIsNull(Query6->FieldValues["SOKU_NO"])!=true)
                		{
                        	sBuf = Query6->FieldValues["SOKU_NO"];
					    }
                        if(AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) < sBuf.ToIntDef(0)) break;
                        i3 = sBuf.ToIntDef(11)-11;
    					sBuf = "";
                		if(VarIsNull(Query6->FieldValues["SOKU_VAL"])!=true)
                		{
                        	sBuf = Query6->FieldValues["SOKU_VAL"];
				    	}
    					strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow +i3].RESULT		, sBuf.c_str());
    					sBuf = "";
                		if(VarIsNull(Query6->FieldValues["DISP_VAL"])!=true)
                		{
 	                        sBuf = Query6->FieldValues["DISP_VAL"];
                        }
                        strcpy(pCELLINFO_RIRE_SYUKA[(iCol * SGr_vRIRE_SYUKA->RowCount) + iRow +i3].DISP_RESULT	, sBuf.c_str());
                        Query6->Next();
                    }
                    i3 = AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0)+1;
					Query6->Close();
                    break;
                }
                iRow ++;
            }
            iRow = iTempRow + AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0);
        }
   	}
	Query2->Close();
}


//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材（測定）の中で履歴があるデータの読み込み。
//
//  機能説明
//    素材（測定）の履歴データを読み込み、CELLINFOに代入します。
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
void __fastcall TForm1::Set_SOKU_SOZAIJISSEKI(void)
{
	int i1,i2,i3,i4;
	int iCol,iRow,iUNQNO;
    int iTempRow;
	AnsiString sLot,sUNQNO;
    AnsiString sBuf,sBuf1;
    double dMAX,dMIN;
    AnsiString sLot_Where;

	sLot = "";
	sBuf = "";
	sBuf1 = "";
    sUNQNO ="";

	if(!hCELLINFO_SOKU_SOZAI) return;			//メモリが確保されていない時は処理を中止
	for(i1 = 0;i1 <SGr_tSOKU->ColCount ; i1++)
	{
        if(SGr_tSOKU->Cells[i1][0].Trim().Length() != 0)
        {
		    sLot += "'" + SGr_tSOKU->Cells[i1][0].Trim() + "',";
        }
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
	for(i1 = 0;i1 <SGr_tSOKU->ColCount ; i1++)
	{
        if(SGr_tSOKU->Cells[i1][0].Trim().Length() != 0)
        {
            sLot_Where += "( LOTNO='" + SGr_tSOKU->Cells[i1][0] + "' AND ";
            sLot_Where += " HINBAN='" + SGr_tSOKU->Cells[i1][1] + "') OR ";
        }
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

	i1 = 0;
    //////////////////////////////////////////////////////////////
    //	UNQ_NOでは検索キーとして不適当なのでKOMK_NOに変更します
    //////////////////////////////////////////////////////////////
	while( 1 )
	{
    	if(i1 >= iSOZAI_ContCnt ) break;
		iUNQNO = AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO).ToIntDef(0);
		sUNQNO += " " + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO) + " ,";
		while(iUNQNO == AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO).ToIntDef(0))
		{
			i1++;
			if(i1 >= iSOZAI_ContCnt ) break;
		}
	}
	sUNQNO = sUNQNO.SubString(1,sUNQNO.Length()-1);



    if(sLot.Length() < 3 ) return;		//ロットの入力がない場合

	sBuf  = "SELECT  KSD02.*, SM12S.TANNAM As UPDNAME ";
	sBuf += " FROM KSD02 LEFT JOIN SM12S ON KSD02.UPDCHR = SM12S.TANSYA ";
    sBuf += " WHERE DTKSHIN = '" + sNowDTKSHIN + "'";
    sBuf += " AND SKB_NO = 1";                        //出荷検査項目、材料証明項目
    //sBuf += " AND LOTNO IN ("+ sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";

	if(sUNQNO.Length() > 3 )
	{
		sBuf += " AND KOMK_NO IN ("+ sUNQNO + ")";
	}
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
	Query4->Close();
	Query4->Active = false;
    Query4->SQL->Clear();
    Query4->SQL->Add(sBuf);
    Query4->Open();
    Query4->Active = true;


    //履歴データが有る出荷ロットが呼び出されているはず
	while(Query4->Eof != true )
    {
    	i1 = 0;
        sLot = Query4->FieldValues["LOTNO"];

        //ロット毎にメモリの初期化が必要
        memset(pRIREKI_DATA,0x00,sizeof(pRIREKI_DATA));

        while( sLot == Query4->FieldValues["LOTNO"] && Query4->Eof != true)
        {
            strcpy(pRIREKI_DATA[i1].DTKSHIN		,"");
            if ( VarIsNull(Query4->FieldValues["DTKSHIN"]) != true)
            {
	        	sBuf	= Query4->FieldValues["DTKSHIN"];							//得意先項目品番
    	        strcpy(pRIREKI_DATA[i1].DTKSHIN			,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].LOTNO		,"");
			if ( VarIsNull(Query4->FieldValues["LOTNO"]) != true  )
            {
            	sBuf = Query4->FieldValues["LOTNO"];                   				//ロットNO
            	strcpy(pRIREKI_DATA[i1].LOTNO      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].HINBAN		,"");
			if ( VarIsNull(Query4->FieldValues["HINBAN"]) != true  )
            {
            	sBuf = Query4->FieldValues["HINBAN"];                   			//工管発行日 onishi
            	strcpy(pRIREKI_DATA[i1].HINBAN      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UNQ_NO		,"");
			if ( VarIsNull(Query4->FieldValues["UNQ_NO"]) != true )
            {
            	sBuf = Query4->FieldValues["UNQ_NO"];                   			//明細NO
            	strcpy(pRIREKI_DATA[i1].UNQ_NO      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ORDER_NO		,"");
			if ( VarIsNull(Query4->FieldValues["ORDER_NO"]) != true)
            {
            	sBuf = Query4->FieldValues["ORDER_NO"];                   		  	//表示・印刷順
            	strcpy(pRIREKI_DATA[i1].ORDER_NO      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SKB_NO		,"");
			if ( VarIsNull(Query4->FieldValues["SKB_NO"]) != true )
            {
            	sBuf = Query4->FieldValues["SKB_NO"];                   		 	//識別NO
            	strcpy(pRIREKI_DATA[i1].SKB_NO      		,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].HINBAN_SK		,"");                      //品番
            if ( VarIsNull(Query4->FieldValues["HINBAN_SK"]) != true )
            {
            	sBuf	= Query4->FieldValues["HINBAN_SK"];
                strcpy(pRIREKI_DATA[i1].HINBAN_SK	,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KOMK_NO		,"");                      //品番
            if ( VarIsNull(Query4->FieldValues["KOMK_NO"]) != true )
            {
	            sBuf    = Query4->FieldValues["KOMK_NO"];                           //測定項目NO
    	        strcpy(pRIREKI_DATA[i1].KOMK_NO			,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KOMK_NM,"");                 				//測定項目名称
            if ( VarIsNull(Query4->FieldValues["KOMK_NM"]) != true )
            {
            	sBuf = Query4->FieldValues["KOMK_NM"];
                strcpy(pRIREKI_DATA[i1].KOMK_NM		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_ENG,"");                 				//測定項目名称（英語)
            if ( VarIsNull(Query4->FieldValues["KOMK_ENG"]) != true )
            {
            	sBuf = Query4->FieldValues["KOMK_ENG"];
                strcpy(pRIREKI_DATA[i1].KOMK_ENG		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_SUB,"");                     			//測定項目サブ名称
            if ( VarIsNull(Query4->FieldValues["KOMK_SUB"]) != true )
            {
            	sBuf = Query4->FieldValues["KOMK_SUB"];
                strcpy(pRIREKI_DATA[i1].KOMK_SUB	,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_SUB_ENG,"");                     	    //測定項目サブ名称(英語)
            if ( VarIsNull(Query4->FieldValues["KOMK_SUB_ENG"]) != true )
            {
            	sBuf = Query4->FieldValues["KOMK_SUB_ENG"];
                strcpy(pRIREKI_DATA[i1].KOMK_SUB_ENG	,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KIKI_NO,"");                     	    //測定項目サブ名称(英語)
            if ( VarIsNull(Query4->FieldValues["KIKI_NO"]) != true )
            {
	            sBuf    = Query4->FieldValues["KIKI_NO"];                       	//測定機器NO
    	        strcpy(pRIREKI_DATA[i1].KIKI_NO			,sBuf.c_str());
         	}
            strcpy(pRIREKI_DATA[i1].KIKI_NM,"");
            if ( VarIsNull(Query4->FieldValues["KIKI_NM"]) != true )				//測定機器名称
            {
            	sBuf = Query4->FieldValues["KIKI_NM"];
                strcpy(pRIREKI_DATA[i1].KIKI_NM		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].TANI       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["TANI"]) != true  )
			{
            	sBuf       = Query4->FieldValues["TANI"];
            	strcpy(pRIREKI_DATA[i1].TANI       ,sBuf.c_str());
			}                                                           		//規格タイプ

            strcpy(pRIREKI_DATA[i1].KIKA_TYPE       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_TYPE"]) != true )
			{
	            sBuf  = Query4->FieldValues["KIKA_TYPE"];
    	        strcpy(pRIREKI_DATA[i1].KIKA_TYPE  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_KIND       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_KIND"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_KIND"];              				//規格種類
            	strcpy(pRIREKI_DATA[i1].KIKA_KIND  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_DECI       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_DECI"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_DECI"];                         	//規格小数点以下桁数
            	strcpy(pRIREKI_DATA[i1].KIKA_DECI  ,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].KIKA_NUM1       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_NUM1"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_NUM1"];                         	//規格値１
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM1  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_NUM2       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_NUM2"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_NUM2"];                      		//規格値２
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM2  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_NUM3       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_NUM3"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_NUM3"];                       	//規格値３
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM3  ,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].KIKA_STR       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_STR"]) != true  )
			{
            	sBuf   = Query4->FieldValues["KIKA_STR"];                        	//規格値文字
            	strcpy(pRIREKI_DATA[i1].KIKA_STR   ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB1       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_SUB1"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_SUB1"];                       	//規格値サブ１
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB1  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB2       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_SUB2"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_SUB2"];                         	//規格値サブ２
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB2  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB3       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_SUB3"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_SUB3"];                        	//規格値サブ３
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB3  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_SU       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["SOKU_SU"]) != true   )
			{
            	sBuf    = Query4->FieldValues["SOKU_SU"];                   		//測定指示ｎ数
            	strcpy(pRIREKI_DATA[i1].SOKU_SU    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_FLG       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["SOKU_FLG"]) != true  )
			{
            	sBuf    = Query4->FieldValues["SOKU_FLG"];                   		//測定項目の有無
            	strcpy(pRIREKI_DATA[i1].SOKU_FLG    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].TOKU_FLG       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["TOKU_FLG"]) != true  )
			{
	            sBuf    = Query4->FieldValues["TOKU_FLG"];                   		//特別項目の有無
	            strcpy(pRIREKI_DATA[i1].TOKU_FLG    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_PRT       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_PRT"]) != true  )
			{
            	sBuf    = Query4->FieldValues["KIKA_PRT"];                   		//上限下限値の印刷
            	strcpy(pRIREKI_DATA[i1].KIKA_PRT    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].VALUE_TYPE       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["VALUE_TYPE"]) != true)
			{
            	sBuf    = Query4->FieldValues["VALUE_TYPE"];                   		//測定値表現
            	strcpy(pRIREKI_DATA[i1].VALUE_TYPE    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].VALUE_DECI       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["VALUE_DECI"]) != true)
			{
            	sBuf    = Query4->FieldValues["VALUE_DECI"];                   		//測定値小数点以下桁数
            	strcpy(pRIREKI_DATA[i1].VALUE_DECI    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SKTYMD       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["SKTYMD"]) != true )
			{
            	sBuf     = Query4->FieldValues["SKTYMD"];                       	//測定日
            	strcpy(pRIREKI_DATA[i1].SKTYMD     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ADDYMD       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["ADDYMD"]) != true )
			{
            	sBuf     = Query4->FieldValues["ADDYMD"];                      		//登録日
            	strcpy(pRIREKI_DATA[i1].ADDYMD     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ADDTIM       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["ADDTIM"]) != true )
			{
            	sBuf     = Query4->FieldValues["ADDTIM"];                       	//登録時間
            	strcpy(pRIREKI_DATA[i1].ADDTIM     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDYMD       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["UPDYMD"]) != true )
			{
            	sBuf     = Query4->FieldValues["UPDYMD"];                         	//変更日
            	strcpy(pRIREKI_DATA[i1].UPDYMD     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDTIM       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["UPDTIM"]) != true )
			{
            	sBuf     = Query4->FieldValues["UPDTIM"];                          	//変更時間
            	strcpy(pRIREKI_DATA[i1].UPDTIM     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDCHR       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["UPDCHR"]) != true )
			{
            	sBuf     = Query4->FieldValues["UPDCHR"];                      		//更新者
            	strcpy(pRIREKI_DATA[i1].UPDCHR     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDCNT       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["UPDCNT"]) != true )
			{
            	sBuf     = Query4->FieldValues["UPDCNT"];                         	//更新回数
            	strcpy(pRIREKI_DATA[i1].UPDCNT     ,sBuf.c_str());
			}

    		strcpy(pRIREKI_DATA[i1].UPDNAME , "");
            if ( VarIsNull(Query4->FieldValues["UPDNAME"]) != true )
			{
            	sBuf     = Query4->FieldValues["UPDNAME"];                         	//更新者
            	strcpy(pRIREKI_DATA[i1].UPDNAME , sBuf.c_str());
			}

//SOKU Result Read ///////////////////////////////////////////////////////////////////////
			strcpy(pRIREKI_DATA[i1].SOKU_VAL01,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL01"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL01"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL01		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL02,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL02"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL02"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL02		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL03,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL03"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL03"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL03		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL04,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL04"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL04"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL04		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL05,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL05"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL05"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL05		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL06,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL06"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL06"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL06		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL07,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL07"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL07"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL07		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL08,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL08"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL08"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL08		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL09,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL09"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL09"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL09		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL10,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL10"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL10"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL10		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_SU,"1");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL_SU"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL_SU"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_SU		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_AVE,"0.0");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL_AVE"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL_AVE"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_AVE		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_MAX,"0.0");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL_MAX"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL_MAX"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_MAX		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_MIN,"0.0");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL_MIN"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL_MIN"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_MIN		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_OK,"0");
            if(VarIsNull(Query4->FieldValues["SOKU_OK"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_OK"];
                strcpy(pRIREKI_DATA[i1].SOKU_OK		,sBuf.c_str());
            }
//DISP Result Read ///////////////////////////////////////////////////////////////////////
			strcpy(pRIREKI_DATA[i1].DISP_VAL01,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL01"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL01"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL01		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL02,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL02"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL02"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL02		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL03,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL03"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL03"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL03		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL04,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL04"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL04"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL04		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL05,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL05"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL05"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL05		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL06,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL06"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL06"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL06		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL07,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL07"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL07"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL07		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL08,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL08"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL08"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL08		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL09,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL09"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL09"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL09		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL10,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL10"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL10"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL10		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_SU,"1");
            if(VarIsNull(Query4->FieldValues["DISP_VAL_SU"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL_SU"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_SU		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_AVE,"0.0");
            if(VarIsNull(Query4->FieldValues["DISP_VAL_AVE"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL_AVE"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_AVE		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_MAX,"0.0");
            if(VarIsNull(Query4->FieldValues["DISP_VAL_MAX"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL_MAX"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_MAX		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_MIN,"0.0");
            if(VarIsNull(Query4->FieldValues["DISP_VAL_MIN"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL_MIN"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_MIN		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_OK,"0");
            if(VarIsNull(Query4->FieldValues["DISP_OK"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_OK"];
                strcpy(pRIREKI_DATA[i1].DISP_OK		,sBuf.c_str());
            }


            i1 ++;
            Query4->Next();
		}
//存在するロットの測定実績データの読み込み完了
//カラムの位置検索
		iCol = 0;
        AnsiString sLot2;
        for(iCol = 0;iCol < SGr_tSOKU->ColCount;iCol++)
        {
        	if( SGr_tSOKU->Cells[iCol][0].Trim() == sLot) break;
        }
//履歴の有ったグリッドをすべて灰色にする
		for(i2= 1; i2 <  SGr_vSOKU_SOZAI->RowCount ; i2++)
        {
            strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + i2].KOMK_NO,"-999");
            pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + i2].INS_ON = false;
        }
//測定機器NO、測定項目NOの一致している場所を探索
		i4 = i1;
        iRow = 1;
        for( i1 = 0; i1 < i4;i1++)
        {
        	i2 = 0;
			iRow = 1;
            while( 1 )
            {
				sBuf = AnsiString(pSOZAI_OR_DATA[i2].KOMK_NM).Trim() + AnsiString(pSOZAI_OR_DATA[i2].KOMK_SUB).Trim();
				sBuf1 =AnsiString(pRIREKI_DATA[i1].KOMK_NM).Trim() + AnsiString(pRIREKI_DATA[i1].KOMK_SUB).Trim();
            	if((AnsiString(pSOZAI_OR_DATA[i2].KIKI_NO).ToIntDef(0) == AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0))
                && (sBuf == sBuf1)
				&& (AnsiString(pSOZAI_OR_DATA[i2].HINBAN_SK) == AnsiString(pRIREKI_DATA[i1].HINBAN_SK))
				&& (AnsiString(pSOZAI_OR_DATA[i2].KOMK_NO).ToIntDef(0) == AnsiString(pRIREKI_DATA[i1].KOMK_NO).ToIntDef(0))
                ) break;
                iRow += AnsiString(pSOZAI_OR_DATA[i2].SOKU_SU).ToIntDef(0);
                i2++;
            	if( i2 >= iSOZAI_ORCNT ) break;		//無限ループから抜けます
            }
            if( i2 >= iSOZAI_ORCNT ) break;		//不正ロットから抜けます

//履歴データのデータ読み取り（10件まで　11件以上を考えること）
            iTempRow = iRow;
            GetLotKIKAKU(i1, &dMAX, &dMIN);
            for(i3 = 0; i3 <  AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) ; i3++ )
            {
            	strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DTKSHIN 		, pRIREKI_DATA[i1].DTKSHIN);
                strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].LOTNO 		, pRIREKI_DATA[i1].LOTNO);
                strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].HINBAN 		, pRIREKI_DATA[i1].HINBAN);
			   	strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].UNQ_NO 		, pRIREKI_DATA[i1].UNQ_NO);
			  	strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].ORDER_NO		, pRIREKI_DATA[i1].ORDER_NO);
			 	strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].SKB_NO 		, pRIREKI_DATA[i1].SKB_NO);
				strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].HINBAN_SK	, pRIREKI_DATA[i1].HINBAN_SK);
		   		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KOMK_NO 		, pRIREKI_DATA[i1].KOMK_NO);
		   		pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].INS_ON = true;
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KOMK_NM 		, pRIREKI_DATA[i1].KOMK_NM);
		 		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KOMK_ENG		, pRIREKI_DATA[i1].KOMK_ENG);
				strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KOMK_SUB		, pRIREKI_DATA[i1].KOMK_SUB);
	   			strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KOMK_SUB_ENG , pRIREKI_DATA[i1].KOMK_SUB_ENG);
	  			strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKI_NO 		, pRIREKI_DATA[i1].KIKI_NO);
	 			strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKI_NM 		, pRIREKI_DATA[i1].KIKI_NM);
				strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].TANI    		, pRIREKI_DATA[i1].TANI);
			  	strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKA_TYPE	, pRIREKI_DATA[i1].KIKA_TYPE);
			 	strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKA_KIND	, pRIREKI_DATA[i1].KIKA_KIND);
				strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKA_DECI	, pRIREKI_DATA[i1].KIKA_DECI);
		   		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKA_NUM1	, pRIREKI_DATA[i1].KIKA_NUM1);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKA_NUM2	, pRIREKI_DATA[i1].KIKA_NUM2);
		 		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKA_NUM3	, pRIREKI_DATA[i1].KIKA_NUM3);
				strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKA_STR		, pRIREKI_DATA[i1].KIKA_STR);
	   			strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKA_SUB1	, pRIREKI_DATA[i1].KIKA_SUB1);
	  			strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKA_SUB2	, pRIREKI_DATA[i1].KIKA_SUB2);
	 			strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKA_SUB3	, pRIREKI_DATA[i1].KIKA_SUB3);
				strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].SOKU_SU 		, pRIREKI_DATA[i1].SOKU_SU);
   				strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].SOKU_FLG		, pRIREKI_DATA[i1].SOKU_FLG);
  				strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].TOKU_FLG		, pRIREKI_DATA[i1].TOKU_FLG);
				strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].KIKA_PRT		, pRIREKI_DATA[i1].KIKA_PRT);
		   		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].VALUE_TYPE	, pRIREKI_DATA[i1].VALUE_TYPE);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].VALUE_DECI	, pRIREKI_DATA[i1].VALUE_DECI);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].SOKU_VAL_SU	, pRIREKI_DATA[i1].SOKU_VAL_SU);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].SOKU_VAL_AVE	, pRIREKI_DATA[i1].SOKU_VAL_AVE);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].SOKU_VAL_MAX	, pRIREKI_DATA[i1].SOKU_VAL_MAX);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].SOKU_VAL_MIN	, pRIREKI_DATA[i1].SOKU_VAL_MIN);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].SOKU_OK		, pRIREKI_DATA[i1].SOKU_OK);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_VAL_SU	, pRIREKI_DATA[i1].DISP_VAL_SU);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_VAL_AVE	, pRIREKI_DATA[i1].DISP_VAL_AVE);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_VAL_MAX	, pRIREKI_DATA[i1].DISP_VAL_MAX);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_VAL_MIN	, pRIREKI_DATA[i1].DISP_VAL_MIN);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_OK		, pRIREKI_DATA[i1].DISP_OK);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].SKTYMD		, pRIREKI_DATA[i1].SKTYMD);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].ADDYMD		, pRIREKI_DATA[i1].ADDYMD);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].ADDTIM		, pRIREKI_DATA[i1].ADDTIM);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].UPDYMD		, pRIREKI_DATA[i1].UPDYMD);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].UPDTIM		, pRIREKI_DATA[i1].UPDTIM);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].UPDCHR		, pRIREKI_DATA[i1].UPDCHR);
		  		strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].UPDCNT		, pRIREKI_DATA[i1].UPDCNT);
                strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].UPDNAME 		, pRIREKI_DATA[i1].UPDNAME);
				//規格
                pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].MAX = dMAX ;
                pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].MIN = dMIN ;
                iRow++;
            }
            iRow = iTempRow;
            for(i3 = 0; i3 <  AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) ; i3++ )
            {
            	switch( i3 )
                {
                case 0:
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL01);
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL01);
                    break;
                case 1:
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL02);
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL02);
                    break;
                case 2:
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL03);
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL03);
                    break;
                case 3:
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL04);
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL04);
                    break;
                case 4:
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL05);
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL05);
                    break;
                case 5:
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL06);
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL06);
                    break;
                case 6:
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL07);
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL07);
                    break;
                case 7:
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL08);
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL08);
                    break;
                case 8:
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL09);
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL09);
                    break;
                case 9:
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL10);
					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL10);
                    break;
                default:
    				sBuf  = "SELECT * FROM KSD03";
    				sBuf += " WHERE DTKSHIN = '" + AnsiString(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].DTKSHIN) 	+ "'";
    				sBuf += " AND LOTNO = '"	 + AnsiString(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].LOTNO) 	+ "'";                        //出荷検査項目、材料証明項目
    				sBuf += " AND UNQ_NO = "	 + AnsiString(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow].UNQ_NO) 	+ " ";                        //出荷検査項目、材料証明項目
                    sBuf += " ORDER BY SOKU_NO ASC";
					//For Debug
                    if( iDEBUG == 1 )
                    {
                        ClpBrd = Clipboard();
                        ClpBrd->Open();
     				    ClpBrd->SetTextBuf(sBuf.c_str());
     				    ClpBrd->Close();
                    }
					// Initial Query
					Form1->Query7->Close();
    				Form1->Query7->SQL->Clear();
    				Form1->Query7->SQL->Add(sBuf);
    				Form1->Query7->Open();
                    Form1->Query7->Active = true;
                    while( Query7->Eof != true)
                    {
					    sBuf = "";
        			    if ( VarIsNull(Query7->FieldValues["SOKU_NO"]) != true )
					    {
                    	    sBuf = Query7->FieldValues["SOKU_NO"];
					    }
                        if(AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) < sBuf.ToIntDef(0)) break;
                        i3 = sBuf.ToIntDef(11) - 11;
    					sBuf = "";
            			if ( VarIsNull(Query7->FieldValues["SOKU_VAL"]) != true )
		    			{
                        	sBuf = Query7->FieldValues["SOKU_VAL"];
				    	}
                        //SGr_vRIRE_SOZAI->Cells[iCol][iRow] = sBuf;
    					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow + i3].RESULT		, sBuf.c_str());

		    			sBuf = "";
        	    		if ( VarIsNull(Query7->FieldValues["DISP_VAL"]) != true )
				    	{
                        	sBuf = Query7->FieldValues["DISP_VAL"];
    					}
    					strcpy(pCELLINFO_SOKU_SOZAI[(iCol * SGr_vSOKU_SOZAI->RowCount) + iRow + i3].DISP_RESULT		, sBuf.c_str());
                        Form1->Query7->Next();
                    }
                    i3 = AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0)+1;
					Form1->Query7->Close();
                	break;
                }
                iRow ++;
            }
            iRow = iTempRow + AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) ;
        }
   }
   Query4->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：素材（履歴）データの読み込み。
//
//  機能説明
//    素材（履歴）データを読み込み、CELLINFOに代入します。
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
void __fastcall TForm1::Set_RIRE_SOZAIJISSEKI(void)
{
	int i1,i2,i3,i4;
	int iCol,iRow,iUNQNO;
    int iTempRow;
	AnsiString sLot,sUNQNO;
    AnsiString sBuf,sBuf1;
    double dMAX,dMIN;
    AnsiString sLot_Where;

	sLot = "";
	sBuf = "";
	sBuf1 = "";
    sUNQNO ="";

	if(!hCELLINFO_RIRE_SOZAI) return;			//メモリが確保されていない時は処理を中止
	for(i1 = 0;i1 < SGr_tRIRE->ColCount ; i1++)
	{
		sLot += "'" + SGr_tRIRE->Cells[i1][0] + "'" + ",";
	}

	sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
    for(i1 = 0; i1 < SGr_tRIRE->ColCount ; i1++)
    {
        sLot_Where += "( LOTNO='" + SGr_tRIRE->Cells[i1][0] + "' AND ";
        sLot_Where += " HINBAN='" + SGr_tRIRE->Cells[i1][1] + "') OR ";
    }
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

	i1 = 0;
    //////////////////////////////////////////////////////////////
    //	UNQ_NOでは検索キーとして不適当なのでKOMK_NOに変更します
    //////////////////////////////////////////////////////////////
	while( 1 )
	{
    	if(i1 >= iSOZAI_ContCnt ) break;
		iUNQNO = AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO).ToIntDef(0);
		sUNQNO += " " + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO) + " ,";
		while(iUNQNO == AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO).ToIntDef(0))
		{
			i1++;
			if(i1 >= iSOZAI_ContCnt ) break;
		}
	}
	sUNQNO = sUNQNO.SubString(1,sUNQNO.Length()-1);



    if(sLot.Length() < 3 ) return;		//ロットの入力がない場合

	sBuf  = "SELECT  KSD02.*, SM12S.TANNAM As UPDNAME ";
	sBuf += " FROM KSD02 LEFT JOIN SM12S ON KSD02.UPDCHR = SM12S.TANSYA ";
    sBuf += " WHERE DTKSHIN = '" + sNowDTKSHIN + "'";
    sBuf += " AND SKB_NO = 1";                        //出荷検査項目、材料証明項目
    //sBuf += " AND LOTNO IN ("+ sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";

	if(sUNQNO.Length() > 3 )
	{
		sBuf += " AND KOMK_NO IN ("+ sUNQNO + ")";
	}
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
	Query4->Close();
	Query4->Active = false;
    Query4->SQL->Clear();
    Query4->SQL->Add(sBuf);
    Query4->Open();
    Query4->Active = true;

//履歴データが有る出荷ロットが呼び出されているはず
	while(Query4->Eof != true )
    {
    	i1 = 0;
        sLot = Query4->FieldValues["LOTNO"];

        //ロット毎にメモリの初期化が必要
        memset(pRIREKI_DATA,0x00,sizeof(pRIREKI_DATA));

        while( sLot == Query4->FieldValues["LOTNO"] && Query4->Eof != true)
        {
            strcpy(pRIREKI_DATA[i1].DTKSHIN		,"");
            if ( VarIsNull(Query4->FieldValues["DTKSHIN"]) != true)
            {
	        	sBuf	= Query4->FieldValues["DTKSHIN"];							//得意先項目品番
    	        strcpy(pRIREKI_DATA[i1].DTKSHIN			,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].LOTNO		,"");
			if ( VarIsNull(Query4->FieldValues["LOTNO"]) != true  )
            {
            	sBuf = Query4->FieldValues["LOTNO"];                   				//ロットNO
            	strcpy(pRIREKI_DATA[i1].LOTNO      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].HINBAN		,"");
			if ( VarIsNull(Query4->FieldValues["HINBAN"]) != true  )
            {
            	sBuf = Query4->FieldValues["HINBAN"];                   			//工管発行日 onishi
            	strcpy(pRIREKI_DATA[i1].HINBAN      	,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UNQ_NO		,"");
			if ( VarIsNull(Query4->FieldValues["UNQ_NO"]) != true )
            {
            	sBuf = Query4->FieldValues["UNQ_NO"];                   			//明細NO
            	strcpy(pRIREKI_DATA[i1].UNQ_NO      	,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ORDER_NO		,"");
			if ( VarIsNull(Query4->FieldValues["ORDER_NO"]) != true)
            {
            	sBuf = Query4->FieldValues["ORDER_NO"];                   		  	//表示・印刷順
            	strcpy(pRIREKI_DATA[i1].ORDER_NO      		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SKB_NO		,"");
			if ( VarIsNull(Query4->FieldValues["SKB_NO"]) != true )
            {
            	sBuf = Query4->FieldValues["SKB_NO"];                   		 	//識別NO
            	strcpy(pRIREKI_DATA[i1].SKB_NO      		,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].HINBAN_SK		,"");
            if ( VarIsNull(Query4->FieldValues["HINBAN_SK"]) != true )
            {
            	sBuf	= Query4->FieldValues["HINBAN_SK"];
                strcpy(pRIREKI_DATA[i1].HINBAN_SK	,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KOMK_NO		,"");
            if ( VarIsNull(Query4->FieldValues["KOMK_NO"]) != true )
            {
	            sBuf    = Query4->FieldValues["KOMK_NO"];                           //測定項目NO
    	        strcpy(pRIREKI_DATA[i1].KOMK_NO			,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KOMK_NM,"");                 				//測定項目名称
            if ( VarIsNull(Query4->FieldValues["KOMK_NM"]) != true )
            {
            	sBuf = Query4->FieldValues["KOMK_NM"];
                strcpy(pRIREKI_DATA[i1].KOMK_NM		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_ENG,"");                 				//測定項目名称（英語)
            if ( VarIsNull(Query4->FieldValues["KOMK_ENG"]) != true )
            {
            	sBuf = Query4->FieldValues["KOMK_ENG"];
                strcpy(pRIREKI_DATA[i1].KOMK_ENG		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_SUB,"");                     			//測定項目サブ名称
            if ( VarIsNull(Query4->FieldValues["KOMK_SUB"]) != true )
            {
            	sBuf = Query4->FieldValues["KOMK_SUB"];
                strcpy(pRIREKI_DATA[i1].KOMK_SUB	,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KOMK_SUB_ENG,"");                     	    //測定項目サブ名称(英語)
            if ( VarIsNull(Query4->FieldValues["KOMK_SUB_ENG"]) != true )
            {
            	sBuf = Query4->FieldValues["KOMK_SUB_ENG"];
                strcpy(pRIREKI_DATA[i1].KOMK_SUB_ENG	,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].KIKI_NO,"");                     	    //測定項目サブ名称(英語)
            if ( VarIsNull(Query4->FieldValues["KIKI_NO"]) != true )
            {
	            sBuf    = Query4->FieldValues["KIKI_NO"];                       	//測定機器NO
    	        strcpy(pRIREKI_DATA[i1].KIKI_NO			,sBuf.c_str());
         	}
            strcpy(pRIREKI_DATA[i1].KIKI_NM,"");
            if ( VarIsNull(Query4->FieldValues["KIKI_NM"]) != true )				//測定機器名称
            {
            	sBuf = Query4->FieldValues["KIKI_NM"];
                strcpy(pRIREKI_DATA[i1].KIKI_NM		,sBuf.c_str());
            }

            strcpy(pRIREKI_DATA[i1].TANI       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["TANI"]) != true  )
			{
            	sBuf       = Query4->FieldValues["TANI"];
            	strcpy(pRIREKI_DATA[i1].TANI       ,sBuf.c_str());
			}                                                           		//規格タイプ

            strcpy(pRIREKI_DATA[i1].KIKA_TYPE       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_TYPE"]) != true )
			{
	            sBuf  = Query4->FieldValues["KIKA_TYPE"];
    	        strcpy(pRIREKI_DATA[i1].KIKA_TYPE  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_KIND       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_KIND"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_KIND"];              				//規格種類
            	strcpy(pRIREKI_DATA[i1].KIKA_KIND  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_DECI       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_DECI"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_DECI"];                         	//規格小数点以下桁数
            	strcpy(pRIREKI_DATA[i1].KIKA_DECI  ,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].KIKA_NUM1       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_NUM1"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_NUM1"];                         	//規格値１
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM1  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_NUM2       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_NUM2"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_NUM2"];                      		//規格値２
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM2  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_NUM3       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_NUM3"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_NUM3"];                       	//規格値３
            	strcpy(pRIREKI_DATA[i1].KIKA_NUM3  ,sBuf.c_str());
			}
            strcpy(pRIREKI_DATA[i1].KIKA_STR       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_STR"]) != true  )
			{
            	sBuf   = Query4->FieldValues["KIKA_STR"];                        	//規格値文字
            	strcpy(pRIREKI_DATA[i1].KIKA_STR   ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB1       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_SUB1"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_SUB1"];                       	//規格値サブ１
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB1  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB2       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_SUB2"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_SUB2"];                         	//規格値サブ２
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB2  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_SUB3       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_SUB3"]) != true )
			{
            	sBuf  = Query4->FieldValues["KIKA_SUB3"];                        	//規格値サブ３
            	strcpy(pRIREKI_DATA[i1].KIKA_SUB3  ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_SU       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["SOKU_SU"]) != true   )
			{
            	sBuf    = Query4->FieldValues["SOKU_SU"];                   		//測定指示ｎ数
            	strcpy(pRIREKI_DATA[i1].SOKU_SU    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_FLG       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["SOKU_FLG"]) != true  )
			{
            	sBuf    = Query4->FieldValues["SOKU_FLG"];                   		//測定項目の有無
            	strcpy(pRIREKI_DATA[i1].SOKU_FLG    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].TOKU_FLG       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["TOKU_FLG"]) != true  )
			{
	            sBuf    = Query4->FieldValues["TOKU_FLG"];                   		//特別項目の有無
	            strcpy(pRIREKI_DATA[i1].TOKU_FLG    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].KIKA_PRT       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["KIKA_PRT"]) != true  )
			{
            	sBuf    = Query4->FieldValues["KIKA_PRT"];                   		//上限下限値の印刷
            	strcpy(pRIREKI_DATA[i1].KIKA_PRT    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].VALUE_TYPE       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["VALUE_TYPE"]) != true)
			{
            	sBuf    = Query4->FieldValues["VALUE_TYPE"];                   		//測定値表現
            	strcpy(pRIREKI_DATA[i1].VALUE_TYPE    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].VALUE_DECI       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["VALUE_DECI"]) != true)
			{
            	sBuf    = Query4->FieldValues["VALUE_DECI"];                   		//測定値小数点以下桁数
            	strcpy(pRIREKI_DATA[i1].VALUE_DECI    ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SKTYMD       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["SKTYMD"]) != true )
			{
            	sBuf     = Query4->FieldValues["SKTYMD"];                       	//測定日
            	strcpy(pRIREKI_DATA[i1].SKTYMD     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ADDYMD       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["ADDYMD"]) != true )
			{
            	sBuf     = Query4->FieldValues["ADDYMD"];                      		//登録日
            	strcpy(pRIREKI_DATA[i1].ADDYMD     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].ADDTIM       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["ADDTIM"]) != true )
			{
            	sBuf     = Query4->FieldValues["ADDTIM"];                       	//登録時間
            	strcpy(pRIREKI_DATA[i1].ADDTIM     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDYMD       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["UPDYMD"]) != true )
			{
            	sBuf     = Query4->FieldValues["UPDYMD"];                         	//変更日
            	strcpy(pRIREKI_DATA[i1].UPDYMD     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDTIM       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["UPDTIM"]) != true )
			{
            	sBuf     = Query4->FieldValues["UPDTIM"];                          	//変更時間
            	strcpy(pRIREKI_DATA[i1].UPDTIM     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDCHR       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["UPDCHR"]) != true )
			{
            	sBuf     = Query4->FieldValues["UPDCHR"];                      		//更新者
            	strcpy(pRIREKI_DATA[i1].UPDCHR     ,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].UPDCNT       ,"");                    		//単位
            if ( VarIsNull(Query4->FieldValues["UPDCNT"]) != true )
			{
            	sBuf     = Query4->FieldValues["UPDCNT"];                         	//更新回数
            	strcpy(pRIREKI_DATA[i1].UPDCNT     ,sBuf.c_str());
			}

    		strcpy(pRIREKI_DATA[i1].UPDNAME , "");
            if ( VarIsNull(Query4->FieldValues["UPDNAME"]) != true )
			{
            	sBuf     = Query4->FieldValues["UPDNAME"];                         	//更新者
            	strcpy(pRIREKI_DATA[i1].UPDNAME , sBuf.c_str());
			}

//SOKU Result Read ///////////////////////////////////////////////////////////////////////
			strcpy(pRIREKI_DATA[i1].SOKU_VAL01,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL01"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL01"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL01		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL02,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL02"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL02"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL02		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL03,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL03"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL03"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL03		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL04,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL04"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL04"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL04		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL05,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL05"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL05"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL05		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL06,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL06"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL06"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL06		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL07,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL07"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL07"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL07		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL08,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL08"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL08"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL08		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL09,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL09"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL09"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL09		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL10,"");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL10"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL10"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL10		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_SU,"1");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL_SU"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL_SU"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_SU		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_AVE,"0.0");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL_AVE"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL_AVE"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_AVE		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_MAX,"0.0");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL_MAX"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL_MAX"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_MAX		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_VAL_MIN,"0.0");
            if(VarIsNull(Query4->FieldValues["SOKU_VAL_MIN"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_VAL_MIN"];
                strcpy(pRIREKI_DATA[i1].SOKU_VAL_MIN		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].SOKU_OK,"0");
            if(VarIsNull(Query4->FieldValues["SOKU_OK"])!=true)
            {
            	sBuf = Query4->FieldValues["SOKU_OK"];
                strcpy(pRIREKI_DATA[i1].SOKU_OK		,sBuf.c_str());
            }
//DISP Result Read ///////////////////////////////////////////////////////////////////////
			strcpy(pRIREKI_DATA[i1].DISP_VAL01,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL01"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL01"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL01		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL02,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL02"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL02"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL02		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL03,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL03"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL03"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL03		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL04,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL04"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL04"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL04		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL05,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL05"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL05"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL05		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL06,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL06"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL06"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL06		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL07,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL07"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL07"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL07		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL08,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL08"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL08"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL08		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL09,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL09"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL09"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL09		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL10,"");
            if(VarIsNull(Query4->FieldValues["DISP_VAL10"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL10"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL10		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_SU,"1");
            if(VarIsNull(Query4->FieldValues["DISP_VAL_SU"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL_SU"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_SU		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_AVE,"0.0");
            if(VarIsNull(Query4->FieldValues["DISP_VAL_AVE"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL_AVE"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_AVE		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_MAX,"0.0");
            if(VarIsNull(Query4->FieldValues["DISP_VAL_MAX"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL_MAX"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_MAX		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_VAL_MIN,"0.0");
            if(VarIsNull(Query4->FieldValues["DISP_VAL_MIN"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_VAL_MIN"];
                strcpy(pRIREKI_DATA[i1].DISP_VAL_MIN		,sBuf.c_str());
            }
            strcpy(pRIREKI_DATA[i1].DISP_OK,"0");
            if(VarIsNull(Query4->FieldValues["DISP_OK"])!=true)
            {
            	sBuf = Query4->FieldValues["DISP_OK"];
                strcpy(pRIREKI_DATA[i1].DISP_OK		,sBuf.c_str());
            }


            i1 ++;
            Query4->Next();
		}
//存在するロットの測定実績データの読み込み完了
//カラムの位置検索
		iCol = 0;

        while(iCol <= SGr_tRIRE->ColCount)
        {
        	if( SGr_tRIRE->Cells[iCol][0] == sLot) break;
			iCol++;
        }

//出荷検査のグリッドをすべて灰色にする
		for(i2= 1; i2 <  SGr_vRIRE_SOZAI->RowCount ; i2++)
        {
        }
//測定機器NO、測定項目NOの一致している場所を探索
		i4 = i1;
        iRow = 1;
        for( i1 = 0; i1 < i4;i1++)
        {
        	i2 = 0;
			iRow = 1;
            while( 1 )
            {
				sBuf = AnsiString(pSOZAI_OR_DATA[i2].KOMK_NM).Trim() + AnsiString(pSOZAI_OR_DATA[i2].KOMK_SUB).Trim();
				sBuf1 =AnsiString(pRIREKI_DATA[i1].KOMK_NM).Trim() + AnsiString(pRIREKI_DATA[i1].KOMK_SUB).Trim();
            	if((AnsiString(pSOZAI_OR_DATA[i2].KIKI_NO).ToIntDef(0) == AnsiString(pRIREKI_DATA[i1].KIKI_NO).ToIntDef(0))
                && (sBuf == sBuf1)
				&& (AnsiString(pSOZAI_OR_DATA[i2].HINBAN_SK) == AnsiString(pRIREKI_DATA[i1].HINBAN_SK))
				&& (AnsiString(pSOZAI_OR_DATA[i2].KOMK_NO).ToIntDef(0) == AnsiString(pRIREKI_DATA[i1].KOMK_NO).ToIntDef(0))
                ) break;
                iRow += AnsiString(pSOZAI_OR_DATA[i2].SOKU_SU).ToIntDef(0);
                i2++;
            	if( i2 >= iSOZAI_ORCNT ) break;		//無限ループから抜けます
            }
            if( i2 >= iSOZAI_ORCNT ) break;		//不正ロットから抜けます

//履歴データのデータ読み取り（10件まで　11件以上を考えること）
            iTempRow = iRow;
            GetLotKIKAKU(i1, &dMAX, &dMIN);
            for(i3 = 0; i3 <  AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) ; i3++ )
            {
            	strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DTKSHIN 		, pRIREKI_DATA[i1].DTKSHIN);
                strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].LOTNO 		, pRIREKI_DATA[i1].LOTNO);
                strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].HINBAN 		, pRIREKI_DATA[i1].HINBAN);
			   	strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].UNQ_NO 		, pRIREKI_DATA[i1].UNQ_NO);
			  	strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].ORDER_NO		, pRIREKI_DATA[i1].ORDER_NO);
			 	strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].SKB_NO 		, pRIREKI_DATA[i1].SKB_NO);
				strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].HINBAN_SK	, pRIREKI_DATA[i1].HINBAN_SK);
		   		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KOMK_NO 		, pRIREKI_DATA[i1].KOMK_NO);
		   		pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].INS_ON = true;
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KOMK_NM 		, pRIREKI_DATA[i1].KOMK_NM);
		 		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KOMK_ENG		, pRIREKI_DATA[i1].KOMK_ENG);
				strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KOMK_SUB		, pRIREKI_DATA[i1].KOMK_SUB);
	   			strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KOMK_SUB_ENG , pRIREKI_DATA[i1].KOMK_SUB_ENG);
	  			strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKI_NO 		, pRIREKI_DATA[i1].KIKI_NO);
	 			strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKI_NM 		, pRIREKI_DATA[i1].KIKI_NM);
				strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].TANI    		, pRIREKI_DATA[i1].TANI);
			  	strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKA_TYPE	, pRIREKI_DATA[i1].KIKA_TYPE);
			 	strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKA_KIND	, pRIREKI_DATA[i1].KIKA_KIND);
				strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKA_DECI	, pRIREKI_DATA[i1].KIKA_DECI);
		   		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKA_NUM1	, pRIREKI_DATA[i1].KIKA_NUM1);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKA_NUM2	, pRIREKI_DATA[i1].KIKA_NUM2);
		 		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKA_NUM3	, pRIREKI_DATA[i1].KIKA_NUM3);
				strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKA_STR		, pRIREKI_DATA[i1].KIKA_STR);
	   			strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKA_SUB1	, pRIREKI_DATA[i1].KIKA_SUB1);
	  			strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKA_SUB2	, pRIREKI_DATA[i1].KIKA_SUB2);
	 			strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKA_SUB3	, pRIREKI_DATA[i1].KIKA_SUB3);
				strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].SOKU_SU 		, pRIREKI_DATA[i1].SOKU_SU);
   				strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].SOKU_FLG		, pRIREKI_DATA[i1].SOKU_FLG);
  				strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].TOKU_FLG		, pRIREKI_DATA[i1].TOKU_FLG);
				strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].KIKA_PRT		, pRIREKI_DATA[i1].KIKA_PRT);
		   		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].VALUE_TYPE	, pRIREKI_DATA[i1].VALUE_TYPE);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].VALUE_DECI	, pRIREKI_DATA[i1].VALUE_DECI);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].SOKU_VAL_SU	, pRIREKI_DATA[i1].SOKU_VAL_SU);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].SOKU_VAL_AVE	, pRIREKI_DATA[i1].SOKU_VAL_AVE);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].SOKU_VAL_MAX	, pRIREKI_DATA[i1].SOKU_VAL_MAX);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].SOKU_VAL_MIN	, pRIREKI_DATA[i1].SOKU_VAL_MIN);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].SOKU_OK		, pRIREKI_DATA[i1].SOKU_OK);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_VAL_SU	, pRIREKI_DATA[i1].DISP_VAL_SU);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_VAL_AVE	, pRIREKI_DATA[i1].DISP_VAL_AVE);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_VAL_MAX	, pRIREKI_DATA[i1].DISP_VAL_MAX);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_VAL_MIN	, pRIREKI_DATA[i1].DISP_VAL_MIN);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_OK		, pRIREKI_DATA[i1].DISP_OK);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].SKTYMD		, pRIREKI_DATA[i1].SKTYMD);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].ADDYMD		, pRIREKI_DATA[i1].ADDYMD);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].ADDTIM		, pRIREKI_DATA[i1].ADDTIM);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].UPDYMD		, pRIREKI_DATA[i1].UPDYMD);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].UPDTIM		, pRIREKI_DATA[i1].UPDTIM);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].UPDCHR		, pRIREKI_DATA[i1].UPDCHR);
		  		strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].UPDCNT		, pRIREKI_DATA[i1].UPDCNT);
                strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].UPDNAME 		, pRIREKI_DATA[i1].UPDNAME);
				//規格
                pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].MAX = dMAX ;
                pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].MIN = dMIN ;
                iRow++;
            }
            iRow = iTempRow;
            for(i3 = 0; i3 <  AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) ; i3++ )
            {
            	switch( i3 )
                {
                case 0:
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL01);
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL01);
                    break;
                case 1:
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL02);
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL02);
                    break;
                case 2:
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL03);
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL03);
                    break;
                case 3:
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL04);
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL04);
                    break;
                case 4:
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL05);
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL05);
                    break;
                case 5:
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL06);
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL06);
                    break;
                case 6:
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL07);
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL07);
                    break;
                case 7:
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL08);
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL08);
                    break;
                case 8:
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL09);
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL09);
                    break;
                case 9:
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].RESULT		, pRIREKI_DATA[i1].SOKU_VAL10);
					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DISP_RESULT	, pRIREKI_DATA[i1].DISP_VAL10);
                    break;
                default:
    				sBuf  = "SELECT * FROM KSD03";
    				sBuf += " WHERE DTKSHIN = '" + AnsiString(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].DTKSHIN) 	+ "'";
    				sBuf += " AND   LOTNO = '"	 + AnsiString(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].LOTNO) 	+ "'";
    				sBuf += " AND   HINBAN = '"	 + AnsiString(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].HINBAN) 	+ "'";
    				sBuf += " AND   UNQ_NO = "	 + AnsiString(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow].UNQ_NO) 	+ " ";
                    sBuf += " ORDER BY SOKU_NO ASC";
					//For Debug
                    if( iDEBUG == 1 )
                    {
                        ClpBrd = Clipboard();
                        ClpBrd->Open();
     				    ClpBrd->SetTextBuf(sBuf.c_str());
     				    ClpBrd->Close();
                    }
					// Initial Query
					Form1->Query7->Close();
    				Form1->Query7->SQL->Clear();
    				Form1->Query7->SQL->Add(sBuf);
    				Form1->Query7->Open();
                    Form1->Query7->Active = true;
                    while( Query7->Eof != true)
                    {
					    sBuf = "";
        			    if ( VarIsNull(Query7->FieldValues["SOKU_NO"]) != true )
					    {
                    	    sBuf = Query7->FieldValues["SOKU_NO"];
					    }
                        if(AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0) < sBuf.ToIntDef(0)) break;
                        i3 = sBuf.ToIntDef(11) - 11;
    					sBuf = "";
            			if ( VarIsNull(Query7->FieldValues["SOKU_VAL"]) != true )
		    			{
                        	sBuf = Query7->FieldValues["SOKU_VAL"];
				    	}
                        //SGr_vRIRE_SOZAI->Cells[iCol][iRow] = sBuf;
    					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow + i3].RESULT		, sBuf.c_str());

		    			sBuf = "";
        	    		if ( VarIsNull(Query7->FieldValues["DISP_VAL"]) != true )
				    	{
                        	sBuf = Query7->FieldValues["DISP_VAL"];
    					}
    					strcpy(pCELLINFO_RIRE_SOZAI[(iCol * SGr_vRIRE_SOZAI->RowCount) + iRow + i3].DISP_RESULT		, sBuf.c_str());
                        Form1->Query7->Next();
                    }
                    i3 = AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0)+1;
					Form1->Query7->Close();
                	break;
                }
                iRow ++;
            }
            iRow = iTempRow + AnsiString(pRIREKI_DATA[i1].SOKU_SU).ToIntDef(0);
        }
   }
   Query4->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：履歴の備考欄作成。
//
//  機能説明
//    履歴備考欄の動的コントロールを作成します。
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
void __fastcall TForm1::Set_RIREMEMO(void)
{
	int i1;
	AnsiString sBuf;

    // 2003/05/13 A.Tamura
	iRIRE_MEMO_CNT = 0;
	SGr_vRIRE_SOZAI->LeftCol = 0;
	SGr_vRIRE_SYUKA->LeftCol = 0;
    SBx_vRIRE_MEMO->HorzScrollBar->Position = 0;
	if(SGr_tRIRE->Cells[0][0]!="")
	{
        Mem_vRIRE_MEMOORG->Visible = false;
    	Mem_vRIRE_MEMO  = new TMemo *[SGr_tRIRE->ColCount];
		for(i1 = 0 ; i1 < SGr_tRIRE->ColCount ;i1++)
		{
			sBuf = i1;
            Mem_vRIRE_MEMO[i1] = new TMemo(SBx_vRIRE_MEMO);
            Mem_vRIRE_MEMO[i1]->Name 		= "Mem_vRIRE_MEMO" + AnsiString::StringOfChar('0000', 5-sBuf.Length()) + sBuf;
            Mem_vRIRE_MEMO[i1]->Parent 		= SBx_vRIRE_MEMO;
            Mem_vRIRE_MEMO[i1]->Width 		= Mem_vRIRE_MEMOORG->Width;
           	Mem_vRIRE_MEMO[i1]->Left		= (Mem_vRIRE_MEMOORG->Width + 1) * i1;
            Mem_vRIRE_MEMO[i1]->Height 		= Mem_vRIRE_MEMOORG->Height;
            Mem_vRIRE_MEMO[i1]->Text 		= "";
        	Mem_vRIRE_MEMO[i1]->BorderStyle	= bsNone;
            Mem_vRIRE_MEMO[i1]->OnEnter		= FormEnter;
            Mem_vRIRE_MEMO[i1]->OnKeyDown	= AllKeyDown;
            Mem_vRIRE_MEMO[i1]->OnKeyUp		= AllKeyUp;
			Mem_vRIRE_MEMO[i1]->OnKeyPress	= Mem_MEMOKeyPress;
			Mem_vRIRE_MEMO[i1]->OnEnter	= Mem_MEMOEnter;
			Mem_vRIRE_MEMO[i1]->OnExit	= Mem_MEMOExit;
    	}
        if( SGr_tRIRE->ColCount > 0 ){
			Pnl_DUMMY4->Parent		= SBx_vRIRE_MEMO;
			Pnl_DUMMY4->Top			= 0;
	    	Pnl_DUMMY4->Height		= Mem_vRIRE_MEMOORG->Height;
        	Pnl_DUMMY4->Width		= Mem_vRIRE_MEMOORG->Width + 15;
			Pnl_DUMMY4->Left		= (Mem_vRIRE_MEMOORG->Width + 1) * i1;
	    	Pnl_DUMMY4->Ctl3D		= false;
    		Pnl_DUMMY4->BevelInner	= bvNone;
	    	Pnl_DUMMY4->BevelOuter	= bvNone;
    		Pnl_DUMMY4->BorderStyle	= bsNone;
	    	Pnl_DUMMY4->BorderWidth	= 0;
			Pnl_DUMMY4->Visible		= true;
		}
		iRIRE_MEMO_CNT = i1;
	}
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：測定備考欄のデータ読み取り表示。
//
//  機能説明
//    測定備考欄のデータ読み取り表示。
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
void __fastcall TForm1::Get_KSD91_SHUKA(void)
{
	int i1,i2,i3;
	AnsiString sBuf,sLot,sBuf1;
    AnsiString sLot_Where;

    //出荷検査にあるロットを抽出してNOTの条件にする
    sLot = "";
	sBuf = "";
	for(i1 = 0;i1 < SGr_tSOKU->ColCount ; i1++)
	{
		sLot += "'" + SGr_tSOKU->Cells[i1][0] + "'" + ",";
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

	if( sLot.Length() < 4 ) return;		//ロットの入力がない

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
    for(i1 = 0;i1 < SGr_tSOKU->ColCount ; i1++)
    {
        sLot_Where += "( LOTNO='" + SGr_tSOKU->Cells[i1][0] + "' AND ";
        sLot_Where += " HINBAN='" + SGr_tSOKU->Cells[i1][1] + "') OR ";
    }
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

    //得意先品番をキーにして必要ロットの取得をする）
    sBuf = "SELECT DTKSHIN, LOTNO, MEMO FROM KSD91";
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
    //sBuf += " AND LOTNO IN ("+ sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";

    //For Debug
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
    Query1->Open();
    Query1->Active = true;

	while( Query1->Eof != true )
	{
        i1 = 0;
		while( 1 )
		{
        	if(SGr_tSOKU->Cells[i1][0] == Query1->FieldValues["LOTNO"]) break;
			i1 ++;
		}
        Mem_vSOKU_MEMO[i1]->Clear();
		sBuf = Query1->FieldValues["MEMO"];
        sBuf1 = "";
		i3 = 1;
		for(i2 = 1;i2 < sBuf.Length() ; i2++)
		{
			if((sBuf.SubString(i3,1) == '\n' && sBuf.SubString(i3+1,1) == '\n')		//化けている改行コード
            || (sBuf.SubString(i3,1) == '\r' && sBuf.SubString(i3+1,1) == '\n'))
			{
				Mem_vSOKU_MEMO[i1]->Lines->Add(sBuf.SubString(1,i3-1));
                sBuf = sBuf.SubString(i3+2,sBuf.Length()-i3);
				i3 = 1;
    		}
			else
			{
                sBuf1 += sBuf.SubString(i3,1);
				i3++;
			}
		}
		if(sBuf.Trim().Length() != 0)
		{
        	Mem_vSOKU_MEMO[i1]->Lines->Add(sBuf);
		}
    	Query1->Next();

        // 2004/06/16 A.Tamura 備考欄の文字の一番上を表示
        Mem_vSOKU_MEMO[i1]->SelStart  = 0;
        Mem_vSOKU_MEMO[i1]->SelLength = 0;
	}
	Query1->Close();

    //得意先品番とロットをキーにして測定実績データからメモを探す
    sBuf = "SELECT DTKSHIN, LOTNO, MEMO FROM KSD01";
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
    //sBuf += " AND LOTNO IN ("+ sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";


    //For Debug
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
    Query1->Open();
    Query1->Active = true;

	int iStrLen;
	while( Query1->Eof != true )
	{
        i1 = 0;
		while( 1 )
		{
        	if(SGr_tSOKU->Cells[i1][0] == Query1->FieldValues["LOTNO"]) break;
			i1 ++;
		}
        sBuf  = Query1->FieldValues["MEMO"];
        Mem_vSOKU_MEMO[i1]->Clear();
		i3 = 1;
		iStrLen = sBuf.Length();
		iStrLen *= 2;
		for(i2 = 1;i2 < iStrLen ; i2++)
		{
			if((sBuf.SubString(i3,1) == '\n' && sBuf.SubString(i3+1,1) == '\n')		//化けている改行コード
            || (sBuf.SubString(i3,1) == '\r' && sBuf.SubString(i3+1,1) == '\n'))		//化けている改行コード
			{
				Mem_vSOKU_MEMO[i1]->Lines->Add(sBuf.SubString(1,i3-1));
                sBuf = sBuf.SubString(i3+2,sBuf.Length()-i3);
				i3 = 1;
    		}
			else
			{
				i3++;
			}
		}
		if(sBuf.Trim().Length() != 0)
		{
			Mem_vSOKU_MEMO[i1]->Lines->Add(sBuf);
		}
    	Query1->Next();

        // 2004/06/16 A.Tamura 備考欄の文字の一番上を表示
        Mem_vSOKU_MEMO[i1]->SelStart  = 0;
        Mem_vSOKU_MEMO[i1]->SelLength = 0;
	}
	Query1->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：履歴備考欄のデータ読み取り表示。
//
//  機能説明
//    履歴備考欄のデータ読み取り表示。
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
void __fastcall TForm1::Get_KSD91_RIREKI(void)
{
	int i1,i2,i3;
	AnsiString sBuf,sLot;
    AnsiString sLot_Where;

    //出荷検査にあるロットを抽出してNOTの条件にする
    sLot = "";
	for(i1 = 0;i1 < SGr_tRIRE->ColCount ; i1++)
	{
		sLot += "'" + SGr_tRIRE->Cells[i1][0] + "'" + ",";
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

	if( sLot.Length() < 4 ) return;		//ロットの入力がない

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
    for(i1 = 0; i1 < SGr_tRIRE->ColCount ; i1++)
    {
        sLot_Where += "( LOTNO='" + SGr_tRIRE->Cells[i1][0] + "' AND ";
        sLot_Where += " HINBAN='" + SGr_tRIRE->Cells[i1][1] + "') OR ";
    }
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

    //得意先品番をキーにして必要ロットの取得をする）
    sBuf = "SELECT DTKSHIN, LOTNO, MEMO FROM KSD91";
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
    //sBuf += " AND LOTNO IN ("+ sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";

    //For Debug
    if( iDEBUG == 1 )
    {
    	ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }

    // Initial Query
    Query2->Close();
    Query2->SQL->Clear();
    Query2->SQL->Add(sBuf);
    Query2->Open();
    Query2->Active = true;

	while( Query2->Eof != true )
	{
        i1 = 0;
		while( 1 )
		{
        	if(SGr_tRIRE->Cells[i1][0] == Query2->FieldValues["LOTNO"]) break;
			i1 ++;
		}
		sBuf = Query2->FieldValues["MEMO"];
		i3 = 1;
		for(i2 = 1;i2 < sBuf.Length() ; i2++)
		{
			if((sBuf.SubString(i3,1) == '\n' && sBuf.SubString(i3+1,1) == '\n')		//化けている改行コード
            || (sBuf.SubString(i3,1) == '\r' && sBuf.SubString(i3+1,1) == '\n'))	//化けている改行コード
			{
				Mem_vRIRE_MEMO[i1]->Lines->Add(sBuf.SubString(1,i3-1));
                sBuf = sBuf.SubString(i3+2,sBuf.Length()-i3);
				i3 = 1;
    		}
			else
			{
				i3++;
			}
		}
		if(sBuf.Trim().Length() != 0)
		{
	    	Mem_vRIRE_MEMO[i1]->Lines->Add(sBuf);
		}
    	Query2->Next();

        // 2004/06/16 A.Tamura 備考欄の文字の一番上を表示
        Mem_vRIRE_MEMO[i1]->SelStart  = 0;
        Mem_vRIRE_MEMO[i1]->SelLength = 0;
	}
	Query2->Close();


    //得意先品番とロットをキーにして測定実績データからメモを探す
    sBuf = "SELECT DTKSHIN, LOTNO, MEMO FROM KSD01";
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
    //sBuf += " AND LOTNO IN ("+ sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";

    //For Debug
    if( iDEBUG == 1 )
    {
    	ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }

    // Initial Query
    Query2->Close();
    Query2->SQL->Clear();
    Query2->SQL->Add(sBuf);
    Query2->Open();
    Query2->Active = true;

	int iStrLen;
	while( Query2->Eof != true )
	{
        i1 = 0;
		while( 1 )
		{
        	if(SGr_tRIRE->Cells[i1][0] == Query2->FieldValues["LOTNO"]) break;
			i1 ++;
		}
        Mem_vRIRE_MEMO[i1]->Clear();
        sBuf  = Query2->FieldValues["MEMO"];
		i3 = 1;
		iStrLen = sBuf.Length();
		iStrLen *= 2;
		for(i2 = 1;i2 < iStrLen ; i2++)
		{
			if((sBuf.SubString(i3,1) == '\n' && sBuf.SubString(i3+1,1) == '\n')		//化けている改行コード
			|| (sBuf.SubString(i3,1) == '\r' && sBuf.SubString(i3+1,1) == '\n'))	//化けている改行コード
			{
				Mem_vRIRE_MEMO[i1]->Lines->Add(sBuf.SubString(1,i3-1));
                sBuf = sBuf.SubString(i3+2,sBuf.Length()-i3);
				i3 = 1;
    		}
			else
			{
				i3++;
			}
		}
		if(sBuf.Trim().Length() != 0)
		{
	    	Mem_vRIRE_MEMO[i1]->Lines->Add(sBuf);
		}
    	Query2->Next();

        // 2004/06/16 A.Tamura 備考欄の文字の一番上を表示
        Mem_vRIRE_MEMO[i1]->SelStart  = 0;
        Mem_vRIRE_MEMO[i1]->SelLength = 0;
	}
	Query2->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：項目のMAX、MIN値を算出する。
//
//  機能説明
//   作成済みのORデータからMAX、MINを算出する。
//
//  パラメタ説明
//    int iIndex        ：ORデータ中の項目NO
//    double *dMAX      ：規格のMAX
//    double *dMIN      ：規格のMIN
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GetKIKAKU(int iIndex,double *dMAX,double *dMIN)
{
	double dSWAP;
    bool bRtn;				//2003.05.08 E.Takase Add
    AnsiString sBufConv;	//2003.05.08 E.Takase Add

	if(iDEBUG == 1)
	{
    	*dMAX=0.0;
        *dMIN=0.0;
        return;
	}
    if( AnsiString(pORDATA[iIndex].KIKA_TYPE).ToIntDef(0) != 3 )
    {
        bRtn = Form1->ConvDoubleDefS(AnsiString(pORDATA[iIndex].KIKA_NUM1),
           								"0.00",
                                        AnsiString(pORDATA[iIndex].KIKA_NUM1),
                                        &sBufConv);
        if ( bRtn ) {
        	*dMAX = Form1->ConvDoubleDefD(AnsiString(pORDATA[iIndex].KIKA_NUM1),0.0);
        	*dMIN = Form1->ConvDoubleDefD(AnsiString(pORDATA[iIndex].KIKA_NUM1),0.0);
        } else {
			*dMAX=0.0;
			*dMIN=0.0;
        	return;
        }
		switch(AnsiString(pORDATA[iIndex].KIKA_TYPE).ToIntDef(0))
        {
        case 1:
        	switch(AnsiString(pORDATA[iIndex].KIKA_KIND).ToIntDef(0))
            {
            case 1:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pORDATA[iIndex].KIKA_NUM2),
           										"0.00",
                                        		AnsiString(pORDATA[iIndex].KIKA_NUM2),
                                        		&sBufConv);
        		if ( bRtn ) {
        			bRtn = Form1->ConvDoubleDefS(AnsiString(pORDATA[iIndex].KIKA_NUM1),
           											"0.00",
                                        			AnsiString(pORDATA[iIndex].KIKA_NUM1),
                                        			&sBufConv);
                	if ( bRtn ) {
            			*dMAX = Form1->ConvDoubleDefD(AnsiString(pORDATA[iIndex].KIKA_NUM2),0.0);
                		*dMIN = Form1->ConvDoubleDefD(AnsiString(pORDATA[iIndex].KIKA_NUM1),0.0);
                    } else {
						*dMAX=0.0;
						*dMIN=0.0;
                    	return;
                    }
                } else {
					*dMAX=0.0;
					*dMIN=0.0;
                 	return;
                }
                break;
            case 2:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pORDATA[iIndex].KIKA_NUM2),
           										"0.00",
                                        		AnsiString(pORDATA[iIndex].KIKA_NUM2),
                                        		&sBufConv);
        		if ( bRtn ) {
                	*dMAX = Form1->ConvDoubleDefD(AnsiString(pORDATA[iIndex].KIKA_NUM2),0.0);
                	*dMIN = 0.0;
                } else {
					*dMAX=0.0;
					*dMIN=0.0;
                 	return;
                }
                break;
            case 3:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pORDATA[iIndex].KIKA_NUM1),
           										"0.00",
                                        		AnsiString(pORDATA[iIndex].KIKA_NUM1),
                                        		&sBufConv);
        		if ( bRtn ) {
                	*dMAX = Form1->ConvDoubleDefD(AnsiString(pORDATA[iIndex].KIKA_NUM1),0.0);
                	*dMIN = Form1->ConvDoubleDefD(AnsiString(pORDATA[iIndex].KIKA_NUM1),0.0)*1.1;
                } else {
					*dMAX=0.0;
					*dMIN=0.0;
                 	return;
                }
                break;
            default:
            	break;
            }
            break;
        case 2:
        	switch(AnsiString(pORDATA[iIndex].KIKA_KIND).ToIntDef(0))
            {
            case 1:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pORDATA[iIndex].KIKA_NUM2),
           										"0.00",
                                        		AnsiString(pORDATA[iIndex].KIKA_NUM2),
                                        		&sBufConv);
        		if ( bRtn ) {
        			bRtn = Form1->ConvDoubleDefS(AnsiString(pORDATA[iIndex].KIKA_NUM3),
           											"0.00",
                                        			AnsiString(pORDATA[iIndex].KIKA_NUM3),
                                        			&sBufConv);
                    if ( bRtn ) {
                		*dMAX += Form1->ConvDoubleDefD(AnsiString(pORDATA[iIndex].KIKA_NUM2),0.0);
                		*dMIN += Form1->ConvDoubleDefD(AnsiString(pORDATA[iIndex].KIKA_NUM3),0.0);
                	} else {
						*dMAX=0.0;
						*dMIN=0.0;
                 		return;
                	}
                } else {
					*dMAX=0.0;
					*dMIN=0.0;
                 	return;
                }
                break;
            case 2:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pORDATA[iIndex].KIKA_NUM2),
           										"0.00",
                                        		AnsiString(pORDATA[iIndex].KIKA_NUM2),
                                        		&sBufConv);
        		if ( bRtn ) {
                		*dMAX += Form1->ConvDoubleDefD(AnsiString(pORDATA[iIndex].KIKA_NUM2),0.0);
                } else {
                    *dMAX=0.0;
                    *dMIN=0.0;
                 	return;
                }
                break;
            case 3:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pORDATA[iIndex].KIKA_NUM3),
           										"0.00",
                                        		AnsiString(pORDATA[iIndex].KIKA_NUM3),
                                        		&sBufConv);
        		if ( bRtn ) {
                		*dMIN += Form1->ConvDoubleDefD(AnsiString(pORDATA[iIndex].KIKA_NUM3),0.0);
                } else {
                    *dMAX=0.0;
                    *dMIN=0.0;
                 	return;
                }
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
//  概要
//    自作関数			：ロット毎のMAX、MIN値を算出する。
//
//  機能説明
//   作成済みのORデータからMAX、MINを算出する。
//
//  パラメタ説明
//    int iIndex        ：ORデータ中の項目NO
//    double *dMAX      ：規格のMAX
//    double *dMIN      ：規格のMIN
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GetLotKIKAKU(int iIndex,double *dMAX,double *dMIN)
{
	double dSWAP;
    bool bRtn;				//2003.05.08 E.Takase Add
    AnsiString sBufConv;	//2003.05.08 E.Takase Add

	if(iDEBUG == 1)
	{
    	*dMAX=0.0;
        *dMIN=0.0;
        return;
	}
    if( AnsiString(pRIREKI_DATA[iIndex].KIKA_TYPE).ToIntDef(0) != 3 )
    {
        bRtn = Form1->ConvDoubleDefS(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM1),
           								"0.00",
                                        AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM1),
                                        &sBufConv);
        if ( bRtn ) {
        	*dMAX = Form1->ConvDoubleDefD(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM1),0.0);
        	*dMIN = Form1->ConvDoubleDefD(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM1),0.0);
        } else {
			*dMAX=0.0;
			*dMIN=0.0;
        	return;
        }
		switch(AnsiString(pRIREKI_DATA[iIndex].KIKA_TYPE).ToIntDef(0))
        {
        case 1:
        	switch(AnsiString(pRIREKI_DATA[iIndex].KIKA_KIND).ToIntDef(0))
            {
            case 1:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),
           										"0.00",
                                        		AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),
                                        		&sBufConv);
        		if ( bRtn ) {
        			bRtn = Form1->ConvDoubleDefS(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM1),
           											"0.00",
                                        			AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM1),
                                        			&sBufConv);
                	if ( bRtn ) {
            			*dMAX = Form1->ConvDoubleDefD(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),0.0);
                		*dMIN = Form1->ConvDoubleDefD(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM1),0.0);
                    } else {
						*dMAX=0.0;
						*dMIN=0.0;
                    	return;
                    }
                } else {
					*dMAX=0.0;
					*dMIN=0.0;
                 	return;
                }
                break;
            case 2:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),
           										"0.00",
                                        		AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),
                                        		&sBufConv);
        		if ( bRtn ) {
                	*dMAX = Form1->ConvDoubleDefD(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),0.0);
                	*dMIN = 0.0;
                } else {
					*dMAX=0.0;
					*dMIN=0.0;
                 	return;
                }
                break;
            case 3:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM1),
           										"0.00",
                                        		AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM1),
                                        		&sBufConv);
        		if ( bRtn ) {
                	*dMAX = Form1->ConvDoubleDefD(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM1),0.0);
                	*dMIN = Form1->ConvDoubleDefD(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM1),0.0)*1.1;
                } else {
					*dMAX=0.0;
					*dMIN=0.0;
                 	return;
                }
                break;
            default:
            	break;
            }
            break;
        case 2:
        	switch(AnsiString(pRIREKI_DATA[iIndex].KIKA_KIND).ToIntDef(0))
            {
            case 1:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),
           										"0.00",
                                        		AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),
                                        		&sBufConv);
        		if ( bRtn ) {
        			bRtn = Form1->ConvDoubleDefS(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM3),
           											"0.00",
                                        			AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM3),
                                        			&sBufConv);
                    if ( bRtn ) {
                		*dMAX += Form1->ConvDoubleDefD(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),0.0);
                		*dMIN += Form1->ConvDoubleDefD(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM3),0.0);
                	} else {
						*dMAX=0.0;
						*dMIN=0.0;
                 		return;
                	}
                } else {
					*dMAX=0.0;
					*dMIN=0.0;
                 	return;
                }
                break;
            case 2:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),
           										"0.00",
                                        		AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),
                                        		&sBufConv);
        		if ( bRtn ) {
                		*dMAX += Form1->ConvDoubleDefD(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM2),0.0);
                } else {
                    *dMAX=0.0;
                    *dMIN=0.0;
                 	return;
                }
                break;
            case 3:
        		bRtn = Form1->ConvDoubleDefS(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM3),
           										"0.00",
                                        		AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM3),
                                        		&sBufConv);
        		if ( bRtn ) {
                		*dMIN += Form1->ConvDoubleDefD(AnsiString(pRIREKI_DATA[iIndex].KIKA_NUM3),0.0);
                } else {
                    *dMAX=0.0;
                    *dMIN=0.0;
                 	return;
                }
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
//  概要
//    自作関数			：マスターに含まれる空白行（SKB_NO=9）データを読み取る。
//
//  機能説明
//   空白行のデータを読みバッファへ代入する。（新規保存時使用する）
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
void __fastcall TForm1::GET_SPACE(void)
{
	//int i1;
	AnsiString sBuf;
	iSPACE_COUNT = 0;

    memset(pSPACE_DATA,0x00,sizeof(pSPACE_DATA));

    //まず処理が簡単な？スペースを読み込みます
	sBuf = "SELECT * FROM KSM02";
    sBuf += " WHERE DTKSHIN ='" + sNowDTKSHIN + "'";
    sBuf += " AND REVCNT = 0" ;
    sBuf += " AND SKB_NO IN ( 9 )";                        //スペース

		//For Debug
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
    	Query1->Open();
    	Query1->Active = true;

    while( Query1->Eof == false )
    {
       	strcpy(pSPACE_DATA[iSPACE_COUNT].DTKSHIN		,"");
        if ( VarIsNull(Query1->FieldValues["DTKSHIN"]) != true )
        {
	       	sBuf = Query1->FieldValues["DTKSHIN"];						//得意先品番
    	   	strcpy(pSPACE_DATA[iSPACE_COUNT].DTKSHIN	,sBuf.c_str());
        }
        strcpy(pSPACE_DATA[iSPACE_COUNT].REVCNT		,"");
        if ( VarIsNull(Query1->FieldValues["REVCNT"]) != true  )
        {
        	sBuf = Query1->FieldValues["REVCNT"];                     	//改訂番号
            strcpy(pSPACE_DATA[iSPACE_COUNT].REVCNT	,sBuf.c_str());
        }
        strcpy(pSPACE_DATA[iSPACE_COUNT].UNQ_NO		,"");
        if ( VarIsNull(Query1->FieldValues["UNQ_NO"]) != true  )
        {
        	sBuf = Query1->FieldValues["UNQ_NO"];                    	//明細識別番号
            strcpy(pSPACE_DATA[iSPACE_COUNT].UNQ_NO	,sBuf.c_str());
        }
        strcpy(pSPACE_DATA[iSPACE_COUNT].ORDER_NO		,"");
        if ( VarIsNull(Query1->FieldValues["ORDER_NO"]) != true )
        {
        	sBuf = Query1->FieldValues["ORDER_NO"];                    	//表示
            strcpy(pSPACE_DATA[iSPACE_COUNT].ORDER_NO	,sBuf.c_str());
        }
        strcpy(pSPACE_DATA[iSPACE_COUNT].SKB_NO		,"");
        if ( VarIsNull(Query1->FieldValues["SKB_NO"]) != true )
        {
        	sBuf = Query1->FieldValues["SKB_NO"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].SKB_NO	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].HINBAN_SK		,"");
        if ( VarIsNull(Query1->FieldValues["HINBAN_SK"]) != true)
        {
        	sBuf = Query1->FieldValues["HINBAN_SK"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].HINBAN_SK	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KOMK_NO		,"");
        if ( VarIsNull(Query1->FieldValues["KOMK_NO"]) != true )
        {
        	sBuf   = Query1->FieldValues["KOMK_NO"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KOMK_NO		,sBuf.c_str());
        }
        sBuf = "";
        strcpy(pSPACE_DATA[iSPACE_COUNT].KOMK_NM		,"");
        if ( VarIsNull(Query1->FieldValues["KOMK_NM"]) != true )
        {
        	sBuf   = Query1->FieldValues["KOMK_NM"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KOMK_NM		,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KOMK_ENG		,"");
        if ( VarIsNull(Query1->FieldValues["KOMK_ENG"]) != true )
        {
        	sBuf = Query1->FieldValues["KOMK_ENG"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KOMK_ENG		,sBuf.c_str());
        }
        sBuf = "";
        strcpy(pSPACE_DATA[iSPACE_COUNT].KOMK_SUB		,"");
        if ( VarIsNull(Query1->FieldValues["KOMK_SUB"]) != true )
        {
        	sBuf = Query1->FieldValues["KOMK_SUB"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KOMK_SUB		,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KOMK_SUB_ENG		,"");
        if ( VarIsNull(Query1->FieldValues["KOMK_SUB_ENG"]) != true)
        {
        	sBuf   = Query1->FieldValues["KOMK_SUB_ENG"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KOMK_SUB_ENG		,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKI_NO		,"");
        if ( VarIsNull(Query1->FieldValues["KIKI_NO"]) != true  )
        {
        	sBuf   = Query1->FieldValues["KIKI_NO"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKI_NO		,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKI_NM		,"");
        if ( VarIsNull(Query1->FieldValues["KIKI_NM"]) != true )
        {
        	sBuf   = Query1->FieldValues["KIKI_NM"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKI_NM   	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].TANI		,"");
        if ( VarIsNull(Query1->FieldValues["TANI"]) != true  )
        {
        	sBuf      = Query1->FieldValues["TANI"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].TANI      	,sBuf.c_str());
        }
        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_TYPE		,"");
        if ( VarIsNull(Query1->FieldValues["KIKA_TYPE"]) != true )
        {
        	sBuf = Query1->FieldValues["KIKA_TYPE"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_TYPE 	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_KIND		,"");
        if ( VarIsNull(Query1->FieldValues["KIKA_KIND"]) != true )
        {
        	sBuf = Query1->FieldValues["KIKA_KIND"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_KIND 	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_DECI		,"");
        if ( VarIsNull(Query1->FieldValues["KIKA_DECI"]) != true )
        {
        	sBuf = Query1->FieldValues["KIKA_DECI"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_DECI 	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_NUM1		,"");
        if ( VarIsNull(Query1->FieldValues["KIKA_NUM1"]) != true )
        {
        	sBuf = Query1->FieldValues["KIKA_NUM1"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_NUM1 	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_NUM2		,"");
        if ( VarIsNull(Query1->FieldValues["KIKA_NUM2"]) != true )
        {
        	sBuf = Query1->FieldValues["KIKA_NUM2"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_NUM2 	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_NUM3		,"");
        if ( VarIsNull(Query1->FieldValues["KIKA_NUM3"]) != true )
        {
        	sBuf = Query1->FieldValues["KIKA_NUM3"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_NUM3 	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_STR		,"");
        if ( VarIsNull(Query1->FieldValues["KIKA_STR"]) != true )
        {
        	sBuf  = Query1->FieldValues["KIKA_STR"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_STR  	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_SUB1		,"");
        if ( VarIsNull(Query1->FieldValues["KIKA_SUB1"]) != true )
        {
        	sBuf = Query1->FieldValues["KIKA_SUB1"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_SUB1 	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_SUB2		,"");
        if ( VarIsNull(Query1->FieldValues["KIKA_SUB2"]) != true )
        {
        	sBuf = Query1->FieldValues["KIKA_SUB2"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_SUB2 	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_SUB3		,"");
        if ( VarIsNull(Query1->FieldValues["KIKA_SUB3"]) != true )
        {
        	sBuf = Query1->FieldValues["KIKA_SUB3"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_SUB3 	,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].SOKU_SU		,"");
        if ( VarIsNull(Query1->FieldValues["SOKU_SU"]) != true )
        {
        	sBuf = Query1->FieldValues["SOKU_SU"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].SOKU_SU		,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].SOKU_FLG		,"");
        if ( VarIsNull(Query1->FieldValues["SOKU_FLG"]) != true )
        {
        	sBuf = Query1->FieldValues["SOKU_FLG"];
            strcpy(pSPACE_DATA[iSPACE_COUNT].SOKU_FLG		,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].TOKU_FLG		,"");
        if ( VarIsNull(Query1->FieldValues["TOKU_FLG"]) != true )
	    {
    	   	sBuf = Query1->FieldValues["TOKU_FLG"];
       		strcpy(pSPACE_DATA[iSPACE_COUNT].TOKU_FLG		,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_PRT		,"");
	   	if ( VarIsNull(Query1->FieldValues["KIKA_PRT"]) != true )
        {
        	sBuf = Query1->FieldValues["KIKA_PRT"];
           	strcpy(pSPACE_DATA[iSPACE_COUNT].KIKA_PRT		,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].VALUE_TYPE		,"");
	   	if ( VarIsNull(Query1->FieldValues["VALUE_TYPE"]) != true)
        {
    	    sBuf = Query1->FieldValues["VALUE_TYPE"];
           	strcpy(pSPACE_DATA[iSPACE_COUNT].VALUE_TYPE		,sBuf.c_str());
        }

        strcpy(pSPACE_DATA[iSPACE_COUNT].VALUE_DECI		,"");
        if ( VarIsNull(Query1->FieldValues["VALUE_DECI"]) != true )
        {
        	sBuf = Query1->FieldValues["VALUE_DECI"];
           	strcpy(pSPACE_DATA[iSPACE_COUNT].VALUE_DECI		,sBuf.c_str());
        }
        iSPACE_COUNT ++;                                              //項目数
        Query1->Next();
    }
    Query1->Close();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：ユーザーコードからグリッドに表示する名前を出力する。
//
//  機能説明
//   ユーザーコードからグリッドに表示する名前を出力する。
//
//  パラメタ説明
//    AnsiString CODE   ：ユーザーコード
//
//  戻り値
//    成功  ：ユーザーコードに対応したユーザー名。
//    失敗  ：既存のユーザー名。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetTANTO(AnsiString CODE)
{
     //ユーザー名検索

	AnsiString sBuf;
    //int i1;

	if( CODE.Length() == 0 ) return(Form1->USER_NAM);
     // 問合せ実行(担当者コード)
     sBuf = "SELECT TANSYA, TANNAM FROM SM12S WHERE TANSYA = ";
     sBuf += CODE ;

     // Initial Query
     QueryTANTO->Close();
     QueryTANTO->SQL->Clear();
     QueryTANTO->SQL->Add(sBuf);
     QueryTANTO->Open();
     QueryTANTO->Active = true;

     //担当者コード無いよ
     if ( QueryTANTO->Bof == true && QueryTANTO->Eof ) {
     //検索結果 ０件
		sBuf = Form1->USER_NAM;
     }
     else
     {
		sBuf = QueryTANTO->FieldValues["TANNAM"];
     }
	 QueryTANTO->Close();
    return(sBuf);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：ユーザーコードからグリッドに表示する名前を出力する。
//
//  機能説明
//   ユーザーコードからグリッドに表示する名前を出力する。
//   （GetTANTO(AnsiString CODE)　と同じコードですがスレッド動作していた頃に
//  　どうしても同じ機能を持つ関数が必要だったために作成しました）
//
//  パラメタ説明
//    AnsiString CODE   ：ユーザーコード
//
//  戻り値
//    成功  ：ユーザーコードに対応したユーザー名。
//    失敗  ：既存のユーザー名
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetTANTO2(AnsiString CODE)
{
     //ユーザー名検索

	AnsiString sBuf;
    //int i1;
	if( CODE.Length() == 0 ) return(Form1->USER_NAM);
     // 問合せ実行(担当者コード)
     sBuf = "SELECT TANSYA, TANNAM FROM SM12S WHERE TANSYA = ";
     sBuf += CODE ;

     // Initial Query
     QueryTANTO2->Close();
     QueryTANTO2->SQL->Clear();
     QueryTANTO2->SQL->Add(sBuf);
     QueryTANTO2->Open();
     QueryTANTO2->Active = true;

     //担当者コード無いよ
     if ( QueryTANTO2->Bof == true && QueryTANTO2->Eof ) {
     //検索結果 ０件
		sBuf = Form1->USER_NAM;
     }
     else
     {
		sBuf = QueryTANTO2->FieldValues["TANNAM"];
     }
	 QueryTANTO2->Close();
    return(sBuf);
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：測定実績データを読み込みます。
//
//  機能説明
//   測定実績データ（測定）を読み込み、バッファに代入します。
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
    AnsiString sLot_Where;

	AnsiString sTIME,sDATE;
	sDATE = FormatDateTime("yyyymmdd",Date());
	sTIME = FormatDateTime("hhmm",Time());

	for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
	{
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN	 ,sNowDTKSHIN.c_str());
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO	 	 ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN 	 ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());          //onishi
		//strcpy(pSOKU_KSD01_DATA[iCol].HINBAN	 ,pKSM01_DATA.HINBAN);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSCOD	 ,pKSM01_DATA.DTKSCOD);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSNAM	 ,pKSM01_DATA.DTKSNAM);
		strcpy(pSOKU_KSD01_DATA[iCol].ZISNAM	 ,pKSM01_DATA.ZISNAM);
		strcpy(pSOKU_KSD01_DATA[iCol].HINMEI	 ,pKSM01_DATA.HINMEI);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ,pKSM01_DATA.DTKSHIN1_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ,pKSM01_DATA.DTKSHIN2_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ,pKSM01_DATA.DTKSHIN3_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ,pKSM01_DATA.DTKSHIN4_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ,pKSM01_DATA.DTKSHIN5_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ,pKSM01_DATA.DTKSHIN6_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ,pKSM01_DATA.LOT_LINK_SZ);
		strcpy(pSOKU_KSD01_DATA[iCol].SOKUTEI_NUM,pKSM01_DATA.SOKUTEI_NUM);
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
        //日付と時刻のデフォルトは測定開始日、開始時刻とします
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ 	 ,sDATE.c_str());
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT  ,sDATE.c_str());
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD 	     ,sDATE.c_str());
		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT     ,sDATE.c_str());
		strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD 	     ,sDATE.c_str());
		strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM 	     ,"");
		strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD 	     ,sDATE.c_str());
		strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM 	     ,"");
		strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	     ,pKSM01_DATA.UPDCHR);
		strcpy(pSOKU_KSD01_DATA[iCol].UPDCNT 	     ,pKSM01_DATA.UPDCNT);
		pSOKU_KSD01_DATA[iCol].UPD_FLG 	= false;
		pSOKU_KSD01_DATA[iCol].SAVE_FLG = true;		//ロード結果と同じだから初期値はTRUE


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
	 		if(AnsiString(pKSM01_DATA.LOT_LINK_SZ) == 1  && sBuf2.Length() != 0 )
			{
                switch( i2 )
                {
                case 0:
				    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
				    //strcpy(pSOKU_KSD01_DATA[iCol].HINBAN1_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                    break;
                case 1:
				    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
				    //strcpy(pSOKU_KSD01_DATA[iCol].HINBAN2_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                    break;
                case 2:
				    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
				    //strcpy(pSOKU_KSD01_DATA[iCol].HINBAN3_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                    break;
                case 3:
				    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
				    //strcpy(pSOKU_KSD01_DATA[iCol].HINBAN4_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                    break;
                case 4:
				    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
				    //strcpy(pSOKU_KSD01_DATA[iCol].HINBAN5_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                    break;
                case 5:
				    strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ,Form1->SGr_tSOKU->Cells[iCol][0].c_str());
				    //strcpy(pSOKU_KSD01_DATA[iCol].HINBAN6_SZ,Form1->SGr_tSOKU->Cells[iCol][1].c_str());
                    break;
                }
			}
       }
	}

    //履歴の有る物のセット
	sLot ="";
	for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
	{
        if(Form1->SGr_tSOKU->Cells[iCol][0].Length() != 0 )
        {
    	    sLot += "'" + Form1->SGr_tSOKU->Cells[iCol][0] +"',";
        }
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
	for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
	{
        if(Form1->SGr_tSOKU->Cells[iCol][0].Length() != 0 )
        {
            sLot_Where += "( LOTNO='" + Form1->SGr_tSOKU->Cells[iCol][0] + "' AND ";
            sLot_Where += " HINBAN='" + Form1->SGr_tSOKU->Cells[iCol][1] + "') OR ";
        }
	}
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

	sBuf = "SELECT * FROM KSD01";
	sBuf += " WHERE DTKSHIN = '" + sNowDTKSHIN + "'";
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
        //履歴測定実績データの読み込み
		for(iCol = 0;iCol<Form1->SGr_tSOKU->ColCount;iCol++)
		{
			if(Form1->SGr_tSOKU->Cells[iCol][0] == AnsiString(Form1->Query4->FieldValues["LOTNO"])) break;
		}

        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN"];						 //得意先品番
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN	 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].LOTNO		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO"];                     	 //ロットNO
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO	 				,sBuf.c_str());
        }
        strcpy(pSOKU_KSD01_DATA[iCol].HINBAN		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN"];                     	 //工管発行日 onishi
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN	 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO1_SZ"];                 	 //素材用ロット１
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO1_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO2_SZ"];                      //素材用ロット２
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO2_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO3_SZ"];                      //素材用ロット３
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO3_SZ	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO4_SZ"];                      //素材用ロット４
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO4_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO5_SZ"];                      //素材用ロット５
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO5_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOTNO6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOTNO6_SZ"];                      //素材用ロット６
			strcpy(pSOKU_KSD01_DATA[iCol].LOTNO6_SZ	 	 		,sBuf.c_str());
		}

		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN1_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN1_SZ"];                 	 //素材用自社品番1
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN1_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN2_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN2_SZ"];                 	 //素材用自社品番2
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN2_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN3_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN3_SZ"];                 	 //素材用自社品番3
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN3_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN4_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN4_SZ"];                 	 //素材用自社品番4
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN4_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN5_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN5_SZ"];                 	 //素材用自社品番5
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN5_SZ	 	 		,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].HINBAN6_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN6_SZ"];                 	 //素材用自社品番6
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN6_SZ	 	 		,sBuf.c_str());
        }

        strcpy(pSOKU_KSD01_DATA[iCol].HINBAN		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINBAN"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINBAN"];                       	//自社品番
			strcpy(pSOKU_KSD01_DATA[iCol].HINBAN	 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].DTKSCOD		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSCOD"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSCOD"];                      	//得意先コード
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSCOD	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSNAM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSNAM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSNAM"];                      	//得意先名称
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSNAM	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].ZISNAM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["ZISNAM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["ZISNAM"];                       	//材質名称
			strcpy(pSOKU_KSD01_DATA[iCol].ZISNAM	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].HINMEI		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["HINMEI"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["HINMEI"];                      	//品名
			strcpy(pSOKU_KSD01_DATA[iCol].HINMEI	 	 		,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN1_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN1_SZ"];                  	//素材用得意先品番１
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN1_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN2_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN2_SZ"];                    //素材用得意先品番２
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN2_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN3_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN3_SZ"];                    //素材用得意先品番３
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN3_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN4_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN4_SZ"];                    //素材用得意先品番４
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN4_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN5_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN5_SZ"];                    //素材用得意先品番５
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN5_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["DTKSHIN6_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["DTKSHIN6_SZ"];                    //素材用得意先品番６
			strcpy(pSOKU_KSD01_DATA[iCol].DTKSHIN6_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["LOT_LINK_SZ"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["LOT_LINK_SZ"];                    //ロットリンク
			strcpy(pSOKU_KSD01_DATA[iCol].LOT_LINK_SZ			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].SOKUTEI_NUM		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SOKUTEI_NUM"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOKUTEI_NUM"];                    //測定項目数
			strcpy(pSOKU_KSD01_DATA[iCol].SOKUTEI_NUM			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SOZAI_OK"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOZAI_OK"];                       //素材判定
			strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK				,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK_PRT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SOZAI_OK_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SOZAI_OK_PRT"];                   //素材判定印刷用
			strcpy(pSOKU_KSD01_DATA[iCol].SOZAI_OK_PRT			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SYUKA_OK"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SYUKA_OK"];                       //出荷判定
			strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK				,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK_PRT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["SYUKA_OK_PRT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["SYUKA_OK_PRT"];                   //出荷判定印刷用
			strcpy(pSOKU_KSD01_DATA[iCol].SYUKA_OK_PRT			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE1		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE1"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE1"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE1 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE2		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE2"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE2"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE2 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE3		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE3"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE3"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE3 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE4		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE4"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE4"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE4 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE5		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE5"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE5"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE5 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE6		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE6"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE6"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE6 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE7		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE7"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE7"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE7 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE8		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["OUT_TITLE8"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["OUT_TITLE8"];
			strcpy(pSOKU_KSD01_DATA[iCol].OUT_TITLE8 			,sBuf.c_str());
		}
        strcpy(pSOKU_KSD01_DATA[iCol].X_OUT		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["X_OUT"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["X_OUT"];
			strcpy(pSOKU_KSD01_DATA[iCol].X_OUT 	 			,sBuf.c_str());
        }
		strcpy(pSOKU_KSD01_DATA[iCol].MEMO		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["MEMO"]) != true)
        {
			sBuf = Form1->Query4->FieldValues["MEMO"];
			strcpy(pSOKU_KSD01_DATA[iCol].MEMO 	 				,sBuf.c_str());
        }

    //検査が途中なら本日を検査日に設定しなおす
        if(AnsiString(pSOKU_KSD01_DATA[iCol].SOZAI_OK).ToIntDef(0) == -1)  //検査未完了
        {
            strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ,FormatDateTime("yyyymmdd",Date()).c_str());
            strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT,FormatDateTime("yyyymmdd",Date()).c_str());
        }
        else
        {
	//素材用検査測定日
    		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ		,"");
            if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_SZ"]) != true )
            {
    			sBuf = Form1->Query4->FieldValues["SKTYMD_SZ"];
	    		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ 	 			,sBuf.c_str());
            }
    		if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD).Trim().Length() != 8 )
	    	{
		    	strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ,pKSM01_DATA.ADDYMD);
            }
	//素材用検査測定日（印刷用）
            strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT		,"");
            if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_SZ_PRT"]) != true)
            {
		    	sBuf = Form1->Query4->FieldValues["SKTYMD_SZ_PRT"];
			    strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT 	 	  	,sBuf.c_str());
            }
	    	if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT).Trim().Length() != 8 )
		    {
			    strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_SZ_PRT,pKSM01_DATA.ADDYMD);
            }
        }
    //検査が途中なら本日を検査日に設定しなおす
        if(AnsiString(pSOKU_KSD01_DATA[iCol].SYUKA_OK).ToIntDef(0) == -1)  //検査未完了
        {
            strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD,FormatDateTime("yyyymmdd",Date()).c_str());
            strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT,FormatDateTime("yyyymmdd",Date()).c_str());
        }
        else
        {
	//出荷用検査測定日
    		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD		,"");
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
            strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT		,"");
            if ( VarIsNull(Form1->Query4->FieldValues["SKTYMD_PRT"]) != true)
            {
			    sBuf = Form1->Query4->FieldValues["SKTYMD_PRT"];
    			strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT 	 	  	,sBuf.c_str());
            }
		    if(AnsiString(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT).Trim().Length() != 8 )
    		{
	    		strcpy(pSOKU_KSD01_DATA[iCol].SKTYMD_PRT,pKSM01_DATA.ADDYMD);
            }
        }
	//代表登録日
		strcpy(pSOKU_KSD01_DATA[iCol].ADDYMD		,"");
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
        strcpy(pSOKU_KSD01_DATA[iCol].ADDTIM		,"");
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
        strcpy(pSOKU_KSD01_DATA[iCol].UPDYMD		,"");
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
		strcpy(pSOKU_KSD01_DATA[iCol].UPDTIM		,"");
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
        strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR		,"");
        if ( VarIsNull(Form1->Query4->FieldValues["UPDCHR"]) != true )
        {
			sBuf = Form1->Query4->FieldValues["UPDCHR"];
			strcpy(pSOKU_KSD01_DATA[iCol].UPDCHR 	 			,sBuf.c_str());
		}
	//代表更新回数
        strcpy(pSOKU_KSD01_DATA[iCol].UPDCNT		,"");
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
//    自作関数			：新規ロットがあるかを判断します。
//
//  機能説明
//   全ロットを抽出条件にして、実際のレコード数と比較し、新規ロットがあるかを調べます。
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    true      ：新規ロット無し。
//    false     ：新規ロット有り。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::ALL_RIRE_DATA( void )
{
	AnsiString sBuf,sLot;
	int iCol,iAllCnt;
    bool bRet;
    AnsiString sLot_Where;

	sLot ="";
	iAllCnt = 0;
    for(iCol=0;iCol < SGr_tRIRE->ColCount; iCol++)
	{
		if(SGr_tRIRE->Cells[iCol][0].Trim().Length()!=0 )
		{
			sLot += "'" + SGr_tRIRE->Cells[iCol][0] +"',";
			iAllCnt ++;
		}
    }
    for(iCol=0;iCol < SGr_tSOKU->ColCount; iCol++)
	{
		if(SGr_tSOKU->Cells[iCol][0].Trim().Length()!=0 )
		{
			sLot += "'" + SGr_tSOKU->Cells[iCol][0] +"',";
			iAllCnt ++;
		}
    }
    sLot = sLot.SubString(1,sLot.Length()-1);

    ///////////////////////////////////////////////////////////////onishi↓
	sLot_Where ="";
	iAllCnt = 0;
    for(iCol=0;iCol < SGr_tRIRE->ColCount; iCol++)
	{
		if(SGr_tRIRE->Cells[iCol][0].Trim().Length()!=0 )
		{
            sLot_Where += "( LOTNO='" + SGr_tRIRE->Cells[iCol][0] + "' AND ";
            sLot_Where += " HINBAN='" + SGr_tRIRE->Cells[iCol][1] + "') OR ";
			iAllCnt ++;
		}
    }
    for(iCol=0;iCol < SGr_tSOKU->ColCount; iCol++)
	{
		if(SGr_tSOKU->Cells[iCol][0].Trim().Length()!=0 )
		{
            sLot_Where += "( LOTNO='" + SGr_tSOKU->Cells[iCol][0] + "' AND ";
            sLot_Where += " HINBAN='" + SGr_tSOKU->Cells[iCol][1] + "') OR ";
			iAllCnt ++;
		}
    }
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

	sBuf = "SELECT * FROM KSD01";
    sBuf += " WHERE DTKSHIN = '" + sNowDTKSHIN 	+ "'";
    //sBuf += " AND   LOTNO IN (";
	//sBuf += sLot;
    //sBuf += ") ";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";

	//For Debug
    if( iDEBUG == 1 )
    {
	    ClpBrd = Clipboard();
	    ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
    // Initial Query
	Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    Form1->Query1->Active = true;
    while( Form1->Query1->Eof == false )
	{
    	if ( VarIsNull(Form1->Query1->FieldValues["LOTNO"]) != true)
        {
        	sBuf = Form1->Query1->FieldValues["LOTNO"];
    		for(iCol=0;iCol < SGr_tRIRE->ColCount; iCol++)
			{
				if(sBuf.Trim() == SGr_tRIRE->Cells[iCol][0]) iAllCnt --;
		    }
    		for(iCol=0;iCol < SGr_tSOKU->ColCount; iCol++)
			{
				if(sBuf.Trim() == SGr_tSOKU->Cells[iCol][0]) iAllCnt --;
    		}
		}
        Form1->Query1->Next();
	}
	Form1->Query1->Close();
	if(iAllCnt == 0)
	{
		bRet = true;
	}
	else
	{
		bRet = false;
	}
	return(bRet);
}

//2003.05.15　M.HIRAI　関数化
//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：動的コントロールの開放。
//
//  機能説明
//   動的コントロールを開放します。
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
void __fastcall TForm1::DynamicCtrl_Free( void )
{
	int i1,i2;

    extern KSM02_DATA pSOZAI_OR_DATA[100];

    extern KSM02_DATA pSOZAI_OR_DATA2[100];

    extern KSM02_DATA pSOZAI_SYKA_DATA[100];

    extern KSD02_DATA pSOZAI_RIRE_DATA[100];

    extern KSD01_DATA pSOZAI_RIRE_LOT[100];

	extern 	int iSOZAI_ORCNT;
	extern	int iSOZAI_SOKUCNT;
    extern  int iSOZAI_DEL_OrCnt;
    extern  int iSOZAI_DEL_SokuCnt;													//ソート時使用する重み計算用バッファ

    for(i2=0 ; i2 < iPnl_InsKikiNameCnt; i2++)
    {
		delete Lab_KIKI_NM[i2];
		delete Pnl_InsKikiName[i2];
    }
    iPnl_InsKikiNameCnt = 0;
    for(i2=0 ;i2<iPnl_InsNoCnt;i2++)
    {
        delete Pnl_InsNo[i2];
    }
    iPnl_InsNoCnt = 0;
	for(i2=0;i2<iContCnt;i2++)
    {
        delete Lab_KOMK_NM[i2];
        delete Lab_TANI[i2];
        delete Lab_KIKA[i2];
        delete Lab_UPKIKA[i2];
        delete Lab_LOKIKA[i2];
        delete Pnl_InsName[i2];
    }
	for(i2=0;i2<iContCnt;i2++)
    {
        delete Pnl_SubBase[i2];
    }
    iContCnt = 0;
	SBx_Left_SYUKA->Refresh();
    SGr_vRIRE_SYUKA->RowCount = 0;
    SGr_vSOKU_SYUKA->RowCount = 0;
    iOrCnt = 0;
    iPnl_InsKikiNameCnt = 0;
//-----------------------------------------------------------
    iSokuSuu=0;
    iRecordCount = 0;
    iKikiCount = 0;
	iRIREKI_KOMKCNT = 0;
	iPnl_InsKikiNameCnt=0;
//-----------------------------------------------------------
            //k.k 2003.05.15
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
			for(i1 = 0 ; i1 < iRIRE_MEMO_CNT ;i1++)
        	{
            	delete Form1->Mem_vRIRE_MEMO[i1];
        	}
            iRIRE_MEMO_CNT = 0;

		    Form1->SGr_vRIRE_SOZAI->RowCount = 0;
		    Form1->SGr_vSOKU_SOZAI->RowCount = 0;
            Form1->SGr_tRIRE->ColCount = 0;

			Form1->Refresh();
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：KSD02へ空白行の追加。
//
//  機能説明
//   新規KSD02への保存時に限り空白行（スペース）データを保存します。
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
void __fastcall TForm1::ADD_SPACE( void )
{
    int iCol,i1;
    bool bNEW;
    AnsiString sBuf;
    KSD02_DATA SetData;
    AnsiString sTIME,sDATE;
    AnsiString sUSER_COD;


    sDATE = FormatDateTime("yyyymmdd",Date());
	sTIME = FormatDateTime("hhmm",TDateTime::CurrentTime());
    sUSER_COD = Form1->USER_COD;

    //KSD01に対し新規追加か更新かをチェックする
    for(iCol = 0;iCol < SGr_tSOKU->ColCount ; iCol++)
    {
        if( SGr_tSOKU->Cells[iCol][0].Length() != 0 && pSOKU_KSD01_DATA[iCol].UPD_FLG == true)
        {
    		sBuf = "SELECT * FROM KSD01";
            sBuf += " WHERE DTKSHIN = '" + sNowDTKSHIN + "'";
            sBuf += " AND LOTNO 	= '" + SGr_tSOKU->Cells[iCol][0] + "'";

            // Initial Query
            Query1->Close();
            Query1->SQL->Clear();
            Query1->SQL->Add(sBuf);
            Query1->Open();
            Query1->Active = true;
    		bNEW = false;

            if( Query1->Eof == true ) bNEW = true;
            Query1->Close();

    		if( bNEW == true )			//新規保存時はスペースも保存します.
	    	{
		    	for(i1 = 0; i1 < iSPACE_COUNT ; i1++)
			    {
    				strcpy(SetData.DTKSHIN		,pSPACE_DATA[i1].DTKSHIN);
        	        strcpy(SetData.LOTNO		,SGr_tSOKU->Cells[iCol][0].c_str());
        	        strcpy(SetData.HINBAN		,SGr_tSOKU->Cells[iCol][1].c_str());        //onishi
            	    strcpy(SetData.UNQ_NO		,pSPACE_DATA[i1].UNQ_NO);
                	strcpy(SetData.ORDER_NO		,pSPACE_DATA[i1].ORDER_NO);
	                strcpy(SetData.SKB_NO		,pSPACE_DATA[i1].SKB_NO);
        	        strcpy(SetData.HINBAN_SK	,pSPACE_DATA[i1].HINBAN_SK);
            	    strcpy(SetData.KOMK_NO		,pSPACE_DATA[i1].KOMK_NO);
                	strcpy(SetData.KOMK_NM		,pSPACE_DATA[i1].KOMK_NM);
	                strcpy(SetData.KOMK_ENG		,pSPACE_DATA[i1].KOMK_ENG);
    	            strcpy(SetData.KOMK_SUB		,pSPACE_DATA[i1].KOMK_SUB);
            	    strcpy(SetData.KOMK_SUB_ENG	,pSPACE_DATA[i1].KOMK_SUB_ENG);
                	strcpy(SetData.KIKI_NO		,pSPACE_DATA[i1].KIKI_NO);
	                strcpy(SetData.KIKI_NM		,pSPACE_DATA[i1].KIKI_NM);
    	            strcpy(SetData.TANI			,pSPACE_DATA[i1].TANI);
        	        strcpy(SetData.KIKA_TYPE	,pSPACE_DATA[i1].KIKA_TYPE);
                	strcpy(SetData.KIKA_KIND	,pSPACE_DATA[i1].KIKA_KIND);
	                strcpy(SetData.KIKA_DECI	,pSPACE_DATA[i1].KIKA_DECI);
    	            strcpy(SetData.KIKA_NUM1	,pSPACE_DATA[i1].KIKA_NUM1);
        	        strcpy(SetData.KIKA_NUM2	,pSPACE_DATA[i1].KIKA_NUM2);
            	    strcpy(SetData.KIKA_NUM3	,pSPACE_DATA[i1].KIKA_NUM3);
    	            strcpy(SetData.KIKA_STR		,pSPACE_DATA[i1].KIKA_STR);
        	        strcpy(SetData.KIKA_SUB1	,pSPACE_DATA[i1].KIKA_SUB1);
            	    strcpy(SetData.KIKA_SUB2	,pSPACE_DATA[i1].KIKA_SUB2);
                	strcpy(SetData.KIKA_SUB3	,pSPACE_DATA[i1].KIKA_SUB3);
	                strcpy(SetData.SOKU_SU		,pSPACE_DATA[i1].SOKU_SU);
        	        strcpy(SetData.SOKU_FLG		,pSPACE_DATA[i1].SOKU_FLG);
            	    strcpy(SetData.TOKU_FLG		,pSPACE_DATA[i1].TOKU_FLG);
                	strcpy(SetData.KIKA_PRT		,pSPACE_DATA[i1].KIKA_PRT);
	                strcpy(SetData.VALUE_TYPE	,pSPACE_DATA[i1].VALUE_TYPE);
        	        strcpy(SetData.VALUE_DECI	,pSPACE_DATA[i1].VALUE_DECI);
                    strcpy(SetData.SOKU_VAL01   ,"");
                    strcpy(SetData.SOKU_VAL02   ,"");
                    strcpy(SetData.SOKU_VAL03   ,"");
                    strcpy(SetData.SOKU_VAL04   ,"");
                    strcpy(SetData.SOKU_VAL05   ,"");
                    strcpy(SetData.SOKU_VAL06   ,"");
                    strcpy(SetData.SOKU_VAL07   ,"");
                    strcpy(SetData.SOKU_VAL08   ,"");
                    strcpy(SetData.SOKU_VAL09   ,"");
                    strcpy(SetData.SOKU_VAL10   ,"");
	    			strcpy(SetData.SOKU_VAL_SU  ,"0");
		    		strcpy(SetData.SOKU_VAL_AVE	,"0");
			    	strcpy(SetData.SOKU_VAL_MAX ,"0");
				    strcpy(SetData.SOKU_VAL_MIN ,"0");
                    strcpy(SetData.SOKU_OK      ,"0");
                    strcpy(SetData.DISP_VAL01   ,"");
                    strcpy(SetData.DISP_VAL02   ,"");
                    strcpy(SetData.DISP_VAL03   ,"");
                    strcpy(SetData.DISP_VAL04   ,"");
                    strcpy(SetData.DISP_VAL05   ,"");
                    strcpy(SetData.DISP_VAL06   ,"");
                    strcpy(SetData.DISP_VAL07   ,"");
                    strcpy(SetData.DISP_VAL08   ,"");
                    strcpy(SetData.DISP_VAL09   ,"");
                    strcpy(SetData.DISP_VAL10   ,"");
    				strcpy(SetData.DISP_VAL_SU  ,"0");
	    			strcpy(SetData.DISP_VAL_AVE	,"0");
		    		strcpy(SetData.DISP_VAL_MAX ,"0");
			    	strcpy(SetData.DISP_VAL_MIN ,"0");
                    strcpy(SetData.DISP_OK      ,"0");
	    			strcpy(SetData.SKTYMD,sDATE.c_str());
		    		strcpy(SetData.ADDYMD,sDATE.c_str());
			    	strcpy(SetData.ADDTIM,sTIME.c_str());
				    strcpy(SetData.UPDYMD,sDATE.c_str());
    				strcpy(SetData.UPDTIM,sTIME.c_str());
	    			strcpy(SetData.UPDCHR,sUSER_COD.c_str());
		    		strcpy(SetData.UPDCNT,"1");
			    	sBuf = "insert into KSD02(";
    	            sBuf += " DTKSHIN, LOTNO, HINBAN, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK, KOMK_NO, KOMK_NM,";
            	    sBuf += " KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI,";
	                sBuf += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3,";
    	            sBuf += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3, SOKU_SU, SOKU_FLG,";
        	        sBuf += " TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI,";
            	    sBuf += " SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05,";
    	            sBuf += " SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,";
        	        sBuf += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK,";
            	    sBuf += " DISP_VAL01, DISP_VAL02, DISP_VAL03, DISP_VAL04, DISP_VAL05,";
                	sBuf += " DISP_VAL06, DISP_VAL07, DISP_VAL08, DISP_VAL09, DISP_VAL10,";
	                sBuf += " DISP_VAL_SU, DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, DISP_OK,";
        	        sBuf += " SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
            	    sBuf += " )";
                	sBuf += " VALUES('";
	                sBuf += AnsiString(SetData.DTKSHIN)           	+ "','";	//	得意先品番
    	            sBuf += AnsiString(SetData.LOTNO)	       		+ "','";	//	ロットNO
    	            sBuf += AnsiString(SetData.HINBAN)	       		+ "', ";	//	工管発行日 onishi
            	    sBuf += AnsiString(SetData.UNQ_NO)  			+ " , ";	//	明細NO
                	sBuf += AnsiString(SetData.ORDER_NO)  			+ " , ";	//	明細NO
	                sBuf += AnsiString(SetData.SKB_NO)  			+ " ,'";	//	識別NO
    	            sBuf += AnsiString(SetData.HINBAN_SK) 			+ "', ";
        	        sBuf += AnsiString(SetData.KOMK_NO) 			+ " ,'";	//	測定項目NO
    	            sBuf += AnsiString(SetData.KOMK_NM)	       		+ "','";	//	測定項目名称
        	        sBuf += AnsiString(SetData.KOMK_ENG)       		+ "','";
            	    sBuf += AnsiString(SetData.KOMK_SUB)	   		+ "','";	//	測定項目名称
                	sBuf += AnsiString(SetData.KOMK_SUB_ENG)   		+ "', ";	//	測定項目名称
	                sBuf += AnsiString(SetData.KIKI_NO) 			+ " ,'";	//	測定機器NO
        	        sBuf += AnsiString(SetData.KIKI_NM)	       		+ "','";	//	測定機器名称
            	    sBuf += AnsiString(SetData.TANI)   	       		+ "', ";	//	単位
                	sBuf += AnsiString(SetData.KIKA_TYPE) + " , ";
	                sBuf += AnsiString(SetData.KIKA_KIND) + " , ";
    	            sBuf += AnsiString(SetData.KIKA_DECI) + " , ";
            	    sBuf += AnsiString(SetData.KIKA_NUM1) + " , ";
                	sBuf += AnsiString(SetData.KIKA_NUM2) + " , ";
	                sBuf += AnsiString(SetData.KIKA_NUM3) + " ,'";
    	            sBuf += AnsiString(SetData.KIKA_STR)            + "','";
        	        sBuf += AnsiString(SetData.KIKA_SUB1)           + "','";
                	sBuf += AnsiString(SetData.KIKA_SUB2)           + "','";
	                sBuf += AnsiString(SetData.KIKA_SUB3)           + "', ";
    	            sBuf += AnsiString(SetData.SOKU_SU) 	+ " , ";	//    　測定指示ｎ数
        	        sBuf += AnsiString(SetData.SOKU_FLG) 	+ " , ";	//    　測定指示ｎ数
            	    sBuf += AnsiString(SetData.TOKU_FLG) 	+ " , ";	//    　測定指示ｎ数
    	            sBuf += AnsiString(SetData.KIKA_PRT) 	+ " , ";	//    　測定指示ｎ数
        	        sBuf += AnsiString(SetData.VALUE_TYPE)+ " , ";	//    　測定指示ｎ数
            	    sBuf += AnsiString(SetData.VALUE_DECI)+ " ,'";	//    　測定指示ｎ数
                	sBuf += AnsiString(SetData.SOKU_VAL01)        	+ "','";	//	測定値１
	                sBuf += AnsiString(SetData.SOKU_VAL02)        	+ "','";	//      測定値２　　　
        	        sBuf += AnsiString(SetData.SOKU_VAL03)        	+ "','";	//	測定値３
            	    sBuf += AnsiString(SetData.SOKU_VAL04)        	+ "','";	//	測定値４
                	sBuf += AnsiString(SetData.SOKU_VAL05)        	+ "','";	//	測定値５
	                sBuf += AnsiString(SetData.SOKU_VAL06)        	+ "','";	//	測定値６
    	            sBuf += AnsiString(SetData.SOKU_VAL07)        	+ "','";	//	測定値７
            	    sBuf += AnsiString(SetData.SOKU_VAL08)        	+ "','";	//	測定値８
	                sBuf += AnsiString(SetData.SOKU_VAL09)        	+ "','";	//	測定値９
    	            sBuf += AnsiString(SetData.SOKU_VAL10)        	+ "', ";	//	測定値１０
        	        sBuf += AnsiString(SetData.SOKU_VAL_SU)         + " , ";	//    　測定指示ｎ数
            	    sBuf += AnsiString(SetData.SOKU_VAL_AVE)        + " , ";	//    　測定指示ｎ数
    	            sBuf += AnsiString(SetData.SOKU_VAL_MAX)        + " , ";	//    　測定指示ｎ数
        	        sBuf += AnsiString(SetData.SOKU_VAL_MIN)        + " , ";	//    　測定指示ｎ数
            	    sBuf += AnsiString(SetData.SOKU_OK)             + " ,'";	//	測定値１０
                	sBuf += AnsiString(SetData.DISP_VAL01)        	+ "','";	//	測定値１
	                sBuf += AnsiString(SetData.DISP_VAL02)        	+ "','";	//      測定値２　　　
        	        sBuf += AnsiString(SetData.DISP_VAL03)        	+ "','";	//	測定値３
            	    sBuf += AnsiString(SetData.DISP_VAL04)        	+ "','";	//	測定値４
                	sBuf += AnsiString(SetData.DISP_VAL05)        	+ "','";	//	測定値５
	                sBuf += AnsiString(SetData.DISP_VAL06)        	+ "','";	//	測定値６
    	            sBuf += AnsiString(SetData.DISP_VAL07)        	+ "','";	//	測定値７
            	    sBuf += AnsiString(SetData.DISP_VAL08)        	+ "','";	//	測定値８
                	sBuf += AnsiString(SetData.DISP_VAL09)        	+ "','";	//	測定値９
	                sBuf += AnsiString(SetData.DISP_VAL10)        	+ "', ";	//	測定値１０
    	            sBuf += AnsiString(SetData.DISP_VAL_SU)+ " , ";	//    　測定指示ｎ数
        	        sBuf += AnsiString(SetData.DISP_VAL_AVE)+ " , ";	//    　測定指示ｎ数
                	sBuf += AnsiString(SetData.DISP_VAL_MAX)+ " , ";	//    　測定指示ｎ数
	                sBuf += AnsiString(SetData.DISP_VAL_MIN)+ " , ";	//    　測定指示ｎ数
    	            sBuf += AnsiString(SetData.DISP_OK)  + " ,'";	//	測定値１０
        	        sBuf += AnsiString(SetData.SKTYMD)   	       + "','";	//	測定日
            	    sBuf += AnsiString(SetData.ADDYMD)   	       + "','";	//	登録日
    	            sBuf += AnsiString(SetData.ADDTIM)   	       + "','";	//	登録時間
        	        sBuf += AnsiString(SetData.UPDYMD)   	       + "','";	//	変更日
            	    sBuf += AnsiString(SetData.UPDTIM)   	       + "',";	//	変更時間
        	        sBuf += AnsiString(SetData.UPDCHR)   	       + ",";	//	変更時間
            	    sBuf += AnsiString(SetData.UPDCNT);  	         	//	更新回数
    	            sBuf += ")";

                    //For Debug
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
                    // 問い合せ文の実行
        		    try{
            		    Query1->ExecSQL();
    	            }
        	        catch(EDatabaseError& e)
            	    {
                		SBr1->Panels->Items[0]->Text = e.Message;
	                    SBr1->Update();
    	                return;
            	    }
                	catch(Exception& e)
	                {
    	            	SBr1->Panels->Items[0]->Text = e.Message;
        	            SBr1->Update();
            	        return;
                	}
	    		}
		    }
        }
    }
}
