//---------------------------------------------------------------------------
//
//  Unit3.cpp
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
#include "Unit3.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：レポート作成処理を開始します（検査結果時系列管理表用）
//
//  機能説明
//    印刷対象データの条件取得後、CreateReportSub5FOutを実行します。
//
//  パラメタ説明
//    int iAutoType		：出力形式
//                        0=印刷指示CSVファイル作成→Excel起動→印刷→Excel終了
//                        1=印刷指示CSVファイル作成→Excel起動
//
//  戻り値
//    bool				 ：true  処理成功
//        				 ：false 処理失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::CreateReportSub5(int iAutoType)
{
	int i;
	AnsiString sBuf;
	AnsiString sBufWLOTNO;
	AnsiString sBufDTKSHIN;
	AnsiString sBufLOTNO;
	AnsiString sBufSKTYMD;
    AnsiString sBufClb6_CHK_LOT;
    AnsiString sBufExcelFileName;
	int iFlagExcel;
    int iFlagKOTEI_PRN;

	sBufLOTNO  	    = "";
	sBufDTKSHIN     = "";
	sBufWLOTNO 	    = "";
	sBufSKTYMD 	    = "";
    iFlagExcel      = 0;

	//ファイルオープン
	if( (fCRSF_stream1 = fopen( sRepData5_1, "w+" )) == NULL ){
    	//ShowMessage("１でした。");
		return(false);
	}
	if( (fCRSF_stream2 = fopen( sRepData5_2, "w+" )) == NULL ){
		fclose(fCRSF_stream1);
    	//ShowMessage("２でした。");
		return(false);
	}
	if( (fCRSF_stream3 = fopen( sRepData5_3, "w+" )) == NULL ){
		fclose(fCRSF_stream1);
		fclose(fCRSF_stream2);
    	//ShowMessage("３でした。");
		return(false);
	}

	iCRSF_PageNo = 0;

    iRDiMax = 0;
    iRDjMax = 0;

	//--------------------------------------------------------------------------
	//�@チェックされたロットより印刷対象データ取得
	//得意先品番・ロット指定の場合
	//得意先品番
	sBufDTKSHIN = Edt5_WHR_DTKSHIN1->Text;
	sBufSKTYMD  = Edt_SEIKAN_YMD->Text;

	//ロットNo
	for ( i = 0; i < Clb5_CHK_LOT->Items->Count; i++ ) {
		if ( Clb5_CHK_LOT->Checked[i] == true ){
			sBufLOTNO = Clb5_CHK_LOT->Items->Strings[i];
			sBufWLOTNO += ", '" + sBufLOTNO + "' ";
			iLOTNO_Length = sBufLOTNO.Length();

	        //Excelのファイル名決定
	        if ( iFlagExcel == 0 ) {
	        	sBufExcelFileName = "検査結果時系列管理表" + sBufDTKSHIN + "_" + sBufLOTNO + ".xls";
	            iFlagExcel = 1;
	        }
		}
	}
	sBufWLOTNO = sBufWLOTNO.SubString(2,sBufWLOTNO.Length()-1);


	if ( Trim(sBufDTKSHIN) != "" && Trim(sBufWLOTNO) != "" ) {
	   CreateReportSub5FOut(sBufDTKSHIN,sBufWLOTNO,sBufSKTYMD);
	}


	//--------------------------------------------------------------------------

	Q_CRSub_KSD01->Close();
	Q_CRSub_KSD02->Close();
	Q_CRSub_KSD11->Close();
	Q_CRSub_KSD12->Close();


    //タイトル部データ出力
    if ( Rdo5_KOTEI_PRN_ON->Checked == true ) {
    	iFlagKOTEI_PRN = 0;
    } else {
    	iFlagKOTEI_PRN = 1;
    }
	fprintf( fCRSF_stream1,"%d,%d,%d,%d,%s,%s,%s,%d,\n",
    		iCRSF_PageNo,iRDiMax,iRDjMax,iAutoType,sBufExcelFileName.c_str(),
            Edt5_CHK_CUSTOMER->Text.c_str(),Edt5_CHK_CUSTOMER2->Text.c_str(),iFlagKOTEI_PRN );

	// ファイルを閉じる
	fclose(fCRSF_stream1);
	fclose(fCRSF_stream2);
	fclose(fCRSF_stream3);

    return(true);

}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：レポート作成処理を開始します（検査結果時系列管理表用）
//
//  機能説明
//    印刷対象データ取得後、印刷指示ファイル(CSV)を作成します
//
//  パラメタ説明
//    AnsiString sBufDTKSHIN	：検索条件（得意先品番）
//    AnsiString sBufWLOTNO		：検索条件（ロットNo）
//
//  戻り値
//    bool				 ：true  処理成功
//        				 ：false 処理失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::CreateReportSub5FOut(AnsiString sBufDTKSHIN, AnsiString sBufWLOTNO, AnsiString sBufSKTYMD)
{

	AnsiString sBufSQL;
	AnsiString sBufWhere;
	AnsiString sBufOrder;
	AnsiString sBufWFix;
	AnsiString sBufWSKB_NO;
	AnsiString sBufWTOKU_FLG;

    int i;
    int iFlag;
	AnsiString sBuf;

    AnsiString sBufLOTNO;
    int        iLenLOTNO;
    int        iPosLOTNO;

	sBufWhere       = "";
    sBufWSKB_NO     = "";
    sBufWTOKU_FLG   = "";
	sBufOrder       = "";

	//SQL文を作成
	//注１：KSD02検索時 識別No=9(スペース) は省く
	//注２：KSD02検索時 測定値表現=0,1のみ取得

    //共通の条件部作成
	sBufWFix = " SKB_NO <> 9 AND ( VALUE_TYPE = 0 OR VALUE_TYPE = 1 ) ";

    //2004.10.06 E.Takase ↓ コメント
    //識別Noの条件不要（これは「出力内容の確認」の際にのみ、必要）
	sBufWSKB_NO = "";
    sBufWTOKU_FLG = "";
	////識別No
	//sBufWSKB_NO = "";
	//素材測定項目
	//if ( Rdo5_WHR_SOZAI_ON->Checked ) {
	//    sBufWSKB_NO += " OR SKB_NO = 1 ";
	//}
	////出荷測定項目
	//if ( Rdo5_WHR_SYUKA_ON->Checked ) {
	//    sBufWSKB_NO += " OR SKB_NO = 2 ";
	//}
	////材料証明項目
	//if ( Rdo5_WHR_ZAIRYOU_ON->Checked ) {
	//    sBufWSKB_NO += " OR SKB_NO = 3 ";
	//}
	//sBufWSKB_NO = sBufWSKB_NO.SubString(4,sBufWSKB_NO.Length()-3);
    //if ( Trim(sBufWSKB_NO) != "" ) {
	//	sBufWSKB_NO = " ( " + sBufWSKB_NO + " ) ";
    //}
    //
	////特別出力項目
	//if ( Rdo5_WHR_TOKUBETSU_ON->Checked ) {
	//    sBufWTOKU_FLG = "";
	//} else {
	//    sBufWTOKU_FLG = "AND TOKU_FLG = 0";
	//}
    ////2004.10.06 E.Takase ↑ コメント


	//KSD02
	sBufWhere =  " WHERE " + sBufWFix;
	sBufWhere += " AND DTKSHIN ='" + sBufDTKSHIN + "'";
	sBufWhere += " AND LOTNO IN (" + sBufWLOTNO + ")";
    sBufWhere += " AND SKTYMD >= '" + sBufSKTYMD + "'";      //onishi
    if ( Trim(sBufWSKB_NO) != "" ) {
		sBufWhere += " AND " + sBufWSKB_NO;
    }
	sBufWhere += sBufWTOKU_FLG;
	//sBufWhere += " AND DISP_VAL_SU > 0 ";
	if( iLOTNO_Length == 5 ){
		sBufOrder = " ORDER BY DTKSHIN,SUBSTR(LOTNO,2),ORDER_NO";
	} else {
		sBufOrder = " ORDER BY DTKSHIN,LOTNO,ORDER_NO";
	}

	//KSD02
	sBufSQL = "SELECT * FROM KSD02";
	sBufSQL += sBufWhere;
	sBufSQL += sBufOrder;

	Q_CRSub_KSD02->Close();
	Q_CRSub_KSD02->SQL->Clear();
	Q_CRSub_KSD02->SQL->Add(sBufSQL);
	Q_CRSub_KSD02->Open();
	Q_CRSub_KSD02->Active = true;
    if ( Q_CRSub_KSD02->Eof == true ) {
        return(false);
    }

	//KSD01
	sBufWhere =  " WHERE ";
	sBufWhere += " DTKSHIN ='" + sBufDTKSHIN + "'";
	sBufWhere += " AND LOTNO IN (" + sBufWLOTNO + ")";
    sBufWhere += " AND SKTYMD >= '" + sBufSKTYMD + "'";      //onishi
	if( iLOTNO_Length == 5 ){
		sBufOrder = " ORDER BY DTKSHIN,SUBSTR(LOTNO,2)";
	} else {
		sBufOrder = " ORDER BY DTKSHIN,LOTNO";
	}

	//KSD01
	sBufSQL = "SELECT * FROM KSD01";
	sBufSQL += sBufWhere;
	sBufSQL += sBufOrder;

	Q_CRSub_KSD01->Close();
	Q_CRSub_KSD01->SQL->Clear();
	Q_CRSub_KSD01->SQL->Add(sBufSQL);
	Q_CRSub_KSD01->Open();
	Q_CRSub_KSD01->Active = true;
    if ( Q_CRSub_KSD01->Eof == true ) {
        return(false);
    }

 	//データ初期化
	iCRSF_KSD01_MAX = 18;
	iCRSF_KSD01_Num = 0;
	iCRSF_KSD01_Pos = 0;
	iCRSF_KSD02_MAX = GetCRSF_KSD02_NUM();
	CRSF_KSD02 = new  struct TCRSF_KSD02[iCRSF_KSD02_MAX];
	CRSF_KSD12 = new  struct TCRSF_KSD02[iCRSF_KSD02_MAX];
	iCRSF_KSD02_Num = 0;
	iCRSF_KSD02_Pos = 0;
	iCRSF_KSD12_Num = 0;
	iCRSF_KSD12_Pos = 0;


	//データの出力＆セット
	Q_CRSub_KSD01->First();
	Q_CRSub_KSD02->First();

	strcpy(sCRSF_DTKSHIN , Null_S(Q_CRSub_KSD01->FieldValues["DTKSHIN"]).c_str());	//�@得意先品番
	strcpy(sCRSF_ZISNAM  , Null_S(Q_CRSub_KSD01->FieldValues["ZISNAM"]).c_str());	//�A材質名称（品種）
	strcpy(sCRSF_HINMEI  , Null_S(Q_CRSub_KSD01->FieldValues["HINMEI"]).c_str());	//�B品名


	while(Q_CRSub_KSD02->Eof == false) {
        //出力対象の測定項目かどうかを判断
        sBuf = "";
        if( !VarIsNull(Q_CRSub_KSD02->FieldValues["KOMK_NM"]) ){
        	sBuf = Q_CRSub_KSD02->FieldValues["KOMK_NM"];
        }
        if( !VarIsNull(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]) ){
        	sBuf = sBuf + " " + Q_CRSub_KSD02->FieldValues["KOMK_SUB"];
        }
        // 2003/10/21 A.Tamura [単位]も含めて選択条件に入れる。
        if( !VarIsNull(Q_CRSub_KSD02->FieldValues["TANI"]) ){
        	sBuf = sBuf + " " + Q_CRSub_KSD02->FieldValues["TANI"];
        }
        iFlag = 0;
        for ( i = 0; i < Clb5_CHK_KOUMOKU->Items->Count; i++ ) {
        	if ( Clb5_CHK_KOUMOKU->Items->Strings[i] == sBuf ) {
                if ( Clb5_CHK_KOUMOKU->Checked[i] == true ) {
            		iFlag = 1;
                }
            }
        }
        if ( iFlag == 1 ) {
			//ロットの描画位置取得(この時1ページに入るロット数を超えたら改ページします)
			iCRSF_KSD01_Pos = GetiCRSF_KSD01_Pos5(Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]));

			//測定項目の描画位置取得
            //2003.06.10 E.Takase
			//iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
			//							 		 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]));
            //2003.10.22 E.Takase
			//iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
			//							 		 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]),
			//							 		 Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]),
			//							 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str()),
			//							 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str()) );
			iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
										 		 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]),
										 		 Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]),
										 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str()),
										 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str()),
										 		 Null_S(Q_CRSub_KSD02->FieldValues["TANI"]) );

			//データ詳細部(sRepData5_3)にデータ出力
			WriteCRSF_sRepData5_3();

        }
		Q_CRSub_KSD02->Next();
	}

	//ページNoを出力
    iCRSF_PageNo++;
    //2003/08/27 E.Takase
    //ロットNOの桁数 画面で指定（時系列）
    sBufLOTNO = CRSF_KSD01[0].LOTNO;
    if ( iLOTNO_OUT_Length < 6 ) {
     	// 右から iLOTNO_OUT_Length 桁利用
        iLenLOTNO = sBufLOTNO.Length();
        iPosLOTNO = iLenLOTNO - iLOTNO_OUT_Length;
        if( iPosLOTNO > 0 ){
           	sBufLOTNO = sBufLOTNO.SubString( iPosLOTNO + 1, iLOTNO_OUT_Length );
      	}
    }
	fprintf( fCRSF_stream2,"*,0,PAGENO,");
    //fprintf( fCRSF_stream2,"%d,%s,%s,%s,\n",iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI);
	//fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    //		iCRSF_PageNo,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,CRSF_KSD01[0].LOTNO);
	fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    		iCRSF_PageNo,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,sBufLOTNO.c_str());
	//ロットデータを出力
	WriteCRSF_KSD01();
	//測定項目データを出力
	WriteCRSF_KSD02();

    //ロットデータを初期化
	memset( CRSF_KSD01, (int)NULL, sizeof(struct TCRSF_KSD01)*iCRSF_KSD01_MAX );
	iCRSF_KSD01_Num = 0;

	//測定項目データを初期化
	memset( CRSF_KSD02, (int)NULL, sizeof(struct TCRSF_KSD02)*iCRSF_KSD02_MAX );
	iCRSF_KSD02_Num = 0;

    return(true);

}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：ロットの描画位置取得します
//
//  機能説明
//	  構造体CRSF_KSD01に指定されたロットの情報を代入します。
//    但し、1ページに入るロット数と比較し、超えていたら改ページ処理します。
//    改ページ処理を行ったら、構造体CRSF_KSD01を初期化します。
//    CreateReportSub5FOutで使用されます
//
//  パラメタ説明
//    AnsiString sSrchLOTNO		：検索条件（ロットNo）
//
//  戻り値
//    int						：ロットの描画位置
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
int  __fastcall TForm1::GetiCRSF_KSD01_Pos5(AnsiString sSrchLOTNO)
{
	int i;
	int iPos;
	AnsiString sBuf;
	AnsiString sBufSKTYMD;
	AnsiString sBufDTKSHIN;
	AnsiString sBufLOTNO;
	AnsiString sBufSQL;

    AnsiString sBufLOTNO2;
    int        iLenLOTNO;
    int        iPosLOTNO;

	iPos = -1;
	for ( i = 0; i < iCRSF_KSD01_Num; i++ ) {
		if ( AnsiString(CRSF_KSD01[i].LOTNO) == sSrchLOTNO ) {
			iPos = i;
		}
	}
	if ( iPos == -1 ) {
		//1ページに入るロット数と比較し、超えていたら改ページ処理
		//データタイトル部(sRepData6_2)
		if ( iCRSF_KSD01_Num+1 > iCRSF_KSD01_MAX ) {
        	//2003/08/27 E.Takase
        	//ロットNOの桁数 画面で指定（時系列）
        	sBufLOTNO2 = CRSF_KSD01[0].LOTNO;
        	if ( iLOTNO_OUT_Length < 6 ) {
        		// 右から iLOTNO_OUT_Length 桁利用
	        	iLenLOTNO = sBufLOTNO2.Length();
            	iPosLOTNO = iLenLOTNO - iLOTNO_OUT_Length;
            	if( iPosLOTNO > 0 ){
            		sBufLOTNO2 = sBufLOTNO2.SubString( iPosLOTNO + 1, iLOTNO_OUT_Length );
        		}
        	}
			//ページNoを出力
	        fprintf( fCRSF_stream2,"*,0,PAGENO,");
	        //fprintf( fCRSF_stream2,"%d,%s,%s,%s,\n",iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI);
		 	//fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    		//				iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,CRSF_KSD01[0].LOTNO);
		 	fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    						iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,sBufLOTNO2.c_str());
			//fprintf( fCRSF_stream2,"*,0,PAGENO,");
			//fprintf( fCRSF_stream2,"%d,\n",iCRSF_PageNo+1);

			//ロットデータを出力
			WriteCRSF_KSD01();
			//測定項目データを出力
			WriteCRSF_KSD02();


			//ロットデータを初期化
			memset( CRSF_KSD01, (int)NULL, sizeof(struct TCRSF_KSD01)*iCRSF_KSD01_MAX );
			iPos = 0;
			iCRSF_KSD01_Num = 0;

			//測定項目データを初期化
			memset( CRSF_KSD02, (int)NULL, sizeof(struct TCRSF_KSD02)*iCRSF_KSD02_MAX );
			iCRSF_KSD02_Num = 0;

			iCRSF_PageNo++;
		}
		//iPos位置にロットデータをセット
		iPos = iCRSF_KSD01_Num;
		//Q_CRSub_KSD01からセットするデータを検索
		Q_CRSub_KSD01->First();
		while(Q_CRSub_KSD01->Eof == false) {
			sBuf = Null_S(Q_CRSub_KSD01->FieldValues["LOTNO"]);
			if (sSrchLOTNO == sBuf) {

				strcpy(CRSF_KSD01[iPos].LOTNO			 , Null_S(Q_CRSub_KSD01->FieldValues["LOTNO"]).c_str());
				strcpy(CRSF_KSD01[iPos].SOZAI_OK_PRT	 , Null_S(Q_CRSub_KSD01->FieldValues["SOZAI_OK_PRT"]).c_str());
				strcpy(CRSF_KSD01[iPos].SYUKA_OK_PRT	 , Null_S(Q_CRSub_KSD01->FieldValues["SYUKA_OK_PRT"]).c_str());
				strcpy(CRSF_KSD01[iPos].UPDCHR		  	 , GetTANNAM(Null_S(Q_CRSub_KSD01->FieldValues["UPDCHR"])).c_str());
				strcpy(CRSF_KSD01[iPos].MEMO			 , Null_S(Q_CRSub_KSD01->FieldValues["MEMO"]).c_str());

				//測定日の書式設定(yyyymmdd→yyyy/mm/dd)
				//測定日,
			    //2003.08.23 E.Takase Add ↓
			    //SD21Sの出荷日を取得して出力
				sBufDTKSHIN = Null_S(Q_CRSub_KSD01->FieldValues["DTKSHIN"]);
				sBufLOTNO = Null_S(Q_CRSub_KSD01->FieldValues["LOTNO"]);

                /*
			 	sBufSQL  = "select DTKSHIN, LOTBNG, ESYUYMD from SD21S ";
				sBufSQL += "where ESYUYMD != '00000000' ";
				sBufSQL += "and DTKSHIN = '" + sBufDTKSHIN + "' ";
				sBufSQL += "and LOTBNG = '"  + sBufLOTNO + "' ";
                */
				// 2004/09/24 A.Tamura 出荷日は最初の日(一番古い日付)とする。
/* 2005/09/26 Y.Sano 検証用テスト
				sBufSQL  = "select TSUYMD";
				sBufSQL += " FROM SD15S RIGHT JOIN SD16S ON SD15S.JSKBNG = SD16S.JSKBNG";
				sBufSQL += " where SD16S.TKSHIN = '" + sBufDTKSHIN + "'";
				sBufSQL += " and SD16S.LOTBNG = '" + sBufLOTNO + "' ";
				sBufSQL += " order by SD15S.TSUYMD";
*/
/* 2005/09/26 Y.Sano 検証用テスト*/
                sBufSQL = "SELECT TSUYMD_MIN from SD15S_16S";
			    sBufSQL += " WHERE TKSHIN='" + sBufDTKSHIN + "'";
                sBufSQL += " AND LOTBNG='" + sBufLOTNO + "'";
                sBufSQL += " AND TSUYMD_MIN >= '" + Edt_SEIKAN_YMD->Text + "'";      //onishi
                sBufSQL += " ORDER BY TSUYMD_MIN";

				Q_CRSub_SD21S->Close();
				Q_CRSub_SD21S->SQL->Clear();
				Q_CRSub_SD21S->SQL->Add(sBufSQL);
				Q_CRSub_SD21S->Open();
				Q_CRSub_SD21S->Active = true;
			    if ( Q_CRSub_SD21S->Eof == true ) {
			        sBuf = "";
			    } else {
					// sBuf = Null_S(Q_CRSub_SD21S->FieldValues["ESYUYMD"]);
					// 2004/09/24 A.Tamura 出荷日は最初の日(一番古い日付)とする。
/* 2005/09/26 Y.Sano 検証用テスト
					sBuf = Null_S(Q_CRSub_SD21S->FieldValues["TSUYMD"]);
*/
/* 2005/09/26 Y.Sano 検証用テスト*/
					sBuf = Null_S(Q_CRSub_SD21S->FieldValues["TSUYMD_MIN"]);

			    	if ( Trim(sBuf) != "" ) {
				    	sBuf.Insert("/",7);
			    		sBuf.Insert("/",5);
			    	}
			    }
			    sBufSKTYMD = sBuf;

			    //2003.05.26 E.Takase Add ↑
			    //2003.05.26 E.Takase コメント ↓

				////CRSF_KSD01[iPos].SKTYMD		 	 = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD"]);
                //sBufSKTYMD = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD"]);
                //if ( Trim(sBufSKTYMD) != "" ) {
				//    sBufSKTYMD.Insert("/",7);
				//    sBufSKTYMD.Insert("/",5);
                //}
                //
			    //2003.05.26 E.Takase コメント ↑
                strcpy(CRSF_KSD01[iPos].SKTYMD , sBufSKTYMD.c_str());




                //2003.05.10 E.Takase Add ↓
				//CRSF_KSD01[iPos].SKTYMD_SZ		 = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD_SZ_PRT"]);
				//素材測定日の書式設定(yyyymmdd→yyyy/mm/dd)
                sBufSKTYMD = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD_SZ_PRT"]);
                if ( Trim(sBufSKTYMD) != "" ) {
				    sBufSKTYMD.Insert("/",7);
				    sBufSKTYMD.Insert("/",5);
                }
                strcpy(CRSF_KSD01[iPos].SKTYMD_SZ , sBufSKTYMD.c_str());
                //2003.05.10 E.Takase Add ↑
				break;
			}
			Q_CRSub_KSD01->Next();
		}
		iCRSF_KSD01_Num++;
	}

	return ( iPos );

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：データ詳細部(sRepData5_3)にデータ出力します
//
//  機能説明
//	  Q_CRSub_KSD02のカレントレコードのデータを出力します。
//    CreateReportSub5FOutで使用されます。
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
void __fastcall TForm1::WriteCRSF_sRepData5_3(void)
{

	int iBuf;
	AnsiString sBuf;
	AnsiString sBufSQL;
	AnsiString sBufSOKUVAL[10];
	AnsiString sBufDTKSHIN;
	AnsiString sBufLOTNO;

    //2003/08/30 E.Takase
	AnsiString sBufSOKU_FLG;
	AnsiString sReSOKU_SU;
	AnsiString sReKIKA_PRT;
	AnsiString sReVALUE_TYPE;
	AnsiString sReVALUE_DECI;
	AnsiString sReDISP_VAL_SU;
	AnsiString sReDISP_VAL_AVE;
	AnsiString sReDISP_VAL_MAX;
	AnsiString sReDISP_VAL_MIN;
	AnsiString sReDISP_OK;
	TStrings *sReDISP_VAL;
	sReDISP_VAL	= new TStringList;

	//ページ番号,データ種別（ここでは0），ロット位置，測定項目位置,分割数（分割じゃないので-1）
	fprintf( fCRSF_stream3,"%d,0,%d,%d,-1,",iCRSF_PageNo,iCRSF_KSD01_Pos,iCRSF_KSD02_Pos);

	//測定日,
	sBuf = Null_S(Q_CRSub_KSD02->FieldValues["SKTYMD"]);
    if ( Trim(sBuf) != "" ) {
	    sBuf.Insert("/",7);
    	sBuf.Insert("/",5);
    }

	fprintf( fCRSF_stream3,"%s,",sBuf.c_str());



    //2003/09/01 E.Takase
    //「測定しない(SOKU_FLG = 0)」と設定されているロットは以前のロットの測定値をコピーする
    sBufSOKU_FLG = Null_S(Q_CRSub_KSD02->FieldValues["SOKU_FLG"]);
    if ( sBufSOKU_FLG == "0" ) {
    	//「測定しない(SOKU_FLG = 0)」
        //2003/10/22 E.Takase 検索条件に単位追加
		//iBuf = GetBeforeLotVal(Null_S(Q_CRSub_KSD02->FieldValues["DTKSHIN"]),
        //        			   Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]),
        //        			   Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
		//					   Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]),
		//					   Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]),
		//					   atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str()),
		//					   atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str()),
        //                       &sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
        //                       &sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
        //                       &sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
		iBuf = GetBeforeLotVal(Null_S(Q_CRSub_KSD02->FieldValues["DTKSHIN"]),
                			   Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]),
                			   Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
							   Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]),
							   Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]),
							   atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str()),
							   atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str()),
							   Null_S(Q_CRSub_KSD02->FieldValues["TANI"]),
                               &sReSOKU_SU, &sReKIKA_PRT, &sReVALUE_TYPE,
                               &sReVALUE_DECI, &sReDISP_VAL_SU, &sReDISP_VAL_AVE,
                               &sReDISP_VAL_MAX, &sReDISP_VAL_MIN, &sReDISP_OK, sReDISP_VAL );
        if ( iBuf != -1 ) {
			//測定値表現,測定値小数点以下桁数,
			fprintf( fCRSF_stream3,"%d,", atoi(sReVALUE_TYPE.c_str()));
			fprintf( fCRSF_stream3,"%d,",atoi(sReVALUE_DECI.c_str()));
			//測定数 ,
			fprintf( fCRSF_stream3,"%d,",atoi(sReDISP_VAL_SU.c_str()));

		    //測定値の最小・最大・平均
			fprintf( fCRSF_stream3, "%s,", sReDISP_VAL_MIN.c_str());
			fprintf( fCRSF_stream3, "%s,", sReDISP_VAL_MAX.c_str());
			fprintf( fCRSF_stream3, "%s,", sReDISP_VAL_AVE.c_str());
        } else {
			//測定値表現,測定値小数点以下桁数,
			fprintf( fCRSF_stream3,"0,");
			fprintf( fCRSF_stream3,"0,");
			//測定数 ,
			fprintf( fCRSF_stream3,"0,");

		    //測定値の最小・最大・平均
			fprintf( fCRSF_stream3, " ,");
			fprintf( fCRSF_stream3, " ,");
			fprintf( fCRSF_stream3, " ,");
        } 

    } else {
    	//「測定する(SOKU_FLG = 1)」
		//測定値表現,測定値小数点以下桁数,
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_TYPE"]).c_str());
		fprintf( fCRSF_stream3,"%d,",iBuf);
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_DECI"]).c_str());
		fprintf( fCRSF_stream3,"%d,",iBuf);

		//測定数 ,
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_SU"]).c_str());
		////測定数（最大・最小・平均なので３固定）,
		//iBuf = 3;
		fprintf( fCRSF_stream3,"%d,",iBuf);

	    //測定値の最小・最大・平均
		fprintf( fCRSF_stream3, "%s,",
						Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_MIN"]).c_str());
		fprintf( fCRSF_stream3, "%s,",
						Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_MAX"]).c_str());
		fprintf( fCRSF_stream3, "%s,",
						Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_AVE"]).c_str());
	}


	fprintf( fCRSF_stream3,"\n");
    iRDiMax++;

	iBuf = 2; //測定数（最大・最小なので２固定）
    if ( iRDjMax < iBuf ) {
        iRDjMax = iBuf;
    }

}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：文字列置換処理
//
//  機能説明
//	  文字列sMasterに含まれるsAを検索してsBに置き換えます。
//    WriteCRSF_KSD01で使用されます。
//
//  パラメタ説明
//    AnsiString sMaster		：置換処理対象文字列
//    AnsiString sA				：検索文字列
//    AnsiString sB				：置換文字列
//
//  戻り値
//    AnsiString				：置換処理後の文字列
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::StrConvAtoB(AnsiString sMaster, AnsiString sA, AnsiString sB)
{
	int iLength;
    AnsiString sBuf;
    int iPos;

    sBuf = sMaster;
    iLength = sMaster.Length();

    if ( iLength <= 0 ) {
    	return ( sBuf );
    }

    while ( 1 ) {

    	iPos = sBuf.AnsiPos(sA);
        if ( iPos <= 0 ) {
        	break;
        }

        sBuf.Delete(iPos, sA.Length());
        sBuf.Insert(sB, iPos);


    }



    return ( sBuf );
}


