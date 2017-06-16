//---------------------------------------------------------------------------
//
//  Unit4.cpp
//    【出荷検査システム－レポート出力】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    高瀬　恵利
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit4.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：レポート作成処理を開始します（検査経歴票用）
//
//  機能説明
//    印刷対象データの条件取得後、CreateReportSub6FOutを実行します。
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
bool __fastcall TForm1::CreateReportSub6(int iAutoType)
{
	int i;
	int iFlag;
	int iFlag2;
	AnsiString sBuf;
	AnsiString sBufWLOTNO;
	AnsiString sBufDTKSHIN;
	AnsiString sBufLOTNO;
	AnsiString sBufSKTYMD;
    AnsiString sBufClb6_CHK_LOT;
    AnsiString sBufExcelFileName;
	int iFlagExcel;

	sBufLOTNO  	    = "";
	sBufDTKSHIN     = "";
	sBufWLOTNO 	    = "";
	sBufSKTYMD 	    = "";
    iFlagExcel      = 0;

	//ファイルオープン
	if( (fCRSF_stream1 = fopen( sRepData6_1, "w+" )) == NULL ){
		return(false);
	}
	if( (fCRSF_stream2 = fopen( sRepData6_2, "w+" )) == NULL ){
		fclose(fCRSF_stream1);
		return(false);
	}
	if( (fCRSF_stream3 = fopen( sRepData6_3, "w+" )) == NULL ){
		fclose(fCRSF_stream1);
		fclose(fCRSF_stream2);
		return(false);
	}

	iCRSF_PageNo = 0;

    iRDiMax = 0;
    iRDjMax = 0;

    sBufSKTYMD  = Edt_SEIKAN_YMD->Text;

	//--------------------------------------------------------------------------
	//①チェックされたロットより印刷対象データ取得
	//得意先品番・ロット指定の場合
	if ( Rdo6_WHR_TYPE1->Checked == true ){
        //得意先品番
		sBufDTKSHIN = Edt6_WHR_DTKSHIN1->Text;

        //ロットNo
		for ( i = 0; i < Clb6_CHK_LOT->Items->Count; i++ ) {
			if ( Clb6_CHK_LOT->Checked[i] == true ){
				sBufLOTNO = Clb6_CHK_LOT->Items->Strings[i];
				sBufWLOTNO += ", '" + sBufLOTNO + "' ";
				iLOTNO_Length = sBufLOTNO.Length();

                //Excelのファイル名決定
                if ( iFlagExcel == 0 ) {
                	sBufExcelFileName = "検査経歴票" + sBufDTKSHIN + "_" + sBufLOTNO + ".xls";
                    iFlagExcel = 1;
                }
			}
		}
		sBufWLOTNO = sBufWLOTNO.SubString(2,sBufWLOTNO.Length()-1);


        if ( Trim(sBufDTKSHIN) != "" && Trim(sBufWLOTNO) != "" ) {
		   CreateReportSub6FOut(sBufDTKSHIN,sBufWLOTNO,sBufSKTYMD);
        }

	} else {
	//検査日指定の場合
        iFlag = 0;
        iFlag2 = 0;
        //得意先品番とロットNoが1行でセットしてあるので分解する
		for ( i = 0; i < Clb6_CHK_LOT->Items->Count; i++ ) {
			if ( Clb6_CHK_LOT->Checked[i] == true ){
				sBufClb6_CHK_LOT = Clb6_CHK_LOT->Items->Strings[i];
                sBuf = Trim(sBufClb6_CHK_LOT.SubString(1,20));

                if ( iFlag == 1 && sBuf != sBufDTKSHIN ) {
                    sBufWLOTNO = sBufWLOTNO.SubString(2,sBufWLOTNO.Length()-1);
                    if ( Trim(sBufDTKSHIN) != "" && Trim(sBufWLOTNO) != "" ) {
		               CreateReportSub6FOut(sBufDTKSHIN,sBufWLOTNO,sBufSKTYMD);
                    }
					sBufWLOTNO = "";
                    iFlag2 = 0;
                }
                sBufDTKSHIN = sBuf;
                sBufLOTNO = Trim(sBufClb6_CHK_LOT.SubString(21,sBufClb6_CHK_LOT.Length()-20));

				sBufWLOTNO += ", '" + sBufLOTNO + "' ";
				iLOTNO_Length = sBufLOTNO.Length();
                iFlag = 1;
                iFlag2 = 1;
                //Excelのファイル名決定
                if ( iFlagExcel == 0 ) {
                	sBufExcelFileName = "検査経歴票" + sBufDTKSHIN + "_" + sBufLOTNO + ".xls";
                    iFlagExcel = 1;
                }

			}
		}
        if ( iFlag2 == 1 ) {
            sBufWLOTNO = sBufWLOTNO.SubString(2,sBufWLOTNO.Length()-1);
            if ( Trim(sBufDTKSHIN) != "" && Trim(sBufWLOTNO) != "" ) {
		       CreateReportSub6FOut(sBufDTKSHIN,sBufWLOTNO,sBufSKTYMD);
            }
            sBufWLOTNO = "";
            iFlag2 = 0;

        }


    }

	//--------------------------------------------------------------------------

    //タイトル部データ出力
	fprintf( fCRSF_stream1,"%d,%d,%d,%d,%s,\n",iCRSF_PageNo,iRDiMax,iRDjMax,iAutoType,sBufExcelFileName.c_str());

	// ファイルを閉じる
	fclose(fCRSF_stream1);
	fclose(fCRSF_stream2);
	fclose(fCRSF_stream3);

	Q_CRSub_KSD01->Close();
	Q_CRSub_KSD02->Close();
	Q_CRSub_KSD11->Close();
	Q_CRSub_KSD12->Close();

    return(true);


}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：レポート作成処理を開始します（検査経歴票用）
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
bool __fastcall TForm1::CreateReportSub6FOut(AnsiString sBufDTKSHIN, AnsiString sBufWLOTNO, AnsiString sBufSKTYMD)
{

	int i;

	AnsiString sBufSQL;
	AnsiString sBufWhere;
	AnsiString sBufOrder;
	AnsiString sBufWFix;
	AnsiString sBufWSKB_NO;
	AnsiString sBufWTOKU_FLG;
    int 	   iBufSKB_NO;
    int 	   iBufUPDCHRCD;

	AnsiString sBuf;

	int iFlag;

	sBufWhere       = "";
    sBufWSKB_NO     = "";
    sBufWTOKU_FLG   = "";
	sBufOrder       = "";

	//SQL文を作成
	//注１：KSD02検索時 識別No=9(スペース) は省く
	//注２：測定項目登録No=1のデータは項目「外観」へ描画する

    //共通の条件部作成
	sBufWFix = " SKB_NO <> 9 ";

    //2004.10.06 E.Takase ↓ コメント
    //識別Noの条件不要（これは「出力内容の確認」の際にのみ、必要）
	sBufWSKB_NO = "";
    sBufWTOKU_FLG = "";
	////識別No
	//sBufWSKB_NO = "";
    ////2003.08.05 E.Takase
    ////出力対象の測定項目かどうかを判断
    ////検査日指定の場のみ条件文指定
	//if ( Rdo6_WHR_TYPE1->Checked == true ){
	////得意先品番・ロット指定の場合
    //    sBufWSKB_NO = "";
    //} else {
    ////検査日指定の場合
	//	//素材測定項目
	//	if ( Rdo6_WHR_SOZAI_ON->Checked ) {
	//	    sBufWSKB_NO += " OR SKB_NO = 1 ";
	//	}
	//	//出荷測定項目
	//	if ( Rdo6_WHR_SYUKA_ON->Checked ) {
	//	    sBufWSKB_NO += " OR SKB_NO = 2 ";
	//	}
	//	//材料証明項目
	//	if ( Rdo6_WHR_ZAIRYOU_ON->Checked ) {
	//	    sBufWSKB_NO += " OR SKB_NO = 3 ";
	//	}
	//	sBufWSKB_NO = sBufWSKB_NO.SubString(4,sBufWSKB_NO.Length()-3);
	//    if ( Trim(sBufWSKB_NO) != "" ) {
	//		sBufWSKB_NO = " ( " + sBufWSKB_NO + " ) ";
	//    }
    //
	//	//特別出力項目
	//	if ( Rdo6_WHR_TOKUBETSU_ON->Checked ) {
	//	    sBufWTOKU_FLG = "";
	//	} else {
	//	    sBufWTOKU_FLG = "AND TOKU_FLG = 0";
	//	}
    //}
    //2004.10.06 E.Takase ↑ コメント

	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    //KSD02 又は KSD02Wからデータを取得
    //検索条件 作成
	sBufWhere =  " WHERE " + sBufWFix;
    //2003/08/29 E.Takase
    //指定された条件により、データ取得のテーブル判断
	//得意先品番・ロット指定の場合 KSD02Wからデータ取得する
	//検査日指定の場合             KSD02 からデータ取得する
	if ( Rdo6_WHR_TYPE1->Checked == true ){ //得意先品番・ロット指定
		//検索条件追加 ホスト名
		sBufWhere += " AND PCNAME ='" + HostName + "'";
    }
	sBufWhere += " AND DTKSHIN ='" + sBufDTKSHIN + "'";
	sBufWhere += " AND SKTYMD >='" + sBufSKTYMD + "'";
	sBufWhere += " AND LOTNO IN (" + sBufWLOTNO + ")";
    if ( Trim(sBufWSKB_NO) != "" ) {
		sBufWhere += " AND " + sBufWSKB_NO;
    }
	sBufWhere += sBufWTOKU_FLG;
	sBufWhere += " AND DISP_VAL_SU > 0 ";
	if( iLOTNO_Length == 5 ){
		sBufOrder = " ORDER BY DTKSHIN,SUBSTR(LOTNO,2),ORDER_NO";
	} else {
		sBufOrder = " ORDER BY DTKSHIN,LOTNO,ORDER_NO";
	}


    //2003/08/29 E.Takase
    //指定された条件により、データ取得のテーブル判断
	//得意先品番・ロット指定の場合 KSD02Wからデータ取得する
	//検査日指定の場合             KSD02 からデータ取得する
	if ( Rdo6_WHR_TYPE1->Checked == true ){ //得意先品番・ロット指定
		sBufSQL = "SELECT * FROM KSD02W";
    } else {
		sBufSQL = "SELECT * FROM KSD02";
    }
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


	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    //KSD01 又は KSD01Wからデータを取得
    //検索条件 作成
	sBufWhere =  " WHERE ";
    //2003/08/29 E.Takase
    //指定された条件により、データ取得のテーブル判断
	//得意先品番・ロット指定の場合 KSD02Wからデータ取得する
	//検査日指定の場合             KSD02 からデータ取得する
	if ( Rdo6_WHR_TYPE1->Checked == true ){ //得意先品番・ロット指定
		//検索条件追加 ホスト名
		sBufWhere += " PCNAME ='" + HostName + "' AND ";
    }
	sBufWhere += " DTKSHIN ='" + sBufDTKSHIN + "'";
	sBufWhere += " AND SKTYMD >='" + sBufSKTYMD + "'";
	sBufWhere += " AND LOTNO IN (" + sBufWLOTNO + ")";
	if( iLOTNO_Length == 5 ){
		sBufOrder = " ORDER BY DTKSHIN,SUBSTR(LOTNO,2)";
	} else {
		sBufOrder = " ORDER BY DTKSHIN,LOTNO";
	}

    //2003/08/29 E.Takase
    //指定された条件により、データ取得のテーブル判断
	//得意先品番・ロット指定の場合 KSD02Wからデータ取得する
	//検査日指定の場合             KSD02 からデータ取得する
	if ( Rdo6_WHR_TYPE1->Checked == true ){ //得意先品番・ロット指定
		sBufSQL = "SELECT * FROM KSD01W";
    } else {
		sBufSQL = "SELECT * FROM KSD01";
    }
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

	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//KSD11
	sBufWhere =  " WHERE ";
	sBufWhere += " DTKSHIN ='" + sBufDTKSHIN + "'";
	sBufWhere += " AND SKTYMD >='" + sBufSKTYMD + "'";
	sBufWhere += " AND LOTNO IN (" + sBufWLOTNO + ")";
	sBufWhere += " AND SOKU_VAL_SU > 0 ";
	if( iLOTNO_Length == 5 ){
		sBufOrder = " ORDER BY DTKSHIN,SUBSTR(LOTNO,2),SKTYMD";
	} else {
		sBufOrder = " ORDER BY DTKSHIN,LOTNO,SKTYMD";
	}

	sBufSQL = "SELECT * FROM KSD11";
	sBufSQL += sBufWhere;
	sBufSQL += sBufOrder;

	Q_CRSub_KSD11->Close();
	Q_CRSub_KSD11->SQL->Clear();
	Q_CRSub_KSD11->SQL->Add(sBufSQL);
	Q_CRSub_KSD11->Open();
	Q_CRSub_KSD11->Active = true;

	//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//データ初期化
	iCRSF_KSD01_MAX = 12;
	iCRSF_KSD01_Num = 0;
	iCRSF_KSD01_Pos = 0;
	iCRSF_KSD02_MAX = GetCRSF_KSD02_NUM();
   	CRSF_KSD02 = new  struct TCRSF_KSD02[iCRSF_KSD02_MAX];
	CRSF_KSD12 = new  struct TCRSF_KSD02[iCRSF_KSD02_MAX];

	iCRSF_KSD02_Num = 0;
	iCRSF_KSD02_Pos = 0;
	iCRSF_KSD12_Num = 0;
	iCRSF_KSD12_Pos = 0;
	iCRSF_KSD11_MAX = GetCRSF_KSD11_NUM() * GetCRSF_KSD11_DayNUM();
	iCRSF_KSD11_Num1 = 0;
	iCRSF_KSD11_Pos = 0;
	//CRSF_KSD11 = new  struct TCRSF_KSD11[iCRSF_KSD11_MAX];

	CRSF_KSD11 = new  struct TCRSF_KSD11*[iCRSF_KSD01_MAX];
	for ( i = 0; i < iCRSF_KSD01_MAX; i++ ) {
	    CRSF_KSD11[i] = new  struct TCRSF_KSD11[iCRSF_KSD11_MAX];
	}
	iCRSF_KSD11_Num2      = new  int[iCRSF_KSD01_MAX];
    //2003.05.26 E.Takase Add ↓
	iCRSF_KSD11_SKTYMDNum = new  int[iCRSF_KSD01_MAX];
    //2003.05.26 E.Takase Add ↑
    //2003.05.26 E.Takase コメント ↓
	//iCRSF_KSD11_OUTFLAG   = new  int[iCRSF_KSD01_MAX];
	//2003.06.10 E.Takase Edit iCRSF_KSD11_OUTFLAG   = new  int[iCRSF_KSD11_MAX];
	iCRSF_KSD11_OUTFLAG   = new  int[iCRSF_KSD01_MAX];
    //2003.05.26 E.Takase コメント ↑


    //2003.05.26 E.Takase Add ↓
    sCRSF_KSD11_SKTYMDMin->Clear();
    sCRSF_KSD11_SKTYMDStr->Clear();
    sCRSF_KSD11_UPDCHR->Clear();
    sCRSF_KSD11_SKTYMD->Clear();
	for ( i = 0; i < iCRSF_KSD01_MAX; i++ ) {
    	sCRSF_KSD11_SKTYMDMin->Add("");
    	sCRSF_KSD11_SKTYMDStr->Add("");
    	sCRSF_KSD11_UPDCHR->Add("");
    	sCRSF_KSD11_SKTYMD->Add("");
	}
    //2003.05.26 E.Takase Add ↑
    //2003.05.26 E.Takase コメント ↓
	//sCRSF_KSD11_SKTYMDMin = new  AnsiString[iCRSF_KSD01_MAX];
	//sCRSF_KSD11_SKTYMDStr = new  AnsiString[iCRSF_KSD01_MAX];
	//sCRSF_KSD11_UPDCHR    = new  AnsiString[iCRSF_KSD01_MAX];
	//sCRSF_KSD11_SKTYMD    = new  AnsiString[iCRSF_KSD01_MAX];
    //2003.05.26 E.Takase コメント ↑

	//データの出力＆セット
	Q_CRSub_KSD01->First();
	Q_CRSub_KSD02->First();

	strcpy(sCRSF_DTKSHIN , Null_S(Q_CRSub_KSD01->FieldValues["DTKSHIN"]).c_str());	//①得意先品番
	strcpy(sCRSF_ZISNAM  , Null_S(Q_CRSub_KSD01->FieldValues["ZISNAM"]).c_str());	//②材質名称（品種）
	strcpy(sCRSF_HINMEI  , Null_S(Q_CRSub_KSD01->FieldValues["HINMEI"]).c_str());	//③品名

/*
	while(Q_CRSub_KSD02->Eof == false) {
		//ロットの描画位置取得(この時1ページに入るロット数を超えたら改ページします)
		iCRSF_KSD01_Pos = GetiCRSF_KSD01_Pos6(Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]));

		//もし外観データ(SKB_NO=2 && KOMK_NO=1)なら CRSF_KSD01[i].DISP_VAL01にセット
		if ( Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]) == "1" &&
             Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"])  == "2"  ) {
            //2003.05.16 E.Takase
			//if ( Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"]) == "1" ) {
			if ( Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"]) == "0" ) {
				strcpy(CRSF_KSD01[iCRSF_KSD01_Pos].DISP_VAL01 , "良");
			} else {
				strcpy(CRSF_KSD01[iCRSF_KSD01_Pos].DISP_VAL01 , "否");
			}
        //それ以外は詳細部に出力
		} else {

			//測定項目の描画位置取得
            //2003.06.10 E.Takase
			//iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
			//								 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]));
			iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
										 		 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]),
										 		 Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]),
										 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str()),
										 		 atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str()) );

			//データ詳細部(sRepData6_3)にデータ出力
			WriteCRSF_sRepData6_3();

            //検査員
            iBufSKB_NO = atoi(Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"]).c_str());
            if ( iBufSKB_NO == 2 || iBufSKB_NO == 3 ) {
            	iBufUPDCHRCD = atoi(Null_S(Q_CRSub_KSD02->FieldValues["UPDCHR"]).c_str());
                if ( iBufUPDCHRCD != 0 ) {
                	if ( CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 == 0 || CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 > iBufUPDCHRCD ) {
                    	CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 = iBufUPDCHRCD;
                    }
                }
            }

		}

		Q_CRSub_KSD02->Next();
	}
*/

	while(Q_CRSub_KSD02->Eof == false) {
        sBuf = "";
        //2003.08.05 E.Takase
        //出力対象の測定項目かどうかを判断
        //得意先品番・ロット指定の場合のみチェック
		if ( Rdo6_WHR_TYPE1->Checked == true ){
		//得意先品番・ロット指定の場合
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
	        for ( i = 0; i < Clb6_CHK_KOUMOKU->Items->Count; i++ ) {
	        	if ( Clb6_CHK_KOUMOKU->Items->Strings[i] == sBuf ) {
	                if ( Clb6_CHK_KOUMOKU->Checked[i] == true ) {
	            		iFlag = 1;
	                }
	            }
	        }
        } else {
        //検査日指定の場合
        	iFlag = 1;
        }

        ////2003/08/30 E.Takase
        //test
        //iFlag = 1;

        if ( iFlag == 1 ) {

			//ロットの描画位置取得(この時1ページに入るロット数を超えたら改ページします)
			iCRSF_KSD01_Pos = GetiCRSF_KSD01_Pos6(Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]));

			//もし外観データ(SKB_NO=2 && KOMK_NO=1)なら CRSF_KSD01[i].DISP_VAL01にセット
			if ( Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]) == "1" &&
	             Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"])  == "2"  ) {
	            //2003.05.16 E.Takase
				//if ( Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"]) == "1" ) {
				if ( Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"]) == "0" ) {
					strcpy(CRSF_KSD01[iCRSF_KSD01_Pos].DISP_VAL01 , "良");
				} else {
                	//2003.09.16 E.Takase
                    //外観 空白のときはそのまま表示
                    if ( Trim(Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"])) == "" ) {
						strcpy(CRSF_KSD01[iCRSF_KSD01_Pos].DISP_VAL01 , " ");
                    } else {
						strcpy(CRSF_KSD01[iCRSF_KSD01_Pos].DISP_VAL01 , "否");
                    }
				}
	        //それ以外は詳細部に出力
			} else {

				//測定項目の描画位置取得
	            //2003.06.10 E.Takase
				//iCRSF_KSD02_Pos = GetiCRSF_KSD02_Pos(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]),
				//								 Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]));
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

				//データ詳細部(sRepData6_3)にデータ出力
				WriteCRSF_sRepData6_3();

	            //検査員
	            iBufSKB_NO = atoi(Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"]).c_str());
	            if ( iBufSKB_NO == 2 || iBufSKB_NO == 3 ) {
	            	iBufUPDCHRCD = atoi(Null_S(Q_CRSub_KSD02->FieldValues["UPDCHR"]).c_str());
	                if ( iBufUPDCHRCD != 0 ) {
	                	if ( CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 == 0 || CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 > iBufUPDCHRCD ) {
	                    	CRSF_KSD01[iCRSF_KSD01_Pos].UPDCHRCD2 = iBufUPDCHRCD;
	                    }
	                }
	            }

			}
        }

		Q_CRSub_KSD02->Next();
	}



	//ページNoを出力
	fprintf( fCRSF_stream2,"*,0,PAGENO,");
   	//fprintf( fCRSF_stream2,"%d,%s,%s,%s,\n",iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI);
   	//
	//fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
   	//		iCRSF_PageNo,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,CRSF_KSD01[0].LOTNO);
	if ( Rdo6_WHR_TYPE1->Checked == true ){
		//得意先品番・ロット指定の場合は品名と品種はフォームで指定されたもの
		fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    		iCRSF_PageNo+1,sCRSF_DTKSHIN,Edt6_CHK_HINSYU->Text.c_str(),Edt6_CHK_HINMEI->Text.c_str(),CRSF_KSD01[0].LOTNO);
	} else {
		//検査日指定の場合はデータベースから
		fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    			iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,CRSF_KSD01[0].LOTNO);
	}

	//ロットデータを出力
	WriteCRSF_KSD01();
	//測定項目データを出力
	WriteCRSF_KSD02();
    //分割データ取得・出力
    SetCRSF_KSD11();
   	iCRSF_PageNo++;


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
//    CreateReportSub6FOutで使用されます
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
int  __fastcall TForm1::GetiCRSF_KSD01_Pos6(AnsiString sSrchLOTNO)
{
	int i;
	int iPos;
	AnsiString sBuf;
	AnsiString sBufSKTYMD;

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
			//ページNoを出力
	        fprintf( fCRSF_stream2,"*,0,PAGENO,");
	        //fprintf( fCRSF_stream2,"%d,%s,%s,%s,\n",iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI);
		 	fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,\n",
    						iCRSF_PageNo+1,sCRSF_DTKSHIN,sCRSF_ZISNAM,sCRSF_HINMEI,CRSF_KSD01[0].LOTNO);
			//fprintf( fCRSF_stream2,"*,0,PAGENO,");
			//fprintf( fCRSF_stream2,"%d,\n",iCRSF_PageNo+1);

			//ロットデータを出力
			WriteCRSF_KSD01();
			//測定項目データを出力
			WriteCRSF_KSD02();

			//分割データ取得・出力
            SetCRSF_KSD11();


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
				//CRSF_KSD01[iPos].SKTYMD		 	 = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD"]);
                sBufSKTYMD = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD"]);
                if ( Trim(sBufSKTYMD) != "" ) {
				    sBufSKTYMD.Insert("/",7);
				    sBufSKTYMD.Insert("/",5);
                }
                strcpy(CRSF_KSD01[iPos].SKTYMD , sBufSKTYMD.c_str());

                //2003.05.10 E.Takase Add ↓
				//CRSF_KSD01[iPos].SKTYMD_SZ		 = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD_SZ_PRT"]);
                sBufSKTYMD = Null_S(Q_CRSub_KSD01->FieldValues["SKTYMD_SZ_PRT"]);
                if ( Trim(sBufSKTYMD) != "" ) {
				    sBufSKTYMD.Insert("/",7);
				    sBufSKTYMD.Insert("/",5);
                }
                strcpy(CRSF_KSD01[iPos].SKTYMD_SZ , sBufSKTYMD.c_str());
                //2003.05.10 E.Takase Add ↑

                //2003.06.11 E.Takase Add
                CRSF_KSD01[iPos].UPDCHRCD = atoi(Null_S(Q_CRSub_KSD01->FieldValues["UPDCHR"]).c_str());

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
//    自作関数					：測定項目の描画位置取得します
//
//  機能説明
//	  構造体CRSF_KSD02に指定された測定項目の情報を代入します。
//    CreateReportSub5FOutで使用されます
//    CreateReportSub6FOutで使用されます
//
//  パラメタ説明
//    AnsiString sSrchKOMK_NM		：検索条件（測定項目名称）
//    AnsiString sSrchKOMK_SUB		：検索条件（測定項目サブ名称）
//    AnsiString sSrchHINBAN_SK		：検索条件（品番）
//    int		 iSrchKIKI_NO		：検索条件（測定機器No）
//    int		 iSrchKOMK_NO		：検索条件（測定項目No）
//    AnsiString sSrchTANI			：検索条件（単位）   //2003/10/22 E.Takase Add
//
//  戻り値
//    int						：測定項目の描画位置
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
int  __fastcall TForm1::GetiCRSF_KSD02_Pos(AnsiString sSrchKOMK_NM, AnsiString sSrchKOMK_SUB,
											AnsiString sSrchHINBAN_SK, int iSrchKIKI_NO, int iSrchKOMK_NO,
                                            AnsiString sSrchTANI)
{
	int i;
	int iBufSKB_NO;
	int iPos;
	AnsiString sBufSKTYMD;

	iPos = -1;
	for ( i = 0; i < iCRSF_KSD02_Num; i++ ) {
        // 2003/10/21 A.Tamura ここに[TANI]は必要か？
        // 2003/10/22 E.Takase Add ここに[TANI]は必要
		if ( AnsiString(CRSF_KSD02[i].KOMK_NM)   == sSrchKOMK_NM   	&&
			 AnsiString(CRSF_KSD02[i].KOMK_SUB)  == sSrchKOMK_SUB 	&&
			 AnsiString(CRSF_KSD02[i].HINBAN_SK) == sSrchHINBAN_SK 	&&
			 CRSF_KSD02[i].KIKI_NO 				 == iSrchKIKI_NO 	&&
			 CRSF_KSD02[i].KOMK_NO 				 == iSrchKOMK_NO 	&&
			 AnsiString(CRSF_KSD02[i].TANI)   	 == sSrchTANI	 	) {
			iPos = i;
		}
	}
	if ( iPos == -1 ) {
		//iPos位置に測定項目データをセット
		iPos = iCRSF_KSD02_Num;
		CRSF_KSD02[iPos].SKB_NO		 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"]).c_str());
		strcpy(CRSF_KSD02[iPos].KOMK_NM	 	 , Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]).c_str());
		strcpy(CRSF_KSD02[iPos].KOMK_SUB	 , Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]).c_str());
		strcpy(CRSF_KSD02[iPos].TANI		 , Null_S(Q_CRSub_KSD02->FieldValues["TANI"]).c_str());
		CRSF_KSD02[iPos].KIKA_TYPE	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_TYPE"]).c_str());
		CRSF_KSD02[iPos].KIKA_KIND	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_KIND"]).c_str());
		CRSF_KSD02[iPos].KIKA_DECI	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_DECI"]).c_str());
		CRSF_KSD02[iPos].KIKA_NUM1	 = atof(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_NUM1"]).c_str());
		CRSF_KSD02[iPos].KIKA_NUM2	 = atof(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_NUM2"]).c_str());
		CRSF_KSD02[iPos].KIKA_NUM3	 = atof(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_NUM3"]).c_str());
		CRSF_KSD02[iPos].KIKA_PRT	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKA_PRT"]).c_str());
		CRSF_KSD02[iPos].VALUE_TYPE	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_TYPE"]).c_str());
		CRSF_KSD02[iPos].VALUE_DECI	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_DECI"]).c_str());
		strcpy(CRSF_KSD02[iPos].KIKA_STR	 , Null_S(Q_CRSub_KSD02->FieldValues["KIKA_STR"]).c_str());
		strcpy(CRSF_KSD02[iPos].KOMK_ENG	 , Null_S(Q_CRSub_KSD02->FieldValues["KOMK_ENG"]).c_str());
		//測定日の書式設定(yyyymmdd→yyyy/mm/dd)
		//CRSF_KSD02[iPos].SKTYMD		 = Null_S(Q_CRSub_KSD02->FieldValues["SKTYMD"]);
        sBufSKTYMD = Null_S(Q_CRSub_KSD02->FieldValues["SKTYMD"]);
        if ( Trim(sBufSKTYMD) != "" ) {
		    sBufSKTYMD.Insert("/",7);
		    sBufSKTYMD.Insert("/",5);
        }
        strcpy(CRSF_KSD02[iPos].SKTYMD ,sBufSKTYMD.c_str());

        //2003.06.10 E.Takase Add
		strcpy(CRSF_KSD02[iPos].HINBAN_SK	 , Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]).c_str());
		CRSF_KSD02[iPos].KIKI_NO	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]).c_str());
		CRSF_KSD02[iPos].KOMK_NO	 = atoi(Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]).c_str());

		iCRSF_KSD02_Num++;
	} else {
		//測定日の比較
		iBufSKB_NO = atoi(Null_S(Q_CRSub_KSD02->FieldValues["SKB_NO"]).c_str());
		if ( iBufSKB_NO == 1 ) {
			sBufSKTYMD = Null_S(Q_CRSub_KSD02->FieldValues["SKTYMD"]);
            if ( Trim(AnsiString(CRSF_KSD02[iPos].SKTYMD)) != "" ) {
			    sBufSKTYMD.Insert("/",7);
			    sBufSKTYMD.Insert("/",5);
            }
			if ( AnsiString(CRSF_KSD02[iPos].SKTYMD) > sBufSKTYMD ) {
            	strcpy(CRSF_KSD02[iPos].SKTYMD , sBufSKTYMD.c_str());
			}
		}
	}

	return ( iPos );
	

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：ロットデータを出力します
//
//  機能説明
//	  CRSF_KSD01のデータを出力します。
//    CreateReportSub5FOut・GetiCRSF_KSD01_Pos5で使用されます
//    CreateReportSub6FOut・GetiCRSF_KSD01_Pos6で使用されます
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
void __fastcall TForm1::WriteCRSF_KSD01(void)
{
	int i;
    AnsiString sBufMEMO;
    AnsiString sBufLOTNO;
    int        iLenLOTNO;
    int        iPosLOTNO;

	fprintf( fCRSF_stream2,"*,1,LTONO,\n");

	for ( i = 0; i < iCRSF_KSD01_Num; i++ ) {
        //sBufMEMO = StrConvAtoB( AnsiString(CRSF_KSD01[i].MEMO),"\n","[CR+LF]");
        //2003.05.23 E.Takase Add ↓
        sBufMEMO = AnsiString(CRSF_KSD01[i].MEMO);
        sBufMEMO = StrConvAtoB( AnsiString(sBufMEMO),"\r\n","[CR+LF]");
        sBufMEMO = StrConvAtoB( AnsiString(sBufMEMO),"\n\n","[CR+LF]");
        sBufMEMO = StrConvAtoB( AnsiString(sBufMEMO),"\n","[CR+LF]");
        sBufMEMO = StrConvAtoB( AnsiString(sBufMEMO),"\r","[CR+LF]");
		//2003.05.23 E.Takase Add ↑

        //2003.06.11 E.Takase Edit
        if ( CRSF_KSD01[i].UPDCHRCD2 != 0 ) {
        	strcpy(CRSF_KSD01[i].UPDCHR2, GetTANNAM(IntToStr(CRSF_KSD01[i].UPDCHRCD2)).c_str());
        } else {
        	strcpy(CRSF_KSD01[i].UPDCHR2, CRSF_KSD01[i].UPDCHR);
        }

        //2003/08/27 E.Takase
        //ロットNOの桁数 画面で指定（時系列）
        sBufLOTNO = CRSF_KSD01[i].LOTNO;
        if ( iLOTNO_OUT_Length < 6 ) {
        	// 右から iLOTNO_OUT_Length 桁利用
	        iLenLOTNO = sBufLOTNO.Length();
            iPosLOTNO = iLenLOTNO - iLOTNO_OUT_Length;
            if( iPosLOTNO > 0 ){
            	sBufLOTNO = sBufLOTNO.SubString( iPosLOTNO + 1, iLOTNO_OUT_Length );
        	}
        }
        fprintf( fCRSF_stream2,"%d,%s,%s,%s,%s,%s,%s,%s,%s,\n",
						i,
						sBufLOTNO.c_str(),
						CRSF_KSD01[i].DISP_VAL01,
						CRSF_KSD01[i].SOZAI_OK_PRT,
						CRSF_KSD01[i].SYUKA_OK_PRT,
						CRSF_KSD01[i].UPDCHR2,
						CRSF_KSD01[i].SKTYMD,
						sBufMEMO.c_str(),
                        CRSF_KSD01[i].SKTYMD_SZ
						);
	}
}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：測定項目データを出力します
//
//  機能説明
//	  CRSF_KSD02のデータを出力します。
//    CreateReportSub5FOut・GetiCRSF_KSD01_Pos5で使用されます
//    CreateReportSub6FOut・GetiCRSF_KSD01_Pos6で使用されます
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
void __fastcall TForm1::WriteCRSF_KSD02(void)
{
	int i;

	fprintf( fCRSF_stream2,"*,2,KOMK_NM,\n");

	for ( i = 0; i < iCRSF_KSD02_Num; i++ ) {
        //注）-1は分割数（分割じゃないので-1）
		fprintf( fCRSF_stream2,"%d,-1,%s,%s,%s,%d,%d,%d,%lf,%lf,%lf,%d,%s,%s,\n",
						i,
						CRSF_KSD02[i].KOMK_NM,
						CRSF_KSD02[i].KOMK_SUB,
						CRSF_KSD02[i].TANI,
						CRSF_KSD02[i].KIKA_TYPE,
						CRSF_KSD02[i].KIKA_KIND,
						CRSF_KSD02[i].KIKA_DECI,
						CRSF_KSD02[i].KIKA_NUM1,
						CRSF_KSD02[i].KIKA_NUM2,
						CRSF_KSD02[i].KIKA_NUM3,
						CRSF_KSD02[i].KIKA_PRT,
						CRSF_KSD02[i].KIKA_STR,
						CRSF_KSD02[i].KOMK_ENG
						);
	}

	//for ( i = 0; i < iCRSF_KSD02_Num; i++ ) {
	//	fprintf( fCRSF_stream2,"%d,%s,%s,%s,%d,%d,%d,%lf,%lf,%lf,%d,%d,%d,%s,\n",
	//					i,
	//					CRSF_KSD02[i].KOMK_NM.c_str(),
	//					CRSF_KSD02[i].KOMK_SUB.c_str(),
	//					CRSF_KSD02[i].TANI.c_str(),
	//					CRSF_KSD02[i].KIKA_TYPE,
	//					CRSF_KSD02[i].KIKA_KIND,
	//					CRSF_KSD02[i].KIKA_DECI,
	//					CRSF_KSD02[i].KIKA_NUM1,
	//					CRSF_KSD02[i].KIKA_NUM2,
	//					CRSF_KSD02[i].KIKA_NUM3,
	//					CRSF_KSD02[i].KIKA_PRT,
	//					CRSF_KSD02[i].VALUE_TYPE,
	//					CRSF_KSD02[i].VALUE_DECI,
	//					CRSF_KSD02[i].SKTYMD.c_str()
	//					);
	//}


}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：データ詳細部(sRepData6_3)にデータ出力します
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
void __fastcall TForm1::WriteCRSF_sRepData6_3(void)
{

	int iBuf;
	int i;
	int n;
	AnsiString sBufSOKU_FLG;
	AnsiString sBuf;
	AnsiString sBufSQL;
	AnsiString sBufSOKUVAL[10];

    //2003/08/30 E.Takase
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
        	//測定値表現,測定値小数点以下桁数
            fprintf( fCRSF_stream3,"%d,",atoi(sReVALUE_TYPE.c_str()));
            fprintf( fCRSF_stream3,"%d,",atoi(sReVALUE_DECI.c_str()));
  			//測定数,
 			fprintf( fCRSF_stream3,"%d,",atoi(sReDISP_VAL_SU.c_str()));
			//測定値1,・・・・
			for ( i = 0; i < iBuf; i++ ) {
				fprintf( fCRSF_stream3,"%s,",sReDISP_VAL->Strings[i].c_str());
			}
		    if ( iRDjMax < iBuf ) {
		        iRDjMax = iBuf;
		    }

        } else {
        	//測定値表現,測定値小数点以下桁数
            fprintf( fCRSF_stream3,"0,");
            fprintf( fCRSF_stream3,"0,");
  			//測定数,
            //2003.09.13 E.Takase
 			//fprintf( fCRSF_stream3,"0,");
 			fprintf( fCRSF_stream3,"1,");
			//測定値1,・・・・
			fprintf( fCRSF_stream3," ,");
        }

		fprintf( fCRSF_stream3,"\n");
	    iRDiMax++;

    } else {
    	//「測定する(SOKU_FLG = 1)」
		//測定値表現,測定値小数点以下桁数,
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_TYPE"]).c_str());
		fprintf( fCRSF_stream3,"%d,",iBuf);
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["VALUE_DECI"]).c_str());
		fprintf( fCRSF_stream3,"%d,",iBuf);

		//測定数,
		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_SU"]).c_str());
		fprintf( fCRSF_stream3,"%d,",iBuf);

		//測定値1,・・・・
		sBufSOKUVAL[0] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL01"]);
		sBufSOKUVAL[1] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL02"]);
		sBufSOKUVAL[2] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL03"]);
		sBufSOKUVAL[3] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL04"]);
		sBufSOKUVAL[4] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL05"]);
		sBufSOKUVAL[5] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL06"]);
		sBufSOKUVAL[6] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL07"]);
		sBufSOKUVAL[7] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL08"]);
		sBufSOKUVAL[8] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL09"]);
		sBufSOKUVAL[9] =  Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL10"]);
		if ( iBuf > 10 ) {
			n = 10;
		} else {
			n = iBuf;
		}
		for ( i = 0; i < n; i++ ) {
			fprintf( fCRSF_stream3,"%s,",sBufSOKUVAL[i].c_str());
		}

		//測定数が10～なら例外テーブルから測定値取得
		if ( iBuf > 10 ) {
		    //2003/08/29 E.Takase
		    //指定された条件により、データ取得のテーブル判断
			//得意先品番・ロット指定の場合 KSD03Wからデータ取得する
			//検査日指定の場合             KSD03 からデータ取得する
			if ( Rdo6_WHR_TYPE1->Checked == true ){ //得意先品番・ロット指定
 				sBufSQL = "SELECT * FROM KSD03W";
				//検索条件追加 ホスト名
				sBufSQL += " WHERE PCNAME ='" + HostName + "'";
				sBufSQL += " AND DTKSHIN ='" + Null_S(Q_CRSub_KSD02->FieldValues["DTKSHIN"]) + "'";
				sBufSQL += " AND LOTNO = '" + Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]) + "'";
				sBufSQL += " AND UNQ_NO = " + Null_S(Q_CRSub_KSD02->FieldValues["UNQ_NO"]);
				sBufSQL += " ORDER BY SOKU_NO";
		    } else {
				sBufSQL = "SELECT * FROM KSD03";
				sBufSQL += " WHERE DTKSHIN ='" + Null_S(Q_CRSub_KSD02->FieldValues["DTKSHIN"]) + "'";
				sBufSQL += " AND LOTNO = '" + Null_S(Q_CRSub_KSD02->FieldValues["LOTNO"]) + "'";
				sBufSQL += " AND UNQ_NO = " + Null_S(Q_CRSub_KSD02->FieldValues["UNQ_NO"]);
				sBufSQL += " ORDER BY SOKU_NO";
		    }

			Q_CRSub_KSD03->Close();
			Q_CRSub_KSD03->SQL->Clear();
			Q_CRSub_KSD03->SQL->Add(sBufSQL);
			Q_CRSub_KSD03->Open();
			Q_CRSub_KSD03->Active = true;
			while(Q_CRSub_KSD03->Eof == false) {
				fprintf( fCRSF_stream3, "%s,",
								Null_S(Q_CRSub_KSD03->FieldValues["DISP_VAL"]).c_str());
				Q_CRSub_KSD03->Next();
			}

		}


		fprintf( fCRSF_stream3,"\n");
	    iRDiMax++;

		iBuf = atoi(Null_S(Q_CRSub_KSD02->FieldValues["DISP_VAL_SU"]).c_str());
	    if ( iRDjMax < iBuf ) {
	        iRDjMax = iBuf;
	    }


    }


}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：KSD02測定項目数を取得します
//
//  機能説明
//	  構造体CRSF_KSD02のメモリ取得の際の個数を取得します。
//	  構造体CRSF_KSD02には測定実績データがセットされます。
//    CreateReportSub5FOutで使用されます
//    CreateReportSub6FOutで使用されます
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    int						：KSD02測定項目数
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
int __fastcall TForm1::GetCRSF_KSD02_NUM(void)
{
    int n;
    AnsiString sBuf;
    AnsiString sBufA;

    Q_CRSub_KSD02->First();
    n = 0;
    sBuf = ",";
	while(Q_CRSub_KSD02->Eof == false) {
        sBufA  = "";
        sBufA += Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NM"]);
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD02->FieldValues["KOMK_SUB"]);
        //2003.06.10 E.Takase Add
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD02->FieldValues["HINBAN_SK"]);
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD02->FieldValues["KIKI_NO"]);
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD02->FieldValues["KOMK_NO"]);

        sBufA += ",";

        if ( sBuf.AnsiPos("," + sBufA) == 0 ) {
            n++;
            sBuf += sBufA;
        }

		Q_CRSub_KSD02->Next();
	}

    return ( n );
}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：KSD11測定項目数を取得します
//
//  機能説明
//	  構造体CRSF_KSD11のメモリ取得の際の個数をGetCRSF_KSD11_DayNUMとセットで取得します。
//	  構造体CRSF_KSD11には測定実績分割データがセットされます。
//    CreateReportSub6FOutで使用されます
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    int						：KSD11測定項目数
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
int __fastcall TForm1::GetCRSF_KSD11_NUM(void)
{
    int n;
    AnsiString sBuf;
    AnsiString sBufA;

    Q_CRSub_KSD11->First();
    n = 0;
    sBuf = ",";
	while(Q_CRSub_KSD11->Eof == false) {
        sBufA  = "";
        sBufA += Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NM"]);
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD11->FieldValues["KOMK_SUB"]);
        //2003.06.10 E.Takase Add
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD11->FieldValues["KIKI_NO"]);
        sBufA += " ";
        sBufA += Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NO"]);

        sBufA += ",";

        if ( sBuf.AnsiPos("," + sBufA) == 0 ) {
            n++;
            sBuf += sBufA;
        }

		Q_CRSub_KSD11->Next();
	}

    return ( n );
}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：KSD11測定日の種類数します
//
//  機能説明
//	  構造体CRSF_KSD11のメモリ取得の際の個数をGetCRSF_KSD11_NUMとセットで取得します。
//	  構造体CRSF_KSD11には測定実績分割データがセットされます。
//    CreateReportSub6FOutで使用されます
//
//  パラメタ説明
//    なし。
//
//  戻り値
//    int						：KSD11測定日の種類数
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
int __fastcall TForm1::GetCRSF_KSD11_DayNUM(void)
{
    int n;
    AnsiString sBuf;
    AnsiString sBufA;

    Q_CRSub_KSD11->First();
    n = 0;
    sBuf = ",";
	while(Q_CRSub_KSD11->Eof == false) {
        sBufA  = "";
        sBufA += Null_S(Q_CRSub_KSD11->FieldValues["SKTYMD"]);
        sBufA += ",";

        if ( sBuf.AnsiPos("," + sBufA) == 0 ) {
            n++;
            sBuf += sBufA;
        }

		Q_CRSub_KSD11->Next();
	}

    return ( n );
}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：Q_CRSub_KSD11から必要なデータのみCRSF_KSD11にセットします
//
//  機能説明
//	  構造体CRSF_KSD01にセットされているデータと
//    一致するレコードのみ（ロットＮNo・測定項目で判断）CRSF_KSD11にセットします。
//    CreateReportSub6FOut・GetiCRSF_KSD01_Pos6で使用されます
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
void __fastcall TForm1::SetCRSF_KSD11(void)
{

    int i;
    int j;
    int n;
    int m;
    int l;
    int a;
    int iPos1;
    int iPos2;
    int iFlag2;
    int iBuf;
    AnsiString sBuf;
    AnsiString sBufFileOut;
    AnsiString sBufFileOut_Day;
    char       cBufFileOut[2056];
    AnsiString sBufSQL;
    AnsiString sBufLOTNO;
    AnsiString sBufKOMK_NM;
    AnsiString sBufKOMK_SUB;
	AnsiString sBufSOKUVAL[10];
    AnsiString sBufSKTYMD;
    AnsiString sBufTANNAM;
    AnsiString sBufWtiteStr;
	int 	   iBufKIKI_NO;         	//機器No		//2003.06.10 E.Takase Add
	int 	   iBufKOMK_NO;         	//測定項目No	//2003.06.10 E.Takase Add

    AnsiString sBufTANI;

    iPos1  = -1;
    iPos2  = -1;
    iFlag2 = -1;
    iCRSF_KSD11_Num1 = iCRSF_KSD01_Num;
    iCRSF_KSD11_SKTYMDNumMax = 0;
	//測定項目データを初期化
	//memset( CRSF_KSD11, (int)NULL, sizeof(struct TCRSF_KSD11)*(iCRSF_KSD01_MAX*iCRSF_KSD11_MAX ));
    FormatCRSF_KSD11();
	memset( iCRSF_KSD11_Num2, (int)NULL, sizeof(int)*iCRSF_KSD01_MAX );
	memset( iCRSF_KSD11_SKTYMDNum, (int)NULL, sizeof(int)*iCRSF_KSD01_MAX );
    //2003.05.26 E.Takase コメント ↓
	//memset( sCRSF_KSD11_SKTYMDMin, (int)NULL, sizeof(AnsiString)*iCRSF_KSD01_MAX );
	//memset( sCRSF_KSD11_SKTYMDStr, (int)NULL, sizeof(AnsiString)*iCRSF_KSD01_MAX );
    //2003.05.26 E.Takase コメント ↑
    for ( i = 0; i < iCRSF_KSD01_MAX; i++ ) {
        //sCRSF_KSD11_SKTYMDStr[i] = ",";
    	//2003.05.26 E.Takase Add ↓
        sCRSF_KSD11_SKTYMDMin->Strings[i] = "";
        sCRSF_KSD11_SKTYMDStr->Strings[i] = ",";
    	//2003.05.26 E.Takase Add ↑
    }
    Q_CRSub_KSD11->First();


	while(Q_CRSub_KSD11->Eof == false) {
        iPos1 = -1;
        iPos2 = -1;
        iFlag2 = -1;
        //チェック①ロット
        sBufLOTNO = Null_S(Q_CRSub_KSD11->FieldValues["LOTNO"]);
        for ( i = 0; i < iCRSF_KSD01_Num; i++ ) {
            if ( sBufLOTNO == AnsiString(CRSF_KSD01[i].LOTNO) ) {
                iPos1 = i;
                break;
            }
        }
        if ( iPos1 >= 0 ) {
            //チェック②検査項目名称
            sBufKOMK_NM  = Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NM"]);
            sBufKOMK_SUB = Null_S(Q_CRSub_KSD11->FieldValues["KOMK_SUB"]);
            //2003.06.10 E.Takase Add
            iBufKIKI_NO = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKI_NO"]).c_str());
            iBufKOMK_NO = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NO"]).c_str());
            // 2003/10/22 E.Takase Add
            sBufTANI = Null_S(Q_CRSub_KSD11->FieldValues["TANI"]);
            for ( i = 0; i < iCRSF_KSD02_Num; i++ ) {
                //2003.06.10 E.Takase Edit
                //if ( sBufKOMK_NM  == AnsiString(CRSF_KSD02[i].KOMK_NM)  &&
                //     sBufKOMK_SUB == AnsiString(CRSF_KSD02[i].KOMK_SUB) ) {

                // 2003/10/21 A.Tamura ここに[TANI]は必要か？
		        // 2003/10/22 E.Takase Add ここに[TANI]は必要
				if ( sBufKOMK_NM  == AnsiString(CRSF_KSD02[i].KOMK_NM)  &&
                     sBufKOMK_SUB == AnsiString(CRSF_KSD02[i].KOMK_SUB) &&
                     iBufKIKI_NO  == CRSF_KSD02[i].KIKI_NO  &&
                     iBufKOMK_NO  == CRSF_KSD02[i].KOMK_NO  &&
                     sBufTANI     == AnsiString(CRSF_KSD02[i].TANI)  ) {
                    iFlag2 = i;
                    break;
                }
            }
        }
        if ( iPos1 >= 0 && iFlag2 >= 0 ) {
            iPos2 = iCRSF_KSD11_Num2[iPos1];

			strcpy(CRSF_KSD11[iPos1][iPos2].KOMK_NM	 , Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NM"]).c_str());
			strcpy(CRSF_KSD11[iPos1][iPos2].KOMK_SUB	 , Null_S(Q_CRSub_KSD11->FieldValues["KOMK_SUB"]).c_str());
			strcpy(CRSF_KSD11[iPos1][iPos2].TANI		 , Null_S(Q_CRSub_KSD11->FieldValues["TANI"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_TYPE	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_TYPE"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_KIND	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_KIND"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_DECI	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_DECI"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_NUM1	 = atof(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_NUM1"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_NUM2	 = atof(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_NUM2"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_NUM3	 = atof(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_NUM3"]).c_str());
			CRSF_KSD11[iPos1][iPos2].KIKA_PRT	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKA_PRT"]).c_str());
			CRSF_KSD11[iPos1][iPos2].VALUE_TYPE	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["VALUE_TYPE"]).c_str());
			CRSF_KSD11[iPos1][iPos2].VALUE_DECI	 = atoi(Null_S(Q_CRSub_KSD11->FieldValues["VALUE_DECI"]).c_str());
			strcpy(CRSF_KSD11[iPos1][iPos2].SKTYMD		 , Null_S(Q_CRSub_KSD11->FieldValues["SKTYMD"]).c_str());
			CRSF_KSD11[iPos1][iPos2].SOKU_VAL_SU = atoi(Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL_SU"]).c_str());
			strcpy(CRSF_KSD11[iPos1][iPos2].UPDCHR		 , Null_S(Q_CRSub_KSD11->FieldValues["UPDCHR"]).c_str());

            //2003.06.10 E.Takase Add
            CRSF_KSD11[iPos1][iPos2].KIKI_NO 	= atoi(Null_S(Q_CRSub_KSD11->FieldValues["KIKI_NO"]).c_str());
            CRSF_KSD11[iPos1][iPos2].KOMK_NO 	= atoi(Null_S(Q_CRSub_KSD11->FieldValues["KOMK_NO"]).c_str());


			//測定値1,・・・・
			sBufSOKUVAL[0] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL01"]);
			sBufSOKUVAL[1] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL02"]);
			sBufSOKUVAL[2] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL03"]);
			sBufSOKUVAL[3] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL04"]);
			sBufSOKUVAL[4] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL05"]);
			sBufSOKUVAL[5] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL06"]);
			sBufSOKUVAL[6] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL07"]);
			sBufSOKUVAL[7] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL08"]);
			sBufSOKUVAL[8] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL09"]);
			sBufSOKUVAL[9] =  Null_S(Q_CRSub_KSD11->FieldValues["SOKU_VAL10"]);
	        if ( CRSF_KSD11[iPos1][iPos2].SOKU_VAL_SU > 10 ) {
		        n = 10;
	        } else {
		        n = CRSF_KSD11[iPos1][iPos2].SOKU_VAL_SU;
	        }

            sBufWtiteStr = "";
	        for ( i = 0; i < n; i++ ) {
		        sBufWtiteStr += sBufSOKUVAL[i] + ",";
	        }

			//測定数が10～なら例外テーブルから測定値取得
			if ( CRSF_KSD11[iPos1][iPos2].SOKU_VAL_SU > 10 ) {
				sBufSQL = "SELECT * FROM KSD12";
				sBufSQL += " WHERE DTKSHIN ='" + Null_S(Q_CRSub_KSD11->FieldValues["DTKSHIN"]) + "'";
				sBufSQL += " AND LOTNO = '" + Null_S(Q_CRSub_KSD11->FieldValues["LOTNO"]) + "'";
				sBufSQL += " AND BNKT_UNQ_NO = " + Null_S(Q_CRSub_KSD11->FieldValues["BNKT_UNQ_NO"]);
				sBufSQL += " ORDER BY SOKU_NO";
				Q_CRSub_KSD12->Close();
				Q_CRSub_KSD12->SQL->Clear();
				Q_CRSub_KSD12->SQL->Add(sBufSQL);
				Q_CRSub_KSD12->Open();
				Q_CRSub_KSD12->Active = true;
				while(Q_CRSub_KSD12->Eof == false) {
                    //2003.06.11 E.Takase Edit
					//sBufWtiteStr += Null_S(Q_CRSub_KSD12->FieldValues["DISP_VAL"]) + ",";
					sBufWtiteStr += Null_S(Q_CRSub_KSD12->FieldValues["SOKU_VAL"]) + ",";
					Q_CRSub_KSD12->Next();
				}
			}
            strcpy(CRSF_KSD11[iPos1][iPos2].WtiteStr,sBufWtiteStr.c_str());

	        //ロット毎の日付の種類
	        sBuf = "," + AnsiString(CRSF_KSD11[iPos1][iPos2].SKTYMD) + ",";
	        iBuf = sCRSF_KSD11_SKTYMDStr->Strings[iPos1].AnsiPos(sBuf);
	        if ( iBuf > 0 ) {
	            //既に登録されている
	            //SKTYMD_IDにセット
	            CRSF_KSD11[iPos1][iPos2].SKTYMD_ID = (iBuf - 1) / 9;
	        } else {
	            CRSF_KSD11[iPos1][iPos2].SKTYMD_ID = iCRSF_KSD11_SKTYMDNum[iPos1];
	            if ( sCRSF_KSD11_SKTYMDMin->Strings[iPos1] == "" ) {
	                sCRSF_KSD11_SKTYMDMin->Strings[iPos1] = CRSF_KSD11[iPos1][iPos2].SKTYMD;
	            } else {
	                if ( sCRSF_KSD11_SKTYMDMin->Strings[iPos1] > CRSF_KSD11[iPos1][iPos2].SKTYMD ) {
	                    sCRSF_KSD11_SKTYMDMin->Strings[iPos1] = CRSF_KSD11[iPos1][iPos2].SKTYMD;
	                }
	            }
	            //sCRSF_KSD11_SKTYMDStr->Strings[iPos1] += AnsiString(CRSF_KSD11[iPos1][iPos2].SKTYMD) + ",";
	            sCRSF_KSD11_SKTYMDStr->Strings[iPos1] = sCRSF_KSD11_SKTYMDStr->Strings[iPos1] + AnsiString(CRSF_KSD11[iPos1][iPos2].SKTYMD) + ",";
	            iCRSF_KSD11_SKTYMDNum[iPos1]++;
	        }

            iCRSF_KSD11_Num2[iPos1]++;
        }


		Q_CRSub_KSD11->Next();
	}
    //ロット毎の日付種類数MAXを取得
    for ( i = 0; i < iCRSF_KSD11_Num1; i++ ) {
        if ( iCRSF_KSD11_SKTYMDNumMax < iCRSF_KSD11_SKTYMDNum[i] ) {
            iCRSF_KSD11_SKTYMDNumMax = iCRSF_KSD11_SKTYMDNum[i];
        }
    }

    //ロット毎の日付種類数MAXでループしてCSVファイルに出力
    for ( i = 0; i < iCRSF_KSD11_SKTYMDNumMax; i++ ) {
        memset( CRSF_KSD12, (int)NULL, sizeof(struct TCRSF_KSD02)*iCRSF_KSD02_MAX );
        //2003.05.26 E.Takase Add ↓
        for ( j = 0; j < iCRSF_KSD01_MAX; j++ ) {
        	sCRSF_KSD11_UPDCHR->Strings[j] = "";
        	sCRSF_KSD11_SKTYMD->Strings[j] = "";
        }
        //2003.05.26 E.Takase Add ↑
        //2003.05.26 E.Takase コメント ↓
        //memset( sCRSF_KSD11_UPDCHR, (int)NULL, sizeof(AnsiString)*iCRSF_KSD02_MAX );
        //memset( sCRSF_KSD11_SKTYMD, (int)NULL, sizeof(AnsiString)*iCRSF_KSD02_MAX );
        //2003.05.26 E.Takase コメント ↑

        //2003.05.26 E.Takase Add ↓
	    //2003.06.10 E.Takase Edit memset( iCRSF_KSD11_OUTFLAG, (int)NULL, sizeof(int)*iCRSF_KSD11_MAX );
	    memset( iCRSF_KSD11_OUTFLAG, (int)NULL, sizeof(int)*iCRSF_KSD01_MAX );
        //2003.05.26 E.Takase Add ↑
        //2003.05.26 E.Takase コメント ↓
        //memset( iCRSF_KSD11_OUTFLAG, (int)NULL, sizeof(int)*iCRSF_KSD02_MAX );
        //2003.05.26 E.Takase コメント ↑

        iCRSF_KSD12_Num = 0;
        sBufFileOut = "";
        sBufFileOut_Day = "";
        //現在のロットの種類数チェック
        //if ( iCRSF_KSD11_SKTYMDNum[i] > i ) {
            for ( j = 0; j < iCRSF_KSD02_Num; j++ ) {
                for ( n = 0; n < iCRSF_KSD11_Num1; n++ ) {
                    for ( m = 0; m < iCRSF_KSD11_Num2[n]; m++ ) {
                        //i番目の日にj項目が測定されているか？

                        // 2003/10/21 A.Tamura ここに[TANI]は必要か？
                        // 2003/10/22 E.Takase Add ここに[TANI]は必要
                        if ( CRSF_KSD11[n][m].SKTYMD_ID == i &&
                             strcmp(CRSF_KSD11[n][m].KOMK_NM , CRSF_KSD02[j].KOMK_NM ) == 0 &&
                             strcmp(CRSF_KSD11[n][m].KOMK_SUB , CRSF_KSD02[j].KOMK_SUB ) == 0 &&
                             CRSF_KSD11[n][m].KIKI_NO == CRSF_KSD02[j].KIKI_NO  &&
                             CRSF_KSD11[n][m].KOMK_NO == CRSF_KSD02[j].KOMK_NO  &&
                             strcmp(CRSF_KSD11[n][m].TANI , CRSF_KSD02[j].TANI ) == 0 ) {
                            //測定されているので出力
                            CRSF_KSD11[n][m].Write_FLG = 1;
                            //縦（測定項目）位置の取得
                            iPos1 = -1;
                            for ( l = 0; l < iCRSF_KSD12_Num; l++ ) {
		                        // 2003/10/21 A.Tamura ここに[TANI]は必要か？
                                // 2003/10/22 E.Takase Add ここに[TANI]は必要
                                if ( strcmp(CRSF_KSD11[n][m].KOMK_NM   , CRSF_KSD12[l].KOMK_NM ) == 0  &&
                                     strcmp(CRSF_KSD11[n][m].KOMK_SUB  , CRSF_KSD12[l].KOMK_SUB ) == 0  &&
                             		 CRSF_KSD11[n][m].KIKI_NO == CRSF_KSD12[l].KIKI_NO  &&
                             		 CRSF_KSD11[n][m].KOMK_NO == CRSF_KSD12[l].KOMK_NO   &&
                             		 strcmp(CRSF_KSD11[n][m].TANI   , CRSF_KSD12[l].TANI ) == 0   ) {
                                    iPos1 = l;
                                    break;
                                }
                            }
                            if ( iPos1 < 0 ) {
                                iPos1 = iCRSF_KSD12_Num;

								strcpy(CRSF_KSD12[iPos1].KOMK_NM  	, CRSF_KSD11[n][m].KOMK_NM);		//a測定項目名称
								strcpy(CRSF_KSD12[iPos1].KOMK_SUB 	, CRSF_KSD11[n][m].KOMK_SUB);		//a測定項目サブ名称
								strcpy(CRSF_KSD12[iPos1].TANI	  	, CRSF_KSD11[n][m].TANI);			//a単位
								CRSF_KSD12[iPos1].KIKA_TYPE		= CRSF_KSD11[n][m].KIKA_TYPE;		//b規格タイプ
								CRSF_KSD12[iPos1].KIKA_KIND		= CRSF_KSD11[n][m].KIKA_KIND;		//b規格種類
								CRSF_KSD12[iPos1].KIKA_DECI		= CRSF_KSD11[n][m].KIKA_DECI;		//b規格小数点以下桁数
								CRSF_KSD12[iPos1].KIKA_NUM1		= CRSF_KSD11[n][m].KIKA_NUM1;		//b規格値1
								CRSF_KSD12[iPos1].KIKA_NUM2		= CRSF_KSD11[n][m].KIKA_NUM2;		//b規格値2
								CRSF_KSD12[iPos1].KIKA_NUM3		= CRSF_KSD11[n][m].KIKA_NUM3;		//b規格値3
								CRSF_KSD12[iPos1].KIKA_PRT  	= CRSF_KSD11[n][m].KIKA_PRT;		//b上限下限値の印刷
								CRSF_KSD12[iPos1].VALUE_TYPE	= CRSF_KSD11[n][m].VALUE_TYPE;		//b,c測定値表現
								CRSF_KSD12[iPos1].VALUE_DECI	= CRSF_KSD11[n][m].VALUE_DECI;		//c測定値小数点以下桁数

								sBufSKTYMD = AnsiString(CRSF_KSD11[n][m].SKTYMD);			//測定日(分割用)
                                if ( Trim(sBufSKTYMD) != "" ) {
			                        sBufSKTYMD.Insert("/",7);
			                        sBufSKTYMD.Insert("/",5);
                                }
                                strcpy(CRSF_KSD12[iPos1].SKTYMD,sBufSKTYMD.c_str());

					            //2003.06.10 E.Takase Add
					            CRSF_KSD12[iPos1].KIKI_NO 	= CRSF_KSD11[n][m].KIKI_NO;
					            CRSF_KSD12[iPos1].KOMK_NO 	= CRSF_KSD11[n][m].KOMK_NO;


                                iCRSF_KSD12_Num++;
                            }

                            //2004.09.27 E.Takase Edit
                            //測定日
                            //sCRSF_KSD11_SKTYMD->Strings[n] = AnsiString(CRSF_KSD12[iPos1].SKTYMD);
							sBufSKTYMD = AnsiString(CRSF_KSD11[n][m].SKTYMD);			//測定日(分割用)
                            if ( Trim(sBufSKTYMD) != "" ) {
		                        sBufSKTYMD.Insert("/",7);
		                        sBufSKTYMD.Insert("/",5);
                            }
                            sCRSF_KSD11_SKTYMD->Strings[n] = sBufSKTYMD;

                            //データ詳細部(sRepData6_3)出力データ作成（出力は後で）
	                        //ページ番号,データ種別（ここでは2），ロット位置，分割何個目か,
                            //測定日,測定数,測定値表現,測定値小数点以下桁数,測定値1,・・・・
	                        sprintf( cBufFileOut,"%d,2,%d,%d,%d,%s,%d,%d,%d,%s,\n",
                                                    iCRSF_PageNo,n,iPos1,i,CRSF_KSD12[iPos1].SKTYMD,
                                                    CRSF_KSD11[n][m].VALUE_TYPE,
                                                    CRSF_KSD11[n][m].VALUE_DECI,
                                                    CRSF_KSD11[n][m].SOKU_VAL_SU,
                                                    CRSF_KSD11[n][m].WtiteStr);
	                        //sprintf( cBufFileOut,"%d,2,%d,%d,%d,%s,\n",
                            //                        iCRSF_PageNo,n,m,
                            //                        CRSF_KSD11[n][m].SOKU_VAL_SU,CRSF_KSD11[n][m].WtiteStr);
                            sBufFileOut += cBufFileOut;
                            iRDiMax++;
                            if ( iRDjMax < CRSF_KSD11[n][m].SOKU_VAL_SU ) {
                                iRDjMax = CRSF_KSD11[n][m].SOKU_VAL_SU;
                            }

                            //測定者
                            if ( sCRSF_KSD11_UPDCHR->Strings[n] == "" ) {
                                sCRSF_KSD11_UPDCHR->Strings[n] = AnsiString(CRSF_KSD11[n][m].UPDCHR);
                            } else {
                                if ( sCRSF_KSD11_UPDCHR->Strings[n] > AnsiString(CRSF_KSD11[n][m].UPDCHR) ) {
                                    sCRSF_KSD11_UPDCHR->Strings[n] = AnsiString(CRSF_KSD11[n][m].UPDCHR);
                                }
                            }
                            iCRSF_KSD11_OUTFLAG[n] = 1;
                         }
                    }
                }
            }

            if ( sBufFileOut != "" ) {
                //データ詳細部(sRepData6_3)にデータ出力
                //日付、測定者
                for ( a = 0; a < iCRSF_KSD11_Num1; a++ ) {
                    //測定者はｺｰﾄﾞで入っているので氏名に変換
                    if ( iCRSF_KSD11_OUTFLAG[a] == 1 ) {
                        sBufSKTYMD = "";
                        sBufTANNAM = "";
                        
                        sBufSKTYMD = sCRSF_KSD11_SKTYMD->Strings[a];

                        sBufTANNAM = GetTANNAM(sCRSF_KSD11_UPDCHR->Strings[a]);
                        
                        fprintf( fCRSF_stream3,"%d,1,%d,%d,%s,%s,\n",
                                        iCRSF_PageNo,a,i,
                                        sBufSKTYMD.c_str(),sBufTANNAM.c_str());
                    	iRDiMax++;
                    }
                }

                //測定値
                fprintf( fCRSF_stream3,"%s",sBufFileOut.c_str());
                


                //測定項目データを出力
				fprintf( fCRSF_stream2,"*,3,SKTYMD_B,\n%d,\n",i);
				fprintf( fCRSF_stream2,"*,4,KOMK_NM_B,\n");

				for ( a = 0; a < iCRSF_KSD12_Num; a++ ) {
					fprintf( fCRSF_stream2,"%d,%d,%s,%s,%s,%d,%d,%d,%lf,%lf,%lf,%d,,\n",
									a,
                                    i,
									CRSF_KSD12[a].KOMK_NM,
									CRSF_KSD12[a].KOMK_SUB,
									CRSF_KSD12[a].TANI,
									CRSF_KSD12[a].KIKA_TYPE,
									CRSF_KSD12[a].KIKA_KIND,
									CRSF_KSD12[a].KIKA_DECI,
									CRSF_KSD12[a].KIKA_NUM1,
									CRSF_KSD12[a].KIKA_NUM2,
									CRSF_KSD12[a].KIKA_NUM3,
									CRSF_KSD12[a].KIKA_PRT
									);
					//fprintf( fCRSF_stream2,"%d,%s,%s,%s,%d,%d,%d,%lf,%lf,%lf,%d,%d,%d,%s,\n",
					//				a,
					//				CRSF_KSD12[a].KOMK_NM.c_str(),
					//				CRSF_KSD12[a].KOMK_SUB.c_str(),
					//				CRSF_KSD12[a].TANI.c_str(),
					//				CRSF_KSD12[a].KIKA_TYPE,
					//				CRSF_KSD12[a].KIKA_KIND,
					//				CRSF_KSD12[a].KIKA_DECI,
					//				CRSF_KSD12[a].KIKA_NUM1,
					//				CRSF_KSD12[a].KIKA_NUM2,
					//				CRSF_KSD12[a].KIKA_NUM3,
					//				CRSF_KSD12[a].KIKA_PRT,
					//				CRSF_KSD12[a].VALUE_TYPE,
					//				CRSF_KSD12[a].VALUE_DECI,
					//				CRSF_KSD12[a].SKTYMD.c_str()
					//				);
				}

            }
        //}

        sBufFileOut = "";
    }
}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：担当者コードから担当者名を取得します
//
//  機能説明
//    GetiCRSF_KSD01_Pos5で使用します。
//    GetiCRSF_KSD01_Pos6・SetCRSF_KSD11で使用します。
//
//  パラメタ説明
//    AnsiString sTANSYA		：担当者コード
//
//  戻り値
//    AnsiString 				：担当者名
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetTANNAM(AnsiString sTANSYA)
{
	AnsiString sBuf;
	AnsiString sBufTANNAM;

    if ( Trim(sTANSYA) == "" ) {
    	return(" ");
    }
	sBufTANNAM = " ";

	//ユーザー名検索
	// Initial Query
	Q_CRSub_TANSYA->Close();
	Q_CRSub_TANSYA->SQL->Clear();

	// 問合せ実行
	sBuf = "SELECT TANSYA, TANNAM, SZKBSY FROM SM12S WHERE  TANSYA = ";
	sBuf += sTANSYA;

	Q_CRSub_TANSYA->SQL->Add(sBuf);
	Q_CRSub_TANSYA->Open();
	Q_CRSub_TANSYA->Active = true;

	if (Q_CRSub_TANSYA->Eof == false ) {
		sBufTANNAM = Null_S(Q_CRSub_TANSYA->FieldValues["TANNAM"]);
	}
	return(sBufTANNAM);


}
//---------------------------------------------------------------------------
//
//  概要
//    自作関数					：構造体の初期化
//
//  機能説明
//    CRSF_KSD11を初期化します。
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
void __fastcall TForm1::FormatCRSF_KSD11(void)
{
    int i;
    int j;

    for ( i = 0; i < iCRSF_KSD01_MAX; i++ ) {
        for ( j = 0; j < iCRSF_KSD11_MAX; j++ ) {
			strcpy(CRSF_KSD11[i][j].KOMK_NM  	 , "");
			strcpy(CRSF_KSD11[i][j].KOMK_SUB     , "");
			strcpy(CRSF_KSD11[i][j].TANI	 	 , "");
			CRSF_KSD11[i][j].KIKA_TYPE   = 0;
			CRSF_KSD11[i][j].KIKA_KIND	 = 0;
			CRSF_KSD11[i][j].KIKA_DECI	 = 0;
			CRSF_KSD11[i][j].KIKA_NUM1 	 = 0;
			CRSF_KSD11[i][j].KIKA_NUM2 	 = 0;
			CRSF_KSD11[i][j].KIKA_NUM3	 = 0;
			CRSF_KSD11[i][j].KIKA_PRT	 = 0;
			CRSF_KSD11[i][j].VALUE_TYPE	 = 0;
			CRSF_KSD11[i][j].VALUE_DECI	 = 0;
			strcpy(CRSF_KSD11[i][j].SKTYMD 	 , "");
			strcpy(CRSF_KSD11[i][j].UPDCHR 	 , "");
			CRSF_KSD11[i][j].SOKU_VAL_SU = 0;
			strcpy(CRSF_KSD11[i][j].WtiteStr  	 , "");
            CRSF_KSD11[i][j].SKTYMD_ID   = 0;
            CRSF_KSD11[i][j].Write_FLG   = 0;  
            CRSF_KSD11[i][j].KIKI_NO  	 = 0;  //機器No		//2003.06.10 E.Takase Add
            CRSF_KSD11[i][j].KOMK_NO  	 = 0;  //測定項目No	//2003.06.10 E.Takase Add
        }
    }

}

