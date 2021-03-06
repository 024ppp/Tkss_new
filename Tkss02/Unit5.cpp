//---------------------------------------------------------------------------
//
//  Unit5.cpp
//    【出荷検査システム−レポート出力】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    高瀬　恵利
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit5.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：指定された範囲指定のロットNOの有効ロットNOを問い合わせます
//
//  機能説明
//    指定した開始ロットと終了ロットの測定済みロットリストを取得します。
//    月をまたぐロットの範囲指定に対応しています
//
//  パラメタ説明
//    AnsiString sDTKSHIN：代表得意先品番
//    AnsiString sLOT_S	：開始ロットNO
//    AnsiString sLOT_E	：終了ロットNO
//
//  戻り値
//    AnsiString		：カンマで区切られたロットNOリストの文字列をかえします
//                        ['LOTNO1','LOTNO2',]と戻ります
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetLotList2(AnsiString sDTKSHIN, AnsiString sLOT_S, AnsiString sLOT_E)
{
	AnsiString sBuf;
	AnsiString sRet;

	if( sLOT_S.Trim() == "" || sLOT_E.Trim() == "" ) return( "" );

	sBuf = "SELECT LOTBNG FROM SD21S";
	sBuf += " WHERE DTKSHIN = '" + sDTKSHIN + "'";

    if( iLOT_LENGTH == 5 ){
	    // 国内ロット（5桁）に対応
    	sBuf += " AND SUBSTR(LOTBNG,2) >= '" + sLOT_S.SubString(2,5) + "'";
	    sBuf += " AND SUBSTR(LOTBNG,2) <= '" + sLOT_E.SubString(2,5) + "'";
        sBuf += " AND DENYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	    sBuf += " ORDER BY SUBSTR(LOTBNG,2)";
	} else {
	    // 海外ロット（6桁）に対応
    	sBuf += " AND LOTBNG >= '" + sLOT_S + "'";
	    sBuf += " AND LOTBNG <= '" + sLOT_E + "'";
        sBuf += " AND DENYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	    sBuf += " ORDER BY LOTBNG";
	}

	// Initial Query
	Query3->Close();
	Query3->SQL->Clear();
	Query3->SQL->Add(sBuf);
	Query3->Open();
	Query3->Active = true;
        sRet = "";
	while(Query3->Eof == false) {

        if( !VarIsNull(Query3->FieldValues["LOTBNG"]) ){
            sRet += "'" + AnsiString(Query3->FieldValues["LOTBNG"]) + "',";
        }
	    Query3->Next();
	}
	Query3->Close();

	return( sRet );

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：以前のロットの値を取得する
//
//  機能説明
//	  以前 測定したロットの値を取得します
//    （ロットの項目が測定しないに設定してある場合に使用します）
//
//  パラメタ説明
//    AnsiString sSrchDTKSHIN		：検索条件（得意先品番）
//    AnsiString sSrchLOTNO		    ：検索条件（ロットNo）
//    AnsiString sSrchKOMK_NM		：検索条件（測定項目名称）
//    AnsiString sSrchKOMK_SUB		：検索条件（測定項目サブ名称）
//    AnsiString sSrchHINBAN_SK		：検索条件（品番）
//    int		 iSrchKIKI_NO		：検索条件（測定機器No）
//    int		 iSrchKOMK_NO		：検索条件（測定項目No）
//    AnsiString sSrchTANI          ：検索条件（単位）
//    AnsiString sReSOKU_SU         ：OUT引数  測定指示n数
//    AnsiString sReKIKA_PRT        ：OUT引数  上限下限値の印刷
//    AnsiString sReVALUE_TYPE      ：OUT引数  測定値表現
//    AnsiString sReVALUE_DECI      ：OUT引数  測定値小数点以下桁数
//    AnsiString sReDISP_VAL_SU     ：OUT引数  印刷用測定実績n数
//    AnsiString sReDISP_VAL_AVE    ：OUT引数  印刷用測定平均値
//    AnsiString sReDISP_VAL_MAX    ：OUT引数  印刷用測定最大値
//    AnsiString sReDISP_VAL_MIN    ：OUT引数  印刷用測定最小値
//    AnsiString sReDISP_OK         ：OUT引数  印刷用測定値判定
//    TStrings *sReDISP_VAL         ：OUT引数  測定項目
//
//  戻り値
//    int						    ：測定項目数（検索結果0件の場合は-1を戻します）
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
int  __fastcall TForm1::GetBeforeLotVal(AnsiString sSrchDTKSHIN, AnsiString sSrchLOTNO,
										AnsiString sSrchKOMK_NM, AnsiString sSrchKOMK_SUB,
										AnsiString sSrchHINBAN_SK, int iSrchKIKI_NO, int iSrchKOMK_NO,
                                        AnsiString sSrchTANI,
										AnsiString *sReSOKU_SU, AnsiString *sReKIKA_PRT,
										AnsiString *sReVALUE_TYPE,
										AnsiString *sReVALUE_DECI, AnsiString *sReDISP_VAL_SU,
										AnsiString *sReDISP_VAL_AVE, AnsiString *sReDISP_VAL_MAX,
										AnsiString *sReDISP_VAL_MIN, AnsiString *sReDISP_OK,
										TStrings *sReDISP_VAL )
{
	int iRtnVal;
    int iLotLen;
    int i;
    int n;
    AnsiString sBufSQL;
	AnsiString sBufSOKUVAL[10];

    iRtnVal = -1;
    iLotLen = sSrchLOTNO.Length();
	*sReVALUE_DECI = "0";
	*sReDISP_VAL_SU = "0";
	*sReDISP_VAL_AVE = "0";
	*sReDISP_VAL_MAX = "0";
	*sReDISP_VAL_MIN = "0";
	*sReDISP_OK = "0";
    sReDISP_VAL->Clear();

    //Q_BLOTVAL
    //KSD02からデータを取得
	sBufSQL = "SELECT * FROM KSD02";
    //検索条件 作成
	sBufSQL +=  " WHERE SKB_NO <> 9 AND SOKU_FLG = 1 ";
	sBufSQL += " AND DISP_VAL_SU > 0 ";
	sBufSQL += " AND DTKSHIN ='" + sSrchDTKSHIN + "'";
	//LOTNO
	if( iLotLen == 5 ){
		sBufSQL += " AND SUBSTR(LOTNO,2) <'" + sSrchLOTNO.SubString(2,5) + "'";
	} else {
		sBufSQL += " AND LOTNO <'" + sSrchLOTNO + "'";
	}
    //KOMK_NM
    if ( Trim(sSrchKOMK_NM) == "" ) {
		sBufSQL += " AND KOMK_NM Is Null ";
    } else {
		sBufSQL += " AND KOMK_NM ='"   + sSrchKOMK_NM + "'";
    }
    //KOMK_SUB
    if ( Trim(sSrchKOMK_SUB) == "" ) {
		sBufSQL += " AND KOMK_SUB Is Null ";
    } else {
		sBufSQL += " AND KOMK_SUB ='"  + sSrchKOMK_SUB + "'";
    }
    // 2003/10/21 A.TamuraここにTANIはいらないの？
    //TANI
    if ( Trim(sSrchTANI) == "" ) {
		sBufSQL += " AND TANI Is Null ";
    } else {
		sBufSQL += " AND TANI ='"  + sSrchTANI + "'";
    }

    //HINBAN_SK
    if ( Trim(sSrchHINBAN_SK) == "" ) {
		sBufSQL += " AND HINBAN_SK Is Null ";
    } else {
		sBufSQL += " AND HINBAN_SK ='"  + sSrchHINBAN_SK + "'";
    }
	sBufSQL += " AND KIKI_NO ="    + IntToStr(iSrchKIKI_NO);
	sBufSQL += " AND KOMK_NO ="    + IntToStr(iSrchKOMK_NO);

	//ソート
	if( iLotLen == 5 ){
		sBufSQL += " ORDER BY SUBSTR(LOTNO,2) DESC";
	} else {
		sBufSQL += " ORDER BY LOTNO DESC";
	}

	Q_BLOTVAL->Close();
	Q_BLOTVAL->SQL->Clear();
	Q_BLOTVAL->SQL->Add(sBufSQL);
	Q_BLOTVAL->Open();
	Q_BLOTVAL->Active = true;
    if ( Q_BLOTVAL->Eof == true ) {
        return(iRtnVal);
    }

    //2003/11/25 E.Takase 「atoi」はまちがい！
	//*sReSOKU_SU 	 = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["SOKU_SU"]).c_str()));
	//*sReKIKA_PRT 	 = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["KIKA_PRT"]).c_str()));
	//*sReVALUE_TYPE 	 = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["VALUE_TYPE"]).c_str()));
	//*sReVALUE_DECI 	 = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["VALUE_DECI"]).c_str()));
	//*sReDISP_VAL_SU  = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_SU"]).c_str()));
	//*sReDISP_VAL_AVE = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_AVE"]).c_str()));
	//*sReDISP_VAL_MAX = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_MAX"]).c_str()));
	//*sReDISP_VAL_MIN = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_MIN"]).c_str()));
	//*sReDISP_OK		 = AnsiString(atoi(Null_S(Q_BLOTVAL->FieldValues["DISP_OK"]).c_str()));
	*sReSOKU_SU 	 = AnsiString(Null_S(Q_BLOTVAL->FieldValues["SOKU_SU"]));
	*sReKIKA_PRT 	 = AnsiString(Null_S(Q_BLOTVAL->FieldValues["KIKA_PRT"]));
	*sReVALUE_TYPE 	 = AnsiString(Null_S(Q_BLOTVAL->FieldValues["VALUE_TYPE"]));
	*sReVALUE_DECI 	 = AnsiString(Null_S(Q_BLOTVAL->FieldValues["VALUE_DECI"]));
	*sReDISP_VAL_SU  = AnsiString(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_SU"]));
	*sReDISP_VAL_AVE = AnsiString(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_AVE"]));
	*sReDISP_VAL_MAX = AnsiString(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_MAX"]));
	*sReDISP_VAL_MIN = AnsiString(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_MIN"]));
	*sReDISP_OK		 = AnsiString(Null_S(Q_BLOTVAL->FieldValues["DISP_OK"]));

	//測定数,
	iRtnVal = atoi((Null_S(Q_BLOTVAL->FieldValues["DISP_VAL_SU"])).c_str());

	if ( iRtnVal > 10 ) {
		n = 10;
	} else {
		n = iRtnVal;
	}

	//測定値1,・・・・
	for ( i = 0; i < n; i++ ) {
        sReDISP_VAL->Add(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL" + FormatFloat("00",i+1)]));
	}

	//測定数が10〜なら例外テーブルから測定値取得
	if ( iRtnVal > 10 ) {
		sBufSQL = "SELECT * FROM KSD03";
		sBufSQL += " WHERE DTKSHIN ='" + Null_S(Q_BLOTVAL->FieldValues["DTKSHIN"]) + "'";
		sBufSQL += " AND LOTNO = '" + Null_S(Q_BLOTVAL->FieldValues["LOTNO"]) + "'";
		sBufSQL += " AND UNQ_NO = " + Null_S(Q_BLOTVAL->FieldValues["UNQ_NO"]);
		sBufSQL += " ORDER BY SOKU_NO";
		Q_BLOTVAL2->Close();
		Q_BLOTVAL2->SQL->Clear();
		Q_BLOTVAL2->SQL->Add(sBufSQL);
		Q_BLOTVAL2->Open();
		Q_BLOTVAL2->Active = true;
		while(Q_BLOTVAL2->Eof == false) {
        	sReDISP_VAL->Add(Null_S(Q_BLOTVAL->FieldValues["DISP_VAL"]));
			Q_BLOTVAL2->Next();
		}
	}

     return(iRtnVal);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：指定されたロットNOリストからワークテーブルを作成
//
//  機能説明
//    指定したロットNOリストを検索条件にしてワークテーブルにデータをセットします。
//
//  パラメタ説明
//    AnsiString sDTKSHIN：代表得意先品番
//    AnsiString sLOT	：ロットNOリスト（カンマ区切り）
//
//  戻り値
//    bool				：true=データ作成成功、false=データ作成失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSDCreateData(AnsiString sDTKSHIN, AnsiString sLOT)
{
	AnsiString sBufSQL;
	AnsiString sBufSQL2;
	bool bRet;
	int iCol;

   	bool bRtn;
    AnsiString sReDTKSHIN;
    AnsiString sReLOT;
    AnsiString sReSKB_NO;
    AnsiString sReKOMK_NO;
    AnsiString sReUNQ_NO;




    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    //�@ホスト名取得
	char tmpHostName[256];
	unsigned long CPUname_MaxLength = 256;
	if(GetComputerName( tmpHostName, &CPUname_MaxLength ) ){
		HostName = AnsiString(tmpHostName);
	}

    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//�Aワークテーブルを初期化
    //�A-1 KSD01W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// 問合せ文作成
	sBufSQL = "delete from KSD01W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// 問い合せ文の実行
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //─────────────────────────────────────
    //�A-2 KSD02W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// 問合せ文作成
	sBufSQL = "delete from KSD02W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// 問い合せ文の実行
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //─────────────────────────────────────
    //�A-3 KSD03W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// 問合せ文作成
	sBufSQL = "delete from KSD03W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// 問い合せ文の実行
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //ロットに検索条件にセットされていない時は終了
	if( sLOT.Trim() == "" ) return( false );

/*
    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//�Bワークテーブルを作成していきます
    //�B-1 まず、KSD01W〜KSD03Wまで必要なロットで枠組みを作る
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// 問合せ文作成
    sBufSQL = "";
	sBufSQL += " INSERT INTO KSD01W ( ";
	sBufSQL += " PCNAME, DTKSHIN, LOTNO ";
	sBufSQL += " ) ";
	sBufSQL += " SELECT '" + HostName + "' AS PCNAME, DTKSHIN, LOTNO ";
	sBufSQL += " FROM KSD01 ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND LOTNO IN (" + sLOT + ")";
	sBufSQL += " UNION ";
	sBufSQL += " SELECT '" + HostName + "' AS PCNAME, DTKSHIN, LOTNO ";
	sBufSQL += " FROM KSD21 ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND LOTNO IN (" + sLOT + ")";
	sBufSQL += " UNION ";
	sBufSQL += " SELECT '" + HostName + "' AS PCNAME, DTKSHIN, LOTBNG AS LOTNO ";
	sBufSQL += " FROM SD21S ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND LOTBNG IN (" + sLOT + ")";

	Q_WORK->SQL->Add(sBufSQL);
	// 問い合せ文の実行
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}


*/

    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//�B測定実績データ(KSD0シリーズ)ワークテーブルを作成していきます
    //�B-1 KSD01 → KSD01W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// 問合せ文作成
    sBufSQL = "";
	sBufSQL += " INSERT INTO KSD01W ( ";
	sBufSQL += " PCNAME, DTKSHIN, LOTNO, HINBAN, DTKSCOD, DTKSNAM, ZISNAM, HINMEI, ";
	sBufSQL += " DTKSHIN1_SZ, DTKSHIN2_SZ, DTKSHIN3_SZ, DTKSHIN4_SZ, DTKSHIN5_SZ, ";
	sBufSQL += " DTKSHIN6_SZ, LOT_LINK_SZ, SOKUTEI_NUM, SOZAI_OK, SOZAI_OK_PRT, SYUKA_OK, ";
	sBufSQL += " SYUKA_OK_PRT, OUT_TITLE1, OUT_TITLE2, OUT_TITLE3, OUT_TITLE4, OUT_TITLE5, ";
	sBufSQL += " OUT_TITLE6, OUT_TITLE7, OUT_TITLE8, X_OUT, MEMO, SKTYMD, SKTYMD_PRT, ";
	sBufSQL += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT, LOTNO1_SZ, LOTNO2_SZ, ";
	sBufSQL += " LOTNO3_SZ, LOTNO4_SZ, LOTNO5_SZ, LOTNO6_SZ, SKTYMD_SZ, SKTYMD_SZ_PRT ) ";

	sBufSQL += " SELECT '" + HostName + "' AS PCNAME, DTKSHIN, LOTNO, HINBAN,  ";
	sBufSQL += " DTKSCOD, DTKSNAM, ZISNAM, HINMEI, DTKSHIN1_SZ,  ";
	sBufSQL += " DTKSHIN2_SZ, DTKSHIN3_SZ, DTKSHIN4_SZ, DTKSHIN5_SZ,  ";
	sBufSQL += " DTKSHIN6_SZ, LOT_LINK_SZ, SOKUTEI_NUM, SOZAI_OK,  ";
	sBufSQL += " SOZAI_OK_PRT, SYUKA_OK, SYUKA_OK_PRT, OUT_TITLE1,  ";
	sBufSQL += " OUT_TITLE2, OUT_TITLE3, OUT_TITLE4, OUT_TITLE5,  ";
	sBufSQL += " OUT_TITLE6, OUT_TITLE7, OUT_TITLE8, X_OUT, MEMO,  ";
	sBufSQL += " SKTYMD, SKTYMD_PRT, ADDYMD, ADDTIM, UPDYMD, UPDTIM,  ";
	sBufSQL += " UPDCHR, UPDCNT, LOTNO1_SZ, LOTNO2_SZ, LOTNO3_SZ, LOTNO4_SZ,  ";
	sBufSQL += " LOTNO5_SZ, LOTNO6_SZ, SKTYMD_SZ, SKTYMD_SZ_PRT ";
	sBufSQL += " FROM KSD01 ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND   LOTNO IN (" + sLOT + ")";
    sBufSQL += " AND   SKTYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi

	Q_WORK->SQL->Add(sBufSQL);
	// 問い合せ文の実行
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}


    //─────────────────────────────────────
    //�B-2 KSD02 → KSD02W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// 問合せ文作成
    sBufSQL = "";
	sBufSQL += " INSERT INTO KSD02W ( ";
	sBufSQL += " PCNAME, DTKSHIN, LOTNO, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK, KOMK_NO, ";
	sBufSQL += " KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI, ";
	sBufSQL += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, ";
	sBufSQL += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, KIKA_SUB3, SOKU_SU, SOKU_FLG, TOKU_FLG, ";
	sBufSQL += " KIKA_PRT, VALUE_TYPE, VALUE_DECI, SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, ";
	sBufSQL += " SOKU_VAL04, SOKU_VAL05, SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, ";
	sBufSQL += " SOKU_VAL10, SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK, ";
	sBufSQL += " DISP_VAL01, DISP_VAL02, DISP_VAL03, DISP_VAL04, DISP_VAL05, DISP_VAL06, ";
	sBufSQL += " DISP_VAL07, DISP_VAL08, DISP_VAL09, DISP_VAL10, DISP_VAL_SU, DISP_VAL_AVE, ";
	sBufSQL += " DISP_VAL_MAX, DISP_VAL_MIN, DISP_OK, SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT ) ";
	sBufSQL += " SELECT '" + HostName + "'  AS PCNAME, DTKSHIN, LOTNO, UNQ_NO, ORDER_NO, SKB_NO, HINBAN_SK, ";
	sBufSQL += " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI, KIKA_TYPE, ";
	sBufSQL += " KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, KIKA_STR, KIKA_SUB1, KIKA_SUB2, ";
	sBufSQL += " KIKA_SUB3, SOKU_SU, SOKU_FLG, TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI, SOKU_VAL01, ";
	sBufSQL += " SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05, SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, ";
	sBufSQL += " SOKU_VAL09, SOKU_VAL10, SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK, ";
	sBufSQL += " DISP_VAL01, DISP_VAL02, DISP_VAL03, DISP_VAL04, DISP_VAL05, DISP_VAL06, DISP_VAL07, ";
	sBufSQL += " DISP_VAL08, DISP_VAL09, DISP_VAL10, DISP_VAL_SU, DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, ";
	sBufSQL += " DISP_OK, SKTYMD, ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT";
	sBufSQL += " FROM KSD02 ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND   LOTNO IN (" + sLOT + ")";
    sBufSQL += " AND   SKTYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi

	Q_WORK->SQL->Add(sBufSQL);
	// 問い合せ文の実行
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //─────────────────────────────────────
    //�B-3 KSD03 → KSD03W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// 問合せ文作成
    sBufSQL = "";
	sBufSQL += " INSERT INTO KSD03W ( ";
	sBufSQL += " PCNAME, DTKSHIN, LOTNO, UNQ_NO, SOKU_NO, SOKU_VAL, DISP_VAL, SKB_NO, KOMK_NO ) ";
	sBufSQL += " SELECT '" + HostName + "'  AS PCNAME, ";
	sBufSQL += " KSD03.DTKSHIN, KSD03.LOTNO, KSD03.UNQ_NO, KSD03.SOKU_NO, ";
    sBufSQL += " KSD03.SOKU_VAL, KSD03.DISP_VAL, ";
	sBufSQL += " KSD02.SKB_NO, KSD02.KOMK_NO ";
	sBufSQL += " FROM KSD03,KSD02 ";
	sBufSQL += " WHERE KSD03.DTKSHIN = KSD02.DTKSHIN ";
	sBufSQL += " AND KSD03.LOTNO = KSD02.LOTNO ";
	sBufSQL += " AND KSD03.UNQ_NO = KSD02.UNQ_NO ";
	sBufSQL += " AND KSD03.DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND KSD03.LOTNO IN (" + sLOT + ")";

	Q_WORK->SQL->Add(sBufSQL);
	// 問い合せ文の実行
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//�C素材データ(KSD2シリーズ)をワークテーブルへ追加します。
    //既に登録されている（測定実績テーブルにデータがある）場合は、何もしません
    //�C-1 KSD21 → KSD01W
    sBufSQL = "";
	sBufSQL += " SELECT * ";
	sBufSQL += " FROM KSD21 ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND   LOTNO IN (" + sLOT + ")";
    sBufSQL += " AND   SKTYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi
	Q_GetKSD21->Close();
	Q_GetKSD21->SQL->Clear();
	Q_GetKSD21->SQL->Add(sBufSQL);
	Q_GetKSD21->Open();
	Q_GetKSD21->Active = true;
    if ( Q_GetKSD21->Eof != true ) {
    	Q_GetKSD21->First();
    	//既にKSD01Wに登録されているかをチェックする
		while(Q_GetKSD21->Eof == false) {

            sReDTKSHIN = Null_S(Q_GetKSD21->FieldValues["DTKSHIN"]);
            sReLOT     = Null_S(Q_GetKSD21->FieldValues["LOTNO"]);

        	bRtn = KSD01WGetLot(sReDTKSHIN,sReLOT);

            if ( bRtn == false ) {
            	//KSD01Wに登録されていないので、追加します
				sBufSQL =  "";
				sBufSQL += " INSERT INTO KSD01W ( PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, HINBAN, DTKSCOD, ";
				sBufSQL += " DTKSNAM, ZISNAM, SOKUTEI_NUM, ";
				sBufSQL += " SOZAI_OK, SOZAI_OK_PRT, ";
				sBufSQL += " SYUKA_OK, SYUKA_OK_PRT, ";
				sBufSQL += " MEMO, ";
                //出荷検査はしていないので、出荷検査日は設定しない
				//sBufSQL += " SKTYMD, SKTYMD_PRT, ";
				sBufSQL += " SKTYMD_SZ, SKTYMD_SZ_PRT, ";
                //出荷検査はしていないので、更新者設定しない
				//sBufSQL += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT ) ";
				sBufSQL += " ADDYMD, ADDTIM, UPDYMD, UPDTIM,  UPDCNT ) ";

				sBufSQL += " SELECT '" + HostName + "' AS PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, HINBAN, DTKSCOD, ";
				sBufSQL += " DTKSNAM, ZISNAM, SOKUTEI_NUM, ";
				sBufSQL += " SOZAI_OK, SOZAI_OK As SOZAI_OK_PRT, ";
                //出荷検査はしていないので、合否は空白
				sBufSQL += " 2, 2, ";
				sBufSQL += " MEMO,";
                //出荷検査はしていないので、出荷検査日は設定しない
				//sBufSQL += " SKTYMD, SKTYMD As SKTYMD_PRT, ";
				sBufSQL += " SKTYMD As SKTYMD_SZ, SKTYMD As SKTYMD_SZ_PRT, ";
                //出荷検査はしていないので、更新者設定しない
				//sBufSQL += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT ";
				sBufSQL += " ADDYMD, ADDTIM, UPDYMD, UPDTIM,  UPDCNT ";
				sBufSQL += " FROM KSD21 ";
				sBufSQL += " WHERE DTKSHIN = '" + sReDTKSHIN + "'";
				sBufSQL += " AND LOTNO ='" + sReLOT + "'";

				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// 問い合せ文の実行
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}


			    //───────────────────────────────
    			//�C-2 KSD22 → KSD02W
    			sBufSQL = "";
				sBufSQL += " SELECT *  FROM KSM02,KSD22  ";
				sBufSQL += " WHERE KSD22.DTKSHIN = KSM02.DTKSHIN ";
				sBufSQL += " AND KSD22.KOMK_NO = KSM02.KOMK_NO ";
				sBufSQL += " AND KSM02.SKB_NO = 1 AND REVCNT = 0 ";
				sBufSQL += " AND KSD22.DTKSHIN = '" + sReDTKSHIN + "'";
				sBufSQL += " AND KSD22.LOTNO ='" + sReLOT + "'";
                sBufSQL += " AND KSD22.SKTYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi
				Q_GetKSD22->Close();
				Q_GetKSD22->SQL->Clear();
				Q_GetKSD22->SQL->Add(sBufSQL);
				Q_GetKSD22->Open();
				Q_GetKSD22->Active = true;


			    if ( Q_GetKSD22->Eof != true ) {
			    	Q_GetKSD22->First();
			    	//既にKSD02Wに登録されているかをチェックする
					while(Q_GetKSD22->Eof == false) {


			            sReSKB_NO  = "1";
			            sReKOMK_NO = Null_S(Q_GetKSD22->FieldValues["KOMK_NO"]);
		                sReUNQ_NO  = Null_S(Q_GetKSD22->FieldValues["UNQ_NO"]);
		         		bRtn = KSD02WGetLot(sReDTKSHIN,sReLOT,sReSKB_NO,sReKOMK_NO);

		            	if ( bRtn == false ) {
                            /*
		            		//KSD02Wに登録されていないので、追加します
							sBufSQL =  "";
							sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
							sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, SKB_NO, HINBAN_SK, ";
                            sBufSQL += " ORDER_NO, ";
							sBufSQL += " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB,  ";
							sBufSQL += " KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI,  ";
							sBufSQL += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1,  ";
							sBufSQL += " KIKA_NUM2, KIKA_NUM3, KIKA_STR, KIKA_SUB1,  ";
                            //2003.09.16 E.Takase
							//sBufSQL += " KIKA_SUB2, SOKU_SU, SOKU_FLG, TOKU_FLG,  ";
							sBufSQL += " KIKA_SUB2, SOKU_SU,  ";
							sBufSQL += " VALUE_TYPE, VALUE_DECI, SOKU_VAL01, SOKU_VAL02,  ";
							sBufSQL += " SOKU_VAL03, SOKU_VAL04, SOKU_VAL05, SOKU_VAL06,  ";
							sBufSQL += " SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,  ";
							sBufSQL += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN,  ";
							sBufSQL += " SOKU_OK, DISP_VAL01, DISP_VAL02, DISP_VAL03,  ";
							sBufSQL += " DISP_VAL04, DISP_VAL05, DISP_VAL06, DISP_VAL07,  ";
							sBufSQL += " DISP_VAL08, DISP_VAL09, DISP_VAL10, DISP_VAL_SU,  ";
							sBufSQL += " DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, ";
			                //出荷検査はしていないので、合否は空白
		                    sBufSQL += " DISP_OK,  ";
			                //検査はしていないので、検査日は設定しない
							//sBufSQL += " SKTYMD, ADDYMD, ADDTIM, UPDYMD,  ";
							sBufSQL += "  ADDYMD, ADDTIM, UPDYMD,  ";
			                //検査はしていないので、更新者は設定しない
							//sBufSQL += " UPDTIM, UPDCHR, UPDCNT )";
							sBufSQL += " UPDTIM,  UPDCNT, " ;
                            //2003.09.16 E.Takase
                            sBufSQL += "SOKU_FLG, TOKU_FLG, KIKA_PRT " ;
                            sBufSQL += " )";

							sBufSQL += " SELECT '" + HostName + "' AS PCNAME,  ";
							sBufSQL += " KSD22.DTKSHIN, KSD22.LOTNO, KSD22.UNQ_NO, 1 As SKB_NO, KSD22.DTKSHIN As HINBAN_SK, ";
                            sBufSQL += " KSD22.KOMK_NO As ORDER_NO, ";
							sBufSQL += " KSD22.KOMK_NO, KSD22.KOMK_NM, KSD22.KOMK_ENG, KSD22.KOMK_SUB, ";
							sBufSQL += " KSD22.KOMK_SUB_ENG, KSD22.KIKI_NO, KSD22.KIKI_NM, KSD22.TANI, ";
							sBufSQL += " KSD22.KIKA_TYPE, KSD22.KIKA_KIND, KSD22.KIKA_DECI, KSD22.KIKA_NUM1, ";
							sBufSQL += " KSD22.KIKA_NUM2, KSD22.KIKA_NUM3, KSD22.KIKA_STR, KSD22.KIKA_SUB1, ";
                            //2003.09.16 E.Takase
							//sBufSQL += " KIKA_SUB2, SOKU_SU, 1 As SOKU_FLG, 0 As TOKU_FLG, ";
							sBufSQL += " KSD22.KIKA_SUB2, KSD22.SOKU_SU,  ";
							sBufSQL += " KSD22.VALUE_TYPE, KSD22.VALUE_DECI, KSD22.SOKU_VAL01, KSD22.SOKU_VAL02, ";
							sBufSQL += " KSD22.SOKU_VAL03, KSD22.SOKU_VAL04, KSD22.SOKU_VAL05, KSD22.SOKU_VAL06, ";
							sBufSQL += " KSD22.SOKU_VAL07, KSD22.SOKU_VAL08, KSD22.SOKU_VAL09, KSD22.SOKU_VAL10, ";
							sBufSQL += " KSD22.SOKU_VAL_SU, KSD22.SOKU_VAL_AVE, KSD22.SOKU_VAL_MAX, ";
							sBufSQL += " KSD22.SOKU_VAL_MIN, KSD22.SOKU_OK, ";
							sBufSQL += " KSD22.SOKU_VAL01 As DISP_VAL01, KSD22.SOKU_VAL02 As DISP_VAL02, ";
							sBufSQL += " KSD22.SOKU_VAL03 As DISP_VAL03, KSD22.SOKU_VAL04 As DISP_VAL04, ";
							sBufSQL += " KSD22.SOKU_VAL05 As DISP_VAL05, KSD22.SOKU_VAL06 As DISP_VAL06, ";
							sBufSQL += " KSD22.SOKU_VAL07 As DISP_VAL07, KSD22.SOKU_VAL08 As DISP_VAL08, ";
							sBufSQL += " KSD22.SOKU_VAL09 As DISP_VAL09, KSD22.SOKU_VAL10 As DISP_VAL10, ";
							sBufSQL += " KSD22.SOKU_VAL_SU As DISP_VAL_SU, SOKU_VAL_AVE As DISP_VAL_AVE, ";
							sBufSQL += " KSD22.SOKU_VAL_MAX As DISP_VAL_MAX, KSD22.SOKU_VAL_MIN As DISP_VAL_MIN, ";
			                //出荷検査はしていないので、合否は空白
							sBufSQL += " 2, ";
			                //検査はしていないので、検査日は設定しない
							//sBufSQL += " SKTYMD, ADDYMD, ADDTIM, UPDYMD, ";
							sBufSQL += "  KSD22.ADDYMD, KSD22.ADDTIM, KSD22.UPDYMD, ";
			                //検査はしていないので、更新者は設定しない
							//sBufSQL += " UPDTIM, UPDCHR, UPDCNT ";
							sBufSQL += " KSD22.UPDTIM,  KSD22.UPDCNT, ";
                            //2003.09.16 E.Takase
                            sBufSQL += "KSM02.SOKU_FLG, KSM02.TOKU_FLG, KSM02.KIKA_PRT " ;

							sBufSQL += " FROM KSD22, KSM02 ";
							sBufSQL += " WHERE KSD22.DTKSHIN = KSM02.DTKSHIN ";
							sBufSQL += " AND KSD22.KOMK_NO = KSM02.KOMK_NO ";
							sBufSQL += " AND KSM02.SKB_NO = 1 AND REVCNT = 0 ";
							sBufSQL += " AND KSD22.DTKSHIN = '" + sReDTKSHIN + "'";
							sBufSQL += " AND KSD22.LOTNO ='" + sReLOT + "'";
							sBufSQL += " AND KSD22.KOMK_NO ='" + sReKOMK_NO + "'";

                            */

 		            		//KSD02Wに登録されていないので、追加します
							sBufSQL =  "";
							sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
							sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, SKB_NO, HINBAN_SK, ";
                            sBufSQL += " ORDER_NO, ";
							sBufSQL += " KOMK_NO, KOMK_NM, KOMK_ENG, KOMK_SUB,  ";
							sBufSQL += " KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI,  ";
							sBufSQL += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1,  ";
							sBufSQL += " KIKA_NUM2, KIKA_NUM3, KIKA_STR, KIKA_SUB1,  ";
                            //2003.09.16 E.Takase
							//sBufSQL += " KIKA_SUB2, SOKU_SU, SOKU_FLG, TOKU_FLG,  ";
							sBufSQL += " KIKA_SUB2, SOKU_SU,  ";
							sBufSQL += " VALUE_TYPE, VALUE_DECI, SOKU_VAL01, SOKU_VAL02,  ";
							sBufSQL += " SOKU_VAL03, SOKU_VAL04, SOKU_VAL05, SOKU_VAL06,  ";
							sBufSQL += " SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10,  ";
							sBufSQL += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN,  ";
							sBufSQL += " SOKU_OK, DISP_VAL01, DISP_VAL02, DISP_VAL03,  ";
							sBufSQL += " DISP_VAL04, DISP_VAL05, DISP_VAL06, DISP_VAL07,  ";
							sBufSQL += " DISP_VAL08, DISP_VAL09, DISP_VAL10, DISP_VAL_SU,  ";
							sBufSQL += " DISP_VAL_AVE, DISP_VAL_MAX, DISP_VAL_MIN, ";
			                //出荷検査はしていないので、合否は空白
		                    sBufSQL += " DISP_OK,  ";
			                //検査はしていないので、検査日は設定しない
							//sBufSQL += " SKTYMD, ADDYMD, ADDTIM, UPDYMD,  ";
							sBufSQL += "  ADDYMD, ADDTIM, UPDYMD,  ";
			                //検査はしていないので、更新者は設定しない
							//sBufSQL += " UPDTIM, UPDCHR, UPDCNT )";
							sBufSQL += " UPDTIM,  UPDCNT, " ;
                            //2003.09.16 E.Takase
                            sBufSQL += "SOKU_FLG, TOKU_FLG, KIKA_PRT " ;
                            sBufSQL += " )";
							sBufSQL += " values (" ;
							sBufSQL += " '" +  HostName 										+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["DTKSHIN"])) 		+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["LOTNO"])) 		+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["UNQ_NO"])) 		+ "' , ";
							sBufSQL +=         "1, ";
                            sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["HINBAN_SK"])) 	+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["ORDER_NO"])) 		+ "' , ";
							sBufSQL +=         Trim(Null_S(Q_GetKSD22->FieldValues["KOMK_NO"])) 		+ ", ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["KOMK_NM"])) 		+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["KOMK_ENG"]))		+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["KOMK_SUB"])) 		+ "' , ";
							sBufSQL += " '" +  Trim(Null_S(Q_GetKSD22->FieldValues["KOMK_SUB_ENG"])) 	+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKI_NO"]) 		+ ", ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["KIKI_NM"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["TANI"]) 			+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_TYPE"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_KIND"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_DECI"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_NUM1"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_NUM2"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_NUM3"]) 	+ ", ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["KIKA_STR"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["KIKA_SUB1"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["KIKA_SUB2"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_SU"]) 		+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["VALUE_TYPE"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["VALUE_DECI"]) 	+ ", ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL01"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL02"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL03"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL04"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL05"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL06"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL07"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL08"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL09"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL10"]) 	+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_SU"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_AVE"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_MAX"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_MIN"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_OK"]) 		+ ", ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL01"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL02"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL03"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL04"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL05"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL06"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL07"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL08"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL09"]) 	+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["SOKU_VAL10"]) 	+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_SU"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_AVE"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_MAX"]) 	+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_VAL_MIN"]) 	+ ", ";
							sBufSQL +=         "2, ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["ADDYMD"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["ADDTIM"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["UPDYMD"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["UPDTIM"]) 		+ "' , ";
							sBufSQL += " '" +  Null_S(Q_GetKSD22->FieldValues["UPDCNT"]) 		+ "' , ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["SOKU_FLG"]) 		+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["TOKU_FLG"]) 		+ ", ";
							sBufSQL +=         Null_S(Q_GetKSD22->FieldValues["KIKA_PRT"]) 		;
							sBufSQL += ")";

							// Initial Query
							Q_WORK->Close();
							Q_WORK->SQL->Clear();
							Q_WORK->SQL->Add(sBufSQL);
							// 問い合せ文の実行
							try
							{
								Q_WORK->ExecSQL();
							}
							catch(EDatabaseError& e)
							{
								ShowMessage(e.Message);
								return(false);
							}
							catch(Exception& e)
							{
								ShowMessage(e.Message);
								return(false);
							}

		                    //─────────────────────────────
		            		//�C-3KSD03Wにも登録されていないので、追加します
							sBufSQL =  "";
							sBufSQL += " INSERT INTO KSD03W ( PCNAME,  ";
							sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, ";
							sBufSQL += " SOKU_NO, SOKU_VAL, DISP_VAL, ";
							sBufSQL += " SKB_NO, KOMK_NO )";
							sBufSQL += " SELECT '" + HostName + "' AS PCNAME,  ";
							sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, ";
							sBufSQL += " SOKU_NO, SOKU_VAL, SOKU_VAL As DISP_VAL, ";
                            sBufSQL +=  sReSKB_NO + " AS SKB_NO," + sReKOMK_NO + " AS KOMK_NO ";
							sBufSQL += " FROM KSD23 ";
							sBufSQL += " WHERE DTKSHIN = '" + sReDTKSHIN + "'";
							sBufSQL += " AND LOTNO ='" + sReLOT + "'";
							sBufSQL += " AND UNQ_NO ='" + sReUNQ_NO + "'";

							// Initial Query
							Q_WORK->Close();
							Q_WORK->SQL->Clear();
							Q_WORK->SQL->Add(sBufSQL);
							// 問い合せ文の実行
							try
							{
								Q_WORK->ExecSQL();
							}
							catch(EDatabaseError& e)
							{
								ShowMessage(e.Message);
								return(false);
							}
							catch(Exception& e)
							{
								ShowMessage(e.Message);
								return(false);
							}

		                }

			            Q_GetKSD22->Next();
					}	
				}

            }

            Q_GetKSD21->Next();
        }

    }

    //2003.10.22 E.Takase
    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    //未測定のロットがあるかどうかを判断する
    //判断方法：検索条件のロット数とKSD02Wのロット数を比較
    //          検索条件のロット数が多いなら未測定のロットがあるとする
    //未測定のロットがあった場合�D〜の処理を行う
    int iSrchLOTNum;
    int iKSD02WLOTNum;

    //検索条件のロット数
    AnsiString Str = sLOT;  	// 対象文字列
    AnsiString From = ",";      // 検索文字列
    AnsiString To = "";         // 置換文字列
    AnsiString Result;          // 置換結果文字列
    Result = StringReplace( Str, From, To, TReplaceFlags() << rfReplaceAll << rfIgnoreCase );

    iSrchLOTNum = sLOT.Length() - Result.Length() + 1;

    //測定されているロットの個数
    sBufSQL = "";
	sBufSQL += " SELECT DISTINCT DTKSHIN, LOTNO FROM KSD02W  ";
	sBufSQL += " WHERE PCNAME='" + HostName + "'";
	Q_GetKSD22->Close();
	Q_GetKSD22->SQL->Clear();
	Q_GetKSD22->SQL->Add(sBufSQL);
	Q_GetKSD22->Open();
	Q_GetKSD22->Active = true;
	if ( Q_GetKSD22->Eof != true ) {
     	iKSD02WLOTNum = Q_GetKSD22->RecordCount;
    } else {
    	iKSD02WLOTNum = 0;
    }

    //検索条件のロット数とKSD02Wのロット数を比較
    if ( iSrchLOTNum == iKSD02WLOTNum ) {
		return(true);
	}


    //2003.09.16 E.Takase
    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    //�D未測定のロットをワークテーブルに追加します
    //ワークテーブルに追加されていないロットのみを追加します
    //�D-1 SD21S → KSD01W
    sBufSQL = "";
	sBufSQL += " SELECT * ";
	sBufSQL += " FROM SD21S ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND LOTBNG IN (" + sLOT + ")";
    sBufSQL += " AND DENYMD >= '" + Form1->Edt_SEIKAN_YMD->Text + "'";      //onishi

	Q_GetKSD21->Close();
	Q_GetKSD21->SQL->Clear();
	Q_GetKSD21->SQL->Add(sBufSQL);
	Q_GetKSD21->Open();
	Q_GetKSD21->Active = true;
    if ( Q_GetKSD21->Eof != true ) {
    	//既にKSD01Wに登録されているかをチェックする
		while(Q_GetKSD21->Eof == false) {

            sReDTKSHIN = Null_S(Q_GetKSD21->FieldValues["DTKSHIN"]);
            sReLOT     = Null_S(Q_GetKSD21->FieldValues["LOTBNG"]);

        	bRtn = KSD01WGetLot(sReDTKSHIN,sReLOT);

            if ( bRtn == false ) {
            	//KSD01Wに登録されていないので、追加します
				sBufSQL =  "";
				sBufSQL += " INSERT INTO KSD01W ( PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, ";
                //検査はしていないので、合否は空白
				sBufSQL += " SOZAI_OK, SOZAI_OK_PRT, ";
				sBufSQL += " SYUKA_OK, SYUKA_OK_PRT ";
                sBufSQL += "  ) ";

				sBufSQL += " values ( '" + HostName + "' ,  ";
				sBufSQL += " '" + sReDTKSHIN + "', ";
				sBufSQL += " '" + sReLOT + "' , ";
                //検査はしていないので、合否は空白
				sBufSQL += " 2, 2, 2, 2 ) ";

				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// 問い合せ文の実行
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}


            }
            Q_GetKSD21->Next();
        }
    }

    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//�E製品規格データ(KSM02)をワークテーブルへ追加します。
    //既に登録されている（測定実績・素材テーブルにデータがある）場合は、何もしません
    //�E-1 KSM02 →  KSD02W
    sBufSQL = "";
	sBufSQL += " SELECT *  from KSM02";
	sBufSQL += " where DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND REVCNT = 0 ";
	Q_GetKSM02->Close();
	Q_GetKSM02->SQL->Clear();
	Q_GetKSM02->SQL->Add(sBufSQL);
	Q_GetKSM02->Open();
	Q_GetKSM02->Active = true;
    if ( Q_GetKSM02->Eof != true ) {
    	//KSD01Wの各ロットに対して、測定項目を追加するか判断していく
	    sBufSQL = "";
		sBufSQL += " SELECT *  from KSD01W";
		sBufSQL += " where PCNAME = '" + HostName + "'";
		Q_GetKSD21->Close();
		Q_GetKSD21->SQL->Clear();
		Q_GetKSD21->SQL->Add(sBufSQL);
		Q_GetKSD21->Open();
		Q_GetKSD21->Active = true;
        if ( Q_GetKSD21->Eof != true ) {
        	while(Q_GetKSD21->Eof == false) {
	            sReDTKSHIN = Null_S(Q_GetKSD21->FieldValues["DTKSHIN"]);
	            sReLOT     = Null_S(Q_GetKSD21->FieldValues["LOTNO"]);
                Q_GetKSM02->First();
                while(Q_GetKSM02->Eof == false) {
                    //現在のロット＆測定項目のパターンがKSD02Wに存在するかをチェックし
                    //存在しなければ追加します。

		            sReSKB_NO  = Null_S(Q_GetKSM02->FieldValues["SKB_NO"]);
		            sReKOMK_NO = Null_S(Q_GetKSM02->FieldValues["KOMK_NO"]);
		         	bRtn = KSD02WGetLot(sReDTKSHIN,sReLOT,sReSKB_NO,sReKOMK_NO);

		            if ( bRtn == false ) {
                        sBufSQL  = "";
					   	sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
						sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, ";
						sBufSQL += " SKB_NO, HINBAN_SK, ORDER_NO, KOMK_NO, ";
						sBufSQL += " KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, ";
						sBufSQL += " KIKI_NO, KIKI_NM, TANI, KIKA_TYPE, KIKA_KIND, ";
						sBufSQL += " KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, ";
						sBufSQL += " KIKA_STR, KIKA_SUB1, KIKA_SUB2, SOKU_SU, ";
						sBufSQL += " VALUE_TYPE, VALUE_DECI, SOKU_OK, DISP_OK, DISP_VAL_SU, ";
						sBufSQL += " SOKU_FLG, TOKU_FLG, KIKA_PRT ";
                        sBufSQL += " )";
						sBufSQL += " values (" ;
						sBufSQL += " '" +  HostName 										+ "' , ";
						sBufSQL += " '" +  sReDTKSHIN 										+ "' , ";
						sBufSQL += " '" +  sReLOT 											+ "' , ";
						//sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["UNQ_NO"]) 		+ "' , ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_NO"])) 		+ "' , ";
						sBufSQL +=         Trim(Null_S(Q_GetKSM02->FieldValues["SKB_NO"])) 		+ ", ";
                        sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["HINBAN_SK"])) 	+ "' , ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["ORDER_NO"])) 		+ "' , ";
						sBufSQL +=         Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_NO"])) 		+ ", ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_NM"])) 		+ "' , ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_ENG"]))		+ "' , ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_SUB"])) 		+ "' , ";
						sBufSQL += " '" +  Trim(Null_S(Q_GetKSM02->FieldValues["KOMK_SUB_ENG"])) 	+ "' , ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKI_NO"]) 		+ ", ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["KIKI_NM"]) 		+ "' , ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["TANI"]) 			+ "' , ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_TYPE"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_KIND"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_DECI"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_NUM1"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_NUM2"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_NUM3"]) 	+ ", ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["KIKA_STR"]) 		+ "' , ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["KIKA_SUB1"]) 	+ "' , ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["KIKA_SUB2"]) 	+ "' , ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["SOKU_SU"]) 		+ "' , ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["VALUE_TYPE"]) 	+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["VALUE_DECI"]) 	+ ", ";
						sBufSQL +=         "2, ";
						sBufSQL +=         "2, ";
						sBufSQL += " '" +  Null_S(Q_GetKSM02->FieldValues["SOKU_SU"]) 		+ "' , ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["SOKU_FLG"]) 		+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["TOKU_FLG"]) 		+ ", ";
						sBufSQL +=         Null_S(Q_GetKSM02->FieldValues["KIKA_PRT"]) 		;
						sBufSQL += ")";

						// Initial Query
						Q_WORK->Close();
						Q_WORK->SQL->Clear();
						Q_WORK->SQL->Add(sBufSQL);
						// 問い合せ文の実行
						try
						{
							Q_WORK->ExecSQL();
						}
						catch(EDatabaseError& e)
						{
							ShowMessage(e.Message);
							return(false);
						}
						catch(Exception& e)
						{
							ShowMessage(e.Message);
							return(false);
						}

                    }

                	Q_GetKSM02->Next();
                }

            	Q_GetKSD21->Next();
            }
        }
    }


    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//�F製造手配データ(SD21S)をワークテーブルへ追加します。
    //既に登録されている（測定実績・素材・製品規格テーブルにデータがある）場合は、何もしません
    //�F-1 SD21S → KSD02W
    //実際はKSD01Wに登録されているロットがKSD02Wに登録されていなかった場合、ダミーデータを追加する
    sBufSQL = "";
	sBufSQL += " SELECT KSD01W.LOTNO ";
	sBufSQL += " FROM KSD01W, KSD02W ";
	sBufSQL += " where KSD02W.PCNAME(+) = KSD01W.PCNAME  ";
	sBufSQL += " AND KSD02W.DTKSHIN(+) = KSD01W.DTKSHIN  ";
	sBufSQL += " AND KSD02W.LOTNO(+) = KSD01W.LOTNO  ";
	sBufSQL += " AND KSD01W.PCNAME = '" + HostName + "'";
	sBufSQL += " AND KSD01W.DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND KSD02W.LOTNO IS NULL ";
	Q_GetKSD21->Close();
	Q_GetKSD21->SQL->Clear();
	Q_GetKSD21->SQL->Add(sBufSQL);
	Q_GetKSD21->Open();
	Q_GetKSD21->Active = true;
    if ( Q_GetKSD21->Eof != true ) {
	}

	//KSD02Wに登録されていないので、追加します
	sBufSQL =  "";
	sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
	sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, SKB_NO, HINBAN_SK, ";
	sBufSQL += " ORDER_NO, KOMK_NO, KOMK_NM, ";
	sBufSQL += " SOKU_SU, SOKU_FLG, DISP_VAL_SU, ";
	//検査はしていないので、合否は空白
	sBufSQL += " DISP_OK  ";
	sBufSQL += " ) ";

	sBufSQL += " SELECT '" + HostName + "' AS PCNAME,  ";

	sBufSQL += " KSD01W.DTKSHIN As DTKSHIN, KSD01W.LOTNO As LOTNO, ";
	sBufSQL += " 1 As UNQ_NO , 1 As SKB_NO ,  ";
	sBufSQL += " KSD01W.DTKSHIN As HINBAN_SK,  ";
	sBufSQL += " 9999 As ORDER_NO, 9999 As KOMK_NO , '-' As KOMK_NM,  ";
	sBufSQL += " 1 As SOKU_SU , 1 As SOKU_FLG, 1 As DISP_VAL_SU, ";
	sBufSQL += " 2 As DISP_OK ";
	sBufSQL += " FROM KSD01W, KSD02W ";
	sBufSQL += " where KSD02W.PCNAME(+) = KSD01W.PCNAME  ";
	sBufSQL += " AND KSD02W.DTKSHIN(+) = KSD01W.DTKSHIN  ";
	sBufSQL += " AND KSD02W.LOTNO(+) = KSD01W.LOTNO  ";
	sBufSQL += " AND KSD01W.PCNAME = '" + HostName + "'";
	sBufSQL += " AND KSD01W.DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND KSD02W.LOTNO IS NULL ";

	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	Q_WORK->SQL->Add(sBufSQL);
	// 問い合せ文の実行
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}


/*
    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//�D製品規格データ(KSM02)をワークテーブルへ追加します。
    //既に登録されている（測定実績・素材テーブルにデータがある）場合は、何もしません
    //�D-1 KSM02 →  KSD02W
    sBufSQL = "";
	sBufSQL += " SELECT DISTINCT  ";
	sBufSQL += "KSM02.DTKSHIN,SD21S.LOTBNG ";
	sBufSQL += "from KSM02, SD21S  ";
	sBufSQL += "where SD21S.DTKSHIN = KSM02.DTKSHIN  ";
	sBufSQL += " AND KSM02.DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND KSM02.REVCNT = 0 ";
	sBufSQL += " AND SD21S.LOTBNG IN (" + sLOT + ")";
	Q_GetKSD21->Close();
	Q_GetKSD21->SQL->Clear();
	Q_GetKSD21->SQL->Add(sBufSQL);
	Q_GetKSD21->Open();
	Q_GetKSD21->Active = true;
    if ( Q_GetKSD21->Eof != true ) {
    	//既にKSD01Wに登録されているかをチェックする
		while(Q_GetKSD21->Eof == false) {

            sReDTKSHIN = Null_S(Q_GetKSD21->FieldValues["DTKSHIN"]);
            sReLOT     = Null_S(Q_GetKSD21->FieldValues["LOTBNG"]);

        	bRtn = KSD01WGetLot(sReDTKSHIN,sReLOT);

            if ( bRtn == false ) {
            	//KSD01Wに登録されていないので、追加します
				sBufSQL =  "";
				sBufSQL += " INSERT INTO KSD01W ( PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, ";
                //検査はしていないので、合否は空白
				sBufSQL += " SOZAI_OK, SOZAI_OK_PRT, ";
				sBufSQL += " SYUKA_OK, SYUKA_OK_PRT ";
                sBufSQL += "  ) ";

				sBufSQL += " values ( '" + HostName + "' ,  ";
				sBufSQL += " '" + sReDTKSHIN + "', ";
				sBufSQL += " '" + sReLOT + "' , ";
                //検査はしていないので、合否は空白
				sBufSQL += " 2, 2, 2, 2 ) ";

				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// 問い合せ文の実行
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
            	//KSD02Wに登録されていないので、追加します
                sBufSQL = "";
				sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
				sBufSQL += " DTKSHIN,LOTNO,UNQ_NO,ORDER_NO, ";
				sBufSQL += " SKB_NO,HINBAN_SK,KOMK_NO,KOMK_NM, ";
				sBufSQL += " KOMK_ENG,KOMK_SUB,KOMK_SUB_ENG, ";
				sBufSQL += " KIKI_NO,KIKI_NM,TANI,KIKA_TYPE, ";
				sBufSQL += " KIKA_KIND,KIKA_DECI,KIKA_NUM1, ";
				sBufSQL += " KIKA_NUM2,KIKA_NUM3,KIKA_STR, ";
				sBufSQL += " KIKA_SUB1,KIKA_SUB2,KIKA_SUB3, ";
				sBufSQL += " SOKU_SU,SOKU_FLG,TOKU_FLG, ";
				sBufSQL += " KIKA_PRT,VALUE_TYPE,VALUE_DECI, ";
				sBufSQL += " DISP_OK, DISP_VAL_SU  ";
				sBufSQL += "  )";

				sBufSQL += " SELECT '" + HostName + "' AS PCNAME,  ";

				sBufSQL += " DTKSHIN, '" + sReLOT + "' As LOTNO,UNQ_NO,ORDER_NO, ";
				sBufSQL += " SKB_NO,HINBAN_SK,KOMK_NO,KOMK_NM, ";
				sBufSQL += " KOMK_ENG,KOMK_SUB,KOMK_SUB_ENG, ";
				sBufSQL += " KIKI_NO,KIKI_NM,TANI,KIKA_TYPE, ";
				sBufSQL += " KIKA_KIND,KIKA_DECI,KIKA_NUM1, ";
				sBufSQL += " KIKA_NUM2,KIKA_NUM3,KIKA_STR, ";
				sBufSQL += " KIKA_SUB1,KIKA_SUB2,KIKA_SUB3, ";
				sBufSQL += " SOKU_SU,SOKU_FLG,TOKU_FLG, ";
				sBufSQL += " KIKA_PRT,VALUE_TYPE,VALUE_DECI, ";
				sBufSQL += " 2 As DISP_OK , SOKU_SU As DISP_VAL_SU ";
                //検査はしていないので、合否は空白
				sBufSQL += " FROM KSM02 ";
				sBufSQL += " WHERE DTKSHIN = '" + sReDTKSHIN + "'";
                sBufSQL += " AND REVCNT = 0";


				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// 問い合せ文の実行
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}

            }



        	Q_GetKSD21->Next();
        }
    }
    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//�E製造手配データ(SD21S)をワークテーブルへ追加します。
    //既に登録されている（測定実績・素材・製品規格テーブルにデータがある）場合は、何もしません
    //�E-1 SD21S → KSD01W , KSD02W
    sBufSQL = "";
	sBufSQL += " SELECT * ";
	sBufSQL += " FROM SD21S ";
	sBufSQL += " WHERE DTKSHIN = '" + sDTKSHIN + "'";
	sBufSQL += " AND LOTBNG IN (" + sLOT + ")";
	Q_GetKSD21->Close();
	Q_GetKSD21->SQL->Clear();
	Q_GetKSD21->SQL->Add(sBufSQL);
	Q_GetKSD21->Open();
	Q_GetKSD21->Active = true;
    if ( Q_GetKSD21->Eof != true ) {
    	//既にKSD01Wに登録されているかをチェックする
		while(Q_GetKSD21->Eof == false) {

            sReDTKSHIN = Null_S(Q_GetKSD21->FieldValues["DTKSHIN"]);
            sReLOT     = Null_S(Q_GetKSD21->FieldValues["LOTBNG"]);

        	bRtn = KSD01WGetLot(sReDTKSHIN,sReLOT);

            if ( bRtn == false ) {
            	//KSD01Wに登録されていないので、追加します
				sBufSQL =  "";
				sBufSQL += " INSERT INTO KSD01W ( PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, ";
                //検査はしていないので、合否は空白
				sBufSQL += " SOZAI_OK, SOZAI_OK_PRT, ";
				sBufSQL += " SYUKA_OK, SYUKA_OK_PRT ";
                sBufSQL += "  ) ";

				sBufSQL += " values ( '" + HostName + "' ,  ";
				sBufSQL += " '" + sReDTKSHIN + "', ";
				sBufSQL += " '" + sReLOT + "' , ";
                //検査はしていないので、合否は空白
				sBufSQL += " 2, 2, 2, 2 ) ";

				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// 問い合せ文の実行
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}


            	//KSD02Wに登録されていないので、追加します
				sBufSQL =  "";
				sBufSQL += " INSERT INTO KSD02W ( PCNAME,  ";
				sBufSQL += " DTKSHIN, LOTNO, UNQ_NO, SKB_NO, HINBAN_SK, ";
				sBufSQL += " ORDER_NO, KOMK_NO, KOMK_NM, ";
				sBufSQL += " SOKU_SU, SOKU_FLG, DISP_VAL_SU, ";
                //検査はしていないので、合否は空白
                sBufSQL += " DISP_OK  ";
				sBufSQL += " ) ";

				sBufSQL += " values ( '" + HostName + "' ,  ";
				sBufSQL += " '" + sReDTKSHIN + "', ";
				sBufSQL += " '" + sReLOT + "',  ";
				sBufSQL += " 1, 1,  ";
				sBufSQL += " '" + sReDTKSHIN + "',  ";
				sBufSQL += " 9999,9999, '-',  ";
				sBufSQL += " 1, 1, 1, ";
                sBufSQL += " 2 ";
                //検査はしていないので、合否は空白
				sBufSQL += ")  ";

				// Initial Query
				Q_WORK->Close();
				Q_WORK->SQL->Clear();
				Q_WORK->SQL->Add(sBufSQL);
				// 問い合せ文の実行
				try
				{
					Q_WORK->ExecSQL();
				}
				catch(EDatabaseError& e)
				{
					ShowMessage(e.Message);
					return(false);
				}
				catch(Exception& e)
				{
					ShowMessage(e.Message);
					return(false);
				}


            }
            Q_GetKSD21->Next();
        }
    }

*/
	return( true );
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：ワークテーブルを初期化
//
//  機能説明
//    ホスト名をキーにしてワークテーブルを初期化します。
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    bool				：true=テーブル初期化成功、false=テーブル初期化失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSDDeleteData(void)
{
	AnsiString sBufSQL;
	AnsiString sBufSQL2;
	bool bRet;
	int iCol;

   	bool bRtn;


    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    //�@ホスト名取得
	char tmpHostName[256];
	unsigned long CPUname_MaxLength = 256;
	if(GetComputerName( tmpHostName, &CPUname_MaxLength ) ){
		HostName = AnsiString(tmpHostName);
	}

    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//�Aワークテーブルを初期化
    //�A-1 KSD01W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// 問合せ文作成
	sBufSQL = "delete from KSD01W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// 問い合せ文の実行
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //─────────────────────────────────────
    //�A-2 KSD02W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// 問合せ文作成
	sBufSQL = "delete from KSD02W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// 問い合せ文の実行
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

    //─────────────────────────────────────
    //�A-3 KSD03W
	// Initial Query
	Q_WORK->Close();
	Q_WORK->SQL->Clear();
	// 問合せ文作成
	sBufSQL = "delete from KSD03W where PCNAME='" + HostName + "'";
	Q_WORK->SQL->Add(sBufSQL);

	// 問い合せ文の実行
	try
	{
		Q_WORK->ExecSQL();
	}
	catch(EDatabaseError& e)
	{
		ShowMessage(e.Message);
		return(false);
	}
	catch(Exception& e)
	{
		ShowMessage(e.Message);
		return(false);
	}

	return( true );
}


//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：指定されたロットNOが存在するか問い合わせます
//
//  機能説明
//    指定したロットNOがワークテーブル（KSD01W）に存在するかどうかを取得します。
//
//  パラメタ説明
//    AnsiString sDTKSHIN：代表得意先品番
//    AnsiString sLOT	：ロットNO
//
//  戻り値
//    bool				：true=対象ロットあり、false=対象ロットなし
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSD01WGetLot(AnsiString sDTKSHIN, AnsiString sLOT)
{
	AnsiString sBuf;

	sBuf = "SELECT * FROM KSD01W";
	sBuf += " WHERE PCNAME = '" + HostName + "'";
	sBuf += " AND DTKSHIN = '" + sDTKSHIN + "'";
	sBuf += " AND LOTNO = '" + sLOT + "'";

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;
    if ( Query1->Eof != true ) {
    	//既にKSD01Wに登録されている
		return( true );
    } else {
		return( false );
    }

}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：指定されたロットNOの測定項目が存在するか問い合わせます
//
//  機能説明
//    指定したロットNOの測定項目がワークテーブル（KSD02W）に存在するかどうかを取得します。
//
//  パラメタ説明
//    AnsiString sDTKSHIN：代表得意先品番
//    AnsiString sLOT	 ：ロットNO
//    AnsiString sSKB_NO ：識別NO
//    AnsiString sKOMK_NO：測定項目NO
//
//  戻り値
//    bool				：true=対象ロットあり、false=対象ロットなし
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSD02WGetLot(AnsiString sDTKSHIN, AnsiString sLOT,AnsiString sSKB_NO,AnsiString sKOMK_NO)
{
	AnsiString sBuf;

	sBuf = "SELECT * FROM KSD02W";
	sBuf += " WHERE PCNAME = '" + HostName + "'";
	sBuf += " AND DTKSHIN = '"  + sDTKSHIN + "'";
	sBuf += " AND LOTNO = '"    + sLOT + "'";
	sBuf += " AND SKB_NO = '"   + sSKB_NO + "'";
	sBuf += " AND KOMK_NO = '"  + sKOMK_NO + "'";

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;
    if ( Query1->Eof != true ) {
    	//既にKSD02Wに登録されている
		return( true );
    } else {
		return( false );
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：指定されたロットNOリストの有効ロットNOを問い合わせます
//
//  機能説明
//    指定したロットNOリストが測定済みロットかどうかを取得します。
//
//  パラメタ説明
//    AnsiString sDTKSHIN：代表得意先品番
//    AnsiString sLOT	：ロットNOリスト（カンマ区切り）
//    (OUT)
//    StringList sLots	：有効なロットNOリスト（StringList）
//
//  戻り値
//    bool				：true=対象ロットあり、false=対象ロットなし
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSD01GetLot2(AnsiString sDTKSHIN, AnsiString sLOT)
{
	AnsiString sBuf;
	bool bRet;
	int iCol;

	if( sLOT.Trim() == "" ) return( false );


	iCol = 0;
	sBuf = "SELECT * FROM KSD01W";
    sBuf += " WHERE PCNAME='" + HostName + "'" ;
	sBuf += " AND DTKSHIN = '" + sDTKSHIN + "'";
	sBuf += " AND SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi

	sBuf += " AND LOTNO IN (" + sLOT + ")";
    if( iLOT_LENGTH == 5 ){
		sBuf += " ORDER BY SUBSTR(LOTNO,2)";
    } else {
		sBuf += " ORDER BY LOTNO";
    }

    bRet = false;
    sLots->Clear();
    sHins->Clear();

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;
	while(Query1->Eof == false) {

        if( iCol >= 99 ){                                                     //onishi99
			MessageDlg("一度に扱えるロット数(最大99件)を超えました。\n以降のロットは対象外になります。",
            			mtWarning, TMsgDlgButtons() << mbOK , 0);
        	break;
        }

        if( !VarIsNull(Query1->FieldValues["LOTNO"]) ){
        	sLots->Add( AnsiString(Query1->FieldValues["LOTNO"]) );
        	sHins->Add( AnsiString(Query1->FieldValues["HINBAN"]) );
        }

		Query1->Next();
		iCol++;
	}

	if( iCol > 0 ) bRet = true;

	return( bRet );
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：有効な測定項目の検索
//
//  機能説明
//    指定した品番・ロット・検索条件から有効な測定項目をKSD02データから取得し
//    検査項目にチェックを付けます
//
//  パラメタ説明
//    AnsiString sDTKSHIN：代表得意先品番
//    AnsiString sLOT	：ロットNOリスト（カンマ区切り）
//    bool		iSEL_SZ	：素材検査項目の出力（true=する/false=しない）
//    bool		iSEL_SK	：出荷検査項目の出力（true=する/false=しない）
//    bool		iSEL_TK	：特別出力項目の出力（true=する/false=しない）
//    bool		iSEL_ZR	：材料証明項目の出力（true=する/false=しない）
//
//  戻り値
//    bool				：true=検索成功、false=検索失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::KSD02GetKOMOKU2(AnsiString sDTKSHIN, AnsiString sLOT,
                             bool iSEL_SZ, bool iSEL_SK, int iSEL_TK, bool iSEL_ZR)
{
	int				i, k, iCol;
	bool			bRet;
	AnsiString		sBuf;
    int				iSKB_NO;
    int				iTOKU_FLG;
    TCheckListBox*	clb;


	iCol = 0;
	sBuf = "SELECT * FROM KSD02W";
    sBuf += " WHERE PCNAME='" + HostName + "'" ;
	sBuf += " AND DTKSHIN = '" + sDTKSHIN + "'";
	sBuf += " AND SKTYMD >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
	sBuf += " AND LOTNO IN (" + sLOT + ")";
	sBuf += " ORDER BY ORDER_NO";
	//sBuf += " ORDER BY SUBSTR(LOTNO,2), ORDER_NO";

    bRet = false;


	if( PgCtr_REPORT->ActivePage->Name == "TabSheet1" ){
        // 検査成績書
    	clb = dynamic_cast<TCheckListBox*>(Clb1_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet2" ){
        // 検査成績書（月別）
    	clb = dynamic_cast<TCheckListBox*>(Clb2_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet3" ){
        // 材料証明書
    	clb = dynamic_cast<TCheckListBox*>(Clb3_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet4" ){
        // 材料証明書（月別）
    	clb = dynamic_cast<TCheckListBox*>(Clb4_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet5" ){
        // 検査結果時系列管理表
    	clb = dynamic_cast<TCheckListBox*>(Clb5_CHK_KOUMOKU);
    }
    else if( PgCtr_REPORT->ActivePage->Name == "TabSheet6" ){
        // 検査経歴票
    	clb = dynamic_cast<TCheckListBox*>(Clb6_CHK_KOUMOKU);
    }

    clb->Clear();

	// Initial Query
	Query2->Close();
	Query2->SQL->Clear();
	Query2->SQL->Add(sBuf);
	Query2->Open();
	Query2->Active = true;
	while(Query2->Eof == false) {

        // 測定項目として出力します。
        iSKB_NO = AnsiString(Query2->FieldValues["SKB_NO"]).ToIntDef(9);
        if( iSKB_NO != 9 ){
            sBuf = "";
        	if( !VarIsNull(Query2->FieldValues["KOMK_NM"]) ){
        		sBuf = Query2->FieldValues["KOMK_NM"];
            }
        	if( !VarIsNull(Query2->FieldValues["KOMK_SUB"]) ){
        		sBuf = sBuf + " " + Query2->FieldValues["KOMK_SUB"];
            }
            // 2003/10/21 A.Tamura ここに[TANI]は必要か？
        	if( !VarIsNull(Query2->FieldValues["TANI"]) ){
        		sBuf = sBuf + " " + Query2->FieldValues["TANI"];
            }
            if( sBuf != "" ){

		        iTOKU_FLG = AnsiString(Query2->FieldValues["TOKU_FLG"]).ToIntDef(0);

                // 未登録の測定項目が有った場合だけ、追加します
                k = 0;
				for( i = 0; i < clb->Items->Count; i++){
					if( clb->Items->Strings[i] == sBuf ){
						k = 1;
                        break;
                    }
                }
                if( k == 0 ){

                	// 新しい測定項目を追加します
			        clb->Items->Add(sBuf);

                	// 素材検査項目で素材検査項目を選択する時はチェックON
                    if( iSKB_NO == 1 ){
                    	if( iSEL_SZ == true ){
							clb->Checked[clb->Items->Count-1] = true;
                    	} else {
                        	clb->Checked[clb->Items->Count-1] = false;
                    	}
                    }

                	// 出荷検査項目で出荷検査項目を選択する時はチェックON
                    if( iSKB_NO == 2 ){
                    	if( iSEL_SK == true ){
							clb->Checked[clb->Items->Count-1] = true;
                    	} else {
                        	clb->Checked[clb->Items->Count-1] = false;
                    	}
                    }

                	// 特別検査項目で特別検査項目を選択する時はチェックON
                    if( iTOKU_FLG == 1 ){
                    	if( iSEL_TK == 1 ){
                        	// 「する」
							clb->Checked[clb->Items->Count-1] = true;
                    	} else if( iSEL_TK == 0 ){
                        	// 「しない」
                        	clb->Checked[clb->Items->Count-1] = false;
                    	} else {
                        	// 「無効」
                    	}
                    }

                	// 材料証明項目で材料証明項目を選択する時はチェックON
                    if( iSKB_NO == 3 ){
                    	if( iSEL_ZR == true ){
							clb->Checked[clb->Items->Count-1] = true;
                    	} else {
                        	clb->Checked[clb->Items->Count-1] = false;
                    	}
                    }
				}
            }

        }

		Query2->Next();
		iCol++;
	}

	//Query1->Close();
    if( iCol > 0 ) bRet = true;

	return( bRet );
}
