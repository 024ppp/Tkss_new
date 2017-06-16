//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include "Thread1.h"
#include "Tkss01.h"
#include "Unit1.h"
#include "UnitDataAccess.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
// 注意：異なるスレッドが所有する VCL のメソッド/関数/プロパティを
//       別のスレッドの中から扱う場合，排他処理の問題が発生します。
//
//       メインスレッドの所有するオブジェクトに対しては Synchronize
//       メソッドを使う事ができます。他のオブジェクトを参照するため
//       のメソッドをスレッドクラスに追加し，Synchronize メソッドの
//       引数として渡します。
//
//       たとえば UpdateCaption を以下のように定義し、
//
//          void __fastcall MyThread::UpdateCaption()
//          {
//            Form1->Caption = "スレッドから書き換えました";
//          }
//
//       Execute メソッドの中で Synchronize メソッドに渡すことでメイ
//       ンスレッドが所有する Form1 の Caption プロパティを安全に変
//       更できます。
//
//          Synchronize(UpdateCaption);
//
//---------------------------------------------------------------------------
HANDLE				hSOZAI_TEMPOR_DATA;
KSM02_DATA 			*pSOZAI_TEMPOR_DATA;
HANDLE				hSOZAI_OR_DATA;
KSM02_DATA 			*pSOZAI_OR_DATA;
HANDLE				hSOZAI_RIREKI_LOT;
KSD01_DATA 			*pSOZAI_RIREKI_LOT;    // 過去履歴対象ロット検索用
extern HANDLE		hRIREKI_LOT;
extern KSD01_DATA 	*pRIREKI_LOT;    		// 過去履歴対象ロット検索用
extern HANDLE 		hSOZAI_SYUKA_DATA;
extern KSM02_DATA	*pSOZAI_SYUKA_DATA;
extern HANDLE 		hSOZAI_RIREKI_DATA;
extern KSD02_DATA	*pSOZAI_RIREKI_DATA;
KSM02_DATA SOZAI_RIREKI_SWAP;

__fastcall MyThread1::MyThread1(bool CreateSuspended)
	: TThread(CreateSuspended)
{
  Priority = tpIdle;
}
//---------------------------------------------------------------------------
//素材の表示
//---------------------------------------------------------------------------
void __fastcall MyThread1::Execute()
{
	int iRow,i1,i2,i3,i4;
    int iRIRE_CNT;
    int iKOMK_CNT;
    int iKOMK_NUM;
    int iSOKU_SU;
    int iLOT_CNT;
    int iPanelNum,iKikiNum,iSokuGoukei,iTKikiNo;
    int iPutKiki;
    int iSyukaWait,iRireWait;
    int iCel;
	AnsiString sBuf,sLot,sTempBuf,sTempLot;

//素材読み取り時使用するメモリの確保（仮）
/*
	// メモリの開放
	if( hSOZAI_TEMPOR_DATA ){
        GlobalUnlock( hSOZAI_TEMPOR_DATA );
        GlobalFree( hSOZAI_TEMPOR_DATA );
    }
*/
    // メモリの確保
    hSOZAI_TEMPOR_DATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * 100 );
    if( hSOZAI_TEMPOR_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pSOZAI_TEMPOR_DATA = (struct KSM02_DATA *)GlobalLock(hSOZAI_TEMPOR_DATA);
    if( hSOZAI_TEMPOR_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
/*
	// メモリの開放
	if( hSOZAI_RIREKI_LOT ){
        GlobalUnlock( hSOZAI_RIREKI_LOT );
        GlobalFree( hSOZAI_RIREKI_LOT );
    }
*/
    // メモリの確保
    hSOZAI_RIREKI_LOT = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * 100 );
    if( hSOZAI_RIREKI_LOT == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pSOZAI_RIREKI_LOT = (struct KSD01_DATA *)GlobalLock(hSOZAI_RIREKI_LOT);
    if( hSOZAI_RIREKI_LOT == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
/*
	// メモリの開放
	if( hSOZAI_SYUKA_DATA ){
        GlobalUnlock( hSOZAI_SYUKA_DATA );
        GlobalFree( hSOZAI_SYUKA_DATA );
    }
*/
    // メモリの確保
    hSOZAI_SYUKA_DATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * 100 );
    if( hSOZAI_SYUKA_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pSOZAI_SYUKA_DATA = (struct KSM02_DATA *)GlobalLock(hSOZAI_SYUKA_DATA);
    if( hSOZAI_SYUKA_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }

/*
	// メモリの開放
	if( hSOZAI_RIREKI_DATA ){
        GlobalUnlock( hSOZAI_RIREKI_DATA );
        GlobalFree( hSOZAI_RIREKI_DATA );
    }
*/
    // メモリの確保
    hSOZAI_RIREKI_DATA = GlobalAlloc( GHND, sizeof(struct KSD02_DATA) * 100 );
    if( hSOZAI_RIREKI_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pSOZAI_RIREKI_DATA = (struct KSD02_DATA *)GlobalLock(hSOZAI_RIREKI_DATA);
    if( hSOZAI_RIREKI_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }

	while(Form1->Query3->Tag != 0){};
	Form1->Query3->Tag 	=1;				//Query3使用中
    Form1->iSOZAI_OrCnt =0;

//得意先品番をキーにして本日出荷用の検査項目数を抽出する
	sBuf = "SELECT * FROM KSM02";
	sBuf += " WHERE DTKSHIN ='" + Form1->Cmb_DTKSHIN->Text + "'";
	sBuf += " AND REVCNT = 0" ;
    sBuf += " AND SKB_NO = 1" ;                                      //素材検査項目
	sBuf += " ORDER BY KIKI_NO, KOMK_NO, KOMK_SUB, UNQ_NO";

//For Debug
/*
    // 2003.06.03 k.y
    if( iDEBUG == 1 )
    {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
*/
	// Initial Query
	Form1->Query3->Close();
	Form1->Query3->SQL->Clear();
	Form1->Query3->SQL->Add(sBuf);
	Form1->Query3->Open();
	Form1->Query3->Active = true;

    Form1->iSOZAI_SYUKA_KOMKCNT = 0;
    while( Form1->Query3->Eof == false )
    {
        sBuf  	= Form1->Query3->FieldValues["HINBAN_SK"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].HINBAN_SK  	,sBuf.c_str());
        sBuf	= Form1->Query3->FieldValues["KOMK_NO"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KOMK_NO		,sBuf.c_str());
       	sBuf   	= Form1->Query3->FieldValues["KOMK_NM"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KOMK_NM    	,sBuf.c_str());
        if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
            && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
        {
            sBuf = Form1->Query3->FieldValues["KOMK_SUB"];
            strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KOMK_SUB	,sBuf.c_str());
        }
        sBuf    = Form1->Query3->FieldValues["KIKI_NO"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKI_NO    ,sBuf.c_str());
        sBuf    = Form1->Query3->FieldValues["KIKI_NM"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKI_NM    ,sBuf.c_str());
        sBuf       = Form1->Query3->FieldValues["TANI"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].TANI       ,sBuf.c_str());
        sBuf  = Form1->Query3->FieldValues["KIKA_TYPE"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKA_TYPE  ,sBuf.c_str());
        sBuf  = Form1->Query3->FieldValues["KIKA_KIND"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKA_KIND  ,sBuf.c_str());
        sBuf  = Form1->Query3->FieldValues["KIKA_DECI"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKA_DECI  ,sBuf.c_str());
        sBuf  = Form1->Query3->FieldValues["KIKA_NUM1"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKA_NUM1  ,sBuf.c_str());
        sBuf  = Form1->Query3->FieldValues["KIKA_NUM2"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKA_NUM2 ,sBuf.c_str());
        sBuf  = Form1->Query3->FieldValues["KIKA_NUM3"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKA_NUM3  ,sBuf.c_str());
        sBuf   = Form1->Query3->FieldValues["KIKA_STR"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKA_STR   ,sBuf.c_str());
        sBuf  = Form1->Query3->FieldValues["KIKA_SUB1"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKA_SUB1  ,sBuf.c_str());
        sBuf  = Form1->Query3->FieldValues["KIKA_SUB2"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKA_SUB2  ,sBuf.c_str());
        sBuf  = Form1->Query3->FieldValues["KIKA_SUB3"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].KIKA_SUB3  ,sBuf.c_str());
        sBuf    = Form1->Query3->FieldValues["SOKU_SU"];
        strcpy(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SYUKA_KOMKCNT].SOKU_SU    ,sBuf.c_str());
        Form1->iSOZAI_SYUKA_KOMKCNT ++;                                              //項目数
        Form1->Query1->Next();
    }
	Form1->Query3->Close();


    iRIRE_CNT   = 0;
    iLOT_CNT    = 0;
    Form1->iSOZAI_RIREKI_KOMKCNT = 0;
	if(Form1->Chk_RIRE->Checked == true)
	{
//出荷検査にあるロットを抽出してNOTの条件にする
    	sTempLot = "";
		for(i1 = 0;i1 < Form1->SGr_tSOKU->ColCount ; i1++)
		{
			sTempLot += "'" + Form1->SGr_tSOKU->Cells[i1][0] + "'" + ",";
		}
		sTempLot = sTempLot.SubString(1,sTempLot.Length()-1);

//得意先品番をキーにして必要ロットの取得をする（履歴数分）
		sBuf = "SELECT * FROM KSD01";
		sBuf += " WHERE DTKSHIN ='" + Form1->Cmb_DTKSHIN->Text + "'";
		if( sTempLot.Length() > 3 ) {
    		sBuf += " AND LOTNO NOT IN ("+ sTempLot + ")";
		}
		sBuf += " ORDER BY UPDYMD, UPDTIM DESC";

//For Debug
/*
    // 2003.06.03 k.y
    if( iDEBUG == 1 )
    {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
*/
	// Initial Query
		Form1->Query3->Close();
		Form1->Query3->SQL->Clear();
		Form1->Query3->SQL->Add(sBuf);
		Form1->Query3->Open();
		Form1->Query3->Active = true;

//同一品番の過去履歴ロットの抽出
    	while( Form1->Query3->Eof == false )
    	{
            strcpy(pSOZAI_RIREKI_LOT[iLOT_CNT].DTKSHIN	,"");
            strcpy(pSOZAI_RIREKI_LOT[iLOT_CNT].LOTNO	,"");
            sBuf =  Form1->Query3->FieldValues["DTKSHIN"];
            strcpy(pSOZAI_RIREKI_LOT[iLOT_CNT].DTKSHIN ,sBuf.c_str());
            sBuf =    Form1->Query3->FieldValues["LOTNO"];
            strcpy(pSOZAI_RIREKI_LOT[iLOT_CNT].LOTNO ,sBuf.c_str());
            iLOT_CNT++;
            Form1->Query3->Next();
    	}
		Form1->Query3->Close();
//    if( iLOT_CNT >  Form1->Edt_RIRE_NUM->Text.ToInt()) iLOT_CNT = Form1->Edt_RIRE_NUM->Text.ToInt();

//抽出ロットのｎ数のMAX値の抽出
    	if( iLOT_CNT > 0 )          //過去履歴が0件出なければ
    	{
	    	sBuf = "SELECT KIKI_NO, KOMK_NO, KOMK_SUB, MAX(SOKU_SU) AS SOKU_SU_MAX FROM KSD02";
	    	sBuf += " WHERE DTKSHIN ='" + Form1->Cmb_DTKSHIN->Text + "'";
        	sBuf += " AND SKB_NO = 1";                        //出荷検査項目、材料証明項目
        	sBuf += " AND LOTNO IN (";
        	for(i1=0;i1<iLOT_CNT;i1++)
        	{
            	sBuf += "'"+AnsiString(pSOZAI_RIREKI_LOT[i1].LOTNO)+"'" ;
            	if(i1+1 < iLOT_CNT ) sBuf += ", ";
        	}
        	sBuf += " )";
	    	sBuf += " GROUP BY KIKI_NO, KOMK_NO, KOMK_SUB";
	    	sBuf += " ORDER BY KIKI_NO, KOMK_NO, KOMK_SUB";

//For Debug
/*
    // 2003.06.03 k.y
    if( iDEBUG == 1 )
    {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
*/
	// Initial Query
	    	Form1->Query3->Close();
	    	Form1->Query3->SQL->Clear();
	    	Form1->Query3->SQL->Add(sBuf);
	    	Form1->Query3->Open();
	    	Form1->Query3->Active = true;


//対象過去履歴の検索　STEP1
        	while( Form1->Query3->Eof == false )
        	{
            	sBuf = Form1->Query3->FieldValues["SOKU_SU_MAX"];
            	strcpy(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RIREKI_KOMKCNT].SOKU_SU ,sBuf.c_str());
            	sBuf = Form1->Query3->FieldValues["KIKI_NO"];
            	strcpy(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RIREKI_KOMKCNT].KIKI_NO ,sBuf.c_str());
            	sBuf = Form1->Query3->FieldValues["KOMK_NO"];
            	strcpy(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RIREKI_KOMKCNT].KOMK_NO ,sBuf.c_str());
            	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
            	&& VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
            	{
                	sBuf = Form1->Query3->FieldValues["KOMK_SUB"];
                	strcpy(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RIREKI_KOMKCNT].KOMK_SUB ,sBuf.c_str());
            	}
            	Form1->iSOZAI_RIREKI_KOMKCNT ++;                                              //項目数
            	Form1->Query3->Next();
        	}
	    	Form1->Query3->Close();
    	}
//NULLでソートが変になっているのでメモリ上で再ソート実行
    	for(i2 = 0;i2< Form1->iSOZAI_RIREKI_KOMKCNT-1;i2++)
    	{
			for(i1 = 0;i1< Form1->iSOZAI_RIREKI_KOMKCNT-1;i1++)
    		{
      			if((pSOZAI_RIREKI_DATA[i1].KIKI_NO 	> pSOZAI_RIREKI_DATA[i1+1].KIKI_NO) ||
               	(pSOZAI_RIREKI_DATA[i1].KOMK_NO 	> pSOZAI_RIREKI_DATA[i1+1].KOMK_NO) ||
               	(pSOZAI_RIREKI_DATA[i1].KOMK_SUB 	> pSOZAI_RIREKI_DATA[i1+1].KOMK_SUB))
      			{
         			strcpy(SOZAI_RIREKI_SWAP.SOKU_SU	,pSOZAI_RIREKI_DATA[i1].SOKU_SU);
         			strcpy(SOZAI_RIREKI_SWAP.KIKI_NO	,pSOZAI_RIREKI_DATA[i1].KIKI_NO);
         			strcpy(SOZAI_RIREKI_SWAP.KOMK_NO	,pSOZAI_RIREKI_DATA[i1].KOMK_NO);
         			strcpy(SOZAI_RIREKI_SWAP.KOMK_SUB	,pSOZAI_RIREKI_DATA[i1].KOMK_SUB);

         			strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_SU  	,pRIREKI_DATA[i1+1].SOKU_SU);
         			strcpy(pSOZAI_RIREKI_DATA[i1].KIKI_NO	,pRIREKI_DATA[i1+1].KIKI_NO);
         			strcpy(pSOZAI_RIREKI_DATA[i1].KOMK_NO	,pRIREKI_DATA[i1+1].KOMK_NO);
         			strcpy(pSOZAI_RIREKI_DATA[i1].KOMK_SUB	,pRIREKI_DATA[i1+1].KOMK_SUB);

         			strcpy(pSOZAI_RIREKI_DATA[i1+1].SOKU_SU	,SOZAI_RIREKI_SWAP.SOKU_SU);
         			strcpy(pSOZAI_RIREKI_DATA[i1+1].KIKI_NO	,SOZAI_RIREKI_SWAP.KIKI_NO);
         			strcpy(pSOZAI_RIREKI_DATA[i1+1].KOMK_NO	,SOZAI_RIREKI_SWAP.KOMK_NO);
         			strcpy(pSOZAI_RIREKI_DATA[i1+1].KOMK_SUB,SOZAI_RIREKI_SWAP.KOMK_SUB);
      			}
    		}
		}
	}
//現在の出荷用の項目と過去履歴の項目の最大数のORを別メモリ上へ格納
    Form1->iSOZAI_RireCnt 	= 0;
    Form1->iSOZAI_SyukaCnt 	= 0;
    Form1->iSOZAI_OrCnt 	= 0;
    while( 1 )
    {
        if( Form1->iSOZAI_SyukaCnt >= Form1->iSOZAI_SYUKA_KOMKCNT && Form1->iSOZAI_RireCnt >= Form1->iSOZAI_RIREKI_KOMKCNT ) break;
//項目がどちらが小さいかの重み付け
//出荷重み計算
        iSyukaWait = AnsiString(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KIKI_NO).ToIntDef(0) * 1000
                    +AnsiString(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KOMK_NO).ToIntDef(0) * 100;

//履歴重み計算
        iRireWait =  AnsiString(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KIKI_NO).ToIntDef(0) * 1000
                    +AnsiString(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_NO).ToIntDef(0) * 100;

        if( Form1->iSOZAI_SyukaCnt  >= Form1->iSOZAI_SYUKA_KOMKCNT ) iSyukaWait = 99999;
        if( Form1->iSOZAI_RireCnt   >= Form1->iSOZAI_RIREKI_KOMKCNT ) iRireWait = 99999;
        if( iSyukaWait < iRireWait )
        {
            strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KIKI_NO,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KIKI_NO);
            strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KOMK_NO,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KOMK_NO);
            strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KOMK_SUB,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KOMK_SUB);
            strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].SOKU_SU,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].SOKU_SU);
            Form1->iSOZAI_SyukaCnt ++;
        }
        else if( iSyukaWait == iRireWait )
        {
        	if( AnsiString(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KOMK_SUB).Trim() < AnsiString(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_SUB).Trim())
            {
            	strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KIKI_NO	,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KIKI_NO);
                strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KOMK_NO	,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KOMK_NO);
                strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KOMK_SUB	,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KOMK_SUB);
                strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].SOKU_SU	,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].SOKU_SU);
                Form1->iSOZAI_SyukaCnt ++;
            }
            else if( AnsiString(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KOMK_SUB).Trim() == AnsiString(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_SUB).Trim())
            {
            	strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KIKI_NO	,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KIKI_NO);
                strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KOMK_NO	,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KOMK_NO);
                strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KOMK_SUB	,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].KOMK_SUB);
                if( AnsiString(pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].SOKU_SU).ToInt() >= AnsiString(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].SOKU_SU).ToInt())
                {
                	strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].SOKU_SU,pSOZAI_SYUKA_DATA[Form1->iSOZAI_SyukaCnt].SOKU_SU);
                }
                else
                {
                	strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].SOKU_SU,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].SOKU_SU);
                }
                Form1->iSOZAI_SyukaCnt ++;
                Form1->iSOZAI_RireCnt ++;
            }
            else
            {
            	strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KIKI_NO,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KIKI_NO);
                strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KOMK_NO,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_NO);
                strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KOMK_SUB,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_SUB);
                strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].SOKU_SU,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].SOKU_SU);
                Form1->iSOZAI_RireCnt ++;
            }
		}
        else
        {
            strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KIKI_NO	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KIKI_NO);
            strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KOMK_NO	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_NO);
            strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].KOMK_SUB	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_SUB);
            strcpy(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_OrCnt].SOKU_SU	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].SOKU_SU);
            Form1->iSOZAI_RireCnt ++;
        }
        Form1->iSOZAI_OrCnt++;
    }

// ---------------------------------------------------------
//現在の出荷用の項目と測定実績の項目の最大数のORを別メモリ上へ格納
//測定実績読み取り
//抽出ロットのｎ数のMAX値の抽出
/*
	// メモリの開放
    if( hSOZAI_RIREKI_LOT ){
    	GlobalUnlock( hSOZAI_RIREKI_LOT );
        GlobalFree( hSOZAI_RIREKI_LOT );
    }
*/
    // メモリの開放
    if( hSOZAI_RIREKI_DATA ){
        GlobalUnlock( hSOZAI_RIREKI_DATA );
        GlobalFree( hSOZAI_RIREKI_DATA );
    }

    // メモリの確保
    hSOZAI_RIREKI_DATA = GlobalAlloc( GHND, sizeof(struct KSD02_DATA) * 100 );
    if( hSOZAI_RIREKI_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pSOZAI_RIREKI_DATA = (struct KSD02_DATA *)GlobalLock(hSOZAI_RIREKI_DATA);
    if( hSOZAI_RIREKI_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }

	int iSOZAI_RIREKI_KOMKCNT2;
	iSOZAI_RIREKI_KOMKCNT2 = 0;
	for(i1 = 0;i1 <= Form1->SGr_tSOKU->ColCount ; i1++)
	{
		sLot += "'" + Form1->SGr_tSOKU->Cells[i1][0] + "'" + ",";
	}
	sLot = sLot.SubString(1,sLot.Length()-1);

//    if( Form1->iRIRE_CNT > 0 )          //過去履歴が0件でなければ
    if( Form1->SGr_tSOKU->Cells[0][0]!="" )          //ロットがあれば
    {
/*
        Form1->SGr_vRIRE_SOZAI->RowCount = 1;
        Form1->SGr_vRIRE_SYUKA->RowCount = 1;
*/
        sBuf  = "SELECT KIKI_NO, KOMK_NO, KOMK_SUB, MAX(SOKU_SU) AS SOKU_SU_MAX FROM KSD02";
        sBuf += " WHERE DTKSHIN ='" + Form1->Cmb_DTKSHIN->Text + "'";
        sBuf += " AND SKB_NO = 1";                        		//出荷検査項目、材料証明項目
        sBuf += " AND LOTNO IN ("+ sLot + ")";
        sBuf += " GROUP BY KIKI_NO, KOMK_NO, KOMK_SUB";
        sBuf += " ORDER BY KIKI_NO, KOMK_NO, KOMK_SUB";

//For Debug
/*
    // 2003.06.03 k.y
    if( iDEBUG == 1 )
    {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
    }
*/
// Initial Query
        Form1->Query3->Close();
        Form1->Query3->SQL->Clear();
        Form1->Query3->SQL->Add(sBuf);
        Form1->Query3->Open();
        Form1->Query3->Active = true;



//出荷検査ロット中で検査済みロットの検索
		while( Form1->Query3->Eof == false )
    	{
    		sBuf = Form1->Query3->FieldValues["SOKU_SU_MAX"];
        	strcpy(pSOZAI_RIREKI_DATA[iSOZAI_RIREKI_KOMKCNT2].SOKU_SU		,sBuf.c_str());
        	sBuf = Form1->Query3->FieldValues["KIKI_NO"];
        	strcpy(pSOZAI_RIREKI_DATA[iSOZAI_RIREKI_KOMKCNT2].KIKI_NO		,sBuf.c_str());
        	sBuf = Form1->Query3->FieldValues["KOMK_NO"];
        	strcpy(pSOZAI_RIREKI_DATA[iSOZAI_RIREKI_KOMKCNT2].KOMK_NO		,sBuf.c_str());
        	strcpy(pSOZAI_RIREKI_DATA[iSOZAI_RIREKI_KOMKCNT2].KIKI_NM 		,"");
        	strcpy(pSOZAI_RIREKI_DATA[iSOZAI_RIREKI_KOMKCNT2].KOMK_NM 		,"");
        	strcpy(pSOZAI_RIREKI_DATA[iSOZAI_RIREKI_KOMKCNT2].KOMK_SUB 		,"");
        	if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
        	&& VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
        	{
        		sBuf = Form1->Query3->FieldValues["KOMK_SUB"];
            	strcpy(pSOZAI_RIREKI_DATA[iSOZAI_RIREKI_KOMKCNT2].KOMK_SUB	,sBuf.c_str());
        	}
        	iSOZAI_RIREKI_KOMKCNT2 ++;                                              //項目数
        	Form1->Query3->Next();
    	}
    	Form1->Query3->Close();
    }

//NULLでソートが変になっているのでメモリ上で再ソート実行
//    KSM02_DATA RIREKI_SWAP;
    for(i2 = 0;i2< iSOZAI_RIREKI_KOMKCNT2;i2++)
    {
		for(i1 = 0;i1< iSOZAI_RIREKI_KOMKCNT2-1;i1++)
    	{
      		if((pSOZAI_RIREKI_DATA[i1].KIKI_NO 		> pSOZAI_RIREKI_DATA[i1+1].KIKI_NO) ||
               (pSOZAI_RIREKI_DATA[i1].KOMK_NO 		> pSOZAI_RIREKI_DATA[i1+1].KOMK_NO) ||
               (pSOZAI_RIREKI_DATA[i1].KOMK_SUB 	> pSOZAI_RIREKI_DATA[i1+1].KOMK_SUB))
      		{
         		strcpy(SOZAI_RIREKI_SWAP.SOKU_SU	,pSOZAI_RIREKI_DATA[i1].SOKU_SU);
         		strcpy(SOZAI_RIREKI_SWAP.KIKI_NO	,pSOZAI_RIREKI_DATA[i1].KIKI_NO);
         		strcpy(SOZAI_RIREKI_SWAP.KOMK_NO	,pSOZAI_RIREKI_DATA[i1].KOMK_NO);
         		strcpy(SOZAI_RIREKI_SWAP.KOMK_SUB	,pSOZAI_RIREKI_DATA[i1].KOMK_SUB);

         		strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_SU 	,pSOZAI_RIREKI_DATA[i1+1].SOKU_SU);
         		strcpy(pSOZAI_RIREKI_DATA[i1].KIKI_NO  	,pSOZAI_RIREKI_DATA[i1+1].KIKI_NO);
         		strcpy(pSOZAI_RIREKI_DATA[i1].KOMK_NO  	,pSOZAI_RIREKI_DATA[i1+1].KOMK_NO);
         		strcpy(pSOZAI_RIREKI_DATA[i1].KOMK_SUB	,pSOZAI_RIREKI_DATA[i1+1].KOMK_SUB);

         		strcpy(pSOZAI_RIREKI_DATA[i1+1].SOKU_SU		,SOZAI_RIREKI_SWAP.SOKU_SU);
         		strcpy(pSOZAI_RIREKI_DATA[i1+1].KIKI_NO		,SOZAI_RIREKI_SWAP.KIKI_NO);
         		strcpy(pSOZAI_RIREKI_DATA[i1+1].KOMK_NO		,SOZAI_RIREKI_SWAP.KOMK_NO);
         		strcpy(pSOZAI_RIREKI_DATA[i1+1].KOMK_SUB	,SOZAI_RIREKI_SWAP.KOMK_SUB);
      		}
    	}
    }

	int iSOZAI_OrCnt2,iSOZAI_SyukaCnt2;

/*
    // メモリの開放
    if( hSOZAI_OR_DATA ){
        GlobalUnlock( hSOZAI_OR_DATA );
        GlobalFree( hSOZAI_OR_DATA );
    }
*/
    // メモリの確保
    hSOZAI_OR_DATA = GlobalAlloc( GHND, sizeof(struct KSM02_DATA) * 100 );
    if( hSOZAI_OR_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pSOZAI_OR_DATA = (struct KSM02_DATA *)GlobalLock(hSOZAI_OR_DATA);
    if( hSOZAI_OR_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }

//現在の出荷用の項目と過去履歴の項目の最大数のORを別メモリ上へ格納
    Form1->iSOZAI_RireCnt 	= 0;
    iSOZAI_SyukaCnt2 	= 0;
    iSOZAI_OrCnt2 	= 0;
    while( 1 )
    {
        if( iSOZAI_SyukaCnt2 >= Form1->iSOZAI_OrCnt && Form1->iSOZAI_RireCnt >= iSOZAI_RIREKI_KOMKCNT2 ) break;
//項目がどちらが小さいかの重み付け
//出荷重み計算
        iSyukaWait = AnsiString(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_SyukaCnt].KIKI_NO).ToIntDef(0) * 1000
                    +AnsiString(pSOZAI_TEMPOR_DATA[Form1->iSOZAI_SyukaCnt].KOMK_NO).ToIntDef(0) * 100;

//履歴重み計算
        iRireWait =  AnsiString(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KIKI_NO).ToIntDef(0) * 1000
                    +AnsiString(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_NO).ToIntDef(0) * 100;

        if( iSOZAI_SyukaCnt2  >= Form1->iSOZAI_OrCnt ) 			iSyukaWait = 99999;
        if( Form1->iSOZAI_RireCnt   >= iSOZAI_RIREKI_KOMKCNT2 ) 	iRireWait = 99999;
        if( iSyukaWait < iRireWait )
        {
            strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KIKI_NO	,pSOZAI_TEMPOR_DATA[iSOZAI_SyukaCnt2].KIKI_NO);
            strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KOMK_NO	,pSOZAI_TEMPOR_DATA[iSOZAI_SyukaCnt2].KOMK_NO);
            strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KOMK_SUB	,pSOZAI_TEMPOR_DATA[iSOZAI_SyukaCnt2].KOMK_SUB);
            strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].SOKU_SU	,pSOZAI_TEMPOR_DATA[iSOZAI_SyukaCnt2].SOKU_SU);
            iSOZAI_SyukaCnt2 ++;
        }
        else if( iSyukaWait == iRireWait )
        {
        	if( AnsiString(pSOZAI_TEMPOR_DATA[iSOZAI_SyukaCnt2].KOMK_SUB).Trim() < AnsiString(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_SUB).Trim())
            {
            	strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KIKI_NO	,pSOZAI_SYUKA_DATA[iSOZAI_SyukaCnt2].KIKI_NO);
                strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KOMK_NO	,pSOZAI_SYUKA_DATA[iSOZAI_SyukaCnt2].KOMK_NO);
                strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KOMK_SUB	,pSOZAI_SYUKA_DATA[iSOZAI_SyukaCnt2].KOMK_SUB);
                strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].SOKU_SU	,pSOZAI_SYUKA_DATA[iSOZAI_SyukaCnt2].SOKU_SU);
                iSOZAI_SyukaCnt2 ++;
            }
            else if( AnsiString(pSOZAI_SYUKA_DATA[iSOZAI_SyukaCnt2].KOMK_SUB).Trim() == AnsiString(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_SUB).Trim())
            {
            	strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KIKI_NO	,pSOZAI_SYUKA_DATA[iSOZAI_SyukaCnt2].KIKI_NO);
                strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KOMK_NO	,pSOZAI_SYUKA_DATA[iSOZAI_SyukaCnt2].KOMK_NO);
                strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KOMK_SUB	,pSOZAI_SYUKA_DATA[iSOZAI_SyukaCnt2].KOMK_SUB);
                if( AnsiString(pSOZAI_TEMPOR_DATA[iSOZAI_SyukaCnt2].SOKU_SU).ToInt() >= AnsiString(pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].SOKU_SU).ToInt())
                {
                	strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].SOKU_SU,pSOZAI_SYUKA_DATA[iSOZAI_SyukaCnt2].SOKU_SU);
                }
                else
                {
                	strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].SOKU_SU,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].SOKU_SU);
                }
                iSOZAI_SyukaCnt2 ++;
                Form1->iSOZAI_RireCnt ++;
            }
            else
            {
            	strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KIKI_NO	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KIKI_NO);
                strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KOMK_NO	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_NO);
                strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KOMK_SUB	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_SUB);
                strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].SOKU_SU	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].SOKU_SU);
                Form1->iSOZAI_RireCnt ++;
            }
		}
        else
        {
            strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KIKI_NO	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KIKI_NO);
            strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KOMK_NO	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_NO);
            strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].KOMK_SUB	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].KOMK_SUB);
            strcpy(pSOZAI_OR_DATA[iSOZAI_OrCnt2].SOKU_SU	,pSOZAI_RIREKI_DATA[Form1->iSOZAI_RireCnt].SOKU_SU);
            Form1->iSOZAI_RireCnt ++;
        }
        iSOZAI_OrCnt2++;
    }
	Form1->iSOZAI_OrCnt = iSOZAI_OrCnt2;


// ---------------------------------------------------------
// メモリの開放
	if( hSOZAI_TEMPOR_DATA ){
        GlobalUnlock( hSOZAI_TEMPOR_DATA );
        GlobalFree( hSOZAI_TEMPOR_DATA );
    }
/*
	if( hSOZAI_RIREKI_DATA ){
        GlobalUnlock( hSOZAI_RIREKI_DATA );
        GlobalFree( hSOZAI_RIREKI_DATA );
    }
*/
//総ｎ数の算出
    Form1->iSOZAI_SokuCnt  = 0;
    for(i1=0;i1<Form1->iSOZAI_OrCnt;i1++)
    {
        Form1->iSOZAI_SokuCnt += AnsiString(pSOZAI_OR_DATA[i1].SOKU_SU).ToIntDef(0);
    }
//機器名称、項目名、規格、単位（最新のものを表示する）
    for(i1=0;i1<Form1->iSOZAI_OrCnt;i1++)
    {
	    sBuf = "SELECT * FROM KSM02";
	    sBuf += " WHERE DTKSHIN ='" + Form1->Cmb_DTKSHIN->Text + "'";
	    sBuf += " AND KIKI_NO = " + AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO) ;
	    sBuf += " AND KOMK_NO = " + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO) ;
        if(AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB).Length() != 0)
        {
	        sBuf += " AND KOMK_SUB ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB) + "'";
        }
        else
        {
	        sBuf += " AND KOMK_SUB IS NULL";
        }
        sBuf += " AND (SKB_NO = 1)";                        //出荷検査項目、材料証明項目

// Initial Query
	    Form1->Query3->Close();
	    Form1->Query3->SQL->Clear();
	    Form1->Query3->SQL->Add(sBuf);
	    Form1->Query3->Open();
	    Form1->Query3->Active = true;
        if( Form1->Query3->Eof == false )
        {
            sBuf   = Form1->Query3->FieldValues["KIKI_NM"];
            strcpy(pSOZAI_OR_DATA[i1].KIKI_NM		,sBuf.c_str());
            sBuf	= Form1->Query3->FieldValues["KOMK_NM"];
            strcpy(pSOZAI_OR_DATA[i1].KOMK_NM		,sBuf.c_str());
            sBuf      = Form1->Query3->FieldValues["TANI"];
            strcpy(pSOZAI_OR_DATA[i1].TANI			,sBuf.c_str());
            sBuf = Form1->Query3->FieldValues["KIKA_TYPE"];
            strcpy(pSOZAI_OR_DATA[i1].KIKA_TYPE		,sBuf.c_str());
            sBuf = Form1->Query3->FieldValues["KIKA_KIND"];
            strcpy(pSOZAI_OR_DATA[i1].KIKA_KIND		,sBuf.c_str());
            sBuf = Form1->Query3->FieldValues["KIKA_DECI"];
            strcpy(pSOZAI_OR_DATA[i1].KIKA_DECI		,sBuf.c_str());
            sBuf = Form1->Query3->FieldValues["KIKA_NUM1"];
            strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM1		,sBuf.c_str());
            sBuf = Form1->Query3->FieldValues["KIKA_NUM2"];
            strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM2		,sBuf.c_str());
            sBuf = Form1->Query3->FieldValues["KIKA_NUM3"];
            strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM3		,sBuf.c_str());
            sBuf  = Form1->Query3->FieldValues["KIKA_STR"];
            strcpy(pSOZAI_OR_DATA[i1].KIKA_STR		,sBuf.c_str());
            sBuf = Form1->Query3->FieldValues["KIKA_SUB1"];
            strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB1		,sBuf.c_str());
            sBuf = Form1->Query3->FieldValues["KIKA_SUB2"];
            strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB2		,sBuf.c_str());
            sBuf = Form1->Query3->FieldValues["KIKA_SUB3"];
            strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB3		,sBuf.c_str());
        }
        else
        {
	        sBuf = "SELECT * FROM KSD02";
	        sBuf += " WHERE DTKSHIN ='" + Form1->Cmb_DTKSHIN->Text + "'";
	        sBuf += " AND KIKI_NO = " + AnsiString(pSOZAI_OR_DATA[i1].KIKI_NO) ;
	        sBuf += " AND KOMK_NO = " + AnsiString(pSOZAI_OR_DATA[i1].KOMK_NO) ;
            if(AnsiString(pORDATA[i1].KOMK_SUB).Length() != 0)
            {
	            sBuf += " AND KOMK_SUB ='"  + AnsiString(pSOZAI_OR_DATA[i1].KOMK_SUB) + "'";
            }
            else
            {
	            sBuf += " AND KOMK_SUB IS NULL";
            }
            sBuf += " AND (SKB_NO = 1)";                        //出荷検査項目、材料証明項目
	        sBuf += " ORDER BY UPDYMD, UPDTIM DESC";

// Initial Query
	        Form1->Query3->Close();
	        Form1->Query3->SQL->Clear();
	        Form1->Query3->SQL->Add(sBuf);
	        Form1->Query3->Open();
	        Form1->Query3->Active = true;
            if( Form1->Query3->Eof == false )
            {
            	sBuf   = Form1->Query3->FieldValues["KIKI_NM"];
            	strcpy(pSOZAI_OR_DATA[i1].KIKI_NM		,sBuf.c_str());
            	sBuf	= Form1->Query3->FieldValues["KOMK_NM"];
            	strcpy(pSOZAI_OR_DATA[i1].KOMK_NM		,sBuf.c_str());
                sBuf      = Form1->Query3->FieldValues["TANI"];
                strcpy(pSOZAI_OR_DATA[i1].TANI			,sBuf.c_str());
                sBuf = Form1->Query3->FieldValues["KIKA_TYPE"];
                strcpy(pSOZAI_OR_DATA[i1].KIKA_TYPE		,sBuf.c_str());
                sBuf = Form1->Query3->FieldValues["KIKA_KIND"];
                strcpy(pSOZAI_OR_DATA[i1].KIKA_KIND		,sBuf.c_str());
                sBuf = Form1->Query3->FieldValues["KIKA_DECI"];
                strcpy(pSOZAI_OR_DATA[i1].KIKA_DECI		,sBuf.c_str());
                sBuf = Form1->Query3->FieldValues["KIKA_NUM1"];
                strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM1		,sBuf.c_str());
                sBuf = Form1->Query3->FieldValues["KIKA_NUM2"];
                strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM2		,sBuf.c_str());
                sBuf = Form1->Query3->FieldValues["KIKA_NUM3"];
                strcpy(pSOZAI_OR_DATA[i1].KIKA_NUM3		,sBuf.c_str());
                sBuf  = Form1->Query3->FieldValues["KIKA_STR"];
                strcpy(pSOZAI_OR_DATA[i1].KIKA_STR		,sBuf.c_str());
                sBuf = Form1->Query3->FieldValues["KIKA_SUB1"];
                strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB1		,sBuf.c_str());
                sBuf = Form1->Query3->FieldValues["KIKA_SUB2"];
                strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB2		,sBuf.c_str());
                sBuf = Form1->Query3->FieldValues["KIKA_SUB3"];
                strcpy(pSOZAI_OR_DATA[i1].KIKA_SUB3		,sBuf.c_str());
            }
        }
        Form1->Query3->Close();
    }
    Synchronize(Form1->Set_SOZAI);
	Form1->Query3->Tag =0;				//Query3開放

//素材の履歴は別に処理することに決めた 2003/03/26
#if 0
    // メモリの確保
    hSOZAI_RIREKI_DATA = GlobalAlloc( GHND, sizeof(struct KSD02_DATA) * 100 );
    if( hSOZAI_RIREKI_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pSOZAI_RIREKI_DATA = (struct KSD02_DATA *)GlobalLock(hSOZAI_RIREKI_DATA);
    if( hSOZAI_RIREKI_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }

    i1 = 0;
    i2 = 0;
   for( Form1->iSOZAI_RIREKI_KOMKCNT = 0 ; Form1->iSOZAI_RIREKI_KOMKCNT < iLOT_CNT ; Form1->iSOZAI_RIREKI_KOMKCNT++ )          //過去履歴が0件出なければ
    {
	    sBuf = "SELECT *  FROM KSD02";
	    sBuf += " WHERE DTKSHIN ='" + Form1->Cmb_DTKSHIN->Text + "'";
        sBuf += " AND SKB_NO = 1";                        //出荷検査項目、材料証明項目
        sBuf += " AND LOTNO IN (";
        sBuf += "'"+AnsiString(pSOZAI_RIREKI_LOT[Form1->iSOZAI_RIREKI_KOMKCNT].LOTNO)+"'" ;
        sBuf += " )";
	    sBuf += " ORDER BY KIKI_NO, KOMK_NO, KOMK_SUB";

	// Initial Query
	    Form1->Query3->Close();
	    Form1->Query3->SQL->Clear();
	    Form1->Query3->SQL->Add(sBuf);
	    Form1->Query3->Open();
	    Form1->Query3->Active = true;
//対象過去履歴の検索
        while( Form1->Query3->Eof == false )
        {
            sBuf    = Form1->Query3->FieldValues["DTKSHIN"];
            strcpy(pSOZAI_RIREKI_DATA[i1].DTKSHIN			,sBuf.c_str());
            sBuf      = Form1->Query3->FieldValues["LOTNO"];
            strcpy(pSOZAI_RIREKI_DATA[i1].LOTNO				,sBuf.c_str());
            sBuf  = Form1->Query3->FieldValues["HINBAN_SK"];
            strcpy(pSOZAI_RIREKI_DATA[i1].HINBAN_SK			,sBuf.c_str());
            sBuf    = Form1->Query3->FieldValues["KOMK_NO"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KOMK_NO			,sBuf.c_str());
            sBuf    = Form1->Query3->FieldValues["KOMK_NM"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KOMK_NM			,sBuf.c_str());
            sBuf = "";
            strcpy(pSOZAI_RIREKI_DATA[i1].KOMK_SUB			,sBuf.c_str());
            if ( VarIsNull(Form1->Query3->FieldValues["KOMK_SUB"]) != true
                && VarIsEmpty(Form1->Query3->FieldValues["KOMK_SUB"]) != true )
            {
                sBuf = Form1->Query3->FieldValues["KOMK_SUB"];
                strcpy(pSOZAI_RIREKI_DATA[i1].KOMK_SUB		,sBuf.c_str());
            }
            sBuf    = Form1->Query3->FieldValues["KIKI_NO"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKI_NO		,sBuf.c_str());
            sBuf    = Form1->Query3->FieldValues["KIKI_NM"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKI_NM    	,sBuf.c_str());
            sBuf       = Form1->Query3->FieldValues["TANI"];
            strcpy(pSOZAI_RIREKI_DATA[i1].TANI      	,sBuf.c_str());
            sBuf  = Form1->Query3->FieldValues["KIKA_TYPE"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKA_TYPE  	,sBuf.c_str());
            sBuf  = Form1->Query3->FieldValues["KIKA_KIND"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKA_KIND  	,sBuf.c_str());
            sBuf  = Form1->Query3->FieldValues["KIKA_DECI"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKA_DECI  	,sBuf.c_str());
            sBuf  = Form1->Query3->FieldValues["KIKA_NUM1"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKA_NUM1  	,sBuf.c_str());
            sBuf  = Form1->Query3->FieldValues["KIKA_NUM2"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKA_NUM2 	,sBuf.c_str());
            sBuf  = Form1->Query3->FieldValues["KIKA_NUM3"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKA_NUM3  	,sBuf.c_str());
            sBuf   = Form1->Query3->FieldValues["KIKA_STR"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKA_STR   	,sBuf.c_str());
            sBuf  = Form1->Query3->FieldValues["KIKA_SUB1"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKA_SUB1  	,sBuf.c_str());
            sBuf  = Form1->Query3->FieldValues["KIKA_SUB2"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKA_SUB2  	,sBuf.c_str());
            sBuf  = Form1->Query3->FieldValues["KIKA_SUB3"];
            strcpy(pSOZAI_RIREKI_DATA[i1].KIKA_SUB3 	,sBuf.c_str());
            sBuf    = Form1->Query3->FieldValues["SOKU_SU"];
            strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_SU    	,sBuf.c_str());
//Result Read ///////////////////////////////////////////////////////////////////////
            strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL01		,"0.0");
            if(VarIsNull(Form1->Query3->FieldValues["SOKU_VAL01"])!=true)
            {
                sBuf = Form1->Query3->FieldValues["SOKU_VAL01"];
                strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL01  	,sBuf.c_str());
            }
            strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL02 		,"0.0");
            if(VarIsNull(Form1->Query3->FieldValues["SOKU_VAL02"])!=true)
            {
                sBuf = Form1->Query3->FieldValues["SOKU_VAL02"];
                strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL02 	,sBuf.c_str());
            }
            strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL03		,"0.0");
            if(VarIsNull(Form1->Query3->FieldValues["SOKU_VAL03"])!=true)
            {
                sBuf = Form1->Query3->FieldValues["SOKU_VAL03"];
                strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL03 	,sBuf.c_str());
            }
            strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL04		,"0.0");
            if(VarIsNull(Form1->Query3->FieldValues["SOKU_VAL04"])!=true)
            {
                sBuf = Form1->Query3->FieldValues["SOKU_VAL04"];
                strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL04 	,sBuf.c_str());
            }
            strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL05		,"0.0");
            if(VarIsNull(Form1->Query3->FieldValues["SOKU_VAL05"])!=true)
            {
                sBuf = Form1->Query3->FieldValues["SOKU_VAL05"];
                strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL05 	,sBuf.c_str());
            }
            strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL06		,"0.0");
            if(VarIsNull(Form1->Query3->FieldValues["SOKU_VAL06"])!=true)
            {
                sBuf = Form1->Query3->FieldValues["SOKU_VAL06"];
                strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL06 	,sBuf.c_str());
            }
            strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL07		,"0.0");
            if(VarIsNull(Form1->Query3->FieldValues["SOKU_VAL07"])!=true)
            {
                sBuf = Form1->Query3->FieldValues["SOKU_VAL07"];
                strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL07 	,sBuf.c_str());
            }
            strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL08		,"0.0");
            if(VarIsNull(Form1->Query3->FieldValues["SOKU_VAL08"])!=true)
            {
                sBuf = Form1->Query3->FieldValues["SOKU_VAL08"];
                strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL08 	,sBuf.c_str());
            }
            strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL09		,"0.0");
            if(VarIsNull(Form1->Query3->FieldValues["SOKU_VAL09"])!=true)
            {
                sBuf = Form1->Query3->FieldValues["SOKU_VAL09"];
                strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL09 	,sBuf.c_str());
            }
            strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL10		,"0.0");
            if(VarIsNull(Form1->Query3->FieldValues["SOKU_VAL10"])!=true)
            {
                sBuf = Form1->Query3->FieldValues["SOKU_VAL10"];
                strcpy(pSOZAI_RIREKI_DATA[i1].SOKU_VAL10 	,sBuf.c_str());
            }
            i1 ++;
            Form1->Query3->Next();
        }
	    Form1->Query3->Close();
    }
    Form1->iSOZAI_RIREKI_KOMKCNT = i1;
#endif
}
//---------------------------------------------------------------------------



