//---------------------------------------------------------------------------
//
//  Thread.cpp
//    【出荷検査システム−出荷履歴読み取り】
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

#include "Thread.h"
#include "Tkss01.h"
#include "Unit1.h"
#pragma package(smart_init)

extern 	iContCnt;
// k.y 2003.05.17
//extern	HANDLE hORDATA;

// k.y 2003.05.17
//extern 	KSM02_DATA *pORDATA;
extern 	KSM02_DATA pORDATA[100];

// k.y 2003.05.17
//extern	HANDLE hRIREKI_DATA;
// k.y 2003.05.17
//extern	KSD02_DATA *pRIREKI_DATA;         // 過去履歴データ
extern	KSD02_DATA pRIREKI_DATA[100];

extern	HANDLE hCELLINFO_RIRE_SYUKA;
extern 	CELLINFO_DATA *pCELLINFO_RIRE_SYUKA;

extern HANDLE 		hRIRE_KSD01_DATA;
extern KSD01_DATA 	*pRIRE_KSD01_DATA;

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
/* k.k 2003.05.17 DELETE
__fastcall ThreadRIRE_SYUKA::ThreadRIRE_SYUKA(bool CreateSuspended)
	: TThread(CreateSuspended)
{
  Priority = tpIdle;
}
//---------------------------------------------------------------------------
//スレッド出荷履歴読み出し
void __fastcall ThreadRIRE_SYUKA::Execute()
{
//	Synchronize(GET_RIRE_SYUKA);
	GET_RIRE_SYUKA();
	if( Terminated ) return;
}
*/
//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：出荷履歴のデータ読み込み全般を行います。
//
//  機能説明
//    KSD02を参照しセルインフォに代入します。
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
void __fastcall TForm1::GET_RIRE_SYUKA(void)
{
    int i1,i2,i3,i4;
    AnsiString sBuf,sTempLot,sRIRE_LOT;
    int iRireCnt;
    //int iColCnt;
    //int iCol,iRow;
	double dMAX,dMIN;//,dSWAP;
	int iRowCount,iColCount;
    //int nDRAW_GRID;
    //int nKENSAKU_KEY,nGridX,nGridY;

    iRireCnt = 0;
	//iColCnt = 0;
	//iCol = 0;
	//iRow = 0;
	iRireCnt = Form1->iRIRE_CNT;
 	GET_KSD01();


    //iColCnt = i1;
	Form1->SGr_tRIRE		->ColCount	= iRireCnt;
    Form1->SGr_vRIRE_SYUKA	->ColCount 	= iRireCnt;
    Form1->SGr_vRIRE_SOZAI	->ColCount 	= iRireCnt;


//	履歴ロットの描画
	for( i1 = 0;i1 < Form1->iRIRE_CNT ; i1++)
	{
		Form1->SGr_tRIRE->Cells[i1][0] = Form1->sRIREKI_LOT->Strings[i1];
		Form1->SGr_tRIRE->Cells[i1][1] = Form1->sRIREKI_HIN->Strings[i1];
	}

//セル情報メモリ設定(出荷履歴）

	iRowCount = Form1->SGr_vRIRE_SYUKA->RowCount;
	iColCount = Form1->SGr_vRIRE_SYUKA->ColCount;


    //初期値代入
    //KOMK_NOに０を入れることで灰色表示を実現します。
	for(i1=0;i1 < iColCount ;i1++)
    {
    	dMAX = 0;
        dMIN = 0;
        i4 = 1;
        for(i2=0 ; i2 < Form1->iOrCount ; i2++)
        {
        	Form1->GetKIKAKU(i2, &dMAX, &dMIN);
            for(i3=0 ; i3 < AnsiString(pORDATA[i2].SOKU_SU).ToIntDef(0);i3++)
			{
	        	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].DTKSHIN 		, pORDATA[ i2 ].DTKSHIN);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].LOTNO 		, Form1->SGr_tRIRE->Cells[i1][0].c_str());
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].HINBAN 		, Form1->SGr_tRIRE->Cells[i1][1].c_str());
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].UNQ_NO 		, pORDATA[ i2 ].UNQ_NO);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].ORDER_NO		, pORDATA[ i2 ].ORDER_NO);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].SKB_NO 		, pORDATA[ i2 ].SKB_NO);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].HINBAN_SK	, pORDATA[ i2 ].HINBAN_SK);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KOMK_NO 		, AnsiString("-999").c_str());
        	    pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].INS_ON = false;
        		strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KOMK_NM 		, pORDATA[ i2 ].KOMK_NM);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KOMK_ENG		, pORDATA[ i2 ].KOMK_ENG);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KOMK_SUB		, pORDATA[ i2 ].KOMK_SUB);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KOMK_SUB_ENG , pORDATA[ i2 ].KOMK_SUB_ENG);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKI_NO 		, pORDATA[ i2 ].KIKI_NO);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKI_NM 		, pORDATA[ i2 ].KIKI_NM);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].TANI    		, pORDATA[ i2 ].TANI);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_TYPE	, pORDATA[ i2 ].KIKA_TYPE);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_KIND	, pORDATA[ i2 ].KIKA_KIND);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_DECI	, pORDATA[ i2 ].KIKA_DECI);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_NUM1	, pORDATA[ i2 ].KIKA_NUM1);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_NUM2	, pORDATA[ i2 ].KIKA_NUM2);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_NUM3	, pORDATA[ i2 ].KIKA_NUM3);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_STR		, pORDATA[ i2 ].KIKA_STR);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_SUB1	, pORDATA[ i2 ].KIKA_SUB1);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_SUB2	, pORDATA[ i2 ].KIKA_SUB2);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_SUB3	, pORDATA[ i2 ].KIKA_SUB3);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].SOKU_SU 		, pORDATA[ i2 ].SOKU_SU);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].SOKU_FLG		, pORDATA[ i2 ].SOKU_FLG);
        	    strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].TOKU_FLG		, pORDATA[ i2 ].TOKU_FLG);
            	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].KIKA_PRT		, pORDATA[ i2 ].KIKA_PRT);
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].VALUE_TYPE	, pORDATA[ i2 ].VALUE_TYPE);
    	        strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].VALUE_DECI	, pORDATA[ i2 ].VALUE_DECI);
				strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].RESULT,"");
	        	strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].DISP_RESULT,"");
    	    	pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].JUDGE = 2;
        	    pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].MAX = dMAX ;
            	pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].MIN = dMIN ;
        	    pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].GMAX = dMAX ;
            	pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].GMIN = dMIN ;
	            i4++;
			}
        }
    }


//履歴ロットの実績読み取り
	Form1->Set_RIRE_SYUKAJISSEKI();
	for(i1=0;i1 < iColCount ;i1++)
    {
    	dMAX = 0;
        dMIN = 0;
        i4 = 1;
        //指示ｎ数が最大件数とずれてきて後々不具合が生じるため、ORDATAで指示ｎ数を上書きします
        for(i2=0 ; i2 < Form1->iOrCount ; i2++)
        {
            for(i3=0 ; i3 < AnsiString(pORDATA[i2].SOKU_SU).ToIntDef(0);i3++)
			{
	            strcpy(pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i4].SOKU_SU 		, pORDATA[ i2 ].SOKU_SU);
	            i4++;
			}
        }
    }
    //データの読み込みが終了したのでデータをセル上に描画します。
	for( i1 = 0; i1 < iColCount ; i1++)
    {
		for(i2= 1; i2 <  iRowCount ; i2++)
        {
        	Form1->SGr_vRIRE_SYUKA->Cells[i1][i2] = pCELLINFO_RIRE_SYUKA[(i1 * iRowCount) + i2].RESULT;
		}
    }

//    Synchronize(Form1->Set_RIREMEMO);		//メモの表示
    Form1->Set_RIREMEMO();		//メモの表示
//    Synchronize(Form1->Get_KSD91_RIREKI);
    Form1->Get_KSD91_RIREKI();

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：測定実績データの読み込み。
//
//  機能説明
//    履歴ロットを参照し、KSD01を各ロットのメモリへ代入します
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
//履歴ロットの測定実績データを取得する
void __fastcall TForm1::GET_KSD01(void)
{
	int iCol;
	AnsiString sBuf,sLot,DTKSHIN;
    AnsiString sLot_Where;

	// メモリの開放
    if( hRIRE_KSD01_DATA ){
    	GlobalUnlock( hRIRE_KSD01_DATA );
        GlobalFree( hRIRE_KSD01_DATA );
    }

    hRIRE_KSD01_DATA = GlobalAlloc( GHND, sizeof(struct KSD01_DATA) * (Form1->iRIRE_CNT+1) );
    if( hRIRE_KSD01_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(履歴データ01)";
        Form1->SBr1->Update();
        Beep();
        return;
    }
    pRIRE_KSD01_DATA = (struct KSD01_DATA *)GlobalLock(hRIRE_KSD01_DATA);
    if( hRIRE_KSD01_DATA == NULL ){
        Form1->SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(履歴データ02)";
        Form1->SBr1->Update();
        Beep();
        return;
    }

    sLot = "";
    for(iCol=0;iCol < Form1->iRIRE_CNT ;iCol++ )
    {
        if(Form1->sRIREKI_LOT->Strings[iCol].Length()!=0)
        {
            sLot += "'" + Form1->sRIREKI_LOT->Strings[iCol] + "',";
        }
    }
	sLot = sLot.SubString(1,sLot.Length()-1);
	if( sLot.Length()<3 ) return;

    ///////////////////////////////////////////////////////////////onishi↓
    // ロット検索条件文字列
    sLot_Where = "";
    for(iCol=0;iCol < Form1->iRIRE_CNT ;iCol++ )
    {
        if(Form1->sRIREKI_LOT->Strings[iCol].Length()!=0)
        {
            sLot_Where += "( LOTNO='" + Form1->sRIREKI_LOT->Strings[iCol] + "' AND ";
            sLot_Where += " HINBAN='" + Form1->sRIREKI_HIN->Strings[iCol] + "') OR ";
        }
    }
    sLot_Where = sLot_Where.SubString(1,sLot_Where.Length()-3);
    ///////////////////////////////////////////////////////////////onishi↓

    sBuf = "SELECT * FROM KSD01 WHERE DTKSHIN = '" + Form1->sNowDTKSHIN + "'";
    //sBuf += " AND LOTNO IN (" + sLot + ")";
    sBuf += " AND (";
    sBuf += sLot_Where;
    sBuf += " )";
	sBuf += " ORDER BY LOTNO";

	// Initial Query
    Form1->Query2->Close();
    Form1->Query2->SQL->Clear();
    Form1->Query2->SQL->Add(sBuf);
    Form1->Query2->Open();
    Form1->Query2->Active = true;
	while(Form1->Query2->Eof == false)
	{
    	sBuf	= Form1->Query2->FieldValues["LOTNO"];
   		for(iCol=0;iCol < Form1->iRIRE_CNT ; iCol++)
		{
        	if( Form1->SGr_tRIRE->Cells[iCol][0]==sBuf) break;
		}
    //得意先品番
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN,sBuf.c_str());
		}
    //ロットNO
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO,sBuf.c_str());
		}
    //工管発行日 onishi
		if(VarIsNull(Form1->Query2->FieldValues["HINBAN"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["HINBAN"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].HINBAN,sBuf.c_str());
		}
    //素材用ロットNo1
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO1_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO1_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO1_SZ,sBuf.c_str());
		}
    //素材用ロットNo2
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO2_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO2_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO2_SZ,sBuf.c_str());
		}
    //素材用ロットNo3
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO3_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO3_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO3_SZ,sBuf.c_str());
		}
    //素材用ロットNo4
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO4_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO4_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO4_SZ,sBuf.c_str());
		}
    //素材用ロットNo5
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO5_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO5_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO5_SZ,sBuf.c_str());
		}
    //素材用ロットNo6
		if(VarIsNull(Form1->Query2->FieldValues["LOTNO6_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOTNO6_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].LOTNO6_SZ,sBuf.c_str());
		}
    //素材用自社品番1
		if(VarIsNull(Form1->Query2->FieldValues["HINBAN1_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["HINBAN1_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].HINBAN1_SZ,sBuf.c_str());
		}
    //素材用自社品番2
		if(VarIsNull(Form1->Query2->FieldValues["HINBAN2_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["HINBAN2_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].HINBAN2_SZ,sBuf.c_str());
		}
    //素材用自社品番3
		if(VarIsNull(Form1->Query2->FieldValues["HINBAN3_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["HINBAN3_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].HINBAN3_SZ,sBuf.c_str());
		}
    //素材用自社品番4
		if(VarIsNull(Form1->Query2->FieldValues["HINBAN4_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["HINBAN4_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].HINBAN4_SZ,sBuf.c_str());
		}
    //素材用自社品番5
		if(VarIsNull(Form1->Query2->FieldValues["HINBAN5_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["HINBAN5_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].HINBAN5_SZ,sBuf.c_str());
		}
    //素材用自社品番6
		if(VarIsNull(Form1->Query2->FieldValues["HINBAN6_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["HINBAN6_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].HINBAN6_SZ,sBuf.c_str());
		}
    //自社品番
		if(VarIsNull(Form1->Query2->FieldValues["HINBAN"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["HINBAN"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].HINBAN,sBuf.c_str());
		}
    //得意先コード
		if(VarIsNull(Form1->Query2->FieldValues["DTKSCOD"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSCOD"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSCOD,sBuf.c_str());
		}
    //得意先名称
		if(VarIsNull(Form1->Query2->FieldValues["DTKSNAM"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSNAM"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSNAM,sBuf.c_str());
		}
    //材質名称（品種）
		if(VarIsNull(Form1->Query2->FieldValues["ZISNAM"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["ZISNAM"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].ZISNAM,sBuf.c_str());
		}
    //品名
		if(VarIsNull(Form1->Query2->FieldValues["HINMEI"])!=true)
        {
    		sBuf	= Form1->Query2->FieldValues["HINMEI"];
	        strcpy(pRIRE_KSD01_DATA[iCol].HINMEI,sBuf.c_str());
		}
    //素材用得意先品番１
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN1_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN1_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN1_SZ,sBuf.c_str());
		}
    //素材用得意先品番２
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN2_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN2_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN2_SZ,sBuf.c_str());
		}
    //素材用得意先品番３
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN3_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN3_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN3_SZ,sBuf.c_str());
		}
    //素材用得意先品番４
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN4_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN4_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN4_SZ,sBuf.c_str());
		}
    //素材用得意先品番５
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN5_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["DTKSHIN5_SZ"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN5_SZ,sBuf.c_str());
		}
    //素材用得意先品番６
		if(VarIsNull(Form1->Query2->FieldValues["DTKSHIN6_SZ"])!=true)
        {
    		sBuf	= Form1->Query2->FieldValues["DTKSHIN6_SZ"];
	        strcpy(pRIRE_KSD01_DATA[iCol].DTKSHIN6_SZ,sBuf.c_str());
		}
    //素材用ロットのリンク
		if(VarIsNull(Form1->Query2->FieldValues["LOT_LINK_SZ"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["LOT_LINK_SZ"];
	        strcpy(pRIRE_KSD01_DATA[iCol].LOT_LINK_SZ,sBuf.c_str());
		}
    //測定項目数
		if(VarIsNull(Form1->Query2->FieldValues["SOKUTEI_NUM"])!=true)
        {
    		sBuf	= Form1->Query2->FieldValues["SOKUTEI_NUM"];
	        strcpy(pRIRE_KSD01_DATA[iCol].SOKUTEI_NUM,sBuf.c_str());
		}
    //素材判定
		if(VarIsNull(Form1->Query2->FieldValues["SOZAI_OK"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["SOZAI_OK"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK,sBuf.c_str());
		}
    //素材判定印刷用
		if(VarIsNull(Form1->Query2->FieldValues["SOZAI_OK_PRT"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["SOZAI_OK_PRT"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].SOZAI_OK_PRT,sBuf.c_str());
		}
    //出荷判定
		if(VarIsNull(Form1->Query2->FieldValues["SYUKA_OK"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["SYUKA_OK"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK,sBuf.c_str());
		}
    //出荷判定印刷用
		if(VarIsNull(Form1->Query2->FieldValues["SYUKA_OK_PRT"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["SYUKA_OK_PRT"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].SYUKA_OK_PRT,sBuf.c_str());
		}
    //成績書タイトル出力項目１
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE1"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE1"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE1,sBuf.c_str());
		}
    //成績書タイトル出力項目２
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE2"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE2"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE2,sBuf.c_str());
		}
    //成績書タイトル出力項目３
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE3"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE3"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE3,sBuf.c_str());
		}
    //成績書タイトル出力項目４
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE4"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE4"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE4,sBuf.c_str());
		}
    //成績書タイトル出力項目５
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE5"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE5"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE5,sBuf.c_str());
		}
    //成績書タイトル出力項目６
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE6"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE6"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE6,sBuf.c_str());
		}
    //成績書タイトル出力項目７
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE7"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE7"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE7,sBuf.c_str());
		}
    //成績書タイトル出力項目８
		if(VarIsNull(Form1->Query2->FieldValues["OUT_TITLE8"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["OUT_TITLE8"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].OUT_TITLE8,sBuf.c_str());
		}
    //Ｘバーの出力
		if(VarIsNull(Form1->Query2->FieldValues["X_OUT"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["X_OUT"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].X_OUT,sBuf.c_str());
		}
    //備考
		if(VarIsNull(Form1->Query2->FieldValues["MEMO"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["MEMO"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].MEMO,sBuf.c_str());
		}
    //測定中なら本日に日付を変更する
        if(AnsiString(pRIRE_KSD01_DATA[iCol].SOZAI_OK).ToIntDef(0) == -1 )
        {
            strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ,FormatDateTime("yyyymmdd",Date()).c_str());
            strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ_PRT,FormatDateTime("yyyymmdd",Date()).c_str());
        }
        else
        {
        //素材用測定日
	    	if(VarIsNull(Form1->Query2->FieldValues["SKTYMD_SZ"])!=true)
            {
	    	    sBuf	= Form1->Query2->FieldValues["SKTYMD_SZ"];
        	    strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ,sBuf.c_str());
	    	}
        //素材用測定日（印刷用）
	    	if(VarIsNull(Form1->Query2->FieldValues["SKTYMD_SZ_PRT"])!=true)
            {
	    	    sBuf	= Form1->Query2->FieldValues["SKTYMD_SZ_PRT"];
        	    strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_SZ_PRT,sBuf.c_str());
	    	}
        }
    //測定中なら本日に日付を変更する
        if(AnsiString(pRIRE_KSD01_DATA[iCol].SYUKA_OK).ToIntDef(0) == -1 )
        {
            strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD,FormatDateTime("yyyymmdd",Date()).c_str());
            strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_PRT,FormatDateTime("yyyymmdd",Date()).c_str());
        }
        else
        {
        //出荷用測定日
	    	if(VarIsNull(Form1->Query2->FieldValues["SKTYMD"])!=true)
            {
	    	    sBuf	= Form1->Query2->FieldValues["SKTYMD"];
        	    strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD,sBuf.c_str());
	    	}
        //出荷用測定日（印刷用）
	    	if(VarIsNull(Form1->Query2->FieldValues["SKTYMD_PRT"])!=true)
            {
	    	    sBuf	= Form1->Query2->FieldValues["SKTYMD_PRT"];
        	    strcpy(pRIRE_KSD01_DATA[iCol].SKTYMD_PRT,sBuf.c_str());
	    	}
        }
    //代表登録日
		if(VarIsNull(Form1->Query2->FieldValues["ADDYMD"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["ADDYMD"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].ADDYMD,sBuf.c_str());
		}
    //代表登録時間
		if(VarIsNull(Form1->Query2->FieldValues["ADDTIM"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["ADDTIM"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].ADDTIM,sBuf.c_str());
		}
    //代表変更日
		if(VarIsNull(Form1->Query2->FieldValues["UPDYMD"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["UPDYMD"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].UPDYMD,sBuf.c_str());
		}
    //代表変更時間
		if(VarIsNull(Form1->Query2->FieldValues["UPDTIM"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["UPDTIM"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].UPDTIM,sBuf.c_str());
		}
    //代表更新者
		if(VarIsNull(Form1->Query2->FieldValues["UPDCHR"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["UPDCHR"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].UPDCHR,sBuf.c_str());
		}
    //代表更新回数
		if(VarIsNull(Form1->Query2->FieldValues["UPDCNT"])!=true)
        {
	    	sBuf	= Form1->Query2->FieldValues["UPDCNT"];
    	    strcpy(pRIRE_KSD01_DATA[iCol].UPDCNT,sBuf.c_str());
		}
        pRIRE_KSD01_DATA[iCol].UPD_FLG = false;
        pRIRE_KSD01_DATA[iCol].SAVE_FLG = true;
//次のレコード
		Form1->Query2->Next();
	}
    Form1->Query2->Close();
}


