//---------------------------------------------------------------------------
//
//  Unit1.cpp
//    【出荷検査システム－測定項目マスター】
//    メインフォーム（TForm1クラス）のメンバ関数の定義
//
//  作成者
//    田村　敦司
//
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma link "PERFGRAP"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//
//  概要
//    OnCreateイベント	：Form1を作成したときに発生します。
//
//  機能説明
//    初期画面の状態を設定します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    フォームが作成されるときイベントが以下の順序で発生します。
//    OnCreate→OnShow→OnActivate→OnPaint
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{

    // 検索中フォームを表示します
    Form2 = new TForm2(this);
	Form2->Show();
	Form2->Refresh();

    // データベース初期化
    Database1->Open();

	// グリッドの初期化
	SGr_List->ColCount = 30;
	SGr_List->ColWidths[0] = 34;
	SGr_List->ColWidths[1] = 175;
	SGr_List->ColWidths[2] = 160;
	SGr_List->ColWidths[3] = 102;
	SGr_List->ColWidths[4] = 50;
	SGr_List->ColWidths[5] = 156;
	SGr_List->ColWidths[6] = 25;
	SGr_List->ColWidths[7] = 55;
	SGr_List->ColWidths[8] = 30;
	SGr_List->ColWidths[9] = 30;
	SGr_List->ColWidths[10] = 78;
	SGr_List->ColWidths[11] = 50;
	SGr_List->ColWidths[12] = 0;
	SGr_List->ColWidths[13] = 0;
	SGr_List->ColWidths[14] = 0;
	SGr_List->ColWidths[15] = 0;
	SGr_List->ColWidths[16] = 0;
	SGr_List->ColWidths[17] = 0;
	SGr_List->ColWidths[18] = 0;
	SGr_List->ColWidths[19] = 0;
	SGr_List->ColWidths[20] = 0;
	SGr_List->ColWidths[21] = 0;
	SGr_List->ColWidths[22] = 0;
	SGr_List->ColWidths[23] = 0;
	SGr_List->ColWidths[24] = 0;
	SGr_List->ColWidths[25] = 0;
	SGr_List->ColWidths[26] = 0;
	SGr_List->ColWidths[27] = 0;
	SGr_List->ColWidths[28] = 0;
	SGr_List->ColWidths[29] = 0;

	SGr_List->Cells[0][0] = "  NO";
	SGr_List->Cells[1][0] = "測定項目";
	SGr_List->Cells[2][0] = "測定項目(English)";
	SGr_List->Cells[3][0] = "測定機器";
	SGr_List->Cells[4][0] = "単位";
	SGr_List->Cells[5][0] = "規格(基本)";
	SGr_List->Cells[6][0] = "n数(基本)";
	SGr_List->Cells[7][0] = "値表現";
	SGr_List->Cells[8][0] = "測定";
	SGr_List->Cells[9][0] = "特別";
	SGr_List->Cells[10][0] = "更新日";
	SGr_List->Cells[11][0] = "更新者";

	SGr_List2->ColCount = 30;
	SGr_List2->ColWidths[0] = 34;
	SGr_List2->ColWidths[1] = 175;
	SGr_List2->ColWidths[2] = 160;
	SGr_List2->ColWidths[3] = 102;
	SGr_List2->ColWidths[4] = 50;
	SGr_List2->ColWidths[5] = 156;
	SGr_List2->ColWidths[6] = 25;
	SGr_List2->ColWidths[7] = 55;
	SGr_List2->ColWidths[8] = 30;
	SGr_List2->ColWidths[9] = 30;
	SGr_List2->ColWidths[10] = 78;
	SGr_List2->ColWidths[11] = 50;
	SGr_List2->ColWidths[12] = 0;
	SGr_List2->ColWidths[13] = 0;
	SGr_List2->ColWidths[14] = 0;
	SGr_List2->ColWidths[15] = 0;
	SGr_List2->ColWidths[16] = 0;
	SGr_List2->ColWidths[17] = 0;
	SGr_List2->ColWidths[18] = 0;
	SGr_List2->ColWidths[19] = 0;
	SGr_List2->ColWidths[20] = 0;
	SGr_List2->ColWidths[21] = 0;
	SGr_List2->ColWidths[22] = 0;
	SGr_List2->ColWidths[23] = 0;
	SGr_List2->ColWidths[24] = 0;
	SGr_List2->ColWidths[25] = 0;
	SGr_List2->ColWidths[26] = 0;
	SGr_List2->ColWidths[27] = 0;
	SGr_List2->ColWidths[28] = 0;
	SGr_List2->ColWidths[29] = 0;

	SGr_List2->Cells[0][0] = "  NO";
	SGr_List2->Cells[1][0] = "測定項目";
	SGr_List2->Cells[2][0] = "測定項目(English)";
	SGr_List2->Cells[3][0] = "測定機器";
	SGr_List2->Cells[4][0] = "単位";
	SGr_List2->Cells[5][0] = "規格(基本)";
	SGr_List2->Cells[6][0] = "n数(基本)";
	SGr_List2->Cells[7][0] = "値表現";
	SGr_List2->Cells[8][0] = "測定";
	SGr_List2->Cells[9][0] = "特別";
	SGr_List2->Cells[10][0] = "更新日";
	SGr_List2->Cells[11][0] = "更新者";

    Pnl_KIKAKU_KIJYUN->Left = Pnl_KIKAKU_MOJI->Left;

    // Grid用フォントの作成
    LogFont.lfHeight = 10;
    LogFont.lfWidth = 0;
    LogFont.lfEscapement = 0;
    LogFont.lfOrientation = 0;
    LogFont.lfWeight = FW_NORMAL;
    LogFont.lfItalic = 0;
    LogFont.lfUnderline = 0;
    LogFont.lfStrikeOut = 0;
    LogFont.lfCharSet = SHIFTJIS_CHARSET;
    LogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    LogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    LogFont.lfQuality = DEFAULT_QUALITY;
    LogFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    strcpy( LogFont.lfFaceName, "ＭＳ ゴシック" );
    MyFont = CreateFontIndirect( &LogFont );

}

//---------------------------------------------------------------------------
//
//  概要
//    OnActivateイベント	：フォームがアクティブになったときに発生します。
//
//  機能説明
//    初期表示に必要なデータを検索します
//    検索中画面(Form2)を閉じます
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{

	int iRow;
	AnsiString sBuf;

   	// 新しいトランザクションを開始
    if( Database1->InTransaction == false ){
        Database1->StartTransaction();
        DataSave = false;
    }

    //----------------------------------------------
    // 測定機器項目マスターの検索

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行（測定機器項目マスターの件数取得）
	sBuf = "SELECT COUNT(*) AS KIKI_NUM FROM KSM14";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if( !Query1->Eof ){
        iKIKI_Cnt = Query1->FieldValues["KIKI_NUM"];
    }
    else {
        iKIKI_Cnt = 50;
    }

    // メモリの確保（測定機器項目マスターの件数分）
    hMemKIKI = GlobalAlloc( GHND, sizeof(int) * iKIKI_Cnt );
    if( hMemKIKI == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    iKIKI = (int *)GlobalLock(hMemKIKI);
    if( hMemKIKI == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行（測定機器項目マスター）
	sBuf = "SELECT KIKI_NO, KIKI_NM FROM KSM14 ORDER BY ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

    iRow = 0;
	while( !Query1->Eof ){

        // 機器名をコンボボックスに追加
		sBuf = Query1->FieldValues["KIKI_NM"];
        Cmb_SKTKIKI->Items->Add(sBuf);

        // 機器Noを記憶（配列番号は、コンボボックスのItemインデックス）
        iKIKI[iRow] = Query1->FieldValues["KIKI_NO"];
        iRow++;

		// カーソルを次にセットする
		Query1->Next();
    }


    //----------------------------------------------
    // 単位マスターの検索

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行（単位マスター）
	sBuf = "SELECT TANI FROM KSM92 ORDER BY ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

    Cmb_TANI->Clear();
	while( !Query1->Eof ){

        // 機器名をコンボボックスに追加
		sBuf = Query1->FieldValues["TANI"];
        Cmb_TANI->Items->Add(sBuf);

		// カーソルを次にセットする
		Query1->Next();
    }


    //----------------------------------------------
    // 測定項目マスター検索

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行（測定項目マスター）
	//sBuf = "SELECT * FROM KSM11 ORDER BY ORDER_NO";
	sBuf  = "SELECT KSM11.KOMK_NO, KSM11.ORDER_NO, KSM11.KOMK_NM,";
    sBuf +=       " KSM11.KOMK_ENG, KSM11.KOMK_SUB, KSM11.KOMK_SUB_ENG,";
    sBuf +=       " KSM11.KIKI_NO, KSM11.KIKI_NM, KSM11.TANI, KSM11.KIKA_TYPE,";
    sBuf +=       " KSM11.KIKA_KIND, KSM11.KIKA_DECI, KSM11.KIKA_NUM1,";
    sBuf +=       " KSM11.KIKA_NUM2, KSM11.KIKA_NUM3, KSM11.KIKA_STR,";
    sBuf +=       " KSM11.KIKA_SUB1, KSM11.KIKA_SUB2, KSM11.KIKA_SUB3,";
    sBuf +=       " KSM11.SOKU_SU, KSM11.SOKU_FLG, KSM11.TOKU_FLG,";
    sBuf +=       " KSM11.KIKA_PRT, KSM11.VALUE_TYPE, KSM11.VALUE_DECI,";
    sBuf +=       " KSM11.ADDYMD, KSM11.ADDTIM, KSM11.UPDYMD, KSM11.UPDTIM,";
    sBuf +=       " KSM11.UPDCHR, KSM11.UPDCNT, SM12S.TANNAM";
    sBuf += " FROM KSM11 LEFT JOIN SM12S ON KSM11.UPDCHR = SM12S.TANSYA";
    sBuf += " ORDER BY KSM11.ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	iRow = 1;
    iSOKUT_KMK_NO_MAX = 0;

	while( !Query1->Eof ){

		// グリッドの最大行数が超えていないかチェックする
		if( iRow >= SGr_List->RowCount ){
			SGr_List->RowCount = iRow + 1;
		}

		// グリッドにデータをセットします。
		sBuf = iRow ;
		SGr_List->Cells[0][iRow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

        if( VarIsNull(Query1->FieldValues["KOMK_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_NM"];
		}
        SGr_List->Cells[1][iRow] = sBuf;   //測定項目（日本語）

        if( VarIsNull(Query1->FieldValues["KOMK_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_ENG"];
        }
        SGr_List->Cells[2][iRow] = sBuf;   //測定項目（英語）

		sBuf = Query1->FieldValues["KIKI_NM"];
		SGr_List->Cells[3][iRow] = sBuf;   //測定機器名称

        if( VarIsNull(Query1->FieldValues["TANI"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["TANI"];
        }
		SGr_List->Cells[4][iRow] = sBuf;   //単位

		SGr_List->Cells[5][iRow] = "";     //規格（基本）   ※再描画する為に必要です。

		sBuf = Query1->FieldValues["SOKU_SU"];
		SGr_List->Cells[6][iRow] = sBuf;   //ｎ数（基本）

		sBuf = Query1->FieldValues["VALUE_TYPE"];
		SGr_List->Cells[7][iRow] = sBuf;   //値表現

		sBuf = Query1->FieldValues["SOKU_FLG"];
		SGr_List->Cells[8][iRow] = sBuf;   //測定項目の有無

		sBuf = Query1->FieldValues["TOKU_FLG"];
		SGr_List->Cells[9][iRow] = sBuf;   //特別項目の有無

		sBuf = Query1->FieldValues["UPDYMD"];
        SGr_List->Cells[10][iRow] = sBuf;   //変更日

		sBuf = Query1->FieldValues["UPDCHR"];
		SGr_List->Cells[12][iRow] = sBuf;   //更新者(担当者コード)

        if( VarIsNull(Query1->FieldValues["TANNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["TANNAM"];
        }
		SGr_List->Cells[11][iRow] = sBuf;   //更新者

		sBuf = Query1->FieldValues["KOMK_NO"];
		SGr_List->Cells[13][iRow] = sBuf;   //項目NO
        // 最大の項目NOを取得します
	    if( StrToInt(sBuf) > iSOKUT_KMK_NO_MAX ){
        	iSOKUT_KMK_NO_MAX = StrToInt(sBuf);
        }

		sBuf = Query1->FieldValues["ORDER_NO"];
		SGr_List->Cells[14][iRow] = sBuf;   //表示順

		sBuf = Query1->FieldValues["KIKI_NO"];
		SGr_List->Cells[15][iRow] = sBuf;   //測定機器NO

		sBuf = Query1->FieldValues["KIKA_TYPE"];
		SGr_List->Cells[16][iRow] = sBuf;   //規格タイプ

		sBuf = Query1->FieldValues["KIKA_KIND"];
		SGr_List->Cells[17][iRow] = sBuf;   //規格種類

		sBuf = Query1->FieldValues["KIKA_DECI"];
		SGr_List->Cells[18][iRow] = sBuf;   //規格小数点以下桁数

		sBuf = Query1->FieldValues["KIKA_NUM1"];
		SGr_List->Cells[19][iRow] = sBuf;   //規格値１

		sBuf = Query1->FieldValues["KIKA_NUM2"];
		SGr_List->Cells[20][iRow] = sBuf;   //規格値２

		sBuf = Query1->FieldValues["KIKA_NUM3"];
		SGr_List->Cells[21][iRow] = sBuf;   //規格値３

        if( VarIsNull(Query1->FieldValues["KIKA_STR"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KIKA_STR"];
        }
		SGr_List->Cells[22][iRow] = sBuf;   //規格文字

		sBuf = Query1->FieldValues["KIKA_PRT"];
		SGr_List->Cells[23][iRow] = sBuf;   //上限下限値の印刷

		sBuf = Query1->FieldValues["VALUE_DECI"];
		SGr_List->Cells[24][iRow] = sBuf;   //測定値小数点以下桁数

		sBuf = Query1->FieldValues["ADDYMD"];
		SGr_List->Cells[25][iRow] = sBuf;   //登録日

		sBuf = Query1->FieldValues["ADDTIM"];
		SGr_List->Cells[26][iRow] =  sBuf;  //登録時間

		sBuf = Query1->FieldValues["UPDTIM"];
		SGr_List->Cells[27][iRow] = sBuf;   //更新時間

		sBuf = Query1->FieldValues["UPDCNT"];
		SGr_List->Cells[28][iRow] = sBuf;   //更新回数

		SGr_List->Cells[29][iRow] = "0";    //更新フラグ

		// カーソルを次にセットする
		Query1->Next();

		iRow += 1;
	}

    // データ件数を表示します
    sBuf = iRow-1;
    LblListCnt->Caption = "件数：" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

    SGr_List->RowCount = iRow + 1;
    SGr_List->Cells[0][iRow] = "";
    SGr_List->Cells[1][iRow] = "";
    SGr_List->Cells[2][iRow] = "";
    SGr_List->Cells[3][iRow] = "";
    SGr_List->Cells[4][iRow] = "";
    SGr_List->Cells[5][iRow] = "";
    SGr_List->Cells[6][iRow] = "";
    SGr_List->Cells[7][iRow] = "";
    SGr_List->Cells[8][iRow] = "";
    SGr_List->Cells[9][iRow] = "";
    SGr_List->Cells[10][iRow] = "";
    SGr_List->Cells[11][iRow] = "";
    SGr_List->Cells[12][iRow] = "";
    SGr_List->Cells[13][iRow] = "";
    SGr_List->Cells[14][iRow] = "";
    SGr_List->Cells[15][iRow] = "";
    SGr_List->Cells[16][iRow] = "";
    SGr_List->Cells[17][iRow] = "";
    SGr_List->Cells[18][iRow] = "";
    SGr_List->Cells[19][iRow] = "";
    SGr_List->Cells[20][iRow] = "";
    SGr_List->Cells[21][iRow] = "";
    SGr_List->Cells[22][iRow] = "";
    SGr_List->Cells[23][iRow] = "";
    SGr_List->Cells[24][iRow] = "";
    SGr_List->Cells[25][iRow] = "";
    SGr_List->Cells[26][iRow] = "";
    SGr_List->Cells[27][iRow] = "";
    SGr_List->Cells[28][iRow] = "";
    SGr_List->Cells[29][iRow] = "";


    //----------------------------------------------
    // 材料証明項目マスター検索

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行（測定項目マスター）
	//sBuf = "SELECT * FROM KSM12 ORDER BY ORDER_NO";
	sBuf  = "SELECT KSM12.KOMK_NO, KSM12.ORDER_NO, KSM12.KOMK_NM,";
    sBuf +=       " KSM12.KOMK_ENG, KSM12.KOMK_SUB, KSM12.KOMK_SUB_ENG,";
    sBuf +=       " KSM12.KIKI_NO, KSM12.KIKI_NM, KSM12.TANI, KSM12.KIKA_TYPE,";
    sBuf +=       " KSM12.KIKA_KIND, KSM12.KIKA_DECI, KSM12.KIKA_NUM1,";
    sBuf +=       " KSM12.KIKA_NUM2, KSM12.KIKA_NUM3, KSM12.KIKA_STR,";
    sBuf +=       " KSM12.KIKA_SUB1, KSM12.KIKA_SUB2, KSM12.KIKA_SUB3,";
    sBuf +=       " KSM12.SOKU_SU, KSM12.SOKU_FLG, KSM12.TOKU_FLG,";
    sBuf +=       " KSM12.KIKA_PRT, KSM12.VALUE_TYPE, KSM12.VALUE_DECI,";
    sBuf +=       " KSM12.ADDYMD, KSM12.ADDTIM, KSM12.UPDYMD, KSM12.UPDTIM,";
    sBuf +=       " KSM12.UPDCHR, KSM12.UPDCNT, SM12S.TANNAM";
    sBuf += " FROM KSM12 LEFT JOIN SM12S ON KSM12.UPDCHR = SM12S.TANSYA";
    sBuf += " ORDER BY KSM12.ORDER_NO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	iRow = 1;
    iZAIRY_KMK_NO_MAX = 0;

	while( !Query1->Eof ){

		// グリッドの最大行数が超えていないかチェックする
		if( iRow >= SGr_List2->RowCount ){
			SGr_List2->RowCount = iRow + 1;
		}

		// グリッドにデータをセットします。
		sBuf = iRow ;
		SGr_List2->Cells[0][iRow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;    //No
		sBuf = iRow + 1;

        if( VarIsNull(Query1->FieldValues["KOMK_NM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_NM"];
		}
        SGr_List2->Cells[1][iRow] = sBuf;   //測定項目（日本語）

        if( VarIsNull(Query1->FieldValues["KOMK_ENG"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KOMK_ENG"];
        }
        SGr_List2->Cells[2][iRow] = sBuf;   //測定項目（英語）

		sBuf = Query1->FieldValues["KIKI_NM"];
		SGr_List2->Cells[3][iRow] = sBuf;   //測定機器名称

        if( VarIsNull(Query1->FieldValues["TANI"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["TANI"];
		}
        SGr_List2->Cells[4][iRow] = sBuf;   //単位

		SGr_List2->Cells[5][iRow] = "";     //規格（基本）   ※再描画する為に必要です。

		sBuf = Query1->FieldValues["SOKU_SU"];
		SGr_List2->Cells[6][iRow] = sBuf;   //ｎ数（基本）

		sBuf = Query1->FieldValues["VALUE_TYPE"];
		SGr_List2->Cells[7][iRow] = sBuf;   //値表現

		sBuf = Query1->FieldValues["SOKU_FLG"];
		SGr_List2->Cells[8][iRow] = sBuf;   //測定項目の有無

		sBuf = Query1->FieldValues["TOKU_FLG"];
		SGr_List2->Cells[9][iRow] = sBuf;   //特別項目の有無

		sBuf = Query1->FieldValues["UPDYMD"];
        SGr_List2->Cells[10][iRow] = sBuf;   //変更日

		sBuf = Query1->FieldValues["UPDCHR"];
		SGr_List2->Cells[12][iRow] = sBuf;   //更新者(担当者コード)

        if( VarIsNull(Query1->FieldValues["TANNAM"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["TANNAM"];
        }
		SGr_List2->Cells[11][iRow] = sBuf;   //更新者

		sBuf = Query1->FieldValues["KOMK_NO"];
		SGr_List2->Cells[13][iRow] = sBuf;   //項目NO
        // 最大の項目NOを取得します
	    if( StrToInt(sBuf) > iZAIRY_KMK_NO_MAX ){
        	iZAIRY_KMK_NO_MAX = StrToInt(sBuf);
        }

		sBuf = Query1->FieldValues["ORDER_NO"];
		SGr_List2->Cells[14][iRow] = sBuf;   //表示順

		sBuf = Query1->FieldValues["KIKI_NO"];
		SGr_List2->Cells[15][iRow] = sBuf;   //測定機器NO

		sBuf = Query1->FieldValues["KIKA_TYPE"];
		SGr_List2->Cells[16][iRow] = sBuf;   //規格タイプ

		sBuf = Query1->FieldValues["KIKA_KIND"];
		SGr_List2->Cells[17][iRow] = sBuf;   //規格種類

		sBuf = Query1->FieldValues["KIKA_DECI"];
		SGr_List2->Cells[18][iRow] = sBuf;   //規格小数点以下桁数

		sBuf = Query1->FieldValues["KIKA_NUM1"];
		SGr_List2->Cells[19][iRow] = sBuf;   //規格値１

		sBuf = Query1->FieldValues["KIKA_NUM2"];
		SGr_List2->Cells[20][iRow] = sBuf;   //規格値２

		sBuf = Query1->FieldValues["KIKA_NUM3"];
		SGr_List2->Cells[21][iRow] = sBuf;   //規格値３

        if( VarIsNull(Query1->FieldValues["KIKA_STR"]) ){
			sBuf = "";
		} else{
			sBuf = Query1->FieldValues["KIKA_STR"];
		}
        SGr_List2->Cells[22][iRow] = sBuf;   //規格文字

		sBuf = Query1->FieldValues["KIKA_PRT"];
		SGr_List2->Cells[23][iRow] = sBuf;   //上限下限値の印刷

		sBuf = Query1->FieldValues["VALUE_DECI"];
		SGr_List2->Cells[24][iRow] = sBuf;   //測定値小数点以下桁数

		sBuf = Query1->FieldValues["ADDYMD"];
		SGr_List2->Cells[25][iRow] = sBuf;   //登録日

		sBuf = Query1->FieldValues["ADDTIM"];
		SGr_List2->Cells[26][iRow] =  sBuf;  //登録時間

		sBuf = Query1->FieldValues["UPDTIM"];
		SGr_List2->Cells[27][iRow] = sBuf;   //更新時間

		sBuf = Query1->FieldValues["UPDCNT"];
		SGr_List2->Cells[28][iRow] = sBuf;   //更新回数

		SGr_List2->Cells[29][iRow] = "0";    //更新フラグ

		// カーソルを次にセットする
		Query1->Next();

		iRow += 1;
	}

    // データ件数を表示します
    sBuf = iRow-1;
    LblListCnt2->Caption = "件数：" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

    SGr_List2->RowCount = iRow + 1;
    SGr_List2->Cells[0][iRow] = "";
    SGr_List2->Cells[1][iRow] = "";
    SGr_List2->Cells[2][iRow] = "";
    SGr_List2->Cells[3][iRow] = "";
    SGr_List2->Cells[4][iRow] = "";
    SGr_List2->Cells[5][iRow] = "";
    SGr_List2->Cells[6][iRow] = "";
    SGr_List2->Cells[7][iRow] = "";
    SGr_List2->Cells[8][iRow] = "";
    SGr_List2->Cells[9][iRow] = "";
    SGr_List2->Cells[10][iRow] = "";
    SGr_List2->Cells[11][iRow] = "";
    SGr_List2->Cells[12][iRow] = "";
    SGr_List2->Cells[13][iRow] = "";
    SGr_List2->Cells[14][iRow] = "";
    SGr_List2->Cells[15][iRow] = "";
    SGr_List2->Cells[16][iRow] = "";
    SGr_List2->Cells[17][iRow] = "";
    SGr_List2->Cells[18][iRow] = "";
    SGr_List2->Cells[19][iRow] = "";
    SGr_List2->Cells[20][iRow] = "";
    SGr_List2->Cells[21][iRow] = "";
    SGr_List2->Cells[22][iRow] = "";
    SGr_List2->Cells[23][iRow] = "";
    SGr_List2->Cells[24][iRow] = "";
    SGr_List2->Cells[25][iRow] = "";
    SGr_List2->Cells[26][iRow] = "";
    SGr_List2->Cells[27][iRow] = "";
    SGr_List2->Cells[28][iRow] = "";
    SGr_List2->Cells[29][iRow] = "";

    //１行目を自動選択します
    SGr_ListSelectCell( SGr_List, 1, 1, true);
    SGr_ListClick( SGr_List );

	Form2->Close();
	Form2->Refresh();
}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyDownイベント	：ユーザーが任意のキーを押すと発生します
//
//  機能説明
//    ファンクションキー、Enterキーによりボタンを選択します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    WORD &Key			：キーコード
//    TShiftState Shift	：[Shift]，[Alt]，[Ctrl]キーを判定します
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    AnsiString sBuf;
    // ステータスメッセージ
    if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
    }

     switch(Key)
     {
         case VK_F2:  BtnF02Click(BtnF02);    Key = 0; break;
         case VK_F3:  BtnF03Click(BtnF03);    Key = 0; break;
         case VK_F4:  BtnF04Click(BtnF04);    Key = 0; break;
         case VK_F5:  BtnF05Click(BtnF05);    Key = 0; break;
         case VK_F8:  BtnF08Click(BtnF08);    Key = 0; break;
         case VK_F9:  BtnF09Click(BtnF09);    Key = 0; break;
         case VK_F10: BtnF10Click(BtnF10);    Key = 0; break;
         case VK_F11: BtnF11Click(BtnF11);    Key = 0; break;
         case VK_F12: BtnF12Click(BtnF12);    Key = 0; break;

         // Enter
         case VK_RETURN:
                // 詳細部
                if( Nmb_N->Focused() ){
                    BtnF08->SetFocus();
                    break;
                }
                else {
                	keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }

     }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnCloseQueryイベント：Close メソッドが呼び出されたときまたはユーザーが
//          フォームのシステムメニューで［閉じる］を選択したときに発生します。
//
//  機能説明
//    更新したデータが未保存の場合、保存するかしないかを確認します。
//    保存する場合は、「Ｆ１１：保存」ボタン処理をコールしデータを保存します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    bool &CanClose	：true  = そのままフォームを閉じます
//                        false = フォームCloseをキャンセルします
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    // データを変更したかどうかのフラグチェック
    if( DataSave ){
        switch( MessageDlg( "データが編集されています。\n保存しますか？",
                           mtConfirmation, mbYesNoCancel, 0) ){
            // 「Yes」      保存
            case mrYes:
	            BtnF11Click(Sender);
                break;
            // 「No」       変更を破棄
            case mrNo:
                if( Database1->InTransaction == True )  Database1->Rollback();
                break;
            // 「Cancel」   キャンセル
            case mrCancel:
                CanClose = false;
                return;
        }
    }
    else{
        if( Database1->InTransaction == True )  Database1->Rollback();
    }

	// データベース接続を開放します
    Query1->Close();
    //Query2->Close();

	Database1->Close();

    // メモリの開放
    if( hMemKIKI ){
        GlobalUnlock( hMemKIKI );
        GlobalFree( hMemKIKI );
    }

    // Grid用フォントの開放
    DeleteObject( MyFont );

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ２：前項」ボタンを押した時の処理
//
//  機能説明
//    選択行を1つ上に移動します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    if( !BtnF02->Enabled )    return;
	if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
	    if(SGr_List->Row > 1){
        	SGr_List->Row -= 1;
        	SGr_List->SetFocus();
    	}
	} else{
	    if(SGr_List2->Row > 1){
        	SGr_List2->Row -= 1;
        	SGr_List2->SetFocus();
    	}
	}

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ３：次項」ボタンを押した時の処理
//
//  機能説明
//    選択行を1つ下に移動します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    if( !BtnF03->Enabled )    return;
	if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
    	if( (SGr_List->RowCount-1) > SGr_List->Row ){
        	SGr_List->Row += 1;
        	SGr_List->SetFocus();
    	}
	} else{
    	if( (SGr_List2->RowCount-1) > SGr_List2->Row ){
        	SGr_List2->Row += 1;
        	SGr_List2->SetFocus();
    	}
	}
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ４：切替」ボタンを押した時の処理
//
//  機能説明
//    選択タブ（出荷検査項目又は材料証明項目）を切り替えます
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF04Click(TObject *Sender)
{
    if( !BtnF04->Enabled )    return;
	if( PgCtr_List->ActivePage->Name == "TabSheet1" ){
	  	PgCtr_List->SelectNextPage(true);
	} else{
	  	PgCtr_List->SelectNextPage(false);
	}
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ５：画面印刷」ボタンを押した時の処理
//
//  機能説明
//    メインフォームを印刷します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{
    if( !BtnF05->Enabled )    return;

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "画面印刷中です... しばらくお待ちください。";
    SBr1->Update();

    Form1->Print();

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ８：新規登録」ボタンを押した時の処理
//
//  機能説明
//    画面下に入力された項目をテーブル（KSM11,KSM12）に登録します
//    StringGridに一行追加します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
    AnsiString sBuf;
    int i, k;
    int iRow;
    int iORDER_NO;
    int nRet;
    int iKMK_NO_MAX;

    TButton *btn = (TButton *)Sender;

    if( !BtnF08->Enabled )    return;

    // 入力データのチェック
    if(Edt_SKTKMK_JPN->Text.IsEmpty()){
        MessageDlg("項目名を入力してください。", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
        Edt_SKTKMK_JPN->SetFocus();
        return;
    }

    if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
        if( Nmb_KIKAKU_HANI_MIN->Text.ToIntDef(0) >
            Nmb_KIKAKU_HANI_MAX->Text.ToIntDef(0) ){
            MessageDlg("規格の範囲指定が正しくありません。", mtWarning
                              ,TMsgDlgButtons() << mbOK, 0);
            Nmb_KIKAKU_HANI_MIN->SetFocus();
            return;
        }
    }

    // 既に登録されている項目名をチェックします
    if( Rdo_TYPE_SYUKA->Checked == true ){

        // 出荷検査測定用項目
        for( i = 1; i < SGr_List->RowCount; i++ ){
            sBuf = SGr_List->Cells[1][i];
	    	if( Edt_SKTKMK_JPN->Text == sBuf ){
		        nRet = MessageDlg("既に同じ測定項目が登録されています。登録しますよろしいですか?", mtConfirmation,
        				TMsgDlgButtons() << mbYes << mbNo, 0);
        		if(nRet == mrNo ) {
        		    return;
        		}
                else {
                	break;
                }
            }
        }

        // 新規登録行を決定します
        // 測定項目マスター順
        iRow = SGr_List->Row + 1;
        if( Rdo_List1_Order2->Checked ){
            // 測定項目名称順
			for( i = 1, iRow = 1; i < SGr_List->RowCount - 1; i++ ){
	            if( SGr_List->Cells[1][i] > Edt_SKTKMK_JPN->Text ){
                    break;
                }
	    	}
			iRow = i;
        } else if( Rdo_List1_Order3->Checked ){
            // 測定機器・測定項目名称順
			sBuf = Edt_SKTKMK_JPN->Text;
			for( i = 1, iRow = 1; i < SGr_List->RowCount - 1; i++ ){
	            if( SGr_List->Cells[15][i].ToIntDef(0) > iKIKI[Cmb_SKTKIKI->ItemIndex] ){
                    break;
				} else {
					if( SGr_List->Cells[15][i].ToIntDef(0) == iKIKI[Cmb_SKTKIKI->ItemIndex] &&
		                SGr_List->Cells[1][i].ToIntDef(0) > Edt_SKTKMK_JPN->Text ){
                    	break;
					}
                }
	    	}
			iRow = i;
        }
       	if( iRow >= SGr_List->RowCount ){
       		iRow--;
		}

        // 新規登録するデータの表示順を決定します
       	iORDER_NO = SGr_List->Cells[14][SGr_List->Row].ToIntDef(-1) + 1;
    	if( iORDER_NO <= 0 ){
        	iORDER_NO = SGr_List->Cells[14][SGr_List->RowCount-2].ToInt() + 1;
    	}

	    // 最大項目NOを+1します
        iSOKUT_KMK_NO_MAX++;
        iKMK_NO_MAX = iSOKUT_KMK_NO_MAX;
    }
    else {

        // 材料証明用項目
        for( i = 1; i < SGr_List2->RowCount; i++ ){
            sBuf = SGr_List2->Cells[1][i];
	    	if( Edt_SKTKMK_JPN->Text == sBuf ){
		        nRet = MessageDlg("既に同じ測定項目が登録されています。登録しますよろしいですか?", mtConfirmation,
        				TMsgDlgButtons() << mbYes << mbNo, 0);
        		if(nRet == mrNo ) {
        		    return;
        		}
                else {
                	break;
                }
            }
        }

        // 新規登録行を決定します
        // 測定項目マスター順
        iRow = SGr_List2->Row + 1;
        if( Rdo_List2_Order2->Checked ){
            // 測定項目名称順
			for( i = 1, iRow = 1; i < SGr_List2->RowCount - 1; i++ ){
	            if( SGr_List2->Cells[1][i] > Edt_SKTKMK_JPN->Text ){
                    break;
                }
	    	}
			iRow = i;
        } else if( Rdo_List2_Order3->Checked ){
            // 測定機器・測定項目名称順
			sBuf = Edt_SKTKMK_JPN->Text;
			for( i = 1, iRow = 1; i < SGr_List2->RowCount - 1; i++ ){
	            if( SGr_List2->Cells[15][i].ToIntDef(0) > iKIKI[Cmb_SKTKIKI->ItemIndex] ){
                    break;
				} else {
					if( SGr_List2->Cells[15][i].ToIntDef(0) == iKIKI[Cmb_SKTKIKI->ItemIndex] &&
		                SGr_List2->Cells[1][i].ToIntDef(0) > Edt_SKTKMK_JPN->Text ){
                    	break;
					}
                }
	    	}
			iRow = i;
        }
       	if( iRow >= SGr_List2->RowCount ){
       		iRow--;
		}

        // 新規登録するデータの表示順を決定します
       	iORDER_NO = SGr_List2->Cells[14][SGr_List2->Row].ToIntDef(-1) + 1;
    	if( iORDER_NO <= 0 ){
        	iORDER_NO = SGr_List2->Cells[14][SGr_List2->RowCount-2].ToInt() + 1;
    	}

	    // 最大項目NOを+1します
        iZAIRY_KMK_NO_MAX++;
        iKMK_NO_MAX = iZAIRY_KMK_NO_MAX;
    }

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "新規登録中です．．．しばらくお待ち下さい。";
    SBr1->Update();


    sBuf = IntToStr(iKMK_NO_MAX);
    strcpy( tmpKSM11_12_DATA.KOMK_NO		,sBuf.c_str() );	// 項目NO
    sBuf = IntToStr(iORDER_NO);
    strcpy( tmpKSM11_12_DATA.ORDER_NO		,sBuf.c_str() );	// 表示順
    sBuf = Edt_SKTKMK_JPN->Text;
    strcpy( tmpKSM11_12_DATA.KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
    sBuf = Edt_SKTKMK_ENG->Text;
    strcpy( tmpKSM11_12_DATA.KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
    sBuf = IntToStr(iKIKI[Cmb_SKTKIKI->ItemIndex]);
    strcpy( tmpKSM11_12_DATA.KIKI_NO		,sBuf.c_str() );	// 測定機器NO
    sBuf = Cmb_SKTKIKI->Text;
    strcpy( tmpKSM11_12_DATA.KIKI_NM		,sBuf.c_str() );	// 測定機器名称
    sBuf = Cmb_TANI->Text;
    strcpy( tmpKSM11_12_DATA.TANI			,sBuf.c_str() );	// 単位
    if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
    	sBuf = Nmb_KIKAKU_HANI_MIN->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// 規格値１
    	sBuf = Nmb_KIKAKU_HANI_MAX->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// 規格値２
    	sBuf = "0";
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// 規格値３
    	sBuf = "";
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// 規格値文字
    	sBuf = "1";
    } else if( Rdo_KIKAKU_SHITEI_KIJYUN->Checked ) {
    	sBuf = Nmb_KIKAKU_KIJYUN_MID->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// 規格値１
    	sBuf = Nmb_KIKAKU_KIJYUN_MAX->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// 規格値２
    	sBuf = Nmb_KIKAKU_KIJYUN_MIN->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// 規格値３
    	sBuf = "";
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// 規格値文字
    	sBuf = "2";
    } else {
    	sBuf = "0";
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// 規格値１
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// 規格値２
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// 規格値３
    	sBuf = Edt_KIKAKU_STRING->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// 規格値文字
    	sBuf = "3";
    }
    strcpy( tmpKSM11_12_DATA.KIKA_TYPE		,sBuf.c_str() );	// 規格タイプ
    if( Rdo_KIKAKU_SYURUI_MINMAX->Checked )			sBuf = "1";
    else if( Rdo_KIKAKU_SYURUI_MAX->Checked )		sBuf = "2";
    else											sBuf = "3";
    strcpy( tmpKSM11_12_DATA.KIKA_KIND		,sBuf.c_str() );	// 規格種類
    sBuf = Nmb_KIKAKU_DOUBLE->Text;
    strcpy( tmpKSM11_12_DATA.KIKA_DECI		,sBuf.c_str() );	// 規格小数点以下桁数
    sBuf = Nmb_N->Text;
    strcpy( tmpKSM11_12_DATA.SOKU_SU		,sBuf.c_str() );	// 測定指示n数
    if( Rdo_SKTKMK_ON->Checked )			sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
    if( Rdo_TKBKMK_ON->Checked )			sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
    if( Rdo_MANMIN_PRT_ON->Checked )		sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
    if( Rdo_VALUE_NORMAL->Checked )			sBuf = "0";
    else if( Rdo_VALUE_KAKUDO->Checked )	sBuf = "1";
    else if( Rdo_VALUE_OK->Checked )		sBuf = "2";
    else									sBuf = "3";
    strcpy( tmpKSM11_12_DATA.VALUE_TYPE		,sBuf.c_str() );	// 測定値の表現
    sBuf = Nmb_VALUE_DOUBLE->Text;
    strcpy( tmpKSM11_12_DATA.VALUE_DECI		,sBuf.c_str() );	// 測定値小数点以下桁数
    sBuf = FormatDateTime("yyyymmdd",Date());
    strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );		// 登録日
    strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );		// 変更日
    sBuf = FormatDateTime("hhmm",TDateTime::CurrentTime());
    strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );		// 登録時間
    strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );		// 変更時間
    sBuf = IntToStr(USER_COD);
    strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );		// 更新者（コード）
    sBuf = USER_NAM;
    strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );		// 更新者（名称）
    sBuf = "0";
    strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );		// 更新回数

    // 新規データの挿入＆新規データ行以下の行をずらします
    if( Rdo_TYPE_SYUKA->Checked ){

	    // データ新規登録処理
 		if( AddData("KSM11") == False )	return;

	    // 一行増やす
    	SGr_List->RowCount = SGr_List->RowCount + 1;
        // 行Noを付ける
		sBuf = IntToStr(SGr_List->RowCount-2);
		SGr_List->Cells[0][SGr_List->RowCount-2] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
	    // 最下行をクリアー
    	for( k = 0; k < SGr_List->ColCount; k++) {
			SGr_List->Cells[k][SGr_List->RowCount-1] = "";
    	}
        // 追加データの表示順より同じか大きい物を表示順＋１します
    	for( i = 1; i < SGr_List->RowCount - 1; i++) {
            if( SGr_List->Cells[14][i].ToIntDef(0) >= iORDER_NO ){
				SGr_List->Cells[14][i] = IntToStr(SGr_List->Cells[14][i].ToIntDef(0) + 1);
				SGr_List->Cells[29][i] = "1";		// 更新フラグもON
        	}
    	}

        // 新規データ行以下の行をずらします
    	for( i = SGr_List->RowCount - 2; i > iRow; i--) {
    		for( k = 1; k < SGr_List->ColCount; k++) {
				SGr_List->Cells[k][i] = SGr_List->Cells[k][i-1];
        	}
    	}

	    // データ件数を表示します
    	sBuf = SGr_List->RowCount-2;
    	LblListCnt->Caption = "件数：" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

	    //新規データをSGr_Listに表示
    	// グリッドにデータをセットします。
		GridLinePaste( SGr_List, iRow, "0");

	} else {

	    // データ新規登録処理
 		if( AddData("KSM12") == False )	return;

	    // 一行増やす
    	SGr_List2->RowCount = SGr_List2->RowCount + 1;
        // 行Noを付ける
		sBuf = IntToStr(SGr_List2->RowCount-2);
		SGr_List2->Cells[0][SGr_List2->RowCount-2] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
	    // 最下行をクリアー
    	for( k = 0; k < SGr_List2->ColCount; k++) {
			SGr_List2->Cells[k][SGr_List2->RowCount-1] = "";
    	}
        // 追加データの表示順より同じか大きい物を表示順＋１します
    	for( i = 1; i < SGr_List2->RowCount - 1; i++) {
            if( SGr_List2->Cells[14][i].ToIntDef(0) >= iORDER_NO ){
				SGr_List2->Cells[14][i] = IntToStr(SGr_List2->Cells[14][i].ToIntDef(0) + 1);
				SGr_List2->Cells[29][i] = "1";		// 更新フラグもON
        	}
    	}

        // 新規データ行以下の行をずらします
    	for( i = SGr_List2->RowCount - 2; i > iRow; i--) {
    		for( k = 1; k < SGr_List2->ColCount; k++) {
				SGr_List2->Cells[k][i] = SGr_List2->Cells[k][i-1];
        	}
    	}

	    // データ件数を表示します
    	sBuf = SGr_List2->RowCount-2;
    	LblListCnt2->Caption = "件数：" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

	    //新規データをSGr_Listに表示
    	// グリッドにデータをセットします。
		GridLinePaste( SGr_List2, iRow, "0");

    }


    // 修正ボタンから呼び出される場合がある（出荷検査項目と素材検査項目の入れ替え）ので
    // 呼び出し元ボタンを判定しています。
    if( btn->Name == "BtnF08" ){

    	// 登録項目にあわせてグリッドの表示を切り替えます
    	if( Rdo_TYPE_SYUKA->Checked ){
    		if( PgCtr_List->ActivePage->Name != "TabSheet1" ){
    			BtnF04Click(BtnF04);
    	    }
    		// 新しい行を選択
            SGr_List->Row = iRow;
    		SGr_List->SetFocus();
    		SGr_ListSelectCell(SGr_List,1,iRow,true);
    	} else {
    		if( PgCtr_List->ActivePage->Name != "TabSheet2" ){
    			BtnF04Click(BtnF04);
    	    }
    		// 新しい行を選択
            SGr_List2->Row = iRow;
    		SGr_List2->SetFocus();
    		SGr_ListSelectCell(SGr_List2,1,iRow,true);
    	}
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // データを変更したフラグ
    DataSave = true;

    // ボタンの初期化
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ９：修正」ボタンを押した時の処理
//
//  機能説明
//    StringGridで選択されたデータに対して画面下に入力された項目に更新します
//    テーブル（KSM11,KSM12）を更新します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{

    AnsiString sBuf;
    int i;
    int nRet;

    if( !BtnF09->Enabled )    return;

    if( PnlUPDYMD->Tag == -1){
    	MessageDlg("修正元がありません。データを選択してください。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    if( Rdo_TYPE_SYUKA->Checked && SGr_List->Cells[13][SGr_List->Row].ToIntDef(0) == 1){
        // ステータスメッセージ
    	MessageDlg("修正出来ない項目です。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    // 表示されているグリッドと修正する項目が違う場合、確認を行い処理します。
    if( Rdo_TYPE_SYUKA->Checked ){
    	if( PgCtr_List->ActivePage->Name != "TabSheet1" ){
        	nRet = MessageDlg("材料証明用項目が、出荷検査項目として修正されようとしています。よろしいですか?", mtConfirmation,
        			TMsgDlgButtons() << mbYes << mbNo, 0);
        	if(nRet == mrNo ) {
        	    return;
        	}

            // 出荷検査項目へ新規登録します
            BtnF08Click(BtnF09);

            // 材料証明書項目の選択項目を削除します
            BtnF10Click(BtnF09);

            // 選択タブの切替
			BtnF04Click(BtnF04);

            return;
        }
    } else {
    	if( PgCtr_List->ActivePage->Name != "TabSheet2" ){
        	nRet = MessageDlg("出荷検査項目が、材料証明用項目として修正されようとしています。よろしいですか?", mtConfirmation,
        			TMsgDlgButtons() << mbYes << mbNo, 0);
        	if(nRet == mrNo ) {
        	    return;
        	}

            // 材料証明書項目へ新規登録します
            BtnF08Click(BtnF09);

            // 出荷検査項目の選択項目を削除します
            BtnF10Click(BtnF09);

            // 選択タブの切替
			BtnF04Click(BtnF04);

            return;
        }
    }

    // 既に登録されている項目名をチェックします
    if( Rdo_TYPE_SYUKA->Checked == true ){

        // 出荷検査測定用項目
        for( i = 1; i < SGr_List->RowCount; i++ ){
            sBuf = SGr_List->Cells[1][i];
	    	if( Edt_SKTKMK_JPN->Text == sBuf && i != SGr_List->Row ){
		        nRet = MessageDlg("既に同じ測定項目が登録されています。登録しますよろしいですか?", mtConfirmation,
        				TMsgDlgButtons() << mbYes << mbNo, 0);
        		if(nRet == mrNo ) {
        		    return;
        		}
                else {
                	break;
                }
            }
        }
    }
    else {

        // 材料証明用項目
        for( i = 1; i < SGr_List2->RowCount; i++ ){
            sBuf = SGr_List2->Cells[1][i];
	    	if( Edt_SKTKMK_JPN->Text == sBuf && i != SGr_List2->Row ){
		        nRet = MessageDlg("既に同じ測定項目が登録されています。登録しますよろしいですか?", mtConfirmation,
        				TMsgDlgButtons() << mbYes << mbNo, 0);
        		if(nRet == mrNo ) {
        		    return;
        		}
                else {
                	break;
                }
            }
        }
    }

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "修正中です．．．しばらくお待ち下さい。";
    SBr1->Update();


    // データをバッファに格納します。
    sBuf = IntToStr(PnlUPDYMD->Tag);
    strcpy( tmpKSM11_12_DATA.KOMK_NO		,sBuf.c_str() );	// 項目NO
    sBuf = SGr_List->Cells[14][SGr_List->Row];
    strcpy( tmpKSM11_12_DATA.ORDER_NO		,sBuf.c_str() );	// 表示順
    sBuf = Edt_SKTKMK_JPN->Text;
    strcpy( tmpKSM11_12_DATA.KOMK_NM		,sBuf.c_str() );	// 測定項目名称（日本語）
    sBuf = Edt_SKTKMK_ENG->Text;
    strcpy( tmpKSM11_12_DATA.KOMK_ENG		,sBuf.c_str() );	// 測定項目名称（英語）
    sBuf = IntToStr(iKIKI[Cmb_SKTKIKI->ItemIndex]);
    strcpy( tmpKSM11_12_DATA.KIKI_NO		,sBuf.c_str() );	// 測定機器NO
    sBuf = Cmb_SKTKIKI->Text;
    strcpy( tmpKSM11_12_DATA.KIKI_NM		,sBuf.c_str() );	// 測定機器名称
    sBuf = Cmb_TANI->Text;
    strcpy( tmpKSM11_12_DATA.TANI			,sBuf.c_str() );	// 単位
    if( Rdo_KIKAKU_SHITEI_HANI->Checked ) {
    	sBuf = Nmb_KIKAKU_HANI_MIN->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// 規格値１
    	sBuf = Nmb_KIKAKU_HANI_MAX->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// 規格値２
    	sBuf = "0";
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// 規格値３
    	sBuf = "";
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// 規格値文字
    	sBuf = "1";
    } else if( Rdo_KIKAKU_SHITEI_KIJYUN->Checked ) {
    	sBuf = Nmb_KIKAKU_KIJYUN_MID->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// 規格値１
    	sBuf = Nmb_KIKAKU_KIJYUN_MAX->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// 規格値２
    	sBuf = Nmb_KIKAKU_KIJYUN_MIN->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// 規格値３
    	sBuf = "";
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// 規格値文字
    	sBuf = "2";
    } else {
    	sBuf = "0";
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	// 規格値１
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	// 規格値２
    	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	// 規格値３
    	sBuf = Edt_KIKAKU_STRING->Text;
    	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	// 規格値文字
    	sBuf = "3";
    }
    strcpy( tmpKSM11_12_DATA.KIKA_TYPE		,sBuf.c_str() );	// 規格タイプ
    if( Rdo_KIKAKU_SYURUI_MINMAX->Checked )			sBuf = "1";
    else if( Rdo_KIKAKU_SYURUI_MAX->Checked )		sBuf = "2";
    else											sBuf = "3";
    strcpy( tmpKSM11_12_DATA.KIKA_KIND		,sBuf.c_str() );	// 規格種類
    sBuf = Nmb_KIKAKU_DOUBLE->Text;
    strcpy( tmpKSM11_12_DATA.KIKA_DECI		,sBuf.c_str() );	// 規格小数点以下桁数
    sBuf = Nmb_N->Text;
    strcpy( tmpKSM11_12_DATA.SOKU_SU		,sBuf.c_str() );	// 測定指示n数
    if( Rdo_SKTKMK_ON->Checked )			sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.SOKU_FLG		,sBuf.c_str() );	// 測定項目の有無
    if( Rdo_TKBKMK_ON->Checked )			sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.TOKU_FLG		,sBuf.c_str() );	// 特別項目の有無
    if( Rdo_MANMIN_PRT_ON->Checked )		sBuf = "1";
    else									sBuf = "0";
    strcpy( tmpKSM11_12_DATA.KIKA_PRT		,sBuf.c_str() );	// 上限下限値の印刷
    if( Rdo_VALUE_NORMAL->Checked )			sBuf = "0";
    else if( Rdo_VALUE_KAKUDO->Checked )	sBuf = "1";
    else if( Rdo_VALUE_OK->Checked )		sBuf = "2";
    else									sBuf = "3";
    strcpy( tmpKSM11_12_DATA.VALUE_TYPE		,sBuf.c_str() );	// 測定値の表現
    sBuf = Nmb_VALUE_DOUBLE->Text;
    strcpy( tmpKSM11_12_DATA.VALUE_DECI		,sBuf.c_str() );	// 測定値小数点以下桁数
    sBuf = FormatDateTime("yyyymmdd",Date());
    //strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );		// 登録日
    strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );		// 変更日
    sBuf = FormatDateTime("hhmm",TDateTime::CurrentTime());
    //strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );		// 登録時間
    strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );		// 変更時間
    sBuf = IntToStr(USER_COD);
    strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );		// 更新者（コード）
    sBuf = USER_NAM;
    strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );		// 更新者（名称）
    sBuf = IntToStr(PnlUPDCHR->Tag + 1);
    strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );		// 更新回数

    // 修正データをSGr_Listに表示
    // グリッドにデータをセットします。
    if( Rdo_TYPE_SYUKA->Checked ){
		// データ修正
		if( UpdData("KSM11") == False )	return;

        sBuf = tmpKSM11_12_DATA.KOMK_NO;

        // 修正データをGridにセットします
		GridLinePaste( SGr_List, ROWPOINT, "");

        // 修正後のデータを選択します
        SGr_List->SetFocus();
   		SGr_ListSelectCell( SGr_List, 1, SGr_List->Row, true);
        if( Rdo_List1_Order1->Checked ){
	    	// 測定項目マスター順
        } else if( Rdo_List1_Order2->Checked ){
	    	// 測定項目名称順
        	Rdo_List1_OrderClick( Rdo_List1_Order2 );
	        for( i = 1; i < SGr_List->RowCount; i++ ){
				if( SGr_List->Cells[13][i] == sBuf ){
                    SGr_List->Row = i;
		    		SGr_ListSelectCell( SGr_List, 1, i, true);
					break;
                }
			}
        } else {
	    	// 測定機器・測定項目名称順
        	Rdo_List1_OrderClick( Rdo_List1_Order3 );
	        for( i = 1; i < SGr_List->RowCount; i++ ){
				if( SGr_List->Cells[13][i] == sBuf ){
                    SGr_List->Row = i;
		    		SGr_ListSelectCell( SGr_List, 1, i, true);
					break;
                }
			}
        }

	} else {
		// データ修正
		if( UpdData("KSM12") == False )	return;

        sBuf = tmpKSM11_12_DATA.KOMK_NO;

        // 修正データをGridにセットします
		GridLinePaste( SGr_List2, ROWPOINT, "");

        // 修正後のデータを選択します
    	SGr_List2->SetFocus();
    	SGr_ListSelectCell( SGr_List2, 1, SGr_List2->Row, true);
        if( Rdo_List2_Order1->Checked ){
	    	// 測定項目マスター順
        } else if( Rdo_List2_Order2->Checked ){
	    	// 測定項目名称順
        	Rdo_List2_OrderClick( Rdo_List2_Order2 );
	        for( i = 1; i < SGr_List2->RowCount; i++ ){
				if( SGr_List2->Cells[13][i] == sBuf ){
                    SGr_List2->Row = i;
		    		SGr_ListSelectCell( SGr_List2, 1, i, true);
					break;
                }
			}
        } else {
	    	// 測定機器・測定項目名称順
        	Rdo_List2_OrderClick( Rdo_List2_Order3 );
	        for( i = 1; i < SGr_List2->RowCount; i++ ){
				if( SGr_List2->Cells[13][i] == sBuf ){
                    SGr_List2->Row = i;
		    		SGr_ListSelectCell( SGr_List2, 1, i, true);
					break;
                }
			}
        }
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // データを変更したフラグ
    DataSave = true;

    // ボタンの初期化
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１０：削除」ボタンを押した時の処理
//
//  機能説明
//    StringGridで選択されたデータを削除します
//    テーブル（KSM11,KSM12）のレコードを削除します
//    StringGridの選択行も削除します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
    int			i, k;
    AnsiString	sBuf;

    TButton *btn = (TButton *)Sender;

    if( !BtnF10->Enabled )    return;

    if( Rdo_TYPE_SYUKA->Checked && SGr_List->Cells[13][SGr_List->Row].ToIntDef(0) == 1){
        // ステータスメッセージ
    	MessageDlg("削除出来ない項目です。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    if( PnlUPDYMD->Tag == -1){
        // ステータスメッセージ
    	MessageDlg("削除対象ではありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        return;
    }

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "削除中です．．．しばらくお待ち下さい。";
    SBr1->Update();

    // データをバッファに格納します。
    sBuf = IntToStr(PnlUPDYMD->Tag);
    strcpy( tmpKSM11_12_DATA.KOMK_NO		,sBuf.c_str() );		// 項目NO

    if( (btn->Name == "BtnF10" &&  Rdo_TYPE_SYUKA->Checked) ||
    	(btn->Name != "BtnF10" && !Rdo_TYPE_SYUKA->Checked) ){

    	// 選択したデータを削除します
    	if( DelData("KSM11") == False )	return;

        // 追加データの表示順より同じか大きい物を表示順－１します
    	for( i = 1; i < SGr_List->RowCount - 1; i++) {
            if( SGr_List->Cells[14][i].ToIntDef(0) >= SGr_List->Cells[14][SGr_List->Row].ToIntDef(0) ){
				SGr_List->Cells[14][i] = IntToStr(SGr_List->Cells[14][i].ToIntDef(-1) - 1);
				SGr_List->Cells[29][i] = "1";		// 更新フラグもON
        	}
    	}

        // 新規データ行以下の行をずらします
    	for( i = SGr_List->Row; i < (SGr_List->RowCount - 1); i++) {
    		for( k = 1; k < SGr_List->ColCount; k++) {
				SGr_List->Cells[k][i] = SGr_List->Cells[k][i+1];
        	}
    	}

    	// 一行減らす
    	SGr_List->RowCount = SGr_List->RowCount - 1;
   		// 最下行をクリアー
   		for( k = 0; k < SGr_List->ColCount; k++) {
			SGr_List->Cells[k][SGr_List->RowCount - 1] = "";
   		}

        // 修正ボタンから呼び出される場合がある（出荷検査項目と素材検査項目の入れ替え）ので
        // 呼び出し元ボタンを判定しています。
        if( btn->Name == "BtnF10" ){
    		// 新しい行を選択
    		if( SGr_List->RowCount == SGr_List->Row){
    		    SGr_List->Row = SGr_List->Row - 1;
    		}

    		// 新しい行を選択
    		SGr_List->SetFocus();
    		SGr_ListSelectCell(SGr_List,1,SGr_List->Row,true);
        }

	    // データ件数を表示します
    	sBuf = SGr_List->RowCount-2;
    	LblListCnt->Caption = "件数：" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

    } else {

    	// 選択したデータを削除します
    	if( DelData("KSM12") == False )	return;

        // 追加データの表示順より同じか大きい物を表示順－１します
    	for( i = 1; i < SGr_List2->RowCount - 1; i++) {
            if( SGr_List2->Cells[14][i].ToIntDef(0) >= SGr_List2->Cells[14][SGr_List2->Row].ToIntDef(0) ){
				SGr_List2->Cells[14][i] = IntToStr(SGr_List2->Cells[14][i].ToIntDef(-1) - 1);
				SGr_List2->Cells[29][i] = "1";		// 更新フラグもON
        	}
    	}

        // 新規データ行以下の行をずらします
    	for( i = SGr_List2->Row; i < (SGr_List2->RowCount - 1); i++) {
    		for( k = 1; k < SGr_List2->ColCount; k++) {
				SGr_List2->Cells[k][i] = SGr_List2->Cells[k][i+1];
        	}
    	}

    	// 一行減らす
    	SGr_List2->RowCount = SGr_List2->RowCount - 1;
   		// 最下行をクリアー
   		for( k = 0; k < SGr_List2->ColCount; k++) {
			SGr_List2->Cells[k][SGr_List2->RowCount - 1] = "";
   		}

        // 修正ボタンから呼び出される場合がある（出荷検査項目と素材検査項目の入れ替え）ので
        // 呼び出し元ボタンを判定しています。
        if( btn->Name == "BtnF10" ){
    		// 新しい行を選択
    		if( SGr_List2->RowCount == SGr_List2->Row){
    		    SGr_List2->Row = SGr_List2->Row - 1;
    		}

    		// 新しい行を選択
    		SGr_List2->SetFocus();
    		SGr_ListSelectCell(SGr_List2,1,SGr_List2->Row,true);
        }

	    // データ件数を表示します
    	sBuf = SGr_List2->RowCount-2;
    	LblListCnt2->Caption = "件数：" + AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // データを変更したフラグ
    DataSave = true;

    // ボタンの初期化
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１１：保存」ボタンを押した時の処理
//
//  機能説明
//    更新の有ったデータを確定（Commit）します
//    表示順が変更された項目も更新しなおします
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{
    int		i;

    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "保存中です．．．しばらくお待ち下さい。";
    SBr1->Update();

    // 変更，挿入，削除を永続的に保存し，現在のトランザクションを終了
    if( Database1->InTransaction == True ){
        Database1->Commit();

    	// 並び替えられた表示順を保存します。
    	for( i = 1; i < SGr_List->RowCount; i++) {
    		if( SGr_List->Cells[29][i] == "1" ){
                UpdData_ORDER_NO( "KSM11", SGr_List->Cells[13][i],SGr_List->Cells[14][i]);
        	}
    	}

    	// 並び替えられた表示順を保存します。
    	for( i = 1; i < SGr_List2->RowCount; i++) {
    		if( SGr_List2->Cells[29][i] == "1" ){
                UpdData_ORDER_NO( "KSM12", SGr_List2->Cells[13][i],SGr_List2->Cells[14][i]);
        	}
    	}

        // 新しいトランザクションを開始
        Database1->StartTransaction();
    }

    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

    // データを変更したフラグ
    DataSave = false;
    BtnF11->Enabled = false;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「Ｆ１２：終了」ボタンを押した時の処理
//
//  機能説明
//    更新されているかどうか確認し、
//    更新されている場合は「Ｆ１１：保存」を呼び出し
//    メインフォームのCloseをコールします
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
     int nRet;
     if( DataSave == true )
     {
         nRet = MessageDlg("編集されています。保存しますか?", mtConfirmation,
                TMsgDlgButtons() << mbYes << mbCancel << mbNo, 0);
         if(nRet == mrYes )
         {
              BtnF11Click(Sender);
              Close();
         }
         else if(nRet == mrCancel)
         {
         }
         else
         {
              DataSave = false;
              Close();
         }
     }
     else
     {
         Close();
     }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnDrawCellイベント：グリッド内のセルを描画する必要があるときに発生します。
//
//  機能説明
//    グリッド内のセル描画をコントロールします
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol			：選択する列の位置
//    int ARow			：選択する行の位置
//    TRect &Rect		：描画セルの左上隅と右下隅の座標
//    TGridDrawState State：描画セルの状態
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_ListDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{

   AnsiString	sBuf, sValue;
   char 		cFormatBuf[20], c1[20], c2[10];
   long			iPos;

   TStringGrid *sg = (TStringGrid *)Sender;

   RECT r=RECT(Rect);

   //固定セルの背景色をセット
   if(State.Contains(gdFixed))
       sg->Canvas->Brush->Color= sg->FixedColor;
   //フォーカスのあるセルの背景色をセット
   //else if(State.Contains(gdFocused)){
   //選択されているセルの背景色をセット
   else if(State.Contains(gdSelected))
       sg->Canvas->Brush->Color= clHighlight;
   //普通のセルの背景色をセット
   else
       sg->Canvas->Brush->Color= sg->Color;

   //背景色で消去
   sg->Canvas->FillRect(Rect);

   //固定セルの立体枠を描く
   if(sg->Ctl3D&&State.Contains(gdFixed))
       DrawEdge(sg->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);

   //フォーカスのあるセルの文字色をセット
   if(State.Contains(gdFocused)){
//       SGr1->Canvas->Font->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlightText: SGr1->Font->Color;
//       //フォーカス枠を描く
//       DrawFocusRect(SGr1->Canvas->Handle,&r);
	   //選択されているセルの文字色をセット
       //if(State.Contains(gdSelected))

       //修正・削除不可能データの場合の文字色をセット
       if( sg->Name == "SGr_List" && ACol > 0 && SGr_List->Cells[13][ARow].ToIntDef(0) == 1 )
           sg->Canvas->Font->Color = clRed;
       else
           sg->Canvas->Font->Color= clHighlightText;
   }
   //選択されているセルの文字色をセット
   else if(State.Contains(gdSelected))
       if( sg->Name == "SGr_List" && ACol > 0 && SGr_List->Cells[13][ARow].ToIntDef(0) == 1 )
           sg->Canvas->Font->Color = clRed;
       else
           sg->Canvas->Font->Color= clHighlightText;
   //修正・削除不可能データの場合の文字色をセット
   else if( sg->Name == "SGr_List" && ACol > 0 && sg->Cells[13][ARow].ToIntDef(0) == 1 )
       sg->Canvas->Font->Color = clRed;
   //普通のセルの文字色をセット
   else
       sg->Canvas->Font->Color= sg->Font->Color;

   //テキスト表示領域の設定
   InflateRect(&r,-2,-2);

   if( ARow > 0 && ACol == 5 ){

        // 規格タイプ毎の表示
        switch( sg->Cells[16][ARow].ToIntDef(0) ){
            case 1: // 範囲指定

                    // 小数点以下桁数のフォーマット文字列
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",sg->Cells[18][ARow].ToIntDef(0) );
            		strcat(c1,c2);

			        switch( sg->Cells[17][ARow].ToIntDef(0) ){
            			case 1: // 上限下限両方
                                sValue = sg->Cells[19][ARow];
			                    sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf = cFormatBuf;
                     			sBuf +=  "～";
                                sValue = sg->Cells[20][ARow];
                     			sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf += cFormatBuf ;
			            		break;

            			case 2: // 上限のみ
                                sValue = sg->Cells[20][ARow];
                     			sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf = cFormatBuf ;
                     			sBuf += "以下";
			            		break;
            			case 3: // 下限のみ
                                sValue = sg->Cells[19][ARow];
                     			sprintf(cFormatBuf, c1, sValue.ToDouble() );
                     			sBuf = cFormatBuf ;
                     			sBuf += "以上";
			            		break;
                    }
					DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
            		break;

            case 2: // 基準値指定

                    // 小数点以下桁数のフォーマット文字列
            		sprintf(c1,"%0");
            		sprintf(c2,"1.%df",sg->Cells[18][ARow].ToIntDef(0) );
            		strcat(c1,c2);

                    sValue = sg->Cells[19][ARow];
                    sprintf(cFormatBuf, c1, sValue.ToDouble() );
                    sBuf = cFormatBuf ;
        			sg->Canvas->TextOut( r.left +  0, r.top + 0, sBuf );
                    iPos = sBuf.Length() * 8;

        			// フォント（小）の設定
        			OrgFont = SelectObject( sg->Canvas->Handle, MyFont );

			        switch( sg->Cells[17][ARow].ToIntDef(0) ){
            			case 1: // 上限下限両方
                    			sValue = sg->Cells[20][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
                                sg->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
                     			sValue = sg->Cells[21][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						sg->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;

            			case 2: // 上限のみ
			                    sValue = sg->Cells[20][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
			        			sg->Canvas->TextOut( r.left + iPos, r.top - 2, sBuf );
			            		break;
            			case 3: // 下限のみ
                     			sValue = sg->Cells[21][ARow];
                    			sprintf(cFormatBuf, c1, sValue.ToDouble() );
			                    sBuf = cFormatBuf ;
                                if( sBuf.SubString(1,1) != "-" ) sBuf.Insert("+",1);
        						sg->Canvas->TextOut( r.left + iPos, r.top + 7, sBuf );
			            		break;
                    }

        			// 元のフォントに戻します
        			SelectObject( sg->Canvas->Handle, OrgFont );

                    break;

        	case 3: // 文字
					DrawText(sg->Canvas->Handle,sg->Cells[22][ARow].c_str(),-1,&r,0); //左寄せ
                    break;
        }

   } else if( ARow > 0 && ACol == 6 ){
        // ｎ数
		DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //右寄せ

   } else if( ARow > 0 && ACol == 7 ){
        // 値表現
        switch( sg->Cells[ACol][ARow].ToIntDef(-1) ){
   			case 0: // 整数・小数(99.99)
                    if( sg->Cells[24][ARow].ToIntDef(0) > 0 ){
                    	sBuf = "9." + AnsiString::StringOfChar('9', sg->Cells[24][ARow].ToIntDef(0));
            		} else{
                    	sBuf = "9";
                    }
                    DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
            		break;
   			case 1: // 角度(99゜99')
                    if( sg->Cells[24][ARow].ToIntDef(0) > 0 ){
	                    sBuf = "9°" + AnsiString::StringOfChar('9', sg->Cells[24][ARow].ToIntDef(0)) + "'";
            		} else{
                    	sBuf = "9°";
                    }
            		DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
            		break;
   			case 2: // 良(OK)／否(NG)
            		DrawText(sg->Canvas->Handle,"良/否",-1,&r,0); //左寄せ
            		break;
   			case 3: // 文字
            		DrawText(sg->Canvas->Handle,"文字",-1,&r,0); //左寄せ
            		break;
       	}

   } else if( ARow > 0 && (ACol == 8 || ACol == 9) ){
        // 測定項目の有無、特別項目の有無
        switch( sg->Cells[ACol][ARow].ToIntDef(-1) ){
   			case 0: DrawText(sg->Canvas->Handle,"無",-1,&r,0); //左寄せ
            		break;
   			case 1: DrawText(sg->Canvas->Handle,"有",-1,&r,0); //左寄せ
            		break;
       	}

   } else if( ARow > 0 && ACol == 10 ){
        // 更新日
        sBuf = sg->Cells[10][ARow];
        if( sBuf.Length() == 8 ){
        	sBuf.Insert("/",5);
       		sBuf.Insert("/",8);
   			DrawText(sg->Canvas->Handle,sBuf.c_str(),-1,&r,0); //左寄せ
        }

   } else{
		//テキストの表示
		DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,0); //左寄せ
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_RIGHT); //右寄せ
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER); //中央寄せ（水平）
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_VCENTER|DT_SINGLELINE); //中央寄せ（垂直）
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_BOTTOM|DT_SINGLELINE); //下寄せ
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE); //水平･垂直とも中央寄せ
		//DrawText(sg->Canvas->Handle,sg->Cells[ACol][ARow].c_str(),-1,&r,DT_WORDBREAK); //複数行表示
   }

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：データを追加します。
//
//  機能説明
//    「Ｆ８：新規登録」時のデータ追加（KSM11,KSM12）処理
//
//  パラメタ説明
//    AnsiString sTBL_NM：保存先のテーブル名（KSM11,KSM12のどちらか）
//
//  戻り値
//    bool				：true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::AddData(AnsiString sTBL_NM)
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf = "insert into " + sTBL_NM + "(";
    sBuf += " KOMK_NO, ORDER_NO, KOMK_NM, KOMK_ENG, KOMK_SUB, KOMK_SUB_ENG, KIKI_NO, KIKI_NM, TANI,";
    sBuf += " KIKA_TYPE, KIKA_KIND, KIKA_DECI, KIKA_NUM1, KIKA_NUM2, KIKA_NUM3, KIKA_STR,";
    sBuf += " SOKU_SU, SOKU_FLG, TOKU_FLG, KIKA_PRT, VALUE_TYPE, VALUE_DECI,";
    sBuf += " ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT )";

    sBuf += " VALUES(";
	sBuf += AnsiString(tmpKSM11_12_DATA.KOMK_NO)	+  "," ;	// 項目NO
	sBuf += AnsiString(tmpKSM11_12_DATA.ORDER_NO)	+  ",'";	// 表示順
	sBuf += AnsiString(tmpKSM11_12_DATA.KOMK_NM)	+ "','";	// 測定項目名称（日本語）
	sBuf += AnsiString(tmpKSM11_12_DATA.KOMK_ENG)	+ "','";	// 測定項目名称（英語）
	sBuf += 										  "','";	// 測定項目サブ名称（日本語）
	sBuf += 										  "'," ;	// 測定項目サブ名称（英語）
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKI_NO)	+  ",'";	// 測定機器NO
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKI_NM)	+ "','";	// 測定機器名称
	sBuf += AnsiString(tmpKSM11_12_DATA.TANI)		+ "'," ;	// 単位
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_TYPE)	+  "," ;	// 規格タイプ
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_KIND)	+  "," ;	// 規格種類
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_DECI)	+  "," ;	// 規格小数点以下桁数
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_NUM1)	+  "," ;	// 規格値１
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_NUM2)	+  "," ;	// 規格値２
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_NUM3)	+  ",'";	// 規格値３
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_STR)	+ "'," ;	// 規格値文字
	sBuf += AnsiString(tmpKSM11_12_DATA.SOKU_SU)	+  "," ;	// 測定指示n数
	sBuf += AnsiString(tmpKSM11_12_DATA.SOKU_FLG)	+  "," ;	// 測定項目の有無
	sBuf += AnsiString(tmpKSM11_12_DATA.TOKU_FLG)	+  "," ;	// 特別項目の有無
	sBuf += AnsiString(tmpKSM11_12_DATA.KIKA_PRT)	+  "," ;	// 上限下限値の印刷
	sBuf += AnsiString(tmpKSM11_12_DATA.VALUE_TYPE)	+  "," ;	// 測定値表現
	sBuf += AnsiString(tmpKSM11_12_DATA.VALUE_DECI)	+  ",'";	// 測定値小数点以下桁数
	sBuf += AnsiString(tmpKSM11_12_DATA.ADDYMD)		+ "','";	// 登録日
	sBuf += AnsiString(tmpKSM11_12_DATA.ADDTIM)		+ "','";	// 登録時間
	sBuf += AnsiString(tmpKSM11_12_DATA.UPDYMD)		+ "','";	// 変更日
	sBuf += AnsiString(tmpKSM11_12_DATA.UPDTIM)		+ "'," ;	// 変更時間
	sBuf += AnsiString(tmpKSM11_12_DATA.UPDCHR)		+  "," ;	// 更新者
	sBuf += AnsiString(tmpKSM11_12_DATA.UPDCNT)		+  ")" ;	// 更新回数

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }

    return(True);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：データを修正します。
//
//  機能説明
//    「Ｆ９：修正」時のデータ更新（KSM21）処理
//
//  パラメタ説明
//    AnsiString sTBL_NM：保存先のテーブル名（KSM11,KSM12のどちらか）
//
//  戻り値
//    bool				：true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::UpdData(AnsiString sTBL_NM)
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf  = "update " + sTBL_NM + " set";
	sBuf += " KOMK_NM='"	+ AnsiString(tmpKSM11_12_DATA.KOMK_NM)		+ "',";	// 測定項目名称（日本語）
	sBuf += " KOMK_ENG='"	+ AnsiString(tmpKSM11_12_DATA.KOMK_ENG)		+ "',";	// 測定項目名称（英語）
	sBuf += " KOMK_SUB='',"		;												// 測定項目サブ名称（日本語）
	sBuf += " KOMK_SUB_ENG='',"	;												// 測定項目サブ名称（英語）
	sBuf += " KIKI_NO="		+ AnsiString(tmpKSM11_12_DATA.KIKI_NO)		+  ",";	// 測定機器NO
	sBuf += " KIKI_NM='"	+ AnsiString(tmpKSM11_12_DATA.KIKI_NM)		+ "',";	// 測定機器名称
	sBuf += " TANI='"		+ AnsiString(tmpKSM11_12_DATA.TANI)			+ "',";	// 単位
	sBuf += " KIKA_TYPE="	+ AnsiString(tmpKSM11_12_DATA.KIKA_TYPE)	+  ",";	// 規格タイプ
	sBuf += " KIKA_KIND="	+ AnsiString(tmpKSM11_12_DATA.KIKA_KIND)	+  ",";	// 規格種類
	sBuf += " KIKA_DECI="	+ AnsiString(tmpKSM11_12_DATA.KIKA_DECI)	+  ",";	// 規格小数点以下桁数
	sBuf += " KIKA_NUM1="	+ AnsiString(tmpKSM11_12_DATA.KIKA_NUM1)	+  ",";	// 規格値１
	sBuf += " KIKA_NUM2="	+ AnsiString(tmpKSM11_12_DATA.KIKA_NUM2)	+  ",";	// 規格値２
	sBuf += " KIKA_NUM3="	+ AnsiString(tmpKSM11_12_DATA.KIKA_NUM3)	+  ",";	// 規格値３
	sBuf += " KIKA_STR='"	+ AnsiString(tmpKSM11_12_DATA.KIKA_STR)		+ "',";	// 規格値文字
	sBuf += " SOKU_SU="		+ AnsiString(tmpKSM11_12_DATA.SOKU_SU)		+  ",";	// 測定指示n数
	sBuf += " SOKU_FLG="	+ AnsiString(tmpKSM11_12_DATA.SOKU_FLG)		+  ",";	// 測定項目の有無
	sBuf += " TOKU_FLG="	+ AnsiString(tmpKSM11_12_DATA.TOKU_FLG)		+  ",";	// 特別項目の有無
	sBuf += " KIKA_PRT="	+ AnsiString(tmpKSM11_12_DATA.KIKA_PRT)		+  ",";	// 上限下限値の印刷
	sBuf += " VALUE_TYPE="	+ AnsiString(tmpKSM11_12_DATA.VALUE_TYPE)	+  ",";	// 測定値表現
	sBuf += " VALUE_DECI="	+ AnsiString(tmpKSM11_12_DATA.VALUE_DECI)	+  ",";	// 測定値小数点以下桁数
	sBuf += " UPDYMD='"		+ AnsiString(tmpKSM11_12_DATA.UPDYMD)		+ "',";	// 変更日
	sBuf += " UPDTIM='"		+ AnsiString(tmpKSM11_12_DATA.UPDTIM)		+ "',";	// 変更時間
	sBuf += " UPDCHR="		+ AnsiString(tmpKSM11_12_DATA.UPDCHR)		+  ",";	// 更新者
	sBuf += " UPDCNT="		+ AnsiString(tmpKSM11_12_DATA.UPDCNT)			  ;	// 更新回数
    sBuf += " WHERE KOMK_NO="+ AnsiString(tmpKSM11_12_DATA.KOMK_NO)			  ; // 項目NO

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }

    return(True);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：データを修正します。（表示順のみ）
//
//  機能説明
//    「Ｆ１１：保存」時の表示順更新（KSM21）処理
//
//  パラメタ説明
//    AnsiString sTBL_NM：保存先のテーブル名（KSM11,KSM12のどちらか）
//    AnsiString sKMK_NO：修正対象の項目NO
//    AnsiString sORDER_NO：新しい表示順NO
//
//  戻り値
//    bool				：true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::UpdData_ORDER_NO(AnsiString sTBL_NM, AnsiString sKMK_NO, AnsiString sORDER_NO)
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf  = "update " + sTBL_NM + " set";
    sBuf += " ORDER_NO="		+ Trim(sORDER_NO)	  ;	//表示順
    sBuf += " WHERE KOMK_NO="	+ Trim(sKMK_NO)		  ; //項目NO

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }

    return(True);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：データを削除します。
//
//  機能説明
//    「Ｆ１０：削除」時のデータ削除（KSM21）処理
//
//  パラメタ説明
//    AnsiString sTBL_NM：保存先のテーブル名（KSM11,KSM12のどちらか）
//
//  戻り値
//    bool				：true = 成功、false = 失敗
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
bool __fastcall TForm1::DelData(AnsiString sTBL_NM)
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf = "select * from " + sTBL_NM;
    sBuf += " WHERE KOMK_NO="+ AnsiString(tmpKSM11_12_DATA.KOMK_NO)  ; //項目NO

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try {
        Query1->Open();
        Query1->Active = true;
        if( Query1->Eof == True &&  Query1->Bof == True ) {
            SBr1->Panels->Items[0]->Text = "該当のデータが見つかりません。削除できませんでした。";
            SBr1->Update();
            return(False);
        }
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ文作成
    sBuf = "DELETE from " + sTBL_NM;
    sBuf += " WHERE KOMK_NO="+ AnsiString(tmpKSM11_12_DATA.KOMK_NO)		  ; //項目NO

    Query1->SQL->Add(sBuf);

    // 問い合せ文の実行
    try {
        Query1->ExecSQL();
    }
    catch(EDatabaseError& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    catch(Exception& e) {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        return(False);
    }
    return(True);

}

//---------------------------------------------------------------------------
//
//  概要
//    OnResizeイベント	：コントロールのサイズが変更された直後に発生します。
//
//  機能説明
//    Panelのサイズに合わせてStringGridのサイズも変更します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Pnl_ListResize(TObject *Sender)
{
    int iBMarg;

    // 親ラベルから見た各コントロールの下端余白
    iBMarg = 6;


    // 検索リスト
	if( PgCtr_List->Top < Pnl_List->Height &&
        Pnl_List->Height - PgCtr_List->Top - iBMarg > 0 ){
		PgCtr_List->Height = Pnl_List->Height - PgCtr_List->Top - iBMarg;
	} else{
		PgCtr_List->Height = 0;
	}

}

//---------------------------------------------------------------------------
//
//  概要
//    OnKeyPressイベント：StringGridでキーを押したときに発生します。
//
//  機能説明
//    矢印キーによりボタンを選択します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    char &Key			：キーコード
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_ListKeyPress(TObject *Sender, char &Key)
{
     switch(Key)
     {
         // 前項
         case VK_UP:
         case VK_LEFT:  BtnF02Click(Sender);    break;

         // 次項
         case VK_DOWN:
         case VK_RIGHT: BtnF03Click(Sender);    break;

     }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「上へ移動」ボタンを押した時の処理
//
//  機能説明
//    StringGridで選択された行を1つ上の行と入れ替えます。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Btn_UpClick(TObject *Sender)
{
    int			i, k;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;
    TStringGrid *sg;

	TBitBtn		*btn = (TBitBtn *)Sender;
    if( btn->Name == "Btn_UP1" ){
	    sg = dynamic_cast<TStringGrid*>(SGr_List);
    } else {
	    sg = dynamic_cast<TStringGrid*>(SGr_List2);
    }

    iChgRow1 = sg->Selection.Top;
    iChgRow2 = sg->Selection.Top - 1;
    iChgRow3 = sg->Selection.Bottom;

    if( iChgRow1 <= 1) return;
    if( iChgRow1 >= sg->RowCount - 1) return;

    if( iChgRow3 >= sg->RowCount - 1)
    	iChgRow3 = sg->Selection.Bottom = sg->RowCount - 2;

    // ※表示順Cells[14]は入れ替えせずにその他の項目を入れ替え、更新フラグ(Cells[29])をONにします。

    // 入れ替え先のデータをバックアップ
	sBuf = sg->Cells[1][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_NM	,sBuf.c_str() );	//測定項目（日本語）
	sBuf = sg->Cells[2][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_ENG	,sBuf.c_str() );	//測定項目（英語）
	sBuf = sg->Cells[3][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKI_NM	,sBuf.c_str() );	//測定機器名称
	sBuf = sg->Cells[4][iChgRow2];
    strcpy( tmpKSM11_12_DATA.TANI		,sBuf.c_str() );	//単位
	sBuf = sg->Cells[6][iChgRow2];
    strcpy( tmpKSM11_12_DATA.SOKU_SU	,sBuf.c_str() );	//ｎ数（基本）
	sBuf = sg->Cells[7][iChgRow2];
    strcpy( tmpKSM11_12_DATA.VALUE_TYPE	,sBuf.c_str() );	//値表現
	sBuf = sg->Cells[8][iChgRow2];
    strcpy( tmpKSM11_12_DATA.SOKU_FLG	,sBuf.c_str() );	//測定項目の有無
	sBuf = sg->Cells[9][iChgRow2];
    strcpy( tmpKSM11_12_DATA.TOKU_FLG	,sBuf.c_str() );	//特別項目の有無
	sBuf = sg->Cells[10][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );	//変更日
	sBuf = sg->Cells[12][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );	//更新者（担当者コード）
	sBuf = sg->Cells[11][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );	//更新者（名称）
	sBuf = sg->Cells[13][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_NO	,sBuf.c_str() );	//項目NO
	sBuf = sg->Cells[15][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKI_NO	,sBuf.c_str() );	//測定機器NO
	sBuf = sg->Cells[16][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_TYPE	,sBuf.c_str() );	//規格タイプ
	sBuf = sg->Cells[17][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_KIND	,sBuf.c_str() );	//規格種類
	sBuf = sg->Cells[18][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_DECI	,sBuf.c_str() );	//規格小数点以下桁数
	sBuf = sg->Cells[19][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	//規格値１
	sBuf = sg->Cells[20][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	//規格値２
	sBuf = sg->Cells[21][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	//規格値３
	sBuf = sg->Cells[22][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	//規格文字
	sBuf = sg->Cells[23][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_PRT	,sBuf.c_str() );	//上限下限値の印刷
	sBuf = sg->Cells[24][iChgRow2];
    strcpy( tmpKSM11_12_DATA.VALUE_DECI	,sBuf.c_str() );	//測定値小数点以下桁数
	sBuf = sg->Cells[25][iChgRow2];
    strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );	//登録日
	sBuf = sg->Cells[26][iChgRow2];
    strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );	//登録時間
	sBuf = sg->Cells[27][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );	//更新時間
	sBuf = sg->Cells[28][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );	//更新回数

	// 上下を入れ替えます
    for( i = iChgRow2; i < iChgRow3; i++ ) {
    	for( k = 1; k < sg->ColCount; k++ ) {
            if( k == 14 ){
                // 表示順は、入れ替えしない
    			// sg->Cells[k][i] = sg->Cells[k][i + 1];
            } else if( k == 29 ){
                // 更新フラグの設定
				sg->Cells[k][i] = "1";
        	} else {
				sg->Cells[k][i] = sg->Cells[k][i + 1];
            }
		}
    }

    // バックアップしたデータを戻します
	sg->Cells[1][iChgRow3] = tmpKSM11_12_DATA.KOMK_NM	;	//測定項目（日本語）
	sg->Cells[2][iChgRow3] = tmpKSM11_12_DATA.KOMK_ENG	;	//測定項目（英語）
	sg->Cells[3][iChgRow3] = tmpKSM11_12_DATA.KIKI_NM	;	//測定機器名称
	sg->Cells[4][iChgRow3] = tmpKSM11_12_DATA.TANI		;	//単位
	sg->Cells[5][iChgRow3] = ""							;	//規格（基本）　※再描画する為に必要です。
	sg->Cells[6][iChgRow3] = tmpKSM11_12_DATA.SOKU_SU	;	//ｎ数（基本）
	sg->Cells[7][iChgRow3] = tmpKSM11_12_DATA.VALUE_TYPE;	//値表現
	sg->Cells[8][iChgRow3] = tmpKSM11_12_DATA.SOKU_FLG	;	//測定項目の有無
	sg->Cells[9][iChgRow3] = tmpKSM11_12_DATA.TOKU_FLG	;	//特別項目の有無
	sg->Cells[10][iChgRow3] = tmpKSM11_12_DATA.UPDYMD	;	//変更日
	sg->Cells[11][iChgRow3] = tmpKSM11_12_DATA.UPDNAM	;	//更新者（名称）
	sg->Cells[12][iChgRow3] = tmpKSM11_12_DATA.UPDCHR	;	//更新者（担当者コード）
	sg->Cells[13][iChgRow3] = tmpKSM11_12_DATA.KOMK_NO	;	//項目NO
	sg->Cells[15][iChgRow3] = tmpKSM11_12_DATA.KIKI_NO	;	//測定機器NO
	sg->Cells[16][iChgRow3] = tmpKSM11_12_DATA.KIKA_TYPE;	//規格タイプ
	sg->Cells[17][iChgRow3] = tmpKSM11_12_DATA.KIKA_KIND;	//規格種類
	sg->Cells[18][iChgRow3] = tmpKSM11_12_DATA.KIKA_DECI;	//規格小数点以下桁数
	sg->Cells[19][iChgRow3] = tmpKSM11_12_DATA.KIKA_NUM1;	//規格値１
	sg->Cells[20][iChgRow3] = tmpKSM11_12_DATA.KIKA_NUM2;	//規格値２
	sg->Cells[21][iChgRow3] = tmpKSM11_12_DATA.KIKA_NUM3;	//規格値３
	sg->Cells[22][iChgRow3] = tmpKSM11_12_DATA.KIKA_STR	;	//規格文字
	sg->Cells[23][iChgRow3] = tmpKSM11_12_DATA.KIKA_PRT	;	//上限下限値の印刷
	sg->Cells[24][iChgRow3] = tmpKSM11_12_DATA.VALUE_DECI;	//測定値小数点以下桁数
	sg->Cells[25][iChgRow3] = tmpKSM11_12_DATA.ADDYMD	;	//登録日
	sg->Cells[26][iChgRow3] = tmpKSM11_12_DATA.ADDTIM	;	//登録時間
	sg->Cells[27][iChgRow3] = tmpKSM11_12_DATA.UPDTIM	;	//更新時間
	sg->Cells[28][iChgRow3] = tmpKSM11_12_DATA.UPDCNT	;	//更新回数
	sg->Cells[29][iChgRow3] = "1"						;	//更新フラグの設定

    // 選択カーソルも同時に上に移動します
    sg->Row--;
	myRect.Left		= sg->Selection.Left;
	myRect.Top		= iChgRow1 - 1;
	myRect.Right	= sg->Selection.Right;
	myRect.Bottom	= iChgRow3 - 1;
    sg->Selection	= myRect;
    SGr_ListSelectCell(sg,1,sg->Row,true);

    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：「下へ移動」ボタンを押した時の処理
//
//  機能説明
//    StringGridで選択された行を1つ下の行と入れ替えます。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Btn_DownClick(TObject *Sender)
{
    int			i, k;
	int			iChgRow1;
	int			iChgRow2;
	int			iChgRow3;
	TGridRect	myRect;
    AnsiString	sBuf;
    TStringGrid *sg;

	TBitBtn		*btn = (TBitBtn *)Sender;
    if( btn->Name == "Btn_DOWN1" ){
	    sg = dynamic_cast<TStringGrid*>(SGr_List);
    } else {
	    sg = dynamic_cast<TStringGrid*>(SGr_List2);
    }

    iChgRow1 = sg->Selection.Top;
    iChgRow2 = sg->Selection.Bottom + 1;
    iChgRow3 = sg->Selection.Bottom;

    if( iChgRow2 >= sg->RowCount - 1) return;

    // ※表示順は入れ替えせずにその他の項目を入れ替え、更新フラグ(Cells[14])をONにします。

    // ※表示順Cells[14]は入れ替えせずにその他の項目を入れ替え、更新フラグ(Cells[29])をONにします。

    // 入れ替え先のデータをバックアップ
	sBuf = sg->Cells[1][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_NM	,sBuf.c_str() );	//測定項目（日本語）
	sBuf = sg->Cells[2][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_ENG	,sBuf.c_str() );	//測定項目（英語）
	sBuf = sg->Cells[3][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKI_NM	,sBuf.c_str() );	//測定機器名称
	sBuf = sg->Cells[4][iChgRow2];
    strcpy( tmpKSM11_12_DATA.TANI		,sBuf.c_str() );	//単位
	sBuf = sg->Cells[6][iChgRow2];
    strcpy( tmpKSM11_12_DATA.SOKU_SU	,sBuf.c_str() );	//ｎ数（基本）
	sBuf = sg->Cells[7][iChgRow2];
    strcpy( tmpKSM11_12_DATA.VALUE_TYPE	,sBuf.c_str() );	//値表現
	sBuf = sg->Cells[8][iChgRow2];
    strcpy( tmpKSM11_12_DATA.SOKU_FLG	,sBuf.c_str() );	//測定項目の有無
	sBuf = sg->Cells[9][iChgRow2];
    strcpy( tmpKSM11_12_DATA.TOKU_FLG	,sBuf.c_str() );	//特別項目の有無
	sBuf = sg->Cells[10][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );	//変更日
	sBuf = sg->Cells[12][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );	//更新者（担当者コード）
	sBuf = sg->Cells[11][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );	//更新者（名称）
	sBuf = sg->Cells[13][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KOMK_NO	,sBuf.c_str() );	//項目NO
	sBuf = sg->Cells[15][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKI_NO	,sBuf.c_str() );	//測定機器NO
	sBuf = sg->Cells[16][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_TYPE	,sBuf.c_str() );	//規格タイプ
	sBuf = sg->Cells[17][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_KIND	,sBuf.c_str() );	//規格種類
	sBuf = sg->Cells[18][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_DECI	,sBuf.c_str() );	//規格小数点以下桁数
	sBuf = sg->Cells[19][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	//規格値１
	sBuf = sg->Cells[20][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	//規格値２
	sBuf = sg->Cells[21][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	//規格値３
	sBuf = sg->Cells[22][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	//規格文字
	sBuf = sg->Cells[23][iChgRow2];
    strcpy( tmpKSM11_12_DATA.KIKA_PRT	,sBuf.c_str() );	//上限下限値の印刷
	sBuf = sg->Cells[24][iChgRow2];
    strcpy( tmpKSM11_12_DATA.VALUE_DECI	,sBuf.c_str() );	//測定値小数点以下桁数
	sBuf = sg->Cells[25][iChgRow2];
    strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );	//登録日
	sBuf = sg->Cells[26][iChgRow2];
    strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );	//登録時間
	sBuf = sg->Cells[27][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );	//更新時間
	sBuf = sg->Cells[28][iChgRow2];
    strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );	//更新回数

	// 上下を入れ替えます
    for( i=iChgRow2; i>iChgRow1 ; i-- ) {
    	for( k = 1; k < sg->ColCount; k++ ) {
            if( k == 14 ){
                // 表示順は、入れ替えしない
    			// sg->Cells[k][i] = sg->Cells[k][i - 1];
            } else if( k == 29 ){
                // 更新フラグの設定
				sg->Cells[k][i] = "1";
        	} else {
				sg->Cells[k][i] = sg->Cells[k][i - 1];
            }
		}
    }

    // バックアップしたデータを戻します
	sg->Cells[1][iChgRow1] = tmpKSM11_12_DATA.KOMK_NM	;	//測定項目（日本語）
	sg->Cells[2][iChgRow1] = tmpKSM11_12_DATA.KOMK_ENG	;	//測定項目（英語）
	sg->Cells[3][iChgRow1] = tmpKSM11_12_DATA.KIKI_NM	;	//測定機器名称
	sg->Cells[4][iChgRow1] = tmpKSM11_12_DATA.TANI		;	//単位
	sg->Cells[5][iChgRow1] = ""							;	//規格（基本）　※再描画する為に必要です。
	sg->Cells[6][iChgRow1] = tmpKSM11_12_DATA.SOKU_SU	;	//ｎ数（基本）
	sg->Cells[7][iChgRow1] = tmpKSM11_12_DATA.VALUE_TYPE;	//値表現
	sg->Cells[8][iChgRow1] = tmpKSM11_12_DATA.SOKU_FLG	;	//測定項目の有無
	sg->Cells[9][iChgRow1] = tmpKSM11_12_DATA.TOKU_FLG	;	//特別項目の有無
	sg->Cells[10][iChgRow1] = tmpKSM11_12_DATA.UPDYMD	;	//変更日
	sg->Cells[11][iChgRow1] = tmpKSM11_12_DATA.UPDNAM	;	//更新者（名称）
	sg->Cells[12][iChgRow1] = tmpKSM11_12_DATA.UPDCHR	;	//更新者（担当者コード）
	sg->Cells[13][iChgRow1] = tmpKSM11_12_DATA.KOMK_NO	;	//項目NO
	sg->Cells[15][iChgRow1] = tmpKSM11_12_DATA.KIKI_NO	;	//測定機器NO
	sg->Cells[16][iChgRow1] = tmpKSM11_12_DATA.KIKA_TYPE;	//規格タイプ
	sg->Cells[17][iChgRow1] = tmpKSM11_12_DATA.KIKA_KIND;	//規格種類
	sg->Cells[18][iChgRow1] = tmpKSM11_12_DATA.KIKA_DECI;	//規格小数点以下桁数
	sg->Cells[19][iChgRow1] = tmpKSM11_12_DATA.KIKA_NUM1;	//規格値１
	sg->Cells[20][iChgRow1] = tmpKSM11_12_DATA.KIKA_NUM2;	//規格値２
	sg->Cells[21][iChgRow1] = tmpKSM11_12_DATA.KIKA_NUM3;	//規格値３
	sg->Cells[22][iChgRow1] = tmpKSM11_12_DATA.KIKA_STR	;	//規格文字
	sg->Cells[23][iChgRow1] = tmpKSM11_12_DATA.KIKA_PRT	;	//上限下限値の印刷
	sg->Cells[24][iChgRow1] = tmpKSM11_12_DATA.VALUE_DECI;	//測定値小数点以下桁数
	sg->Cells[25][iChgRow1] = tmpKSM11_12_DATA.ADDYMD	;	//登録日
	sg->Cells[26][iChgRow1] = tmpKSM11_12_DATA.ADDTIM	;	//登録時間
	sg->Cells[27][iChgRow1] = tmpKSM11_12_DATA.UPDTIM	;	//更新時間
	sg->Cells[28][iChgRow1] = tmpKSM11_12_DATA.UPDCNT	;	//更新回数
	sg->Cells[29][iChgRow1] = "1"						;	//更新フラグの設定

    // 選択カーソルも同時に下に移動します
    sg->Row++;
	myRect.Left		= sg->Selection.Left;
	myRect.Top		= iChgRow1 + 1;
	myRect.Right	= sg->Selection.Right;
	myRect.Bottom	= iChgRow3 + 1;
    sg->Selection	= myRect;
    SGr_ListSelectCell(sg,1,sg->Row,true);

    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：StringGridを選択した時に発生します。
//
//  機能説明
//    選択（範囲選択）されたTopとBottomを記憶します（SGr_ListRowMovedで利用される）
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_ListClick(TObject *Sender)
{
    TStringGrid* sg = dynamic_cast<TStringGrid*>(Sender);

   	iRowSelTop    = sg->Selection.Top;
   	iRowSelBottom = sg->Selection.Bottom;
}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：StringGridの行の位置が変更された直後に発生します。
//
//  機能説明
//    StringGridで行が移動された（ドラッグ）時の複数行対応処理
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int FromIndex		：移動元の行位置
//    int ToIndex		：移動先の行位置
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_ListRowMoved(TObject *Sender, int FromIndex,
      int ToIndex)
{

    int         i;
    int			k;
    int			m;
	int			CopyCnt;
    int			iStart;
    int			iEnd;
    int			iSkip;
    HANDLE  	hMemCopy;
    AnsiString  sBuf;
    KSM11_12_DATA  *pKSM11_12_DATA;
	TGridRect	myRect;
    TStringGrid* sg = dynamic_cast<TStringGrid*>(Sender);


    // 範囲選択したものと実際に移動処理された行の指定位置が異なる時は、エラー
    if( FromIndex < iRowSelTop || FromIndex > iRowSelBottom ){
        RowExchange(sg, FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("選択範囲が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // 範囲選択した移動先が、その範囲選択内への移動の時は、エラー
    if( ToIndex >= iRowSelTop && ToIndex <= iRowSelBottom ){
        RowExchange(sg, FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("移動先が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // 最下行の下へ移動の時は、エラー
    if( ToIndex >= sg->RowCount - 1 ){
        RowExchange(sg, FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("移動先が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    // 範囲選択したものに最下行を含む時は、エラー
    if( sg->RowCount - 1 <= iRowSelBottom ){
        RowExchange(sg, FromIndex,ToIndex);
        // エラーメッセージ
    	MessageDlg("選択範囲が正しくありません。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
    	return;
    }

    if( FromIndex < ToIndex ){
        iStart = iRowSelTop;
        iEnd   = ToIndex;

		// 表示順を入れ替えます
    	sBuf = sg->Cells[14][ToIndex];
		for( i = ToIndex; i > FromIndex; i-- ){
			sg->Cells[14][i] = sg->Cells[14][i-1];
    	}
    	sg->Cells[14][FromIndex] = sBuf;
    }
    else {
        iStart = ToIndex;
        iEnd   = iRowSelBottom;

		// 表示順を入れ替えます
        sBuf = sg->Cells[14][ToIndex];
		for( i = ToIndex; i < FromIndex; i++ ){
			sg->Cells[14][i] = sg->Cells[14][i+1];
    	}
    	sg->Cells[14][FromIndex] = sBuf;
    }

	// 行Noを元に戻します
	for( i = iStart; i <= iEnd; i++ ){
		sBuf = i ;
		if( i < sg->RowCount - 1 ){
			sg->Cells[0][i] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
   	    	sg->Cells[29][i] = "1";						// 更新フラグON
		}
        else{
			sg->Cells[0][i] = "";
   	    	sg->Cells[29][i] = "";
        }
    }

    // コピーの個数を確保します
    CopyCnt = iRowSelBottom - iRowSelTop;

    // メモリの確保
    hMemCopy = GlobalAlloc( GHND, sizeof(struct KSM11_12_DATA) * CopyCnt );
    if( hMemCopy == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
        SBr1->Update();
        Beep();
        return;
    }
    pKSM11_12_DATA = (struct KSM11_12_DATA *)GlobalLock(hMemCopy);
    if( hMemCopy == NULL ){
        SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
        SBr1->Update();
        Beep();
        return;
    }

    if( FromIndex < ToIndex ){

	    // 選択されている範囲をメモリに格納します
    	for( i=iRowSelTop, k=0; i<iRowSelBottom; i++, k++ ) {
			sBuf = sg->Cells[1][i];
			strcpy( pKSM11_12_DATA[k].KOMK_NM		,sBuf.c_str() );	//測定項目（日本語）
			sBuf = sg->Cells[2][i];
			strcpy( pKSM11_12_DATA[k].KOMK_ENG		,sBuf.c_str() );	//測定項目（英語）
			sBuf = sg->Cells[3][i];
			strcpy( pKSM11_12_DATA[k].KIKI_NM		,sBuf.c_str() );	//測定機器名称
			sBuf = sg->Cells[4][i];
			strcpy( pKSM11_12_DATA[k].TANI			,sBuf.c_str() );	//単位
			sBuf = sg->Cells[6][i];
			strcpy( pKSM11_12_DATA[k].SOKU_SU		,sBuf.c_str() );	//ｎ数（基本）
			sBuf = sg->Cells[7][i];
			strcpy( pKSM11_12_DATA[k].VALUE_TYPE	,sBuf.c_str() );	//値表現
			sBuf = sg->Cells[8][i];
			strcpy( pKSM11_12_DATA[k].SOKU_FLG		,sBuf.c_str() );	//測定項目の有無
			sBuf = sg->Cells[9][i];
			strcpy( pKSM11_12_DATA[k].TOKU_FLG		,sBuf.c_str() );	//特別項目の有無
			sBuf = sg->Cells[10][i];
			strcpy( pKSM11_12_DATA[k].UPDYMD		,sBuf.c_str() );	//変更日
			sBuf = sg->Cells[12][i];
			strcpy( pKSM11_12_DATA[k].UPDCHR		,sBuf.c_str() );	//更新者（担当者コード）
			sBuf = sg->Cells[11][i];
			strcpy( pKSM11_12_DATA[k].UPDNAM		,sBuf.c_str() );	//更新者（名称）
			sBuf = sg->Cells[13][i];
			strcpy( pKSM11_12_DATA[k].KOMK_NO		,sBuf.c_str() );	//項目NO
			sBuf = sg->Cells[15][i];
			strcpy( pKSM11_12_DATA[k].KIKI_NO		,sBuf.c_str() );	//測定機器NO
			sBuf = sg->Cells[16][i];
			strcpy( pKSM11_12_DATA[k].KIKA_TYPE		,sBuf.c_str() );	//規格タイプ
			sBuf = sg->Cells[17][i];
			strcpy( pKSM11_12_DATA[k].KIKA_KIND		,sBuf.c_str() );	//規格種類
			sBuf = sg->Cells[18][i];
			strcpy( pKSM11_12_DATA[k].KIKA_DECI		,sBuf.c_str() );	//規格小数点以下桁数
			sBuf = sg->Cells[19][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM1		,sBuf.c_str() );	//規格値１
			sBuf = sg->Cells[20][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM2		,sBuf.c_str() );	//規格値２
			sBuf = sg->Cells[21][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM3		,sBuf.c_str() );	//規格値３
			sBuf = sg->Cells[22][i];
			strcpy( pKSM11_12_DATA[k].KIKA_STR		,sBuf.c_str() );	//規格文字
			sBuf = sg->Cells[23][i];
			strcpy( pKSM11_12_DATA[k].KIKA_PRT		,sBuf.c_str() );	//上限下限値の印刷
			sBuf = sg->Cells[24][i];
			strcpy( pKSM11_12_DATA[k].VALUE_DECI	,sBuf.c_str() );	//測定値小数点以下桁数
			sBuf = sg->Cells[25][i];
			strcpy( pKSM11_12_DATA[k].ADDYMD		,sBuf.c_str() );	//登録日
			sBuf = sg->Cells[26][i];
			strcpy( pKSM11_12_DATA[k].ADDTIM		,sBuf.c_str() );	//登録時間
			sBuf = sg->Cells[27][i];
			strcpy( pKSM11_12_DATA[k].UPDTIM		,sBuf.c_str() );	//更新時間
			sBuf = sg->Cells[28][i];
			strcpy( pKSM11_12_DATA[k].UPDCNT		,sBuf.c_str() );	//更新回数
    	}

		// 複数選択内容を移動します
		for( i = iRowSelBottom; i <= ToIndex; i++ ){
	    	for( k = 1; k < sg->ColCount; k++ ) {
	            if( k == 14 ){
	                // 表示順は、入れ替えしない
	    			// sg->Cells[k][i-CopyCnt] = sg->Cells[k][i];
	        	} else {
					sg->Cells[k][i-CopyCnt] = sg->Cells[k][i];
	            }
			}
    	}

        // 自動移動された行を正しい位置に移動します。
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
	    	for( k = 1; k < sg->ColCount; k++ ) {
	            if( k == 14 ){
	                // 表示順は、入れ替えしない
	    			// sg->Cells[k][ToIndex-CopyCnt+iSkip] = sg->Cells[k][ToIndex];
	        	} else {
					sg->Cells[k][ToIndex-CopyCnt+iSkip] = sg->Cells[k][ToIndex];
	            }
			}
        }

		// メモリに格納した内容を戻します
        i = ToIndex - CopyCnt;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
				sg->Cells[1][i+k] = pKSM11_12_DATA[m].KOMK_NM		;	//測定項目（日本語）
				sg->Cells[2][i+k] = pKSM11_12_DATA[m].KOMK_ENG		;	//測定項目（英語）
				sg->Cells[3][i+k] = pKSM11_12_DATA[m].KIKI_NM		;	//測定機器名称
				sg->Cells[4][i+k] = pKSM11_12_DATA[m].TANI			;	//単位
				sg->Cells[5][i+k] = ""								;	//規格（基本）　※再描画する為に必要です。
				sg->Cells[6][i+k] = pKSM11_12_DATA[m].SOKU_SU		;	//ｎ数（基本）
				sg->Cells[7][i+k] = pKSM11_12_DATA[m].VALUE_TYPE	;	//値表現
				sg->Cells[8][i+k] = pKSM11_12_DATA[m].SOKU_FLG		;	//測定項目の有無
				sg->Cells[9][i+k] = pKSM11_12_DATA[m].TOKU_FLG		;	//特別項目の有無
				sg->Cells[10][i+k] = pKSM11_12_DATA[m].UPDYMD		;	//変更日
				sg->Cells[11][i+k] = pKSM11_12_DATA[m].UPDNAM		;	//更新者（名称）
				sg->Cells[12][i+k] = pKSM11_12_DATA[m].UPDCHR		;	//更新者（担当者コード）
				sg->Cells[13][i+k] = pKSM11_12_DATA[m].KOMK_NO		;	//項目NO
				sg->Cells[15][i+k] = pKSM11_12_DATA[m].KIKI_NO		;	//測定機器NO
				sg->Cells[16][i+k] = pKSM11_12_DATA[m].KIKA_TYPE	;	//規格タイプ
				sg->Cells[17][i+k] = pKSM11_12_DATA[m].KIKA_KIND	;	//規格種類
				sg->Cells[18][i+k] = pKSM11_12_DATA[m].KIKA_DECI	;	//規格小数点以下桁数
				sg->Cells[19][i+k] = pKSM11_12_DATA[m].KIKA_NUM1	;	//規格値１
				sg->Cells[20][i+k] = pKSM11_12_DATA[m].KIKA_NUM2	;	//規格値２
				sg->Cells[21][i+k] = pKSM11_12_DATA[m].KIKA_NUM3	;	//規格値３
				sg->Cells[22][i+k] = pKSM11_12_DATA[m].KIKA_STR		;	//規格文字
				sg->Cells[23][i+k] = pKSM11_12_DATA[m].KIKA_PRT		;	//上限下限値の印刷
				sg->Cells[24][i+k] = pKSM11_12_DATA[m].VALUE_DECI	;	//測定値小数点以下桁数
				sg->Cells[25][i+k] = pKSM11_12_DATA[m].ADDYMD		;	//登録日
				sg->Cells[26][i+k] = pKSM11_12_DATA[m].ADDTIM		;	//登録時間
				sg->Cells[27][i+k] = pKSM11_12_DATA[m].UPDTIM		;	//更新時間
				sg->Cells[28][i+k] = pKSM11_12_DATA[m].UPDCNT		;	//更新回数
				sg->Cells[29][i+k] = "1"							;	//更新フラグの設定
				m++;
        	}
        }

    	// 移動先の行を選択範囲を決定します
		myRect.Left		= sg->Selection.Left;
		myRect.Top		= ToIndex - CopyCnt;
		myRect.Right	= sg->Selection.Right;
		myRect.Bottom	= myRect.Top + CopyCnt;
    }
    else {

	    // 選択されている範囲をメモリに格納します
    	for( i=iRowSelTop+1, k=0; i<=iRowSelBottom; i++, k++ ) {
			sBuf = sg->Cells[1][i];
			strcpy( pKSM11_12_DATA[k].KOMK_NM		,sBuf.c_str() );	//測定項目（日本語）
			sBuf = sg->Cells[2][i];
			strcpy( pKSM11_12_DATA[k].KOMK_ENG		,sBuf.c_str() );	//測定項目（英語）
			sBuf = sg->Cells[3][i];
			strcpy( pKSM11_12_DATA[k].KIKI_NM		,sBuf.c_str() );	//測定機器名称
			sBuf = sg->Cells[4][i];
			strcpy( pKSM11_12_DATA[k].TANI			,sBuf.c_str() );	//単位
			sBuf = sg->Cells[6][i];
			strcpy( pKSM11_12_DATA[k].SOKU_SU		,sBuf.c_str() );	//ｎ数（基本）
			sBuf = sg->Cells[7][i];
			strcpy( pKSM11_12_DATA[k].VALUE_TYPE	,sBuf.c_str() );	//値表現
			sBuf = sg->Cells[8][i];
			strcpy( pKSM11_12_DATA[k].SOKU_FLG		,sBuf.c_str() );	//測定項目の有無
			sBuf = sg->Cells[9][i];
			strcpy( pKSM11_12_DATA[k].TOKU_FLG		,sBuf.c_str() );	//特別項目の有無
			sBuf = sg->Cells[10][i];
			strcpy( pKSM11_12_DATA[k].UPDYMD		,sBuf.c_str() );	//変更日
			sBuf = sg->Cells[12][i];
			strcpy( pKSM11_12_DATA[k].UPDCHR		,sBuf.c_str() );	//更新者（担当者コード）
			sBuf = sg->Cells[11][i];
			strcpy( pKSM11_12_DATA[k].UPDNAM		,sBuf.c_str() );	//更新者（名称）
			sBuf = sg->Cells[13][i];
			strcpy( pKSM11_12_DATA[k].KOMK_NO		,sBuf.c_str() );	//項目NO
			sBuf = sg->Cells[15][i];
			strcpy( pKSM11_12_DATA[k].KIKI_NO		,sBuf.c_str() );	//測定機器NO
			sBuf = sg->Cells[16][i];
			strcpy( pKSM11_12_DATA[k].KIKA_TYPE		,sBuf.c_str() );	//規格タイプ
			sBuf = sg->Cells[17][i];
			strcpy( pKSM11_12_DATA[k].KIKA_KIND		,sBuf.c_str() );	//規格種類
			sBuf = sg->Cells[18][i];
			strcpy( pKSM11_12_DATA[k].KIKA_DECI		,sBuf.c_str() );	//規格小数点以下桁数
			sBuf = sg->Cells[19][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM1		,sBuf.c_str() );	//規格値１
			sBuf = sg->Cells[20][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM2		,sBuf.c_str() );	//規格値２
			sBuf = sg->Cells[21][i];
			strcpy( pKSM11_12_DATA[k].KIKA_NUM3		,sBuf.c_str() );	//規格値３
			sBuf = sg->Cells[22][i];
			strcpy( pKSM11_12_DATA[k].KIKA_STR		,sBuf.c_str() );	//規格文字
			sBuf = sg->Cells[23][i];
			strcpy( pKSM11_12_DATA[k].KIKA_PRT		,sBuf.c_str() );	//上限下限値の印刷
			sBuf = sg->Cells[24][i];
			strcpy( pKSM11_12_DATA[k].VALUE_DECI	,sBuf.c_str() );	//測定値小数点以下桁数
			sBuf = sg->Cells[25][i];
			strcpy( pKSM11_12_DATA[k].ADDYMD		,sBuf.c_str() );	//登録日
			sBuf = sg->Cells[26][i];
			strcpy( pKSM11_12_DATA[k].ADDTIM		,sBuf.c_str() );	//登録時間
			sBuf = sg->Cells[27][i];
			strcpy( pKSM11_12_DATA[k].UPDTIM		,sBuf.c_str() );	//更新時間
			sBuf = sg->Cells[28][i];
			strcpy( pKSM11_12_DATA[k].UPDCNT		,sBuf.c_str() );	//更新回数
    	}

		// 複数選択内容を移動します
		for( i = iRowSelTop; i >= ToIndex; i-- ){
	    	for( k = 1; k < sg->ColCount; k++ ) {
	            if( k == 14 ){
	                // 表示順は、入れ替えしない
	    			// sg->Cells[k][i+CopyCnt] = sg->Cells[k][i];
	        	} else {
					sg->Cells[k][i+CopyCnt] = sg->Cells[k][i];
	            }
			}
    	}

        // 自動移動された行を正しい位置に移動します。
        iSkip = FromIndex - iRowSelTop;
        if( iSkip != 0 ){
	    	for( k = 1; k < sg->ColCount; k++ ) {
	            if( k == 14 ){
	                // 表示順は、入れ替えしない
	    			// sg->Cells[k][ToIndex+iSkip] = sg->Cells[k][ToIndex];
	        	} else {
					sg->Cells[k][ToIndex+iSkip] = sg->Cells[k][ToIndex];
	            }
			}
        }

		// メモリに格納した内容を戻します
        i = ToIndex;
		for( k = 0, m = 0; k <= CopyCnt; k++ ){
            if( k != iSkip ){
				sg->Cells[1][i+k] = pKSM11_12_DATA[m].KOMK_NM		;	//測定項目（日本語）
				sg->Cells[2][i+k] = pKSM11_12_DATA[m].KOMK_ENG		;	//測定項目（英語）
				sg->Cells[3][i+k] = pKSM11_12_DATA[m].KIKI_NM		;	//測定機器名称
				sg->Cells[4][i+k] = pKSM11_12_DATA[m].TANI			;	//単位
				sg->Cells[5][i+k] = ""								;	//規格（基本）　※再描画する為に必要です。
				sg->Cells[6][i+k] = pKSM11_12_DATA[m].SOKU_SU		;	//ｎ数（基本）
				sg->Cells[7][i+k] = pKSM11_12_DATA[m].VALUE_TYPE	;	//値表現
				sg->Cells[8][i+k] = pKSM11_12_DATA[m].SOKU_FLG		;	//測定項目の有無
				sg->Cells[9][i+k] = pKSM11_12_DATA[m].TOKU_FLG		;	//特別項目の有無
				sg->Cells[10][i+k] = pKSM11_12_DATA[m].UPDYMD		;	//変更日
				sg->Cells[11][i+k] = pKSM11_12_DATA[m].UPDNAM		;	//更新者（名称）
				sg->Cells[12][i+k] = pKSM11_12_DATA[m].UPDCHR		;	//更新者（担当者コード）
				sg->Cells[13][i+k] = pKSM11_12_DATA[m].KOMK_NO		;	//項目NO
				sg->Cells[15][i+k] = pKSM11_12_DATA[m].KIKI_NO		;	//測定機器NO
				sg->Cells[16][i+k] = pKSM11_12_DATA[m].KIKA_TYPE	;	//規格タイプ
				sg->Cells[17][i+k] = pKSM11_12_DATA[m].KIKA_KIND	;	//規格種類
				sg->Cells[18][i+k] = pKSM11_12_DATA[m].KIKA_DECI	;	//規格小数点以下桁数
				sg->Cells[19][i+k] = pKSM11_12_DATA[m].KIKA_NUM1	;	//規格値１
				sg->Cells[20][i+k] = pKSM11_12_DATA[m].KIKA_NUM2	;	//規格値２
				sg->Cells[21][i+k] = pKSM11_12_DATA[m].KIKA_NUM3	;	//規格値３
				sg->Cells[22][i+k] = pKSM11_12_DATA[m].KIKA_STR		;	//規格文字
				sg->Cells[23][i+k] = pKSM11_12_DATA[m].KIKA_PRT		;	//上限下限値の印刷
				sg->Cells[24][i+k] = pKSM11_12_DATA[m].VALUE_DECI	;	//測定値小数点以下桁数
				sg->Cells[25][i+k] = pKSM11_12_DATA[m].ADDYMD		;	//登録日
				sg->Cells[26][i+k] = pKSM11_12_DATA[m].ADDTIM		;	//登録時間
				sg->Cells[27][i+k] = pKSM11_12_DATA[m].UPDTIM		;	//更新時間
				sg->Cells[28][i+k] = pKSM11_12_DATA[m].UPDCNT		;	//更新回数
				sg->Cells[29][i+k] = "1"							;	//更新フラグの設定
				m++;
        	}
        }

    	// 移動先の行を選択範囲を決定します
		myRect.Left		= sg->Selection.Left;
		myRect.Top		= ToIndex;
		myRect.Right	= sg->Selection.Right;
		myRect.Bottom	= ToIndex + CopyCnt;
    }

    // メモリの開放
    if( hMemCopy ){
        GlobalUnlock( hMemCopy );
        GlobalFree( hMemCopy );
    }


    // 移動先の行を選択します
    sg->Row   		= myRect.Top;
    sg->Selection	= myRect;
    SGr_ListSelectCell(Sender,1,sg->Row,true);

    iRowSelTop    = sg->Selection.Top;
    iRowSelBottom = sg->Selection.Bottom;

    // データを変更したフラグ
    DataSave = true;
    BtnF11->Enabled = true;
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：一行だけ行の入れ替え処理を行ないます。
//
//  機能説明
//    指定した行同士の入れ替え処理を行ないます
//
//  パラメタ説明
//    TStringGrid* sg	：呼び出し元のTStringGridオブジェクト
//    int FromIndex		：移動元の行位置
//    int ToIndex		：移動先の行位置
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::RowExchange(TStringGrid* sg, int FromIndex, int ToIndex)
{
    int			i, k;
	TGridRect	myRect;
    AnsiString	sBuf;
    AnsiString	sLineNo;

    // 入れ替え先のデータをバックアップ
    sLineNo = sg->Cells[0][ToIndex];						//行番号
	sBuf = sg->Cells[1][ToIndex];
    strcpy( tmpKSM11_12_DATA.KOMK_NM	,sBuf.c_str() );	//測定項目（日本語）
	sBuf = sg->Cells[2][ToIndex];
    strcpy( tmpKSM11_12_DATA.KOMK_ENG	,sBuf.c_str() );	//測定項目（英語）
	sBuf = sg->Cells[3][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKI_NM	,sBuf.c_str() );	//測定機器名称
	sBuf = sg->Cells[4][ToIndex];
    strcpy( tmpKSM11_12_DATA.TANI		,sBuf.c_str() );	//単位
	sBuf = sg->Cells[6][ToIndex];
    strcpy( tmpKSM11_12_DATA.SOKU_SU	,sBuf.c_str() );	//ｎ数（基本）
	sBuf = sg->Cells[7][ToIndex];
    strcpy( tmpKSM11_12_DATA.VALUE_TYPE	,sBuf.c_str() );	//値表現
	sBuf = sg->Cells[8][ToIndex];
    strcpy( tmpKSM11_12_DATA.SOKU_FLG	,sBuf.c_str() );	//測定項目の有無
	sBuf = sg->Cells[9][ToIndex];
    strcpy( tmpKSM11_12_DATA.TOKU_FLG	,sBuf.c_str() );	//特別項目の有無
	sBuf = sg->Cells[10][ToIndex];
    strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );	//変更日
	sBuf = sg->Cells[12][ToIndex];
    strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );	//更新者（担当者コード）
	sBuf = sg->Cells[11][ToIndex];
    strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );	//更新者（名称）
	sBuf = sg->Cells[13][ToIndex];
    strcpy( tmpKSM11_12_DATA.KOMK_NO	,sBuf.c_str() );	//項目NO
	sBuf = sg->Cells[14][ToIndex];
    strcpy( tmpKSM11_12_DATA.ORDER_NO	,sBuf.c_str() );	//表示順
	sBuf = sg->Cells[15][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKI_NO	,sBuf.c_str() );	//測定機器NO
	sBuf = sg->Cells[16][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_TYPE	,sBuf.c_str() );	//規格タイプ
	sBuf = sg->Cells[17][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_KIND	,sBuf.c_str() );	//規格種類
	sBuf = sg->Cells[18][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_DECI	,sBuf.c_str() );	//規格小数点以下桁数
	sBuf = sg->Cells[19][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	//規格値１
	sBuf = sg->Cells[20][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	//規格値２
	sBuf = sg->Cells[21][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	//規格値３
	sBuf = sg->Cells[22][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	//規格文字
	sBuf = sg->Cells[23][ToIndex];
    strcpy( tmpKSM11_12_DATA.KIKA_PRT	,sBuf.c_str() );	//上限下限値の印刷
	sBuf = sg->Cells[24][ToIndex];
    strcpy( tmpKSM11_12_DATA.VALUE_DECI	,sBuf.c_str() );	//測定値小数点以下桁数
	sBuf = sg->Cells[25][ToIndex];
    strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );	//登録日
	sBuf = sg->Cells[26][ToIndex];
    strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );	//登録時間
	sBuf = sg->Cells[27][ToIndex];
    strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );	//更新時間
	sBuf = sg->Cells[28][ToIndex];
    strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );	//更新回数
	sBuf = sg->Cells[29][ToIndex];							//更新フラグ

    if( ToIndex > FromIndex ){
		// 上下を入れ替えます
    	for( i=ToIndex; i>FromIndex; i-- ) {
	    	for( k = 0; k < sg->ColCount; k++ ) {
				sg->Cells[k][i] = sg->Cells[k][i-1];
			}
    	}
    }
    else{
		// 上下を入れ替えます
    	for( i=ToIndex; i<FromIndex; i++ ) {
	    	for( k = 0; k < sg->ColCount; k++ ) {
				sg->Cells[k][i] = sg->Cells[k][i+1];
			}
    	}
    }

    // バックアップしたデータを元にもどします。
    sg->Cells[0][FromIndex] = sLineNo						;	//行番号
	sg->Cells[1][FromIndex] = tmpKSM11_12_DATA.KOMK_NM		;	//測定項目（日本語）
	sg->Cells[2][FromIndex] = tmpKSM11_12_DATA.KOMK_ENG		;	//測定項目（英語）
	sg->Cells[3][FromIndex] = tmpKSM11_12_DATA.KIKI_NM		;	//測定機器名称
	sg->Cells[4][FromIndex] = tmpKSM11_12_DATA.TANI			;	//単位
	sg->Cells[5][FromIndex] = ""							;	//規格（基本）　※再描画する為に必要です。
	sg->Cells[6][FromIndex] = tmpKSM11_12_DATA.SOKU_SU		;	//ｎ数（基本）
	sg->Cells[7][FromIndex] = tmpKSM11_12_DATA.VALUE_TYPE	;	//値表現
	sg->Cells[8][FromIndex] = tmpKSM11_12_DATA.SOKU_FLG		;	//測定項目の有無
	sg->Cells[9][FromIndex] = tmpKSM11_12_DATA.TOKU_FLG		;	//特別項目の有無
	sg->Cells[10][FromIndex] = tmpKSM11_12_DATA.UPDYMD		;	//変更日
	sg->Cells[11][FromIndex] = tmpKSM11_12_DATA.UPDNAM		;	//更新者（名称）
	sg->Cells[12][FromIndex] = tmpKSM11_12_DATA.UPDCHR		;	//更新者（担当者コード）
	sg->Cells[13][FromIndex] = tmpKSM11_12_DATA.KOMK_NO		;	//項目NO
	sg->Cells[14][FromIndex] = tmpKSM11_12_DATA.ORDER_NO	;	//表示順
	sg->Cells[15][FromIndex] = tmpKSM11_12_DATA.KIKI_NO		;	//測定機器NO
	sg->Cells[16][FromIndex] = tmpKSM11_12_DATA.KIKA_TYPE	;	//規格タイプ
	sg->Cells[17][FromIndex] = tmpKSM11_12_DATA.KIKA_KIND	;	//規格種類
	sg->Cells[18][FromIndex] = tmpKSM11_12_DATA.KIKA_DECI	;	//規格小数点以下桁数
	sg->Cells[19][FromIndex] = tmpKSM11_12_DATA.KIKA_NUM1	;	//規格値１
	sg->Cells[20][FromIndex] = tmpKSM11_12_DATA.KIKA_NUM2	;	//規格値２
	sg->Cells[21][FromIndex] = tmpKSM11_12_DATA.KIKA_NUM3	;	//規格値３
	sg->Cells[22][FromIndex] = tmpKSM11_12_DATA.KIKA_STR	;	//規格文字
	sg->Cells[23][FromIndex] = tmpKSM11_12_DATA.KIKA_PRT	;	//上限下限値の印刷
	sg->Cells[24][FromIndex] = tmpKSM11_12_DATA.VALUE_DECI	;	//測定値小数点以下桁数
	sg->Cells[25][FromIndex] = tmpKSM11_12_DATA.ADDYMD		;	//登録日
	sg->Cells[26][FromIndex] = tmpKSM11_12_DATA.ADDTIM		;	//登録時間
	sg->Cells[27][FromIndex] = tmpKSM11_12_DATA.UPDTIM		;	//更新時間
	sg->Cells[28][FromIndex] = tmpKSM11_12_DATA.UPDCNT		;	//更新回数
	sg->Cells[29][FromIndex] = sBuf							;	//更新フラグの設定

    // 選択し直します
    //SGr_List->Row	= iRowSelTop;
	myRect.Left		= sg->Selection.Left;
	myRect.Top		= iRowSelTop;
	myRect.Right	= sg->Selection.Right;
	myRect.Bottom	= iRowSelBottom;
    sg->Selection	= myRect;
    //SGr_ListSelectCell(Sender,1,sg->Row,true);

}

//---------------------------------------------------------------------------
//
//  概要
//    OnSelectCellイベント：StringGridのセルが選択される前に発生します。
//
//  機能説明
//    StringGridで選択されたら、画面下部のTextBoxにセットします
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//    int ACol			：選択する列の位置
//    int ARow			：選択する行の位置
//    bool &CanSelect	：選択を許すかどうかのフラグ
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::SGr_ListSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{

    int			i, k;
    AnsiString	sBuf;
	TStringGrid *sg = (TStringGrid *)Sender;


    if(ARow == 0) ARow = 1;
    ROWPOINT = ARow;

	// 項目の種類
    if( sg->Name == "SGr_List" ){
        Rdo_TYPE_SYUKA->Checked = true;
	} else{
        Rdo_TYPE_ZAIRYO->Checked = true;
	}

    // 測定項目（日本語）
    Edt_SKTKMK_JPN->Text = sg->Cells[1][ARow];

    // 項目名（英語）
    Edt_SKTKMK_ENG->Text = sg->Cells[2][ARow];

    // 測定機器
    k = sg->Cells[15][ARow].ToIntDef(-1);
    if( k == -1 ){
	    Cmb_SKTKIKI->ItemIndex = 0;
    }
    else {
    	for( i = 0; i < iKIKI_Cnt; i++){
    		if( iKIKI[i] == k ){
			    Cmb_SKTKIKI->ItemIndex = i;
            	break;
        	}
    	}
    }

    // 単位
    Cmb_TANI->Text = sg->Cells[4][ARow];

	// 測定項目としての扱い
    switch( sg->Cells[8][ARow].ToIntDef(-1) ){
		case 0: Rdo_SKTKMK_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_SKTKMK_ON->Checked = true;
          		break;
   	}

	// 特別項目としての扱い
    switch( sg->Cells[9][ARow].ToIntDef(-1) ){
		case 1: Rdo_TKBKMK_ON->Checked = true;
				break;
		case 0:
        default:Rdo_TKBKMK_OFF->Checked = true;
          		break;
   	}

	// 規格（指定方法）
    switch( sg->Cells[16][ARow].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SHITEI_MOJI->Checked = true;
				break;
		case 2: Rdo_KIKAKU_SHITEI_KIJYUN->Checked = true;
				break;
		case 1:
        default:Rdo_KIKAKU_SHITEI_HANI->Checked = true;
          		break;
   	}

	// 規格（種類）
    switch( sg->Cells[17][ARow].ToIntDef(-1) ){
		case 3: Rdo_KIKAKU_SYURUI_MIN->Checked = true;
				break;
		case 2: Rdo_KIKAKU_SYURUI_MAX->Checked = true;
				break;
		case 1:
        default:Rdo_KIKAKU_SYURUI_MINMAX->Checked = true;
          		break;
   	}

	// 規格（上限下限値の印刷）
    switch( sg->Cells[23][ARow].ToIntDef(-1) ){
		case 0: Rdo_MANMIN_PRT_OFF->Checked = true;
				break;
		case 1:
        default:Rdo_MANMIN_PRT_ON->Checked = true;
          		break;
   	}

	// 規格（小数点以下桁数）
    Nmb_KIKAKU_DOUBLE->Text = IntToStr(sg->Cells[18][ARow].ToIntDef(0));

	// 規格値（範囲指定）
    Nmb_KIKAKU_HANI_MIN->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_HANI_MAX->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_HANI_MIN->Text = sg->Cells[19][ARow];
    if( sg->Cells[16][ARow].ToIntDef(-1) == 1 ){
	    Nmb_KIKAKU_HANI_MAX->Text = sg->Cells[20][ARow];
    }
    else {
	    Nmb_KIKAKU_HANI_MAX->Text = "0";
    }

	// 規格値（基準値指定）
    Nmb_KIKAKU_KIJYUN_MID->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MAX->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MIN->FPos = sg->Cells[18][ARow].ToIntDef(0);
    Nmb_KIKAKU_KIJYUN_MID->Text = sg->Cells[19][ARow];
    if( sg->Cells[16][ARow].ToIntDef(-1) == 2 ){
    	Nmb_KIKAKU_KIJYUN_MAX->Text = sg->Cells[20][ARow];
    	Nmb_KIKAKU_KIJYUN_MIN->Text = sg->Cells[21][ARow];
    }
    else {
    	Nmb_KIKAKU_KIJYUN_MAX->Text = "0";
    	Nmb_KIKAKU_KIJYUN_MIN->Text = "0";
    }

	// 規格値（文字指定）
    Edt_KIKAKU_STRING->Text = sg->Cells[22][ARow];

	// 測定値（値表現）
    switch( sg->Cells[7][ARow].ToIntDef(-1) ){
		case 3: Rdo_VALUE_TEXT->Checked = true;
				break;
		case 2: Rdo_VALUE_OK->Checked = true;
				break;
		case 1: Rdo_VALUE_KAKUDO->Checked = true;
				break;
		case 0:
        default:Rdo_VALUE_NORMAL->Checked = true;
          		break;
   	}

	// 測定値（小数点以下桁数）
    Nmb_VALUE_DOUBLE->Text = IntToStr(sg->Cells[24][ARow].ToIntDef(0));

	// 測定値（抜取ｎ数）
    Nmb_N->Text = IntToStr(sg->Cells[6][ARow].ToIntDef(2));

    // 更新日
    sBuf = sg->Cells[10][ARow];
    if( sBuf.Length() == 8 ){
    	sBuf.Insert("/",5);
       	sBuf.Insert("/",8);
	   	PnlUPDYMD->Caption = sBuf;
    }
    else {
	   	PnlUPDYMD->Caption = "";
    }

    // 更新者
    PnlUPDCHR->Caption = sg->Cells[11][ARow];

    // 修正･削除の為に「項目No」を記憶します。
    if( sg->Cells[13][ARow] == "" ){
        PnlUPDYMD->Tag = -1;
    }
    else {
        PnlUPDYMD->Tag = StrToInt(sg->Cells[13][ARow]);
    }

    // 更新回数を記憶します。
    if( sg->Cells[28][ARow] == "" ){
    	PnlUPDCHR->Tag = -1;
    }
    else {
    	PnlUPDCHR->Tag = StrToInt(sg->Cells[28][ARow]);
    }

    // 更新・削除不可能項目の場合、修正・削除ボタンを利用不可にします。
    if( SGr_List->Cells[13][ARow] == 1 || PnlUPDYMD->Tag == -1 ){
		BtnF09->Enabled = false;
		BtnF10->Enabled = false;
    }
    else{
		BtnF09->Enabled = true;
		BtnF10->Enabled = true;
    }
}

//---------------------------------------------------------------------------
//
//  概要
//    OnChangeイベント	：新しいタブが選択されると発生します。
//
//  機能説明
//    ページコントロールによる「出荷検査測定項目」「材料証明項目」の切替
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::PgCtr_ListChange(TObject *Sender)
{
	TPageControl *pPC = (TPageControl *)Sender;

	if( pPC->ActivePage->Name == "TabSheet1" ){
	    //行を自動選択します
    	SGr_ListSelectCell( SGr_List, 1, SGr_List->Row, true);
	    SGr_ListClick( SGr_List );
	} else{
	    //行を自動選択します
    	SGr_ListSelectCell( SGr_List2, 1, SGr_List2->Row, true);
	    SGr_ListClick( SGr_List2 );
	}
}

//---------------------------------------------------------------------------
//
//  概要
//    OnExitイベント	：入力フォーカスが別のコントロールへ移ったときに発生します。
//
//  機能説明
//    規格の小数点以下桁数と測定値の小数点以下桁数に同じ値を設定します。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Nmb_KIKAKU_DOUBLEExit(TObject *Sender)
{

	TNumberEdit *ne = (TNumberEdit *)Sender;

    // 値の範囲チェックを行ないます
    if( ne->Value > 5 || ne->Value < 0 ){
    	MessageDlg("小数点以下桁数の指定範囲は、0～5以内です。", mtWarning,
                    TMsgDlgButtons() << mbOK , 0);
        if( ne->Value > 5 ){
            if( ne->Name == "Nmb_KIKAKU_DOUBLE" ){
        		Nmb_KIKAKU_DOUBLE->Text = "5";
			}
        	else {
        		Nmb_VALUE_DOUBLE->Text = "5";
        	}
        }
        else {
            if( ne->Name == "Nmb_KIKAKU_DOUBLE" ){
        		Nmb_KIKAKU_DOUBLE->Text = "0";
			}
        	else {
        		Nmb_VALUE_DOUBLE->Text = "0";
        	}
        }
    }

    // 「規格値」の小数点以下桁数の値を変更したら
    // 指定されている規格の小数点以下桁数の値をあわせます。
    if( ne->Name == "Nmb_KIKAKU_DOUBLE" ){
    	AnsiString	sBuf;

        // 「測定値」の小数点以下桁数は＋１します。
        sBuf = Nmb_KIKAKU_DOUBLE->Text;
        if( sBuf.ToIntDef(0) >= 0 && sBuf.ToIntDef(0) < 5 ){
        	sBuf = AnsiString(sBuf.ToIntDef(0) + 1);
        }
		Nmb_VALUE_DOUBLE->Text = sBuf;

		Nmb_KIKAKU_HANI_MIN->FPos   = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_HANI_MAX->FPos   = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MAX->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MID->FPos = Nmb_KIKAKU_DOUBLE->Value;
		Nmb_KIKAKU_KIJYUN_MIN->FPos = Nmb_KIKAKU_DOUBLE->Value;

        Nmb_KIKAKU_HANI_MIN->Text   = Nmb_KIKAKU_HANI_MIN->Text;
		Nmb_KIKAKU_HANI_MAX->Text   = Nmb_KIKAKU_HANI_MAX->Text;
		Nmb_KIKAKU_KIJYUN_MAX->Text = Nmb_KIKAKU_KIJYUN_MAX->Text;
		Nmb_KIKAKU_KIJYUN_MID->Text = Nmb_KIKAKU_KIJYUN_MID->Text;
		Nmb_KIKAKU_KIJYUN_MIN->Text = Nmb_KIKAKU_KIJYUN_MIN->Text;
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の指定方法「範囲指定」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_KIKAKU_SHITEI_HANIClick(TObject *Sender)
{
    Pnl_KIKAKU_HANI->Visible   = true;
    Pnl_KIKAKU_KIJYUN->Visible = false;
    Pnl_KIKAKU_MOJI->Visible   = false;
    Pnl_SYURUI->Enabled        = true;
	Pnl_MANMIN_PRT->Enabled    = false;
    Nmb_KIKAKU_DOUBLE->Enabled = true;
    //Pnl_VALUE->Enabled         = true;
    Rdo_KIKAKU_SYURUI_MINMAX->Font->Color = clBlack;
    Rdo_KIKAKU_SYURUI_MAX->Font->Color    = clBlack;
    Rdo_KIKAKU_SYURUI_MIN->Font->Color    = clBlack;
	Rdo_MANMIN_PRT_ON->Font->Color        = clGray;
	Rdo_MANMIN_PRT_OFF->Font->Color       = clGray;
	Nmb_KIKAKU_DOUBLE->Font->Color        = clBlack;
    //Rdo_VALUE_NORMAL->Font->Color         = clBlack;
    //Rdo_VALUE_KAKUDO->Font->Color         = clBlack;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の指定方法「基準指定」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_KIKAKU_SHITEI_KIJYUNClick(TObject *Sender)
{
    Pnl_KIKAKU_HANI->Visible   = false;
    Pnl_KIKAKU_KIJYUN->Visible = true;
    Pnl_KIKAKU_MOJI->Visible   = false;
    Pnl_SYURUI->Enabled        = true;
	Pnl_MANMIN_PRT->Enabled    = true;
    Nmb_KIKAKU_DOUBLE->Enabled = true;
    //Pnl_VALUE->Enabled         = true;
    Rdo_KIKAKU_SYURUI_MINMAX->Font->Color = clBlack;
    Rdo_KIKAKU_SYURUI_MAX->Font->Color    = clBlack;
    Rdo_KIKAKU_SYURUI_MIN->Font->Color    = clBlack;
	Rdo_MANMIN_PRT_ON->Font->Color        = clBlack;
	Rdo_MANMIN_PRT_OFF->Font->Color       = clBlack;
	Nmb_KIKAKU_DOUBLE->Font->Color        = clBlack;
    //Rdo_VALUE_NORMAL->Font->Color         = clBlack;
    //Rdo_VALUE_KAKUDO->Font->Color         = clBlack;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の指定方法「文字指定」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_KIKAKU_SHITEI_MOJIClick(TObject *Sender)
{
    Pnl_KIKAKU_HANI->Visible   = false;
    Pnl_KIKAKU_KIJYUN->Visible = false;
    Pnl_KIKAKU_MOJI->Visible   = true;
    Pnl_SYURUI->Enabled        = false;
	Pnl_MANMIN_PRT->Enabled    = false;
    Nmb_KIKAKU_DOUBLE->Enabled = false;
    //Pnl_VALUE->Enabled         = false;
    Rdo_KIKAKU_SYURUI_MINMAX->Font->Color = clGray;
    Rdo_KIKAKU_SYURUI_MAX->Font->Color    = clGray;
    Rdo_KIKAKU_SYURUI_MIN->Font->Color    = clGray;
	Rdo_MANMIN_PRT_ON->Font->Color        = clGray;
	Rdo_MANMIN_PRT_OFF->Font->Color       = clGray;
	Nmb_KIKAKU_DOUBLE->Font->Color        = clGray;
    //Rdo_VALUE_NORMAL->Font->Color         = clGray;
    //Rdo_VALUE_KAKUDO->Font->Color         = clGray;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の種類「上限下限両方」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_KIKAKU_SYURUI_MINMAXClick(TObject *Sender)
{
    Nmb_KIKAKU_HANI_MIN->Enabled	= true;
    Nmb_KIKAKU_HANI_MAX->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MIN->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MAX->Enabled	= true;
    Nmb_KIKAKU_HANI_MIN->Color		= clWindow;
    Nmb_KIKAKU_HANI_MAX->Color		= clWindow;
    Nmb_KIKAKU_KIJYUN_MIN->Color	= clWindow;
    Nmb_KIKAKU_KIJYUN_MAX->Color	= clWindow;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の種類「上限のみ」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_KIKAKU_SYURUI_MAXClick(TObject *Sender)
{
    Nmb_KIKAKU_HANI_MIN->Enabled	= false;
    Nmb_KIKAKU_HANI_MAX->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MIN->Enabled	= false;
    Nmb_KIKAKU_KIJYUN_MAX->Enabled	= true;
    Nmb_KIKAKU_HANI_MIN->Color		= clBtnFace;
    Nmb_KIKAKU_HANI_MAX->Color		= clWindow;
    Nmb_KIKAKU_KIJYUN_MIN->Color	= clBtnFace;
    Nmb_KIKAKU_KIJYUN_MAX->Color	= clWindow;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：規格の種類「下限のみ」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_KIKAKU_SYURUI_MINClick(TObject *Sender)
{
    Nmb_KIKAKU_HANI_MIN->Enabled	= true;
    Nmb_KIKAKU_HANI_MAX->Enabled	= false;
    Nmb_KIKAKU_KIJYUN_MIN->Enabled	= true;
    Nmb_KIKAKU_KIJYUN_MAX->Enabled	= false;
    Nmb_KIKAKU_HANI_MIN->Color		= clWindow;
    Nmb_KIKAKU_HANI_MAX->Color		= clBtnFace;
    Nmb_KIKAKU_KIJYUN_MIN->Color	= clWindow;
    Nmb_KIKAKU_KIJYUN_MAX->Color	= clBtnFace;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：項目の種類「出荷検査項目」クリックしたときに発生します。
//
//  機能説明
//    出荷検査項目として画面下を扱います（色変更＝水色）
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_TYPE_SYUKAClick(TObject *Sender)
{
	Pnl_t01->Color = (TColor)0x00FFEEDD;
	Pnl_t02->Color = (TColor)0x00FFEEDD;
	Pnl_t03->Color = (TColor)0x00FFEEDD;
	Pnl_t04->Color = (TColor)0x00FFEEDD;
	Pnl_t05->Color = (TColor)0x00FFEEDD;
	Pnl_t06->Color = (TColor)0x00FFEEDD;
	Pnl_t07->Color = (TColor)0x00FFEEDD;
	Pnl_t08->Color = (TColor)0x00FFEEDD;
	Pnl_t09->Color = (TColor)0x00FFEEDD;
	Pnl_t10->Color = (TColor)0x00FFEEDD;
	Pnl_t11->Color = (TColor)0x00FFEEDD;
	Pnl_t12->Color = (TColor)0x00FFEEDD;
	Pnl_t13->Color = (TColor)0x00FFEEDD;
	Pnl_t14->Color = (TColor)0x00FFEEDD;
	Pnl_t15->Color = (TColor)0x00FFEEDD;
	Pnl_t16->Color = (TColor)0x00FFEEDD;
	Pnl_t17->Color = (TColor)0x00FFEEDD;
	Pnl_t18->Color = (TColor)0x00FFEEDD;
	Pnl_t19->Color = (TColor)0x00FFEEDD;
	Pnl_t20->Color = (TColor)0x00FFEEDD;
	Pnl_t21->Color = (TColor)0x00FFEEDD;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：項目の種類「材料証明項目」クリックしたときに発生します。
//
//  機能説明
//    材料証明項目として画面下を扱います（色変更＝紫色）
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_TYPE_ZAIRYOClick(TObject *Sender)
{
    Pnl_t01->Color = (TColor)0x00FFE1FD;
    Pnl_t02->Color = (TColor)0x00FFE1FD;
    Pnl_t03->Color = (TColor)0x00FFE1FD;
    Pnl_t04->Color = (TColor)0x00FFE1FD;
    Pnl_t05->Color = (TColor)0x00FFE1FD;
    Pnl_t06->Color = (TColor)0x00FFE1FD;
    Pnl_t07->Color = (TColor)0x00FFE1FD;
    Pnl_t08->Color = (TColor)0x00FFE1FD;
    Pnl_t09->Color = (TColor)0x00FFE1FD;
    Pnl_t10->Color = (TColor)0x00FFE1FD;
    Pnl_t11->Color = (TColor)0x00FFE1FD;
    Pnl_t12->Color = (TColor)0x00FFE1FD;
    Pnl_t13->Color = (TColor)0x00FFE1FD;
    Pnl_t14->Color = (TColor)0x00FFE1FD;
    Pnl_t15->Color = (TColor)0x00FFE1FD;
    Pnl_t16->Color = (TColor)0x00FFE1FD;
    Pnl_t17->Color = (TColor)0x00FFE1FD;
	Pnl_t18->Color = (TColor)0x00FFE1FD;
	Pnl_t19->Color = (TColor)0x00FFE1FD;
	Pnl_t20->Color = (TColor)0x00FFE1FD;
	Pnl_t21->Color = (TColor)0x00FFE1FD;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：測定値の値表現「整数」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_VALUE_NORMALClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled        = true;
	Nmb_VALUE_DOUBLE->Font->Color    = clBlack;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：測定値の値表現「角度」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_VALUE_KAKUDOClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled        = true;
	Nmb_VALUE_DOUBLE->Font->Color    = clBlack;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：測定値の値表現「良/否」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_VALUE_OKClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled        = false;
	Nmb_VALUE_DOUBLE->Font->Color    = clGray;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：測定値の値表現「文字」クリックしたときに発生します。
//
//  機能説明
//    関連するコントロールの有効／無効を制御します
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_VALUE_TEXTClick(TObject *Sender)
{
    Nmb_VALUE_DOUBLE->Enabled        = false;
	Nmb_VALUE_DOUBLE->Font->Color    = clGray;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：出荷検査用StringGridの表示順（３種類）をクリックしたときに発生します。
//
//  機能説明
//    出荷検査用StringGridの表示順を変更します
//      ・測定項目マスター順
//      ・測定項目名称順
//      ・測定機器・測定項目名称順
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_List1_OrderClick(TObject *Sender)
{
    int				i, k, m;
	AnsiString		sBuf;
	TRadioButton	*rdo = (TRadioButton *)Sender;

    if( rdo->Name == "Rdo_List1_Order1" ){
        // ON
		Btn_UP1->Enabled   = true;
		Btn_DOWN1->Enabled = true;
        SGr_List->Options = SGr_List->Options << goRowMoving;

	    // 表示順でソートを行ないます
		for( i = 1; i < SGr_List->RowCount - 2; i++ ){
	    	for( k = i + 1; k < SGr_List->RowCount - 1; k++ ) {
	            if( SGr_List->Cells[14][i].ToIntDef(0) > SGr_List->Cells[14][k].ToIntDef(0) ){
                    sBuf = GridLineCopy( SGr_List, i);
					for( m = 1; m < SGr_List->ColCount; m++ ) {
						SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
                    }
                    GridLinePaste( SGr_List, k, sBuf);
	            }
			}
    	}

	} else {
        // OFF
		Btn_UP1->Enabled   = false;
		Btn_DOWN1->Enabled = false;
        SGr_List->Options = SGr_List->Options >> goRowMoving;

	    if( rdo->Name == "Rdo_List1_Order2" ){

		    // 測定項目順でソートを行ないます
			for( i = 1; i < SGr_List->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List->RowCount - 1; k++ ) {
		            if( SGr_List->Cells[1][i] > SGr_List->Cells[1][k] ){
	                    sBuf = GridLineCopy( SGr_List, i);
						for( m = 1; m < SGr_List->ColCount; m++ ) {
							SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List, k, sBuf);
		            }
				}
	    	}
		} else {

		    // 測定機器・測定項目順でソートを行ないます
			for( i = 1; i < SGr_List->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List->RowCount - 1; k++ ) {
		            if( SGr_List->Cells[15][i].ToIntDef(0) > SGr_List->Cells[15][k].ToIntDef(0) ){
	                    sBuf = GridLineCopy( SGr_List, i);
						for( m = 1; m < SGr_List->ColCount; m++ ) {
							SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List, k, sBuf);
		            } else {
		            	if( SGr_List->Cells[15][i] == SGr_List->Cells[15][k] &&
                        	SGr_List->Cells[1][i] > SGr_List->Cells[1][k] ){
	                    	sBuf = GridLineCopy( SGr_List, i);
							for( m = 1; m < SGr_List->ColCount; m++ ) {
								SGr_List->Cells[m][i] = SGr_List->Cells[m][k];
	                    	}
	                    	GridLinePaste( SGr_List, k, sBuf);
						}
                    }
				}
	    	}
        }
    }

	SGr_ListSelectCell( SGr_List, 1, SGr_List->Row, true);

}

//---------------------------------------------------------------------------
//
//  概要
//    OnClickイベント	：材料証明用StringGridの表示順（３種類）をクリックしたときに発生します。
//
//  機能説明
//    材料証明用StringGridの表示順を変更します
//      ・測定項目マスター順
//      ・測定項目名称順
//      ・測定機器・測定項目名称順
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Rdo_List2_OrderClick(TObject *Sender)
{
    int				i, k, m;
	AnsiString		sBuf;
	TRadioButton	*rdo = (TRadioButton *)Sender;

    if( rdo->Name == "Rdo_List2_Order1" ){
        // ON
		Btn_UP2->Enabled   = true;
		Btn_DOWN2->Enabled = true;
        SGr_List2->Options = SGr_List2->Options << goRowMoving;

	    // 表示順でソートを行ないます
		for( i = 1; i < SGr_List2->RowCount - 2; i++ ){
	    	for( k = i + 1; k < SGr_List2->RowCount - 1; k++ ) {
	            if( SGr_List2->Cells[14][i].ToIntDef(0) > SGr_List2->Cells[14][k].ToIntDef(0) ){
                    sBuf = GridLineCopy( SGr_List2, i);
					for( m = 1; m < SGr_List2->ColCount; m++ ) {
						SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
                    }
                    GridLinePaste( SGr_List2, k, sBuf);
	            }
			}
    	}

	} else {
        // OFF
		Btn_UP2->Enabled   = false;
		Btn_DOWN2->Enabled = false;
        SGr_List2->Options = SGr_List2->Options >> goRowMoving;

	    if( rdo->Name == "Rdo_List2_Order2" ){

		    // 測定項目順でソートを行ないます
			for( i = 1; i < SGr_List2->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List2->RowCount - 1; k++ ) {
		            if( SGr_List2->Cells[1][i] > SGr_List2->Cells[1][k] ){
	                    sBuf = GridLineCopy( SGr_List2, i);
						for( m = 1; m < SGr_List2->ColCount; m++ ) {
							SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List2, k, sBuf);
		            }
				}
	    	}
		} else {

		    // 測定機器・測定項目順でソートを行ないます
			for( i = 1; i < SGr_List2->RowCount - 2; i++ ){
		    	for( k = i + 1; k < SGr_List2->RowCount - 1; k++ ) {
		            if( SGr_List2->Cells[15][i].ToIntDef(0) > SGr_List2->Cells[15][k].ToIntDef(0) ){
	                    sBuf = GridLineCopy( SGr_List2, i);
						for( m = 1; m < SGr_List2->ColCount; m++ ) {
							SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
	                    }
	                    GridLinePaste( SGr_List2, k, sBuf);
		            } else {
		            	if( SGr_List2->Cells[15][i] == SGr_List2->Cells[15][k] &&
                        	SGr_List2->Cells[1][i] > SGr_List2->Cells[1][k] ){
	                    	sBuf = GridLineCopy( SGr_List2, i);
							for( m = 1; m < SGr_List2->ColCount; m++ ) {
								SGr_List2->Cells[m][i] = SGr_List2->Cells[m][k];
	                    	}
	                    	GridLinePaste( SGr_List2, k, sBuf);
						}
                    }
				}
	    	}
        }
    }
	SGr_ListSelectCell( SGr_List2, 1, SGr_List2->Row, true);

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：StringGridの指定行をバッファに保存します
//
//  機能説明
//    StringGridの指定行をバッファに保存します
//
//  パラメタ説明
//    TStringGrid* sg	：呼び出し元のTStringGridオブジェクト
//    int iCpyIndex		：複写する行NO
//
//  戻り値
//    AnsiString		：更新フラグ（複写した行が更新済みかどうか）
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GridLineCopy( TStringGrid* sg, int iCpyIndex)
{
	AnsiString sBuf;

	sBuf = sg->Cells[1][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KOMK_NM	,sBuf.c_str() );	//測定項目（日本語）
	sBuf = sg->Cells[2][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KOMK_ENG	,sBuf.c_str() );	//測定項目（英語）
	sBuf = sg->Cells[3][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKI_NM	,sBuf.c_str() );	//測定機器名称
	sBuf = sg->Cells[4][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.TANI		,sBuf.c_str() );	//単位
	sBuf = sg->Cells[6][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.SOKU_SU	,sBuf.c_str() );	//ｎ数（基本）
	sBuf = sg->Cells[7][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.VALUE_TYPE	,sBuf.c_str() );	//値表現
	sBuf = sg->Cells[8][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.SOKU_FLG	,sBuf.c_str() );	//測定項目の有無
	sBuf = sg->Cells[9][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.TOKU_FLG	,sBuf.c_str() );	//特別項目の有無
	sBuf = sg->Cells[10][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDYMD		,sBuf.c_str() );	//変更日
	sBuf = sg->Cells[12][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDCHR		,sBuf.c_str() );	//更新者（担当者コード）
	sBuf = sg->Cells[11][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDNAM		,sBuf.c_str() );	//更新者（名称）
	sBuf = sg->Cells[13][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KOMK_NO	,sBuf.c_str() );	//項目NO
	sBuf = sg->Cells[14][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.ORDER_NO	,sBuf.c_str() );	//表示順
	sBuf = sg->Cells[15][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKI_NO	,sBuf.c_str() );	//測定機器NO
	sBuf = sg->Cells[16][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_TYPE	,sBuf.c_str() );	//規格タイプ
	sBuf = sg->Cells[17][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_KIND	,sBuf.c_str() );	//規格種類
	sBuf = sg->Cells[18][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_DECI	,sBuf.c_str() );	//規格小数点以下桁数
	sBuf = sg->Cells[19][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_NUM1	,sBuf.c_str() );	//規格値１
	sBuf = sg->Cells[20][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_NUM2	,sBuf.c_str() );	//規格値２
	sBuf = sg->Cells[21][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_NUM3	,sBuf.c_str() );	//規格値３
	sBuf = sg->Cells[22][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_STR	,sBuf.c_str() );	//規格文字
	sBuf = sg->Cells[23][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.KIKA_PRT	,sBuf.c_str() );	//上限下限値の印刷
	sBuf = sg->Cells[24][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.VALUE_DECI	,sBuf.c_str() );	//測定値小数点以下桁数
	sBuf = sg->Cells[25][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.ADDYMD		,sBuf.c_str() );	//登録日
	sBuf = sg->Cells[26][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.ADDTIM		,sBuf.c_str() );	//登録時間
	sBuf = sg->Cells[27][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDTIM		,sBuf.c_str() );	//更新時間
	sBuf = sg->Cells[28][iCpyIndex];
	strcpy( tmpKSM11_12_DATA.UPDCNT		,sBuf.c_str() );	//更新回数
	sBuf = sg->Cells[29][iCpyIndex];						//更新フラグ
	
	return sBuf;	// 更新フラグ
}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：バッファに保存されたStringGridデータをStringGridの指定行に復元します
//
//  機能説明
//    バッファに保存されたStringGridデータをStringGridの指定行に復元します
//
//  パラメタ説明
//    TStringGrid* sg	：呼び出し元のTStringGridオブジェクト
//    int iPstIndex		：復元する行NO
//    AnsiString sUpdFlg：復元する行に設定する更新フラグ
//
//  戻り値
//    なし。
//
//  備考
//    なし。
//
//---------------------------------------------------------------------------
void __fastcall TForm1::GridLinePaste( TStringGrid* sg, int iPstIndex, AnsiString sUpdFlg)
{

	sg->Cells[1][iPstIndex] = tmpKSM11_12_DATA.KOMK_NM		;	//測定項目（日本語）
	sg->Cells[2][iPstIndex] = tmpKSM11_12_DATA.KOMK_ENG		;	//測定項目（英語）
	sg->Cells[3][iPstIndex] = tmpKSM11_12_DATA.KIKI_NM		;	//測定機器名称
	sg->Cells[4][iPstIndex] = tmpKSM11_12_DATA.TANI			;	//単位
	sg->Cells[5][iPstIndex] = ""							;	//規格（基本）　※再描画する為に必要です。
	sg->Cells[6][iPstIndex] = tmpKSM11_12_DATA.SOKU_SU		;	//ｎ数（基本）
	sg->Cells[7][iPstIndex] = tmpKSM11_12_DATA.VALUE_TYPE	;	//値表現
	sg->Cells[8][iPstIndex] = tmpKSM11_12_DATA.SOKU_FLG		;	//測定項目の有無
	sg->Cells[9][iPstIndex] = tmpKSM11_12_DATA.TOKU_FLG		;	//特別項目の有無
	sg->Cells[10][iPstIndex] = tmpKSM11_12_DATA.UPDYMD		;	//変更日
	sg->Cells[11][iPstIndex] = tmpKSM11_12_DATA.UPDNAM		;	//更新者（名称）
	sg->Cells[12][iPstIndex] = tmpKSM11_12_DATA.UPDCHR		;	//更新者（担当者コード）
	sg->Cells[13][iPstIndex] = tmpKSM11_12_DATA.KOMK_NO		;	//項目NO
	sg->Cells[14][iPstIndex] = tmpKSM11_12_DATA.ORDER_NO	;	//表示順
	sg->Cells[15][iPstIndex] = tmpKSM11_12_DATA.KIKI_NO		;	//測定機器NO
	sg->Cells[16][iPstIndex] = tmpKSM11_12_DATA.KIKA_TYPE	;	//規格タイプ
	sg->Cells[17][iPstIndex] = tmpKSM11_12_DATA.KIKA_KIND	;	//規格種類
	sg->Cells[18][iPstIndex] = tmpKSM11_12_DATA.KIKA_DECI	;	//規格小数点以下桁数
	sg->Cells[19][iPstIndex] = tmpKSM11_12_DATA.KIKA_NUM1	;	//規格値１
	sg->Cells[20][iPstIndex] = tmpKSM11_12_DATA.KIKA_NUM2	;	//規格値２
	sg->Cells[21][iPstIndex] = tmpKSM11_12_DATA.KIKA_NUM3	;	//規格値３
	sg->Cells[22][iPstIndex] = tmpKSM11_12_DATA.KIKA_STR	;	//規格文字
	sg->Cells[23][iPstIndex] = tmpKSM11_12_DATA.KIKA_PRT	;	//上限下限値の印刷
	sg->Cells[24][iPstIndex] = tmpKSM11_12_DATA.VALUE_DECI	;	//測定値小数点以下桁数
	sg->Cells[25][iPstIndex] = tmpKSM11_12_DATA.ADDYMD		;	//登録日
	sg->Cells[26][iPstIndex] = tmpKSM11_12_DATA.ADDTIM		;	//登録時間
	sg->Cells[27][iPstIndex] = tmpKSM11_12_DATA.UPDTIM		;	//更新時間
	sg->Cells[28][iPstIndex] = tmpKSM11_12_DATA.UPDCNT		;	//更新回数
    if( sUpdFlg != "" ){
		sg->Cells[29][iPstIndex] = sUpdFlg				   	;	//更新フラグの設定
    }

}

//---------------------------------------------------------------------------
//
//  概要
//    自作関数			：コマンドライン引数を分離（部署名、ユーザ名など）
//
//  機能説明
//    プログラム起動時のコマンドライン引数を分離し変数に設定します。
//    ユーザコード、ユーザ名、部署コード、部署名を抽出します
//
//  パラメタ説明
//    AnsiString str	：コマンドライン文字列
//
//  戻り値
//    なし。
//
//  備考
//    プログラム起動時に使用
//
//---------------------------------------------------------------------------
void __fastcall TForm1::ExtractCode(AnsiString str)
{
    int i,n1,m,strlen;

    //初期化
    USER_COD = 0;
    USER_NAM = "";
    BUMO_COD = "";
    BUMO_NAM = "";

    strlen = str.Length();
    n1 = m = 1;

    for ( i = 1; i <= strlen; i++ ) {
        //区切り記号","の検索
        if ( str.SubString(i,1) == "," ) {
            if ( n1 < i ) {
            //n1=iの時は文字列NULL
                switch(m){
                //変数に文字列代入
                    case 1:
                    //USER_COD
                        USER_COD = StrToInt(str.SubString(n1,i - n1));
                        break;
                    case 2:
                    //USER_NAM
                        USER_NAM = str.SubString(n1,i - n1);
                        break;
                    case 3:
                    //BUMO_COD
                        BUMO_COD = str.SubString(n1,i - n1);
                        break;
                    case 4:
                    //BUMO_NAM
                        BUMO_NAM = str.SubString(n1,i - n1);
                        break;
                    default:
                        break;
                }

            }
            //次の文字列開始位置
            n1 = i + 1;
            m++;

        }
    }
    if ( m <= 4 ) {
        //BUMO_NAM
        BUMO_NAM = str.SubString(n1,strlen - n1 + 1);
    }

    // 初期化表示
    PnlBumCode->Caption = BUMO_COD;
    PnlBumName->Caption = BUMO_NAM;
    PnlTanCode->Caption = IntToStr(USER_COD);
    PnlTanName->Caption = USER_NAM;

}

//---------------------------------------------------------------------------
//
//  概要
//    OnChangeイベント	：編集コントロールのテキストに変更が加えられたときに発生します。
//
//  機能説明
//    入力文字(シングルコーテーション、半角カンマ)のチェックを行ないます。
//
//  パラメタ説明
//    TObject *Sender	：呼び出し元のVCLオブジェクト
//
//  戻り値
//    なし。
//
//  備考
//    シングルコーテーションはＤＢ登録時にエラーが発生する
//    ので全角のシングルコーテーションに変換します
//
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt_ALLChange(TObject *Sender)
{

    int			i;
    AnsiString	sBuf;
    TEdit* edt = dynamic_cast<TEdit*>(Sender);


    sBuf = edt->Text;

    // シングルコーテーションはＤＢ登録時にエラーが発生する
    // ので全角のシングルコーテーションに変換します
    i = sBuf.AnsiPos("'");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( edt->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("’",i);
    	}
        edt->Text = sBuf;
        edt->SelStart = i + 1;
    }

    // 半角カンマはＤＢ登録時にエラーが発生する
    // ので全角のカンマに変換します
    i = sBuf.AnsiPos(",");
    if( i > 0 ){
        sBuf.Delete( i, 1);
        if( edt->MaxLength >= sBuf.Length() + 2 ){
        	sBuf.Insert("，",i);
    	}
        edt->Text = sBuf;
        edt->SelStart = i + 1;
    }
}


