//---------------------------------------------------------------------------
//
//  Unit2.cpp
//    【出荷検査システム－自動整理登録処理】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    高瀬　恵利
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：自動整理登録
//
//  機能説明
//    ①素材測定実績データ前回取り込み日時から中間検査DBの検索条件を作成
//    ②①の条件で中間検査DBからデータを取得し出荷検査DBへ移行
//    ③素材測定実績データ（KSD21）の更新回数および素材判定を更新
//
//  パラメタ説明
//    なし
//
//  戻り値
//    int					：更新した得意先品番・ロット数
//
//  備考
//    なし。
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::AutoEntry()
{
	int iRtn;
	AnsiString sRtn;
	int i;
	AnsiString FileName;
	FILE *fp;

	//FixStr初期化
	FormatFixStr();

	//TStrings初期化
	//sDTKSHIN	= new TStringList;    	//得意先品番
	//sLOTNO		= new TStringList; 		//ロットNO
	sDTKSHIN->Clear();
	sHINBAN->Clear();
	sLOTNO->Clear();
	isDTKSHINNum = 0;

    FileName = Application->ExeName;
    FileName = FileName.SubString(1,FileName.Length()-4);
    FileName = FileName + ".log";
	if( (fp = fopen( FileName.c_str(), "w" )) != NULL ){
		fclose(fp);
	}

	//素材測定実績データ前回取り込み日時データ取得
	//iRtn = GetKSD29("1");
   	KSD29.STRWHERE = " WHERE ( ADDYMD >='" + KSD29.UPDYMD + "'" +
						  " OR UPDYMD >='" + KSD29.UPDYMD + "' ) ";


	//素材測定実績明細データ取得(KDX1)
	for ( i = 0; i < FixStrNum; i++ ) {
		iRtn = GetKD_1(i);
	}
	//iRtn = GetKD_1(14);

	//素材測定実績データ（KSD21）の更新回数および素材判定を更新
	for ( i = 0; i < isDTKSHINNum; i++ ) {
		sRtn = UpdDataKSD21_UPDCNT(sDTKSHIN->Strings[i],sLOTNO->Strings[i]);
		WriteErrLog(sRtn,"UpdDataKSD21_UPDCNT",KSD21.DTKSHIN,KSD21.LOTNO);
	}

	return(isDTKSHINNum);
}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：素材測定実績明細データ取得(KDX1)
//
//  機能説明
//    ①KDX1からデータを取得し、Q_KD_1にセット
//    ②Q_KD_1を1件ずつ見ていき、KDS21・KDS22・KDS23を検索しデータベースに登録
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    int					：0=検索成功 -1=検索失敗
//
//  備考
//    なし。
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::GetKD_1(int iNo)
{
	AnsiString sBuf;
	AnsiString sErr;
	int iRtn;
	int iSOKUTEI_SU;
	int iSOKUTEI_SU2;
	AnsiString sSOKUTEI_SU2;
	int i;
	int iSOKU_VAL_SU;
	int iFlag;
	AnsiString sKEIJYO_KBN;
	int iKEIJYO_KBN_OK;
    int LogCnt = 0;

	//KDX1からデータを取得し、Q_KD_1にセット
	iRtn = SrchKD_1(iNo);
	//検索結果０件の場合は終了
	if ( iRtn < 0 ) {
		return(-1);
	}

	//Q_KD_1を1件ずつ見ていき、KDS21・KDS22・KDS23を検索
	Q_KD_1->First();
	while( !Q_KD_1->Eof ) {

    	LogCnt++;
        //フォームに LogCntを表示
        Lbl_3->Caption = FixStr[iNo].TABLE1 + "からデータ取得・登録中[" + IntToStr(LogCnt) + "]";
        Form1->Refresh();

		//ブラシ幅・内径・ブラシ縦・外径の場合
		//形状区分により、処理を続行するかを決定
		iKEIJYO_KBN_OK = 0;
		switch (iNo)
		{
			case 1: //ブラシ幅
			case 3: //ブラシ縦
				//形状区分がコンミ以外の場合 実行
				sKEIJYO_KBN = GetKEIJYO_KBN();
				if ( sKEIJYO_KBN != "5" ) {
					iKEIJYO_KBN_OK = 0;
				} else {
					iKEIJYO_KBN_OK = 1;
				}
				break;

			case 2: //内径
			case 4: //外径
				//形状区分がコンミの場合 実行
				sKEIJYO_KBN = GetKEIJYO_KBN();
				if ( sKEIJYO_KBN == "5" ) {
					iKEIJYO_KBN_OK = 0;
				} else {
					iKEIJYO_KBN_OK = 1;
				}
				break;

			default: //その他 処理実行
				iKEIJYO_KBN_OK = 0;
				break;

		}

		if ( iKEIJYO_KBN_OK == 0 ) {
			//構造体にセット
			SetKD_1(iNo);

			//測定項目数が２以上の場合、例外テーブルを検索
			iSOKUTEI_SU = KD_1.SOKUTEI_SU.ToIntDef(0);
			if ( iSOKUTEI_SU > 2 ) {
				iRtn = SrchKD_2(iNo);
				if ( iRtn == 0 ) {
					//構造体にセット
					SetKD_2(iNo);
				}
			}

			//測定最小値・最大値・判定
			CalcKD_1(iNo);

			//構造体KSD21・KSD22・KSD23を初期化
			FormatKSD21(iNo);
			FormatKSD22(iNo);
			FormatKSD23(iNo);

			//得意先品番、ロットNoよりKSD21を検索
			KSD21.InsFlag = SrchKSD21(iNo);
			//得意先品番、ロットNoよりKSD22を検索
			KSD22.InsFlag = SrchKSD22(iNo);

			//測定実績数が10以上の場合、例外テーブルを検索
			if ( KSD22.InsFlag >= 0 ) {
				sSOKUTEI_SU2 = Null_S(Q_KSD22->FieldValues["SOKU_VAL_SU"]);
				iSOKUTEI_SU2 = sSOKUTEI_SU2.ToIntDef(0);
				if ( iSOKUTEI_SU2 > 10 ) {
					//得意先品番、ロットNoよりKSD23を検索
					KSD23.InsFlag = SrchKSD23(iNo);
					////構造体KSD23にセット
					//if ( KSD23.InsFlag > 0 ) {
					//	SetKSD23(iNo);
					//}
				}
			}

			//構造体KSD22にセット
			SetKSD22(iNo);
			//構造体KSD21にセット
			SetKSD21(iNo);

			//データベース登録
			//-KSD22
			if ( KSD22.InsFlag >= 0 ) {
				sErr = UpdDataKSD22();
				WriteErrLog(sErr,"UpdDataKSD22",KSD21.DTKSHIN,KSD21.LOTNO);
			} else {
				sErr = AddDataKSD22();
				WriteErrLog(sErr,"AddDataKSD22",KSD21.DTKSHIN,KSD21.LOTNO);
			}


			//-KSD23
			if ( KSD23.InsFlag >= 0 ) {
				sErr = DelDataKSD23();
				WriteErrLog(sErr,"DelDataKSD23",KSD21.DTKSHIN,KSD21.LOTNO);
			}
			iSOKU_VAL_SU = atoi(KSD22.SOKU_VAL_SU.c_str());
			if ( iSOKU_VAL_SU > 10 ) {
				for ( i = 10; i < iSOKU_VAL_SU; i++ ) {
					sErr = AddDataKSD23(i);
					WriteErrLog(sErr,"AddDataKSD23(" + IntToStr(i) + ")",KSD21.DTKSHIN,KSD21.LOTNO);
				}
			}

			//-KSD21
			if ( KSD21.InsFlag >= 0 ) {
				sErr = UpdDataKSD21();
				WriteErrLog(sErr,"UpdDataKSD21",KSD21.DTKSHIN,KSD21.LOTNO);
			} else {
				sErr = AddDataKSD21();
				WriteErrLog(sErr,"AddDataKSD21",KSD21.DTKSHIN,KSD21.LOTNO);
			}

			//最後に更新回数を設定するためのデータ
			iFlag = 0;
			for ( i = 0; i < isDTKSHINNum; i++ ) {
				if ( KSD21.DTKSHIN == sDTKSHIN->Strings[i] &&
					 KSD21.LOTNO   == sLOTNO->Strings[i] ) {
					iFlag = 1;
					break;
				}
			}
			if ( iFlag == 0 ) {
				sDTKSHIN->Add(KSD21.DTKSHIN);
				sLOTNO->Add(KSD21.LOTNO);
				isDTKSHINNum++;
			}
		}

		Q_KD_1->Next();
	}



	 return(0);
}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：測定値最大・最小・判定を判断
//
//  機能説明
//    KD_1のSOKUTEIから最大・最小・判定を取得します。
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    なし
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::CalcKD_1(int iNo)
{
	int i;
	int iSOKUTEI_SU;
	float fSOKUTEI;
	float fSOKUTE_MAX;
	float fSOKUTE_MIN;
	float fKIKA_NUM1;
	float fKIKA_NUM2;
	int iSOKUTE_OK;
	
	iSOKUTEI_SU = KD_1.SOKUTEI_SU.ToIntDef(0);
	fSOKUTE_MAX = atof(KD_1.SOKUTEI[0].c_str());
	fSOKUTE_MIN = atof(KD_1.SOKUTEI[0].c_str());
	iSOKUTE_OK  = 0;
	KD_1.SOKUTE_MAX = KD_1.SOKUTEI[0];
	KD_1.SOKUTE_MIN = KD_1.SOKUTEI[0];
	
	for ( i = 0; i < iSOKUTEI_SU; i++ ) {
		fSOKUTEI = atof(KD_1.SOKUTEI[i].c_str());
		//最大値
		if ( fSOKUTE_MAX < fSOKUTEI ) {
			fSOKUTE_MAX = fSOKUTEI;
			KD_1.SOKUTE_MAX = KD_1.SOKUTEI[i];
		}
		//最小値
		if ( fSOKUTE_MIN > fSOKUTEI ) {
			fSOKUTE_MIN = fSOKUTEI;
			KD_1.SOKUTE_MIN = KD_1.SOKUTEI[i];
		}
		//判定
		if ( iSOKUTE_OK == 0 ) {
			switch (iNo)
			{
				case 6: //取付強度 下限規格
					fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
					if ( fKIKA_NUM1 > fSOKUTEI ) {
						iSOKUTE_OK = 1;
					}
					break;

				case 7: //取付抵抗 上限規格
					fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
					if ( fKIKA_NUM1 < fSOKUTEI ) {
						iSOKUTE_OK = 1;
					}
					break;

                //2003.06.03 E.Takase
				case 16: //ヒストグラム（ブラシ厚さMin・Max）
				case 17: //ヒストグラム（ブラシ厚さCp・Cpk）
                    switch (FixStr[iNo].KIKA_KIND.ToIntDef(1)) {
                    	case 2:
							fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
							if ( fKIKA_NUM1 < fSOKUTEI ) { //上限規格
								iSOKUTE_OK = 1;
							}
							break;
                    	case 3:
							fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
							if ( fKIKA_NUM1 > fSOKUTEI ) { //下限規格
								iSOKUTE_OK = 1;
							}
                            break;
						default:
							fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
							fKIKA_NUM2 = atof(KD_1.KIKA_NUM2.c_str());
							if ( fKIKA_NUM1 > fSOKUTEI || fSOKUTEI > fKIKA_NUM2) { //両側規格
								iSOKUTE_OK = 1;
							}
                            break;
					}


					break;

				default: //その他 両側規格
					fKIKA_NUM1 = atof(KD_1.KIKA_NUM1.c_str());
					fKIKA_NUM2 = atof(KD_1.KIKA_NUM2.c_str());
					if ( fKIKA_NUM1 > fSOKUTEI || fSOKUTEI > fKIKA_NUM2) {
						iSOKUTE_OK = 1;
					}
					break;

			}
		}
	}

	KD_1.SOKUTE_OK = IntToStr(iSOKUTE_OK);

    //平均値の計算 ヒストグラムのみ    //2003.06.03 E.Takase
    if ( iNo == 16 || iNo == 17 ) {
    	KD_1.SOKUTE_AVE =  ( fSOKUTE_MAX + fSOKUTE_MIN ) / 2.0;
    }


}

/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：データ検索
//
//  機能説明
//    KDX1からデータを取得し、Q_KD_1にセット
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    int					：0=検索成功 -1=検索失敗
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::SrchKD_1(int iNo)
{
	AnsiString sBuf;

	//Initial Query
	Q_KD_1->Close();
	Q_KD_1->SQL->Clear();

    //2003.06.03 E.Takase
    if ( iNo == 16 || iNo == 17 ) {
		// 問合せ実行
		sBuf = "";
		//SELECT文
		sBuf += " SELECT  ";
		//共通フィールド1
		sBuf += " KENSA_YMD, SEQNO, HIST_KIKAK, ";
		sBuf += " DTKSCOD, DTKSHIN, ";
		sBuf += " LOTNO, HINBAN, ZISCOD, ZISNAM, ";
		//各素材検査によって異なるフィールド名
		sBuf += FixStr[iNo].F_SOKUTE_KBN + " As SOKUTE_KBN, ";
		sBuf += FixStr[iNo].F_KIKA_NUM1  + " As KIKA_NUM1, ";
		sBuf += FixStr[iNo].F_KIKA_NUM2  + " As KIKA_NUM2, ";
		sBuf += FixStr[iNo].F_KIKA_SUB1  + " As KIKA_SUB1, ";
		sBuf += FixStr[iNo].F_KIKA_SUB2  + " As KIKA_SUB2, ";
		sBuf += FixStr[iNo].F_KEIJYO_KBN + " As KEIJYO_KBN,";
		sBuf += FixStr[iNo].F_SOKUTEI_1  + " As SOKUTEI_1, ";
		sBuf += FixStr[iNo].F_SOKUTEI_2  + " As SOKUTEI_2, ";
		sBuf += FixStr[iNo].F_SOKUTEI_SU + " As SOKUTEI_SU,";
		sBuf += FixStr[iNo].F_SOKUTEI_NM + " As SOKUTEI_NM,";
		sBuf += FixStr[iNo].F_SOKUTE_AVE + " As SOKUTE_AVE,";
		//共通フィールド2
		sBuf += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, ";
		sBuf += " UPDCHR, UPDCNT, MEMO ";
                //20170417 Y.Onishi 工場区分追加
		sBuf += " , KOJOKBN ";
		//テーブル名
		sBuf += " FROM " + FixStr[iNo].TABLE1;
		//WHERE文
		sBuf += KSD29.STRWHERE;
		//- SOKUTE_KBN
	    if ( Trim(FixStr[iNo].W_SOKUTE_KBN) != "" ) {
			sBuf +=  " AND " + FixStr[iNo].W_SOKUTE_KBN;
		}

		//ORDER文
		sBuf += " ORDER BY DTKSHIN, LOTNO, KENSA_YMD,SEQNO " ;
    } else {
		// 問合せ実行
		sBuf = "";
		//SELECT文
		sBuf += " SELECT  ";
		//共通フィールド1
		sBuf += " KENSA_YMD, TOLEY_NO, SAMPLE_P, ";
		sBuf += " DTKSCOD, DTKSHIN, ";
		sBuf += " LOTNO, HINBAN, ZISCOD, ZISNAM, ";
		//各素材検査によって異なるフィールド名
		sBuf += FixStr[iNo].F_SOKUTE_KBN + " As SOKUTE_KBN, ";
		sBuf += FixStr[iNo].F_KIKA_NUM1  + " As KIKA_NUM1, ";
		sBuf += FixStr[iNo].F_KIKA_NUM2  + " As KIKA_NUM2, ";
		sBuf += FixStr[iNo].F_KIKA_SUB1  + " As KIKA_SUB1, ";
		sBuf += FixStr[iNo].F_KIKA_SUB2  + " As KIKA_SUB2, ";
		sBuf += FixStr[iNo].F_KEIJYO_KBN + " As KEIJYO_KBN,";
		sBuf += FixStr[iNo].F_SOKUTEI_1  + " As SOKUTEI_1, ";
		sBuf += FixStr[iNo].F_SOKUTEI_2  + " As SOKUTEI_2, ";
		sBuf += FixStr[iNo].F_SOKUTEI_SU + " As SOKUTEI_SU,";
		sBuf += FixStr[iNo].F_SOKUTEI_NM + " As SOKUTEI_NM,";
		sBuf += FixStr[iNo].F_SOKUTE_AVE + " As SOKUTE_AVE,";
		//共通フィールド2
		sBuf += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, ";
		sBuf += " UPDCHR, UPDCNT, MEMO ";
                //20170417 Y.Onishi 工場区分追加
		sBuf += " , KOJOKBN ";
		//テーブル名
		sBuf += " FROM " + FixStr[iNo].TABLE1;
		//WHERE文
		sBuf += KSD29.STRWHERE;
		//- SOKUTE_KBN
	    if ( Trim(FixStr[iNo].W_SOKUTE_KBN) != "" ) {
			sBuf +=  " AND " + FixStr[iNo].W_SOKUTE_KBN;
		}

		//ORDER文
		sBuf += " ORDER BY DTKSHIN, LOTNO " ;

    }

	//Test
	sBufSQL = sBuf;

	Q_KD_1->SQL->Add(sBuf);
	Q_KD_1->Open();
	Q_KD_1->Active = true;

	if ( Q_KD_1->Bof && Q_KD_1->Eof ) {
		//検索結果 ０件
		return(-1);
	}

	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：構造体にデータを代入
//
//  機能説明
//    SrchKD_1での検索結果を構造体（KD_1）にセット
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    なし
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::SetKD_1(int iNo)
{

	//Q_KD_1を構造体にセット
	KD_1.KENSA_YMD  = Null_S(Q_KD_1->FieldValues["KENSA_YMD"]);

    //2003.06.03 E.Takase
    if ( iNo == 16 || iNo == 17 ) {
		KD_1.TOLEY_NO   = "";
		KD_1.SAMPLE_P   = "";

        //規格  HIST_KIKAK
        if ( iNo == 16 ) {
        	switch ( Null_S(Q_KD_1->FieldValues["HIST_KIKAK"]).ToIntDef(1) ) {
        		case 1: FixStr[iNo].KIKA_KIND = "1";	break;
        		case 2: FixStr[iNo].KIKA_KIND = "3";	break;
        		case 3: FixStr[iNo].KIKA_KIND = "2";	break;
            }
        } else {
        	 FixStr[iNo].KIKA_KIND = "3";
        }

    } else {
		KD_1.TOLEY_NO   = Null_S(Q_KD_1->FieldValues["TOLEY_NO"]);
		KD_1.SAMPLE_P   = Null_S(Q_KD_1->FieldValues["SAMPLE_P"]);
    }

	KD_1.SOKUTEI_SU = Null_S(Q_KD_1->FieldValues["SOKUTEI_SU"]);
	KD_1.DTKSHIN    = Null_S(Q_KD_1->FieldValues["DTKSHIN"]);
	KD_1.LOTNO      = Null_S(Q_KD_1->FieldValues["LOTNO"]);
	KD_1.HINBAN 	= Null_S(Q_KD_1->FieldValues["HINBAN"]);
	KD_1.ZISCOD 	= Null_S(Q_KD_1->FieldValues["ZISCOD"]);
	KD_1.ZISNAM 	= Null_S(Q_KD_1->FieldValues["ZISNAM"]);
	KD_1.KIKA_NUM1 	= Null_S(Q_KD_1->FieldValues["KIKA_NUM1"]);
	KD_1.KIKA_NUM2 	= Null_S(Q_KD_1->FieldValues["KIKA_NUM2"]);
	KD_1.KIKA_SUB1 	= Null_S(Q_KD_1->FieldValues["KIKA_SUB1"]);
	KD_1.KIKA_SUB2 	= Null_S(Q_KD_1->FieldValues["KIKA_SUB2"]);
	KD_1.KEIJYO_KBN = Null_S(Q_KD_1->FieldValues["KEIJYO_KBN"]);
	KD_1.SOKUTEI[0] = Null_S(Q_KD_1->FieldValues["SOKUTEI_1"]);
	KD_1.SOKUTEI[1] = Null_S(Q_KD_1->FieldValues["SOKUTEI_2"]);
	KD_1.SOKUTEI_SU = Null_S(Q_KD_1->FieldValues["SOKUTEI_SU"]);
	KD_1.SOKUTEI_NM = Null_S(Q_KD_1->FieldValues["SOKUTEI_NM"]);
	KD_1.SOKUTE_AVE = Null_S(Q_KD_1->FieldValues["SOKUTE_AVE"]);
	KD_1.ADDYMD 	= Null_S(Q_KD_1->FieldValues["ADDYMD"]);
	KD_1.ADDTIM 	= Null_S(Q_KD_1->FieldValues["ADDTIM"]);
	KD_1.UPDYMD 	= Null_S(Q_KD_1->FieldValues["UPDYMD"]);
	KD_1.UPDTIM 	= Null_S(Q_KD_1->FieldValues["UPDTIM"]);
	KD_1.UPDCHR 	= Null_S(Q_KD_1->FieldValues["UPDCHR"]);
	KD_1.UPDCNT 	= Null_S(Q_KD_1->FieldValues["UPDCNT"]);
	KD_1.MEMO		= Null_S(Q_KD_1->FieldValues["MEMO"]);

    //2003.08.22 E.Takase
	//if ( Trim(KD_1.UPDYMD) == "" ) {
	//	KD_1.SKTYMD = KD_1.ADDYMD;
	//} else {
	//	KD_1.SKTYMD = KD_1.UPDYMD;
	//}
	//KD_1.SKTYMD = KD_1.KENSA_YMD;
    //2004.02.26 E.Takase 測定日は ADDYMD
    KD_1.SKTYMD = KD_1.ADDYMD;

    //20170417 Y.Onishi 工場区分追加
    KD_1.KOJOKBN 	= Null_S(Q_KD_1->FieldValues["KOJOKBN"]);

}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：データ検索
//
//  機能説明
//    KDX2からデータを取得し、Q_KD_2にセット
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    int					：0=検索成功 -1=検索失敗
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::SrchKD_2(int iNo)
{
	AnsiString sBuf;

    //2003.06.03 E.Takase
    if ( iNo == 16 || iNo == 17 ) {
    	return(0);
    }
	//Initial Query
	Q_KD_2->Close();
	Q_KD_2->SQL->Clear();

	// 問合せ実行
	sBuf = "";
	//SELECT文
	sBuf += " SELECT  ";
	//共通フィールド1
	sBuf += " KENSA_YMD,TOLEY_NO,SAMPLE_P, " ;
	sBuf += " SOKUTEI_NO, ";
	//各素材検査によって異なるフィールド名
	sBuf += FixStr[iNo].F_SOKUTEICHI  + " As SOKUTEICHI ";
	//テーブル名
	sBuf += " FROM " + FixStr[iNo].TABLE2;
	//WHERE文
	sBuf += " WHERE  ";
	sBuf += " KENSA_YMD ='" + KD_1.KENSA_YMD + "' AND ";
	sBuf += " TOLEY_NO ="   + KD_1.TOLEY_NO + " AND ";
	sBuf += " SAMPLE_P ="   + KD_1.SAMPLE_P;
        //20170417 Y.Onishi 工場区分追加
	sBuf += " AND KOJOKBN ="   + KD_1.KOJOKBN;
	//ORDER文
	sBuf += " ORDER BY SOKUTEI_NO " ;


	Q_KD_2->SQL->Add(sBuf);
	Q_KD_2->Open();
	Q_KD_2->Active = true;

	if ( Q_KD_2->Bof && Q_KD_2->Eof ) {
		//検索結果 ０件
		return(-1);
	}

	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：構造体にデータを代入
//
//  機能説明
//    SrchKD_2での検索結果を構造体（KD_2）にセット
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    なし
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::SetKD_2(int iNo)
{
	int i;

    //2003.06.03 E.Takase
    if ( iNo == 16 || iNo == 17 ) {
    	return;
    }

	//Q_KD_2を構造体にセット
	i = 2;
	Q_KD_2->First();
	while( !Q_KD_2->Eof ) {
		KD_1.SOKUTEI[i] = Null_S(Q_KD_2->FieldValues["SOKUTEICHI"]);
		i++;
		Q_KD_2->Next();
	}


}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：データ検索
//
//  機能説明
//    KSD21からデータを取得し、Q_KSD21にセット
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    int					：0=検索成功 -1=検索失敗
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::SrchKSD21(int iNo)
{
	AnsiString sBuf;

	//Initial Query
	Q_KSD21->Close();
	Q_KSD21->SQL->Clear();

	// 問合せ実行
	sBuf = "";
	//SELECT文
	sBuf += " SELECT ";
	sBuf += " DTKSHIN, LOTNO, HINBAN, DTKSCOD, ";
	sBuf += " DTKSNAM, ZISNAM, SOKUTEI_NUM, ";
	sBuf += " SOZAI_OK, MEMO, SKTYMD, ";
	sBuf += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, ";
	sBuf += " UPDCHR, UPDCNT ";
	//テーブル名
	sBuf += " FROM KSD21 ";
	//WHERE文
	sBuf += " WHERE  ";
	sBuf += " DTKSHIN ='" + KD_1.DTKSHIN + "' AND ";
	sBuf += " HINBAN  ='" + KD_1.HINBAN + "' AND ";
	sBuf += " LOTNO   ='" + KD_1.LOTNO + "' ";


	Q_KSD21->SQL->Add(sBuf);
	Q_KSD21->Open();
	Q_KSD21->Active = true;

	if ( Q_KSD21->Bof && Q_KSD21->Eof ) {
		//検索結果 ０件
		return(-1);
	}

	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：構造体にデータを代入
//
//  機能説明
//    SrchKSD21での検索結果を構造体（KSD21）にセット
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    なし
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::SetKSD21(int iNo)
{
	int iRtn;
	int iUPDCHR1;
	int iUPDCHR2;

	if ( KSD21.InsFlag == 0 ) {
		KSD21.DTKSCOD = Null_S(Q_KSD21->FieldValues["DTKSCOD"]);
		KSD21.DTKSNAM = Null_S(Q_KSD21->FieldValues["DTKSNAM"]);
		//KSD21.SOKUTEI_NUM = Null_S(Q_KSD21->FieldValues["SOKUTEI_NUM"]);
		//KSD21.SOZAI_OK = Null_S(Q_KSD21->FieldValues["SOZAI_OK"]);
		KSD21.MEMO = Null_S(Q_KSD21->FieldValues["MEMO"]);
		KSD21.SKTYMD = Null_S(Q_KSD21->FieldValues["SKTYMD"]);
		//KSD21.ADDYMD = Null_S(Q_KSD21->FieldValues["ADDYMD"]);
		//KSD21.ADDTIM = Null_S(Q_KSD21->FieldValues["ADDTIM"]);
		//KSD21.UPDYMD = FormatDateTime("yyyymmdd",Now());// 更新日
		//KSD21.UPDTIM = FormatDateTime("hhnn",Now());	// 更新時間

		KSD21.SKTYMD = Null_S(Q_KSD21->FieldValues["SKTYMD"]);	//測定日
		KSD21.UPDCHR = Null_S(Q_KSD21->FieldValues["UPDCHR"]);	//更新者

		////測定項目No更新
		//if ( KSD22.InsFlag != 0 ) {
		//	//新規検査項目の時 測定項目Noをインクリメント
		//	iBuf = KSD21.SOKUTEI_NUM.ToIntDef(0);
		//	KSD21.SOKUTEI_NUM = IntToStr(iBuf+1);
		//}

		//今回登録するデータと比較
		//測定日 新しい日付優先
        //2004.02.26 E.Takase Edit
        //例）2/10と2/12なら 2/10を採用
		//if ( Trim(KSD21.SKTYMD) == "" || KSD21.SKTYMD < KD_1.SKTYMD ) {
		if ( Trim(KSD21.SKTYMD) == "" || KSD21.SKTYMD > KD_1.SKTYMD ) {
			KSD21.SKTYMD = KD_1.SKTYMD;
		}
		//更新者 小さいほう優先
		iUPDCHR2 = atoi(KD_1.UPDCHR.c_str());
		if ( iUPDCHR2 != 0 ) {
			iUPDCHR1 = atoi(KSD21.UPDCHR.c_str());
			if ( iUPDCHR1 > iUPDCHR2 ) {
				KSD21.UPDCHR = KD_1.UPDCHR;
			}
		}

	} else {
		//新規の場合 得意先コード、得意先名称 取得
		iRtn = GetDTKS();
		KSD21.SOKUTEI_NUM = "1";
		KSD21.SKTYMD = KD_1.SKTYMD; //測定日
		KSD21.UPDCHR = KD_1.UPDCHR; //更新者
	}

	////素材判定更新
	//if ( KD_1.SOKUTE_OK == "1" ) {
	//	//NGの場合 1に更新
	//	KSD21.SOZAI_OK = "1";
	//}

	//備考
	if ( Trim(KD_1.MEMO) != "" ) {
		KSD21.MEMO = InsMEMO(KSD21.MEMO,iNo,KD_1.MEMO);
	}



}

/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：でーた検索
//
//  機能説明
//    KSD22からデータを取得し、Q_KSD22にセット
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    int					：0=検索成功 -1=検索失敗
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::SrchKSD22(int iNo)
{
	AnsiString sBuf;

	//Initial Query
	Q_KSD22->Close();
	Q_KSD22->SQL->Clear();

	// 問合せ実行
	sBuf = "";
	//SELECT文
	sBuf += " SELECT ";
	sBuf += " DTKSHIN, LOTNO, UNQ_NO, KOMK_NO, KOMK_NM, ";
	sBuf += " KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, ";
	sBuf += " KIKI_NM, TANI, KIKA_TYPE, KIKA_KIND, KIKA_DECI, ";
	sBuf += " KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, KIKA_STR, ";
	sBuf += " KIKA_SUB1, KIKA_SUB2, SOKU_SU, VALUE_TYPE, VALUE_DECI, ";
	sBuf += " SOKU_VAL01, SOKU_VAL02, SOKU_VAL03, SOKU_VAL04, SOKU_VAL05, ";
	sBuf += " SOKU_VAL06, SOKU_VAL07, SOKU_VAL08, SOKU_VAL09, SOKU_VAL10, ";
	sBuf += " SOKU_VAL_SU, SOKU_VAL_AVE, SOKU_VAL_MAX, SOKU_VAL_MIN, SOKU_OK, SKTYMD, ";
	sBuf += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT, HINBAN ";
	//テーブル名
	sBuf += " FROM KSD22 ";
	//WHERE文
	sBuf += " WHERE  ";
	sBuf += " DTKSHIN ='" + KD_1.DTKSHIN + "' AND ";
	sBuf += " HINBAN  ='" + KD_1.HINBAN + "' AND ";
	sBuf += " LOTNO   ='" + KD_1.LOTNO + "' AND ";
	sBuf += " UNQ_NO =" + FixStr[iNo].KOMK_NO;



	Q_KSD22->SQL->Add(sBuf);
	Q_KSD22->Open();
	Q_KSD22->Active = true;

	if ( Q_KSD22->Bof && Q_KSD22->Eof ) {
		//検索結果 ０件
		return(-1);
	}

	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：構造体にデータを代入
//
//  機能説明
//    SrchKSD22での検索結果を構造体（KSD22）にセット
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    なし
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::SetKSD22(int iNo)
{
	AnsiString sBuf;
	int i;
	int iSOKU_VAL_SU;
	int iUPDCNT;

	//実績明細データ（KSD22）より
	if ( KSD22.InsFlag == 0 ) {
		KSD22.ADDYMD = Null_S(Q_KSD22->FieldValues["ADDYMD"]);
		KSD22.ADDTIM = Null_S(Q_KSD22->FieldValues["ADDTIM"]);
		KSD22.UPDYMD = FormatDateTime("yyyymmdd",Now());// 更新日
		KSD22.UPDTIM = FormatDateTime("hhnn",Now());	// 更新時間
		KSD22.UPDCNT = Null_S(Q_KSD22->FieldValues["UPDCNT"]);

	}
	//更新回数インクリメント
	iUPDCNT = atoi(KSD22.UPDCNT.c_str());
	iUPDCNT++;
	KSD22.UPDCNT = IntToStr(iUPDCNT);

	//素材明細データ（KDX1）より
	//単位
	KSD22.TANI = "";
	switch (iNo)
	{
		case 6: //取付強度
			sBuf = KD_1.KIKA_SUB2;
            switch( sBuf.ToIntDef(1) ){
				case 1:	KSD22.TANI = FixStr[iNo].TANI[0];	break;
                case 2:	KSD22.TANI = FixStr[iNo].TANI[1];	break;
                case 3:	KSD22.TANI = FixStr[iNo].TANI[2];	break;
            }
			break;

		case 7: //取付抵抗
			KSD22.TANI = FixStr[iNo].TANI[0] + KD_1.KIKA_NUM2 + FixStr[iNo].TANI[1];
			break;

        //2003.07.01 抵抗率 μΩ･cm10A → μΩ･cm に変更になった
		//case 8: //抵抗率
		//	KSD22.TANI = FixStr[iNo].TANI[0] + KD_1.KIKA_SUB1 + FixStr[iNo].TANI[1];
		//	break;

		case 9: //曲げ強さ
			sBuf = KD_1.KIKA_SUB2;
            switch( sBuf.ToIntDef(1) ){
            	case 1:	KSD22.TANI = FixStr[iNo].TANI[0];	break;
                case 2:	KSD22.TANI = FixStr[iNo].TANI[1];	break;
                case 3:	KSD22.TANI = FixStr[iNo].TANI[2];	break;
				case 4:	KSD22.TANI = FixStr[iNo].TANI[3];	break;
            }
			break;

		case 10: //曲げ強さ（現物）
			sBuf = KD_1.KIKA_SUB2;
            switch( sBuf.ToIntDef(1) ){
            	case 1:	KSD22.TANI = FixStr[iNo].TANI[0];	break;
                case 2:	KSD22.TANI = FixStr[iNo].TANI[1];	break;
                case 3:	KSD22.TANI = FixStr[iNo].TANI[2];	break;
                case 4:	KSD22.TANI = FixStr[iNo].TANI[3];	break;
                //2003/07/22 E.Takase 単位追加
                case 5:	KSD22.TANI = FixStr[iNo].TANI[4];	break;
            }
			break;
			
		default: //その他 両側規格
			KSD22.TANI = FixStr[iNo].TANI[0];
			break;

	}

	//規格値1・規格値2
	switch (iNo)
	{
		case 6: //取付強度 下限規格
			KSD22.KIKA_NUM1 = KD_1.KIKA_NUM1;
			break;

		case 7: //取付抵抗 上限規格
        	//2003.05.29 E.Takase Mod
			//KSD22.KIKA_NUM1 = KD_1.KIKA_NUM1;
			KSD22.KIKA_NUM1 = "0";
			KSD22.KIKA_NUM2 = KD_1.KIKA_NUM1;
			break;

		default: //その他 両側規格
			KSD22.KIKA_NUM1 = KD_1.KIKA_NUM1;
			KSD22.KIKA_NUM2 = KD_1.KIKA_NUM2;
			break;

	}

	//規格値サブ1・規格値サブ2
	switch (iNo)
	{
		case 6: //取付強度（測定速度・単位記号）
			KSD22.KIKA_SUB1 = KD_1.KIKA_SUB1;
			KSD22.KIKA_SUB2 = KD_1.KIKA_SUB2;
			break;

		case 7: //取付抵抗（測定時間・測定タイプ）
			KSD22.KIKA_SUB1 = KD_1.KIKA_SUB1;
			KSD22.KIKA_SUB2 = KD_1.KIKA_SUB2;
			break;

		case 9: //曲げ（スパン・単位記号）
			KSD22.KIKA_SUB1 = KD_1.KIKA_SUB1;
			KSD22.KIKA_SUB2 = KD_1.KIKA_SUB2;
			break;

		case 10: //曲げ（スパン・単位記号）
			KSD22.KIKA_SUB1 = KD_1.KIKA_SUB1;
			KSD22.KIKA_SUB2 = KD_1.KIKA_SUB2;
			break;

	}


	KSD22.SOKU_SU = KD_1.SOKUTEI_NM; 		//測定指示n数
	KSD22.SOKU_VAL_SU = KD_1.SOKUTEI_SU;  	//測定実績n数

	//測定値
	iSOKU_VAL_SU = KSD22.SOKU_VAL_SU.ToIntDef(0);
	for ( i = 0; i < iSOKU_VAL_SU; i++ ) {
		KSD22.SOKU_VAL[i] = KD_1.SOKUTEI[i];
	}

	KSD22.SOKU_VAL_AVE = KD_1.SOKUTE_AVE; 	//測定平均値
	KSD22.SOKU_VAL_MAX = KD_1.SOKUTE_MAX; 	//測定最大値
	KSD22.SOKU_VAL_MIN = KD_1.SOKUTE_MIN; 	//測定最小値
	KSD22.SOKU_OK = KD_1.SOKUTE_OK;       	//測定値判定
	KSD22.SKTYMD = KD_1.SKTYMD;           	//測定日
	KSD22.UPDCHR = KD_1.UPDCHR;           	//更新者


}

/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：データ検索
//
//  機能説明
//    KSD22からデータを取得し、Q_KSD22にセット
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    int					：0=検索成功 -1=検索失敗
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::SrchKSD23(int iNo)
{
	AnsiString sBuf;

	//Initial Query
	Q_KSD23->Close();
	Q_KSD23->SQL->Clear();

	// 問合せ実行
	sBuf = "";
	//SELECT文
	sBuf += " SELECT ";
	sBuf += " DTKSHIN, LOTNO, UNQ_NO, SOKU_NO, SOKU_VAL, HINBAN ";
	//テーブル名
	sBuf += " FROM KSD23 ";
	//WHERE文
	sBuf += " WHERE  ";
	sBuf += " DTKSHIN ='" + KD_1.DTKSHIN + "' AND ";
	sBuf += " HINBAN  ='" + KD_1.HINBAN + "' AND ";
	sBuf += " LOTNO   ='" + KD_1.LOTNO + "' AND ";
	sBuf += " UNQ_NO =" + FixStr[iNo].KOMK_NO;



	Q_KSD23->SQL->Add(sBuf);
	Q_KSD23->Open();
	Q_KSD23->Active = true;

	if ( Q_KSD23->Bof && Q_KSD23->Eof ) {
		//検索結果 ０件
		return(-1);
	}

	return(0);
}

/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：構造体の初期化
//
//  機能説明
//    KSD21初期化を初期化します。
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    なし
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormatKSD21(int iNo)
{

	KSD21.InsFlag 		= -1; 								// 新規の場合：-1
	KSD21.DTKSHIN 		= KD_1.DTKSHIN;						// 得意先品番
	KSD21.LOTNO   		= KD_1.LOTNO; 						// ロットNO
	KSD21.HINBAN		= KD_1.HINBAN; 						// 自社品番
	KSD21.DTKSCOD 		= " "; 								// 得意先コード
	KSD21.DTKSNAM 		= " "; 								// 得意先名称
	KSD21.ZISNAM 		= KD_1.ZISNAM; 						// 材質名称（品種）
	KSD21.SOKUTEI_NUM 	= "0"; 								// 測定項目数
	KSD21.SOZAI_OK 		= "0"; 								// 素材判定
	KSD21.MEMO 			= " "; 								// 備考
	KSD21.SKTYMD		= " "; 								// 測定日
	KSD21.ADDYMD 		= FormatDateTime("yyyymmdd",Now());	// 登録日
	KSD21.ADDTIM 		= FormatDateTime("hhnn",Now());		// 登録時間
	KSD21.UPDYMD 		= " "; 								// 変更日
	KSD21.UPDTIM 		= " "; 								// 変更時間
	KSD21.UPDCHR 		= "0"; 								// 更新者
	KSD21.UPDCNT 		= "0"; 								// 更新回数

}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：構造体の初期化
//
//  機能説明
//    KSD22初期化を初期化します。
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    なし
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormatKSD22(int iNo)
{
	int i;

	//素材測定実績明細データ
	KSD22.InsFlag 		= -1; 							// 新規の場合：-1
	KSD22.DTKSHIN 		= KD_1.DTKSHIN; 				// 得意先品番
	KSD22.LOTNO 		= KD_1.LOTNO; 					// ロットNO
	KSD22.HINBAN 		= KD_1.HINBAN; 					// 自社品番
	KSD22.UNQ_NO 		= FixStr[iNo].KOMK_NO; 			// 明細NO
	KSD22.KOMK_NO 		= FixStr[iNo].KOMK_NO; 			// 測定項目NO
	KSD22.KOMK_NM 		= FixStr[iNo].KOMK_NM; 			// 測定項目名称
	KSD22.KOMK_ENG 		= FixStr[iNo].KOMK_ENG; 		// 測定項目名称（英語）
	KSD22.KOMK_SUB 		= ""; 							// 測定項目サブ名称
	KSD22.KOMK_SUB_ENG 	= ""; 							// 測定項目サブ名称（英語）
	KSD22.KIKI_NO 		= FixStr[iNo].KIKI_NO; 			// 測定機器NO
	KSD22.KIKI_NM 		= FixStr[iNo].KIKI_NM; 			// 測定機器名称
	KSD22.TANI 			= ""; 							// 単位
	KSD22.KIKA_TYPE 	= FixStr[iNo].KIKA_TYPE; 		// 規格タイプ
	KSD22.KIKA_KIND 	= FixStr[iNo].KIKA_KIND; 		// 規格種類
	KSD22.KIKA_DECI 	= FixStr[iNo].KIKA_DECI; 		// 規格小数点以下桁数
	KSD22.KIKA_NUM1 	= "0"; 							// 規格値1
	KSD22.KIKA_NUM2 	= "0"; 							// 規格値2
	KSD22.KIKA_NUM3 	= FixStr[iNo].KIKA_NUM3; 		// 規格値3
	KSD22.KIKA_STR 		= FixStr[iNo].KIKA_STR; 		// 規格値文字
	KSD22.KIKA_SUB1 	= ""; 							// 規格値サブ1
	KSD22.KIKA_SUB2 	= ""; 							// 規格値サブ2
	KSD22.SOKU_SU 		= "0"; 							// 測定指示n数
	KSD22.VALUE_TYPE 	= FixStr[iNo].VALUE_TYPE; 		// 測定値表現
	KSD22.VALUE_DECI 	= FixStr[iNo].VALUE_DECI; 		// 測定値小数点以下桁数

	for ( i = 0; i < 100; i++ ) {
		KSD22.SOKU_VAL[i] = ""; 						// 測定値
	}
	KSD22.SOKU_VAL_SU 	= "0";							// 測定実績n数
	KSD22.SOKU_VAL_AVE 	= "0"; 							// 測定平均値
	KSD22.SOKU_VAL_MAX 	= "0"; 							// 測定最大値
	KSD22.SOKU_VAL_MIN 	= "0";							// 測定最小値
	KSD22.SOKU_OK 		= "0"; 							// 測定値判定
	KSD22.SKTYMD 		= ""; 							// 測定日
	KSD22.ADDYMD 		= FormatDateTime("yyyymmdd",Now());// 登録日
	KSD22.ADDTIM 		= FormatDateTime("hhnn",Now());	// 登録時間
	KSD22.UPDYMD 		= ""; 							// 変更日
	KSD22.UPDTIM 		= ""; 							// 変更時間
	KSD22.UPDCHR 		= "0"; 							// 更新者
	KSD22.UPDCNT 		= "0"; 							// 更新回数

}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：構造体の初期化
//
//  機能説明
//    KSD23初期化を初期化します。
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    なし
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormatKSD23(int iNo)
{
	KSD23.InsFlag = -1; 					// 新規の場合：-1
}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：構造体の初期化
//
//  機能説明
//    FixStr初期化を初期化します。
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    なし
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
void __fastcall TForm1::FormatFixStr(void)
{

	//FixStrNum = 16;
	FixStrNum = 18;

	//フィールド名
	//リード線長さ
	FixStr[0].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[0].F_KIKA_NUM1 = "LD_LNG_MIN";
	FixStr[0].F_KIKA_NUM2 = "LD_LNG_MAX";
	FixStr[0].F_KIKA_SUB1 = "' '";
	FixStr[0].F_KIKA_SUB2 = "' '";
	FixStr[0].F_KEIJYO_KBN = "' '";
	FixStr[0].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[0].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[0].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[0].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[0].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[0].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[0].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//ブラシ幅
	FixStr[1].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[1].F_KIKA_NUM1 = "BURASI_MIN";
	FixStr[1].F_KIKA_NUM2 = "BURASI_MAX";
	FixStr[1].F_KIKA_SUB1 = "' '";
	FixStr[1].F_KIKA_SUB2 = "' '";
	FixStr[1].F_KEIJYO_KBN = "' '";
	FixStr[1].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[1].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[1].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[1].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[1].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[1].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[1].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//内径
	FixStr[2].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[2].F_KIKA_NUM1 = "BURASI_MIN";
	FixStr[2].F_KIKA_NUM2 = "BURASI_MAX";
	FixStr[2].F_KIKA_SUB1 = "' '";
	FixStr[2].F_KIKA_SUB2 = "' '";
	FixStr[2].F_KEIJYO_KBN = "' '";
	FixStr[2].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[2].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[2].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[2].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[2].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[2].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[2].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//ブラシ幅 (縦押し)
	FixStr[3].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[3].F_KIKA_NUM1 = "BURASIT_MIN";
	FixStr[3].F_KIKA_NUM2 = "BURASIT_MAX";
	FixStr[3].F_KIKA_SUB1 = "' '";
	FixStr[3].F_KIKA_SUB2 = "' '";
	FixStr[3].F_KEIJYO_KBN = "' '";
	FixStr[3].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[3].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[3].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[3].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[3].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[3].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[3].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//外径
	FixStr[4].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[4].F_KIKA_NUM1 = "BURASIT_MIN";
	FixStr[4].F_KIKA_NUM2 = "BURASIT_MAX";
	FixStr[4].F_KIKA_SUB1 = "' '";
	FixStr[4].F_KIKA_SUB2 = "' '";
	FixStr[4].F_KEIJYO_KBN = "' '";
	FixStr[4].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[4].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[4].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[4].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[4].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[4].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[4].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//見掛比重
	FixStr[5].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[5].F_KIKA_NUM1 = "BOTAI_MIN";
	FixStr[5].F_KIKA_NUM2 = "BOTAI_MAX";
	FixStr[5].F_KIKA_SUB1 = "' '";
	FixStr[5].F_KIKA_SUB2 = "' '";
	FixStr[5].F_KEIJYO_KBN = "KEIJYO_KBN";
	FixStr[5].F_SOKUTEI_1 = "SOKUTEI_1B";
	FixStr[5].F_SOKUTEI_2 = "SOKUTEI_2B";
	FixStr[5].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[5].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[5].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[5].F_SOKUTEICHI = "SOKUTEI_B";
	FixStr[5].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//リード線取付強度
	FixStr[6].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[6].F_KIKA_NUM1 = "LD_HP_MIN";
	FixStr[6].F_KIKA_NUM2 = "' '";
	FixStr[6].F_KIKA_SUB1 = "LD_HP_SPD";
	FixStr[6].F_KIKA_SUB2 = "LD_HP_TAN";
	FixStr[6].F_KEIJYO_KBN = "' '";
	FixStr[6].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[6].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[6].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[6].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[6].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[6].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[6].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//リード線取付抵抗
	FixStr[7].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[7].F_KIKA_NUM1 = "LD_TR_MAX";
	FixStr[7].F_KIKA_NUM2 = "LD_TR_DEN";
	FixStr[7].F_KIKA_SUB1 = "LD_TR_TIME";
	FixStr[7].F_KIKA_SUB2 = "LD_TR_TYPE";
	FixStr[7].F_KEIJYO_KBN = "' '";
	FixStr[7].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[7].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[7].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[7].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[7].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[7].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[7].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//抵抗率
	FixStr[8].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[8].F_KIKA_NUM1 = "KOYU_MIN";
	FixStr[8].F_KIKA_NUM2 = "KOYU_MAX";
	FixStr[8].F_KIKA_SUB1 = "KOYU_DEN";
	FixStr[8].F_KIKA_SUB2 = "' '";
	FixStr[8].F_KEIJYO_KBN = "KEIJYO_KBN";
	FixStr[8].F_SOKUTEI_1 = "SOKUTEI_1T";
	FixStr[8].F_SOKUTEI_2 = "SOKUTEI_2T";
	FixStr[8].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[8].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[8].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[8].F_SOKUTEICHI = "SOKUTEI_T";
	FixStr[8].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//曲げ強さ
	FixStr[9].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[9].F_KIKA_NUM1 = "MAGE_MIN";
	FixStr[9].F_KIKA_NUM2 = "MAGE_MAX";
	FixStr[9].F_KIKA_SUB1 = "MAGE_SPAN";
	FixStr[9].F_KIKA_SUB2 = "MAGE_TAN";
	FixStr[9].F_KEIJYO_KBN = "KEIJYO_KBN";
	FixStr[9].F_SOKUTEI_1 = "SOKUTEI_1M";
	FixStr[9].F_SOKUTEI_2 = "SOKUTEI_2M";
	FixStr[9].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[9].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[9].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[9].F_SOKUTEICHI = "SOKUTEI_M";
	FixStr[9].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//曲げ強さ（現物）
	FixStr[10].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[10].F_KIKA_NUM1 = "MAGEG_MIN";
	FixStr[10].F_KIKA_NUM2 = "MAGEG_MAX";
	FixStr[10].F_KIKA_SUB1 = "MAGEG_SPAN";
	FixStr[10].F_KIKA_SUB2 = "MAGEG_TAN";
	FixStr[10].F_KEIJYO_KBN = "KEIJYO_KBN";
	FixStr[10].F_SOKUTEI_1 = "SOKUTEI_1M";
	FixStr[10].F_SOKUTEI_2 = "SOKUTEI_2M";
	FixStr[10].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[10].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[10].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[10].F_SOKUTEICHI = "SOKUTEI_M";
	FixStr[10].W_SOKUTE_KBN = " (SOKUTE_KBN = 1) ";

	//硬度ＨｓＣ（圧面）
	FixStr[11].F_SOKUTE_KBN = "SOKUTE_KBN1";
	FixStr[11].F_KIKA_NUM1 = "HSC_A_MIN";
	FixStr[11].F_KIKA_NUM2 = "HSC_A_MAX";
	FixStr[11].F_KIKA_SUB1 = "' '";
	FixStr[11].F_KIKA_SUB2 = "' '";
	FixStr[11].F_KEIJYO_KBN = "' '";
	FixStr[11].F_SOKUTEI_1 = "HSC_A_1";
	FixStr[11].F_SOKUTEI_2 = "HSC_A_2";
	FixStr[11].F_SOKUTEI_SU = "HSC_SK_SU";
	FixStr[11].F_SOKUTEI_NM = "HSC_SK_NUM";
	FixStr[11].F_SOKUTE_AVE = "HSC_A_AVE";
	FixStr[11].F_SOKUTEICHI = "HSC_A";
	FixStr[11].W_SOKUTE_KBN = " ( SOKUTE_KBN1 = 1 OR SOKUTE_KBN1 = 3 ) ";

	//硬度ＨｓＣ（側面）
	FixStr[12].F_SOKUTE_KBN = "SOKUTE_KBN1";
	FixStr[12].F_KIKA_NUM1 = "HSC_S_MIN";
	FixStr[12].F_KIKA_NUM2 = "HSC_S_MAX";
	FixStr[12].F_KIKA_SUB1 = "' '";
	FixStr[12].F_KIKA_SUB2 = "' '";
	FixStr[12].F_KEIJYO_KBN = "' '";
	FixStr[12].F_SOKUTEI_1 = "HSC_S_1";
	FixStr[12].F_SOKUTEI_2 = "HSC_S_2";
	FixStr[12].F_SOKUTEI_SU = "HSC_SK_SU";
	FixStr[12].F_SOKUTEI_NM = "HSC_SK_NUM";
	FixStr[12].F_SOKUTE_AVE = "HSC_S_AVE";
	FixStr[12].F_SOKUTEICHI = "HSC_S";
	FixStr[12].W_SOKUTE_KBN = " ( SOKUTE_KBN1 = 2 OR SOKUTE_KBN1 = 3 ) ";

	//硬度 (HsD 圧面)
	FixStr[13].F_SOKUTE_KBN = "SOKUTE_KBN2";
	FixStr[13].F_KIKA_NUM1 = "HSD_A_MIN";
	FixStr[13].F_KIKA_NUM2 = "HSD_A_MAX";
	FixStr[13].F_KIKA_SUB1 = "' '";
	FixStr[13].F_KIKA_SUB2 = "' '";
	FixStr[13].F_KEIJYO_KBN = "' '";
	FixStr[13].F_SOKUTEI_1 = "HSD_A_1";
	FixStr[13].F_SOKUTEI_2 = "HSD_A_2";
	FixStr[13].F_SOKUTEI_SU = "HSD_SK_SU";
	FixStr[13].F_SOKUTEI_NM = "HSD_SK_NUM";
	FixStr[13].F_SOKUTE_AVE = "HSD_A_AVE";
	FixStr[13].F_SOKUTEICHI = "HSD_A";
	FixStr[13].W_SOKUTE_KBN = " ( SOKUTE_KBN2 = 1 OR SOKUTE_KBN2 = 3 ) ";

	//硬度 (HsD 側面)
	FixStr[14].F_SOKUTE_KBN = "SOKUTE_KBN2";
	FixStr[14].F_KIKA_NUM1 = "HSD_S_MIN";
	FixStr[14].F_KIKA_NUM2 = "HSD_S_MAX";
	FixStr[14].F_KIKA_SUB1 = "' '";
	FixStr[14].F_KIKA_SUB2 = "' '";
	FixStr[14].F_KEIJYO_KBN = "' '";
	FixStr[14].F_SOKUTEI_1 = "HSD_S_1";
	FixStr[14].F_SOKUTEI_2 = "HSD_S_2";
	FixStr[14].F_SOKUTEI_SU = "HSD_SK_SU";
	FixStr[14].F_SOKUTEI_NM = "HSD_SK_NUM";
	FixStr[14].F_SOKUTE_AVE = "HSD_S_AVE";
	FixStr[14].F_SOKUTEICHI = "HSD_S";
	FixStr[14].W_SOKUTE_KBN = " ( SOKUTE_KBN2 = 2 OR SOKUTE_KBN2 = 3 ) ";

	//座屈
	FixStr[15].F_SOKUTE_KBN = "SOKUTE_KBN";
	FixStr[15].F_KIKA_NUM1 = "ZAKUT_MIN";
	FixStr[15].F_KIKA_NUM2 = "ZAKUT_MAX";
	FixStr[15].F_KIKA_SUB1 = "' '";
	FixStr[15].F_KIKA_SUB2 = "' '";
	FixStr[15].F_KEIJYO_KBN = "' '";
	FixStr[15].F_SOKUTEI_1 = "SOKUTEI_1";
	FixStr[15].F_SOKUTEI_2 = "SOKUTEI_2";
	FixStr[15].F_SOKUTEI_SU = "SOKUTEI_SU";
	FixStr[15].F_SOKUTEI_NM = "SOKUTEI_NM";
	FixStr[15].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[15].F_SOKUTEICHI = "SOKUTEICHI";
	FixStr[15].W_SOKUTE_KBN = " SOKUTE_KBN = 1 ";

	//ヒストグラム(ブラシ厚さMin・Max)
	FixStr[16].F_SOKUTE_KBN = "' '";
	FixStr[16].F_KIKA_NUM1 = "HIST_MIN";
	FixStr[16].F_KIKA_NUM2 = "HIST_MAX";
	FixStr[16].F_KIKA_SUB1 = "' '";
	FixStr[16].F_KIKA_SUB2 = "' '";
	FixStr[16].F_KEIJYO_KBN = "' '";
	FixStr[16].F_SOKUTEI_1 = "SOKUTE_MIN";
	FixStr[16].F_SOKUTEI_2 = "SOKUTE_MAX";
	FixStr[16].F_SOKUTEI_SU = "'2'";
	FixStr[16].F_SOKUTEI_NM = "'2'";
	FixStr[16].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[16].F_SOKUTEICHI = "' '";
	FixStr[16].W_SOKUTE_KBN = "";
	FixStr[16].W_SOKUTE_KBN = "";

	//ヒストグラム(ブラシ厚さCp・Cpk)
	FixStr[17].F_SOKUTE_KBN = "' '";
	FixStr[17].F_KIKA_NUM1 = "'1.33'";
	FixStr[17].F_KIKA_NUM2 = "'0'";
	FixStr[17].F_KIKA_SUB1 = "' '";
	FixStr[17].F_KIKA_SUB2 = "' '";
	FixStr[17].F_KEIJYO_KBN = "' '";
	FixStr[17].F_SOKUTEI_1 = "SOKUTE_CP";
	FixStr[17].F_SOKUTEI_2 = "SOKUTE_CPK";
	FixStr[17].F_SOKUTEI_SU = "'2'";
	FixStr[17].F_SOKUTEI_NM = "'2'";
	FixStr[17].F_SOKUTE_AVE = "SOKUTE_AVE";
	FixStr[17].F_SOKUTEICHI = "' '";
	FixStr[17].W_SOKUTE_KBN = "";

	//*********************************************************
	//固定文字列
	//リード線長さ
	FixStr[0].TABLE1 = "KD01";
	FixStr[0].TABLE2 = "KD02";
	FixStr[0].KOMK_NO = "1";
	FixStr[0].ORDER_NO = "11";
	FixStr[0].KOMK_NM = "リード線長さ";
	FixStr[0].KOMK_ENG = "L/W Length";
	FixStr[0].KIKI_NO = "2";
	FixStr[0].KIKI_NM = "ノギス";
	FixStr[0].TANI[0] = "mm";
	FixStr[0].TANI[1] = "";
	FixStr[0].TANI[2] = "";
	FixStr[0].TANI[3] = "";
	FixStr[0].KIKA_TYPE = "1";
	FixStr[0].KIKA_KIND = "1";
	FixStr[0].KIKA_DECI = "2";
	FixStr[0].KIKA_NUM2 = "";
	FixStr[0].KIKA_NUM3 = "0";
	FixStr[0].KIKA_STR = "";
	FixStr[0].SOKU_FLG = "1";
	FixStr[0].TOKU_FLG = "0";
	FixStr[0].KIKA_PRT = "1";
	FixStr[0].VALUE_TYPE = "0";
	FixStr[0].VALUE_DECI = "2";

	//ブラシ幅
	FixStr[1].TABLE1 = "KD11";
	FixStr[1].TABLE2 = "KD12";
	FixStr[1].KOMK_NO = "2";
	FixStr[1].ORDER_NO = "12";
	FixStr[1].KOMK_NM = "ブラシ幅";
	FixStr[1].KOMK_ENG = "Brush Width";
	FixStr[1].KIKI_NO = "1";
	FixStr[1].KIKI_NM = "マイクロメータ";
	FixStr[1].TANI[0] = "mm";
	FixStr[1].TANI[1] = "";
	FixStr[1].TANI[2] = "";
	FixStr[1].TANI[3] = "";
	FixStr[1].KIKA_TYPE = "1";
	FixStr[1].KIKA_KIND = "1";
	FixStr[1].KIKA_DECI = "3";
	FixStr[1].KIKA_NUM2 = "";
	FixStr[1].KIKA_NUM3 = "0";
	FixStr[1].KIKA_STR = "";
	FixStr[1].SOKU_FLG = "1";
	FixStr[1].TOKU_FLG = "0";
	FixStr[1].KIKA_PRT = "1";
	FixStr[1].VALUE_TYPE = "0";
	FixStr[1].VALUE_DECI = "3";

	//内径
	FixStr[2].TABLE1 = "KD11";
	FixStr[2].TABLE2 = "KD12";
	FixStr[2].KOMK_NO = "3";
	FixStr[2].ORDER_NO = "14";
	FixStr[2].KOMK_NM = "内径";
	FixStr[2].KOMK_ENG = "";
	FixStr[2].KIKI_NO = "1";
	FixStr[2].KIKI_NM = "マイクロメータ";
	FixStr[2].TANI[0] = "mm";
	FixStr[2].TANI[1] = "";
	FixStr[2].TANI[2] = "";
	FixStr[2].TANI[3] = "";
	FixStr[2].KIKA_TYPE = "1";
	FixStr[2].KIKA_KIND = "1";
	FixStr[2].KIKA_DECI = "3";
	FixStr[2].KIKA_NUM2 = "";
	FixStr[2].KIKA_NUM3 = "0";
	FixStr[2].KIKA_STR = "";
	FixStr[2].SOKU_FLG = "1";
	FixStr[2].TOKU_FLG = "0";
	FixStr[2].KIKA_PRT = "1";
	FixStr[2].VALUE_TYPE = "0";
	FixStr[2].VALUE_DECI = "3";

	//ブラシ幅 (縦押し)
	FixStr[3].TABLE1 = "KD21";
	FixStr[3].TABLE2 = "KD22";
	FixStr[3].KOMK_NO = "4";
	FixStr[3].ORDER_NO = "13";
	FixStr[3].KOMK_NM = "ブラシ幅 (縦押し)";
	FixStr[3].KOMK_ENG = "Brush Width A";
	FixStr[3].KIKI_NO = "1";
	FixStr[3].KIKI_NM = "マイクロメータ";
	FixStr[3].TANI[0] = "mm";
	FixStr[3].TANI[1] = "";
	FixStr[3].TANI[2] = "";
	FixStr[3].TANI[3] = "";
	FixStr[3].KIKA_TYPE = "1";
	FixStr[3].KIKA_KIND = "1";
	FixStr[3].KIKA_DECI = "3";
	FixStr[3].KIKA_NUM2 = "";
	FixStr[3].KIKA_NUM3 = "0";
	FixStr[3].KIKA_STR = "";
	FixStr[3].SOKU_FLG = "1";
	FixStr[3].TOKU_FLG = "0";
	FixStr[3].KIKA_PRT = "1";
	FixStr[3].VALUE_TYPE = "0";
	FixStr[3].VALUE_DECI = "3";

	//外径
	FixStr[4].TABLE1 = "KD21";
	FixStr[4].TABLE2 = "KD22";
	FixStr[4].KOMK_NO = "5";
	FixStr[4].ORDER_NO = "15";
	FixStr[4].KOMK_NM = "外径";
	FixStr[4].KOMK_ENG = "";
	FixStr[4].KIKI_NO = "1";
	FixStr[4].KIKI_NM = "マイクロメータ";
	FixStr[4].TANI[0] = "mm";
	FixStr[4].TANI[1] = "";
	FixStr[4].TANI[2] = "";
	FixStr[4].TANI[3] = "";
	FixStr[4].KIKA_TYPE = "1";
	FixStr[4].KIKA_KIND = "1";
	FixStr[4].KIKA_DECI = "3";
	FixStr[4].KIKA_NUM2 = "";
	FixStr[4].KIKA_NUM3 = "0";
	FixStr[4].KIKA_STR = "";
	FixStr[4].SOKU_FLG = "1";
	FixStr[4].TOKU_FLG = "0";
	FixStr[4].KIKA_PRT = "1";
	FixStr[4].VALUE_TYPE = "0";
	FixStr[4].VALUE_DECI = "3";

	//見掛比重
	FixStr[5].TABLE1 = "KD51";
	FixStr[5].TABLE2 = "KD52";
	FixStr[5].KOMK_NO = "6";
	FixStr[5].ORDER_NO = "1";
	FixStr[5].KOMK_NM = "見掛比重";
	FixStr[5].KOMK_ENG = "Apparent Density";
	FixStr[5].KIKI_NO = "3";
	FixStr[5].KIKI_NM = "マイクロメータ、天秤";
	FixStr[5].TANI[0] = "";
	FixStr[5].TANI[1] = "";
	FixStr[5].TANI[2] = "";
	FixStr[5].TANI[3] = "";
	FixStr[5].KIKA_TYPE = "1";
	FixStr[5].KIKA_KIND = "1";
	FixStr[5].KIKA_DECI = "2";
	FixStr[5].KIKA_NUM2 = "";
	FixStr[5].KIKA_NUM3 = "0";
	FixStr[5].KIKA_STR = "";
	FixStr[5].SOKU_FLG = "1";
	FixStr[5].TOKU_FLG = "0";
	FixStr[5].KIKA_PRT = "1";
	FixStr[5].VALUE_TYPE = "0";
	FixStr[5].VALUE_DECI = "2";

	//リード線取付強度
	FixStr[6].TABLE1 = "KD41";
	FixStr[6].TABLE2 = "KD42";
	FixStr[6].KOMK_NO = "7";
	FixStr[6].ORDER_NO = "10";
	FixStr[6].KOMK_NM = "リード線取付強度";
	FixStr[6].KOMK_ENG = "Pull Strength";
	FixStr[6].KIKI_NO = "5";
	FixStr[6].KIKI_NM = "材料試験機";
	FixStr[6].TANI[0] = "kgf";
	FixStr[6].TANI[1] = "N";
	FixStr[6].TANI[2] = "MPa";
	FixStr[6].TANI[3] = "";
	FixStr[6].KIKA_TYPE = "1";
	FixStr[6].KIKA_KIND = "3";
	FixStr[6].KIKA_DECI = "1";
	FixStr[6].KIKA_NUM2 = "0";
	FixStr[6].KIKA_NUM3 = "0";
	FixStr[6].KIKA_STR = "";
	FixStr[6].SOKU_FLG = "1";
	FixStr[6].TOKU_FLG = "0";
	FixStr[6].KIKA_PRT = "1";
	FixStr[6].VALUE_TYPE = "0";
	FixStr[6].VALUE_DECI = "1";

	//リード線取付抵抗
	FixStr[7].TABLE1 = "KD31";
	FixStr[7].TABLE2 = "KD32";
	FixStr[7].KOMK_NO = "8";
	FixStr[7].ORDER_NO = "9";
	FixStr[7].KOMK_NM = "リード線取付抵抗";
	FixStr[7].KOMK_ENG = "Connection Drop";
	FixStr[7].KIKI_NO = "12";
	FixStr[7].KIKI_NM = "リード線取付抵抗測定機";
	FixStr[7].TANI[0] = "mV/";
	FixStr[7].TANI[1] = "A";
	FixStr[7].TANI[2] = "";
	FixStr[7].TANI[3] = "";
	FixStr[7].KIKA_TYPE = "1";
	FixStr[7].KIKA_KIND = "2";
	FixStr[7].KIKA_DECI = "1";
	FixStr[7].KIKA_NUM2 = "0";
	FixStr[7].KIKA_NUM3 = "0";
	FixStr[7].KIKA_STR = "";
	FixStr[7].SOKU_FLG = "1";
	FixStr[7].TOKU_FLG = "0";
	FixStr[7].KIKA_PRT = "1";
	FixStr[7].VALUE_TYPE = "0";
	FixStr[7].VALUE_DECI = "1";

	//抵抗率
	FixStr[8].TABLE1 = "KD71";
	FixStr[8].TABLE2 = "KD72";
	FixStr[8].KOMK_NO = "9";
	FixStr[8].ORDER_NO = "6";
	FixStr[8].KOMK_NM = "抵抗率";
	FixStr[8].KOMK_ENG = "Specific Resistance";
	FixStr[8].KIKI_NO = "11";
	FixStr[8].KIKI_NM = "抵抗率測定機";
    //2003.07.01 抵抗率 μΩ･cm10A → μΩ･cm に変更になった
	//FixStr[8].TANI[0] = "μΩ･cm ";
	//FixStr[8].TANI[1] = "A";
	FixStr[8].TANI[0] = "μΩ･cm";
	FixStr[8].TANI[1] = "";
	FixStr[8].TANI[2] = "";
	FixStr[8].TANI[3] = "";
	FixStr[8].KIKA_TYPE = "1";
	FixStr[8].KIKA_KIND = "1";
	FixStr[8].KIKA_DECI = "0";
	FixStr[8].KIKA_NUM2 = "";
	FixStr[8].KIKA_NUM3 = "0";
	FixStr[8].KIKA_STR = "";
	FixStr[8].SOKU_FLG = "1";
	FixStr[8].TOKU_FLG = "0";
	FixStr[8].KIKA_PRT = "1";
	FixStr[8].VALUE_TYPE = "0";
	FixStr[8].VALUE_DECI = "0";

	//曲げ強さ
	FixStr[9].TABLE1 = "KD81";
	FixStr[9].TABLE2 = "KD82";
	FixStr[9].KOMK_NO = "10";
	FixStr[9].ORDER_NO = "7";
	FixStr[9].KOMK_NM = "曲げ強さ";
	FixStr[9].KOMK_ENG = "Transverse Strength";
	FixStr[9].KIKI_NO = "5";
	FixStr[9].KIKI_NM = "材料試験機";
	FixStr[9].TANI[0] = "kgf/c㎡";
	FixStr[9].TANI[1] = "N/c㎡";
	FixStr[9].TANI[2] = "Mpa";
	FixStr[9].TANI[3] = "N/m㎡";
	FixStr[9].KIKA_TYPE = "1";
	FixStr[9].KIKA_KIND = "1";
	FixStr[9].KIKA_DECI = "1";
	FixStr[9].KIKA_NUM2 = "";
	FixStr[9].KIKA_NUM3 = "0";
	FixStr[9].KIKA_STR = "";
	FixStr[9].SOKU_FLG = "1";
	FixStr[9].TOKU_FLG = "0";
	FixStr[9].KIKA_PRT = "1";
	FixStr[9].VALUE_TYPE = "0";
	FixStr[9].VALUE_DECI = "1";

	//曲げ強さ（現物）
	FixStr[10].TABLE1 = "KDC1";
	FixStr[10].TABLE2 = "KDC2";
	FixStr[10].KOMK_NO = "11";
	FixStr[10].ORDER_NO = "8";
	FixStr[10].KOMK_NM = "曲げ強さ（現物）";
	FixStr[10].KOMK_ENG = "Transverse Strength(Genuine)";
	FixStr[10].KIKI_NO = "5";
	FixStr[10].KIKI_NM = "材料試験機";
	FixStr[10].TANI[0] = "kgf/c㎡";
	FixStr[10].TANI[1] = "N/c㎡";
	FixStr[10].TANI[2] = "Mpa";
	FixStr[10].TANI[3] = "N/m㎡";
    //2003/07/22 E.Takase 単位追加
	FixStr[10].TANI[4] = "N";
	FixStr[10].KIKA_TYPE = "1";
	FixStr[10].KIKA_KIND = "1";
	FixStr[10].KIKA_DECI = "1";
	FixStr[10].KIKA_NUM2 = "";
	FixStr[10].KIKA_NUM3 = "0";
	FixStr[10].KIKA_STR = "";
	FixStr[10].SOKU_FLG = "1";
	FixStr[10].TOKU_FLG = "0";
	FixStr[10].KIKA_PRT = "1";
	FixStr[10].VALUE_TYPE = "0";
	FixStr[10].VALUE_DECI = "1";

	//硬度ＨｓＣ（圧面）
	FixStr[11].TABLE1 = "KD61";
	FixStr[11].TABLE2 = "KD62";
	FixStr[11].KOMK_NO = "12";
	FixStr[11].ORDER_NO = "2";
	FixStr[11].KOMK_NM = "硬度ＨｓＣ（圧面）";
	FixStr[11].KOMK_ENG = "Hardness(HsC P)";
	FixStr[11].KIKI_NO = "9";
	FixStr[11].KIKI_NM = "ショア硬度計Ｃ型";
	FixStr[11].TANI[0] = "HsC";
	FixStr[11].TANI[1] = "";
	FixStr[11].TANI[2] = "";
	FixStr[11].TANI[3] = "";
	FixStr[11].KIKA_TYPE = "1";
	FixStr[11].KIKA_KIND = "1";
	FixStr[11].KIKA_DECI = "0";
	FixStr[11].KIKA_NUM2 = "";
	FixStr[11].KIKA_NUM3 = "0";
	FixStr[11].KIKA_STR = "";
	FixStr[11].SOKU_FLG = "1";
	FixStr[11].TOKU_FLG = "0";
	FixStr[11].KIKA_PRT = "1";
	FixStr[11].VALUE_TYPE = "0";
	FixStr[11].VALUE_DECI = "0";

	//硬度ＨｓＣ（側面）
	FixStr[12].TABLE1 = "KD61";
	FixStr[12].TABLE2 = "KD62";
	FixStr[12].KOMK_NO = "13";
	FixStr[12].ORDER_NO = "3";
	FixStr[12].KOMK_NM = "硬度ＨｓＣ（側面）";
	FixStr[12].KOMK_ENG = "Hardness(HsC S)";
	FixStr[12].KIKI_NO = "9";
	FixStr[12].KIKI_NM = "ショア硬度計Ｃ型";
	FixStr[12].TANI[0] = "HsC";
	FixStr[12].TANI[1] = "";
	FixStr[12].TANI[2] = "";
	FixStr[12].TANI[3] = "";
	FixStr[12].KIKA_TYPE = "1";
	FixStr[12].KIKA_KIND = "1";
	FixStr[12].KIKA_DECI = "0";
	FixStr[12].KIKA_NUM2 = "";
	FixStr[12].KIKA_NUM3 = "0";
	FixStr[12].KIKA_STR = "";
	FixStr[12].SOKU_FLG = "1";
	FixStr[12].TOKU_FLG = "0";
	FixStr[12].KIKA_PRT = "1";
	FixStr[12].VALUE_TYPE = "0";
	FixStr[12].VALUE_DECI = "0";

	//硬度 (HsD 圧面)
	FixStr[13].TABLE1 = "KD61";
	FixStr[13].TABLE2 = "KD62";
	FixStr[13].KOMK_NO = "14";
	FixStr[13].ORDER_NO = "4";
	FixStr[13].KOMK_NM = "硬度 (HsD 圧面）";
	FixStr[13].KOMK_ENG = "Hardness(HsD P)";
	FixStr[13].KIKI_NO = "10";
	FixStr[13].KIKI_NM = "ショア硬度計Ｄ型";
	FixStr[13].TANI[0] = "HsD";
	FixStr[13].TANI[1] = "";
	FixStr[13].TANI[2] = "";
	FixStr[13].TANI[3] = "";
	FixStr[13].KIKA_TYPE = "1";
	FixStr[13].KIKA_KIND = "1";
	FixStr[13].KIKA_DECI = "1";
	FixStr[13].KIKA_NUM2 = "";
	FixStr[13].KIKA_NUM3 = "0";
	FixStr[13].KIKA_STR = "";
	FixStr[13].SOKU_FLG = "1";
	FixStr[13].TOKU_FLG = "0";
	FixStr[13].KIKA_PRT = "1";
	FixStr[13].VALUE_TYPE = "0";
	FixStr[13].VALUE_DECI = "1";

	//硬度 (HsD 側面)
	FixStr[14].TABLE1 = "KD61";
	FixStr[14].TABLE2 = "KD62";
	FixStr[14].KOMK_NO = "15";
	FixStr[14].ORDER_NO = "5";
	FixStr[14].KOMK_NM = "硬度 (HsD 側面）";
	FixStr[14].KOMK_ENG = "Hardness(HsD S)";
	FixStr[14].KIKI_NO = "10";
	FixStr[14].KIKI_NM = "ショア硬度計Ｄ型";
	FixStr[14].TANI[0] = "HsD";
	FixStr[14].TANI[1] = "";
	FixStr[14].TANI[2] = "";
	FixStr[14].TANI[3] = "";
	FixStr[14].KIKA_TYPE = "1";
	FixStr[14].KIKA_KIND = "1";
	FixStr[14].KIKA_DECI = "1";
	FixStr[14].KIKA_NUM2 = "";
	FixStr[14].KIKA_NUM3 = "0";
	FixStr[14].KIKA_STR = "";
	FixStr[14].SOKU_FLG = "1";
	FixStr[14].TOKU_FLG = "0";
	FixStr[14].KIKA_PRT = "1";
	FixStr[14].VALUE_TYPE = "0";
	FixStr[14].VALUE_DECI = "1";

	//座屈
	FixStr[15].TABLE1 = "KD91";
	FixStr[15].TABLE2 = "KD92";
	FixStr[15].KOMK_NO = "16";
	FixStr[15].ORDER_NO = "16";
	FixStr[15].KOMK_NM = "座屈";
	FixStr[15].KOMK_ENG = "Crackforce";
	FixStr[15].KIKI_NO = "5";
	FixStr[15].KIKI_NM = "材料試験機";
	FixStr[15].TANI[0] = "N";
	FixStr[15].TANI[1] = "";
	FixStr[15].TANI[2] = "";
	FixStr[15].TANI[3] = "";
	FixStr[15].KIKA_TYPE = "1";
	FixStr[15].KIKA_KIND = "1";
	FixStr[15].KIKA_DECI = "1";
	FixStr[15].KIKA_NUM2 = "";
	FixStr[15].KIKA_NUM3 = "0";
	FixStr[15].KIKA_STR = "";
	FixStr[15].SOKU_FLG = "1";
	FixStr[15].TOKU_FLG = "0";
	FixStr[15].KIKA_PRT = "1";
	FixStr[15].VALUE_TYPE = "0";
	FixStr[15].VALUE_DECI = "1";

	//ヒストグラム(ブラシ厚さMin・Max)
	FixStr[16].TABLE1 = "KDA1";
	FixStr[16].TABLE2 = " ";
	FixStr[16].KOMK_NO = "17";
	FixStr[16].ORDER_NO = "17";
	FixStr[16].KOMK_NM = "ブラシ厚さ";
	FixStr[16].KOMK_ENG = "Brush Thickness";
	FixStr[16].KIKI_NO = "1";
	FixStr[16].KIKI_NM = "マイクロメータ";
	FixStr[16].TANI[0] = "mm";
	FixStr[16].TANI[1] = "";
	FixStr[16].TANI[2] = "";
	FixStr[16].TANI[3] = "";
	FixStr[16].KIKA_TYPE = "1";
	FixStr[16].KIKA_KIND = "";
	FixStr[16].KIKA_DECI = "2";
	FixStr[16].KIKA_NUM2 = "0";
	FixStr[16].KIKA_NUM3 = "0";
	FixStr[16].KIKA_STR = "";
	FixStr[16].SOKU_FLG = "1";
	FixStr[16].TOKU_FLG = "0";
	FixStr[16].KIKA_PRT = "1";
	FixStr[16].VALUE_TYPE = "0";
	FixStr[16].VALUE_DECI = "2";

	//ヒストグラム(ブラシ厚さCp・Cpk)
	FixStr[17].TABLE1 = "KDA1";
	FixStr[17].TABLE2 = " ";
	FixStr[17].KOMK_NO = "18";
	FixStr[17].ORDER_NO = "18";
	FixStr[17].KOMK_NM = "ブラシ厚さ";
	FixStr[17].KOMK_ENG = "Brush Thickness";
	FixStr[17].KIKI_NO = "1";
	FixStr[17].KIKI_NM = "マイクロメータ";
	FixStr[17].TANI[0] = "Cpk";
	FixStr[17].TANI[1] = "";
	FixStr[17].TANI[2] = "";
	FixStr[17].TANI[3] = "";
	FixStr[17].KIKA_TYPE = "1";
	FixStr[17].KIKA_KIND = "3";
	FixStr[17].KIKA_DECI = "2";
	FixStr[17].KIKA_NUM2 = "0";
	FixStr[17].KIKA_NUM3 = "0";
	FixStr[17].KIKA_STR = "";
	FixStr[17].SOKU_FLG = "1";
	FixStr[17].TOKU_FLG = "0";
	FixStr[17].KIKA_PRT = "1";
	FixStr[17].VALUE_TYPE = "0";
	FixStr[17].VALUE_DECI = "2";

}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：データベース検索
//
//  機能説明
//    製品規格マスタより得意先コード・得意先名称取得します
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    int					：0=検索成功 -1=検索失敗
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
int __fastcall TForm1::GetDTKS(void)
{
	AnsiString sBuf;

	KSD21.DTKSCOD = "";
	KSD21.DTKSNAM = "";

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行
	sBuf = "";
	sBuf += "SELECT DTKSCOD, DTKSNAM, DTKSHIN, HINBAN ";
	sBuf += "FROM KM02 WHERE DTKSHIN='";
	sBuf += KD_1.DTKSHIN;
	sBuf += "' AND REVCNT = 0";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof && Query1->Eof ) {
	//検索結果 ０件
		return(-1);
	}
	Query1->First();
	KSD21.DTKSCOD = Null_S(Query1->FieldValues["DTKSCOD"]);
	KSD21.DTKSNAM = Null_S(Query1->FieldValues["DTKSNAM"]);


	return(0);
}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：データベース検索
//
//  機能説明
//    製品規格マスタより、形状区分取得
//
//  パラメタ説明
//    int iNo				：処理対象の測定項目ID
//
//  戻り値
//    int					：0=検索成功 -1=検索失敗
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::GetKEIJYO_KBN(void)
{
	AnsiString sBuf;
	AnsiString sKEIJYO_KBN;
	AnsiString sDTKSHIN;

	sKEIJYO_KBN = "";
	sDTKSHIN    = Null_S(Q_KD_1->FieldValues["DTKSHIN"]);
	
	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行
	sBuf  = "";
	sBuf += "SELECT KEIJKBN ";
	sBuf += "FROM KM02 WHERE DTKSHIN='";
	sBuf += sDTKSHIN;
	sBuf += "' AND REVCNT = 0";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof && Query1->Eof ) {
	//検索結果 ０件
		return(-1);
	}
	Query1->First();
	sKEIJYO_KBN = Null_S(Query1->FieldValues["KEIJKBN"]);


	return(sKEIJYO_KBN);
}

/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：文字列操作
//
//  機能説明
//    引数がNullならスペースを返す
//
//  パラメタ説明
//    Variant &vBuf			：処理対象文字列
//
//  戻り値
//    AnsiString			：文字列操作結果
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::Null_S(Variant &vBuf)
{
	AnsiString sBuf;

	if ( vBuf.IsNull() ) {
		sBuf = " ";
	} else {
		sBuf = VarToStr(vBuf);
	}
	return ( sBuf );

}

/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：文字列操作
//
//  機能説明
//    備考strMにstrAを挿入
//
//  パラメタ説明
//    AnsiString strM		：代入される文字列
//    int iNo				：処理対象の測定項目ID
//    AnsiString strA		：代入する文字列
//
//  戻り値
//    AnsiString			：文字列操作結果
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
AnsiString __fastcall TForm1::InsMEMO(AnsiString strM, int iNo, AnsiString strA)
{
	int iPos;
	int iPos2;
	int iPos3;
	int iLen;
	int i;
	AnsiString sBuf;
	AnsiString sBuf2;
	sBuf = "";
	sBuf2 = "";

	//MEMOStr配列初期化
	for ( i = 0; i < FixStrNum; i++ ) {
		MEMOStr[i] = "";
	}

	//MEMOStr配列にセット
	for ( i = 0; i < FixStrNum; i++ ) {
		iPos = strM.AnsiPos(FixStr[i].KOMK_NM);
		//テスト用で書き換えた。iPos = strM.AnsiPos(FixStr[i].KOMK_NO);
		if ( iPos > 0 ) {
			iLen = strM.Length();
			iPos2 = iPos + FixStr[i].KOMK_NM.Length() ;
			sBuf = strM.SubString(iPos2+1,iLen-iPos2);
			iPos3 = sBuf.AnsiPos("┃");
			if ( iPos3 > 0 ) {
				sBuf2 = sBuf.SubString(1,iPos3-2);
			} else {
				sBuf2 = sBuf;
			}
            MEMOStr[i] = sBuf2;
		}
	}

	MEMOStr[iNo] = strA;
	sBuf = "";
	for ( i = 0; i < FixStrNum; i++ ) {
		if ( Trim(MEMOStr[i]) != "" ) {
			sBuf += FixStr[i].KOMK_NM + ":" + MEMOStr[i] + "┃";
			//テスト用で書き換えた。sBuf += FixStr[i].KOMK_NO + ":" + MEMOStr[i] + "┃";
		}
	}

	//MEMOの最大文字数は128
	if ( sBuf.Length() > 128 ) {
		if ( sBuf.ByteType(128) == mbLeadByte ) {
			sBuf2 = sBuf.SubString(1,128-1);
		} else {
			sBuf2 = sBuf.SubString(1,128);
		}
	} else {
    	sBuf2 = sBuf;
	}
	return(sBuf2);
}
/*----------------------------------------------------------------------------*/
//
//  概要
//    自作関数				：ログ出力
//
//  機能説明
//    リストボックス・ログファイルにログを出力
//
//  パラメタ説明
//    AnsiString sErrLog	：エラーメッセージ
//    AnsiString sePrg		：関数名
//    AnsiString seDTKSHIN	：得意先品番
//    AnsiString seLOTNO  	：ロットNo
//
//  戻り値
//    AnsiString			：文字列操作結果
//
//  備考
//    なし
//
/*----------------------------------------------------------------------------*/
//リストボックスにログを出力
void __fastcall TForm1::WriteErrLog(AnsiString sErrLog,  AnsiString sePrg,
								 	AnsiString seDTKSHIN,AnsiString seLOTNO)
{
	AnsiString sBuf;
	AnsiString FileName;
	FILE *fp;

    if ( ListLog->Items->Count > 100 ) {
    	ListLog->Clear();
    }

	sBuf = "";
	sBuf += sePrg + AnsiString::StringOfChar(' ', 25-sePrg.Length());
	sBuf += "DTKSHIN：" + seDTKSHIN + AnsiString::StringOfChar(' ', 20-seDTKSHIN.Length());
	sBuf += " LOTNO：" + seLOTNO    + AnsiString::StringOfChar(' ', 8-seLOTNO.Length());
    ListLog->Items->Add(sBuf);

    if ( Trim(sErrLog) != "" ) {
		sBuf = "   Error：" + sErrLog + "(" + sePrg + ")";
        ListLog->Items->Add(sBuf);
    }


    Form1->Refresh();


    FileName = Application->ExeName;
    FileName = FileName.SubString(1,FileName.Length()-4);
    FileName = FileName + ".log";
	if( (fp = fopen( FileName.c_str(), "a" )) != NULL ){
		fprintf(fp,"%s\n", sBuf.c_str());
		fclose(fp);
	}


}
//---------------------------------------------------------------------------


